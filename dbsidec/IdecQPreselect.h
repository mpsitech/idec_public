/**
  * \file IdecQPreselect.h
  * Dbs and XML wrapper for table TblIdecQPreselect (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQPRESELECT_H
#define IDECQPRESELECT_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQPreselect: record of TblIdecQPreselect
  */
class IdecQPreselect {

public:
	IdecQPreselect(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0);

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQPreselect: recordset of TblIdecQPreselect
  */
class ListIdecQPreselect {

public:
	ListIdecQPreselect();
	ListIdecQPreselect(const ListIdecQPreselect& src);
	~ListIdecQPreselect();

	void clear();
	unsigned int size() const;
	void append(IdecQPreselect* rec);

	ListIdecQPreselect& operator=(const ListIdecQPreselect& src);

public:
	vector<IdecQPreselect*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQPreselect: C++ wrapper for table TblIdecQPreselect
  */
class TblIdecQPreselect {

public:
	TblIdecQPreselect();
	virtual ~TblIdecQPreselect();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQPreselect** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQPreselect& rst);

	virtual void insertRec(IdecQPreselect* rec);
	ubigint insertNewRec(IdecQPreselect** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0);
	ubigint appendNewRecToRst(ListIdecQPreselect& rst, IdecQPreselect** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0);
	virtual void insertRst(ListIdecQPreselect& rst);
	virtual void updateRec(IdecQPreselect* rec);
	virtual void updateRst(ListIdecQPreselect& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQPreselect** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQPreselect& rst);
};

/**
  * LiteIdecQPreselect: C++ wrapper for table TblIdecQPreselect (SQLite database)
  */
class LiteTblIdecQPreselect : public TblIdecQPreselect, public LiteTable {

public:
	LiteTblIdecQPreselect();
	~LiteTblIdecQPreselect();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByQref;
	sqlite3_stmt* stmtRemoveRstByJref;

	sqlite3_stmt* stmtLoadRecByQref;
	sqlite3_stmt* stmtLoadRecByJref;
	sqlite3_stmt* stmtLoadRstByJref;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecQPreselect** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQPreselect& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQPreselect** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQPreselect& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQPreselect** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQPreselect& rst);

	void insertRec(IdecQPreselect* rec);
	void insertRst(ListIdecQPreselect& rst);
	void updateRec(IdecQPreselect* rec);
	void updateRst(ListIdecQPreselect& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQPreselect** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQPreselect& rst);
};
#endif

