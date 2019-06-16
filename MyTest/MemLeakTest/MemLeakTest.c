#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define malloc MemMalloc
#define free MemFree

typedef struct {
	unsigned int *address;
	int count;
	int freesize;
	int *allocsize;
	int totalsize;
}MemLeakTrack;

MemLeakTrack memtrack;



void *MemMalloc(size_t size)
{

	void *ptr = NULL;
	static int i = 0;

	ptr = malloc(size);
	if(ptr == NULL)
	{
		return NULL;
	}
	memtrack.address[i] = (unsigned int)ptr;
	printf("Malloc Address[%d] = %u\n",i,memtrack.address[i]);
	memtrack.allocsize[i] = size;
	i++;
	memtrack.count += i;
	memtrack.totalsize += size;
	return ptr;
}

void MemFree(void *ptr)
{
	int size = 0;
	int i = 0;
	unsigned int ptrAddr = (unsigned int)ptr;
	
	if(ptr == NULL)
	{
		return;
	}
	size = sizeof(ptr);
	free(ptr);

	//printf("TOTAL COUNT = %d\n",memtrack.count);

	for(i=0; i<memtrack.count; i++)
	{
		if(memtrack.address[i] == (unsigned int)ptrAddr)
		{
			printf("Free Address[%d] = %u\n",i,(unsigned int)ptrAddr);
			memtrack.freesize += memtrack.allocsize[i];
			memtrack.address[i] = 0;
			break;
		}
	}
}


void CalculateMemLeak()
{
	//int totalleak = 0;
	printf("***************************************************************\n");
	fprintf(stderr,"Total Memory Allocated = %d\n",memtrack.totalsize);
	fprintf(stderr,"Total Memory Freed     = %d\n",memtrack.freesize);
	fprintf(stderr,"Total Memory Leakage   = %d\n",(memtrack.totalsize - memtrack.freesize));
	printf("***************************************************************\n");
}

typedef struct {
	char c;
	int x;
	int y;
}TestStruck;


int main()
{
	int *ptr1[10];
	char *ptr2 = NULL;
	int i = 0;

	TestStruck *struck = NULL;

	#define MAX_SIZE	1024

	memset(&memtrack,0,sizeof(memtrack));
	memtrack.address = (unsigned int *)malloc(sizeof(char)*MAX_SIZE*MAX_SIZE);
	memtrack.allocsize = (int *)malloc(sizeof(char)*MAX_SIZE*MAX_SIZE);

	for(i=0; i<10; i++)
	{
		ptr1[i] = (int *)malloc(512*32);
	}
	//ptr2 = (char *)MemMalloc(512*1024);
	struck = (TestStruck *)malloc(sizeof(TestStruck));

	for(i=0; i<9; i++)
	{
		free(ptr1[i]);
	}
	//MemFree(ptr2);
	free(struck);

	CalculateMemLeak();

	free(memtrack.address);
	free(memtrack.allocsize);
}


