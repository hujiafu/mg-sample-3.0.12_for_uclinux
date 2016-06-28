
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"

extern struct textStruct back;
extern struct buttonObject btn_back_1;
extern int back_width, back_height;
extern POINT s_point[2][3];
extern struct buttonObject btn_front_page_1;
extern struct buttonObject btn_next_page_1;
extern int page_cnt1;
extern const char * cancel_text[];
extern const char * test_msg_hz2[];
extern const char * title_warn_106[];
extern unsigned char test_108_1[];
extern unsigned char sel_title[50];
extern unsigned char sel_title_color[10];

POINT form_pos_start[2];
POINT form_pos_end[2];
struct buttonObject form_obj[2];
struct buttonObject select_obj[SEL_MAX_COUNT];
int select_obj_no;
int select_width, select_height;
int btn_cancel_width, btn_cancel_height;
int form_width, form_height;
int spare_height;
int top_start_x, top_start_y;
struct buttonObject btn_cancel;
struct warnForm top_warn[2];
struct textStruct top_text[3];
int top_window;

void jointwarn_paint_cancel(HDC hdc)
{
	PLOGFONT s_font;

	btn_cancel_width = 100;
        btn_cancel_height = 40;
	btn_cancel.point_start.x = top_start_x + form_width - 160;
        btn_cancel.point_start.y = top_start_y + form_height - spare_height + 10;
        btn_cancel.point_end.x = btn_cancel.point_start.x + btn_cancel_width;
        btn_cancel.point_end.y = btn_cancel.point_start.y + btn_cancel_height;
        btn_cancel.active = 1;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
	FillBox(hdc, btn_cancel.point_start.x, btn_cancel.point_start.y, btn_cancel_width, btn_cancel_height);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 20, 0);
	SelectFont(hdc,s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, btn_cancel.point_start.x + 10, btn_cancel.point_start.y + 10, cancel_text[0]);
        DestroyLogFont(s_font);

}

void JointWarn_create_top(HDC hdc, struct warnForm *warn, int count, int width, int height)
{
	int top_height = 20;
	int mid_height = 30;
	int bottom_height = 20;
	int sel_height = 0, sel_width = 0;
	int sel_area_height;
	int sel_start_x, sel_start_y;
	int len;
	int i, j;
	int offset_x;
	unsigned char red, green, blue;
	PLOGFONT s_font;
	
	form_width = width;
	form_height = height;
	spare_height = 80;

	SetBkMode(hdc,BM_TRANSPARENT);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                               FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, \
			       FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 20, 0);
        SelectFont(hdc, s_font);
	sel_area_height = (count-1) * mid_height;
	for(i=0; i<count; i++){
		sel_area_height += warn[i].textCnt * FONT20_HIGH_PIXEL;
	}
	//form_height = top_height + bottom_height + sel_height;
	//form_height -= spare_height;
	sel_start_y = top_start_y + ((form_height - (spare_height + sel_area_height)) >> 1);

	for(i=0; i<count; i++){
		for(j=0; j<warn[i].textCnt; j++){
			printf("font count %d\n", strlen(warn[i].text[j]->name));
			len = strlen(warn[i].text[j]->name) * FONT20_PIXEL;
			sel_width = sel_width > len ? sel_width : len;
		}
		sel_start_x = top_start_x + ((form_width - sel_width) >> 1);
		sel_height = FONT20_HIGH_PIXEL * warn[i].textCnt;
		
		red = (warn[i].formColor & 0xff000000) >> 24; 
		green = (warn[i].formColor & 0x00ff0000) >> 16; 
		blue = (warn[i].formColor & 0x0000ff00) >> 8; 
		SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		FillBox(hdc, sel_start_x, sel_start_y, sel_width + 10, sel_height);
		printf("sel_width = %d\n", sel_width);	
	
		for(j=0; j<warn[i].textCnt; j++){
			red = (warn[i].text[j]->color & 0xff000000) >> 24; 
			green = (warn[i].text[j]->color & 0x00ff0000) >> 16; 
			blue = (warn[i].text[j]->color & 0x0000ff00) >> 8;
			SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
			len = strlen(warn[i].text[j]->name) * FONT20_PIXEL;
			offset_x = (sel_width - len) >> 1;
			TextOut(hdc, sel_start_x+offset_x+5, sel_start_y+j*FONT20_HIGH_PIXEL+3, warn[i].text[j]->name);
		} 
		sel_start_y += mid_height + sel_height;	
	}
	DestroyLogFont(s_font);
	
	jointwarn_paint_cancel(hdc);
}

