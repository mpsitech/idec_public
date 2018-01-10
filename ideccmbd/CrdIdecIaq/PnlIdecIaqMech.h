/**
  * \file PnlIdecIaqMech.h
  * job handler for job PnlIdecIaqMech (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQMECH_H
#define PNLIDECIAQMECH_H

// IP custInclude --- INSERT

#include "JobIdecMechctl.h"

#define VecVIdecIaqMechDo PnlIdecIaqMech::VecVDo
#define VecVIdecIaqMechMode PnlIdecIaqMech::VecVMode
#define VecVIdecIaqMechSge PnlIdecIaqMech::VecVSge

#define ContIacIdecIaqMech PnlIdecIaqMech::ContIac
#define ContInfIdecIaqMech PnlIdecIaqMech::ContInf
#define StatShrIdecIaqMech PnlIdecIaqMech::StatShr
#define TagIdecIaqMech PnlIdecIaqMech::Tag

#define DpchAppIdecIaqMechData PnlIdecIaqMech::DpchAppData
#define DpchAppIdecIaqMechDo PnlIdecIaqMech::DpchAppDo
#define DpchEngIdecIaqMechData PnlIdecIaqMech::DpchEngData
#define DpchEngIdecIaqMechLive PnlIdecIaqMech::DpchEngLive

/**
  * PnlIdecIaqMech
  */
