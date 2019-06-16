#include<stdio.h>
#include<stdlib.h>


long int power(int x, long int y)
{
	int i = 0; long int p = 1;
	for(i=1; i<=y; i++)
	{
		p = p*x;
	}
	return(p);
}

main()
{
	int n = 0;
	int i = 0; int k = 1; int num = 0;
	int *prime;
	int flag = 1;

	printf("Enter the total numbers:-\n");
	scanf("%d",&n);
	prime = (int *)malloc(sizeof(int)*n);
	if(n <= 1)
	{
		prime[k++] = 2; 
	}
	else
	{
		for(i=2; i<=n; i++)
		{
			num = 2; flag = 1;
			while(num < i)
			{
				if( i%num == 0 )
				{
					flag = 0; break;
				}
				num++;
			}
			if(flag == 1) prime[k++] = i;
		}
	}
	/*
	for(i=1; i<=k-1; i++)
	{
		printf("%d  ",prime[i]);
	}
	*/
	printf("\n");
	for(i=1; i<=k-1; i++)
	{
		long int e = 1;
		while(1)
		{
			if( (power(i, e) % (long int)prime[i]) == 1)
			{
				printf("prime - %d --> %d^%ld  = %ld\n",prime[i],i,e,power(i,e));
				break;
			}
			e++;
			if(e > 10000) break;
		}
	}
}




