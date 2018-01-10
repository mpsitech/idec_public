/**
  * \file IdecAMPersonDetail.h
  * database access for table TblIdecAMPersonDetail (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECAMPERSONDETAIL_H
#define IDECAMPERSONDETAIL_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAMPersonDetail: record of TblIdecAMPersonDetail
  */
class IdecAMPersonDetail {

public:
	IdecAMPersonDetail(const ubigint ref = 0, const ubigint refIdecMPerson = 0, const string x1SrefKType = "", const string Val = "");

public:
	ubigint ref;
	ubigint refIdecMPerson;
	string x1SrefKType;
	string Val;

public:
	bool operator==(const IdecAMPersonDetail& comp);
	bool operator!=(const IdecAMPersonDetail& comp);
};

/**
  * ListIdecAMPersonDetail: recordset of TblIdecAMPersonDetail
  */
class ListIdecAMPersonDetail {

public:
	ListIdecAMPersonDetail();
	ListIdecAMPersonDetail(const ListIdecAMPersonDetail& src);
	~ListIdecAMPersonDetail();

	void clear();
	unsigned int size() const;
	void append(IdecAMPersonDetail* rec);

	IdecAMPersonDetail* operator[](const uint ix);
	ListIdecAMPersonDetail& operator=(const ListIdecAMPersonDetail& src);
	bool operator==(const ListIdecAMPersonDetail& comp);
	bool operator!=(const ListIdecAMPersonDetail& comp);

public:
	vector<IdecAMPersonDetail*> nodes;
};

/**
  * TblIdecAMPersonDetail: C++ wrapper for table TblIdecAMPersonDetail
  */
class TblIdecAMPersonDetail {

public:

public:
	TblIdecAMPersonDetail();
	virtual ~TblIdecAMPersonDetail();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAMPersonDetail** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAMPersonDetail& rst);

	virtual void insertRec(IdecAMPersonDetail* rec);
	ubigint insertNewRec(IdecAMPersonDetail** rec = NULL, const ubigint refIdecMPerson = 0, const string x1SrefKType = "", const string Val = "");
	ubigint appendNewRecToRst(ListIdecAMPersonDetail& rst, IdecAMPersonDetail** rec = NULL, const ubigint refIdecMPerson = 0, const string x1SrefKType = "", const string Val = "");
	virtual void insertRst(ListIdecAMPersonDetail& rst, bool transact = false);
	virtual void updateRec(IdecAMPersonDetail* rec);
	virtual void updateRst(ListIdecAMPersonDetail& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAMPersonDetail** rec);
	virtual bool loadRecByPrsTyp(ubigint refIdecMPerson, string x1SrefKType, IdecAMPersonDetail** rec);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAMPersonDetail& rst);
};

/**
  * LiteTblIdecAMPersonDetail: C++ wrapper for table TblIdecAMPersonDetail (SQLite database)
  */
class LiteTblIdecAMPersonDetail : public TblIdecAMPersonDetail, public LiteTable {

public:
	LiteTblIdecAMPersonDetail();
	~LiteTblIdecAMPersonDetail();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByPrsTyp;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAMPersonDetail** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAMPersonDetail& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAMPersonDetail** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAMPersonDetail** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAMPersonDetail& rst);

	void insertRec(IdecAMPersonDetail* rec);
	void insertRst(ListIdecAMPersonDetail& rst, bool transact = false);
	void updateRec(IdecAMPersonDetail* rec);
	void updateRst(ListIdecAMPersonDetail& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAMPersonDetail** rec);
	bool loadRecByPrsTyp(ubigint refIdecMPerson, string x1SrefKType, IdecAMPersonDetail** rec);
};

#endif

