/**
  * \file Idec.h
  * Idec global functionality (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDEC_H
#define IDEC_H

#define IDEC_VERSION "0.2.1"
#define IDEC_VERSION_MAJOR 0
#define IDEC_VERSION_MINOR 2
#define IDEC_VERSION_SUB 1

// IP incl --- IBEGIN
#include <sys/time.h>

#include <bitset>
// IP incl --- IEND

#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

#include "VecIdecVAxisste.h"
#include "VecIdecVCall.h"
#include "VecIdecVCamres.h"
#include "VecIdecVCamste.h"
#include "VecIdecVCamtype.h"
#include "VecIdecVChannel.h"
#include "VecIdecVCorner.h"
#include "VecIdecVDpch.h"
#include "VecIdecVExpstate.h"
#include "VecIdecVIop.h"
#include "VecIdecVJob.h"
#include "VecIdecVLat.h"
#include "VecIdecVLop.h"
#include "VecIdecVMimetype.h"
#include "VecIdecVOolop.h"
#include "VecIdecVOpengtype.h"
#include "VecIdecVOppack.h"
#include "VecIdecVPort.h"
#include "VecIdecVQcdste.h"
#include "VecIdecVQrystate.h"
#include "VecIdecVReqitmode.h"
#include "VecIdecVSqrgrp.h"
#include "VecIdecVStled.h"
#include "VecIdecVStub.h"
#include "VecIdecVSystem.h"
#include "VecIdecVTag.h"
#include "VecVJobIdecMechctlXlorient.h"
#include "VecVJobIdecQcdacqFan.h"
#include "VecVJobIdecRecordOverwrite.h"

#include <DbsIdec.h>

#include <sbecore/Stub.h>

/**
  * Acv
  */
namespace Acv {
	ubigint addfile(DbsIdec* dbsidec, const string& acvpath, const string& path, const uint refIxVTbl, const ubigint refUref, const string& osrefKContent, const string& Filename, const string& srefKMimetype, const string& Comment);
	void alterfile(DbsIdec* dbsidec, const string& acvpath, const string& path, const ubigint ref);
	string getfile(DbsIdec* dbsidec, const ubigint refIdecMFile);
};

/**
  * Lop
  */
namespace Lop {
	void apply(const uint ixIdecVLop, vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref);

	void insert(vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref);
	void remove(vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref);
};

/**
  * Oolop
  */
namespace Oolop {
	void apply(const uint ixIdecVOolop, vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref1, const ubigint ref2);

	void insertBefore(vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref1, const ubigint ref2);
	void insertAfter(vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref1, const ubigint ref2);
	void remove(vector<ubigint>& refsList, vector<ubigint>& refsPool, const ubigint ref);
	void toBefore(vector<ubigint>& refsList, const ubigint ref1, const ubigint ref2);
	void toAfter(vector<ubigint>& refsList, const ubigint ref1, const ubigint ref2);
	void swap(vector<ubigint>& refsList, const ubigint ref1, const ubigint ref2);
};

/**
  * Tmp
  */
namespace Tmp {
	string newfile(const string& tmppath, const string& ext);
	string newfolder(const string& tmppath);
	string random();
};

// IP cust --- IBEGIN
/**
  * Colormap
  */
namespace Colormap {
	unsigned int red(const unsigned int range, double val);
	unsigned int green(const unsigned int range, double val);
	unsigned int blue(const unsigned int range, double val);
};

/**
  * Dotmatrix
  */
namespace Dotmatrix {
	bitset<35> getBitset(const char c);
	bool getDot(const char c, const unsigned int ix);
};

/**
  * Imgbufitem
  */
class Imgbufitem {

public:
	Imgbufitem(const unsigned int seqno, const timespec timestamp, unsigned char* data, const size_t datalen, const ubigint jref);

public:
	unsigned int seqno;
	timespec timestamp;

	unsigned char* data;
	size_t datalen;

	list<ubigint> jrefsClaim;

public:
	void claim(const ubigint jref);
	void release(const ubigint jref);
};

/**
  * Imgbuf
  */
class Imgbuf {

public:
	Imgbuf();
	~Imgbuf();

