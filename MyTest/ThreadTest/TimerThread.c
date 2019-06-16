#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>
#include<sys/time.h>
#include<signal.h>


// To compile use : gcc -o ThreadPriority.out ThreadPriority.c -D_POSIX_THREAD_PRIORITY_SCHEDULING -lpthread -pthread

static int done = 0;

typedef unsigned long	UINT32;
typedef unsigned char	BOOL;

#define TRUE	1
#define FALSE	0

typedef void(*TIMER_CB_FUNC)(UINT32,BOOL);


void  TimeOutHandler(int sig, siginfo_t*  extra, void* cruft)
{
	unsigned int dwSigNo = 0;
	sigset_t sigset, oldset;

	if (extra->si_code != SI_TIMER )
	{
		fprintf(stderr,"TimeOut : Already deleted TIMER sig %d cause %d\n", sig - SIGRTMIN ,extra->si_code);
		return ;
	}
	sigfillset(&sigset);
	if (sigprocmask(SIG_BLOCK, &sigset, &oldset) < 0)
	{
		OSAL_MSG_ERROR("sigprocmask %d error ", sig);
	}

	dwSigNo = sig - SIGRTMIN;

	((TIMER_CB_FUNC)extra->_sifields._rt.si_sigval.sival_ptr)(dwSigNo, TRUE);
	return;
}

void* CreateTimer( UINT32 timeOut, TIMER_CB_FUNC fnc, int dwUser, unsigned char timertype)
{
	struct sigevent evp;
	struct itimerspec tSpec;

	if ( SIGRTMIN + dwUser > SIGRTMAX)
	{
		fprintf(stderr,"===== Too Many timers!!! ======\n");
		return 0;
	}

	timer_info *pTimer = malloc(sizeof(timer_info));

	pTimer->sig_no = SIGRTMIN + dwUser;
			
	evp.sigev_notify = SIGEV_SIGNAL;
	evp.sigev_signo   = SIGRTMIN + dwUser;

	evp.sigev_value.sival_ptr = (void *)fnc;

	// sigemptyset(&pTimer->act.sa_mask);	
	sigfillset( &pTimer->act.sa_mask);        // Block all other signal

	pTimer->act.sa_flags = SA_SIGINFO;
	pTimer->act.sa_sigaction = TimeOutHandler;
	
	if( sigaction(SIGRTMIN + dwUser , &pTimer->act , &pTimer->oldact) < 0 )
	{
		fprintf(stderr,"==== sigaction return false =====\n");
		free(pTimer);
		pTimer = NULL;
		return 0;
	}

	if( timer_create(CLOCK_REALTIME, &evp, &pTimer->timer)  != 0 )
	{
		fprintf(stderr,"timer_create return false : %s\n", strerror(errno));
		free(pTimer);
		pTimer = NULL;		
		return 0;
	}

	{
		unsigned long sec = timeOut / 1000;
		unsigned long msec = timeOut % 1000;

		tSpec.it_value.tv_sec = sec;
		tSpec.it_value.tv_nsec = msec * 1000000;

		if ( timertype & TIMER_PERIODIC )
		{
			tSpec.it_interval.tv_sec = sec;
			tSpec.it_interval.tv_nsec = msec * 1000000;
		}
		else
		{
			tSpec.it_interval.tv_sec = 0;
			tSpec.it_interval.tv_nsec = 0;
		}
	}

	if(timer_settime(pTimer->timer ,0, &tSpec,NULL) != 0)
	{
		fprintf(stderr,"timer_settime return false\n");

		if (timer_delete(pTimer->timer) == 0)
		{
			fprintf(stderr,"CreateTimer: timer_delete TIMER_T=(%#x) Failed : %s\n",pTimer->timer, strerror(errno));
		}
	}

	fprintf("platform Timer create TIMER_T=%#x Sig Num=%d TimeOut=%dms\n", pTimer->timer, dwUser, timeOut);

	pTimer->bCreated = TRUE;
	return (TIMER_T )pTimer;
}

