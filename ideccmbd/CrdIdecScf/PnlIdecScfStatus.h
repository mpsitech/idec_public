/**
  * \file PnlIdecScfStatus.h
  * job handler for job PnlIdecScfStatus (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFSTATUS_H
#define PNLIDECSCFSTATUS_H

// IP custInclude --- IBEGIN
#include <sys/statvfs.h>
// IP custInclude --- IEND

#include "JobIdecFusion.h"
#include "JobIdecMechctl.h"
#include "JobIdecQcdacq.h"
#include "JobIdecRecord.h"
#include "JobIdecStereo.h"

#define VecVIdecScfStatusDo PnlIdecScfStatus::VecVDo
#define VecVIdecScfStatusSge PnlIdecScfStatus::VecVSge

#define ContInfIdecScfStatus PnlIdecScfStatus::ContInf
#define StatAppIdecScfStatus PnlIdecScfStatus::StatApp
#define StatShrIdecScfStatus PnlIdecScfStatus::StatShr
#define TagIdecScfStatus PnlIdecScfStatus::Tag

#define DpchAppIdecScfStatusDo PnlIdecScfStatus::DpchAppDo
#define DpchEngIdecScfStatusData PnlIdecScfStatus::DpchEngData

/**
  * PnlIdecScfStatus
  */
class PnlIdecScfStatus : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfStatusDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;
		static const uint BUTTHECLEARCLICK = 2;
		static const uint BUTPHICLEARCLICK = 3;
		static const uint BUTSTECLEARCLICK = 4;
		static const uint BUTFUSCLEARCLICK = 5;
		static const uint BUTQNUCLEARCLICK = 6;
		static const uint BUTQALCLEARCLICK = 7;
		static const uint BUTACVCLEARCLICK = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecScfStatusSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRCTH = 2;
		static const uint ALRCPH = 3;
		static const uint ALRCST = 4;
		static const uint ALRCFU = 5;
		static const uint ALRCQN = 6;
		static const uint ALRCQA = 7;
		static const uint ALRCAC = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContInf (full: ContInfIdecScfStatus)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTTHE = 2;
		static const uint TXTPHI = 3;
		static const uint TXTSTE = 4;
		static const uint TXTFUS = 5;
		static const uint TXTQNU = 6;
		static const uint TXTQAL = 7;
		static const uint TXTACV = 8;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtThe = "", const string& TxtPhi = "", const string& TxtSte = "", const string& TxtFus = "", const string& TxtQnu = "", const string& TxtQal = "", const string& TxtAcv = "");

	public:
		bool ButMasterOn;
		string TxtThe;
		string TxtPhi;
		string TxtSte;
		string TxtFus;
		string TxtQnu;
		string TxtQal;
		string TxtAcv;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecScfStatus)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecScfStatus)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTTHECLEARACTIVE = 1;
		static const uint BUTPHICLEARACTIVE = 2;
		static const uint BUTSTECLEARACTIVE = 3;
		static const uint BUTFUSCLEARACTIVE = 4;
		static const uint BUTQNUCLEARACTIVE = 5;
		static const uint BUTQALCLEARACTIVE = 6;
		static const uint BUTACVCLEARACTIVE = 7;

	public:
		StatShr(const bool ButTheClearActive = true, const bool ButPhiClearActive = true, const bool ButSteClearActive = true, const bool ButFusClearActive = true, const bool ButQnuClearActive = true, const bool ButQalClearActive = true, const bool ButAcvClearActive = true);

	public:
		bool ButTheClearActive;
		bool ButPhiClearActive;
		bool ButSteClearActive;
		bool ButFusClearActive;
		bool ButQnuClearActive;
		bool ButQalClearActive;
		bool ButAcvClearActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScfStatus)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecScfStatusDo)
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
		* DpchEngData (full: DpchEngIdecScfStatusData)
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

	bool evalButTheClearActive(DbsIdec* dbsidec);
	bool evalButPhiClearActive(DbsIdec* dbsidec);
	bool evalButSteClearActive(DbsIdec* dbsidec);
	bool evalButFusClearActive(DbsIdec* dbsidec);
	bool evalButQnuClearActive(DbsIdec* dbsidec);
	bool evalButQalClearActive(DbsIdec* dbsidec);
	bool evalButAcvClearActive(DbsIdec* dbsidec);

public:
	PnlIdecScfStatus(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfStatus();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;

	JobIdecFusion* jobfusion;
	JobIdecMechctl* jobmechctl;
	JobIdecQcdacq* jobqcdacq;
	JobIdecRecord* jobrecord;
	JobIdecStereo* jobstereo;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge, DpchEngIdec** dpcheng = NULL);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeAlrcth(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcth(DbsIdec* dbsidec);
	uint enterSgeAlrcph(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcph(DbsIdec* dbsidec);
	uint enterSgeAlrcst(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcst(DbsIdec* dbsidec);
	uint enterSgeAlrcfu(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcfu(DbsIdec* dbsidec);
	uint enterSgeAlrcqn(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcqn(DbsIdec* dbsidec);
	uint enterSgeAlrcqa(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcqa(DbsIdec* dbsidec);
	uint enterSgeAlrcac(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrcac(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMasterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButSteClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButFusClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButQnuClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButQalClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButAcvClearClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


