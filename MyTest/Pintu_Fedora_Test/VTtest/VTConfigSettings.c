#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "h324mConfig.h"
#include "h324mCommon.h"
#include "h324mSetting.h"



#define H324M_CONFIG_FILENAME	"VTConfig.cfg"
#define TOTAL_CODEC_TYPE	13

FILE *fp = NULL;

#ifdef VT_CONFIG_FILE_ENABLED
void Initialize_VTStack_ConfigParams();
#endif

/*
const char *configCodecType[] = {
	"SUPPORT_VIDEO_CODEC_NONE",
	"SUPPORT_VIDEO_CODEC_MPEG4_SP",
	"SUPPORT_VIDEO_CODEC_MPEG4_ASP",
	"SUPPORT_VIDEO_CODEC_MPEG4_SP_SVH",
	"SUPPORT_VIDEO_CODEC_H263_P0",
	"SUPPORT_VIDEO_CODEC_H263_P3",
	"SUPPORT_VIDEO_CODEC_H264_BP",
	"SUPPORT_AUDIO_CODEC_NONE",
	"SUPPORT_AUDIO_CODEC_G723_1",
	"SUPPORT_AUDIO_CODEC_AMR_NB",
	"SUPPORT_AUDIO_CODEC_AAC",
	"SUPPORT_AUDIO_CODEC_MP3",
	"SUPPORT_AUDIO_CODEC_OGG",
};
*/


int IsH263Profile3Supported()
{
	char strvalue[80] = {0};

	if(ReadConfigValue(strvalue, "SUPPORT_H263_PROFILE_3"))
	{
		if(strvalue != NULL)
		{
			if( atoi(strvalue) == 1) 
			{
				return 1;
			}
			else if( atoi(strvalue) == 0)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}

int GetPreferredVideoCodecType()
{
	char strvalue[80] = {0};

	if(ReadConfigValue(strvalue, "PREFERRED_VIDEO_CODEC_TYPE"))
	{
		if(strvalue != NULL)
		{
			if(strstr(strvalue, "MPEG4"))
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_VIDEO_MPEG4;
			}
			else if(strstr(strvalue, "H264"))
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_VIDEO_H264;
			}
			else if(strstr(strvalue, "H263"))
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_VIDEO_H263;
			}
			else
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_INVALID; 
			}
		}
	}
	return H324M_CODEC_NONE;
}


int GetPreferredAudioCodecType()
{
	char strvalue[80] = {0};

	if(ReadConfigValue(strvalue, "PREFERRED_AUDIO_CODEC_TYPE"))
	{
		if(strvalue != NULL)
		{
			if(strstr(strvalue, "AMR"))
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_AUDIO_AMR;
			}
			else if(strstr(strvalue, "G723_1"))
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_AUDIO_G723_1;
			}
			/*
			else if(strstr(strvalue, "MP3"))
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_AUDIO_MP3;
			}
			*/
			else
			{
				printf("strValue = %s\n",strvalue);
				return H324M_CODEC_INVALID; 
			}
		}
	}
	return H324M_CODEC_NONE;
}

int ReadConfigValue(char *cfgValue, const char *cfgParam)
{
	char strcfg[80] = {0}; char *ptrequal = NULL;
	int lineLen = 0;

	rewind(fp);
	while( !feof(fp) )
	{
		memset(strcfg, 0, sizeof(strcfg));
		fgets(strcfg, 80, fp);
		if(strcfg[0] == '#') continue;
		lineLen = strlen(strcfg) - 1;
		strcfg[lineLen] = 0;
		if( strstr(strcfg, cfgParam) )
		{
			ptrequal = strchr(strcfg, '=');
			if( ptrequal )
			{
				//strcpy(cfgValue, &strcfg[lineLen-1]);
				strcpy(cfgValue, (++ptrequal));
				return(1);
			}
		}
	}
	return(0);
}


