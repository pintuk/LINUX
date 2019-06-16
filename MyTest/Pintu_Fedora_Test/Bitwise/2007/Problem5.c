#include<stdio.h>
#include<stdlib.h>


long int power(int x, long int y)
{
	long int i = 0; long int p = 1;

	for(i=1; i<=y; i++)
	{
		p = p*x;
	}
	return(p);
}

main()
{
	int n = 0;
	int prime[100]; int setA[100]; long int Order[100];
	int i = 0; int j = 0; int k = 0; long int e = 1; long int sum = 0;

	printf("Enter one prime number:-\n");
	scanf("%d", &n);

	for(k=1; k<=n-1; k++)
	{
		setA[k] = k;
		printf("%d  ",setA[k]);
		e = 1;
		while(e >= 1)
		{
			if( (power(k, e) % (long int)n) == 1)
			{
				Order[k] = e;
				break;
			}
			e++;
			if(e >= 100000) break;
		}
		
	}
	printf("\nOrders of set A is:-\n");
	for(i=1; i<=n-1; i++)
	{
		printf("%ld  ",Order[i]);
		sum = sum + Order[i];
	}
	printf("\n");
	printf("Sum of orders = %ld\n",sum);
}

