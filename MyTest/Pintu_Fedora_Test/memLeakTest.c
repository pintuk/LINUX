
#include<stdio.h>
#include<stdlib.h>


void function1()
{
	printf("function1() - is called !\n");
}


main()
{
	void (*ptrfunc1)();
	printf("Entering - main() -\n");
	ptrfunc1 = function1;
	(*ptrfunc1)();
	printf("Address of function1 - %u\n",ptrfunc1);
	while(1);
}
