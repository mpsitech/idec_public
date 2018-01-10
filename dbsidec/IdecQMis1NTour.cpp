/**
  * \file IdecQMis1NTour.cpp
  * Dbs and XML wrapper for table TblIdecQMis1NTour (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQMis1NTour.h"

/******************************************************************************
 class IdecQMis1NTour
 ******************************************************************************/

IdecQMis1NTour::IdecQMis1NTour(
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

void IdecQMis1NTour::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQMis1NTour";

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
 class ListIdecQMis1NTour
 ******************************************************************************/

ListIdecQMis1NTour::ListIdecQMis1NTour() {
};

ListIdecQMis1NTour::ListIdecQMis1NTour(
			const ListIdecQMis1NTour& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMis1NTour(*(src.nodes[i]));
};

ListIdecQMis1NTour::~ListIdecQMis1NTour() {
	clear();
};

void ListIdecQMis1NTour::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQMis1NTour::size() const {
	return(nodes.size());
};

void ListIdecQMis1NTour::append(
			IdecQMis1NTour* rec
		) {
	nodes.push_back(rec);
};

ListIdecQMis1NTour& ListIdecQMis1NTour::operator=(
			const ListIdecQMis1NTour& src
		) {
	IdecQMis1NTour* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQMis1NTour(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQMis1NTour::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQMis1NTour";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQMis1NTour
 ******************************************************************************/

TblIdecQMis1NTour::TblIdecQMis1NTour() {
};

TblIdecQMis1NTour::~TblIdecQMis1NTour() {
};

bool TblIdecQMis1NTour::loadRecBySQL(
			const string& sqlstr
			, IdecQMis1NTour** rec
		) {
	return false;
};

ubigint TblIdecQMis1NTour::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQMis1NTour& rst
		) {
	return 0;
};

void TblIdecQMis1NTour::insertRec(
			IdecQMis1NTour* rec
		) {
};

ubigint TblIdecQMis1NTour::insertNewRec(
			IdecQMis1NTour** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQMis1NTour* _rec = NULL;

	_rec = new IdecQMis1NTour(0, jref, jnum, ref, stubRef);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQMis1NTour::appendNewRecToRst(
			ListIdecQMis1NTour& rst
			, IdecQMis1NTour** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string stubRef
		) {
	ubigint retval = 0;
	IdecQMis1NTour* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, stubRef);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQMis1NTour::insertRst(
			ListIdecQMis1NTour& rst
		) {
};

void TblIdecQMis1NTour::updateRec(
			IdecQMis1NTour* rec
		) {
};

void TblIdecQMis1NTour::updateRst(
			ListIdecQMis1NTour& rst
		) {
};

void TblIdecQMis1NTour::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQMis1NTour::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQMis1NTour::loadRecByQref(
			ubigint qref
			, IdecQMis1NTour** rec
		) {
	return false;
};

ubigint TblIdecQMis1NTour::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQMis1NTour& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQMis1NTour
 ******************************************************************************/

LiteTblIdecQMis1NTour::LiteTblIdecQMis1NTour() : TblIdecQMis1NTour(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQMis1NTour::~LiteTblIdecQMis1NTour() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQMis1NTour::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQMis1NTour (jref, jnum, ref) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQMis1NTour SET jref = ?1, jnum = ?2, ref = ?3 WHERE qref = ?4");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQMis1NTour WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQMis1NTour WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQMis1NTour WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref FROM TblIdecQMis1NTour WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQMis1NTour::loadRec(
			sqlite3_stmt* stmt
			, IdecQMis1NTour** rec
		) {
	int res;

	IdecQMis1NTour* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQMis1NTour();

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

ubigint LiteTblIdecQMis1NTour::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQMis1NTour& rst
		) {
	int res; ubigint numread = 0;

	IdecQMis1NTour* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQMis1NTour();

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

bool LiteTblIdecQMis1NTour::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQMis1NTour** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQMis1NTour::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQMis1NTour& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQMis1NTour::loadRecBySQL(
			const string& sqlstr
			, IdecQMis1NTour** rec
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

ubigint LiteTblIdecQMis1NTour::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQMis1NTour& rst
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

void LiteTblIdecQMis1NTour::insertRec(
			IdecQMis1NTour* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMis1NTour / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQMis1NTour::insertRst(
			ListIdecQMis1NTour& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQMis1NTour::updateRec(
			IdecQMis1NTour* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMis1NTour / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQMis1NTour::updateRst(
			ListIdecQMis1NTour& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQMis1NTour::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMis1NTour / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQMis1NTour::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMis1NTour / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQMis1NTour::loadRecByQref(
			ubigint qref
			, IdecQMis1NTour** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQMis1NTour::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQMis1NTour& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

