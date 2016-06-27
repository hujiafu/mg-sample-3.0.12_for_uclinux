
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"
#include "JointWarn_Main.h"
#include "JointWarn_Json.h"
#include "JointWarn_network.h"

extern int window_no;
extern int form_tot_cnt;
extern int total_frame_cnt;
extern int window_frame_cnt;
extern const char * test_msg_hz2[];
extern const char * test_tmsg_hz1[];
extern unsigned char test_106_1[];
extern unsigned char select_project_str[50];
extern const char * title_warn_106[];
extern const unsigned char request_oper[];
extern unsigned char udp_buf[UDP_MAX_LEN];
extern int g_update_sel_index;
extern int g_sel_count;

struct selStruct * gPsel;

unsigned char * JointWarn_106_get_data(int sel_index){
	//TODO: get data from server
        
	unsigned char pro_no_sel[4];
        unsigned char request_pro_str[100];

        sprintf(pro_no_sel, "%d", sel_index);
        strcpy(request_pro_str, request_oper);
        strcat(request_pro_str, pro_no_sel);
        strcat(request_pro_str, "\"}");
        JointWarn_udp_send(request_pro_str, 0);

	
	return udp_buf; //only for test

}

struct selStruct * JointWarn_106_parepar_data(unsigned char * originStr)
{
	struct selStruct * psel;
	unsigned int ptr;

	total_frame_cnt = JointAnalysisCmdLine(originStr, &ptr);	
	psel = (struct selStruct *)ptr;

	return psel;
}

void JointWarn_free_data(struct selStruct * psel)
{	
	if(psel != NULL){
		free(psel);
	}
}

void JointWarn_106_repaint_sel(HDC hdc, struct selStruct * psel, int start_index, int count)
{
	int i;
	struct textStruct testText[1];
	struct warnForm warn[1];
	
	if(psel != NULL){
		for(i=0; i<count; i++){
			testText[0].color = 0xffffffff;
			testText[0].filesize = 20;
			testText[0].offsetx = 5;
			testText[0].offsety = 20;
			strcpy(testText[0].name, psel[i + start_index].text1);
			if(0 == strcmp("green", psel[i + start_index].color)){
				warn[0].formColor = 0x3cb371ff;
			}else{
				warn[0].formColor = 0xff0000ff;
			}
			warn[0].text[0] = &testText[0];
			JointWarn_repaint_select(hdc, warn, i, 1);
		
			testText[0].color = 0xff0000ff;
			testText[0].filesize = 20;
			testText[0].offsetx = 5;
			testText[0].offsety = 20;
			strcpy(testText[0].name, psel[i + start_index].text2);
			warn[0].formColor = 0xffffffff;
			warn[0].text[0] = &testText[0];
			JointWarn_repaint_select(hdc, warn, i, 2);
		}	
	}


}

void JointWarn_clear_sel(HDC hdc)
{
	struct warnForm warn[1];

	warn[0].formColor = 0x3cb371ff;
	JointWarn_create_select(hdc, warn);
}

void JointWarn_repaint_106(HDC hdc, struct warnForm *warn, struct warnForm *warn1, int cnt)
{	
	int i;
	struct warnForm warn2[1];

	warn2[0].formColor = 0x3cb371ff;
	JointWarn_create_select(hdc, warn2);
	
	for(i=0; i<cnt; i++){
		JointWarn_repaint_select(hdc, warn[i], i, 1);
		JointWarn_repaint_select(hdc, warn1[i], i, 2);
	}
}

void jointwarn_create_sel_win(HDC hdc, struct selStruct * psel, struct textStruct *msg, int msg_cnt)
{
	unsigned int back_color;
	unsigned int count;
	int row;
	struct warnForm warn[1];
	back_color = 0x473c8bff;
        JointWarn_paint_back(hdc, back_color);
	
	count = 2;
	warn[0].formColor = 0x1e90ffff;
	warn[0].starty = 70;
	warn[0].height = 290;
	JointWarn_create_form(hdc, warn, count);

	warn[0].formColor = 0x3cb371ff;
	row = 4;
	JointWarn_create_select(hdc, warn, row);
	
	count = g_sel_count > SEL_MAX_COUNT ? SEL_MAX_COUNT : g_sel_count;
	form_tot_cnt = g_sel_count / SEL_MAX_COUNT + 1;
	JointWarn_106_repaint_sel(hdc, psel, 0, count);
	jointwarn_prompt(hdc, msg, msg_cnt);

	jointwarn_create_flag(hdc);
	jointwarn_paint_back(hdc);
	jointwarn_crate_top_title(hdc);
}

