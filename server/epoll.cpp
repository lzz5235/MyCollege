/* 
 * File:   epoll.cpp
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:51
 */

#include "def.h"
#include "server.h"
#include"protocol.h"



int main(int argc, char* argv[])
{
    int                     fdServer;
    int                     epfd;
    int                     ndfs;
    int                     listenfd, connfd, sockfd;
    socklen_t               clilen;
    struct  epoll_event     ev;
    struct  epoll_event     event[MAXEPOLLEVENT];
    struct  sockaddr_in     servaddr, cliaddr;

    epfd = epoll_create(MAXEPOLLEVENT);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //setnonblocking(listenfd);

    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET;

    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    
    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 20);
    
    //fdServer = initStorageServer(IP,4000);
    
 while(1)
    {
         ndfs = epoll_wait(epfd, event, 20, -1);
        
        for(int i = 0; i < ndfs; i++)
        {
            if(event[i].data.fd == listenfd)
              {
                    connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
                    setnonblocking(connfd);
                    if(connfd < 0)
                    {
                        printf("connfd < 0\n");
                        printf("%d\n",connfd);
                        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
                        return -1;
                    }
                    ev.data.fd = connfd;
                    ev.events = EPOLLIN | EPOLLET;

                    epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
                }
                else if(event[i].events & EPOLLIN)
                {

                        sockfd = event[i].data.fd;
                        if(sockfd < 0)
                            continue;
                        //CheckUser(sockfd);
                        //来自客户的r w
                        printf("---------------FromClientSockfd start----------------------\n");
                        OperateFromClient(sockfd,4000);
                        printf("---------------FromClientSockfd endd-------------------\n");
                        ev.data.fd = sockfd;
                        ev.events = EPOLLET;
                        //epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
                }
               /* else if(event[i].events & EPOLLOUT)
                {
                    sockfd = event[i].data.fd;

                    if(sockfd < 0)
                        continue;
                    //写到客户机 == 下载
                    writeToCli(sockfd);                

                    ev.data.fd = sockfd;
                    ev.events = EPOLLET | EPOLLIN;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
                 }*/
        }
    }
    close(epfd);
    close(listenfd);
}

