#ifndef __JOINT_WARN_JOSN_H__
#define	__JOINT_WARN_JOSN_H__

#define TX_MAX_LEN	1024

#define MAX_FORM_NUM	50
#define MAX_SEL_NUM	50
#define MAX_MSGFORM_NUM 4

struct selStruct{
        unsigned char index[4];
        unsigned char color[10];
	unsigned char text1[22];
	unsigned char text2[22];
};

struct formStruct{
        unsigned char index[4];
	unsigned char color[10]
	unsigned char text1[22];
};

struct msgformStruct{
	unsigned char index[4];
	unsigned char color[10];
	unsigned char textcolor[10];
	unsigned char text1[100];
};


#endif 
