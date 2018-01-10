/**
  * \file DlgIdecMisNew.h
  * job handler for job DlgIdecMisNew (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DLGIDECMISNEW_H
#define DLGIDECMISNEW_H

// IP custInclude --- INSERT

#define VecVDlgIdecMisNewDo DlgIdecMisNew::VecVDo
#define VecVDlgIdecMisNewSge DlgIdecMisNew::VecVSge

#define ContIacDlgIdecMisNew DlgIdecMisNew::ContIac
#define ContInfDlgIdecMisNew DlgIdecMisNew::ContInf
#define StatAppDlgIdecMisNew DlgIdecMisNew::StatApp
#define StatShrDlgIdecMisNew DlgIdecMisNew::StatShr
#define TagDlgIdecMisNew DlgIdecMisNew::Tag

#define DpchAppDlgIdecMisNewData DlgIdecMisNew::DpchAppData
#define DpchAppDlgIdecMisNewDo DlgIdecMisNew::DpchAppDo
#define DpchEngDlgIdecMisNewData DlgIdecMisNew::DpchEngData

/**
  * DlgIdecMisNew
  */
class DlgIdecMisNew : public JobIdec {

public:
	/**
		* VecVDo (full: VecVDlgIdecMisNewDo)
		*/
	class VecVDo {

	public:
		static const uint BUTCNCCLICK = 1;
		static const uint BUTCRECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVDlgIdecMisNewSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint CREATE = 2;
		static const uint DONE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContIac (full: ContIacDlgIdecMisNew)
	  */
	class ContIac : public Block {

	public:
		static const uint DETTXFTIT = 1;
		static const uint NUMFDETPUPCRY = 2;
		static const uint DETTXFREG = 3;
		static const uint DETTXFMUN = 4;

	public:
		ContIac(const string& DetTxfTit = "", const uint numFDetPupCry = 1, const string& DetTxfReg = "", const string& DetTxfMun = "");

	public:
		string DetTxfTit;
		uint numFDetPupCry;
		string DetTxfReg;
		string DetTxfMun;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfDlgIdecMisNew)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;

	public:
		ContInf(const uint numFSge = 1);

	public:
		uint numFSge;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppDlgIdecMisNew)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const string& shortMenu = "");
	};

	/**
		* StatShr (full: StatShrDlgIdecMisNew)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTCNCACTIVE = 1;
		static const uint BUTCREACTIVE = 2;

	public:
		StatShr(const bool ButCncActive = true, const bool ButCreActive = true);

	public:
		bool ButCncActive;
		bool ButCreActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagDlgIdecMisNew)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppDlgIdecMisNewData)
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
		* DpchAppDo (full: DpchAppDlgIdecMisNewDo)
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
		* DpchEngData (full: DpchEngDlgIdecMisNewData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFDETPUPCRY = 4;
		static const uint FEEDFSGE = 5;
		static const uint STATAPP = 6;
		static const uint STATSHR = 7;
		static const uint TAG = 8;
		static const uint ALL = 9;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFDetPupCry = NULL, Feed* feedFSge = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFDetPupCry;
		Feed feedFSge;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButCncActive(DbsIdec* dbsidec);
	bool evalButCreActive(DbsIdec* dbsidec);

public:
	DlgIdecMisNew(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~DlgIdecMisNew();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFDetPupCry;
	Feed feedFSge;

	bool valid;

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
	uint enterSgeCreate(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeCreate(DbsIdec* dbsidec);
	uint enterSgeDone(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeDone(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButCncClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCreClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

};

#endif

