#include<stdio.h>
#include<stdlib.h>


int LIS(int n, int *S, int *L)
{
	int store[100] = {0};
	int i = 0; int j = 0; int k = 0; int p = 0;
	int pos = 0;
	int small = 0; int start = 0; int len = 0;
	int *ptr = NULL;

	for(pos=0; pos<n; pos++)
	{
		start = S[pos];
		store[0] = start;
		for(i=pos; i<n; i++)
		{
			k=1; small = start;
			for(j=i+1; j<n; j++)
			{
				if(S[j] > small)
				{
					small = S[j];
					store[k++] = S[j];
				}
			}
			if(k > len)
			{
				len = k;
				for(p=0; p<len; p++)
				{
					L[p] = 0;
					L[p] = store[p];
				}
			}
		}
	}
	//L = ptr;
	return(len);
}


main()
{
	int n = 0;
	int S[100]; int L[100];
	int i = 0; 
	int len = 0;

	printf("Enter the length of the sequence:-\n");
	scanf("%d",&n);
	printf("Enter the sequence:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d",&S[i]);
	}
	printf("The longest increasing Sequence is:-\n");
	len = LIS(n, S, L);
	for(i=0; i<len; i++)
	{
		printf("%d  ",L[i]);
	}
	printf("\nLength = %d\n",len);
}
