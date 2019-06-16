#include<stdio.h>
#include<ctype.h>


main()
{
	char input[10];
	int i = 0; int j = 0; int k = 0;
	char s[2] = {0};
	int data[10][10];

	for(i=1; i<=9; i++)
	{
	scanf("%s",&input);
	for(j=0; input[j] != '\0'; j++)
	{
		k = j+1;
		if(input[j] == '.')
		{
			data[i][k] = 0;
		}
		else
		{
			sprintf(s,"%c",input[j]);
			data[i][k] = atoi(s);
		}
		printf("%d  ",data[i][k]);
	}
	printf("\n");
	}

	printf("\n--------------------------\n");
	for(i=1; i<=9; i++)
	{
	for(j=1; j<=9; j++)
	{
		printf("%d  ",data[i][j]);
	}
	printf("\n");
	}

	printf("\n");
}

