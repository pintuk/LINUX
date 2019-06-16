
SRCSPATH =.
#CC = /scratchbox/compilers/arm-linux-gnueabi-gcc4.4.1-glibc2.11.1/bin/arm-none-linux-gnueabi-gcc
CC = gcc

INCLUDEDIR = -I.

#CCFLAGS = $(INCLUDEDIR) -Wall -O2 -g -fomit-frame-pointer -lstdc++ -pthread
CCFLAGS = $(INCLUDEDIR) -g

#LIB = ./libcdrengine.so

all : user1 user2
clean:
	rm -f *.o *~ *.out

user1 : msguser1.c
	$(CC) -o  msguser1.out  msguser1.c ipcmsgq.c $(CCFLAGS)


user2 :  msguser2.c
	$(CC) -o  msguser2.out  msguser2.c ipcmsgq.c $(CCFLAGS)


