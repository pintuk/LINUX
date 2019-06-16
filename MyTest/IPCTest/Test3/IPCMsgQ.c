
#include "IPCMsgQ.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

 
#define MAX_MSG_SIZE 		1024
#define MAX_QUEUE_COUNT		10

#define MESSAGE_TYPE		1
#define QUEUENAME_PREFIX 	"/tmp/%s"
#define MAX_PATH 		255


//static msgqd_t msgqd_list[MAX_QUEUE_COUNT] = {NULL,};

struct msgbuf
{
	long    mtype;   /* message type, must be > 0 */
	unsigned char message[MAX_MSG_SIZE];
};




int PeekMessage( long qid, long type )
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


BOOL OpenMessageQ(int *mqId, const char * name)
{
	char msgqname[MAX_PATH] = {0};
	key_t key;
	char proj_id = 'v';

	if(NULL == name)
	{
		fprintf(stderr,"ERROR : OpenMessageQ : Invalid Parameter\n");
		return FALSE;
	}
	sprintf(msgqname,QUEUENAME_PREFIX, name);

	if(open(msgqname, O_CREAT | O_TRUNC, 0666) == -1)
	{
	    fprintf(stderr,"open (%s): Failed to open this file, reason = (%s) \n",msgqname, strerror(errno));
	    return FALSE;
	}

	key = ftok(msgqname, proj_id);
	if(-1 == key)
	{
		fprintf(stderr,"ERROR : OpenMessageQ : (%s): Failed to create Unique Key = %d (%s)\n",name, errno, strerror(errno));
		return FALSE;
	}

    	if ( (*mqId = msgget(key, IPC_CREAT|0666)) == -1 )		//  0660 -> Permision.
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

		*mqId = -1;
		mqId = NULL;
		return FALSE;
	}

	// Flush All previous stored messages from Queues. This is important in case of crashes
	FlushMessage(*mqId);
	printf("---------- All MESSAGES FLUSHED ----------\n");

	return  TRUE;
}


BOOL CloseMessageQ(int *mqId)
{
	if(mqId == NULL || *mqId == -1)
	{
		fprintf(stderr,"ERROR : CloseMessageQ : Queue is already closed\n");
		return FALSE;
	}

	if(msgctl(*mqId, IPC_RMID, 0) == -1)
	{
		fprintf(stderr,"ERROR : CloseMessageQ : Failed :  Cause = (%s)\n",strerror(errno));
		return FALSE;
	}
	*mqId = -1;
	mqId = NULL;
	
	return TRUE;

}



BOOL FlushMessage(int mqId)
{
	struct msgbuf  buf = {0,};
	int r = -1;
	#define MSGTYPE_ALL	0   /* This will remove all messages from beginning irrespective of the type */

	if(mqId == -1)
	{
		fprintf(stderr,"ERROR : FlushMessage : Queue does not exists \n");
		return FALSE;
	}

	while(PeekMessage( mqId, MSGTYPE_ALL) == TRUE)		// while queue is not empty
	{
		do {
			r = msgrcv(mqId, (struct msgbuf *)&buf, sizeof(struct msgbuf) - sizeof(long), MSGTYPE_ALL, 0);
		} while ( r == -1 && errno == EINTR);
		
		if ( r == -1 )
		{
			fprintf(stderr,"ERROR : FlushMessage : msgrcv FAILED - errorno=%d (%s)\n", errno, strerror(errno));
		}
	}

	return TRUE;
}


BOOL SendMessage(int mqId, const char *msg_ptr, int msg_len, long msgtype)
{
	struct msgbuf buf = {0,};
	int r = -1;

	if(mqId == -1)
	{
		fprintf(stderr,"ERROR : SendMessage : Queue does not exists \n");
		return FALSE;
	}

	buf.mtype = msgtype;  //MESSAGE_TYPE;

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
		r = msgsnd( mqId, (struct msgbuf *)&buf, sizeof(struct msgbuf) - sizeof(long), IPC_NOWAIT);
	} while ( r == -1 && errno == EINTR);

	if ( r == -1 )
	{
		fprintf(stderr,"ERROR : SendMessage (%d)  Failed :  cause = %s",mqId,strerror(errno));
		return FALSE;
	}

	return TRUE;
}



BOOL ReceiveMessage(int mqId, char *msg_ptr, int *msg_len, long msgtype)
{
	struct msgbuf buf = {0,};
	int r = -1;

	if(mqId == -1)
	{
		fprintf(stderr,"ERROR : ReceiveMessage : Queue does not exists \n");
		return FALSE;
	}

	buf.mtype = msgtype;  //MESSAGE_TYPE;

	do {
		r = msgrcv( mqId, (struct msgbuf *)&buf, sizeof(struct msgbuf) - sizeof(long), buf.mtype, 0);		
	} while ( r == -1 && errno == EINTR);

	if (r == -1)
	{
		fprintf(stderr,"ERROR : ReceiveMessage (%d) Failed : %s",mqId,strerror(errno));
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



BOOL MsgGetAttr(int mqId, struct msgq_attr *attr)
{
	return FALSE;
}


BOOL MsgSetAttr(int mqId, struct msgq_attr *newattr, struct msgq_attr *oldattr)
{
	return FALSE;
}

