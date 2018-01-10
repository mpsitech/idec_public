#!/bin/bash
# file remake.sh
# re-make script for Idec daemon, release idecd_ungenio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/Users/mpsitech/src
export set REPROOT=/Users/mpsitech/srcrep

cd $REPROOT/idec/_rls/idecd_ungenio
./checkout.sh

cd $SRCROOT/idecd

./make.sh "$@"

