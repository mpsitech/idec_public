/**
  * \file PnlIdecFilDetail.h
  * job handler for job PnlIdecFilDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECFILDETAIL_H
#define PNLIDECFILDETAIL_H

// IP custInclude --- INSERT

#define VecVIdecFilDetailDo PnlIdecFilDetail::VecVDo

#define ContIacIdecFilDetail PnlIdecFilDetail::ContIac
#define ContInfIdecFilDetail PnlIdecFilDetail::ContInf
#define StatAppIdecFilDetail PnlIdecFilDetail::StatApp
#define StatShrIdecFilDetail PnlIdecFilDetail::StatShr
#define TagIdecFilDetail PnlIdecFilDetail::Tag

#define DpchAppIdecFilDetailData PnlIdecFilDetail::DpchAppData
#define DpchAppIdecFilDetailDo PnlIdecFilDetail::DpchAppDo
#define DpchEngIdecFilDetailData PnlIdecFilDetail::DpchEngData

/**
  * PnlIdecFilDetail
  */
class PnlIdecFilDetail : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecFilDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTCLUVIEWCLICK = 2;
		static const uint BUTCLUCLUSTERCLICK = 3;
		static const uint BUTCLUUNCLUSTERCLICK = 4;
		static const uint BUTREUVIEWCLICK = 5;
		static const uint BUTCNTEDITCLICK = 6;
		static const uint BUTMIMEDITCLICK = 7;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecFilDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint TXFFNM = 1;
		static const uint NUMFLSTCLU = 2;
		static const uint NUMFPUPRET = 3;
		static const uint NUMFPUPCNT = 4;
		static const uint TXFCNT = 5;
		static const uint TXFACV = 6;
		static const uint TXFANM = 7;
		static const uint NUMFPUPMIM = 8;
		static const uint TXFMIM = 9;
		static const uint TXFSIZ = 10;
		static const uint TXFCMT = 11;

	public:
		ContIac(const string& TxfFnm = "", const uint numFLstClu = 1, const uint numFPupRet = 1, const uint numFPupCnt = 1, const string& TxfCnt = "", const string& TxfAcv = "", const string& TxfAnm = "", const uint numFPupMim = 1, const string& TxfMim = "", const string& TxfSiz = "", const string& TxfCmt = "");

	public:
		string TxfFnm;
		uint numFLstClu;
		uint numFPupRet;
		uint numFPupCnt;
		string TxfCnt;
		string TxfAcv;
		string TxfAnm;
		uint numFPupMim;
		string TxfMim;
		string TxfSiz;
		string TxfCmt;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecFilDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTCLU = 1;
		static const uint TXTREU = 2;

	public:
		ContInf(const string& TxtClu = "", const string& TxtReu = "");

	public:
		string TxtClu;
		string TxtReu;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecFilDetail)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool LstCluAlt = true, const bool PupCntAlt = false, const bool PupMimAlt = false, const uint LstCluNumFirstdisp = 1);
	};

	/**
		* StatShr (full: StatShrIdecFilDetail)
		*/
	class StatShr : public Block {

	public:
		static const uint TXFCNTVALID = 1;
		static const uint TXFMIMVALID = 2;
		static const uint BUTSAVEAVAIL = 3;
		static const uint BUTSAVEACTIVE = 4;
		static const uint TXFFNMACTIVE = 5;
		static const uint LSTCLUACTIVE = 6;
		static const uint BUTCLUVIEWACTIVE = 7;
		static const uint BUTCLUCLUSTERAVAIL = 8;
		static const uint BUTCLUUNCLUSTERAVAIL = 9;
		static const uint TXTREUACTIVE = 10;
		static const uint BUTREUVIEWAVAIL = 11;
		static const uint BUTREUVIEWACTIVE = 12;
		static const uint PUPCNTACTIVE = 13;
		static const uint BUTCNTEDITAVAIL = 14;
		static const uint TXFACVACTIVE = 15;
		static const uint TXFANMACTIVE = 16;
		static const uint PUPMIMACTIVE = 17;
		static const uint BUTMIMEDITAVAIL = 18;
		static const uint TXFSIZACTIVE = 19;
		static const uint TXFCMTACTIVE = 20;

	public:
		StatShr(const bool TxfCntValid = false, const bool TxfMimValid = false, const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxfFnmActive = true, const bool LstCluActive = true, const bool ButCluViewActive = true, const bool ButCluClusterAvail = true, const bool ButCluUnclusterAvail = true, const bool TxtReuActive = true, const bool ButReuViewAvail = true, const bool ButReuViewActive = true, const bool PupCntActive = true, const bool ButCntEditAvail = true, const bool TxfAcvActive = true, const bool TxfAnmActive = true, const bool PupMimActive = true, const bool ButMimEditAvail = true, const bool TxfSizActive = true, const bool TxfCmtActive = true);

	public:
		bool TxfCntValid;
		bool TxfMimValid;
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxfFnmActive;
		bool LstCluActive;
		bool ButCluViewActive;
		bool ButCluClusterAvail;
		bool ButCluUnclusterAvail;
		bool TxtReuActive;
		bool ButReuViewAvail;
		bool ButReuViewActive;
		bool PupCntActive;
		bool ButCntEditAvail;
		bool TxfAcvActive;
		bool TxfAnmActive;
		bool PupMimActive;
		bool ButMimEditAvail;
		bool TxfSizActive;
		bool TxfCmtActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecFilDetail)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecFilDetailData)
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
		* DpchAppDo (full: DpchAppIdecFilDetailDo)
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
		* DpchEngData (full: DpchEngIdecFilDetailData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFLSTCLU = 4;
		static const uint FEEDFPUPCNT = 5;
		static const uint FEEDFPUPMIM = 6;
		static const uint FEEDFPUPRET = 7;
		static const uint STATAPP = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;
		static const uint ALL = 11;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFLstClu = NULL, Feed* feedFPupCnt = NULL, Feed* feedFPupMim = NULL, Feed* feedFPupRet = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFLstClu;
		Feed feedFPupCnt;
		Feed feedFPupMim;
		Feed feedFPupRet;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButSaveAvail(DbsIdec* dbsidec);
	bool evalButSaveActive(DbsIdec* dbsidec);
	bool evalTxfFnmActive(DbsIdec* dbsidec);
	bool evalLstCluActive(DbsIdec* dbsidec);
	bool evalButCluViewActive(DbsIdec* dbsidec);
	bool evalButCluClusterAvail(DbsIdec* dbsidec);
	bool evalButCluUnclusterAvail(DbsIdec* dbsidec);
	bool evalTxtReuActive(DbsIdec* dbsidec);
	bool evalButReuViewAvail(DbsIdec* dbsidec);
	bool evalButReuViewActive(DbsIdec* dbsidec);
	bool evalPupCntActive(DbsIdec* dbsidec);
	bool evalButCntEditAvail(DbsIdec* dbsidec);
	bool evalTxfAcvActive(DbsIdec* dbsidec);
	bool evalTxfAnmActive(DbsIdec* dbsidec);
	bool evalPupMimActive(DbsIdec* dbsidec);
	bool evalButMimEditAvail(DbsIdec* dbsidec);
	bool evalTxfSizActive(DbsIdec* dbsidec);
	bool evalTxfCmtActive(DbsIdec* dbsidec);

public:
	PnlIdecFilDetail(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecFilDetail();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFLstClu;
	Feed feedFPupCnt;
	Feed feedFPupMim;
	Feed feedFPupRet;

	IdecMFile recFil;

	bool dirty;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshLstClu(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshClu(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshPupCnt(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshTxfCnt(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshCnt(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshPupMim(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshTxfMim(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshMim(DbsIdec* dbsidec, set<uint>& moditems);

	void refreshRecFil(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButSaveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCluViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCluClusterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCluUnclusterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButReuViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButCntEditClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButMimEditClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecFil_cluEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv, bool& boolvalRet);
	bool handleCallIdecFil_retEq(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, bool& boolvalRet);
	bool handleCallIdecFil_reuEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv, bool& boolvalRet);
	bool handleCallIdecFilUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
	bool handleCallIdecKlsAkeyMod_klsEq(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv);
	bool handleCallIdecFilMod_cluEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

