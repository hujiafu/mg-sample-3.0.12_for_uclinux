#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"
#include "JointWarn_Json.h"
#include "JointWarn_network.h"
#include "helloworld_res_en.h"

#define NUM_PRE_LINE	3
#define NUM_ROWS	4
#define FONT35_PIXEL	19	//FORNT SIZE 35
#define FONT30_PIXEL	16	//FORNT SIZE 30
#define FONT30_HIGH_PIXEL	35
#define WARN_FRAME_HIGH		20

extern const char* menu_hz[];
//extern const char* warningText[];
//extern struct textStruct menu_hiz[];
//extern struct textStruct warn_msg[];
extern struct textStruct back;
extern int gRow;
extern int gColumn;
extern int window_frame_cnt;
extern int total_frame_cnt;
extern int form_count;
extern unsigned char test_102[];
extern unsigned char test_103[];
extern unsigned char test_104[];
extern unsigned char udp_buf[UDP_MAX_LEN];
extern const unsigned char request_area[];
extern const unsigned char request_equi[];
extern const unsigned char request_pro[];
extern unsigned char display_no_str[10];

int page_cnt1;
int form_tot_cnt;
int max_font_cnt;
	//SetBkMode(hdc,BM_TRANSPARENT);        
int back_width, back_height;
int partHeight, partWidth;
int x[100], y[100];
int hx[5], hy[5], vx[5], vy[5];
struct buttonObject btn_back_1;
struct buttonObject btn_front_page_1;
struct buttonObject btn_next_page_1;
struct buttonObject select_apply;
struct buttonObject select_canel;
POINT s_point[2][3];
struct formStruct * gPform_area;
struct formStruct * gPform_equi;
struct formStruct * gPform_pro;

void jointwarn_test(HDC hdc)
{
	SetBkMode(hdc,BM_TRANSPARENT);
	SetTextColor(hdc, COLOR_lightwhite);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x27, 0x40, 0x8B, 0xFF));
	FillBox(hdc, 5, 5, 200, 300);
}

unsigned char * JointWarn_back_request(){
	unsigned char request_str[500];
	JointWarnCreateRequest(request_str, "normal", display_no_str, "null", "true", "false", "null");
	JointWarn_udp_send(request_str, 0);
        return udp_buf; //only for test
}

unsigned char * JointWarn_sel_request(unsigned int sel_index){

	unsigned char request_str[500];
	unsigned char sel[4];

	sprintf(sel, "%d", sel_index);
	JointWarnCreateRequest(request_str, "normal", display_no_str, sel, "false", "false", "null");
	JointWarn_udp_send(request_str, 0);
        return udp_buf; //only for test

}

unsigned char * JointWarn_102_get_data(unsigned int sel_index){
        //TODO: get data from server
	unsigned char request_str[500];
	unsigned char sel[4];

	sprintf(sel, "%d", sel_index);
	JointWarnCreateRequest(request_str, "normal", display_no_str, sel, "false", "false", "null");
	JointWarn_udp_send(request_str, 0);
        return udp_buf; //only for test

}
unsigned char * JointWarn_103_get_data(unsigned int sel_index){
        //TODO: get data from server
	unsigned char sel[4];
	unsigned char request_str[500];

	sprintf(sel, "%d", sel_index);
	JointWarnCreateRequest(request_str, "normal", display_no_str, sel, "false", "false", "null");
	JointWarn_udp_send(request_str, 0);
        return udp_buf; //only for test

}
unsigned char * JointWarn_104_get_data(unsigned int sel_index){
        //TODO: get data from server
	unsigned char sel[4];
	unsigned char request_str[500];

	sprintf(sel, "%d", sel_index);

	JointWarnCreateRequest(request_str, "normal", display_no_str, sel, "false", "false", "null");

	JointWarn_udp_send(request_str, 0);
        return udp_buf; //only for test

}

