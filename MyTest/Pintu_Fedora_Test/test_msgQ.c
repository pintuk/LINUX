
// Message Queues --- Example

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>

const key_t MSGKEY = 1234;
const int PERMS = 0666;

struct my_msg
{
	long msgtype;
	unsigned char data[20];
}Msg;


unsigned int msgPriority = 1;
int flag = 0;

main()
{
	struct my_msg msg = {0};
	struct msqid_ds msgattr = {0};
	int msgid=0;
	int choice = 1;
	char ch='y';
	int i = 0; int j = 0;

	msgid=msgget(MSGKEY,PERMS | IPC_CREAT);
	if(msgid<0)
	{
		perror("Cannot Create Message Queue...\n");
		exit(1);
	}
	msgattr.msg_qbytes = 65536;
	msgctl(msgid, IPC_SET, &msgattr);
	msgrcv(msgid,&msg,65536,(long)0, IPC_NOWAIT | MSG_NOERROR);
	j=1;
	for(i=0; i<900; i++)	
	{
		memset(msg.data, 0, sizeof(msg.data));
		//if(i > 6) j = 2;
		sprintf(msg.data,"%u",(50 + i));
		msg.msgtype=(long int)j;
		if(msgsnd(msgid,&msg,sizeof(Msg)-sizeof(long),0)<0)
		{
			perror("Cannot Send...\n");
		}
		printf("msg send.....\n");
	}
	msgctl(msgid, IPC_STAT, &msgattr);
	printf("------------------------------------\n");
	printf("msgattr - msg_qbytes = %d\n",msgattr.msg_qbytes);
	printf("------------------------------------\n");
	j=i;
	i=1;
	while(1)
	{
		//prio = 1;
		//memset(msg.data, 0, sizeof(Msg));
		if(msgrcv(msgid,&msg,sizeof(Msg)-sizeof(long),(long)0,IPC_NOWAIT)<0)
		{
			perror("Cannot Receive...\n");
			break;
		}
		printf("COUNT : %d\n",i++);
		printf("Message Received : %s\n",msg.data);
		printf("Priority : %d\n",msg.msgtype);
		if(i > j) break;
	}
	printf("msgattr - msg_qbytes = %d\n",msgattr.msg_qbytes);
	msgctl(msgid,IPC_RMID,0);
	exit(0);
}


