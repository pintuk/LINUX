#include <stdio.h> 
#include <sys/types.h> 
#include <pthread.h> 
#include<unistd.h>


#define MAX_THREADS	2


void *ThreadFunction(void *arg) 
{
	int i = 0; 
	int n = *(int *)arg;
	printf("The value of n = %d\n",n);

	for(i=0; i<n; i++)
	{
		sleep(1);
		printf("Thread[0x%x] - Doing Something !\n",(int)pthread_self());
	}
} 


int main(int argc, char* argv[]) 
{ 
        int n = 100;
	int i = 0;
        pthread_t tid[MAX_THREADS]; 


        /* Start up thread */ 
        for (i = 0; i < MAX_THREADS; i++) 
        { 
                pthread_create(&tid[i], NULL, ThreadFunction, (void *)&n); 
        } 


        /* Synchronize the completion of each thread. */ 
        for (i = 0; i < MAX_THREADS; i++) 
        { 
                pthread_join(tid[i], NULL); 
        } 
    printf("ALL FINISHED.......!!!\n"); 
    return 0; 


} 
