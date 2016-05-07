#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"


void JointWarn_create_105_2(HDC hdc)
{
	unsigned char msg_str[2][100];
	struct warnForm warn[2];
	struct textStruct text_msg[2];
	
	font_len1 = JointWarn_calc_msglen(text_msg[0].name);	
	font_len2 = JointWarn_calc_msglen(text_msg[1].name);

	font_len = font_len1 > font_len2 ? font_len1 : font_len2;

	tmp = (font_len - font_len1) >> 1;	
	strcpy(text_msg[0].name, test_menu_hz1);
	text_msg[0].color = 0xffffffff;
	text_msg[0].offsetx = FONT30_PIXEL + tmp * FONT30_PIXEL;
	text_msg[0].filesize = 30;

	tmp = (font_len - font_len2) >> 1;	
	strcpy(text_msg[1].name, msg_hz1);
	text_msg[1].color = 0x0000ffff;
	text_msg[1].offsetx = FONT30_PIXEL + tmp * FONT30_PIXEL;
	text_msg[1].filesize = 30;
}
