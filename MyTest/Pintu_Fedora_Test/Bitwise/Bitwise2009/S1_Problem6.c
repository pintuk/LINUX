#include<stdio.h>
#include<stdlib.h>


#define MAXCASES	500


int gcd ( int a, int b )
{
	int c = 0;
	while ( a != 0 ) 
	{
		c = a; a = b%a;  b = c;
	}
	return b;
}


int FindSum(int n, int E[MAXCASES][MAXCASES], int M[MAXCASES][MAXCASES])
{
	int i = 0; int j = 0;
	int sum = 0;

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(E[i][j] == 1)
			{
				sum = sum + M[i][j];
			}
		}
	}
	return(sum);
}


main()
{
	int t= 0; int ncases = 0;
	int V[MAXCASES] = {0}; int L[MAXCASES][MAXCASES]; int W[MAXCASES][MAXCASES];
	int edges[MAXCASES][MAXCASES];
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
				edges[i][j] = 0;
				scanf("%d",&edges[i][j]);
			}
		}
		for(i=0; i<V[t]; i++)
		{
			for(j=0; j<V[t]; j++)
			{
				L[i][j] = 0;
				scanf("%d",&L[i][j]);
			}
		}
		for(i=0; i<V[t]; i++)
		{
			for(j=0; j<V[t]; j++)
			{
				W[i][j] = 0;
				scanf("%d",&W[i][j]);
			}
		}
		sumL = FindSum(V[t], edges, L);
		sumW = FindSum(V[t], edges, W);
		d = gcd(sumL, sumW);
		if(d<=0) d = 1;
		printf("%d %d \n",sumL/d, sumW/d);
	}

	
	return 0;
}


