#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "pos_main.h"

const char * sz_menu2[]=
{
        "卡号",
        "姓名",
        "消费状态",
};


extern HWND hMainWnd;

extern struct cardData def_card;
extern const char * sz_menu[];
extern const char * sz_menu1[];
extern struct posData def_detil[];
extern int windows_no;

int histroy_cnt;
int page_num;
int page_cnt;
int page_no;

void create_query_ui(HDC hdc)
{
	PLOGFONT s_font;


	windows_no = 6;

	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        FillBox(hdc, MWINDOW_LX, MWINDOW_TY, MWINDOW_RX, MWINDOW_BY);
	SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
        s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 30, 0);
        SelectFont(hdc,s_font);

	TextOut(hdc, 20, 20, sz_menu[0]);
	TextOut(hdc, 300, 20, sz_menu[1]);
	TextOut(hdc, 500, 20, sz_menu[2]);

	SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0xFF, 0xFF));
	TextOut(hdc, 20, 60, def_card.cardId);
	TextOut(hdc, 300, 60, def_card.userName);
	TextOut(hdc, 500, 60, def_card.cardState);

	printf("0x%x 0x%x\n", sz_menu[0][0], sz_menu[0][1]);
	printf("0x%x 0x%x\n", sz_menu1[0][0], sz_menu1[0][1]);

	DestroyLogFont(s_font);

}



void display_detil(HDC hdc, struct posData * detil)
{
	int i;
	PLOGFONT s_font;

        s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 30, 0);
        SelectFont(hdc,s_font);
        FillBox(hdc, 20, 60, MWINDOW_RX - 20, 320);
        SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0xFF, 0xFF));
	for(i=0; i<page_cnt; i++){
        	TextOut(hdc, 20, 60 + i*40, detil[i].cardId);
        	TextOut(hdc, 200, 60 + i*40, detil[i].userName);
        	TextOut(hdc, 350, 60 + i*40, detil[i].posValue);
        	TextOut(hdc, 500, 60 + i*40, detil[i].time);
	}
        DestroyLogFont(s_font);

}

void query_detil(HDC hdc)
{
	int i;
	PLOGFONT s_font;

	windows_no = 7;
        SetBkMode(hdc,BM_TRANSPARENT);
        SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        FillBox(hdc, MWINDOW_LX, MWINDOW_TY, MWINDOW_RX, MWINDOW_BY);
        SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
        s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 30, 0);
        SelectFont(hdc,s_font);

        TextOut(hdc, 20, 20, sz_menu1[0]);
        TextOut(hdc, 200, 20, sz_menu1[1]);
        TextOut(hdc, 350, 20, sz_menu1[2]);
        TextOut(hdc, 500, 20, sz_menu1[3]);

	histroy_cnt = 12;
	page_num = histroy_cnt / PAGE_PRE_COUNT + 1;
	page_cnt = histroy_cnt > PAGE_PRE_COUNT ? PAGE_PRE_COUNT : histroy_cnt;	
	page_no = 0;

	display_detil(hdc, &def_detil[page_no]);

        DestroyLogFont(s_font);
}
