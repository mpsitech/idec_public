/**
  * \file IdecRMUserMUsergroup.h
  * database access for table TblIdecRMUserMUsergroup (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECRMUSERMUSERGROUP_H
#define IDECRMUSERMUSERGROUP_H

#include <sbecore/LiteDbs.h>

/**
  * IdecRMUserMUsergroup: record of TblIdecRMUserMUsergroup
  */
class IdecRMUserMUsergroup {

public:
	IdecRMUserMUsergroup(const ubigint ref = 0, const ubigint refIdecMUser = 0, const ubigint refIdecMUsergroup = 0, const uint ixIdecVUserlevel = 0);

public:
	ubigint ref;
	ubigint refIdecMUser;
	ubigint refIdecMUsergroup;
	uint ixIdecVUserlevel;

public:
	bool operator==(const IdecRMUserMUsergroup& comp);
	bool operator!=(const IdecRMUserMUsergroup& comp);
};

/**
  * ListIdecRMUserMUsergroup: recordset of TblIdecRMUserMUsergroup
  */
class ListIdecRMUserMUsergroup {

public:
	ListIdecRMUserMUsergroup();
	ListIdecRMUserMUsergroup(const ListIdecRMUserMUsergroup& src);
	~ListIdecRMUserMUsergroup();

	void clear();
	unsigned int size() const;
	void append(IdecRMUserMUsergroup* rec);

	IdecRMUserMUsergroup* operator[](const uint ix);
	ListIdecRMUserMUsergroup& operator=(const ListIdecRMUserMUsergroup& src);
	bool operator==(const ListIdecRMUserMUsergroup& comp);
	bool operator!=(const ListIdecRMUserMUsergroup& comp);

public:
	vector<IdecRMUserMUsergroup*> nodes;
};

/**
  * TblIdecRMUserMUsergroup: C++ wrapper for table TblIdecRMUserMUsergroup
  */
class TblIdecRMUserMUsergroup {

public:

public:
	TblIdecRMUserMUsergroup();
	virtual ~TblIdecRMUserMUsergroup();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecRMUserMUsergroup** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecRMUserMUsergroup& rst);

	virtual void insertRec(IdecRMUserMUsergroup* rec);
	ubigint insertNewRec(IdecRMUserMUsergroup** rec = NULL, const ubigint refIdecMUser = 0, const ubigint refIdecMUsergroup = 0, const uint ixIdecVUserlevel = 0);
	ubigint appendNewRecToRst(ListIdecRMUserMUsergroup& rst, IdecRMUserMUsergroup** rec = NULL, const ubigint refIdecMUser = 0, const ubigint refIdecMUsergroup = 0, const uint ixIdecVUserlevel = 0);
	virtual void insertRst(ListIdecRMUserMUsergroup& rst, bool transact = false);
	virtual void updateRec(IdecRMUserMUsergroup* rec);
	virtual void updateRst(ListIdecRMUserMUsergroup& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecRMUserMUsergroup** rec);
	virtual ubigint loadRstByUsg(ubigint refIdecMUsergroup, const bool append, ListIdecRMUserMUsergroup& rst);
	virtual ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecRMUserMUsergroup& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecRMUserMUsergroup& rst);
};

/**
  * LiteTblIdecRMUserMUsergroup: C++ wrapper for table TblIdecRMUserMUsergroup (SQLite database)
  */
class LiteTblIdecRMUserMUsergroup : public TblIdecRMUserMUsergroup, public LiteTable {

public:
	LiteTblIdecRMUserMUsergroup();
	~LiteTblIdecRMUserMUsergroup();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRstByUsg;
	sqlite3_stmt* stmtLoadRstByUsr;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecRMUserMUsergroup** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecRMUserMUsergroup& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecRMUserMUsergroup** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecRMUserMUsergroup& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecRMUserMUsergroup** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecRMUserMUsergroup& rst);

	void insertRec(IdecRMUserMUsergroup* rec);
	void insertRst(ListIdecRMUserMUsergroup& rst, bool transact = false);
	void updateRec(IdecRMUserMUsergroup* rec);
	void updateRst(ListIdecRMUserMUsergroup& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecRMUserMUsergroup** rec);
	ubigint loadRstByUsg(ubigint refIdecMUsergroup, const bool append, ListIdecRMUserMUsergroup& rst);
	ubigint loadRstByUsr(ubigint refIdecMUser, const bool append, ListIdecRMUserMUsergroup& rst);
};

#endif

