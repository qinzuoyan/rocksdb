#!/bin/bash

if [ -z "$DSN_ROOT" ]; then
    echo "ERROR: DSN_ROOT not defined"
    exit -1
fi

if [ ! -d "$DSN_ROOT" ]; then
    echo "ERROR: DSN_ROOT directory not exist: ${DSN_ROOT}"
    exit -1
fi

DIR=deploy_rrdb
TAR=deploy_rrdb.tar.gz
MAC=deploy_machine
USER=work
DEPLOY=rrdb

cp $DSN_ROOT/bin/rrdb/rrdb $DIR
cp $DSN_ROOT/bin/rrdb/libdsn.core.so $DIR

