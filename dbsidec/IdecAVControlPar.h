/**
  * \file IdecAVControlPar.h
  * database access for table TblIdecAVControlPar (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECAVCONTROLPAR_H
#define IDECAVCONTROLPAR_H

#include <sbecore/LiteDbs.h>

/**
  * IdecAVControlPar: record of TblIdecAVControlPar
  */
class IdecAVControlPar {

public:
	IdecAVControlPar(const ubigint ref = 0, const uint ixIdecVControl = 0, const ubigint x1RefIdecMUser = 0, const uint x2IxIdecVLocale = 0, const string Par = "", const string Val = "");

public:
	ubigint ref;
	uint ixIdecVControl;
	ubigint x1RefIdecMUser;
	uint x2IxIdecVLocale;
	string Par;
	string Val;

public:
	bool operator==(const IdecAVControlPar& comp);
	bool operator!=(const IdecAVControlPar& comp);
};

/**
  * ListIdecAVControlPar: recordset of TblIdecAVControlPar
  */
class ListIdecAVControlPar {

public:
	ListIdecAVControlPar();
	ListIdecAVControlPar(const ListIdecAVControlPar& src);
	~ListIdecAVControlPar();

	void clear();
	unsigned int size() const;
	void append(IdecAVControlPar* rec);

	IdecAVControlPar* operator[](const uint ix);
	ListIdecAVControlPar& operator=(const ListIdecAVControlPar& src);
	bool operator==(const ListIdecAVControlPar& comp);
	bool operator!=(const ListIdecAVControlPar& comp);

public:
	vector<IdecAVControlPar*> nodes;
};

/**
  * TblIdecAVControlPar: C++ wrapper for table TblIdecAVControlPar
  */
class TblIdecAVControlPar {

public:

public:
	TblIdecAVControlPar();
	virtual ~TblIdecAVControlPar();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecAVControlPar** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAVControlPar& rst);

	virtual void insertRec(IdecAVControlPar* rec);
	ubigint insertNewRec(IdecAVControlPar** rec = NULL, const uint ixIdecVControl = 0, const ubigint x1RefIdecMUser = 0, const uint x2IxIdecVLocale = 0, const string Par = "", const string Val = "");
	ubigint appendNewRecToRst(ListIdecAVControlPar& rst, IdecAVControlPar** rec = NULL, const uint ixIdecVControl = 0, const ubigint x1RefIdecMUser = 0, const uint x2IxIdecVLocale = 0, const string Par = "", const string Val = "");
	virtual void insertRst(ListIdecAVControlPar& rst, bool transact = false);
	virtual void updateRec(IdecAVControlPar* rec);
	virtual void updateRst(ListIdecAVControlPar& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecAVControlPar** rec);
	virtual bool loadRefByCtlUsrPar(uint ixIdecVControl, ubigint x1RefIdecMUser, string Par, ubigint& ref);
	virtual bool loadValByCtlUsrPar(uint ixIdecVControl, ubigint x1RefIdecMUser, string Par, string& Val);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecAVControlPar& rst);
};

/**
  * LiteTblIdecAVControlPar: C++ wrapper for table TblIdecAVControlPar (SQLite database)
  */
class LiteTblIdecAVControlPar : public TblIdecAVControlPar, public LiteTable {

public:
	LiteTblIdecAVControlPar();
	~LiteTblIdecAVControlPar();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRefByCtlUsrPar;
	sqlite3_stmt* stmtLoadValByCtlUsrPar;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecAVControlPar** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecAVControlPar& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecAVControlPar** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecAVControlPar** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecAVControlPar& rst);

	void insertRec(IdecAVControlPar* rec);
	void insertRst(ListIdecAVControlPar& rst, bool transact = false);
	void updateRec(IdecAVControlPar* rec);
	void updateRst(ListIdecAVControlPar& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecAVControlPar** rec);
	bool loadRefByCtlUsrPar(uint ixIdecVControl, ubigint x1RefIdecMUser, string Par, ubigint& ref);
	bool loadValByCtlUsrPar(uint ixIdecVControl, ubigint x1RefIdecMUser, string Par, string& Val);
};

#endif

