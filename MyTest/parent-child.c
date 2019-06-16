#include<stdio.h>


int globaldata = 1;
int *ptr = NULL;

int main()
{
	if(fork() == 0)
	{
		printf("child process....\n");
		sleep(1);
		globaldata++;
		printf("child globaldata = %d\n",globaldata);
		*ptr = 2;
	}
	else
	{
		printf("parent process....\n");
		globaldata++;
		printf("parent globaldata = %d\n",globaldata);
		*ptr = 1;
	}

	return 0;
}

