#ifndef __HUFG_MAINUI_H__
#define __HUFG_MAINUI_H__

#define MWINDOW_LX   0
#define MWINDOW_TY   0
#define MWINDOW_RX   800
#define MWINDOW_BY   480

#define CONTEXT_SIZE	6000000
#define PAGE_PRE_COUNT  8
#define COS_MAX_NO	4

struct posData{
        char	posValue[10];
	char	userName[10];
        char	time[20];
        char	cardId[20];
        char	counted[2];
};

struct cardData{
	char	cardId[20];
	char	userName[10];
	char	cardState[10];
};

#endif
