#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>
#include<sys/stat.h>


#define CMD_LAUNCH(cmd)	"cat timing.log | " #cmd " -n 1 | awk '{print $2}'"


struct launch_time {
	time_t t;
	int millsecs;
};

struct launch_time get_launch_time_from_log(const char *cmdline)
{
	FILE *fp;
	char output[128];
	int hour,min,sec,msec,tzone;
	struct tm tm = {0,};
	struct tm *localtm = NULL;
	time_t t;
	struct launch_time ltime = {0,};

	memset(output, '\0', sizeof(output));
	fp = popen(cmdline, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s: Failed to open: %s : %s\n",
			__func__, cmdline, strerror(errno));
		return ltime;
	}
	if (fgets(output, sizeof(output), fp) != NULL) {
		sscanf(output, "%d:%d:%d.%d+%d", &hour, &min, &sec, &msec, &tzone);
	}
	printf("hour: %d, min: %d, sec: %d, msec: %d, time zone: %d\n", hour,min,sec,msec,tzone);
	memset(&tm,0,sizeof(tm));
	
	t = time(NULL);
        localtm = localtime(&t);
	printf("LOCAL:-> day:%d, mon:%d, year:%d, hour:%d, min:%d, sec:%d, zone: %d\n", localtm->tm_mday,localtm->tm_mon,localtm->tm_year,localtm->tm_hour,localtm->tm_min,localtm->tm_sec,localtm->tm_isdst);

	tm = *localtm;
	tm.tm_hour = hour;
	tm.tm_min = min;
	tm.tm_sec = sec;
	//tm.tm_year = (2005 - 1900);
	//tm.tm_mday = 22;
	//tm.tm_mon = (9 - 1);
	//tm.tm_isdst = -1;

	t = mktime(&tm);
	ltime.t = t;
	ltime.millsecs = msec;

	pclose(fp);
	return ltime;
}

int get_app_launch_time()
{
	struct launch_time start,end;
	int millisecs = 0;
	double s1;

	start = get_launch_time_from_log(CMD_LAUNCH(head));
	end = get_launch_time_from_log(CMD_LAUNCH(tail));

	s1 = difftime(end.t, start.t);
	printf("difftime: %f\n", s1);
	millisecs = difftime(end.t, start.t)*1000 + (end.millsecs - start.millsecs);
	return millisecs;
}

int main()
{
	struct tm tm;
	time_t t1,t2;
	int ms;

	ms = get_app_launch_time();
	printf("launch_time = %d ms\n", ms);

	return 0;
}
