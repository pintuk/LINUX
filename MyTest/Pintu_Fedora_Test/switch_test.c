#include<stdio.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef enum Codec
{
	VIDEO_CODEC_NONE,
	VIDEO_CODEC_MPEG4_SP,
	VIDEO_CODEC_MPEG4_SP_SVH,
	VIDEO_CODEC_H263_P0,
	VIDEO_CODEC_H263_P3,
	VIDEO_CODEC_H264_BP,
}video_codec_type;


BOOL IsSupportedEncoder(video_codec_type type)
{
    switch(type)
    {
		case VIDEO_CODEC_NONE:
			printf("codec type - NONE\n");
			return FALSE;
	    case VIDEO_CODEC_MPEG4_SP:
			printf("codec type - MPEG4_SP\n");
	        return TRUE;
	    case VIDEO_CODEC_MPEG4_SP_SVH:
	    case VIDEO_CODEC_H263_P0:
	    case VIDEO_CODEC_H263_P3:
	    case VIDEO_CODEC_H264_BP:
			printf("codec type - MPEG4_SP_SVH,H263P0,H263P3,H264BP\n");
	        return FALSE;
	    default:
	        printf("default - Not supported codec\n");
	        return FALSE;
    }

    return TRUE;
}


main()
{
	BOOL x = 0; int i = 0;

	printf("Supported Codec type :-\n");
	printf("----------------------------\n");
	printf(" 0. VIDEO_CODEC_NONE\n");
	printf(" 1. VIDEO_CODEC_MPEG4_SP\n");
	printf(" 2. VIDEO_CODEC_MPEG4_SP_SVH\n");
	printf(" 3. VIDEO_CODEC_H263_P0\n");
	printf(" 4. VIDEO_CODEC_H263_P3\n");
	printf(" 5. VIDEO_CODEC_H264_BP\n");
	printf("----------------------------\n");

	printf("Enter the value of i = ");
	scanf("%d",&i);
	x = IsSupportedEncoder(i);
	printf("return x = %d\n",x);
}

