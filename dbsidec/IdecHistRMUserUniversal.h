/**
  * \file IdecHistRMUserUniversal.h
  * database access for table TblIdecHistRMUserUniversal (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECHISTRMUSERUNIVERSAL_H
#define IDECHISTRMUSERUNIVERSAL_H

#include <sbecore/LiteDbs.h>

/**
  * IdecHistRMUserUniversal: record of TblIdecHistRMUserUniversal
  */
class IdecHistRMUserUniversal {

public:
	IdecHistRMUserUniversal(const ubigint ref = 0, const ubigint refIdecMUser = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVCard = 0, const uint ixIdecVPreset = 0, const uint preIxIdecVMaintable = 0, const ubigint preUref = 0, const uint start = 0);

public:
	ubigint ref;
	ubigint refIdecMUser;
	uint unvIxIdecVMaintable;
	ubigint unvUref;
	uint ixIdecVCard;
	uint ixIdecVPreset;
	uint preIxIdecVMaintable;
	ubigint preUref;
	uint start;

public:
	bool operator==(const IdecHistRMUserUniversal& comp);
	bool operator!=(const IdecHistRMUserUniversal& comp);
};

/**
  * ListIdecHistRMUserUniversal: recordset of TblIdecHistRMUserUniversal
  */
class ListIdecHistRMUserUniversal {

public:
	ListIdecHistRMUserUniversal();
	ListIdecHistRMUserUniversal(const ListIdecHistRMUserUniversal& src);
	~ListIdecHistRMUserUniversal();

	void clear();
	unsigned int size() const;
	void append(IdecHistRMUserUniversal* rec);

	IdecHistRMUserUniversal* operator[](const uint ix);
	ListIdecHistRMUserUniversal& operator=(const ListIdecHistRMUserUniversal& src);
	bool operator==(const ListIdecHistRMUserUniversal& comp);
	bool operator!=(const ListIdecHistRMUserUniversal& comp);

public:
	vector<IdecHistRMUserUniversal*> nodes;
};

/**
  * TblIdecHistRMUserUniversal: C++ wrapper for table TblIdecHistRMUserUniversal
  */
class TblIdecHistRMUserUniversal {

public:

public:
	TblIdecHistRMUserUniversal();
	virtual ~TblIdecHistRMUserUniversal();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecHistRMUserUniversal** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecHistRMUserUniversal& rst);

	virtual void insertRec(IdecHistRMUserUniversal* rec);
	ubigint insertNewRec(IdecHistRMUserUniversal** rec = NULL, const ubigint refIdecMUser = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVCard = 0, const uint ixIdecVPreset = 0, const uint preIxIdecVMaintable = 0, const ubigint preUref = 0, const uint start = 0);
	ubigint appendNewRecToRst(ListIdecHistRMUserUniversal& rst, IdecHistRMUserUniversal** rec = NULL, const ubigint refIdecMUser = 0, const uint unvIxIdecVMaintable = 0, const ubigint unvUref = 0, const uint ixIdecVCard = 0, const uint ixIdecVPreset = 0, const uint preIxIdecVMaintable = 0, const ubigint preUref = 0, const uint start = 0);
	virtual void insertRst(ListIdecHistRMUserUniversal& rst, bool transact = false);
	virtual void updateRec(IdecHistRMUserUniversal* rec);
	virtual void updateRst(ListIdecHistRMUserUniversal& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecHistRMUserUniversal** rec);
	virtual ubigint loadRstByUsrCrd(ubigint refIdecMUser, uint ixIdecVCard, const bool append, ListIdecHistRMUserUniversal& rst);
	virtual bool loadUnuByRef(ubigint ref, ubigint& unvUref);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecHistRMUserUniversal& rst);
};

/**
  * LiteTblIdecHistRMUserUniversal: C++ wrapper for table TblIdecHistRMUserUniversal (SQLite database)
  */
class LiteTblIdecHistRMUserUniversal : public TblIdecHistRMUserUniversal, public LiteTable {

public:
	LiteTblIdecHistRMUserUniversal();
	~LiteTblIdecHistRMUserUniversal();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRstByUsrCrd;
	sqlite3_stmt* stmtLoadUnuByRef;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecHistRMUserUniversal** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecHistRMUserUniversal& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecHistRMUserUniversal** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecHistRMUserUniversal& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecHistRMUserUniversal** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecHistRMUserUniversal& rst);

	void insertRec(IdecHistRMUserUniversal* rec);
	void insertRst(ListIdecHistRMUserUniversal& rst, bool transact = false);
	void updateRec(IdecHistRMUserUniversal* rec);
	void updateRst(ListIdecHistRMUserUniversal& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecHistRMUserUniversal** rec);
	ubigint loadRstByUsrCrd(ubigint refIdecMUser, uint ixIdecVCard, const bool append, ListIdecHistRMUserUniversal& rst);
	bool loadUnuByRef(ubigint ref, ubigint& unvUref);
};

#endif

