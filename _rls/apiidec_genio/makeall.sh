#!/bin/bash
# file makeall.sh
# make script for Idec API library, release apiidec_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

make ApiIdec.h.gch
if [ $? -ne 0 ]; then
	exit
fi

make -j4
if [ $? -ne 0 ]; then
	exit
fi

make install