void JointWarn_free_area_buf()
{
	if(gPform_area != NULL)
		free(gPform_area);
	gPform_area = NULL;
}

void JointWarn_free_equi_buf()
{
	if(gPform_equi != NULL)
		free(gPform_equi);
	gPform_equi = NULL;
}

void JointWarn_free_pro_buf()
{
	if(gPform_pro != NULL)
		free(gPform_pro);
	gPform_pro = NULL;
}


struct formStruct * JointWarn_102_4_parepar_data(unsigned char * originStr, int index)
{
        struct formStruct * psel;
        unsigned int ptr;

        total_frame_cnt = JointAnalysisCmdLine(originStr, &ptr);
	printf("total_frame_cnt = %d\n", total_frame_cnt);
        psel = (struct formStruct *)ptr;
	if(index == 0)
		gPform_area = psel;
	if(index == 1)
		gPform_equi = psel;
	if(index == 2)
		gPform_pro = psel;

        return psel;
}


//void jointwarn_paint_frame(HDC hdc, struct textStruct *text, int count)
void jointwarn_paint_frame(HDC hdc, struct formStruct *form, int count, int index)
{
	int i, j, k = 0;
	int font_len;
	int offsetx = 5;
	int offsety = 22;
	int filesize = 30;
	PLOGFONT s_font;
	
	if(index == 3)
		offsety = 10;

	SetBkMode(hdc,BM_TRANSPARENT);
	SetTextColor(hdc, COLOR_lightwhite);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x27, 0x40, 0x8B, 0xFF));
	for(i=0; i<gRow; i++){
		for(j=0; j<gColumn; j++){
			x[k] = vx[j] - partWidth + 5;
			y[k] = hy[i] - partHeight + 5;
			printf("x = %d, y = %d, %d, %d\n", x[k], y[k], partWidth - 10, partHeight - 10);
			FillBox(hdc, x[k], y[k], partWidth - 10, partHeight - 10);
			k++;
		}
	}
	k = 0;
	for(i=0; i<gRow; i++){
		for(j=0; j<gColumn; j++){
			if(k >= count)
				break;
			//s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
			//	FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, text[k].filesize, 0);
			s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
				FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, filesize, 0);
			SelectFont(hdc,s_font);
			//font_len = strlen(text[k].name);	
			font_len = strlen(form[k].text1);	
			printf("font_len = %d, start = %d\n", font_len, x[k]);
			//if(font_len >= 16){
			//	font_len = 0;
			//}else{
				font_len = (max_font_cnt - font_len) >> 1;
			//}
			//TextOut(hdc, x[k] + text[k].offsetx + (FONT30_PIXEL * font_len), y[k] + text[k].offsety, text[k].name);	
			TextOut(hdc, x[k] + offsetx + (FONT30_PIXEL * font_len), y[k] + offsety, form[k].text1);	
			DestroyLogFont(s_font);
			k++;
		}
	}
}

void jointwarn_paint_flag(HDC hdc, int left, int right)
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
void jointwarn_create_flag(HDC hdc)
{
	int left, right;

	btn_front_page_1.point_start.x = 300;
	btn_front_page_1.point_start.y = SPARE_Y + 20;
	btn_front_page_1.point_end.x = 340;
	btn_front_page_1.point_end.y = SPARE_Y + 50;
	btn_front_page_1.active = 0;
	btn_next_page_1.point_start.x = MWINDOW_RX - 300;
	btn_next_page_1.point_start.y = SPARE_Y + 20;
	btn_next_page_1.point_end.x = MWINDOW_RX - 340;
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
	
	left = 0;
	right = 0;
	if(total_frame_cnt > window_frame_cnt){
		right = 1;
	}	
	jointwarn_paint_flag(hdc, left, right);

}

