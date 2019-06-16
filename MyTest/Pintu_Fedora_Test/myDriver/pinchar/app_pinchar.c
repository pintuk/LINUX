
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<sys/mman.h>
#include "pinchar_ioctl.h"


#define DEVICE_NAME			"/dev/pinchar"
#define MAX_BUFFER_SIZE		(64*1024)

main()
{
	int fd;
	char msg[25];
	char *buffer=NULL; char ch;
	int buffer_size=0; int i=0;
	size_t total_size = 0;
	int ret=-1;
	int length=0;
	char *mmap_buffer = NULL;
	

	strcpy(msg,"Hi Pinchar! From mmap.");
	printf("msg = %s\n",msg);
	printf("--------------------------------------\n");
	fd = open(DEVICE_NAME, O_RDWR);
	if(fd < 0)
	{
		perror("::ERROR - opening device");
		exit(-1);
	}
	printf("Enter the buffer size: ");
	scanf("%d",&buffer_size);
	total_size = (buffer_size*sizeof(char)+1);
	buffer = (char *)malloc(total_size);
	memset(buffer,0,total_size);
	printf("Enter the message: \n");
	getchar();
	while( (ch = getchar()) != '\n') buffer[i++] = ch;
	sleep(10);
	write(fd,buffer,total_size);
	sleep(10);
	memset(buffer,0,total_size);
	read(fd,buffer,total_size);
	//sleep(10);
	printf("Data Read from Device -\n");
	printf("%s\n",buffer);

	/********************* IOCTL Related Code **********************/
	/*
	ret = ioctl(fd,PINCHAR_IOCLENGTH,&length);
	if(ret < 0)
	{
		printf("ERROR : Failed to get Length via IOCTL....\n");
	}
	printf("Length of Buffer = %d\n",length);
	
	memset(buffer,0,total_size);
	ret = ioctl(fd,PINCHAR_IOCUPPER,buffer);
	if(ret < 0)
	{
		printf("ERROR : Failed to get Length via IOCTL....\n");
	}
	printf("UPPER Buffer = %s\n",buffer);
	
	ret = ioctl(fd,PINCHAR_IOCEMPTY,buffer);
	if(ret < 0)
	{
		printf("ERROR : Failed to get Length via IOCTL....\n");
	}
	read(fd,buffer,total_size);
	printf("Buffer = %s\n",buffer);
	*/

	/*************** MMAP Related Code ****************/
	/*
	mmap_buffer = mmap(0,total_size,PROT_READ | PROT_WRITE,MAP_FILE | MAP_SHARED,fd,0);
	if(mmap_buffer == MAP_FAILED)
	{
		printf("ERROR : mmap() failed....\n");
		free(buffer);
		close(fd);
		exit(1);
	}
	memset(mmap_buffer,'\0',total_size);
	strncpy(mmap_buffer,msg,sizeof(msg));
	
	memset(buffer,0,total_size);
	strncpy(buffer,mmap_buffer,total_size);
	//mmap_buffer[total_size+1]='\0';
	//buffer[total_size+1]='\0';
	printf("Content Returned by mmap - \n");
	printf("%s\n\n\n",buffer);
	munmap(mmap_buffer,total_size);
	*/
	buffer=NULL;	
	free(buffer);
	close(fd);
}

