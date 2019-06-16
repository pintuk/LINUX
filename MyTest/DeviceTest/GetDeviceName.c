#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>


char DeviceName[20] = {0,};

char *_CdrOsalGetDeviceName(const char *mountpoint)
{
	//char DeviceName[50] = {0,};
	FILE *fp = NULL;
	char cmd[100] = {0,};
	int ret = -1;
	
	#define FILEPATH "/opt/etc/CdrDeviceName.df"
	
	sprintf(cmd,"%s %s %s %s","df | grep",mountpoint,"| awk '{print $1}' > ",FILEPATH);

	//printf("Command : %s\n",cmd);
	ret = system(cmd);

	if(ret < 0)
	{
		return NULL;
	}
	
	fp = fopen(FILEPATH,"r");
	if(fp == NULL)
	{
		perror("ERROR : fopen : ");
		return NULL;
	}
	memset(DeviceName,0,sizeof(DeviceName));
	fscanf(fp,"%s",DeviceName);
	fclose(fp);
	remove(FILEPATH);
	if(DeviceName[0] == '\0')
	{
		return NULL;
	}
	return(DeviceName);
}

int main(int argc, char *argv[])
{
	char *devname1 = NULL;
	char *devname2 = NULL;

	system("echo Get Device Name.....called");
	devname1 = _CdrOsalGetDeviceName(argv[1]);
	if(devname1 == NULL)
	{
		printf("Dev Name1 is NULL\n");
		exit(0);
	}
	printf("DeviceName1 : %s\n",devname1);

	devname2 = _CdrOsalGetDeviceName(argv[2]);
        if(devname2 == NULL)
        {
                printf("Dev Name2 is NULL\n");
                exit(0);
        }
        printf("DeviceName2 : %s\n",devname2);

	return(0);
}


