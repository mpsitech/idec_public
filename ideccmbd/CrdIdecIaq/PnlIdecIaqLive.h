/**
  * \file PnlIdecIaqLive.h
  * job handler for job PnlIdecIaqLive (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQLIVE_H
#define PNLIDECIAQLIVE_H

// IP custInclude --- INSERT

#include "JobIdecFusion.h"
#include "JobIdecLwiracq.h"
#include "JobIdecRecord.h"
#include "JobIdecStereo.h"
#include "JobIdecTrigger.h"
#include "JobIdecVislacq.h"
#include "JobIdecVisracq.h"

#define VecVIdecIaqLiveDo PnlIdecIaqLive::VecVDo
#define VecVIdecIaqLiveSge PnlIdecIaqLive::VecVSge
#define VecVIdecIaqLiveSource PnlIdecIaqLive::VecVSource

#define ContIacIdecIaqLive PnlIdecIaqLive::ContIac
#define ContInfIdecIaqLive PnlIdecIaqLive::ContInf
#define StatShrIdecIaqLive PnlIdecIaqLive::StatShr
#define TagIdecIaqLive PnlIdecIaqLive::Tag

#define DpchAppIdecIaqLiveData PnlIdecIaqLive::DpchAppData
#define DpchAppIdecIaqLiveDo PnlIdecIaqLive::DpchAppDo
#define DpchEngIdecIaqLiveData PnlIdecIaqLive::DpchEngData
#define DpchEngIdecIaqLiveLive PnlIdecIaqLive::DpchEngLive

/**
  * PnlIdecIaqLive
  */
