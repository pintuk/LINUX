#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_LIST 4

char *InputFileList[] = {
	"File1.txt",
	"File2.txt",
	"File3.txt",
	NULL
};

typedef struct PreviewWindowProperties
{
	int Height;
	int Width;
	int xpos;
	int ypos;
}s_PreviewWindowProperties;


s_PreviewWindowProperties ThumbNailInfo[] = {
	{10, 10, 10, 10},
	{20, 20, 20, 20},
	{30, 30, 30, 30},
	{40, 40, 40, 40},
	{0}
};

s_PreviewWindowProperties winprops = {10, 20, 50, 100};


typedef enum
{
	EnMPAPP_INVALID			= 0,
	EnMPAPP_FrameSnapshot 	= 0x1,
	EnMPAPP_VisualSeek		= 0x2,
	EnMPAPP_TrickPlay		= 0x4,
	EnMPAPP_VideoMagnifier	= 0x8,
	EnMPAPP_VideoZoom		= 0x10,
	EnMPAPP_VideoCatalogue	= 0x20,
	EnMPAPP_VideoGrid		= 0x40,
	EnMPAPP_MaxLimit		= 0x80
}e_EnMP_APP_ID;


typedef struct
{
	int x;
	int y;
}XY;

typedef struct
{
	int a;
	int b;
}AB;


XY initxy = {10, 20};
AB initab = {100, 200};


typedef struct
{
	e_EnMP_APP_ID featureName;
	void *featureData;
}s_FeatureList;


void ProcessFile(char **plist)
{
	while(*plist != NULL)
	{
		printf("FILE - %s\n",*plist);
		plist++;
	}
}


void DisplayProperty(s_PreviewWindowProperties *wprop)
{
	if(wprop)
	{
		printf("Win height - %d\n", wprop->Height);
		printf("Win height - %d\n", wprop->Width);
		printf("Win height - %d\n", wprop->xpos);
		printf("Win height - %d\n", wprop->ypos);
	}
}


void DisplayFeature(s_FeatureList *feature)
{

	if(feature->featureName == EnMPAPP_VideoGrid)
	{
		XY *xy = (XY *)feature->featureData;

		printf("Feature Name = 0x%x\n",feature->featureName);
		printf("XY - x = %d\n",xy->x);
		printf("XY - y = %d\n",xy->y);
	}
	else
	{
		AB *ab = (AB *)feature->featureData;

		printf("Feature Name = 0x%x\n",feature->featureName);
		printf("AB - a = %d\n",ab->a);
		printf("AB - b = %d\n",ab->b);
	}
}


main()
{
	int i = 0;
	char **ppList = (char **)InputFileList;

	s_FeatureList featureList;

	
	//s_PreviewWindowProperties **pThumbNailInfo = (s_PreviewWindowProperties *)ThumbNailInfo;
	//s_PreviewWindowProperties **pThumbNailInfo = NULL;

#if 0
	pThumbNailInfo = (s_PreviewWindowProperties **)malloc(sizeof(s_PreviewWindowProperties *)*4);
	for(i=0; i<4; i++)
	{
		pThumbNailInfo[i] = (s_PreviewWindowProperties *)malloc(sizeof(s_PreviewWindowProperties));
		(pThumbNailInfo[i])->Width = ThumbNailInfo[i].Width;
		(pThumbNailInfo[i])->Height = ThumbNailInfo[i].Height;
		(pThumbNailInfo[i])->xpos = ThumbNailInfo[i].xpos;
		(pThumbNailInfo[i])->ypos = ThumbNailInfo[i].ypos;
	}
#endif
	
	//ppList = (char **)malloc(sizeof(char *)*MAX_LIST);

	//for(i=0; i<MAX_LIST; i++)
	while(*ppList != NULL)
	{
		//ppList[i] = (char *)InputFileList[i];
		printf("ppList - %s\n",*ppList);
		ppList++;
	}
	printf("------------------------\n");

	i=0;
	//while(i<4)
	{
		//printf("W - %d\n", (pThumbNailInfo[i])->Width);
		//printf("H - %d\n", (pThumbNailInfo[i])->Height);
		//printf("X - %d\n", (pThumbNailInfo[i])->xpos);
		//printf("Y - %d\n", (pThumbNailInfo[i])->ypos);
		//printf("\n");
		//pThumbNailInfo++; i++;
	}
	printf("\n");
	//ProcessFile(InputFileList);
	printf("=======================\n");
	//DisplayProperty(&winprops);
	//free(ppList);
	//ppList = NULL;

	memset(&featureList, 0, sizeof(s_FeatureList));
	
	featureList.featureName = 0; //EnMPAPP_VideoGrid;
	featureList.featureData = (AB *)malloc(sizeof(AB));
	//featureList.featureData = (void *)initxy;
	memcpy(featureList.featureData, &initab, sizeof(AB));

	//xy = (XY *)featureList.featureData;
	DisplayFeature(&featureList);
}









