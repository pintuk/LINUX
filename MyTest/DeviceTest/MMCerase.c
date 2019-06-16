#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>




#define DEVICE_NAME	"/dev/mmcblk1"



int main(int argc, char *argv[])
{
	int fd = -1;
	int devname[256] = {0,};
	unsigned char erase[512] = {0,};
	off_t offset = 0L;
	int ret = 0;

	if(argc < 2)
	{
		printf("Usage Error : <exe> <devname>\n");
		return 0;
	}
	strcpy(devname,argv[1]);
	fd = open(devname, O_RDWR);
	if(fd < 0)
	{
		printf("ERROR : open failed : <%s>\n",strerror(errno));
		return 0;
	}
	memset(erase, 0x00, sizeof(erase));
	ret = lseek(fd, 512L, SEEK_SET);
	if(ret < 0)
	{
		printf("ERROR : lseek failed : <%s>\n",strerror(errno));
		close(fd);
		return 0;
	}
	while(fd)
	{
	ret = write(fd, erase, sizeof(erase));
	if(ret > 0)
	{
		printf("Written : %d bytes\n",ret);
	}
	}
	close(fd);
	return 0;
}


