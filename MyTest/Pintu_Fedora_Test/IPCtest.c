#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<fcntl.h>


#define	TRUE	1
#define FALSE	0

typedef int BOOL;


BOOL OpenIPCChannel()
{
}





void close_serial(int fp)
{
	if (fp<0)
		return;

	if (tcsetattr(fp, TCSAFLUSH, &serial_old) < 0)
		perror("tcsetattr");

	close(fp);
}


int open_serial(char *dev, char*baudr, char*par, char*bits, char*stop, int hwf, int swf)
{
	int fp = open(dev, O_RDWR);

	if (fp < 0) 
	{
		perror(dev);
		return -1;
	}
	if (m_setparms(fp, baudr, par, bits, stop, hwf, swf) < 0) 
	{
		close(fp);
		return -1;
	}
	return fp;
}


