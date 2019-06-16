#ifndef __IPCMSGQ_H
#define __IPCMSGQ_H



#define TRUE    1
#define FALSE   0

typedef int BOOL;


typedef struct QMsg {
        long mtype;
	//int type;
        //int len;
        unsigned char buffer[255];
}QMsg;

typedef struct MSGQ{
	long qId;
	char *qname;
}msgQInfo;
typedef msgQInfo * msgqd_t;

//typedef int * MSGQId;


#define is_msgQ_valid(x) ( ((NULL != (x)) || ((x) >= 0) )?TRUE:FALSE)


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


//#ifdef __cplusplus
//extern "C" {
//#endif
BOOL OpenMsgQ(int* mqId, const char * name);
BOOL CloseMsgQ(int* mqId);
BOOL SendMsgQ(int mqId, const char *msg_ptr, int msg_len, long msgtype);
BOOL ReceiveMsgQ(int mqId, char *msg_ptr, int *msg_len, long msgtype);
BOOL GetAttrMsgQ(int mqId, struct msgq_attr *attr);
BOOL SetAttrMsgQ(int mqId, struct msgq_attr *newattr,  struct msgq_attr *oldattr);
BOOL FlushMsgQ(int mqId);

//#ifdef __cplusplus
//}
//#endif

#endif /*__IPCMSGQ_H  End */

