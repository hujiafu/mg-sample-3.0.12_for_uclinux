
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
extern int histroy_cnt;
extern int page_num;
extern int page_cnt;
extern int page_no;
extern int item_no;
extern int item_num;
extern int cos_no;
extern unsigned int cos_isconst_value;
extern unsigned int cos_isconst_count;
extern unsigned char cos_pos_value_fstr[10];
extern unsigned char cos_pos_value_str[10];
extern unsigned int cos_pos_value_cnt;
extern unsigned char cos_pos_count_fstr[10];
extern unsigned char cos_pos_count_str[10];
extern unsigned int cos_pos_count_cnt;


unsigned char posStr[50];
unsigned char posIdStr[10];
unsigned long posId = 1;
unsigned int  posSize;
unsigned int  posCount;
long usedCount;
long leaveCount;
unsigned char leaveStr[10];
int windows_no;

struct cardData def_card = {
        .cardId = "00001",
        .userName = "张三",
        .cardState = "正常",
};

struct posData def_detil[] = {
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "13.5",
		.time = "2016-3-12 9:1:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "8.5",
		.time = "2016-3-12 10:1:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "13",
		.time = "2016-3-12 15:1:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "14",
		.time = "2016-3-12 15:3:42",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "15.5",
		.time = "2016-3-12 16:8:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "16.5",
		.time = "2016-3-12 17:18:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "18.5",
		.time = "2016-3-12 17:20:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "19.5",
		.time = "2016-3-12 17:33:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "15.5",
		.time = "2016-3-12 17:36:11",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "3.5",
		.time = "2016-3-12 17:45:13",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "20.5",
		.time = "2016-3-12 19:28:23",
	},
	{
		.cardId = "00001",
		.userName = "张三",
		.posValue = "28.5",
		.time = "2016-3-12 20:12:23",
	},

};

const char * sz_menu[]=
{
        "卡号",
        "姓名",
        "消费状态",
};

const char * sz_menu1[]=
{
        "卡号",
        "姓名",
        "消费金额",
        "消费日期",
};

const char * item_menu[]=
{
	"管理员操作",
	"消费参数",
	"系统初始化",
	"音量设置",
	"用户管理",
	"设置管理卡",
	"通信设置",
	"日期设置",
	"消费参数",
};

const char * cos_menu[]=
{
        "定额",
        "是否计次",
        "是否定额",
        "定次",
};

const char * cos_menu1[]=
{
	"是",
	"否",
};

void display_time(){

	HDC hdc;
	PLOGFONT s_font;

	hdc = GetDC(hMainWnd);	
	s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
        FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, 40, 0);
        SelectFont(hdc,s_font);
	get_time();
	FillBox(hdc, 0, 400, MWINDOW_RX, 80);
	TextOut(hdc, 20, 420, gtime);
	
	DestroyLogFont(s_font);
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
	strcpy(posStr, "机号 : ");
	strcat(posStr, posIdStr);
	TextOut(hdc, 20, 20, posStr);

	posSize = sizeof(struct posData);
	posCount = CONTEXT_SIZE / posSize;
	leaveCount = posCount - usedCount;
	printf("posCount = %d, leaveCount = %d\n", posCount, leaveCount);
	strcpy(posStr, "剩余容量 : ");
	sprintf(leaveStr, "%d", leaveCount);
	strcat(posStr, leaveStr);
	TextOut(hdc, 420, 20, posStr);
	DestroyLogFont(s_font);

	timer_init();

}

