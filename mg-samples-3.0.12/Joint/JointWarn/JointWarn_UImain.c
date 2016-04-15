#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"
#include "helloworld_res_en.h"

#define NUM_PRE_LINE	3
#define NUM_ROWS	4
#define SPARE_Y		360
#define FONT35_PIXEL	19	//FORNT SIZE 35
#define FONT30_PIXEL	16	//FORNT SIZE 30

extern const char* menu_hz[];
extern const char* warningText[];
extern struct textStruct menu_hiz[];
extern struct textStruct back;

int page_cnt1;
int back_width, back_height;
int row, column;
int partHeight, partWidth;
int x[TOTAL_NUM], y[TOTAL_NUM];
int hx[5], hy[5], vx[5], vy[5];
POINT s_point[2][3];
struct buttonObject btn_back_1;
struct buttonObject btn_front_page_1;
struct buttonObject btn_next_page_1;

void jointwarn_paint_frame(HDC hdc, struct textStruct *text, int count)
{
	int i, j, k = 0;
	int font_len;
	PLOGFONT s_font;
	
	SetBkMode(hdc,BM_TRANSPARENT);
	SetTextColor(hdc, COLOR_lightwhite);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x27, 0x40, 0x8B, 0xFF));
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			//if(i*column + j >= TOTAL_NUM)
			if(k >= count)
				break;
			//x[i*column + j] = vx[j] - partWidth + 5;
			//y[i*column + j] = hy[i] - partHeight + 5;
			//printf("x = %d, y = %d\n", x[i*column + j], y[i*column + j]);
			x[k] = vx[j] - partWidth + 5;
			y[k] = hy[i] - partHeight + 5;
			printf("x = %d, y = %d\n", x[k], y[k]);
			FillBox(hdc, x[k], y[k], partWidth - 10, partHeight - 10);
			//s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
				FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, menu_hiz[i*column + j].filesize, 0);
			s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
				FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, text[k].filesize, 0);
			SelectFont(hdc,s_font);
			//FillBox(hdc, x[i*column + j], y[i*column + j], partWidth - 10, partHeight - 10);
			//font_len = strlen(menu_hiz[i*column + j].name);	
			font_len = strlen(text[k].name);	
			printf("font_len = %d\n", font_len);
			font_len = (16 - font_len) >> 1;
			//TextOut(hdc, x[i*column + j] + menu_hiz[i*column + j].offsetx + (FONT30_PIXEL * font_len), y[i*column + j] + menu_hiz[i*column + j].offsety, menu_hiz[i*column + j].name);	
			TextOut(hdc, x[k] + text[k].offsetx + (FONT30_PIXEL * font_len), y[k] + text[k].offsety, text[k].name);	
			DestroyLogFont(s_font);
			k++;
		}
	}
	
}

