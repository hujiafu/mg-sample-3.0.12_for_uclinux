

/**
Json format
===================================================================
平台回复(中文采用 GB2312 编码格式)
===================================================================

更新选择区域选项 //例子 102
	{
	"sn" : "abcd", 				设备号
	"action" : "update_area",		更新选项
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

显示 105-1
	{
	"sn" : "abcd",
	"action" : "display_105",
	"sub_no" : "1",
	}

显示 105-2
	{
	"sn" : "abcd",
	"action" : "display_105",
	"sub_no" : "2",
	}

显示 105-3
	{
	"sn" : "abcd",
	"action" : "display_105",
	"sub_no" : "3",
	}

更新SEL选项 //例子 106-1, 106-2, 106-3
	{
	"sn" : "abcd", 				设备号
	"action" : "update_sel",			更新选项
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
		"action" : "request_area"
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
		"sel_no" : "1"
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
extern int index_105;
extern int final_cmd;

unsigned int select_cnt;
unsigned char sn[20];
unsigned char action[20];
unsigned char gTxBuf[TX_MAX_LEN];
struct warnForm top_warn[2];
struct textStruct top_warn_text[4];

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


int JointAnalysisCmdLine(unsigned char * orignStr, unsigned int *ptr){

	json_object *newObject, *tmpObject, *selArrayObject, *selObject, *titleArrayObject, *titleObject;
	int i;
	int count, size;
	unsigned char *tmp;
	int tmpLen;
	struct selStruct * psel;
	struct formStruct * pform;
	int index;
	
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

	if(0 == strcmp(action, "display_105")){
		tmpObject = json_object_object_get(newObject, "sub_no");
		if(tmpObject == NULL){
			printf("sub_no NULL\n");
			return 0;
		}
		sprintf(index_105, "%s", json_object_get_string(tmpObject));
		if(0 == strcmp(index_105, "1")){
			final_cmd = CMD_CREATE_105_1;
		}	
		if(0 == strcmp(index_105, "2")){
			final_cmd = CMD_CREATE_105_2;
		}	
		if(0 == strcmp(index_105, "3")){
			final_cmd = CMD_CREATE_105_3;
		}	
		
	}
	if(0 == strcmp(action, "update_sel")){
		selArrayObject = json_object_object_get(newObject, "selects");
		count = json_object_array_length(selArrayObject);
		printf("json count = %d\n", count);
		size = count * sizeof(struct selStruct);
		psel = malloc(size);
		if(psel == NULL){
			printf("malloc failed\n");
			return 0;
		}
		memset(psel, 0, size);
		*ptr = psel;
		for(i=0; i < json_object_array_length(selArrayObject); i++){

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
				memcpy(psel[i].index, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "color");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 8 > strlen(tmp) ? strlen(tmp) : 8;
				memcpy(psel[i].color, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "text1");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 20 > strlen(tmp) ? strlen(tmp) : 20;
				memcpy(psel[i].text1, tmp, tmpLen);	
			}
			tmpObject = json_object_object_get(selObject, "text2");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 20 > strlen(tmp) ? strlen(tmp) : 20;
				memcpy(psel[i].text2, tmp, tmpLen);	
			}
			json_object_put(tmpObject);
		}
	}
	if((0 == strcmp(action, "update_area")) || (0 == strcmp(action, "update_equi")) || (0 == strcmp(action, "update_pro"))){
		selArrayObject = json_object_object_get(newObject, "selects");
		count = json_object_array_length(selArrayObject);
		printf("json count = %d\n", count);
		size = count * sizeof(struct formStruct);
		pform = malloc(size);
		if(pform == NULL){
			printf("malloc failed\n");
			return 0;
		}
		memset(pform, 0, size);
		*ptr = pform;
		for(i=0; i < json_object_array_length(selArrayObject); i++){
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
				memcpy(pform[i].index, tmp, tmpLen);	
			}
			
			tmpObject = json_object_object_get(selObject, "text1");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				tmpLen = 20 > strlen(tmp) ? strlen(tmp) : 20;
				memcpy(pform[i].text1, tmp, tmpLen);
				printf("%s\n", pform[i].text1);	
			}
		}	
	}
	if(0 == strcmp(action, "update_top")){
		titleArrayObject = json_object_object_get(newObject, "titles");
		count = json_object_array_length(titleArrayObject);
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
					top_warn[index].formColor = 0x548b54ff;
				}
				if(0 == strcmp(tmp, "red")){
					top_warn[index].formColor = 0xff0000ff;
				}
				if(0 == strcmp(tmp, "yellow")){
					top_warn[index].formColor = 0xffff00ff;
				}
				printf("json: color %s\n",tmp);
			}
	
			tmpObject = json_object_object_get(titleObject, "count");
			if(tmpObject != NULL){
				tmp = json_object_get_string(tmpObject);
				printf("json: count %s\n",tmp);
				if(0 == strcmp(tmp, "1")){
					tmpObject = json_object_object_get(titleObject, "title1");
					if(tmpObject != NULL){
						if(index == 0){
							strcpy(top_warn_text[0].name, tmpObject);
							top_warn_text[0].color = 0xffffffff;
							top_warn[index].text[0] = &top_warn_text[0];
						}
						if(index == 1){
							strcpy(top_warn_text[2].name, tmpObject);
							top_warn_text[2].color = 0x191970ff;
							top_warn[index].text[0] = &top_warn_text[2];
						}
					}
					top_warn[index].textCnt = 1;
				}
				if(0 == strcmp(tmp, "2")){
					tmpObject = json_object_object_get(titleObject, "title1");
					if(tmpObject != NULL){
						if(index == 0){
							strcpy(top_warn_text[0].name, tmpObject);
							top_warn_text[0].color = 0xffffffff;
							top_warn[index].text[0] = &top_warn_text[0];
						}
						if(index == 1){
							strcpy(top_warn_text[2].name, tmpObject);
							top_warn_text[2].color = 0x191970ff;
							top_warn[index].text[0] = &top_warn_text[2];
						}
					}
					tmpObject = json_object_object_get(titleObject, "title2");
					if(tmpObject != NULL){
						if(index == 0){
							strcpy(top_warn_text[1].name, tmpObject);
							top_warn_text[1].color = 0xffffffff;
							top_warn[index].text[1] = &top_warn_text[1];
						}
						if(index == 1){
							strcpy(top_warn_text[3].name, tmpObject);
							top_warn_text[3].color = 0x191970ff;
							top_warn[index].text[1] = &top_warn_text[3];
						}
					}
					top_warn[index].textCnt = 2;
				}
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
