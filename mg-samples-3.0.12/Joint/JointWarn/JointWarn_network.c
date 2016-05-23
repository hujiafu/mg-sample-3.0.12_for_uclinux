
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <string.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h> 
#include<fcntl.h> 

#include "JointWarn_network.h"

#define PORT 10008

unsigned char udp_buf[UDP_MAX_LEN];
int gCounter = 0;

int sockfd;
struct sockaddr_in addr;  
int addr_len;

void udp_listen_task(int *counter)
{
	
    int len;  
    
    addr_len = sizeof(struct sockaddr_in);  
    /*建立socket*/  
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){  
        perror ("socket");  
        exit(1);  
    }  
    /*填写sockaddr_in 结构*/  
    bzero ( &addr, sizeof(addr) );  
    addr.sin_family=AF_INET;  
    addr.sin_port=htons(PORT);  
    addr.sin_addr.s_addr=htonl(INADDR_ANY) ;  
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0){  
        perror("connect");  
        exit(1);  
    }  
    while(1){  
        bzero(udp_buf,sizeof(udp_buf));  
        len = recvfrom(sockfd, udp_buf, sizeof(udp_buf), 0 , (struct sockaddr *)&addr ,&addr_len);  
        /*显示client端的网络地址*/  
        //printf("receive from %s\n" , inet_ntoa( addr.sin_addr));  
        /*将字串返回给client端*/  
        //sendto(sockfd, udp_buf,len,0,(struct sockaddr *)&addr,addr_len);  
    }  

}

int JointWarn_udp_send(unsigned char *buf, int len)
{

    addr_len = sizeof(struct sockaddr_in);  
    /*建立socket*/  
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){  
        perror ("socket");  
        exit(1);  
    }  
    /*填写sockaddr_in 结构*/  
    bzero ( &addr, sizeof(addr) );  
    addr.sin_family=AF_INET;  
    addr.sin_port=htons(PORT);  
    addr.sin_addr.s_addr=inet_addr("112.124.115.184") ;  
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0){  
        perror("connect");  
        exit(1);  
    }  
    //while(1){ 
	printf("connected\n"); 
        bzero(udp_buf,sizeof(udp_buf)); 
	send(sockfd, buf, strlen(buf), 0); 
	printf("send %s\n", buf); 
        len = recv(sockfd, udp_buf, sizeof(udp_buf), 0); 
	printf("%s\n", udp_buf);	 
        //len = recvfrom(sockfd, udp_buf, sizeof(udp_buf), 0 , (struct sockaddr *)&addr ,&addr_len);  
        /*显示client端的网络地址*/  
        //printf("receive from %s\n" , inet_ntoa( addr.sin_addr));  
        /*将字串返回给client端*/  
        //sendto(sockfd, udp_buf,len,0,(struct sockaddr *)&addr,addr_len);  
    //}  
        //sendto(sockfd, buf, len, 0, (struct sockaddr *)&addr,addr_len);  
}

void JointWarn_network_init()
{

	pthread_t thrd,thrd2;
	int result;	
	
	result = pthread_create(&thrd, NULL, (void*)udp_listen_task, (void*)&gCounter);
        if (result)
        {
                 perror("pthread create fail");
                 exit(0);        
        }
	return 0;

}
