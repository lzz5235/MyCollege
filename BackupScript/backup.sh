
floderName1="/home/lzz/User"
backupName1="$floderName1-`date   +%Y%m%d%H%M`.tar.bz2" 
backupPath1="/home/lzz/backup/"
tar -cjvf $backupName1   $floderName1
mv $backupName1 $backupPath1
