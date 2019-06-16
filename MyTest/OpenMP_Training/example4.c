#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<omp.h>



int main()
{
	int i = 0;
	long int sum = 0;
	printf("OpenMP test....\n");

	#pragma omp parallel private(i) num_threads(10)
	{
		//static int j = 1;
		#pragma omp for private(i) reduction(+:sum)
		for(i=1; i<=100; i++)
		{
			//sleep(1);
			sum = sum + i;
		}
	}
	printf("SUM = %ld\n",sum);
	printf("DONE....!\n");
}


