#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<omp.h>



int main()
{
	int i = 0;
	int n1 = 0;
	int n2 = 0;
	long int sum = 0;
	printf("OpenMP test....\n");

	#pragma omp parallel
	{
		n1 = omp_get_num_procs();
		printf("Number of cores = %d\n",n1);
		n2 = omp_get_num_threads();
		printf("Number of threads = %d\n",n2);
		#pragma omp for reduction(+:sum)
		for(i=1; i<=10; i++)
		{
			//sleep(1);
			sum = sum + i;
		}
	}
	printf("SUM = %ld\n",sum);
	printf("DONE....!\n");
}


