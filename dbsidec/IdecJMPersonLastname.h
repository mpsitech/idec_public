/**
  * \file IdecJMPersonLastname.h
  * database access for table TblIdecJMPersonLastname (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECJMPERSONLASTNAME_H
#define IDECJMPERSONLASTNAME_H

#include <sbecore/LiteDbs.h>

/**
  * IdecJMPersonLastname: record of TblIdecJMPersonLastname
  */
class IdecJMPersonLastname {

public:
	IdecJMPersonLastname(const ubigint ref = 0, const ubigint refIdecMPerson = 0, const uint x1Startd = 0, const string Lastname = "");

public:
	ubigint ref;
	ubigint refIdecMPerson;
	uint x1Startd;
	string Lastname;

public:
	bool operator==(const IdecJMPersonLastname& comp);
	bool operator!=(const IdecJMPersonLastname& comp);
};

/**
  * ListIdecJMPersonLastname: recordset of TblIdecJMPersonLastname
  */
class ListIdecJMPersonLastname {

public:
	ListIdecJMPersonLastname();
	ListIdecJMPersonLastname(const ListIdecJMPersonLastname& src);
	~ListIdecJMPersonLastname();

	void clear();
	unsigned int size() const;
	void append(IdecJMPersonLastname* rec);

	IdecJMPersonLastname* operator[](const uint ix);
	ListIdecJMPersonLastname& operator=(const ListIdecJMPersonLastname& src);
	bool operator==(const ListIdecJMPersonLastname& comp);
	bool operator!=(const ListIdecJMPersonLastname& comp);

public:
	vector<IdecJMPersonLastname*> nodes;
};

/**
  * TblIdecJMPersonLastname: C++ wrapper for table TblIdecJMPersonLastname
  */
class TblIdecJMPersonLastname {

public:

public:
	TblIdecJMPersonLastname();
	virtual ~TblIdecJMPersonLastname();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecJMPersonLastname** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecJMPersonLastname& rst);

	virtual void insertRec(IdecJMPersonLastname* rec);
	ubigint insertNewRec(IdecJMPersonLastname** rec = NULL, const ubigint refIdecMPerson = 0, const uint x1Startd = 0, const string Lastname = "");
	ubigint appendNewRecToRst(ListIdecJMPersonLastname& rst, IdecJMPersonLastname** rec = NULL, const ubigint refIdecMPerson = 0, const uint x1Startd = 0, const string Lastname = "");
	virtual void insertRst(ListIdecJMPersonLastname& rst, bool transact = false);
	virtual void updateRec(IdecJMPersonLastname* rec);
	virtual void updateRst(ListIdecJMPersonLastname& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecJMPersonLastname** rec);
	virtual bool loadRecByPrsSta(ubigint refIdecMPerson, uint x1Startd, IdecJMPersonLastname** rec);
	virtual ubigint loadRefsByPrs(ubigint refIdecMPerson, const bool append, vector<ubigint>& refs);
	virtual ubigint loadRstByPrs(ubigint refIdecMPerson, const bool append, ListIdecJMPersonLastname& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecJMPersonLastname& rst);
};

/**
  * LiteTblIdecJMPersonLastname: C++ wrapper for table TblIdecJMPersonLastname (SQLite database)
  */
class LiteTblIdecJMPersonLastname : public TblIdecJMPersonLastname, public LiteTable {

public:
	LiteTblIdecJMPersonLastname();
	~LiteTblIdecJMPersonLastname();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByPrsSta;
	sqlite3_stmt* stmtLoadRefsByPrs;
	sqlite3_stmt* stmtLoadRstByPrs;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecJMPersonLastname** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecJMPersonLastname& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecJMPersonLastname** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecJMPersonLastname& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecJMPersonLastname** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecJMPersonLastname& rst);

	void insertRec(IdecJMPersonLastname* rec);
	void insertRst(ListIdecJMPersonLastname& rst, bool transact = false);
	void updateRec(IdecJMPersonLastname* rec);
	void updateRst(ListIdecJMPersonLastname& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecJMPersonLastname** rec);
	bool loadRecByPrsSta(ubigint refIdecMPerson, uint x1Startd, IdecJMPersonLastname** rec);
	ubigint loadRefsByPrs(ubigint refIdecMPerson, const bool append, vector<ubigint>& refs);
	ubigint loadRstByPrs(ubigint refIdecMPerson, const bool append, ListIdecJMPersonLastname& rst);
};

#endif

