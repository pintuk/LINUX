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


int VTMainQ = -1;

int choice = 0;



void PostMessageToMainTask(VTAppMsg *Msg)
{
        int ret = 0;

        ret = SendMessage(VTMainQ, (char *)Msg, sizeof(VTAppMsg), VTUI_MSG_TYPE_ID);
        if(ret == FALSE)
        {
                fprintf(stderr,"ERROR : PostMessageToMainTask : SendMessage - Failed !\n");
                return;
        }
}


void *VT_UI_Task(void *arg)
{
	VTAppMsg Msg = {0,};
	int msgLen = 0;

	vtui_task_done = 1;
	memset(&Msg, 0, sizeof(Msg));

	while(task_terminate == FALSE)
	{
		memset(&Msg, 0, sizeof(Msg));
		msgLen = sizeof(Msg);
		if(msgq_isValid(&VTMainQ)==FALSE)
        	{
                	fprintf(stderr,"ERROR: OpenMessageQ - VTMainQ is Not Valid !!!\n");
			task_terminate = 1;
                	return NULL;
        	}
		if(ReceiveMessage(VTMainQ, (char*)&Msg, &msgLen, VTMAIN_MSG_TYPE_ID) == FALSE)
		{
			fprintf(stderr,"ERROR : vt_ui_task : Failed to Receive Message\n");
			continue;
		}
		switch(Msg.stype)
		{
			case VTUI_NOTI_OUTGOING:
			{
				static int i = 0;
				Msg.stype = VTUI_NOTI_INCOMING;
				Msg.type = VTAPP_NOTI_STR;
				i++;
				sprintf(Msg.message,"FROM_VT_UI_TASK-%d",i);
                        	Msg.msgLen = sizeof(Msg);
				PostMessageToMainTask(&Msg);
				sleep(1);
			}
			break;
			case VTMAIN_NOTI_INCOMING:
				printf("\n");
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
				fprintf(stderr,"Message From VTMAIN : %s\n",Msg.message);
				fprintf(stderr,"Message Type        : %d\n",Msg.type);
				printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
				sleep(1);
			break;
			case VTMAIN_NOTI_END:
				fprintf(stderr,"Message From VTMAIN : %s\n",Msg.message);
				
				task_terminate = TRUE;
			break;
			default:
				//fprintf(stderr,"Default Message From VTMAIN , type = %d\n",Msg.stype);
			break;
		}
	}
	printf("--------- Ending - vt_ui_task -----------\n");
	ExitTask(vtuitaskId);

	return NULL;
}


int main(int argc, char *argv[])
{
	int ret = 0;
	VTAppMsg Msg = {0,};
	void *arg = NULL;

	if(OpenMessageQ(&VTMainQ, VT_MAIN_QUEUE_NAME) == FALSE)
	{
		fprintf(stderr,"ERROR : OpenMessageQ(%s) : Failed !!!\n",VT_MAIN_QUEUE_NAME);
		return -1;
	}
        if(msgq_isValid(&VTMainQ)==FALSE)
        {
                fprintf(stderr,"ERROR: OpenMessageQ - VTMainQ is Not Valid !!!\n");
                return -1;
        }
	printf(" [VT_UI] - Queue Id = %d\n",VTMainQ);

	ret = CreateTask(&vtuitaskId, VTUI_TASK_NAME, VT_UI_Task, arg);
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


	printf("------ UI Task Waiting ------\n");

	WaitForTaskExit(vtuitaskId);

	Msg.stype = VTUI_NOTI_END;
	Msg.type = VTAPP_NOTI_EXIT;
	sprintf(Msg.message,"VT_UI_EXIT");
	Msg.msgLen = sizeof(Msg);
	PostMessageToMainTask(&Msg);

	printf("##########  vtui process - Terminated  #########\n");

	return 0;
}


