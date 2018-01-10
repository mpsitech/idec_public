/**
  * \file IdecAccRMUserUniversal.h
  * database access for table TblIdecAccRMUserUniversal (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECACCRMUSERUNIVERSAL_H
#define IDECACCRMUSERUNIVERSAL_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAccRMUserUniversal: record of TblIdecAccRMUserUniversal
  */
class IdecAccRMUserUniversal {

public:
	IdecAccRMUserUniversal(const ubigint ref = 0, const ubigint refIdecMUser = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVAccess = 0);

public:
	ubigint ref;
	ubigint refIdecMUser;
	uint unvIxIdecVMaintable;
	ubigint unvUref;
	uint ixIdecVAccess;

public:
	bool operator==(const IdecAccRMUserUniversal& comp);
	bool operator!=(const IdecAccRMUserUniversal& comp);
};

/**
  * ListIdecAccRMUserUniversal: recordset of TblIdecAccRMUserUniversal
  */
class ListIdecAccRMUserUniversal {

public:
	ListIdecAccRMUserUniversal();
	ListIdecAccRMUserUniversal(const ListIdecAccRMUserUniversal& src);
	~ListIdecAccRMUserUniversal();

	void clear();
	unsigned int size() const;
	void append(IdecAccRMUserUniversal* rec);

	IdecAccRMUserUniversal* operator[](const uint ix);
	ListIdecAccRMUserUniversal& operator=(const ListIdecAccRMUserUniversal& src);
	bool operator==(const ListIdecAccRMUserUniversal& comp);
	bool operator!=(const ListIdecAccRMUserUniversal& comp);

public:
	vector<IdecAccRMUserUniversal*> nodes;
};

/**
  * TblIdecAccRMUserUniversal: C++ wrapper for table TblIdecAccRMUserUniversal
  */
class TblIdecAccRMUserUniversal {

public:

public:
	TblIdecAccRMUserUniversal();
	virtual ~TblIdecAccRMUserUniversal();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAccRMUserUniversal** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAccRMUserUniversal& rst);

	virtual void insertRec(IdecAccRMUserUniversal* rec);
	ubigint insertNewRec(IdecAccRMUserUniversal** rec = NULL, const ubigint refIdecMUser = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVAccess = 0);
	ubigint appendNewRecToRst(ListIdecAccRMUserUniversal& rst, IdecAccRMUserUniversal** rec = NULL, const ubigint refIdecMUser = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVAccess = 0);
	virtual void insertRst(ListIdecAccRMUserUniversal& rst, bool transact = false);
	virtual void updateRec(IdecAccRMUserUniversal* rec);
	virtual void updateRst(ListIdecAccRMUserUniversal& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAccRMUserUniversal** rec);
	virtual bool loadRecByUsrMtbUnv(ubigint refIdecMUser, uint unvIxIdecVMaintable, ubigint unvUref, IdecAccRMUserUniversal** rec);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAccRMUserUniversal& rst);
};

/**
  * LiteTblIdecAccRMUserUniversal: C++ wrapper for table TblIdecAccRMUserUniversal (SQLite database)
  */
class LiteTblIdecAccRMUserUniversal : public TblIdecAccRMUserUniversal, public LiteTable {

public:
	LiteTblIdecAccRMUserUniversal();
	~LiteTblIdecAccRMUserUniversal();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByUsrMtbUnv;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAccRMUserUniversal** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAccRMUserUniversal& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAccRMUserUniversal** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAccRMUserUniversal** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAccRMUserUniversal& rst);

	void insertRec(IdecAccRMUserUniversal* rec);
	void insertRst(ListIdecAccRMUserUniversal& rst, bool transact = false);
	void updateRec(IdecAccRMUserUniversal* rec);
	void updateRst(ListIdecAccRMUserUniversal& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAccRMUserUniversal** rec);
	bool loadRecByUsrMtbUnv(ubigint refIdecMUser, uint unvIxIdecVMaintable, ubigint unvUref, IdecAccRMUserUniversal** rec);
};

#endif

