#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>
#include<sys/stat.h>


typedef struct DateType {
	int day;
	int mon;
	int year;
	int hour;
	int min;
	int sec;
	unsigned long long int fullseconds;
}datetype;


int DiffDate(datetype dt2, datetype dt1)
{
	struct tm tm1, tm2;
	time_t t1, t2;
	int numdays = -1;

	memset(&tm1,0,sizeof(tm1));
	memset(&tm2,0,sizeof(tm2));
	tm2.tm_mday = dt2.day;
	tm2.tm_mon  = dt2.mon - 1;
	tm2.tm_year = dt2.year - 1900;
	tm2.tm_isdst = -1;

	t2 = mktime(&tm2);

	tm1.tm_mday = dt1.day;
        tm1.tm_mon  = dt1.mon - 1;
        tm1.tm_year = dt1.year - 1900;
        tm1.tm_isdst = -1;

	t1 = mktime(&tm1);

	numdays = (abs)((int)(t2-t1)/(24*60*60));

	return(numdays);
	
}


char *GetSystemTime(datetype *dt)
{
	struct tm *tm;
	time_t t;
	char *str = NULL;

	t = time(NULL);
	tm = localtime(&t);
	
	str = asctime(tm);
	if(str == NULL)
	{
		return NULL;
	}
	dt->day = tm->tm_mday;
	dt->mon = tm->tm_mon + 1;
	dt->year = tm->tm_year + 1900;
	dt->hour = tm->tm_hour;
	dt->min = tm->tm_min;
	dt->sec = tm->tm_sec;

	dt->fullseconds = (unsigned long long int)t;

	return(str);
}

char *GetDateType(unsigned int intdate, unsigned int inttime, datetype *dt)
{
	struct tm tm;
	char *str = NULL;
	time_t t = -1;
	unsigned long long int seconds;

	memset(&tm,0,sizeof(tm));
	if(intdate == 0)
	{
		return NULL;
	}
	dt->day = (intdate & 0x001F);
        dt->mon  = (intdate & 0x01E0) >> 5;
        dt->year = (((intdate & 0xFE00) >> 9) + 1980);

	dt->sec = (inttime & 0x001F)*2;
        dt->min = (inttime & 0x07E0) >> 5;
        dt->hour = (inttime & 0xF800) >> 11;

	tm.tm_mday = dt->day;
        tm.tm_mon  = dt->mon - 1;
        tm.tm_year = dt->year - 1900;
	
	tm.tm_hour = dt->hour;
        tm.tm_min = dt->min;
        tm.tm_sec = dt->sec;

        tm.tm_isdst = -1;

        t = mktime(&tm);
	if(t < 0)
	{
		printf("ERROR : mktime failed : <%s>\n",strerror(errno));
		return NULL;
	}
	dt->fullseconds = (unsigned long long int)t;
	str = asctime(&tm);

	return str;
}



int main(int argc, char *argv[])
{
	unsigned int intdate = 0;
	unsigned int inttime = 0;
	//int day = 0; int mon = 0; int year = 0;
	//int hour = 0; int min = 0; int sec = 0;
	char *str = NULL;
	datetype dt = {0,};
	datetype dt1 = {0,};
	datetype dt2 = {0,};
	unsigned long long int s1 = 0, s2 = 0;
	int noofDays = 0;

	if(argc < 3)
	{
		printf("Usage Error : <exe> <integer date> <integer time>\n");
		exit(0);
	}
	intdate = (unsigned int)atoi(argv[1]);
	inttime = (unsigned int)atoi(argv[2]);

	str = GetDateType(intdate, inttime, &dt);
	printf("Date : %d / %d / %d\n",dt.day,dt.mon,dt.year);
	printf("Time : %d:%d:%d\n",dt.hour,dt.min,dt.sec);
	printf("FULL = %s\n",str);
	s1 = dt.fullseconds;
	printf("Total Seconds = %llu\n",s1);

	//str = GetTime(intdate, &hour, &min, &sec);
	//printf("Time : %d : %d : %d\n",hour,min,sec);
	//printf("FULL = %s\n",str);

	//strftime(str, sizeof(str), "%c", &tm);
	//printf("String Date : %s\n",str);

	str = GetSystemTime(&dt);
	printf("Current Time : %s\n",str);
	printf("Date : %d-%d-%d\n",dt.day,dt.mon,dt.year);
	printf("Time : %d::%d::%d\n",dt.hour,dt.min,dt.sec);
	s2 = dt.fullseconds;
	printf("Total Seconds = %llu\n",s2);

	printf("Diff Days = %d\n",(int)(s2-s1)/(24*60*60));
	printf("\n\n");
	GetDateType(intdate, inttime, &dt1);
	//GetDateType(intdate, inttime, &dt);
	noofDays = DiffDate(dt,dt1);
	printf("Number Of Days   =   %d\n",noofDays);
	return 0;
}



