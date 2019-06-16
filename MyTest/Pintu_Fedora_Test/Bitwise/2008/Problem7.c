#include<stdio.h>
#include<stdlib.h>


int FindvMin(int n, int *X, int m)
{
	int i = 0; int min = 0;

	min = X[1];
	for(i=1; i<=n; i++)
	{
		if( (X[i] > m) && (X[i] < min) )
		{
			min = X[i];
		}
	}
	return(min);
}

void InitializeZero(int n, int *C)
{
	int i = 0;

	for(i=1; i<=n; i++)
	{
		C[i] = 0;
	}
}


void CorrectOrder(int n, int *X, int *C, int *len)
{
	int i = 0; int j = 0; int k = 1;
	int min = -1; 

	InitializeZero(n+n, C);
	for(i=1; i<=n; i++)
	{
		min = FindvMin(n, X, min);
		for(j=1; j<=n; j++)
		{
			if(min == X[j])
			{
				C[k] = j;
				k++;
			}
		}
		if(k >n) break;
	}
	*len = k-1;
}

main()
{
	int i = 0; 
	int n = 0;
	int X[100]; int Order[100]; int L = 0;

	printf("Enter the number of pictures:-\n");
	scanf("%d",&n);
	printf("Enter the index of dinosaur(large to small):-\n");
	for(i=1; i<=n; i++)
	{
		scanf("%d", &X[i]);
	}
	CorrectOrder(n, X, Order, &L);
	printf("The order in which Bubba seen the dinosaurs are:-\n");
	for(i=1; i<=L; i++)
	{
		printf("%d  ",Order[i]);
	}
	printf("\n");
}

