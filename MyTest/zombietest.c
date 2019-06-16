#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>

main()
{
	pid_t pid;

	pid = fork();
	if(pid < 0)
	{
		perror("fork() failed....\n");
		exit(-1);
	}
	if(pid != 0)
	{
		printf("Parent....\n");
		sleep(100);
		//waitforpid(0);
		//while(1);
	}
	else
	{
		printf("Child....\n");
		sleep(30);
		printf("child exited...\n");
		exit(0);
	}
	printf("DONE.....\n");
}
