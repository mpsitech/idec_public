/**
  * \file IdecAVValuelistVal.h
  * database access for table TblIdecAVValuelistVal (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECAVVALUELISTVAL_H
#define IDECAVVALUELISTVAL_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAVValuelistVal: record of TblIdecAVValuelistVal
  */
class IdecAVValuelistVal {

public:
	IdecAVValuelistVal(const ubigint ref = 0, const uint vlsIxIdecVValuelist = 0, const uint vlsNum = 0, const uint x1IxIdecVLocale = 0, const string Val = "");

public:
	ubigint ref;
	uint vlsIxIdecVValuelist;
	uint vlsNum;
	uint x1IxIdecVLocale;
	string Val;

public:
	bool operator==(const IdecAVValuelistVal& comp);
	bool operator!=(const IdecAVValuelistVal& comp);
};

/**
  * ListIdecAVValuelistVal: recordset of TblIdecAVValuelistVal
  */
class ListIdecAVValuelistVal {

public:
	ListIdecAVValuelistVal();
	ListIdecAVValuelistVal(const ListIdecAVValuelistVal& src);
	~ListIdecAVValuelistVal();

	void clear();
	unsigned int size() const;
	void append(IdecAVValuelistVal* rec);

	IdecAVValuelistVal* operator[](const uint ix);
	ListIdecAVValuelistVal& operator=(const ListIdecAVValuelistVal& src);
	bool operator==(const ListIdecAVValuelistVal& comp);
	bool operator!=(const ListIdecAVValuelistVal& comp);

public:
	vector<IdecAVValuelistVal*> nodes;
};

/**
  * TblIdecAVValuelistVal: C++ wrapper for table TblIdecAVValuelistVal
  */
class TblIdecAVValuelistVal {

public:

public:
	TblIdecAVValuelistVal();
	virtual ~TblIdecAVValuelistVal();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAVValuelistVal** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAVValuelistVal& rst);

	virtual void insertRec(IdecAVValuelistVal* rec);
	ubigint insertNewRec(IdecAVValuelistVal** rec = NULL, const uint vlsIxIdecVValuelist = 0, const uint vlsNum = 0, const uint x1IxIdecVLocale = 0, const string Val = "");
	ubigint appendNewRecToRst(ListIdecAVValuelistVal& rst, IdecAVValuelistVal** rec = NULL, const uint vlsIxIdecVValuelist = 0, const uint vlsNum = 0, const uint x1IxIdecVLocale = 0, const string Val = "");
	virtual void insertRst(ListIdecAVValuelistVal& rst, bool transact = false);
	virtual void updateRec(IdecAVValuelistVal* rec);
	virtual void updateRst(ListIdecAVValuelistVal& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAVValuelistVal** rec);
	virtual ubigint loadRstByVlsLcl(uint vlsIxIdecVValuelist, uint x1IxIdecVLocale, const bool append, ListIdecAVValuelistVal& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAVValuelistVal& rst);
};

/**
  * LiteTblIdecAVValuelistVal: C++ wrapper for table TblIdecAVValuelistVal (SQLite database)
  */
class LiteTblIdecAVValuelistVal : public TblIdecAVValuelistVal, public LiteTable {

public:
	LiteTblIdecAVValuelistVal();
	~LiteTblIdecAVValuelistVal();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRstByVlsLcl;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAVValuelistVal** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAVValuelistVal& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAVValuelistVal** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecAVValuelistVal& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAVValuelistVal** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAVValuelistVal& rst);

	void insertRec(IdecAVValuelistVal* rec);
	void insertRst(ListIdecAVValuelistVal& rst, bool transact = false);
	void updateRec(IdecAVValuelistVal* rec);
	void updateRst(ListIdecAVValuelistVal& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAVValuelistVal** rec);
	ubigint loadRstByVlsLcl(uint vlsIxIdecVValuelist, uint x1IxIdecVLocale, const bool append, ListIdecAVValuelistVal& rst);
};

#endif

