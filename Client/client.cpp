/* 
 * File:   client.cpp
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:34
 */

#include"client.h"
#include"protocol.h"

int main(int argc,char **argv)
{
                int fd;
                int serverip;
                int StorageServerPort = -1;
                char UserName[FILENAME]="";
                struct sockaddr_in serverinfo;
                serverinfo.sin_family=AF_INET;
                serverinfo.sin_port=htons(PORT);
                inet_pton(AF_INET,IP,&serverip);
                serverinfo.sin_addr.s_addr=serverip;
                fd=socket(AF_INET,SOCK_STREAM,0);

                if(fd<0)
                {
                            printf("socket error\n");
                            return -1;
                }

                connect(fd,(const struct sockaddr *)&serverinfo,sizeof(serverinfo));
                
                StorageServerPort = CheckUser(fd,UserName);//检查用户，获取存储节点端口号
                
                close(fd);
/************************************************************************/                
                serverinfo.sin_family=AF_INET;
                serverinfo.sin_port=htons(StorageServerPort);
                inet_pton(AF_INET,IP,&serverip);
                serverinfo.sin_addr.s_addr=serverip;
                fd=socket(AF_INET,SOCK_STREAM,0);

                if(fd<0)
                {
                            printf("socket error\n");
                            return -1;
                }

                connect(fd,(const struct sockaddr *)&serverinfo,sizeof(serverinfo));

                if(strcmp(argv[1],"download")==0)//判断是否要执行下载程序
                {
                            download(fd,UserName);
                            printf("compete\n");
                            return 1;
                }
                else if(strcmp(argv[1],"upload")==0)//判断是否执行上传程序
                {
                            uploading(fd,UserName);
                            printf("compete\n");
                            return 1;
                }
                else if(strcmp(argv[1],"delete")==0)
                {
                            deleteFile(fd,UserName);
                            printf("compete\n");
                            return 1;
                }
                else 
                {
                                printf("input error,please try again\n");
                                 return 1;
                }
                close(fd);
}

