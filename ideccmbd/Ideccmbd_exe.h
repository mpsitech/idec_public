/**
  * \file Ideccmbd_exe.h
  * Idec combined daemon main (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECCMBD_EXE_H
#define IDECCMBD_EXE_H

#include <string>
#include <vector>

using namespace std;

#include <signal.h>

#include "IdeccmbdAppsrv.h"
#include "IdeccmbdJobprc.h"
#include "IdeccmbdOpprc.h"

/**
  * PrefIdeccmbd
  */
class PrefIdeccmbd : public Block {

public:
	static const uint STGIDECCMBD = 1;
	static const uint STGIDECDATABASE = 2;
	static const uint STGIDECGENERAL = 3;
	static const uint STGIDECHARDWARE = 4;
	static const uint STGIDECMONITOR = 5;
	static const uint STGIDECPATH = 6;
	static const uint STGJOBIDECFUSION = 7;
	static const uint STGJOBIDECILLUM = 8;
	static const uint STGJOBIDECLWIRACQ = 9;
	static const uint STGJOBIDECMECHCTL = 10;
	static const uint STGJOBIDECMECHCTLPHI = 11;
	static const uint STGJOBIDECMECHCTLTHETA = 12;
	static const uint STGJOBIDECQCDACQ = 13;
	static const uint STGJOBIDECRECORD = 14;
	static const uint STGJOBIDECSPOTFIND = 15;
	static const uint STGJOBIDECSTEREO = 16;
	static const uint STGJOBIDECTRIGGER = 17;
	static const uint STGJOBIDECVISLACQ = 18;
	static const uint STGJOBIDECVISRACQ = 19;
	static const uint ALL = 20;

public:
	PrefIdeccmbd(StgIdeccmbd* stgideccmbd = NULL, StgIdecDatabase* stgidecdatabase = NULL, StgIdecGeneral* stgidecgeneral = NULL, StgIdecHardware* stgidechardware = NULL, StgIdecMonitor* stgidecmonitor = NULL, StgIdecPath* stgidecpath = NULL, StgJobIdecFusion* stgjobidecfusion = NULL, StgJobIdecIllum* stgjobidecillum = NULL, StgJobIdecLwiracq* stgjobideclwiracq = NULL, StgJobIdecMechctl* stgjobidecmechctl = NULL, StgJobIdecMechctlPhi* stgjobidecmechctlphi = NULL, StgJobIdecMechctlTheta* stgjobidecmechctltheta = NULL, StgJobIdecQcdacq* stgjobidecqcdacq = NULL, StgJobIdecRecord* stgjobidecrecord = NULL, StgJobIdecSpotfind* stgjobidecspotfind = NULL, StgJobIdecStereo* stgjobidecstereo = NULL, StgJobIdecTrigger* stgjobidectrigger = NULL, StgJobIdecVislacq* stgjobidecvislacq = NULL, StgJobIdecVisracq* stgjobidecvisracq = NULL, const set<uint>& mask = {ALL});

public:
	StgIdeccmbd stgideccmbd;
	StgIdecDatabase stgidecdatabase;
	StgIdecGeneral stgidecgeneral;
	StgIdecHardware stgidechardware;
	StgIdecMonitor stgidecmonitor;
	StgIdecPath stgidecpath;
	StgJobIdecFusion stgjobidecfusion;
	StgJobIdecIllum stgjobidecillum;
	StgJobIdecLwiracq stgjobideclwiracq;
	StgJobIdecMechctl stgjobidecmechctl;
	StgJobIdecMechctlPhi stgjobidecmechctlphi;
	StgJobIdecMechctlTheta stgjobidecmechctltheta;
	StgJobIdecQcdacq stgjobidecqcdacq;
	StgJobIdecRecord stgjobidecrecord;
	StgJobIdecSpotfind stgjobidecspotfind;
	StgJobIdecStereo stgjobidecstereo;
	StgJobIdecTrigger stgjobidectrigger;
	StgJobIdecVislacq stgjobidecvislacq;
	StgJobIdecVisracq stgjobidecvisracq;

public:
	static bool all(const set<uint>& items);

	void readXMLFromFile(const string& fullpath);
	void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXMLToFile(const string& fullpath);
	void writeXML(xmlTextWriter* wr);
};

/**
  * Ideccmbd
  */
class Ideccmbd {

public:
	Ideccmbd(const string& exedir, const bool clearAll, const bool startMon);
	~Ideccmbd();

	void init(const string& exedir, const bool clearAll, const bool startMon);
	bool initdone;
	void term();

public:
	string exedir;

	DbsIdec dbsidec;

	XchgIdeccmbd* xchg;
	
	RootIdec* root;

	MHD_Daemon* appsrv;

	vector<pthread_t> jobprcs;

	vector<pthread_t> opprcs;

public:
	void loadPref();
	void storePref();

	void initXchgdataJobprc();
	void termXchgdataJobprc();

	void initXchgdataOpprc();
	void termXchgdataOpprc();
};

Ideccmbd* ideccmbd;

#endif

