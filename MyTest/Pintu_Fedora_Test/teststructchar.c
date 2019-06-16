#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct
{
	int x;
	int evId;
}MSGQ_T;

typedef struct
{
	int sessionID;
	char *msg;
}s_TaskMsg;


int msgreceive(unsigned char *msg_ptr)
{
	char Message[50] = {0};
	char msgd[50] = {0};
	int id = 0;
	int i = 0;

	if(msg_ptr == NULL)
	{
		printf("msg_ptr is NULL...\n");
		return 0;
	}

	for(i=0; i<sizeof(s_TaskMsg); i++)
	{
		printf("%d\n",msg_ptr[i]);
	}

	sprintf(Message, "%s",msg_ptr);
	Message[sizeof(s_TaskMsg) + 1] = '\0';

	sscanf(Message,"%4s",&msgd);
	printf("session ID - %d\n",atoi(msgd));
	printf("MSG PTR - %s\n",Message);
}


main()
{
	s_TaskMsg mmsg = {0};
	char MsgData[] = "EnMMMsg\0";

	mmsg.sessionID = 1;
	mmsg.msg = MsgData;

	msgreceive((unsigned char *)&mmsg);
	//sprintf(MsgData,"%s",(char*)&mmsg);
	//printf("MsgData - %s\n",MsgData);
}


