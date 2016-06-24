
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
#include "JointWarn_Main.h"
#include "JointWarn_Json.h"

static char welcome_text [512];
static char msg_text [256];
static RECT welcome_rc = {10, 100, 600, 400};
static RECT msg_rc = {10, 100, 600, 400};
unsigned char jointwarn_sn[10] = "abcd";

extern struct buttonObject btn_back_1;
extern struct buttonObject btn_front_page_1;
extern struct buttonObject btn_next_page_1;
extern struct buttonObject select_apply;
extern struct buttonObject select_canel;
extern POINT s_point[2][3];

extern int page_cnt1;
extern int form_tot_cnt;
extern int back_width, back_height;
extern int partHeight, partWidth;
extern int x[100], y[100];
extern struct selStruct * gPsel;
extern struct formStruct * gPform_area;
extern struct formStruct * gPform_equi;
extern struct formStruct * gPform_pro;
extern struct buttonObject select_obj[6];
extern int select_obj_no;
extern int top_window;
extern struct buttonObject btn_cancel;

extern struct formStruct * g_pform;
extern struct selStruct * g_psel;
extern int g_form_count;
extern int g_sel_count;
extern struct formStruct g_form[MAX_FORM_NUM];
HWND hMainWnd;

static const char* syskey = "";

static int last_key = -1;
static int last_key_count = 0;
int window_no = WIN_NULL_NO;
//int area_window_frame_cnt = 0;
//int equipment_window_frame_cnt = 0;
//int project_window_frame_cnt = 0;
int window_frame_cnt = 0;
int total_frame_cnt = 0;
int form_count = 0;
int area_select_no = 0;
int equipment_select_no = 0;
int project_select_no = 0;
int gRow, gColumn;
unsigned char area_sel_no_str[4];
unsigned char equi_sel_no_str[4];
unsigned char pro_sel_no_str[4];
unsigned char final_cmd = 0;
unsigned char select_project_str[50];
unsigned char area_sel_str[20];
unsigned char equi_sel_str[20];
unsigned char prj_sel_str[20];
unsigned char display_no_str[10];
int project_str_len;

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

struct textStruct menu_hz1[] = {
	{
		.name = "申请作业项目",
		.filesize = 50,
		.offsetx = 60,
		.offsety = 25,
	},
	{
		.name = "撤销作业项目",
		.filesize = 50,
		.offsetx = 60,
		.offsety = 25,
	},
}; 

const char * select_msg[]=
{
	"请选择作业区域！",
	"请选择作业设备！",
	"请选择作业项目！",
};

struct textStruct menu_hz1_warn = {
	.name = "请选择操作项目",
	.filesize = 30,
	.offsetx = 10,
	.offsety = 5,
	.color = 0x00008BFF,
};

struct textStruct warn_msg[] = {
	{
		.name = "请选择作业区域！",
		.filesize = 30,
		.offsetx = 10,
		.offsety = 5,
		.color = 0x00008BFF,
	},
	{
		.name = "请选择作业设备！",
		.filesize = 30,
		.offsetx = 10,
		.offsety = 5,
		.color = 0x00008BFF,
	},
	{
		.name = "请选择作业项目！",
		.filesize = 30,
		.offsetx = 10,
		.offsety = 5,
		.color = 0x00008BFF,
	},
};

const char* menu_hz[]=
{ 	
	"液压站",

};

const int meun_hz_size[]=
{
	40,
};

const char test_menu_hz1[] =
{
	"申请作业项目：轧机区域F1主电机碳刷检查更换",
};

const char msg_hz1[] = 
{
	"项目作业中，不能重复选择，请规范操作！",
};

const char msg_hz2[] = 
{
	"请作业负责人打卡确认！",
};

const char msg_hz3[] = 
{
	"请勿越权选择，请重新选择作业申请项目！",
};

const char * test_msg_hz2[] = 
{
	"F1高压开关",
	"F1力磁进线单元",
	"F1主回路接触器",
};
const char * test_tmsg_hz1[] = 
{
	"请安全关闭！",
	"安全关闭绑定完成！",
};

const char * title_warn_106[] =
{
	"请实施介质安全关闭",
	"请实施部分介质安全关闭",
	"请选择单项介质安全关闭确认",
};

