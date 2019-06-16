#include<stdio.h>
#include<stdlib.h>


int FindMax(int n, int *S)
{
	int i = 0;
	int max = 0;

	max = S[0];
	for(i=0; i<n; i++)
	{
		if(S[i] > max) max = S[i];
	}
	return(max);
}


void Initialize(int n, int *S)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		S[i] = 0;
	}
}

main()
{
	int S[100]; int a[100]; int n = 0; int x = 0; int sumj = 0; int store[100];
	int i = 0; int j = 0; int k = 0; int max = 0; int l = 0; int len = 0;
	int K[100];

	printf("Enter the length:-\n");
	scanf("%d",&n);
	printf("Enter the sequence:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d",&a[i]);
	}

	Initialize(n, S); Initialize(n, K);
	
	for(i=1; i<=n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(a[j] < a[i])
			S[j] = K[i];
		}
		K[i] = FindMax(n, S);
	}
	
	printf("\nMax Length = %d\n",K[i]);
	printf("And Sequence is :-\n");
	for(i=0; i<x; i++)
	{
		//printf("%5d",store[i]);
	}
	printf("\n");
}



