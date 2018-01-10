/**
  * \file IdecAMUserAccess.h
  * database access for table TblIdecAMUserAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECAMUSERACCESS_H
#define IDECAMUSERACCESS_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAMUserAccess: record of TblIdecAMUserAccess
  */
class IdecAMUserAccess {

public:
	IdecAMUserAccess(const ubigint ref = 0, const ubigint refIdecMUser = 0, const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);

public:
	ubigint ref;
	ubigint refIdecMUser;
	uint x1IxIdecVCard;
	uint ixIdecWUiaccess;

public:
	bool operator==(const IdecAMUserAccess& comp);
	bool operator!=(const IdecAMUserAccess& comp);
};

/**
  * ListIdecAMUserAccess: recordset of TblIdecAMUserAccess
  */
class ListIdecAMUserAccess {

public:
	ListIdecAMUserAccess();
	ListIdecAMUserAccess(const ListIdecAMUserAccess& src);
	~ListIdecAMUserAccess();

	void clear();
	unsigned int size() const;
	void append(IdecAMUserAccess* rec);

	IdecAMUserAccess* operator[](const uint ix);
	ListIdecAMUserAccess& operator=(const ListIdecAMUserAccess& src);
	bool operator==(const ListIdecAMUserAccess& comp);
	bool operator!=(const ListIdecAMUserAccess& comp);

public:
	vector<IdecAMUserAccess*> nodes;
};

/**
  * TblIdecAMUserAccess: C++ wrapper for table TblIdecAMUserAccess
  */
class TblIdecAMUserAccess {

public:

public:
	TblIdecAMUserAccess();
	virtual ~TblIdecAMUserAccess();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAMUserAccess** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAMUserAccess& rst);

	virtual void insertRec(IdecAMUserAccess* rec);
	ubigint insertNewRec(IdecAMUserAccess** rec = NULL, const ubigint refIdecMUser = 0, const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);
	ubigint appendNewRecToRst(ListIdecAMUserAccess& rst, IdecAMUserAccess** rec = NULL, const ubigint refIdecMUser = 0, const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);
	virtual void insertRst(ListIdecAMUserAccess& rst, bool transact = false);
	virtual void updateRec(IdecAMUserAccess* rec);
	virtual void updateRst(ListIdecAMUserAccess& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAMUserAccess** rec);
	virtual bool loadRecByUsrCrd(ubigint refIdecMUser, uint x1IxIdecVCard, IdecAMUserAccess** rec);
	virtual ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecAMUserAccess& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAMUserAccess& rst);
};

/**
  * LiteTblIdecAMUserAccess: C++ wrapper for table TblIdecAMUserAccess (SQLite database)
  */
class LiteTblIdecAMUserAccess : public TblIdecAMUserAccess, public LiteTable {

public:
	LiteTblIdecAMUserAccess();
	~LiteTblIdecAMUserAccess();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByUsrCrd;
	sqlite3_stmt* stmtLoadRstByUsr;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAMUserAccess** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAMUserAccess& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAMUserAccess** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecAMUserAccess& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAMUserAccess** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAMUserAccess& rst);

	void insertRec(IdecAMUserAccess* rec);
	void insertRst(ListIdecAMUserAccess& rst, bool transact = false);
	void updateRec(IdecAMUserAccess* rec);
	void updateRst(ListIdecAMUserAccess& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAMUserAccess** rec);
	bool loadRecByUsrCrd(ubigint refIdecMUser, uint x1IxIdecVCard, IdecAMUserAccess** rec);
	ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecAMUserAccess& rst);
};

#endif

