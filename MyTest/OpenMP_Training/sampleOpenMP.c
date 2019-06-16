#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<omp.h>



int main()
{
	int tid = 0;
	#pragma omp parallel
	{
		tid = omp_get_num_threads();
		//#pragma omp parallel for reduction(+:sum)
	}
	printf("DONE....!\n");
}


