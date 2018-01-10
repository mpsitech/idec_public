/**
  * \file PnlIdecTouDetail.h
  * job handler for job PnlIdecTouDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECTOUDETAIL_H
#define PNLIDECTOUDETAIL_H

// IP custInclude --- INSERT

#define VecVIdecTouDetailDo PnlIdecTouDetail::VecVDo

#define ContIacIdecTouDetail PnlIdecTouDetail::ContIac
#define ContInfIdecTouDetail PnlIdecTouDetail::ContInf
#define StatAppIdecTouDetail PnlIdecTouDetail::StatApp
#define StatShrIdecTouDetail PnlIdecTouDetail::StatShr
#define TagIdecTouDetail PnlIdecTouDetail::Tag

#define DpchAppIdecTouDetailData PnlIdecTouDetail::DpchAppData
#define DpchAppIdecTouDetailDo PnlIdecTouDetail::DpchAppDo
#define DpchEngIdecTouDetailData PnlIdecTouDetail::DpchEngData

/**
  * PnlIdecTouDetail
  */
class PnlIdecTouDetail : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecTouDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTMISVIEWCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecTouDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFTIT = 1;
		static const uint TXFSTA = 2;
		static const uint TXFSTO = 3;
		static const uint TXFARE = 4;
		static const uint TXFTHE = 5;
		static const uint TXFPHI = 6;
		static const uint TXFCMT = 7;

	public:
		ContIac(const string& TxfTit = "", const string& TxfSta = "", const string& TxfSto = "", const string& TxfAre = "", const string& TxfThe = "", const string& TxfPhi = "", const string& TxfCmt = "");

	public:
		string TxfTit;
		string TxfSta;
		string TxfSto;
		string TxfAre;
		string TxfThe;
		string TxfPhi;
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecTouDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTMIS = 1;

	public:
		ContInf(const string& TxtMis = "");

	public:
		string TxtMis;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecTouDetail)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecTouDetail)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTSAVEAVAIL = 1;
		static const uint BUTSAVEACTIVE = 2;
		static const uint TXFTITACTIVE = 3;
		static const uint TXTMISACTIVE = 4;
		static const uint BUTMISVIEWAVAIL = 5;
		static const uint BUTMISVIEWACTIVE = 6;
		static const uint TXFSTAACTIVE = 7;
		static const uint TXFSTOACTIVE = 8;
		static const uint TXFAREACTIVE = 9;
		static const uint TXFTHEACTIVE = 10;
		static const uint TXFPHIACTIVE = 11;
		static const uint TXFCMTACTIVE = 12;

	public:
		StatShr(const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxfTitActive = true, const bool TxtMisActive = true, const bool ButMisViewAvail = true, const bool ButMisViewActive = true, const bool TxfStaActive = true, const bool TxfStoActive = true, const bool TxfAreActive = true, const bool TxfTheActive = true, const bool TxfPhiActive = true, const bool TxfCmtActive = true);

	public:
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxfTitActive;
		bool TxtMisActive;
		bool ButMisViewAvail;
		bool ButMisViewActive;
		bool TxfStaActive;
		bool TxfStoActive;
		bool TxfAreActive;
		bool TxfTheActive;
		bool TxfPhiActive;
		bool TxfCmtActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecTouDetail)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecTouDetailData)
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
		* DpchAppDo (full: DpchAppIdecTouDetailDo)
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
		* DpchEngData (full: DpchEngIdecTouDetailData)
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
	bool evalTxfTitActive(DbsIdec* dbsidec);
	bool evalTxtMisActive(DbsIdec* dbsidec);
	bool evalButMisViewAvail(DbsIdec* dbsidec);
	bool evalButMisViewActive(DbsIdec* dbsidec);
	bool evalTxfStaActive(DbsIdec* dbsidec);
	bool evalTxfStoActive(DbsIdec* dbsidec);
	bool evalTxfAreActive(DbsIdec* dbsidec);
	bool evalTxfTheActive(DbsIdec* dbsidec);
	bool evalTxfPhiActive(DbsIdec* dbsidec);
	bool evalTxfCmtActive(DbsIdec* dbsidec);

public:
	PnlIdecTouDetail(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecTouDetail();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	IdecMTour recTou;

	bool dirty;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshRecTou(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButSaveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMisViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecTou_misEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv, bool& boolvalRet);
	bool handleCallIdecTouUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

