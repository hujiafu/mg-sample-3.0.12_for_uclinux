
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

static HWND hMainWnd1 = HWND_INVALID;

static int InitOrderProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)   //第二及处理消息   
{  
	int pre_x, pre_y;   
 
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
	pCreateInfo->dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER;  
	pCreateInfo->dwExStyle = WS_EX_NONE;  
	pCreateInfo->spCaption = "";  
	pCreateInfo->hMenu = 0;  
	pCreateInfo->hCursor = GetSystemCursor(1);  
	pCreateInfo->hIcon = 0;  
	pCreateInfo->MainWindowProc = InitOrderProc; //窗体回调函数   
	pCreateInfo->lx = (800 - 320)>>1;  
	pCreateInfo->ty = (480 - 240)>>1;  
	pCreateInfo->rx = 320 + pCreateInfo->lx;  
	pCreateInfo->by = 240 + pCreateInfo->ty;  
	pCreateInfo->iBkColor = COLOR_darkblue;  
	pCreateInfo->dwAddData = 0;  
}  



int InitConfirmWindow(HWND hWnd, int winx, int winy, int width, int heigth)
{
	MAINWINCREATE CreateInfo; //新建一个窗口  
	MSG Msg; 
 
	InitCreateInfoTWO (&CreateInfo);  
	CreateInfo.hHosting = hWnd;
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
}


