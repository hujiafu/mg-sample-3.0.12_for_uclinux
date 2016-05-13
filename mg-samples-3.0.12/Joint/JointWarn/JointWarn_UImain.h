#ifndef __JOINT_WARN_MAINUI_H__
#define __JOINT_WARN_MAINUI_H__

#define MWINDOW_LX   0
#define MWINDOW_TY   0
#define MWINDOW_RX   800
#define MWINDOW_BY   480
#define BACK_XOFFSET	600
#define SPARE_Y         360

#define TOTAL_NUM       25
//#define TOTAL_FRAME     12
#define FONT35_PIXEL    19      //FORNT SIZE 35
#define FONT30_PIXEL    16      //FORNT SIZE 30
#define FONT30_HIGH_PIXEL       35
#define WARN_FRAME_HIGH         20

#define SEL_MAX_COUNT	6

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
	struct textStruct * text[3];
};

struct buttonObject{
	POINT point_start;
	POINT point_end;
	char active;	
};

//void jointwarn_crate_mainui(HDC hdc, int width, int height);

#endif
