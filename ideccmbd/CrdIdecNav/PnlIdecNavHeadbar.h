/**
  * \file PnlIdecNavHeadbar.h
  * job handler for job PnlIdecNavHeadbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECNAVHEADBAR_H
#define PNLIDECNAVHEADBAR_H

// IP custInclude --- INSERT

#define StatShrIdecNavHeadbar PnlIdecNavHeadbar::StatShr
#define StgInfIdecNavHeadbar PnlIdecNavHeadbar::StgInf
#define TagIdecNavHeadbar PnlIdecNavHeadbar::Tag

#define DpchEngIdecNavHeadbarData PnlIdecNavHeadbar::DpchEngData

/**
  * PnlIdecNavHeadbar
  */
class PnlIdecNavHeadbar : public JobIdec {

public:
	/**
		* StatShr (full: StatShrIdecNavHeadbar)
		*/
	class StatShr : public Block {

	public:
		static const uint MENCRDAVAIL = 1;

	public:
		StatShr(const bool MenCrdAvail = true);

	public:
		bool MenCrdAvail;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* StgInf (full: StgInfIdecNavHeadbar)
		*/
	class StgInf {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* Tag (full: TagIdecNavHeadbar)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchEngData (full: DpchEngIdecNavHeadbarData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint STATSHR = 2;
		static const uint STGINF = 3;
		static const uint TAG = 4;
		static const uint ALL = 5;

	public:
		DpchEngData(const ubigint jref = 0, StatShr* statshr = NULL, const set<uint>& mask = {NONE});

	public:
		StatShr statshr;

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

	bool evalMenCrdAvail(DbsIdec* dbsidec);
	bool evalMspCrd1Avail(DbsIdec* dbsidec);
	bool evalMitCrdUsgAvail(DbsIdec* dbsidec);
	bool evalMitCrdUsrAvail(DbsIdec* dbsidec);
	bool evalMitCrdScfAvail(DbsIdec* dbsidec);
	bool evalMitCrdUtlAvail(DbsIdec* dbsidec);
	bool evalMspCrd2Avail(DbsIdec* dbsidec);
	bool evalMitCrdMisAvail(DbsIdec* dbsidec);
	bool evalMitCrdTouAvail(DbsIdec* dbsidec);
	bool evalMitCrdIaqAvail(DbsIdec* dbsidec);
	bool evalMitCrdAd1Avail(DbsIdec* dbsidec);
	bool evalMitCrdFilAvail(DbsIdec* dbsidec);

public:
	PnlIdecNavHeadbar(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecNavHeadbar();

public:
	StatShr statshr;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	DpchEngIdec* getNewDpchEng(set<uint> items);

	void refresh(DbsIdec* dbsidec, set<uint>& moditems);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	void handleDpchAppIdecInit(DbsIdec* dbsidec, DpchAppIdecInit* dpchappidecinit, DpchEngIdec** dpcheng);

};

#endif

