#!/bin/bash
# file checkout.sh
# checkout script for Idec daemon, release idecd_che
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/home/mpsitech/src
export set LIBROOT=/home/mpsitech/lib
export set BINROOT=/home/mpsitech/bin
export set REPROOT=/home/mpsitech/srcrep
export set CMBDSRCROOT=$REPROOT/idec/ideccmbd

mkdir $SRCROOT/idecd
mkdir $SRCROOT/idecd/IexIdec
mkdir $SRCROOT/idecd/VecIdec
mkdir $SRCROOT/idecd/CrdIdecNav
mkdir $SRCROOT/idecd/CrdIdecUsg
mkdir $SRCROOT/idecd/CrdIdecUsr
mkdir $SRCROOT/idecd/CrdIdecScf
mkdir $SRCROOT/idecd/CrdIdecUtl
mkdir $SRCROOT/idecd/CrdIdecMis
mkdir $SRCROOT/idecd/CrdIdecTou
mkdir $SRCROOT/idecd/CrdIdecIaq
mkdir $SRCROOT/idecd/CrdIdecAd1
mkdir $SRCROOT/idecd/CrdIdecFil

mkdir $LIBROOT/idecd

mkdir $BINROOT/idecd

cp make.sh $SRCROOT/idecd/
cp remake.sh $SRCROOT/idecd/

cp Makefile.inc $SRCROOT/idecd/
cp Makefile $SRCROOT/idecd/

cp ../../idecd/Idecd.h $SRCROOT/idecd/
cp ../../idecd/Idecd.cpp $SRCROOT/idecd/

cp ../../idecd/IdecdAppsrv.h $SRCROOT/idecd/
cp ../../idecd/IdecdAppsrv.cpp $SRCROOT/idecd/

cp ../../idecd/IdecdJobprc.h $SRCROOT/idecd/
cp ../../idecd/IdecdJobprc.cpp $SRCROOT/idecd/

cp ../../idecd/IdecdOpengconsrv.h $SRCROOT/idecd/
cp ../../idecd/IdecdOpengconsrv.cpp $SRCROOT/idecd/

cp ../../idecd/IdecdOpengcli.h $SRCROOT/idecd/
cp ../../idecd/IdecdOpengcli.cpp $SRCROOT/idecd/

cp ../../idecd/Idecd_exe.h $SRCROOT/idecd/
cp ../../idecd/Idecd_exe.cpp $SRCROOT/idecd/

cp $CMBDSRCROOT/Idec.h $SRCROOT/idecd/
cp $CMBDSRCROOT/Idec.cpp $SRCROOT/idecd/

cp $CMBDSRCROOT/Root*.h $SRCROOT/idecd/
cp $CMBDSRCROOT/Root*.cpp $SRCROOT/idecd/

cp $CMBDSRCROOT/Sess*.h $SRCROOT/idecd/
cp $CMBDSRCROOT/Sess*.cpp $SRCROOT/idecd/

cp $CMBDSRCROOT/gbl/*.h $SRCROOT/idecd/
cp $CMBDSRCROOT/gbl/*.cpp $SRCROOT/idecd/

cp Makefile_IexIdec $SRCROOT/idecd/IexIdec/Makefile

cp $CMBDSRCROOT/IexIdec/IexIdec*.h $SRCROOT/idecd/IexIdec/
cp $CMBDSRCROOT/IexIdec/IexIdec*.cpp $SRCROOT/idecd/IexIdec/

cp Makefile_VecIdec $SRCROOT/idecd/VecIdec/Makefile

cp $CMBDSRCROOT/VecIdec/Vec*.h $SRCROOT/idecd/VecIdec/
cp $CMBDSRCROOT/VecIdec/Vec*.cpp $SRCROOT/idecd/VecIdec/

cp Makefile_CrdIdecNav $SRCROOT/idecd/CrdIdecNav/Makefile

cp $CMBDSRCROOT/CrdIdecNav/*.h $SRCROOT/idecd/CrdIdecNav/
cp $CMBDSRCROOT/CrdIdecNav/*.cpp $SRCROOT/idecd/CrdIdecNav/

cp Makefile_CrdIdecUsg $SRCROOT/idecd/CrdIdecUsg/Makefile

cp $CMBDSRCROOT/CrdIdecUsg/*.h $SRCROOT/idecd/CrdIdecUsg/
cp $CMBDSRCROOT/CrdIdecUsg/*.cpp $SRCROOT/idecd/CrdIdecUsg/

cp Makefile_CrdIdecUsr $SRCROOT/idecd/CrdIdecUsr/Makefile

cp $CMBDSRCROOT/CrdIdecUsr/*.h $SRCROOT/idecd/CrdIdecUsr/
cp $CMBDSRCROOT/CrdIdecUsr/*.cpp $SRCROOT/idecd/CrdIdecUsr/

cp Makefile_CrdIdecScf $SRCROOT/idecd/CrdIdecScf/Makefile

cp $CMBDSRCROOT/CrdIdecScf/*.h $SRCROOT/idecd/CrdIdecScf/
cp $CMBDSRCROOT/CrdIdecScf/*.cpp $SRCROOT/idecd/CrdIdecScf/

cp Makefile_CrdIdecUtl $SRCROOT/idecd/CrdIdecUtl/Makefile

cp $CMBDSRCROOT/CrdIdecUtl/*.h $SRCROOT/idecd/CrdIdecUtl/
cp $CMBDSRCROOT/CrdIdecUtl/*.cpp $SRCROOT/idecd/CrdIdecUtl/

cp Makefile_CrdIdecMis $SRCROOT/idecd/CrdIdecMis/Makefile

cp $CMBDSRCROOT/CrdIdecMis/*.h $SRCROOT/idecd/CrdIdecMis/
cp $CMBDSRCROOT/CrdIdecMis/*.cpp $SRCROOT/idecd/CrdIdecMis/

cp Makefile_CrdIdecTou $SRCROOT/idecd/CrdIdecTou/Makefile

cp $CMBDSRCROOT/CrdIdecTou/*.h $SRCROOT/idecd/CrdIdecTou/
cp $CMBDSRCROOT/CrdIdecTou/*.cpp $SRCROOT/idecd/CrdIdecTou/

cp Makefile_CrdIdecIaq $SRCROOT/idecd/CrdIdecIaq/Makefile

cp $CMBDSRCROOT/CrdIdecIaq/*.h $SRCROOT/idecd/CrdIdecIaq/
cp $CMBDSRCROOT/CrdIdecIaq/*.cpp $SRCROOT/idecd/CrdIdecIaq/

cp Makefile_CrdIdecAd1 $SRCROOT/idecd/CrdIdecAd1/Makefile

cp $CMBDSRCROOT/CrdIdecAd1/*.h $SRCROOT/idecd/CrdIdecAd1/
cp $CMBDSRCROOT/CrdIdecAd1/*.cpp $SRCROOT/idecd/CrdIdecAd1/

cp Makefile_CrdIdecFil $SRCROOT/idecd/CrdIdecFil/Makefile

cp $CMBDSRCROOT/CrdIdecFil/*.h $SRCROOT/idecd/CrdIdecFil/
cp $CMBDSRCROOT/CrdIdecFil/*.cpp $SRCROOT/idecd/CrdIdecFil/

