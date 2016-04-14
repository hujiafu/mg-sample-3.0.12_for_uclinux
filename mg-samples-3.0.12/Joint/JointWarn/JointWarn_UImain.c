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
#define TOTAL_NUM	11
#define SPARE_Y		360

extern const char* menu_hz[];
extern const char* warningText[];
extern struct textStruct menu_hiz[];
extern struct textStruct back;

POINT s_back;
int back_width, back_height;
void test_b(HDC hdc)
{
	//HDC hdc;
	//hdc = BeginPaint(hWnd);
	TextOut(hdc, 500, 295, "测 试 2");
	//EndPaint(hWnd,hdc);
}

void jointwarn_crate_mainui(HWND hWnd, int width, int height)
{
	int column;
	int row;
	int i, j;
	int partHeight, partWidth;
	int hx[5], hy[5], vx[5], vy[5];
	int xx = 0, yy = 0;
	int x[20], y[20];
	PLOGFONT s_font;
	POINT s_point[2][3];
	HDC hdc;

	hdc = BeginPaint(hWnd);

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
	
	SetTextColor(hdc, COLOR_lightwhite);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x27, 0x40, 0x8B, 0xFF));
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			if(i*column + j >= TOTAL_NUM)
				break;
			x[i*column + j] = vx[j] - partWidth + 5;
			y[i*column + j] = hy[i] - partHeight + 5;
			printf("x = %d, y = %d\n", x[i*column + j], y[i*column + j]);
			s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
				FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, menu_hiz[i*column + j].filesize, 0);
			SelectFont(hdc,s_font);
			FillBox(hdc, x[i*column + j], y[i*column + j], partWidth - 10, partHeight - 10);	
			TextOut(hdc, x[i*column + j] + menu_hiz[i*column + j].offsetx, y[i*column + j] + menu_hiz[i*column + j].offsety, menu_hiz[i*column + j].name);	
			DestroyLogFont(s_font);
		}
	}

	printf("yy = %d\n", yy);
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
	s_point[0][0].x = 10;
	s_point[0][0].y = yy - partHeight + 30;
	s_point[0][1].x = 30;
	s_point[0][1].y = yy - partHeight + 10;
	s_point[0][2].x = 30;
	s_point[0][2].y = yy - partHeight + 50;
	s_point[1][0].x = width - 10;
	s_point[1][0].y = yy - partHeight + 30;
	s_point[1][1].x = width - 30;
	s_point[1][1].y = yy - partHeight + 10;
	s_point[1][2].x = width - 30;
	s_point[1][2].y = yy - partHeight + 50;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x00, 0xFF, 0x00, 0xFF));
	FillPolygon(hdc, s_point[0], 3);
	FillPolygon(hdc, s_point[1], 3);

	s_back.x = 2 * partWidth + 100;
	s_back.y = yy - partHeight/2;
	back_width = 120;
	back_height = 50;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
	FillBox(hdc, s_back.x, s_back.y, back_width, back_height);	
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
		FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, back.filesize, 0);
	SelectFont(hdc,s_font);
	SetTextColor(hdc, COLOR_lightwhite);
	TextOut(hdc, s_back.x + back.offsetx, s_back.y + back.offsety, back.name);	
	DestroyLogFont(s_font);
	
	EndPaint(hWnd,hdc);	

}
