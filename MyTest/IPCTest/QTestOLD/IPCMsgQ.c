
#include "IPCMsgQ.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

 
#define MSGQ_BASE_PORT 43000
#define MAX_MSG_SIZE 1024
#define MAX_QUEUE_COUNT  10 

static msgqd_t msgqd_list[MAX_QUEUE_COUNT] = {NULL,};

struct msgbuf
{
	long    mtype;   /* message type, must be > 0 */
	unsigned char message[MAX_MSG_SIZE];
};

#define MESSAGE_TYPE	1
#define QUEUENAME_PREFIX "/tmp/%s"
#define MAX_PATH 255



int PeekMessage( int qid, long type )
{
    int  r = -1;

	do {
		r = msgrcv( qid, NULL, 0, type,  IPC_NOWAIT);		
	} while ( r == -1 && errno == EINTR);
		

    if( r == -1)
    {
        if(errno == E2BIG)
			return TRUE;		// if queue is not empty, return true
    }

    return FALSE;
}


msgqd_t OpenMessageQ(const char * name,  struct msgq_attr*attr)
{
	msgqd_t mqdes;
	char msgqname[MAX_PATH] = {0};

	int index =0;
	key_t key;
	char proj_id = 'v';
	int len = 0;

	if(NULL == name || NULL == attr)
	{
		fprintf(stderr,"ERROR : OpenMessageQ : Invalid Parameter\n");
		return NULL;
	}

	for(index=0;index < MAX_QUEUE_COUNT;index++)
	{
		if((NULL != msgqd_list[index]) && (!strcmp(msgqd_list[index]->name,name)))
		{
			msgqd_list[index]->refCount++;

			return msgqd_list[index];
		}
	}

	sprintf(msgqname,QUEUENAME_PREFIX, name);

	if(open(msgqname, O_CREAT | O_TRUNC) == -1)
	{
	    fprintf(stderr,"ERROR : OpenMessageQ (%s): Failed to open a file = %d (%s)\n",name, errno, strerror(errno));
	    return NULL;
	}

	key = ftok(msgqname, proj_id);

	if(-1 == key)
	{
		fprintf(stderr,"ERROR : OpenMessageQ : (%s): Failed to create Unique Key = %d (%s)\n",name, errno, strerror(errno));
		return NULL;
	}
	else
	{
		//fprintf(stderr,"SUCCESS : OpenMessageQ : Key 0x%x for %s\n",key, name);
	}

	mqdes =(msgQInfo*) malloc(sizeof(msgQInfo));
	if(NULL == mqdes)
	{
		fprintf(stderr,"ERROR : OpenMessageQ : malloc(msgQInfo) - Failed - (%s)\n",strerror(errno));
		return NULL;
	}

    if ( (mqdes->qId = msgget(key, IPC_CREAT|0666)) == -1 )		//  0660 -> Permision.
	{
		switch(errno)
		{
			case EEXIST :
				fprintf(stderr,"ERROR : msgget - %s\n",strerror(errno));
			break;
			case EIDRM  :
				fprintf(stderr,"ERROR : msgget - %s\n",strerror(errno));
			break;
			case ENOENT  :
				fprintf(stderr,"ERROR : msgget - %s\n",strerror(errno));
			break;
			case ENOMEM  :
				fprintf(stderr,"ERROR : msgget - %s\n",strerror(errno));
			break;
			case ENOSPC  :
				fprintf(stderr,"ERROR : msgget - %s\n",strerror(errno));
				system("ipcs -q");
				printf("\n");
			break;
			default:
				fprintf(stderr,"ERROR : msgget - %s\n",strerror(errno));
			break;
		}

			free(mqdes);
			return NULL;
	}

	len = strlen(name);

	mqdes->name = malloc(len+1);
	strcpy(mqdes->name,name);


	for(index=0;index<MAX_QUEUE_COUNT;index++)
	{
		if((NULL == msgqd_list[index]) )
		{
			msgqd_list[index]= mqdes;
			msgqd_list[index]->refCount = 1;
			break;
		}
	}

	// Flush All previous stored messages from Queues. This is important in case of crashes
	FlushMessage(mqdes);
	printf("---------- All MESSAGES FLUSHED ----------\n");

	//return  (MSGQ_T)mqdes;
	return  mqdes;
}