class PnlIdecIaqMech : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecIaqMechDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTMASTERCLICK = 3;
		static const uint BUTTHECCWCLICK = 4;
		static const uint BUTTHECCWSTMDN = 5;
		static const uint BUTTHECCWSTMUP = 6;
		static const uint BUTTHECWSTMDN = 7;
		static const uint BUTTHECWSTMUP = 8;
		static const uint BUTTHECWCLICK = 9;
		static const uint BUTPHICCWCLICK = 10;
		static const uint BUTPHICCWSTMDN = 11;
		static const uint BUTPHICCWSTMUP = 12;
		static const uint BUTPHICWSTMDN = 13;
		static const uint BUTPHICWSTMUP = 14;
		static const uint BUTPHICWCLICK = 15;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVMode (full: VecVIdecIaqMechMode)
		*/
	class VecVMode {

	public:
		static const uint MANUAL = 1;
		static const uint INTACT = 2;
		static const uint AUTO = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVSge (full: VecVIdecIaqMechSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContIac (full: ContIacIdecIaqMech)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPMOD = 1;
		static const uint SLDTVV = 2;
		static const uint CUSTHEANS = 3;
		static const uint CUSPHIANS = 4;

	public:
		ContIac(const uint numFPupMod = 2, const double SldTvv = 0.0, const double CusTheAns = 0.0, const double CusPhiAns = 0.0);

	public:
		uint numFPupMod;
		double SldTvv;
		double CusTheAns;
		double CusPhiAns;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqMech)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTTHEANG = 2;
		static const uint TXTTHERPM = 3;
		static const uint NUMFCSITHESTE = 4;
		static const uint BUTTHECCWON = 5;
		static const uint BUTTHECWON = 6;
		static const uint TXTPHIANG = 7;
		static const uint TXTPHIRPM = 8;
		static const uint NUMFCSIPHISTE = 9;
		static const uint BUTPHICCWON = 10;
		static const uint BUTPHICWON = 11;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtTheAng = "", const string& TxtTheRpm = "", const uint numFCsiTheSte = 1, const bool ButTheCcwOn = false, const bool ButTheCwOn = false, const string& TxtPhiAng = "", const string& TxtPhiRpm = "", const uint numFCsiPhiSte = 1, const bool ButPhiCcwOn = false, const bool ButPhiCwOn = false);

	public:
		bool ButMasterOn;
		string TxtTheAng;
		string TxtTheRpm;
		uint numFCsiTheSte;
		bool ButTheCcwOn;
		bool ButTheCwOn;
		string TxtPhiAng;
		string TxtPhiRpm;
		uint numFCsiPhiSte;
		bool ButPhiCcwOn;
		bool ButPhiCwOn;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatShr (full: StatShrIdecIaqMech)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint SLDTVVAVAIL = 2;
		static const uint SLDTVVMIN = 3;
		static const uint SLDTVVMAX = 4;
		static const uint CUSTHEANSACTIVE = 5;
		static const uint BUTTHECCWACTIVE = 6;
		static const uint BUTTHECCWSTACTIVE = 7;
		static const uint BUTTHECWSTACTIVE = 8;
		static const uint BUTTHECWACTIVE = 9;
		static const uint CUSPHIANSACTIVE = 10;
		static const uint BUTPHICCWACTIVE = 11;
		static const uint BUTPHICCWSTACTIVE = 12;
		static const uint BUTPHICWSTACTIVE = 13;
		static const uint BUTPHICWACTIVE = 14;
		static const uint CUSTHEANSMIN = 15;
		static const uint CUSTHEANSMAX = 16;
		static const uint CUSPHIANSMIN = 17;
		static const uint CUSPHIANSMAX = 18;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool SldTvvAvail = true, const double SldTvvMin = -10.0, const double SldTvvMax = 10.0, const bool CusTheAnsActive = true, const bool ButTheCcwActive = true, const bool ButTheCcwstActive = true, const bool ButTheCwstActive = true, const bool ButTheCwActive = true, const bool CusPhiAnsActive = true, const bool ButPhiCcwActive = true, const bool ButPhiCcwstActive = true, const bool ButPhiCwstActive = true, const bool ButPhiCwActive = true, const double CusTheAnsMin = -60.0, const double CusTheAnsMax = 60.0, const double CusPhiAnsMin = -45.0, const double CusPhiAnsMax = 45.0);

	public:
		uint ixIdecVExpstate;
		bool SldTvvAvail;
		double SldTvvMin;
		double SldTvvMax;
		bool CusTheAnsActive;
		bool ButTheCcwActive;
		bool ButTheCcwstActive;
		bool ButTheCwstActive;
		bool ButTheCwActive;
		bool CusPhiAnsActive;
		bool ButPhiCcwActive;
		bool ButPhiCcwstActive;
		bool ButPhiCwstActive;
		bool ButPhiCwActive;
		double CusTheAnsMin;
		double CusTheAnsMax;
		double CusPhiAnsMin;
		double CusPhiAnsMax;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecIaqMech)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqMechData)
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
		* DpchAppDo (full: DpchAppIdecIaqMechDo)
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
		* DpchEngData (full: DpchEngIdecIaqMechData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIPHISTE = 4;
		static const uint FEEDFCSITHESTE = 5;
		static const uint FEEDFPUPMOD = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;
		static const uint ALL = 9;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFCsiPhiSte = NULL, Feed* feedFCsiTheSte = NULL, Feed* feedFPupMod = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiPhiSte;
		Feed feedFCsiTheSte;
		Feed feedFPupMod;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	/**
		* DpchEngLive (full: DpchEngIdecIaqMechLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint ALL = 3;

	public:
		DpchEngLive(const ubigint jref = 0, ContInf* continf = NULL, const set<uint>& mask = {NONE});

	public:
		ContInf continf;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalSldTvvAvail(DbsIdec* dbsidec);
	bool evalCusTheAnsActive(DbsIdec* dbsidec);
	bool evalButTheCcwActive(DbsIdec* dbsidec);
	bool evalButTheCcwstActive(DbsIdec* dbsidec);
	bool evalButTheCwstActive(DbsIdec* dbsidec);
	bool evalButTheCwActive(DbsIdec* dbsidec);
	bool evalCusPhiAnsActive(DbsIdec* dbsidec);
	bool evalButPhiCcwActive(DbsIdec* dbsidec);
	bool evalButPhiCcwstActive(DbsIdec* dbsidec);
	bool evalButPhiCwstActive(DbsIdec* dbsidec);
	bool evalButPhiCwActive(DbsIdec* dbsidec);

public:
	PnlIdecIaqMech(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecIaqMech();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFCsiPhiSte;
	Feed feedFCsiTheSte;
	Feed feedFPupMod;

	JobIdecMechctl* jobmechctl;

	// IP custVar --- INSERT

public:
	// IP cust --- IBEGIN
	void refreshLive(DbsIdec* dbsidec, set<uint>& moditems);
	// IP cust --- IEND

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge, DpchEngIdec** dpcheng = NULL);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButRegularizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMinimizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMasterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheCcwClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheCcwstMdn(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheCcwstMup(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheCwstMdn(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheCwstMup(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTheCwClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiCcwClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiCcwstMdn(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiCcwstMup(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiCwstMdn(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiCwstMup(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPhiCwClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


