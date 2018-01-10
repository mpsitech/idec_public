/**
  * \file IdecQUsgList.cpp
  * Dbs and XML wrapper for table TblIdecQUsgList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQUsgList.h"

/******************************************************************************
 class IdecQUsgList
 ******************************************************************************/

IdecQUsgList::IdecQUsgList(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string sref
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->sref = sref;
};

void IdecQUsgList::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQUsgList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "srf", sref);
	} else {
		writeString(wr, "sref", sref);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQUsgList
 ******************************************************************************/

ListIdecQUsgList::ListIdecQUsgList() {
};

ListIdecQUsgList::ListIdecQUsgList(
			const ListIdecQUsgList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgList(*(src.nodes[i]));
};

ListIdecQUsgList::~ListIdecQUsgList() {
	clear();
};

void ListIdecQUsgList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQUsgList::size() const {
	return(nodes.size());
};

void ListIdecQUsgList::append(
			IdecQUsgList* rec
		) {
	nodes.push_back(rec);
};

ListIdecQUsgList& ListIdecQUsgList::operator=(
			const ListIdecQUsgList& src
		) {
	IdecQUsgList* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQUsgList(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQUsgList::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQUsgList";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQUsgList
 ******************************************************************************/

TblIdecQUsgList::TblIdecQUsgList() {
};

TblIdecQUsgList::~TblIdecQUsgList() {
};

bool TblIdecQUsgList::loadRecBySQL(
			const string& sqlstr
			, IdecQUsgList** rec
		) {
	return false;
};

ubigint TblIdecQUsgList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsgList& rst
		) {
	return 0;
};

void TblIdecQUsgList::insertRec(
			IdecQUsgList* rec
		) {
};

ubigint TblIdecQUsgList::insertNewRec(
			IdecQUsgList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string sref
		) {
	ubigint retval = 0;
	IdecQUsgList* _rec = NULL;

	_rec = new IdecQUsgList(0, jref, jnum, ref, sref);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQUsgList::appendNewRecToRst(
			ListIdecQUsgList& rst
			, IdecQUsgList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string sref
		) {
	ubigint retval = 0;
	IdecQUsgList* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, sref);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQUsgList::insertRst(
			ListIdecQUsgList& rst
		) {
};

void TblIdecQUsgList::updateRec(
			IdecQUsgList* rec
		) {
};

void TblIdecQUsgList::updateRst(
			ListIdecQUsgList& rst
		) {
};

void TblIdecQUsgList::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQUsgList::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQUsgList::loadRecByQref(
			ubigint qref
			, IdecQUsgList** rec
		) {
	return false;
};

ubigint TblIdecQUsgList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsgList& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQUsgList
 ******************************************************************************/

LiteTblIdecQUsgList::LiteTblIdecQUsgList() : TblIdecQUsgList(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQUsgList::~LiteTblIdecQUsgList() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQUsgList::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQUsgList (jref, jnum, ref, sref) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQUsgList SET jref = ?1, jnum = ?2, ref = ?3, sref = ?4 WHERE qref = ?5");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQUsgList WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQUsgList WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref, sref FROM TblIdecQUsgList WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref, sref FROM TblIdecQUsgList WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQUsgList::loadRec(
			sqlite3_stmt* stmt
			, IdecQUsgList** rec
		) {
	int res;

	IdecQUsgList* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQUsgList();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);
		_rec->sref.assign((const char*) sqlite3_column_text(stmt, 4));

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

ubigint LiteTblIdecQUsgList::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsgList& rst
		) {
	int res; ubigint numread = 0;

	IdecQUsgList* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQUsgList();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);
		rec->sref.assign((const char*) sqlite3_column_text(stmt, 4));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQUsgList::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQUsgList** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQUsgList::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsgList& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQUsgList::loadRecBySQL(
			const string& sqlstr
			, IdecQUsgList** rec
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

ubigint LiteTblIdecQUsgList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsgList& rst
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

void LiteTblIdecQUsgList::insertRec(
			IdecQUsgList* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);
	sqlite3_bind_text(stmtInsertRec, 4, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgList / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQUsgList::insertRst(
			ListIdecQUsgList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQUsgList::updateRec(
			IdecQUsgList* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgList / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQUsgList::updateRst(
			ListIdecQUsgList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQUsgList::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgList / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQUsgList::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgList / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQUsgList::loadRecByQref(
			ubigint qref
			, IdecQUsgList** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQUsgList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsgList& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

