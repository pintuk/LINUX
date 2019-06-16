#include<stdio.h>
#include<stdlib.h>


#define CASES	1000


int FindX(int t, int *k, int *M, int a[][CASES], int n[][CASES])	
{
		int y1 = 0; int y2 = 0; float Y = 0; int value = 0;
		int flag = 0;
		int i = 0; int x = 0;
		
		x = M[t]; y1 = 1;
		for(i=1; i<=k[t]-1; i++)
		{
			y1 = y1 * n[t][i];	
		}
		y2 = 1;
		for(i=k[t]-1+1; i<=k[t]; i++)
		{
			y2 = y2 * n[t][i];	
		}
		if(y2 != 0) 
		{
			Y = (float)(1/2.00) * ((float)y1 / (float)y2);
		}

		for(i=1; i<=k[t]; i++)
		{
		flag = 0;
		for(x=1; x<=M[t]; x++)
		{
			if((float)x < Y)
			{
				if( (x % n[t][i]) == a[t][i])
				{
					flag = 1; value = x;
				}
			}
		}
		}
		if(flag == 1)
		{
			//printf("%d\n",value);
			return(value);
		}
		else
		{
			//printf("-1\n");
			return(-1);
		}
}


main()
{
	int t = 0; int ncases = 0; 
	int k[CASES]; int M[CASES] = {0}; int error[CASES] = {0};
	int a[CASES][CASES]; int n[CASES][CASES];
	int X[CASES];
	
	int i = 0; int j = 0;

	scanf("%d",&ncases);
	for(t=1; t<= ncases; t++)
	{
		scanf("%d %d %d",&k[t],&error[t],&M[t]);
		for(i=1; i<= k[t]; i++)
		{
			scanf("%d %d",&a[t][i],&n[t][i]);
		}
		X[t] = FindX(t, k, M, a, n);
	}
	printf("\n OUTPUT \n");
	for(t=1; t<= ncases; t++)
	{
		printf("%d\n",X[t]);
	}
		
	return 0;
}



