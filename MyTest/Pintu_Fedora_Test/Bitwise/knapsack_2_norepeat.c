#include<stdio.h>
#include<stdlib.h>


#define		max(a,b)	((a) > (b)) ? (a) : (b)


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
	for(j=-1; j<=n; j++)
	{
		K[0][j] = 0;
	}
	for(j=-1; j<=W; j++)
	{
		K[j][0] = 0;
	}
	
}

void PrintList(int n, int W, int K[][100])
{
	int i = 0; int j = 0;

	for(i=1; i<=W; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%5d",K[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

main()
{
	int n = 0;
	int W = 0;
	int S[100];
	int Weight[50] = {0}; int Value[100] = {0}; int K[100][100];
	int i = 0; int j = 0; int w = 0;
	int opval = 0;
	
	printf("Enter the number of items:-\n");
	scanf("%d",&n);
	printf("Enter the Weight <whitespace> Value of each items:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d %d",&Weight[i],&Value[i]);
	}
	printf("Enter the Total Weight to pick:-\n");
	scanf("%d",&W);
	Initialize(n, W, K);

	for(j=0; j<n; j++)
	{
		for(w=1; w<=W; w++)
		{
			if(Weight[j] > w)
			{
				K[w][j] = K[w][j-1];
				//printf("S[%d] (K[%d] + %d) = %d\n",i,(w-Weight[i]),Value[i],S[i]);
			}
			else
			{
				K[w][j] = max(K[w][j-1], (K[w-Weight[j]][j-1] + Value[j]) );
			}
			//printf("---- K[%d][%d] = %d ------\n\n",j,w,K[j][w]);
		}
		//K[w] = FindMax(n, S);
		PrintList(n, W, K);
		printf("-------------------------\n");
	}
	opval = K[W][n-1];
	printf("\nThe optimal value obtained is = %d\n",opval);
}



