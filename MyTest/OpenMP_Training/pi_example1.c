#include<stdio.h>
#include<stdlib.h>

#include<omp.h>

static long num_steps = 999999996;
double step = 0;


int main()
{
	int i = 0;
	double x = 0.0;
	double pi = 0.0;
	double sum = 0.0;

	step = 1.0/(double)num_steps;
#pragma omp parallel shared(step) private(i, x, sum) num_threads(10)
{
	//#pragma omp for
	for(i=0; i<=num_steps; i++)
	{
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
//}
	pi = step*sum;
}
	printf("PI = %lf\n",pi);

	return 0;
}

