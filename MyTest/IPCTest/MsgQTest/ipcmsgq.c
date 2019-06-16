#include "ipcmsgq.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<errno.h>


//const key_t MSGKEY = 1234;
const int PERMS = 0666;

const char uniqueID = 'U';

typedef struct MsgBuf {
	long mtype;
	char data[1024];
}MsgBuf;

//int msgqid = -1;
#define QUEUE_PREFIX	"/tmp/%s"
char filename[255];


int PeekMsgQ( long qid, long type )
{
    int  r = -1;

        do {
                r = msgrcv( qid, NULL, 0, type,  IPC_NOWAIT);
        } while ( r == -1 && errno == EINTR);


    if( r == -1) {
        if(errno == E2BIG)
		return TRUE;            // if queue is not empty, return true
    }

    return FALSE;
}


void flushMsgQ(int *msgId)
{
	MsgBuf msg;
	int err = -1;
	char buf[1024];
	int len=0;

	msg.mtype = 0;
	len = sizeof(MsgBuf) - sizeof(long);

	do {
                err = msgrcv(*msgId, &msg, len, 0, IPC_NOWAIT);
        } while(err == -1 && ((errno == EINTR) || (errno == E2BIG)) );

}


BOOL openMsgQ(int *msgId, const char *qname)
{
	key_t key;

	sprintf(filename,QUEUE_PREFIX,qname);

	creat(filename, PERMS);	

	if ((key = ftok(filename, uniqueID)) == -1) {
		fprintf(stderr,"openMsgQ - ftok - Failed : %s\n",(char *)strerror(errno));
		return FALSE;
	}
	if ((*msgId = msgget(key, PERMS | IPC_CREAT)) == -1) {
		fprintf(stderr,"openMsgQ - msgget - Failed : %s\n",(char *)strerror(errno));
		return FALSE;
	}
	//flushMsgQ(msgId);
	return TRUE;
}

void closeMsgQ(int msgId)
{
	flushMsgQ(&msgId);
	if (msgctl(msgId, IPC_RMID, NULL) == -1) {
		//fprintf(stderr,"closeMsgQ - msgctl - Failed : %s\n",(char *)strerror(errno));
	}
	msgId = -1;
	remove(filename);
}

BOOL sendMsgQ(int msgId, void *buf, int len, long mtype)
{
	MsgBuf msg;
	int err = -1;
	
	msg.mtype = mtype;
	memcpy(msg.data, buf, len);

	len = sizeof(MsgBuf) - sizeof(long);
	do {
		err = msgsnd(msgId, &msg, (len), IPC_NOWAIT);
	} while(err == -1 && errno == EINTR);

	if(err == -1) {
		fprintf(stderr,"sendMsgQ - msgsnd - Failed : %s\n",(char *)strerror(errno));
		return FALSE;
	}
	return TRUE;
}


BOOL receiveMsgQ(int msgId, void *buf, int len, long mtype)
{
	MsgBuf msg;
	int err = -1;

	msg.mtype = mtype;
	memset(msg.data,0,sizeof(msg.data));
	len = sizeof(MsgBuf) - sizeof(long);
	do {
                err = msgrcv(msgId, &msg, len, mtype, 0);
        } while(err == -1 && errno == EINTR);
	
	memcpy(buf,msg.data,len);

        if(err == -1) {
                fprintf(stderr,"receiveMsgQ - msgrcv - Failed : %s\n",(char *)strerror(errno));
                return FALSE;
        }
        return TRUE;
}


