#include <stdio.h> 
#include <sys/types.h> 
#include <pthread.h> 


void *hello(void *arg) 
{ 
        printf("Hello from node %d\n", *(int *)arg); 



} 


int main(int argc, char* argv[]) 
{ 
        int n,i; 
        pthread_t threads[2]; 

        n = 2; 


        /* Start up thread */ 
        for (i = 0; i < n; i++) 
        { 
                pthread_create(&threads[i], NULL, hello, (void *)&i); 
        } 


        /* Synchronize the completion of each thread. */ 
        for (i = 0; i < n; i++) 
        { 
                pthread_join(threads[i],NULL); 
        } 
    printf("pthread_test returns \n"); 
    return 0; 


} 
