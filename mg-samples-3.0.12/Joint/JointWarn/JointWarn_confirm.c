
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_UImain.h"

extern struct textStruct warn_canel;

static HWND hMainWnd1 = HWND_INVALID;

static int warn_width;
static int warn_height;

static int InitOrderProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)   //第二及处理消息   
{  
	int pre_x, pre_y;   
	HDC hdc;
	PLOGFONT s_font;
 
	switch (message) {  
		case MSG_CREATE:                  
			printf("InitOrderProc MSG_CREATE\n");
			SetFocusChild(hWnd);
       //   CreateWindow (CTRL_BUTTON,  
         //                "返回上级窗口",  
           //              WS_CHILD | BS_PUSHBUTTON | BS_CHECKED | WS_VISIBLE,  
             //            IDC_BUTTON3, /*button 3*/  
               //          10, 70, 80, 20, hWnd, 0);               
  
    //CreateWindow (CTRL_BUTTON,  
      //                   "到第三级窗口",  
        //                 WS_CHILD | BS_PUSHBUTTON | BS_CHECKED | WS_VISIBLE,  
          //               IDC_BUTTON4, /*Button 4 */  
            //             100, 70, 80, 20, hWnd, 0);    
			break;   
		case MSG_PAINT:
			hdc = BeginPaint(hWnd);
			//SetBkColor(hdc, RGBA2Pixel(hdc, 0x00, 0xB2, 0xEE, 0xFF));
			SetBkMode(hdc,BM_TRANSPARENT);			

			SetBrushColor(hdc, RGBA2Pixel(hdc, 0x18, 0x74, 0xCD, 0xFF));
			FillBox(hdc, 0, 0, warn_width, warn_height);

			SetPenColor(hdc, RGBA2Pixel(hdc, 0x00, 0xFF, 0x00, 0xFF));
			SetPenWidth(hdc, 2);
			SetPenCapStyle(hdc, PT_CAP_ROUND);
			SetPenJoinStyle(hdc, PT_JOIN_ROUND);
			LineEx(hdc, 2, 2, warn_width-2, 2);
			LineEx(hdc, warn_width-2, 2, warn_width-2, warn_height-2);
			LineEx(hdc, warn_width-2, warn_height-2, 2, warn_height-2);
			LineEx(hdc, 2, warn_height-2, 2, 2);
			//Rectangle(hdc, 2, 2, 337, 257);

			SetBrushColor(hdc, RGBA2Pixel(hdc, 0x68, 0x22, 0x8B, 0xFF));
			FillBox(hdc, warn_width - 100, warn_height - 60, 80, 40);
		
			s_font = CreateLogFont("FONT_TYPE_NAME_SCALE_TTF", "mini", "GB2312-0", \
                		FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN, FONT_FLIP_NIL, FONT_OTHER_NIL, FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE, warn_canel.filesize, 0);
        		SelectFont(hdc, s_font);
			//SetPenWidth(hdc, 0);
        		SetTextColor(hdc, COLOR_lightwhite);
			TextOut(hdc, warn_width - 90 + warn_canel.offsetx, warn_height - 60 + warn_canel.offsety, warn_canel.name);
	
			EndPaint(hWnd,hdc);
			break; 
 	case MSG_LBUTTONDOWN:
                        printf("MSG_LBUTTONDOWN 1\n");
                        pre_x = LOWORD(lParam);
                        pre_y = HIWORD(lParam);
                        printf("x = %d, y = %d\n", pre_x, pre_y);
	break; 
    case MSG_COMMAND:  
#if 0
       {//-----------------Event   
           int id    = LOWORD(wParam);  
           int code = HIWORD(wParam);  
           char buffer [256];  
           sprintf (buffer, "ID: %d, Code: %x", id, code);  
           switch (id)  
           {  
               case (IDC_BUTTON3):               
                 SendMessage (hWnd, MSG_CLOSE, 0, 0);    
               break;                
               case (IDC_BUTTON4):  
    if(code == BN_CLICKED)  
  
 {   
                   testDialogBox3 (hWnd);                 
     }  
               break;      
               default:  
               break;  
           }                        
       }
#endif  
       break;  
      
case MSG_DESTROY:  
           DestroyAllControls (hWnd);  
           hMainWnd1 = HWND_INVALID;  
return 0;    
  
case MSG_CLOSE:  
           DestroyMainWindow (hWnd);  
           MainWindowCleanup (hWnd);  
      return 0;  
   }     
   return DefaultMainWinProc (hWnd, message, wParam, lParam);  
}  



static void InitCreateInfoTWO(PMAINWINCREATE pCreateInfo)  
{  
	pCreateInfo->dwStyle = WS_CHILD | WS_VISIBLE;  
	pCreateInfo->dwExStyle = WS_EX_NONE;  
	pCreateInfo->spCaption = "";  
	pCreateInfo->hMenu = 0;  
	pCreateInfo->hCursor = GetSystemCursor(1);  
	pCreateInfo->hIcon = 0;  
	pCreateInfo->MainWindowProc = InitOrderProc; //窗体回调函数   
	pCreateInfo->iBkColor = COLOR_darkblue;  
	pCreateInfo->dwAddData = 0;  
}  



int InitConfirmWindow(HWND hWnd, int width, int height)
{
	MAINWINCREATE CreateInfo; //新建一个窗口  
	MSG Msg;
	HDC hdc; 
	
	//hdc = BeginPaint(hWnd); 
	//hdc = GetClientDC(hWnd);
	//SetPenColor(hdc, RGBA2Pixel(hdc, 0xFF, 0x00, 0x00, 0xFF));
	//Rectangle(hdc, 300, 100, 500, 300);
	//LineEx(hdc, 300, 100, 500, 100);
	warn_width = width;
	warn_height = height;	
	InitCreateInfoTWO (&CreateInfo);  
	CreateInfo.hHosting = hWnd;
	CreateInfo.lx = (MWINDOW_RX - width)>>1;  
	CreateInfo.ty = (MWINDOW_BY - height)>>1;  
	CreateInfo.rx = width + CreateInfo.lx;  
	CreateInfo.by = height + CreateInfo.ty;  
	hMainWnd1 = CreateMainWindow(&CreateInfo);//建立窗口     
  
	if(hMainWnd1 != HWND_INVALID)   
	{ 
		printf("hMainWnd1\n");
	//	EnableWindow(hWnd, FALSE);
	//	ShowWindow(hMainWnd1, SW_SHOWNORMAL); //显示窗口   
		
	//	while(GetMessage(&Msg,hMainWnd1))
        //	{
          //      	TranslateMessage(&Msg);
          //      	DispatchMessage(&Msg);
        //	}
	//	printf("hMainWnd1 end\n");
		return;  
	} 
	//EndPaint(hWnd,hdc); 
}


