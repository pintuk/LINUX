#ifndef __COMMONTYPES_H
#define __COMMONTYPES_H



#define TRUE	1
#define FALSE	0

typedef int BOOL;



typedef enum {
	VTMAIN_MSG_TYPE_ID=1,
	VTUI_MSG_TYPE_ID=2
}vtapp_msgtype_id;


typedef struct
{
	long stype;
	int type;
	int msgLen;
	char message[255];
}VTAppMsg;


typedef enum {
		VTAPP_NOTI_NONE,
		VTMAIN_NOTI_OUTGOING,
		VTMAIN_NOTI_INCOMING,
		VTUI_NOTI_INCOMING,
		VTUI_NOTI_OUTGOING,
		VTMAIN_NOTI_END,
		VTUI_NOTI_END,
		VTAPP_NOTI_END
} vtapp_noti_stype_t;


typedef enum {
		VTAPP_NOTI,
		VTAPP_NOTI_STR,
		VTAPP_NOTI_EXIT,
		VTAPP_NOTI_CRASH
} vtapp_noti_msgtype_t;

#endif


