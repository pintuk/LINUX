
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include<signal.h>



char *gbuffer[1024] = {0};
int shared_data=0;
pthread_mutex_t mlock;
pthread_cond_t pcond;
int flag=0;

int done = 0;


void ReadNormalFunction(int arg);



void *write_data(void *arg)
{
	int i = 0; int n=0;
	unsigned char buff[50] = {0};

	n = (int)arg;

	done = 1;

	for(i=1; i<=n; i++)
	{
		pthread_mutex_lock(&mlock);
			memset(buff,0,sizeof(buff));
			sprintf(buff,"SomeData-%d",i);
			gbuffer[i] = (unsigned char *)malloc(sizeof(buff));
			memcpy(gbuffer[i], buff, sizeof(buff));
			printf("Written\t - %s\n",gbuffer[i]);
			shared_data = i;
			//pthread_cond_signal(&pcond);
		pthread_mutex_unlock(&mlock);
			//pthread_cond_signal(&pcond);
		usleep(100); 

		ReadNormalFunction(i);

		free(gbuffer[i]);
	}

	//free(gbuffer);

	printf("===== WRITE - FINISHED =====\n");
	pthread_exit((void *)0);
}

void ReadNormalFunction(int arg)
{
	#define MAX_IPC_BUFF_SIZE  8000
	int i = 0; int n = 0;
	struct timespec tm;
	int err = -1;
	unsigned char recvBuf[8000] = {0};
	int bytes_read = 0;
	

	i = arg;
	//for(i=1; i<=n; i++)
	{
		pthread_mutex_lock(&mlock);
			clock_gettime(CLOCK_REALTIME, &tm);
			tm.tv_sec += 5;
			//tm.tv_nsec += 1000*1000; //tm.tv_nsec + (milisec * 1000000);
			printf("waiting.....\n");
			//err = pthread_cond_timedwait(&pcond, &mlock, &tm);
			if(err == ETIMEDOUT)
			{
				printf("Timed out !!!\n");
				sleep(1);
			}
			else
			{
				printf("----- received ------\n");
				memset(recvBuf, 0, sizeof(recvBuf));
				if(gbuffer[i] != NULL)
				{
					memcpy(recvBuf, gbuffer[i], MAX_IPC_BUFF_SIZE);
					bytes_read = strlen(recvBuf);
					printf("Read \t - %s\n\n",recvBuf);
					//free(gbuffer[i]);
				}
				sleep(1);
			}
		pthread_mutex_unlock(&mlock);
	}

	//printf("===== READ - FINISHED =====\n");
	//pthread_exit((void *)0);

}


main()
{
	pthread_t th1, th2;
	int n=10;

	pthread_mutex_init(&mlock,NULL);
	pthread_cond_init(&pcond,NULL);

	//buffer = (char *)malloc(50*sizeof(buffer));
	//memset(buffer,'\0',sizeof(buffer));
	//buffer=NULL;

	//ReadNormalFunction((void *)n);

	//pthread_create(&th2,NULL,&read_data,(void *)n);
	pthread_create(&th1,NULL,&write_data,(void *)n);
	printf("----- Main - Thread -------\n");
	while(done != 1);

	//ReadNormalFunction((void *)n);
	sleep(5);

	pthread_join(th1,NULL);
	//pthread_join(th2,NULL);


	printf("\n ----- ALL - DONE -----\n");

}

