
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* hex2bin(unsigned int x)
{
	unsigned int num=0x00;
	char *binary = 0x00;
	int n=0;

	binary = malloc(sizeof(x)*sizeof(int));
	n = sizeof(x)*sizeof(int);
	memset(binary,'\0',sizeof(binary));
	binary[n] = '\0';
	while(n != 0)
	{
		binary[--n] = (char )((x % 0x02) + '0');
		x = x/0x02;
	}
	return(binary);
}


unsigned int bitinvert(unsigned int x, int p, int n)
{
	unsigned int y = 0x00;

	y = x ^ ( ~(~0 << n) ) << ((p-n)+1);   //invert 1 to 0 and 0 to 1 for p-n bits 

	return(y);
}


main()
{
	unsigned int x = 0xA1B2; //0x3973;
	unsigned int num = 0x00;
	char *binary = NULL;
	int i=0;

	printf("X = 0x%X\n",x);
	binary = hex2bin(x);
	printf("Binary of X = ");
	for(i=0; i<strlen(binary); i++)
	{
		if((i > 0) && (i % 4 == 0)) printf(" ");
		printf("%c",binary[i]);
	}
	printf("\n\n");
	num = bitinvert(x,8,4);
	binary = NULL;
	binary = hex2bin(num);
	printf("Binary of New Number = ");
	for(i=0; i<strlen(binary); i++)
	{
		if((i > 0) && (i % 4 == 0)) printf(" ");
		printf("%c",binary[i]);
	}
	printf("\n");
	printf("New Number = 0x%X\n",num);
	free(binary);
}



