#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include "VTTask.h"


//typedef struct {
//	pthread_t tId;
//	const char *tName;
//}TaskList;

//TaskList list;

BOOL CreateTask(pthread_t *pTaskId, const char *taskName, void *(*task_function)(void *), void *arg)
{
	int retVal = 0;

	retVal= pthread_create(pTaskId, NULL /* attr */, task_function, arg);
	if(retVal != 0)
	{
		fprintf(stderr,"ERROR : CreateTask(%s) - pthread_create - Failed ! , reason = %s\n",taskName, strerror(errno));
		return FALSE;
	}
	//list.tId = *pTaskId;
	//list.tName = taskName;

	//printf("SUCCESS : CreateTask : TaskName (%s)\n",taskName);

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
	return TRUE;
}

