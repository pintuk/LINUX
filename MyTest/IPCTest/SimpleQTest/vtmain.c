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


int VTMainQ = -1;


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

void PostMessageToUITask(VTAppMsg *Msg)
{
	int ret = 0;

	ret = SendMessage(VTMainQ, (char *)Msg, sizeof(VTAppMsg), VTMAIN_MSG_TYPE_ID);
	if(ret == FALSE)
	{
		fprintf(stderr,"ERROR : PostMessageToUITask : SendMessage - Failed !\n");
		return;
	}
}


void *VT_Main_Task(void *arg)
{
	VTAppMsg Msg = {0,};
	int msgLen = 0;

	vtmain_task_done = 1;
	memset(&Msg, 0, sizeof(VTAppMsg));

	while(task_terminate == FALSE)
	{
		memset(&Msg,0,sizeof(VTAppMsg));
		msgLen = sizeof(Msg);
		if(ReceiveMessage(VTMainQ, (char*)&Msg, &msgLen, VTUI_MSG_TYPE_ID) == FALSE)
		{
			fprintf(stderr,"ERROR : vt_main_task : Failed to Receive Message\n");
			continue;
		}
		switch(Msg.stype)
		{
			case VTUI_NOTI_INCOMING:
				printf("==============================================\n");
				fprintf(stderr,"Message From UI : %s\n",Msg.message);
				fprintf(stderr,"Message Type    : %d\n",Msg.type);
				printf("==============================================\n");
				printf("\n");
				memset(&Msg,0,sizeof(Msg));
				sleep(1);
			break;
			case VTUI_NOTI_END:
				fprintf(stderr,"Message From UI : %s\n",Msg.message);
				task_terminate = TRUE;
			break;
			default:
				//fprintf(stderr,"Default Message From UI - type = %d\n",Msg.stype);
			break;
		}
	}
	FlushMessage(VTMainQ);
	CloseMessageQ(&VTMainQ);
	sleep(2);
	ExitTask(vtmaintaskId);

	return NULL;
}


int main(int argc, char *argv[])
{
	char *argv_ui[7] = {0,};
	int pid = -1;
	void *arg = NULL;
	VTAppMsg Msg = {0,};
	int choice = 0;

	VTMainQ = -1;

	if(OpenMessageQ(&VTMainQ, VT_MAIN_QUEUE_NAME) == FALSE)
	{
		fprintf(stderr,"ERROR : OpenMessageQ Failed !!!\n");
		return -1;
	}
	if(msgq_isValid(&VTMainQ)==FALSE)
	{
		fprintf(stderr,"ERROR: OpenMessageQ - VTMainQ is Not Valid !!!\n");
		return -1;
	}
	printf(" [VTMAIN] - QUEUE Id = %d\n",VTMainQ);
	CreateTask(&vtmaintaskId, VTMAIN_TASK_NAME, VT_Main_Task, arg);
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
	printf("2. Receive Msg From UI. \n");
	printf("3. EXIT UI.             \n");
	printf("**********************************\n");
	printf("Enter the choice : \n");
	//choice = getchar();
	scanf("%d",&choice);
	printf("\n");
	switch(choice)
	{
		case 1:
		{
			static int i = 0;
			memset(&Msg, 0, sizeof(Msg));
			i++;
                        Msg.stype = VTMAIN_NOTI_INCOMING;
                        Msg.type = VTAPP_NOTI_STR;
                        sprintf(Msg.message,"FROM_VT_MAIN_TASK-%d",i);
                        Msg.msgLen = sizeof(Msg);
                        PostMessageToUITask(&Msg);
		}
		break;
		case 2:
			memset(&Msg, 0, sizeof(Msg));
                        Msg.stype = VTUI_NOTI_OUTGOING;
                        Msg.type = VTAPP_NOTI_STR;
                        sprintf(Msg.message,"VTMAIN-INCOMING");
                        Msg.msgLen = sizeof(Msg);
                        PostMessageToUITask(&Msg);
		break;
		case 3:
			memset(&Msg, 0, sizeof(Msg));
			Msg.stype = VTMAIN_NOTI_END;
                        Msg.type = VTAPP_NOTI_EXIT;
                        sprintf(Msg.message,"FROM_VT_MAIN_END_TASK");
                        Msg.msgLen = sizeof(Msg);
                        PostMessageToUITask(&Msg);
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

	VTMainQ = -1;

	return 0;
}


