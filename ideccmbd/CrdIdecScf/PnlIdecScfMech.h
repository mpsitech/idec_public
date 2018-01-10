/**
  * \file PnlIdecScfMech.h
  * job handler for job PnlIdecScfMech (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFMECH_H
#define PNLIDECSCFMECH_H

// IP custInclude --- INSERT

#include "JobIdecMechctl.h"

#define VecVIdecScfMechDo PnlIdecScfMech::VecVDo
#define VecVIdecScfMechSge PnlIdecScfMech::VecVSge

#define ContIacIdecScfMech PnlIdecScfMech::ContIac
#define ContInfIdecScfMech PnlIdecScfMech::ContInf
#define StatShrIdecScfMech PnlIdecScfMech::StatShr
#define TagIdecScfMech PnlIdecScfMech::Tag

#define DpchAppIdecScfMechData PnlIdecScfMech::DpchAppData
#define DpchAppIdecScfMechDo PnlIdecScfMech::DpchAppDo
#define DpchEngIdecScfMechData PnlIdecScfMech::DpchEngData
#define DpchEngIdecScfMechLive PnlIdecScfMech::DpchEngLive

/**
  * PnlIdecScfMech
  */
class PnlIdecScfMech : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfMechDo)
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
		* VecVSge (full: VecVIdecScfMechSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContIac (full: ContIacIdecScfMech)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFTGR = 1;
		static const uint SLDTLL = 2;
		static const uint SLDTUL = 3;
		static const uint TXFPGR = 4;
		static const uint SLDPLL = 5;
		static const uint SLDPUL = 6;
		static const uint CUSTHEANS = 7;
		static const uint CUSPHIANS = 8;

	public:
		ContIac(const string& TxfTgr = "", const double SldTll = 0.0, const double SldTul = 0.0, const string& TxfPgr = "", const double SldPll = 0.0, const double SldPul = 0.0, const double CusTheAns = 0.0, const double CusPhiAns = 0.0);

	public:
		string TxfTgr;
		double SldTll;
		double SldTul;
		string TxfPgr;
		double SldPll;
		double SldPul;
		double CusTheAns;
		double CusPhiAns;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfMech)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTORSALPHA = 2;
		static const uint TXTORSBETA = 3;
		static const uint TXTTHEANG = 4;
		static const uint TXTTHERPM = 5;
		static const uint NUMFCSITHESTE = 6;
		static const uint BUTTHECCWON = 7;
		static const uint BUTTHECWON = 8;
		static const uint TXTPHIANG = 9;
		static const uint TXTPHIRPM = 10;
		static const uint NUMFCSIPHISTE = 11;
		static const uint BUTPHICCWON = 12;
		static const uint BUTPHICWON = 13;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtOrsAlpha = "", const string& TxtOrsBeta = "", const string& TxtTheAng = "", const string& TxtTheRpm = "", const uint numFCsiTheSte = 1, const bool ButTheCcwOn = false, const bool ButTheCwOn = false, const string& TxtPhiAng = "", const string& TxtPhiRpm = "", const uint numFCsiPhiSte = 1, const bool ButPhiCcwOn = false, const bool ButPhiCwOn = false);

	public:
		bool ButMasterOn;
		string TxtOrsAlpha;
		string TxtOrsBeta;
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
		* StatShr (full: StatShrIdecScfMech)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint CUSTHEANSACTIVE = 2;
		static const uint BUTTHECCWACTIVE = 3;
		static const uint BUTTHECCWSTACTIVE = 4;
		static const uint BUTTHECWSTACTIVE = 5;
		static const uint BUTTHECWACTIVE = 6;
		static const uint TXFTGRACTIVE = 7;
		static const uint SLDTLLACTIVE = 8;
		static const uint SLDTLLMIN = 9;
		static const uint SLDTLLMAX = 10;
		static const uint SLDTULACTIVE = 11;
		static const uint SLDTULMIN = 12;
		static const uint SLDTULMAX = 13;
		static const uint CUSPHIANSACTIVE = 14;
		static const uint BUTPHICCWACTIVE = 15;
		static const uint BUTPHICCWSTACTIVE = 16;
		static const uint BUTPHICWSTACTIVE = 17;
		static const uint BUTPHICWACTIVE = 18;
		static const uint TXFPGRACTIVE = 19;
		static const uint SLDPLLACTIVE = 20;
		static const uint SLDPLLMIN = 21;
		static const uint SLDPLLMAX = 22;
		static const uint SLDPULACTIVE = 23;
		static const uint SLDPULMIN = 24;
		static const uint SLDPULMAX = 25;
		static const uint CUSTHEANSMIN = 26;
		static const uint CUSTHEANSMAX = 27;
		static const uint CUSPHIANSMIN = 28;
		static const uint CUSPHIANSMAX = 29;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool CusTheAnsActive = true, const bool ButTheCcwActive = true, const bool ButTheCcwstActive = true, const bool ButTheCwstActive = true, const bool ButTheCwActive = true, const bool TxfTgrActive = true, const bool SldTllActive = true, const double SldTllMin = -60.0, const double SldTllMax = 60.0, const bool SldTulActive = true, const double SldTulMin = -60.0, const double SldTulMax = 60.0, const bool CusPhiAnsActive = true, const bool ButPhiCcwActive = true, const bool ButPhiCcwstActive = true, const bool ButPhiCwstActive = true, const bool ButPhiCwActive = true, const bool TxfPgrActive = true, const bool SldPllActive = true, const double SldPllMin = -45.0, const double SldPllMax = 45.0, const bool SldPulActive = true, const double SldPulMin = -45.0, const double SldPulMax = 45.0, const double CusTheAnsMin = -60.0, const double CusTheAnsMax = 60.0, const double CusPhiAnsMin = -45.0, const double CusPhiAnsMax = 45.0);

	public:
		uint ixIdecVExpstate;
		bool CusTheAnsActive;
		bool ButTheCcwActive;
		bool ButTheCcwstActive;
		bool ButTheCwstActive;
		bool ButTheCwActive;
		bool TxfTgrActive;
		bool SldTllActive;
		double SldTllMin;
		double SldTllMax;
		bool SldTulActive;
		double SldTulMin;
		double SldTulMax;
		bool CusPhiAnsActive;
		bool ButPhiCcwActive;
		bool ButPhiCcwstActive;
		bool ButPhiCwstActive;
		bool ButPhiCwActive;
		bool TxfPgrActive;
		bool SldPllActive;
		double SldPllMin;
		double SldPllMax;
		bool SldPulActive;
		double SldPulMin;
		double SldPulMax;
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
		* Tag (full: TagIdecScfMech)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfMechData)
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
		* DpchAppDo (full: DpchAppIdecScfMechDo)
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
		* DpchEngData (full: DpchEngIdecScfMechData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIPHISTE = 4;
		static const uint FEEDFCSITHESTE = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFCsiPhiSte = NULL, Feed* feedFCsiTheSte = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiPhiSte;
		Feed feedFCsiTheSte;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	/**
		* DpchEngLive (full: DpchEngIdecScfMechLive)
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

	bool evalCusTheAnsActive(DbsIdec* dbsidec);
	bool evalButTheCcwActive(DbsIdec* dbsidec);
	bool evalButTheCcwstActive(DbsIdec* dbsidec);
	bool evalButTheCwstActive(DbsIdec* dbsidec);
	bool evalButTheCwActive(DbsIdec* dbsidec);
	bool evalTxfTgrActive(DbsIdec* dbsidec);
	bool evalSldTllActive(DbsIdec* dbsidec);
	bool evalSldTulActive(DbsIdec* dbsidec);
	bool evalCusPhiAnsActive(DbsIdec* dbsidec);
	bool evalButPhiCcwActive(DbsIdec* dbsidec);
	bool evalButPhiCcwstActive(DbsIdec* dbsidec);
	bool evalButPhiCwstActive(DbsIdec* dbsidec);
	bool evalButPhiCwActive(DbsIdec* dbsidec);
	bool evalTxfPgrActive(DbsIdec* dbsidec);
	bool evalSldPllActive(DbsIdec* dbsidec);
	bool evalSldPulActive(DbsIdec* dbsidec);

public:
	PnlIdecScfMech(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfMech();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFCsiPhiSte;
	Feed feedFCsiTheSte;

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
	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


