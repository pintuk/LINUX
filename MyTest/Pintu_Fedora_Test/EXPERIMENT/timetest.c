#include<stdio.h>
#include<time.h>
#include<sys/time.h>


main()
{
	int remain_ms;

	remain_ms = -19;

	if(remain_ms < -200)
	{
		printf("remain_ms = %d\n",remain_ms);
	}
}

