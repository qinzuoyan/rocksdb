#!/bin/bash

DIR=deploy_rrdb
TAR=deploy_rrdb.tar.gz
MAC=deploy_machine
USER=work
DEPLOY=rrdb

for mac in `cat $MAC | awk '{print $1}' | sort -u`
do
    echo "stop on $mac ..."
    ssh $USER@$mac 'killall rrdb &>/dev/null'
done