main(int argc, char *argv[])
{
	char *cfgfilename = NULL;
	char cfgValue[80] = {0};
	int preferVCodec = -1; int preferACodec = -1;
	int i = 0;
	
	fp = fopen(H324M_CONFIG_FILENAME, "r");
	if(fp == NULL)
	{
		perror(": cannot open file - \n");
		exit(0);
	}

#ifdef VT_CONFIG_FILE_ENABLED
	Initialize_VTStack_ConfigParams();
	/***********************************************/
	printf("****************************************************\n");
	printf("TerminalType                 = %d\n",VTStackConfigParams.terminalType);
	
	printf("Num of Video Codec           = %d\n",VTStackConfigParams.supportedVCodecNum);
	printf("VideoCodec[0]                = %d\n",VTStackConfigParams.supportedVCodecs[0]);
	printf("VideoCodec[1]                = %d\n",VTStackConfigParams.supportedVCodecs[1]);
	printf("VideoCodec[2]                = %d\n",VTStackConfigParams.supportedVCodecs[2]);
	
	printf("Num of Audio Codec           = %d\n",VTStackConfigParams.supportedACodecNum);
	printf("AudioCodec[0]                = %d\n",VTStackConfigParams.supportedACodecs[0]);
	printf("AudioCodec[1]                = %d\n",VTStackConfigParams.supportedACodecs[1]);
	
	printf("VideoChannel OLC Type        = %d\n",VTStackConfigParams.VideoChannel.OLCType);
	printf("VideoChannel CodecRestrict   = %d\n",VTStackConfigParams.VideoChannel.Codec_restrict);
	printf("VideoChannel WithAL1         = %d\n",VTStackConfigParams.VideoChannel.WithAL1);
	printf("VideoChannel WithAL2         = %d\n",VTStackConfigParams.VideoChannel.WithAL2);
	printf("VideoChannel WithAL3         = %d\n",VTStackConfigParams.VideoChannel.WithAL3);
	
	printf("AudioChannel OLC Type        = %d\n",VTStackConfigParams.AudioChannel.OLCType);
	printf("AudioChannel CodecRestrict   = %d\n",VTStackConfigParams.AudioChannel.Codec_restrict);
	printf("AudioChannel WithAL1         = %d\n",VTStackConfigParams.AudioChannel.WithAL1);
	printf("AudioChannel WithAL2         = %d\n",VTStackConfigParams.AudioChannel.WithAL2);
	printf("AudioChannel WithAL3         = %d\n",VTStackConfigParams.AudioChannel.WithAL3);

	printf("Vendor Info Send             = %d\n",VTStackConfigParams.vendor_info.bSendVendorInfo);
	printf("Vendor Info Product          = %s\n",VTStackConfigParams.vendor_info.Product);
	printf("Vendor Info Version          = %s\n",VTStackConfigParams.vendor_info.Version);
	
	printf("Debug Setting - LogH245Msg   = %d\n",VTStackConfigParams.DebugSetting.bLogH245Msg);
	printf("Debug Setting - LogVideoData = %d\n",VTStackConfigParams.DebugSetting.bLogVideoData);
	printf("Debug Setting - LogAudioData = %d\n",VTStackConfigParams.DebugSetting.bLogAudioData);
	printf("Debug Setting - LogLogMsg    = %d\n",VTStackConfigParams.DebugSetting.bLogLogMsg);
	printf("****************************************************\n");
	/***********************************************/
#endif

	/*
	for(i=0; i<TOTAL_CODEC_TYPE; i++)
	{
		if( ReadConfigValue(cfgValue, configCodecType[i]) )
		{
			if(atoi(cfgValue) == 0)
			{
				printf("%s = %d\n",configCodecType[i],atoi(cfgValue));
			}
			else if(atoi(cfgValue) == 1)
			{
				printf("%s = %d\n",configCodecType[i],atoi(cfgValue));
			}
			else
			{
				printf("ERROR : %s - Not Found !!!\n",configCodecType[i]);
			}
		}
	}
	printf("\n");
	preferVCodec = GetPreferredVideoCodecType();
	printf("Preferred Video Codec Type = %d\n",preferVCodec);
	preferACodec = GetPreferredAudioCodecType();
	printf("Preferred Audio Codec Type = %d\n",preferACodec);
	*/
	/*
	if( IsH263Profile3Supported() )
	{
		printf("SUPPORT_H263_PROFILE_3 - is Supported !!!\n");
	}
	else
	{
		printf("SUPPORT_H263_PROFILE_3 - NOT Supported !!!\n");
	}
	*/
//#define SUPPORT_H263_PROFILE_3 (IsH263Profile3Supported() == 1) ? 1 : 0

#ifdef SUPPORT_H263_PROFILE_3	
if (SUPPORT_H263_PROFILE_3)
{
	printf("SUPPORT_H263_PROFILE_3 - is Supported !!!\n");
}
#endif

printf("H324M_H245_T106_MSDSE_TIMER = %d\n",H324M_H245_T106_MSDSE_TIMER);
printf("H324M_H245_T101_CESE_TIMER = %d\n",H324M_H245_T101_CESE_TIMER);
printf("H324M_H245_T103_LCSE_TIMER = %d\n",H324M_H245_T103_LCSE_TIMER);
printf("H324M_H245_T108_CLCSE_TIMER = %s\n",H324M_H245_T108_CLCSE_TIMER);
printf("H324M_H245_T104_MTSE_TIMER = %d\n",H324M_H245_T104_MTSE_TIMER);
printf("H324M_H245_T109_MRSE_TIMER = %d\n",H324M_H245_T109_MRSE_TIMER);
printf("H324M_H245_T105_RTDSE_TIMER = %d\n",H324M_H245_T105_RTDSE_TIMER);
printf("H324M_T401_WNSRP_NSRP_TRANSMIT_TIMER = %d\n",H324M_T401_WNSRP_NSRP_TRANSMIT_TIMER);
printf("H324M_H245_N100_MSDSE_COUNTER = %d\n",H324M_H245_N100_MSDSE_COUNTER);
printf("H324M_N400_SRP_TRANSMIT_COUNTER = %d\n",H324M_N400_SRP_TRANSMIT_COUNTER);
printf("H324M_N402_WNSRP_MODE_COUNTER = %d\n",H324M_N402_WNSRP_MODE_COUNTER);
printf("MDX_LEVEL_SYNC_PACKET_SEND_INTERVAL = %d\n",MDX_LEVEL_SYNC_PACKET_SEND_INTERVAL);
printf("H324M_SESSION_TIMEOUT = %d\n",H324M_SESSION_TIMEOUT);
printf("H324M_2WAY_COMM_ESTABLISHMENT_TIMEOUT = %d\n",H324M_2WAY_COMM_ESTABLISHMENT_TIMEOUT);

fclose(fp);

}




