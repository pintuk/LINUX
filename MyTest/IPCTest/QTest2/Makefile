
SRCSPATH =.
#CC = /scratchbox/compilers/arm-linux-gnueabi-gcc4.4.1-glibc2.11.1/bin/arm-none-linux-gnueabi-gcc
CC = gcc

INCLUDEDIR = -I.

#CCFLAGS = $(INCLUDEDIR) -Wall -O2 -g -fomit-frame-pointer -lstdc++ -pthread
CCFLAGS = $(INCLUDEDIR) -g

#LIB = ./libcdrengine.so

all : Quser1 Quser2
clean:
	rm -f *.o *~ *.out

Quser1 : Quser1.c
	$(CC) -o Quser1.out Quser1.c IPCMsgQ.c $(CCFLAGS)


Quser2 : Quser2.c
	$(CC) -o Quser2.out Quser2.c IPCMsgQ.c $(CCFLAGS)


