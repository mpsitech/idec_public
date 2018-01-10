/**
  * \file IdecCFile.h
  * Dbs and XML wrapper for table TblIdecCFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECCFILE_H
#define IDECCFILE_H

#include <sbecore/LiteDbs.h>

/**
  * TblIdecCFile: C++ wrapper for table TblIdecCFile
  */
class TblIdecCFile {

public:
	TblIdecCFile();
	virtual ~TblIdecCFile();

public:
	virtual ubigint getNewRef();
};

/**
  * LiteTblIdecCFile: C++ wrapper for table TblIdecCFile (SQLite database)
  */
class LiteTblIdecCFile : public TblIdecCFile, public LiteTable {

public:
	LiteTblIdecCFile();
	~LiteTblIdecCFile();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtGetNewRef;

public:
	ubigint getNewRef();
};
#endif

