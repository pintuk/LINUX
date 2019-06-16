#include <stdio.h>


static void function1()
{
	printf("insid static function1\n");
}

void *function2()
{
	void (*ptr)(void) = &function1;

	return ptr;
}

int main()
{
	void (*ptr)(void) = &function2;

	//ptr = &function2;

	(*ptr)();

	return 0;
}
