/**
  * \file IdecQSelect.h
  * Dbs and XML wrapper for table TblIdecQSelect (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQSELECT_H
#define IDECQSELECT_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQSelect: record of TblIdecQSelect
  */
class IdecQSelect {

public:
	IdecQSelect(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const uint ix = 0, const ubigint ref = 0);

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	uint ix;
	ubigint ref;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQSelect: recordset of TblIdecQSelect
  */
class ListIdecQSelect {

public:
	ListIdecQSelect();
	ListIdecQSelect(const ListIdecQSelect& src);
	~ListIdecQSelect();

	void clear();
	unsigned int size() const;
	void append(IdecQSelect* rec);

	ListIdecQSelect& operator=(const ListIdecQSelect& src);

public:
	vector<IdecQSelect*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQSelect: C++ wrapper for table TblIdecQSelect
  */
class TblIdecQSelect {

public:
	TblIdecQSelect();
	virtual ~TblIdecQSelect();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQSelect** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQSelect& rst);

	virtual void insertRec(IdecQSelect* rec);
	ubigint insertNewRec(IdecQSelect** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const uint ix = 0, const ubigint ref = 0);
	ubigint appendNewRecToRst(ListIdecQSelect& rst, IdecQSelect** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const uint ix = 0, const ubigint ref = 0);
	virtual void insertRst(ListIdecQSelect& rst);
	virtual void updateRec(IdecQSelect* rec);
	virtual void updateRst(ListIdecQSelect& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQSelect** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQSelect& rst);
};

/**
  * LiteIdecQSelect: C++ wrapper for table TblIdecQSelect (SQLite database)
  */
class LiteTblIdecQSelect : public TblIdecQSelect, public LiteTable {

public:
	LiteTblIdecQSelect();
	~LiteTblIdecQSelect();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQSelect** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQSelect& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQSelect** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQSelect& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQSelect** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQSelect& rst);

	void insertRec(IdecQSelect* rec);
	void insertRst(ListIdecQSelect& rst);
	void updateRec(IdecQSelect* rec);
	void updateRst(ListIdecQSelect& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQSelect** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQSelect& rst);
};
#endif

