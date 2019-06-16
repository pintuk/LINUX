#include<stdio.h>

int test1()
{
	static int i = 0;

	i++;
	if(i%5 == 0) 
	{
		return 0;
		i = 0;
	}
	else
	return  1;
}


main()
{
	int r;

	do {
		r == test1();
		printf("r = %d\n",r);
		sleep(1);
	}while(r == -1);
}

