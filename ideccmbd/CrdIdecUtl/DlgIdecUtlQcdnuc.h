/**
  * \file DlgIdecUtlQcdnuc.h
  * job handler for job DlgIdecUtlQcdnuc (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DLGIDECUTLQCDNUC_H
#define DLGIDECUTLQCDNUC_H

// IP custInclude --- INSERT

#include "JobIdecLwiracq.h"
#include "JobIdecQcdacq.h"
#include "JobIdecSpotfind.h"
#include "JobIdecTrigger.h"

#define VecVDlgIdecUtlQcdnucDit DlgIdecUtlQcdnuc::VecVDit
#define VecVDlgIdecUtlQcdnucDo DlgIdecUtlQcdnuc::VecVDo
#define VecVDlgIdecUtlQcdnucSge DlgIdecUtlQcdnuc::VecVSge

#define ContIacDlgIdecUtlQcdnuc DlgIdecUtlQcdnuc::ContIac
#define ContInfDlgIdecUtlQcdnuc DlgIdecUtlQcdnuc::ContInf
#define StatAppDlgIdecUtlQcdnuc DlgIdecUtlQcdnuc::StatApp
#define TagDlgIdecUtlQcdnuc DlgIdecUtlQcdnuc::Tag

#define DpchAppDlgIdecUtlQcdnucData DlgIdecUtlQcdnuc::DpchAppData
#define DpchAppDlgIdecUtlQcdnucDo DlgIdecUtlQcdnuc::DpchAppDo
#define DpchEngDlgIdecUtlQcdnucData DlgIdecUtlQcdnuc::DpchEngData

/**
  * DlgIdecUtlQcdnuc
  */
class DlgIdecUtlQcdnuc : public JobIdec {

public:
	/**
		* VecVDit (full: VecVDlgIdecUtlQcdnucDit)
		*/
	class VecVDit {

	public:
		static const uint PRP = 1;
		static const uint CAL = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVDo (full: VecVDlgIdecUtlQcdnucDo)
		*/
	class VecVDo {

	public:
		static const uint BUTDNECLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVDlgIdecUtlQcdnucSge)
		*/
	class VecVSge {

	public:

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContIac (full: ContIacDlgIdecUtlQcdnuc)
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
	  * ContInf (full: ContInfDlgIdecUtlQcdnuc)
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
		* StatApp (full: StatAppDlgIdecUtlQcdnuc)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const bool initdone = false, const string& shortMenu = "");
	};

	/**
		* Tag (full: TagDlgIdecUtlQcdnuc)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppDlgIdecUtlQcdnucData)
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
		* DpchAppDo (full: DpchAppDlgIdecUtlQcdnucDo)
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
		* DpchEngData (full: DpchEngDlgIdecUtlQcdnucData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFDSE = 4;
		static const uint FEEDFSGE = 5;
		static const uint STATAPP = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFDse = NULL, Feed* feedFSge = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFDse;
		Feed feedFSge;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

public:
	DlgIdecUtlQcdnuc(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~DlgIdecUtlQcdnuc();

public:
	ContIac contiac;
	ContInf continf;

	Feed feedFDse;
	Feed feedFSge;

	JobIdecLwiracq* joblwiracq;
	JobIdecQcdacq* jobqcdacq;
	JobIdecSpotfind* jobspotfind;
	JobIdecTrigger* jobtrigger;

	uint ixVDit;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshPrp(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshCal(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButDneClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

