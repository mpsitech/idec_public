/**
  * \file IdecMMission.h
  * database access for table TblIdecMMission (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMMISSION_H
#define IDECMMISSION_H

#include <sbecore/LiteDbs.h>

/**
  * IdecMMission: record of TblIdecMMission
  */
class IdecMMission {

public:
	IdecMMission(const ubigint ref = 0, const ubigint grp = 0, const ubigint own = 0, const string Title = "", const uint startd = 0, const uint stopd = 0, const string srefKCountry = "", const string Region = "", const string Municipality = "", const string Comment = "");

public:
	ubigint ref;
	ubigint grp;
	ubigint own;
	string Title;
	uint startd;
	uint stopd;
	string srefKCountry;
	string Region;
	string Municipality;
	string Comment;

public:
	bool operator==(const IdecMMission& comp);
	bool operator!=(const IdecMMission& comp);
};

/**
  * ListIdecMMission: recordset of TblIdecMMission
  */
class ListIdecMMission {

public:
	ListIdecMMission();
	ListIdecMMission(const ListIdecMMission& src);
	~ListIdecMMission();

	void clear();
	unsigned int size() const;
	void append(IdecMMission* rec);

	IdecMMission* operator[](const uint ix);
	ListIdecMMission& operator=(const ListIdecMMission& src);
	bool operator==(const ListIdecMMission& comp);
	bool operator!=(const ListIdecMMission& comp);

public:
	vector<IdecMMission*> nodes;
};

/**
  * TblIdecMMission: C++ wrapper for table TblIdecMMission
  */
class TblIdecMMission {

public:

public:
	TblIdecMMission();
	virtual ~TblIdecMMission();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMMission** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMMission& rst);

	virtual void insertRec(IdecMMission* rec);
	ubigint insertNewRec(IdecMMission** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const string Title = "", const uint startd = 0, const uint stopd = 0, const string srefKCountry = "", const string Region = "", const string Municipality = "", const string Comment = "");
	ubigint appendNewRecToRst(ListIdecMMission& rst, IdecMMission** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const string Title = "", const uint startd = 0, const uint stopd = 0, const string srefKCountry = "", const string Region = "", const string Municipality = "", const string Comment = "");
	virtual void insertRst(ListIdecMMission& rst, bool transact = false);
	virtual void updateRec(IdecMMission* rec);
	virtual void updateRst(ListIdecMMission& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMMission** rec);
	virtual bool loadTitByRef(ubigint ref, string& Title);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMMission& rst);
};

/**
  * LiteTblIdecMMission: C++ wrapper for table TblIdecMMission (SQLite database)
  */
class LiteTblIdecMMission : public TblIdecMMission, public LiteTable {

public:
	LiteTblIdecMMission();
	~LiteTblIdecMMission();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadTitByRef;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMMission** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMMission& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMMission** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMMission** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMMission& rst);

	void insertRec(IdecMMission* rec);
	void insertRst(ListIdecMMission& rst, bool transact = false);
	void updateRec(IdecMMission* rec);
	void updateRst(ListIdecMMission& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMMission** rec);
	bool loadTitByRef(ubigint ref, string& Title);
};

#endif

