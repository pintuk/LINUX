
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include<errno.h>
#include<unistd.h>

#define EnMM_TIMER_ARRAY_SIZE 64
#define TRUE 1
#define FALSE 0

typedef void (*fpEnMM_TimerCbFPtr)(unsigned int userData);
typedef fpEnMM_TimerCbFPtr EnMM_TimerCbType;
typedef int EnMM_HTimer;
typedef int BOOL;

BOOL EnMM_StartTimer_LNX(EnMM_HTimer hTimer, int timeoutValue, BOOL bOneShot );
EnMM_HTimer EnMM_CreateTimer_LNX(char* pTimerName, EnMM_TimerCbType callbackFunction, int userData);
BOOL  EnMM_GetTimer_LNX(EnMM_HTimer hTimer, int* pTimerArrayIndex );

/*
typedef struct
{
	EnMM_TimerCbType m_ptr;
	int m_nUser;
	int m_nSig;
	unsigned int m_nTimeOut;
} timer_info;
*/

typedef struct
{
	EnMM_HTimer hTimer;
	EnMM_TimerCbType pCbFptr;
	int	timeout;
	int	data;
	unsigned char bOneShot;	
}EnMM_TimerData_T;
EnMM_TimerData_T	*pTimerData[EnMM_TIMER_ARRAY_SIZE];
int	gLastUsedTimerIndex = -1;


void MyTimerCallBack(int param)
{
	printf("param = %d\n",param);
}


void TimerFunctioncb(int sig, siginfo_t*  extra, void* cruft)
{
	//struct itimerspec tSpec;
	int timerArrayIndex = -1;
	BOOL enMM_RetVal = 1;
	unsigned int dwSigNo = 0;
	EnMM_TimerData_T* pLocalTimerData = NULL;
	EnMM_HTimer hTimer = -1;
	
	if (extra->si_code != SI_TIMER )
	{
		printf("Timer expired = %d\n",sig);
		return;
	}
	dwSigNo = sig - SIGRTMIN;
	
	pLocalTimerData = extra->_sifields._rt.si_sigval.sival_ptr;
	hTimer = pLocalTimerData->hTimer;
	printf("pLocalTimerData->hTimer = %d\n",hTimer);
	
	enMM_RetVal = EnMM_GetTimer_LNX(hTimer, &timerArrayIndex);

	if(1 == enMM_RetVal)
	{
		if((pTimerData[timerArrayIndex]) && (pTimerData[timerArrayIndex]->pCbFptr))
		{
			printf("calling.......pCbFptr(sig)\n");
			pTimerData[timerArrayIndex]->pCbFptr(sig);
			fprintf(stderr, "EnMM_TimedCb_LNX: TimedCb for HTimer(%d), TimerIndex(%d)...\n",hTimer,timerArrayIndex);
		}

		if((pTimerData[timerArrayIndex]) && (!pTimerData[timerArrayIndex]->bOneShot))
		{
			printf("Time Out Value - %d\n",pTimerData[timerArrayIndex]->timeout);
			printf("EnMM_StartTimer_LNX - bOneShot = FALSE\n");
			//EnMM_StartTimer_LNX(hTimer, pTimerData[timerArrayIndex]->timeout, FALSE);
		}	
	}

}

BOOL  EnMM_GetTimer_LNX(EnMM_HTimer hTimer, int* pTimerArrayIndex )
{
	BOOL bIndexFound = FALSE;

	printf("EnMM_GetTimer_LNX.....hTimer = %d\n",hTimer);
	printf("pTimerArrayIndex = %d\n",*pTimerArrayIndex);
	if(pTimerArrayIndex)
	{
		int arrayIndex = 0;

		for(arrayIndex = 0 ; arrayIndex < EnMM_TIMER_ARRAY_SIZE; arrayIndex++)
		{
			if(pTimerData[arrayIndex] != NULL)
			{
				if(pTimerData[arrayIndex]->hTimer == hTimer)
				{
					*pTimerArrayIndex = arrayIndex;
					bIndexFound = TRUE;
					printf("FOUND - pTimerArrayIndex = %d\n",*pTimerArrayIndex);
					break;
				}
			}
		}
	}
	return (bIndexFound) ? 1 : 0;

}

