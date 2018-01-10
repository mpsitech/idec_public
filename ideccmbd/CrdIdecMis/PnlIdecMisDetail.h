/**
  * \file PnlIdecMisDetail.h
  * job handler for job PnlIdecMisDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISDETAIL_H
#define PNLIDECMISDETAIL_H

// IP custInclude --- INSERT

#define VecVIdecMisDetailDo PnlIdecMisDetail::VecVDo

#define ContIacIdecMisDetail PnlIdecMisDetail::ContIac
#define StatAppIdecMisDetail PnlIdecMisDetail::StatApp
#define StatShrIdecMisDetail PnlIdecMisDetail::StatShr
#define TagIdecMisDetail PnlIdecMisDetail::Tag

#define DpchAppIdecMisDetailData PnlIdecMisDetail::DpchAppData
#define DpchAppIdecMisDetailDo PnlIdecMisDetail::DpchAppDo
#define DpchEngIdecMisDetailData PnlIdecMisDetail::DpchEngData

/**
  * PnlIdecMisDetail
  */
class PnlIdecMisDetail : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecMisDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTCRYEDITCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecMisDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFTIT = 1;
		static const uint TXFSTA = 2;
		static const uint TXFSTO = 3;
		static const uint NUMFPUPCRY = 4;
		static const uint TXFCRY = 5;
		static const uint TXFREG = 6;
		static const uint TXFMUN = 7;
		static const uint TXFCMT = 8;

	public:
		ContIac(const string& TxfTit = "", const string& TxfSta = "", const string& TxfSto = "", const uint numFPupCry = 1, const string& TxfCry = "", const string& TxfReg = "", const string& TxfMun = "", const string& TxfCmt = "");

	public:
		string TxfTit;
		string TxfSta;
		string TxfSto;
		uint numFPupCry;
		string TxfCry;
		string TxfReg;
		string TxfMun;
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
		* StatApp (full: StatAppIdecMisDetail)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool PupCryAlt = false);
	};

	/**
		* StatShr (full: StatShrIdecMisDetail)
		*/
	class StatShr : public Block {

	public:
		static const uint TXFCRYVALID = 1;
		static const uint BUTSAVEAVAIL = 2;
		static const uint BUTSAVEACTIVE = 3;
		static const uint TXFTITACTIVE = 4;
		static const uint TXFSTAACTIVE = 5;
		static const uint TXFSTOACTIVE = 6;
		static const uint PUPCRYACTIVE = 7;
		static const uint BUTCRYEDITAVAIL = 8;
		static const uint TXFREGACTIVE = 9;
		static const uint TXFMUNACTIVE = 10;
		static const uint TXFCMTACTIVE = 11;

	public:
		StatShr(const bool TxfCryValid = false, const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxfTitActive = true, const bool TxfStaActive = true, const bool TxfStoActive = true, const bool PupCryActive = true, const bool ButCryEditAvail = true, const bool TxfRegActive = true, const bool TxfMunActive = true, const bool TxfCmtActive = true);

	public:
		bool TxfCryValid;
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxfTitActive;
		bool TxfStaActive;
		bool TxfStoActive;
		bool PupCryActive;
		bool ButCryEditAvail;
		bool TxfRegActive;
		bool TxfMunActive;
		bool TxfCmtActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecMisDetail)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecMisDetailData)
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
		* DpchAppDo (full: DpchAppIdecMisDetailDo)
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
		* DpchEngData (full: DpchEngIdecMisDetailData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint FEEDFPUPCRY = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;
		static const uint ALL = 7;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, Feed* feedFPupCry = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		Feed feedFPupCry;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButSaveAvail(DbsIdec* dbsidec);
	bool evalButSaveActive(DbsIdec* dbsidec);
	bool evalTxfTitActive(DbsIdec* dbsidec);
	bool evalTxfStaActive(DbsIdec* dbsidec);
	bool evalTxfStoActive(DbsIdec* dbsidec);
	bool evalPupCryActive(DbsIdec* dbsidec);
	bool evalButCryEditAvail(DbsIdec* dbsidec);
	bool evalTxfRegActive(DbsIdec* dbsidec);
	bool evalTxfMunActive(DbsIdec* dbsidec);
	bool evalTxfCmtActive(DbsIdec* dbsidec);

public:
	PnlIdecMisDetail(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecMisDetail();

public:
	ContIac contiac;
	StatShr statshr;

	Feed feedFPupCry;

	IdecMMission recMis;

	bool dirty;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshPupCry(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshTxfCry(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshCry(DbsIdec* dbsidec, set<uint>& moditems);

	void refreshRecMis(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButSaveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCryEditClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecMisUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
	bool handleCallIdecKlsAkeyMod_klsEq(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv);
};

#endif

