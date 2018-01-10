/**
  * \file CrdIdecMis.h
  * job handler for job CrdIdecMis (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECMIS_H
#define CRDIDECMIS_H

// IP custInclude --- INSERT

#include "DlgIdecMisNew.h"
#include "PnlIdecMisRec.h"
#include "PnlIdecMisHeadbar.h"
#include "PnlIdecMisList.h"

#define VecVIdecMisDo CrdIdecMis::VecVDo
#define VecVIdecMisSge CrdIdecMis::VecVSge

#define ContInfIdecMis CrdIdecMis::ContInf
#define StatAppIdecMis CrdIdecMis::StatApp
#define StatShrIdecMis CrdIdecMis::StatShr
#define TagIdecMis CrdIdecMis::Tag

#define DpchAppIdecMisDo CrdIdecMis::DpchAppDo
#define DpchEngIdecMisData CrdIdecMis::DpchEngData

/**
  * CrdIdecMis
  */
class CrdIdecMis : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecMisDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITCRDNEWCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecMisSge)
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
	  * ContInf (full: ContInfIdecMis)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MTXCRDMIS = 3;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "", const string& MtxCrdMis = "");

	public:
		uint numFSge;
		string MrlAppHlp;
		string MtxCrdMis;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecMis)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneHeadbar = false, const bool initdoneList = false, const bool initdoneRec = false);
	};

	/**
		* StatShr (full: StatShrIdecMis)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFDLGNEW = 1;
		static const uint JREFHEADBAR = 2;
		static const uint JREFLIST = 3;
		static const uint JREFREC = 4;
		static const uint MSPCRD1AVAIL = 5;
		static const uint MITCRDNEWAVAIL = 6;

	public:
		StatShr(const ubigint jrefDlgnew = 0, const ubigint jrefHeadbar = 0, const ubigint jrefList = 0, const ubigint jrefRec = 0, const bool MspCrd1Avail = true, const bool MitCrdNewAvail = true);

	public:
		ubigint jrefDlgnew;
		ubigint jrefHeadbar;
		ubigint jrefList;
		ubigint jrefRec;
		bool MspCrd1Avail;
		bool MitCrdNewAvail;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecMis)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecMisDo)
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
		* DpchEngData (full: DpchEngIdecMisData)
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

	bool evalMspCrd1Avail(DbsIdec* dbsidec);
	bool evalMitCrdNewAvail(DbsIdec* dbsidec);

public:
	CrdIdecMis(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const ubigint ref = 0);
	~CrdIdecMis();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	DlgIdecMisNew* dlgnew;
	PnlIdecMisRec* pnlrec;
	PnlIdecMisHeadbar* pnlheadbar;
	PnlIdecMisList* pnllist;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);
	void refresh(DbsIdec* dbsidec, set<uint>& moditems);
	void changeRef(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint ref, const bool notif = false);
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
	void handleDpchAppDoMitCrdNewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDlgClose(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecRefPreSet(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv);
};

#endif

