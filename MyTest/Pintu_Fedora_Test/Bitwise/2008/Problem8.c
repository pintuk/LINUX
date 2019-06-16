#include<stdio.h>
#include<stdlib.h>



void InitializeZero(int n, int M[][1024])
{
	int i = 0; int j = 0;

	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			M[i][j] = 0;
}

main()
{
	int n = 0;
	int x[1024]; int y[1024]; int point[1024];
	int M[1024][1024];
	int i = 0; int j = 0; int k = 0; int num_of_one = 0;

	printf("Enter the number of points:-\n");
	scanf("%d",&n);
	printf("Enter the co-ordinates:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d %d",&x[i],&y[i]);
	}
	InitializeZero(n, M);
	
	for(i=0; i<20; i++)
	{
		M[x[i]][y[i]] = 1;
	}
	printf("------------------------\n");
	for(i=0; i<20; i++)
	{
		for(j=0; j<20; j++)
		{
			printf("%5d",M[i][j]);
		}
		printf("\n");
	}
	printf("------------------------\n");
	printf("Co-ordinates for the straight line is:-\n");
	printf("checking in each rows....\n");
	for(i=0; i<20; i++)
	{
		k = 0; num_of_one = 0;
		for(j=0; j<20; j++)
		{
			if(M[i][j] == 1)
			{
				num_of_one++; 
				point[k++] = i;
				point[k++] = j;
			}
		}
		if(num_of_one == 2)
		{
			for(j=0; j<k; j++)
			{
				printf("%d ",point[j]);
			}
			printf("\n");
			//break; 
			exit(0);
		}
	}
	printf("checking in each columns...\n");
	for(i=0; i<20; i++)
	{
		k = 0; num_of_one = 0;
		for(j=0; j<20; j++)
		{
			if(M[j][i] == 1)
			{
				num_of_one++; 
				point[k++] = j;
				point[k++] = i;
			}
		}
		if(num_of_one == 2)
		{
			for(j=0; j<k; j++)
			{
				printf("%d ",point[j]);
			}
			printf("\n");
			//break;
			exit(0);
		}
	}
	if(num_of_one != 2)
	{
		printf("-1 -1 -1 -1\n");
	}
	printf("\n");
}

