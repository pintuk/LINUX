#include<stdio.h>
#include<stdlib.h>
#include<string.h>


main()
{
	char str[200] = {0};

	printf("Enter a message : \n");
	fgets(str, sizeof(str), stdin);

	printf("message - \n");
	printf("%s\n",str);
}
