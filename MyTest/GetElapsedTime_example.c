#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

#define BLOCK_SIZE	1024
#define FILENAME	"sample.dat"



/* Returns time in millisecs */
double GetSysElapsedTime(void)
{
        struct timeval current_time;
	double value = 0.00;

        gettimeofday(&current_time, NULL);
	value = (double)((double)current_time.tv_sec * 1000000.00 + (double)(current_time.tv_usec))/1000.00;

        return  value;
}


int main()
{
	FILE *fp = NULL;
	char *buffer = NULL;
	size_t len = 0;
	double time1,time2;

	len = 512*BLOCK_SIZE;
	buffer = (char *)malloc(sizeof(char)*len);
	if(buffer == NULL)
	{
		perror("ERROR : malloc failed : ");
		exit(-1);
	}
	memset(buffer,'A',len);
	fp = fopen(FILENAME,"w+");
	if(fp == NULL)
	{
		perror("ERROR : fopen failed : ");
		free(buffer);
		exit(-2);
	}

	time1 = GetSysElapsedTime();
	fwrite(buffer,len,1,fp);
	sleep(1);
	time2 = GetSysElapsedTime();
	printf("Time taken by fwrite = %5.3f msecs\n",(time2 - time1));
	fclose(fp);
	printf("Done....\n");

	return 0;
}

