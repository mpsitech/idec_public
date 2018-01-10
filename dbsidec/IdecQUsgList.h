/**
  * \file IdecQUsgList.h
  * Dbs and XML wrapper for table TblIdecQUsgList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSGLIST_H
#define IDECQUSGLIST_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsgList: record of TblIdecQUsgList
  */
class IdecQUsgList {

public:
	IdecQUsgList(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string sref = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	string sref;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQUsgList: recordset of TblIdecQUsgList
  */
class ListIdecQUsgList {

public:
	ListIdecQUsgList();
	ListIdecQUsgList(const ListIdecQUsgList& src);
	~ListIdecQUsgList();

	void clear();
	unsigned int size() const;
	void append(IdecQUsgList* rec);

	ListIdecQUsgList& operator=(const ListIdecQUsgList& src);

public:
	vector<IdecQUsgList*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsgList: C++ wrapper for table TblIdecQUsgList
  */
class TblIdecQUsgList {

public:
	TblIdecQUsgList();
	virtual ~TblIdecQUsgList();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsgList** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsgList& rst);

	virtual void insertRec(IdecQUsgList* rec);
	ubigint insertNewRec(IdecQUsgList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string sref = "");
	ubigint appendNewRecToRst(ListIdecQUsgList& rst, IdecQUsgList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string sref = "");
	virtual void insertRst(ListIdecQUsgList& rst);
	virtual void updateRec(IdecQUsgList* rec);
	virtual void updateRst(ListIdecQUsgList& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsgList** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsgList& rst);
};

/**
  * LiteIdecQUsgList: C++ wrapper for table TblIdecQUsgList (SQLite database)
  */
class LiteTblIdecQUsgList : public TblIdecQUsgList, public LiteTable {

public:
	LiteTblIdecQUsgList();
	~LiteTblIdecQUsgList();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsgList** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsgList& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsgList** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsgList& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsgList** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsgList& rst);

	void insertRec(IdecQUsgList* rec);
	void insertRst(ListIdecQUsgList& rst);
	void updateRec(IdecQUsgList* rec);
	void updateRst(ListIdecQUsgList& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsgList** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsgList& rst);
};
#endif

