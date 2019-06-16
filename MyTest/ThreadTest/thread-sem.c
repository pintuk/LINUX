#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


pthread_mutex_t mlock;
sem_t sem1,sem2, semth;
volatile int terminate = 0;

void *function1(void *arg)
{
	sem_post(&semth);

	sem_init(&sem1, 0, 1);
	while (!terminate) {
		sem_wait(&sem2);
		printf("A\n");
		sem_post(&sem1);

		usleep(100);
	}

	return NULL;
}

void *function2(void *arg)
{
	int count = 0;
	sem_init(&sem2, 0, 1);
	while (!terminate) {
		sem_wait(&sem1);
		printf("B\n");
		count++;
		sem_post(&sem2);

		if (count >= 10)
			terminate = 1;

		usleep(100);
	}

	return NULL;
}

int main()
{
	pthread_t t1, t2;

	pthread_mutex_init(&mlock, NULL);
	//sem_init(&sem, 0, 1);
	sem_init(&semth, 0, 1);

	pthread_create(&t1, NULL, &function1, NULL);
	sem_wait(&semth);
	pthread_create(&t2, NULL, &function2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("\nDONE\n");

	return 0;
}
