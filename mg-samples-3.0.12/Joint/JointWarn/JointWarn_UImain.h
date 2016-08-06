#ifndef __JOINT_WARN_MAINUI_H__
#define __JOINT_WARN_MAINUI_H__

#define DEBUG_QVFB  0

#define MWINDOW_LX   0
#define MWINDOW_TY   0
#define MWINDOW_RX   800
#define MWINDOW_BY   480
#define BACK_XOFFSET	670
#define SPARE_Y         360

#define TOTAL_NUM       25
//#define TOTAL_FRAME     12
#define FONT40_PIXEL    22      //FORNT SIZE 40
#define FONT35_PIXEL    19      //FORNT SIZE 35
//#define FONT30_PIXEL    16      //FORNT SIZE 30
#define FONT30_PIXEL    15      //FORNT SIZE 30
#define FONT20_PIXEL    10     //FORNT SIZE 20
#define FONT40_HIGH_PIXEL       45
#define FONT30_HIGH_PIXEL       35
#define FONT20_HIGH_PIXEL       30
#define WARN_FRAME_HIGH         20

#define SEL_MAX_COUNT	8

struct textStruct{
	char name[100];
	char  filesize;
	int  offsetx;
	int  offsety;
	int   color;
};

struct warnForm{
	int messageCount;
	int formColor;
	int borderColor;
	int width;
	int height;
	int startx;
	int starty;
	int textCnt;
	struct textStruct * text[3];
};

struct buttonObject{
	POINT point_start;
	POINT point_end;
	char active;	
};

//void jointwarn_crate_mainui(HDC hdc, int width, int height);

#endif
