/**
  * \file IdecMUsergroup.h
  * database access for table TblIdecMUsergroup (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMUSERGROUP_H
#define IDECMUSERGROUP_H

#include <sbecore/LiteDbs.h>

/**
  * IdecMUsergroup: record of TblIdecMUsergroup
  */
class IdecMUsergroup {

public:
	IdecMUsergroup(const ubigint ref = 0, const ubigint grp = 0, const ubigint own = 0, const string sref = "", const string Comment = "");

public:
	ubigint ref;
	ubigint grp;
	ubigint own;
	string sref;
	string Comment;

public:
	bool operator==(const IdecMUsergroup& comp);
	bool operator!=(const IdecMUsergroup& comp);
};

/**
  * ListIdecMUsergroup: recordset of TblIdecMUsergroup
  */
class ListIdecMUsergroup {

public:
	ListIdecMUsergroup();
	ListIdecMUsergroup(const ListIdecMUsergroup& src);
	~ListIdecMUsergroup();

	void clear();
	unsigned int size() const;
	void append(IdecMUsergroup* rec);

	IdecMUsergroup* operator[](const uint ix);
	ListIdecMUsergroup& operator=(const ListIdecMUsergroup& src);
	bool operator==(const ListIdecMUsergroup& comp);
	bool operator!=(const ListIdecMUsergroup& comp);

public:
	vector<IdecMUsergroup*> nodes;
};

/**
  * TblIdecMUsergroup: C++ wrapper for table TblIdecMUsergroup
  */
class TblIdecMUsergroup {

public:

public:
	TblIdecMUsergroup();
	virtual ~TblIdecMUsergroup();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMUsergroup** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMUsergroup& rst);

	virtual void insertRec(IdecMUsergroup* rec);
	ubigint insertNewRec(IdecMUsergroup** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const string sref = "", const string Comment = "");
	ubigint appendNewRecToRst(ListIdecMUsergroup& rst, IdecMUsergroup** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const string sref = "", const string Comment = "");
	virtual void insertRst(ListIdecMUsergroup& rst, bool transact = false);
	virtual void updateRec(IdecMUsergroup* rec);
	virtual void updateRst(ListIdecMUsergroup& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMUsergroup** rec);
	virtual bool loadRecBySrf(string sref, IdecMUsergroup** rec);
	virtual bool loadRefBySrf(string sref, ubigint& ref);
	virtual bool loadSrfByRef(ubigint ref, string& sref);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMUsergroup& rst);
};

/**
  * LiteTblIdecMUsergroup: C++ wrapper for table TblIdecMUsergroup (SQLite database)
  */
class LiteTblIdecMUsergroup : public TblIdecMUsergroup, public LiteTable {

public:
	LiteTblIdecMUsergroup();
	~LiteTblIdecMUsergroup();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecBySrf;
	sqlite3_stmt* stmtLoadRefBySrf;
	sqlite3_stmt* stmtLoadSrfByRef;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMUsergroup** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMUsergroup& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMUsergroup** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMUsergroup** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMUsergroup& rst);

	void insertRec(IdecMUsergroup* rec);
	void insertRst(ListIdecMUsergroup& rst, bool transact = false);
	void updateRec(IdecMUsergroup* rec);
	void updateRst(ListIdecMUsergroup& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMUsergroup** rec);
	bool loadRecBySrf(string sref, IdecMUsergroup** rec);
	bool loadRefBySrf(string sref, ubigint& ref);
	bool loadSrfByRef(ubigint ref, string& sref);
};

#endif

