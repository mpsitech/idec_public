/**
  * \file IdecQMisList.h
  * Dbs and XML wrapper for table TblIdecQMisList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQMISLIST_H
#define IDECQMISLIST_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQMisList: record of TblIdecQMisList
  */
class IdecQMisList {

public:
	IdecQMisList(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Title = "", const ubigint grp = 0, const string stubGrp = "", const ubigint own = 0, const string stubOwn = "", const uint startd = 0, const string ftmStartd = "", const uint stopd = 0, const string ftmStopd = "", const string srefKCountry = "", const string titSrefKCountry = "", const string Region = "", const string Municipality = "");

public:
	ubigint qref;
	ubigint jref;
	uint jnum;
	ubigint ref;
	string Title;
	ubigint grp;
	string stubGrp;
	ubigint own;
	string stubOwn;
	uint startd;
	string ftmStartd;
	uint stopd;
	string ftmStopd;
	string srefKCountry;
	string titSrefKCountry;
	string Region;
	string Municipality;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "", bool jnumattr = false, bool shorttags = false);
};

/**
  * ListIdecQMisList: recordset of TblIdecQMisList
  */
class ListIdecQMisList {

public:
	ListIdecQMisList();
	ListIdecQMisList(const ListIdecQMisList& src);
	~ListIdecQMisList();

	void clear();
	unsigned int size() const;
	void append(IdecQMisList* rec);

	ListIdecQMisList& operator=(const ListIdecQMisList& src);

public:
	vector<IdecQMisList*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQMisList: C++ wrapper for table TblIdecQMisList
  */
class TblIdecQMisList {

public:
	TblIdecQMisList();
	virtual ~TblIdecQMisList();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQMisList** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQMisList& rst);

	virtual void insertRec(IdecQMisList* rec);
	ubigint insertNewRec(IdecQMisList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Title = "", const ubigint grp = 0, const string stubGrp = "", const ubigint own = 0, const string stubOwn = "", const uint startd = 0, const string ftmStartd = "", const uint stopd = 0, const string ftmStopd = "", const string srefKCountry = "", const string titSrefKCountry = "", const string Region = "", const string Municipality = "");
	ubigint appendNewRecToRst(ListIdecQMisList& rst, IdecQMisList** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string Title = "", const ubigint grp = 0, const string stubGrp = "", const ubigint own = 0, const string stubOwn = "", const uint startd = 0, const string ftmStartd = "", const uint stopd = 0, const string ftmStopd = "", const string srefKCountry = "", const string titSrefKCountry = "", const string Region = "", const string Municipality = "");
	virtual void insertRst(ListIdecQMisList& rst);
	virtual void updateRec(IdecQMisList* rec);
	virtual void updateRst(ListIdecQMisList& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQMisList** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQMisList& rst);
};

/**
  * LiteIdecQMisList: C++ wrapper for table TblIdecQMisList (SQLite database)
  */
class LiteTblIdecQMisList : public TblIdecQMisList, public LiteTable {

public:
	LiteTblIdecQMisList();
	~LiteTblIdecQMisList();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQMisList** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQMisList& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQMisList** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQMisList& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQMisList** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQMisList& rst);

	void insertRec(IdecQMisList* rec);
	void insertRst(ListIdecQMisList& rst);
	void updateRec(IdecQMisList* rec);
	void updateRst(ListIdecQMisList& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQMisList** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQMisList& rst);
};
#endif

