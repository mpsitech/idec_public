/**
  * \file Ideccmbd.h
  * inter-thread exchange object for Idec combined daemon (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECCMBD_H
#define IDECCMBD_H

#ifdef __CYGWIN__
	#include <sys/select.h>
#endif

#include <unistd.h>

#ifndef _WIN32
	#include <sys/socket.h>
#endif
#ifdef _WIN32
	#include <windows.h>
	#include <winsock.h>
	typedef int socklen_t;
#endif

#include <sys/stat.h>

#include <microhttpd.h>

#include <sbecore/Engtypes.h>
#include <sbecore/Txtrd.h>
#include <sbecore/DbsMon.h>

#include "Idec.h"

// IP incl --- IBEGIN
#include "DevIdhw.h"
// IP incl --- IEND

class XchgIdeccmbd;
typedef XchgIdeccmbd XchgIdec;

/**
	* DpchAppIdec
	*/
class DpchAppIdec : public DpchIdec {

public:
	static const uint JREF = 1;

public:
	DpchAppIdec(const uint ixIdecVDpch = 0);
	virtual ~DpchAppIdec();

public:
	ubigint jref;

public:
	static bool all(const set<uint>& items);
	virtual string getSrefsMask();

	virtual void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * DpchAppIdecAlert
  */
class DpchAppIdecAlert : public DpchAppIdec {

public:
	static const uint JREF = 1;
	static const uint NUMFMCB = 2;

public:
	DpchAppIdecAlert();

public:
	uint numFMcb;

public:
	static bool all(const set<uint>& items);
	string getSrefsMask();

	void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * DpchAppIdecInit
  */
class DpchAppIdecInit : public DpchAppIdec {

public:
	DpchAppIdecInit();
};

/**
  * DpchAppIdecResume
  */
class DpchAppIdecResume : public DpchAppIdec {

public:
	DpchAppIdecResume();
};

/**
	* DpchEngIdec
	*/
class DpchEngIdec : public DpchIdec {

public:
	static const uint JREF = 1;

public:
	DpchEngIdec(const uint ixIdecVDpch = 0, const ubigint jref = 0);
	virtual ~DpchEngIdec();

public:
	ubigint jref;

public:
	static bool all(const set<uint>& items);
	virtual string getSrefsMask();
	virtual void merge(DpchEngIdec* dpcheng);

	virtual void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
};

/**
  * DpchEngIdecAck
  */
class DpchEngIdecAck : public DpchEngIdec {

public:
	DpchEngIdecAck(const ubigint jref = 0);
};

/**
  * DpchEngIdecAlert
  */
class DpchEngIdecAlert : public DpchEngIdec {

public:
	static const uint JREF = 1;
	static const uint CONTINF = 2;
	static const uint FEEDFMCB = 3;
	static const uint ALL = 4;

public:
	DpchEngIdecAlert(const ubigint jref = 0, ContInfIdecAlert* continf = NULL, Feed* feedFMcb = NULL, const set<uint>& mask = {NONE});

public:
	ContInfIdecAlert continf;
	Feed feedFMcb;

public:
	static bool all(const set<uint>& items);
	string getSrefsMask();
	void merge(DpchEngIdec* dpcheng);

	void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
};

/**
  * DpchEngIdecConfirm
  */
class DpchEngIdecConfirm : public DpchEngIdec {

public:
	static const uint ACCEPTED = 1;
	static const uint JREF = 2;
	static const uint SREF = 3;
	static const uint ALL = 4;

public:
	DpchEngIdecConfirm(const bool accepted = false, const ubigint jref = 0, const string& sref = "", const set<uint>& mask = {ALL});

public:
	bool accepted;
	string sref;

public:
	static bool all(const set<uint>& items);
	string getSrefsMask();
	void merge(DpchEngIdec* dpcheng);

	void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
};

/**
  * DpchEngIdecSuspend
  */
class DpchEngIdecSuspend : public DpchEngIdec {

public:
	DpchEngIdecSuspend(const ubigint jref = 0);
};

/**
	* StgIdeccmbd
	*/
class StgIdeccmbd : public Block {

public:
	static const uint JOBPRCN = 1;
	static const uint OPPRCN = 2;
	static const uint APPSRVPORT = 3;
	static const uint HTTPS = 4;
	static const uint HISTLENGTH = 5;

public:
	StgIdeccmbd(const usmallint jobprcn = 1, const usmallint opprcn = 1, const usmallint appsrvport = 0, const bool https = false, const usmallint histlength = 20);

public:
	usmallint jobprcn;
	usmallint opprcn;
	usmallint appsrvport;
	bool https;
	usmallint histlength;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgIdeccmbd* comp);
	set<uint> diff(const StgIdeccmbd* comp);
};

/**
	* StgIdecDatabase
	*/
class StgIdecDatabase : public Block {

public:
	static const uint IXDBSVDBSTYPE = 1;
	static const uint DBSPATH = 2;
	static const uint DBSNAME = 3;
	static const uint USERNAME = 4;
	static const uint PASSWORD = 5;
	static const uint IP = 6;
	static const uint PORT = 7;

public:
	StgIdecDatabase(const uint ixDbsVDbstype = 0, const string& dbspath = "", const string& dbsname = "", const string& username = "mpsitech", const string& password = "f9w8feeh", const string& ip = "", const usmallint port = 0);

public:
	uint ixDbsVDbstype;
	string dbspath;
	string dbsname;
	string username;
	string password;
	string ip;
	usmallint port;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgIdecDatabase* comp);
	set<uint> diff(const StgIdecDatabase* comp);
};

/**
	* StgIdecGeneral
	*/
class StgIdecGeneral : public Block {

public:
	static const uint IXIDECVSTLED = 1;
	static const uint DUMMY = 2;

public:
	StgIdecGeneral(const uint ixIdecVStled = VecIdecVStled::TEST, const bool dummy = false);

public:
	uint ixIdecVStled;
	bool dummy;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgIdecGeneral* comp);
	set<uint> diff(const StgIdecGeneral* comp);
};

/**
	* StgIdecHardware
	*/
class StgIdecHardware : public Block {

public:
	static const uint IXIDECVSYSTEM = 1;
	static const uint NRETRY = 2;
	static const uint DTPOLL = 3;
	static const uint PATH = 4;
	static const uint BPS = 5;
	static const uint LOGPATH = 6;

public:
	StgIdecHardware(const uint ixIdecVSystem = VecIdecVSystem::DSPCOMPLEX3SPI, const utinyint Nretry = 3, const double dtpoll = 100.0, const string& path = "/dev/spidev1.1", const uint bps = 24000000, const string& logpath = "");

public:
	uint ixIdecVSystem;
	utinyint Nretry;
	double dtpoll;
	string path;
	uint bps;
	string logpath;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgIdecHardware* comp);
	set<uint> diff(const StgIdecHardware* comp);
};

