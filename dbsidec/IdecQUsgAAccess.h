/**
  * \file IdecQUsgAAccess.h
  * Dbs and XML wrapper for table TblIdecQUsgAAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSGAACCESS_H
#define IDECQUSGAACCESS_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsgAAccess: record of TblIdecQUsgAAccess
  */
class IdecQUsgAAccess {

public:
	IdecQUsgAAccess(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const uint x1IxIdecVCard = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const uint ixIdecWUiaccess = 0, const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	uint x1IxIdecVCard;
	string srefX1IxIdecVCard;
	string titX1IxIdecVCard;
	uint ixIdecWUiaccess;
	string srefsIxIdecWUiaccess;
	string titsIxIdecWUiaccess;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQUsgAAccess: recordset of TblIdecQUsgAAccess
  */
class ListIdecQUsgAAccess {

public:
	ListIdecQUsgAAccess();
	ListIdecQUsgAAccess(const ListIdecQUsgAAccess& src);
	~ListIdecQUsgAAccess();

	void clear();
	unsigned int size() const;
	void append(IdecQUsgAAccess* rec);

	ListIdecQUsgAAccess& operator=(const ListIdecQUsgAAccess& src);

public:
	vector<IdecQUsgAAccess*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsgAAccess: C++ wrapper for table TblIdecQUsgAAccess
  */
class TblIdecQUsgAAccess {

public:
	TblIdecQUsgAAccess();
	virtual ~TblIdecQUsgAAccess();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsgAAccess** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsgAAccess& rst);

	virtual void insertRec(IdecQUsgAAccess* rec);
	ubigint insertNewRec(IdecQUsgAAccess** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const uint x1IxIdecVCard = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const uint ixIdecWUiaccess = 0, const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");
	ubigint appendNewRecToRst(ListIdecQUsgAAccess& rst, IdecQUsgAAccess** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const uint x1IxIdecVCard = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const uint ixIdecWUiaccess = 0, const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");
	virtual void insertRst(ListIdecQUsgAAccess& rst);
	virtual void updateRec(IdecQUsgAAccess* rec);
	virtual void updateRst(ListIdecQUsgAAccess& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsgAAccess** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsgAAccess& rst);
};

/**
  * LiteIdecQUsgAAccess: C++ wrapper for table TblIdecQUsgAAccess (SQLite database)
  */
class LiteTblIdecQUsgAAccess : public TblIdecQUsgAAccess, public LiteTable {

public:
	LiteTblIdecQUsgAAccess();
	~LiteTblIdecQUsgAAccess();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsgAAccess** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsgAAccess& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsgAAccess** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsgAAccess& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsgAAccess** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsgAAccess& rst);

	void insertRec(IdecQUsgAAccess* rec);
	void insertRst(ListIdecQUsgAAccess& rst);
	void updateRec(IdecQUsgAAccess* rec);
	void updateRst(ListIdecQUsgAAccess& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsgAAccess** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsgAAccess& rst);
};
#endif

