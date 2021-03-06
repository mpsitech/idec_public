/**
  * \file QryIdecUsrAAccess.h
  * job handler for job QryIdecUsrAAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef QRYIDECUSRAACCESS_H
#define QRYIDECUSRAACCESS_H

// IP custInclude --- INSERT

#define StatAppQryIdecUsrAAccess QryIdecUsrAAccess::StatApp
#define StatShrQryIdecUsrAAccess QryIdecUsrAAccess::StatShr
#define StgIacQryIdecUsrAAccess QryIdecUsrAAccess::StgIac

/**
  * QryIdecUsrAAccess
  */
class QryIdecUsrAAccess : public JobIdec {

public:
	/**
		* StatApp (full: StatAppQryIdecUsrAAccess)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint firstcol = 1, const uint jnumFirstdisp = 1, const uint ncol = 4, const uint ndisp = 10);
	};

	/**
		* StatShr (full: StatShrQryIdecUsrAAccess)
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
		* StgIac (full: StgIacQryIdecUsrAAccess)
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
	QryIdecUsrAAccess(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~QryIdecUsrAAccess();

public:
	StatShr statshr;
	StgIac stgiac;

	ListIdecQUsrAAccess rst;

	uint ixIdecVQrystate;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	void refreshJnum();

	void rerun(DbsIdec* dbsidec, const bool call = false);
	void rerun_filtSQL(string& sqlstr, const uint preX1, const bool addwhere);
	void rerun_filtSQL_append(string& sqlstr, bool& first);

	void fetch(DbsIdec* dbsidec);

	uint getJnumByRef(const ubigint ref);
	ubigint getRefByJnum(const uint jnum);
	IdecQUsrAAccess* getRecByJnum(const uint jnum);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	bool handleRerun(DbsIdec* dbsidec);
	bool handleShow(DbsIdec* dbsidec);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStubChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecUsrAaccMod_usrEq(DbsIdec* dbsidec, const ubigint jrefTrig, const ubigint refInv);
};

#endif

