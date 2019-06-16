#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<wchar.h>
#include<langinfo.h>
#include<locale.h>


typedef unsigned int t_filetype;


typedef struct OperationType {
	t_filetype Path1[1024+1];
	unsigned int PathLen1;
	t_filetype Path2[1024+1];
	unsigned int PathLen2;
	t_filetype Noname[1024+1];
	unsigned int NonameLen3;
}OperationType_t;

void ConvertToUniCode(t_filetype *pOutStr, char *pInStr)
{
	int i = 0;
	
	for(i=0; pInStr[i] != '\0'; i++)
	{
		pOutStr[i] = (unsigned int)pInStr[i];
	}
	pOutStr[i] = '\0';
}

t_filetype *WideStrCat(t_filetype *pOutStr, t_filetype *pInStr)
{
	t_filetype *pOut = NULL;

	pOut = wcscat((wchar_t*)pOutStr,(wchar_t*)pInStr);
	if(pOut == NULL) return NULL;

	return(pOut);
}

t_filetype *WideStrnCpy(t_filetype *pOutStr, t_filetype *pInStr, unsigned int len)
{
	t_filetype *pOut = NULL;

	pOut = wcsncpy((wchar_t*)pOutStr,(wchar_t*)pInStr,(size_t)len);
	if(pOut == NULL) return NULL;

	return(pOut);
}

t_filetype *WideStrrChr(t_filetype *pOutStr, t_filetype pInCh)
{
	t_filetype *pOut = NULL;

	pOut = wcsrchr((wchar_t*)pOutStr,(wchar_t)pInCh);
	if(pOut == NULL) return NULL;

	return(pOut);
}

t_filetype *StrrChr(t_filetype *pOutStr, t_filetype pInCh)
{
	unsigned int i = 0;
	unsigned int len = 0;

	len = WideStrLen(pOutStr);
	printf("\nlen = %d\n",len);
	//printf("**********************************\n");
	//for(i=0;pOutStr[i]!='\0';i++)
	for(i=len;i>=0;i--)
	{
		//printf("%c",(char)pOutStr[i]);
		if(pOutStr[i] == pInCh) break;
	}
	//printf("\n");
	//printf("**********************************\n");
	//while (pOutStr[i] != '\0') 
 	//{
 	//	i++;
 	//}

 	//while (pOutStr[i] != pInCh) 
 	//{
 	//	i--;
 	//}
	return((t_filetype *)&pOutStr[i]);
}

int WideStrLen(t_filetype *pOutStr)
{
	unsigned int len = 0;

	if(pOutStr == NULL)
	{
		return 0;
	}
	len = wcslen((wchar_t*)pOutStr);
	return len;
}

int main()
{
	//char str1[7] = {255,254,253,252,251,250,'\0'};
	char str1[] = "Hello_";
	char str2[] = "Ubuntu";
	char Ufilename[] = "unknown.ext";
	char OutName[50] = {0,};
	t_filetype *pStrChr = NULL;
	unsigned int len1 = 0;
	unsigned int len2 = 0;
	unsigned int len3 = 0;
	int i = 0;
	OperationType_t OpType;

	unsigned short outstr1[1024+1] = {0,};
	unsigned short outstr2[1024+1] = {0,};
	unsigned short outfilename[1024+1] = {0,};

	//setlocale(LC_ALL, "");
	setlocale(LC_CTYPE, "");
	if(strcmp(nl_langinfo(CODESET), "UTF-8") == 0)
	{
		printf("UTF-8 is supported !!!\n");
	}
	else
	{
		printf("UTF-8 not supported...\n");
	}

	memset(&OpType, 0, sizeof(OpType));
	printf("str1 = %s , Length = %d\n",str1,strlen(str1));
	printf("str2 = %s , Length = %d\n",str2,strlen(str2));
	ConvertToUniCode(outstr1, str1);
	ConvertToUniCode(outstr2, str2);
	ConvertToUniCode(outfilename, Ufilename);
	
	mbstowcs((wchar_t*)outstr1, str1, strlen(str1)+1);
	mbstowcs((wchar_t*)outstr2, str2, strlen(str2)+1);
	mbstowcs((wchar_t*)outfilename, Ufilename, strlen(Ufilename)+1);
	len1 = WideStrLen(outstr1);
	len2 = WideStrLen(outstr2);
	len3 = WideStrLen(outfilename);

	if(wcsstr((wchar_t*)outstr2,L"Ubuntu") != NULL)
	{
		printf("FOUND................\n");
		exit(0);
	}
	printf("\n");
	printf("Out String 1 = %ls , Len = %d\n",(wchar_t*)outstr1,len1);	
	printf("Out String 2 = %ls , Len = %d\n",(wchar_t*)outstr2,len2);	
	OpType.PathLen1 = len1;
	OpType.PathLen2 = len2;
	OpType.NonameLen3 = len3;
	WideStrnCpy(OpType.Path1,outstr1,len1);
	WideStrnCpy(OpType.Path2,outstr2,len2);
	WideStrnCpy(OpType.Noname,outfilename,len3);

	printf("\n");
	printf("OpType Path 1 = %ls , Len = %d\n",(wchar_t*)OpType.Path1,OpType.PathLen1);	
	printf("OpType Path 2 = %ls , Len = %d\n",(wchar_t*)OpType.Path2,OpType.PathLen2);	
	printf("OpType NoName = %ls , Len = %d\n",(wchar_t*)OpType.Noname,OpType.NonameLen3);	
	WideStrCat(OpType.Path1,OpType.Path2);
	printf("Out String Cat = %ls , Len = %d\n",(wchar_t*)OpType.Path1,WideStrLen(OpType.Path1));

	pStrChr = (unsigned int *)WideStrrChr(OpType.Noname,'.');
	if(pStrChr != NULL)
	{
		*pStrChr = '\0';
	}
	printf("Out String strrchr = %ls , Len = %d\n",(wchar_t*)OpType.Noname,WideStrLen(OpType.Noname));

	//wcstombs(OutName,(wchar_t*)OpType.Noname,len3);
	//printf("OpType.Noname  =  %s\n",(char*)OutName);

	//mbstowcs((wchar_t*)OpType.Noname,OutName,len3);
	pStrChr = StrrChr(OpType.Noname,'.');
	if(pStrChr != NULL)
	{
		*pStrChr = '\0';
	}
	for(i=0; OpType.Noname[i]!='\0';i++)
	{
		printf("%c",(char)OpType.Noname[i]);
	}

	printf("\n");

	return 0;	
}


