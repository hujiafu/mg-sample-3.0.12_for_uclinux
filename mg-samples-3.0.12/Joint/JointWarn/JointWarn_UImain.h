#ifndef __JOINT_WARN_MAINUI_H__
#define __JOINT_WARN_MAINUI_H__

#define MWINDOW_LX   0
#define MWINDOW_TY   0
#define MWINDOW_RX   800
#define MWINDOW_BY   480

struct textStruct{
	char name[20];
	int  filesize;
	int  offsetx;
	int  offsety;
};

struct warnForm{
	int formCount;
	struct textStruct * text[3];
};

void jointwarn_crate_mainui(HDC hdc, int width, int height);

#endif