/**
	* StgIdecMonitor
	*/
class StgIdecMonitor : public Block {

public:
	static const uint USERNAME = 1;
	static const uint PASSWORD = 2;
	static const uint IP = 3;
	static const uint PORT = 4;
	static const uint IXDBSVDBSTYPE = 5;
	static const uint DBSPATH = 6;
	static const uint DBSNAME = 7;
	static const uint DBSUSERNAME = 8;
	static const uint DBSPASSWORD = 9;

public:
	StgIdecMonitor(const string& username = "", const string& password = "", const string& ip = "", const usmallint port = 0, const uint ixDbsVDbstype = 0, const string& dbspath = "", const string& dbsname = "", const string& dbsusername = "", const string& dbspassword = "");

public:
	string username;
	string password;
	string ip;
	usmallint port;
	uint ixDbsVDbstype;
	string dbspath;
	string dbsname;
	string dbsusername;
	string dbspassword;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgIdecMonitor* comp);
	set<uint> diff(const StgIdecMonitor* comp);
};

/**
	* StgIdecPath
	*/
class StgIdecPath : public Block {

public:
	static const uint ACVPATH = 1;
	static const uint KEYPATH = 2;
	static const uint MONPATH = 3;
	static const uint TMPPATH = 4;
	static const uint WEBPATH = 5;
	static const uint HELPURL = 6;

public:
	StgIdecPath(const string& acvpath = "", const string& keypath = "", const string& monpath = "", const string& tmppath = "", const string& webpath = "", const string& helpurl = "");

public:
	string acvpath;
	string keypath;
	string monpath;
	string tmppath;
	string webpath;
	string helpurl;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgIdecPath* comp);
	set<uint> diff(const StgIdecPath* comp);
};

/**
	* StgJobIdecFusion
	*/
class StgJobIdecFusion : public Block {

public:
	static const uint TCALIB = 1;
	static const uint DXLWIR = 2;
	static const uint DYLWIR = 3;
	static const uint DTHETALWIR = 4;
	static const uint DPHILWIR = 5;

public:
	StgJobIdecFusion(const uint tcalib = 0, const double dxlwir = -20.0, const double dylwir = -60.0, const double dthetalwir = 0.0, const double dphilwir = 0.0);

public:
	uint tcalib;
	double dxlwir;
	double dylwir;
	double dthetalwir;
	double dphilwir;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecFusion* comp);
	set<uint> diff(const StgJobIdecFusion* comp);
};

/**
	* StgJobIdecIllum
	*/
class StgJobIdecIllum : public Block {

public:
	static const uint FLDIXIDECVPORT = 1;
	static const uint SPTIXIDECVPORT = 2;

public:
	StgJobIdecIllum(const uint fldIxIdecVPort = VecIdecVPort::LED1, const uint sptIxIdecVPort = VecIdecVPort::LED2);

public:
	uint fldIxIdecVPort;
	uint sptIxIdecVPort;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecIllum* comp);
	set<uint> diff(const StgJobIdecIllum* comp);
};

/**
	* StgJobIdecLwiracq
	*/
class StgJobIdecLwiracq : public Block {

public:
	static const uint IXIDECVCAMTYPE = 1;
	static const uint LAM0 = 2;
	static const uint LAM1 = 3;
	static const uint WIDTH = 4;
	static const uint HEIGHT = 5;
	static const uint HPIX = 6;
	static const uint SERNO = 7;
	static const uint A = 8;
	static const uint B = 9;
	static const uint DS = 10;
	static const uint DT = 11;
	static const uint IPLTTVSSSX = 12;
	static const uint IPLTTVSSSY = 13;
	static const uint IXIDECVSQRGRP = 14;
	static const uint F = 15;
	static const uint FN = 16;
	static const uint K1 = 17;
	static const uint K2 = 18;
	static const uint P1 = 19;
	static const uint P2 = 20;
	static const uint K3 = 21;
	static const uint K4 = 22;
	static const uint K5 = 23;
	static const uint K6 = 24;

public:
	StgJobIdecLwiracq(const uint ixIdecVCamtype = VecIdecVCamtype::FLIRTAU2, const double lam0 = 7.0, const double lam1 = 14.0, const uint width = 640, const uint height = 512, const double hpix = 17, const string& serno = "", const double a = 0.05, const double b = 15000, const double dS = 0.008, const double dT = 0.006, const vector<usmallint>& iplTTvsSSx = {}, const vector<double>& iplTTvsSSy = {}, const uint ixIdecVSqrgrp = VecIdecVSqrgrp::R2, const double f = 9, const double fn = 1.4, const double k1 = 0.0, const double k2 = 0.0, const double p1 = 0.0, const double p2 = 0.0, const double k3 = 0.0, const double k4 = 0.0, const double k5 = 0.0, const double k6 = 0.0);

public:
	uint ixIdecVCamtype;
	double lam0;
	double lam1;
	uint width;
	uint height;
	double hpix;
	string serno;
	double a;
	double b;
	double dS;
	double dT;
	vector<usmallint> iplTTvsSSx;
	vector<double> iplTTvsSSy;
	uint ixIdecVSqrgrp;
	double f;
	double fn;
	double k1;
	double k2;
	double p1;
	double p2;
	double k3;
	double k4;
	double k5;
	double k6;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecLwiracq* comp);
	set<uint> diff(const StgJobIdecLwiracq* comp);
};

/**
	* StgJobIdecMechctl
	*/
class StgJobIdecMechctl : public Block {

public:
	static const uint IXVXLORIENT = 1;

public:
	StgJobIdecMechctl(const uint ixVXlorient = VecVJobIdecMechctlXlorient::XDOWN);

public:
	uint ixVXlorient;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecMechctl* comp);
	set<uint> diff(const StgJobIdecMechctl* comp);
};

/**
	* StgJobIdecMechctlPhi
	*/
