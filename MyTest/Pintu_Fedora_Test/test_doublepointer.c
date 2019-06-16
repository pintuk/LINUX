#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void PrintTable(int **A, int row, int col)
{
        int i,j;

        for(i=0; i<row; i++) {
                for(j=0; j<col; j++) {
			A[i][j] = i+j+1;
                        printf("%d   ",A[i][j]);
                }
                printf("\n");
        }
        printf("\n");
        printf("----------------------------\n");
}


int main()
{
	int i,j;
	int row,col;
	int **A = NULL;

	printf("Enter the no. of rows: ");
	scanf("%d",&row);
	printf("Enter the no. of columns: ");
	scanf("%d",&col);
	
	A = (int **)malloc(sizeof(int *)*row);
	for(i=0; i<row; i++) {
		A[i] = (int *)malloc(sizeof(int)*col);
	}
	PrintTable(A,row,col);
	for(i=0; i<row; i++) {
		free(A[i]);
	}
	free(A);
	return 0;
}

