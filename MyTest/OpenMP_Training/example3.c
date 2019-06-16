#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<omp.h>


omp_lock_t lock_A;


int main()
{
	int tid = 0;
	int level = 0;

	omp_set_nested(1);
	omp_init_lock(&lock_A);

	#pragma omp parallel private(tid,level) num_threads(2)
	{
		tid = omp_get_thread_num();
		level = tid;

		#pragma omp parallel private(tid) firstprivate(level) num_threads(3)
		{
			tid = omp_get_thread_num();
			#pragma omp critical
			//omp_set_lock(&lock_A);
			printf("Thread(%d,%d) inside - Lock Acquired !\n",level,tid);
			//omp_unset_lock(&lock_A);
		}
	}
	omp_destroy_lock(&lock_A);
	printf("DONE....!\n");
	return(0);
}


