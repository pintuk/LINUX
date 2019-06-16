#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#include "library2.h"

//extern void Function1(int c);


static int done = 0;


void CallFromThread2()
{
	Function1(2);
}


void *Thread2(void *arg)
{
	int flag = 0; int x = 0;

	done++;
	printf("Thread2 - Created !!!\n");
	while(flag==0)
	{
		sleep(1);
		//Function1(2);
		CallFromThread2();
		x++;
		if(x>=20) break;
	}
	printf("Thread2 - Ended !!!\n");

	return NULL;
}

void CreateThread2(pthread_t *th2)
{
	//pthread_t th2;

	printf("main : Inside Main -\n");
	pthread_create(th2, NULL, Thread2, NULL);

	while(done < 1)
	{
		printf("Waiting.....\n");
	}
	printf("====== thread2 Ready =====\n");

	//pthread_join(th2,NULL);
}


