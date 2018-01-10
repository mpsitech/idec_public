/**
  * \file CrdIdecScf.h
  * job handler for job CrdIdecScf (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECSCF_H
#define CRDIDECSCF_H

// IP custInclude --- INSERT

#include "PnlIdecScfConn.h"
#include "PnlIdecScfStatus.h"
#include "PnlIdecScfMech.h"
#include "PnlIdecScfOptics.h"
#include "PnlIdecScfTrigger.h"
#include "PnlIdecScfLwir.h"
#include "PnlIdecScfQcd.h"
#include "PnlIdecScfRecord.h"
#include "PnlIdecScfHeadbar.h"

#define VecVIdecScfDo CrdIdecScf::VecVDo
#define VecVIdecScfSge CrdIdecScf::VecVSge

#define ContInfIdecScf CrdIdecScf::ContInf
#define StatAppIdecScf CrdIdecScf::StatApp
#define StatShrIdecScf CrdIdecScf::StatShr
#define TagIdecScf CrdIdecScf::Tag

#define DpchAppIdecScfDo CrdIdecScf::DpchAppDo
#define DpchEngIdecScfData CrdIdecScf::DpchEngData

/**
  * CrdIdecScf
  */
class CrdIdecScf : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecScfSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRIDECABT = 2;
		static const uint CLOSE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContInf (full: ContInfIdecScf)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "");

	public:
		uint numFSge;
		string MrlAppHlp;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecScf)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneConn = false, const bool initdoneStatus = false, const bool initdoneMech = false, const bool initdoneOptics = false, const bool initdoneTrigger = false, const bool initdoneLwir = false, const bool initdoneQcd = false, const bool initdoneRecord = false, const bool initdoneHeadbar = false);
	};

	/**
		* StatShr (full: StatShrIdecScf)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFCONN = 1;
		static const uint JREFSTATUS = 2;
		static const uint JREFMECH = 3;
		static const uint JREFOPTICS = 4;
		static const uint JREFTRIGGER = 5;
		static const uint JREFLWIR = 6;
		static const uint JREFQCD = 7;
		static const uint JREFRECORD = 8;
		static const uint JREFHEADBAR = 9;

	public:
		StatShr(const ubigint jrefConn = 0, const ubigint jrefStatus = 0, const ubigint jrefMech = 0, const ubigint jrefOptics = 0, const ubigint jrefTrigger = 0, const ubigint jrefLwir = 0, const ubigint jrefQcd = 0, const ubigint jrefRecord = 0, const ubigint jrefHeadbar = 0);

	public:
		ubigint jrefConn;
		ubigint jrefStatus;
		ubigint jrefMech;
		ubigint jrefOptics;
		ubigint jrefTrigger;
		ubigint jrefLwir;
		ubigint jrefQcd;
		ubigint jrefRecord;
		ubigint jrefHeadbar;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScf)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecScfDo)
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
		* DpchEngData (full: DpchEngIdecScfData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint FEEDFSGE = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;
		static const uint ALL = 7;

	public:
		DpchEngData(const ubigint jref = 0, ContInf* continf = NULL, Feed* feedFSge = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContInf continf;
		Feed feedFSge;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

public:
	CrdIdecScf(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~CrdIdecScf();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	PnlIdecScfConn* pnlconn;
	PnlIdecScfStatus* pnlstatus;
	PnlIdecScfMech* pnlmech;
	PnlIdecScfOptics* pnloptics;
	PnlIdecScfTrigger* pnltrigger;
	PnlIdecScfLwir* pnllwir;
	PnlIdecScfQcd* pnlqcd;
	PnlIdecScfRecord* pnlrecord;
	PnlIdecScfHeadbar* pnlheadbar;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);
	void refresh(DbsIdec* dbsidec, set<uint>& moditems);
	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge, DpchEngIdec** dpcheng = NULL);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeAlridecabt(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlridecabt(DbsIdec* dbsidec);
	uint enterSgeClose(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeClose(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

	void handleDpchAppDoClose(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitAppAbtClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDlgClose(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

