/**
  * \file PnlIdecScfOptics.h
  * job handler for job PnlIdecScfOptics (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFOPTICS_H
#define PNLIDECSCFOPTICS_H

// IP custInclude --- INSERT

#include "JobIdecFusion.h"
#include "JobIdecLwiracq.h"
#include "JobIdecQcdacq.h"
#include "JobIdecStereo.h"
#include "JobIdecVislacq.h"
#include "JobIdecVisracq.h"

#define VecVIdecScfOpticsDo PnlIdecScfOptics::VecVDo

#define ContIacIdecScfOptics PnlIdecScfOptics::ContIac
#define ContInfIdecScfOptics PnlIdecScfOptics::ContInf
#define StatAppIdecScfOptics PnlIdecScfOptics::StatApp
#define StatShrIdecScfOptics PnlIdecScfOptics::StatShr
#define TagIdecScfOptics PnlIdecScfOptics::Tag

#define DpchAppIdecScfOpticsData PnlIdecScfOptics::DpchAppData
#define DpchAppIdecScfOpticsDo PnlIdecScfOptics::DpchAppDo
#define DpchEngIdecScfOpticsData PnlIdecScfOptics::DpchEngData

/**
  * PnlIdecScfOptics
  */
class PnlIdecScfOptics : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfOpticsDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfOptics)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFDST = 1;
		static const uint TXFIDX = 2;
		static const uint TXFIDY = 3;
		static const uint TXFQDX = 4;
		static const uint TXFQDY = 5;
		static const uint TXFADX = 6;
		static const uint TXFADY = 7;
		static const uint NUMFPUPLSG = 8;
		static const uint NUMFPUPRSG = 9;
		static const uint NUMFPUPISG = 10;
		static const uint UPDQWH = 11;
		static const uint TXFQHP = 12;
		static const uint TXFQDP = 13;
		static const uint TXFQFL = 14;
		static const uint TXFQFN = 15;
		static const uint NUMFPUPQSG = 16;

	public:
		ContIac(const string& TxfDst = "", const string& TxfIdx = "", const string& TxfIdy = "", const string& TxfQdx = "", const string& TxfQdy = "", const string& TxfAdx = "", const string& TxfAdy = "", const uint numFPupLsg = 1, const uint numFPupRsg = 1, const uint numFPupIsg = 1, const int UpdQwh = 0, const string& TxfQhp = "", const string& TxfQdp = "", const string& TxfQfl = "", const string& TxfQfn = "", const uint numFPupQsg = 1);

	public:
		string TxfDst;
		string TxfIdx;
		string TxfIdy;
		string TxfQdx;
		string TxfQdy;
		string TxfAdx;
		string TxfAdy;
		uint numFPupLsg;
		uint numFPupRsg;
		uint numFPupIsg;
		int UpdQwh;
		string TxfQhp;
		string TxfQdp;
		string TxfQfl;
		string TxfQfn;
		uint numFPupQsg;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfOptics)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTVWI = 2;
		static const uint TXTVHE = 3;
		static const uint TXTVHP = 4;
		static const uint TXTVFL = 5;
		static const uint TXTVFN = 6;
		static const uint TXTIWI = 7;
		static const uint TXTIHE = 8;
		static const uint TXTIHP = 9;
		static const uint TXTIFL = 10;
		static const uint TXTIFN = 11;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtVwi = "", const string& TxtVhe = "", const string& TxtVhp = "", const string& TxtVfl = "", const string& TxtVfn = "", const string& TxtIwi = "", const string& TxtIhe = "", const string& TxtIhp = "", const string& TxtIfl = "", const string& TxtIfn = "");

	public:
		bool ButMasterOn;
		string TxtVwi;
		string TxtVhe;
		string TxtVhp;
		string TxtVfl;
		string TxtVfn;
		string TxtIwi;
		string TxtIhe;
		string TxtIhp;
		string TxtIfl;
		string TxtIfn;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecScfOptics)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecScfOptics)
		*/
	class StatShr : public Block {

	public:
		static const uint TXFDSTACTIVE = 1;
		static const uint TXFIDXACTIVE = 2;
		static const uint TXFIDYACTIVE = 3;
		static const uint TXFQDXACTIVE = 4;
		static const uint TXFQDYACTIVE = 5;
		static const uint TXFADXACTIVE = 6;
		static const uint TXFADYACTIVE = 7;
		static const uint PUPLSGACTIVE = 8;
		static const uint PUPRSGACTIVE = 9;
		static const uint PUPISGACTIVE = 10;
		static const uint UPDQWHACTIVE = 11;
		static const uint UPDQWHMIN = 12;
		static const uint UPDQWHMAX = 13;
		static const uint TXFQHPACTIVE = 14;
		static const uint TXFQDPACTIVE = 15;
		static const uint TXFQFLACTIVE = 16;
		static const uint TXFQFNACTIVE = 17;
		static const uint PUPQSGACTIVE = 18;

	public:
		StatShr(const bool TxfDstActive = true, const bool TxfIdxActive = true, const bool TxfIdyActive = true, const bool TxfQdxActive = true, const bool TxfQdyActive = true, const bool TxfAdxActive = true, const bool TxfAdyActive = true, const bool PupLsgActive = true, const bool PupRsgActive = true, const bool PupIsgActive = true, const bool UpdQwhActive = true, const int UpdQwhMin = 0, const int UpdQwhMax = 100, const bool TxfQhpActive = true, const bool TxfQdpActive = true, const bool TxfQflActive = true, const bool TxfQfnActive = true, const bool PupQsgActive = true);

	public:
		bool TxfDstActive;
		bool TxfIdxActive;
		bool TxfIdyActive;
		bool TxfQdxActive;
		bool TxfQdyActive;
		bool TxfAdxActive;
		bool TxfAdyActive;
		bool PupLsgActive;
		bool PupRsgActive;
		bool PupIsgActive;
		bool UpdQwhActive;
		int UpdQwhMin;
		int UpdQwhMax;
		bool TxfQhpActive;
		bool TxfQdpActive;
		bool TxfQflActive;
		bool TxfQfnActive;
		bool PupQsgActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScfOptics)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfOpticsData)
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
		* DpchAppDo (full: DpchAppIdecScfOpticsDo)
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
		* DpchEngData (full: DpchEngIdecScfOpticsData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPISG = 4;
		static const uint FEEDFPUPLSG = 5;
		static const uint FEEDFPUPQSG = 6;
		static const uint FEEDFPUPRSG = 7;
		static const uint STATAPP = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;
		static const uint ALL = 11;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupIsg = NULL, Feed* feedFPupLsg = NULL, Feed* feedFPupQsg = NULL, Feed* feedFPupRsg = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupIsg;
		Feed feedFPupLsg;
		Feed feedFPupQsg;
		Feed feedFPupRsg;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalTxfDstActive(DbsIdec* dbsidec);
	bool evalTxfIdxActive(DbsIdec* dbsidec);
	bool evalTxfIdyActive(DbsIdec* dbsidec);
	bool evalTxfQdxActive(DbsIdec* dbsidec);
	bool evalTxfQdyActive(DbsIdec* dbsidec);
	bool evalTxfAdxActive(DbsIdec* dbsidec);
	bool evalTxfAdyActive(DbsIdec* dbsidec);
	bool evalPupLsgActive(DbsIdec* dbsidec);
	bool evalPupRsgActive(DbsIdec* dbsidec);
	bool evalPupIsgActive(DbsIdec* dbsidec);
	bool evalUpdQwhActive(DbsIdec* dbsidec);
	bool evalTxfQhpActive(DbsIdec* dbsidec);
	bool evalTxfQdpActive(DbsIdec* dbsidec);
	bool evalTxfQflActive(DbsIdec* dbsidec);
	bool evalTxfQfnActive(DbsIdec* dbsidec);
	bool evalPupQsgActive(DbsIdec* dbsidec);

public:
	PnlIdecScfOptics(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfOptics();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFPupIsg;
	Feed feedFPupLsg;
	Feed feedFPupQsg;
	Feed feedFPupRsg;

	JobIdecFusion* jobfusion;
	JobIdecLwiracq* joblwiracq;
	JobIdecQcdacq* jobqcdacq;
	JobIdecStereo* jobstereo;
	JobIdecVislacq* jobvislacq;
	JobIdecVisracq* jobvisracq;

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

