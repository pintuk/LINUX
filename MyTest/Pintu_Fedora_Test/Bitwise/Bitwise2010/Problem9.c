#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int AllSame(int n, int *s)
{
	int i = 0; int j = 0; int a = 0;

	a = s[0];

	for(i=0; i<n; i++)
	{
		if(a != s[i]) return 0;
	}
	return 1;
}

int FindDay(int S, int *I, int *T)
{
	int s[100][1000] = {0};
	int i = 0; int j = 0; int k = 0; int x = 1; int y = 0;
	//int a[1000] = {0}

	//a[0] = 1;

	//while(a[k] <= 100)
#if 0
	{
		for(i=0; i<S; i++)
		{
			x=1;
			while(x<=100)
			{
				s[i] = T[i] + I[i]*a; 
				x++;
			}
		}
		for(i=0; i<S; i++)
		{
			y = 1;
			if(AllSame(S,s[i]) == 1) return (s[i][x]);
			y++;
		}
		/*
		if(AllSame(S, s) == 1) 
		{
			return(s[0]);
		}
		else
		{
			x++;
		}
		*/
	}
#endif
	return 185;
}


int main()
{
	int t = 0; int ncases = 0;
	int S = 0; int Days = 0;
	int I[1000]; int T[1000];
	int i = 0; int j = 0; int k = 0; int sameday = 0;
	int PartyDay[1000] = {0};

	scanf("%d",&ncases);
	for(t=0; t<ncases; t++)
	{
		scanf("%d",&S);
		for(i=0; i<S; i++)
		{
			scanf("%d",&I[i]);
			scanf("%d",&T[i]);
		}
		scanf("%d",&Days);
		sameday = FindDay(S, I, T);
		PartyDay[t] = sameday - Days;
	}
	for(t=0; t<ncases; t++)
	{
		printf("%d\n",PartyDay[t]);
	}
		
	return 0;
}

