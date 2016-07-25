
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"
#include "JointWarn_Json.h"
#include "JointWarn_lib.h"

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
extern struct warnForm top_warn[2];
extern int g_top_count;
extern struct textStruct system_main;
extern struct buttonObject btn_sys_logger;
extern struct buttonObject btn_sys_area;
extern struct buttonObject btn_sys_work;
extern struct buttonObject btn_sys_error;
extern struct buttonObject btn_sys_volume;
extern struct buttonObject btn_sys_light;
extern struct buttonObject btn_sys_reset;
extern struct buttonObject btn_sys_back;
extern struct textStruct system_logger_txt;
extern struct textStruct system_area_txt;
extern struct textStruct system_work_txt;
extern struct textStruct system_error_txt;
extern struct textStruct system_volume_txt;
extern struct textStruct system_light_txt;
extern struct textStruct system_reset_txt;
extern struct textStruct system_back_txt;
extern int max_font_cnt;
extern struct selStruct g_sel[MAX_SEL_NUM];
extern int g_sel_count;

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
//struct warnForm top_warn[2];
//struct textStruct top_text[3];
int top_window;

void jointwarn_paint_cancel(HDC hdc)
{
	PLOGFONT s_font;

	btn_cancel_width = 60;
        btn_cancel_height = 30;
	btn_cancel.point_start.x = top_start_x + form_width - 80;
        btn_cancel.point_start.y = top_start_y + form_height - spare_height - 30;
        btn_cancel.point_end.x = btn_cancel.point_start.x + btn_cancel_width;
        btn_cancel.point_end.y = btn_cancel.point_start.y + btn_cancel_height;
        btn_cancel.active = 1;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
	FillBox(hdc, btn_cancel.point_start.x, btn_cancel.point_start.y, btn_cancel_width, btn_cancel_height);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 20, 0);
	SelectFont(hdc,s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, btn_cancel.point_start.x + 10, btn_cancel.point_start.y + 4, cancel_text[0]);
        DestroyLogFont(s_font);

}

void JointWarn_create_top(HDC hdc, struct warnForm *warn, int count, int width, int height, int has_canel)
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
	spare_height = 20;

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
	if(1 == has_canel){
		jointwarn_paint_cancel(hdc);
	}else{
		//auto canel after 3s
	}
}

void JointWarn_create_top_back(HDC hdc, int width, int height, int has_canel)
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
		
	SetPenColor(hdc, RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
	SetPenWidth(hdc, 1);
	LineEx(hdc, top_start_x, top_start_y, top_start_x + width, top_start_y); 
	LineEx(hdc, top_start_x + width, top_start_y, top_start_x + width, top_start_y + height); 
	LineEx(hdc, top_start_x + width, top_start_y + height, top_start_x, top_start_y + height); 
	LineEx(hdc, top_start_x, top_start_y + height, top_start_x, top_start_y); 
	
	//printf("%s\n", test_108_1);

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
	JointWarn_create_top(hdc, top_warn, g_top_count, width, height, has_canel);
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
		warn[0].formColor = 0x228822ff;
	}else{
		warn[0].formColor = 0xff0000ff;
	}
	//warn[0].formColor = 0x3cb371ff;
	warn[0].borderColor = 0xffff00ff;
	testText[0].color = 0xffffffff;
	testText[0].filesize = 30;
	testText[0].offsety = 10;
	len = strlen(sel_title) > 48 ? 48 : strlen(sel_title);
	memset(testText[0].name, 0, 50);
	memcpy(testText[0].name, sel_title, len);
	warn[0].text[0] = &testText[0];
	testText[0].offsetx = (MWINDOW_RX - (FONT30_PIXEL * len)) >> 1;
	JointWarn_create_title(hdc, warn, 1);



}

