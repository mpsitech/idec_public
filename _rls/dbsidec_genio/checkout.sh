#!/bin/bash
# file checkout.sh
# checkout script for Idec database access library, release dbsidec_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/home/mpsitech/src

mkdir $SRCROOT/dbsidec

cp makeall.sh $SRCROOT/dbsidec/

cp Makefile $SRCROOT/dbsidec/

cp ../../dbsidec/DbsIdec.h $SRCROOT/dbsidec/
cp ../../dbsidec/DbsIdec_vecs.cpp $SRCROOT/dbsidec/
cp ../../dbsidec/DbsIdec.cpp $SRCROOT/dbsidec/

cp ../../dbsidec/Idec*.h $SRCROOT/dbsidec/
cp ../../dbsidec/Idec*.cpp $SRCROOT/dbsidec/

