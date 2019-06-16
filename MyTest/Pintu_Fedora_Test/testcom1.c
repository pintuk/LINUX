#include <stdio.h>

#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


#define BAUD 	B115200
#define COMPORT 	"/dev/ttyS0"
#define DATABITS 	CS8
#define STOPBITS	1
#define PARITY		0

static char *gbuffer = NULL;

main()
{
	int fd = -1;
	unsigned char buff[255] = {0};
	unsigned char rcvdBuf[255] = {0};
	struct termios oldterm, newterm;
	int bsize = 0;

	close(fd);

	fd=open(COMPORT,O_RDWR);
	if(fd < 0)
	{
		perror("::Opening Error...\n");
		exit(-1);
	}
	printf("opened.....\n");

	tcgetattr(fd,&oldterm);
	newterm.c_cflag = BAUD | CRTSCTS | DATABITS | STOPBITS | PARITY | CLOCAL | CREAD;
	newterm.c_iflag = IGNPAR;
	newterm.c_oflag = 0;
	newterm.c_lflag = 0;
	newterm.c_cc[VMIN] = 1;
	newterm.c_cc[VTIME] = 0;

	tcflush(fd,TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newterm);

	memset(buff,0,sizeof(buff));
	sprintf(buff,"Hello!!!");
	write(fd,buff,sizeof(buff));
	//strcat(buff,"\r\n");
	gbuffer = buff;
	usleep(1000);
	printf("read -----\n");
	while(gbuffer != NULL)
	{
		//bsize = read(fd,buff,255);
		memcpy(rcvdBuf, gbuffer, 255);
		bsize = strlen(gbuffer);
		printf("%s\n",rcvdBuf);
		printf("size = %d\n",bsize);
		gbuffer = NULL;
	}
	tcsetattr(fd,TCSANOW,&oldterm);
	close(fd);
}