void JointWarn_create_msg(HDC hdc, struct warnForm *warn, int cnt, int border)
{
	PLOGFONT s_font;
	int start_x, start_y;
	int width = 0;
	int height = 0;
	int last_msg_h = 20;
	int i;
	unsigned char red, green, blue;

	SetBkMode(hdc,BM_TRANSPARENT);

	//s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        //                       FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn[0].text[0]->filesize, 0);
        //SelectFont(hdc, s_font);
	
	for(i=0; i<cnt; i++){
		width = warn[i].width > width ? warn[i].width : width; 
		height += warn[i].height;
	}
	//height += last_msg_h; //for last msg

	start_x = (MWINDOW_RX - width) >> 1;
	//start_y = (SPARE_Y - height) >> 1;
	if(1 == border){
		start_y = (SPARE_Y - height) >> 1;
	}else{
		start_y = (MWINDOW_BY - height) >> 1;
	}
	for(i=0; i<cnt ; i++){
		s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                               FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn[i].text[0]->filesize, 0);
        	SelectFont(hdc, s_font);
		red = (warn[i].formColor & 0xff000000) >> 24; 
		green = (warn[i].formColor & 0x00ff0000) >> 16; 
		blue = (warn[i].formColor & 0x0000ff00) >> 8; 
		if(i > 0){
			start_y += warn[i-1].height;
		}
		SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		FillBox(hdc, start_x, start_y, width, warn[i].height);
		if(1 == border){
			red = (warn[i].borderColor & 0xff000000) >> 24; 
			green = (warn[i].borderColor & 0x00ff0000) >> 16; 
			blue = (warn[i].borderColor & 0x0000ff00) >> 8; 
			SetPenColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
			SetPenWidth(hdc, 1);
			LineEx(hdc, start_x, start_y, start_x + width, start_y); 
			LineEx(hdc, start_x, start_y + warn[i].height, start_x + width, start_y + warn[i].height); 
		
		}
	
		red = (warn[i].text[0]->color & 0xff000000) >> 24;
                green = (warn[i].text[0]->color & 0x00ff0000) >> 16;
                blue = (warn[i].text[0]->color & 0x0000ff00) >> 8;
		SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		TextOut(hdc, start_x + warn[i].text[0]->offsetx, start_y + warn[i].text[0]->offsety, warn[i].text[0]->name);
		
		DestroyLogFont(s_font);
	}

	//DestroyLogFont(s_font);
		
#if 0
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                               FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 40, 0);
        SelectFont(hdc, s_font);
	red = (warn[i].formColor & 0xff000000) >> 24; 
	green = (warn[i].formColor & 0x00ff0000) >> 16; 
	blue = (warn[i].formColor & 0x0000ff00) >> 8; 
	if(i > 0){
		start_y += warn[i-1].height;
	}
	SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
	FillBox(hdc, start_x, start_y, width, warn[i].height + last_msg_h);
		red = (warn[i].text[0]->color & 0xff000000) >> 24;
                green = (warn[i].text[0]->color & 0x00ff0000) >> 16;
                blue = (warn[i].text[0]->color & 0x0000ff00) >> 8;
		SetTextColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
		TextOut(hdc, start_x + warn[i].text[0]->offsetx, start_y + warn[i].text[0]->offsety, warn[i].text[0]->name);
	DestroyLogFont(s_font);
#endif
}

int JointWarn_calc_msglen(unsigned char * msg, int len)
{
	int font_len, font_cnt;

	font_cnt = strlen(msg) + 2;
	printf("font_cnt = %d\n", font_cnt);
	font_len = len * font_cnt;
	return font_len;
}

void JointWarn_create_backbtn(HDC hdc){

	PLOGFONT s_font;
	SetBkMode(hdc,BM_TRANSPARENT);

        back_width = 80;
        back_height = 40;
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

static BITMAP s_bmp[10];
int sys_border_width, sys_border_height;
int sys_border_start_x, sys_border_start_y;
int sys_btn_len, sys_btn_height;

void jointwarn_system_log(HDC hdc)
{
	PLOGFONT s_font;
	int start_x, start_y;
	int width, height;
	
	width = MWINDOW_RX;
	height = 80;
	start_x = 0;
	start_y = 160;
 
	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0x00, 0x00, 0xFF));
        FillBox(hdc, start_x, start_y, width, height);
        s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, system_main.filesize, 0);
        SelectFont(hdc,s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, 0 + system_main.offsetx, start_y + system_main.offsety, system_main.name);
        DestroyLogFont(s_font);

}

