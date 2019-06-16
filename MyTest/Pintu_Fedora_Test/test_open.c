#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

main()
{
	int fd = -1;
	unsigned char data[256] = {0};
	unsigned char readdata[256] = {0};
	int dataLen = 0; int i = 0;

	fd = open("opentest.raw", O_CREAT | O_RDWR);
	if(fd < 0)
	{
		fprintf(stderr, "open error.....\n");
		return -1;
	}
	memset(data, 0, sizeof(data));
	data[0] = 0x21; data[1] = 0x22; data[2] = 0x30;
	dataLen = 3;
	write(fd, data, sizeof(data));
	sleep(1);
	memset(readdata, 0, sizeof(readdata));
	read(fd, readdata, sizeof(readdata)); 
	for(i=0; i<dataLen; i++)
	{
		printf("read[%d] = 0x%x\n",i,readdata[i]);
	}
	close(fd);
}

