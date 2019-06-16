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

static const char *StrPool1[] = {
				"ranjit",
				"praveen",
				"suneel",
				"rajesh",
				"vinay",
				"sanjay",
				"ajay",
				"kamal",
				"soniya",
				"snadeep",
				"promod",
				"vicky",
				"pintu",
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
		//printf("pool[%d] = %s\n",i,pool[i]);
	}
	return flag;	
}


void *TaskFunction(void *arg)
{
	BOOL ret = FALSE;
	int *val = (int*)arg;
	pthread_t id;

	id = pthread_self();
	printf("val = %d\n",*val);
	taskdone++;
	while(1)
	{
		if(*val == 1)
		{
			printf("scanning.....\n");
			sleep(5);
			ret = ScanString(StrPool1,"pintu");
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
	//ExitTask(id);
	return NULL;
}



BOOL CreateTask(pthread_t *pTaskId, void *(*task_function)(void *), void *arg)
{
	int retVal = 0;

	retVal= pthread_create(pTaskId, NULL /* attr */, task_function, arg);
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

	printf("thread_t xid( d ) = %d\n",xid);
	printf("thread_t xid( u ) = %u\n",xid);
	if(CreateTask(&taskId1, TaskFunction, &x) == FALSE)
	{
		fprintf(stderr,"ERROR : CreateTask1 - Failed !!!\n");
		exit(EXIT_FAILURE);
	}
	while(taskdone != 1)
	{
		printf("Task1 : waiting\n");
		usleep(100);
	}
	if(CreateTask(&taskId2, TaskFunction, &y) == FALSE)
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
	printf("taskId1 = %d\n",taskId1);
	printf("taskId2 = %d\n",taskId2);
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






