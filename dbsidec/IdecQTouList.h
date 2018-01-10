/**
  * \file IdecQTouList.h
  * Dbs and XML wrapper for table TblIdecQTouList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQTOULIST_H
#define IDECQTOULIST_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQTouList: record of TblIdecQTouList
  */
class IdecQTouList {

public:
	IdecQTouList(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Title = "", const ubigint refIdecMMission = 0, const string stubRefIdecMMission = "", const uint start = 0, const string ftmStart = "", const uint stop = 0, const string ftmStop = "", const string Area = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	string Title;
	ubigint refIdecMMission;
	string stubRefIdecMMission;
	uint start;
	string ftmStart;
	uint stop;
	string ftmStop;
	string Area;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQTouList: recordset of TblIdecQTouList
  */
class ListIdecQTouList {

public:
	ListIdecQTouList();
	ListIdecQTouList(const ListIdecQTouList& src);
	~ListIdecQTouList();

	void clear();
	unsigned int size() const;
	void append(IdecQTouList* rec);

	ListIdecQTouList& operator=(const ListIdecQTouList& src);

public:
	vector<IdecQTouList*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQTouList: C++ wrapper for table TblIdecQTouList
  */
class TblIdecQTouList {

public:
	TblIdecQTouList();
	virtual ~TblIdecQTouList();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQTouList** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQTouList& rst);

	virtual void insertRec(IdecQTouList* rec);
	ubigint insertNewRec(IdecQTouList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Title = "", const ubigint refIdecMMission = 0, const string stubRefIdecMMission = "", const uint start = 0, const string ftmStart = "", const uint stop = 0, const string ftmStop = "", const string Area = "");
	ubigint appendNewRecToRst(ListIdecQTouList& rst, IdecQTouList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Title = "", const ubigint refIdecMMission = 0, const string stubRefIdecMMission = "", const uint start = 0, const string ftmStart = "", const uint stop = 0, const string ftmStop = "", const string Area = "");
	virtual void insertRst(ListIdecQTouList& rst);
	virtual void updateRec(IdecQTouList* rec);
	virtual void updateRst(ListIdecQTouList& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQTouList** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQTouList& rst);
};

/**
  * LiteIdecQTouList: C++ wrapper for table TblIdecQTouList (SQLite database)
  */
class LiteTblIdecQTouList : public TblIdecQTouList, public LiteTable {

public:
	LiteTblIdecQTouList();
	~LiteTblIdecQTouList();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQTouList** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQTouList& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQTouList** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQTouList& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQTouList** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQTouList& rst);

	void insertRec(IdecQTouList* rec);
	void insertRst(ListIdecQTouList& rst);
	void updateRec(IdecQTouList* rec);
	void updateRst(ListIdecQTouList& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQTouList** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQTouList& rst);
};
#endif

