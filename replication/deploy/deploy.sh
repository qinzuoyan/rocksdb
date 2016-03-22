#!/bin/bash

DIR=deploy_rrdb
TAR=deploy_rrdb.tar.gz
MAC=deploy_machine
USER=work
DEPLOY=rrdb

files=`ls $DIR`
rm -rf $TAR
tar cfz $TAR $DIR
for mac in `cat $MAC | awk '{print $1}' | sort -u`
do
    echo "deploy to $mac ..."
    ssh $USER@$mac "rm -rf $TAR $DEPLOY"
    scp $TAR $USER@$mac:
    ssh $USER@$mac "mkdir -p $DEPLOY; tar xfz $TAR -C $DEPLOY"
    for app in `cat $MAC | grep $mac | awk '{print $2}' | sort -u`
    do
        ssh $USER@$mac "cp -r $DEPLOY/$DIR $DEPLOY/$app"
    done
done