void jointwarn_system_main_btn(HDC hdc, struct buttonObject *btn, int btn_len, int index, struct textStruct *text)
{
	PLOGFONT s_font;
	int border = 5;
	int btn_height;
	int btn_width;

	btn_width = btn_len - 2;
	btn_height = sys_border_height - 2 * border;
	sys_btn_height = btn_height;
        btn->point_start.x = sys_border_start_x + border + 2 + (index - 1) * btn_len;
        btn->point_start.y = sys_border_start_y + border;
        btn->point_end.x = btn->point_start.x + btn_len;
        btn->point_end.y = btn->point_start.y + btn_height;
        btn->active = 1;

	SetPenColor(hdc, RGBA2Pixel(hdc, 0xff, 0xff, 0xff, 0xFF));
	SetPenWidth(hdc, 2);
	LineEx(hdc, btn->point_start.x, btn->point_start.y, btn->point_start.x + btn_len, btn->point_start.y); 
	LineEx(hdc, btn->point_start.x + btn_len, btn->point_start.y, btn->point_start.x + btn_len, btn->point_start.y + btn_height); 
	LineEx(hdc, btn->point_start.x + btn_len, btn->point_start.y + btn_height, btn->point_start.x, btn->point_start.y + btn_height); 
	LineEx(hdc, btn->point_start.x, btn->point_start.y + btn_height, btn->point_start.x, btn->point_start.y); 
	
        s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, text->filesize, 0);
        SelectFont(hdc, s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, btn->point_start.x + text->offsetx, btn->point_start.y + text->offsety, text->name);
        DestroyLogFont(s_font);
}	

void jointwarn_system_create_bottom(HDC hdc)
{
	int start_x, start_y;
	int width, height;
	int border_len;
	int btn_len;

	width = MWINDOW_RX;
	height = 80;
	start_x = 0;
	start_y = 400;

	border_len = 10;
	sys_border_start_x = border_len;
	sys_border_start_y = start_y + border_len;
	sys_border_width = width - (2 * border_len);
	sys_border_height = height - (2 * border_len);

	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x80, 0x80, 0x80, 0xFF));
        FillBox(hdc, start_x, start_y, width, height);
	
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x14, 0x41, 0x85, 0xFF));
        FillBox(hdc, sys_border_start_x, sys_border_start_y, sys_border_width, sys_border_height);
		
	SetPenColor(hdc, RGBA2Pixel(hdc, 0xff, 0xff, 0xff, 0xFF));
	SetPenWidth(hdc, 1);
	LineEx(hdc, sys_border_start_x, sys_border_start_y, sys_border_start_x + sys_border_width, sys_border_start_y); 
	LineEx(hdc, sys_border_start_x + sys_border_width, sys_border_start_y, sys_border_start_x + sys_border_width, sys_border_start_y + sys_border_height); 
	LineEx(hdc, sys_border_start_x + sys_border_width, sys_border_start_y + sys_border_height, sys_border_start_x, sys_border_start_y + sys_border_height); 
	LineEx(hdc, sys_border_start_x, sys_border_start_y + sys_border_height, sys_border_start_x, sys_border_start_y); 


	sys_btn_len = (sys_border_width - 10)/ 8;
	jointwarn_system_main_btn(hdc, &btn_sys_logger, sys_btn_len, 1, &system_logger_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_area, sys_btn_len, 2, &system_area_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_work, sys_btn_len, 3, &system_work_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_error, sys_btn_len, 4, &system_error_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_volume, sys_btn_len, 5, &system_volume_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_light, sys_btn_len, 6, &system_light_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_reset, sys_btn_len, 7, &system_reset_txt);
	jointwarn_system_main_btn(hdc, &btn_sys_back, sys_btn_len, 8, &system_back_txt);


}

void jointwarn_system_create_volume(HDC hdc)
{
	PLOGFONT s_font;
	int start_x, start_y;
	int png_width = 126;
	int png_height = 102;	
	LoadBitmap(HDC_SCREEN,&s_bmp[1],"/usr/local/minigui/local/share/minigui/res/bmp/volume_logo.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[2],"/usr/local/minigui/local/share/minigui/res/bmp/up.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[3],"/usr/local/minigui/local/share/minigui/res/bmp/down.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[4],"/usr/local/minigui/local/share/minigui/res/bmp/process0.png");
	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x22, 0x92, 0xdd, 0xFF));
        FillBox(hdc, 0, 0, MWINDOW_RX, MWINDOW_BY - 80);
	
	start_x = (MWINDOW_RX - png_width) >> 1;
	start_y = 100;

	FillBoxWithBitmap(hdc, start_x, start_y, png_width, png_height, &s_bmp[1]);
	start_x = 150;
	FillBoxWithBitmap(hdc, start_x, start_y + png_height + 40, 40, 40, &s_bmp[3]);
	start_x += 40;
	start_x += 15;
	FillBoxWithBitmap(hdc, start_x, start_y + png_height + 42, 393, 33, &s_bmp[4]);
	start_x += 393;
	start_x += 15;
	FillBoxWithBitmap(hdc, start_x, start_y + png_height + 40, 40, 40, &s_bmp[2]);

	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xf9, 0x60, 0x3a, 0xFF));
        FillBox(hdc, btn_sys_volume.point_start.x + 1, btn_sys_volume.point_start.y + 1, sys_btn_len - 2, sys_btn_height - 2);
        
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, system_volume_txt.filesize, 0);
        SelectFont(hdc, s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, btn_sys_volume.point_start.x + system_volume_txt.offsetx, btn_sys_volume.point_start.y + system_volume_txt.offsety, system_volume_txt.name);
        DestroyLogFont(s_font);
}

