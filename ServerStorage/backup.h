/* 
 * File:   backup.h
 * Author: lzz
 *
 * Created on 2013年4月23日, 下午7:47
 */

#ifndef BACKUP_H
#define	BACKUP_H

void BackupAlarm(int sig);
int backup(char *cmd_string,char *logfile);

#define TIMER  60*60


#endif	/* BACKUP_H */

