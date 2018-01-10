/**
  * \file CrdIdecIaq.h
  * job handler for job CrdIdecIaq (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef CRDIDECIAQ_H
#define CRDIDECIAQ_H

// IP custInclude --- INSERT

#include "PnlIdecIaqLive.h"
#include "PnlIdecIaqMech.h"
#include "PnlIdecIaqScill.h"
#include "PnlIdecIaqQcdsp.h"
#include "PnlIdecIaqHeadbar.h"

#define VecVIdecIaqDo CrdIdecIaq::VecVDo
#define VecVIdecIaqSge CrdIdecIaq::VecVSge

#define ContInfIdecIaq CrdIdecIaq::ContInf
#define StatAppIdecIaq CrdIdecIaq::StatApp
#define StatShrIdecIaq CrdIdecIaq::StatShr
#define TagIdecIaq CrdIdecIaq::Tag

#define DpchAppIdecIaqDo CrdIdecIaq::DpchAppDo
#define DpchEngIdecIaqData CrdIdecIaq::DpchEngData

/**
  * CrdIdecIaq
  */
class CrdIdecIaq : public JobIdec {

public:
	/**
		* VecVDo (full: VecVIdecIaqDo)
		*/
	class VecVDo {

	public:
		static const uint CLOSE = 1;
		static const uint MITAPPABTCLICK = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVSge (full: VecVIdecIaqSge)
		*/
	class VecVSge {

	public:
		static const uint IDLE = 1;
		static const uint ALRIDECABT = 2;
		static const uint CLOSE = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
	  * ContInf (full: ContInfIdecIaq)
	  */
	class ContInf : public Block {

	public:
		static const uint NUMFSGE = 1;
		static const uint MRLAPPHLP = 2;

	public:
		ContInf(const uint numFSge = 1, const string& MrlAppHlp = "");

	public:
		uint numFSge;
		string MrlAppHlp;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const ContInf* comp);
		set<uint> diff(const ContInf* comp);
	};

	/**
		* StatApp (full: StatAppIdecIaq)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint ixIdecVReqitmode = VecIdecVReqitmode::IDLE, const usmallint latency = 5, const string& shortMenu = "", const uint widthMenu = 0, const bool initdoneLive = false, const bool initdoneMech = false, const bool initdoneScill = false, const bool initdoneQcdsp = false, const bool initdoneHeadbar = false);
	};

	/**
		* StatShr (full: StatShrIdecIaq)
		*/
	class StatShr : public Block {

	public:
		static const uint JREFLIVE = 1;
		static const uint JREFMECH = 2;
		static const uint JREFSCILL = 3;
		static const uint JREFQCDSP = 4;
		static const uint JREFHEADBAR = 5;

	public:
		StatShr(const ubigint jrefLive = 0, const ubigint jrefMech = 0, const ubigint jrefScill = 0, const ubigint jrefQcdsp = 0, const ubigint jrefHeadbar = 0);

	public:
		ubigint jrefLive;
		ubigint jrefMech;
		ubigint jrefScill;
		ubigint jrefQcdsp;
		ubigint jrefHeadbar;

	public:
		void writeXML(pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* Tag (full: TagIdecIaq)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchAppDo (full: DpchAppIdecIaqDo)
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
		* DpchEngData (full: DpchEngIdecIaqData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint CONTINF = 2;
		static const uint FEEDFSGE = 3;
		static const uint STATAPP = 4;
		static const uint STATSHR = 5;
		static const uint TAG = 6;
		static const uint ALL = 7;

	public:
		DpchEngData(const ubigint jref = 0, ContInf* continf = NULL, Feed* feedFSge = NULL, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		ContInf continf;
		Feed feedFSge;
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

public:
	CrdIdecIaq(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale, const uint ixIdecVPreset = VecIdecVPreset::VOID, const ubigint preUref = 0);
	~CrdIdecIaq();

public:
	ContInf continf;
	StatShr statshr;

	Feed feedFMcbAlert;
	Feed feedFSge;

	PnlIdecIaqLive* pnllive;
	PnlIdecIaqMech* pnlmech;
	PnlIdecIaqScill* pnlscill;
	PnlIdecIaqQcdsp* pnlqcdsp;
	PnlIdecIaqHeadbar* pnlheadbar;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);
	void refresh(DbsIdec* dbsidec, set<uint>& moditems);
	void updatePreset(DbsIdec* dbsidec, const uint ixIdecVPreset, const ubigint jrefTrig, const bool notif = false);

public:
	void changeStage(DbsIdec* dbsidec, uint _ixVSge, DpchEngIdec** dpcheng = NULL);

	uint enterSgeIdle(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeIdle(DbsIdec* dbsidec);
	uint enterSgeAlridecabt(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeAlridecabt(DbsIdec* dbsidec);
	uint enterSgeClose(DbsIdec* dbsidec, const bool reenter);
	void leaveSgeClose(DbsIdec* dbsidec);

	string getSquawk(DbsIdec* dbsidec);

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

	void handleDpchAppDoClose(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppDoMitAppAbtClick(DbsIdec* dbsidec, DpchEngIdec** dpcheng);
	void handleDpchAppIdecAlert(DbsIdec* dbsidec, DpchAppIdecAlert* dpchappidecalert, DpchEngIdec** dpcheng);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecDlgClose(DbsIdec* dbsidec, const ubigint jrefTrig);
};

#endif

