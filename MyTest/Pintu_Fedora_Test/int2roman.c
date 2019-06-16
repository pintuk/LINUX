#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *Int2Roman(int num)
{
	char roman[50];
	int i = 0;

	//roman = malloc(sizeof(char)*20);
	memset(roman,'\0',sizeof(roman));
	while(num >= 1000)
	{
		roman[i++] = 'M';
		num = num - 1000;
	}
	while(num >= 900)
	{
		roman[i++] = 'C';
		roman[i++] = 'M';
		num = num - 900;
	}
	while(num >= 500)
	{
		roman[i++] = 'D';
		num = num - 500;
	}
	while(num >= 400)
	{
		roman[i++] = 'C';
		roman[i++] = 'D';
		num = num - 400;
	}
	while(num >= 100)
	{
		roman[i++] = 'C';
		num = num - 100;
	}
	while(num >= 90)
	{
		roman[i++] = 'X';
		roman[i++] = 'C';
		num = num - 90;
	}
	while(num >= 50)
	{
		roman[i++] = 'L';
		num = num - 50;
	}
	while(num >= 40)
	{
		roman[i++] = 'X';
		roman[i++] = 'L';
		num = num - 40;
	}
	while(num >= 10)
	{
		roman[i++] = 'X';
		num = num - 10;
	}
	while(num >= 9)
	{
		roman[i++] = 'I';
		roman[i++] = 'X';
		num = num - 9;
	}
	while(num >= 5)
	{
		roman[i++] = 'V';
		num = num - 5;
	}
	while(num >= 4)
	{
		roman[i++] = 'I';
		roman[i++] = 'V';
		num = num - 4;
	}
	while(num >= 1)
	{
		roman[i++] = 'I';
		num = num - 1;
	}
	roman[i] = '\0';

	return(roman);
}


main()
{
	int x = 0;
	int i = 0;
	char **roman;

	roman = malloc(3001*sizeof(char *));
	for(i=0; i<3001; i++)
	{
		roman[i] = malloc(20*sizeof(char));
		memset(&roman[i],'\0',20*sizeof(char));
	}
	printf("\tINT \t\t\tROMAN\n");
	printf("\t----\t\t\t-------------\n");
	for(i=0; i<=3000; i++)
	{
		roman[i] = Int2Roman(i);
		printf("\t%d\t\t\t%s\n",i,roman[i]);
	}
	printf("value at 3000 = %s\n",roman[3000]);
}
