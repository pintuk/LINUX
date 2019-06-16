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


void FindMinor(int row, int col, int n, int matrix[MAXSIZE][MAXSIZE], int minor[][MAXSIZE], int *order)
{
	int i = 0; int j = 0; int k = 0; int p = 0; int q = 0; int flag = 0;
	int temp[MAXSIZE][MAXSIZE];

	/* Copy matrix into temp */
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			temp[i][j] = matrix[i][j];

	for(j=0; j<n; j++)
	{
		temp[row][j] = INFINITY;
		temp[j][col] = INFINITY;
	}
	
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
		FindMinor(i,j, n, matrix, minorMatrix, &morder);
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

void FindAdjoint(int n, int matrix[][MAXSIZE])
{
	int i = 0; int j = 0;
	int adjoint[MAXSIZE][MAXSIZE];

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			adjoint[j][i] = matrix[i][j];
		}
	}
	/* Copy adjoint into original */
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			matrix[i][j] = adjoint[i][j];
		}
	}
}

void FindInverse(int n, int matrix[MAXSIZE][MAXSIZE], int det, float inverseMatrix[][MAXSIZE])
{
	int minor[MAXSIZE][MAXSIZE]; int order_of_minor = 0;
	int i = 0; int j = 0; int power = 0;
	int cofactor[MAXSIZE][MAXSIZE];
	int adjoint[MAXSIZE][MAXSIZE];

	printf("******* Finding Inverse *********\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			FindMinor(i,j, n, matrix, minor, &order_of_minor);
			if( ((i+j)%2) == 0) power = 1;
			else
			power = -1;
			/* Find the co-factors of each elements of the matrix */
			cofactor[i][j] = (power)*determinant(order_of_minor, minor);
			//adjoint[j][i] = cofactor[i][j];
		}
	}
	/* Find the Adjoint - Transpose of co-factor matrix = Adjoint */
	FindAdjoint(n, cofactor);

	printf("The adjoint of matrix is:-\n");
	PrintMatrix(n, cofactor);

	/* Now find the inverse using the Adjoint matrix */
	/* each element of inverse = ( 1/determinant ) X Adjoint[i][j] */
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			inverseMatrix[i][j] = (float)(1.00/(float)det)*(cofactor[i][j]);  
		}
	}
}

void MultiplyMatrix(int n, float matrix[MAXSIZE][MAXSIZE], float constant[MAXSIZE][1], float sol[][1])
{
	int i = 0; int j = 0; int k = 0; float sum = 0;

	for(i=0; i<n; i++)
	{
		sum = 0.00;
		for(j=0; j<n; j++)
		{
			sum = (float)sum + (float)matrix[i][j]*constant[j][0];
		}
		sol[i][0] = sum;
	}
}

main()
{
	int n = 0; int det = 0;
	int matrix[MAXSIZE][MAXSIZE]; float inverseMatrix[MAXSIZE][MAXSIZE];
	float C[MAXSIZE][1]; float solution[MAXSIZE][1];
	int i = 0; int j = 0;

	printf("Enter the order:- \n");
	scanf("%d",&n);
	printf("Enter the co-efficient(x,y,z) and constant [1 per line]:-\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			scanf("%d",&matrix[i][j]);
		}
		scanf("%f",&C[i][0]);
	}
	printf("---------------------\n");
	printf("The constant matrix is:-\n");
	for(i=0; i<n; i++)
		printf("%8.2f\n",C[i][0]);
	printf("---------------------\n");
	det = determinant(n, matrix);
	printf("Determinant of matrix = %d\n",det);

	if(det == 0)
	{
		printf("Determinant is 0 - No INVERSE exists!!!!\n");
		printf("NO - Solution !!!!\n");
		exit(0);
	}

	FindInverse(n, matrix, det, inverseMatrix);
	
	printf("The inverse of the matrix is:-\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%10.2f",inverseMatrix[i][j]);
		}
		printf("\n");
	}

	MultiplyMatrix(n, inverseMatrix, C, solution);

	printf("The solution matrix is:-\n");
	for(i=0; i<n; i++)
	{
		printf("%8.2f\n",solution[i][0]);
	}
	
}

