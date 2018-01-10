/**
  * \file IdecQMisRef1NFile.h
  * Dbs and XML wrapper for table TblIdecQMisRef1NFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQMISREF1NFILE_H
#define IDECQMISREF1NFILE_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQMisRef1NFile: record of TblIdecQMisRef1NFile
  */
class IdecQMisRef1NFile {

public:
	IdecQMisRef1NFile(const ubigint qref = 0, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");

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
  * ListIdecQMisRef1NFile: recordset of TblIdecQMisRef1NFile
  */
class ListIdecQMisRef1NFile {

public:
	ListIdecQMisRef1NFile();
	ListIdecQMisRef1NFile(const ListIdecQMisRef1NFile& src);
	~ListIdecQMisRef1NFile();

	void clear();
	unsigned int size() const;
	void append(IdecQMisRef1NFile* rec);

	ListIdecQMisRef1NFile& operator=(const ListIdecQMisRef1NFile& src);

public:
	vector<IdecQMisRef1NFile*> nodes;

public:
	void writeXML(xmlTextWriter* wr, string difftag = "");
};

/**
  * TblIdecQMisRef1NFile: C++ wrapper for table TblIdecQMisRef1NFile
  */
class TblIdecQMisRef1NFile {

public:
	TblIdecQMisRef1NFile();
	virtual ~TblIdecQMisRef1NFile();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecQMisRef1NFile** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQMisRef1NFile& rst);

	virtual void insertRec(IdecQMisRef1NFile* rec);
	ubigint insertNewRec(IdecQMisRef1NFile** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	ubigint appendNewRecToRst(ListIdecQMisRef1NFile& rst, IdecQMisRef1NFile** rec = NULL, const ubigint jref = 0, const uint jnum = 0, const ubigint ref = 0, const string stubRef = "");
	virtual void insertRst(ListIdecQMisRef1NFile& rst);
	virtual void updateRec(IdecQMisRef1NFile* rec);
	virtual void updateRst(ListIdecQMisRef1NFile& rst);
	virtual void removeRecByQref(ubigint qref);
	virtual void removeRstByJref(ubigint jref);

	virtual bool loadRecByQref(ubigint qref, IdecQMisRef1NFile** rec);
	virtual ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQMisRef1NFile& rst);
};

/**
  * LiteIdecQMisRef1NFile: C++ wrapper for table TblIdecQMisRef1NFile (SQLite database)
  */
class LiteTblIdecQMisRef1NFile : public TblIdecQMisRef1NFile, public LiteTable {

public:
	LiteTblIdecQMisRef1NFile();
	~LiteTblIdecQMisRef1NFile();

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
	bool loadRec(sqlite3_stmt* stmt, IdecQMisRef1NFile** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecQMisRef1NFile& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecQMisRef1NFile** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecQMisRef1NFile& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecQMisRef1NFile** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecQMisRef1NFile& rst);

	void insertRec(IdecQMisRef1NFile* rec);
	void insertRst(ListIdecQMisRef1NFile& rst);
	void updateRec(IdecQMisRef1NFile* rec);
	void updateRst(ListIdecQMisRef1NFile& rst);
	void removeRecByQref(ubigint qref);
	void removeRstByJref(ubigint jref);

	bool loadRecByQref(ubigint qref, IdecQMisRef1NFile** rec);
	ubigint loadRstByJref(ubigint jref, const bool append, ListIdecQMisRef1NFile& rst);
};
#endif

