#include<stdio.h>
#include<stdlib.h>
#include<string.h>


main()
{
	unsigned char wrtbuf[1024] = {0x00};
	unsigned char gbuf[8000] = {0x00};
	unsigned char wrtlen = 0; int gbuflen = 0;

	wrtbuf[0] = 1;
	wrtbuf[1] = 3;
	wrtlen = 0x160;

	gbuf[gbuflen] = wrtbuf[0];
	gbuf[gbuflen+1] = wrtlen >> 8; //(wrtlen & 0xff00);
	gbuf[gbuflen+2] = wrtlen; //(wrtlen & 0x00ff);
	//gbuf[gbuflen+2] = (wrtlen & 0xf0) >> 8;
	memcpy(&gbuf[gbuflen+3],&wrtbuf[1],wrtlen+1);
	printf("gbuf = 0x%x, 0x%x, 0x%x, 0x%x\n",gbuf[0],gbuf[1],gbuf[2],gbuf[3]);
}

