
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include "pos_main.h"

HWND hMainWnd;
HDC	ghdc;

extern unsigned char gtime[20];

unsigned char posStr[50];
unsigned char posIdStr[10];
unsigned long posId = 1;
unsigned int  posSize;
unsigned int  posCount;
long usedCount;
long leaveCount;
unsigned char leaveStr[10];


void display_time(){

	HDC hdc;
	hdc = BeginPaint(hMainWnd);
	get_time();
	FillBox(hdc, 0, 400, MWINDOW_RX, 80);
	TextOut(ghdc, 20, 420, gtime);
	EndPaint(hMainWnd, hdc);
}

int timer_init(){

	int res = 0;
	struct itimerval tick;
    
	signal(SIGALRM, display_time);
	memset(&tick, 0, sizeof(tick));

	//Timeout to run first time
	tick.it_value.tv_sec = 1;
	tick.it_value.tv_usec = 0;

	//After first, the Interval time for clock
	tick.it_interval.tv_sec = 1;
	tick.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
            printf("Set timer failed!\n");

}


int cal_pos_history(){

}

void pos_create_main_ui(HDC hdc){

	PLOGFONT s_font;


	SetBkMode(hdc,BM_TRANSPARENT);
	SetBrushColor(hdc, RGBA2Pixel(hdc, 0xFF, 0xFF, 0xFF, 0xFF));
	FillBox(hdc, MWINDOW_LX, MWINDOW_TY, MWINDOW_RX, MWINDOW_BY);

	SetTextColor(hdc,RGBA2Pixel(hdc, 0x0, 0x0, 0x0, 0xFF));
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 40, 0);
        SelectFont(hdc,s_font);

	sprintf(posIdStr, "%d", posId);
	strcpy(posStr, "���� : ");
	strcat(posStr, posIdStr);
	TextOut(hdc, 20, 20, posStr);

	posSize = sizeof(struct posData);
	posCount = CONTEXT_SIZE / posSize;
	leaveCount = posCount - usedCount;
	printf("posCount = %d, leaveCount = %d\n", posCount, leaveCount);
	strcpy(posStr, "ʣ������ : ");
	sprintf(leaveStr, "%d", leaveCount);
	strcat(posStr, leaveStr);
	TextOut(hdc, 420, 20, posStr);
	DestroyLogFont(s_font);

	timer_init();

}

static int WinProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam)
{
	static BITMAP s_startbmp,s_background;
	static BITMAP s_bmp[6];
	static PLOGFONT s_font;
	static int s_sel=0;
	static int s_selbak=0;
	static int pre_x, pre_y;
	int i;
	int cnt;
	int left_flag, right_flag;
	HDC hdc;
	
	switch(message)
	{
		case MSG_CREATE:
			printf("MSG_CREATE ok\n");
   			break;
  		case MSG_PAINT:
			printf("MSG_PAINT begin1\n");
			hdc = BeginPaint(hWnd);
			pos_create_main_ui(hdc);
			EndPaint(hWnd,hdc);
			break;
		case MSG_LBUTTONDOWN:
			printf("MSG_LBUTTONDOWN\n");
			break;
		case MSG_RBUTTONDOWN:
			printf("MSG_RBUTTONDOWN:\n");
			break;
		case MSG_CHAR:
			printf("MSG_CHAR ok\n");
#if 0
			i = 0;
			switch(wParam)
			{
				case '1':
					if(s_sel>3)
					{
						s_selbak = s_sel;
						s_sel = s_sel-4;
						i = 1;
					}
					break;
				case '2':
					if(s_sel<5)
					{
						s_selbak = s_sel;
						s_sel++;
						i = 1;
					}
					else
					{
						s_selbak = 0;
						s_sel = 5;
					}
					break;
				case '3':
					if(s_sel<4)
					{
						s_selbak = s_sel;
						s_sel += 4;
						if(s_sel>5)s_sel=5;
						i = 1;
					}
					break;
				case '6':
					if(s_sel<=0)
					{
						s_selbak = 5;
						s_sel= 0;
					}
					else
					{
						s_selbak = s_sel;
						s_sel--;
						i = 1;
					}
					break;
				case '8':
					MessageBox(hMainWnd,"�������ڽ���...","��ʾ",MB_OK);
					break;
				
				default:
					break;
			}
			
			if(i==1)
			{
				hdc = BeginPaint(hWnd);

				SetPenColor(hdc,COLOR_lightgray);
				if(s_selbak<4)
				{
					Rectangle(hdc,8,s_selbak*70+8,60,s_selbak*70+60);
				}
				else
				{
					Rectangle(hdc,78,(s_selbak-4)*70+8,130,(s_selbak-4)*70+60);
				}

				SetPenColor(hdc,COLOR_black);
				if(s_sel<4)
				{
					Rectangle(hdc,8,s_sel*70+8,60,s_sel*70+60);
				}
				else
				{
					Rectangle(hdc,78,(s_sel-4)*70+8,130,(s_sel-4)*70+60);
				}
				FillBoxWithBitmap(hdc,0,283,240,37,&s_startbmp);
				SetBkMode(hdc,BM_TRANSPARENT);
				SetTextColor(hdc,COLOR_lightwhite);
				SelectFont(hdc,s_font);
				TextOut(hdc,30,295,"�� ʼ ");
				SelectFont(hdc,s_font1);
				TextOut(hdc,130,295,menu_hz[s_sel]);

				EndPaint(hWnd,hdc);
			}
#endif
			break;
			
		case MSG_CLOSE:
		printf("MSG_CLOSE ok\n");
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;

		default:
			return(DefaultMainWinProc(hWnd,message,wParam,lParam));
	}
	return(0);	
}












int InitMainWindow(void)
{
	MAINWINCREATE window_info;

	window_info.dwStyle = WS_VISIBLE;
	window_info.dwExStyle = WS_EX_NONE;
	window_info.spCaption = "";	
  	window_info.hMenu = 0;
	window_info.hCursor = GetSystemCursor(0);
	window_info.hIcon = 0;
	window_info.MainWindowProc = WinProc;	
  	window_info.lx = MWINDOW_LX;
	window_info.ty = MWINDOW_TY;
	window_info.rx = MWINDOW_RX;
	window_info.by = MWINDOW_BY;
	window_info.iBkColor = COLOR_lightgray;
	window_info.dwAddData = 0;
	window_info.hHosting = HWND_DESKTOP;
	hMainWnd = CreateMainWindow(&window_info);
	if(hMainWnd == HWND_INVALID) return(0);
	else return(1);
}


int MiniGUIMain (int argc, const char* argv[])
{
	MSG Msg;
	
	InitMainWindow();	

	while(GetMessage(&Msg,hMainWnd))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	MainWindowThreadCleanup(hMainWnd);

	return 0;
}