class StgJobIdecMechctlPhi : public Block {

public:
	static const uint IXIDECVPORT = 1;
	static const uint TPR = 2;
	static const uint TCALIB = 3;
	static const uint GR = 4;
	static const uint OX = 5;
	static const uint OY = 6;
	static const uint AXM = 7;
	static const uint AYM = 8;
	static const uint PHIX = 9;
	static const uint PHIY = 10;
	static const uint LLIM = 11;
	static const uint ULIM = 12;
	static const uint TSTEP = 13;

public:
	StgJobIdecMechctlPhi(const uint ixIdecVPort = VecIdecVPort::SPI2, const utinyint tpr = 6, const uint tcalib = 0, const usmallint gr = 550, const double Ox = 0.0, const double Oy = 0.0, const double Axm = 1.0, const double Aym = 1.0, const double phix = 0.0, const double phiy = 0.0, const double llim = -25.0, const double ulim = 25.0, const usmallint tstep = 100);

public:
	uint ixIdecVPort;
	utinyint tpr;
	uint tcalib;
	usmallint gr;
	double Ox;
	double Oy;
	double Axm;
	double Aym;
	double phix;
	double phiy;
	double llim;
	double ulim;
	usmallint tstep;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecMechctlPhi* comp);
	set<uint> diff(const StgJobIdecMechctlPhi* comp);
};

/**
	* StgJobIdecMechctlTheta
	*/
class StgJobIdecMechctlTheta : public Block {

public:
	static const uint IXIDECVPORT = 1;
	static const uint TPR = 2;
	static const uint TCALIB = 3;
	static const uint GR = 4;
	static const uint OX = 5;
	static const uint OY = 6;
	static const uint AXM = 7;
	static const uint AYM = 8;
	static const uint PHIX = 9;
	static const uint PHIY = 10;
	static const uint LLIM = 11;
	static const uint ULIM = 12;
	static const uint TSTEP = 13;

public:
	StgJobIdecMechctlTheta(const uint ixIdecVPort = VecIdecVPort::SPI1, const utinyint tpr = 6, const uint tcalib = 0, const usmallint gr = 825, const double Ox = 0.0, const double Oy = 0.0, const double Axm = 1.0, const double Aym = 1.0, const double phix = 0.0, const double phiy = 0.0, const double llim = -45.0, const double ulim = 45.0, const usmallint tstep = 100);

public:
	uint ixIdecVPort;
	utinyint tpr;
	uint tcalib;
	usmallint gr;
	double Ox;
	double Oy;
	double Axm;
	double Aym;
	double phix;
	double phiy;
	double llim;
	double ulim;
	usmallint tstep;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecMechctlTheta* comp);
	set<uint> diff(const StgJobIdecMechctlTheta* comp);
};

/**
	* StgJobIdecQcdacq
	*/
class StgJobIdecQcdacq : public Block {

public:
	static const uint LAM0 = 1;
	static const uint DLAM = 2;
	static const uint WIDTH = 3;
	static const uint HPIX = 4;
	static const uint DPIX = 5;
	static const uint IXIDECVPORT = 6;
	static const uint TCALNUC = 7;
	static const uint A = 8;
	static const uint B = 9;
	static const uint ERR = 10;
	static const uint MULTERR = 11;
	static const uint DS = 12;
	static const uint DT = 13;
	static const uint IPLTTVSSSX = 14;
	static const uint IPLTTVSSSY = 15;
	static const uint IPLDTDSVSSSX = 16;
	static const uint IPLDTDSVSSSY = 17;
	static const uint IXIDECVSQRGRP = 18;
	static const uint F = 19;
	static const uint FN = 20;
	static const uint ON = 21;
	static const uint TTURNOFF = 22;
	static const uint TDET = 23;
	static const uint IXVFAN = 24;
	static const uint MOD = 25;
	static const uint FMOD = 26;
	static const uint VDD = 27;
	static const uint VREF = 28;
	static const uint TCALALN = 29;
	static const uint DXQCD = 30;
	static const uint DYQCD = 31;
	static const uint DXALIGN = 32;
	static const uint DYALIGN = 33;
	static const uint DTHETAALIGN = 34;
	static const uint DPHIALIGN = 35;

public:
	StgJobIdecQcdacq(const double lam0 = 4.4, const double dlam = 0.44, const uint width = 8, const double hpix = 75, const double dpix = 225, const uint ixIdecVPort = VecIdecVPort::SPI3, const uint tcalnuc = 0, const vector<double>& a = {}, const vector<double>& b = {}, const vector<double>& err = {}, const double multerr = 1.2, const double dS = 0.08, const double dT = 0.006, const vector<usmallint>& iplTTvsSSx = {}, const vector<double>& iplTTvsSSy = {}, const vector<usmallint>& iplDTdSvsSSx = {}, const vector<double>& iplDTdSvsSSy = {}, const uint ixIdecVSqrgrp = VecIdecVSqrgrp::S1, const double f = 30, const double fn = 1.8, const bool on = true, const double tturnoff = 30.0, const double Tdet = -40.0, const uint ixVFan = VecVJobIdecQcdacqFan::OFFREC, const bool mod = true, const double fmod = 150.0, const double Vdd = 3.3, const double Vref = 1.65, const uint tcalaln = 0, const double dxqcd = 10.0, const double dyqcd = -30.0, const double dxalign = 25.0, const double dyalign = 0.0, const double dthetaalign = 0.0, const double dphialign = 0.0);

public:
	double lam0;
	double dlam;
	uint width;
	double hpix;
	double dpix;
	uint ixIdecVPort;
	uint tcalnuc;
	vector<double> a;
	vector<double> b;
	vector<double> err;
	double multerr;
	double dS;
	double dT;
	vector<usmallint> iplTTvsSSx;
	vector<double> iplTTvsSSy;
	vector<usmallint> iplDTdSvsSSx;
	vector<double> iplDTdSvsSSy;
	uint ixIdecVSqrgrp;
	double f;
	double fn;
	bool on;
	double tturnoff;
	double Tdet;
	uint ixVFan;
	bool mod;
	double fmod;
	double Vdd;
	double Vref;
	uint tcalaln;
	double dxqcd;
	double dyqcd;
	double dxalign;
	double dyalign;
	double dthetaalign;
	double dphialign;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecQcdacq* comp);
	set<uint> diff(const StgJobIdecQcdacq* comp);
};

/**
	* StgJobIdecRecord
	*/
