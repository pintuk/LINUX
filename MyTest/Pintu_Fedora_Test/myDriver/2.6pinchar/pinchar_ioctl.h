
#ifndef _PINCHAR_IOCTL_H
#define _PINCHAR_IOCTL_H

#include<linux/ioctl.h>

#define PINCHAR_MAGIC	'p'

#define PINCHAR_IOCLENGTH	_IOR(PINCHAR_MAGIC, 1, int)
#define PINCHAR_IOCUPPER	_IOWR(PINCHAR_MAGIC, 2, char *)
#define PINCHAR_IOCEMPTY	_IOW(PINCHAR_MAGIC, 3, char *)

#endif
