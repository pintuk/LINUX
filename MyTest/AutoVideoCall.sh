#!/bin/sh

number=$1
counter=0

echo "Start Time : "`date`
while [ 1 ]
do

starttime=`date +%d/%m/%Y/%T`
echo "**********************    START ($starttime)   *************************"
	/usr/bin/vtmain MO $number -1 -1 &
	sleep 1m
	echo "Done...sleeping......."
        vtuipid=`ps -ae | grep -i vtui | awk '{print $1}`
	if [ "$vtuipid" = "" ]
	then
	continue
	fi 
	echo "killing.....VTUI......"
	kill -9 $vtuipid
        let counter=$counter+1
	endtime=`date +%d/%m/%Y/%T`
echo "**********************    DONE ($endtime)      **************************"
echo "**********************    COUNTER = $counter   **************************"
echo
echo
echo
echo
echo
echo
        sleep 1m
done


