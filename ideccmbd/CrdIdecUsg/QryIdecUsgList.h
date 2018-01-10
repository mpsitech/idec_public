/**
  * \file QryIdecUsgList.h
  * job handler for job QryIdecUsgList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef QRYIDECUSGLIST_H
#define QRYIDECUSGLIST_H

// IP custInclude --- INSERT

#define VecVQryIdecUsgListOrd QryIdecUsgList::VecVOrd

#define StatAppQryIdecUsgList QryIdecUsgList::StatApp
#define StatShrQryIdecUsgList QryIdecUsgList::StatShr
#define StgIacQryIdecUsgList QryIdecUsgList::StgIac

/**
  * QryIdecUsgList
  */
class QryIdecUsgList : public JobIdec {

public:
	/**
		* VecVOrd (full: VecVQryIdecUsgListOrd)
		*/
	class VecVOrd {

	public:
		static const uint SRF = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
		* StatApp (full: StatAppQryIdecUsgList)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint firstcol = 1, const uint jnumFirstdisp = 1, const uint ncol = 1, const uint ndisp = 25);
	};

	/**
		* StatShr (full: StatShrQryIdecUsgList)
		*/
	class StatShr : public Block {

	public:
		static const uint NTOT = 1;
		static const uint JNUMFIRSTLOAD = 2;
		static const uint NLOAD = 3;

	public:
		StatShr(const uint ntot = 0, const uint jnumFirstload = 0, const uint nload = 0);

	public:
		uint ntot;
		uint jnumFirstload;
		uint nload;

	public:
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StatShr* comp);
		set<uint> diff(const StatShr* comp);
	};

	/**
		* StgIac (full: StgIacQryIdecUsgList)
		*/
	class StgIac : public Block {

	public:
		static const uint JNUM = 1;
		static const uint JNUMFIRSTLOAD = 2;
		static const uint NLOAD = 3;

	public:
		StgIac(const uint jnum = 0, const uint jnumFirstload = 1, const uint nload = 100);

	public:
		uint jnum;
		uint jnumFirstload;
		uint nload;

	public:
		bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
		void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
		set<uint> comm(const StgIac* comp);
		set<uint> diff(const StgIac* comp);
	};

public:
	QryIdecUsgList(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~QryIdecUsgList();

public:
	StatShr statshr;
	StgIac stgiac;

	ListIdecQUsgList rst;

	uint ixIdecVQrystate;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	void refreshJnum();

	void rerun(DbsIdec* dbsidec, const bool call = false);
	void rerun_filtSQL(string& sqlstr, const string& preSrf, const bool addwhere);
	void rerun_filtSQL_append(string& sqlstr, bool& first);

	void fetch(DbsIdec* dbsidec);

	uint getJnumByRef(const ubigint ref);
	ubigint getRefByJnum(const uint jnum);
	IdecQUsgList* getRecByJnum(const uint jnum);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	bool handleRerun(DbsIdec* dbsidec);
	bool handleShow(DbsIdec* dbsidec);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStubChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecUsgMod(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecUsgUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

