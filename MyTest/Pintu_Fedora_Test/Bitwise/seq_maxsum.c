#include<stdio.h>
#include<stdlib.h>



main()
{
	int a[100]; int n = 0; int x = 0; int sumj = 0; int store[100];
	int i = 0; int j = 0; int k = 0; int max = 0; int l = 0;

	printf("Enter the length:-\n");
	scanf("%d",&n);
	printf("Enter the sequence:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d",&a[i]);
	}
	for(k=0; k<n; k++)
	{
	for(i=k+1; i<n; i++)
	{
		sumj = 0; 
		//printf("----------------------------------\n");
		for(j=k; j<=i; j++)
		{
			//printf("%d  +  %d  =  %d\n",sumj,a[j],(sumj+a[j]));
			sumj = sumj + a[j];
			if(sumj > max) 
			{
				max = sumj; x = 0;
				for(l=k; l<=i; l++)
				{
					store[x++] = a[l];
				}
			}
			
		}
		//printf("----------------------------------\n");
		//printf("Max = %d\n",max);
	}
	}
	printf("\nMax = %d\n",max);
	printf("And Sequence is :-\n");
	for(i=0; i<x; i++)
	{
		printf("%5d",store[i]);
	}
	printf("\n");
}



