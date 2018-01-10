/**
  * \file PnlIdecMisRec.h
  * job handler for job PnlIdecMisRec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISREC_H
#define PNLIDECMISREC_H

// IP custInclude --- INSERT

#include "PnlIdecMisDetail.h"
#include "PnlIdecMis1NTour.h"
#include "PnlIdecMisRef1NFile.h"

#define VecVIdecMisRecDo PnlIdecMisRec::VecVDo

#define ContInfIdecMisRec PnlIdecMisRec::ContInf
#define StatAppIdecMisRec PnlIdecMisRec::StatApp
#define StatShrIdecMisRec PnlIdecMisRec::StatShr
#define TagIdecMisRec PnlIdecMisRec::Tag

#define DpchAppIdecMisRecDo PnlIdecMisRec::DpchAppDo
#define DpchEngIdecMisRecData PnlIdecMisRec::DpchEngData

/**
  * PnlIdecMisRec
  */
class PnlIdecMisRec : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecMisRecDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecMisRec)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTREF = 1;

	public:
		ContInf(const string& TxtRef = "");

	public:
		string TxtRef;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecMisRec)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const bool initdoneDetail = false, const bool initdone1NTour = false, const bool initdoneRef1NFile = false);
	};

	/**
		* StatShr (full: StatShrIdecMisRec)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint JREFDETAIL = 2;
		static const uint JREF1NTOUR = 3;
		static const uint JREFREF1NFILE = 4;
		static const uint BUTREGULARIZEACTIVE = 5;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::REGD, const ubigint jrefDetail = 0, const ubigint jref1NTour = 0, const ubigint jrefRef1NFile = 0, const bool ButRegularizeActive = true);

	public:
		uint ixIdecVExpstate;
		ubigint jrefDetail;
		ubigint jref1NTour;
		ubigint jrefRef1NFile;
		bool ButRegularizeActive;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecMisRec)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecMisRecDo)
		*/
	class DpchAppDo : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint IXVDO = 2;

	public:
		DpchAppDo();

	public:
		uint ixVDo;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngData (full: DpchEngIdecMisRecData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint STATAPP = 3;
		static const uint STATSHR = 4;
		static const uint TAG = 5;
		static const uint ALL = 6;

	public:
		DpchEngData(const ubigint jref = 0, ContInf* continf = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContInf continf;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButRegularizeActive(DbsIdec* dbsidec);

public:
	PnlIdecMisRec(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecMisRec();

public:
	ContInf continf;
	StatShr statshr;

	PnlIdecMisDetail* pnldetail;
	PnlIdecMis1NTour* pnl1ntour;
	PnlIdecMisRef1NFile* pnlref1nfile;

	IdecMMission recMis;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);
	void minimize(DbsIdec* dbsidec, const bool notif = false, DpchEngIdec** dpcheng = NULL);
	void regularize(DbsIdec* dbsidec, const bool notif = false, DpchEngIdec** dpcheng = NULL);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMinimizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButRegularizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecMisUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

