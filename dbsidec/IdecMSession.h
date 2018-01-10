/**
  * \file IdecMSession.h
  * database access for table TblIdecMSession (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMSESSION_H
#define IDECMSESSION_H

#include <sbecore/LiteDbs.h>

/**
  * IdecMSession: record of TblIdecMSession
  */
class IdecMSession {

public:
	IdecMSession(const ubigint ref = 0, const ubigint refIdecMUser = 0, const uint start = 0, const uint stop = 0, const string Ip = "");

public:
	ubigint ref;
	ubigint refIdecMUser;
	uint start;
	uint stop;
	string Ip;

public:
	bool operator==(const IdecMSession& comp);
	bool operator!=(const IdecMSession& comp);
};

/**
  * ListIdecMSession: recordset of TblIdecMSession
  */
class ListIdecMSession {

public:
	ListIdecMSession();
	ListIdecMSession(const ListIdecMSession& src);
	~ListIdecMSession();

	void clear();
	unsigned int size() const;
	void append(IdecMSession* rec);

	IdecMSession* operator[](const uint ix);
	ListIdecMSession& operator=(const ListIdecMSession& src);
	bool operator==(const ListIdecMSession& comp);
	bool operator!=(const ListIdecMSession& comp);

public:
	vector<IdecMSession*> nodes;
};

/**
  * TblIdecMSession: C++ wrapper for table TblIdecMSession
  */
class TblIdecMSession {

public:

public:
	TblIdecMSession();
	virtual ~TblIdecMSession();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMSession** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMSession& rst);

	virtual void insertRec(IdecMSession* rec);
	ubigint insertNewRec(IdecMSession** rec = NULL, const ubigint refIdecMUser = 0, const uint start = 0, const uint stop = 0, const string Ip = "");
	ubigint appendNewRecToRst(ListIdecMSession& rst, IdecMSession** rec = NULL, const ubigint refIdecMUser = 0, const uint start = 0, const uint stop = 0, const string Ip = "");
	virtual void insertRst(ListIdecMSession& rst, bool transact = false);
	virtual void updateRec(IdecMSession* rec);
	virtual void updateRst(ListIdecMSession& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMSession** rec);
	virtual ubigint loadRefsByUsr(ubigint refIdecMUser, const bool append, vector<ubigint>& refs);
	virtual ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecMSession& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMSession& rst);
};

/**
  * LiteTblIdecMSession: C++ wrapper for table TblIdecMSession (SQLite database)
  */
class LiteTblIdecMSession : public TblIdecMSession, public LiteTable {

public:
	LiteTblIdecMSession();
	~LiteTblIdecMSession();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRefsByUsr;
	sqlite3_stmt* stmtLoadRstByUsr;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMSession** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMSession& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMSession** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecMSession& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMSession** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMSession& rst);

	void insertRec(IdecMSession* rec);
	void insertRst(ListIdecMSession& rst, bool transact = false);
	void updateRec(IdecMSession* rec);
	void updateRst(ListIdecMSession& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMSession** rec);
	ubigint loadRefsByUsr(ubigint refIdecMUser, const bool append, vector<ubigint>& refs);
	ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecMSession& rst);
};

#endif

