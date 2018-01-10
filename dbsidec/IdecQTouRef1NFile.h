/**
  * \file IdecQTouRef1NFile.h
  * Dbs and XML wrapper for table TblIdecQTouRef1NFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQTOUREF1NFILE_H
#define IDECQTOUREF1NFILE_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQTouRef1NFile: record of TblIdecQTouRef1NFile
  */
class IdecQTouRef1NFile {

public:
	IdecQTouRef1NFile(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");

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
  * ListIdecQTouRef1NFile: recordset of TblIdecQTouRef1NFile
  */
class ListIdecQTouRef1NFile {

public:
	ListIdecQTouRef1NFile();
	ListIdecQTouRef1NFile(const ListIdecQTouRef1NFile& src);
	~ListIdecQTouRef1NFile();

	void clear();
	unsigned int size() const;
	void append(IdecQTouRef1NFile* rec);

	ListIdecQTouRef1NFile& operator=(const ListIdecQTouRef1NFile& src);

public:
	vector<IdecQTouRef1NFile*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQTouRef1NFile: C++ wrapper for table TblIdecQTouRef1NFile
  */
class TblIdecQTouRef1NFile {

public:
	TblIdecQTouRef1NFile();
	virtual ~TblIdecQTouRef1NFile();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQTouRef1NFile** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQTouRef1NFile& rst);

	virtual void insertRec(IdecQTouRef1NFile* rec);
	ubigint insertNewRec(IdecQTouRef1NFile** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	ubigint appendNewRecToRst(ListIdecQTouRef1NFile& rst, IdecQTouRef1NFile** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	virtual void insertRst(ListIdecQTouRef1NFile& rst);
	virtual void updateRec(IdecQTouRef1NFile* rec);
	virtual void updateRst(ListIdecQTouRef1NFile& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQTouRef1NFile** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQTouRef1NFile& rst);
};

/**
  * LiteIdecQTouRef1NFile: C++ wrapper for table TblIdecQTouRef1NFile (SQLite database)
  */
class LiteTblIdecQTouRef1NFile : public TblIdecQTouRef1NFile, public LiteTable {

public:
	LiteTblIdecQTouRef1NFile();
	~LiteTblIdecQTouRef1NFile();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQTouRef1NFile** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQTouRef1NFile& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQTouRef1NFile** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQTouRef1NFile& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQTouRef1NFile** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQTouRef1NFile& rst);

	void insertRec(IdecQTouRef1NFile* rec);
	void insertRst(ListIdecQTouRef1NFile& rst);
	void updateRec(IdecQTouRef1NFile* rec);
	void updateRst(ListIdecQTouRef1NFile& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQTouRef1NFile** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQTouRef1NFile& rst);
};
#endif

