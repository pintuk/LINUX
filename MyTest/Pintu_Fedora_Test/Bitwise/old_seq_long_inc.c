#include<stdio.h>
#include<stdlib.h>



main()
{
	int a[100]; int n = 0; int x = 0; int sumj = 0; int store[100];
	int i = 0; int j = 0; int k = 0; int max = 0; int l = 0; int len = 0;

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
		sumj = 0; max = a[k]; x=0;
		printf("----------------------------------\n");
		for(j=k; j<=i; j++)
		{
			if(a[j] > max) 
			{
				max = a[j]; 
				//store[x] = a[j]; 
				x++;
				printf("%5d",a[j]);
			}
			
		}
		printf("\n");
		if(x > len)
		{
			len = x;
		}
		printf("----------------------------------\n");
		//printf("Max = %d\n",max);
	}
	}
	printf("\nMax Length = %d\n",len);
	printf("And Sequence is :-\n");
	for(i=0; i<x; i++)
	{
		//printf("%5d",store[i]);
	}
	printf("\n");
}