void jointwarn_prompt(HDC hdc, struct textStruct * warn_text, int msg_cnt)
{
	int offset_x;
	int msgHeight;
	int start_x, start_y;
	int font_len, font_cnt;
	int i;
	PLOGFONT s_font;
	
	SetBkMode(hdc,BM_TRANSPARENT);        
	//SetBrushColor(hdc, RGBA2Pixel(hdc, 0x69, 0x69, 0x69, 0xFF));
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xD7, 0x00, 0xFF));

	msgHeight = FONT40_HIGH_PIXEL * msg_cnt;
	start_x = 0;
	start_y = MWINDOW_BY - msgHeight;
	FillBox(hdc, start_x, start_y, MWINDOW_RX, msgHeight);
	//SetTextColor(hdc, RGBA2Pixel(hdc, 0xff, 0xff, 0xff, 0xFF));
	SetTextColor(hdc, RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
	FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn_text[0].filesize, 0);
	SelectFont(hdc,s_font);
	
	for(i=0; i<msg_cnt; i++){
		font_cnt = strlen(warn_text[i].name);
		font_len = font_cnt * FONT30_PIXEL;
		offset_x = (MWINDOW_RX - font_len) >> 1;
		TextOut(hdc, offset_x + warn_text[i].offsetx, start_y + warn_text[i].offsety + FONT30_HIGH_PIXEL * i, warn_text[i].name);
	}
	DestroyLogFont(s_font);
}

void jointwarn_paint_warning(HDC hdc, struct textStruct * warn_text, int msg_linecnt)
{
	int offsety;
	int font_len, font_cnt = 0;
	int i, tmp;
	PLOGFONT s_font;

	SetBkMode(hdc,BM_TRANSPARENT);        
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	FillBox(hdc, 0 + 100, SPARE_Y, (BACK_XOFFSET - 100), MWINDOW_BY - SPARE_Y);
	if(msg_linecnt == 1){
		offsety = 30;
	}
	if(msg_linecnt == 2){
		offsety = 15;
	}
	if(msg_linecnt == 3){
		offsety = 0;
	}
	for(i=0; i<msg_linecnt; i++){
		tmp = strlen(warn_text[i].name);
		font_cnt = font_cnt > tmp ? font_cnt : tmp;
	}
	font_len = font_cnt * FONT30_PIXEL;
	printf("font_len = %d\n", font_len);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0x00, 0xFF));
	FillBox(hdc, 0 + 100, SPARE_Y + offsety + 3, (font_len + 10), warn_text[0].offsety + FONT30_HIGH_PIXEL * msg_linecnt);
	SetTextColor(hdc,COLOR_blue);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
	FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn_text[0].filesize, 0);
	SelectFont(hdc,s_font);
	for(i=0; i<msg_linecnt; i++){
		TextOut(hdc, 0 + 100 + warn_text[i].offsetx, SPARE_Y + offsety + 5 + warn_text[i].offsety + FONT30_HIGH_PIXEL * i, warn_text[i].name);
	}
	DestroyLogFont(s_font);


}

void jointwarn_paint_back(HDC hdc)
{
	PLOGFONT s_font;
	
	back_width = 80;
	back_height = 40;
	btn_back_1.point_start.x = BACK_XOFFSET;
	btn_back_1.point_start.y = SPARE_Y + 20;
	btn_back_1.point_end.x = btn_back_1.point_start.x + back_width;
	btn_back_1.point_end.y = btn_back_1.point_start.y + back_height;
	btn_back_1.active = 1;
	//SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x17, 0x30, 0x93, 0xFF));
	FillBox(hdc, btn_back_1.point_start.x, btn_back_1.point_start.y, back_width, back_height);	
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
		FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, back.filesize, 0);
	SelectFont(hdc,s_font);
	SetTextColor(hdc, COLOR_lightwhite);
	TextOut(hdc, btn_back_1.point_start.x + back.offsetx, btn_back_1.point_start.y + back.offsety, back.name);	
	DestroyLogFont(s_font);

}


