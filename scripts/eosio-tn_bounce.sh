#!/bin/bash
#
# eotio-tn_bounce is used to restart a node that is acting badly or is down.
# usage: eotio-tn_bounce.sh [arglist]
# arglist will be passed to the node's command line. First with no modifiers
# then with --replay and then a third time with --resync
#
# the data directory and log file are set by this script. Do not pass them on
# the command line.
#
# in most cases, simply running ./eotio-tn_bounce.sh is sufficient.
#

pushd $eotIO_HOME

if [ ! -f programs/nodeot/nodeot ]; then
    echo unable to locate binary for nodeot
    exit 1
fi

config_base=etc/eotio/node_
if [ -z "$eotIO_NODE" ]; then
    DD=`ls -d ${config_base}[012]?`
    ddcount=`echo $DD | wc -w`
    if [ $ddcount -ne 1 ]; then
        echo $HOSTNAME has $ddcount config directories, bounce not possible. Set environment variable
        echo eotIO_NODE to the 2-digit node id number to specify which node to bounce. For example:
        echo eotIO_NODE=06 $0 \<options\>
        cd -
        exit 1
    fi
    OFS=$((${#DD}-2))
    export eotIO_NODE=${DD:$OFS}
else
    DD=${config_base}$eotIO_NODE
    if [ ! \( -d $DD \) ]; then
        echo no directory named $PWD/$DD
        cd -
        exit 1
    fi
fi

bash $eotIO_HOME/scripts/eotio-tn_down.sh
bash $eotIO_HOME/scripts/eotio-tn_up.sh $*
