/* 
 * File:   server.cpp
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:52
 */

#include"server.h"
#include"def.h"
#include"protocol.h"


int OperateFromClient(int sockfd,int Port)
{
    int                   n;
    Msg                 *serverinfo;
    serverinfo = (Msg *)malloc(sizeof(Msg)); 
    memset(serverinfo, 0, sizeof(Msg));
    
    int fdStorage;
    int serverip;
    struct sockaddr_in serverStorage;
    serverStorage.sin_family=AF_INET;
    serverStorage.sin_port=htons(Port);
    inet_pton(AF_INET,IP,&serverip);
    serverStorage.sin_addr.s_addr=serverip;
    fdStorage=socket(AF_INET,SOCK_STREAM,0);

    if(fdStorage<0)
    {
            printf("fdStorage socket error\n");
            return -1;
    }

    connect(fdStorage,(const struct sockaddr *)&serverStorage,sizeof(serverStorage));
    
    while( (n = read(sockfd, serverinfo, sizeof(Msg))) > 0)
    {
        if(serverinfo->cmd=='c'||serverinfo->cmd=='w'||serverinfo->cmd=='d'||serverinfo->cmd=='r')
        {
            printf("Msg CMD sends Success! \n");
            write(fdStorage, serverinfo, sizeof(Msg));            
        }
        else
        {
            printf("Msg CMD error!\n");
            continue;
        }
        serverinfo->Port = 4000;//port
        serverinfo->cmd = 'p';
        strcpy( serverinfo->IPAddr,IP);
        write(sockfd,serverinfo,sizeof(Msg));
        memset(serverinfo, 0, sizeof(Msg));        
    }
    memset(serverinfo, 0, sizeof(Msg));
    return 0;
}
int setnonblocking(int sockfd)
{
        int flags;
        flags = fcntl(sockfd, F_GETFL, 0);

        if(flags < 0)
            return -1;
        flags |= O_NONBLOCK;
        if(fcntl(sockfd, F_SETFL, flags) < 0)
            return -1;

        return 0;
}

