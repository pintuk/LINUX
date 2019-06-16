#include<stdio.h>
#include<assert.h>


void function1(char **ptr)
{
	int *len;
	int expr1 = (ptr != NULL);
	int expr2 = (0 < len);

	if(!expr1)
	{
		printf("expr1....\n");
		assert(0);
	}
	if(!expr2)
	{
		printf("expr2....\n");
		assert(0);
	}
	if(ptr == NULL)
	{
		printf("ERROR : **ptr is NULL...\n");
		assert(ptr != NULL);
	}
}


main()
{
	char *ptr1 = NULL;

	function1(&ptr1);
	printf("Done....\n");
}


