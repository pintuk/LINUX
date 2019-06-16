#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int FindMax(int N, int *A)
{
	int i = 0;
	int max = 0;

	max = A[0];
	for(i=1; i<N; i++)
	{
		if(A[i] > max) max = A[i];
	}
	return(max);
}

main()
{
	int ncases = 0;
	int i = 0;
	int *Max = NULL;

	printf("No. of test cases: ");
	scanf("%d",&ncases);
	Max = malloc(sizeof(int)*ncases);
	memset(Max,0,sizeof(int)*ncases);
	for(i=0; i<ncases; i++)
	{
		int *A = NULL;
		int N = 0;
		int j = 0;

		//printf("Enter size of array : ");
		scanf("%d",&N);
		A = malloc(sizeof(int)*N);
		memset(A,0,sizeof(int)*N);
		for(j=0; j<N; j++)
		{
			scanf("%d",&A[j]);
		}
		Max[i] = FindMax(N, A);
		free(A);
	}
	printf("output:-\n");
	for(i=0; i<ncases; i++)
	{
		printf("%d\n",Max[i]);
	}
	free(Max);
}




