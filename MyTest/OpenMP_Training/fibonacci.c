#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<omp.h>

#define N 10


int fibonacci(int n)
{
	if(n<=1)
		return(n);

	return(fibonacci(n-1)+fibonacci(n-2));
}


int main()
{
	int tid = 0;
	 #pragma omp parallel
	{
		tid = omp_get_num_threads();
		//#pragma omp parallel for reduction(+:sum)
		for(i=0; i<N; i++)
		{
			sum = sum + fibonacci(i);
		}
	}
	printf("DONE....!\n");
}


