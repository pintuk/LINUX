
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

void *write_data(void *arg)
{
	int i = 0; int n=0;
	unsigned char buff[50] = {0};

	n = (int)arg;

	for(i=1; i<=n; i++)
	{
		pthread_mutex_lock(&mlock);
			memset(buff,0,sizeof(buff));
			sprintf(buff,"Write_Data-%d",i);
			gbuffer[i] = (unsigned char *)malloc(sizeof(buff));
			memcpy(gbuffer[i], buff, sizeof(buff));
			printf("Written - %s\n",gbuffer[i]);
			shared_data = i;
			//sleep(2);
			pthread_cond_signal(&pcond);
		pthread_mutex_unlock(&mlock);
		usleep(100); 
		//sleep(2);
	}
	//pthread_exit((void *)0);
}

void *read_data(void *arg)
{
	#define MAX_IPC_BUFF_SIZE  8000
	int i = 0; int n = 0;
	struct timespec tm;
	int err = -1;
	unsigned char recvBuf[8000] = {0};
	int bytes_read = 0;
	

	n = (int)arg;
	//sleep(2);
	for(i=1; i<=n; i++)
	{
		//pthread_cond_wait(&pcond, &mlock);
		pthread_mutex_lock(&mlock);
		clock_gettime(CLOCK_REALTIME, &tm);
		tm.tv_sec += 1;
		//tm.tv_nsec += 1000*1000; //tm.tv_nsec + (milisec * 1000000);
		printf("waiting.....\n");
		err = pthread_cond_timedwait(&pcond, &mlock, &tm);
		//pthread_cond_wait(&pcond, &mlock);
		
		if(err == ETIMEDOUT)
		{
			printf("Timed out !!!\n");
		}
		else
		{
			memset(recvBuf, 0, sizeof(recvBuf));
			memcpy(recvBuf, gbuffer[i], MAX_IPC_BUFF_SIZE);
			bytes_read = strlen(recvBuf);
			printf("Read Data  -  %s\n\n",recvBuf);
			sleep(1);
			free(gbuffer[i]);
		}
		pthread_mutex_unlock(&mlock);
	}
	//while(1)
	{
		printf("read....\n");
		sleep(1);
	}
	//pthread_exit((void *)0);

	printf("read_data --- done\n");
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

	pthread_create(&th2,NULL,&read_data,(void *)n);
	pthread_create(&th1,NULL,&write_data,(void *)n);
	printf("----- Main - Thread -------\n");
	sleep(5);
	//pthread_kill(th1, SIGTERM);
	//pthread_kill(th2, SIGTERM);
	//pthread_join(th1,NULL); //wait for th1 exit
	//pthread_join(th2,NULL); //wait for th2 exit

	pthread_join(th1,NULL);
	//th1=-1;
	//printf("th1 = %d\n",th1);
	//pthread_join(th1,NULL);
	
	pthread_join(th2,NULL);

	//pthread_detach(th1);
	//pthread_detach(th2);
	//pthread_cancel(th1);
	//pthread_cancel(th2);

	//printf("\nMain Read = %s\n",buffer);
	//buffer=NULL;
	//free(buffer);


}

