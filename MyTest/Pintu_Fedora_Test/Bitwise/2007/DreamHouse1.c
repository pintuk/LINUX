#include<stdio.h>
#include<stdlib.h>


main()
{
	int ncases = 0;
	int n = 0;
	int Nodes[1000][1000] = {0};
	int i = 0; int j = 0; int k = 0;

	printf("Enter the number of test cases: -");
	scanf("%d",&ncases);

	for(k=0; k<ncases; k++)
	{
		printf("Enter the number of Nodes:");
		scanf("%d",&n);
		printf("Enter the edges :");
		for(i=0; i<n; i++)
		{
			for(j=
