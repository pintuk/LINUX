#include<stdio.h>
#include<stdlib.h>


/* Longest Increasing Circular Sequence */

int LICS(int n, int *S, int *L, int *ID)
{
	int store[100] = {0}; int indices[100];
	int i = 0; int j = 0; int k = 0; int p = 0;
	int pos = 0;
	int small = 0; int start = 0; int len = 0;
	int *ptr = NULL;

	for(pos=0; pos<n; pos++)
	{
		start = S[pos];
		store[0] = start;
		indices[0] = pos;
		for(i=pos; i<n; i++)
		{
			k=1; small = start;
			for(j=i+1; j<n; j++)
			{
				if(S[j] > small)
				{
					small = S[j];
					store[k] = S[j];
					indices[k] = j;
					k++;
				}
			}
			/*
			if(k > len)
			{
				len = k;
				for(p=0; p<len; p++)
				{
					L[p] = 0;
					L[p] = store[p];
				}
			}
			*/
			for(j=0; j<pos; j++)
			{
				if(S[j] > small)
				{
					small = S[j];
					store[k] = S[j];
					indices[k] = j;
					k++;
				}
			}
			if(k > len)
			{
				len = k;
				for(p=0; p<len; p++)
				{
					L[p] = 0;
					L[p] = store[p];
					ID[p] = indices[p];
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
	int S[100]; int L[100]; int indices[100];
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
	len = LICS(n, S, L, indices);
	for(i=0; i<len; i++)
	{
		printf("indices(%d)->%d  ",indices[i],L[i]);
	}
	printf("\n");
	printf("\nLength = %d\n",len);
}
