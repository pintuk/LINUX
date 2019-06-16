#include <stdio.h> 
#include <sys/types.h> 
#include <pthread.h> 
#include<unistd.h>
#include<stdlib.h>
#include <semaphore.h>

volatile static int terminate = 0;
pthread_mutex_t mlock;
pthread_cond_t pcond;
sem_t sem;
volatile static int thread1 = 0;

void *Function1(void *arg)
{
	int count = 0;
	//printf("Inside.....Function1\n");

	thread1 = 1;

	while(!terminate)
	{
		//sem_wait(&sem);
		pthread_mutex_lock(&mlock);
		//printf("Function1 - count = %d\n", ++count);
		printf("A\n");
		pthread_mutex_unlock(&mlock);
		//sleep(1);
		//pthread_cond_timedwait(&pcond, &mlock, &tm);
		sem_post(&sem);
		sem_wait(&sem);
		sleep(1);
	}
}

void *Function2(void *arg)
{
	int count = 0;
	//printf("Inside.....Function2\n");
	while(!terminate)
	{
		sem_wait(&sem);
		pthread_mutex_lock(&mlock);
		//printf("Function2 -------------- count = %d\n", ++count);
		printf("B\n");
		count++;
		pthread_mutex_unlock(&mlock);
		//sleep(1);
		sem_post(&sem);

		if (count >= 10)
			terminate = 1;
		sleep(1);
	}
}


int main(int argc, char* argv[]) 
{ 
        pthread_t th1, th2;
	pthread_mutex_init(&mlock,NULL);
	pthread_cond_init(&pcond,NULL);
	sem_init(&sem, 0, 1);

	pthread_create(&th1, NULL, Function1, NULL);
	while (thread1 == 0);
	pthread_create(&th2, NULL, Function2, NULL);

        /* Synchronize the completion of each thread. */ 
	pthread_join(th1,NULL); 
	pthread_join(th2,NULL);
	sem_destroy(&sem);
	printf("\n");
    printf("DONE !!!! \n"); 
    return 0;
} 
