#ifndef __IPCMSGQ_H
#define __IPCMSGQ_H


#include "commontypes.h"


#define	VT_MAIN_QUEUE_NAME	"VTMAINQ"
#define	VT_UI_QUEUE_NAME	"VTUIQ"
#define VT_APP_MAX_MESSAGE	100

void * VTMainQ;
void * VTUIQ;


typedef struct MSGQ{
	BOOL status;
	int qId;
	int evId;
	char *name;
	unsigned short refCount;
}msgQInfo;
typedef msgQInfo * msgqd_t;


#define msgq_isValid(x) ((NULL != (x))?TRUE:FALSE)


enum MQ_FLAGS{
	MQ_O_RDONLY =0x01,
	MQ_O_WRONLY = 0x02, 
	MQ_O_RDWR = 0x04,
	MQ_O_NONBLOCK=0x08,
	MQ_O_CREAT=0x10,
	MQ_O_EXCL = 0x20
};

    
struct msgq_attr {
    long msgq_flags;       /* Flags: 0 or MQ_O_NONBLOCK */
    long msgq_maxmsg;      /* Max. # of messages on queue */
    long msgq_msgsize;     /* Max. message size (bytes) */
    long msgq_curmsgs;     /* # of messages currently in queue */
};


#ifdef __cplusplus
extern "C" {
#endif
msgqd_t OpenMessageQ(const char * name, struct msgq_attr*attr);
BOOL CloseMessageQ(msgqd_t mqdes);
BOOL SendMessage(msgqd_t mqdes, const char *msg_ptr, int msg_len, unsigned msg_prio);
BOOL ReceiveMessage(msgqd_t mqdes, char *msg_ptr, int *msg_len, unsigned *msg_prio);
BOOL MsgGetAttr(msgqd_t mqdes, struct msgq_attr *attr);
BOOL MsgSetAttr(msgqd_t mqdes, struct msgq_attr *newattr,  struct msgq_attr *oldattr);
BOOL FlushMessage(msgqd_t mqdes);

#ifdef __cplusplus
}
#endif

#endif /*__IPCMSGQ_H  End */