void JointWarn_create_top_back(HDC hdc, int width, int height)
{
	int count;
	unsigned int ptr;
	struct warnForm * pwarn;

	printf("JointWarn_create_top_back\n");

	top_window = 1;
	top_start_x = (MWINDOW_RX - width) >> 1;
	top_start_y = (MWINDOW_BY - height) >> 1;

		
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x10, 0x4e, 0x8b, 0xFF));
	FillBox(hdc, top_start_x, top_start_y, width, height);
	
	printf("%s\n", test_108_1);

#if 0
	count = JointAnalysisCmdLine(test_108_1, &ptr);
	pwarn = (struct warnForm *)ptr;
	printf("count = %d\n", count);
	printf("color = 0x%x\n", pwarn[0].formColor);
#endif

#if 0
	count = 2;
	                strcpy(top_text[0].name, test_msg_hz2[0]);
                        strcpy(top_text[1].name, title_warn_106[0]);
                        strcpy(top_text[2].name, title_warn_106[2]);
                        top_text[0].filesize = 20;
                        top_text[1].filesize = 20;
                        top_text[2].filesize = 20;
                        top_text[0].color = 0xffffffff;
                        top_text[1].color = 0x191970ff;
                        top_text[2].color = 0x191970ff;

                        top_warn[0].formColor = 0xff0000ff;
                        top_warn[1].formColor = 0xffff00ff;
                        top_warn[0].text[0] = &top_text[0];
                        top_warn[1].text[0] = &top_text[1];
                        top_warn[1].text[1] = &top_text[2];
                        top_warn[0].textCnt = 1;
                        top_warn[1].textCnt = 2;
#endif
	//JointWarn_create_top(hdc, pwarn, count, width, height);
	JointWarn_create_top(hdc, top_warn, g_top_count, width, height);
}

void JointWarn_create_form(HDC hdc, struct warnForm *warn, int count)
{
	int border_len;
	int form_len;
	int start_x, start_y;
	int red, green, blue;
	int i;

	SetBkMode(hdc,BM_TRANSPARENT);
	
	border_len = 15;
	form_len = (MWINDOW_RX - (border_len * (count + 1))) / count;
	printf("form_len = %d\n", form_len);
	
	SetBkMode(hdc,BM_TRANSPARENT);
	red = (warn[0].formColor & 0xff000000) >> 24; 
	green = (warn[0].formColor & 0x00ff0000) >> 16; 
	blue = (warn[0].formColor & 0x0000ff00) >> 8; 
	SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));

	start_x = border_len;
	start_y = warn[0].starty;
	for(i=0; i<count; i++){
		start_x += ((form_len + border_len) * i);
		form_obj[i].point_start.x = start_x;
		form_obj[i].point_start.y = start_y;
		form_obj[i].point_end.x = start_x + form_len;
		form_obj[i].point_end.y = start_y + warn[0].height;
		FillBox(hdc, start_x, start_y, form_len, warn[0].height);
	}
	
}

void JointWarn_create_select(HDC hdc, struct warnForm *warn, int row)
{
	int border_len;
	unsigned char red, green, blue;
	int i;

	SetBkMode(hdc,BM_TRANSPARENT);
	
	border_len = 5;
	select_width = (form_obj[0].point_end.x - form_obj[0].point_start.x) - 2 * border_len;
	select_height = ((form_obj[0].point_end.y - form_obj[0].point_start.y) - (row+1) * border_len) / row;
	
	red = (warn[0].formColor & 0xff000000) >> 24; 
	green = (warn[0].formColor & 0x00ff0000) >> 16; 
	blue = (warn[0].formColor & 0x0000ff00) >> 8; 
	SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));

	for(i=0; i<SEL_MAX_COUNT; i++){
		if(i<row){
			select_obj[i].point_start.x = form_obj[0].point_start.x + border_len;
			select_obj[i].point_start.y = form_obj[0].point_start.y + (select_height + border_len) * i + border_len;
			select_obj[i].point_end.x = select_obj[i].point_start.x + select_width;			
			select_obj[i].point_end.y = select_obj[i].point_start.y + select_height;			
			FillBox(hdc, select_obj[i].point_start.x, select_obj[i].point_start.y, select_width, select_height);
		}else{
			select_obj[i].point_start.x = form_obj[1].point_start.x + border_len;
			select_obj[i].point_start.y = form_obj[1].point_start.y + (select_height + border_len) * (i - row) + border_len;
			select_obj[i].point_end.x = select_obj[i].point_start.x + select_width;			
			select_obj[i].point_end.y = select_obj[i].point_start.y + select_height;			
			FillBox(hdc, select_obj[i].point_start.x, select_obj[i].point_start.y, select_width, select_height);
		}
	}

	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	for(i=0; i<SEL_MAX_COUNT; i++){
		FillBox(hdc, select_obj[i].point_start.x + (select_width >> 1), select_obj[i].point_start.y, (select_width >> 1), select_height);
	}
}

