#ifndef __H324M_CONFIG_H
#define __H324M_CONFIG_H


#define TRUE	1
#define FALSE	0

typedef int BOOL;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;


int IsH263Profile3Supported();
int ReadConfigValue(char *, const char *);
static char strV[80] = {0};


#define VT_CONFIG_FILE_ENABLED

#ifndef SUPPORT_H263_PROFILE_3
#define SUPPORT_H263_PROFILE_3 (IsH263Profile3Supported()==1) ? 1 : 0
#endif


#endif

																								   
