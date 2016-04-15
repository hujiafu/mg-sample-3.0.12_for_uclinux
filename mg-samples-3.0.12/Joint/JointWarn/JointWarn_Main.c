
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>


#ifdef _LANG_ZHCN
#include "helloworld_res_cn.h"
#elif defined _LANG_ZHTW
#include "helloworld_res_tw.h"
#else
#include "helloworld_res_en.h"
#endif
#include "JointWarn_Logic.h"
#include "JointWarn_UImain.h"

static char welcome_text [512];
static char msg_text [256];
static RECT welcome_rc = {10, 100, 600, 400};
static RECT msg_rc = {10, 100, 600, 400};

extern struct buttonObject btn_back_1;
extern struct buttonObject btn_front_page_1;
extern struct buttonObject btn_next_page_1;

extern int page_cnt1; 
extern int back_width, back_height;




HWND hMainWnd;

static const char* syskey = "";

static int last_key = -1;
static int last_key_count = 0;

static void make_welcome_text (void)
{
    	const char* sys_charset = GetSysCharset (TRUE);
    	const char* format;

	if (sys_charset == NULL)
		sys_charset = GetSysCharset (FALSE);

    	SetRect (&welcome_rc,  10, 10, g_rcScr.right - 10, g_rcScr.bottom / 2 - 10);
    	SetRect (&msg_rc, 10, welcome_rc.bottom + 10, g_rcScr.right - 10, g_rcScr.bottom - 20);

	if (strcmp (sys_charset, FONT_CHARSET_GB2312_0) == 0
		|| strcmp (sys_charset, FONT_CHARSET_GBK) == 0
		|| strcmp (sys_charset, FONT_CHARSET_GB18030_0) == 0) {
		format = "欢迎来到 MiniGUI 的世界! 如果您能看到该文本, 则说明 MiniGUI Version %d.%d.%d 可在该硬件上运行!";
    	}
    	else if (strcmp (sys_charset, FONT_CHARSET_BIG5) == 0) {
        	format = "欢迎来到 MiniGUI 的世界! 如果您能看到该文本, 则说明 MiniGUI Version %d.%d.%d 可在该硬件上运行!";
    	}
	else {
		format = "Welcome to the world of MiniGUI. \nIf you can see this text, MiniGUI Version %d.%d.%d can run on this hardware board.";
	}

    	sprintf (welcome_text, format, MINIGUI_MAJOR_VERSION, MINIGUI_MINOR_VERSION, MINIGUI_MICRO_VERSION);

    	strcpy (msg_text, HL_ST_NOMES);
}
#if 0
static int HelloWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    	HDC hdc;

    	syskey = "";

    	switch (message) {
        	case MSG_CREATE:
            		make_welcome_text ();
            		SetTimer (hWnd, 100, 200);
            		break;

        	case MSG_TIMER:
            		sprintf (msg_text, HL_ST_TIMER, GetTickCount ());
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_LBUTTONDOWN:
            		strcpy (msg_text, HL_ST_LBD);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_LBUTTONUP:
            		strcpy (msg_text, HL_ST_LBU);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_RBUTTONDOWN:
            		strcpy (msg_text, HL_ST_RBD);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_RBUTTONUP:
            		strcpy (msg_text, HL_ST_RBU);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_PAINT:
            		hdc = BeginPaint (hWnd);
            		DrawText (hdc, welcome_text, -1, &welcome_rc, DT_LEFT | DT_WORDBREAK);
            		DrawText (hdc, msg_text, -1, &msg_rc, DT_LEFT | DT_WORDBREAK);
            		EndPaint (hWnd, hdc);
            		return 0;

        	case MSG_SYSKEYDOWN:
            		syskey = HL_ST_SYS;
        	case MSG_KEYDOWN:
            		if(last_key == wParam)
                		last_key_count++;
            		else
            		{
                		last_key = wParam;
                		last_key_count = 1;
            		}
            		sprintf (msg_text, HL_ST_KEYD, wParam, syskey, last_key_count);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		return 0;

        	case MSG_KEYLONGPRESS:
            		sprintf (msg_text, HL_ST_KEYLONG, wParam);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_KEYALWAYSPRESS:
            		sprintf (msg_text, HL_ST_KEYALWAY, wParam);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		break;

        	case MSG_KEYUP:
            		sprintf (msg_text, HL_ST_KEYU, wParam);
            		InvalidateRect (hWnd, &msg_rc, TRUE);
            		return 0;

        	case MSG_CLOSE:
            		KillTimer (hWnd, 100);
            		DestroyMainWindow (hWnd);
            		PostQuitMessage (hWnd);
            		return 0;
    	}

    	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}
#endif

const char* warningText[]=
{
	"请选择作业区域！",
};

const char* menu_hz[]=
{ 	
	"轧机",
	"接杆",
	"导卫",
	"压下",
	"立轧机",
	"活套",
	"除尘",
	"除鳞",
	"小车、平台",
	"测厚仪",
	"液压站",

};