BOOL CloseMessageQ(msgqd_t mqdes)
{
	int index=0;
	if(mqdes == NULL)
	{
		fprintf(stderr,"ERROR : CloseMessageQ : Queue is already closed\n");
		return FALSE;
	}

	mqdes->refCount--;
	if( mqdes->refCount != 0)
	{
		return TRUE;
	}
	
	for(index=0;index<MAX_QUEUE_COUNT;index++)
	{
		if((mqdes == msgqd_list[index]) )
		{
			if (0 != mqdes->qId &&  msgctl(mqdes->qId, IPC_RMID, 0)==-1)
			{
				fprintf(stderr,"ERROR : CloseMessageQ : Failed :  Cause = (%s)\n",strerror(errno));
				return FALSE;
			}
			else
			{
				//fprintf(stderr,"SUCCESS : CloseMessageQ : Closed\n");
			}

			free( mqdes->name );
			mqdes->name = NULL;
			mqdes->qId = -1;
			mqdes->refCount = 0;
			free(mqdes);
			msgqd_list[index]= NULL;
			mqdes = NULL;
			return TRUE;
		}
	} // end for


	return TRUE;

}



BOOL FlushMessage(msgqd_t mqdes)
{
	struct msgbuf  buf = {0,};
	int r = -1;

	if(mqdes == NULL)
	{
		fprintf(stderr,"ERROR : FlushMessage : Queue does not exists \n");
		return FALSE;
	}

	while(PeekMessage( mqdes->qId, 1 ) == TRUE)		// while queue is not empty
	{
		do {
			r = msgrcv(mqdes->qId, (struct msgbuf *)&buf, sizeof(struct msgbuf) - sizeof(long), MESSAGE_TYPE, 0);
		} while ( r == -1 && errno == EINTR);
		
		if ( r == -1 )
		{
			fprintf(stderr,"ERROR : FlushMessage : msgrcv FAILED - errorno=%d (%s)\n", errno, strerror(errno));
		}
	}

	return TRUE;
}


BOOL SendMessage(msgqd_t mqdes, const  char *msg_ptr, int msg_len, unsigned msg_prio)
{
	//MSGQ *mqdes = (MSGQ *)hQueue;
	struct msgbuf buf = {0,};
	int r = -1;

	if(mqdes == NULL)
	{
		fprintf(stderr,"ERROR : SendMessage : Queue does not exists \n");
		return FALSE;
	}

	buf.mtype = MESSAGE_TYPE;

	if (msg_len > MAX_MSG_SIZE)
	{
		fprintf(stderr,"ERROR : SendMessage : Failed - msg_len is greter than MAX_MSG_SIZE=%d\n", MAX_MSG_SIZE);
		return FALSE;
	}

	if (NULL != msg_ptr)
	{
		memcpy(&(buf.message),msg_ptr, msg_len);
	}
	else
	{
		fprintf(stderr,"ERROR : SendMessage : msg_ptr is NULL\n");
	}

	do {
		r = msgsnd( mqdes->qId, (struct msgbuf *)&buf, sizeof(struct msgbuf) - sizeof(long), IPC_NOWAIT);
	} while ( r == -1 && errno == EINTR);

	if ( r == -1 )
	{
		fprintf(stderr,"ERROR : SendMessage (%s)  Failed :  cause = %s",mqdes->name,strerror(errno));
		return FALSE;
	}

	return TRUE;
}



BOOL ReceiveMessage(msgqd_t mqdes, char *msg_ptr, int *msg_len, unsigned *msg_prio)
{
	struct msgbuf buf = {0,};
	int r = -1;

	if(mqdes == NULL)
	{
		fprintf(stderr,"ERROR : ReceiveMessage : Queue does not exists \n");
		return FALSE;
	}

	buf.mtype = MESSAGE_TYPE;

	do {
		r = msgrcv( mqdes->qId, (struct msgbuf *)&buf, sizeof(struct msgbuf) - sizeof(long), MESSAGE_TYPE, 0);		
	} while ( r == -1 && errno == EINTR);

	if (r == -1)
	{
		fprintf(stderr,"ERROR : ReceiveMessage (%s) Failed : %s",mqdes->name,strerror(errno));
		return FALSE;
	}

	if (*msg_len < MAX_MSG_SIZE)
	{
		memcpy(msg_ptr,&buf.message, *msg_len);
		return TRUE;
	}

	*msg_len = 0;
	fprintf(stderr,"ERROR : ReceiveMessage -  Failed - msg_len is greter than MAX_MSG_SIZE\n");

	return FALSE;
}



BOOL MsgGetAttr(msgqd_t mqdes, struct msgq_attr *attr)
{
	return FALSE;
}


BOOL MsgSetAttr(msgqd_t mqdes, struct msgq_attr *newattr,
                 struct msgq_attr *oldattr)
{
	return FALSE;
}

