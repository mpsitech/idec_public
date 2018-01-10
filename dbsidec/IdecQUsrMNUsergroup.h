/**
  * \file IdecQUsrMNUsergroup.h
  * Dbs and XML wrapper for table TblIdecQUsrMNUsergroup (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSRMNUSERGROUP_H
#define IDECQUSRMNUSERGROUP_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsrMNUsergroup: record of TblIdecQUsrMNUsergroup
  */
class IdecQUsrMNUsergroup {

public:
	IdecQUsrMNUsergroup(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint mref = 0, const string stubMref = "", const ubigint ref = 0, const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");

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
  * ListIdecQUsrMNUsergroup: recordset of TblIdecQUsrMNUsergroup
  */
class ListIdecQUsrMNUsergroup {

public:
	ListIdecQUsrMNUsergroup();
	ListIdecQUsrMNUsergroup(const ListIdecQUsrMNUsergroup& src);
	~ListIdecQUsrMNUsergroup();

	void clear();
	unsigned int size() const;
	void append(IdecQUsrMNUsergroup* rec);

	ListIdecQUsrMNUsergroup& operator=(const ListIdecQUsrMNUsergroup& src);

public:
	vector<IdecQUsrMNUsergroup*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsrMNUsergroup: C++ wrapper for table TblIdecQUsrMNUsergroup
  */
class TblIdecQUsrMNUsergroup {

public:
	TblIdecQUsrMNUsergroup();
	virtual ~TblIdecQUsrMNUsergroup();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsrMNUsergroup** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsrMNUsergroup& rst);

	virtual void insertRec(IdecQUsrMNUsergroup* rec);
	ubigint insertNewRec(IdecQUsrMNUsergroup** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint mref = 0, const string stubMref = "", const ubigint ref = 0, const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");
	ubigint appendNewRecToRst(ListIdecQUsrMNUsergroup& rst, IdecQUsrMNUsergroup** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint mref = 0, const string stubMref = "", const ubigint ref = 0, const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");
	virtual void insertRst(ListIdecQUsrMNUsergroup& rst);
	virtual void updateRec(IdecQUsrMNUsergroup* rec);
	virtual void updateRst(ListIdecQUsrMNUsergroup& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsrMNUsergroup** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsrMNUsergroup& rst);
};

/**
  * LiteIdecQUsrMNUsergroup: C++ wrapper for table TblIdecQUsrMNUsergroup (SQLite database)
  */
class LiteTblIdecQUsrMNUsergroup : public TblIdecQUsrMNUsergroup, public LiteTable {

public:
	LiteTblIdecQUsrMNUsergroup();
	~LiteTblIdecQUsrMNUsergroup();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsrMNUsergroup** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsrMNUsergroup& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsrMNUsergroup** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsrMNUsergroup& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsrMNUsergroup** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsrMNUsergroup& rst);

	void insertRec(IdecQUsrMNUsergroup* rec);
	void insertRst(ListIdecQUsrMNUsergroup& rst);
	void updateRec(IdecQUsrMNUsergroup* rec);
	void updateRst(ListIdecQUsrMNUsergroup& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsrMNUsergroup** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsrMNUsergroup& rst);
};
#endif

