/**
  * \file PnlIdecAd1Headbar.h
  * job handler for job PnlIdecAd1Headbar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef PNLIDECAD1HEADBAR_H
#define PNLIDECAD1HEADBAR_H

// IP custInclude --- INSERT

#define StgInfIdecAd1Headbar PnlIdecAd1Headbar::StgInf
#define TagIdecAd1Headbar PnlIdecAd1Headbar::Tag

#define DpchEngIdecAd1HeadbarData PnlIdecAd1Headbar::DpchEngData

/**
  * PnlIdecAd1Headbar
  */
class PnlIdecAd1Headbar : public JobIdec {

public:
	/**
		* StgInf (full: StgInfIdecAd1Headbar)
		*/
	class StgInf {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* Tag (full: TagIdecAd1Headbar)
		*/
	class Tag {

	public:
		static void writeXML(const uint ixIdecVLocale, xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	};

	/**
		* DpchEngData (full: DpchEngIdecAd1HeadbarData)
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
	PnlIdecAd1Headbar(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~PnlIdecAd1Headbar();

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

