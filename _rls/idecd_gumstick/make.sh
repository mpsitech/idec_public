#!/bin/bash
# file make.sh
# make script for Idec daemon, release idecd_gumstick
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

make Idecd.h.gch
if [ $? -ne 0 ]; then
	exit
fi

if [ "$1" = "all" ]; then
	subs=("IexIdec" "VecIdec" "CrdIdecNav" "CrdIdecUsg" "CrdIdecUsr" "CrdIdecScf" "CrdIdecUtl" "CrdIdecMis" "CrdIdecTou" "CrdIdecIaq" "CrdIdecAd1" "CrdIdecFil")
else
	subs=("$@")
fi

for var in "${subs[@]}"
do
	cd "$var"
	make -j2
	if [ $? -ne 0 ]; then
		exit
	fi
	make install
	cd ..
done

make -j2
if [ $? -ne 0 ]; then
	exit
fi

make install

rm Idecd.h.gch

