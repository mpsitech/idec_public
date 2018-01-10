/**
  * \file DlgIdecNavLoaini.h
  * job handler for job DlgIdecNavLoaini (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DLGIDECNAVLOAINI_H
#define DLGIDECNAVLOAINI_H

// IP custInclude --- IBEGIN
#include <sys/types.h>
#include <dirent.h>
// IP custInclude --- IEND

#include "IexIdecIni.h"

#define VecVDlgIdecNavLoainiDit DlgIdecNavLoaini::VecVDit
#define VecVDlgIdecNavLoainiDo DlgIdecNavLoaini::VecVDo
#define VecVDlgIdecNavLoainiDoImp DlgIdecNavLoaini::VecVDoImp
#define VecVDlgIdecNavLoainiSge DlgIdecNavLoaini::VecVSge

#define ContIacDlgIdecNavLoaini DlgIdecNavLoaini::ContIac
#define ContInfDlgIdecNavLoaini DlgIdecNavLoaini::ContInf
#define ContInfDlgIdecNavLoainiImp DlgIdecNavLoaini::ContInfImp
#define StatAppDlgIdecNavLoaini DlgIdecNavLoaini::StatApp
#define StatShrDlgIdecNavLoaini DlgIdecNavLoaini::StatShr
#define StatShrDlgIdecNavLoainiAcv DlgIdecNavLoaini::StatShrAcv
#define StatShrDlgIdecNavLoainiIfi DlgIdecNavLoaini::StatShrIfi
#define StatShrDlgIdecNavLoainiImp DlgIdecNavLoaini::StatShrImp
#define StatShrDlgIdecNavLoainiLfi DlgIdecNavLoaini::StatShrLfi
#define TagDlgIdecNavLoaini DlgIdecNavLoaini::Tag
#define TagDlgIdecNavLoainiAcv DlgIdecNavLoaini::TagAcv
#define TagDlgIdecNavLoainiIfi DlgIdecNavLoaini::TagIfi
#define TagDlgIdecNavLoainiImp DlgIdecNavLoaini::TagImp
#define TagDlgIdecNavLoainiLfi DlgIdecNavLoaini::TagLfi

#define DpchAppDlgIdecNavLoainiData DlgIdecNavLoaini::DpchAppData
#define DpchAppDlgIdecNavLoainiDo DlgIdecNavLoaini::DpchAppDo
#define DpchEngDlgIdecNavLoainiData DlgIdecNavLoaini::DpchEngData

/**
  * DlgIdecNavLoaini
  */
class DlgIdecNavLoaini : public JobIdec {

public:
	/**
		* VecVDit (full: VecVDlgIdecNavLoainiDit)
		*/
	class VecVDit {

	public:
		static const uint IFI = 1;
		static const uint IMP = 2;
		static const uint ACV = 3;
		static const uint LFI = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVDo (full: VecVDlgIdecNavLoainiDo)
		*/
	class VecVDo {

	public:
		static const uint BUTDNECLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVDoImp (full: VecVDlgIdecNavLoainiDoImp)
		*/
	class VecVDoImp {

	public:
		static const uint BUTRUNCLICK = 1;
		static const uint BUTSTOCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVDlgIdecNavLoainiSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint PRSIDLE = 2;
		static const uint PARSE = 3;
		static const uint ALRIDECPER = 4;
		static const uint PRSDONE = 5;
		static const uint IMPIDLE = 6;
		static const uint IMPORT = 7;
		static const uint IMPDONE = 8;
		static const uint UPKIDLE = 9;
		static const uint UNPACK = 10;
		static const uint DONE = 11;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContIac (full: ContIacDlgIdecNavLoaini)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFDSE = 1;

	public:
		ContIac(const uint numFDse = 1);

	public:
		uint numFDse;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfDlgIdecNavLoaini)
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
	  * ContInfImp (full: ContInfDlgIdecNavLoainiImp)
	  */
	class ContInfImp : public Block {

	public:
		static const uint TXTPRG = 1;

	public:
		ContInfImp(const string& TxtPrg = "");

	public:
		string TxtPrg;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInfImp* comp);
		set<uint> diff(const ContInfImp* comp);
	};

	/**
		* StatApp (full: StatAppDlgIdecNavLoaini)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const bool initdone = false, const string& shortMenu = "");
	};

	/**
		* StatShr (full: StatShrDlgIdecNavLoaini)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTDNEACTIVE = 1;

	public:
		StatShr(const bool ButDneActive = true);

	public:
		bool ButDneActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* StatShrAcv (full: StatShrDlgIdecNavLoainiAcv)
		*/
	class StatShrAcv : public Block {

	public:
		static const uint ULDACTIVE = 1;

	public:
		StatShrAcv(const bool UldActive = true);

	public:
		bool UldActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShrAcv* comp);
		set<uint> diff(const StatShrAcv* comp);
	};

	/**
		* StatShrIfi (full: StatShrDlgIdecNavLoainiIfi)
		*/
	class StatShrIfi : public Block {

	public:
		static const uint ULDACTIVE = 1;

	public:
		StatShrIfi(const bool UldActive = true);

