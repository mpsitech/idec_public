/**
  * \file PnlIdecNavMaint.h
  * job handler for job PnlIdecNavMaint (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVMAINT_H
#define PNLIDECNAVMAINT_H

// IP custInclude --- INSERT

#define VecVIdecNavMaintDo PnlIdecNavMaint::VecVDo

#define ContIacIdecNavMaint PnlIdecNavMaint::ContIac
#define StatAppIdecNavMaint PnlIdecNavMaint::StatApp
#define StatShrIdecNavMaint PnlIdecNavMaint::StatShr
#define TagIdecNavMaint PnlIdecNavMaint::Tag

#define DpchAppIdecNavMaintData PnlIdecNavMaint::DpchAppData
#define DpchAppIdecNavMaintDo PnlIdecNavMaint::DpchAppDo
#define DpchEngIdecNavMaintData PnlIdecNavMaint::DpchEngData

/**
  * PnlIdecNavMaint
  */
class PnlIdecNavMaint : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecNavMaintDo)
		*/
	class VecVDo {

	public:
		static const uint BUTUSGVIEWCLICK = 1;
		static const uint BUTUSGNEWCRDCLICK = 2;
		static const uint BUTUSRVIEWCLICK = 3;
		static const uint BUTUSRNEWCRDCLICK = 4;
		static const uint BUTSCFNEWCRDCLICK = 5;
		static const uint BUTUTLNEWCRDCLICK = 6;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecNavMaint)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFLSTUSG = 1;
		static const uint NUMFLSTUSR = 2;

	public:
		ContIac(const uint numFLstUsg = 1, const uint numFLstUsr = 1);

	public:
		uint numFLstUsg;
		uint numFLstUsr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
		* StatApp (full: StatAppIdecNavMaint)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool LstUsgAlt = true, const bool LstUsrAlt = true, const uint LstUsgNumFirstdisp = 1, const uint LstUsrNumFirstdisp = 1);
	};

	/**
		* StatShr (full: StatShrIdecNavMaint)
		*/
	class StatShr : public Block {

	public:
		static const uint LSTUSGAVAIL = 1;
		static const uint BUTUSGVIEWACTIVE = 2;
		static const uint LSTUSRAVAIL = 3;
		static const uint BUTUSRVIEWACTIVE = 4;

	public:
		StatShr(const bool LstUsgAvail = true, const bool ButUsgViewActive = true, const bool LstUsrAvail = true, const bool ButUsrViewActive = true);

	public:
		bool LstUsgAvail;
		bool ButUsgViewActive;
		bool LstUsrAvail;
		bool ButUsrViewActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecNavMaint)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecNavMaintData)
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
		* DpchAppDo (full: DpchAppIdecNavMaintDo)
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
		* DpchEngData (full: DpchEngIdecNavMaintData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint FEEDFLSTUSG = 3;
		static const uint FEEDFLSTUSR = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, Feed* feedFLstUsg = NULL, Feed* feedFLstUsr = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		Feed feedFLstUsg;
		Feed feedFLstUsr;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalLstUsgAvail(DbsIdec* dbsidec);
	bool evalButUsgViewActive(DbsIdec* dbsidec);
	bool evalLstUsrAvail(DbsIdec* dbsidec);
	bool evalButUsrViewActive(DbsIdec* dbsidec);

public:
	PnlIdecNavMaint(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecNavMaint();

public:
	ContIac contiac;
	StatShr statshr;

	Feed feedFLstUsg;
	Feed feedFLstUsr;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshLstUsg(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshUsg(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshLstUsr(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshUsr(DbsIdec* dbsidec, set<uint>& moditems);
	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButUsgViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButUsgNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButUsrViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButUsrNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButScfNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButUtlNewcrdClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecHusrRunvMod_crdUsrEq(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv);
};

#endif

