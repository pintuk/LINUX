#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define FILENAME1	"example1.txt"
#define FILENAME2	"example2.txt"
typedef int EnMM_File;


EnMM_File EnMM_CreateFile(const char *filename, int flags)
{
	FILE *fp = NULL;
	char fg[2] = {0};

	if(flags == 1)
	{
		printf("flags = %d\n",flags);
		sprintf(fg, "rw+");
	}
	fp = fopen(filename, fg);
	if(fp == NULL)
	{
		fprintf(stderr, "fopen - failed....\n");
		return -1;
	}
	printf("File Created - fp = %d\n",fp);
	return (EnMM_File )fp;
}

int EnMM_WriteFile(EnMM_File fileHandle, char* pDataToWrite, int sizeInBytes)
{
	if(fileHandle < 0)
	{
		fprintf(stderr, "EnMM_WriteFile - Invalid File Handle.....\n");
		return -1;
	}
	fwrite(pDataToWrite, 1, sizeInBytes, (FILE *)fileHandle);
	printf("file handle = %d\n",fileHandle);
	printf("data written = %s\n", pDataToWrite);
	
	return 1;
}

int EnMM_ReadFile(EnMM_File fileHandle,void* pBuffer, unsigned int bufLen, unsigned int * pReadLen)
{
	FILE *fp = (FILE *)fileHandle;

	if(fileHandle < 0)
	{
		fprintf(stderr, "EnMM_ReadFile - Invalid File Handle.....\n");
		return -1;
	}
	printf("EnMM_ReadFile - file handle = %d\n",fp);
	printf("buf Len = %d\n",bufLen);
	*pReadLen = fread(pBuffer, 1, bufLen, (FILE *)fileHandle);
	printf("pbuffer = %s\n",pBuffer);
	if(pReadLen <= 0)
	{
		printf("Error : fread - pReadLen = %d\n",pReadLen);
	}
	
}

int main()
{
	FILE *ff = NULL;
	EnMM_File hfile1 = -1;
	EnMM_File hfile2 = -1;
	char data1[] = "Hello. World !!!\n";
	char data2[] = "Hello....There...\n";
	unsigned char flag = 1;
	char *buffer = NULL;
	unsigned int rlen = 0;

	hfile1 = EnMM_CreateFile(FILENAME1, flag);
	printf("Create file2.....\n");
	hfile2 = EnMM_CreateFile(FILENAME2, flag);

	ff = fopen(FILENAME1, "rw");
	if(ff == NULL)
	{
		perror("Error : ");
	}
	hfile1 = (EnMM_File)ff;
	buffer = malloc(sizeof(char)*100);
	memset(buffer, 0, 100);
	//EnMM_WriteFile(hfile1, data2, sizeof(data1));
	printf("read from file1....\n");
	EnMM_ReadFile(hfile1, buffer, 10, &rlen);
	printf("rlen = %d\n",rlen);

	printf("Write into file2.....\n");
	EnMM_WriteFile(hfile2, buffer, rlen);
	fclose((FILE *)hfile2);
	fclose((FILE *)hfile1);
	free(buffer);
	buffer = NULL;
}



