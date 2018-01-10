/**
  * \file PnlIdecScfHeadbar.h
  * job handler for job PnlIdecScfHeadbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECSCFHEADBAR_H
#define PNLIDECSCFHEADBAR_H

// IP custInclude --- INSERT

#define StgInfIdecScfHeadbar PnlIdecScfHeadbar::StgInf
#define TagIdecScfHeadbar PnlIdecScfHeadbar::Tag

#define DpchEngIdecScfHeadbarData PnlIdecScfHeadbar::DpchEngData

/**
  * PnlIdecScfHeadbar
  */
class PnlIdecScfHeadbar : public JobIdec {

public:
	/**
		* StgInf (full: StgInfIdecScfHeadbar)
		*/
	class StgInf {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* Tag (full: TagIdecScfHeadbar)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchEngData (full: DpchEngIdecScfHeadbarData)
		*/
	class DpchEngData : public DpchEngIdec {

	public:
		static const uint JREF = 1;
		static const uint STGINF = 2;
		static const uint TAG = 3;
		static const uint ALL = 4;

	public:
		DpchEngData(const ubigint jref = 0, const set<uint>& mask = {NONE});

	public:

	public:
		string getSrefsMask();
		void merge(DpchEngIdec* dpcheng);

		void writeXML(const uint ixIdecVLocale, pthread_mutex_t* mScr, map<ubigint,string>& scr, map<string,ubigint>& descr, xmlTextWriter* wr);
	};

public:
	PnlIdecScfHeadbar(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecScfHeadbar();

public:

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

