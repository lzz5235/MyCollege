/* 
 * File:   protocol.h
 * Author: lzz
 *
 * Created on 2013年4月1日, 下午12:49
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H


typedef char int8;
typedef int  int32;


#if  __DWORDSIZE == 64
typedef long int   int64;
#else
typedef long long int int64;
#endif

#pragma pack(1)
typedef struct
{
            int8  cmd;
            int32 Port;
            int8 IPAddr[FILENAME];
            int8 UserName[FILENAME];
            int32 headLength;
            int8  FileName[FILENAME];
            int64 offset;
            int64 reqLength;
            int8  Data[MAXSIZE];	
            int8  isComplete;
}Msg, *pMsg;
#pragma pack()


#endif	/* PROTOCOL_H */

