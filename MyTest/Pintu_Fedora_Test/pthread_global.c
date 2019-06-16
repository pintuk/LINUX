
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include<signal.h>
#include<assert.h>

#define		LIVE	1


#define H324M_ASSERT(expr) \
		do { \
				if (!(expr)) \
				{ \
					fprintf(stderr, #expr); \
					abort(); \
				} \
			} while(0)





pthread_t th1, th2;
pthread_mutex_t *mlock = NULL;
pthread_cond_t pcond;

pthread_attr_t  pattr;

static char *buffer = NULL;
static char T2Buffer[176*144*3/2] = {0};
volatile static int terminate = 0;
volatile static int terminate_t2 = 0;
volatile static int SOURCE = 0;


void ObtainLock()
{
	H324M_ASSERT(mlock != NULL);
	pthread_mutex_lock(mlock);
}
void ReleaseLock()
{
	H324M_ASSERT(mlock != NULL);
	pthread_mutex_unlock(mlock);
}
void DestroyLock()
{
	H324M_ASSERT(mlock != NULL);
	pthread_mutex_destroy(mlock);
	free(mlock);
	//mlock = NULL;
}



void GetBufferData(char *buf)
{
	char *data = NULL;
	static int i = 1;

	data = (char *)malloc(50 * sizeof(char));
	
	sprintf(data,"Hello-%d",i++);
	memcpy(buf,data,strlen(data));

	//free(data);

	//if(i > 50) raise(SIGSEGV);
}

void PutBuffer(char *pbuffer)
{
	int ret = -1;
	int len = 176*144*3/2;
	//sleep(2);
	//while(1)
	if(terminate_t2 == 0)
	{
		ObtainLock();
		sleep(1);
		memcpy(T2Buffer, pbuffer, len);
		ReleaseLock();
	}
}

void Delete_Memory()
{
	printf("Delete...Memory\n");
	terminate = 1;
	free(buffer);
	buffer = NULL;
	printf("Delete...Done\n");
}

void *thread_function(void *arg)
{
	static int i = 1; int n=0;
	char *tmpbuf;
	static char pOutBuf[50] = {0};
	int ret = 0;

	n = (int)arg;
	printf("Thread1.......Created !!!!\n");
	while(terminate == 0)
	{
		switch(SOURCE)
		{
			case LIVE:
		//pthread_mutex_lock(&mlock);
			//memset(buff,0,sizeof(buff));
			GetBufferData(buffer);
			usleep(200);
			printf("%s\n",buffer);
			memcpy(pOutBuf, buffer, 50);
			tmpbuf = pOutBuf;
			//pthread_cond_signal(&pcond);
		//pthread_mutex_unlock(&mlock);
			//sleep(1);
			PutBuffer(tmpbuf);
			break;
		}
	}
	printf("Thread.......EXITED !!!!\n");
	terminate = 1;

	return NULL;
	
	//Delete_Memory();
	//pthread_exit((void *)0);
	//pthread_detach(pthread_self());
}



void *thread_function2(void *arg)
{
	int ret = -1;
	char Buf[176*144*3/2] = {0};
	printf("Thread - 2\n");
	//sleep(2);
	while(terminate_t2 == 0)
	{
		ObtainLock();
		memcpy(Buf, T2Buffer, sizeof(Buf));
		printf("Data at Thread 2 = %s\n",Buf);
		sleep(1);
		ReleaseLock();
	}
	printf("Thread - 2 - END\n");
	terminate_t2 = 1;
	DestroyLock();
	pthread_detach(pthread_self());

	terminate = 1;
	//th1 = 0;
	//pthread_exit((void *)0);
	printf("T2 - Waiting for T1\n");
	pthread_join(th1, NULL);

	return NULL;
}

main()
{
	int n=10;
	int stacksize = 0;
	int ret = 0;
	void *treturn = NULL;

	mlock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	
	pthread_mutex_init(mlock,NULL);
	pthread_cond_init(&pcond,NULL);

	//pthread_attr_init(&pattr);
	//pthread_attr_setdetachstate(&pattr, PTHREAD_CREATE_JOINABLE);

	buffer = (char *)malloc(50*sizeof(buffer));
	memset(buffer,'\0',sizeof(buffer));
	terminate = 0;
	terminate_t2 = 0;
	SOURCE = LIVE;
	printf("Create Thread..........\n");
	pthread_create(&th1,&pattr,&thread_function,(void *)n);
	//sleep(1);
	pthread_create(&th2,&pattr,&thread_function2,(void *)n);

	printf("----- Main - Thread -------\n");
	//pthread_attr_getstacksize(&pattr, &stacksize);
	//printf("Thread Stack Size = %d\n",stacksize);
	sleep(2);
	terminate_t2 = 1;
	printf("join....waiting2\n");
	if( (ret = pthread_join(th2,&treturn)) != 0)
	{
		fprintf(stderr,"Main pthread_join(th2) : %d (%s)\n",strerror(errno));
		printf("Main T2 - ret = %d\n",ret);
	}
	
	sleep(5);
	terminate = 1;
	sleep(2);
	//th1 = 0;
	printf("join....waiting1 - TID = %x\n",th1);
	if( (ret = pthread_join(th1,&treturn)) != 0)
	{
		fprintf(stderr,"Main pthread_join(th1) : %d (%s)\n",strerror(errno));
		printf("Main T1 - ret = %d\n",ret);
	}
	Delete_Memory();
	//pthread_detach(pthread_self());
	//pthread_attr_destroy(&pattr);
	/* If I put the below function here. I get Segmentation Fault */
	
	printf("Thread.......Deleted !!!!\n");
	
	printf("\n");
	printf("============================================\n");
	//pthread_detach(th1);

}

