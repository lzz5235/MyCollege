#include<stdio.h>
#include<stdlib.h>

#define FILENAME 1024
int backup(char *cmd_string,char *logfile)
{
	char cmd[FILENAME]="";
	sprintf(cmd, "%s 2&>> %s ",cmd_string,logfile);
	printf("%s",cmd);
	return system(cmd);
}

int main()
{
	char cmd[FILENAME]="/home/lzz/NetBeansProjects/BackupScript/backup.sh";
	char file[FILENAME]="log.txt";
	printf("\n%d\n",backup(cmd,file));
	return 0;
}