void JointWarn_repaint_select(HDC hdc, struct warnForm *warn, int index, int type)
{
	unsigned char red, green, blue;
	PLOGFONT s_font;
		
	SetBkMode(hdc,BM_TRANSPARENT);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                               FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, \
			       FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn[0].text[0]->filesize, 0);
        SelectFont(hdc, s_font);

	if(type == 1){
		red = (warn[0].formColor & 0xff000000) >> 24; 
		green = (warn[0].formColor & 0x00ff0000) >> 16; 
		blue = (warn[0].formColor & 0x0000ff00) >> 8; 
		SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		FillBox(hdc, select_obj[index].point_start.x, select_obj[index].point_start.y, (select_width >> 1), select_height);
		
		red = (warn[0].text[0]->color & 0xff000000) >> 24; 
		green = (warn[0].text[0]->color & 0x00ff0000) >> 16; 
		blue = (warn[0].text[0]->color & 0x0000ff00) >> 8; 
		SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		TextOut(hdc, select_obj[index].point_start.x + warn[0].text[0]->offsetx, select_obj[index].point_start.y + warn[0].text[0]->offsety, warn[0].text[0]->name);
	}
	if(type == 2){
		SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
		FillBox(hdc, select_obj[index].point_start.x + (select_width >> 1), select_obj[index].point_start.y, (select_width >> 1), select_height);
		
		red = (warn[0].text[0]->color & 0xff000000) >> 24; 
		green = (warn[0].text[0]->color & 0x00ff0000) >> 16; 
		blue = (warn[0].text[0]->color & 0x0000ff00) >> 8; 
		SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		TextOut(hdc, select_obj[index].point_start.x + (select_width >> 1) + warn[0].text[0]->offsetx, select_obj[index].point_start.y + warn[0].text[0]->offsety, warn[0].text[0]->name);
	}
	
	DestroyLogFont(s_font);
}

void JointWarn_create_title(HDC hdc, struct warnForm *warn, unsigned char border)
{
	PLOGFONT s_font;
	unsigned char red, green, blue;
	int start_x, start_y;

	SetBkMode(hdc,BM_TRANSPARENT);

	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                               FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, \
			       FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn[0].text[0]->filesize, 0);
        SelectFont(hdc, s_font);
	
	start_x = warn[0].startx;
	start_y = warn[0].starty;

	red = (warn[0].formColor & 0xff000000) >> 24; 
	green = (warn[0].formColor & 0x00ff0000) >> 16; 
	blue = (warn[0].formColor & 0x0000ff00) >> 8; 
	SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
	FillBox(hdc, start_x, start_y, warn[0].width, warn[0].height);

	if(border == 1){
		red = (warn[0].borderColor & 0xff000000) >> 24; 
		green = (warn[0].borderColor & 0x00ff0000) >> 16; 
		blue = (warn[0].borderColor & 0x0000ff00) >> 8;
		SetPenColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		SetPenWidth(hdc, 1);
		LineEx(hdc, start_x, start_y, start_x + warn[0].width, start_y); 
		LineEx(hdc, start_x, start_y + warn[0].height, start_x + warn[0].width, start_y + warn[0].height); 
	}
	
	red = (warn[0].text[0]->color & 0xff000000) >> 24;
        green = (warn[0].text[0]->color & 0x00ff0000) >> 16;
        blue = (warn[0].text[0]->color & 0x0000ff00) >> 8;
	SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
	TextOut(hdc, start_x + warn[0].text[0]->offsetx, start_y + warn[0].text[0]->offsety, warn[0].text[0]->name);
	
	DestroyLogFont(s_font);
}

void jointwarn_crate_top_title(HDC hdc)
{
	struct warnForm warn[1];
	struct textStruct testText[3];
	int len;

	warn[0].startx = 0;
	warn[0].starty = 10;
	warn[0].width = MWINDOW_RX;
	warn[0].height = 50;
	if(0 == strcmp("green", sel_title_color)){
		warn[0].formColor = 0x00cd00ff;
	}else{
		warn[0].formColor = 0xff0000ff;
	}
	//warn[0].formColor = 0x3cb371ff;
	warn[0].borderColor = 0xffff00ff;
	testText[0].color = 0xffffffff;
	testText[0].filesize = 30;
	testText[0].offsety = 8;
	len = strlen(sel_title) > 48 ? 48 : strlen(sel_title);
	memset(testText[0].name, 0, 50);
	memcpy(testText[0].name, sel_title, len);
	warn[0].text[0] = &testText[0];
	testText[0].offsetx = (MWINDOW_RX - (FONT30_PIXEL * len)) >> 1;
	JointWarn_create_title(hdc, warn, 1);



}

