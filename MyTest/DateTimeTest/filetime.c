#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>
#include<sys/stat.h>


char *GetAccessTime(struct stat *st)
{
	struct tm *tm = NULL;
	time_t timeinfo;
	char *str = NULL;

	str = ctime( &(st->st_atime) );
	printf("*************************************\n");
	printf("Last Access = %s\n",ctime(&st->st_atime));
	printf("Last Modify = %s\n",ctime(&st->st_mtime));
	printf("Last Change = %s\n",ctime(&st->st_ctime));
	printf("*************************************\n");
	printf("\n");
	
#if 0
	tm = gmtime(&(st->st_ctime));
        printf("Date = %d/%d/%d\n",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900);
        printf("Time = %d::%d::%d\n",tm->tm_hour,tm->tm_min,tm->tm_sec);
        printf("Week = %d\n",tm->tm_wday+1);
        printf("\n");
	str = asctime(tm);
        //timeinfo = mktime(tm);
        //str = ctime(&timeinfo);
#endif
	return(str);
}


int main(int argc, char *argv[])
{
	struct stat st = {0,};
	int fd = -1;
	char filename[256] = {0,};
	int ret = -1;
	char *strdate = NULL;
	char week[4] = {0,};
	char month[4] = {0,};
	int day = 0; int hour = 0; int min = 0; int sec = 0; int year = 0;
	//char day[3] = {0,};
	//char year[5] = {0,};
	//char hour[3] = {0,};
	//char min[3] = {0,};
	//char sec[3] = {0,};


	if(argc < 2)
	{
		printf("Usage Error : <exe> <filename>\n");
		exit(0);
	}
	strcpy(filename,argv[1]);
	//fd = open(filename, O_RDONLY);
	//if(fd < 0)
	//{
	//	printf("ERROR : open failed : <%s>\n",strerror(errno));
	//	exit(0);
	//}
	//ret = fstat(fd,&st);
	ret = stat(filename,&st);
	if(ret < 0)
        {
                printf("ERROR : fstat failed : <%s>\n",strerror(errno));
		//close(fd);
                exit(0);
        }
	printf("FILE = %s\n",filename);
	strdate = GetAccessTime(&st);
	printf("Last Access Date : %s\n",strdate);

	sscanf(strdate,"%s %s %d %d:%d:%d %d",week,month,&day,&hour,&min,&sec,&year);
	printf("Date ==> Day = %d , Month = %s , Year = %d\n",day,month,year);
	printf("WeekDay = %s\n",week);
	printf("Time ==> Hour = %d , Min = %d , Sec = %d\n",hour,min,sec);
	//close(fd);
}


