/* 
 * File:   function.cpp
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:34
 */

#include<stdio.h>
#include"client.h"
#include"protocol.h"

int GetFileName(char *buf,char *filename)
{
    int k=0,j=0,m=0;
              for(int i=0;buf[i]!='\0';i++)
                    if(buf[i]=='/')
                            j++;
	for(int i=0;buf[i]!='\0';i++)
	{
		if(buf[i]=='/')
			k++;
		if(k==j)
		{
			filename[m]=buf[i+1];
			m++;
		}
	}
              return 0;
}
int CheckUser(int fd,char *UserName)
{
        int   n;
        Msg *buffer = (Msg *)malloc(sizeof(Msg));
        bzero(buffer,sizeof(Msg));
        int Port=0;

        printf("＊＊＊＊请输入帐号＊＊＊＊\n");
        gets(UserName);
        strcpy(buffer->UserName,UserName);
        buffer->cmd='c';
        buffer->isComplete='n';
        write(fd,buffer,sizeof(Msg));//命令传送给服务器
        bzero(buffer,sizeof(Msg));
        if((n = read(fd, buffer, sizeof(Msg))) > 0&&buffer->cmd=='p')
        {
            Port =  buffer->Port;
            bzero(buffer,sizeof(Msg));
            return Port;
        }
        return 0;
}
int download(int fd,char *UserName)//下载程序
{
                int ret;
                int n=0;
                char buf[FILENAME]="";
                char fileName[FILENAME]="";
                Msg *buffer = (Msg *)malloc(sizeof(Msg));
                bzero(buffer,sizeof(Msg));
                printf("＊＊＊＊输入你想要下载的文件＊＊＊＊\n");
                gets(buf);
                if(strcmp(buf,"")!=0)
                {
                            strcpy(buffer->FileName,buf);
                            strcpy(buffer->UserName,UserName);
                            buffer->cmd='r';
                            buffer->offset = 0;
                            buffer->headLength = sizeof(Msg);
                            write(fd,buffer,sizeof(Msg));//命令传送给服务器
                            
                            strcpy(fileName,buffer->FileName);
                            printf("fileName is %s \n",fileName);
                            bzero(buffer,sizeof(Msg));
                            
                            if(access(fileName, F_OK) == -1)//不存在这个文件
                            {
                                    ret = open(fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

                                     if(fd == -1)
                                    {
                                            printf("open file failed\n");
                                    }
                            }
                            else
                            {
                                    ret = open(fileName, O_RDWR);
                            } 

                            while((n = read(fd, buffer, sizeof(Msg))) > 0)
                            {
                                    if(n != sizeof(Msg))
                                    {
                                            printf("read length is not head length\n");
                                            continue;
                                    }
                                    lseek(ret, 0 , SEEK_END);
                                    printf("this is in read server ,the start is %d,and the length is %d \n",buffer->offset,buffer->reqLength);
                                    if(buffer->reqLength ==0)     
                                             return -1;
                                    write(ret, buffer->Data,buffer->reqLength);
                                    bzero(buffer,sizeof(Msg));           
                             }
                }
}
int uploading(int fd,char *UserName)//上传程序
{
	int64 ret;
	int64 count=0;
	char buf[MAXSIZE]="";
	char filename[FILENAME]="";

	Msg *buffer = (Msg *)malloc(sizeof(Msg));
	bzero(buffer,sizeof(Msg));
	
	buffer->cmd='w';
	buffer->headLength = sizeof(Msg);
		
	bzero(buf,sizeof(buf));
	printf("＊＊＊＊输入你想要上传文件的绝对路径＊＊＊＊\n");
	gets(buf);
	// /home/lzz/Downloads/1.mp3
	GetFileName(buf,filename);
	strcpy(buffer->FileName,filename);
              strcpy(buffer->UserName,UserName);
              strcpy( buffer->IPAddr,IP);
              printf("filename:%s\n",buffer->FileName);
              printf("UserName:%s\n",buffer->UserName);
              
	buffer->offset =0;	

	ret=open(buf,O_RDONLY);//打开所要上传的文件
	if(ret<0)
	{
		printf("open file error\n");
		return -1;
	}
	while(1)
	{
		bzero(buffer->Data,MAXSIZE*sizeof(char));
		count=read(ret,buffer->Data,MAXSIZE*sizeof(char));//从已打开的文件中读取
		if(count==0)
			return -2;
                           buffer->Port = -1;
		buffer->reqLength = count;
                                printf("send %d \n",count);
                           buffer->isComplete ='n';    
		if(count<MAXSIZE)
			buffer->isComplete ='y';		
		write(fd,buffer,sizeof(Msg));//把从文件中读取到的东西传给服务器
		buffer->offset +=count;
                           printf("send offset %d \n",buffer->offset);
	}
}
int deleteFile(int fd,char *UserName)
{
                int  n=0;
                char buf[FILENAME]="";
                Msg *buffer = (Msg *)malloc(sizeof(Msg));
                bzero(buffer,sizeof(Msg));
                printf("＊＊＊＊输入你想要删除的文件＊＊＊＊\n");
                gets(buf);
                if(strcmp(buf,"")!=0)
                {
                            strcpy(buffer->FileName,buf);
                            strcpy(buffer->UserName,UserName);
                            buffer->Port = -1;
                            buffer->cmd='d';
                            buffer->offset = 0;
                            buffer->headLength = sizeof(Msg);
                            write(fd,buffer,sizeof(Msg));//命令传送给服务器
                            bzero(buffer,sizeof(Msg));
                }
                if((n = read(fd, buffer, sizeof(Msg))) > 0)
                {
                                    if(n != sizeof(Msg))
                                    {
                                            printf("read length is not head length\n");
                                            return -3;
                                    }
                                    if(buffer->isComplete=='y')
                                        printf("delete success!\n");
                                    else
                                        printf("delete failture!\n");
                }             
    
}

