#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "romancalc.h"



void UI_setResult(const char *pszNumber)
{
	//strcpy(display,pszNumber);
	printf("%s ",pszNumber);
}

main()
{
	char c = 0;
	
	memset(display,'\0',sizeof(display));
	CALC_initialize();
	printf("\nEnter the roman expression: \n");
	while( (c=getchar()) != '\n')
	{
		CALC_onChar(c);
	}
	printf("\n");
	CALC_finalize();
	printf("Final = %s\n",display);
}
