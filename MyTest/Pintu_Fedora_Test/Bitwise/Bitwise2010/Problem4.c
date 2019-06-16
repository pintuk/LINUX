#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main()
{
	int t = 0; int ncases = 0;
	int S = 0; int W = 0; int E = 0; int i = 0; int j = 0; int k = 0;
	char ESentence[1001]; char EWord[101][15];
	char NSentence[1001]; char NWord[101][15];
	char InWords[101][15]; char OutWords[101][15];

	scanf("%d",&ncases);
	for(t=0; t<ncases; t++)
	{
		scanf("%d",&S);
		for(i=0; i<S; i++)
		{
			scanf("%d",&W);
			for(j=0; j<W; j++)
			{
				scanf("%s",&EWord[j]);
			}
			for(j=0; j<W; j++)
			{
				scanf("%s",&NWord[j]);
			}
		}
		scanf("%d",&E);
		for(i=0; i<E; i++)
		{
			scanf("%s",InWords[i]);
		}


	}
	/* ****************** Checking Input ************************ */
#if 0
	for(t=0; t<ncases; t++)
	{
		for(i=0; i<S; i++)
		{
			for(j=0; j<W; j++)
			{
				printf("%s ",EWord[j]);
			}
			printf("\n");
			for(j=0; j<W; j++)
			{
				printf("%s ",NWord[j]);
			}
			printf("\n");
		}
		for(i=0; i<E; i++)
		{
			printf("%s\n",InWords[i]);
		}
	}
#endif

	
	
	return 0;
}


