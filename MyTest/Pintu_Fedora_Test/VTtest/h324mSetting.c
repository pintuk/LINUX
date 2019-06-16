#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "h324mConfig.h"
#include "h324mCommon.h"
#include "h324mSetting.h"


#ifdef VT_CONFIG_FILE_ENABLED
/***************************************************************/
/***************************************************************/
#endif


#ifdef VT_CONFIG_FILE_ENABLED
vtstack_h324_default_setting VTStackConfigParams;

void Initialize_VTStack_ConfigParams()
{
	char strValue[80] = {0};
	char *preferredVcodec = NULL;
	char *preferredAcodec = NULL;

	memset(strValue, 0, sizeof(strValue));
	memset(&VTStackConfigParams, 0, sizeof(vtstack_h324_default_setting));
	if(ReadConfigValue(strValue, "VT_TERMINAL_TYPE"))
	{
		if(strValue)
		{
			if(strcasecmp(strValue,"DEFAULT")==0)
			{
				VTStackConfigParams.terminalType = VT_TERMINAL_TYPE_DEFAULT;
			}
			else if(strcasecmp(strValue,"MASTER")==0)
			{
				VTStackConfigParams.terminalType = VT_TERMINAL_TYPE_MASTER;
			}
			else if(strcasecmp(strValue,"SLAVE")==0)
			{
				VTStackConfigParams.terminalType = VT_TERMINAL_TYPE_SLAVE;
			}
			else
			{
				VTStackConfigParams.terminalType = -1; //NONE
			}
		}
	}
	memset(strValue, 0, sizeof(strValue));
	VTStackConfigParams.supportedVCodecNum = 
		(ReadConfigValue(strValue, "NUMBER_OF_VIDEO_CODEC_SUPPORTED")==1) ? atoi(strValue) : 0;

	VTStackConfigParams.supportedVCodecs[0] = GetPreferredVideoCodecType();
	memset(strValue, 0, sizeof(strValue));
	preferredVcodec = (ReadConfigValue(strValue, "SUPPORTED_VIDEO_CODEC_ORDER")==1) ? strValue : NULL;
	if(preferredVcodec != NULL)
	{
		char *ptrVcodec = NULL;
		int i = 0;
		
		ptrVcodec = strtok(preferredVcodec, ",");
		while(ptrVcodec != NULL)
		{
			if(i <= VTStackConfigParams.supportedVCodecNum)
			{
				if(strcasecmp(ptrVcodec,"H264") == 0)
				{
					VTStackConfigParams.supportedVCodecs[i++] = H324M_CODEC_VIDEO_H264;
				}
				else if(strcasecmp(ptrVcodec,"MPEG4") == 0)
				{
					VTStackConfigParams.supportedVCodecs[i++] = H324M_CODEC_VIDEO_MPEG4;
				}
				else if(strcasecmp(ptrVcodec,"H263") == 0)
				{
					VTStackConfigParams.supportedVCodecs[i++] = H324M_CODEC_VIDEO_H263;
				}
				else
				{
					VTStackConfigParams.supportedVCodecs[i++] = H324M_CODEC_INVALID;
				}
			}
			ptrVcodec = strtok(NULL, ",");
		}
	}
	memset(strValue, 0, sizeof(strValue));
	VTStackConfigParams.supportedACodecNum = 
		(ReadConfigValue(strValue, "NUMBER_OF_AUDIO_CODEC_SUPPORTED")==1) ? atoi(strValue) : 0;

	VTStackConfigParams.supportedACodecs[0] = GetPreferredAudioCodecType();
	memset(strValue, 0, sizeof(strValue));
	preferredAcodec = (ReadConfigValue(strValue, "SUPPORTED_AUDIO_CODEC_ORDER")==1) ? strValue : NULL;
	if(preferredAcodec != NULL)
	{
		char *ptrAcodec = NULL;
		int i = 0;
		
		ptrAcodec = strtok(preferredAcodec, ",");
		while(ptrAcodec != NULL)
		{
			if(i <= VTStackConfigParams.supportedACodecNum)
			{
				if(strcasecmp(ptrAcodec,"AMR") == 0)
				{
					VTStackConfigParams.supportedACodecs[i++] = H324M_CODEC_AUDIO_AMR;
				}
				else if(strcasecmp(ptrAcodec,"G723_1") == 0)
				{
					VTStackConfigParams.supportedACodecs[i++] = H324M_CODEC_AUDIO_G723_1;
				}
				else
				{
					VTStackConfigParams.supportedACodecs[i++] = H324M_CODEC_INVALID;
				}
			}
			ptrAcodec = strtok(NULL, ",");
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VIDEO_CHANNEL_OLC_TYPE"))
	{
		if(strValue)
		{
			if(strcasecmp(strValue,"UNI")==0)
			{
				VTStackConfigParams.VideoChannel.OLCType = OLC_TYPE_UNI;
			}
			else if(strcasecmp(strValue,"BI")==0)
			{
				VTStackConfigParams.VideoChannel.OLCType = OLC_TYPE_BI;
			}
			else
			{
				VTStackConfigParams.VideoChannel.OLCType = -1;  //NONE
			}
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VIDEO_CHANNEL_CODECRESTRICT"))
	{
		if(strValue)
		{
			if(strcasecmp(strValue,"ASYMMETRIC")==0)
			{
				VTStackConfigParams.VideoChannel.Codec_restrict = ASYMMETRIC_CODECS_SUPPORT;
			}
			else if(strcasecmp(strValue,"SYMMETRIC")==0)
			{
				VTStackConfigParams.VideoChannel.Codec_restrict = SYMMETRIC_CODECS_SUPPORT;
			}
			else
			{
				VTStackConfigParams.VideoChannel.Codec_restrict = -1;  //NONE
			}
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VIDEO_CHANNEL_AL1"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.VideoChannel.WithAL1 = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.VideoChannel.WithAL1 = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VIDEO_CHANNEL_AL2"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.VideoChannel.WithAL2 = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.VideoChannel.WithAL2 = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VIDEO_CHANNEL_AL3"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.VideoChannel.WithAL3 = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.VideoChannel.WithAL3 = FALSE;
		}
	}
	/************** Audio Channel **************** */
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "AUDIO_CHANNEL_OLC_TYPE"))
	{
		if(strValue)
		{
			if(strcasecmp(strValue,"UNI")==0)
			{
				VTStackConfigParams.AudioChannel.OLCType = OLC_TYPE_UNI;
			}
			else if(strcasecmp(strValue,"BI")==0)
			{
				VTStackConfigParams.AudioChannel.OLCType = OLC_TYPE_BI;
			}
			else
			{
				VTStackConfigParams.AudioChannel.OLCType = -1;  //NONE
			}
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "AUDIO_CHANNEL_CODECRESTRICT"))
	{
		if(strValue)
		{
			if(strcasecmp(strValue,"ASYMMETRIC")==0)
			{
				VTStackConfigParams.AudioChannel.Codec_restrict = ASYMMETRIC_CODECS_SUPPORT;
			}
			else if(strcasecmp(strValue,"SYMMETRIC")==0)
			{
				VTStackConfigParams.AudioChannel.Codec_restrict = SYMMETRIC_CODECS_SUPPORT;
			}
			else
			{
				VTStackConfigParams.AudioChannel.Codec_restrict = -1;  //NONE
			}
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "AUDIO_CHANNEL_AL1"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.AudioChannel.WithAL1 = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.AudioChannel.WithAL1 = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "AUDIO_CHANNEL_AL2"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.AudioChannel.WithAL2 = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.AudioChannel.WithAL2 = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "AUDIO_CHANNEL_AL3"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.AudioChannel.WithAL3 = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.AudioChannel.WithAL3 = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VENDOR_INFO_SEND_INFO"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.vendor_info.bSendVendorInfo = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.vendor_info.bSendVendorInfo = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VENDOR_INFO_PRODUCT"))
	{
		if(strValue)
		{
			memcpy(VTStackConfigParams.vendor_info.Product, 
					strValue, sizeof(VTStackConfigParams.vendor_info.Product));
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "VENDOR_INFO_VERSION"))
	{
		if(strValue)
		{
			memcpy(VTStackConfigParams.vendor_info.Version, 
					strValue, sizeof(VTStackConfigParams.vendor_info.Version));
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "DEBUG_LOG_H245_MSG"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.DebugSetting.bLogH245Msg = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.DebugSetting.bLogH245Msg = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "DEBUG_LOG_VIDEO_DATA"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.DebugSetting.bLogVideoData = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.DebugSetting.bLogVideoData = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "DEBUG_LOG_AUDIO_DATA"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.DebugSetting.bLogAudioData = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.DebugSetting.bLogAudioData = FALSE;
		}
	}
	memset(strValue, 0, sizeof(strValue));
	if(ReadConfigValue(strValue, "DEBUG_LOG_LOGMSG"))
	{
		if(atoi(strValue) == 1)
		{
			VTStackConfigParams.DebugSetting.bLogLogMsg = TRUE;
		}
		else if(atoi(strValue) == 0)
		{
			VTStackConfigParams.DebugSetting.bLogLogMsg = FALSE;
		}
	}
	/********************************************* */
}
#else
vtstack_h324_default_setting VTStackConfigParams = 
{
	VT_TERMINAL_TYPE_DEFAULT,  				// terminalType

	3,	// Number of supported Video Codec
	{	//supported Video codecs List  in order of preference- supportedVCodecs
		H324M_CODEC_VIDEO_H264,			
		H324M_CODEC_VIDEO_MPEG4,  
		H324M_CODEC_VIDEO_H263,		
	},	 

	1,	// Number of supported Audio Codec
	{	//supported Audio Codecs List in order of preference- supportedACodecs
		H324M_CODEC_AUDIO_AMR, 
	},


	{	// Video Logical channel info
		OLC_TYPE_BI,		
		ASYMMETRIC_CODECS_SUPPORT,
		FALSE,
		TRUE,
		TRUE,
	},


	{	// Audio Logical channel info
		OLC_TYPE_UNI,					
		SYMMETRIC_CODECS_SUPPORT,
		FALSE,
		TRUE,
		FALSE,
	},

	{	// Vendor Infomation
		TRUE,
		"i8315",
		"0.5.6",
	},

	{	// Debug Information
		FALSE,
		FALSE,		
		FALSE,
		FALSE,
	},
	
};
#endif

