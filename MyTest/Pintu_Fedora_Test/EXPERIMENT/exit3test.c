#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


#define ASSERT(expr)	do { \
							if(!(expr)) \
							assert(0); \
							exit(3); \
						} while(0) 


void Cleanup()
{
	printf("Cleaning UP!\n");
	exit(0);
}


int main()
{
	int x = 0;

	atexit(Cleanup);

	printf("Main ---->\n");

	ASSERT((x!=0));

	printf("Done....\n");
}



