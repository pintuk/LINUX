#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>


#define TRUE	1
#define FALSE	0

typedef int	BOOL;


/*Retrieves the number of milliseconds that have elapsed since the system was started*/
unsigned int GetSysElapsedTime(void)
{
	static struct timeval init_time = { 0 , 0 };
	static BOOL bFirst = FALSE;
	struct timeval current_time;

	if ( bFirst == FALSE )
	{
		bFirst = TRUE;
		gettimeofday(&init_time, NULL);
	}

	gettimeofday(&current_time, NULL);

	// 	return 	(current_time.tv_sec - init_time.tv_sec) * 1000UL + 	(UINT32)((current_time.tv_usec - init_time.tv_usec) / 1000.0)	;
	return 	((current_time.tv_sec * 1000000 + current_time.tv_usec) - (init_time.tv_sec * 1000000 + init_time.tv_usec))/1000;
}



main()
{
	char startSec[50] = {0};
	char endSec[50] = {0};
	char startTime[50] = {0};
	char endTime[50] = {0};
	time_t t;
	struct tm *tmt;
	int i = 0;
	int sec = 0;
	struct timeval current_time;
	double time1 = 0; double time2 = 0;
	unsigned int gettime1 = 0; unsigned int gettime2 = 0;
	long val1_mul = 0; long val2_sft = 0;

	t = time(NULL);
	tmt = localtime(&t);

	if(tmt == NULL)
	{
		perror("ERROR : localtime");
		exit(-1);
	}

	time1 = (double)GetSysElapsedTime();
	fprintf(stderr,"Main called.......\n");
	//printf("main - called - time1 = %d\n",time1);
	//sleep(1);
	//time2 = (double)GetSysElapsedTime();
	//printf("time for printf - %7.2f\n",time2 - time1);
	
	gettime1 = GetSysElapsedTime();
	printf("main - called - gettime1 = %d\n",gettime1);

	gettimeofday(&current_time, NULL);
	time1 = (double)((double)current_time.tv_sec * 1000000.00 + (double)(current_time.tv_usec))/1000.00;
	val1_mul = 176 * 144 * 2;
	printf("val1_mul = %d\n",val1_mul);
	gettimeofday(&current_time, NULL);
	time2 = (double)((double)current_time.tv_sec * 1000000.00 + (double)(current_time.tv_usec))/1000.00;
	printf("Time Taken - Multiply = %7.2f\n",(time2-time1));
	gettimeofday(&current_time, NULL);
	time1 = (double)((double)current_time.tv_sec * 1000000.00 + (double)(current_time.tv_usec))/1000.00;
	val2_sft = (100 - 1) << 512;
	printf("val2_sft = %d\n",val1_mul);
	gettimeofday(&current_time, NULL);
	time2 = (double)((double)current_time.tv_sec * 1000000.00 + (double)(current_time.tv_usec))/1000.00;
	printf("Time Taken - Shift = %7.2f\n",(time2-time1));
	
	
	strftime(startSec,sizeof(startSec),"%s",tmt);
	strftime(startTime,sizeof(startTime),"%r",tmt);
	printf("TIME 1 - %s\n",startTime);
	printf("time1 - %5.2f\n",time1);
	for(i=0; i<10000; i++)
	{
		;
	}
	sleep(2);
	t = time(NULL);
	tmt = localtime(&t);
	strftime(endSec,sizeof(endSec),"%s",tmt);
	strftime(endTime,sizeof(endTime),"%r",tmt);
	printf("TIME 2 - %s\n",endTime);
	printf("Seconds - %d\n",(atoi(endSec) - atoi(startSec)));
	gettimeofday(&current_time, NULL);
	time2 = (double)((double)current_time.tv_sec*1000000.00 + (double)(current_time.tv_usec))/1000.00;
	printf("time2 - %5.2f\n",time2);
	printf("DIFF time - %5.2f\n",(time2-time1));

	gettime2 = GetSysElapsedTime();
	printf("main - called - gettime2 = %d\n",gettime2);

	printf("The time Taken = %d\n", (gettime2 - gettime1));
}


