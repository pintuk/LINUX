#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define INFINITY	9999   //pow(2, 15)   
#define	MAX			50

#define min(a,b)	( ( (a) < (b) )? (a) : (b) )
#define max(a,b)	( ( (a) > (b) )? (a) : (b) )


											
void PrintPath(int dist[MAX][MAX], int s, int d)
{
	int k = 0; int len = 0; int p = 0; int Path[MAX];

	Path[len] = d;
	k = dist[s][d];
	while(k != 0)
	{
		Path[++len] = k;
		k = dist[s][k];
	}
	Path[++len] = s;
	for(k=len; k>=0; k--)
		printf("%d->",Path[k]);

	/************* This is for recursion *************
	if(dist[s][d] == 0) return;

	if(dist[s][d] != 0)
	{
		PrintPath(dist, s, dist[s][d]);
		printf("%d->",dist[s][d]);
		PrintPath(dist, dist[s][d], d);
		return;
	}
	else
	return;
	*****************************************************/
	printf("\n");
}
										

void display(int n, int path[MAX][MAX])
{
	int i = 0; int j = 0;
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%d \t",path[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int PlaceFound(int n, int p, int places[MAX])
{
	int i = 0;
	for(i=0; i<n; i++)
	{
		if(places[i] == p) return i;
	}
	return -1;
}

int FindMax(int n, int graph[MAX][MAX])
{
	int i = 0; int j = 0;
	int maxvalue = 0; int nodevalue = 0;
	
	for(i=0; i<n; i++)
	{
		maxvalue = graph[i][0];
		if(maxvalue == INFINITY) maxvalue = 0;
		for(j=1; j<n; j++)
		{
			if(graph[i][j] == INFINITY) nodevalue = 0;
			else
			nodevalue = graph[i][j];
			maxvalue = max(maxvalue, nodevalue);
		}
	}
	return(maxvalue);
}
										
main()
{
	int n = 0; int maxvalue = 0; 
	int Source[MAX]; int Destination[MAX]; int TravelTime[MAX];
	int graph[MAX][MAX]; int dist[MAX][MAX];
	int start = 0; int end = 0; int sum = 0;
	int i = 0; int j = 0; int k = 0;
	int found_flag = 0; int notfound_flag = 0;
	int flag = 0; int found = 0;

	memset(graph,0,sizeof(graph));
	memset(dist,0,sizeof(dist));
	
	printf("Enter the number of nodes: -\n");
	scanf("%d",&n);
	printf("Enter the Source <whitespace> Destination <whitespace> TravelTime :\n");
	/* Get number of connected paths */
	for(i=0; i < n-1; i++)
	{
		scanf("%d %d %d",&Source[i],&Destination[i],&TravelTime[i]);
	}
	/* Initialize the graph with INFINITY */
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			graph[i][j] = INFINITY;
		}
	}

	/* Store the Source & Destination Time in Graph */
	/* This is for directed graph */
	/* Hence Source->Destination & Destination->Source is same */
	for(i=0; i<n-1; i++)
	{
		int x = 0; int y = 0;
		//x = PlaceFound(n, Source[i], places);
		//y = PlaceFound(n, Destination[i], places);
		graph[Source[i]][Destination[i]] = TravelTime[i];
		graph[Destination[i]][Source[i]] = TravelTime[i];
			//graph[x][y] = TravelTime[i];  //Source-to-Destination = Destination-to-Source
	}

	printf("Enter the Staring Point: \n");
	scanf("%d",&start);
	/*
	if( PlaceFound(n,start,places) == -1 )
	{
		printf("ERROR :: Place <%d> NOT FOUND in List Of Places...!!!\n",start);
		exit(-1);
	}
	*/
	printf("Enter the Ending Point: \n");
	scanf("%d",&end);
	/*
	if( PlaceFound(n,start,places) == -1 )
	{
		printf("ERROR :: Place <%d> NOT FOUND in List Of Places...!!!\n",end);
		exit(-1);
	}
	*/
	printf("The shortest path between (%d) to (%d) is:-\n",start, end);
	for(k=0; k<n; k++)
	{
		for(i=0; i<n; i++)
		{
			/* This is for un-directed graph */
			for(j=i+1; j<n; j++)
			/* For directed graph - use this */
			//for(j=0; j<n; j++)
			{
				sum = 0;
				if( (i != k) && (j != k) ) //for directed graph - comment this
				{
					sum = graph[i][k] + graph[k][j];
					if(min(graph[i][j], sum) == sum)
					{
						dist[i][j] = k;
					}
					graph[i][j] = min(graph[i][j], sum);
					graph[j][i] = graph[i][j];  //for directed graph - comment this
				}
			}
		}
	}
	PrintPath(dist, start, end);
	printf("\nDistance = %d\n",graph[start][end]);
	printf("\n");
	
	printf("The path is:-\n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%d\t",graph[i][j]);
		}
		printf("\n");
	}
	maxvalue = FindMax(n, graph);
	k = 0;
	printf("\nMax Value = %d\n",maxvalue);
	printf("Best possible nodes are:- \n");
	for(i=0; i<n; i++)
	{
		//found_flag = 0; notfound_flag = 0;
		found = 0;
		for(j=0; j<n; j++)
		{
			//printf("graph[i][j] = %d\n",graph[i][j]);
			if(graph[i][j] == maxvalue) 
			{
				found = 1; 
			}
		}
		if(found == 0)
		printf("%d ",i);
	}
	printf("\n");
}