	bool initdone;
	void init(const unsigned int N, const unsigned int itemlen);
	void term();

public:
	unsigned char* data;
	unsigned int N;
	unsigned int itemlen;

	pthread_mutex_t mAccess;

	ubigint brefseq;

	vector<ubigint> brefs; // size: N, to identify occupied/empty slots
	map<ubigint, Imgbufitem*> brefsItems;

public:
	ubigint getNewItem(const ubigint jref, const unsigned int seqno, timespec timestamp); // for master access

	Imgbufitem* getItem(const ubigint bref); // for read or write access

	void claim(const ubigint bref, const ubigint jref);

	void release(const ubigint bref, const ubigint jref);
	void releaseByJref(const ubigint jref);

	unsigned int cleanup(); // see if jrefsClaim is empty ; if yes, free slot in brefs
};

/**
  * Snippet
  */
class Snippet {

public:
	Snippet(const uint ixIdecVCamres, const uint ixIdecVChannel, const unsigned int w = 0, const unsigned int h = 0, const unsigned int x0 = 0, const unsigned int y0 = 0);
	~Snippet();

public:
	uint ixIdecVCamres;
	uint ixIdecVChannel;

	unsigned int w;
	unsigned int h;

	unsigned int x0;
	unsigned int y0;

	unsigned char* data;

	pthread_mutex_t mAccess;
	ubigint jrefClaim;

public:
	void reposition(const unsigned int _x0, const unsigned int _y0);
	void clear();

	bool claim(const ubigint jref);
	void release();

	void addDottext(const string& s, const uint ixIdecVCorner, const unsigned int margin, const bool invert = false);
};

/**
  * Testpat
  */
class Testpat {

public:
	Testpat(const unsigned int w, const unsigned int h, const bool grayscale);
	~Testpat();

public:
	unsigned int w;
	unsigned int h;

	bool grayscale;

	unsigned int dh;
	unsigned int hWhite;

	unsigned int r0;
	unsigned int dr;

	unsigned int ofs;
	bool up;

	// bars
	unsigned char* redEven;
	unsigned char* redOdd;
	unsigned char* greenEven;
	unsigned char* greenOdd;
	unsigned char* blueEven;
	unsigned char* blueOdd;

	unsigned short* grayEven;
	unsigned short* grayOdd;

	// circle
	vector<unsigned int> icsCircle;

	// h and v lines
	vector<unsigned int> icsHline;
	vector<unsigned int> icsVline;

public:
	void step(unsigned char* buf);
};
// IP cust --- IEND

/**
  * Idec
  */
namespace Idec {
	// IP gbl --- IBEGIN
	void getTimestamp(timespec* timestamp);
	double getDoubletime(timespec* timestamp);

	void setupIpl(const double xscl, vector<double>& y, const unsigned int N, vector<usmallint>& iplX, vector<double>& iplY);
	void setupFromIpl(vector<usmallint>& iplX, vector<double>& iplY, const unsigned int N, vector<double>& y);

	void getCamresWh(const uint ixIdecVCamres, unsigned int& w, unsigned int& h, const unsigned int _w = 0, const unsigned int _h = 0);

	void setupIntavg(const unsigned int inN, const unsigned int inMax, const unsigned int outMax, const double outPmin, unsigned int& im, bool* rshs, unsigned int& rshsN);
	unsigned int intavg(const unsigned int in, const unsigned int im, bool* rshs, const unsigned int rshsN);

	void copytrfBuf(unsigned char* src, unsigned char* trg, const unsigned int wlen, const unsigned int w, const unsigned int h, const uint ixIdecVSqrgrp);

	void addSpot(unsigned char* buf, const unsigned int w, const unsigned int h, const double A, const double x0, const double y0, const double dr);
	// IP gbl --- IEND
};

/**
  * OpengIdec
  */
namespace OpengIdec {
	void getIcsIdecVOppackByIxIdecVOpengtype(const uint ixIdecVOpengtype, vector<uint>& icsIdecVOppack);
	void getIcsIdecVDpchByIxIdecVOppack(const uint ixIdecVOppack, set<uint>& icsIdecVDpch);
};

/**
  * StubIdec
  */
