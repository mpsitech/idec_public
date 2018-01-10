/**
  * \file PnlIdecUsgDetail.h
  * job handler for job PnlIdecUsgDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSGDETAIL_H
#define PNLIDECUSGDETAIL_H

// IP custInclude --- INSERT

#define VecVIdecUsgDetailDo PnlIdecUsgDetail::VecVDo

#define ContIacIdecUsgDetail PnlIdecUsgDetail::ContIac
#define ContInfIdecUsgDetail PnlIdecUsgDetail::ContInf
#define StatAppIdecUsgDetail PnlIdecUsgDetail::StatApp
#define StatShrIdecUsgDetail PnlIdecUsgDetail::StatShr
#define TagIdecUsgDetail PnlIdecUsgDetail::Tag

#define DpchAppIdecUsgDetailData PnlIdecUsgDetail::DpchAppData
#define DpchAppIdecUsgDetailDo PnlIdecUsgDetail::DpchAppDo
#define DpchEngIdecUsgDetailData PnlIdecUsgDetail::DpchEngData

/**
  * PnlIdecUsgDetail
  */
class PnlIdecUsgDetail : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecUsgDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecUsgDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFCMT = 1;

	public:
		ContIac(const string& TxfCmt = "");

	public:
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecUsgDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTSRF = 1;

	public:
		ContInf(const string& TxtSrf = "");

	public:
		string TxtSrf;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecUsgDetail)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecUsgDetail)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTSAVEAVAIL = 1;
		static const uint BUTSAVEACTIVE = 2;
		static const uint TXTSRFACTIVE = 3;
		static const uint TXFCMTACTIVE = 4;

	public:
		StatShr(const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxtSrfActive = true, const bool TxfCmtActive = true);

	public:
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxtSrfActive;
		bool TxfCmtActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecUsgDetail)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecUsgDetailData)
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
		* DpchAppDo (full: DpchAppIdecUsgDetailDo)
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
		* DpchEngData (full: DpchEngIdecUsgDetailData)
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

	bool evalButSaveAvail(DbsIdec* dbsidec);
	bool evalButSaveActive(DbsIdec* dbsidec);
	bool evalTxtSrfActive(DbsIdec* dbsidec);
	bool evalTxfCmtActive(DbsIdec* dbsidec);

public:
	PnlIdecUsgDetail(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecUsgDetail();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	IdecMUsergroup recUsg;

	bool dirty;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshRecUsg(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButSaveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecUsgUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

