/**
  * \file IdecQMis1NTour.h
  * Dbs and XML wrapper for table TblIdecQMis1NTour (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQMIS1NTOUR_H
#define IDECQMIS1NTOUR_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQMis1NTour: record of TblIdecQMis1NTour
  */
class IdecQMis1NTour {

public:
	IdecQMis1NTour(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");

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
  * ListIdecQMis1NTour: recordset of TblIdecQMis1NTour
  */
class ListIdecQMis1NTour {

public:
	ListIdecQMis1NTour();
	ListIdecQMis1NTour(const ListIdecQMis1NTour& src);
	~ListIdecQMis1NTour();

	void clear();
	unsigned int size() const;
	void append(IdecQMis1NTour* rec);

	ListIdecQMis1NTour& operator=(const ListIdecQMis1NTour& src);

public:
	vector<IdecQMis1NTour*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQMis1NTour: C++ wrapper for table TblIdecQMis1NTour
  */
class TblIdecQMis1NTour {

public:
	TblIdecQMis1NTour();
	virtual ~TblIdecQMis1NTour();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQMis1NTour** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQMis1NTour& rst);

	virtual void insertRec(IdecQMis1NTour* rec);
	ubigint insertNewRec(IdecQMis1NTour** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	ubigint appendNewRecToRst(ListIdecQMis1NTour& rst, IdecQMis1NTour** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	virtual void insertRst(ListIdecQMis1NTour& rst);
	virtual void updateRec(IdecQMis1NTour* rec);
	virtual void updateRst(ListIdecQMis1NTour& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQMis1NTour** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQMis1NTour& rst);
};

/**
  * LiteIdecQMis1NTour: C++ wrapper for table TblIdecQMis1NTour (SQLite database)
  */
class LiteTblIdecQMis1NTour : public TblIdecQMis1NTour, public LiteTable {

public:
	LiteTblIdecQMis1NTour();
	~LiteTblIdecQMis1NTour();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQMis1NTour** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQMis1NTour& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQMis1NTour** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQMis1NTour& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQMis1NTour** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQMis1NTour& rst);

	void insertRec(IdecQMis1NTour* rec);
	void insertRst(ListIdecQMis1NTour& rst);
	void updateRec(IdecQMis1NTour* rec);
	void updateRst(ListIdecQMis1NTour& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQMis1NTour** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQMis1NTour& rst);
};
#endif

