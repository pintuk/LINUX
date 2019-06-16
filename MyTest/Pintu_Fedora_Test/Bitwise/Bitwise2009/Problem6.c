#include<stdio.h>
#include<stdlib.h>


#define MAXCASES	50


int gcd ( int a, int b )
{
	int c = 0;
	while ( a != 0 ) 
	{
		c = a; a = b%a;  b = c;
	}
	return b;
}


int FindSum(int n, int t, int E[10][MAXCASES][MAXCASES], int M[10][MAXCASES][MAXCASES])
{
	int i = 0; int j = 0;
	int sum = 0;

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(E[t][i][j] == 1)
			{
				sum = sum + M[t][i][j];
			}
		}
	}
	return(sum);
}


main()
{
	int t= 0; int ncases = 0;
	int V[MAXCASES] = {0}; int L[10][MAXCASES][MAXCASES]; int W[10][MAXCASES][MAXCASES];
	int edges[10][MAXCASES][MAXCASES];
	int sumL = 0; int sumW = 0; int d = 0;
	int i = 0; int j = 0;

	scanf("%d",&ncases);
	for(t=1; t<= ncases; t++)
	{
		scanf("%d",&V[t]);
		for(i=0; i<V[t]; i++)
		{
			for(j=0; j<V[t]; j++)
			{
				edges[t][i][j] = 0;
				scanf("%d",&edges[t][i][j]);
			}
		}
		for(i=0; i<V[t]; i++)
		{
			for(j=0; j<V[t]; j++)
			{
				L[t][i][j] = 0;
				scanf("%d",&L[t][i][j]);
			}
		}
		for(i=0; i<V[t]; i++)
		{
			for(j=0; j<V[t]; j++)
			{
				W[t][i][j] = 0;
				scanf("%d",&W[t][i][j]);
			}
		}
	}
	printf("\n");
	for(t=1; t<= ncases; t++)
	{
		sumL = FindSum(V[t], t, edges, L);
		sumW = FindSum(V[t], t, edges, W);
		d = gcd(sumL, sumW);
		if(d<=0) d = 1;
		printf("%d %d \n",sumL/d, sumW/d);
	}

	
	return 0;
}