class StgJobIdecRecord : public Block {

public:
	static const uint FRMLIXIDECVCAMRES = 1;
	static const uint FRMLGRAY = 2;
	static const uint FRMRIXIDECVCAMRES = 3;
	static const uint FRMRGRAY = 4;
	static const uint FRMIIXIDECVCAMRES = 5;
	static const uint FRMQCD = 6;
	static const uint FRMSTEREO = 7;
	static const uint VIDFPS = 8;
	static const uint VIDLIXIDECVCAMRES = 9;
	static const uint VIDLGRAY = 10;
	static const uint VIDRIXIDECVCAMRES = 11;
	static const uint VIDRGRAY = 12;
	static const uint VIDIIXIDECVCAMRES = 13;
	static const uint VIDQCD = 14;
	static const uint VIDSTEREO = 15;
	static const uint IXVOVERWRITE = 16;

public:
	StgJobIdecRecord(const uint frmlIxIdecVCamres = VecIdecVCamres::MAX, const bool frmlGray = false, const uint frmrIxIdecVCamres = VecIdecVCamres::OFF, const bool frmrGray = false, const uint frmiIxIdecVCamres = VecIdecVCamres::MAX, const bool frmqcd = false, const bool frmstereo = false, const double vidfps = 10.0, const uint vidlIxIdecVCamres = VecIdecVCamres::_640, const bool vidlGray = true, const uint vidrIxIdecVCamres = VecIdecVCamres::OFF, const bool vidrGray = false, const uint vidiIxIdecVCamres = VecIdecVCamres::MAX, const bool vidqcd = false, const bool vidstereo = false, const uint ixVOverwrite = VecVJobIdecRecordOverwrite::NEVER);

public:
	uint frmlIxIdecVCamres;
	bool frmlGray;
	uint frmrIxIdecVCamres;
	bool frmrGray;
	uint frmiIxIdecVCamres;
	bool frmqcd;
	bool frmstereo;
	double vidfps;
	uint vidlIxIdecVCamres;
	bool vidlGray;
	uint vidrIxIdecVCamres;
	bool vidrGray;
	uint vidiIxIdecVCamres;
	bool vidqcd;
	bool vidstereo;
	uint ixVOverwrite;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecRecord* comp);
	set<uint> diff(const StgJobIdecRecord* comp);
};

/**
	* StgJobIdecSpotfind
	*/
class StgJobIdecSpotfind : public Block {

public:
	static const uint SEQLEN = 1;
	static const uint PMAX = 2;
	static const uint ADAPT = 3;

public:
	StgJobIdecSpotfind(const uint seqlen = 3, const double Pmax = 1.0, const bool adapt = true);

public:
	uint seqlen;
	double Pmax;
	bool adapt;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecSpotfind* comp);
	set<uint> diff(const StgJobIdecSpotfind* comp);
};

/**
	* StgJobIdecStereo
	*/
class StgJobIdecStereo : public Block {

public:
	static const uint TCALIB = 1;
	static const uint DSTEREO = 2;
	static const uint DTHETAVISR = 3;
	static const uint DPHIVISR = 4;

public:
	StgJobIdecStereo(const uint tcalib = 0, const double dstereo = 120.0, const double dthetavisr = 0.0, const double dphivisr = 0.0);

public:
	uint tcalib;
	double dstereo;
	double dthetavisr;
	double dphivisr;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecStereo* comp);
	set<uint> diff(const StgJobIdecStereo* comp);
};

/**
	* StgJobIdecTrigger
	*/
class StgJobIdecTrigger : public Block {

public:
	static const uint TVISR = 1;
	static const uint TLWIR = 2;
	static const uint TQCD = 3;

public:
	StgJobIdecTrigger(const double tvisr = 0.0, const double tlwir = 0.0, const double tqcd = 0.0);

public:
	double tvisr;
	double tlwir;
	double tqcd;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecTrigger* comp);
	set<uint> diff(const StgJobIdecTrigger* comp);
};

/**
	* StgJobIdecVislacq
	*/
class StgJobIdecVislacq : public Block {

public:
	static const uint IXIDECVCAMTYPE = 1;
	static const uint WIDTH = 2;
	static const uint HEIGHT = 3;
	static const uint HPIX = 4;
	static const uint TRIGIXIDECVPORT = 5;
	static const uint PATH = 6;
	static const uint SERNO = 7;
	static const uint IXIDECVSQRGRP = 8;
	static const uint F = 9;
	static const uint FN = 10;
	static const uint K1 = 11;
	static const uint K2 = 12;
	static const uint P1 = 13;
	static const uint P2 = 14;
	static const uint K3 = 15;
	static const uint K4 = 16;
	static const uint K5 = 17;
	static const uint K6 = 18;

public:
	StgJobIdecVislacq(const uint ixIdecVCamtype = VecIdecVCamtype::MSLIFE, const uint width = 1280, const uint height = 720, const double hpix = 3, const uint trigIxIdecVPort = VecIdecVPort::GPIO1, const string& path = "", const string& serno = "", const uint ixIdecVSqrgrp = VecIdecVSqrgrp::R2, const double f = 3, const double fn = 2, const double k1 = 0.0, const double k2 = 0.0, const double p1 = 0.0, const double p2 = 0.0, const double k3 = 0.0, const double k4 = 0.0, const double k5 = 0.0, const double k6 = 0.0);

public:
	uint ixIdecVCamtype;
	uint width;
	uint height;
	double hpix;
	uint trigIxIdecVPort;
	string path;
	string serno;
	uint ixIdecVSqrgrp;
	double f;
	double fn;
	double k1;
	double k2;
	double p1;
	double p2;
	double k3;
	double k4;
	double k5;
	double k6;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecVislacq* comp);
	set<uint> diff(const StgJobIdecVislacq* comp);
};

/**
	* StgJobIdecVisracq
	*/
class StgJobIdecVisracq : public Block {

public:
	static const uint IXIDECVCAMTYPE = 1;
	static const uint WIDTH = 2;
	static const uint HEIGHT = 3;
	static const uint HPIX = 4;
	static const uint TRIGIXIDECVPORT = 5;
	static const uint PATH = 6;
	static const uint SERNO = 7;
	static const uint IXIDECVSQRGRP = 8;
	static const uint F = 9;
	static const uint FN = 10;
	static const uint K1 = 11;
	static const uint K2 = 12;
	static const uint P1 = 13;
	static const uint P2 = 14;
	static const uint K3 = 15;
	static const uint K4 = 16;
	static const uint K5 = 17;
	static const uint K6 = 18;

public:
	StgJobIdecVisracq(const uint ixIdecVCamtype = VecIdecVCamtype::MSLIFE, const uint width = 1280, const uint height = 720, const double hpix = 3, const uint trigIxIdecVPort = VecIdecVPort::GPIO2, const string& path = "", const string& serno = "", const uint ixIdecVSqrgrp = VecIdecVSqrgrp::R2, const double f = 3, const double fn = 2, const double k1 = 0.0, const double k2 = 0.0, const double p1 = 0.0, const double p2 = 0.0, const double k3 = 0.0, const double k4 = 0.0, const double k5 = 0.0, const double k6 = 0.0);

public:
	uint ixIdecVCamtype;
	uint width;
	uint height;
	double hpix;
	uint trigIxIdecVPort;
	string path;
	string serno;
	uint ixIdecVSqrgrp;
	double f;
	double fn;
	double k1;
	double k2;
	double p1;
	double p2;
	double k3;
	double k4;
	double k5;
	double k6;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> comm(const StgJobIdecVisracq* comp);
	set<uint> diff(const StgJobIdecVisracq* comp);
};

