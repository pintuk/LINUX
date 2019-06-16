#include <stdio.h>


int ispowerof2(int x)
{
	return (x && !(x & (x-1)));
}

int main()
{
	int num;
	int val=0;

	printf("Enter a number: ");
	scanf("%d", &num);
	val = ispowerof2(num);
	printf("val = %d\n", val);
	if (val)
		printf("%d number is power of 2\n", num);
	else
		printf("NOT power of 2\n");

	return 0;
}

