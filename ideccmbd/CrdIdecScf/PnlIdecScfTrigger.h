/**
  * \file PnlIdecScfTrigger.h
  * job handler for job PnlIdecScfTrigger (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFTRIGGER_H
#define PNLIDECSCFTRIGGER_H

// IP custInclude --- INSERT

#include "JobIdecTrigger.h"

#define VecVIdecScfTriggerDo PnlIdecScfTrigger::VecVDo

#define ContIacIdecScfTrigger PnlIdecScfTrigger::ContIac
#define ContInfIdecScfTrigger PnlIdecScfTrigger::ContInf
#define StatAppIdecScfTrigger PnlIdecScfTrigger::StatApp
#define StatShrIdecScfTrigger PnlIdecScfTrigger::StatShr
#define TagIdecScfTrigger PnlIdecScfTrigger::Tag

#define DpchAppIdecScfTriggerData PnlIdecScfTrigger::DpchAppData
#define DpchAppIdecScfTriggerDo PnlIdecScfTrigger::DpchAppDo
#define DpchEngIdecScfTriggerData PnlIdecScfTrigger::DpchEngData

/**
  * PnlIdecScfTrigger
  */
class PnlIdecScfTrigger : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfTriggerDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfTrigger)
	  */
	class ContIac : public Block {

	public:
		static const uint SLDRDL = 1;
		static const uint SLDIDL = 2;
		static const uint SLDQDL = 3;

	public:
		ContIac(const double SldRdl = 0.0, const double SldIdl = 0.0, const double SldQdl = 0.0);

	public:
		double SldRdl;
		double SldIdl;
		double SldQdl;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfTrigger)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;

	public:
		ContInf(const bool ButMasterOn = false);

	public:
		bool ButMasterOn;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecScfTrigger)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecScfTrigger)
		*/
	class StatShr : public Block {

	public:
		static const uint SLDRDLACTIVE = 1;
		static const uint SLDRDLMIN = 2;
		static const uint SLDRDLMAX = 3;
		static const uint SLDRDLRAST = 4;
		static const uint SLDIDLACTIVE = 5;
		static const uint SLDIDLMIN = 6;
		static const uint SLDIDLMAX = 7;
		static const uint SLDIDLRAST = 8;
		static const uint SLDQDLACTIVE = 9;
		static const uint SLDQDLMIN = 10;
		static const uint SLDQDLMAX = 11;
		static const uint SLDQDLRAST = 12;

	public:
		StatShr(const bool SldRdlActive = true, const double SldRdlMin = -100, const double SldRdlMax = 100, const double SldRdlRast = 0.1, const bool SldIdlActive = true, const double SldIdlMin = -100, const double SldIdlMax = 100, const double SldIdlRast = 0.1, const bool SldQdlActive = true, const double SldQdlMin = -100, const double SldQdlMax = 100, const double SldQdlRast = 0.1);

	public:
		bool SldRdlActive;
		double SldRdlMin;
		double SldRdlMax;
		double SldRdlRast;
		bool SldIdlActive;
		double SldIdlMin;
		double SldIdlMax;
		double SldIdlRast;
		bool SldQdlActive;
		double SldQdlMin;
		double SldQdlMax;
		double SldQdlRast;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScfTrigger)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfTriggerData)
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
		* DpchAppDo (full: DpchAppIdecScfTriggerDo)
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
		* DpchEngData (full: DpchEngIdecScfTriggerData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;
		static const uint ALL = 7;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalSldRdlActive(DbsIdec* dbsidec);
	bool evalSldIdlActive(DbsIdec* dbsidec);
	bool evalSldQdlActive(DbsIdec* dbsidec);

public:
	PnlIdecScfTrigger(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfTrigger();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	JobIdecTrigger* jobtrigger;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMasterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStgChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

