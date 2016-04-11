#ifndef __JOINT_WARN_MAINUI_H__
#define __JOINT_WARN_MAINUI_H__

struct textStruct{
	char name[20];
	int  filesize;
	int  offsetx;
	int  offsety;
};

void jointwarn_crate_mainui(HDC hdc, int width, int height);

#endif
