#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "IPCMsgQ.h"
#include "VTTask.h"


#define VTAPP_PATH_UI_PROCESS   "./vtui.out"
#define VTMAIN_TASK_NAME	"VTMainTask"


static pthread_t vtmaintaskId;
static int vtmain_task_done = 0;
static volatile BOOL task_terminate = FALSE;

int vtmain_launch_ui(char* argv[])
{
	pid_t pid = -1;

	pid = fork();
	
	switch (pid) 
	{
		case -1:
			return -1;
		break;
		case 0:
			fprintf(stderr,"[vtmain1] - Child Process(%s) - Created Successfully !!!\n",argv[0]);
			execvp(argv[0], argv);
		default:
			fprintf(stderr,"vtmain_launch_ui - , pid = %d\n",(int)pid);
		break;
	}

	return (int)pid;
}


void ProcessTask(int type)
{
	VTMainMsg Msg = {0,};
	static int i = 0;
	int ret = 0;

	memset(&Msg,0,sizeof(VTMainMsg));
	switch(type)
	{
		case VTAPP_NOTI_STR:
			i++;
			Msg.stype = VTMAIN_NOTI_INCOMING;
			Msg.type = type;
			sprintf(Msg.message,"FROM_VT_MAIN_TASK-%d",i);
			Msg.msgLen = sizeof(Msg);
			ret = SendMessage(VTMainQ, (char *)&Msg, sizeof(Msg), 0);
			if(ret == FALSE)
			{
				fprintf(stderr,"ERROR : SendMessage(VTAPP_NOTI_INCOMING) - Failed !\n");
				return;
			}
		break;
		case VTAPP_NOTI_EXIT:
			Msg.stype = VTMAIN_NOTI_END;
			Msg.type = type;
			sprintf(Msg.message,"FROM_VT_MAIN_END_TASK");
			Msg.msgLen = sizeof(Msg);
			ret = SendMessage(VTMainQ, (char *)&Msg, sizeof(Msg), 0);
			if(ret == FALSE)
			{
				fprintf(stderr,"ERROR : SendMessage(VTAPP_NOTI_END) - Failed !\n");
				return;
			}
		break;
		default:
		break;
	}
	
}

void *vt_main_task(void *arg)
{
	VTMainMsg Msg = {0,};
	int msgLen = 0;

	vtmain_task_done = 1;
	memset(&Msg, 0, sizeof(VTMainMsg));

	//printf("Entry ---> Inside vt_main_task\n");
	while(task_terminate == FALSE)
	{
		memset(&Msg,0,sizeof(VTMainMsg));
		msgLen = sizeof(Msg);
		if(ReceiveMessage(VTUIQ, (char*)&Msg, &msgLen, NULL) == FALSE)
		{
			fprintf(stderr,"ERROR : vt_main_task : Failed to Receive Message\n");
			continue;
		}
		switch(Msg.stype)
		{
			case VTMAIN_NOTI_OUTGOING:
				Msg.type = VTAPP_NOTI_STR;
				ProcessTask(Msg.type);
				sleep(1);	
			break;
			case VTUI_NOTI_INCOMING:
				printf("==============================================\n");
				fprintf(stderr,"Message From UI : %s\n",Msg.message);
				fprintf(stderr,"Message Type    : %d\n",Msg.type);
				printf("==============================================\n");
				printf("\n");
				memset(&Msg,0,sizeof(VTMainMsg));
				sleep(1);
			break;
			case VTUI_NOTI_END:
				fprintf(stderr,"Message From UI : %s\n",Msg.message);
				task_terminate = TRUE;
			break;
			default:
				memset(&Msg,0,sizeof(VTMainMsg));
				//fprintf(stderr,"Default Message From UI - type = %d\n",Msg.stype);
			break;
		}
	}
	FlushMessage(VTMainQ);
	CloseMessageQ(VTMainQ);
	FlushMessage(VTUIQ);
	CloseMessageQ(VTUIQ);
	sleep(2);
	ExitTask(vtmaintaskId,VTMAIN_TASK_NAME);

	return NULL;
}


int main(int argc, char *argv[])
{
	char *argv_ui[7] = {0,};
	int pid = -1;
	void *arg = NULL;
	struct msgq_attr attr = {0,};
	VTMainMsg Msg = {0,};
	int choice = 0;

	attr.msgq_flags = MQ_O_WRONLY;
	attr.msgq_maxmsg = VT_APP_MAX_MESSAGE;
	attr.msgq_msgsize = sizeof(VTMainMsg);

	VTMainQ = OpenMessageQ(VT_MAIN_QUEUE_NAME,&attr);
	if(msgq_isValid(VTMainQ)==FALSE)
	{
		fprintf(stderr,"ERROR: OpenMessageQ - VTMainQ is Not Valid !!!\n");
		return -1;
	}
	VTUIQ = OpenMessageQ(VT_UI_QUEUE_NAME,&attr);
	if(msgq_isValid(VTUIQ)==FALSE)
	{
		fprintf(stderr,"ERROR: OpenMessageQ - VTUIQ is Not Valid !!!\n");
		return -1;
	}

	CreateTask(&vtmaintaskId, VTMAIN_TASK_NAME, &vt_main_task, arg);
	while(vtmain_task_done != 1)
	{
		fprintf(stderr,"--- Waiting For Task(%s) --- \n",VTMAIN_TASK_NAME);
		sleep(1);
	}

	argv_ui[0] = VTAPP_PATH_UI_PROCESS;
	argv_ui[1] = "MO";
	argv_ui[2] = "000000"; // number
	argv_ui[3] = "-1"; // contact ID
	argv_ui[4] = "-1"; // contact storage type

	pid = (int)vtmain_launch_ui(argv_ui);

	printf("\n ==========   ALL  TASK  CREATED   ===========\n\n");

	choice = 1;

	while(choice != 0)
	{
	printf("************  MENU   *************\n");
	printf("1. Send Message To UI.  \n");
	printf("2. EXIT UI.             \n");
	printf("**********************************\n");
	printf("Enter the choice : \n");
	//choice = getchar();
	scanf("%d",&choice);
	printf("\n");
	switch(choice)
	{
		case 1:
		{
			memset(&Msg, 0, sizeof(Msg));
			//Msg.stype = VTMAIN_NOTI_OUTGOING;
			Msg.type = VTAPP_NOTI_STR;
			//sprintf(Msg.message,"VTMAIN_MSG-%d",i);
			ProcessTask(Msg.type);
		}
		break;
		case 2:
			memset(&Msg, 0, sizeof(Msg));
                        Msg.type = VTAPP_NOTI_EXIT;
                        ProcessTask(Msg.type);
			choice = 0;
		break;
		default:
			printf("Default Choice = %d\n",choice);
		break;
	}
	}

	printf("========= Waiting For VTMAIN Task To End =========\n");

	WaitForTaskExit(vtmaintaskId);
	vtmaintaskId = -1;

	printf("##########  vtmain process - Terminated  #########\n");

	return 0;
}


