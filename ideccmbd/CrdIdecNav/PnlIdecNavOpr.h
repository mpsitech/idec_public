/**
  * \file PnlIdecNavOpr.h
  * job handler for job PnlIdecNavOpr (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVOPR_H
#define PNLIDECNAVOPR_H

// IP custInclude --- INSERT

#define VecVIdecNavOprDo PnlIdecNavOpr::VecVDo

#define ContIacIdecNavOpr PnlIdecNavOpr::ContIac
#define StatAppIdecNavOpr PnlIdecNavOpr::StatApp
#define StatShrIdecNavOpr PnlIdecNavOpr::StatShr
#define TagIdecNavOpr PnlIdecNavOpr::Tag

#define DpchAppIdecNavOprData PnlIdecNavOpr::DpchAppData
#define DpchAppIdecNavOprDo PnlIdecNavOpr::DpchAppDo
#define DpchEngIdecNavOprData PnlIdecNavOpr::DpchEngData

/**
  * PnlIdecNavOpr
  */
class PnlIdecNavOpr : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecNavOprDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMISVIEWCLICK = 1;
		static const uint BUTMISNEWCRDCLICK = 2;
		static const uint BUTTOUVIEWCLICK = 3;
		static const uint BUTTOUNEWCRDCLICK = 4;
		static const uint BUTIAQNEWCRDCLICK = 5;
		static const uint BUTAD1NEWCRDCLICK = 6;
		static const uint BUTFILVIEWCLICK = 7;
		static const uint BUTFILNEWCRDCLICK = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecNavOpr)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFLSTMIS = 1;
		static const uint NUMFLSTTOU = 2;
		static const uint NUMFLSTFIL = 3;

	public:
		ContIac(const uint numFLstMis = 1, const uint numFLstTou = 1, const uint numFLstFil = 1);

	public:
		uint numFLstMis;
		uint numFLstTou;
		uint numFLstFil;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
		* StatApp (full: StatAppIdecNavOpr)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool LstMisAlt = true, const bool LstTouAlt = true, const bool LstFilAlt = true, const uint LstMisNumFirstdisp = 1, const uint LstTouNumFirstdisp = 1, const uint LstFilNumFirstdisp = 1);
	};

	/**
		* StatShr (full: StatShrIdecNavOpr)
		*/
	class StatShr : public Block {

	public:
		static const uint LSTMISAVAIL = 1;
		static const uint BUTMISVIEWACTIVE = 2;
		static const uint LSTTOUAVAIL = 3;
		static const uint BUTTOUVIEWACTIVE = 4;
		static const uint BUTTOUNEWCRDACTIVE = 5;
		static const uint BUTIAQNEWCRDACTIVE = 6;
		static const uint BUTAD1NEWCRDACTIVE = 7;
		static const uint LSTFILAVAIL = 8;
		static const uint BUTFILVIEWACTIVE = 9;
		static const uint BUTFILNEWCRDACTIVE = 10;

	public:
		StatShr(const bool LstMisAvail = true, const bool ButMisViewActive = true, const bool LstTouAvail = true, const bool ButTouViewActive = true, const bool ButTouNewcrdActive = true, const bool ButIaqNewcrdActive = true, const bool ButAd1NewcrdActive = true, const bool LstFilAvail = true, const bool ButFilViewActive = true, const bool ButFilNewcrdActive = true);

	public:
		bool LstMisAvail;
		bool ButMisViewActive;
		bool LstTouAvail;
		bool ButTouViewActive;
		bool ButTouNewcrdActive;
		bool ButIaqNewcrdActive;
		bool ButAd1NewcrdActive;
		bool LstFilAvail;
		bool ButFilViewActive;
		bool ButFilNewcrdActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecNavOpr)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecNavOprData)
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
		* DpchAppDo (full: DpchAppIdecNavOprDo)
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
		* DpchEngData (full: DpchEngIdecNavOprData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint FEEDFLSTFIL = 3;
		static const uint FEEDFLSTMIS = 4;
		static const uint FEEDFLSTTOU = 5;
		static const uint STATAPP = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;
		static const uint ALL = 9;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, Feed* feedFLstFil = NULL, Feed* feedFLstMis = NULL, Feed* feedFLstTou = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		Feed feedFLstFil;
		Feed feedFLstMis;
		Feed feedFLstTou;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalLstMisAvail(DbsIdec* dbsidec);
	bool evalButMisViewActive(DbsIdec* dbsidec);
	bool evalLstTouAvail(DbsIdec* dbsidec);
	bool evalButTouViewActive(DbsIdec* dbsidec);
	bool evalButTouNewcrdActive(DbsIdec* dbsidec);
	bool evalButIaqNewcrdActive(DbsIdec* dbsidec);
	bool evalButAd1NewcrdActive(DbsIdec* dbsidec);
	bool evalLstFilAvail(DbsIdec* dbsidec);
	bool evalButFilViewActive(DbsIdec* dbsidec);
	bool evalButFilNewcrdActive(DbsIdec* dbsidec);

public:
	PnlIdecNavOpr(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecNavOpr();

public:
	ContIac contiac;
	StatShr statshr;

	Feed feedFLstFil;
	Feed feedFLstMis;
	Feed feedFLstTou;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshLstMis(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshMis(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshLstTou(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshTou(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshLstFil(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshFil(DbsIdec* dbsidec, set<uint>& moditems);
	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMisViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMisNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTouViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTouNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButIaqNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButAd1NewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButFilViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButFilNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecHusrRunvMod_crdUsrEq(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv);
};

#endif

