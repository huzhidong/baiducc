#!/bin/bash 
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

DIR="bgcc boost freeswitch json-c libcurl libxml2 mysql pcre opensips"

build()
{
    for d in ${DIR}; do
        if [ -d $d ]; then
	    ret=0;
            cd $d && if [ -f build.sh ]; then bash build.sh; ret=$?;  else python build.py; ret=$?; fi && cd ..;
	    if [ $ret == 0 ]; then
	    	echo "BUILD $d SUCCESS!";
            else
		echo "BUILD $d FAILED!";
		exit $ret;
	    fi
        fi
    done
}

clean()
{
    for d in ${DIR}; do
        if [ -d $d ]; then
            rm -fr $d/$d*;
            rm -fr $d/output;
            rm -fr $d/INSTALL;
        fi
    done
}

case "$1" in
    clean)
        clean
        ;;
    *)
        build
        ;;
esac

