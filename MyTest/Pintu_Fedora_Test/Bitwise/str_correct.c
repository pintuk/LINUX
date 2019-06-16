#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define		min(a,b)	( (a) < (b) ) ? (a) : (b)
					


int diff(char x, char y)
{
	if(x == y) return(0);
	else
	return(1);
}

/*
void PrintTable(int m, int n, int E[][100])
{
	int i = 0; int j = 0;

	for(i=0; i<=m; i++)
	{
		for(j=0; j<=n; j++)
		{
			printf("%5d",E[i][j]);
		}
		printf("\n");
	}
}
*/

int Knapsack_Edit(int m, int n, char *x, char *y, char *substr)
{
	int E[128][128];
	int i = 0; int j = 0; int k = 0;

	for(i=0; i<=m; i++)
	{
		E[i][0] = i;
	}
	for(j=1; j<=n; j++)
	{
		E[0][j] = j;
	}

	for(i=1; i<=m; i++)
	{
		for(j=1; j<=n; j++)
		{
			E[i][j] = min( min(E[i-1][j]+1, E[i][j-1]+1), (E[i-1][j-1] + diff(x[i-1],y[j-1])) );
			if( (x[i-1] == y[j-1]) && (strchr(substr,x[i-1]) == NULL) )
			{
				substr[j] = x[i-1];
			}
		}
	}
	substr[j] = '\0';
	//PrintTable(m, n, E);
	return(E[m][n]);
}


main()
{
	int n = 0; int m = 0;
	int i = 0; int j = 0;
	char string1[128]; char string2[128]; char matchstr[256];
	int maxdist = 0; int len = 0;

	memset(matchstr,'\0',sizeof(matchstr));
	printf("Enter a target string 1:-\n");
	scanf("%s",string1);
	printf("Enter the correct string 2:-\n");
	scanf("%s",string2);

	m = strlen(string1);
	n = strlen(string2);

	printf("Longest Common Subsequence is:-\n");
	maxdist = Knapsack_Edit(m, n, string1, string2, matchstr);
	for(i=0; i<n; i++)
	{
		printf("%c ",matchstr[i]);
		if(matchstr[i] != string2[i]) matchstr[i] = string2[i];
		string1[i] = matchstr[i];
	}
	printf("\n");
	string1[n] = '\0';
	printf("Final String is :-\n");
	printf("%s\n",string1);
	printf("\n");
}




