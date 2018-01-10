/**
  * \file PnlIdecScfRecord.h
  * job handler for job PnlIdecScfRecord (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFRECORD_H
#define PNLIDECSCFRECORD_H

// IP custInclude --- INSERT

#include "JobIdecRecord.h"

#define VecVIdecScfRecordDo PnlIdecScfRecord::VecVDo

#define ContIacIdecScfRecord PnlIdecScfRecord::ContIac
#define ContInfIdecScfRecord PnlIdecScfRecord::ContInf
#define StatAppIdecScfRecord PnlIdecScfRecord::StatApp
#define StatShrIdecScfRecord PnlIdecScfRecord::StatShr
#define TagIdecScfRecord PnlIdecScfRecord::Tag

#define DpchAppIdecScfRecordData PnlIdecScfRecord::DpchAppData
#define DpchAppIdecScfRecordDo PnlIdecScfRecord::DpchAppDo
#define DpchEngIdecScfRecordData PnlIdecScfRecord::DpchEngData

/**
  * PnlIdecScfRecord
  */
class PnlIdecScfRecord : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecScfRecordDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMASTERCLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecScfRecord)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPFLR = 1;
		static const uint CHKFLG = 2;
		static const uint NUMFPUPFRR = 3;
		static const uint CHKFRG = 4;
		static const uint NUMFPUPFIR = 5;
		static const uint CHKFQC = 6;
		static const uint CHKFST = 7;
		static const uint SLDVFR = 8;
		static const uint NUMFPUPVLR = 9;
		static const uint CHKVLG = 10;
		static const uint NUMFPUPVRR = 11;
		static const uint CHKVRG = 12;
		static const uint NUMFPUPVIR = 13;
		static const uint CHKVQC = 14;
		static const uint CHKVST = 15;
		static const uint NUMFPUPOWR = 16;

	public:
		ContIac(const uint numFPupFlr = 1, const bool ChkFlg = false, const uint numFPupFrr = 1, const bool ChkFrg = false, const uint numFPupFir = 1, const bool ChkFqc = false, const bool ChkFst = false, const double SldVfr = 0.0, const uint numFPupVlr = 1, const bool ChkVlg = false, const uint numFPupVrr = 1, const bool ChkVrg = false, const uint numFPupVir = 1, const bool ChkVqc = false, const bool ChkVst = false, const uint numFPupOwr = 1);

	public:
		uint numFPupFlr;
		bool ChkFlg;
		uint numFPupFrr;
		bool ChkFrg;
		uint numFPupFir;
		bool ChkFqc;
		bool ChkFst;
		double SldVfr;
		uint numFPupVlr;
		bool ChkVlg;
		uint numFPupVrr;
		bool ChkVrg;
		uint numFPupVir;
		bool ChkVqc;
		bool ChkVst;
		uint numFPupOwr;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecScfRecord)
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
		* StatApp (full: StatAppIdecScfRecord)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecScfRecord)
		*/
	class StatShr : public Block {

	public:
		static const uint PUPFLRACTIVE = 1;
		static const uint CHKFLGACTIVE = 2;
		static const uint PUPFRRACTIVE = 3;
		static const uint CHKFRGACTIVE = 4;
		static const uint PUPFIRACTIVE = 5;
		static const uint CHKFQCACTIVE = 6;
		static const uint CHKFSTACTIVE = 7;
		static const uint SLDVFRACTIVE = 8;
		static const uint SLDVFRMIN = 9;
		static const uint SLDVFRMAX = 10;
		static const uint PUPVLRACTIVE = 11;
		static const uint CHKVLGACTIVE = 12;
		static const uint PUPVRRACTIVE = 13;
		static const uint CHKVRGACTIVE = 14;
		static const uint PUPVIRACTIVE = 15;
		static const uint CHKVQCACTIVE = 16;
		static const uint CHKVSTACTIVE = 17;
		static const uint PUPOWRACTIVE = 18;

	public:
		StatShr(const bool PupFlrActive = true, const bool ChkFlgActive = true, const bool PupFrrActive = true, const bool ChkFrgActive = true, const bool PupFirActive = true, const bool ChkFqcActive = true, const bool ChkFstActive = true, const bool SldVfrActive = true, const double SldVfrMin = 1.0, const double SldVfrMax = 10.0, const bool PupVlrActive = true, const bool ChkVlgActive = true, const bool PupVrrActive = true, const bool ChkVrgActive = true, const bool PupVirActive = true, const bool ChkVqcActive = true, const bool ChkVstActive = true, const bool PupOwrActive = true);

	public:
		bool PupFlrActive;
		bool ChkFlgActive;
		bool PupFrrActive;
		bool ChkFrgActive;
		bool PupFirActive;
		bool ChkFqcActive;
		bool ChkFstActive;
		bool SldVfrActive;
		double SldVfrMin;
		double SldVfrMax;
		bool PupVlrActive;
		bool ChkVlgActive;
		bool PupVrrActive;
		bool ChkVrgActive;
		bool PupVirActive;
		bool ChkVqcActive;
		bool ChkVstActive;
		bool PupOwrActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecScfRecord)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecScfRecordData)
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
		* DpchAppDo (full: DpchAppIdecScfRecordDo)
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
		* DpchEngData (full: DpchEngIdecScfRecordData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPFIR = 4;
		static const uint FEEDFPUPFLR = 5;
		static const uint FEEDFPUPFRR = 6;
		static const uint FEEDFPUPOWR = 7;
		static const uint FEEDFPUPVIR = 8;
		static const uint FEEDFPUPVLR = 9;
		static const uint FEEDFPUPVRR = 10;
		static const uint STATAPP = 11;
		static const uint STATSHR = 12;
		static const uint TAG = 13;
		static const uint ALL = 14;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupFir = NULL, Feed* feedFPupFlr = NULL, Feed* feedFPupFrr = NULL, Feed* feedFPupOwr = NULL, Feed* feedFPupVir = NULL, Feed* feedFPupVlr = NULL, Feed* feedFPupVrr = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupFir;
		Feed feedFPupFlr;
		Feed feedFPupFrr;
		Feed feedFPupOwr;
		Feed feedFPupVir;
		Feed feedFPupVlr;
		Feed feedFPupVrr;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalPupFlrActive(DbsIdec* dbsidec);
	bool evalChkFlgActive(DbsIdec* dbsidec);
	bool evalPupFrrActive(DbsIdec* dbsidec);
	bool evalChkFrgActive(DbsIdec* dbsidec);
	bool evalPupFirActive(DbsIdec* dbsidec);
	bool evalChkFqcActive(DbsIdec* dbsidec);
	bool evalChkFstActive(DbsIdec* dbsidec);
	bool evalSldVfrActive(DbsIdec* dbsidec);
	bool evalPupVlrActive(DbsIdec* dbsidec);
	bool evalChkVlgActive(DbsIdec* dbsidec);
	bool evalPupVrrActive(DbsIdec* dbsidec);
	bool evalChkVrgActive(DbsIdec* dbsidec);
	bool evalPupVirActive(DbsIdec* dbsidec);
	bool evalChkVqcActive(DbsIdec* dbsidec);
	bool evalChkVstActive(DbsIdec* dbsidec);
	bool evalPupOwrActive(DbsIdec* dbsidec);

public:
	PnlIdecScfRecord(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfRecord();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFPupFir;
	Feed feedFPupFlr;
	Feed feedFPupFrr;
	Feed feedFPupOwr;
	Feed feedFPupVir;
	Feed feedFPupVlr;
	Feed feedFPupVrr;

	JobIdecRecord* jobrecord;

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

