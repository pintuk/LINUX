#include<stdio.h>


int globaldata = 1;


main()
{
	if(fork() == 0)
	{
		printf("child....\n");
		sleep(15);
		printf("globaldata = %d\n",globaldata);
	}
	else
	{
		globaldata = 2;
	}
}

