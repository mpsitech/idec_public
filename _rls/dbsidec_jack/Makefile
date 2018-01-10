# file Makefile
# make file for Idec database access library, release dbsidec_jack
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

LIBROOT = /home/mpsitech/lib

CPP = g++
CPPFLAGS = -std=c++11 -g -Wall -Os -pthread

STATLIB = ar
STATLIBFLAGS = rcs

INCPATH = -I/usr/include -I/usr/include/libxml2 -I/usr/local/include

PCHS = DbsIdec.h.gch

OBJS = DbsIdec.o
OBJS += IdecAccRMUserUniversal.o IdecAMPersonDetail.o IdecAMUserAccess.o IdecAMUsergroupAccess.o IdecAVControlPar.o IdecAVKeylistKey.o IdecAVValuelistVal.o IdecCFile.o IdecHistRMUserUniversal.o IdecJAVKeylistKey.o IdecJMPersonLastname.o IdecJMUserState.o IdecMFile.o IdecMMission.o IdecMPerson.o IdecMSession.o IdecMTour.o IdecMUser.o IdecMUsergroup.o IdecRMUsergroupUniversal.o IdecRMUserMUsergroup.o
OBJS += IdecQFilList.o IdecQMis1NTour.o IdecQMisList.o IdecQMisRef1NFile.o IdecQPreselect.o IdecQSelect.o IdecQTouList.o IdecQTouRef1NFile.o IdecQUsgAAccess.o IdecQUsgList.o IdecQUsgMNUser.o IdecQUsr1NSession.o IdecQUsrAAccess.o IdecQUsrList.o IdecQUsrMNUsergroup.o

LIB = libdbsidec

.SUFFIXES:	.h .h.gch .cpp

.h.h.gch :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

.cpp.o :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

all:	$(LIB)

$(LIB):	$(PCHS) $(OBJS)
	$(STATLIB) $(STATLIBFLAGS) $(LIB).a $(OBJS)
	rm -f *.o

install:
	mv $(LIB).a $(LIBROOT)/

clean:
	rm -f *.gch
	rm -f *.o

