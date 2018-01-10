/**
  * \file IdecJMUserState.h
  * database access for table TblIdecJMUserState (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECJMUSERSTATE_H
#define IDECJMUSERSTATE_H

#include <sbecore/LiteDbs.h>

/**
  * IdecJMUserState: record of TblIdecJMUserState
  */
class IdecJMUserState {

public:
	IdecJMUserState(const ubigint ref = 0, const ubigint refIdecMUser = 0, const uint x1Startd = 0, const uint ixVState = 0);

public:
	ubigint ref;
	ubigint refIdecMUser;
	uint x1Startd;
	uint ixVState;

public:
	bool operator==(const IdecJMUserState& comp);
	bool operator!=(const IdecJMUserState& comp);
};

/**
  * ListIdecJMUserState: recordset of TblIdecJMUserState
  */
class ListIdecJMUserState {

public:
	ListIdecJMUserState();
	ListIdecJMUserState(const ListIdecJMUserState& src);
	~ListIdecJMUserState();

	void clear();
	unsigned int size() const;
	void append(IdecJMUserState* rec);

	IdecJMUserState* operator[](const uint ix);
	ListIdecJMUserState& operator=(const ListIdecJMUserState& src);
	bool operator==(const ListIdecJMUserState& comp);
	bool operator!=(const ListIdecJMUserState& comp);

public:
	vector<IdecJMUserState*> nodes;
};

/**
  * TblIdecJMUserState: C++ wrapper for table TblIdecJMUserState
  */
class TblIdecJMUserState {

public:

public:
	TblIdecJMUserState();
	virtual ~TblIdecJMUserState();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecJMUserState** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecJMUserState& rst);

	virtual void insertRec(IdecJMUserState* rec);
	ubigint insertNewRec(IdecJMUserState** rec = NULL, const ubigint refIdecMUser = 0, const uint x1Startd = 0, const uint ixVState = 0);
	ubigint appendNewRecToRst(ListIdecJMUserState& rst, IdecJMUserState** rec = NULL, const ubigint refIdecMUser = 0, const uint x1Startd = 0, const uint ixVState = 0);
	virtual void insertRst(ListIdecJMUserState& rst, bool transact = false);
	virtual void updateRec(IdecJMUserState* rec);
	virtual void updateRst(ListIdecJMUserState& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecJMUserState** rec);
	virtual bool loadRecByUsrSta(ubigint refIdecMUser, uint x1Startd, IdecJMUserState** rec);
	virtual ubigint loadRefsByUsr(ubigint refIdecMUser, const bool append, vector<ubigint>& refs);
	virtual ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecJMUserState& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecJMUserState& rst);
};

/**
  * LiteTblIdecJMUserState: C++ wrapper for table TblIdecJMUserState (SQLite database)
  */
class LiteTblIdecJMUserState : public TblIdecJMUserState, public LiteTable {

public:
	LiteTblIdecJMUserState();
	~LiteTblIdecJMUserState();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByUsrSta;
	sqlite3_stmt* stmtLoadRefsByUsr;
	sqlite3_stmt* stmtLoadRstByUsr;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecJMUserState** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecJMUserState& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecJMUserState** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecJMUserState& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecJMUserState** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecJMUserState& rst);

	void insertRec(IdecJMUserState* rec);
	void insertRst(ListIdecJMUserState& rst, bool transact = false);
	void updateRec(IdecJMUserState* rec);
	void updateRst(ListIdecJMUserState& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecJMUserState** rec);
	bool loadRecByUsrSta(ubigint refIdecMUser, uint x1Startd, IdecJMUserState** rec);
	ubigint loadRefsByUsr(ubigint refIdecMUser, const bool append, vector<ubigint>& refs);
	ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecJMUserState& rst);
};

#endif

