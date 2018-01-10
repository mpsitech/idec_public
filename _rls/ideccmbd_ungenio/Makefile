# file Makefile
# make file for Idec combined daemon, release ideccmbd_ungenio
# author Alexander Wirthmueller
# date created: 30 Dec 2017
# modified: 30 Dec 2017

include Makefile.inc

CPP = g++
CPPFLAGS = -std=c++11 -g -Wall -Os -pthread -DIDECCMBD

LINK = g++
LINKFLAGS =

INCPATH = -I$(SRCROOT)/dbsidec -I$(SRCROOT)/ideccmbd/VecIdec -I$(SRCROOT)/ideccmbd/IexIdec -I$(SRCROOT)/ideccmbd
INCPATH += -I$(SRCROOT)/ideccmbd/CrdIdecNav -I$(SRCROOT)/ideccmbd/CrdIdecUsg -I$(SRCROOT)/ideccmbd/CrdIdecUsr -I$(SRCROOT)/ideccmbd/CrdIdecScf -I$(SRCROOT)/ideccmbd/CrdIdecUtl -I$(SRCROOT)/ideccmbd/CrdIdecMis -I$(SRCROOT)/ideccmbd/CrdIdecTou -I$(SRCROOT)/ideccmbd/CrdIdecIaq -I$(SRCROOT)/ideccmbd/CrdIdecAd1 -I$(SRCROOT)/ideccmbd/CrdIdecFil
INCPATH += -I/Library/PostgreSQL/9.6/include -I/Users/mpsitech/src/devidhw -I/usr/include -I/usr/local/include -I/usr/local/include/aravis-0.6 -I/usr/local/include/libxml2 -I/usr/local/include/opencv -I/usr/local/mysql/include -I/usr/local/opt/sqlite/include

PCHS = Ideccmbd.h.gch

OBJS = Idec.o IdeccmbdAppsrv.o IdeccmbdJobprc.o IdeccmbdOpprc.o Ideccmbd.o
OBJS += JobIdecFusion.o JobIdecIllum.o JobIdecLwiracq.o JobIdecMechctl.o JobIdecQcdacq.o JobIdecRecord.o JobIdecSpotfind.o JobIdecStereo.o JobIdecTrigger.o JobIdecVislacq.o JobIdecVisracq.o
OBJS += RootIdec.o SessIdec.o
OBJS += Ideccmbd_exe.o

LIBPATH = -L$(LIBROOT)
LIBPATH += -L$(LIBROOT)/ideccmbd
LIBPATH += -L/Library/PostgreSQL/9.6/lib -L/Users/mpsitech/lib -L/usr/include -L/usr/local/lib -L/usr/local/mysql/lib -L/usr/local/opt/sqlite/lib
LIBPATH += 

LIBS = -lcrdidecnav -lcrdidecusg -lcrdidecusr -lcrdidecscf -lcrdidecutl -lcrdidecmis -lcrdidectou -lcrdideciaq -lcrdidecad1 -lcrdidecfil
LIBS += -liexidec -lvecidec -ldbsidec
LIBS += -laravis-0.6 -ldevidhw -lflycapture -ljpeg -lmicrohttpd -lnetcdf -lopencv_calib3d -lsbecore_dbsmon -lsbecore_mon
LIBS += -ldbecore -ldbswzem -lglib-2.0 -lhdf5_hl -lopencv_contrib
LIBS += -lgobject-2.0 -lhdf5 -lopencv_core -lsbecore_lite -lsbecore_my -lsbecore_pg
LIBS += -lmysqlclient -lopencv_features2d -lpq -lsbecore -lsqlite3
LIBS += -lopencv_flann -lxml2
LIBS += -lopencv_gpu -lz
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_legacy
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_ocl
LIBS += -lopencv_photo
LIBS += -lopencv_stitching
LIBS += -lopencv_superres
LIBS += -lopencv_ts
LIBS += -lopencv_video
LIBS += -lopencv_videostab
LIBS += 

EXE = Ideccmbd

.SUFFIXES:	.h .h.gch .cpp

.h.h.gch :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

.cpp.o :
	$(CPP) $(CPPFLAGS) $(INCPATH) -o $@ -c $<

all:	$(PCHS) $(EXE)

$(EXE):	$(OBJS)
	$(LINK) $(LINKFLAGS) $(OBJS) $(LIBPATH) $(LIBS) -o $(EXE)
	rm -f *.o

pch:	$(PCHS)

install:
	mv $(EXE) $(BINROOT)/ideccmbd/

clean:
	rm -f *.gch
	rm -f *.o

