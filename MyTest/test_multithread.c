#include <stdio.h> 
#include <sys/types.h> 
#include <pthread.h> 
#include<unistd.h>
#include<stdlib.h>

volatile static int terminate = 0;

typedef struct packet {
	char *buf;
} pkt_t;

pkt_t pktbuf;

void *Function1(void *arg)
{
	printf("Inside.....Function1\n");
	while(terminate == 0)
	{
		//sleep(20);
		//printf("Ok...Function1 is done\n");
		pkt_t pkt;
		pkt.buf = pktbuf.buf;
		char *buf = pkt.buf;
		printf("Function1 - buf addr = %p\n", buf);
		free(buf);
		//terminate = 1;
		sleep(1);
	}
}

void *Function2(void *arg)
{
	printf("Inside.....Function2\n");
	while(terminate == 0)
	{
		int i=0;
		char *buf = NULL;
		pkt_t pkt;
		for (i=0; i<100; i++) {
			buf = malloc((32+i)*sizeof(int));
			printf("Function2 - buf addr = %p\n", buf);
			pkt.buf = buf;
			pktbuf.buf = pkt.buf;
			sleep(1);
		}
		//sleep(15);
		//printf("Ok...Function2 is done\n");
		terminate = 1;
	}
}



int main(int argc, char* argv[]) 
{ 
        pthread_t th1, th2; 


	pthread_create(&th1, NULL, Function1, NULL);
	pthread_create(&th2, NULL, Function2, NULL);

        /* Synchronize the completion of each thread. */ 
	pthread_join(th1,NULL); 
	pthread_join(th2,NULL); 
    printf("DONE !!!! \n"); 
    return 0; 


} 