void JointWarn_create_106(HDC hdc, int index, struct selStruct * psel)
{
	unsigned int back_color;
	unsigned int count;
	struct warnForm warn[1];
	struct warnForm testWarn[3];
	struct textStruct testText[3];
	unsigned char * origin_str;
	int len;

	int i;
	
	
	if(psel != NULL)
	{
	if(index == 1)
		window_no = WIN_106_1_NO;
	if(index == 2)
		window_no = WIN_106_2_NO;
	if(index == 3)
		window_no = WIN_107_NO;
	window_frame_cnt = SEL_MAX_COUNT;

	back_color = 0x473c8bff;
        JointWarn_paint_back(hdc, back_color);
	JointWarn_create_spare(hdc);

	//top title
	warn[0].startx = 0;
	warn[0].starty = 10;
	warn[0].width = MWINDOW_RX;
	warn[0].height = 50;
	warn[0].formColor = 0x3cb371ff;
	warn[0].borderColor = 0xffff00ff;
	testText[0].color = 0xffffffff;
	testText[0].filesize = 30;
	testText[0].offsety = 5;
	len = strlen(select_project_str) > 50 ? 50 : strlen(select_project_str);
	memset(testText[0].name, 0, 50);
	memcpy(testText[0].name, select_project_str, len);
	warn[0].text[0] = &testText[0];
	testText[0].offsetx = (MWINDOW_RX - (FONT30_PIXEL * len)) >> 1;
	JointWarn_create_title(hdc, warn, 1);
	
	//bottom title
	warn[0].startx = 0;
	warn[0].starty = 300;
	warn[0].width = MWINDOW_RX;
	warn[0].height = 50;
	warn[0].formColor = 0xffd700ff;
	warn[0].borderColor = 0xffff00ff;
	testText[0].color = 0x333399ff;
	testText[0].filesize = 30;
	testText[0].offsety = 10;
	len = strlen(title_warn_106[index - 1]) > 50 ? 50 : strlen(title_warn_106[index - 1]);
	memset(testText[0].name, 0, 50);
	memcpy(testText[0].name, title_warn_106[index - 1], len);
	warn[0].text[0] = &testText[0];
	testText[0].offsetx = (MWINDOW_RX - (FONT30_PIXEL * len)) >> 1;
	JointWarn_create_title(hdc, warn, 0);
	
	count = 2;
	warn[0].formColor = 0x1e90ffff;
	warn[0].starty = 70;
	warn[0].height = 220;
	JointWarn_create_form(hdc, warn, count);

	warn[0].formColor = 0x3cb371ff;
	JointWarn_create_select(hdc, warn);

	gPsel = psel;
	count = total_frame_cnt > SEL_MAX_COUNT ? SEL_MAX_COUNT : total_frame_cnt;
	form_tot_cnt = total_frame_cnt / SEL_MAX_COUNT + 1;
	JointWarn_106_repaint_sel(hdc, psel, 0, count);
	if(total_frame_cnt <= SEL_MAX_COUNT){
		JointWarn_free_data(psel);
	}

	JointWarn_create_flag(hdc, total_frame_cnt, SEL_MAX_COUNT);
	}
	else{

	}
#if 0	
	for(i=0; i<3; i++){
		testText[0].color = 0xffffffff;
		testText[0].filesize = 20;
		testText[0].offsetx = 5;
		testText[0].offsety = 20;
		strcpy(testText[0].name, test_msg_hz2[i]);
		testWarn[0].formColor = 0x3cb371ff;
		//testWarn[0].formColor = 0xff0000ff;
		testWarn[0].text[0] = &testText[0];
		
		JointWarn_repaint_select(hdc, testWarn, i, 1);
		
		testText[0].color = 0xff0000ff;
		testText[0].filesize = 20;
		testText[0].offsetx = 5;
		testText[0].offsety = 20;
		strcpy(testText[0].name, test_tmsg_hz1[0]);
		testWarn[0].formColor = 0xffffffff;
		testWarn[0].text[0] = &testText[0];
		
		JointWarn_repaint_select(hdc, testWarn, i, 2);
	}
#endif
}

void JointWarn_request_sel(HDC hdc, int pro_index)
{
	unsigned char * origin_str;
	struct selStruct * psel;
	
	origin_str = JointWarn_106_get_data(pro_index);
	psel = JointWarn_106_parepar_data(origin_str);

	JointWarn_create_106(hdc, g_update_sel_index, psel);

}
