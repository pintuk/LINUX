#include "ipcmsgq.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#define QUEUE_NAME	"TESTQ1"

typedef struct MsgData {
	int len;
	char buffer[128];
}MsgData;


int main()
{
	int msgqId = -1;
	char message[] = "HelloMsg";
	MsgData msg;
	int len = 0;

	if (openMsgQ(&msgqId, QUEUE_NAME) == FALSE) {
		printf("ERROR : openMsgQ - Failed !\n");
		return 0;
	}
	//strncpy(msg.buffer,message,sizeof(message));
	//len = sizeof(MsgData);
	len = sizeof(message);
	msg.len = len;
	if (sendMsgQ(msgqId, &message, len, 1) == FALSE) {
		printf("ERROR : sendMsgQ - Failed !\n");
		goto out;
	}
	printf("Message send successfully...\n");
	sleep(20);

out:
	closeMsgQ(msgqId);


	return 0;
}

