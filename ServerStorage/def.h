/* 
 * File:   def.h
 * Author: lzz
 *
 * Created on 2013年4月23日, 下午7:40
 */

#ifndef DEF_H
#define	DEF_H

#include<sys/epoll.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
 #include <sys/stat.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<fcntl.h>
#include<signal.h>

#define PORT 4000

#define IP "localhost"

#define PATHNAME 1024

#define FILENAME 255

#define MAXEPOLLEVENT  50


#endif	/* DEF_H */