void jointwarn_crate_mainui(HDC hdc, int width, int height)
{
	int i, j;
	int font_len;
	int xx, yy;
	int form_count;
	PLOGFONT s_font;
	//HDC hdc;

	//hdc = BeginPaint(hWnd);

	SetBkMode(hdc,BM_TRANSPARENT);
	SetTextColor(hdc,COLOR_lightwhite);
	//SetBkColor(hdc, RGBA2Pixel(hdc, 0x20, 0xB2, 0xAA, 0xFF));
	//TextOut(hdc,100,295,"测试");
	column = NUM_PRE_LINE;
	row = NUM_ROWS;
	//row = TOTAL_NUM / column;
	//if(TOTAL_NUM % column != 0){
	//	row += 1;
	//}
	
	//partHeight = height / (row + 1);
	partHeight = SPARE_Y / (row);
	partWidth = width / column;
	yy = partHeight;
	xx = partWidth;
	for(i=0; i<row; i++){
		hx[i] = 0;
		hy[i] = yy;
		yy += partHeight;
	}
	for(i=0; i<column; i++){
		vx[i] = xx; 
		vy[i] = 0;
		xx += partWidth;
	}
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x20, 0xB2, 0xAA, 0xFF));
	FillBox(hdc, 0, 0, width, yy - partHeight);	
	
	for(i=0; i<row; i++){
		//DrawHDotLine(hdc, hx[i], hy[i], width);
		LineEx(hdc, hx[i], hy[i], width, hy[i]);
	}
	for(i=0; i<column; i++){
		//DrawVDotLine(hdc, vx[i], vy[i], height);	
		LineEx(hdc, vx[i], vy[i], vx[i], height - partHeight);
	}

	form_count = TOTAL_NUM > TOTAL_FRAME ? TOTAL_FRAME : TOTAL_NUM;
	page_cnt1 = 0; 
	jointwarn_paint_frame(hdc, menu_hiz, form_count);
	
	printf("partWidth = %d\n", partWidth);
	//Rectangle(hdc, partWidth, yy - partHeight + 20, width - (2 * partWidth), height - 20);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	FillBox(hdc, 0, SPARE_Y, width, height - SPARE_Y);	

	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0x00, 0xFF));
	FillBox(hdc, 0 + 100, SPARE_Y + 20, (width - partWidth - 100), height - SPARE_Y - 40);	
	//SetBkMode(hdc,BM_TRANSPARENT);	
	SetTextColor(hdc,COLOR_blue);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 50, 0);
	SelectFont(hdc,s_font);
	TextOut(hdc, 0 + 100 + 20, yy - partHeight + 40, warningText[0]);	
	DestroyLogFont(s_font);
	//TextOut(hdc, partWidth + 30, yy - partHeight/2, "ABCDEF");	
	//TextOut(hdc,100,295,"测试");
	//test_output(hdc, "测试555");

	btn_front_page_1.point_start.x = 10;
	btn_front_page_1.point_start.y = yy - partHeight + 10;
	btn_front_page_1.point_end.x = 50;
	btn_front_page_1.point_end.y = yy - partHeight + 50;
	btn_front_page_1.active = 0;
	btn_next_page_1.point_start.x = width - 10;
	btn_next_page_1.point_start.y = yy - partHeight + 10;
	btn_next_page_1.point_end.x = width - 50;
	btn_next_page_1.point_end.y = yy - partHeight + 50;
	btn_next_page_1.active = 0;
	printf("%d, %d, %d, %d\n", btn_next_page_1.point_start.x, btn_next_page_1.point_end.x, btn_next_page_1.point_start.y, btn_next_page_1.point_end.y);
	s_point[0][0].x = btn_front_page_1.point_start.x;
	s_point[0][0].y = (btn_front_page_1.point_start.y + btn_front_page_1.point_end.y) >> 1;
	s_point[0][1].x = btn_front_page_1.point_end.x;
	s_point[0][1].y = btn_front_page_1.point_start.y;
	s_point[0][2].x = btn_front_page_1.point_end.x;
	s_point[0][2].y = btn_front_page_1.point_end.y;
	s_point[1][0].x = btn_next_page_1.point_start.x;
	s_point[1][0].y = (btn_next_page_1.point_start.y + btn_next_page_1.point_end.y) >> 1;
	s_point[1][1].x = btn_next_page_1.point_end.x;
	s_point[1][1].y = btn_next_page_1.point_start.y;
	s_point[1][2].x = btn_next_page_1.point_end.x;
	s_point[1][2].y = btn_next_page_1.point_end.y;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xB3, 0xB3, 0xB3, 0xFF));
	FillPolygon(hdc, s_point[0], 3);
	if(TOTAL_NUM > TOTAL_FRAME){
		btn_next_page_1.active = 1;
		SetBrushColor(hdc, RGBA2Pixel(hdc, 0x00, 0xFF, 0x00, 0xFF));
	}
	FillPolygon(hdc, s_point[1], 3);

	back_width = 120;
	back_height = 50;
	btn_back_1.point_start.x = 2 * partWidth + 100;
	btn_back_1.point_start.y = yy - partHeight/2;
	btn_back_1.point_end.x = btn_back_1.point_start.x + back_width;
	btn_back_1.point_end.y = btn_back_1.point_start.y + back_height;
	btn_back_1.active = 1;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
	FillBox(hdc, btn_back_1.point_start.x, btn_back_1.point_start.y, back_width, back_height);	
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
		FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, back.filesize, 0);
	SelectFont(hdc,s_font);
	SetTextColor(hdc, COLOR_lightwhite);
	TextOut(hdc, btn_back_1.point_start.x + back.offsetx, btn_back_1.point_start.y + back.offsety, back.name);	
	DestroyLogFont(s_font);
	
	//EndPaint(hWnd,hdc);	

}
