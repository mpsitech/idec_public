/**
  * \file IdecMFile.h
  * database access for table TblIdecMFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMFILE_H
#define IDECMFILE_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

#define VecIdecVMFileRefTbl TblIdecMFile::VecVRefTbl

/**
  * IdecMFile: record of TblIdecMFile
  */
class IdecMFile {

public:
	IdecMFile(const ubigint ref = 0, const ubigint grp = 0, const ubigint own = 0, const ubigint refIdecCFile = 0, const uint refIxVTbl = 0, const ubigint refUref = 0, const string osrefKContent = "", const uint Archived = 0, const string Filename = "", const string Archivename = "", const string srefKMimetype = "", const usmallint Size = 0, const string Comment = "");

public:
	ubigint ref;
	ubigint grp;
	ubigint own;
	ubigint refIdecCFile;
	uint refIxVTbl;
	ubigint refUref;
	string osrefKContent;
	uint Archived;
	string Filename;
	string Archivename;
	string srefKMimetype;
	usmallint Size;
	string Comment;

public:
	bool operator==(const IdecMFile& comp);
	bool operator!=(const IdecMFile& comp);
};

/**
  * ListIdecMFile: recordset of TblIdecMFile
  */
class ListIdecMFile {

public:
	ListIdecMFile();
	ListIdecMFile(const ListIdecMFile& src);
	~ListIdecMFile();

	void clear();
	unsigned int size() const;
	void append(IdecMFile* rec);

	IdecMFile* operator[](const uint ix);
	ListIdecMFile& operator=(const ListIdecMFile& src);
	bool operator==(const ListIdecMFile& comp);
	bool operator!=(const ListIdecMFile& comp);

public:
	vector<IdecMFile*> nodes;
};

/**
  * TblIdecMFile: C++ wrapper for table TblIdecMFile
  */
class TblIdecMFile {

public:
	/**
		* VecVRefTbl (full: VecIdecVMFileRefTbl)
		*/
	class VecVRefTbl {

	public:
		static const uint VOID = 1;
		static const uint MIS = 2;
		static const uint TOU = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

public:
	TblIdecMFile();
	virtual ~TblIdecMFile();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMFile** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMFile& rst);

	virtual void insertRec(IdecMFile* rec);
	ubigint insertNewRec(IdecMFile** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const ubigint refIdecCFile = 0, const uint refIxVTbl = 0, const ubigint refUref = 0, const string osrefKContent = "", const uint Archived = 0, const string Filename = "", const string Archivename = "", const string srefKMimetype = "", const usmallint Size = 0, const string Comment = "");
	ubigint appendNewRecToRst(ListIdecMFile& rst, IdecMFile** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const ubigint refIdecCFile = 0, const uint refIxVTbl = 0, const ubigint refUref = 0, const string osrefKContent = "", const uint Archived = 0, const string Filename = "", const string Archivename = "", const string srefKMimetype = "", const usmallint Size = 0, const string Comment = "");
	virtual void insertRst(ListIdecMFile& rst, bool transact = false);
	virtual void updateRec(IdecMFile* rec);
	virtual void updateRst(ListIdecMFile& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMFile** rec);
	virtual bool loadFnmByRef(ubigint ref, string& Filename);
	virtual ubigint loadRefsByClu(ubigint refIdecCFile, const bool append, vector<ubigint>& refs);
	virtual ubigint loadRstByClu(ubigint refIdecCFile, const bool append, ListIdecMFile& rst);
	virtual ubigint loadRstByRetReu(uint refIxVTbl, ubigint refUref, const bool append, ListIdecMFile& rst);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMFile& rst);
};

/**
  * LiteTblIdecMFile: C++ wrapper for table TblIdecMFile (SQLite database)
  */
class LiteTblIdecMFile : public TblIdecMFile, public LiteTable {

public:
	LiteTblIdecMFile();
	~LiteTblIdecMFile();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadFnmByRef;
	sqlite3_stmt* stmtLoadRefsByClu;
	sqlite3_stmt* stmtLoadRstByClu;
	sqlite3_stmt* stmtLoadRstByRetReu;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMFile** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMFile& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMFile** rec);
	ubigint loadRstByStmt(sqlite3_stmt* stmt, const bool append, ListIdecMFile& rst);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMFile** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMFile& rst);

	void insertRec(IdecMFile* rec);
	void insertRst(ListIdecMFile& rst, bool transact = false);
	void updateRec(IdecMFile* rec);
	void updateRst(ListIdecMFile& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMFile** rec);
	bool loadFnmByRef(ubigint ref, string& Filename);
	ubigint loadRefsByClu(ubigint refIdecCFile, const bool append, vector<ubigint>& refs);
	ubigint loadRstByClu(ubigint refIdecCFile, const bool append, ListIdecMFile& rst);
	ubigint loadRstByRetReu(uint refIxVTbl, ubigint refUref, const bool append, ListIdecMFile& rst);
};

#endif

