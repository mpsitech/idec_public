/**
  * \file IdecCFile.cpp
  * Dbs and XML wrapper for table TblIdecCFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecCFile.h"

/******************************************************************************
 class TblIdecCFile
 ******************************************************************************/

TblIdecCFile::TblIdecCFile() {
};

TblIdecCFile::~TblIdecCFile() {
};

ubigint TblIdecCFile::getNewRef() {
	return 0;
};

/******************************************************************************
 class LiteTblIdecCFile
 ******************************************************************************/

LiteTblIdecCFile::LiteTblIdecCFile() : TblIdecCFile(), LiteTable() {
	stmtGetNewRef = NULL;
};

LiteTblIdecCFile::~LiteTblIdecCFile() {
	if (stmtGetNewRef) sqlite3_finalize(stmtGetNewRef);
};

void LiteTblIdecCFile::initStatements() {
	stmtGetNewRef = createStatement("INSERT INTO TblIdecCFile (void) VALUES (0)");
};

ubigint LiteTblIdecCFile::getNewRef() {
	if (sqlite3_step(stmtGetNewRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecCFile / stmtGetNewRef)\n");
	return sqlite3_last_insert_rowid(dbs);
};

