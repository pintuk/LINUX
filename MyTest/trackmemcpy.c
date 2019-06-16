#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define KB	(1024)

#define MEM_SIZE	(100*KB)

int main()
{
	int a = 0;
	int b = 0;
	char data1[MEM_SIZE+1];
	char data2[MEM_SIZE+1];

	memset(data1,1,MEM_SIZE);
	memcpy(data2,data1,MEM_SIZE);
	getchar();
	printf("Done...\n");
	return 0;
}

