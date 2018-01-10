/**
  * \file PnlIdecAd1Control.h
  * job handler for job PnlIdecAd1Control (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECAD1CONTROL_H
#define PNLIDECAD1CONTROL_H

// IP custInclude --- INSERT

#include "JobIdecAutdet1.h"

#define VecVIdecAd1ControlDo PnlIdecAd1Control::VecVDo
#define VecVIdecAd1ControlSge PnlIdecAd1Control::VecVSge

#define ContIacIdecAd1Control PnlIdecAd1Control::ContIac
#define ContInfIdecAd1Control PnlIdecAd1Control::ContInf
#define StatAppIdecAd1Control PnlIdecAd1Control::StatApp
#define StatShrIdecAd1Control PnlIdecAd1Control::StatShr
#define TagIdecAd1Control PnlIdecAd1Control::Tag

#define DpchAppIdecAd1ControlData PnlIdecAd1Control::DpchAppData
#define DpchAppIdecAd1ControlDo PnlIdecAd1Control::DpchAppDo
#define DpchEngIdecAd1ControlData PnlIdecAd1Control::DpchEngData

/**
  * PnlIdecAd1Control
  */
class PnlIdecAd1Control : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecAd1ControlDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;
		static const uint BUTRUNCLICK = 2;
		static const uint BUTSTOCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecAd1ControlSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRGUM = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContIac (full: ContIacIdecAd1Control)
	  */
	class ContIac : public Block {

	public:
		static const uint SLDTLL = 1;
		static const uint SLDTUL = 2;
		static const uint UPDMCT = 3;

	public:
		ContIac(const double SldTll = 0.0, const double SldTul = 0.0, const int UpdMct = 0);

	public:
		double SldTll;
		double SldTul;
		int UpdMct;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecAd1Control)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint BUTMASTERON = 2;
		static const uint TXTPRG = 3;

	public:
		ContInf(const uint numFSge = 1, const bool ButMasterOn = false, const string& TxtPrg = "");

	public:
		uint numFSge;
		bool ButMasterOn;
		string TxtPrg;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecAd1Control)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecAd1Control)
		*/
	class StatShr : public Block {

	public:
		static const uint SLDTLLMIN = 1;
		static const uint SLDTLLMAX = 2;
		static const uint SLDTULMIN = 3;
		static const uint SLDTULMAX = 4;
		static const uint UPDMCTMIN = 5;
		static const uint UPDMCTMAX = 6;
		static const uint BUTRUNACTIVE = 7;
		static const uint BUTSTOACTIVE = 8;

	public:
		StatShr(const double SldTllMin = 25.0, const double SldTllMax = 45.0, const double SldTulMin = 25.0, const double SldTulMax = 45.0, const int UpdMctMin = 1, const int UpdMctMax = 10, const bool ButRunActive = true, const bool ButStoActive = true);

	public:
		double SldTllMin;
		double SldTllMax;
		double SldTulMin;
		double SldTulMax;
		int UpdMctMin;
		int UpdMctMax;
		bool ButRunActive;
		bool ButStoActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecAd1Control)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecAd1ControlData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;

	public:
		DpchAppData();

	public:
		ContIac contiac;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecAd1ControlDo)
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
		* DpchEngData (full: DpchEngIdecAd1ControlData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFSGE = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFSge = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFSge;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButRunActive(DbsIdec* dbsidec);
	bool evalButStoActive(DbsIdec* dbsidec);

public:
	PnlIdecAd1Control(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecAd1Control();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	JobIdecAutdet1* jobautdet1;

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
	uint enterSgeAlrgum(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlrgum(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMasterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButRunClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButStoClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