namespace StubIdec {
	string getStub(DbsIdec* dbsidec, const uint ixIdecVStub, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);

	string getStubFilStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubGrp(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubMisStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubOwn(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubPrsStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubSesMenu(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubSesStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubTouStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubUsgStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
	string getStubUsrStd(DbsIdec* dbsidec, const ubigint ref, const uint ixIdecVLocale = VecIdecVLocale::ENUS, const uint ixVNonetype = Stub::VecVNonetype::DASH, Stcch* stcch = NULL, stcchitemref_t* strefSub = NULL, const bool refresh = false);
};

/**
  * IdecException
  */
struct IdecException {
	string err;

	IdecException(string err) {
		this->err = err;
	};
};

/**
	* ContInfIdecAlert
	*/
class ContInfIdecAlert : public Block {

public:
	static const uint TXTCPT = 1;
	static const uint TXTMSG1 = 2;
	static const uint TXTMSG2 = 3;
	static const uint TXTMSG3 = 4;
	static const uint TXTMSG4 = 5;
	static const uint TXTMSG5 = 6;
	static const uint TXTMSG6 = 7;
	static const uint TXTMSG7 = 8;
	static const uint TXTMSG8 = 9;
	static const uint TXTMSG9 = 10;
	static const uint TXTMSG10 = 11;
	static const uint TXTMSG11 = 12;
	static const uint TXTMSG12 = 13;

public:
	ContInfIdecAlert(const string& TxtCpt = "", const string& TxtMsg1 = "", const string& TxtMsg2 = "", const string& TxtMsg3 = "", const string& TxtMsg4 = "", const string& TxtMsg5 = "", const string& TxtMsg6 = "", const string& TxtMsg7 = "", const string& TxtMsg8 = "", const string& TxtMsg9 = "", const string& TxtMsg10 = "", const string& TxtMsg11 = "", const string& TxtMsg12 = "");

public:
	string TxtCpt;
	string TxtMsg1;
	string TxtMsg2;
	string TxtMsg3;
	string TxtMsg4;
	string TxtMsg5;
	string TxtMsg6;
	string TxtMsg7;
	string TxtMsg8;
	string TxtMsg9;
	string TxtMsg10;
	string TxtMsg11;
	string TxtMsg12;

public:
	static bool all(const set<uint>& items);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> compare(const ContInfIdecAlert* comp);
};

/**
  * DpchIdec
  */
class DpchIdec : public Block {

public:
	DpchIdec(const uint ixIdecVDpch = 0);
	virtual ~DpchIdec();

public:
	uint ixIdecVDpch;
};

/**
  * DpchInvIdec
  */
class DpchInvIdec : public DpchIdec {

public:
	static const uint SCROREF = 1;
	static const uint OREF = 1;
	static const uint SCRJREF = 2;
	static const uint JREF = 2;
	static const uint ALL = 3;

public:
	DpchInvIdec(const uint ixIdecVDpch = VecIdecVDpch::DPCHINVIDEC, const ubigint oref = 0, const ubigint jref = 0, const set<uint>& mask = {ALL});
	virtual ~DpchInvIdec();

public:
	string scrOref;
	ubigint oref;
	string scrJref;
	ubigint jref;

public:
	static bool all(const set<uint>& items);

	virtual void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	virtual void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
};

/**
	* DpchRetIdec
  */
class DpchRetIdec : public DpchIdec {

public:
	static const uint SCROREF = 1;
	static const uint OREF = 1;
	static const uint SCRJREF = 2;
	static const uint JREF = 2;
	static const uint SUCCESS = 3;
	static const uint ALL = 4;

public:
	DpchRetIdec(const uint ixIdecVDpch = VecIdecVDpch::DPCHRETIDEC, const string& scrOref = "", const string& scrJref = "", const bool success = false, const set<uint>& mask = {ALL});
	virtual ~DpchRetIdec();

public:
	string scrOref;
	ubigint oref;
	string scrJref;
	ubigint jref;
	bool success;

public:
	static bool all(const set<uint>& items);

	virtual void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	virtual void writeXML(xmlTextWriter* wr);
};

#endif


