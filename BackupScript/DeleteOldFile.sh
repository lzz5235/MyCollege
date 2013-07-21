#!/bin/sh
echo "begin deleting"  
#进入备份文件夹下   
cd /home/lzz/backup   
#取得最新文件及其时间   
lastestfile=`ls -t|head -n1`   
lastestdate=`ls -la $lastestfile --time-style '+%Y%m%d'| awk '{print$6}'`   
((lastestdate=lastestdate-1));   
while true  
do  
#取得最老的文件及其时间   
        oldfile=`ls -rt|head -n1`   
        olddate=`ls -la $oldfile --time-style '+%Y%m%d'| awk '{print$6}'`   
        if [ "$lastestdate" -eq "$olddate" ]; then   
#删除完毕，退出循环   
                exit 0   
        fi   
        if [ "$lastestdate" -gt "$olddate" ]; then   
                rm $oldfile   
        fi   
done  
