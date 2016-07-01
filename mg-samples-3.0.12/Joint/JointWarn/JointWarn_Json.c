

/**
Json format
===================================================================
平台回复(中文采用 GB2312 编码格式)
===================================================================

更新选择区域选项 //例子 102
	{
	"sn" : "abcd", 				设备号
	"action" : "update_area",		更新选项
	"display_no" : "102",
	"selects" : [ 
	{
		"index" : "1",
		"text1"  : "具体内容"           具体内容		
	}, 
	{
		"index" : "2",
		"text1"  : "具体内容"           具体内容		
	} 
	]
	}

更新选择设备选项 //例子 103
	{
	"sn" : "abcd", 				设备号
	"action" : "update_equi",		更新选项
	"display_no" : "103",
	"selects" : [ 
	{
		"index" : "1",
		"text1"  : "具体内容"           具体内容		
	}, 
	{
		"index" : "2",
		"text1"  : "具体内容"           具体内容		
	} 
	]
	}

更新选择项目选项 //例子 104-1, 104-2
	{
	"sn" : "abcd", 				设备号
	"action" : "update_pro",		更新选项
	"display_no" : "104-1",
	"selects" : [ 
	{
		"index" : "1",
		"text1"  : "具体内容"           具体内容		
	}, 
	{
		"index" : "2",
		"text1"  : "具体内容"           具体内容		
	} 
	]
	}

显示FROM内容 //例子 105-1, 105-2, 105-3, 106-3
	{
	"sn" : "abcd",
	"action" : "display_form",
	"display_no" : "105-1",
	"selects" : [
		{
			"index" : "1",
			"color" : "red",
			"textcolor" : "white",
			"text1" : "具体内容"	
		},
		{
			"index" : "2",
			"color" : "red",
			"textcolor" : "white",
			"text1" : "具体内容"	
		}
	]
	}

更新SEL选项 //例子 106-1, 106-2, 107
	{
	"sn" : "abcd", 				设备号
	"action" : "update_sel",			更新选项
	"display_no" : "106-1",
	"sub_no" : "1",
	"selects" : [ 
	{
		"index" : "1",
		"color" : "green",		red or green
		"text1"  : "具体内容",           具体内容		
		"text2"  : "提示内容",           提示内容		
	}, 
	{
		"index" : "2",
		"color" : "red",		red or green
		"text1"  : "具体内容",           具体内容		
		"text2"  : "提示内容"           提示内容		
	} 
	]
	}

显示悬浮窗口
	{
		"sn" : "abcd",
		"action" : "update_top",
		"titles" : [
		{
			"index" : "1",
			"count" : "1",
			"color" : "red",
			"title1" : "具体内容",
			"title2" : "具体内容"
		},
		{
			"index" : "2",
			"count" : "2",
			"color" : "yellow",
			"title1" : "具体内容",
			"title2" : "具体内容"
		}
		]
	}
==========================================================================
设备发送请求
==========================================================================
设备发送区域请求
	{
		"sn" : "abcd",
		"display_no" : "101"
		"select_no" : "0"
		"back_pressed" : "Ture"
	}

设备发送设备请求
	{
		"sn" : "abcd",
		"action" : "request_equi",
		"area_no"  : "1"
	}

设备发送项目请求
	{
		"sn" : "abcd",
		"action" : "request_pro",
		"equi_no" : "1"
	}

设备发送申请请求
	{
		"sn" : "abcd",
		"action" : "request_oper",
		"pro_no" : "1"
	}
发送选择介质
	{
		"sn" : "abcd",
		"action" : "request_sel",
		"sel_no" : "1",
		"id" : "1"
	}
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include "JointWarn_Main.h"
#include "JointWarn_UImain.h"
#include "JointWarn_Json.h"

#include "json-c/json.h"


extern unsigned char jointwarn_sn[4];
extern unsigned char area_sel_no_str[4];
extern unsigned char equi_sel_no_str[4];
extern unsigned char pro_sel_no_str[4];
extern struct textStruct sel_prompt_msg;
extern int index_105;
extern int final_cmd;

unsigned int select_cnt;
unsigned char sn[20];
unsigned char action[20];
unsigned char display_no[20];
unsigned char gTxBuf[TX_MAX_LEN];
struct warnForm top_warn[2];
struct textStruct top_warn_text[4];
int g_update_sel_index;
struct formStruct * g_pform;
struct selStruct * g_psel;
int g_form_count;
int g_msgform_count;
int g_sel_count;
int g_top_count;

struct formStruct g_form[MAX_FORM_NUM];
struct selStruct g_sel[MAX_SEL_NUM];
struct msgformStruct g_msgform[MAX_MSGFORM_NUM];
unsigned char sel_title[50];
unsigned char sel_title_color[10];
#if 0
int check_cmd_and_run()
{
	printf("check_cmd_and_run\n");
}

int check_cmd_init(){

        int res = 0;
        struct itimerval tick;

        signal(SIGALRM, check_cmd_and_run);
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
#endif

int JointCreateAreaRequest(unsigned char * resultBuf)
{
	json_object *postObject;

	postObject = json_object_new_object();
	json_object_object_add(postObject, "sn", json_object_new_string(jointwarn_sn));
	json_object_object_add(postObject, "action", json_object_new_string("request_area"));

	strcpy(resultBuf, json_object_get_string(postObject));
	json_object_put(postObject);

	return;
}

int JointCreateEquiRequest(unsigned char * resultBuf)
{
	json_object *postObject;

	postObject = json_object_new_object();
	json_object_object_add(postObject, "sn", json_object_new_string(jointwarn_sn));
	json_object_object_add(postObject, "action", json_object_new_string("request_equi"));
	json_object_object_add(postObject, "area_no", json_object_new_string(area_sel_no_str));

	strcpy(resultBuf, json_object_get_string(postObject));
	json_object_put(postObject);

	return;
}

int JointCreateProRequest(unsigned char * resultBuf)
{
	json_object *postObject;

	postObject = json_object_new_object();
	json_object_object_add(postObject, "sn", json_object_new_string(jointwarn_sn));
	json_object_object_add(postObject, "action", json_object_new_string("request_pro"));
	json_object_object_add(postObject, "equi_no", json_object_new_string(equi_sel_no_str));

	strcpy(resultBuf, json_object_get_string(postObject));
	json_object_put(postObject);

	return;
}

int JointCreateOperRequest(unsigned char * resultBuf)
{
	json_object *postObject;

	postObject = json_object_new_object();
	json_object_object_add(postObject, "sn", json_object_new_string(jointwarn_sn));
	json_object_object_add(postObject, "action", json_object_new_string("request_oper"));
	json_object_object_add(postObject, "pro_no", json_object_new_string(pro_sel_no_str));

	strcpy(resultBuf, json_object_get_string(postObject));
	json_object_put(postObject);

	return;
}

int JointWarnCreateRequest(unsigned char * resultBuf, unsigned char * action, unsigned char * display_no, unsigned char * select_no, unsigned char * back, unsigned char * cannel, unsigned char *id)
{
	json_object *postObject;

	postObject = json_object_new_object();
	json_object_object_add(postObject, "sn", json_object_new_string(jointwarn_sn));
	json_object_object_add(postObject, "action", json_object_new_string(action));
	json_object_object_add(postObject, "display_no", json_object_new_string(display_no));
	json_object_object_add(postObject, "select_no", json_object_new_string(select_no));
	json_object_object_add(postObject, "id", json_object_new_string(id));
	json_object_object_add(postObject, "back_btn", json_object_new_string(back));
	json_object_object_add(postObject, "cannel_btn", json_object_new_string(cannel));

	strcpy(resultBuf, json_object_get_string(postObject));
	json_object_put(postObject);

	return;
}

int JointAnalysisCmdLine(unsigned char * orignStr, unsigned int *ptr){

	json_object *newObject, *tmpObject, *selArrayObject, *selObject, *titleArrayObject, *titleObject;
	int i;
	int count, size;
	unsigned char *tmp;
	int tmpLen;
	int index;
	int len;
	unsigned char tbuf[10];

	newObject = NULL;
	selObject = NULL;
	titleObject = NULL;
	
	newObject = json_tokener_parse(orignStr);
	if(newObject == NULL){
		printf("newObject NULL\n");
		return 0;
	}
	tmpObject = json_object_object_get(newObject, "sn");
	if(tmpObject == NULL){
		printf("sn NULL\n");
		return 0;
	}
	strcpy(sn, json_object_get_string(tmpObject));
	tmpObject = json_object_object_get(newObject, "action");
	if(tmpObject == NULL){
		printf("action NULL\n");
		return 0;
	}
	strcpy(action, json_object_get_string(tmpObject));
	strcpy(sn, json_object_get_string(tmpObject));
	tmpObject = json_object_object_get(newObject, "display_no");
	if(tmpObject == NULL){
		printf("action NULL\n");
		return 0;
	}
	strcpy(display_no, json_object_get_string(tmpObject));
	printf("action %s\n", action);
	if(0 == strcmp(action, "display_105")){
		tmpObject = json_object_object_get(newObject, "sub_no");
		if(tmpObject == NULL){
			printf("sub_no NULL\n");
			return 0;
		}
		strcpy(tbuf, json_object_get_string(tmpObject));
		//sprintf(index_105, "%s", json_object_get_string(tmpObject));
		if(0 == strcmp(tbuf, "1")){
			final_cmd = CMD_CREATE_105_1;
			printf("display_105 1\n");
			return 1;
		}	
		if(0 == strcmp(tbuf, "2")){
			final_cmd = CMD_CREATE_105_2;
			printf("display_105 2\n");
			return 2;
		}	
		if(0 == strcmp(tbuf, "3")){
			final_cmd = CMD_CREATE_105_3;
			printf("display_105 3\n");
			return 3;
		}	
		
	}
	if(0 == strcmp(action, "display_106")){
		tmpObject = json_object_object_get(newObject, "sub_no");
		if(tmpObject == NULL){
			printf("sub_no NULL\n");
			return 0;
		}
		strcpy(tbuf, json_object_get_string(tmpObject));
		if(0 == strcmp(tbuf, "3")){
			final_cmd = CMD_CREATE_106_3;
			printf("display_106 3\n");
			*ptr = NULL;
			return 3;
		}	

	}
	if(0 == strcmp(action, "display_form")){
		if(0 == strcmp(display_no, "105-1")){
			final_cmd = CMD_CREATE_105_1;
		}	
		if(0 == strcmp(display_no, "105-2")){
			final_cmd = CMD_CREATE_105_2;
		}	
		if(0 == strcmp(display_no, "105-3")){
			final_cmd = CMD_CREATE_105_3;
		}	
		if(0 == strcmp(display_no, "106-3")){
			final_cmd = CMD_CREATE_106_3;
		}	
		if(0 == strcmp(display_no, "106-4")){
			final_cmd = CMD_CREATE_106_4;
		}	
		if(0 == strcmp(display_no, "111-1")){
			final_cmd = CMD_CREATE_111_1;
		}	
		if(0 == strcmp(display_no, "113-1")){
			final_cmd = CMD_CREATE_113_1;
		}	
		if(0 == strcmp(display_no, "113-2")){
			final_cmd = CMD_CREATE_113_2;
		}	
		if(0 == strcmp(display_no, "113-3")){
			final_cmd = CMD_CREATE_113_3;
		}	
		if(0 == strcmp(display_no, "113-4")){
			final_cmd = CMD_CREATE_113_4;
		}	
		if(0 == strcmp(display_no, "114-3")){
			final_cmd = CMD_CREATE_114_3;
		}	
		if(0 == strcmp(display_no, "114-4")){
			final_cmd = CMD_CREATE_114_4;
		}	
		if(0 == strcmp(display_no, "114-5")){
			final_cmd = CMD_CREATE_114_5;
		}	
		if(0 == strcmp(display_no, "114-6")){
			final_cmd = CMD_CREATE_114_6;
		}	
		if(0 == strcmp(display_no, "119-1")){
			final_cmd = CMD_CREATE_119_1;
		}	
		if(0 == strcmp(display_no, "120")){
			final_cmd = CMD_CREATE_120;
		}	
		if(0 == strcmp(display_no, "121-1")){
			final_cmd = CMD_CREATE_121_1;
		}	
		if(0 == strcmp(display_no, "121-2")){
			final_cmd = CMD_CREATE_121_2;
		}	
		if(0 == strcmp(display_no, "122")){
			final_cmd = CMD_CREATE_122;
		}	
		if(0 == strcmp(display_no, "123")){
			final_cmd = CMD_CREATE_123;
		}	
		selArrayObject = json_object_object_get(newObject, "selects");
		count = json_object_array_length(selArrayObject);
		g_msgform_count = count;
		printf("msgform count = %d\n", count);
		len = json_object_array_length(selArrayObject) > MAX_MSGFORM_NUM ? MAX_MSGFORM_NUM : json_object_array_length(selArrayObject);
		for(i=0; i < len; i++){
			selObject = json_object_array_get_idx(selArrayObject, i);
			if(selObject == NULL){
				printf("selObject NULL\n");
				continue;
			}else{
				selObject = json_tokener_parse(json_object_get_string(selObject));
			}
			
			tmpObject = json_object_object_get(selObject, "index");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 3 > strlen(tmp) ? strlen(tmp) : 3;
				memcpy(g_msgform[i].index, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "color");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 8 > strlen(tmp) ? strlen(tmp) : 8;
				memcpy(g_msgform[i].color, tmp, tmpLen);
				printf("color %s\n", tmp);
			}
			tmpObject = json_object_object_get(selObject, "textcolor");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 8 > strlen(tmp) ? strlen(tmp) : 8;
				memcpy(g_msgform[i].textcolor, tmp, tmpLen);
				printf("textcolor %s\n", tmp);
			}
			tmpObject = json_object_object_get(selObject, "text1");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 98 > strlen(tmp) ? strlen(tmp) : 98;
				memcpy(g_msgform[i].text1, tmp, tmpLen);
			}

		}
		return count;

	}
	if(0 == strcmp(action, "update_sel")){
		if(0 == strcmp(display_no, "106-1")){
			final_cmd = CMD_CREATE_106_1;
		}	
		if(0 == strcmp(display_no, "106-2")){
			final_cmd = CMD_CREATE_106_2;
		}	
		if(0 == strcmp(display_no, "107")){
			final_cmd = CMD_CREATE_107;
		}	
		if(0 == strcmp(display_no, "110")){
			final_cmd = CMD_CREATE_110;
		}	
		if(0 == strcmp(display_no, "114-1")){
			final_cmd = CMD_CREATE_114_1;
		}	
		if(0 == strcmp(display_no, "114-2")){
			final_cmd = CMD_CREATE_114_2;
		}	
		if(0 == strcmp(display_no, "115")){
			final_cmd = CMD_CREATE_115;
		}	
		if(0 == strcmp(display_no, "118")){
			final_cmd = CMD_CREATE_118;
		}	
		//g_update_sel_index = 0;
		tmpObject = json_object_object_get(newObject, "titlecolor");
		if(tmpObject != NULL){
			tmp = json_object_get_string(tmpObject);
			tmpLen = 8 > strlen(tmp) ? strlen(tmp) : 8;
			memcpy(sel_title_color, tmp, tmpLen);	
		}
		tmpObject = json_object_object_get(newObject, "title");
		if(tmpObject != NULL){
			tmp = json_object_get_string(tmpObject);
			tmpLen = 48 > strlen(tmp) ? strlen(tmp) : 48;
			memcpy(sel_title, tmp, tmpLen);	
		}
		//g_update_sel_index = atoi(json_object_get_string(tmpObject));
		
		selArrayObject = json_object_object_get(newObject, "selects");
		count = json_object_array_length(selArrayObject);
		g_sel_count = count;
		printf("json count = %d\n", count);
#if 0
		size = count * sizeof(struct selStruct);
		g_psel = malloc(size);
		if(g_psel == NULL){
			printf("malloc failed\n");
			return 0;
		}
		memset(g_psel, 0, size);
		*ptr = g_psel;
#endif
		*ptr = g_sel;
		len = json_object_array_length(selArrayObject) > MAX_SEL_NUM ? MAX_SEL_NUM : json_object_array_length(selArrayObject);
		for(i=0; i < len; i++){

			selObject = json_object_array_get_idx(selArrayObject, i);
			if(selObject == NULL){
				printf("selObject NULL\n");
				continue;
			}else{
				selObject = json_tokener_parse(json_object_get_string(selObject));
			}

			tmpObject = json_object_object_get(selObject, "index");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 3 > strlen(tmp) ? strlen(tmp) : 3;
				memcpy(g_sel[i].index, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "color");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 8 > strlen(tmp) ? strlen(tmp) : 8;
				memcpy(g_sel[i].color, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "text1");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 20 > strlen(tmp) ? strlen(tmp) : 20;
				memcpy(g_sel[i].text1, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "text2");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 20 > strlen(tmp) ? strlen(tmp) : 20;
				memcpy(g_sel[i].text2, tmp, tmpLen);	
			}
			json_object_put(tmpObject);
		}
	}
	if((0 == strcmp(action, "update_area")) || (0 == strcmp(action, "update_equi")) || (0 == strcmp(action, "update_pro"))){
		selArrayObject = json_object_object_get(newObject, "selects");
		count = json_object_array_length(selArrayObject);
		g_form_count = count;
		printf("json count = %d\n", count);
		//size = count * sizeof(struct formStruct);
		//g_pform = malloc(size);
		//if(g_pform == NULL){
		//	printf("malloc failed\n");
		//	return 0;
		//}
		//memset(g_pform, 0, size);
		//*ptr = g_pform;
		len = json_object_array_length(selArrayObject) > MAX_FORM_NUM ? MAX_FORM_NUM : json_object_array_length(selArrayObject);
		//for(i=0; i < json_object_array_length(selArrayObject); i++){
		for(i=0; i < len; i++){
			selObject = json_object_array_get_idx(selArrayObject, i);
			if(selObject == NULL){
				printf("selObject NULL\n");
				continue;
			}else{
				selObject = json_tokener_parse(json_object_get_string(selObject));
			}
			
			tmpObject = json_object_object_get(selObject, "index");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 3 > strlen(tmp) ? strlen(tmp) : 3;
				//memcpy(g_pform[i].index, tmp, tmpLen);	
				memcpy(g_form[i].index, tmp, tmpLen);	
			}
			
			tmpObject = json_object_object_get(selObject, "text1");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 20 > strlen(tmp) ? strlen(tmp) : 20;
				//memcpy(g_pform[i].text1, tmp, tmpLen);
				memcpy(g_form[i].text1, tmp, tmpLen);
				printf("%s\n", g_form[i].text1);	
			}
		}
		if(0 == strcmp(display_no, "102")){
			final_cmd = CMD_CREATE_102;
		}	
		if(0 == strcmp(display_no, "103")){
			final_cmd = CMD_CREATE_103;
		}	
		if(0 == strcmp(display_no, "104-1")){
			final_cmd = CMD_CREATE_104_1;
		}	
		if(0 == strcmp(display_no, "104-2")){
			final_cmd = CMD_CREATE_104_2;
		}
		return count;	
	}
	if(0 == strcmp(action, "system")){
		
		if(0 == strcmp(display_no, "124")){
			final_cmd = CMD_CREATE_124;
		}
		return 0;
	}
	if(0 == strcmp(action, "update_top")){
		printf("Json: update_top\n");
		if(0 == strcmp(display_no, "108-1")){
			final_cmd = CMD_CREATE_108_1;
		}
		if(0 == strcmp(display_no, "108-2")){
			final_cmd = CMD_CREATE_108_2;
		}
		if(0 == strcmp(display_no, "108-3")){
			final_cmd = CMD_CREATE_108_3;
		}
		if(0 == strcmp(display_no, "108-4")){
			final_cmd = CMD_CREATE_108_4;
		}
		if(0 == strcmp(display_no, "109-1")){
			final_cmd = CMD_CREATE_109_1;
		}
		if(0 == strcmp(display_no, "109-2")){
			final_cmd = CMD_CREATE_109_2;
		}
		if(0 == strcmp(display_no, "109-3")){
			final_cmd = CMD_CREATE_109_3;
		}
		if(0 == strcmp(display_no, "111-2")){
			final_cmd = CMD_CREATE_111_2;
		}
		if(0 == strcmp(display_no, "111-3")){
			final_cmd = CMD_CREATE_111_3;
		}
		if(0 == strcmp(display_no, "116-1")){
			final_cmd = CMD_CREATE_116_1;
		}
		if(0 == strcmp(display_no, "116-2")){
			final_cmd = CMD_CREATE_116_2;
		}
		if(0 == strcmp(display_no, "116-3")){
			final_cmd = CMD_CREATE_116_3;
		}
		if(0 == strcmp(display_no, "116-4")){
			final_cmd = CMD_CREATE_116_4;
		}
		if(0 == strcmp(display_no, "117-1")){
			final_cmd = CMD_CREATE_117_1;
		}
		if(0 == strcmp(display_no, "117-2")){
			final_cmd = CMD_CREATE_117_2;
		}
		if(0 == strcmp(display_no, "117-3")){
			final_cmd = CMD_CREATE_117_3;
		}
		if(0 == strcmp(display_no, "119-2")){
			final_cmd = CMD_CREATE_119_2;
		}
		if(0 == strcmp(display_no, "119-3")){
			final_cmd = CMD_CREATE_119_3;
		}
	
		titleArrayObject = json_object_object_get(newObject, "titles");
		count = json_object_array_length(titleArrayObject);
		g_top_count = count;
		for(i=0; i < json_object_array_length(titleArrayObject); i++){

			titleObject = json_object_array_get_idx(titleArrayObject, i);
			if(titleObject == NULL){
				printf("titleObject NULL\n");
				continue;
			}else{
				titleObject = json_tokener_parse(json_object_get_string(titleObject));
			}
			tmpObject = json_object_object_get(titleObject, "index");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				if(0 == strcmp(tmp, "1")){
					index = 0;			
				}
				if(0 == strcmp(tmp, "2")){
					index = 1;			
				}
				printf("json: index %s\n",tmp);
				
			}
			
			tmpObject = json_object_object_get(titleObject, "color");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				if(0 == strcmp(tmp, "green")){
					top_warn[index].formColor = 0x228b22ff;
				}
				if(0 == strcmp(tmp, "red")){
					top_warn[index].formColor = 0xff0000ff;
				}
				if(0 == strcmp(tmp, "yellow")){
					top_warn[index].formColor = 0xffff00ff;
				}
				if(0 == strcmp(tmp, "white")){
					top_warn[index].formColor = 0xffffffff;
				}
				printf("json: color %s\n",tmp);
			}
			
			tmpObject = json_object_object_get(titleObject, "textcolor");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				if(index == 0){
					if(0 == strcmp(tmp, "white")){
						top_warn_text[0].color = 0xffffffff;
					}
					if(0 == strcmp(tmp, "blue")){
						top_warn_text[0].color = 0x0000ffff;
					}
					if(0 == strcmp(tmp, "red")){
						top_warn_text[0].color = 0xff0000ff;
					}
				}
				if(index == 1){
					if(0 == strcmp(tmp, "white")){
						top_warn_text[2].color = 0xffffffff;
					}
					if(0 == strcmp(tmp, "blue")){
						top_warn_text[2].color = 0x0000ffff;
					}
					if(0 == strcmp(tmp, "red")){
						top_warn_text[2].color = 0xff0000ff;
					}
				}
			
			}

			tmpObject = json_object_object_get(titleObject, "count");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				printf("json: count %s\n",tmp);
				if(0 == strcmp(tmp, "1")){
					tmpObject = json_object_object_get(titleObject, "title1");
					if(tmpObject != NULL){
						tmp = json_object_get_string(tmpObject);
						if(index == 0){
							memset(top_warn_text[0].name, 0, 100);
							strcpy(top_warn_text[0].name, tmp);
							//top_warn_text[0].color = 0xffffffff;
							top_warn[index].text[0] = &top_warn_text[0];
						}
						if(index == 1){
							memset(top_warn_text[2].name, 0, 100);
							strcpy(top_warn_text[2].name, tmp);
							//top_warn_text[2].color = 0x191970ff;
							top_warn[index].text[0] = &top_warn_text[2];
						}
					}
					top_warn[index].textCnt = 1;
				}
				if(0 == strcmp(tmp, "2")){
					tmpObject = json_object_object_get(titleObject, "title1");
					if(tmpObject != NULL){
						tmp = json_object_get_string(tmpObject);
						if(index == 0){
							memset(top_warn_text[0].name, 0, 100);
							strcpy(top_warn_text[0].name, tmp);
							//top_warn_text[0].color = 0xffffffff;
							top_warn[index].text[0] = &top_warn_text[0];
						}
						if(index == 1){
							memset(top_warn_text[2].name, 0, 100);
							strcpy(top_warn_text[2].name, tmp);
							//top_warn_text[2].color = 0x191970ff;
							top_warn[index].text[0] = &top_warn_text[2];
						}
					}
					tmpObject = json_object_object_get(titleObject, "title2");
					if(tmpObject != NULL){
						tmp = json_object_get_string(tmpObject);
						if(index == 0){
							memset(top_warn_text[1].name, 0, 100);
							strcpy(top_warn_text[1].name, tmp);
							//top_warn_text[1].color = 0xffffffff;
							top_warn[index].text[1] = &top_warn_text[1];
						}
						if(index == 1){
							memset(top_warn_text[3].name, 0, 100);
							strcpy(top_warn_text[3].name, tmp);
							//top_warn_text[3].color = 0x191970ff;
							top_warn[index].text[1] = &top_warn_text[3];
						}
					}
					top_warn[index].textCnt = 2;
				}
				*ptr = top_warn;
			}

		}

	}
	if(selObject != NULL)
		json_object_put(selObject);

	if(titleObject != NULL)
		json_object_put(titleObject);
		
	if(newObject != NULL)
		json_object_put(newObject);
	return count;
}

void test_select_json(){

	struct selStruct * psel;
	unsigned int ptr;
	int count;
	int i;
	
	unsigned char test[500] = "{\"sn\" : \"JointCtrl1\", \"action\" : \"update_sel\", \"selects\" : \
	[{\"index\" : \"1\", \"color\" : \"green\", \"text1\" : \"mytest1\", \"text2\" : \"mytext2\"},\
	{\"index\" : \"2\", \"color\" : \"red\", \"text1\" : \"mytest3\", \"text2\" : \"mytext4\"}\
	]}";
	//unsigned char test[500] = "{\"sn\" : \"JointCtrl1\", \"action\" : \"update_sel\"}";

	printf("%s\n", test);
	count = JointAnalysisCmdLine(test, &ptr);
	psel = (struct selStruct *)ptr;
	if(psel != NULL){
		for(i=0; i<count; i++){
			printf("psel[%d].index = %s\n", i, psel[i].index);
			printf("psel[%d].color = %s\n", i, psel[i].color);
			printf("psel[%d].text1 = %s\n", i, psel[i].text1);
			printf("psel[%d].text2 = %s\n", i, psel[i].text2);
		}
		free(psel);
	}

	

}
