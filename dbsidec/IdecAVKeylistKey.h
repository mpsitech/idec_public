/**
  * \file IdecAVKeylistKey.h
  * database access for table TblIdecAVKeylistKey (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECAVKEYLISTKEY_H
#define IDECAVKEYLISTKEY_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAVKeylistKey: record of TblIdecAVKeylistKey
  */
class IdecAVKeylistKey {

public:
	IdecAVKeylistKey(const ubigint ref = 0, const uint klsIxIdecVKeylist = 0, const uint klsNum = 0, const uint x1IxIdecVMaintable = 0, const ubigint x1Uref = 0, const bool Fixed = false, const string sref = "", const string Avail = "", const string Implied = "", const ubigint refJ = 0, const string Title = "", const string Comment = "");

public:
	ubigint ref;
	uint klsIxIdecVKeylist;
	uint klsNum;
	uint x1IxIdecVMaintable;
	ubigint x1Uref;
	bool Fixed;
	string sref;
	string Avail;
	string Implied;
	ubigint refJ;
	string Title;
	string Comment;

public:
	bool operator==(const IdecAVKeylistKey& comp);
	bool operator!=(const IdecAVKeylistKey& comp);
};

/**
  * ListIdecAVKeylistKey: recordset of TblIdecAVKeylistKey
  */
class ListIdecAVKeylistKey {

public:
	ListIdecAVKeylistKey();
	ListIdecAVKeylistKey(const ListIdecAVKeylistKey& src);
	~ListIdecAVKeylistKey();

	void clear();
	unsigned int size() const;
	void append(IdecAVKeylistKey* rec);

	IdecAVKeylistKey* operator[](const uint ix);
	ListIdecAVKeylistKey& operator=(const ListIdecAVKeylistKey& src);
	bool operator==(const ListIdecAVKeylistKey& comp);
	bool operator!=(const ListIdecAVKeylistKey& comp);

public:
	vector<IdecAVKeylistKey*> nodes;
};

/**
  * TblIdecAVKeylistKey: C++ wrapper for table TblIdecAVKeylistKey
  */
class TblIdecAVKeylistKey {

public:

public:
	TblIdecAVKeylistKey();
	virtual ~TblIdecAVKeylistKey();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAVKeylistKey** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAVKeylistKey& rst);

	virtual void insertRec(IdecAVKeylistKey* rec);
	ubigint insertNewRec(IdecAVKeylistKey** rec = NULL, const uint klsIxIdecVKeylist = 0, const uint klsNum = 0, const uint x1IxIdecVMaintable = 0, const ubigint x1Uref = 0, const bool Fixed = false, const string sref = "", const string Avail = "", const string Implied = "", const ubigint refJ = 0, const string Title = "", const string Comment = "");
	ubigint appendNewRecToRst(ListIdecAVKeylistKey& rst, IdecAVKeylistKey** rec = NULL, const uint klsIxIdecVKeylist = 0, const uint klsNum = 0, const uint x1IxIdecVMaintable = 0, const ubigint x1Uref = 0, const bool Fixed = false, const string sref = "", const string Avail = "", const string Implied = "", const ubigint refJ = 0, const string Title = "", const string Comment = "");
	virtual void insertRst(ListIdecAVKeylistKey& rst, bool transact = false);
	virtual void updateRec(IdecAVKeylistKey* rec);
	virtual void updateRst(ListIdecAVKeylistKey& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAVKeylistKey** rec);
	virtual bool loadRefByKlsMtbUrfSrf(uint klsIxIdecVKeylist, uint x1IxIdecVMaintable, ubigint x1Uref, string sref, ubigint& ref);
	virtual bool loadRefByKlsSrf(uint klsIxIdecVKeylist, string sref, ubigint& ref);
	virtual ubigint loadRstByKls(uint klsIxIdecVKeylist, const bool append, ListIdecAVKeylistKey& rst);
	virtual ubigint loadRstByKlsMtbUrf(uint klsIxIdecVKeylist, uint x1IxIdecVMaintable, ubigint x1Uref, const bool append, ListIdecAVKeylistKey& rst);
	virtual bool loadTitByRef(ubigint ref, string& Title);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAVKeylistKey& rst);
};

/**
  * LiteTblIdecAVKeylistKey: C++ wrapper for table TblIdecAVKeylistKey (SQLite database)
  */
class LiteTblIdecAVKeylistKey : public TblIdecAVKeylistKey, public LiteTable {

public:
	LiteTblIdecAVKeylistKey();
	~LiteTblIdecAVKeylistKey();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRefByKlsMtbUrfSrf;
	sqlite3_stmt* stmtLoadRefByKlsSrf;
	sqlite3_stmt* stmtLoadRstByKls;
	sqlite3_stmt* stmtLoadRstByKlsMtbUrf;
	sqlite3_stmt* stmtLoadTitByRef;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAVKeylistKey** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAVKeylistKey& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAVKeylistKey** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecAVKeylistKey& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAVKeylistKey** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAVKeylistKey& rst);

	void insertRec(IdecAVKeylistKey* rec);
	void insertRst(ListIdecAVKeylistKey& rst, bool transact = false);
	void updateRec(IdecAVKeylistKey* rec);
	void updateRst(ListIdecAVKeylistKey& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAVKeylistKey** rec);
	bool loadRefByKlsMtbUrfSrf(uint klsIxIdecVKeylist, uint x1IxIdecVMaintable, ubigint x1Uref, string sref, ubigint& ref);
	bool loadRefByKlsSrf(uint klsIxIdecVKeylist, string sref, ubigint& ref);
	ubigint loadRstByKls(uint klsIxIdecVKeylist, const bool append, ListIdecAVKeylistKey& rst);
	ubigint loadRstByKlsMtbUrf(uint klsIxIdecVKeylist, uint x1IxIdecVMaintable, ubigint x1Uref, const bool append, ListIdecAVKeylistKey& rst);
	bool loadTitByRef(ubigint ref, string& Title);
};

#endif

