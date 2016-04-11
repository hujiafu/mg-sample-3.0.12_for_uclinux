#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"
#include "helloworld_res_en.h"

#define NUM_PRE_LINE	5
#define TOTAL_NUM	11

extern const char* menu_hz[];

void test_b(HDC hdc)
{
	//HDC hdc;
	//hdc = BeginPaint(hWnd);
	TextOut(hdc, 500, 295, "测 试 2");
	//EndPaint(hWnd,hdc);
}

void jointwarn_crate_mainui(HDC hdc, int width, int height)
{
	int column;
	int row;
	int i;
	int partHeight, partWidth;
	int hx[5], hy[5], vx[5], vy[5];
	int xx = 0, yy = 0;
	PLOGFONT s_font;

	TextOut(hdc,100,295,"测试");
	column = NUM_PRE_LINE;
	row = TOTAL_NUM / column;
	if(TOTAL_NUM % column != 0){
		row += 1;
	}
	
	partHeight = height / (row + 1);
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
	
	for(i=0; i<row; i++){
		//DrawHDotLine(hdc, hx[i], hy[i], width);
		LineEx(hdc, hx[i], hy[i], width, hy[i]);
	}
	for(i=0; i<column; i++){
		//DrawVDotLine(hdc, vx[i], vy[i], height);	
		LineEx(hdc, vx[i], vy[i], vx[i], height - partHeight);
	}

	printf("yy = %d\n", yy);
	//Rectangle(hdc, partWidth, yy - partHeight + 20, width - (2 * partWidth), height - 20);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xff, 0xFF));
	FillBox(hdc, 0, yy - partHeight, width, partHeight);	

	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0x00, 0xFF));
	FillBox(hdc, partWidth, yy - partHeight + 20, width - (2 * partWidth), partHeight - 40);	
	//SetBkMode(hdc,BM_TRANSPARENT);	
	SetTextColor(hdc,COLOR_blue);
	//s_font = CreateLogFont(NULL,"Song","GB2312-80",
        //                FONT_WEIGHT_REGULAR,FONT_SLANT_ITALIC,FONT_FLIP_NIL,
        //                FONT_OTHER_NIL,FONT_UNDERLINE_NONE,FONT_STRUCKOUT_NONE,40,0);
	
	//s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "times", "ISO8859-1", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 50, 0);
	//s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "simhei", "GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 50, 0);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 60, 0);

	SelectFont(hdc,s_font);
	TextOut(hdc, partWidth + 30, yy - partHeight + 30, menu_hz[0]);	
	//TextOut(hdc, partWidth + 30, yy - partHeight/2, "ABCDEF");	
	//TextOut(hdc,100,295,"测试");
	//test_output(hdc, "测试555");
}