void pos_cos_input(HDC hdc, char param){
	
	if(cos_no == 0){
		if(cos_pos_value_cnt<6){
			cos_pos_value_str[cos_pos_value_cnt] = param;
			printf("cos_pos_value_str %s\n", cos_pos_value_str);
			cos_pos_value_cnt++;
			pos_set_const_value(hdc, cos_no);
		}
	}
	if(cos_no == 3){
		if(cos_pos_count_cnt<6){
			cos_pos_count_str[cos_pos_count_cnt] = param;
			printf("cos_pos_count_str %s\n", cos_pos_count_str);
			cos_pos_count_cnt++;
			pos_set_const_value(hdc, cos_no);
		}
	}
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
	int tmp;
	
	switch(message)
	{
		case MSG_CREATE:
			printf("MSG_CREATE ok\n");
   			break;
  		case MSG_PAINT:
			printf("MSG_PAINT begin1\n");
			hdc = BeginPaint(hWnd);
			//ghdc = hdc;
			pos_create_main_ui(hdc);
			EndPaint(hWnd,hdc);
			break;
		case MSG_LBUTTONDOWN:
			printf("MSG_LBUTTONDOWN\n");
			//create_query_ui(hdc);
			//query_detil(hdc);
			break;
		case MSG_RBUTTONDOWN:
			printf("MSG_RBUTTONDOWN:\n");
			break;
		case MSG_CHAR:
			printf("MSG_CHAR ok\n");
			printf("0x%x\n", wParam);

			hdc = GetDC(hMainWnd);
			switch(wParam)
			{
				case 'p' :
					if(windows_no == 2){
						if(item_no > 0){
							clear_pos_item(hdc, item_no);
							item_no--;
							select_pos_item(hdc,item_no);							
						}
					}

					if(windows_no == 7){
						if(page_no > 0){
							page_no--;
							tmp = histroy_cnt - page_no * PAGE_PRE_COUNT;
							page_cnt = tmp > PAGE_PRE_COUNT ? PAGE_PRE_COUNT : tmp; 
							printf("page_cnt = %d, page_no = %d\n", page_cnt, page_no); 
							display_detil(hdc, &def_detil[page_no * PAGE_PRE_COUNT]);
						}
					}
					if(windows_no == 4){
						if(cos_no > 0){
							pos_cos_clear(hdc, cos_no);
							cos_no--;
							pos_cos_sel(hdc, cos_no);
						}
					}

					break;
				case 'n' :
					if(windows_no == 2){
						if(item_no < (item_num - 1)){
							clear_pos_item(hdc, item_no);
							item_no++;
							select_pos_item(hdc,item_no);							
						}
					}
					if(windows_no == 7){
						if(page_no < (page_num - 1)){
							page_no++;
							tmp = histroy_cnt - page_no * PAGE_PRE_COUNT;
							page_cnt = tmp > PAGE_PRE_COUNT ? PAGE_PRE_COUNT : tmp;
							printf("page_cnt = %d, page_no = %d\n", page_cnt, page_no); 
							display_detil(hdc, &def_detil[page_no * PAGE_PRE_COUNT]);
						}
					}
					if(windows_no == 4){
						if(cos_no < (COS_MAX_NO - 1)){
							pos_cos_clear(hdc, cos_no);
							cos_no++;
							pos_cos_sel(hdc, cos_no);
						}
					}
					break;
				case 'm' :
					if(windows_no == 0){
						create_pos_item(hdc);
					}		
					break;
				case 'q' :
					if(windows_no == 4 || windows_no == 6){
						create_pos_item(hdc);
					}
					if(windows_no == 7){
						create_query_ui(hdc);
					}
					break;
				case 0xd :
					if(windows_no == 6){
						query_detil(hdc);
					}
					if(windows_no == 4){
						if(cos_no == 1){
							cos_isconst_count = cos_isconst_count == 0 ? 1 : 0;
							pos_set_const_state(hdc, cos_no);
						}
						if(cos_no == 2){
							cos_isconst_value = cos_isconst_value == 0 ? 1 : 0;
							pos_set_const_state(hdc, cos_no);
						}
						if(cos_no == 0){
							strcpy(cos_pos_value_fstr, cos_pos_value_str);
							cos_pos_value_cnt = 0;
							memset(cos_pos_value_str, 0, 10);
						}
						if(cos_no == 3){
							strcpy(cos_pos_count_fstr, cos_pos_count_str);
							cos_pos_count_cnt = 0;
							memset(cos_pos_count_str, 0, 10);
						}
					}
					if(windows_no == 2){
						if(item_no == 8){
							create_poscos_set(hdc);
						}
						if(item_no == 4){
							create_query_ui(hdc);
						}
					}
					break;
				case 0x7f :
					if(windows_no == 4){
						if(cos_no == 0){
							if(cos_pos_value_cnt > 0){
								cos_pos_value_cnt--;
								cos_pos_value_str[cos_pos_value_cnt] = 0;	
								pos_set_const_value(hdc, cos_no);
							}
						}
						if(cos_no == 3){
							if(cos_pos_count_cnt > 0){
								cos_pos_count_cnt--;
								cos_pos_count_str[cos_pos_count_cnt] = 0;	
								pos_set_const_value(hdc, cos_no);
							}
						}
					}
					break;
				case '0':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '1':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '2':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '3':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '4':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '5':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '6':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '7':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '8':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '9':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
				case '.':
					if(windows_no == 4){
						pos_cos_input(hdc, wParam);
					}
					break;
			}
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
