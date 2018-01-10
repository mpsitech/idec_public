/**
  * \file IdecQPreselect.cpp
  * Dbs and XML wrapper for table TblIdecQPreselect (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQPreselect.h"

/******************************************************************************
 class IdecQPreselect
 ******************************************************************************/

IdecQPreselect::IdecQPreselect(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
};

void IdecQPreselect::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQPreselect";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
	} else {
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQPreselect
 ******************************************************************************/

ListIdecQPreselect::ListIdecQPreselect() {
};

ListIdecQPreselect::ListIdecQPreselect(
			const ListIdecQPreselect& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQPreselect(*(src.nodes[i]));
};

ListIdecQPreselect::~ListIdecQPreselect() {
	clear();
};

void ListIdecQPreselect::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQPreselect::size() const {
	return(nodes.size());
};

void ListIdecQPreselect::append(
			IdecQPreselect* rec
		) {
	nodes.push_back(rec);
};

ListIdecQPreselect& ListIdecQPreselect::operator=(
			const ListIdecQPreselect& src
		) {
	IdecQPreselect* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQPreselect(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQPreselect::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQPreselect";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQPreselect
 ******************************************************************************/

TblIdecQPreselect::TblIdecQPreselect() {
};

TblIdecQPreselect::~TblIdecQPreselect() {
};

bool TblIdecQPreselect::loadRecBySQL(
			const string& sqlstr
			, IdecQPreselect** rec
		) {
	return false;
};

ubigint TblIdecQPreselect::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQPreselect& rst
		) {
	return 0;
};

void TblIdecQPreselect::insertRec(
			IdecQPreselect* rec
		) {
};

ubigint TblIdecQPreselect::insertNewRec(
			IdecQPreselect** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
		) {
	ubigint retval = 0;
	IdecQPreselect* _rec = NULL;

	_rec = new IdecQPreselect(0, jref, jnum, ref);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQPreselect::appendNewRecToRst(
			ListIdecQPreselect& rst
			, IdecQPreselect** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
		) {
	ubigint retval = 0;
	IdecQPreselect* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQPreselect::insertRst(
			ListIdecQPreselect& rst
		) {
};

void TblIdecQPreselect::updateRec(
			IdecQPreselect* rec
		) {
};

void TblIdecQPreselect::updateRst(
			ListIdecQPreselect& rst
		) {
};

void TblIdecQPreselect::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQPreselect::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQPreselect::loadRecByQref(
			ubigint qref
			, IdecQPreselect** rec
		) {
	return false;
};

ubigint TblIdecQPreselect::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQPreselect& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQPreselect
 ******************************************************************************/

LiteTblIdecQPreselect::LiteTblIdecQPreselect() : TblIdecQPreselect(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQPreselect::~LiteTblIdecQPreselect() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQPreselect::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQPreselect (jref, jnum, ref) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQPreselect SET jref = ?1, jnum = ?2, ref = ?3 WHERE qref = ?4");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQPreselect WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQPreselect WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQPreselect WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQPreselect WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQPreselect::loadRec(
			sqlite3_stmt* stmt
			, IdecQPreselect** rec
		) {
	int res;

	IdecQPreselect* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQPreselect();

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

ubigint LiteTblIdecQPreselect::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQPreselect& rst
		) {
	int res; ubigint numread = 0;

	IdecQPreselect* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQPreselect();

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

bool LiteTblIdecQPreselect::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQPreselect** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQPreselect::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQPreselect& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQPreselect::loadRecBySQL(
			const string& sqlstr
			, IdecQPreselect** rec
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

ubigint LiteTblIdecQPreselect::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQPreselect& rst
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

void LiteTblIdecQPreselect::insertRec(
			IdecQPreselect* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQPreselect / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQPreselect::insertRst(
			ListIdecQPreselect& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQPreselect::updateRec(
			IdecQPreselect* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQPreselect / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQPreselect::updateRst(
			ListIdecQPreselect& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQPreselect::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQPreselect / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQPreselect::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQPreselect / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQPreselect::loadRecByQref(
			ubigint qref
			, IdecQPreselect** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQPreselect::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQPreselect& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

