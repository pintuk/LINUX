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
	char message[] = "Hello TESTQ...\0";

	QMsg msg;
	msg.mtype = 1;
	msg.len = sizeof(message);
	strncpy(msg.buffer,message,msg.len);

	if(OpenMessageQ(&QId, QUEUE_NAME) == FALSE)
	{
		fprintf(stderr,"ERROR : OpenMsgQ Failed : %s\n",strerror(errno));
		goto out;
	}
	len = sizeof(QMsg);
	if(SendMessage(QId,(char *)&msg,len,1))
	{
		fprintf(stderr,"ERROR : SendMsgQ Failed : %s\n",strerror(errno));
		goto msgqout;
	}
	sleep(60);


msgqout:
	printf("closing msgQ...\n");
	CloseMessageQ(&QId);

out:
	return 0;
}



