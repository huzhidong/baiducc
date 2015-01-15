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

DIST_VERSION="opensips-1.6.4-2-tls"
PWD=`pwd`
PREFIX=$PWD/output

file="$DIST_VERSION"_src.tar.gz


echo "prepare build..."

echo "$DIST_VERSION"

if [ -z "$DIST_VERSION" ]; then
    echo "errno: no DIST_VERSION info"
    exit 1
fi

DIRNAME=$DIST_VERSION
if [ -d "$DIRNAME" ]; then  
    rm -rf $DIRNAME
fi

if [ -d "$PREFIX" ]; then
    rm -fr $PREFIX
fi

if [ ! -f $file ]; then
    wget http://opensips.org/pub/opensips/1.6.4/src/${file}
fi

if [ ! -f "$file" ]; then    
    echo "error: no $file"  
    exit 1
fi

echo "tar xzf $file..."
tar xzf $file

if [ ! -d "$DIRNAME" ]; then  
    echo "error: no $DIRNAME"   
    exit 1
fi
    

cd $DIRNAME
patch -p1 < ../patch/db_mysql.patch
patch -p1 < ../patch/dialplan.patch

echo "begin to build..."

export CROSS_COMPILE=true
export include_modules="db_mysql dialplan"
make prefix=$PREFIX all 
export include_modules="db_mysql dialplan"
make prefix=$PREFIX install 

if [ ! -f "$PREFIX/sbin/opensips" ]; then
    echo "error: no opensips"
    exit 1
fi

cp $PREFIX/../opensips.sh $PREFIX/

cd $PREFIX
tar cvzf $DIST_VERSION.tgz *
find -type d -maxdepth 1 | grep "\./" | xargs rm -fr
rm -f opensips.sh

if [ ! -f "$PREFIX/$DIST_VERSION.tgz" ]; then
    echo "error: no $PREFIX/$DIST_VERSION.tgz"
    exit 1
fi

echo "build binary done success"
