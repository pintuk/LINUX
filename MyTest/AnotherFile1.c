#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include "library1.h"

//extern void Function1(int c);


static int done = 0;

void CallFromThread1()
{
	Function1(1);
}


void *Thread1(void *arg)
{
	int flag = 0; int x = 0;

	done++;
	printf("Thread1 - Created !!!\n");
	while(flag==0)
	{
		sleep(2);
		//Function1(1);
		CallFromThread1();
		x++;
		if(x>=20) break;
	}
	printf("Thread1 - Ended !!!\n");

	return NULL;
}

void CreateThread1(pthread_t *th1)
{
	//pthread_t th1;

	printf("main : Inside Main -\n");
	pthread_create(th1, NULL, Thread1, NULL);

	while(done < 1)
	{
		printf("Waiting.....\n");
	}
	printf("====== thread1 Ready =====\n");

	//pthread_join(th2,NULL);
}


