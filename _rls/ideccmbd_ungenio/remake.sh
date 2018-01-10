#!/bin/bash
# file remake.sh
# re-make script for Idec combined daemon, release ideccmbd_ungenio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/Users/mpsitech/src
export set REPROOT=/Users/mpsitech/srcrep

cd $REPROOT/idec/_rls/ideccmbd_ungenio
./checkout.sh

cd $SRCROOT/ideccmbd

./make.sh "$@"

