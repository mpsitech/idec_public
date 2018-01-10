/**
  * \file PnlIdecIaqScill.h
  * job handler for job PnlIdecIaqScill (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECIAQSCILL_H
#define PNLIDECIAQSCILL_H

// IP custInclude --- INSERT

#include "JobIdecIllum.h"

#define VecVIdecIaqScillDo PnlIdecIaqScill::VecVDo
#define VecVIdecIaqScillMode PnlIdecIaqScill::VecVMode

#define ContIacIdecIaqScill PnlIdecIaqScill::ContIac
#define ContInfIdecIaqScill PnlIdecIaqScill::ContInf
#define StatAppIdecIaqScill PnlIdecIaqScill::StatApp
#define StatShrIdecIaqScill PnlIdecIaqScill::StatShr
#define TagIdecIaqScill PnlIdecIaqScill::Tag

#define DpchAppIdecIaqScillData PnlIdecIaqScill::DpchAppData
#define DpchAppIdecIaqScillDo PnlIdecIaqScill::DpchAppDo
#define DpchEngIdecIaqScillData PnlIdecIaqScill::DpchEngData

/**
  * PnlIdecIaqScill
  */
class PnlIdecIaqScill : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecIaqScillDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVMode (full: VecVIdecIaqScillMode)
		*/
	class VecVMode {

	public:
		static const uint MANUAL = 1;
		static const uint AUTOLIVE = 2;
		static const uint AUTOREC = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
	  * ContIac (full: ContIacIdecIaqScill)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPMOD = 1;
		static const uint SLDTHR = 2;
		static const uint SLDFLD = 3;
		static const uint SLDSPT = 4;

	public:
		ContIac(const uint numFPupMod = 2, const double SldThr = 0.0, const double SldFld = 0.0, const double SldSpt = 0.0);

	public:
		uint numFPupMod;
		double SldThr;
		double SldFld;
		double SldSpt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecIaqScill)
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
		* StatApp (full: StatAppIdecIaqScill)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecIaqScill)
		*/
	class StatShr : public Block {

	public:
		static const uint PUPMODACTIVE = 1;
		static const uint SLDTHRAVAIL = 2;
		static const uint SLDTHRACTIVE = 3;
		static const uint SLDTHRMIN = 4;
		static const uint SLDTHRMAX = 5;
		static const uint SLDFLDACTIVE = 6;
		static const uint SLDFLDMIN = 7;
		static const uint SLDFLDMAX = 8;
		static const uint SLDSPTACTIVE = 9;
		static const uint SLDSPTMIN = 10;
		static const uint SLDSPTMAX = 11;

	public:
		StatShr(const bool PupModActive = true, const bool SldThrAvail = true, const bool SldThrActive = true, const double SldThrMin = 0.0, const double SldThrMax = 1.0, const bool SldFldActive = true, const double SldFldMin = 0.0, const double SldFldMax = 1.0, const bool SldSptActive = true, const double SldSptMin = 0.0, const double SldSptMax = 1.0);

	public:
		bool PupModActive;
		bool SldThrAvail;
		bool SldThrActive;
		double SldThrMin;
		double SldThrMax;
		bool SldFldActive;
		double SldFldMin;
		double SldFldMax;
		bool SldSptActive;
		double SldSptMin;
		double SldSptMax;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecIaqScill)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecIaqScillData)
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
		* DpchAppDo (full: DpchAppIdecIaqScillDo)
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
		* DpchEngData (full: DpchEngIdecIaqScillData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPMOD = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupMod = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupMod;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalPupModActive(DbsIdec* dbsidec);
	bool evalSldThrAvail(DbsIdec* dbsidec);
	bool evalSldThrActive(DbsIdec* dbsidec);
	bool evalSldFldActive(DbsIdec* dbsidec);
	bool evalSldSptActive(DbsIdec* dbsidec);

public:
	PnlIdecIaqScill(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecIaqScill();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFPupMod;

	JobIdecIllum* jobillum;

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

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecMastslvChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