const char * cancel_text[] = 
{
	"立即取消",
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

struct textStruct menu_project[]=
{
	{
		.name = "主电机碳刷检查更新0",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新1",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新2",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新3",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新4",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新5",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新6",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新7",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新8",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新9",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新10",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新11",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新12",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新13",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
	{
		.name = "主电机碳刷检查更新14",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 15,
	},
};

struct textStruct menu_equipment[]=
{
	{
		.name = "F0主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F1主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F2主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F3主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F4主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F5主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F6主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F7主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F8主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F9主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F10主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F11主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F12主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F13主电机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},

};

struct textStruct menu_hiz[]=
{
	{
		.name = "轧机aA12131415",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试测接杆测试",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "我我测我导卫您你",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "F1压下",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "立轧机",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "活套",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "除尘",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "除鳞",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "小车、平台",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测厚仪",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "液压站",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试0",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试1",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试2",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试3",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试4",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试5",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试6",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试7",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试8",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试9",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试10",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试11",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试12",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
	{
		.name = "测试13",
		.filesize = 30,
		.offsetx = 5,
		.offsety = 22,
	},
};

unsigned char test_104[] = 
	"{\"sn\" : \"JointCtrl1\", \"action\" : \"update_pro\", \"selects\" : \
        [{\"index\" : \"1\", \"text1\" : \"promytest1\"},\
        {\"index\" : \"2\", \"text1\" : \"promytest2\"},\
        {\"index\" : \"3\", \"text1\" : \"promytest3\"},\
        {\"index\" : \"4\", \"text1\" : \"promytest4\"},\
        {\"index\" : \"5\", \"text1\" : \"promytest5\"},\
        {\"index\" : \"6\", \"text1\" : \"promytest6\"},\
        {\"index\" : \"7\", \"text1\" : \"promytest7\"},\
        {\"index\" : \"8\", \"text1\" : \"promytest8\"},\
        {\"index\" : \"9\", \"text1\" : \"promytest9\"},\
        {\"index\" : \"10\", \"text1\" : \"promytest10\"},\
        {\"index\" : \"11\", \"text1\" : \"promytest11\"},\
        {\"index\" : \"12\", \"text1\" : \"promytest12\"},\
        {\"index\" : \"13\", \"text1\" : \"promytest13\"},\
        {\"index\" : \"14\", \"text1\" : \"promytest14\"},\
        ]}";

unsigned char test_103[] = 
	"{\"sn\" : \"JointCtrl1\", \"action\" : \"update_equi\", \"selects\" : \
        [{\"index\" : \"1\", \"text1\" : \"eqmytest1\"},\
        {\"index\" : \"2\", \"text1\" : \"eqmytest2\"},\
        {\"index\" : \"3\", \"text1\" : \"eqmytest3\"},\
        {\"index\" : \"4\", \"text1\" : \"eqmytest4\"},\
        {\"index\" : \"5\", \"text1\" : \"eqmytest5\"},\
        {\"index\" : \"6\", \"text1\" : \"eqmytest6\"},\
        {\"index\" : \"7\", \"text1\" : \"eqmytest7\"},\
        {\"index\" : \"8\", \"text1\" : \"eqmytest8\"},\
        {\"index\" : \"9\", \"text1\" : \"eqmytest9\"},\
        {\"index\" : \"10\", \"text1\" : \"eqmytest10\"},\
        {\"index\" : \"11\", \"text1\" : \"eqmytest11\"},\
        {\"index\" : \"12\", \"text1\" : \"eqmytest12\"},\
        {\"index\" : \"13\", \"text1\" : \"eqmytest13\"},\
        {\"index\" : \"14\", \"text1\" : \"eqmytest14\"},\
        {\"index\" : \"15\", \"text1\" : \"eqmytest15\"}\
        ]}";

unsigned char test_102[] = 
	"{\"sn\" : \"JointCtrl1\", \"action\" : \"update_area\", \"selects\" : \
        [{\"index\" : \"1\", \"text1\" : \"mytest1\"},\
        {\"index\" : \"2\", \"text1\" : \"mytest2\"},\
        {\"index\" : \"3\", \"text1\" : \"mytest3\"},\
        {\"index\" : \"4\", \"text1\" : \"mytest4\"},\
        {\"index\" : \"5\", \"text1\" : \"mytest5\"},\
        {\"index\" : \"6\", \"text1\" : \"mytest6\"},\
        {\"index\" : \"7\", \"text1\" : \"mytest7\"},\
        {\"index\" : \"8\", \"text1\" : \"mytest8\"},\
        {\"index\" : \"9\", \"text1\" : \"mytest9\"},\
        {\"index\" : \"10\", \"text1\" : \"mytest10\"},\
        {\"index\" : \"11\", \"text1\" : \"mytest11\"},\
        {\"index\" : \"12\", \"text1\" : \"mytest12\"},\
        {\"index\" : \"13\", \"text1\" : \"mytest13\"},\
        {\"index\" : \"14\", \"text1\" : \"mytest14\"},\
        {\"index\" : \"15\", \"text1\" : \"mytest15\"},\
        {\"index\" : \"16\", \"text1\" : \"mytest16\"},\
        {\"index\" : \"17\", \"text1\" : \"mytest17\"},\
        {\"index\" : \"18\", \"text1\" : \"mytest18\"},\
        {\"index\" : \"19\", \"text1\" : \"mytest19\"},\
        {\"index\" : \"20\", \"text1\" : \"mytest20\"},\
        {\"index\" : \"21\", \"text1\" : \"mytest21\"},\
        {\"index\" : \"22\", \"text1\" : \"mytest22\"},\
        {\"index\" : \"23\", \"text1\" : \"mytest23\"},\
        {\"index\" : \"24\", \"text1\" : \"mytest24\"},\
        {\"index\" : \"25\", \"text1\" : \"mytest25\"}\
        ]}";

unsigned char test_106_1[] = 
	"{\"sn\" : \"JointCtrl1\", \"action\" : \"update_sel\", \"selects\" : \
        [{\"index\" : \"1\", \"color\" : \"green\", \"text1\" : \"mytest1\", \"text2\" : \"mytext2\"},\
        {\"index\" : \"2\", \"color\" : \"red\", \"text1\" : \"mytest3\", \"text2\" : \"mytext4\"},\
        {\"index\" : \"3\", \"color\" : \"green\", \"text1\" : \"测试1\", \"text2\" : \"测试2\"},\
        {\"index\" : \"4\", \"color\" : \"green\", \"text1\" : \"测试4-1\", \"text2\" : \"测试4-2\"},\
        {\"index\" : \"5\", \"color\" : \"green\", \"text1\" : \"测试5-1\", \"text2\" : \"测试5-2\"},\
        {\"index\" : \"6\", \"color\" : \"green\", \"text1\" : \"测试6-1\", \"text2\" : \"测试6-2\"},\
        {\"index\" : \"7\", \"color\" : \"green\", \"text1\" : \"测试7-1\", \"text2\" : \"测试7-2\"}\
        ]}";

unsigned char test_108_1[] = 
	"{\"sn\" : \"JonitCtrl1\", \"action\" : \"update_top\", \"titles\" : \
	[{\"index\" : \"1\", \"count\" : \"1\", \"color\" : \"green\", \"title1\" : \"F1高压开关\"},\
	 {\"index\" : \"2\", \"count\" : \"1\", \"color\" : \"yellow\", \"title1\" : \"介质未安全关闭，不能选择！\"} \
	]}";

const unsigned char request_area[] = 
	"{\"sn\":\"abc\", \"action\":\"request_area\"}";

const unsigned char request_equi[] = 
	"{\"sn\":\"abc\", \"action\":\"request_equi\", \"area_no\":\"";

const unsigned char request_pro[] = 
	"{\"sn\":\"abc\", \"action\":\"request_pro\", \"equi_no\":\"";

const unsigned char request_oper[] = 
	"{\"sn\":\"abc\", \"action\":\"request_oper\", \"pro_no\":\"";

void test_chinese(HDC hdc){
	TextOut(hdc,200,295,"测试1");

}

void test_output(HDC hdc, char * str)
{
	TextOut(hdc,300,295, str);
}

void create_project_window(HDC hdc)
{
	unsigned char * origin_str;
	struct formStruct * pform;
	int len;
	
	gRow = 5;
	gColumn = 2;
	window_no = WIN_104_1_NO;
	total_frame_cnt = 15;
	window_frame_cnt = gRow * gColumn;
	strcpy(warn_msg[1].name, gPform_equi[equipment_select_no].text1);
	strcpy(warn_msg[2].name, select_msg[2]);

	len = strlen(warn_msg[1].name);
	len = len > (50 - project_str_len) ? (50 - project_str_len) : len;
	memcpy(select_project_str + project_str_len, warn_msg[1].name, len);
	project_str_len += len;


	origin_str = JointWarn_104_get_data(equipment_select_no);
	pform = JointWarn_102_4_parepar_data(origin_str, 2);
	jointwarn_crate_mainui(hdc, pform, warn_msg, 3);
}

void create_equipment_window(HDC hdc)
{
	unsigned char * origin_str;
	struct formStruct * pform;
	int len;
	
	gRow = 4;
	gColumn = 3;
	window_no = WIN_103_NO;
	total_frame_cnt = 14;
	window_frame_cnt = gRow * gColumn;
	strcpy(warn_msg[0].name, gPform_area[area_select_no].text1);
	strcpy(warn_msg[1].name, select_msg[1]);
	
	project_str_len = 0;
	memset(select_project_str, 0, 50);
	len = strlen(warn_msg[0].name);
	len = len > 50 ? 50 : len;
	memcpy(select_project_str, warn_msg[0].name, len);
	project_str_len += len;
	
	origin_str = JointWarn_103_get_data(area_select_no);
	pform = JointWarn_102_4_parepar_data(origin_str, 1);
	jointwarn_crate_mainui(hdc, pform, warn_msg, 2);
}

void create_area_window(HDC hdc)
{
	unsigned char * origin_str;
	struct formStruct * pform;

	gRow = 4;
	gColumn = 3;
	window_no = WIN_102_NO;
	total_frame_cnt = 25;
	window_frame_cnt = gRow * gColumn;
	strcpy(warn_msg[0].name, select_msg[0]);

	origin_str = JointWarn_102_get_data();
	pform = JointWarn_102_4_parepar_data(origin_str, 0);
	//jointwarn_crate_mainui(hdc, menu_hiz, warn_msg, 1);
	jointwarn_crate_mainui(hdc, pform, warn_msg, 1);

}

void create_select_window(HDC hdc, struct textStruct * text, struct textStruct *warn)
{
	printf("create_select_window\n");
	window_no = WIN_101_NO;
	jointwarn_create_select(hdc, text, warn);
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
	int count;
	int len;
	HDC hdc;
	unsigned char * origin_str;	
	unsigned int ptr;

	
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
			//hdc = BeginPaint(hWnd);
			hdc = BeginPaint(hMainWnd);
			//hdc = GetDC(hMainWnd);
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
			//gRow = 4;
			//gColumn = 3;
			//window_no = 1;
			//total_frame_cnt = 25;
			//window_frame_cnt = gRow * gColumn;
			//jointwarn_crate_mainui(hdc, menu_hiz, warn_msg, 3);
			//TextOut(hdc,400,295,"测试");

			//test_select_json();
			//create_area_window(hdc);
			//JointWarn_create_105(hdc, 3);
			//JointWarn_create_106(hdc, 1);
			//create_select_window(hdc, &menu_hz1[0], &menu_hz1_warn);
			//JointWarn_udp_send("{\"sn\":\"abc\", \"action\":\"request_area\"}", 0);
			//JointWarn_create_top_back(hdc, 480, 280);
			//InitConfirmWindow(hWnd, 480, 280, &warnform1, 1);
			//EndPaint(hWnd,hdc);

			final_cmd = CMD_CREATE_101; 
			JointRunCmdLine(hdc);

			EndPaint(hMainWnd,hdc);
			break;
		case MSG_LBUTTONDOWN:
			printf("MSG_LBUTTONDOWN\n");
			//hdc = BeginPaint(hWnd);
	
			pre_x = LOWORD(lParam);
			pre_y = HIWORD(lParam);
			printf("x = %d, y = %d\n", pre_x, pre_y);
			if(top_window == 0){
			if(window_no == WIN_101_NO){
				if(select_apply.active == 1){
					if((pre_x > select_apply.point_start.x && pre_x < select_apply.point_end.x) && (pre_y > select_apply.point_start.y && pre_y < select_apply.point_end.y)){
						printf("select_apply press\n");
						origin_str = JointWarn_102_get_data(0);
						printf("=======================================\n");
						JointAnalysisCmdLine(origin_str, &ptr);
						printf("=======================================\n");
						JointRunCmdLine(hdc);
						printf("=======================================\n");
						//create_area_window(hdc);
						break;
					}
				}
				if(select_canel.active == 1){
					if((pre_x > select_canel.point_start.x && pre_x < select_canel.point_end.x) && (pre_y > select_canel.point_start.y && pre_y < select_canel.point_end.y)){
						printf("select_canel press\n");
						break;
					}
				}
			}
			if(btn_back_1.active == 1){
				if((pre_x > btn_back_1.point_start.x && pre_x < btn_back_1.point_end.x) && (pre_y > btn_back_1.point_start.y && pre_y < btn_back_1.point_end.y)){
					printf("back pressed\n");
					
					if(WIN_103_NO == window_no){
						//JointWarn_free_area_buf();
						origin_str = JointWarn_102_get_data(0);
						JointAnalysisCmdLine(origin_str, &ptr);
						JointRunCmdLine(hdc);
						//create_area_window(hdc);
						break;
					}
					if(WIN_104_1_NO == window_no){
						//JointWarn_free_equi_buf();
						//create_equipment_window(hdc);
						origin_str = JointWarn_103_get_data(area_select_no);
						JointAnalysisCmdLine(origin_str, &ptr);
						JointRunCmdLine(hdc);
						break;
					}
					if(WIN_106_1_NO == window_no){
						JointWarn_free_pro_buf();
						create_project_window(hdc);
					}
					if(4 == window_no){
						printf("back to 100-2\n");
						break;
					}
					//EnableWindow(hWnd, FALSE);
					//InitConfirmWindow(hWnd, 400, 300, &warnform1, 1);
				}
			}
			//if((window_no >= 1 && window_no <=3) || window_no == 8){
			if((WIN_102_NO == window_no) || (WIN_103_NO == window_no) || (WIN_104_1_NO == window_no) || (WIN_106_1_NO == window_no)){
			if(btn_front_page_1.active == 1){
				if((pre_x > btn_front_page_1.point_start.x && pre_x < btn_front_page_1.point_end.x) && (pre_y > btn_front_page_1.point_start.y && pre_y < btn_front_page_1.point_end.y)){
					printf("front page pressed\n");
					page_cnt1--;
					cnt = window_frame_cnt * page_cnt1;
					form_count = window_frame_cnt;
					if(page_cnt1 > 0){
						left_flag = 1;
					}else{
						left_flag = 0;
					}
					if(page_cnt1 >= form_tot_cnt - 1){
						right_flag = 0;
					}else{
						right_flag = 1;
					}
					jointwarn_paint_flag(hdc, left_flag, right_flag);
					
					if(WIN_102_NO == window_no){
						//jointwarn_paint_frame(hdc, &menu_hiz[cnt], form_count);
						jointwarn_paint_frame(hdc, &g_form[cnt], form_count, 1);
						break;
					}
					if(WIN_103_NO == window_no){
						jointwarn_paint_frame(hdc, &g_form[cnt], form_count, 2);
						break;
					}
					if(WIN_104_1_NO == window_no){
						jointwarn_paint_frame(hdc, &g_form[cnt], form_count, 3);
						break;
					}
					if(WIN_106_1_NO == window_no){
						JointWarn_clear_sel(hdc);
						count = form_count > window_frame_cnt ? window_frame_cnt : form_count;
						JointWarn_106_repaint_sel(hdc, gPsel, cnt, count);	
					}
	#if 0
					if(page_cnt1 > 0){
						left_flag = 1;
					}else{
						left_flag = 0;
					}
					if(page_cnt1 >= form_tot_cnt - 1){
						right_flag = 0;
					}else{
						right_flag = 1;
					}
					jointwarn_paint_flag(hdc, left_flag, right_flag);
	#endif
				}
			}
			if(btn_next_page_1.active == 1){
				if((pre_x > btn_next_page_1.point_end.x && pre_x < btn_next_page_1.point_start.x) && (pre_y > btn_next_page_1.point_start.y && pre_y < btn_next_page_1.point_end.y)){
					printf("next page pressed\n");
					cnt = window_frame_cnt * (page_cnt1 + 1);
					printf("page_cnt1 = %d, window_frame_cnt = %d\n", page_cnt1, window_frame_cnt);
					form_count = total_frame_cnt - cnt;
					printf("form_count = %d\n", form_count); 
					form_count = form_count > window_frame_cnt ? window_frame_cnt : form_count;
					page_cnt1++;
					if(page_cnt1 > 0){
						left_flag = 1;
					}else{
						left_flag = 0;
					}
					if(page_cnt1 >= form_tot_cnt - 1){
						right_flag = 0;
					}else{
						right_flag = 1;
					}
					jointwarn_paint_flag(hdc, left_flag, right_flag);

					if(WIN_102_NO == window_no){
						//jointwarn_paint_frame(hdc, &menu_hiz[cnt], form_count);
						jointwarn_paint_frame(hdc, &g_form[cnt], form_count, 1);
						break;
					}
					if(WIN_103_NO == window_no){
						jointwarn_paint_frame(hdc, &g_form[cnt], form_count, 2);
						break;
					}
					if(WIN_104_1_NO == window_no){
						jointwarn_paint_frame(hdc, &g_form[cnt], form_count, 3);
						break;
					}
					if(WIN_106_1_NO == window_no){
						JointWarn_clear_sel(hdc);
						count = form_count > window_frame_cnt ? window_frame_cnt : form_count;
						printf("cnt = %d, count = %d\n", cnt, count);
						JointWarn_106_repaint_sel(hdc, gPsel, cnt, count);	
						break;
					}
#if 0
					page_cnt1++;
					if(page_cnt1 > 0){
						left_flag = 1;
					}else{
						left_flag = 0;
					}
					if(page_cnt1 >= form_tot_cnt - 1){
						right_flag = 0;
					}else{
						right_flag = 1;
					}
					jointwarn_paint_flag(hdc, left_flag, right_flag);
#endif
				}
			}
			if(((pre_x > 5) && (pre_x < (MWINDOW_RX - 5))) && ((pre_y > 5) && (pre_y < (MWINDOW_BY - 5)))){
				//printf("form_count = %d\n", form_count);
				if((WIN_104_1_NO == window_no) || (WIN_103_NO == window_no) || (WIN_102_NO == window_no)){
				for(i=0; i<form_count; i++){
					if(pre_x >= x[i] && pre_x <= (x[i] + partWidth - 10) && pre_y >= y[i] && pre_y <= (y[i] + partHeight - 10)){

						printf("window_no = %d\n", window_no);
						if(WIN_104_1_NO == window_no){
							project_select_no = i + window_frame_cnt * page_cnt1;
							sprintf(pro_sel_no_str,"%d", project_select_no);
							printf("frame %s project select \n", pro_sel_no_str);
							
							strcpy(warn_msg[2].name, gPform_pro[project_select_no].text1);
							len = strlen(warn_msg[2].name);
							len = len > (50 - project_str_len) ? (50 - project_str_len) : len;
							memcpy(select_project_str + project_str_len, warn_msg[2].name, len);
							project_str_len += len;
							
							JointWarn_create_105(hdc, project_select_no);
							//JointWarn_create_106(hdc, 1, project_select_no);
							//create_project_window(hdc);
							goto WinProcEnd;
						}
						if(WIN_103_NO == window_no){
							equipment_select_no = i + window_frame_cnt * page_cnt1;
							sprintf(equi_sel_no_str,"%d", equipment_select_no);
							printf("frame %s equipment select \n", equi_sel_no_str);
							memset(equi_sel_str, 0, 20);	
							strcpy(equi_sel_str, g_form[equipment_select_no].text1);
							origin_str = JointWarn_104_get_data(equipment_select_no);
							printf("=======================================\n");
							JointAnalysisCmdLine(origin_str, &ptr);
							printf("=======================================\n");
							JointRunCmdLine(hdc);
							printf("=======================================\n");
							goto WinProcEnd;
						}
						if(WIN_102_NO == window_no){
							area_select_no = i + window_frame_cnt * page_cnt1;
							sprintf(area_sel_no_str,"%d", area_select_no);
							printf("frame %s area select \n", area_sel_no_str);
							
							memset(area_sel_str, 0, 20);	
							strcpy(area_sel_str, g_form[area_select_no].text1);
							//JointWarn_free_equi_buf();
							origin_str = JointWarn_103_get_data(area_select_no);
							printf("=======================================\n");
							JointAnalysisCmdLine(origin_str, &ptr);
							printf("=======================================\n");
							JointRunCmdLine(hdc);
							printf("=======================================\n");
							//create_equipment_window(hdc);
							goto WinProcEnd;
						}
					}
				}
				}
				if(WIN_106_1_NO == window_no){
					for(i=0; i<6; i++){
						if(((pre_x > select_obj[i].point_start.x) && (pre_x < select_obj[i].point_end.x)) && \
							((pre_y > select_obj[i].point_start.y) && (pre_y < select_obj[i].point_end.y))){
							select_obj_no = i + window_frame_cnt * page_cnt1;
							printf("select %d sel\n", select_obj_no);										
							JointWarn_create_top_back(hdc, 480, 280);
							//InitConfirmWindow(hWnd, 480, 280, &warnform1, 1);
						}
					}	
				}
			}

			}
			}else{
				//top window is active
				if(((pre_x > btn_cancel.point_start.x) && (pre_x < btn_cancel.point_end.x)) \
                        	&& ((pre_y > btn_cancel.point_start.y) && (pre_y < btn_cancel.point_end.y)) \
                        	){
					printf("cancel pressed\n");
					top_window = 0;
					JointWarn_create_106(hdc, 1);
				}

			}
			//EndPaint(hWnd,hdc);
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
WinProcEnd:
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

void JointRunCmdLine(HDC hdc)
{
	int len;

	switch(final_cmd)
	{
		case CMD_NULL:
			printf("CMD_NULL\n");
			break;
		case CMD_CREATE_101:
			window_no = WIN_101_NO;
			memset(display_no_str, 0, 10);
			strcpy(display_no_str, "101");
			jointwarn_create_select(hdc, &menu_hz1[0], &menu_hz1_warn);
			final_cmd = CMD_NULL;
			break;
		case CMD_CREATE_102:
			printf("CMD_CREATE_102\n");
			//create_area_window(hdc);
			//gPform_area = g_pform;
			memset(display_no_str, 0, 10);
			strcpy(display_no_str, "102");

			gRow = 4;
			gColumn = 3;
			window_no = WIN_102_NO;
			window_frame_cnt = gRow * gColumn;
			total_frame_cnt = g_form_count;
			strcpy(warn_msg[0].name, select_msg[0]);
			//jointwarn_crate_mainui(hdc, g_pform, warn_msg, 1);
			jointwarn_crate_mainui(hdc, g_form, warn_msg, 1);
			final_cmd = CMD_NULL;
			break;
		case CMD_CREATE_103:
			printf("CMD_CREATE_103\n");
			memset(display_no_str, 0, 10);
			strcpy(display_no_str, "103");
			//create_equipment_window(hdc);
			gRow = 4;
			gColumn = 3;
			window_no = WIN_103_NO;
			window_frame_cnt = gRow * gColumn;
			total_frame_cnt = g_form_count;
			strcpy(warn_msg[0].name, area_sel_str);
			strcpy(warn_msg[1].name, select_msg[1]);
	
			project_str_len = 0;
			memset(select_project_str, 0, 50);
			len = strlen(warn_msg[0].name);
			len = len > 50 ? 50 : len;
			memcpy(select_project_str, warn_msg[0].name, len);
			project_str_len += len;
	
			jointwarn_crate_mainui(hdc, g_form, warn_msg, 2);
			final_cmd = CMD_NULL;
			break;
		case CMD_CREATE_104_1:
			printf("CMD_CREATE_104_1\n");
			memset(display_no_str, 0, 10);
			strcpy(display_no_str, "104-1");
			
			gRow = 5;
			gColumn = 2;
			window_no = WIN_104_1_NO;
			window_frame_cnt = gRow * gColumn;
			total_frame_cnt = g_form_count;
			strcpy(warn_msg[1].name, equi_sel_str);
			strcpy(warn_msg[2].name, select_msg[2]);

			len = strlen(warn_msg[1].name);
			len = len > (50 - project_str_len) ? (50 - project_str_len) : len;
			memcpy(select_project_str + project_str_len, warn_msg[1].name, len);
			project_str_len += len;

			jointwarn_crate_mainui(hdc, g_form, warn_msg, 3);
			final_cmd = CMD_NULL;
			break;
		default:
			break;
		

	}

	return;

}

unsigned long gCounter;

void check_task(int *counter)
{
	printf("check_task\n");
	while(1){
		switch(final_cmd)
		{
			case CMD_CREATE_102:
				printf("CMD_CREATE_102\n");
				//create_area_window(hdc);
				final_cmd = CMD_NULL;
				break;
		}

	}

	return;
}


int MiniGUIMain (int argc, const char* argv[])
{
	MSG Msg;
	pthread_t thrd;
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
	pthread_create(&thrd, NULL, (void*)check_task, (void*)&gCounter);
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
