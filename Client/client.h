/* 
 * File:   client.h
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:33
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

// /home/lzz/Downloads/1.mp3
//#define PORT 4000

#define PORT 10022
#define IP "localhost"

int download(int fd,char *UserName);
int uploading(int fd,char *UserName);
int deleteFile(int fd,char *UserName);
int CheckUser(int fd,char *buf);
int GetFileName(char *buf,char *filename);

#endif	/* CLIENT_H */

