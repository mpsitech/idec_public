/**
  * \file IdecAMUsergroupAccess.h
  * database access for table TblIdecAMUsergroupAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECAMUSERGROUPACCESS_H
#define IDECAMUSERGROUPACCESS_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAMUsergroupAccess: record of TblIdecAMUsergroupAccess
  */
class IdecAMUsergroupAccess {

public:
	IdecAMUsergroupAccess(const ubigint ref = 0, const ubigint refIdecMUsergroup = 0, const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);

public:
	ubigint ref;
	ubigint refIdecMUsergroup;
	uint x1IxIdecVCard;
	uint ixIdecWUiaccess;

public:
	bool operator==(const IdecAMUsergroupAccess& comp);
	bool operator!=(const IdecAMUsergroupAccess& comp);
};

/**
  * ListIdecAMUsergroupAccess: recordset of TblIdecAMUsergroupAccess
  */
class ListIdecAMUsergroupAccess {

public:
	ListIdecAMUsergroupAccess();
	ListIdecAMUsergroupAccess(const ListIdecAMUsergroupAccess& src);
	~ListIdecAMUsergroupAccess();

	void clear();
	unsigned int size() const;
	void append(IdecAMUsergroupAccess* rec);

	IdecAMUsergroupAccess* operator[](const uint ix);
	ListIdecAMUsergroupAccess& operator=(const ListIdecAMUsergroupAccess& src);
	bool operator==(const ListIdecAMUsergroupAccess& comp);
	bool operator!=(const ListIdecAMUsergroupAccess& comp);

public:
	vector<IdecAMUsergroupAccess*> nodes;
};

/**
  * TblIdecAMUsergroupAccess: C++ wrapper for table TblIdecAMUsergroupAccess
  */
class TblIdecAMUsergroupAccess {

public:

public:
	TblIdecAMUsergroupAccess();
	virtual ~TblIdecAMUsergroupAccess();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAMUsergroupAccess** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAMUsergroupAccess& rst);

	virtual void insertRec(IdecAMUsergroupAccess* rec);
	ubigint insertNewRec(IdecAMUsergroupAccess** rec = NULL, const ubigint refIdecMUsergroup = 0, const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);
	ubigint appendNewRecToRst(ListIdecAMUsergroupAccess& rst, IdecAMUsergroupAccess** rec = NULL, const ubigint refIdecMUsergroup = 0, const uint x1IxIdecVCard = 0, const uint ixIdecWUiaccess = 0);
	virtual void insertRst(ListIdecAMUsergroupAccess& rst, bool transact = false);
	virtual void updateRec(IdecAMUsergroupAccess* rec);
	virtual void updateRst(ListIdecAMUsergroupAccess& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAMUsergroupAccess** rec);
	virtual bool loadRecByUsgCrd(ubigint refIdecMUsergroup, uint x1IxIdecVCard, IdecAMUsergroupAccess** rec);
	virtual ubigint loadRefsByUsg(ubigint refIdecMUsergroup, const bool append, vector<ubigint>& refs);
	virtual ubigint loadRstByUsg(ubigint refIdecMUsergroup, const bool append, ListIdecAMUsergroupAccess& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAMUsergroupAccess& rst);
};

/**
  * LiteTblIdecAMUsergroupAccess: C++ wrapper for table TblIdecAMUsergroupAccess (SQLite database)
  */
class LiteTblIdecAMUsergroupAccess : public TblIdecAMUsergroupAccess, public LiteTable {

public:
	LiteTblIdecAMUsergroupAccess();
	~LiteTblIdecAMUsergroupAccess();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByUsgCrd;
	sqlite3_stmt* stmtLoadRefsByUsg;
	sqlite3_stmt* stmtLoadRstByUsg;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAMUsergroupAccess** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAMUsergroupAccess& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAMUsergroupAccess** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecAMUsergroupAccess& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAMUsergroupAccess** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAMUsergroupAccess& rst);

	void insertRec(IdecAMUsergroupAccess* rec);
	void insertRst(ListIdecAMUsergroupAccess& rst, bool transact = false);
	void updateRec(IdecAMUsergroupAccess* rec);
	void updateRst(ListIdecAMUsergroupAccess& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAMUsergroupAccess** rec);
	bool loadRecByUsgCrd(ubigint refIdecMUsergroup, uint x1IxIdecVCard, IdecAMUsergroupAccess** rec);
	ubigint loadRefsByUsg(ubigint refIdecMUsergroup, const bool append, vector<ubigint>& refs);
	ubigint loadRstByUsg(ubigint refIdecMUsergroup, const bool append, ListIdecAMUsergroupAccess& rst);
};

#endif

