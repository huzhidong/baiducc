#!/bin/bash

# Copyright 2002-2014 the original author or authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      CC/LICENSE
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ROOT_DIR=`pwd`

export PATH=$ROOT_DIR/sbin/:$PATH
export LD_LIBRARY_PATH=$ROOT_DIR/lib:$LD_LIBRARY_PATH
NAME=opensips
DAEMON=$ROOT_DIR/sbin/$NAME

CONF_FILE=$ROOT_DIR/etc/opensips/opensips.cfg

do_start()
{
    $DAEMON -f $CONF_FILE -m 4096
    RETVAL=$?
    if [ $RETVAL = 0 ]; then
        echo "success $DAEMON startup"
    else
        echo "failure $DAEMON startup"
    fi
    
    return $RETVAL
}

do_stop()
{
    killall $NAME 
    echo "success $DAEMON stop"
    return 0
}

case "$1" in
    
    start)
        do_start
        ;;
    stop)
        do_stop
        ;;
    restart)
        do_stop
        sleep 1
        do_start
        ;;
    *)
        echo "Usage: $0 {start|stop}"
        exit 2
        ;;
esac

exit $RETVAL

