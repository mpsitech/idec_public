/**
  * \file IdecQFilList.h
  * Dbs and XML wrapper for table TblIdecQFilList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQFILLIST_H
#define IDECQFILLIST_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQFilList: record of TblIdecQFilList
  */
class IdecQFilList {

public:
	IdecQFilList(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Filename = "", const uint refIxVTbl = 0, const string srefRefIxVTbl = "", const string titRefIxVTbl = "", const ubigint refUref = 0, const string stubRefUref = "", const string osrefKContent = "", const string titOsrefKContent = "", const string srefKMimetype = "", const string titSrefKMimetype = "", const usmallint Size = 0);

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	string Filename;
	uint refIxVTbl;
	string srefRefIxVTbl;
	string titRefIxVTbl;
	ubigint refUref;
	string stubRefUref;
	string osrefKContent;
	string titOsrefKContent;
	string srefKMimetype;
	string titSrefKMimetype;
	usmallint Size;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQFilList: recordset of TblIdecQFilList
  */
class ListIdecQFilList {

public:
	ListIdecQFilList();
	ListIdecQFilList(const ListIdecQFilList& src);
	~ListIdecQFilList();

	void clear();
	unsigned int size() const;
	void append(IdecQFilList* rec);

	ListIdecQFilList& operator=(const ListIdecQFilList& src);

public:
	vector<IdecQFilList*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQFilList: C++ wrapper for table TblIdecQFilList
  */
class TblIdecQFilList {

public:
	TblIdecQFilList();
	virtual ~TblIdecQFilList();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQFilList** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQFilList& rst);

	virtual void insertRec(IdecQFilList* rec);
	ubigint insertNewRec(IdecQFilList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Filename = "", const uint refIxVTbl = 0, const string srefRefIxVTbl = "", const string titRefIxVTbl = "", const ubigint refUref = 0, const string stubRefUref = "", const string osrefKContent = "", const string titOsrefKContent = "", const string srefKMimetype = "", const string titSrefKMimetype = "", const usmallint Size = 0);
	ubigint appendNewRecToRst(ListIdecQFilList& rst, IdecQFilList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Filename = "", const uint refIxVTbl = 0, const string srefRefIxVTbl = "", const string titRefIxVTbl = "", const ubigint refUref = 0, const string stubRefUref = "", const string osrefKContent = "", const string titOsrefKContent = "", const string srefKMimetype = "", const string titSrefKMimetype = "", const usmallint Size = 0);
	virtual void insertRst(ListIdecQFilList& rst);
	virtual void updateRec(IdecQFilList* rec);
	virtual void updateRst(ListIdecQFilList& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQFilList** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQFilList& rst);
};

/**
  * LiteIdecQFilList: C++ wrapper for table TblIdecQFilList (SQLite database)
  */
class LiteTblIdecQFilList : public TblIdecQFilList, public LiteTable {

public:
	LiteTblIdecQFilList();
	~LiteTblIdecQFilList();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByQref;
	sqlite3_stmt* stmtRemoveRstByJref;

	sqlite3_stmt* stmtLoadRecByQref;
	sqlite3_stmt* stmtLoadRecByJref;
	sqlite3_stmt* stmtLoadRstByJref;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecQFilList** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQFilList& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQFilList** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQFilList& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQFilList** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQFilList& rst);

	void insertRec(IdecQFilList* rec);
	void insertRst(ListIdecQFilList& rst);
	void updateRec(IdecQFilList* rec);
	void updateRst(ListIdecQFilList& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQFilList** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQFilList& rst);
};
#endif

