#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<wchar.h>


typedef struct OperationType {
	unsigned short Path1[1024+1];
	unsigned int PathLen1;
	unsigned short Path2[1024+1];
	unsigned int PathLen2;
	unsigned short Noname[1024+1];
	unsigned int NonameLen3;
}OperationType_t;

void ConvertToUniCode(unsigned short *pOutStr, char *pInStr)
{
	int i = 0;
	
	for(i=0; pInStr[i] != '\0'; i++)
	{
		pOutStr[i] = (unsigned char)pInStr[i];
	}
	pOutStr[i] = '\0';
}

wchar_t *WideStrCat(unsigned short *pOutStr, unsigned short *pInStr)
{
	wchar_t *pOut = NULL;

	pOut = wcscat((wchar_t*)pOutStr,(wchar_t*)pInStr);
	if(pOut == NULL) return NULL;

	return(pOut);
}

wchar_t *WideStrnCpy(unsigned short *pOutStr, unsigned short *pInStr, unsigned int len)
{
	wchar_t *pOut = NULL;

	pOut = wcsncpy((wchar_t*)pOutStr,(wchar_t*)pInStr,(size_t)len);
	if(pOut == NULL) return NULL;

	return(pOut);
}

wchar_t *WideStrrChr(unsigned short *pOutStr, unsigned short pInCh)
{
	wchar_t *pOut = NULL;

	pOut = wcsrchr((wchar_t*)pOutStr,(wchar_t)pInCh);
	if(pOut == NULL) return NULL;

	return(pOut);
}

int WideStrLen(unsigned short *pOutStr)
{
	int len = 0;

	if(pOutStr == NULL)
	{
		return 0;
	}
	len = wcslen((wchar_t*)pOutStr);
	return len;
}

int main()
{
	char str1[7] = {255,254,253,252,251,250,'\0'};
	char str2[] = "Ubuntu";
	char Ufilename[] = "unknown.ext";
	unsigned char *pStrChr = NULL;
	int len1 = 0;
	int len2 = 0;
	int len3 = 0;
	OperationType_t OpType;

	unsigned short outstr1[1024+1] = {0,};
	unsigned short outstr2[1024+1] = {0,};
	unsigned short outfilename[1024+1] = {0,};

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

	pStrChr = (unsigned char *)WideStrrChr(OpType.Noname,'.');
	if(pStrChr != NULL)
	{
		*pStrChr = '\0';
	}
	printf("Out String strrchr = %ls , Len = %d\n",(wchar_t*)OpType.Noname,WideStrLen(OpType.Noname));
	
	return 0;	
}


