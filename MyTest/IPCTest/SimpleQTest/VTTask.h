#ifndef __VTTASK_H
#define __VTTASK_H

#include <pthread.h>
#include "commontypes.h"


BOOL CreateTask(pthread_t *pTaskId, const char *taskName, void *(*task_function)(void *), void *arg);
BOOL ExitTask(pthread_t pTaskId);

BOOL WaitForTaskExit(pthread_t pTaskId);



#endif
