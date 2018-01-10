/**
  * \file PnlIdecUsgList.h
  * job handler for job PnlIdecUsgList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECUSGLIST_H
#define PNLIDECUSGLIST_H

// IP custInclude --- INSERT

#include "QryIdecUsgList.h"

#define VecVIdecUsgListDo PnlIdecUsgList::VecVDo

#define ContIacIdecUsgList PnlIdecUsgList::ContIac
#define ContInfIdecUsgList PnlIdecUsgList::ContInf
#define StatShrIdecUsgList PnlIdecUsgList::StatShr
#define StgIacIdecUsgList PnlIdecUsgList::StgIac
#define TagIdecUsgList PnlIdecUsgList::Tag

#define DpchAppIdecUsgListData PnlIdecUsgList::DpchAppData
#define DpchAppIdecUsgListDo PnlIdecUsgList::DpchAppDo
#define DpchEngIdecUsgListData PnlIdecUsgList::DpchEngData

/**
  * PnlIdecUsgList
  */
class PnlIdecUsgList : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecUsgListDo)
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
	  * ContIac (full: ContIacIdecUsgList)
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
	  * ContInf (full: ContInfIdecUsgList)
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
		* StatShr (full: StatShrIdecUsgList)
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
		* StgIac (full: StgIacIdecUsgList)
		*/
	class StgIac : public Block {

	public:
		static const uint TCOSRFWIDTH = 1;

	public:
		StgIac(const uint TcoSrfWidth = 100);

	public:
		uint TcoSrfWidth;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StgIac* comp);
		set<uint> diff(const StgIac* comp);
	};

	/**
		* Tag (full: TagIdecUsgList)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppData (full: DpchAppIdecUsgListData)
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
		QryIdecUsgList::StgIac stgiacqry;

	public:
		string getSrefsMask();

		void readXML(pthread_mutex_t* mScr, map<string,ubigint>& descr, xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	};

	/**
		* DpchAppDo (full: DpchAppIdecUsgListDo)
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
		* DpchEngData (full: DpchEngIdecUsgListData)
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
		DpchEngData(const ubigint jref = 0, ContIac* contiac = NULL, ContInf* continf = NULL, Feed* feedFCsiQst = NULL, Feed* feedFTos = NULL, StatShr* statshr = NULL, StgIac* stgiac = NULL, ListIdecQUsgList* rst = NULL, QryIdecUsgList::StatShr* statshrqry = NULL, QryIdecUsgList::StgIac* stgiacqry = NULL, const set<uint>& mask = {NONE});

	public:
		ContIac contiac;
		ContInf continf;
		Feed feedFCsiQst;
		Feed feedFTos;
		StatShr statshr;
		StgIac stgiac;
		ListIdecQUsgList rst;
		QryIdecUsgList::StatShr statshrqry;
		QryIdecUsgList::StgIac stgiacqry;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalButDeleteActive(DbsIdec* dbsidec);

public:
	PnlIdecUsgList(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecUsgList();

public:
	ContIac contiac;
	ContInf continf;
	StatShr statshr;
	StgIac stgiac;

	Feed feedFCsiQst;
	Feed feedFTos;

	QryIdecUsgList* qry;

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
	void handleDpchAppDataStgiacqry(DbsIdec* dbsidec, QryIdecUsgList::StgIac* _stgiacqry, DpchEngIdec** dpcheng);

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

