#include<stdio.h>


main()
{
	//unsigned long int x = 0x00;
	unsigned char *x = "005";
	char *buf = NULL;

	buf = x;

	printf("buff = %s\n",buf);
}

