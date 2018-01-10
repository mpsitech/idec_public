/**
  * \file IdecQUsrAAccess.h
  * Dbs and XML wrapper for table TblIdecQUsrAAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSRAACCESS_H
#define IDECQUSRAACCESS_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsrAAccess: record of TblIdecQUsrAAccess
  */
class IdecQUsrAAccess {

public:
	IdecQUsrAAccess(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const uint x1IxIdecVCard = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const uint ixIdecWUiaccess = 0, const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");

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
  * ListIdecQUsrAAccess: recordset of TblIdecQUsrAAccess
  */
class ListIdecQUsrAAccess {

public:
	ListIdecQUsrAAccess();
	ListIdecQUsrAAccess(const ListIdecQUsrAAccess& src);
	~ListIdecQUsrAAccess();

	void clear();
	unsigned int size() const;
	void append(IdecQUsrAAccess* rec);

	ListIdecQUsrAAccess& operator=(const ListIdecQUsrAAccess& src);

public:
	vector<IdecQUsrAAccess*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsrAAccess: C++ wrapper for table TblIdecQUsrAAccess
  */
class TblIdecQUsrAAccess {

public:
	TblIdecQUsrAAccess();
	virtual ~TblIdecQUsrAAccess();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsrAAccess** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsrAAccess& rst);

	virtual void insertRec(IdecQUsrAAccess* rec);
	ubigint insertNewRec(IdecQUsrAAccess** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const uint x1IxIdecVCard = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const uint ixIdecWUiaccess = 0, const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");
	ubigint appendNewRecToRst(ListIdecQUsrAAccess& rst, IdecQUsrAAccess** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const uint x1IxIdecVCard = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const uint ixIdecWUiaccess = 0, const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");
	virtual void insertRst(ListIdecQUsrAAccess& rst);
	virtual void updateRec(IdecQUsrAAccess* rec);
	virtual void updateRst(ListIdecQUsrAAccess& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsrAAccess** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsrAAccess& rst);
};

/**
  * LiteIdecQUsrAAccess: C++ wrapper for table TblIdecQUsrAAccess (SQLite database)
  */
class LiteTblIdecQUsrAAccess : public TblIdecQUsrAAccess, public LiteTable {

public:
	LiteTblIdecQUsrAAccess();
	~LiteTblIdecQUsrAAccess();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsrAAccess** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsrAAccess& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsrAAccess** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsrAAccess& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsrAAccess** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsrAAccess& rst);

	void insertRec(IdecQUsrAAccess* rec);
	void insertRst(ListIdecQUsrAAccess& rst);
	void updateRec(IdecQUsrAAccess* rec);
	void updateRst(ListIdecQUsrAAccess& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsrAAccess** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsrAAccess& rst);
};
#endif