BOOL DeleteTimer(TIMER_T TmId)
{
	timer_info *pTimer = (timer_info *)TmId;
	
	long result = -1;
	long overrun = timer_getoverrun(pTimer->timer);

	pTimer->bCreated = FALSE;
	
	if ( overrun > 0 )
	{
		fprintf(stderr,"Timer Overrun detected - TIMER_T=%#x Count=%d Error=%s\n", pTimer->timer, overrun,strerror(errno) );
		free(pTimer);
		return TRUE;		// FIXME:: I cannot calcualte this is correct way
	}

	result = timer_delete(pTimer->timer);

	if (result == 0)
	{
		fprintf(stderr,"platform Timer delete TIMER_T=%#x Overrun=%d\n", pTimer->timer, overrun);
		free(pTimer);
		return TRUE;
	}

	fprintf(stderr,"DeleteTimer: timer_delete TIMER_T=(%#x) Failed Error=%s\n", pTimer->timer, strerror(errno) );
	free(pTimer);
	return FALSE;

}


void *Thread1(void *arg)
{
	int flag = 0; int x = 0;
	int policy = 0;
	pthread_t id = pthread_self();
	struct sched_param param_in, param_out;

	/* *************** Linux Thread Policies ***************** */
	/* SCHED_OTHER = 0 , Priority = 0 , Do not use any priority numbers here. It may not schedule at all */
	/* SCHED_FIFO  = 1 , Priority Min = 1, Max = 99 , But never use ABOVE(90) , System may hang. This is used for Real-time scheduling with avg priority */
	/* SCHED_RR    = 2 , Priority Min = 1, Max = 99, Do not use priority > 90, System may hang . Let it as LOW for Normal task */
	/* ******************************************************* */

	/* USE This To Set the Thread Policy After Creating the Thread */
	//param_in.sched_priority = 50;
	//pthread_setschedparam(id, SCHED_FIFO, &param_in);

	done++;
	printf("Thread1 - Created !!!\n");
	pthread_getschedparam(id, &policy, &param_out);
	printf("Thread Priority Set to : %d, POLICY = %d\n",(int)param_out.sched_priority,policy);
	while(flag==0)
	{
		sleep(2);
		//Function1(1);
		printf("Thread doing some Task.....\n");
		x++;
		if(x>=20) break;
	}
	printf("Thread1 - Ended !!!\n");

	pthread_exit(0);
	return NULL;
}

void CreateThread1(pthread_t *th1)
{
	//pthread_t th1;
	pthread_attr_t sched_attr;
	struct sched_param param;
	int priority = 50;

	param.sched_priority = priority;
	pthread_attr_init(&sched_attr);
	pthread_attr_setinheritsched(&sched_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&sched_attr, SCHED_FIFO);
	pthread_attr_setschedparam(&sched_attr, &param );
	/* Set the thread policy before creating the thread */
	/* OR Set the policy after creating the thread and inside the thread */
	pthread_create(th1, &sched_attr, Thread1, NULL);

	/* DONT USE THE BELOW SETTING OUTSIDE THE THREAD . THIS WILL HAVE NO EFFECT in the Beginning. Its gets effected once thread started doing the operation */
	//param.sched_priority = priority;
	//pthread_setschedparam(*th1, SCHED_FIFO, &param );

	while(done < 1)
	{
		printf("Waiting.....\n");
	}
	printf("====== thread1 Ready =====\n");

}

int main()
{
	pthread_t th1;
	struct sched_param param;
	int priority = 0; long int nsec = 0; int sec = 0;
	struct timespec tp;

	printf("main : Inside Main -\n");
	CreateThread1(&th1);

	priority = sched_get_priority_max(SCHED_FIFO);
	param.sched_priority = priority;
	sched_rr_get_interval(0,&tp);
	sec = (int)tp.tv_sec;
	nsec = (long int)tp.tv_nsec;

	printf("max priority = %d\n",priority);
	printf("Interval : %d (secs) : %ld (nsecs) \n",sec,nsec);

	pthread_join(th1,NULL);	

	printf("=========== ALL is Well ===============\n");
}




