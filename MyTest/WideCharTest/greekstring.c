#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>



int main()
{
	char s1[] = "ÎκÏροÏή";
	char s2[] = "Îν δεν είναι";

	char *final = NULL;

	int len1 = 0; int len2 = 0; int fsize = 0;

	len1 = strlen(s1);
	len2 = strlen(s2);
	fsize = len1+len2+1;
	final = (char*)malloc(fsize);
	memset(final,'\0',(fsize));
	printf("s1 = %s , Len = %d\n",s1,len1);
	printf("s2 = %s , Len = %d\n",s2,len2);

	strcpy(final,s1);
	strcat(final,s2);
	printf("Final s1 = %s\n",final);

	free(final);
	return 0;
}

