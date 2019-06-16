#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>


#include<sys/ioctl.h>

#include "IPCMsgQ.h"


#define QUEUE_NAME	"TESTQ1"

/*
typedef struct QMsg {
	long mtype;
	int len;
	char buffer[255];
}QMsg;
*/

int main()
{
	int err = -1;
	int len = 0;
	int QId = -1;
	char message[] = "HelloTESTQ1";
	QMsg msg;

	msg.mtype = 1;
	//msg.type = 1;
	len = sizeof(message);
	//strncpy(msg.buffer,message,len);
	printf("Buffer : %s , len = %d\n",message,len);

	//remove("/tmp/TESTQ");

	if(OpenMsgQ(&QId, QUEUE_NAME) == FALSE)
	{
		fprintf(stderr,"ERROR : OpenMsgQ Failed : %s\n",strerror(errno));
		goto out;
	}
	//len = sizeof(QMsg);
	if(SendMsgQ(QId,(char *)message,len,1))
	{
		fprintf(stderr,"ERROR : SendMsgQ Failed : %s\n",strerror(errno));
		goto msgqout;
	}
	sleep(60);


msgqout:
	printf("closing msgQ...\n");
	CloseMsgQ(&QId);

out:
	return 0;
}