/**
  * AlrIdec
  */
namespace AlrIdec {
	DpchEngIdecAlert* prepareAlrAbt(const ubigint jref, const uint ixIdecVLocale, Feed& feedFMcbAlert);
	DpchEngIdecAlert* prepareAlrPer(const ubigint jref, const uint ixIdecVLocale, const string& lineno, Feed& feedFMcbAlert);
	DpchEngIdecAlert* prepareAlrSav(const ubigint jref, const uint ixIdecVLocale, Feed& feedFMcbAlert);
};

/**
  * ReqIdec
  */
class ReqIdec {

public:
	/**
		* VecVBasetype
		*/
	class VecVBasetype {

	public:
		static const uint NONE = 0; // invalid
		static const uint WEB = 1; // web-client triggered ui file request (GET)
		static const uint CMD = 2; // command-line request
		static const uint REGULAR = 3; // web-client triggered Dpch request (POST+Dpch)
		static const uint NOTIFY = 4; // web-client triggered notify-on-Dpch request (POST/empty)
		static const uint POLL = 5; // web-client triggered Dpch poll request (POST/empty)
		static const uint UPLOAD = 6; // web-client triggered file upload request (POST)
		static const uint DOWNLOAD = 7; // web-client triggered file download request (GET)
		static const uint RET = 8; // op-engine or opprc triggered op return (DpchRet)
		static const uint TIMER = 9; // timer triggered request
		static const uint EXTCALL = 10; // externally triggered call request
	};

	/**
		* VecVState
		*/
	class VecVState {

	public:
		static const uint NONE = 0; // invalid
		static const uint RECEIVE = 1; // during data reception - appsrv internal
		static const uint WAITPRC = 2; // before caught by job processor that is idle - in reqs list
		static const uint PRC = 3; // while being processesd by job processor - still in reqs list ; appsrv thread waiting on cReply
		static const uint REPLY = 4; // while reply being transmitted by appsrv - appsrv internal
	};

public:
	ReqIdec(const uint ixVBasetype = VecVBasetype::NONE, const uint ixVState = VecVState::RECEIVE, const string& ip = "");
	~ReqIdec();

public:
	uint ixVBasetype;
	uint ixVState;

	// specific data for base type CMD
	string cmd;

	// specific data for base types REGULAR, NOTIFY, POLL, UPLOAD, DOWNLOAD
	string ip;

	// specific data for base types REGULAR, NOTIFY, POLL, UPLOAD
	MHD_PostProcessor* pp;

	// specific data for base types CMD, REGULAR, NOTIFY, UPLOAD, DOWNLOAD
	bool retain;
	pthread_mutex_t mcReady; // also protects compare/set of ixVState to REPLY
	pthread_cond_t cReady;

	// specific data for base types WEB, UPLOAD, DOWNLOAD
	string filename; // full path
	fstream* file;
	size_t filelen;

	// specific data for base types REGULAR, NOTIFY, POLL, RET
	char* request;
	size_t requestlen;

	// specific data for base types CMD, REGULAR, NOTIFY, POLL, UPLOAD, DOWNLOAD, RET, TIMER
	ubigint jref;

	// specific data for base type TIMER
	ubigint wref;
	string sref;

	// specific data for base type EXTCALL
	Call* call;

	// specific data for base types CMD, REGULAR, UPLOAD, DOWNLOAD, RET, TIMER
	bool weak;

	// specific data for base type REGULAR
	DpchAppIdec* dpchapp;

	// specific data for base types REGULAR, NOTIFY, POLL
	DpchEngIdec* dpcheng;
	uint ixIdecVLocale;

	// specific data for base type RET
	DpchInvIdec* dpchinv;
	DpchRetIdec* dpchret;

	// specific data for base types REGULAR, NOTIFY, POLL, RET
	char* reply;
	size_t replylen;

public:
	void setStateReply();
};

/**
	* DcolIdec
	*/
class DcolIdec {

public:
	DcolIdec(const ubigint jref = 0, const uint ixIdecVLocale = VecIdecVLocale::ENUS);
	~DcolIdec();

public:
	ubigint jref;

	uint ixIdecVLocale;

	pthread_mutex_t mAccess;

	bool hot;

	list<DpchEngIdec*> dpchs;

	ReqIdec* req;

public:
	int lockAccess(const string& srefObject = "", const string& srefMember = "");
	int unlockAccess(const string& srefObject = "", const string& srefMember = "");
};

/**
  * JobIdec
  */
class JobIdec {

public:
	JobIdec(XchgIdec* xchg, const uint ixIdecVJob = 0, const ubigint jrefSup = 0, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const bool prefmast = false);
	virtual ~JobIdec();

public:
	XchgIdec* xchg;

	ubigint jref;

	uint ixIdecVJob;

	ubigint jrefSup;
	set<ubigint> jrefsSub;

	uint ixIdecVLocale;

	ubigint jrefMast;
	list<ubigint> jrefsSlv;

	bool prefmast;

	pthread_mutex_t mAccess;

	bool muteRefresh;

	uint ixVSge;
	uint nextIxVSge;

	uint opNdone;
	uint opN;

	vector<DpchInvIdec*> invs;

	pthread_mutex_t mOps;
	list<Op*> ops;
	string opsqkLast;

	ubigint wrefLast;
	ubigint wrefMin;

	ReqIdec* reqCmd;

public:
	virtual DpchEngIdec* getNewDpchEng(set<uint> items);

	virtual void refresh(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshWithDpchEng(DbsIdec* dbsidec, DpchEngIdec** dpcheng = NULL);

	virtual string getSquawk(DbsIdec* dbsidec);

	virtual void giveupMaster(DbsIdec* dbsidec);
	virtual void giveupSlave(DbsIdec* dbsidec);
	virtual void becomeMaster(DbsIdec* dbsidec);
	virtual void becomeSlave(DbsIdec* dbsidec);

	virtual bool handleClaimMaster(DbsIdec* dbsidec);
	virtual void handleRequest(DbsIdec* dbsidec, ReqIdec* req);
	virtual void handleCall(DbsIdec* dbsidec, Call* call);

	int lockAccess(const string& srefObject, const string& srefMember);
	int trylockAccess(const string& srefObject, const string& srefMember);
	int unlockAccess(const string& srefObject, const string& srefMember);
	int lockAccess(const string& srefMember);
	int unlockAccess(const string& srefMember);

	void clearInvs();
	ubigint addInv(DpchInvIdec* inv);
	void addInvs(vector<DpchInvIdec*>& _invs);
	void submitInvs(DbsIdec* dbsidec, const uint emptyIxVSge, uint& _ixVSge);

	void clearOps();
	void addOp(DbsIdec* dbsidec, DpchInvIdec* inv);
	void removeOp(const ubigint oref);
	string getOpsqkLast();

	void callback(const uint _nextIxVSge);
	void invalidateWakeups();
};

/**
  * StmgrIdec
  */
class StmgrIdec {

public:
	StmgrIdec(XchgIdec* xchg, const ubigint jref, const uint ixVNonetype);
	~StmgrIdec();

public:
	XchgIdec* xchg;

