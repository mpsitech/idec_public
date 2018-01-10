# file Makefile
# make file for Idec API library, release apiidec_genio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

LIBROOT = /home/mpsitech/lib

CPP = g++
CPPFLAGS = -std=c++11 -g -Wall -Os -pthread -fpic

STATLIB = ar
STATLIBFLAGS = rcs

DYNLIB = g++
DYNLIBFLAGS = -shared
DYNLIBEXT = so

INCPATH = -I/usr/include/libxml2 -I/usr/local/include

PCHS = ApiIdec.h.gch

OBJS = ApiIdec_blks.o ApiIdec.o
OBJS += VecIdecVDpch.o VecIdecVExpstate.o VecIdecVQrystate.o VecIdecVReqitmode.o
OBJS += IdecQFilList.o IdecQMis1NTour.o IdecQMisList.o IdecQMisRef1NFile.o IdecQTouList.o IdecQTouRef1NFile.o IdecQUsgAAccess.o IdecQUsgList.o IdecQUsgMNUser.o IdecQUsr1NSession.o IdecQUsrAAccess.o IdecQUsrList.o IdecQUsrMNUsergroup.o
OBJS += CrdIdecAd1.o CrdIdecFil.o CrdIdecIaq.o CrdIdecMis.o CrdIdecNav.o CrdIdecScf.o CrdIdecTou.o CrdIdecUsg.o CrdIdecUsr.o CrdIdecUtl.o DlgIdecFilExtrmed.o DlgIdecMisNew.o DlgIdecNavLoaini.o DlgIdecTouNew.o DlgIdecUtlFusion.o DlgIdecUtlPhi.o DlgIdecUtlQcdaln.o DlgIdecUtlQcdnuc.o DlgIdecUtlStereo.o DlgIdecUtlTheta.o PnlIdecAd1Control.o PnlIdecAd1Headbar.o PnlIdecFilDetail.o PnlIdecFilHeadbar.o PnlIdecFilList.o PnlIdecFilRec.o PnlIdecIaqHeadbar.o PnlIdecIaqLive.o PnlIdecIaqMech.o PnlIdecIaqQcdsp.o PnlIdecIaqScill.o PnlIdecMis1NTour.o PnlIdecMisDetail.o PnlIdecMisHeadbar.o PnlIdecMisList.o PnlIdecMisRec.o PnlIdecMisRef1NFile.o PnlIdecNavHeadbar.o PnlIdecNavMaint.o PnlIdecNavOpr.o PnlIdecNavPre.o PnlIdecScfConn.o PnlIdecScfHeadbar.o PnlIdecScfLwir.o PnlIdecScfMech.o PnlIdecScfOptics.o PnlIdecScfQcd.o PnlIdecScfRecord.o PnlIdecScfStatus.o PnlIdecScfTrigger.o PnlIdecTouDetail.o PnlIdecTouHeadbar.o PnlIdecTouList.o PnlIdecTouRec.o PnlIdecTouRef1NFile.o PnlIdecUsgAAccess.o PnlIdecUsgDetail.o PnlIdecUsgHeadbar.o PnlIdecUsgList.o PnlIdecUsgMNUser.o PnlIdecUsgRec.o PnlIdecUsr1NSession.o PnlIdecUsrAAccess.o PnlIdecUsrDetail.o PnlIdecUsrHeadbar.o PnlIdecUsrList.o PnlIdecUsrMNUsergroup.o PnlIdecUsrRec.o PnlIdecUtlHeadbar.o PnlIdecUtlSpiterm.o QryIdecFilList.o QryIdecMis1NTour.o QryIdecMisList.o QryIdecMisRef1NFile.o QryIdecTouList.o QryIdecTouRef1NFile.o QryIdecUsgAAccess.o QryIdecUsgList.o QryIdecUsgMNUser.o QryIdecUsr1NSession.o QryIdecUsrAAccess.o QryIdecUsrList.o QryIdecUsrMNUsergroup.o RootIdec.o SessIdec.o

LIB = libapiidec

.SUFFIXES:	.h .h.gch .cpp

.h.h.gch :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

.cpp.o :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

all:	$(LIB)

$(LIB):	$(PCHS) $(OBJS)
	$(STATLIB) $(STATLIBFLAGS) $(LIB).a $(OBJS)
	$(DYNLIB) $(DYNLIBFLAGS) $(OBJS) -o $(LIB).$(DYNLIBEXT)
	rm -f *.o

install:
	mv $(LIB).a $(LIBROOT)/
	mv $(LIB).$(DYNLIBEXT) $(LIBROOT)/

clean:
	rm -f *.gch
	rm -f *.o

