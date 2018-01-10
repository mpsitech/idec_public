/**
  * \file QryIdecMisRef1NFile.h
  * job handler for job QryIdecMisRef1NFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef QRYIDECMISREF1NFILE_H
#define QRYIDECMISREF1NFILE_H

// IP custInclude --- INSERT

#define StatAppQryIdecMisRef1NFile QryIdecMisRef1NFile::StatApp
#define StatShrQryIdecMisRef1NFile QryIdecMisRef1NFile::StatShr
#define StgIacQryIdecMisRef1NFile QryIdecMisRef1NFile::StgIac

/**
  * QryIdecMisRef1NFile
  */
class QryIdecMisRef1NFile : public JobIdec {

public:
	/**
		* StatApp (full: StatAppQryIdecMisRef1NFile)
		*/
	class StatApp {

	public:
		static void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true, const uint firstcol = 1, const uint jnumFirstdisp = 1, const uint ncol = 1, const uint ndisp = 10);
	};

	/**
		* StatShr (full: StatShrQryIdecMisRef1NFile)
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
		* StgIac (full: StgIacQryIdecMisRef1NFile)
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
	QryIdecMisRef1NFile(XchgIdec* xchg, DbsIdec* dbsidec, const ubigint jrefSup, const uint ixIdecVLocale);
	~QryIdecMisRef1NFile();

public:
	StatShr statshr;
	StgIac stgiac;

	ListIdecQMisRef1NFile rst;

	uint ixIdecVQrystate;

	// IP custVar --- INSERT

public:
	// IP cust --- INSERT

public:
	void refreshJnum();

	void rerun(DbsIdec* dbsidec, const bool call = false);

	void fetch(DbsIdec* dbsidec);

	uint getJnumByRef(const ubigint ref);
	ubigint getRefByJnum(const uint jnum);
	IdecQMisRef1NFile* getRecByJnum(const uint jnum);

public:

	void handleRequest(DbsIdec* dbsidec, ReqIdec* req);

	bool handleRerun(DbsIdec* dbsidec);
	bool handleShow(DbsIdec* dbsidec);

	void handleCall(DbsIdec* dbsidec, Call* call);

	bool handleCallIdecStubChg(DbsIdec* dbsidec, const ubigint jrefTrig);
	bool handleCallIdecFilMod_retReuEq(DbsIdec* dbsidec, const ubigint jrefTrig, const uint ixInv, const ubigint refInv);
};

#endif

