/**
  * \file PnlIdecMisRef1NFile.h
  * job handler for job PnlIdecMisRef1NFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISREF1NFILE_H
#define PNLIDECMISREF1NFILE_H

// IP custInclude --- INSERT

#include "QryIdecMisRef1NFile.h"

#define VecVIdecMisRef1NFileDo PnlIdecMisRef1NFile::VecVDo

#define ContInfIdecMisRef1NFile PnlIdecMisRef1NFile::ContInf
#define StatAppIdecMisRef1NFile PnlIdecMisRef1NFile::StatApp
#define StatShrIdecMisRef1NFile PnlIdecMisRef1NFile::StatShr
#define StgIacIdecMisRef1NFile PnlIdecMisRef1NFile::StgIac
#define TagIdecMisRef1NFile PnlIdecMisRef1NFile::Tag

#define DpchAppIdecMisRef1NFileData PnlIdecMisRef1NFile::DpchAppData
#define DpchAppIdecMisRef1NFileDo PnlIdecMisRef1NFile::DpchAppDo
#define DpchEngIdecMisRef1NFileData PnlIdecMisRef1NFile::DpchEngData

/**
  * PnlIdecMisRef1NFile
  */
class PnlIdecMisRef1NFile : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecMisRef1NFileDo)
		*/
	class VecVDo {

	public:
		static const uint BUTVIEWCLICK = 1;
		static const uint BUTNEWCLICK = 2;
		static const uint BUTDELETECLICK = 3;
		static const uint BUTREFRESHCLICK = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContInf (full: ContInfIdecMisRef1NFile)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFCSIQST = 1;

	public:
		ContInf(const uint numFCsiQst = 1);

	public:
		uint numFCsiQst;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecMisRef1NFile)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecMisRef1NFile)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTVIEWAVAIL = 1;
		static const uint BUTVIEWACTIVE = 2;
		static const uint BUTNEWAVAIL = 3;
		static const uint BUTDELETEAVAIL = 4;
		static const uint BUTDELETEACTIVE = 5;

	public:
		StatShr(const bool ButViewAvail = true, const bool ButViewActive = true, const bool ButNewAvail = true, const bool ButDeleteAvail = true, const bool ButDeleteActive = true);

	public:
		bool ButViewAvail;
		bool ButViewActive;
		bool ButNewAvail;
		bool ButDeleteAvail;
		bool ButDeleteActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* StgIac (full: StgIacIdecMisRef1NFile)
		*/
	class StgIac : public Block {

	public:
		static const uint TCOREFWIDTH = 1;

	public:
		StgIac(const uint TcoRefWidth = 100);

	public:
		uint TcoRefWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StgIac* comp);
		set<uint> diff(const StgIac* comp);
	};

	/**
		* Tag (full: TagIdecMisRef1NFile)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecMisRef1NFileData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint STGIAC = 2;
		static const uint STGIACQRY = 3;

	public:
		DpchAppData();

	public:
		StgIac stgiac;
		QryIdecMisRef1NFile::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecMisRef1NFileDo)
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
		* DpchEngData (full: DpchEngIdecMisRef1NFileData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint FEEDFCSIQST = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint STGIAC = 6;
		static const uint TAG = 7;
		static const uint RST = 8;
		static const uint STATAPPQRY = 9;
		static const uint STATSHRQRY = 10;
		static const uint STGIACQRY = 11;
		static const uint ALL = 12;

	public:
		DpchEngData(const ubigint jref = 0, ContInf* continf = NULL, Feed* feedFCsiQst = NULL, StatShr* statshr = NULL, StgIac* stgiac = NULL, ListIdecQMisRef1NFile* rst = NULL, QryIdecMisRef1NFile::StatShr* statshrqry = NULL, QryIdecMisRef1NFile::StgIac* stgiacqry = NULL, const set<uint>& mask = {NONE});

	public:
		ContInf continf;
		Feed feedFCsiQst;
		StatShr statshr;
		StgIac stgiac;
		ListIdecQMisRef1NFile rst;
		QryIdecMisRef1NFile::StatShr statshrqry;
		QryIdecMisRef1NFile::StgIac stgiacqry;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButViewAvail(DbsIdec* dbsidec);
	bool evalButViewActive(DbsIdec* dbsidec);
	bool evalButNewAvail(DbsIdec* dbsidec);
	bool evalButDeleteAvail(DbsIdec* dbsidec);
	bool evalButDeleteActive(DbsIdec* dbsidec);

public:
	PnlIdecMisRef1NFile(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecMisRef1NFile();

public:
	ContInf continf;
	StatShr statshr;
	StgIac stgiac;

	Feed feedFCsiQst;

	QryIdecMisRef1NFile* qry;

	IdecMFile recFil;

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
	void handleDpchAppDataStgiac(DbsIdec* dbsidec, StgIac* _stgiac, DpchEngIdec** dpcheng);
	void handleDpchAppDataStgiacqry(DbsIdec* dbsidec, QryIdecMisRef1NFile::StgIac* _stgiacqry, DpchEngIdec** dpcheng);

	void handleDpchAppDoButViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButNewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButDeleteClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButRefreshClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

