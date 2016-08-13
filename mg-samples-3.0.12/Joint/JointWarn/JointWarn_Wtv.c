#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include "JointWarn_Wtv.h"


int wtv_fd;

unsigned char write_buf[10];

int JointWarn_GetWtv()
{
	int ret = 0;
	int fd = -1;

	fd = open("/dev/lpc178x_wtv", O_RDWR);
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

void JointWarn_WriteWtv(int fd, unsigned char *buf, int count){
	int ret = 0;

	ret = write(fd, buf, count);
	if(ret == -1){
		printf("wtv write failed\n");
	}
}

void JointWarn_OpenWtv(int fd){

	write_buf[0] = 0xF1;
	JointWarn_WriteWtv(fd, write_buf, 1);
}

void JointWarn_StopWtv(int fd){
	write_buf[0] = 0xFE;
	JointWarn_WriteWtv(fd, write_buf, 1);
}
void JointWarn_CloseWtv(int fd){
	write_buf[0] = 0xF0;
	JointWarn_WriteWtv(fd, write_buf, 1);
}

void JointWarn_PlayWtv(int sel)
{
	int fd;
	fd = JointWarn_GetWtv();
	if(fd != -1){
		//JointWarn_OpenWtv(fd);
		//write_buf[0] = 0xF2;
		//JointWarn_WriteWtv(fd, write_buf);
		//write_buf[0] = sel;
		//JointWarn_WriteWtv(fd, write_buf);
		write_buf[0] = 0xf1;
		write_buf[1] = 0xf2;
		write_buf[2] = sel;
		JointWarn_WriteWtv(fd, write_buf, 3);
	}
	JointWarn_DelWtv(fd);
}

