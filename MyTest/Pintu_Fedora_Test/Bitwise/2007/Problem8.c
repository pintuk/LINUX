#include<stdio.h>
#include<stdlib.h>


#define		INFINITY	99999


int power(int x, int v)
{
	int i = 0; int p = 1;

	for(i=0; i<v; i++)
	{
		p = p*x;
	}
	return(p);
}

int FindMin(int n, int *A)
{
	int i = 0;
	int min = A[0];

	for(i=0; i<n; i++)
	{
		if(A[i] < min) min = A[i];
	}
	return(min);
}

void Initialize(int n, int *K)
{
	int i = 0;

	for(i=1; i<=n; i++)
	{
		K[i] = INFINITY;
	}
}

main()
{
	int n = 0;
	int valuei[100]; int cost[5000]; int K[100]; int A[100];
	int S = 0; int s = 0; int dist[100];
	int i = 0; int j = 0; int k = 0;


	printf("Enter the number of tyres:-\n");
	scanf("%d",&n);
	printf("Enter the value of each i <whitespace> costs:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d %d",&valuei[i],&cost[i]);
		dist[i] = power(2, valuei[i]);
	}
	printf("Enter the max distance:-\n");
	scanf("%d",&S);

	Initialize(S, K);
	K[0] = 0;

	for(s=1; s<=S; s++)
	{
		k = 0;
		for(i=0; i<n; i++)
		{
			if(dist[i] <= s)
			{
				A[k] = K[s - dist[i]] + cost[i];
				printf("A[%d]->(K[%d] + %d) = %d\n",k,(s-dist[i]),cost[i],A[k]);
				k++;
			}
		}
		K[s] = FindMin(k, A);
		printf("---- min K[%d] = %d -----\n",s,K[s]);
	}
	printf("Min cost = %d\n",K[S]);
}


