#include <stdio.h>


#define mysizeof(type)	((int)((__typeof__(type)*)0 + 1))
//#define mysizeof(X) ((int)(&(*(__typeof__(X) *)0) + 1))
//#define mysizeof(X) ((int)(&(*(__typeof__(X)*)0) + 1))


struct xyz {
	int x;
	float y;
	char z;
};

int main()
{
	int x;
	printf("size of int: %d\n", mysizeof(int));
	printf("size of double: %d\n", mysizeof(double));
	printf("size of unsigned int: %d\n", mysizeof(unsigned int));
	printf("size of long: %d\n", mysizeof(long));
	printf("size of unsigned long long: %d\n", mysizeof(unsigned long long));
	printf("size of struct xyz: %d\n", mysizeof(struct xyz));
	printf("size of int x: %d\n", mysizeof(x));
	printf("size of x++: %d\n", mysizeof(x++));

	return 0;
}