//void jointwarn_crate_mainui(HDC hdc, struct textStruct * text, struct textStruct * warn_text, int msg_linecnt)
void jointwarn_crate_mainui(HDC hdc, struct formStruct * text, struct textStruct * warn_text, int msg_linecnt)
{
	int i, j;
	int font_len, font_cnt;
	int xx, yy;
	int left, right;
	int width, height;
	int offsety;
	int tmp;
	PLOGFONT s_font;

	printf("jointwarn_crate_mainui \n");
	width = MWINDOW_RX;
	height = MWINDOW_BY;

	SetBkMode(hdc,BM_TRANSPARENT);
	SetTextColor(hdc,COLOR_lightwhite);
	
	partHeight = SPARE_Y / (gRow);
	partWidth = width / gColumn;
	max_font_cnt = partWidth / FONT30_PIXEL;
	yy = partHeight;
	xx = partWidth;
	for(i=0; i<gRow; i++){
		hx[i] = 0;
		hy[i] = yy;
		yy += partHeight;
	}
	for(i=0; i<gColumn; i++){
		vx[i] = xx; 
		vy[i] = 0;
		xx += partWidth;
	}
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x20, 0xB2, 0xAA, 0xFF));
	FillBox(hdc, 0, 0, width, height);	
	
	for(i=0; i<gRow; i++){
		//DrawHDotLine(hdc, hx[i], hy[i], width);
		LineEx(hdc, hx[i], hy[i], width, hy[i]);
	}
	for(i=0; i<gColumn; i++){
		//DrawVDotLine(hdc, vx[i], vy[i], height);	
		//LineEx(hdc, vx[i], vy[i], vx[i], height - partHeight);
		LineEx(hdc, vx[i], vy[i], vx[i], SPARE_Y);
	}

	form_tot_cnt = total_frame_cnt / window_frame_cnt;
	if(total_frame_cnt % window_frame_cnt != 0){
		form_tot_cnt += 1;
	}
	form_count = total_frame_cnt > window_frame_cnt ? window_frame_cnt : total_frame_cnt;
	page_cnt1 = 0; 
	jointwarn_paint_frame(hdc, text, form_count, msg_linecnt);
	
	printf("partWidth = %d, form_count = %d\n", partWidth, form_count);
	//Rectangle(hdc, partWidth, yy - partHeight + 20, width - (2 * partWidth), height - 20);
	//SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	//FillBox(hdc, 0, SPARE_Y, width, height - SPARE_Y);	




#if 0
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	FillBox(hdc, 0 + 100, SPARE_Y, (BACK_XOFFSET - 100), height - SPARE_Y);	
	if(msg_linecnt == 1){
		offsety = 30;
	}
	if(msg_linecnt == 2){
		offsety = 15;
	}
	if(msg_linecnt == 3){
		offsety = 0;
	}
	for(i=0; i<msg_linecnt; i++){
		tmp = strlen(warn_text[i].name);
		font_cnt = font_cnt > tmp ? font_cnt : tmp;
	}
	font_len = font_cnt * FONT30_PIXEL;
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0x00, 0xFF));
	FillBox(hdc, 0 + 100, SPARE_Y + offsety + 3, (font_len + 10), warn_text[0].offsety + FONT30_HIGH_PIXEL * msg_linecnt);	
	//SetBkMode(hdc,BM_TRANSPARENT);	
	SetTextColor(hdc,COLOR_blue);
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
		FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn_text[0].filesize, 0);
	SelectFont(hdc,s_font);
	for(i=0; i<msg_linecnt; i++){
		TextOut(hdc, 0 + 100 + warn_text[i].offsetx, SPARE_Y + offsety + 5 + warn_text[i].offsety + FONT30_HIGH_PIXEL * i, warn_text[i].name);	
	}
	DestroyLogFont(s_font);
#endif	
	//jointwarn_paint_warning(hdc, warn_text, msg_linecnt);
	jointwarn_prompt(hdc, warn_text, 1);





