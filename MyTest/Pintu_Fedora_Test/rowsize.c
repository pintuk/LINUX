#include<stdio.h>


#define N 3


void func(int **p)
{
	printf("p[1][1] = %d\n",*((p+1)+1));
}


main()
{
	int A[N][N] = { 
					{1,2,3},
					{4,5,6},
					{7,8,9}
				  };

	func((int **)A);
}


