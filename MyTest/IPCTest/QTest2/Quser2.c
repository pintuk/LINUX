#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>


#include<sys/ioctl.h>

#include "IPCMsgQ.h"


#define QUEUE_NAME	"TESTQ"

#if 0
typedef struct QMsg {
        long mtype;
	int len;
        char buffer[255];
}QMsg;
#endif

int main()
{
	int err = -1;
	int len = 0;
	int QId = -1;
	//char message[1024];
	QMsg msg;

	if(OpenMsgQ(&QId, QUEUE_NAME) == FALSE)
	{
		fprintf(stderr,"ERROR : OpenMsgQ Failed : %s\n",strerror(errno));
		goto out;
	}
	len = sizeof(QMsg);
	if(ReceiveMsgQ(QId,(char *)&msg,&len,1))
	{
		fprintf(stderr,"ERROR : ReceiveMsgQ Failed : %s\n",strerror(errno));
		goto msgqout;
	}
	printf("Message : %s\n",msg.buffer);
	sleep(10);


msgqout:
	printf("closing msgQ...\n");
	CloseMsgQ(&QId);

out:
	return 0;
}



