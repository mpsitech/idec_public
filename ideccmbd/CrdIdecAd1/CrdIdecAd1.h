/**
  * \file CrdIdecAd1.h
  * job handler for job CrdIdecAd1 (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECAD1_H
#define CRDIDECAD1_H

// IP custInclude --- INSERT

#include "PnlIdecAd1Control.h"
#include "PnlIdecAd1Headbar.h"

#define VecVIdecAd1Do CrdIdecAd1::VecVDo
#define VecVIdecAd1Sge CrdIdecAd1::VecVSge

#define ContInfIdecAd1 CrdIdecAd1::ContInf
#define StatAppIdecAd1 CrdIdecAd1::StatApp
#define StatShrIdecAd1 CrdIdecAd1::StatShr
#define TagIdecAd1 CrdIdecAd1::Tag

#define DpchAppIdecAd1Do CrdIdecAd1::DpchAppDo
#define DpchEngIdecAd1Data CrdIdecAd1::DpchEngData

/**
  * CrdIdecAd1
  */
class CrdIdecAd1 : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecAd1Do)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecAd1Sge)
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
	  * ContInf (full: ContInfIdecAd1)
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
		* StatApp (full: StatAppIdecAd1)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneControl = false, const bool initdoneHeadbar = false);
	};

	/**
		* StatShr (full: StatShrIdecAd1)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFCONTROL = 1;
		static const uint JREFHEADBAR = 2;

	public:
		StatShr(const ubigint jrefControl = 0, const ubigint jrefHeadbar = 0);

	public:
		ubigint jrefControl;
		ubigint jrefHeadbar;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecAd1)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecAd1Do)
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
		* DpchEngData (full: DpchEngIdecAd1Data)
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
	CrdIdecAd1(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const uint ixIdecVPreset = VecIdecVPreset::VOID, const ubigint preUref = 0);
	~CrdIdecAd1();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	PnlIdecAd1Control* pnlcontrol;
	PnlIdecAd1Headbar* pnlheadbar;

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

