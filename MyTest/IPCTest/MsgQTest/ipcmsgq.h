#ifndef __IPCMSGQ_H__
#define __IPCMSGQ_H__

typedef int BOOL;

#define TRUE 	1
#define FALSE 	0


BOOL openMsgQ(int *msgId, const char *qname);
void closeMsgQ(int msgId);
BOOL sendMsgQ(int msgId, void *buf, int len, long mtype);
BOOL receiveMsgQ(int msgId, void *buf, int len, long mtype);
void flushMsgQ(int *msgIq);


#endif
