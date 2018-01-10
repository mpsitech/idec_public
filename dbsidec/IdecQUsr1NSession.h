/**
  * \file IdecQUsr1NSession.h
  * Dbs and XML wrapper for table TblIdecQUsr1NSession (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSR1NSESSION_H
#define IDECQUSR1NSESSION_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsr1NSession: record of TblIdecQUsr1NSession
  */
class IdecQUsr1NSession {

public:
	IdecQUsr1NSession(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	string stubRef;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQUsr1NSession: recordset of TblIdecQUsr1NSession
  */
class ListIdecQUsr1NSession {

public:
	ListIdecQUsr1NSession();
	ListIdecQUsr1NSession(const ListIdecQUsr1NSession& src);
	~ListIdecQUsr1NSession();

	void clear();
	unsigned int size() const;
	void append(IdecQUsr1NSession* rec);

	ListIdecQUsr1NSession& operator=(const ListIdecQUsr1NSession& src);

public:
	vector<IdecQUsr1NSession*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsr1NSession: C++ wrapper for table TblIdecQUsr1NSession
  */
class TblIdecQUsr1NSession {

public:
	TblIdecQUsr1NSession();
	virtual ~TblIdecQUsr1NSession();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsr1NSession** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsr1NSession& rst);

	virtual void insertRec(IdecQUsr1NSession* rec);
	ubigint insertNewRec(IdecQUsr1NSession** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	ubigint appendNewRecToRst(ListIdecQUsr1NSession& rst, IdecQUsr1NSession** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	virtual void insertRst(ListIdecQUsr1NSession& rst);
	virtual void updateRec(IdecQUsr1NSession* rec);
	virtual void updateRst(ListIdecQUsr1NSession& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsr1NSession** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsr1NSession& rst);
};

/**
  * LiteIdecQUsr1NSession: C++ wrapper for table TblIdecQUsr1NSession (SQLite database)
  */
class LiteTblIdecQUsr1NSession : public TblIdecQUsr1NSession, public LiteTable {

public:
	LiteTblIdecQUsr1NSession();
	~LiteTblIdecQUsr1NSession();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsr1NSession** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsr1NSession& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsr1NSession** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsr1NSession& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsr1NSession** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsr1NSession& rst);

	void insertRec(IdecQUsr1NSession* rec);
	void insertRst(ListIdecQUsr1NSession& rst);
	void updateRec(IdecQUsr1NSession* rec);
	void updateRst(ListIdecQUsr1NSession& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsr1NSession** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsr1NSession& rst);
};
#endif

