#include<stdio.h>
#include<string.h>


int main()
{
	int len = 0;
	char str[81] = {'a','b','c','d','e','\0','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e','a','b','c','d','e'};

	//char str[5] = {'a','b','c','d','e'};

	len = strlen(str);

	printf("Length = %d\n",len);
}

