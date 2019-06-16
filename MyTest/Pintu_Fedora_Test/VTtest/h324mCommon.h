#ifndef _H324M_COMMON_H_
#define _H324M_COMMON_H_

// Common header for H.223 and H.245 

#ifdef __cplusplus
extern "C" {
#endif

// Constant
#define MAX_PDU_SIZE			254
#define LCN(num) (num)

typedef enum {
	ST_MGMT_SERVICE = 1,
	ST_CONTROL_SERVICE,
	ST_MEDIA_SERVICE,
	ST_TIMER_SERVICE,
	ST_APP_CONTROL_SERVICE,
	ST_MEDIA_CONTROL_SERVICE,
	ST_MEDIA_DATA_SERVICE, 
	ST_AYSNC_OLC_ADD_MSG,
	ST_RECORD_SERVICE
#if defined(VT_FEATURE_MONA)
	, ST_MONA_SERVICE
#endif
} ServiceTypes;


typedef struct {
	UINT8	serviceType;
	UINT8	sessionID;
	UINT16	msgType;
	UINT32	lcn;
	UINT32	msgLen;
	void	*msgPtr;
} H324mMsg;


typedef enum
{	
	VT_DEVICE_START   				=      0x01,
	VT_DEVICE_STOP,
	VT_DEVICE_MUTE,
	VT_DEVICE_UNMUTE,
}H324mDeviceCntlMSgType;

typedef enum
{
	DL_VIDEO_CRC_OK,
	DL_VIDEO_CRC_ERR,
	DL_VIDEO_CRC_CHK_INVALID_AL,
	DL_VIDEO_CRC_CHK_INVALID_PDU_LEN,
	DL_VIDEO_CRC_CHK_NONE
} al_video_crc_chk_status;

typedef enum
{
	DL_AUDIO_CRC_OK,
	DL_AUDIO_CRC_ERR,
	DL_AUDIO_CRC_CHK_INVALID_AL,
	DL_AUDIO_CRC_CHK_INVALID_PDU_LEN,
	DL_AUDIO_CRC_CHK_NONE
} al_audio_crc_chk_status;

typedef enum
{
	SEQ_NO_CHK_ERR =0,
	SEQ_NO_OK,
	SEQ_NO_SKIP,
	SEQ_NO_DUP
}al_pdu_seq_no_chk_status;


/* Control messages from Modem to PDA */
typedef enum H324mCntlMSgModemToMCTag
{	
	H324M_H223_LVL_SYNC_DONE = 1,
	H324M_NSRP_DATA_IND, 			//Downlink NSRP Data to Application chip
	H324M_VIDEO_DATA_IND, 			//Downlink Video Data to Application chip
	H324M_AUDIO_DATA_IND_DL,		//Uplink Audio Data to Application chip
	H324M_FIFO_KEEP_ALIVE_REQ, 	//For FIFO Debug from Modem TO MC
	H324M_VIDEO_CRC_ERROR_IND, 	// For Indicating the crc error to MC.
	H324M_SEND_I_FRAME, 			// QCOM00002915 - This is sent to MC after flushing the V Q's  ('cos of DSM non-availability), to send I frame
	H324M_CALL_END_IND_DUE_TO_DL_ERR,
#ifdef FEATURE_H324M_SKEW_IND_SUPPORT	
    H324M_FIRST_VIDEO_FRAME_IND,
    H324M_FIRST_AUDIO_FRAME_IND,
#endif       
	H324M_AUDIO_DATA_IND_UL, 		//Downlink Audio Data to Application chip
} H324mCntlMSgModemToMC;

/* Control messages from PDA to Modem */
typedef enum H324mCntlMSgMCToModemTag
{
	H324M_AUDIO_CTRL=0,
	H324M_H223_CREATE_MSG = 1, 
	H324M_LVL_SYNC,	
	H324M_H245_CTRL_UPDATE_LOCAL_MTB,
	H324M_H245_CTRL_UPDATE_REMOTE_MTB,	
	H324M_H245_CTRL_ADD_AUDIO_CH,	
	H324M_H245_CTRL_ADD_VIDEO_CH,	
	H324M_CONFIGURE_OTHER_PARAMS,
	H324M_H245_CTRL_DELETE_AUDIO_CH,	
	H324M_H245_CTRL_DELETE_VIDEO_CH,		
	H324M_NSRP_DATA_REQ,	//Uplink NSRP  Data from Application chip
	H324M_VIDEO_DATA_REQ,	//Uplink Video Data from Application chip
	H324M_AUDIO_DATA_REQ,	//Uplink Audio Data from Application chip
	H324M_H223_DELETE_MSG,
	H324M_FIFO_KEEP_ALIVE_RSP,
	H324M_CLR_DATA_FROM_QUEUES,
	H324M_VTCALL_RECORD_START,
	H324M_VTCALL_RECORD_STOP,
#ifdef FEATURE_H324M_SKEW_IND_SUPPORT
	H324M_SKEW_IND,
#endif /* FEATURE_H324M_SKEW_IND_SUPPORT */
#if defined(VT_FEATURE_MONA)
	H324M_H223_PM_LS_START,
	H324M_MONA_SPC_DATA_REQ,
#endif

	H324M_INVALID_COMMAND = 0xFF,
}H324mCntlMSgMCToModem;


typedef enum H324mDirectionTypeTag
{
	H324M_DIRECTION_TYPE_UNI = 1,
	H324M_DIRECTION_TYPE_BI,
	H324M_DIRECTION_TYPE_INVALID, 
} H324mDirectionType;


typedef enum H324mMuxEntryStatusTag
{
	ACTIVE = 1,
	INACTIVE = 2
} H324mMuxEntryStatus;

typedef enum H324mChannelTypeTag
{
	INCOMING_CH = 1,
	OUTGOING_CH = 2,
	INVALID_CH
} H324mChannelType;

typedef enum H324mMediaTypeTag{
	H324M_MEDIA_TYPE_AUDIO = 1,
	H324M_MEDIA_TYPE_VIDEO,
	H324M_MEDIA_TYPE_DATA
} H324mMediaType;

#if 0 
enum H324mCodecTypeTag
{
	H324M_CODEC_NONE	,
	H324M_CODEC_AUDIO_AMR			= 1,
	H324M_CODEC_AUDIO_G723_1		=2,

	H324M_CODEC_AUDIO_INVALID = INVALID_AUDIO_CODEC,

	H324M_CODEC_VIDEO_H263_P0		= 1,
	H324M_CODEC_VIDEO_H263	= H324M_CODEC_VIDEO_H263_P0,
	H324M_CODEC_VIDEO_H263_P3		= 2,
	H324M_CODEC_VIDEO_MPEG4			=3,
	H324M_CODEC_VIDEO_MPEG4_SVH	=4,

	H324M_CODEC_VIDEO_H264			=5,
	H324M_CODEC_VIDEO_INVALID
} ;
#endif

enum H324mCodecTypeTag
{
	H324M_CODEC_NONE,
	H324M_CODEC_AUDIO_AMR, 
	H324M_CODEC_AUDIO_G723_1, 
	H324M_CODEC_VIDEO_H263_P0, 
	H324M_CODEC_VIDEO_H263 = H324M_CODEC_VIDEO_H263_P0, 	//TODO: delete h.263 codec type
	H324M_CODEC_VIDEO_H263_P3, 
	H324M_CODEC_VIDEO_MPEG4,
	H324M_CODEC_VIDEO_MPEG4_SVH,
	H324M_CODEC_VIDEO_H264,
	H324M_CODEC_INVALID,
};

typedef enum H324mCodecTypeTag H324mCodecType;
typedef enum H324mCodecTypeTag H324mVideoCodecType;
typedef enum H324mCodecTypeTag H324mAudioCodecType;

typedef	enum
{
	/*	AL2 with out sequence numbers	*/
	H324M_AL2_NO_SEQ_NUM = 1,
	/*	AL2 with sequence numbers		*/
	H324M_AL2_SEQ_NUM,
	/*	AL3 with out sequence numbers	*/
	H324M_AL3_NO_SEQ_NUM,
	/*	AL3 with 1 byte sequence numbers	*/
	H324M_AL3_1_BYTE_SEQ_NUM,
	/*	AL3 with 2 byte sequence numbers	*/
	H324M_AL3_2_BYTE_SEQ_NUM,
	H324M_AL_SEQ_NO_INVALID	
} al_seq_no_config;

typedef enum
{
	H324M_MOBILE_LEVEL_UNDEFINED = -1,
	H324M_MOBILE_LEVEL0 = 0,
	H324M_MOBILE_LEVEL1,
	H324M_MOBILE_LEVEL1D,
	H324M_MOBILE_LEVEL2,
	H324M_MOBILE_LEVEL1_WITH_DF_START,
	H324M_MOBILE_LEVEL1_WITH_DF_STOP,
	H324M_MOBILE_LEVEL2_WITH_OPTIONAL_HEADER,
	H324M_MOBILE_LEVEL_MAX
							/*	do not change position of H324M_MAX_LEVEL_VALUE, else has effect
								If any thing else is to be added in this enum, check
								"MdxConfigurationParameters" enum once  to avoid unpredictable results
							*/
 } H324mMobileLevel;


// Below structures are used for exchanging data between Modem chip and Application chipset. 
// MTE and Channel info should be shared
 struct H324mChannelInfoTag
{
	unsigned short 	oglcn;			/* out going or forward logical channel number */
	unsigned short 	iclcn;			/* incoming or reverse logical channel number */

	unsigned char 	fwd_altype;	/* altype for out going direction */
	unsigned char 	rev_altype;	/* al type for incoming direction */

	unsigned char 	codectype;	/* codec type */
	unsigned char	directiontype; 	/* direction type */

	unsigned char 	chtype; 	/* channel type - out going [or] incoming */

	unsigned char	fwd_alSeqNoStatus;	/* forward al seq number status to indicate how many control bytes to use etc*/
	unsigned char	rev_alSeqNoStatus;	/* Rev al seq number status to indicate how many control bytes to use etc*/
	double 			datarate;		/* data rate */

	unsigned char		dummy[5];  
};
 
typedef struct H324mChannelInfoTag H324mAudioChInfo;
typedef struct H324mChannelInfoTag H324mVideoChInfo;

typedef struct H324mMultiplexElementTag
{
	unsigned short 	meStatus;
	unsigned short 	repeatCountChoice;
	unsigned short 	lcn;
	unsigned short 	repeatCount;
}H324mMultiplexElement;

typedef struct H324mMultiplexEntryDescriptorTag
{
	unsigned short 			medStatus;
	unsigned short 			medNumber;
	H324mMultiplexElement 	me[2];
}H324mMultiplexEntryDescriptor;

typedef struct H324mMultiplexEntryTableTag
{
	H324mMultiplexEntryDescriptor medesc[16];
} H324mMultiplexEntryTable;

typedef struct H324mOtherConfigParamsTag
{
	unsigned long maxMuxPduSize;
} H324mOtherConfigParams;

#ifdef __cplusplus
}
#endif

#endif		/* _H324M_COMMON_H_*/

