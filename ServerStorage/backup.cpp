/* 
 * File:   backup.cpp
 * Author: lzz
 *
 * Created on 2013年4月23日, 下午7:46
 */

#include "def.h"
#include "backup.h"

void BackupAlarm(int sig)
{
    char cmd[FILENAME]="/home/lzz/NetBeansProjects/BackupScript/backup.sh";
    char file[FILENAME]="/home/lzz/NetBeansProjects/BackupScript/log.txt";
    if(backup(cmd,file)==0)
        printf("Saving Success!\n");
    else
        printf("Saving Failed!\n");
    alarm(TIMER);
}
int backup(char *cmd_string,char *logfile)
{
	char cmd[PATHNAME]="";
	sprintf(cmd, "%s 2&>> %s ",cmd_string,logfile);
	printf("%s",cmd);
	return system(cmd);
}

