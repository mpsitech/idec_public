#!/bin/bash
# file make.sh
# make script for Idec combined daemon, release ideccmbd_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

make Ideccmbd.h.gch
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
	make -j4
	if [ $? -ne 0 ]; then
		exit
	fi
	make install
	cd ..
done

make -j4
if [ $? -ne 0 ]; then
	exit
fi

make install

rm Ideccmbd.h.gch

