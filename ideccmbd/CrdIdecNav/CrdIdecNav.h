/**
  * \file CrdIdecNav.h
  * job handler for job CrdIdecNav (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECNAV_H
#define CRDIDECNAV_H

// IP custInclude --- INSERT

#include "DlgIdecNavLoaini.h"
#include "PnlIdecNavHeadbar.h"
#include "PnlIdecNavPre.h"
#include "PnlIdecNavMaint.h"
#include "PnlIdecNavOpr.h"

#define VecVIdecNavDo CrdIdecNav::VecVDo
#define VecVIdecNavSge CrdIdecNav::VecVSge

#define ContInfIdecNav CrdIdecNav::ContInf
#define StatAppIdecNav CrdIdecNav::StatApp
#define StatShrIdecNav CrdIdecNav::StatShr
#define TagIdecNav CrdIdecNav::Tag

#define DpchAppIdecNavDo CrdIdecNav::DpchAppDo
#define DpchEngIdecNavData CrdIdecNav::DpchEngData

/**
  * CrdIdecNav
  */
class CrdIdecNav : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecNavDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITSESTRMCLICK = 3;
		static const uint MITCRDUSGCLICK = 4;
		static const uint MITCRDUSRCLICK = 5;
		static const uint MITCRDSCFCLICK = 6;
		static const uint MITCRDUTLCLICK = 7;
		static const uint MITCRDMISCLICK = 8;
		static const uint MITCRDTOUCLICK = 9;
		static const uint MITCRDIAQCLICK = 10;
		static const uint MITCRDAD1CLICK = 11;
		static const uint MITCRDFILCLICK = 12;
		static const uint MITAPPLOICLICK = 13;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecNavSge)
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
	  * ContInf (full: ContInfIdecNav)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;
		static const uint MTXSESSES1 = 3;
		static const uint MTXSESSES2 = 4;
		static const uint MTXSESSES3 = 5;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "", const string& MtxSesSes1 = "", const string& MtxSesSes2 = "", const string& MtxSesSes3 = "");

	public:
		uint numFSge;
		string MrlAppHlp;
		string MtxSesSes1;
		string MtxSesSes2;
		string MtxSesSes3;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecNav)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneHeadbar = false, const bool initdonePre = false, const bool initdoneMaint = false, const bool initdoneOpr = false);
	};

	/**
		* StatShr (full: StatShrIdecNav)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFDLGLOAINI = 1;
		static const uint JREFHEADBAR = 2;
		static const uint JREFPRE = 3;
		static const uint PNLPREAVAIL = 4;
		static const uint JREFMAINT = 5;
		static const uint PNLMAINTAVAIL = 6;
		static const uint JREFOPR = 7;
		static const uint PNLOPRAVAIL = 8;
		static const uint MSPCRD1AVAIL = 9;
		static const uint MITCRDUSGAVAIL = 10;
		static const uint MITCRDUSRAVAIL = 11;
		static const uint MITCRDSCFAVAIL = 12;
		static const uint MITCRDUTLAVAIL = 13;
		static const uint MSPCRD2AVAIL = 14;
		static const uint MITCRDMISAVAIL = 15;
		static const uint MITCRDTOUAVAIL = 16;
		static const uint MITCRDIAQAVAIL = 17;
		static const uint MITCRDIAQACTIVE = 18;
		static const uint MITCRDAD1AVAIL = 19;
		static const uint MITCRDAD1ACTIVE = 20;
		static const uint MITCRDFILAVAIL = 21;
		static const uint MSPAPP2AVAIL = 22;
		static const uint MITAPPLOIAVAIL = 23;

	public:
		StatShr(const ubigint jrefDlgloaini = 0, const ubigint jrefHeadbar = 0, const ubigint jrefPre = 0, const bool pnlpreAvail = false, const ubigint jrefMaint = 0, const bool pnlmaintAvail = false, const ubigint jrefOpr = 0, const bool pnloprAvail = false, const bool MspCrd1Avail = true, const bool MitCrdUsgAvail = true, const bool MitCrdUsrAvail = true, const bool MitCrdScfAvail = true, const bool MitCrdUtlAvail = true, const bool MspCrd2Avail = true, const bool MitCrdMisAvail = true, const bool MitCrdTouAvail = true, const bool MitCrdIaqAvail = true, const bool MitCrdIaqActive = true, const bool MitCrdAd1Avail = true, const bool MitCrdAd1Active = true, const bool MitCrdFilAvail = true, const bool MspApp2Avail = true, const bool MitAppLoiAvail = true);

	public:
		ubigint jrefDlgloaini;
		ubigint jrefHeadbar;
		ubigint jrefPre;
		bool pnlpreAvail;
		ubigint jrefMaint;
		bool pnlmaintAvail;
		ubigint jrefOpr;
		bool pnloprAvail;
		bool MspCrd1Avail;
		bool MitCrdUsgAvail;
		bool MitCrdUsrAvail;
		bool MitCrdScfAvail;
		bool MitCrdUtlAvail;
		bool MspCrd2Avail;
		bool MitCrdMisAvail;
		bool MitCrdTouAvail;
		bool MitCrdIaqAvail;
		bool MitCrdIaqActive;
		bool MitCrdAd1Avail;
		bool MitCrdAd1Active;
		bool MitCrdFilAvail;
		bool MspApp2Avail;
		bool MitAppLoiAvail;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecNav)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecNavDo)
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
		* DpchEngData (full: DpchEngIdecNavData)
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

	bool evalPnlpreAvail(DbsIdec* dbsidec);
	bool evalPnlmaintAvail(DbsIdec* dbsidec);
	bool evalPnloprAvail(DbsIdec* dbsidec);
	bool evalMspCrd1Avail(DbsIdec* dbsidec);
	bool evalMitCrdUsgAvail(DbsIdec* dbsidec);
	bool evalMitCrdUsrAvail(DbsIdec* dbsidec);
	bool evalMitCrdScfAvail(DbsIdec* dbsidec);
	bool evalMitCrdUtlAvail(DbsIdec* dbsidec);
	bool evalMspCrd2Avail(DbsIdec* dbsidec);
	bool evalMitCrdMisAvail(DbsIdec* dbsidec);
	bool evalMitCrdTouAvail(DbsIdec* dbsidec);
	bool evalMitCrdIaqAvail(DbsIdec* dbsidec);
	bool evalMitCrdIaqActive(DbsIdec* dbsidec);
	bool evalMitCrdAd1Avail(DbsIdec* dbsidec);
	bool evalMitCrdAd1Active(DbsIdec* dbsidec);
	bool evalMitCrdFilAvail(DbsIdec* dbsidec);
	bool evalMspApp2Avail(DbsIdec* dbsidec);
	bool evalMitAppLoiAvail(DbsIdec* dbsidec);

public:
	CrdIdecNav(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~CrdIdecNav();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	DlgIdecNavLoaini* dlgloaini;
	PnlIdecNavHeadbar* pnlheadbar;
	PnlIdecNavPre* pnlpre;
	PnlIdecNavMaint* pnlmaint;
	PnlIdecNavOpr* pnlopr;

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
	void handleDpchAppDoMitSesTrmClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdUsgClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdUsrClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdScfClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdUtlClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdMisClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdTouClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdIaqClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdAd1Click(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdFilClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitAppLoiClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDlgClose(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

