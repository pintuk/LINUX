#include<stdio.h>
#include<stdlib.h>


#define		max(a,b)	((a) > (b)) ? (a) : (b)
#define		min(a,b)	((a) < (b)) ? (a) : (b)
#define		INFINITY	99999											 


int FindMax(int n, int *K)
{
	int i = 0;
	int max = 0;

	max = K[0];
	for(i=1; i<=n; i++)
	{
		if(K[i] > max) max = K[i];
	}
	return(max);
}

void Initialize(int n, int W, int K[][100])
{
	int i = 0; int j = 0;
	for(j=1; j<=n; j++)
	{
		K[0][j] = INFINITY;
	}
	for(j=1; j<=W; j++)
	{
		K[j][0] = INFINITY;
		K[j][-1] = INFINITY;
	}
	
}

void PrintList(int n, int W, int K[][100])
{
	int i = 0; int j = 0;

	for(i=1; i<=W; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%10d",K[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


int power(int x, int v)
{
	int i = 0; int p = 1;

	for(i=0; i<v; i++)
	{
		p = p*x;
	}
	return(p);
}

main()
{
	int n = 0;
	int W = 0;
	int S[100];
	int Weight[50] = {0}; int Value[100] = {0}; int K[100][100]; int dist[100];
	int i = 0; int j = 0; int w = 0;
	int opval = 0;
	
	printf("Enter the number of tyres:-\n");
	scanf("%d",&n);
	printf("Enter the value of i <whitespace> cost of each items:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d %d",&Weight[i],&Value[i]);
		dist[i] = power(2, Weight[i]);
	}
	printf("Enter the Total Distance:-\n");
	scanf("%d",&W);
	Initialize(n, W, K);
	K[0][0] = 0;
	K[0][-1] = 0;
	K[1][-1] = INFINITY;

	for(j=0; j<n; j++)
	{
		for(w=1; w<=W; w++)
		{
			if(dist[j] > w)
			{
				K[w][j] = K[w][j-1];
			}
			else
			{
				printf("K[w][j-1] -> %d\n",K[w][j-1]);
				printf("w-dist[j] = %d\n",w-dist[j]);
				printf("Cost[j] = %d\n",Value[j]);
				K[w][j] = min(K[w][j-1], (K[w-dist[j]][j-1] + Value[j]) );
			}
			printf("---- min K[%d][%d] = %d ------\n\n",w,j,K[w][j]);
		}
		//K[w] = FindMax(n, S);
		PrintList(n, W, K);
		printf("-------------------------\n");
	}
	opval = K[W][n-1];
	printf("\nThe optimal value obtained is = %d\n",opval);
}



