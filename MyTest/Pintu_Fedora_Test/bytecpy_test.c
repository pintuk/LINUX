
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


main()
{
	unsigned char *pktdata = (unsigned char *)0x469e7d0f;
	unsigned char hbuf[1024] = {0x00,};
	unsigned char wrtbuf[1024] = {0x00};

	printf("pktdata = 0x%x\n",pktdata);
	memset(hbuf,0x00,sizeof(hbuf));	
	hbuf[0] = 1;
	hbuf[1] = (unsigned char *)pktdata;
	//memcpy(&hbuf[1],(unsigned char *)pktdata,1);
	printf("After memcpy - hbuf[0] = 0x%x, hbuf[1] = 0x%x, hbuf[2] = 0x%x\n",hbuf[0],hbuf[1],hbuf[2]);
	memset(wrtbuf,0x00,sizeof(wrtbuf));
	memcpy(wrtbuf,hbuf,2);
	printf("wrtbuf[0] = 0x%x, wrtbuf[1] = 0x%x, wrtbuf[2] = 0x%x\n",wrtbuf[0],wrtbuf[1],wrtbuf[2]);

	printf("write buf = 0x%x\n",wrtbuf);
}
