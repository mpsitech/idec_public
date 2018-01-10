/**
  * \file PnlIdecScfLwir.h
  * job handler for job PnlIdecScfLwir (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFLWIR_H
#define PNLIDECSCFLWIR_H

// IP custInclude --- INSERT

#include "JobIdecLwiracq.h"

#define VecVIdecScfLwirDo PnlIdecScfLwir::VecVDo

#define ContIacIdecScfLwir PnlIdecScfLwir::ContIac
#define ContInfIdecScfLwir PnlIdecScfLwir::ContInf
#define StatAppIdecScfLwir PnlIdecScfLwir::StatApp
#define StatShrIdecScfLwir PnlIdecScfLwir::StatShr
#define TagIdecScfLwir PnlIdecScfLwir::Tag

#define DpchAppIdecScfLwirData PnlIdecScfLwir::DpchAppData
#define DpchAppIdecScfLwirDo PnlIdecScfLwir::DpchAppDo
#define DpchEngIdecScfLwirData PnlIdecScfLwir::DpchEngData

/**
  * PnlIdecScfLwir
  */
class PnlIdecScfLwir : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfLwirDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfLwir)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFLM0 = 1;
		static const uint TXFLM1 = 2;

	public:
		ContIac(const string& TxfLm0 = "", const string& TxfLm1 = "");

	public:
		string TxfLm0;
		string TxfLm1;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfLwir)
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
		* StatApp (full: StatAppIdecScfLwir)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecScfLwir)
		*/
	class StatShr : public Block {

	public:
		static const uint TXFLM0ACTIVE = 1;
		static const uint TXFLM1ACTIVE = 2;

	public:
		StatShr(const bool TxfLm0Active = true, const bool TxfLm1Active = true);

	public:
		bool TxfLm0Active;
		bool TxfLm1Active;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScfLwir)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfLwirData)
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
		* DpchAppDo (full: DpchAppIdecScfLwirDo)
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
		* DpchEngData (full: DpchEngIdecScfLwirData)
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

	bool evalTxfLm0Active(DbsIdec* dbsidec);
	bool evalTxfLm1Active(DbsIdec* dbsidec);

public:
	PnlIdecScfLwir(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfLwir();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	JobIdecLwiracq* joblwiracq;

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

