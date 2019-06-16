#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


#define	MAXSIZE		100
#define INFINITY	9999



void Initialize(int n, int *K)
{
	int i = 0;

	for(i=0; i<n; i++)
	{
		K[i] = INFINITY;
	}
}

int FindMin(int n, int *S)
{
	int i = 0;
	int min = 0;

	min = S[0];
	for(i=0; i<n; i++)
	{
		if(S[i] < min) min = S[i];
	}
	return(min);
}

main()
{
	char c = 0; char input[MAXSIZE] = {0}; 
	int Sum = 0; int n=0; int s = 0; int num_of_d = 0;
	int d[30]; int a[MAXSIZE]; int b[100]; int product[MAXSIZE];
	int S[100]; int K[100];
	int i = 0; int j = 0; int k = 0;

	printf("Enter the sum amount:-\n");
	scanf("%d",&Sum);
	printf("Enter the number of available denominations: \n");
	i=0;
	getchar();
	c = getchar();
	while( c != '\n')
	{
		char ch = 0;
		
		k=0;
		while(isdigit(c))
		{
			input[k++] = c;
			c = getchar();
		}
		if(k!=0)
		{
			input[k] = '\0';
			d[i++] = atoi(input);
			ungetc(c,stdin);
		}
		c = getchar();
	}
	num_of_d = i;
	printf("-----------\n");
	for(i=0; i<num_of_d; i++)
	{
		printf("d[%d] = %d\n",i,d[i]);
	}
	k=0;
	printf("Enter the value of d <whitespace> num of coins for all d:-\n");
	for(i=0; i<num_of_d; i++)
	{
		for(j=0; j<d[i]; j++)
		{
			scanf("%d %d",&a[k],&b[k]);
			product[k] = a[k]*b[k];
			k++;
		}
	}
	n = k;
	printf("Value of n = %d\n",n);
	printf("Denominations are:-\n");
	k=0;
	for(i=0; i<n; i++)
	{
		printf("%d \t %d \t %d\n\n",a[i],b[i],product[i]);
	}
	Initialize(n, K); Initialize(n, S);

	K[0] = 0;
	for(s=1; s<=Sum; s++)
	{
		for(i=0; i<n; i++)
		{
			if(product[i] <= s)
			{
				S[i] = K[s - product[i]] + b[i];
				//printf("K[%d] -> (K(%d) + %d) = %d\n",i,(s-product[i]),b[i],S[i]);
			}
		}
		K[s] = FindMin(n, S);
		//printf("--- min K[%d] = %d ----\n\n",s,K[s]);
		//getchar();
	}
	printf("Minimum Number of coins required = %d\n",K[Sum]);
}





