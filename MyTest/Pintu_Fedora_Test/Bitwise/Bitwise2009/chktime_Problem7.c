#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>


int BinSearch(float x, int k, float *a)
{
	int beg = 0; int end1 = 0; int mid = 0;
	
	beg = 1;
	end1 = k;
	if(k == 0) return(0);
	printf("k = %d\n",k); printf("x = %3.2f\n",x);
	do
	{
		mid = (beg + end1) / 2;
		if(x < a[mid])
		{
			end1 = mid - 1;
		}
		else if(x > a[mid])
		{
			beg = mid + 1;
		}
		else
		{
			break;
		}
		mid = (beg + end1) / 2;
	}while (a[mid] != x);
	if(a[mid] == x) return(1);
	
	return(0);
}


float FindSlope(float y2, float y1, float x2, float x1)
{
	float slope = 0.00;

	slope = (float)(y2 - y1)/(float)(x2 - x1);

	return(slope);
}


int CheckRepeat(float s, int k, float *slope)
{
	int i = 0;

	for(i=0; i<k; i++)
	{
		if(s == slope[i])
		{
			return 1;
		}
	}
	return 0;
}

main()
{
	int t = 0; int ncases = 0; int n[1000] = {0};
	int count_1stClass = 0;
	float a = 0.00; int a_N[1000] = {0}; int a_D[1000] = {0};
	float Y = 0.00; float s = 0.00;
	int i = 0; int j = 0; int k = 0;
	float actual_slope = 0.00; float slope[1000] = {0.00};

	struct timeval starttime, endtime;

	scanf("%d",&ncases);
	for(t=1; t<= ncases; t++)
	{
		scanf("%d %d %d",&a_N[t],&a_D[t],&n[t]);
	}
	printf("\n");
	printf("OUTPUT -\n");
	gettimeofday(&starttime, NULL);
	for(t=1; t<= ncases; t++)
	{
		gettimeofday(&starttime, NULL);
		printf("start time - %d (microsec)\n",starttime.tv_usec);
		a = (float)a_N[t]/(float)a_D[t];
		Y = (float)a * n[t];

		//actual_slope = FindSlope(Y, 0, n[t], 0);
		actual_slope = (float) Y / (float)n[t];

		count_1stClass = (int)actual_slope;
		//count_1stClass = 0; k = 0;
		for(i=1; i<=Y; i++)
		{
			for(j=1; j<=n[t]-1; j++)
			{
				//s = FindSlope(i, 0, j, 0);
				s = (float) i / (float)j;
				if( (CheckRepeat(s, k, slope) != 1) && (actual_slope >= s) )
				{
					count_1stClass++; slope[k++] = s;
				}
			}
		}
		printf("%d\n",count_1stClass);
		gettimeofday(&endtime, NULL);
		printf("End time - %d (microsec)\n",endtime.tv_usec);
		printf("TIME TAKEN = %d\n",(endtime.tv_usec - starttime.tv_usec));
	}
	
}


