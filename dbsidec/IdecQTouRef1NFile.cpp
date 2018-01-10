/**
  * \file IdecQTouRef1NFile.cpp
  * Dbs and XML wrapper for table TblIdecQTouRef1NFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQTouRef1NFile.h"

/******************************************************************************
 class IdecQTouRef1NFile
 ******************************************************************************/

IdecQTouRef1NFile::IdecQTouRef1NFile(
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

void IdecQTouRef1NFile::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQTouRef1NFile";

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
 class ListIdecQTouRef1NFile
 ******************************************************************************/

ListIdecQTouRef1NFile::ListIdecQTouRef1NFile() {
};

ListIdecQTouRef1NFile::ListIdecQTouRef1NFile(
			const ListIdecQTouRef1NFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQTouRef1NFile(*(src.nodes[i]));
};

ListIdecQTouRef1NFile::~ListIdecQTouRef1NFile() {
	clear();
};

void ListIdecQTouRef1NFile::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQTouRef1NFile::size() const {
	return(nodes.size());
};

void ListIdecQTouRef1NFile::append(
			IdecQTouRef1NFile* rec
		) {
	nodes.push_back(rec);
};

ListIdecQTouRef1NFile& ListIdecQTouRef1NFile::operator=(
			const ListIdecQTouRef1NFile& src
		) {
	IdecQTouRef1NFile* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQTouRef1NFile(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQTouRef1NFile::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQTouRef1NFile";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQTouRef1NFile
 ******************************************************************************/

TblIdecQTouRef1NFile::TblIdecQTouRef1NFile() {
};

TblIdecQTouRef1NFile::~TblIdecQTouRef1NFile() {
};

bool TblIdecQTouRef1NFile::loadRecBySQL(
			const string& sqlstr
			, IdecQTouRef1NFile** rec
		) {
	return false;
};

ubigint TblIdecQTouRef1NFile::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQTouRef1NFile& rst
		) {
	return 0;
};

void TblIdecQTouRef1NFile::insertRec(
			IdecQTouRef1NFile* rec
		) {
};

ubigint TblIdecQTouRef1NFile::insertNewRec(
			IdecQTouRef1NFile** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQTouRef1NFile* _rec = NULL;

	_rec = new IdecQTouRef1NFile(0, jref, jnum, ref, stubRef);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQTouRef1NFile::appendNewRecToRst(
			ListIdecQTouRef1NFile& rst
			, IdecQTouRef1NFile** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQTouRef1NFile* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, stubRef);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQTouRef1NFile::insertRst(
			ListIdecQTouRef1NFile& rst
		) {
};

void TblIdecQTouRef1NFile::updateRec(
			IdecQTouRef1NFile* rec
		) {
};

void TblIdecQTouRef1NFile::updateRst(
			ListIdecQTouRef1NFile& rst
		) {
};

void TblIdecQTouRef1NFile::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQTouRef1NFile::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQTouRef1NFile::loadRecByQref(
			ubigint qref
			, IdecQTouRef1NFile** rec
		) {
	return false;
};

ubigint TblIdecQTouRef1NFile::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQTouRef1NFile& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQTouRef1NFile
 ******************************************************************************/

LiteTblIdecQTouRef1NFile::LiteTblIdecQTouRef1NFile() : TblIdecQTouRef1NFile(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQTouRef1NFile::~LiteTblIdecQTouRef1NFile() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQTouRef1NFile::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQTouRef1NFile (jref, jnum, ref) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQTouRef1NFile SET jref = ?1, jnum = ?2, ref = ?3 WHERE qref = ?4");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQTouRef1NFile WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQTouRef1NFile WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQTouRef1NFile WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQTouRef1NFile WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQTouRef1NFile::loadRec(
			sqlite3_stmt* stmt
			, IdecQTouRef1NFile** rec
		) {
	int res;

	IdecQTouRef1NFile* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQTouRef1NFile();

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

ubigint LiteTblIdecQTouRef1NFile::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQTouRef1NFile& rst
		) {
	int res; ubigint numread = 0;

	IdecQTouRef1NFile* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQTouRef1NFile();

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

bool LiteTblIdecQTouRef1NFile::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQTouRef1NFile** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQTouRef1NFile::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQTouRef1NFile& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQTouRef1NFile::loadRecBySQL(
			const string& sqlstr
			, IdecQTouRef1NFile** rec
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

ubigint LiteTblIdecQTouRef1NFile::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQTouRef1NFile& rst
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

void LiteTblIdecQTouRef1NFile::insertRec(
			IdecQTouRef1NFile* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouRef1NFile / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQTouRef1NFile::insertRst(
			ListIdecQTouRef1NFile& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQTouRef1NFile::updateRec(
			IdecQTouRef1NFile* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouRef1NFile / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQTouRef1NFile::updateRst(
			ListIdecQTouRef1NFile& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQTouRef1NFile::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouRef1NFile / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQTouRef1NFile::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouRef1NFile / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQTouRef1NFile::loadRecByQref(
			ubigint qref
			, IdecQTouRef1NFile** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQTouRef1NFile::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQTouRef1NFile& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