const int meun_hz_size[]=
{
	40,
	40,
	40,
	40,
	40,
	40,
	40,
	40,
	30,
	40,
	40,
};

struct textStruct warn_message1 = {
	.name = "轧机区域F1主电机",
	.filesize = 30,
	.offsetx = 10,
	.offsety = 5,
	.color = 0xFFFFFFFF,
};

struct textStruct warn_message2 = {
	.name = "碳刷检查更新",
	.filesize = 30,
	.offsetx = 10,
	.offsety = 40,
	.color = 0xFFFFFFFF,
};

struct textStruct warn_message3 = {
	.name = "F1高压开关",
	.filesize = 30,
	.offsetx = 10,
	.offsety = 75,
	.color = 0xFFFFFFFF
};

struct warnForm warnform1 = {
	.messageCount = 3,
	.formColor = 0x32CD3200,
	.borderColor = 0xFFFFFF00,
	.width = 300,
	.height = 110,
	.text[0] = &warn_message1,
	.text[1] = &warn_message2,
	.text[2] = &warn_message3,
};

struct textStruct warn_canel = {
	.name = "取消",
	.filesize = 30,
	.offsetx = 3,
	.offsety = 5,
};

struct textStruct back ={
	.name = "返回",
	.filesize = 40,
	.offsetx = 20,
	.offsety = 5,
};

struct textStruct menu_hiz[]=
{
	{
		.name = "轧机aA12131415",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "测试测接杆测试",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "我我测我导卫您你",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "F1压下",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "立轧机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "活套",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "除尘",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "除鳞",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "小车、平台",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "测厚仪",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "液压站",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "测试1",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "测试2",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
	{
		.name = "测试3",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 20,
	},
};

void test_chinese(HDC hdc){
	TextOut(hdc,200,295,"测试1");

}

void test_output(HDC hdc, char * str)
{
	TextOut(hdc,300,295, str);
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
	int form_cnt;
	int cnt;
	HDC hdc;
	
	switch(message)
	{
		case MSG_CREATE:
		printf("MSG_CREATE ok\n");
			LoadBitmap(HDC_SCREEN,&s_background,"/usr/local/res/background.jpg");
#if 0
			//LoadBitmapFromMem   (HDC_SCREEN,&s_startbmp,start_data,start_no,"bmp");
			LoadBitmap(HDC_SCREEN,&s_startbmp,"/usr/local/res/start.bmp");

			//LoadBitmapFromMem(HDC_SCREEN,&s_bmp[0],no01_data,sz_no01,"bmp");
			LoadBitmap(HDC_SCREEN,&s_bmp[0],"/usr/local/res/my computer.bmp");

			//LoadBitmapFromMem(HDC_SCREEN,&s_bmp[1],no02_data,sz_no02,"bmp");
			LoadBitmap(HDC_SCREEN,&s_bmp[1],"/usr/local/res/ie.bmp");

			//LoadBitmapFromMem(HDC_SCREEN,&s_bmp[2],no03_data,sz_no03,"bmp");
			LoadBitmap(HDC_SCREEN,&s_bmp[2],"/usr/local/res/music.bmp");

			//LoadBitmapFromMem(HDC_SCREEN,&s_bmp[3],no04_data,sz_no04,"bmp");
			LoadBitmap(HDC_SCREEN,&s_bmp[3],"/usr/local/res/picture.bmp");

			//LoadBitmapFromMem(HDC_SCREEN,&s_bmp[4],no05_data,sz_no05,"bmp");
			LoadBitmap(HDC_SCREEN,&s_bmp[4],"/usr/local/res/camera.bmp");

			//LoadBitmapFromMem(HDC_SCREEN,&s_bmp[5],no06_data,sz_no06,"bmp");
			LoadBitmap(HDC_SCREEN,&s_bmp[5],"/usr/local/res/clock.bmp");
#endif	

			
			//s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF","mini","GB2312-80", \
			FONT_WEIGHT_REGULAR,FONT_SLANT_ROMAN,FONT_SETWIDTH_NORMAL, \
			FONT_SPACING_CHARCELL,FONT_UNDERLINE_NONE,FONT_STRUCKOUT_NONE,16,0);

			printf("MSG_CREATE finish\n");

   		break;
		
  		case MSG_PAINT:
			printf("MSG_PAINT begin1\n");
			hdc = BeginPaint(hWnd);
			//FillBoxWithBitmap(hdc,0,0,800,360,&s_background);
#if 0
			for(i=0;i<4;i++)
			{
				FillBoxWithBitmap(hdc,10,i*70+10,48,48,&s_bmp[i]);
				printf("FillBoxWithBitmap ok\n");
			}
			for(i=0;i<2;i++)
			{
				FillBoxWithBitmap(hdc,80,i*70+10,48,48,&s_bmp[i+4]);
			}
	
			FillBoxWithBitmap(hdc,0,283,240,37,&s_startbmp);
#endif
			//SetBkMode(hdc,BM_TRANSPARENT);
			//SetTextColor(hdc,COLOR_lightwhite);
//			SelectFont(hdc,s_font);
			//TextOut(hdc,30,295,"测试");
			//TextOut(hdc,200,295,"测试");
			//test_chinese(hdc);
			//test_b(hdc);
#if 0

			SetPenColor(hdc,COLOR_black);
			if(s_sel<4)
			{
				Rectangle(hdc,8,s_sel*70+8,60,s_sel*70+60);
			}
			else
			{
				Rectangle(hdc,8,s_sel*70+8,60,s_sel*70+60);
			}
			SelectFont(hdc,s_font1);
			TextOut(hdc,130,295,menu_hz[s_sel]);
#endif
			jointwarn_crate_mainui(hdc, g_rcScr.right, g_rcScr.bottom);
			//TextOut(hdc,400,295,"测试");

			EndPaint(hWnd,hdc);

			break;
		case MSG_LBUTTONDOWN:
			printf("MSG_LBUTTONDOWN\n");
			hdc = BeginPaint(hWnd);
			
			pre_x = LOWORD(lParam);
			pre_y = HIWORD(lParam);
			printf("x = %d, y = %d\n", pre_x, pre_y);
			if(btn_back_1.active == 1){
				if((pre_x > btn_back_1.point_start.x && pre_x < btn_back_1.point_end.x) && (pre_y > btn_back_1.point_start.y && pre_y < btn_back_1.point_end.y)){
					printf("back pressed\n");
					InitConfirmWindow(hWnd, 400, 300, &warnform1, 1);
				}
			}
			if(btn_front_page_1.active == 1){
				if((pre_x > btn_front_page_1.point_start.x && pre_x < btn_front_page_1.point_end.x) && (pre_y > btn_front_page_1.point_start.y && pre_y < btn_front_page_1.point_end.y)){
					printf("front page pressed\n");
				}
			}
			if(btn_next_page_1.active == 1){
				if((pre_x > btn_next_page_1.point_end.x && pre_x < btn_next_page_1.point_start.x) && (pre_y > btn_next_page_1.point_start.y && pre_y < btn_next_page_1.point_end.y)){
					printf("next page pressed\n");
					cnt = TOTAL_FRAME * (page_cnt1 + 1);
					form_cnt = TOTAL_NUM - cnt; 
					form_cnt = form_cnt > TOTAL_FRAME ? TOTAL_FRAME : form_cnt;
					jointwarn_paint_frame(hdc, &menu_hiz[cnt], form_cnt);
					page_cnt1++;
				}
			}
			
			EndPaint(hWnd,hdc);
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
					MessageBox(hMainWnd,"功能正在建设...","提示",MB_OK);
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
				TextOut(hdc,30,295,"开 始 ");
				SelectFont(hdc,s_font1);
				TextOut(hdc,130,295,menu_hz[s_sel]);

				EndPaint(hWnd,hdc);
			}
#endif
			break;
			
