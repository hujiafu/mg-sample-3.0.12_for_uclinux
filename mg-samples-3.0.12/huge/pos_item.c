#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "pos_main.h"

#define ITEM_NUM	10

extern int windows_no;
extern const char * item_menu[];

static BITMAP s_bmp[ITEM_NUM];
int item_num;
int item_no;
int item_pos[ITEM_NUM][2];

void clear_pos_item(HDC hdc, int itemNo)
{
	int start_x, start_y;

	start_x = item_pos[itemNo][0] - 13;
	start_y = item_pos[itemNo][1] - 13;
	
	SetBkMode(hdc,BM_TRANSPARENT);
        SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        FillBox(hdc, start_x, start_y, 62, 62);
	FillBoxWithBitmap(hdc, item_pos[itemNo][0], item_pos[itemNo][1], 32, 32, &s_bmp[itemNo]);
}

void select_pos_item(HDC hdc, int itemNo)
{
	int start_x, start_y;
	SetBkMode(hdc,BM_TRANSPARENT);

        //SetBrushColor(hdc, RGBA2Pixel(hdc, 0x00, 0x00, 0xFF, 0xFF));
        //FillBox(hdc, item_pos[itemNo][0] - 13, item_pos[itemNo][1] - 13, 60, 60);
	SetPenColor(hdc, RGBA2Pixel(hdc, 0x00, 0x00, 0xFF, 0xFF));
	SetPenWidth(hdc, 1);

	start_x = item_pos[itemNo][0] - 13;
	start_y = item_pos[itemNo][1] - 13;
	LineEx(hdc, start_x, start_y, start_x + 60, start_y);
	LineEx(hdc, start_x + 60, start_y, start_x + 60, start_y + 60);
	LineEx(hdc, start_x + 60, start_y + 60, start_x, start_y + 60);
	LineEx(hdc, start_x, start_y + 60, start_x, start_y);
	
	printf("itemNo = %d\n", itemNo);
	printf("%d, %d\n", item_pos[itemNo][0], item_pos[itemNo][1]);
}

void create_pos_item(HDC hdc)
{
	int i, j;
	PLOGFONT s_font;	

	windows_no = 2;

	item_num = 9;

	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 15, 0);
	SelectFont(hdc,s_font);

	SetBkMode(hdc,BM_TRANSPARENT);
        SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        FillBox(hdc, MWINDOW_LX, MWINDOW_TY, MWINDOW_RX, MWINDOW_BY);

	LoadBitmap(HDC_SCREEN,&s_bmp[0],"/usr/local/minigui/local/share/minigui/res/bmp/address.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[1],"/usr/local/minigui/local/share/minigui/res/bmp/calendar.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[2],"/usr/local/minigui/local/share/minigui/res/bmp/config.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[3],"/usr/local/minigui/local/share/minigui/res/bmp/consulting.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[4],"/usr/local/minigui/local/share/minigui/res/bmp/customers.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[5],"/usr/local/minigui/local/share/minigui/res/bmp/date.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[6],"/usr/local/minigui/local/share/minigui/res/bmp/networking.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[7],"/usr/local/minigui/local/share/minigui/res/bmp/order_159.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[8],"/usr/local/minigui/local/share/minigui/res/bmp/user.png");

	for(i=0; i<2; i++){
		for(j=0; j<6; j++){
			if((i * 6 + j) > (item_num - 1)){
				break;
			}
			item_pos[i * 6 + j][0] = 80 + j*120;
			item_pos[i * 6 + j][1] = 40 + i*140;
			printf("item_pos no %d\n", i * 6 + j);
			printf("item_pos %d, %d\n", item_pos[i * 6 + j][0], item_pos[i * 6 + j][1]);
			if((i * 6 + j) == 0){
				item_no = 0;
				select_pos_item(hdc, item_no);
			}
			FillBoxWithBitmap(hdc, item_pos[i * 6 + j][0], item_pos[i * 6 + j][1], 32, 32, &s_bmp[i * 6 + j]);
			TextOut(hdc, item_pos[i * 6 + j][0] - 15, item_pos[i * 6 + j][1] + 60, item_menu[i * 6 + j]);
		}
	}

	DestroyLogFont(s_font);
}
