/**
  * \file IdecQUsrList.h
  * Dbs and XML wrapper for table TblIdecQUsrList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSRLIST_H
#define IDECQUSRLIST_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsrList: record of TblIdecQUsrList
  */
class IdecQUsrList {

public:
	IdecQUsrList(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const ubigint refIdecMPerson = 0, const string stubRefIdecMPerson = "", const string sref = "", const ubigint refIdecMUsergroup = 0, const string stubRefIdecMUsergroup = "", const uint ixVState = 0, const string srefIxVState = "", const string titIxVState = "", const uint ixIdecVLocale = 0, const string srefIxIdecVLocale = "", const string titIxIdecVLocale = "", const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	ubigint refIdecMPerson;
	string stubRefIdecMPerson;
	string sref;
	ubigint refIdecMUsergroup;
	string stubRefIdecMUsergroup;
	uint ixVState;
	string srefIxVState;
	string titIxVState;
	uint ixIdecVLocale;
	string srefIxIdecVLocale;
	string titIxIdecVLocale;
	uint ixIdecVUserlevel;
	string srefIxIdecVUserlevel;
	string titIxIdecVUserlevel;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQUsrList: recordset of TblIdecQUsrList
  */
class ListIdecQUsrList {

public:
	ListIdecQUsrList();
	ListIdecQUsrList(const ListIdecQUsrList& src);
	~ListIdecQUsrList();

	void clear();
	unsigned int size() const;
	void append(IdecQUsrList* rec);

	ListIdecQUsrList& operator=(const ListIdecQUsrList& src);

public:
	vector<IdecQUsrList*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQUsrList: C++ wrapper for table TblIdecQUsrList
  */
class TblIdecQUsrList {

public:
	TblIdecQUsrList();
	virtual ~TblIdecQUsrList();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQUsrList** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsrList& rst);

	virtual void insertRec(IdecQUsrList* rec);
	ubigint insertNewRec(IdecQUsrList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const ubigint refIdecMPerson = 0, const string stubRefIdecMPerson = "", const string sref = "", const ubigint refIdecMUsergroup = 0, const string stubRefIdecMUsergroup = "", const uint ixVState = 0, const string srefIxVState = "", const string titIxVState = "", const uint ixIdecVLocale = 0, const string srefIxIdecVLocale = "", const string titIxIdecVLocale = "", const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");
	ubigint appendNewRecToRst(ListIdecQUsrList& rst, IdecQUsrList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const ubigint refIdecMPerson = 0, const string stubRefIdecMPerson = "", const string sref = "", const ubigint refIdecMUsergroup = 0, const string stubRefIdecMUsergroup = "", const uint ixVState = 0, const string srefIxVState = "", const string titIxVState = "", const uint ixIdecVLocale = 0, const string srefIxIdecVLocale = "", const string titIxIdecVLocale = "", const uint ixIdecVUserlevel = 0, const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");
	virtual void insertRst(ListIdecQUsrList& rst);
	virtual void updateRec(IdecQUsrList* rec);
	virtual void updateRst(ListIdecQUsrList& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQUsrList** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsrList& rst);
};

/**
  * LiteIdecQUsrList: C++ wrapper for table TblIdecQUsrList (SQLite database)
  */
class LiteTblIdecQUsrList : public TblIdecQUsrList, public LiteTable {

public:
	LiteTblIdecQUsrList();
	~LiteTblIdecQUsrList();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQUsrList** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQUsrList& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQUsrList** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQUsrList& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQUsrList** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQUsrList& rst);

	void insertRec(IdecQUsrList* rec);
	void insertRst(ListIdecQUsrList& rst);
	void updateRec(IdecQUsrList* rec);
	void updateRst(ListIdecQUsrList& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQUsrList** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQUsrList& rst);
};
#endif

