#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JointWarn_Wtv.h"


int wtv_fd;


int JointWarn_GetWtv()
{
	int ret = 0;
	int fd = -1;

	fd = open("/dev/lpc178x_wtv", 0);
	if(fd < 0)
	{
		printf("can't open /dev/lpc178x_wtv\n");
		return -1;
	}
	return fd;
}

void JointWarn_DelWtv(int fd)
{
	close(fd);

}

void JointWarn_WriteWtv(int fd, unsigned char data){
	int ret = 0;

	ret = write(fd, &data, 1);
	if(ret == -1){
		printf("wtv write failed\n");
	}
}

void JointWarn_OpenWtv(int fd){
	JointWarn_WriteWtv(fd, 0xF1);
}

void JointWarn_StopWtv(int fd){
	JointWarn_WriteWtv(fd, 0xFE);
}
void JointWarn_CloseWtv(int fd){
	JointWarn_WriteWtv(fd, 0xF0);
}

void JointWarn_PlayWtv(int sel)
{
	int fd;
	fd = JointWarn_GetWtv();
	if(fd != -1){
		JointWarn_OpenWtv(fd);
		JointWarn_WriteWtv(fd, 0xF2);
		JointWarn_WriteWtv(fd, sel);
	}
	JointWarn_DelWtv(fd);
}

