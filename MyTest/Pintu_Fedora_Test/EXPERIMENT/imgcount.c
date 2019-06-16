#include<stdio.h>



void PutImage()
{
	static int i = 1;
	
	if((i == 1) || (i == 100))
	{
		printf("Send Image............\n");
		i=0;
	}
	i++;
	sleep(1);
}

main()
{
	int imgcount = 0;

	while(1)
	{
#define NO_OF_TIMES_IMAGE_SLEEP_IN_1FPS 10
	if ((imgcount%NO_OF_TIMES_IMAGE_SLEEP_IN_1FPS) == 0)
	{
		imgcount=0;
		PutImage();
	}
	imgcount++;
	printf("img count = %d\n",imgcount);
	}
}


