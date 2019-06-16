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


main()
{
	unsigned int x = 0xa1;
	char *binary = NULL;
	
	printf("Number = 0x%x\n",x);
	binary = hex2bin(x);

	printf("Number in Binary = %s\n",binary);
}

