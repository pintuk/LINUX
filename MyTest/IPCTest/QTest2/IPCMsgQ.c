
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

 
#define MAX_MSG_SIZE 		1024
#define MAX_QUEUE_COUNT		10

#define MESSAGE_TYPE		1
#define QUEUENAME_PREFIX 	"/tmp/%s"
#define MAX_PATH 		255


//static msgqd_t msgqd_list[MAX_QUEUE_COUNT] = {NULL,};

typedef struct MsgBuf
{
	long    mtype;   /* message type, must be > 0 */
	char message[1024];
}MsgBuf;




int PeekMsgQ( long qid, long type )
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


BOOL OpenMsgQ(int *mqId, const char * name)
{
	char msgqname[MAX_PATH] = {0};
	key_t key;
	char proj_id = 'U';

	if(NULL == name)
	{
		fprintf(stderr,"ERROR : OpenMsgQ : Invalid Parameter\n");
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
		fprintf(stderr,"ERROR : OpenMsgQ : (%s): Failed to create Unique Key = %d (%s)\n",name, errno, strerror(errno));
		return FALSE;
	}

	/* NOTE : The unique "key" (to the whole system not just this process) is required only if you want to communicate */
	/*            between 2 totally different processes                                                                                           */
	/*            For local sharing within the process we can use "IPC_PRIVATE" in place of key                                     */
	/*            Even in case of child process IPC_PRIVATE should work                                                                   */
	if ( (*mqId = msgget(key, IPC_CREAT|0666)) == -1 )		//  0666 -> all rw Permision.
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
	FlushMsgQ(*mqId);
	//printf("---------- All MESSAGES FLUSHED ----------\n");

	return  TRUE;
}


BOOL CloseMsgQ(int *mqId)
{
	if(mqId == NULL || *mqId == -1)
	{
		fprintf(stderr,"ERROR : CloseMsgQ : Queue is already closed\n");
		return FALSE;
	}

	if(msgctl(*mqId, IPC_RMID, 0) == -1)
	{
		//fprintf(stderr,"ERROR : CloseMsgQ : Failed :  Cause = (%s)\n",strerror(errno));
		//return FALSE;
	}
	*mqId = -1;
	mqId = NULL;
	
	return TRUE;

}



BOOL FlushMsgQ(int mqId)
{
	MsgBuf  buf = {0,};
	int r = -1;
	#define MSGTYPE_ALL	0   /* This will remove all messages from beginning irrespective of the type */

	if(mqId == -1)
	{
		fprintf(stderr,"ERROR : FlushMessage : Queue does not exists \n");
		return FALSE;
	}

	while(PeekMsgQ( mqId, MSGTYPE_ALL) == TRUE)		// while queue is not empty
	{
		do {
			r = msgrcv(mqId, (MsgBuf *)&buf, sizeof(MsgBuf) - sizeof(long), MSGTYPE_ALL, 0);
		} while ( r == -1 && errno == EINTR);
		
		if ( r == -1 )
		{
			fprintf(stderr,"ERROR : FlushMessage : msgrcv FAILED - errorno=%d (%s)\n", errno, strerror(errno));
		}
	}

	return TRUE;
}


BOOL SendMsgQ(int mqId, const char *msg_ptr, int msg_len, long msgtype)
{
	MsgBuf buf = {0,};
	int r = -1;

	if(mqId == -1)
	{
		fprintf(stderr,"ERROR : SendMessage : Queue does not exists \n");
		return FALSE;
	}
	if(msgtype <= 0)
	{
		fprintf(stderr,"ERROR : SendMessage : Failed : msgtype : %ld\n",msgtype);
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
		return FALSE;
	}
	printf("Message : %s\n",buf.message);
	do {
		r = msgsnd( mqId, (MsgBuf *)&buf, sizeof(MsgBuf) - sizeof(long), IPC_NOWAIT);
	} while ( r == -1 && errno == EINTR);

	if ( r == -1 )
	{
		fprintf(stderr,"ERROR : SendMessage (%d)  Failed :  cause = %s\n",mqId,strerror(errno));
		return FALSE;
	}

	return TRUE;
}



BOOL ReceiveMsgQ(int mqId, char *msg_ptr, int *msg_len, long msgtype)
{
	MsgBuf buf = {0,};
	int r = -1;

	if(mqId == -1)
	{
		fprintf(stderr,"ERROR : ReceiveMessage : Queue does not exists \n");
		return FALSE;
	}
        if(msgtype <= 0)
        {
                fprintf(stderr,"ERROR : ReceiveMsgQ : Failed : msgtype : %ld\n",msgtype);
                return FALSE;
        }

	buf.mtype = msgtype;  //MESSAGE_TYPE;

	do {
		r = msgrcv( mqId, (MsgBuf *)&buf, sizeof(MsgBuf) - sizeof(long), buf.mtype, 0);		
	} while ( r == -1 && errno == EINTR);

	if (r == -1)
	{
		fprintf(stderr,"ERROR : ReceiveMessage (%d) Failed : %s\n",mqId,strerror(errno));
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



BOOL GetAttrMsgQ(int mqId, struct msgq_attr *attr)
{
	return FALSE;
}


BOOL SetAttrMsgQ(int mqId, struct msgq_attr *newattr, struct msgq_attr *oldattr)
{
	return FALSE;
}