void jointwarn_system_create_light(HDC hdc)
{
	PLOGFONT s_font;
	int start_x, start_y;
	int png_width = 178;
	int png_height = 178;	
	
	LoadBitmap(HDC_SCREEN,&s_bmp[5],"/usr/local/minigui/local/share/minigui/res/bmp/light_logo.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[6],"/usr/local/minigui/local/share/minigui/res/bmp/up.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[7],"/usr/local/minigui/local/share/minigui/res/bmp/down.png");
	LoadBitmap(HDC_SCREEN,&s_bmp[8],"/usr/local/minigui/local/share/minigui/res/bmp/process0.png");
	
	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x22, 0x92, 0xdd, 0xFF));
        FillBox(hdc, 0, 0, MWINDOW_RX, MWINDOW_BY - 80);
	
	start_x = (MWINDOW_RX - png_width) >> 1;
	start_y = 80;

	FillBoxWithBitmap(hdc, start_x, start_y, png_width, png_height, &s_bmp[5]);
	start_x = 150;
	FillBoxWithBitmap(hdc, start_x, start_y + png_height + 40, 40, 40, &s_bmp[7]);
	start_x += 40;
	start_x += 15;
	FillBoxWithBitmap(hdc, start_x, start_y + png_height + 42, 393, 33, &s_bmp[8]);
	start_x += 393;
	start_x += 15;
	FillBoxWithBitmap(hdc, start_x, start_y + png_height + 40, 40, 40, &s_bmp[6]);

	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xf9, 0x60, 0x3a, 0xFF));
        FillBox(hdc, btn_sys_light.point_start.x + 1, btn_sys_light.point_start.y + 1, sys_btn_len - 2, sys_btn_height - 2);
        
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, system_light_txt.filesize, 0);
        SelectFont(hdc, s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, btn_sys_light.point_start.x + system_light_txt.offsetx, btn_sys_light.point_start.y + system_light_txt.offsety, system_light_txt.name);
        DestroyLogFont(s_font);
}

void jointwarn_system_create_reset(HDC hdc)
{
	PLOGFONT s_font;
	int png_width = 180;
	int png_height = 180;
	int start_x, start_y;

	LoadBitmap(HDC_SCREEN,&s_bmp[0],"/usr/local/minigui/local/share/minigui/res/bmp/reset_logo.png");
	
	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x22, 0x92, 0xdd, 0xFF));
        FillBox(hdc, 0, 0, MWINDOW_RX, MWINDOW_BY - 80);

	start_x = (MWINDOW_RX - png_width) >> 1;
	start_y = 100;

	FillBoxWithBitmap(hdc, start_x, start_y, png_width, png_height, &s_bmp[0]);


	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xf9, 0x60, 0x3a, 0xFF));
        FillBox(hdc, btn_sys_reset.point_start.x + 1, btn_sys_reset.point_start.y + 1, sys_btn_len - 2, sys_btn_height - 2);
        
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, system_reset_txt.filesize, 0);
        SelectFont(hdc, s_font);
        SetTextColor(hdc, COLOR_lightwhite);
        TextOut(hdc, btn_sys_reset.point_start.x + system_reset_txt.offsetx, btn_sys_reset.point_start.y + system_reset_txt.offsety, system_reset_txt.name);
        DestroyLogFont(s_font);
}

void jointwarn_system_create_main(HDC hdc)
{
	unsigned int back_color;
	back_color = 0x2292ddff;

	JointWarn_paint_back(hdc, back_color);
	jointwarn_system_log(hdc);
	jointwarn_system_create_bottom(hdc);

	//jointwarn_system_create_volume(hdc);
	//jointwarn_system_create_light(hdc);
	//jointwarn_system_create_reset(hdc);

}

int logger_total_cnt;
int logger_perwin_cnt;
int logger_hx[LOGGER_ROW + 1], logger_hy[LOGGER_ROW + 1], logger_vx[LOGGER_COL + 1], logger_vy[LOGGER_COL + 1];
int logger_x[LOGGER_ROW * LOGGER_COL], logger_y[LOGGER_ROW * LOGGER_COL];
int g_logger_count;
int logger_row_step, logger_col_step;

