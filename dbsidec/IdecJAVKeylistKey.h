/**
  * \file IdecJAVKeylistKey.h
  * database access for table TblIdecJAVKeylistKey (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECJAVKEYLISTKEY_H
#define IDECJAVKEYLISTKEY_H

#include <sbecore/LiteDbs.h>

/**
  * IdecJAVKeylistKey: record of TblIdecJAVKeylistKey
  */
class IdecJAVKeylistKey {

public:
	IdecJAVKeylistKey(const ubigint ref = 0, const ubigint refIdecAVKeylistKey = 0, const uint x1IxIdecVLocale = 0, const string Title = "", const string Comment = "");

public:
	ubigint ref;
	ubigint refIdecAVKeylistKey;
	uint x1IxIdecVLocale;
	string Title;
	string Comment;

public:
	bool operator==(const IdecJAVKeylistKey& comp);
	bool operator!=(const IdecJAVKeylistKey& comp);
};

/**
  * ListIdecJAVKeylistKey: recordset of TblIdecJAVKeylistKey
  */
class ListIdecJAVKeylistKey {

public:
	ListIdecJAVKeylistKey();
	ListIdecJAVKeylistKey(const ListIdecJAVKeylistKey& src);
	~ListIdecJAVKeylistKey();

	void clear();
	unsigned int size() const;
	void append(IdecJAVKeylistKey* rec);

	IdecJAVKeylistKey* operator[](const uint ix);
	ListIdecJAVKeylistKey& operator=(const ListIdecJAVKeylistKey& src);
	bool operator==(const ListIdecJAVKeylistKey& comp);
	bool operator!=(const ListIdecJAVKeylistKey& comp);

public:
	vector<IdecJAVKeylistKey*> nodes;
};

/**
  * TblIdecJAVKeylistKey: C++ wrapper for table TblIdecJAVKeylistKey
  */
class TblIdecJAVKeylistKey {

public:

public:
	TblIdecJAVKeylistKey();
	virtual ~TblIdecJAVKeylistKey();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecJAVKeylistKey** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecJAVKeylistKey& rst);

	virtual void insertRec(IdecJAVKeylistKey* rec);
	ubigint insertNewRec(IdecJAVKeylistKey** rec = NULL, const ubigint refIdecAVKeylistKey = 0, const uint x1IxIdecVLocale = 0, const string Title = "", const string Comment = "");
	ubigint appendNewRecToRst(ListIdecJAVKeylistKey& rst, IdecJAVKeylistKey** rec = NULL, const ubigint refIdecAVKeylistKey = 0, const uint x1IxIdecVLocale = 0, const string Title = "", const string Comment = "");
	virtual void insertRst(ListIdecJAVKeylistKey& rst, bool transact = false);
	virtual void updateRec(IdecJAVKeylistKey* rec);
	virtual void updateRst(ListIdecJAVKeylistKey& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecJAVKeylistKey** rec);
	virtual bool loadRecByKlkLcl(ubigint refIdecAVKeylistKey, uint x1IxIdecVLocale, IdecJAVKeylistKey** rec);
	virtual ubigint loadRefsByKlk(ubigint refIdecAVKeylistKey, const bool append, vector<ubigint>& refs);
	virtual bool loadTitByKlkLcl(ubigint refIdecAVKeylistKey, uint x1IxIdecVLocale, string& Title);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecJAVKeylistKey& rst);
};

/**
  * LiteTblIdecJAVKeylistKey: C++ wrapper for table TblIdecJAVKeylistKey (SQLite database)
  */
class LiteTblIdecJAVKeylistKey : public TblIdecJAVKeylistKey, public LiteTable {

public:
	LiteTblIdecJAVKeylistKey();
	~LiteTblIdecJAVKeylistKey();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByKlkLcl;
	sqlite3_stmt* stmtLoadRefsByKlk;
	sqlite3_stmt* stmtLoadTitByKlkLcl;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecJAVKeylistKey** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecJAVKeylistKey& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecJAVKeylistKey** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecJAVKeylistKey** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecJAVKeylistKey& rst);

	void insertRec(IdecJAVKeylistKey* rec);
	void insertRst(ListIdecJAVKeylistKey& rst, bool transact = false);
	void updateRec(IdecJAVKeylistKey* rec);
	void updateRst(ListIdecJAVKeylistKey& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecJAVKeylistKey** rec);
	bool loadRecByKlkLcl(ubigint refIdecAVKeylistKey, uint x1IxIdecVLocale, IdecJAVKeylistKey** rec);
	ubigint loadRefsByKlk(ubigint refIdecAVKeylistKey, const bool append, vector<ubigint>& refs);
	bool loadTitByKlkLcl(ubigint refIdecAVKeylistKey, uint x1IxIdecVLocale, string& Title);
};

#endif

