#include<stdio.h>
#include<pthread.h>

#include "library.h"

extern void Function1();


extern void CreateThread1(pthread_t *);
extern void CreateThread2(pthread_t *);

int main()
{
	pthread_t th1, th2;

	printf("main : Inside Main -\n");
	//pthread_create(&th1, NULL, Thread1, NULL);
	//pthread_create(&th2, NULL, Thread2, NULL);

	CreateThread1(&th1);
	CreateThread2(&th2);

	printf("====== All threads Ready =====\n");

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	//Function1();

	printf("Main --- FINISHED \n");
	return 0;
}


