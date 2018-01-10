/**
  * \file CrdIdecUtl.h
  * job handler for job CrdIdecUtl (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECUTL_H
#define CRDIDECUTL_H

// IP custInclude --- INSERT

#include "DlgIdecUtlTheta.h"
#include "DlgIdecUtlPhi.h"
#include "DlgIdecUtlStereo.h"
#include "DlgIdecUtlFusion.h"
#include "DlgIdecUtlQcdnuc.h"
#include "DlgIdecUtlQcdaln.h"
#include "PnlIdecUtlSpiterm.h"
#include "PnlIdecUtlHeadbar.h"

#define VecVIdecUtlDo CrdIdecUtl::VecVDo
#define VecVIdecUtlSge CrdIdecUtl::VecVSge

#define ContInfIdecUtl CrdIdecUtl::ContInf
#define StatAppIdecUtl CrdIdecUtl::StatApp
#define StatShrIdecUtl CrdIdecUtl::StatShr
#define TagIdecUtl CrdIdecUtl::Tag

#define DpchAppIdecUtlDo CrdIdecUtl::DpchAppDo
#define DpchEngIdecUtlData CrdIdecUtl::DpchEngData

/**
  * CrdIdecUtl
  */
class CrdIdecUtl : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecUtlDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;
		static const uint MITCRDTHECLICK = 3;
		static const uint MITCRDPHICLICK = 4;
		static const uint MITCRDSTECLICK = 5;
		static const uint MITCRDFSNCLICK = 6;
		static const uint MITCRDQNUCLICK = 7;
		static const uint MITCRDQALCLICK = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecUtlSge)
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
	  * ContInf (full: ContInfIdecUtl)
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
		* StatApp (full: StatAppIdecUtl)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneSpiterm = false, const bool initdoneHeadbar = false);
	};

	/**
		* StatShr (full: StatShrIdecUtl)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFDLGFUSION = 1;
		static const uint JREFDLGPHI = 2;
		static const uint JREFDLGQCDALN = 3;
		static const uint JREFDLGQCDNUC = 4;
		static const uint JREFDLGSTEREO = 5;
		static const uint JREFDLGTHETA = 6;
		static const uint JREFSPITERM = 7;
		static const uint JREFHEADBAR = 8;

	public:
		StatShr(const ubigint jrefDlgfusion = 0, const ubigint jrefDlgphi = 0, const ubigint jrefDlgqcdaln = 0, const ubigint jrefDlgqcdnuc = 0, const ubigint jrefDlgstereo = 0, const ubigint jrefDlgtheta = 0, const ubigint jrefSpiterm = 0, const ubigint jrefHeadbar = 0);

	public:
		ubigint jrefDlgfusion;
		ubigint jrefDlgphi;
		ubigint jrefDlgqcdaln;
		ubigint jrefDlgqcdnuc;
		ubigint jrefDlgstereo;
		ubigint jrefDlgtheta;
		ubigint jrefSpiterm;
		ubigint jrefHeadbar;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecUtl)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUtlDo)
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
		* DpchEngData (full: DpchEngIdecUtlData)
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
	CrdIdecUtl(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~CrdIdecUtl();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	DlgIdecUtlTheta* dlgtheta;
	DlgIdecUtlPhi* dlgphi;
	DlgIdecUtlStereo* dlgstereo;
	DlgIdecUtlFusion* dlgfusion;
	DlgIdecUtlQcdnuc* dlgqcdnuc;
	DlgIdecUtlQcdaln* dlgqcdaln;
	PnlIdecUtlSpiterm* pnlspiterm;
	PnlIdecUtlHeadbar* pnlheadbar;

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
	void handleDpchAppDoMitCrdTheClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdPhiClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdSteClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdFsnClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdQnuClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitCrdQalClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDlgClose(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