	ubigint jref;
	uint ixVNonetype;

	Stcch* stcch;

	pthread_mutex_t mAccess;

public:
	void handleCall(DbsIdec* dbsidec, Call* call);
	bool refresh(DbsIdec* dbsidec, Stcchitem* stit);

	void begin();
	void commit();

	int lockAccess(const string& srefObject = "", const string& srefMember = "");
	int unlockAccess(const string& srefObject = "", const string& srefMember = "");
};

/**
  * WakeupIdec
  */
class WakeupIdec {

public:
	WakeupIdec(XchgIdec* xchg, const ubigint wref, const ubigint jref, const string sref, const unsigned int deltat = 0, const bool weak = false);

public:
	XchgIdec* xchg;

	ubigint wref;

	ubigint jref;
	string sref;
	unsigned int deltat;
	bool weak;
};

/**
  * ExtcallIdec
  */
class ExtcallIdec {

public:
	ExtcallIdec(XchgIdec* xchg, Call* call);

public:
	XchgIdec* xchg;
	Call* call;
};

/**
  * XchgdataIdecJobprc
  */
class XchgdataIdecJobprc {

public:
	// IP datajobprc.subs --- INSERT

public:
	XchgdataIdecJobprc();

public:
	// IP datajobprc --- IBEGIN
	SysIdhw* sysidhw;
	XchgIdhw* xchgidhw;

	pthread_mutex_t mFlycap;
	// IP datajobprc --- IEND
};

/**
  * XchgdataIdecOpprc
  */
class XchgdataIdecOpprc {

public:
	// IP dataopprc.subs --- INSERT

public:
	XchgdataIdecOpprc();

public:
	// IP dataopprc --- INSERT
};

/**
	* XchgdataJobIdecFusion
	*/
class XchgdataJobIdecFusion {

public:
	// IP XchgdataJobIdecFusion.subs --- INSERT

public:
	XchgdataJobIdecFusion();

public:
	// IP XchgdataJobIdecFusion --- IBEGIN
	unsigned int seqno;

	pthread_mutex_t mJrefsStarted;
	set<ubigint> jrefsStarted;

	// run-time data
	Snippet* lwirgray;
	Snippet* vislred;
	Snippet* vislgreen;
	Snippet* vislblue;

	Imgbuf rgb;
	// IP XchgdataJobIdecFusion --- IEND
};

/**
	* XchgdataJobIdecIllum
	*/
class XchgdataJobIdecIllum {

public:
	// IP XchgdataJobIdecIllum.subs --- INSERT

public:
	XchgdataJobIdecIllum();

public:
	// IP XchgdataJobIdecIllum --- IBEGIN
	UntIdhwDcx3* dcx3;
	
	// status
	double pFlood;
	double pSpot;
	// IP XchgdataJobIdecIllum --- IEND
};

/**
	* XchgdataJobIdecLwiracq
	*/
class XchgdataJobIdecLwiracq {

public:
	// IP XchgdataJobIdecLwiracq.subs --- INSERT

public:
	XchgdataJobIdecLwiracq();

public:
	// IP XchgdataJobIdecLwiracq --- IBEGIN
	UntIdhwDcx3* dcx3;
	UntIdhwTau2* tau2;

	// status
	bool dummy;

	uint ixIdecVCamste;

	unsigned int seqno;

	pthread_mutex_t mJrefsStarted;
	set<ubigint> jrefsStarted;

	// run-time data
	vector<usmallint> TTvsSS;

	unsigned short* gray0;

	Imgbuf gray;

	// dummy functionality
	unsigned short* testpat;

	int x;
	int y;
	int vx; // displacement in pixels per dummy frame
	int vy;
	// IP XchgdataJobIdecLwiracq --- IEND
};

/**
	* XchgdataJobIdecMechctl
	*/
class XchgdataJobIdecMechctl {

public:
	// IP XchgdataJobIdecMechctl.subs --- INSERT

public:
	XchgdataJobIdecMechctl();

public:
	// IP XchgdataJobIdecMechctl --- IBEGIN
	UntIdhwAxs2* thetaaxs2;
	UntIdhwAxs2* phiaxs2;

	// status
	bool dummy;

	uint theIxIdecVAxisste;
	uint phiIxIdecVAxisste;

	double alpha;
	double beta;

	double theta;
	double phi;

	uint thetaRpm;
	uint phiRpm;

	// dummy functionality
	double alphaA, alphaT;
	double betaA, betaT;

	uint rpmp;
	uint drpmdt;

	double theta0, theta1;
	timespec ttheta0;

	double phi0, phi1;
	timespec tphi0;
	// IP XchgdataJobIdecMechctl --- IEND
};

/**
	* XchgdataJobIdecQcdacq
	*/
class XchgdataJobIdecQcdacq {

public:
	// IP XchgdataJobIdecQcdacq.subs --- INSERT

public:
	XchgdataJobIdecQcdacq();

public:
	// IP XchgdataJobIdecQcdacq --- IBEGIN
	UntIdhwIcm2* icm2;

	// status
	bool dummy;

	uint ixIdecVQcdste;

	unsigned int seqno;

	pthread_mutex_t mJrefsStarted;
	set<ubigint> jrefsStarted;

	double Tdet;

	bool fullframe;
	usmallint pixel;
	unsigned int Ncyc;

	// run-time data
	vector<usmallint> TTvsSS;
	vector<double> dTdSvsSS;

	vector<double> T0;
	vector<double> DeltaT0;

	Imgbuf TDeltaT;

	// dummy functionality
	double dTdetDt = 5.0;

	double Tdet0, Tdet1;
	timespec tTdet0;
	// IP XchgdataJobIdecQcdacq --- IEND
};

/**
	* XchgdataJobIdecSpotfind
	*/
class XchgdataJobIdecSpotfind {

public:
	// IP XchgdataJobIdecSpotfind.subs --- INSERT

public:
	XchgdataJobIdecSpotfind();

public:
	// IP XchgdataJobIdecSpotfind --- IBEGIN
	UntIdhwDcx3* dcx3;

	// status
	bool dummy;

