#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char VideoCodecOrder[] = "H264";


main()
{
	char *ptr = NULL;

	ptr = 
		VideoCodecOrder;

	if(VideoCodecOrder)
	{
		ptr=strtok(VideoCodecOrder,",");
		while(ptr != NULL)
		{
			printf("%s\n",ptr);
			ptr = strtok(NULL,",");
			//if(ptr == NULL) break;
		}
	}
}

