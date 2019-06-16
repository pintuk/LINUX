#include<stdio.h>
#include<stdlib.h>


int FindMax(int n, int *K)
{
	int i = 0;
	int max = K[0];

	for(i=0; i<n; i++)
	{
		if(K[i] > max) max = K[i];
	}
	return(max);
}


void Initialize(int n, int ship[][500])
{
	int i = 0; int j = 0;

	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			ship[i][j] = 0;
}


main()
{
	int nship = 0; int npirate = 0;
	int ship[500][500];
	int sx[500]; int sy[500];
	int px[500]; int py[500];
	int pr[500];
	int i = 0; int j = 0; int k = 0; int p = 0; int maxship = 0;
	int K[100];

	printf("Enter the number of ships:-\n");
	scanf("%d",&nship);
	printf("Enter the ship location:-\n");
	for(i=0; i<nship; i++)
	{
		scanf("%d %d",&sx[i],&sy[i]);
	}
	printf("Enter the number of pirates:-\n");
	scanf("%d",&npirate);
	printf("Enter the pirates location <whitespace> range :-\n");
	for(i=0; i<npirate; i++)
	{
		scanf("%d %d %d",&px[i],&py[i],&pr[i]);
	}

	Initialize(500, ship);
	
	for(i=0; i<npirate; i++)
	{
		p=0;
		Initialize(500, ship);
		for(j=0; j < nship; j++)
		{
			for(k=0; k < pr[i]; k++)
			{
				if( ((px[i] + k) == sx[j]) && ((py[i] + k) == sy[j]) ) 
				{
					if(ship[sx[j]][sy[j]] != 1)
					{
						ship[sx[j]][sy[j]] = 1;
						p++;
					}
				}
				if( ((px[i] + k) == sx[j]) && (py[i] == sy[j]) ) 
				{
					if(ship[sx[j]][sy[j]] != 1)
					{
						ship[sx[j]][sy[j]] = 1;
						p++;
					}
				}
				if( (px[i] == sx[j]) && ( (py[i] + k) == sy[j]) ) 
				{
					if(ship[sx[j]][sy[j]] != 1)
					{
						ship[sx[j]][sy[j]] = 1;
						p++;
					}
				}
			}
			for(k=pr[i]-1; k>=0; k--)
			{	
				if( ((px[i] - k) == sx[j]) && ((py[i] - k) == sy[j]) ) 
				{
					if(ship[sx[j]][sy[j]] != 1)
					{
						ship[sx[j]][sy[j]] = 1;
						p++;
					}
				}
				if( ((px[i] - k) == sx[j]) && (py[i] == sy[j]) ) 
				{
					if(ship[sx[j]][sy[j]] != 1)
					{
						ship[sx[j]][sy[j]] = 1;
						p++;
					}
				}
				if( (px[i] == sx[j]) && ( (py[i] - k) == sy[j]) ) 
				{
					if(ship[sx[j]][sy[j]] != 1)
					{
						ship[sx[j]][sy[j]] = 1;
						p++;
					}
				}
			}
		}
		K[i] = p;
		printf("K[%d] = %d\n",i,K[i]);
	}
	maxship = FindMax(npirate, K);
	printf("Maximum number of ships = %d\n",maxship);
}

