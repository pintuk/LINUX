#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MOD_VALUE	1000000007


long long int FindCommonTime(int i, int M, int *A)
{
	int j,k;
	long long int x=1;

	for(j=i; j<(i+M-1); j++)
	{
		B[x] = A[j]*x;
	}
}

int main()
{
	int i,j;
	int N,M;
	int A[50000];
	long long int x=0;

	scanf("%d %d",&N,&M);
	for(i=1; i<=N; i++)
	scanf("%d",&A[i]);

	for(i=1; i<(N-M+1); i++)
	{
		x = FindCommonTime(i,M,A);
		x = x%MOD_VALUE;
		printf("%lld ",x);
	}
	printf("\n");
		
	return 0;
}