		case MSG_CLOSE:
		printf("MSG_CLOSE ok\n");
			UnloadBitmap(&s_startbmp);
			for(i=0;i<6;i++)UnloadBitmap(&s_bmp[i]);
			//DestroyLogFont(s_font);
			//DestroyLogFont(s_font1);
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
	//HWND hMainWnd;
	//MAINWINCREATE CreateInfo;
#if 0	    
	//CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwStyle = WS_DISABLED | WS_DLGFRAME | WS_CAPTION;
    	CreateInfo.dwExStyle = WS_EX_NONE;
    	CreateInfo.spCaption = HL_ST_CAP;
    	CreateInfo.hMenu = 0;
    	CreateInfo.hCursor = GetSystemCursor(0);
    	CreateInfo.hIcon = 0;
    	CreateInfo.MainWindowProc = HelloWinProc;
    	CreateInfo.lx = 0;
    	CreateInfo.ty = 0;
    	CreateInfo.rx = g_rcScr.right;
    	CreateInfo.by = g_rcScr.bottom;
    	CreateInfo.iBkColor = COLOR_lightwhite;
    	CreateInfo.dwAddData = 0;
    	CreateInfo.hHosting = HWND_DESKTOP;

    	hMainWnd = CreateMainWindow (&CreateInfo);

    	if (hMainWnd == HWND_INVALID)
        	return -1;

    	ShowWindow(hMainWnd, SW_SHOWNORMAL);
#endif
	InitMainWindow();	
		
	//printf("argc = %d\n", argc);
	//printf("argc[1] %d\n", atoi(argv[1]));
	//printf("argc[2] %d\n", atoi(argv[2]));
	
	//play_rock(atoi(argv[1]), atoi(argv[2]));

	while(GetMessage(&Msg,hMainWnd))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	MainWindowThreadCleanup(hMainWnd);
	return(0);

#if 0
    	while (GetMessage(&Msg, hMainWnd)) {
        	TranslateMessage(&Msg);
        	DispatchMessage(&Msg);
    	}

    	MainWindowThreadCleanup (hMainWnd);
#endif
	return 0;
}
