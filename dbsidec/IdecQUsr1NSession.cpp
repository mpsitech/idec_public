/**
  * \file IdecQUsr1NSession.cpp
  * Dbs and XML wrapper for table TblIdecQUsr1NSession (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQUsr1NSession.h"

/******************************************************************************
 class IdecQUsr1NSession
 ******************************************************************************/

IdecQUsr1NSession::IdecQUsr1NSession(
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

void IdecQUsr1NSession::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQUsr1NSession";

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
 class ListIdecQUsr1NSession
 ******************************************************************************/

ListIdecQUsr1NSession::ListIdecQUsr1NSession() {
};

ListIdecQUsr1NSession::ListIdecQUsr1NSession(
			const ListIdecQUsr1NSession& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsr1NSession(*(src.nodes[i]));
};

ListIdecQUsr1NSession::~ListIdecQUsr1NSession() {
	clear();
};

void ListIdecQUsr1NSession::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQUsr1NSession::size() const {
	return(nodes.size());
};

void ListIdecQUsr1NSession::append(
			IdecQUsr1NSession* rec
		) {
	nodes.push_back(rec);
};

ListIdecQUsr1NSession& ListIdecQUsr1NSession::operator=(
			const ListIdecQUsr1NSession& src
		) {
	IdecQUsr1NSession* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQUsr1NSession(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQUsr1NSession::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQUsr1NSession";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQUsr1NSession
 ******************************************************************************/

TblIdecQUsr1NSession::TblIdecQUsr1NSession() {
};

TblIdecQUsr1NSession::~TblIdecQUsr1NSession() {
};

bool TblIdecQUsr1NSession::loadRecBySQL(
			const string& sqlstr
			, IdecQUsr1NSession** rec
		) {
	return false;
};

ubigint TblIdecQUsr1NSession::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsr1NSession& rst
		) {
	return 0;
};

void TblIdecQUsr1NSession::insertRec(
			IdecQUsr1NSession* rec
		) {
};

ubigint TblIdecQUsr1NSession::insertNewRec(
			IdecQUsr1NSession** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQUsr1NSession* _rec = NULL;

	_rec = new IdecQUsr1NSession(0, jref, jnum, ref, stubRef);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQUsr1NSession::appendNewRecToRst(
			ListIdecQUsr1NSession& rst
			, IdecQUsr1NSession** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQUsr1NSession* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, stubRef);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQUsr1NSession::insertRst(
			ListIdecQUsr1NSession& rst
		) {
};

void TblIdecQUsr1NSession::updateRec(
			IdecQUsr1NSession* rec
		) {
};

void TblIdecQUsr1NSession::updateRst(
			ListIdecQUsr1NSession& rst
		) {
};

void TblIdecQUsr1NSession::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQUsr1NSession::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQUsr1NSession::loadRecByQref(
			ubigint qref
			, IdecQUsr1NSession** rec
		) {
	return false;
};

ubigint TblIdecQUsr1NSession::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsr1NSession& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQUsr1NSession
 ******************************************************************************/

LiteTblIdecQUsr1NSession::LiteTblIdecQUsr1NSession() : TblIdecQUsr1NSession(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQUsr1NSession::~LiteTblIdecQUsr1NSession() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQUsr1NSession::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQUsr1NSession (jref, jnum, ref) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQUsr1NSession SET jref = ?1, jnum = ?2, ref = ?3 WHERE qref = ?4");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQUsr1NSession WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQUsr1NSession WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQUsr1NSession WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQUsr1NSession WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQUsr1NSession::loadRec(
			sqlite3_stmt* stmt
			, IdecQUsr1NSession** rec
		) {
	int res;

	IdecQUsr1NSession* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQUsr1NSession();

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

ubigint LiteTblIdecQUsr1NSession::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsr1NSession& rst
		) {
	int res; ubigint numread = 0;

	IdecQUsr1NSession* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQUsr1NSession();

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

bool LiteTblIdecQUsr1NSession::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQUsr1NSession** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQUsr1NSession::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsr1NSession& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQUsr1NSession::loadRecBySQL(
			const string& sqlstr
			, IdecQUsr1NSession** rec
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

ubigint LiteTblIdecQUsr1NSession::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsr1NSession& rst
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

void LiteTblIdecQUsr1NSession::insertRec(
			IdecQUsr1NSession* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsr1NSession / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQUsr1NSession::insertRst(
			ListIdecQUsr1NSession& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQUsr1NSession::updateRec(
			IdecQUsr1NSession* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsr1NSession / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQUsr1NSession::updateRst(
			ListIdecQUsr1NSession& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQUsr1NSession::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsr1NSession / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQUsr1NSession::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsr1NSession / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQUsr1NSession::loadRecByQref(
			ubigint qref
			, IdecQUsr1NSession** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQUsr1NSession::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsr1NSession& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

