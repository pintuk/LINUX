#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "IPCMsgQ.h"
#include "VTTask.h"

#define VTUI_TASK_NAME	"VTUITASK"

static pthread_t vtuitaskId;
static int vtui_task_done = 0;
static volatile BOOL task_terminate = FALSE;

int choice = 0;

void ProcessTask(int type)
{
	VTMainMsg Msg = {0,};
	static int i = 0;
	int ret = 0;

	switch(type)
	{
		case VTAPP_NOTI_STR:
			i++;
			memset(&Msg,0,sizeof(VTMainMsg));
			Msg.stype = VTUI_NOTI_INCOMING;
			Msg.type = type;
			sprintf(Msg.message,"FROM_VT_UI_TASK-%d",i);
			Msg.msgLen = sizeof(Msg);
			ret = SendMessage(VTUIQ, (char *)&Msg, sizeof(Msg), 0);
			if(ret == FALSE)
			{
				fprintf(stderr,"ERROR : [VT_UI] SendMessage(VTAPP_NOTI_INCOMING) - Failed !\n");
				return;
			}
		break;
		case VTAPP_NOTI_EXIT:
			printf("[VTUI] - ProcessTask - VTAPP_NOTI_EXIT\n");
			task_terminate = 1;
		break;

		default:
		break;
	}
	
}

void *vt_ui_task(void *arg)
{
	VTMainMsg Msg = {0,};
	int msgLen = 0;

	vtui_task_done = 1;
	memset(&Msg, 0, sizeof(VTMainMsg));

	while(task_terminate == FALSE)
	{
		memset(&Msg, 0, sizeof(VTMainMsg));
		msgLen = sizeof(Msg);
		if(msgq_isValid(VTMainQ)==FALSE)
        	{
                	fprintf(stderr,"ERROR: OpenMessageQ - VTMainQ is Not Valid !!!\n");
			task_terminate = 1;
                	return NULL;
        	}
		if(ReceiveMessage(VTMainQ, (char*)&Msg, &msgLen, NULL) == FALSE)
		{
			fprintf(stderr,"ERROR : vt_ui_task : Failed to Receive Message\n");
			continue;
		}
		switch(Msg.stype)
		{
			case VTUI_NOTI_OUTGOING:
				ProcessTask(Msg.type);
				sleep(1);	
			break;
			case VTMAIN_NOTI_INCOMING:
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
				fprintf(stderr,"Message From VTMAIN : %s\n",Msg.message);
				fprintf(stderr,"Message Type        : %d\n",Msg.type);
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
				sleep(1);
			break;
			case VTMAIN_NOTI_END:
				fprintf(stderr,"Message From VTMAIN : %s\n",Msg.message);
				Msg.type = VTAPP_NOTI_EXIT;
				ProcessTask(Msg.type);
				//task_terminate = TRUE;
			break;
			default:
				memset(&Msg, 0, sizeof(VTMainMsg));
				//fprintf(stderr,"Default Message From VTMAIN , type = %d\n",Msg.stype);
			break;
		}
	}
	printf("--------- Ending - vt_ui_task -----------\n");
	//FlushMessage(VTMainQ);
	//CloseMessageQ(VTMainQ);
	//FlushMessage(VTUIQ);
	//CloseMessageQ(VTUIQ);
	//choice = 2;
	ExitTask(vtuitaskId,VTUI_TASK_NAME);

	return NULL;
}


int main(int argc, char *argv[])
{
	struct msgq_attr attr = {0,};
	int ret = 0;
	VTMainMsg Msg = {0,};
	void *arg = NULL;

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

	ret = CreateTask(&vtuitaskId, VTUI_TASK_NAME, vt_ui_task, arg);
	if(ret == FALSE)
	{
		fprintf(stderr,"ERROR : CreateTask Failed !!!\n");
		return -1;
	}
	while(vtui_task_done != 1)
	{
		fprintf(stderr,"--- Waiting For Task(%s) --- \n",VTUI_TASK_NAME);
		sleep(1);
	}

	choice = 1;

#if 0
        while(choice != 0)
        {
        printf("************  VTUI MENU   *************\n");
        printf("1. Send Message To UI.  \n");
        printf("2. EXIT UI.             \n");
        printf("***************************************\n");
        printf("Enter the choice : ");
        choice = getchar();
        scanf("%d",&choice);
        switch(choice)
        {
                case 1:
                        memset(&Msg, 0, sizeof(Msg));
                        Msg.type = VTAPP_NOTI_STR;
                        ProcessTask(Msg.type);
			sleep(1);
                break;
                case 2:
                        memset(&Msg, 0, sizeof(Msg));
                        Msg.type = VTAPP_NOTI_EXIT;
                        ProcessTask(Msg.type);
			sleep(1);
                        choice = 0;
                break;
                default:
                        printf("Default Choice = %d\n",choice);
                break;
        }
        }
#endif

	printf("------ Waiting for UI Task To End ------\n");

	WaitForTaskExit(vtuitaskId);

	Msg.stype = VTUI_NOTI_END;
	Msg.type = VTAPP_NOTI_EXIT;
	sprintf(Msg.message,"VT_UI_EXIT");
	Msg.msgLen = sizeof(Msg);
	ret = SendMessage(VTUIQ, (char *)&Msg, sizeof(Msg), 0);
	if(ret == FALSE)
	{
		fprintf(stderr,"ERROR : [VT_UI] SendMessage(VTUI_NOTI_END) - Failed !\n");
		
	}

	printf("##########  vtui process - Terminated  #########\n");

	return 0;
}


