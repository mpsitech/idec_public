/**
  * \file IdecQMisRef1NFile.cpp
  * Dbs and XML wrapper for table TblIdecQMisRef1NFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQMisRef1NFile.h"

/******************************************************************************
 class IdecQMisRef1NFile
 ******************************************************************************/

IdecQMisRef1NFile::IdecQMisRef1NFile(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->stubRef = stubRef;
};

void IdecQMisRef1NFile::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQMisRef1NFile";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "ref", stubRef);
	} else {
		writeString(wr, "stubRef", stubRef);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQMisRef1NFile
 ******************************************************************************/

ListIdecQMisRef1NFile::ListIdecQMisRef1NFile() {
};

ListIdecQMisRef1NFile::ListIdecQMisRef1NFile(
			const ListIdecQMisRef1NFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMisRef1NFile(*(src.nodes[i]));
};

ListIdecQMisRef1NFile::~ListIdecQMisRef1NFile() {
	clear();
};

void ListIdecQMisRef1NFile::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQMisRef1NFile::size() const {
	return(nodes.size());
};

void ListIdecQMisRef1NFile::append(
			IdecQMisRef1NFile* rec
		) {
	nodes.push_back(rec);
};

ListIdecQMisRef1NFile& ListIdecQMisRef1NFile::operator=(
			const ListIdecQMisRef1NFile& src
		) {
	IdecQMisRef1NFile* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQMisRef1NFile(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQMisRef1NFile::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQMisRef1NFile";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQMisRef1NFile
 ******************************************************************************/

TblIdecQMisRef1NFile::TblIdecQMisRef1NFile() {
};

TblIdecQMisRef1NFile::~TblIdecQMisRef1NFile() {
};

bool TblIdecQMisRef1NFile::loadRecBySQL(
			const string& sqlstr
			, IdecQMisRef1NFile** rec
		) {
	return false;
};

ubigint TblIdecQMisRef1NFile::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQMisRef1NFile& rst
		) {
	return 0;
};

void TblIdecQMisRef1NFile::insertRec(
			IdecQMisRef1NFile* rec
		) {
};

ubigint TblIdecQMisRef1NFile::insertNewRec(
			IdecQMisRef1NFile** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQMisRef1NFile* _rec = NULL;

	_rec = new IdecQMisRef1NFile(0, jref, jnum, ref, stubRef);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQMisRef1NFile::appendNewRecToRst(
			ListIdecQMisRef1NFile& rst
			, IdecQMisRef1NFile** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQMisRef1NFile* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, stubRef);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQMisRef1NFile::insertRst(
			ListIdecQMisRef1NFile& rst
		) {
};

void TblIdecQMisRef1NFile::updateRec(
			IdecQMisRef1NFile* rec
		) {
};

void TblIdecQMisRef1NFile::updateRst(
			ListIdecQMisRef1NFile& rst
		) {
};

void TblIdecQMisRef1NFile::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQMisRef1NFile::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQMisRef1NFile::loadRecByQref(
			ubigint qref
			, IdecQMisRef1NFile** rec
		) {
	return false;
};

ubigint TblIdecQMisRef1NFile::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQMisRef1NFile& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQMisRef1NFile
 ******************************************************************************/

LiteTblIdecQMisRef1NFile::LiteTblIdecQMisRef1NFile() : TblIdecQMisRef1NFile(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQMisRef1NFile::~LiteTblIdecQMisRef1NFile() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQMisRef1NFile::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQMisRef1NFile (jref, jnum, ref) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQMisRef1NFile SET jref = ?1, jnum = ?2, ref = ?3 WHERE qref = ?4");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQMisRef1NFile WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQMisRef1NFile WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQMisRef1NFile WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQMisRef1NFile WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQMisRef1NFile::loadRec(
			sqlite3_stmt* stmt
			, IdecQMisRef1NFile** rec
		) {
	int res;

	IdecQMisRef1NFile* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQMisRef1NFile();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);

		res = sqlite3_step(stmt);
		if (res == SQLITE_DONE) {
			*rec = _rec;
			retval = true;
		} else {
			delete _rec;
		};
	};

	return retval;
};

ubigint LiteTblIdecQMisRef1NFile::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQMisRef1NFile& rst
		) {
	int res; ubigint numread = 0;

	IdecQMisRef1NFile* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQMisRef1NFile();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQMisRef1NFile::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQMisRef1NFile** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQMisRef1NFile::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQMisRef1NFile& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQMisRef1NFile::loadRecBySQL(
			const string& sqlstr
			, IdecQMisRef1NFile** rec
		) {
	int res;
	sqlite3_stmt* stmt;

	bool retval = false;

	res = sqlite3_prepare_v2(dbs, sqlstr.c_str(), sqlstr.length()+1, &stmt, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	retval = loadRec(stmt, rec);

	sqlite3_finalize(stmt);

	return retval;
};

ubigint LiteTblIdecQMisRef1NFile::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQMisRef1NFile& rst
		) {
	int res;
	sqlite3_stmt* stmt;

	ubigint retval = 0;

	res = sqlite3_prepare_v2(dbs, sqlstr.c_str(), sqlstr.length()+1, &stmt, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	retval = loadRst(stmt, append, rst);

	sqlite3_finalize(stmt);

	return retval;
};

void LiteTblIdecQMisRef1NFile::insertRec(
			IdecQMisRef1NFile* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisRef1NFile / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQMisRef1NFile::insertRst(
			ListIdecQMisRef1NFile& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQMisRef1NFile::updateRec(
			IdecQMisRef1NFile* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisRef1NFile / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQMisRef1NFile::updateRst(
			ListIdecQMisRef1NFile& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQMisRef1NFile::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisRef1NFile / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQMisRef1NFile::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisRef1NFile / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQMisRef1NFile::loadRecByQref(
			ubigint qref
			, IdecQMisRef1NFile** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQMisRef1NFile::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQMisRef1NFile& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

