#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>
#include<sys/time.h>
#include<signal.h>
#include<string.h>
#include<errno.h>



#define FALSE 		0
#define TRUE 		1

typedef unsigned char BOOL;
pthread_t taskId1 = -1;
pthread_t taskId2 = -1;
static volatile int taskdone = 0;

static const char *StringPool[] = {"ranjit","praveen","suneel","rajesh","vinay","sanjay","ajay","kamal","soniya","sandeep",
				   "promod","vicky","pintu","pinky","chaya","manish","iqbal","varun","nitish","manju",
				   NULL,
				  };


BOOL ScanString(const char *pool[],const char*str)
{
	int i = 0;
	BOOL flag = FALSE;

	for(i=0; pool[i] != NULL; i++)
	{
		if(strcmp(pool[i],str) == 0)
		{
			printf("Found : %s\n",pool[i]);
			flag = TRUE;
			break;
		}
	}
	return flag;	
}


void *TaskFunction2(void *arg)
{
	BOOL ret = FALSE;
	int *val = (int*)arg;
	pthread_t id;
	int policy = 0;
	struct sched_param param;

	id = pthread_self();
	taskdone++;
	printf("val = %d\n",*val);
	pthread_getschedparam(id, &policy, &param);
        printf("Thread Priority Set to : %d, POLICY = %d\n",(int)param.sched_priority,policy);
	while(1)
	{
		if(*val == 1)
		{
			printf("scanning.....\n");
			sleep(5);
			ret = ScanString(StringPool,"pintu");
			if(ret == TRUE)
			{
				printf("<<<<<    FOUND    >>>>>\n");
				sleep(3);
				break;
			}
		}
		if(*val == 2)
		{
			printf("Thread 2 : <nothing doing>\n");
			break;
		}
	}
	printf("Task exiting : <%u>\n",(unsigned int)id);
	return NULL;
}

void *TaskFunction1(void *arg)
{
	BOOL ret = FALSE;
	pthread_t id;
	int *val = (int*)arg;
	int policy = 0;
	struct sched_param param;

	id = pthread_self();
	taskdone++;
	pthread_getschedparam(id, &policy, &param);
	printf("Thread Priority Set to : %d, POLICY = %d\n",(int)param.sched_priority,policy);
        while(1)
        {
		printf("Task1 : scanning.....\n"); 
		sleep(2);
		ret = ScanString(StringPool,"pintu");
		if(ret == TRUE) {
			printf("<<<<<    FOUND    >>>>>\n");
			sleep(3);
			break;
		}
        }
        printf("Task exiting : <%u>\n",(unsigned int)id);
}


BOOL CreateTask(pthread_t *pTaskId, void *(*task_function)(void *), void *arg)
{
	int retVal = 0;
	pthread_attr_t sched_attr;
	struct sched_param param;
	int priority = 0;

        param.sched_priority = 75;
        pthread_attr_init(&sched_attr);
        pthread_attr_setinheritsched(&sched_attr, PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&sched_attr, SCHED_RR);
        pthread_attr_setschedparam(&sched_attr, &param );
        /* Set the thread policy before creating the thread */
        /* OR Set the policy after creating the thread and inside the thread */
	retVal= pthread_create(pTaskId, &sched_attr, task_function, arg);
	if(retVal != 0)
	{
		fprintf(stderr,"ERROR : pthread_create - Failed ! , reason = %s\n",strerror(errno));
		*pTaskId = -1;
		pTaskId = NULL;
		return FALSE;
	}
	printf("SUCCESS : CreateTask : TaskID (%u)\n",(unsigned int)*pTaskId);

	return TRUE;
}

BOOL ExitTask(pthread_t pTaskId)
{
	if(pTaskId < 0)
	{
		fprintf(stderr,"ERROR : ExitTask Failed : UnKnown Task ID (%u) \n", (unsigned int)pTaskId);
		return FALSE;
	}
	pthread_exit((void *)0);
	return TRUE;
}

BOOL WaitForTaskExit(pthread_t pTaskId)
{
	int ret = 0;

	if(pTaskId < 0)
	{
		fprintf(stderr,"ERROR : WaitForTaskExit Failed , TaskId < 0\n");
		return FALSE;
	}
	ret = pthread_join(pTaskId, NULL);
	if (ret != 0)
	{
		fprintf(stderr,"ERROR : WaitForTaskExit - pthread_join - Failed , reason = %s\n",strerror(errno));
		return FALSE;
	}
	//pthread_detach(pTaskId);
	return TRUE;
}


int main()
{
	int x = 1;
	int y = 2;
	pthread_t xid = -1;

	printf("thread_t xid( d ) = %u\n",(unsigned int)xid);
	printf("thread_t xid( u ) = %u\n",(unsigned int)xid);
	if(CreateTask(&taskId1, TaskFunction1, &x) == FALSE)
	{
		fprintf(stderr,"ERROR : CreateTask1 - Failed !!!\n");
		exit(EXIT_FAILURE);
	}
	while(taskdone != 1)
	{
		printf("Task1 : waiting\n");
		usleep(100);
	}
	if(CreateTask(&taskId2, TaskFunction2, &y) == FALSE)
	{
		fprintf(stderr,"ERROR : CreateTask2 - Failed !!!\n");
		exit(EXIT_FAILURE);
	}
	while(taskdone != 2)
	{
		printf("Task2 : waiting\n");
		usleep(100);
	}
	WaitForTaskExit(taskId2);
	WaitForTaskExit(taskId1);
	taskId1 = -1;
	taskId2 = -1;
	printf("taskId1 = %u\n",(unsigned int)taskId1);
	printf("taskId2 = %u\n",(unsigned int)taskId2);
	if(taskId1 != (pthread_t)(-1))
	{
		printf("detaching....task1\n");
		pthread_detach(taskId1);
	}
	if(taskId2 > (pthread_t)(-1))
	{
		printf("detaching....task2\n");
		pthread_detach(taskId2);
	}
	
	printf("-------   ALL  DONE   --------\n");
	return 0;
}