BOOL EnMM_StartTimer_LNX(EnMM_HTimer hTimer, int timeoutValue, BOOL bOneShot )
{
	struct itimerspec tSpec;
	//unsigned int timeoutValue = 5000;
	unsigned long sec = timeoutValue / 1000;
	unsigned long msec = timeoutValue % 1000;
	int timerArrayIndex = -1;

	printf("---------------------------------------------------------\n");
	printf("EnMM_StartTimer_LNX......, id(%d)\n",hTimer);
	if(EnMM_GetTimer_LNX(hTimer, &timerArrayIndex) == TRUE)
	{
		printf("EnMM_StartTimer_LNX -> EnMM_GetTimer_LNX - TRUE\n");
		pTimerData[timerArrayIndex]->timeout = timeoutValue;
		pTimerData[timerArrayIndex]->bOneShot = bOneShot;

		if(bOneShot == TRUE)
		{
			printf("ONE SHOT .......\n");
			tSpec.it_value.tv_sec = sec;
			tSpec.it_value.tv_nsec = msec * 1000000;
			tSpec.it_interval.tv_sec = 0;//tSpec.it_value.tv_sec;
			tSpec.it_interval.tv_nsec = 0; //tSpec.it_value.tv_nsec;
		}
		else
		{
			printf("MULTI SHOT.....\n");
			tSpec.it_value.tv_sec = sec;
			tSpec.it_value.tv_nsec = msec * 1000000;
			tSpec.it_interval.tv_sec = tSpec.it_value.tv_sec;
			tSpec.it_interval.tv_nsec = tSpec.it_value.tv_nsec;
		}
		if(timer_settime((timer_t)hTimer, 0, &tSpec, NULL) != 0)
		{
			fprintf(stderr, "timer_settime - failed !, Error = %s\n",strerror(errno));
			if (timer_delete((timer_t)hTimer) != 0)
			{
				fprintf(stderr, "timer_delete - failed !, Error = %s\n",strerror(errno));
			}
		}
		printf("timer_settime - DONE - \n");
		printf("---------------------------------------------------------\n");
		return TRUE;		
	}
	return FALSE;
}

int main()
{
	//timer_info *pInfo;
	EnMM_HTimer hTimer = -1;
	struct sigevent evp;
	struct sigaction sa;
	struct itimerspec tSpec;
    timer_t timerid;
	unsigned int userData = 30;
	unsigned int timeoutValue = 3000;
	int bOneShot = 0;
	int newTimerIndex = gLastUsedTimerIndex + 1;
	EnMM_TimerData_T* pLocalTimerData = NULL;
	int i = 0;
	
	if(SIGRTMIN + userData > SIGRTMAX)
	{
		perror("Too Many timers!!! : ");
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = (void *)TimerFunctioncb;
	sigaction(SIGRTMAX, &sa, NULL);
	evp.sigev_notify = SIGEV_SIGNAL;
	evp.sigev_signo   = SIGRTMIN + userData;
	//evp.sigev_value.sival_ptr = (void *)TimerFunctioncb;
	//pInfo = (timer_info *)malloc(sizeof (timer_info));
	pLocalTimerData = (EnMM_TimerData_T*)malloc(sizeof(EnMM_TimerData_T));
	//pInfo->m_ptr = TimerFunctioncb;
	//pInfo->m_nUser = userData;
	//pInfo->m_nTimeOut = -1;
	//pInfo->m_nSig = SIGRTMIN + userData;
	//pInfo.timerName = pTimerName;

	if(gLastUsedTimerIndex == (EnMM_TIMER_ARRAY_SIZE-1))
	{
		gLastUsedTimerIndex = -1;
	}

	evp.sigev_value.sival_ptr = (void *)pLocalTimerData;

    if (timer_create(CLOCK_REALTIME, &evp, &timerid) != 0) {
		perror("timer_create error:");
	}
	printf("Timer Created - Successfully.....\n");
	hTimer = (EnMM_HTimer)timerid;

	pLocalTimerData->hTimer = hTimer;
	pLocalTimerData->timeout = -1;
	pLocalTimerData->pCbFptr = (void *)MyTimerCallBack;
	pLocalTimerData->data = userData;

	pTimerData[newTimerIndex] = pLocalTimerData;
	gLastUsedTimerIndex++;

	printf("Timer Started - FIRST TIME ##################################\n");
	EnMM_StartTimer_LNX(hTimer, timeoutValue, bOneShot);
	printf("Timer FINISHED - FIRST TIME ##################################\n");
	
	for(i=0; i<10; i++)
	{
		sleep(1);
	}
	
	timer_delete((timer_t)hTimer);
	printf("Timer....Deleted!!!!\n");
	
	free(pLocalTimerData);
	pLocalTimerData = NULL;
	exit(0);
}




