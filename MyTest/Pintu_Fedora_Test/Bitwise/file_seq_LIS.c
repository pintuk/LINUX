#include<stdio.h>
#include<stdlib.h>


int LIS(int n, int *S, int *L)
{
	int store[100] = {0};
	int i = 0; int j = 0; int k = 0; int p = 0;
	int pos = 0;
	int small = 0; int start = 0; int len = 0;
	int *ptr = NULL;

	for(pos=0; pos<n; pos++)
	{
		start = S[pos];
		store[0] = start;
		for(i=pos; i<n; i++)
		{
			k=1; small = start;
			for(j=i+1; j<n; j++)
			{
				if(S[j] > small)
				{
					small = S[j];
					store[k++] = S[j];
				}
			}
			if(k > len)
			{
				len = k;
				for(p=0; p<len; p++)
				{
					L[p] = 0;
					L[p] = store[p];
				}
			}
		}
	}
	//L = ptr;
	return(len);
}


main(int argc, char *argv[])
{
	FILE *fp1 = NULL; FILE *fp2 = NULL;
	int n = 0; int ncases = 0;
	int S[100]; int L[100];
	int i = 0; int j = 0;
	int len = 0;

	if(argc < 2)
	{
		printf("Usage: %s <input file>\n",__FILE__);
		exit(-1);
	}
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");

	if(fp1 == NULL)
	{
		printf("No input file....\n");
		exit(-1);
	}
	while(!feof(fp1))
	{
		fscanf(fp1, "%d", &ncases);
		for(j=1; j<=ncases; j++)
		{
			fscanf(fp1,"%d",&n);
			for(i=0; i<n; i++)
			{
				fscanf(fp1,"%d ",&S[i]);
			}
			len = LIS(n, S, L);
			fprintf(fp2,"%d\n",j);
			for(i=0; i<len; i++)
			{
				fprintf(fp2,"%d  ",L[i]);
			}
			fprintf(fp2,"\nLength = %d\n",len);
		}
	}
	fclose(fp1);
	fclose(fp2);
}


