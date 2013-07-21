/* 
 * File:   ServerStorage.h
 * Author: lzz
 *
 * Created on 2013年4月23日, 下午7:42
 */

#ifndef SERVERSTORAGE_H
#define	SERVERSTORAGE_H

#define MAXSIZE 1024*4


int OperateFromClient(int clientfd);//来自客户的读写
int setnonblocking(int sockfd);


#endif	/* SERVERSTORAGE_H */

