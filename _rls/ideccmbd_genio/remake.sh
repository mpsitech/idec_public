#!/bin/bash
# file remake.sh
# re-make script for Idec combined daemon, release ideccmbd_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/home/mpsitech/src
export set REPROOT=/home/mpsitech/srcrep

cd $REPROOT/idec/_rls/ideccmbd_genio
./checkout.sh

cd $SRCROOT/ideccmbd

./make.sh "$@"

