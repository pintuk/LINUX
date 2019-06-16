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
	char message[1024];
	//MsgData msg;

	if (openMsgQ(&msgqId, QUEUE_NAME) == FALSE) {
		printf("ERROR : openMsgQ - Failed !\n");
		return 0;
	}
	//memset(&msg,0,sizeof(MsgData));
	memset(&message,0,sizeof(message));
	//msg.len = sizeof(MsgData);
	if (receiveMsgQ(msgqId, &message, sizeof(message), 1) == FALSE) {
		printf("ERROR : receiveMsgQ - Failed !\n");
		goto out;
	}
	//printf("Message : %s\n",msg.buffer);
	printf("Message : %s\n",message);
	//printf("Message Length : %d\n",msg.len);
	//sleep(10);

out:
	closeMsgQ(msgqId);


	return 0;
}

