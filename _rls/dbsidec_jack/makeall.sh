#!/bin/bash
# file makeall.sh
# make script for Idec database access library, release dbsidec_jack
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

make DbsIdec.h.gch
if [ $? -ne 0 ]; then
	exit
fi

make -j16
if [ $? -ne 0 ]; then
	exit
fi

make install