	pthread_mutex_t mJrefsStartedVisr;
	set<ubigint> jrefsStarted;
	set<ubigint> jrefsVisr;

	// run-time data
	Snippet* vislred;
	Snippet* visrred;

	bool found;

	double x;
	double y;

	// dummy functionality
	double A;
	double dr;

	unsigned int Njump; // number of frames before random re-initialization of x0, y0, vx, vy, ds

	unsigned int seqno_last;

	double x0;
	double y0;

	double ds; // stereo distance in pixels

	double vx; // displacement in pixels per frame
	double vy;

	// IP XchgdataJobIdecSpotfind --- IEND
};

/**
	* XchgdataJobIdecStereo
	*/
class XchgdataJobIdecStereo {

public:
	// IP XchgdataJobIdecStereo.subs --- INSERT

public:
	XchgdataJobIdecStereo();

public:
	// IP XchgdataJobIdecStereo --- IBEGIN
	unsigned int seqno;

	pthread_mutex_t mJrefsStarted;
	set<ubigint> jrefsStarted;

	// run-time data
	Snippet* vislgray;
	Snippet* visrgray;

	Imgbuf depth;
	// IP XchgdataJobIdecStereo --- IEND
};

/**
	* XchgdataJobIdecTrigger
	*/
class XchgdataJobIdecTrigger {

public:
	// IP XchgdataJobIdecTrigger.subs --- INSERT

public:
	XchgdataJobIdecTrigger();

public:
	// IP XchgdataJobIdecTrigger --- IBEGIN
	UntIdhwDcx3* dcx3;

	// status
	bool dummy;

	unsigned int seqno;

	// dummy functionality (software trigger)
	unsigned int usecFps;

	vector<int> usecWaits;
	vector<uint> icsIdecVCall;

	unsigned int ixUsecWaits;
	// IP XchgdataJobIdecTrigger --- IEND
};

/**
	* XchgdataJobIdecVislacq
	*/
class XchgdataJobIdecVislacq {

public:
	// IP XchgdataJobIdecVislacq.subs --- INSERT

public:
	XchgdataJobIdecVislacq();

public:
	// IP XchgdataJobIdecVislacq --- IBEGIN

	// status
	bool dummy;

	uint ixIdecVCamste;

	unsigned int seqno;

	pthread_mutex_t mJrefsStarted;
	set<ubigint> jrefsStarted;

	// camera data at full resolution, no orientation transform applied
	unsigned char* red0;
	unsigned char* green0;
	unsigned char* blue0;

	// camera data at full resolution with orientation transform applied
	Imgbuf rgb;

	// dummy functionality
	Testpat* testpat;

	// IP XchgdataJobIdecVislacq --- IEND
};

/**
	* XchgdataJobIdecVisracq
	*/
class XchgdataJobIdecVisracq {

public:
	// IP XchgdataJobIdecVisracq.subs --- INSERT

public:
	XchgdataJobIdecVisracq();

public:
	// IP XchgdataJobIdecVisracq --- IBEGIN

	// status
	bool dummy;

	uint ixIdecVCamste;

	unsigned int seqno;

	pthread_mutex_t mJrefsStarted;
	set<ubigint> jrefsStarted;

	// run-time data
	unsigned char* red0;
	unsigned char* green0;
	unsigned char* blue0;

	Imgbuf rgb;

	// dummy functionality
	Testpat* testpat;

	// IP XchgdataJobIdecVisracq --- IEND
};

/**
  * XchgIdeccmbd
  */
class XchgIdeccmbd {

public:
	XchgIdeccmbd();
	~XchgIdeccmbd();

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

	XchgdataIdecJobprc datajobprc;
	XchgdataIdecOpprc dataopprc;
	XchgdataJobIdecFusion datajobidecfusion;
	XchgdataJobIdecIllum datajobidecillum;
	XchgdataJobIdecLwiracq datajobideclwiracq;
	XchgdataJobIdecMechctl datajobidecmechctl;
	XchgdataJobIdecQcdacq datajobidecqcdacq;
	XchgdataJobIdecSpotfind datajobidecspotfind;
	XchgdataJobIdecStereo datajobidecstereo;
	XchgdataJobIdecTrigger datajobidectrigger;
	XchgdataJobIdecVislacq datajobidecvislacq;
	XchgdataJobIdecVisracq datajobidecvisracq;

public:
	// IP cust --- INSERT

public:
	// executable/archive/temporary folder paths and help URL
	string exedir;
	string acvpath;
	string tmppath;
	string helpurl;

	// root job
	ubigint jrefRoot;

	// job receiving commands
	ubigint jrefCmd;

	// scrambled ref codes
	pthread_mutex_t mScr;
	map<ubigint,string> scr;
	map<string,ubigint> descr;

	// monitor object
	DbsMon mon;

	// log file
	pthread_mutex_t mLogfile;

	// condition for job processors
	pthread_mutex_t mcJobprcs;
	pthread_cond_t cJobprcs;

	// condition for op processors
	pthread_mutex_t mcOpprcs;
	pthread_cond_t cOpprcs;

	// request list
	pthread_mutex_t mReqs;
	list<ReqIdec*> reqs;

	// operation invocation list
	Refseq* orefseq;
	pthread_mutex_t mInvs;
	list<DpchInvIdec*> invs;

	// presetting list
	pthread_mutex_t mPresets;
	multimap<presetref_t,Preset*> presets;

	// stub manager list
	pthread_mutex_t mStmgrs;
	map<ubigint,StmgrIdec*> stmgrs;

	// call listener list
	pthread_mutex_t mClstns;
	multimap<clstnref_t,Clstn*> clstns;
	multimap<clstnref2_t,clstnref_t> cref2sClstns;

	// dispatch collector list
	pthread_mutex_t mDcols;
	map<ubigint,DcolIdec*> dcols;

	// job list
	Refseq* jrefseq;
	pthread_mutex_t mJobs;
	map<ubigint,JobIdec*> jobs;

	// sequence for wakeup references
	Refseq* wrefseq;

public:
	// monitor object methods
	void startMon();
	void stopMon();

	// log file methods
	void appendToLogfile(const string& str);

	// request list methods
	void addReq(ReqIdec* req);
	ReqIdec* pullFirstReq();

	// operation invocation list methods
	void addInvs(DbsIdec* dbsidec, const ubigint jref, vector<DpchInvIdec*>& dpchinvs);
	DpchInvIdec* pullFirstInv();

	// presetting methods
	Preset* addPreset(const uint ixIdecVPreset, const ubigint jref, const Arg& arg);

