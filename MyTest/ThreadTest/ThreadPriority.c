#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>
#include<sys/time.h>


// To compile use : gcc -o ThreadPriority.out ThreadPriority.c -D_POSIX_THREAD_PRIORITY_SCHEDULING -lpthread -pthread


static int done = 0;


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
	//param_in.sched_priority = 59;
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
		if(x>=100) break;
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
	int priority = 0;

	param.sched_priority = 59;
	pthread_attr_init(&sched_attr);
	pthread_attr_setinheritsched(&sched_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&sched_attr, SCHED_RR);
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

	priority = sched_get_priority_max(SCHED_RR);
	param.sched_priority = priority;
	sched_rr_get_interval(0,&tp);
	sec = (int)tp.tv_sec;
	nsec = (long int)tp.tv_nsec;

	printf("max priority = %d\n",priority);
	printf("Interval : %d (secs) : %ld (nsecs) \n",sec,nsec);

	pthread_join(th1,NULL);	

	printf("=========== ALL is Well ===============\n");
}




