#ifndef __JOINT_WARN_MAINUI_H__
#define __JOINT_WARN_MAINUI_H__

#define MWINDOW_LX   0
#define MWINDOW_TY   0
#define MWINDOW_RX   800
#define MWINDOW_BY   480

#define TOTAL_NUM       14
#define TOTAL_FRAME     12



struct textStruct{
	char name[20];
	char  filesize;
	char  offsetx;
	char  offsety;
	int   color;
};

struct warnForm{
	int messageCount;
	int formColor;
	int borderColor;
	int width;
	int height;
	struct textStruct * text[3];
};

struct buttonObject{
	POINT point_start;
	POINT point_end;
	char active;	
};

void jointwarn_crate_mainui(HDC hdc, int width, int height);

#endif
