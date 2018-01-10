#!/bin/bash
# file remake.sh
# re-make script for Idec daemon, release idecd_gumstick
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/home/mpsitech/src
export set REPROOT=/home/mpsitech/srcrep

cd $REPROOT/idec/_rls/idecd_gumstick
./checkout.sh

cd $SRCROOT/idecd

./make.sh "$@"