	Preset* addIxPreset(const uint ixIdecVPreset, const ubigint jref, const uint ix);
	Preset* addRefPreset(const uint ixIdecVPreset, const ubigint jref, const ubigint ref);
	Preset* addRefsPreset(const uint ixIdecVPreset, const ubigint jref, const vector<ubigint>& refs);
	Preset* addSrefPreset(const uint ixIdecVPreset, const ubigint jref, const string& sref);
	Preset* addIntvalPreset(const uint ixIdecVPreset, const ubigint jref, const int intval);
	Preset* addDblvalPreset(const uint ixIdecVPreset, const ubigint jref, const double dblval);
	Preset* addBoolvalPreset(const uint ixIdecVPreset, const ubigint jref, const bool boolval);
	Preset* addTxtvalPreset(const uint ixIdecVPreset, const ubigint jref, const string& txtval);

	Preset* getPresetByPref(const presetref_t& pref);

	Arg getPreset(const uint ixIdecVPreset, const ubigint jref);

	uint getIxPreset(const uint ixIdecVPreset, const ubigint jref);
	ubigint getRefPreset(const uint ixIdecVPreset, const ubigint jref);
	vector<ubigint> getRefsPreset(const uint ixIdecVPreset, const ubigint jref);
	string getSrefPreset(const uint ixIdecVPreset, const ubigint jref);
	int getIntvalPreset(const uint ixIdecVPreset, const ubigint jref);
	double getDblvalPreset(const uint ixIdecVPreset, const ubigint jref);
	bool getBoolvalPreset(const uint ixIdecVPreset, const ubigint jref);
	string getTxtvalPreset(const uint ixIdecVPreset, const ubigint jref);

	void getPresetsByJref(const ubigint jref, vector<uint>& icsIdecVPreset, vector<Arg>& args);

	void removePreset(const uint ixIdecVPreset, const ubigint jref);
	void removePresetsByJref(const ubigint jref);

	// stub manager methods
	StmgrIdec* addStmgr(const ubigint jref, const uint ixVNonetype);
	StmgrIdec* getStmgrByJref(const ubigint jref);
	void removeStmgrByJref(const ubigint jref);

	// call listener list methods
	Clstn* addClstn(const uint ixIdecVCall, const ubigint jref, const uint ixVJobmask, const ubigint jrefTrig, const Arg& argMask, const uint ixVJactype = Clstn::VecVJactype::LOCK);

	Clstn* addIxClstn(const uint ixIdecVCall, const ubigint jref, const uint ixVJobmask, const ubigint jrefTrig, const uint ixMask, const uint ixVJactype = Clstn::VecVJactype::LOCK);
	Clstn* addRefClstn(const uint ixIdecVCall, const ubigint jref, const uint ixVJobmask, const ubigint jrefTrig, const ubigint refMask, const uint ixVJactype = Clstn::VecVJactype::LOCK);
	Clstn* addIxRefClstn(const uint ixIdecVCall, const ubigint jref, const uint ixVJobmask, const ubigint jrefTrig, const uint ixMask, const ubigint refMask, const uint ixVJactype = Clstn::VecVJactype::LOCK);
	Clstn* addIxRefSrefClstn(const uint ixIdecVCall, const ubigint jref, const uint ixVJobmask, const ubigint jrefTrig, const uint ixMask, const ubigint refMask, const string& srefMask, const uint ixVJactype = Clstn::VecVJactype::LOCK);

	Clstn* addClstnStmgr(const uint ixIdecVCall, const ubigint jref);

	Clstn* getClstnByCref(const clstnref_t& cref);
	void getClstnsByJref(const ubigint jref, const bool stmgr, vector<uint>& icsIdecVCall, vector<uint>& icsVJobmask);

	void removeClstns(const uint ixIdecVCall, const ubigint jref, const bool stmgr = false);
	void removeClstnsByJref(const ubigint jref, const bool stmgr = false);

	// call methods
	void findJrefsByCall(Call* call, vector<ubigint>& jrefs, vector<bool>& stmgrs, vector<uint>& icsVJactype);

	void triggerCall(DbsIdec* dbsidec, Call* call);

	bool triggerArgToArgCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const Arg& argInv, Arg& argRet);
	bool triggerCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref);
	bool triggerIxCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv);
	bool triggerRefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const ubigint refInv);
	bool triggerIntvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const int intvalInv);
	bool triggerBoolvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const bool boolvalInv);
	bool triggerIxRefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const ubigint refInv);
	bool triggerIxSrefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const string& srefInv);
	bool triggerIxIntvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const int intvalInv);
	bool triggerIxDblvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const double dblvalInv);
	bool triggerIxTxtvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const string& txtvalInv);
	bool triggerToBoolvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, bool& boolvalRet);
	bool triggerIxToBoolvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, bool& boolvalRet);
	bool triggerRefToSrefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const ubigint refInv, string& srefRet);
	bool triggerRefToBoolvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const ubigint refInv, bool& boolvalRet);
	bool triggerIxRefToIxCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const ubigint refInv, uint& ixRet);
	bool triggerIxRefToRefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const ubigint refInv, ubigint& refRet);
	bool triggerIxRefSrefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const ubigint refInv, const string& srefInv);
	bool triggerIxRefSrefIntvalCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const ubigint refInv, const string& srefInv, const int intvalInv);
	bool triggerIxRefSrefIntvalToRefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const uint ixInv, const ubigint refInv, const string& srefInv, const int intvalInv, ubigint& refRet);
	bool triggerRefToIxCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const ubigint refInv, uint& ixRet);
	bool triggerSrefToRefCall(DbsIdec* dbsidec, const uint ixIdecVCall, const ubigint jref, const string& srefInv, ubigint& refRet);

	// dispatch collector list methods
	DcolIdec* addDcol(const ubigint jref);
	DcolIdec* getDcolByJref(const ubigint jref, const bool tree = true);
	void removeDcolByJref(const ubigint jref);

	void submitDpch(DpchEngIdec* dpcheng);
	DpchEngIdec* pullFirstDpch(DcolIdec* dcol);

	// job list methods
	ubigint addJob(JobIdec* job);
	ubigint addJob(DbsIdec* dbsidec, JobIdec* job);

	JobIdec* getJobByJref(const ubigint jref);

	void removeJobByJref(const ubigint jref);

	void transferMaster(DbsIdec* dbsidec, JobIdec* fromjob, JobIdec* tojob);
	void offerMaster(DbsIdec* dbsidec, const ubigint jref);
	bool claimMaster(DbsIdec* dbsidec, const ubigint jref);

	// timer methods
	ubigint addWakeup(const ubigint jref, const string sref, const unsigned int deltat = 0, const bool weak = false);
	static void* runWakeup(void* arg);

	// external call methods
	static void runExtcall(void* arg);
};
#endif


