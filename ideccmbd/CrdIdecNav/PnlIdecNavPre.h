/**
  * \file PnlIdecNavPre.h
  * job handler for job PnlIdecNavPre (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVPRE_H
#define PNLIDECNAVPRE_H

// IP custInclude --- INSERT

#define VecVIdecNavPreDo PnlIdecNavPre::VecVDo

#define ContInfIdecNavPre PnlIdecNavPre::ContInf
#define StatShrIdecNavPre PnlIdecNavPre::StatShr
#define TagIdecNavPre PnlIdecNavPre::Tag

#define DpchAppIdecNavPreDo PnlIdecNavPre::DpchAppDo
#define DpchEngIdecNavPreData PnlIdecNavPre::DpchEngData

/**
  * PnlIdecNavPre
  */
class PnlIdecNavPre : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecNavPreDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMISREMOVECLICK = 1;
		static const uint BUTTOUREMOVECLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecNavPre)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTMIS = 1;
		static const uint TXTTOU = 2;

	public:
		ContInf(const string& TxtMis = "", const string& TxtTou = "");

	public:
		string TxtMis;
		string TxtTou;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatShr (full: StatShrIdecNavPre)
		*/
	class StatShr : public Block {

	public:
		static const uint TXTMISAVAIL = 1;
		static const uint TXTTOUAVAIL = 2;

	public:
		StatShr(const bool TxtMisAvail = true, const bool TxtTouAvail = true);

	public:
		bool TxtMisAvail;
		bool TxtTouAvail;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecNavPre)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecNavPreDo)
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
		* DpchEngData (full: DpchEngIdecNavPreData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint STATSHR = 3;
		static const uint TAG = 4;
		static const uint ALL = 5;

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

	bool evalTxtMisAvail(DbsIdec* dbsidec);
	bool evalTxtTouAvail(DbsIdec* dbsidec);

public:
	PnlIdecNavPre(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecNavPre();

public:
	ContInf continf;
	StatShr statshr;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMisRemoveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButTouRemoveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

};

#endif

