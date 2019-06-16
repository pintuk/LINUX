#include<stdio.h>
#include<stdlib.h>

#include<omp.h>

static long num_steps = 999999996;
//static long num_steps = 100000000;
double step = 0;

#define NUM_THREADS 4
	
struct NumStep {
	long int start;
	long int step;
}ns[NUM_THREADS];

int main()
{
	int k = 0;
	//double x = 0.0;
	double pi = 0.0;
	double sum[NUM_THREADS];

	step = 1.0/(double)num_steps;
//#pragma omp parallel shared(step) private(i, x, sum) num_threads(NUM_THREADS)
#pragma omp parallel num_threads(NUM_THREADS)
{
	//#pragma omp parallel for
	long int i = 0;
	double x = 0.0;
	int tid = 0;
	
	tid = omp_get_thread_num();

	//ns[tid].step = num_steps/NUM_THREADS;
	//ns[tid].start = (tid*num_steps)/NUM_THREADS;

	sum[tid] = 0;
	#pragma omp for
	for(i=0; i<num_steps; i++)
	{
		x = (i-0.5)*step;
		sum[tid] = sum[tid] + 4.0/(1.0+x*x);
	}
	//printf("sum = %lf\n",sum[tid]);
}
	for(k=0; k<NUM_THREADS; k++)
	pi = pi + step*sum[k];
	
	printf("PI = %lf\n",pi);

	return 0;
}