#if 0
	btn_front_page_1.point_start.x = 300;
	btn_front_page_1.point_start.y = yy - partHeight + 10;
	btn_front_page_1.point_end.x = 340;
	btn_front_page_1.point_end.y = yy - partHeight + 40;
	btn_front_page_1.active = 0;
	btn_next_page_1.point_start.x = width - 300;
	btn_next_page_1.point_start.y = yy - partHeight + 10;
	btn_next_page_1.point_end.x = width - 340;
	btn_next_page_1.point_end.y = yy - partHeight + 40;
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
	
	left = 0;
	right = 0;
	if(total_frame_cnt > window_frame_cnt){
		right = 1;
	}	
	jointwarn_paint_flag(hdc, left, right);
#endif
	jointwarn_create_flag(hdc);

#if 0
	back_width = 120;
	back_height = 50;
	btn_back_1.point_start.x = BACK_XOFFSET;
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
#endif	
	jointwarn_paint_back(hdc);
	//EndPaint(hWnd,hdc);	

}

void jointwarn_create_select(HDC hdc, struct textStruct * text, struct textStruct *warn)
{
	int frame_width = 400;
	int frame_height = 100;
	int start_x, start_y;
	int i;
	PLOGFONT s_font;
	
	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x20, 0xB2, 0xAA, 0xFF));
	FillBox(hdc, 0, 0, MWINDOW_RX, MWINDOW_BY);	
	
	SetTextColor(hdc, COLOR_lightwhite);

	for(i=0; i<2; i++){
		SetBrushColor(hdc, RGBA2Pixel(hdc, 0x27, 0x40, 0x8B, 0xFF));
		start_x = (MWINDOW_RX - frame_width) >> 1;
		if(i == 1){
			start_y = SPARE_Y >> 1;
			select_canel.point_start.x = start_x;
			select_canel.point_start.y = start_y;
			select_canel.point_end.x = start_x + frame_width;
			select_canel.point_end.y = start_y + frame_height;
			select_canel.active = 1;
		}else{
			start_y = ((SPARE_Y >> 1) - frame_height) >> 1;
			select_apply.point_start.x = start_x;
			select_apply.point_start.y = start_y;
			select_apply.point_end.x = start_x + frame_width;
			select_apply.point_end.y = start_y + frame_height;
			select_apply.active = 1;
		}
		FillBox(hdc, start_x, start_y, frame_width, frame_height);
			
		SetPenColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0x00, 0xFF));
        	SetPenWidth(hdc, 1);
        	LineEx(hdc, start_x + 1, start_y + 1, start_x + frame_width - 1, start_y + 1);
        	LineEx(hdc, start_x + frame_width - 1, start_y + 1, start_x + frame_width - 1, start_y + frame_height - 1);
        	LineEx(hdc, start_x + frame_width - 1, start_y + frame_height - 1, start_x + 1, start_y + frame_height - 1);
        	LineEx(hdc, start_x + 1, start_y + frame_height - 1, start_x + 1, start_y + 1);

		SetTextColor(hdc, COLOR_lightwhite);
		s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
			FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, text[i].filesize, 0);
		SelectFont(hdc,s_font);
		TextOut(hdc, start_x + text[i].offsetx, start_y + text[i].offsety, text[i].name);	
		DestroyLogFont(s_font);
	}

	//SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	//FillBox(hdc, 0, SPARE_Y, MWINDOW_RX, MWINDOW_BY - SPARE_Y);	
	//jointwarn_paint_warning(hdc, warn, 1);
	jointwarn_prompt(hdc, warn, 1);
	jointwarn_paint_back(hdc);
	//start_x = (MWINDOW_RX - frame_width) >> 1;
	//start_y = (SPARE_Y >> 1);
	//FillBox(hdc, start_x, start_y, frame_width, frame_height);	
//	SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
//	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
		FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, text[k].filesize, 0);
//	SelectFont(hdc,s_font);
}
