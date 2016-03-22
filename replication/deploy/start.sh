#!/bin/bash

DIR=deploy_rrdb
TAR=deploy_rrdb.tar.gz
MAC=deploy_machine
USER=work
DEPLOY=rrdb

lines=""
if [ $# -gt 0 ]; then
    if [ $# -ne 2 ]; then
        echo "ERROR: $0 <mac> <app>"
        exit -1
    fi
    mac=$1
    app=$2
    lines="$mac:$app"
else
    while read line
    do
        mac=`echo $line | awk '{print $1}'`
        app=`echo $line | awk '{print $2}'`
        lines="$lines $mac:$app"
    done <$MAC
fi

for line in $lines
do
    mac=`echo $line | awk -F: '{print $1}'`
    app=`echo $line | awk -F: '{print $2}'`
    echo "start $app on $mac ..."
    #ssh $USER@$mac 'cd '$DEPLOY'/'$app'; nohup sh -c "((./rrdb config.ini -app_list '$app' >out 2>err)&; echo $! >PID)"'
    ssh $USER@$mac 'cd '$DEPLOY'/'$app'; ./start.sh '$app
done

