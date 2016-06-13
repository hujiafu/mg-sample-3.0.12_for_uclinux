#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"
#include "JointWarn_network.h"

extern const char test_menu_hz1[];
extern const char msg_hz1[];
extern const char msg_hz2[];
extern const char msg_hz3[];
extern unsigned char select_project_str[100];
extern const unsigned char request_oper[];
extern unsigned char udp_buf[UDP_MAX_LEN];

int index_105 = 0;


unsigned char * JointWarn_105_get_data(int pro_index){
        //TODO: get data from server

        unsigned char pro_no_sel[4];
        unsigned char request_pro_str[100];

        sprintf(pro_no_sel, "%d", pro_index);
        strcpy(request_pro_str, request_oper);
        strcat(request_pro_str, pro_no_sel);
        strcat(request_pro_str, "\"}");
        JointWarn_udp_send(request_pro_str, 0);


        return udp_buf; //only for test

}

int JointWarn_105_parepar_data(unsigned char * originStr)
{
        int index;
	unsigned int ptr;

        index = JointAnalysisCmdLine(originStr, &ptr);

        return index;
}



void JointWarn_create_105(HDC hdc, int pro_index)
{
	unsigned char msg_str[2][100];
	struct warnForm warn[2];
	struct textStruct text_msg[2];
	unsigned int back_color;
	int font_len, font_len1, font_len2;
	int tmp;
	int index;
	unsigned char * origin_str;

	origin_str = JointWarn_105_get_data(pro_index);
	index = JointWarn_105_parepar_data(origin_str);
	
	//strcpy(text_msg[0].name, test_menu_hz1);
	strcpy(text_msg[0].name, select_project_str);
	printf("test_menu_hz1 = %d\n", strlen(test_menu_hz1));
	if(index == 1){
		strcpy(text_msg[1].name, msg_hz2);
	}
	if(index == 2){
		strcpy(text_msg[1].name, msg_hz1);
	}
	if(index == 3){
		strcpy(text_msg[1].name, msg_hz3);
	}
	font_len1 = JointWarn_calc_msglen(text_msg[0].name);	
	font_len2 = JointWarn_calc_msglen(text_msg[1].name);
	printf("font_len1 = %d, font_len2 = %d\n", font_len1, font_len2);

	font_len = font_len1 > font_len2 ? font_len1 : font_len2;

	tmp = (font_len - font_len1) >> 1;	
	text_msg[0].color = 0xffffffff;
	text_msg[0].offsetx = 2*FONT30_PIXEL + tmp;
	text_msg[0].offsety = 18;
	text_msg[0].filesize = 30;
	printf("tmp = %d, offsetx = %d\n", tmp, text_msg[0].offsetx);

	tmp = (font_len - font_len2) >> 1;	
	text_msg[1].color = 0x0000ffff;
	text_msg[1].offsetx = 2*FONT30_PIXEL + tmp;
	text_msg[1].offsety = 18;
	text_msg[1].filesize = 30;
	printf("tmp = %d, offsetx = %d\n", tmp, text_msg[1].offsetx);

	warn[0].messageCount = 1;
	if(index == 1 || index == 3)
		warn[0].formColor = 0x228b22ff;
	if(index == 2)
		warn[0].formColor = 0xff0000ff;
	warn[0].width = font_len;
	warn[0].height = FONT30_HIGH_PIXEL * 2;
	warn[0].text[0] = &text_msg[0];
	
	warn[1].messageCount = 1;
	warn[1].formColor = 0xffff00ff;
	warn[1].width = font_len;
	warn[1].height = FONT30_HIGH_PIXEL * 2;
	warn[1].text[0] = &text_msg[1];

	back_color = 0x473c8bff;
	JointWarn_paint_back(hdc, back_color);
	JointWarn_create_spare(hdc);
	JointWarn_create_msg(hdc, warn, 2);

}

