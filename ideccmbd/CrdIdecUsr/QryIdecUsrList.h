/**
  * \file QryIdecUsrList.h
  * job handler for job QryIdecUsrList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef QRYIDECUSRLIST_H
#define QRYIDECUSRLIST_H

// IP custInclude --- INSERT

#define VecVQryIdecUsrListOrd QryIdecUsrList::VecVOrd

#define StatAppQryIdecUsrList QryIdecUsrList::StatApp
#define StatShrQryIdecUsrList QryIdecUsrList::StatShr
#define StgIacQryIdecUsrList QryIdecUsrList::StgIac

/**
  * QryIdecUsrList
  */
class QryIdecUsrList : public JobIdec {

public:
	/**
		* VecVOrd (full: VecVQryIdecUsrListOrd)
		*/
	class VecVOrd {

	public:
		static const uint PRS = 1;
		static const uint SRF = 2;
		static const uint USG = 3;
		static const uint STE = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static void fillFeed(Feed& feed);
	};

	/**
		* StatApp (full: StatAppQryIdecUsrList)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint firstcol = 1, const uint jnumFirstdisp = 1, const uint ncol = 9, const uint ndisp = 25);
	};

	/**
		* StatShr (full: StatShrQryIdecUsrList)
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
		* StgIac (full: StgIacQryIdecUsrList)
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
	QryIdecUsrList(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~QryIdecUsrList();

public:
	StatShr statshr;
	StgIac stgiac;

	ListIdecQUsrList rst;

	uint ixIdecVQrystate;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	void refreshJnum();

	void rerun(DbsIdec* dbsidec, const bool call = false);
	void rerun_filtSQL(string& sqlstr, const ubigint prePrs, const string& preSrf, const ubigint preUsg, const uint preSte, const bool addwhere);
	void rerun_filtSQL_append(string& sqlstr, bool& first);
	void rerun_orderSQL(string& sqlstr, const uint preIxOrd);

	void fetch(DbsIdec* dbsidec);

	uint getJnumByRef(const ubigint ref);
	ubigint getRefByJnum(const uint jnum);
	IdecQUsrList* getRecByJnum(const uint jnum);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	bool handleRerun(DbsIdec* dbsidec);
	bool handleShow(DbsIdec* dbsidec);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStubChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecUsrMod(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecUsrUpd_refEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

