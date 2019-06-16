
#include<sys/types.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <fcntl.h>
#include<string.h>

#define	DEVNAME		"/dev/pinchar"

static int fd = -1;

char buf[50] = "Hello\n";

void *InsideThread(void *arg)
{
	fd_set fds;
	struct timeval tv;
	int r;

	while(1)
	{
		FD_ZERO (&fds);
		FD_SET (fd, &fds);
		char buffer[50] = {0};

		tv.tv_sec = 0;
		tv.tv_usec = 500 * 1000;		// 500 msec

		printf("select waiting.....(500ms)\n");
		memset(buffer,0,sizeof(buffer));
		r = select (fd + 1, &fds, NULL, NULL, &tv);

		if(r > 0)
		{
			if(FD_ISSET(fd, &fds))
			{
				printf("OK ---> FD is set now...\n");
				read(fd, buffer, 50);
				printf("Buffer = %s\n",buffer);
				sleep(1);
				FD_CLR(fd, &fds);
				close(fd);
				//break;
				
			}
		}
		else if (0 == r)
		{
			printf("select timeout....\n");
			break;
		}
		else
		{
			printf("select....Error, timout = %d\n", tv.tv_usec / 1E3);
			break;
		}
		
	}
	printf("Done....!\n");
}



main()
{
	//char buf[50] = "Hello\n";
	pthread_t th1;
	fd = open (DEVNAME, O_RDWR /* required */ | O_NONBLOCK , 0);
	if (-1 == fd)
	{
		perror("fd open failed");
		exit(0);
	}

	pthread_create(&th1,NULL,&InsideThread,NULL);
	printf("----- Main - Thread -------\n");
	write(fd, buf, sizeof(buf));
	//close(fd);
	//InsideThread();

	read(fd, buf, sizeof(buf));
	sleep(2);
	//pthread_cancel(th1);
	//close(fd);
	//fd = -1;
	printf("fd is closed......\n");

	sleep(5);

	pthread_join(th1,NULL);

	printf("main...done\n");
}













