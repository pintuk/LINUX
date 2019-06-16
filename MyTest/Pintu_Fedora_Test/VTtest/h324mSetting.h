
#ifndef __H324MSETTING_H__
#define __H324MSETTING_H__

#include "h324mCommon.h"


typedef enum
{
	VT_TERMINAL_TYPE_MASTER  	= 255 ,
	VT_TERMINAL_TYPE_SLAVE 		= 1 , 
	VT_TERMINAL_TYPE_DEFAULT	= 128 
} VTTerminalType;

typedef enum
{
	OLC_TYPE_UNI = 1,
	OLC_TYPE_BI,
} OLC_Type;

typedef enum 
{
 	ASYMMETRIC_CODECS_SUPPORT,
 	SYMMETRIC_CODECS_SUPPORT,		
} CODECRESTRICT;

typedef struct 
{
	OLC_Type	OLCType;
	CODECRESTRICT Codec_restrict;
	
	BOOL 	WithAL1;
	BOOL 	WithAL2;	
	BOOL 	WithAL3;	

} Logical_channel_setting; 

typedef struct  
{
	BOOL bLogH245Msg;
	BOOL bLogVideoData;
	BOOL bLogAudioData;
	BOOL bLogLogMsg;	
} h324_logging_setting;

typedef struct 
{
	BOOL bSendVendorInfo;
	
	UINT8 Product[40];
	UINT8 Version[40];
} h324_vendor_info;

#define MAX_SUPPORT_CODEC 3

typedef struct  
{
	VTTerminalType terminalType;

	UINT32 supportedVCodecNum;
	H324mVideoCodecType  supportedVCodecs[MAX_SUPPORT_CODEC];
	
	UINT32 supportedACodecNum;
	H324mAudioCodecType supportedACodecs[MAX_SUPPORT_CODEC];
	
	Logical_channel_setting	VideoChannel;
	Logical_channel_setting AudioChannel;

	h324_vendor_info vendor_info;
	
	h324_logging_setting DebugSetting;
} vtstack_h324_default_setting;


/********************************************************************/
#define H324M_H245_T106_MSDSE_TIMER (ReadConfigValue(strV,"H324M_H245_T106_MSDSE_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_T101_CESE_TIMER      (ReadConfigValue(strV,"H324M_H245_T101_CESE_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_T103_LCSE_TIMER      (ReadConfigValue(strV,"H324M_H245_T103_LCSE_TIMER")==1) ? atoi(strV) : 0

#define H324M_H245_T108_CLCSE_TIMER     (ReadConfigValue(strV,"H324M_H245_T108_CLCSE_TIMER")==1) ? strV : 0

#define H324M_H245_T104_MTSE_TIMER      (ReadConfigValue(strV,"H324M_H245_T104_MTSE_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_T109_MRSE_TIMER      (ReadConfigValue(strV,"H324M_H245_T109_MRSE_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_T105_RTDSE_TIMER     (ReadConfigValue(strV,"H324M_H245_T105_RTDSE_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_T107_RMESE_TIMER     (ReadConfigValue(strV,"H324M_H245_T107_RMESE_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_T102_MLSE_TIMER      (ReadConfigValue(strV,"H324M_H245_T102_MLSE_TIMER")==1) ? atoi(strV) : 0

#define H324M_T401_WNSRP_NSRP_TRANSMIT_TIMER    (ReadConfigValue(strV,"H324M_T401_WNSRP_NSRP_TRANSMIT_TIMER")==1) ? atoi(strV) : 0
#define H324M_H245_N100_MSDSE_COUNTER   (ReadConfigValue(strV,"H324M_H245_N100_MSDSE_COUNTER")==1) ? atoi(strV) : 0

#define H324M_N400_SRP_TRANSMIT_COUNTER (ReadConfigValue(strV,"H324M_N400_SRP_TRANSMIT_COUNTER")==1) ? atoi(strV) : 0

#define H324M_N402_WNSRP_MODE_COUNTER   (ReadConfigValue(strV,"H324M_N402_WNSRP_MODE_COUNTER")==1) ? atoi(strV) : 0

// Non-Specifcation Counter & Timer
#define MDX_LEVEL_SYNC_PACKET_SEND_INTERVAL  \
								(ReadConfigValue(strV,"MDX_LEVEL_SYNC_PACKET_SEND_INTERVAL")==1) ? atoi(strV) : 0

#define H324M_SESSION_TIMEOUT   (ReadConfigValue(strV,"H324M_SESSION_TIMEOUT")==1) ? atoi(strV) : 0
#define H324M_2WAY_COMM_ESTABLISHMENT_TIMEOUT \
									(ReadConfigValue(strV,"H324M_2WAY_COMM_ESTABLISHMENT_TIMEOUT")==1) ? atoi(strV) : 0


#define H324M_LOOPBACK_ENABLED  (ReadConfigValue(strV,"H324M_LOOPBACK_ENABLED")==1) ? atoi(strV) : 0
																								   
/********************************************************************/




#ifdef __cplusplus
extern "C" vtstack_h324_default_setting VTStackConfigParams;
#else
extern vtstack_h324_default_setting VTStackConfigParams;
#endif

#endif // __H324MSETTING_H__

