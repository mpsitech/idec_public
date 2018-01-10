/**
  * \file IdecQUsgMNUser.h
  * Dbs and XML wrapper for table TblIdecQUsgMNUser (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSGMNUSER_H
#define IDECQUSGMNUSER_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsgMNUser: record of TblIdecQUsgMNUser
  */
class IdecQUsgMNUser {

public:
	IdecQUsgMNUser(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint mref = 0, const string stubMref = "", const ubigint ref = 0, const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint mref;
	string stubMref;
	ubigint ref;
	uint ixIdecVUserlevel;
	string srefIxIdecVUserlevel;
	string titIxIdecVUserlevel;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQUsgMNUser: recordset of TblIdecQUsgMNUser
  */
class ListIdecQUsgMNUser {

public:
	ListIdecQUsgMNUser();
	ListIdecQUsgMNUser(const ListIdecQUsgMNUser& src);
	~ListIdecQUsgMNUser();

	void clear();
	unsigned int size() const;
	void append(IdecQUsgMNUser* rec);

	ListIdecQUsgMNUser& operator=(const ListIdecQUsgMNUser& src);

public:
	vector<IdecQUsgMNUser*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsgMNUser: C++ wrapper for table TblIdecQUsgMNUser
  */
class TblIdecQUsgMNUser {

public:
	TblIdecQUsgMNUser();
	virtual ~TblIdecQUsgMNUser();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsgMNUser** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsgMNUser& rst);

	virtual void insertRec(IdecQUsgMNUser* rec);
	ubigint insertNewRec(IdecQUsgMNUser** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint mref = 0, const string stubMref = "", const ubigint ref = 0, const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");
	ubigint appendNewRecToRst(ListIdecQUsgMNUser& rst, IdecQUsgMNUser** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint mref = 0, const string stubMref = "", const ubigint ref = 0, const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");
	virtual void insertRst(ListIdecQUsgMNUser& rst);
	virtual void updateRec(IdecQUsgMNUser* rec);
	virtual void updateRst(ListIdecQUsgMNUser& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsgMNUser** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsgMNUser& rst);
};

/**
  * LiteIdecQUsgMNUser: C++ wrapper for table TblIdecQUsgMNUser (SQLite database)
  */
class LiteTblIdecQUsgMNUser : public TblIdecQUsgMNUser, public LiteTable {

public:
	LiteTblIdecQUsgMNUser();
	~LiteTblIdecQUsgMNUser();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsgMNUser** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsgMNUser& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsgMNUser** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsgMNUser& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsgMNUser** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsgMNUser& rst);

	void insertRec(IdecQUsgMNUser* rec);
	void insertRst(ListIdecQUsgMNUser& rst);
	void updateRec(IdecQUsgMNUser* rec);
	void updateRst(ListIdecQUsgMNUser& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsgMNUser** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsgMNUser& rst);
};
#endif

