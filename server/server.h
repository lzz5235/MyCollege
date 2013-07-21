/* 
 * File:   server.h
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:50
 */

#ifndef SERVER_H
#define	SERVER_H

#define MAXSIZE 1024*4

int OperateFromClient(int clientfd,int Port);//来自客户的读写
int CheckUser(int fd);
int setnonblocking(int sockfd);

#endif	/* SERVER_H */

