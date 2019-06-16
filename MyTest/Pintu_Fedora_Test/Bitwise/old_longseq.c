#include<stdio.h>
#include<stdlib.h>


main()
{
	int n = 0;
	int store[100];
	int S[50]; int L[50]; int Length[1000]; int max = 0;
	int i = 0; int j = 0; int k = 0; int p = 0; int l = 0; int m = 0;

	printf("Enter the length of the sequence:-\n");
	scanf("%d",&n);
	printf("Enter the sequence:-\n");
	for(i=0; i<n; i++)
	{
		scanf("%d",&S[i]);
	}
	printf("----------------- Sequence ---------------------\n");
	l = 0; max = 0;
	for(j=0; j<n;)
	{
		for(i=j+1; i<n; i++)
		{
			m = i;
			while(S[m] > S[j])
			{
				L[0] = S[j]; p = 0;
				for(k=m; k<n; k++)
				{
					if(S[k] > L[p])
					{
						p = p+1;
						L[p] = S[k];
						//printf("L[p] = %d\n",L[p]);
					}
				}
				Length[l] = 1+p;
				for(k=0; k<Length[l]; k++)
				{
					printf("%d  ",L[k]);
				}
				if(Length[l] > max)
				{
					max = Length[l];
					for(k=0; k<Length[l]; k++)
					{
						store[k] = L[k];
					}
				}
				printf("\n");
				m++; l++;
				if(m >= n)
				{
					break;
				}
			}
		}
		printf("-----------------------------------------------\n");
		printf("Length of the Longest Sequence is = %d\n",max);
		printf("Longest sequence is:-\n");
		for(k=0; k<max; k++)
		{
			printf("%5d",store[k]);
		}
		printf("\n");
	}
}
