
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"


extern const char * test_msg_hz2[];
extern const char * test_tmsg_hz1[];


void JointWarn_106_parper()
{
	
		testText[0].color = 0xffffffff;
		testText[0].filesize = 20;
		testText[0].offsetx = 5;
		testText[0].offsety = 20;
		strcpy(testText[0].name, test_msg_hz2[i]);
		testWarn[0].formColor = 0x3cb371ff;
		//testWarn[0].formColor = 0xff0000ff;
		testWarn[0].text[0] = &testText[0];

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

void JointWarn_create_106(HDC hdc, int index)
{
	unsigned int back_color;
	unsigned int count;
	struct warnForm warn[1];
	struct warnForm testWarn[3];
	struct textStruct testText[3];

	int i;

	back_color = 0x473c8bff;
        JointWarn_paint_back(hdc, back_color);
	JointWarn_create_spare(hdc);

	count = 2;
	warn[0].formColor = 0x1e90ffff;
	warn[0].starty = 70;
	warn[0].height = 220;
	JointWarn_create_form(hdc, warn, count);

	warn[0].formColor = 0x3cb371ff;
	JointWarn_create_select(hdc, warn);

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
}
