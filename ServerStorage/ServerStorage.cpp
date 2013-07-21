/* 
 * File:   ServerStorage.cpp
 * Author: lzz
 *
 * Created on 2013年4月23日, 下午7:51
 */


#include"ServerStorage.h"
#include"def.h"
#include"protocol.h"


int OperateFromClient(int sockfd)
{
    int                   n,count;
    Msg                 *serverinfo;
    int                   fd;
    char                 AbsolutefileName[FILENAME]="";
    serverinfo = (Msg *)malloc(sizeof(Msg)); 
    memset(serverinfo, 0, sizeof(Msg));

    while( (n = read(sockfd, serverinfo, sizeof(Msg))) > 0)
    {
        bzero(AbsolutefileName,sizeof(AbsolutefileName));
        strcpy(AbsolutefileName,"/home/lzz/User/");
        strcat(AbsolutefileName,serverinfo->UserName);
        strcat(AbsolutefileName,"/");
        if(serverinfo->cmd=='c'&&access(AbsolutefileName,F_OK)==-1)
        {
            //printf("fileName is %s \n",AbsolutefileName);
            if(mkdir(AbsolutefileName,0777))
            {
                printf("Create file Failed!\n");
                continue;
            }
            printf("Create file success!\n");
        }
        else if(serverinfo->cmd=='r'||serverinfo->cmd=='w'||serverinfo->cmd=='d')
        {
                   // printf("fileName is %s \n",serverinfo->FileName);
                    strcat(AbsolutefileName,serverinfo->FileName);    
                    //printf("AbsolutefileName is %s \n",AbsolutefileName);
                    if(access(AbsolutefileName, F_OK) == -1)//不存在这个文件
                    {
                        fd = open(AbsolutefileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

                        if(fd == -1)
                        {
                            printf("open file failed\n");
                            continue;
                        }
                    }
                    else
                    {
                        fd = open(AbsolutefileName, O_RDWR);
                        if(fd == -1)
                        {
                            printf("open file failed\n");
                                continue;
                        }
                    } 
                   
                    switch(serverinfo->cmd)
                    {
                        case 'r':
                            while(1)
                            {
                                        bzero(serverinfo->Data,MAXSIZE*sizeof(char));
                                        count=read(fd,serverinfo->Data,MAXSIZE*sizeof(char));//从已打开的文件中读取
                                        if(count==0)
                                                    break;
                                        serverinfo->reqLength = count;
                                        printf("send %d \n",count);
                                        
                                        serverinfo->isComplete ='n';
                                        if(count<MAXSIZE)
                                            serverinfo->isComplete ='y';
                                        strcpy(serverinfo->IPAddr,IP);

                                        write(sockfd,serverinfo,sizeof(Msg));//把从文件中读取到的东西传给客户端
                                        serverinfo->offset +=count;
                                        printf("send offset %d \n",serverinfo->offset);
                            }
                            break;
                        case 'w':
                            lseek(fd, 0, SEEK_END);
                            printf("this is in write server ,the start is %d,and the length is %d \n",serverinfo->offset,serverinfo->reqLength);
                            if(serverinfo->reqLength==0)     
                                            return -2;
                            write(fd, serverinfo->Data,serverinfo->reqLength);
                            bzero(serverinfo,sizeof(Msg));             
                            break;
                        case 'd':
                            count = remove(AbsolutefileName);
                            printf("count:%d\n",count);
                            serverinfo->isComplete = 'y';
                            if(count!=0)
                                serverinfo->isComplete = 'n';
                            strcpy(serverinfo->IPAddr,IP);
                            write(sockfd,serverinfo,sizeof(Msg));//把从文件状态信息传给客户端
                            break;
                    }
                    close(fd);
                    memset(serverinfo, 0, sizeof(Msg));            
        }
        else
        {
            printf("Msg CMD error!\n");
            continue;
        }
    }
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



