#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INFINITY        99999
#define MIN(a,b)        ((a < b) ? (a) : (b))

int dist[500][500];


void AllShortestPath(int n)
{
	int i,j,k;
	for(k=1; k<=n; k++)
	{
		for(i=1; i<=n; i++)
		{
			for(j=1; j<=n; j++)
			{
				if( (i!=j) && (dist[i][j] == 0)) dist[i][j] = INFINITY;
				dist[i][j] = MIN(dist[i][j],(dist[i][k]+dist[k][j]));
			}
		}
	}
}

int FindShortestPath(int n, int s, int d)
{
	int i,j,k;
	int value[500];
	int min = value[1];
	for(k=1; k<=n; k++)
	{
		value[k] = MIN(dist[s][d],(dist[s][k]+dist[k][d]));
		if(k==1) min = value[1];
		if(value[k] < min) min = value[k];
		
	}
	//value = dist[s][d];
	return min;
}


int main()
{
	int n=0;
	int i,j,w;
	int source,destination;

	printf("Enter the no. of edges: ");
	scanf("%d",&n);
	//memset(&dist,INFINITY,sizeof(dist));
	printf("Enter the weight for connected vertices:\n");
	for(i=1; i<=n; i++)
	for(j=1; j<=n; j++)
	{
	scanf("%d",&dist[i][j]);
	if(i==j) dist[i][j] = 0;
	if( (i!=j) && (dist[i][j] == 0)) dist[i][j] = INFINITY;
	}
	//AllShortestPath(n);
	printf("The shortestpath matrix is: \n");
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			printf("%d       ",dist[i][j]);
		}
		printf("\n");
	}
	printf("Enter source : ");
	scanf("%d",&source);
	printf("Enter destination : ");
	scanf("%d",&destination);
	w = FindShortestPath(n,source,destination);
	printf("Shortest Path between [%d] --> [%d] : %d\n",source,destination,w);
}

