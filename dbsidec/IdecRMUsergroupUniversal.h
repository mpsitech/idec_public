/**
  * \file IdecRMUsergroupUniversal.h
  * database access for table TblIdecRMUsergroupUniversal (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECRMUSERGROUPUNIVERSAL_H
#define IDECRMUSERGROUPUNIVERSAL_H

#include <sbecore/LiteDbs.h>

/**
  * IdecRMUsergroupUniversal: record of TblIdecRMUsergroupUniversal
  */
class IdecRMUsergroupUniversal {

public:
	IdecRMUsergroupUniversal(const ubigint ref = 0, const ubigint refIdecMUsergroup = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVAccess = 0);

public:
	ubigint ref;
	ubigint refIdecMUsergroup;
	uint unvIxIdecVMaintable;
	ubigint unvUref;
	uint ixIdecVAccess;

public:
	bool operator==(const IdecRMUsergroupUniversal& comp);
	bool operator!=(const IdecRMUsergroupUniversal& comp);
};

/**
  * ListIdecRMUsergroupUniversal: recordset of TblIdecRMUsergroupUniversal
  */
class ListIdecRMUsergroupUniversal {

public:
	ListIdecRMUsergroupUniversal();
	ListIdecRMUsergroupUniversal(const ListIdecRMUsergroupUniversal& src);
	~ListIdecRMUsergroupUniversal();

	void clear();
	unsigned int size() const;
	void append(IdecRMUsergroupUniversal* rec);

	IdecRMUsergroupUniversal* operator[](const uint ix);
	ListIdecRMUsergroupUniversal& operator=(const ListIdecRMUsergroupUniversal& src);
	bool operator==(const ListIdecRMUsergroupUniversal& comp);
	bool operator!=(const ListIdecRMUsergroupUniversal& comp);

public:
	vector<IdecRMUsergroupUniversal*> nodes;
};

/**
  * TblIdecRMUsergroupUniversal: C++ wrapper for table TblIdecRMUsergroupUniversal
  */
class TblIdecRMUsergroupUniversal {

public:

public:
	TblIdecRMUsergroupUniversal();
	virtual ~TblIdecRMUsergroupUniversal();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecRMUsergroupUniversal** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecRMUsergroupUniversal& rst);

	virtual void insertRec(IdecRMUsergroupUniversal* rec);
	ubigint insertNewRec(IdecRMUsergroupUniversal** rec = NULL, const ubigint refIdecMUsergroup = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVAccess = 0);
	ubigint appendNewRecToRst(ListIdecRMUsergroupUniversal& rst, IdecRMUsergroupUniversal** rec = NULL, const ubigint refIdecMUsergroup = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVAccess = 0);
	virtual void insertRst(ListIdecRMUsergroupUniversal& rst, bool transact = false);
	virtual void updateRec(IdecRMUsergroupUniversal* rec);
	virtual void updateRst(ListIdecRMUsergroupUniversal& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecRMUsergroupUniversal** rec);
	virtual bool loadRecByUsgMtbUnv(ubigint refIdecMUsergroup, uint unvIxIdecVMaintable, ubigint unvUref, IdecRMUsergroupUniversal** rec);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecRMUsergroupUniversal& rst);
};

/**
  * LiteTblIdecRMUsergroupUniversal: C++ wrapper for table TblIdecRMUsergroupUniversal (SQLite database)
  */
class LiteTblIdecRMUsergroupUniversal : public TblIdecRMUsergroupUniversal, public LiteTable {

public:
	LiteTblIdecRMUsergroupUniversal();
	~LiteTblIdecRMUsergroupUniversal();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByUsgMtbUnv;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecRMUsergroupUniversal** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecRMUsergroupUniversal& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecRMUsergroupUniversal** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecRMUsergroupUniversal** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecRMUsergroupUniversal& rst);

	void insertRec(IdecRMUsergroupUniversal* rec);
	void insertRst(ListIdecRMUsergroupUniversal& rst, bool transact = false);
	void updateRec(IdecRMUsergroupUniversal* rec);
	void updateRst(ListIdecRMUsergroupUniversal& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecRMUsergroupUniversal** rec);
	bool loadRecByUsgMtbUnv(ubigint refIdecMUsergroup, uint unvIxIdecVMaintable, ubigint unvUref, IdecRMUsergroupUniversal** rec);
};

#endif

