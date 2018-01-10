#!/bin/bash
# file makeall.sh
# make script for Idec API library, release apiidec_jack
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

make ApiIdec.h.gch
if [ $? -ne 0 ]; then
	exit
fi

make -j16
if [ $? -ne 0 ]; then
	exit
fi

make install

