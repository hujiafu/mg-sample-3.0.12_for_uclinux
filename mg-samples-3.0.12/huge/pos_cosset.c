#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "pos_main.h"

extern const char * cos_menu[];
extern const char * cos_menu1[];
extern int windows_no;

unsigned int cos_menu_pos[4][2];
unsigned int cos_no = 0;
unsigned int cos_pos_no;
unsigned char cos_pos_no_str[10];
unsigned int cos_isconst_value = 0;
unsigned int cos_isconst_count = 0;
double cos_pos_value;
unsigned char cos_pos_value_fstr[10];
unsigned char cos_pos_value_str[10];
unsigned int cos_pos_value_cnt;
unsigned char cos_pos_count_fstr[10];
unsigned char cos_pos_count_str[10];
unsigned int cos_pos_count_cnt;

double char2double(char ch[])
{
	int i;
	double intg = 0, fl = 0;
	int flag = 0;

	for(i = 0; ch[i]; i++){
		if(!flag){
			if(ch[i] == '.'){
				flag = 1;
			}
			else{
				intg = intg*10 + ch[i] - '0';
			}
		}
		else{
			fl = fl*10 + ch[i] - '0';
			flag++;
		}
	}

	for(i = flag; i > 1; i--){
		fl /= 10;
	}
	return intg + fl;
}


void pos_cos_clear(HDC hdc, int sel)
{
	int start_x, start_y;
	int width, height;
	
	start_x = cos_menu_pos[sel][0] - 20;
        start_y = cos_menu_pos[sel][1] - 20;
	width = MWINDOW_RX - 40;
	height = 80;
	SetPenColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        SetPenWidth(hdc, 1);
        LineEx(hdc, start_x, start_y, start_x + width, start_y);
        LineEx(hdc, start_x + width, start_y, start_x + width, start_y + height);
        LineEx(hdc, start_x + width, start_y + height, start_x, start_y + height);
        LineEx(hdc, start_x, start_y + height, start_x, start_y);

}

void pos_cos_sel(HDC hdc, int sel)
{
	int start_x, start_y;
	int width, height;
	
	start_x = cos_menu_pos[sel][0] - 20;
        start_y = cos_menu_pos[sel][1] - 20;
	width = MWINDOW_RX - 40;
	height = 80;
	SetPenColor(hdc, RGBA2Pixel(hdc, 0x00, 0x00, 0xFF, 0xFF));
        SetPenWidth(hdc, 1);
        LineEx(hdc, start_x, start_y, start_x + width, start_y);
        LineEx(hdc, start_x + width, start_y, start_x + width, start_y + height);
        LineEx(hdc, start_x + width, start_y + height, start_x, start_y + height);
        LineEx(hdc, start_x, start_y + height, start_x, start_y);

}

void pos_set_const_state(HDC hdc, int no)
{
	PLOGFONT s_font;

        SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 40, 0);
        SelectFont(hdc,s_font);
	
	if(no == 2){
		FillBox(hdc, cos_menu_pos[2][0] + 400 - 10, cos_menu_pos[2][1] - 10, 50, 50);
		if(cos_isconst_value == 0){
			TextOut(hdc, cos_menu_pos[2][0] + 400, cos_menu_pos[2][1], cos_menu1[1]);	
		}else{
			TextOut(hdc, cos_menu_pos[2][0] + 400, cos_menu_pos[2][1], cos_menu1[0]);	
		}
	}
	if(no == 1){
		FillBox(hdc, cos_menu_pos[1][0] + 400 - 10, cos_menu_pos[1][1] - 10, 50, 50);
		if(cos_isconst_count == 0){
			TextOut(hdc, cos_menu_pos[1][0] + 400, cos_menu_pos[1][1], cos_menu1[1]);	
		}else{
			TextOut(hdc, cos_menu_pos[1][0] + 400, cos_menu_pos[1][1], cos_menu1[0]);	
		}
	}
	
	DestroyLogFont(s_font);
}

void pos_set_const_value(HDC hdc, int no){
	
	PLOGFONT s_font;

        SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 40, 0);
        SelectFont(hdc,s_font);
	
	
	FillBox(hdc, cos_menu_pos[no][0] + 400 - 10, cos_menu_pos[no][1] - 10, 300, 50);
	if(no == 0)
		TextOut(hdc, cos_menu_pos[no][0] + 400, cos_menu_pos[no][1], cos_pos_value_str);	
	else
		TextOut(hdc, cos_menu_pos[no][0] + 400, cos_menu_pos[no][1], cos_pos_count_str);
	
	DestroyLogFont(s_font);
}

void create_poscos_set(HDC hdc)
{
	int i;
	PLOGFONT s_font;

	windows_no = 4;

	SetBkMode(hdc,BM_TRANSPARENT);
        SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	FillBox(hdc, MWINDOW_LX, MWINDOW_TY, MWINDOW_RX, MWINDOW_BY);

	SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 40, 0);
        SelectFont(hdc,s_font);

	for(i=0; i<4; i++){
		cos_menu_pos[i][0] = 40;
		cos_menu_pos[i][1] = 40 + i * 80;
		TextOut(hdc, cos_menu_pos[i][0], cos_menu_pos[i][1], cos_menu[i]);	
	}

	cos_pos_value_cnt = 0;
	//cos_pos_value = 12;
	//if(cos_pos_value != 0){
	//	sprintf(cos_pos_value_str, "%d", cos_pos_value);
		//SetTextColor(hdc,RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        	//SetBrushColor(hdc, RGBA2Pixel(hdc, 0x00, 0x00, 0xFF, 0xFF));
		//FillBox(hdc, cos_menu_pos[0][0] - 20, cos_menu_pos[0][1] - 20, MWINDOW_RX - 40, 80);	
		//TextOut(hdc, cos_menu_pos[0][0], cos_menu_pos[0][1], cos_menu[0]);	
		TextOut(hdc, cos_menu_pos[0][0] + 400, cos_menu_pos[0][1], cos_pos_value_fstr);
		memset(cos_pos_value_str, 0, 10);	
	//}
	cos_pos_count_cnt = 0;
	//cos_pos_no = 2;
	//if(cos_pos_no != 0){
	//	sprintf(cos_pos_count_str, "%d", cos_pos_no);
		TextOut(hdc, cos_menu_pos[3][0] + 400, cos_menu_pos[3][1], cos_pos_count_fstr);	
		memset(cos_pos_count_str, 0, 10);	
		
	//}

	if(cos_isconst_value == 0){
		TextOut(hdc, cos_menu_pos[2][0] + 400, cos_menu_pos[2][1], cos_menu1[1]);	
	}else{
		TextOut(hdc, cos_menu_pos[2][0] + 400, cos_menu_pos[2][1], cos_menu1[0]);	
	}
	
	if(cos_isconst_count == 0){
		TextOut(hdc, cos_menu_pos[1][0] + 400, cos_menu_pos[1][1], cos_menu1[1]);	
	}else{
		TextOut(hdc, cos_menu_pos[1][0] + 400, cos_menu_pos[1][1], cos_menu1[0]);	
	}
	
	//cos_no = 0;
	pos_cos_sel(hdc, cos_no);
	
	DestroyLogFont(s_font);
}
