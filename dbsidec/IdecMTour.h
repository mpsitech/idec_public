/**
  * \file IdecMTour.h
  * database access for table TblIdecMTour (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMTOUR_H
#define IDECMTOUR_H

#include <sbecore/LiteDbs.h>

/**
  * IdecMTour: record of TblIdecMTour
  */
class IdecMTour {

public:
	IdecMTour(const ubigint ref = 0, const ubigint refIdecMMission = 0, const string Title = "", const uint start = 0, const uint stop = 0, const string Area = "", const double theta = 0.0, const double phi = 0.0, const string Comment = "");

public:
	ubigint ref;
	ubigint refIdecMMission;
	string Title;
	uint start;
	uint stop;
	string Area;
	double theta;
	double phi;
	string Comment;

public:
	bool operator==(const IdecMTour& comp);
	bool operator!=(const IdecMTour& comp);
};

/**
  * ListIdecMTour: recordset of TblIdecMTour
  */
class ListIdecMTour {

public:
	ListIdecMTour();
	ListIdecMTour(const ListIdecMTour& src);
	~ListIdecMTour();

	void clear();
	unsigned int size() const;
	void append(IdecMTour* rec);

	IdecMTour* operator[](const uint ix);
	ListIdecMTour& operator=(const ListIdecMTour& src);
	bool operator==(const ListIdecMTour& comp);
	bool operator!=(const ListIdecMTour& comp);

public:
	vector<IdecMTour*> nodes;
};

/**
  * TblIdecMTour: C++ wrapper for table TblIdecMTour
  */
class TblIdecMTour {

public:

public:
	TblIdecMTour();
	virtual ~TblIdecMTour();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMTour** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMTour& rst);

	virtual void insertRec(IdecMTour* rec);
	ubigint insertNewRec(IdecMTour** rec = NULL, const ubigint refIdecMMission = 0, const string Title = "", const uint start = 0, const uint stop = 0, const string Area = "", const double theta = 0.0, const double phi = 0.0, const string Comment = "");
	ubigint appendNewRecToRst(ListIdecMTour& rst, IdecMTour** rec = NULL, const ubigint refIdecMMission = 0, const string Title = "", const uint start = 0, const uint stop = 0, const string Area = "", const double theta = 0.0, const double phi = 0.0, const string Comment = "");
	virtual void insertRst(ListIdecMTour& rst, bool transact = false);
	virtual void updateRec(IdecMTour* rec);
	virtual void updateRst(ListIdecMTour& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMTour** rec);
	virtual ubigint loadRstByMis(ubigint refIdecMMission, const bool append, ListIdecMTour& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMTour& rst);
};

/**
  * LiteTblIdecMTour: C++ wrapper for table TblIdecMTour (SQLite database)
  */
class LiteTblIdecMTour : public TblIdecMTour, public LiteTable {

public:
	LiteTblIdecMTour();
	~LiteTblIdecMTour();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRstByMis;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMTour** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMTour& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMTour** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecMTour& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMTour** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMTour& rst);

	void insertRec(IdecMTour* rec);
	void insertRst(ListIdecMTour& rst, bool transact = false);
	void updateRec(IdecMTour* rec);
	void updateRst(ListIdecMTour& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMTour** rec);
	ubigint loadRstByMis(ubigint refIdecMMission, const bool append, ListIdecMTour& rst);
};

#endif

