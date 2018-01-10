/**
  * \file PnlIdecScfQcd.h
  * job handler for job PnlIdecScfQcd (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFQCD_H
#define PNLIDECSCFQCD_H

// IP custInclude --- INSERT

#include "JobIdecQcdacq.h"
#include "JobIdecSpotfind.h"

#define VecVIdecScfQcdDo PnlIdecScfQcd::VecVDo

#define ContIacIdecScfQcd PnlIdecScfQcd::ContIac
#define ContInfIdecScfQcd PnlIdecScfQcd::ContInf
#define StatAppIdecScfQcd PnlIdecScfQcd::StatApp
#define StatShrIdecScfQcd PnlIdecScfQcd::StatShr
#define TagIdecScfQcd PnlIdecScfQcd::Tag

#define DpchAppIdecScfQcdData PnlIdecScfQcd::DpchAppData
#define DpchAppIdecScfQcdDo PnlIdecScfQcd::DpchAppDo
#define DpchEngIdecScfQcdData PnlIdecScfQcd::DpchEngData

/**
  * PnlIdecScfQcd
  */
class PnlIdecScfQcd : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfQcdDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfQcd)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFLAM = 1;
		static const uint TXFDLM = 2;
		static const uint CHKAON = 3;
		static const uint SLDTOF = 4;
		static const uint SLDTMP = 5;
		static const uint NUMFPUPFAN = 6;
		static const uint SLDFMD = 7;
		static const uint SLDVDD = 8;
		static const uint CHKVD2 = 9;
		static const uint SLDVRF = 10;
		static const uint UPDASL = 11;
		static const uint SLDAMO = 12;
		static const uint CHKAAD = 13;

	public:
		ContIac(const string& TxfLam = "", const string& TxfDlm = "", const bool ChkAon = false, const double SldTof = 0.0, const double SldTmp = 0.0, const uint numFPupFan = 1, const double SldFmd = 0.0, const double SldVdd = 0.0, const bool ChkVd2 = false, const double SldVrf = 0.0, const int UpdAsl = 0, const double SldAmo = 0.0, const bool ChkAad = false);

	public:
		string TxfLam;
		string TxfDlm;
		bool ChkAon;
		double SldTof;
		double SldTmp;
		uint numFPupFan;
		double SldFmd;
		double SldVdd;
		bool ChkVd2;
		double SldVrf;
		int UpdAsl;
		double SldAmo;
		bool ChkAad;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfQcd)
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
		* StatApp (full: StatAppIdecScfQcd)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecScfQcd)
		*/
	class StatShr : public Block {

	public:
		static const uint TXFLAMACTIVE = 1;
		static const uint TXFDLMACTIVE = 2;
		static const uint CHKAONACTIVE = 3;
		static const uint SLDTOFACTIVE = 4;
		static const uint SLDTOFMIN = 5;
		static const uint SLDTOFMAX = 6;
		static const uint SLDTOFRAST = 7;
		static const uint SLDTMPACTIVE = 8;
		static const uint SLDTMPMIN = 9;
		static const uint SLDTMPMAX = 10;
		static const uint SLDTMPRAST = 11;
		static const uint PUPFANACTIVE = 12;
		static const uint SLDFMDACTIVE = 13;
		static const uint SLDFMDMIN = 14;
		static const uint SLDFMDMAX = 15;
		static const uint SLDFMDRAST = 16;
		static const uint SLDVDDACTIVE = 17;
		static const uint SLDVDDMIN = 18;
		static const uint SLDVDDMAX = 19;
		static const uint SLDVDDRAST = 20;
		static const uint CHKVD2ACTIVE = 21;
		static const uint SLDVRFACTIVE = 22;
		static const uint SLDVRFMIN = 23;
		static const uint SLDVRFMAX = 24;
		static const uint SLDVRFRAST = 25;
		static const uint UPDASLACTIVE = 26;
		static const uint UPDASLMIN = 27;
		static const uint UPDASLMAX = 28;
		static const uint SLDAMOACTIVE = 29;
		static const uint SLDAMOMIN = 30;
		static const uint SLDAMOMAX = 31;
		static const uint SLDAMORAST = 32;
		static const uint CHKAADACTIVE = 33;

	public:
		StatShr(const bool TxfLamActive = true, const bool TxfDlmActive = true, const bool ChkAonActive = true, const bool SldTofActive = true, const double SldTofMin = 30, const double SldTofMax = 960, const double SldTofRast = 2, const bool SldTmpActive = true, const double SldTmpMin = -50, const double SldTmpMax = 10, const double SldTmpRast = 1, const bool PupFanActive = true, const bool SldFmdActive = true, const double SldFmdMin = 100, const double SldFmdMax = 300, const double SldFmdRast = 10, const bool SldVddActive = true, const double SldVddMin = 2.8, const double SldVddMax = 3.8, const double SldVddRast = 0.1, const bool ChkVd2Active = true, const bool SldVrfActive = true, const double SldVrfMin = 1.0, const double SldVrfMax = 3.0, const double SldVrfRast = 0.05, const bool UpdAslActive = true, const int UpdAslMin = 0, const int UpdAslMax = 100, const bool SldAmoActive = true, const double SldAmoMin = 0.5, const double SldAmoMax = 5.0, const double SldAmoRast = 0.5, const bool ChkAadActive = true);

	public:
		bool TxfLamActive;
		bool TxfDlmActive;
		bool ChkAonActive;
		bool SldTofActive;
		double SldTofMin;
		double SldTofMax;
		double SldTofRast;
		bool SldTmpActive;
		double SldTmpMin;
		double SldTmpMax;
		double SldTmpRast;
		bool PupFanActive;
		bool SldFmdActive;
		double SldFmdMin;
		double SldFmdMax;
		double SldFmdRast;
		bool SldVddActive;
		double SldVddMin;
		double SldVddMax;
		double SldVddRast;
		bool ChkVd2Active;
		bool SldVrfActive;
		double SldVrfMin;
		double SldVrfMax;
		double SldVrfRast;
		bool UpdAslActive;
		int UpdAslMin;
		int UpdAslMax;
		bool SldAmoActive;
		double SldAmoMin;
		double SldAmoMax;
		double SldAmoRast;
		bool ChkAadActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScfQcd)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfQcdData)
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
		* DpchAppDo (full: DpchAppIdecScfQcdDo)
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
		* DpchEngData (full: DpchEngIdecScfQcdData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPFAN = 4;
		static const uint STATAPP = 5;
		static const uint STATSHR = 6;
		static const uint TAG = 7;
		static const uint ALL = 8;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupFan = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupFan;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalTxfLamActive(DbsIdec* dbsidec);
	bool evalTxfDlmActive(DbsIdec* dbsidec);
	bool evalChkAonActive(DbsIdec* dbsidec);
	bool evalSldTofActive(DbsIdec* dbsidec);
	bool evalSldTmpActive(DbsIdec* dbsidec);
	bool evalPupFanActive(DbsIdec* dbsidec);
	bool evalSldFmdActive(DbsIdec* dbsidec);
	bool evalSldVddActive(DbsIdec* dbsidec);
	bool evalChkVd2Active(DbsIdec* dbsidec);
	bool evalSldVrfActive(DbsIdec* dbsidec);
	bool evalUpdAslActive(DbsIdec* dbsidec);
	bool evalSldAmoActive(DbsIdec* dbsidec);
	bool evalChkAadActive(DbsIdec* dbsidec);

public:
	PnlIdecScfQcd(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfQcd();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFPupFan;

	JobIdecQcdacq* jobqcdacq;
	JobIdecSpotfind* jobspotfind;

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

