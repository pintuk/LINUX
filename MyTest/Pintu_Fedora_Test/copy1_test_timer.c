
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

BOOL EnMM_StartTimer_SHP(EnMM_HTimer hTimer ,enMPInt32 timeoutValue, enMPBool bOneShot );
EnMM_HTimer EnMM_CreateTimer_SHP(char* pTimerName, EnMM_TimerCbType callbackFunction, int userData);



typedef struct
{
	EnMM_TimerCbType m_ptr;
	int m_nUser;
	int m_nSig;
	unsigned int m_nTimeOut;
} timer_info;

typedef struct
{
	EnMM_HTimer hTimer;
	EnMM_TimerCbType pCbFptr;
	int	timeout;
	int	data;
	unsigned char bOneShot;	
}EnMM_TimerData_SHP;
EnMM_TimerData_SHP	*pTimerData[EnMM_TIMER_ARRAY_SIZE];
int	gLastUsedTimerIndex = -1;



void TimerFunctioncb(unsigned int userData)
{
	struct itimerspec tSpec;
	printf("Timer expired = %d\n",userData);

	if(!OneshotTimer)
	{
    tSpec.it_value.tv_sec = 10;
	tSpec.it_value.tv_nsec = 0;
	//usleep(10 * 1000);
	timer_settime(id, 0, &tSpec, NULL);
	printf("Timer restarted.....\n");
	sleep(5);
	}
}

int main()
{
	timer_info *pInfo;
	struct sigevent evp;
	struct sigaction sa;
	struct itimerspec tSpec;
    timer_t timerid;
	unsigned int userData = 30;
	unsigned int timeoutValue = 5000;
	unsigned long sec = timeoutValue / 1000;
	unsigned long msec = timeoutValue % 1000;
	int bOneShot = 1;
	
	if(SIGRTMIN + userData > SIGRTMAX)
	{
		perror("Too Many timers!!! : ");
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = (void *)TimerFunctioncb;
	sigaction(SIGRTMAX, &sa, NULL);
	evp.sigev_notify = SIGEV_SIGNAL;
	//evp.sigev_notify = SIGEV_CALLBACK;
	evp.sigev_signo   = SIGRTMIN + userData;
	//evp.sigev_value.sival_ptr = (void *)TimerFunctioncb;
	pInfo = (timer_info *)malloc(sizeof (timer_info));
	pInfo->m_ptr = TimerFunctioncb;
	pInfo->m_nUser = userData;
	pInfo->m_nTimeOut = -1;
	pInfo->m_nSig = SIGRTMIN + userData;
	//pInfo.timerName = pTimerName;
	evp.sigev_value.sival_ptr = (void *)pInfo;

    if (timer_create(CLOCK_REALTIME, &evp, &timerid) != 0) {
		perror("timer_create error:");
	}
	printf("Timer Created - Successfully.....\n");
	id = timerid;
	
	if(bOneShot)
	{
		OneshotTimer = 1;
		tSpec.it_value.tv_sec = sec;
		tSpec.it_value.tv_nsec = msec * 1000000;
		tSpec.it_interval.tv_sec = 0;
		tSpec.it_interval.tv_nsec = 0;
	}
	else
	{
		OneshotTimer = 0;
		tSpec.it_value.tv_sec = sec;
		tSpec.it_value.tv_nsec = msec * 1000000;
		tSpec.it_interval.tv_sec = tSpec.it_value.tv_sec;
		tSpec.it_interval.tv_nsec = tSpec.it_value.tv_nsec;
	}
			
	if(timer_settime(timerid, 0, &tSpec, NULL) != 0)
	{
		fprintf(stderr, "timer_settime - failed !, Error = %s\n",strerror(errno));
		if (timer_delete(timerid) != 0)
		{
			fprintf(stderr, "timer_delete - failed !, Error = %s\n",strerror(errno));
		}
	}
	printf("timer_settime - DONE - \n");
	//tSpec.it_value.tv_sec = 0;
	//tSpec.it_value.tv_nsec = 0;
	//timer_settime(timerid, 0, &tSpec, NULL);

	usleep(1 * 1000);
	
	//tSpec.it_value.tv_sec = 10;
	//tSpec.it_value.tv_nsec = 0;
	//timer_settime(timerid, 0, &tSpec, NULL);
	
	sleep(5);
	
	free(pInfo);
	pInfo = NULL;
	exit(0);
}