class PnlIdecIaqLive : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecIaqLiveDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTMASTERCLICK = 3;
		static const uint BUTSNAPCLICK = 4;
		static const uint BUTRECCLICK = 5;
		static const uint BUTPLAYCLICK = 6;
		static const uint BUTSTOPCLICK = 7;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecIaqLiveSge)
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
		* VecVSource (full: VecVIdecIaqLiveSource)
		*/
	class VecVSource {

	public:
		static const uint VISL = 1;
		static const uint VISR = 2;
		static const uint LWIR = 3;
		static const uint STEREO = 4;
		static const uint FUSION = 5;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
	  * ContIac (full: ContIacIdecIaqLive)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPSRC = 1;
		static const uint NUMFPUPRES = 2;
		static const uint CHKGRS = 3;
		static const uint SLDFRR = 4;
		static const uint SLDEXT = 5;

	public:
		ContIac(const uint numFPupSrc = 1, const uint numFPupRes = 1, const bool ChkGrs = false, const double SldFrr = 1.0, const double SldExt = 0.0);

	public:
		uint numFPupSrc;
		uint numFPupRes;
		bool ChkGrs;
		double SldFrr;
		double SldExt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqLive)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTSTE = 2;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtSte = "");

	public:
		bool ButMasterOn;
		string TxtSte;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatShr (full: StatShrIdecIaqLive)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint CUSIMGHEIGHT = 2;
		static const uint CHKGRSAVAIL = 3;
		static const uint SLDCONAVAIL = 4;
		static const uint SLDCONMIN = 5;
		static const uint SLDCONMAX = 6;
		static const uint SLDBRIAVAIL = 7;
		static const uint SLDBRIMIN = 8;
		static const uint SLDBRIMAX = 9;
		static const uint SLDFRRACTIVE = 10;
		static const uint SLDFRRMIN = 11;
		static const uint SLDFRRMAX = 12;
		static const uint SLDFRRRAST = 13;
		static const uint SLDEXTAVAIL = 14;
		static const uint SLDEXTACTIVE = 15;
		static const uint SLDEXTMIN = 16;
		static const uint SLDEXTMAX = 17;
		static const uint SLDEXTRAST = 18;
		static const uint BUTPLAYACTIVE = 19;
		static const uint BUTSTOPACTIVE = 20;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const uint CusImgHeight = 480, const bool ChkGrsAvail = true, const bool SldConAvail = true, const double SldConMin = 1.0, const double SldConMax = 100.0, const bool SldBriAvail = true, const double SldBriMin = 0.0, const double SldBriMax = 1.0, const bool SldFrrActive = true, const double SldFrrMin = 1.0, const double SldFrrMax = 15.0, const double SldFrrRast = 0.1, const bool SldExtAvail = true, const bool SldExtActive = true, const double SldExtMin = 0.01, const double SldExtMax = 1.0, const double SldExtRast = 1.25893, const bool ButPlayActive = true, const bool ButStopActive = true);

	public:
		uint ixIdecVExpstate;
		uint CusImgHeight;
		bool ChkGrsAvail;
		bool SldConAvail;
		double SldConMin;
		double SldConMax;
		bool SldBriAvail;
		double SldBriMin;
		double SldBriMax;
		bool SldFrrActive;
		double SldFrrMin;
		double SldFrrMax;
		double SldFrrRast;
		bool SldExtAvail;
		bool SldExtActive;
		double SldExtMin;
		double SldExtMax;
		double SldExtRast;
		bool ButPlayActive;
		bool ButStopActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecIaqLive)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqLiveData)
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
		* DpchAppDo (full: DpchAppIdecIaqLiveDo)
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
		* DpchEngData (full: DpchEngIdecIaqLiveData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPRES = 4;
		static const uint FEEDFPUPSRC = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupRes = NULL, Feed* feedFPupSrc = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupRes;
		Feed feedFPupSrc;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	/**
		* DpchEngLive (full: DpchEngIdecIaqLiveLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint RGB = 3;
		static const uint RED = 4;
		static const uint GREEN = 5;
		static const uint BLUE = 6;
		static const uint GRAY = 7;
		static const uint DEPTH = 8;
		static const uint ALL = 9;

	public:
		DpchEngLive(const ubigint jref = 0, ContInf* continf = NULL, const vector<utinyint>& rgb = {}, const vector<utinyint>& red = {}, const vector<utinyint>& green = {}, const vector<utinyint>& blue = {}, const vector<usmallint>& gray = {}, const vector<float>& depth = {}, const set<uint>& mask = {NONE});

	public:
		ContInf continf;
		vector<utinyint> rgb;
		vector<utinyint> red;
		vector<utinyint> green;
		vector<utinyint> blue;
		vector<usmallint> gray;
		vector<float> depth;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalChkGrsAvail(DbsIdec* dbsidec);
	bool evalSldConAvail(DbsIdec* dbsidec);
	bool evalSldBriAvail(DbsIdec* dbsidec);
	bool evalSldFrrActive(DbsIdec* dbsidec);
	bool evalSldExtAvail(DbsIdec* dbsidec);
	bool evalSldExtActive(DbsIdec* dbsidec);
	bool evalButPlayActive(DbsIdec* dbsidec);
	bool evalButStopActive(DbsIdec* dbsidec);

public:
	PnlIdecIaqLive(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecIaqLive();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFPupRes;
	Feed feedFPupSrc;

	JobIdecFusion* jobfusion;
	JobIdecLwiracq* joblwiracq;
	JobIdecRecord* jobrecord;
	JobIdecStereo* jobstereo;
	JobIdecTrigger* jobtrigger;
	JobIdecVislacq* jobvislacq;
	JobIdecVisracq* jobvisracq;

	// IP custVar --- IBEGIN
	uint ixVSource;
	
	Snippet* red;
	Snippet* green;
	Snippet* blue;
	Snippet* gray;
	Snippet* depth;
	
	unsigned int fnew;
	double fps;
	// IP custVar --- IEND

public:
	// IP cust --- IBEGIN
	void changeSource(DbsIdec* dbsidec, const uint _ixVSource);

	void refreshLive(DbsIdec* dbsidec, set<uint>& moditems);

	bool started();
	// IP cust --- IEND

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

	void handleDpchAppDoButRegularizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMinimizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMasterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButSnapClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButRecClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButPlayClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButStopClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleTimer(DbsIdec* dbsidec, const string& sref);
	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecImgrdy(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecSptfnd(DbsIdec* dbsidec, const ubigint jrefTrig, const bool boolvalInv);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