void JointWarn_create_msg(HDC hdc, struct warnForm *warn, int cnt)
{
	PLOGFONT s_font;
	int start_x, start_y;
	int width = 0;
	int height = 0;
	int i;
	unsigned char red, green, blue;

	SetBkMode(hdc,BM_TRANSPARENT);

	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                               FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn[0].text[0]->filesize, 0);
        SelectFont(hdc, s_font);
	
	for(i=0; i<cnt; i++){
		width = warn[i].width > width ? warn[i].width : width; 
		height += warn[i].height;
	}

	start_x = (MWINDOW_RX - width) >> 1;
	start_y = (SPARE_Y - height) >> 1;

	for(i=0; i<cnt; i++){
		red = (warn[i].formColor & 0xff000000) >> 24; 
		green = (warn[i].formColor & 0x00ff0000) >> 16; 
		blue = (warn[i].formColor & 0x0000ff00) >> 8; 
		if(i > 0){
			start_y += warn[i-1].height;
		}
		SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		FillBox(hdc, start_x, start_y, width, warn[i].height);

		red = (warn[i].text[0]->color & 0xff000000) >> 24;
                green = (warn[i].text[0]->color & 0x00ff0000) >> 16;
                blue = (warn[i].text[0]->color & 0x0000ff00) >> 8;
		SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		TextOut(hdc, start_x + warn[i].text[0]->offsetx, start_y + warn[i].text[0]->offsety, warn[i].text[0]->name);
	}

	DestroyLogFont(s_font);
}

int JointWarn_calc_msglen(unsigned char * msg)
{
	int font_len, font_cnt;

	font_cnt = strlen(msg) + 2;
	printf("font_cnt = %d\n", font_cnt);
	font_len = FONT30_PIXEL * font_cnt;
	return font_len;
}

void JointWarn_create_backbtn(HDC hdc){

	PLOGFONT s_font;
	SetBkMode(hdc,BM_TRANSPARENT);

        back_width = 120;
        back_height = 50;
        btn_back_1.point_start.x = BACK_XOFFSET;
        btn_back_1.point_start.y = SPARE_Y + 35;
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

}


void JointWarn_create_spare(HDC hdc){

	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
        FillBox(hdc, 0, SPARE_Y, MWINDOW_RX, MWINDOW_BY - SPARE_Y);
	JointWarn_create_backbtn(hdc);
}

void JointWarn_paint_back(HDC hdc, int color){

	unsigned char red, green, blue;

	red = (color & 0xff000000) >> 24;	
	green = (color & 0x00ff0000) >> 16;	
	blue = (color & 0x0000ff00) >> 8;	
	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
        FillBox(hdc, 0, 0, MWINDOW_RX, MWINDOW_BY);

}

void jointwarn_repaint_flag(HDC hdc, int left, int right)
{
        if(left == 0){
                SetBrushColor(hdc, RGBA2Pixel(hdc, 0xB3, 0xB3, 0xB3, 0xFF));
                FillPolygon(hdc, s_point[0], 3);
                btn_front_page_1.active = 0;
        }else{
                SetBrushColor(hdc, RGBA2Pixel(hdc, 0x00, 0xFF, 0x00, 0xFF));
                FillPolygon(hdc, s_point[0], 3);
                btn_front_page_1.active = 1;
        }

        if(right == 0){
                SetBrushColor(hdc, RGBA2Pixel(hdc, 0xB3, 0xB3, 0xB3, 0xFF));
                FillPolygon(hdc, s_point[1], 3);
                btn_next_page_1.active = 0;
        }else{
                SetBrushColor(hdc, RGBA2Pixel(hdc, 0x00, 0xFF, 0x00, 0xFF));
                FillPolygon(hdc, s_point[1], 3);
                btn_next_page_1.active = 1;
        }

}


void JointWarn_create_flag(HDC hdc, int total_cnt, int win_cnt)
{
	int left, right;

	left = 0;
	right = 0;


	page_cnt1 = 0;	
	btn_front_page_1.point_start.x = 10;
        btn_front_page_1.point_start.y = SPARE_Y + 10;
        btn_front_page_1.point_end.x = 50;
        btn_front_page_1.point_end.y = SPARE_Y + 50;
        btn_front_page_1.active = 0;
        btn_next_page_1.point_start.x = MWINDOW_RX - 10;
        btn_next_page_1.point_start.y = SPARE_Y + 10;
        btn_next_page_1.point_end.x = MWINDOW_RX - 50;
        btn_next_page_1.point_end.y = SPARE_Y + 50;
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

	if(total_cnt > win_cnt){
                right = 1;
        }
	jointwarn_repaint_flag(hdc, left, right);


}
