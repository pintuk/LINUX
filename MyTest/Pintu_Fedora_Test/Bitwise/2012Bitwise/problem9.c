#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define INFINITY	9999
#define MIN(a,b)	((a < b) ? (a) : (b))

int dist[5000][5000];


int ShortestPath(int n, int s, int d)
{
	int i,j,k;
	int value=0;
	
	for(k=1; k<=n; k++)
	{
		if( (s!=d) && (dist[s][d]==0)) dist[s][d] = INFINITY;
		value = MIN(dist[s][d],(dist[s][k]+dist[k][d]));
	}
	return(value);
}

void AllShortestPath(int n)
{
	int i,j,k;
	for(k=1; k<=n; k++)
	{
		for(i=1; i<=n; i++)
		{
			for(j=1; j<=n; j++)
			{
				if( (i!=j) && (dist[i][j]==0)) dist[i][j] = INFINITY;
				dist[i][j] = MIN(dist[i][j],(dist[i][k]+dist[k][j]));
			}
		}
	}
}

void PrintShortestPath(int n)
{
	int i,j,k;
	int s=0;

	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			s = ShortestPath(n,i,j);
			printf("%d   ",s);
		}
		printf("\n");
	}
}

int main()
{
	int i,j,k,m,n;
	int C,P,S,H;
	int u[60000],v[60000],t[60000],f[20000],w[20000];
	int totaltime=0;
	int totalweight=0;
	int value=0;
	int commonedge=0;

	memset(&dist,0,sizeof(dist));
	scanf("%d %d %d",&C,&P,&S);
	for(i=1; i<=P; i++)
	{
		scanf("%d %d %d",&u[i],&v[i],&t[i]);
		m=u[i]; n=v[i]; 
		dist[m][n] = t[i];
		dist[n][m] = t[i];
	}
	scanf("%d",&H);
	for(i=1; i<=H; i++)
	{
		scanf("%d %d",&f[i],&w[i]);
		totalweight += w[i];
	}
	//AllShortestPath(C);
	//PrintShortestPath(C);

#if 0
	for(i=1; i<=H; i++)
	{
		int x=f[i];
		int k=0;
		commonedge=0;
		for(j=1; j<=x; j++)
		{
			if( (dist[x][j] != 0) || (dist[x][j] != INFINITY))
			{
				commonedge = j;
				printf("common : %d\n",commonedge);
				//break;
			}
		}
	}
	printf("Common Edge : %d\n",commonedge);
#endif
	for(i=1; i<=H; i++)
	{
		//value = ShortestPath(C,commonedge,f[i]);
		value = ShortestPath(C,f[i],S);
		totaltime += value*w[i];
	}
	//value = ShortestPath(C,commonedge,S);
	//totaltime += value*totalweight;

	printf("%d\n",totaltime);

	return 0;
}

