#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define		MAXSIZE		50
#define		INFINITY	9999



void PrintMatrix(int n, int matrix[MAXSIZE][MAXSIZE])
{
	int i = 0; int j = 0;
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%8d",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void FindMinorOfColumn(int pos, int n, int matrix[MAXSIZE][MAXSIZE], int minor[][MAXSIZE], int *order)
{
	int i = 0; int j = 0; int k = 0; int p = 0; int q = 0; int flag = 0;
	int temp[MAXSIZE][MAXSIZE];

	/* Copy matrix into temp */
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			temp[i][j] = matrix[i][j];
	
	for(j=0; j<n; j++)
	{
		temp[0][j] = INFINITY;
		temp[j][pos] = INFINITY;
	}
	
	//printf("Temp Matrix:-\n");
	//PrintMatrix(n, temp);
	p = 0; q = 0;
	for(i=0; i<n; i++)
	{
		flag = 0; q = 0;
		for(j=0; j<n; j++)
		{
			if(temp[i][j] != INFINITY)
			{
				minor[p][q++] = temp[i][j];
				flag = 1;
			}
		}
		if(flag == 1) p++;
	}
	*order = p;
}

int determinant(int n, int matrix[MAXSIZE][MAXSIZE])
{
	int i = 0; int j = 0; int k = 0; int p = 0; int q = 0;
	int minorMatrix[MAXSIZE][MAXSIZE]; int d = 0;
	int morder = 0; int power = 0; int sum = 0;
	int factor[MAXSIZE];

	if(n==0) return 0;
	if(n==1) return(matrix[0][0]);

	if(n==2)
	{
		d = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];  //for 2x2 matrix = (a*d - b*c)
		return(d);
	}

	i=0;
	for(j=0; j<n; j++)
	{
		FindMinorOfColumn(j, n, matrix, minorMatrix, &morder);
		//printf("----------------------------\n");
		//PrintMatrix(morder, minorMatrix);
		//printf("----------------------------\n");
		if( (j%2) == 0) power = 1;
		else
		power = -1;
		factor[j] = (power)*(matrix[i][j])*determinant(morder, minorMatrix);
	}
	sum = 0;
	for(i=0; i<n; i++)
	{
		sum = sum + factor[i];
	}
	return(sum);
}


main()
{
	int n = 0; int det = 0;
	int matrix[MAXSIZE][MAXSIZE]; int **mat;
	int i = 0; int j = 0; int k = 0;

	printf("Enter the order:- \n");
	scanf("%d",&n);
	printf("Enter the matrix:-\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			scanf("%d",&matrix[i][j]);
		}
	}
	det = determinant(n, matrix);
	printf("Determinant of matrix = %d\n",det);
	/*
	printf("The copy matrix is:-\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%5d",mat[i][j]);
		}
		printf("\n");
	}
	*/
}

