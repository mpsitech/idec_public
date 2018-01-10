/**
  * \file ApiIdec_blks.h
  * Idec API library global data blocks (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef APIIDEC_BLKS_H
#define APIIDEC_BLKS_H

#include "VecIdecVDpch.h"
#include "VecIdecVExpstate.h"
#include "VecIdecVQrystate.h"
#include "VecIdecVReqitmode.h"

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
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
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
	* DpchAppIdec
	*/
class DpchAppIdec : public DpchIdec {

public:
	static const uint SCRJREF = 1;

public:
	DpchAppIdec(const uint ixIdecVDpch = 0, const string& scrJref = "");
	virtual ~DpchAppIdec();

public:
	string scrJref;

public:
	static bool all(const set<uint>& items);
	virtual string getSrefsMask();

	virtual void writeXML(xmlTextWriter* wr);
};

/**
	* DpchAppIdecAlert
	*/
class DpchAppIdecAlert : public DpchAppIdec {

public:
	static const uint SCRJREF = 1;
	static const uint NUMFMCB = 2;
	static const uint ALL = 3;

public:
	DpchAppIdecAlert(const string& scrJref = "", const uint numFMcb = 0, const set<uint>& mask = {NONE});

public:
	uint numFMcb;

public:
	static bool all(const set<uint>& items);
	string getSrefsMask();

	void writeXML(xmlTextWriter* wr);
};

/**
	* DpchAppIdecInit
	*/
class DpchAppIdecInit : public DpchAppIdec {

public:
	DpchAppIdecInit(const string& scrJref = "");
};

/**
	* DpchAppIdecResume
	*/
class DpchAppIdecResume : public DpchAppIdec {

public:
	DpchAppIdecResume(const string& scrJref = "");
};

/**
	* DpchEngIdec
	*/
class DpchEngIdec : public DpchIdec {

public:
	static const uint SCRJREF = 1;

public:
	DpchEngIdec(const uint ixIdecVDpch = 0);
	virtual ~DpchEngIdec();

public:
	string scrJref;

public:
	static bool all(const set<uint>& items);
	virtual string getSrefsMask();

	virtual void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
	* DpchEngIdecAck
	*/
class DpchEngIdecAck : public DpchEngIdec {

public:
	DpchEngIdecAck();
};

/**
	* DpchEngIdecAlert
	*/
class DpchEngIdecAlert : public DpchEngIdec {

public:
	static const uint SCRJREF = 1;
	static const uint CONTINF = 2;
	static const uint FEEDFMCB = 3;

public:
	DpchEngIdecAlert();

public:
	ContInfIdecAlert continf;
	Feed feedFMcb;

public:
	static bool all(const set<uint>& items);
	string getSrefsMask();

	void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
	* DpchEngIdecConfirm
	*/
class DpchEngIdecConfirm : public DpchEngIdec {

public:
	static const uint ACCEPTED = 1;
	static const uint SCRJREF = 2;
	static const uint SREF = 3;

public:
	DpchEngIdecConfirm();

public:
	bool accepted;
	string sref;

public:
	static bool all(const set<uint>& items);
	string getSrefsMask();

	void readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
	* DpchEngIdecSuspend
	*/
class DpchEngIdecSuspend : public DpchEngIdec {

public:
	DpchEngIdecSuspend();
};

#endif