	public:
		bool UldActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShrIfi* comp);
		set<uint> diff(const StatShrIfi* comp);
	};

	/**
		* StatShrImp (full: StatShrDlgIdecNavLoainiImp)
		*/
	class StatShrImp : public Block {

	public:
		static const uint BUTRUNACTIVE = 1;
		static const uint BUTSTOACTIVE = 2;

	public:
		StatShrImp(const bool ButRunActive = true, const bool ButStoActive = true);

	public:
		bool ButRunActive;
		bool ButStoActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShrImp* comp);
		set<uint> diff(const StatShrImp* comp);
	};

	/**
		* StatShrLfi (full: StatShrDlgIdecNavLoainiLfi)
		*/
	class StatShrLfi : public Block {

	public:
		static const uint DLDACTIVE = 1;

	public:
		StatShrLfi(const bool DldActive = true);

	public:
		bool DldActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShrLfi* comp);
		set<uint> diff(const StatShrLfi* comp);
	};

	/**
		* Tag (full: TagDlgIdecNavLoaini)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* TagAcv (full: TagDlgIdecNavLoainiAcv)
		*/
	class TagAcv {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* TagIfi (full: TagDlgIdecNavLoainiIfi)
		*/
	class TagIfi {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* TagImp (full: TagDlgIdecNavLoainiImp)
		*/
	class TagImp {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* TagLfi (full: TagDlgIdecNavLoainiLfi)
		*/
	class TagLfi {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppDlgIdecNavLoainiData)
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
		* DpchAppDo (full: DpchAppDlgIdecNavLoainiDo)
		*/
	class DpchAppDo : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint IXVDO = 2;
		static const uint IXVDOIMP = 3;

	public:
		DpchAppDo();

	public:
		uint ixVDo;
		uint ixVDoImp;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchEngData (full: DpchEngDlgIdecNavLoainiData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint CONTINFIMP = 4;
		static const uint FEEDFDSE = 5;
		static const uint FEEDFSGE = 6;
		static const uint STATAPP = 7;
		static const uint STATSHR = 8;
		static const uint STATSHRACV = 9;
		static const uint STATSHRIFI = 10;
		static const uint STATSHRIMP = 11;
		static const uint STATSHRLFI = 12;
		static const uint TAG = 13;
		static const uint TAGACV = 14;
		static const uint TAGIFI = 15;
		static const uint TAGIMP = 16;
		static const uint TAGLFI = 17;
		static const uint ALL = 18;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, ContInfImp* continfimp = NULL, Feed* feedFDse = NULL, Feed* feedFSge = NULL, StatShr* statshr = NULL, StatShrAcv* statshracv = NULL, StatShrIfi* statshrifi = NULL, StatShrImp* statshrimp = NULL, StatShrLfi* statshrlfi = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		ContInfImp continfimp;
		Feed feedFDse;
		Feed feedFSge;
		StatShr statshr;
		StatShrAcv statshracv;
		StatShrIfi statshrifi;
		StatShrImp statshrimp;
		StatShrLfi statshrlfi;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalIfiUldActive(DbsIdec* dbsidec);
	bool evalImpButRunActive(DbsIdec* dbsidec);
	bool evalImpButStoActive(DbsIdec* dbsidec);
	bool evalAcvUldActive(DbsIdec* dbsidec);
	bool evalLfiDldActive(DbsIdec* dbsidec);
	bool evalButDneActive(DbsIdec* dbsidec);

public:
	DlgIdecNavLoaini(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~DlgIdecNavLoaini();

public:
	ContIac contiac;
	ContInf continf;
	ContInfImp continfimp;
	StatShr statshr;
	StatShrAcv statshracv;
	StatShrIfi statshrifi;
	StatShrImp statshrimp;
	StatShrLfi statshrlfi;

	Feed feedFMcbAlert;
	Feed feedFDse;
	Feed feedFSge;

	IexIdecIni* iex;

	uint ixVDit;

	// IP custVar --- IBEGIN
	string infilename;
	// IP custVar --- IEND

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshIfi(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshImp(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshAcv(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshLfi(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge, DpchEngIdec** dpcheng = NULL);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgePrsidle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePrsidle(DbsIdec* dbsidec);
	uint enterSgeParse(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeParse(DbsIdec* dbsidec);
	uint enterSgeAlridecper(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlridecper(DbsIdec* dbsidec);
	uint enterSgePrsdone(DbsIdec* dbsidec, const bool reenter);
	void leaveSgePrsdone(DbsIdec* dbsidec);
	uint enterSgeImpidle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeImpidle(DbsIdec* dbsidec);
	uint enterSgeImport(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeImport(DbsIdec* dbsidec);
	uint enterSgeImpdone(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeImpdone(DbsIdec* dbsidec);
	uint enterSgeUpkidle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeUpkidle(DbsIdec* dbsidec);
	uint enterSgeUnpack(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeUnpack(DbsIdec* dbsidec);
	uint enterSgeDone(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeDone(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButDneClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleDpchAppDoImpButRunClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoImpButStoClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleUpload(DbsIdec* dbsidec, const string& filename);
	string handleDownload(DbsIdec* dbsidec);
	void handleTimer(DbsIdec* dbsidec, const string& sref);

};

#endif


