#include <stdio.h>

float average(unsigned int a, unsigned int b)
{
	float avg = 0.00;

	avg = (a >> 1) + (b >> 1) + (a & b & 1);

	return avg;
}

int main(int argc, char *argv[])
{
	unsigned int a,b;
	float avg;

	printf("Enter 2 numbers: ");
	scanf("%u %u", &a, &b);
	avg = average(a, b);
	printf("Average of (%u, %u): %5.2f\n", a,b,avg);

	return 0;
}

