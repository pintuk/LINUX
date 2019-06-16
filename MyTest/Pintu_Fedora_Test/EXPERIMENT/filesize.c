#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


main()
{
	int filesize = 0;

	struct stat		s;	

	stat("opentest.raw", &s);

	filesize = s.st_size;

	printf("file size = %d\n",filesize);
}


