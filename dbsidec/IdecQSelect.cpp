/**
  * \file IdecQSelect.cpp
  * Dbs and XML wrapper for table TblIdecQSelect (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQSelect.h"

/******************************************************************************
 class IdecQSelect
 ******************************************************************************/

IdecQSelect::IdecQSelect(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const uint ix
			, const ubigint ref
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ix = ix;
	this->ref = ref;
};

void IdecQSelect::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQSelect";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
	} else {
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQSelect
 ******************************************************************************/

ListIdecQSelect::ListIdecQSelect() {
};

ListIdecQSelect::ListIdecQSelect(
			const ListIdecQSelect& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQSelect(*(src.nodes[i]));
};

ListIdecQSelect::~ListIdecQSelect() {
	clear();
};

void ListIdecQSelect::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQSelect::size() const {
	return(nodes.size());
};

void ListIdecQSelect::append(
			IdecQSelect* rec
		) {
	nodes.push_back(rec);
};

ListIdecQSelect& ListIdecQSelect::operator=(
			const ListIdecQSelect& src
		) {
	IdecQSelect* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQSelect(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQSelect::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQSelect";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQSelect
 ******************************************************************************/

TblIdecQSelect::TblIdecQSelect() {
};

TblIdecQSelect::~TblIdecQSelect() {
};

bool TblIdecQSelect::loadRecBySQL(
			const string& sqlstr
			, IdecQSelect** rec
		) {
	return false;
};

ubigint TblIdecQSelect::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQSelect& rst
		) {
	return 0;
};

void TblIdecQSelect::insertRec(
			IdecQSelect* rec
		) {
};

ubigint TblIdecQSelect::insertNewRec(
			IdecQSelect** rec
			, const ubigint jref
			, const uint jnum
			, const uint ix
			, const ubigint ref
		) {
	ubigint retval = 0;
	IdecQSelect* _rec = NULL;

	_rec = new IdecQSelect(0, jref, jnum, ix, ref);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQSelect::appendNewRecToRst(
			ListIdecQSelect& rst
			, IdecQSelect** rec
			, const ubigint jref
			, const uint jnum
			, const uint ix
			, const ubigint ref
		) {
	ubigint retval = 0;
	IdecQSelect* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ix, ref);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQSelect::insertRst(
			ListIdecQSelect& rst
		) {
};

void TblIdecQSelect::updateRec(
			IdecQSelect* rec
		) {
};

void TblIdecQSelect::updateRst(
			ListIdecQSelect& rst
		) {
};

void TblIdecQSelect::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQSelect::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQSelect::loadRecByQref(
			ubigint qref
			, IdecQSelect** rec
		) {
	return false;
};

ubigint TblIdecQSelect::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQSelect& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQSelect
 ******************************************************************************/

LiteTblIdecQSelect::LiteTblIdecQSelect() : TblIdecQSelect(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQSelect::~LiteTblIdecQSelect() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQSelect::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQSelect (jref, jnum, ix, ref) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQSelect SET jref = ?1, jnum = ?2, ix = ?3, ref = ?4 WHERE qref = ?5");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQSelect WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQSelect WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ix, ref FROM TblIdecQSelect WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ix, ref FROM TblIdecQSelect WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQSelect::loadRec(
			sqlite3_stmt* stmt
			, IdecQSelect** rec
		) {
	int res;

	IdecQSelect* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQSelect();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ix = sqlite3_column_int(stmt, 3);
		_rec->ref = sqlite3_column_int64(stmt, 4);

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

ubigint LiteTblIdecQSelect::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQSelect& rst
		) {
	int res; ubigint numread = 0;

	IdecQSelect* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQSelect();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ix = sqlite3_column_int(stmt, 3);
		rec->ref = sqlite3_column_int64(stmt, 4);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQSelect::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQSelect** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQSelect::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQSelect& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQSelect::loadRecBySQL(
			const string& sqlstr
			, IdecQSelect** rec
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

ubigint LiteTblIdecQSelect::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQSelect& rst
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

void LiteTblIdecQSelect::insertRec(
			IdecQSelect* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int(stmtInsertRec, 3, rec->ix);
	sqlite3_bind_int64(stmtInsertRec, 4, rec->ref);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQSelect / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQSelect::insertRst(
			ListIdecQSelect& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQSelect::updateRec(
			IdecQSelect* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->ix);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQSelect / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQSelect::updateRst(
			ListIdecQSelect& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQSelect::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQSelect / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQSelect::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQSelect / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQSelect::loadRecByQref(
			ubigint qref
			, IdecQSelect** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQSelect::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQSelect& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

