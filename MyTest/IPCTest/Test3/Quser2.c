#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>


#include<sys/ioctl.h>

#include "IPCMsgQ.h"


#define QUEUE_NAME	"TESTQ"

typedef struct QMsg {
        long mtype;
	int len;
        char buffer[255];
}QMsg;


int main()
{
	int err = -1;
	int len = 0;
	int QId = -1;
	//char message[1024];
	QMsg msg;

	if(OpenMessageQ(&QId, QUEUE_NAME) == FALSE)
	{
		fprintf(stderr,"ERROR : OpenMsgQ Failed : %s\n",strerror(errno));
		goto out;
	}
	len = sizeof(QMsg);
	if(ReceiveMessage(QId,(char *)&msg,len,1))
	{
		fprintf(stderr,"ERROR : ReceiveMsgQ Failed : %s\n",strerror(errno));
		goto msgqout;
	}
	printf("Message : %s\n",msg.buffer);
	sleep(10);


msgqout:
	printf("closing msgQ...\n");
	CloseMessageQ(&QId);

out:
	return 0;
}



