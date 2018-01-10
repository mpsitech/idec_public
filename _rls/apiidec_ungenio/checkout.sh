#!/bin/bash
# file checkout.sh
# checkout script for Idec API library, release apiidec_ungenio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/Users/mpsitech/src

mkdir $SRCROOT/apiidec

cp makeall.sh $SRCROOT/apiidec/

cp Makefile $SRCROOT/apiidec/

cp ../../apiidec/*.h $SRCROOT/apiidec/
cp ../../apiidec/*.cpp $SRCROOT/apiidec/

