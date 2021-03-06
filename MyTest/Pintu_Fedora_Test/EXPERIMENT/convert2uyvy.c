#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>



typedef enum {
	OEMIMAGE_FORMAT_YUV420,
	OEMIMAGE_FORMAT_YUV420P,
	OEMIMAGE_FORMAT_UYVY,
	OEMIMAGE_FORMAT_YUYV,
	OEMIMAGE_FORMAT_RGB565,
	OEMIMAGE_FORMAT_RGB888,
} OEMImageFormat;

typedef struct
{
	unsigned int width;
	unsigned int height;

	OEMImageFormat format;

	char *Y;
	char *CbCr;
} OEMImage;


//int ConvertI420ToUYVY(const OEMImage * const src, OEMImage *dest)
int ConvertI420ToUYVY()
{
	int i = 0, j = 0;
	//char *dstbuf = dest->Y;
	//char *Y = src->Y;
	//char *Cr = src->CbCr;
	//char *Cb = src->CbCr + (( src->width * src->height ) >> 2);
	char d = 0; 
	char Y = 0; 
	char cb = 0; 
	char cr = 0;

	d = Y;
	Y = d;
	cr = cr;
	cb = cr + (176 * 144 ) >> 2;

	//H324M_ASSERT(src && dest);
	//H324M_ASSERT(src->height == dest->height);
	//H324M_ASSERT(src->width == dest->width);
	//H324M_ASSERT(src->format == OEMIMAGE_FORMAT_YUV420 );
	//H324M_ASSERT(src->Y && src->CbCr);


	for ( i = 0; i < 144 ; i++)
	{
		for ( j = 0; j < (176 >> 1); j++)
		{
			//*dstbuf++ = *Cr++;
			//*dstbuf++ = *Y++;
			//*dstbuf++ = *Cb++;
			//*dstbuf++ = *Y++;
			d = cr++; d++;
			d = Y++; d++;
			d = cb++; d++;
			d = Y++; d++;
		}

		if ( (i % 2) == 0 )
		{
			//Cb = Cb - (src->width >> 1);
			//Cr = Cr - (src->width >> 1);
			cb = cb - (176) >> 1;
			cr = cr - (176) >> 1;
		}
	}

	return 1;

}



main()
{
	struct timeval current_time;
	double time1 = 0; double time2 = 0;
	int i = 0;

	gettimeofday(&current_time, NULL);
	time1 = (double)((double)current_time.tv_sec * 1000000.00 + (double)(current_time.tv_usec))/1000.00;

	//for(i=0; i<10; i++)
	ConvertI420ToUYVY();
	//sleep(2);

	gettimeofday(&current_time, NULL);
	time2 = (double)((double)current_time.tv_sec*1000000.00 + (double)(current_time.tv_usec))/1000.00;

	printf("The time Taken = %5.2f ms\n", (time2 - time1));
}