void jointwarn_repaint_logerlist(HDC hdc, struct selStruct *warn)
{
	PLOGFONT s_font;
	int i;
	unsigned int color;
	unsigned char red, green, blue;
	int font_cnt, font_len;
	int tmp;
		
	max_font_cnt = 8;	
	SetBkMode(hdc,BM_TRANSPARENT);
		
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                	FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 20, 0);
        SelectFont(hdc, s_font);
        SetTextColor(hdc, COLOR_lightwhite);

	for(i=0; i<g_sel_count; i++){
		font_cnt = strlen(warn[i].text1) > max_font_cnt ? max_font_cnt : strlen(warn[i].text1);
		tmp = (max_font_cnt - font_cnt) >> 1;
		font_len = (logger_col_step - 3) / max_font_cnt;
		if(0 == strcmp("green", warn[i].color)){
			color = 0x228822ff;
		}else{
			color = 0xff0000ff;
		}
		red = (color & 0xff000000) >> 24;	
		green = (color & 0x00ff0000) >> 16;	
		blue = (color & 0x0000ff00) >> 8;	
		SetBrushColor(hdc, RGBA2Pixel(hdc, red, green, blue, 0xFF));
        	FillBox(hdc, logger_x[i] + 2, logger_y[i] + 2, logger_col_step - 3, logger_row_step - 3);
        	TextOut(hdc, logger_x[i] + 5 + (tmp * font_len), logger_y[i] + 25, warn[i].text1);
			
	}
        DestroyLogFont(s_font);
}

void jointwarn_paint_logerlist(HDC hdc)
{
	int logger_row_cnt = LOGGER_ROW;
	int logger_col_cnt = LOGGER_COL;
	int logger_win_width = 600;
	int logger_win_height = 300; 
	int start_x, start_y;
	int row_step, col_step;
	int i, j;
	

	start_x = (MWINDOW_RX - logger_win_width) >> 1; 
	start_y = (SPARE_Y - logger_win_height) >> 1; 
	row_step = logger_win_height / logger_row_cnt;
	col_step = logger_win_width / logger_col_cnt;
	logger_row_step = row_step;
	logger_col_step = col_step;

	logger_perwin_cnt = logger_col_cnt * logger_row_cnt;
		
	SetBkMode(hdc,BM_TRANSPARENT);
	//SetBrushColor(hdc, RGBA2Pixel(hdc, 0x22, 0x88, 0x22, 0xFF));
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x69, 0x69, 0x69, 0xFF));
        FillBox(hdc, start_x, start_y, logger_win_width, logger_win_height);
	
	SetPenColor(hdc, RGBA2Pixel(hdc, 0xff, 0xff, 0xff, 0xFF));
	SetPenWidth(hdc, 3);
	for(i=0; i<(LOGGER_ROW + 1); i++){
		logger_hx[i] = start_x;
		logger_hy[i] = start_y + row_step * i;
		printf("hx %d, hy %d\n", logger_hx[i], logger_hy[i]);
		LineEx(hdc, logger_hx[i], logger_hy[i], logger_hx[i] + logger_win_width, logger_hy[i]); 
		
	}
	for(j=0; j<(LOGGER_COL + 1); j++){
		logger_vx[j] = start_x + col_step * j;
		logger_vy[j] = start_y;
		LineEx(hdc, logger_vx[j], logger_vy[j], logger_vx[j], logger_vy[j] + logger_win_height); 
	}

	for(i=0; i<LOGGER_ROW; i++){
		for(j=0; j<LOGGER_COL; j++){
		
			logger_x[i*LOGGER_ROW + j] = logger_vx[j];
			logger_y[i*LOGGER_ROW + j] = logger_hy[i];
			printf("index %d, x %d,y %d\n", i*LOGGER_ROW + j, logger_x[i*LOGGER_ROW + j], logger_y[i*LOGGER_ROW + j]);
		}

	}

}

void jointwarn_create_logerlist(HDC hdc, struct selStruct * text, struct textStruct *msg)
{
	unsigned int back_color;
	back_color = 0x2292ddff;

	JointWarn_paint_back(hdc, back_color);
	jointwarn_paint_logerlist(hdc);
	jointwarn_repaint_logerlist(hdc, text);
	jointwarn_prompt(hdc, msg, 1);
	jointwarn_create_flag(hdc);
	jointwarn_paint_back(hdc);
}
