/**
  * \file PnlIdecUsrRec.h
  * job handler for job PnlIdecUsrRec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSRREC_H
#define PNLIDECUSRREC_H

// IP custInclude --- INSERT

#include "PnlIdecUsrDetail.h"
#include "PnlIdecUsrAAccess.h"
#include "PnlIdecUsr1NSession.h"
#include "PnlIdecUsrMNUsergroup.h"

#define VecVIdecUsrRecDo PnlIdecUsrRec::VecVDo

#define ContInfIdecUsrRec PnlIdecUsrRec::ContInf
#define StatAppIdecUsrRec PnlIdecUsrRec::StatApp
#define StatShrIdecUsrRec PnlIdecUsrRec::StatShr
#define TagIdecUsrRec PnlIdecUsrRec::Tag

#define DpchAppIdecUsrRecDo PnlIdecUsrRec::DpchAppDo
#define DpchEngIdecUsrRecData PnlIdecUsrRec::DpchEngData

/**
  * PnlIdecUsrRec
  */
class PnlIdecUsrRec : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecUsrRecDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecUsrRec)
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
		* StatApp (full: StatAppIdecUsrRec)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const bool initdoneDetail = false, const bool initdoneAAccess = false, const bool initdone1NSession = false, const bool initdoneMNUsergroup = false);
	};

	/**
		* StatShr (full: StatShrIdecUsrRec)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint JREFDETAIL = 2;
		static const uint JREFAACCESS = 3;
		static const uint JREF1NSESSION = 4;
		static const uint JREFMNUSERGROUP = 5;
		static const uint BUTREGULARIZEACTIVE = 6;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::REGD, const ubigint jrefDetail = 0, const ubigint jrefAAccess = 0, const ubigint jref1NSession = 0, const ubigint jrefMNUsergroup = 0, const bool ButRegularizeActive = true);

	public:
		uint ixIdecVExpstate;
		ubigint jrefDetail;
		ubigint jrefAAccess;
		ubigint jref1NSession;
		ubigint jrefMNUsergroup;
		bool ButRegularizeActive;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecUsrRec)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUsrRecDo)
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
		* DpchEngData (full: DpchEngIdecUsrRecData)
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
	PnlIdecUsrRec(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecUsrRec();

public:
	ContInf continf;
	StatShr statshr;

	PnlIdecUsrDetail* pnldetail;
	PnlIdecUsrAAccess* pnlaaccess;
	PnlIdecUsr1NSession* pnl1nsession;
	PnlIdecUsrMNUsergroup* pnlmnusergroup;

	IdecMUser recUsr;

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

	bool handleCallIdecUsrUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

