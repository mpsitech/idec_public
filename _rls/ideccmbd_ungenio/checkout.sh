#!/bin/bash
# file checkout.sh
# checkout script for Idec combined daemon, release ideccmbd_ungenio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

export set SRCROOT=/Users/mpsitech/src
export set LIBROOT=/Users/mpsitech/lib
export set BINROOT=/Users/mpsitech/bin

mkdir $SRCROOT/ideccmbd
mkdir $SRCROOT/ideccmbd/IexIdec
mkdir $SRCROOT/ideccmbd/VecIdec
mkdir $SRCROOT/ideccmbd/CrdIdecNav
mkdir $SRCROOT/ideccmbd/CrdIdecUsg
mkdir $SRCROOT/ideccmbd/CrdIdecUsr
mkdir $SRCROOT/ideccmbd/CrdIdecScf
mkdir $SRCROOT/ideccmbd/CrdIdecUtl
mkdir $SRCROOT/ideccmbd/CrdIdecMis
mkdir $SRCROOT/ideccmbd/CrdIdecTou
mkdir $SRCROOT/ideccmbd/CrdIdecIaq
mkdir $SRCROOT/ideccmbd/CrdIdecAd1
mkdir $SRCROOT/ideccmbd/CrdIdecFil

mkdir $LIBROOT/ideccmbd

mkdir $BINROOT/ideccmbd

cp make.sh $SRCROOT/ideccmbd/
cp remake.sh $SRCROOT/ideccmbd/

cp Makefile.inc $SRCROOT/ideccmbd/
cp Makefile $SRCROOT/ideccmbd/

cp ../../ideccmbd/Ideccmbd.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/Ideccmbd.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/IdeccmbdAppsrv.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/IdeccmbdAppsrv.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/IdeccmbdJobprc.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/IdeccmbdJobprc.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/IdeccmbdOpprc.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/IdeccmbdOpprc.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/Ideccmbd_exe.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/Ideccmbd_exe.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/Idec.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/Idec.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/Root*.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/Root*.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/Sess*.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/Sess*.cpp $SRCROOT/ideccmbd/

cp ../../ideccmbd/gbl/*.h $SRCROOT/ideccmbd/
cp ../../ideccmbd/gbl/*.cpp $SRCROOT/ideccmbd/

cp Makefile_IexIdec $SRCROOT/ideccmbd/IexIdec/Makefile

cp ../../ideccmbd/IexIdec/IexIdec*.h $SRCROOT/ideccmbd/IexIdec/
cp ../../ideccmbd/IexIdec/IexIdec*.cpp $SRCROOT/ideccmbd/IexIdec/

cp Makefile_VecIdec $SRCROOT/ideccmbd/VecIdec/Makefile

cp ../../ideccmbd/VecIdec/Vec*.h $SRCROOT/ideccmbd/VecIdec/
cp ../../ideccmbd/VecIdec/Vec*.cpp $SRCROOT/ideccmbd/VecIdec/

cp Makefile_CrdIdecNav $SRCROOT/ideccmbd/CrdIdecNav/Makefile

cp ../../ideccmbd/CrdIdecNav/*.h $SRCROOT/ideccmbd/CrdIdecNav/
cp ../../ideccmbd/CrdIdecNav/*.cpp $SRCROOT/ideccmbd/CrdIdecNav/

cp Makefile_CrdIdecUsg $SRCROOT/ideccmbd/CrdIdecUsg/Makefile

cp ../../ideccmbd/CrdIdecUsg/*.h $SRCROOT/ideccmbd/CrdIdecUsg/
cp ../../ideccmbd/CrdIdecUsg/*.cpp $SRCROOT/ideccmbd/CrdIdecUsg/

cp Makefile_CrdIdecUsr $SRCROOT/ideccmbd/CrdIdecUsr/Makefile

cp ../../ideccmbd/CrdIdecUsr/*.h $SRCROOT/ideccmbd/CrdIdecUsr/
cp ../../ideccmbd/CrdIdecUsr/*.cpp $SRCROOT/ideccmbd/CrdIdecUsr/

cp Makefile_CrdIdecScf $SRCROOT/ideccmbd/CrdIdecScf/Makefile

cp ../../ideccmbd/CrdIdecScf/*.h $SRCROOT/ideccmbd/CrdIdecScf/
cp ../../ideccmbd/CrdIdecScf/*.cpp $SRCROOT/ideccmbd/CrdIdecScf/

cp Makefile_CrdIdecUtl $SRCROOT/ideccmbd/CrdIdecUtl/Makefile

cp ../../ideccmbd/CrdIdecUtl/*.h $SRCROOT/ideccmbd/CrdIdecUtl/
cp ../../ideccmbd/CrdIdecUtl/*.cpp $SRCROOT/ideccmbd/CrdIdecUtl/

cp Makefile_CrdIdecMis $SRCROOT/ideccmbd/CrdIdecMis/Makefile

cp ../../ideccmbd/CrdIdecMis/*.h $SRCROOT/ideccmbd/CrdIdecMis/
cp ../../ideccmbd/CrdIdecMis/*.cpp $SRCROOT/ideccmbd/CrdIdecMis/

cp Makefile_CrdIdecTou $SRCROOT/ideccmbd/CrdIdecTou/Makefile

cp ../../ideccmbd/CrdIdecTou/*.h $SRCROOT/ideccmbd/CrdIdecTou/
cp ../../ideccmbd/CrdIdecTou/*.cpp $SRCROOT/ideccmbd/CrdIdecTou/

cp Makefile_CrdIdecIaq $SRCROOT/ideccmbd/CrdIdecIaq/Makefile

cp ../../ideccmbd/CrdIdecIaq/*.h $SRCROOT/ideccmbd/CrdIdecIaq/
cp ../../ideccmbd/CrdIdecIaq/*.cpp $SRCROOT/ideccmbd/CrdIdecIaq/

cp Makefile_CrdIdecAd1 $SRCROOT/ideccmbd/CrdIdecAd1/Makefile

cp ../../ideccmbd/CrdIdecAd1/*.h $SRCROOT/ideccmbd/CrdIdecAd1/
cp ../../ideccmbd/CrdIdecAd1/*.cpp $SRCROOT/ideccmbd/CrdIdecAd1/

cp Makefile_CrdIdecFil $SRCROOT/ideccmbd/CrdIdecFil/Makefile

cp ../../ideccmbd/CrdIdecFil/*.h $SRCROOT/ideccmbd/CrdIdecFil/
cp ../../ideccmbd/CrdIdecFil/*.cpp $SRCROOT/ideccmbd/CrdIdecFil/

