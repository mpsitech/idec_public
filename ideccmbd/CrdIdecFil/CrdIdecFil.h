/**
  * \file CrdIdecFil.h
  * job handler for job CrdIdecFil (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECFIL_H
#define CRDIDECFIL_H

// IP custInclude --- INSERT

#include "DlgIdecFilExtrmed.h"
#include "PnlIdecFilRec.h"
#include "PnlIdecFilHeadbar.h"
#include "PnlIdecFilList.h"

#define VecVIdecFilDo CrdIdecFil::VecVDo
#define VecVIdecFilSge CrdIdecFil::VecVSge

#define ContInfIdecFil CrdIdecFil::ContInf
#define StatAppIdecFil CrdIdecFil::StatApp
#define StatShrIdecFil CrdIdecFil::StatShr
#define TagIdecFil CrdIdecFil::Tag

#define DpchAppIdecFilDo CrdIdecFil::DpchAppDo
#define DpchEngIdecFilData CrdIdecFil::DpchEngData

/**
  * CrdIdecFil
  */
class CrdIdecFil : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecFilDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITCRDEXMCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecFilSge)
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
	  * ContInf (full: ContInfIdecFil)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MTXCRDFIL = 3;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "", const string& MtxCrdFil = "");

	public:
		uint numFSge;
		string MrlAppHlp;
		string MtxCrdFil;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecFil)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneHeadbar = false, const bool initdoneList = false, const bool initdoneRec = false);
	};

	/**
		* StatShr (full: StatShrIdecFil)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFDLGEXTRMED = 1;
		static const uint JREFHEADBAR = 2;
		static const uint JREFLIST = 3;
		static const uint JREFREC = 4;
		static const uint MITCRDEXMACTIVE = 5;

	public:
		StatShr(const ubigint jrefDlgextrmed = 0, const ubigint jrefHeadbar = 0, const ubigint jrefList = 0, const ubigint jrefRec = 0, const bool MitCrdExmActive = true);

	public:
		ubigint jrefDlgextrmed;
		ubigint jrefHeadbar;
		ubigint jrefList;
		ubigint jrefRec;
		bool MitCrdExmActive;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecFil)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecFilDo)
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
		* DpchEngData (full: DpchEngIdecFilData)
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

	bool evalMitCrdExmActive(DbsIdec* dbsidec);

public:
	CrdIdecFil(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const ubigint ref = 0, const uint ixIdecVPreset = VecIdecVPreset::VOID, const ubigint preUref = 0);
	~CrdIdecFil();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	DlgIdecFilExtrmed* dlgextrmed;
	PnlIdecFilRec* pnlrec;
	PnlIdecFilHeadbar* pnlheadbar;
	PnlIdecFilList* pnllist;

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
	void handleDpchAppDoMitCrdExmClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDlgClose(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecRefPreSet(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv);
};

#endif

