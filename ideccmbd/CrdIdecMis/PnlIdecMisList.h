/**
  * \file PnlIdecMisList.h
  * job handler for job PnlIdecMisList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECMISLIST_H
#define PNLIDECMISLIST_H

// IP custInclude --- INSERT

#include "QryIdecMisList.h"

#define VecVIdecMisListDo PnlIdecMisList::VecVDo

#define ContIacIdecMisList PnlIdecMisList::ContIac
#define ContInfIdecMisList PnlIdecMisList::ContInf
#define StatShrIdecMisList PnlIdecMisList::StatShr
#define StgIacIdecMisList PnlIdecMisList::StgIac
#define TagIdecMisList PnlIdecMisList::Tag

#define DpchAppIdecMisListData PnlIdecMisList::DpchAppData
#define DpchAppIdecMisListDo PnlIdecMisList::DpchAppDo
#define DpchEngIdecMisListData PnlIdecMisList::DpchEngData

/**
  * PnlIdecMisList
  */
class PnlIdecMisList : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecMisListDo)
		*/
	class VecVDo {

	public:
		static const uint BUTMINIMIZECLICK = 1;
		static const uint BUTREGULARIZECLICK = 2;
		static const uint BUTNEWCLICK = 3;
		static const uint BUTDELETECLICK = 4;
		static const uint BUTFILTERCLICK = 5;
		static const uint BUTREFRESHCLICK = 6;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
	  * ContIac (full: ContIacIdecMisList)
	  */
	class ContIac : public Block {

	public:
		static const uint NUMFTOS = 1;

	public:
		ContIac(const uint numFTos = 1);

	public:
		uint numFTos;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContIac* comp);
		set<uint> diff(const ContIac* comp);
	};

	/**
	  * ContInf (full: ContInfIdecMisList)
	  */
	class ContInf : public Block {

	public:
		static const uint BUTFILTERON = 1;
		static const uint NUMFCSIQST = 2;

	public:
		ContInf(const bool ButFilterOn = false, const uint numFCsiQst = 1);

	public:
		bool ButFilterOn;
		uint numFCsiQst;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatShr (full: StatShrIdecMisList)
		*/
	class StatShr : public Block {

	public:
		static const uint IXIDECVEXPSTATE = 1;
		static const uint BUTDELETEACTIVE = 2;

	public:
		StatShr(const uint ixIdecVExpstate = VecIdecVExpstate::MIND, const bool ButDeleteActive = true);

	public:
		uint ixIdecVExpstate;
		bool ButDeleteActive;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* StgIac (full: StgIacIdecMisList)
		*/
	class StgIac : public Block {

	public:
		static const uint TCOTITWIDTH = 1;
		static const uint TCOGRPWIDTH = 2;
		static const uint TCOOWNWIDTH = 3;
		static const uint TCOSTAWIDTH = 4;
		static const uint TCOSTOWIDTH = 5;
		static const uint TCOCRYWIDTH = 6;
		static const uint TCOREGWIDTH = 7;
		static const uint TCOMUNWIDTH = 8;

	public:
		StgIac(const uint TcoTitWidth = 100, const uint TcoGrpWidth = 100, const uint TcoOwnWidth = 100, const uint TcoStaWidth = 100, const uint TcoStoWidth = 100, const uint TcoCryWidth = 100, const uint TcoRegWidth = 100, const uint TcoMunWidth = 100);

	public:
		uint TcoTitWidth;
		uint TcoGrpWidth;
		uint TcoOwnWidth;
		uint TcoStaWidth;
		uint TcoStoWidth;
		uint TcoCryWidth;
		uint TcoRegWidth;
		uint TcoMunWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StgIac* comp);
		set<uint> diff(const StgIac* comp);
	};

	/**
		* Tag (full: TagIdecMisList)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecMisListData)
		*/
	class DpchAppData : public DpchAppIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint STGIAC = 3;
		static const uint STGIACQRY = 4;

	public:
		DpchAppData();

	public:
		ContIac contiac;
		StgIac stgiac;
		QryIdecMisList::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecMisListDo)
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
		* DpchEngData (full: DpchEngIdecMisListData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTIAC = 2;
		static const uint CONTINF = 3;
		static const uint FEEDFCSIQST = 4;
		static const uint FEEDFTOS = 5;
		static const uint STATSHR = 6;
		static const uint STGIAC = 7;
		static const uint TAG = 8;
		static const uint RST = 9;
		static const uint STATAPPQRY = 10;
		static const uint STATSHRQRY = 11;
		static const uint STGIACQRY = 12;
		static const uint ALL = 13;

	public:
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFCsiQst = NULL, Feed* feedFTos = NULL, StatShr* statshr = NULL, StgIac* stgiac = NULL, ListIdecQMisList* rst = NULL, QryIdecMisList::StatShr* statshrqry = NULL, QryIdecMisList::StgIac* stgiacqry = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiQst;
		Feed feedFTos;
		StatShr statshr;
		StgIac stgiac;
		ListIdecQMisList rst;
		QryIdecMisList::StatShr statshrqry;
		QryIdecMisList::StgIac stgiacqry;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButDeleteActive(DbsIdec* dbsidec);

public:
	PnlIdecMisList(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecMisList();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;
	StgIac stgiac;

	Feed feedFCsiQst;
	Feed feedFTos;

	QryIdecMisList* qry;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);
	void minimize(DbsIdec* dbsidec, const bool notif = false, DpchEngIdec** dpcheng = NULL);
	void regularize(DbsIdec* dbsidec, const bool notif = false, DpchEngIdec** dpcheng = NULL);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);
	void handleDpchAppDataContiac(DbsIdec* dbsidec, ContIac* _contiac, DpchEngIdec** dpcheng);
	void handleDpchAppDataStgiac(DbsIdec* dbsidec, StgIac* _stgiac, DpchEngIdec** dpcheng);
	void handleDpchAppDataStgiacqry(DbsIdec* dbsidec, QryIdecMisList::StgIac* _stgiacqry, DpchEngIdec** dpcheng);

	void handleDpchAppDoButMinimizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButRegularizeClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButNewClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButDeleteClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButFilterClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoButRefreshClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStatChg(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

