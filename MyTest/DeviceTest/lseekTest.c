#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>



#define DEVICE_NAME	"/dev/mmcblk0p1"


int main(int argc, char *argv[])
{
	off_t offset = 0;
	int fd = -1;
	int ret = -1;
	int sectorno = 0;

	fd = open(DEVICE_NAME, O_RDONLY);
	if(fd < 0)
	{
		printf("open failed : %s\n",strerror(errno));
		exit(0);
	}
	sectorno = 4194464;
	offset = (off_t)(sectorno*512);
	
	ret = lseek(fd, offset, SEEK_SET);
	if(ret < 0)
	{
		printf("lseek failed : %s\n",strerror(errno));
		printf("lseek offset value = %u\n",offset);
		exit(0);
	}
	printf("--- DONE ----\n");
	
}



