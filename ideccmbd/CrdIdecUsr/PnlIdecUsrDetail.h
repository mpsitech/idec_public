/**
  * \file PnlIdecUsrDetail.h
  * job handler for job PnlIdecUsrDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSRDETAIL_H
#define PNLIDECUSRDETAIL_H

// IP custInclude --- INSERT

#define VecVIdecUsrDetailDo PnlIdecUsrDetail::VecVDo

#define ContIacIdecUsrDetail PnlIdecUsrDetail::ContIac
#define ContInfIdecUsrDetail PnlIdecUsrDetail::ContInf
#define StatAppIdecUsrDetail PnlIdecUsrDetail::StatApp
#define StatShrIdecUsrDetail PnlIdecUsrDetail::StatShr
#define TagIdecUsrDetail PnlIdecUsrDetail::Tag

#define DpchAppIdecUsrDetailData PnlIdecUsrDetail::DpchAppData
#define DpchAppIdecUsrDetailDo PnlIdecUsrDetail::DpchAppDo
#define DpchEngIdecUsrDetailData PnlIdecUsrDetail::DpchEngData

/**
  * PnlIdecUsrDetail
  */
class PnlIdecUsrDetail : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecUsrDetailDo)
		*/
	class VecVDo {

	public:
		static const uint BUTSAVECLICK = 1;
		static const uint BUTUSGVIEWCLICK = 2;
		static const uint BUTJEDITCLICK = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecUsrDetail)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFPUPJ = 1;
		static const uint NUMFPUPSTE = 2;
		static const uint NUMFPUPLCL = 3;
		static const uint NUMFPUPULV = 4;
		static const uint TXFPWD = 5;

	public:
		ContIac(const uint numFPupJ = 1, const uint numFPupSte = 1, const uint numFPupLcl = 1, const uint numFPupUlv = 1, const string& TxfPwd = "");

	public:
		uint numFPupJ;
		uint numFPupSte;
		uint numFPupLcl;
		uint numFPupUlv;
		string TxfPwd;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecUsrDetail)
	  */
	class ContInf : public Block {

	public:
		static const uint TXTPRS = 1;
		static const uint TXTSRF = 2;
		static const uint TXTUSG = 3;

	public:
		ContInf(const string& TxtPrs = "", const string& TxtSrf = "", const string& TxtUsg = "");

	public:
		string TxtPrs;
		string TxtSrf;
		string TxtUsg;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecUsrDetail)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVExpstate = VecIdecVExpstate::MIND);
	};

	/**
		* StatShr (full: StatShrIdecUsrDetail)
		*/
	class StatShr : public Block {

	public:
		static const uint BUTSAVEAVAIL = 1;
		static const uint BUTSAVEACTIVE = 2;
		static const uint TXTPRSACTIVE = 3;
		static const uint TXTSRFACTIVE = 4;
		static const uint TXTUSGACTIVE = 5;
		static const uint BUTUSGVIEWAVAIL = 6;
		static const uint BUTUSGVIEWACTIVE = 7;
		static const uint PUPJACTIVE = 8;
		static const uint BUTJEDITAVAIL = 9;
		static const uint PUPSTEACTIVE = 10;
		static const uint PUPLCLACTIVE = 11;
		static const uint PUPULVACTIVE = 12;
		static const uint TXFPWDACTIVE = 13;

	public:
		StatShr(const bool ButSaveAvail = true, const bool ButSaveActive = true, const bool TxtPrsActive = true, const bool TxtSrfActive = true, const bool TxtUsgActive = true, const bool ButUsgViewAvail = true, const bool ButUsgViewActive = true, const bool PupJActive = true, const bool ButJEditAvail = true, const bool PupSteActive = true, const bool PupLclActive = true, const bool PupUlvActive = true, const bool TxfPwdActive = true);

	public:
		bool ButSaveAvail;
		bool ButSaveActive;
		bool TxtPrsActive;
		bool TxtSrfActive;
		bool TxtUsgActive;
		bool ButUsgViewAvail;
		bool ButUsgViewActive;
		bool PupJActive;
		bool ButJEditAvail;
		bool PupSteActive;
		bool PupLclActive;
		bool PupUlvActive;
		bool TxfPwdActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecUsrDetail)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecUsrDetailData)
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
		* DpchAppDo (full: DpchAppIdecUsrDetailDo)
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
		* DpchEngData (full: DpchEngIdecUsrDetailData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFPUPJ = 4;
		static const uint FEEDFPUPLCL = 5;
		static const uint FEEDFPUPSTE = 6;
		static const uint FEEDFPUPULV = 7;
		static const uint STATAPP = 8;
		static const uint STATSHR = 9;
		static const uint TAG = 10;
		static const uint ALL = 11;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFPupJ = NULL, Feed* feedFPupLcl = NULL, Feed* feedFPupSte = NULL, Feed* feedFPupUlv = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFPupJ;
		Feed feedFPupLcl;
		Feed feedFPupSte;
		Feed feedFPupUlv;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButSaveAvail(DbsIdec* dbsidec);
	bool evalButSaveActive(DbsIdec* dbsidec);
	bool evalTxtPrsActive(DbsIdec* dbsidec);
	bool evalTxtSrfActive(DbsIdec* dbsidec);
	bool evalTxtUsgActive(DbsIdec* dbsidec);
	bool evalButUsgViewAvail(DbsIdec* dbsidec);
	bool evalButUsgViewActive(DbsIdec* dbsidec);
	bool evalPupJActive(DbsIdec* dbsidec);
	bool evalButJEditAvail(DbsIdec* dbsidec);
	bool evalPupSteActive(DbsIdec* dbsidec);
	bool evalPupLclActive(DbsIdec* dbsidec);
	bool evalPupUlvActive(DbsIdec* dbsidec);
	bool evalTxfPwdActive(DbsIdec* dbsidec);

public:
	PnlIdecUsrDetail(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecUsrDetail();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;

	Feed feedFPupJ;
	Feed feedFPupLcl;
	Feed feedFPupSte;
	Feed feedFPupUlv;

	IdecMUser recUsr;

	IdecJMUserState recUsrJste;

	bool dirty;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refreshJ(DbsIdec* dbsidec, set<uint>& moditems);

	void refreshRecUsr(DbsIdec* dbsidec, set<uint>& moditems);
	void refreshRecUsrJste(DbsIdec* dbsidec, set<uint>& moditems);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);

	void handleDpchAppDoButSaveClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButUsgViewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButJEditClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecUsr_usgEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv, bool& boolvalRet);
	bool handleCallIdecUsrUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
	bool handleCallIdecUsrJsteMod_usrEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

