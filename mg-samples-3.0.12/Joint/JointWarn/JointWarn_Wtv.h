#ifndef __JOINTWARN_WTV_H__
#define __JOINTWARN_WTV_H__

int JointWarn_GetWtv();
void JointWarn_DelWtv(int fd);
void JointWarn_WriteWtv(int fd, unsigned char * buf, int count);
void JointWarn_OpenWtv(int fd);
void JointWarn_StopWtv(int fd);
void JointWarn_CloseWtv(int fd);
void JointWarn_CloseWtv(int sel);






#endif
