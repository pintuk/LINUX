#include<stdio.h>
#include<stdlib.h>


int FindMax(int n, int *K)
{
	int i = 0;
	int max = 0;

	max = K[0];
	for(i=0; i<n; i++)
	{
		if(K[i] > max) max = K[i];
	}
	return(max);
}

void Initialize(int n, int *A)
{
	int i = 0;
	for(i=0; i<n; i++)
	{
		A[i] = 0;
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
	int n = 0;
	int W = 0;
	int S[100];
	int Weight[50] = {0}; int Value[100] = {0}; int K[100] = {0};
	int i = 0; int w = 0;
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
	Initialize(n, S);

	for(w=1; w<=W; w++)
	{
		for(i=0; i<n; i++)
		{
			if(Weight[i] <= w)
			{
				S[i] = K[w - Weight[i]] + Value[i];
				printf("S[%d] (K[%d] + %d) = %d\n",i,(w-Weight[i]),Value[i],S[i]);
			}
		}
		K[w] = FindMax(n, S);
		printf("---- K[%d] = %d ------\n\n",w,K[w]);
	}
	opval = FindMax(W+1, K);
	printf("\nThe optimal value obtained is = %d\n",opval);
}



