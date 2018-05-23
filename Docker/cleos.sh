#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./cleot.sh
# Run single cmd:  sudo ./cleot.sh <cleot paramers>

PREFIX="docker exec docker_nodeotd_1 cleot"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "cleot " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX $@
fi
