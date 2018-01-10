/**
  * \file PnlIdecIaqQcdsp.h
  * job handler for job PnlIdecIaqQcdsp (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQQCDSP_H
#define PNLIDECIAQQCDSP_H

// IP custInclude --- INSERT

#include "JobIdecLwiracq.h"
#include "JobIdecQcdacq.h"

#define VecVIdecIaqQcdspDo PnlIdecIaqQcdsp::VecVDo
#define VecVIdecIaqQcdspMode PnlIdecIaqQcdsp::VecVMode

#define ContIacIdecIaqQcdsp PnlIdecIaqQcdsp::ContIac
#define ContInfIdecIaqQcdsp PnlIdecIaqQcdsp::ContInf
#define StatShrIdecIaqQcdsp PnlIdecIaqQcdsp::StatShr
#define TagIdecIaqQcdsp PnlIdecIaqQcdsp::Tag

#define DpchAppIdecIaqQcdspData PnlIdecIaqQcdsp::DpchAppData
#define DpchAppIdecIaqQcdspDo PnlIdecIaqQcdsp::DpchAppDo
#define DpchEngIdecIaqQcdspData PnlIdecIaqQcdsp::DpchEngData
#define DpchEngIdecIaqQcdspLive PnlIdecIaqQcdsp::DpchEngLive

/**
  * PnlIdecIaqQcdsp
  */
class PnlIdecIaqQcdsp : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecIaqQcdspDo)
		*/
	class VecVDo {

	public:
		static const uint BUTREGULARIZECLICK = 1;
		static const uint BUTMINIMIZECLICK = 2;
		static const uint BUTMASTERCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVMode (full: VecVIdecIaqQcdspMode)
		*/
	class VecVMode {

	public:
		static const uint OFF = 1;
		static const uint PIX = 2;
		static const uint FRM = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
	  * ContIac (full: ContIacIdecIaqQcdsp)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPMOD = 1;
		static const uint SLDTIN = 2;
		static const uint CUSIMGPXS = 3;

	public:
		ContIac(const uint numFPupMod = 1, const double SldTin = 0.0, const usmallint CusImgPxs = 0);

	public:
		uint numFPupMod;
		double SldTin;
		usmallint CusImgPxs;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqQcdsp)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTMASTERON = 1;
		static const uint TXTIMGIL0 = 2;
		static const uint TXTIMGIL1 = 3;
		static const uint TXTIMGQWH = 4;
		static const uint TXTIMGQHP = 5;
		static const uint TXTIMGQDP = 6;
		static const uint TXTIMGSIQ = 7;
		static const uint TXTIMGDXI = 8;
		static const uint TXTIMGDYI = 9;
		static const uint TXTIMGQLM = 10;
		static const uint TXTIMGQDL = 11;
		static const uint NUMFCSIIMGSTE = 12;

	public:
		ContInf(const bool ButMasterOn = false, const string& TxtImgIl0 = "", const string& TxtImgIl1 = "", const string& TxtImgQwh = "", const string& TxtImgQhp = "", const string& TxtImgQdp = "", const string& TxtImgSiq = "", const string& TxtImgDxi = "", const string& TxtImgDyi = "", const string& TxtImgQlm = "", const string& TxtImgQdl = "", const uint numFCsiImgSte = 1);

	public:
		bool ButMasterOn;
		string TxtImgIl0;
		string TxtImgIl1;
		string TxtImgQwh;
		string TxtImgQhp;
		string TxtImgQdp;
		string TxtImgSiq;
		string TxtImgDxi;
		string TxtImgDyi;
		string TxtImgQlm;
		string TxtImgQdl;
		uint numFCsiImgSte;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatShr (full: StatShrIdecIaqQcdsp)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint PUPMODACTIVE = 2;
		static const uint SLDTINMIN = 3;
		static const uint SLDTINMAX = 4;
		static const uint SLDTINRAST = 5;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool PupModActive = true, const double SldTinMin = 1, const double SldTinMax = 1024, const double SldTinRast = 2);

	public:
		uint ixIdecVExpstate;
		bool PupModActive;
		double SldTinMin;
		double SldTinMax;
		double SldTinRast;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecIaqQcdsp)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqQcdspData)
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
		* DpchAppDo (full: DpchAppIdecIaqQcdspDo)
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
		* DpchEngData (full: DpchEngIdecIaqQcdspData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIIMGSTE = 4;
		static const uint FEEDFPUPMOD = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFCsiImgSte = NULL, Feed* feedFPupMod = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiImgSte;
		Feed feedFPupMod;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	/**
		* DpchEngLive (full: DpchEngIdecIaqQcdspLive)
		*/
	class DpchEngLive : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint TLWIR = 3;
		static const uint TQCD = 4;
		static const uint DELTATQCD = 5;
		static const uint ALL = 6;

	public:
		DpchEngLive(const ubigint jref = 0, ContInf* continf = NULL, const vector<double>& Tlwir = {}, const vector<double>& Tqcd = {}, const vector<double>& DeltaTqcd = {}, const set<uint>& mask = {NONE});

	public:
		ContInf continf;
		vector<double> Tlwir;
		vector<double> Tqcd;
		vector<double> DeltaTqcd;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalPupModActive(DbsIdec* dbsidec);

public:
	PnlIdecIaqQcdsp(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecIaqQcdsp();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFCsiImgSte;
	Feed feedFPupMod;

	JobIdecLwiracq* joblwiracq;
	JobIdecQcdacq* jobqcdacq;

	// IP custVar --- INSERT

public:
	// IP cust --- IBEGIN
	void refreshLive(DbsIdec* dbsidec, set<uint>& moditems);
	// IP cust --- IEND

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButRegularizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMinimizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMasterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecImgrdy(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif


