#include<stdio.h>
#include<stdlib.h>

#include<omp.h>

static long num_steps = 999999999;
//static long num_steps = 10000;
//static long num_steps = 100000000;
double step = 0;

#define NUM_THREADS 4
	
struct NumStep {
	int start;
	int step;
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
	int i = 0;
	int j = 0;
	double x = 0.0;
	int tid = 0;
	
	tid = omp_get_thread_num();

	ns[tid].step = num_steps/NUM_THREADS + 1;
	ns[tid].start = ( ((tid*num_steps)/NUM_THREADS) + tid)+1;

	sum[tid] = 0;
	//#pragma omp barrier
	j = ns[tid].start;
	//for(i=0; i<NUM_THREADS; i++)
	//for(i=ns[tid].start,j=0; i<ns[tid].start; i++)
	for(i=j; i<(j+ns[tid].step); i++)
	//for(i=tid; i<num_steps; i+=NUM_THREADS)
	{
		x = (i-0.5)*step;
		//x = (i+0.5)*step;
		sum[tid] = sum[tid] + 4.0/(1.0+x*x);
		if(i>num_steps) break;
		//j++;
	}
	//printf("sum = %lf\n",sum[tid]);
}
	for(k=0; k<NUM_THREADS; k++)
	pi = pi + step*sum[k];
	
	printf("PI = %lf\n",pi);

	return 0;
}

