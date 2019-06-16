#include<stdio.h>
#include<stdlib.h>


#define		INFINITY	999999999
//long long int INFINITY = 9999999999;

int FindMin(int n, int *K)
{
	int i = 0;
	int min = 0;

	min = K[0];
	for(i=0; i<n; i++)
	{
		if(K[i] < min) min = K[i];
	}
	return(min);
}

void Initialize(int n, int *A)
{
	int i = 0;
	for(i=0; i<n; i++)
	{
		A[i] = INFINITY;
	}
}

void PrintList(int n, int *K)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		printf("%5d",K[i]);
	}
	printf("\n");
}

main()
{
	int n = 0; int pos = 0;
	int W = 0;
	int hotel[50] = {0}; int S[500] = {0}; int K[500] = {0}; int store[100];
	int i = 0; int w = 0; int penalty = 0; int sum = 0;
	int opval = 0; int x = 0; int p = 0;
	
	printf("Enter the number of hotels:-\n");
	scanf("%d",&n);
	printf("Enter the miles for each hotels:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d",&hotel[i]);
	}
	Initialize(n, S); Initialize(n, K); Initialize(n, store);

	x = 0; p = 0; sum = 0;
	for(pos=0; pos<n; pos++)
	{
	for(i=pos; i<n; i++)
	{
		if(hotel[i] >= 200 || (i == (n-1)))
		{
			x = hotel[i] - x;
		}
		else
		x = hotel[i];
		
			penalty = (200-x)*(200-x);
			//sum = sum + penalty;
			S[i] = penalty;
			printf("S[%d] = %d\n",i,S[i]);
	}
	K[pos] = FindMin(n, S);
	for(i=0; i<n; i++)
	{
		if(S[i] != INFINITY && (K[pos] == S[i]))
		{
			store[i] = i;;
		}
	}
	}
	printf("\nHotel numbers to stop :-\n");
	for(i=0; i<n; i++)
	{
		if(store[i] != INFINITY)
		{
			printf("%5d ",i+1);
		}
	}
	opval = K[pos];
	printf("\nThe optimal value obtained is = %d\n",opval);
}



