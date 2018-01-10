/**
  * \file IdecQUsrAAccess.cpp
  * Dbs and XML wrapper for table TblIdecQUsrAAccess (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQUsrAAccess.h"

/******************************************************************************
 class IdecQUsrAAccess
 ******************************************************************************/

IdecQUsrAAccess::IdecQUsrAAccess(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const uint x1IxIdecVCard
			, const string srefX1IxIdecVCard
			, const string titX1IxIdecVCard
			, const uint ixIdecWUiaccess
			, const string srefsIxIdecWUiaccess
			, const string titsIxIdecWUiaccess
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->x1IxIdecVCard = x1IxIdecVCard;
	this->srefX1IxIdecVCard = srefX1IxIdecVCard;
	this->titX1IxIdecVCard = titX1IxIdecVCard;
	this->ixIdecWUiaccess = ixIdecWUiaccess;
	this->srefsIxIdecWUiaccess = srefsIxIdecWUiaccess;
	this->titsIxIdecWUiaccess = titsIxIdecWUiaccess;
};

void IdecQUsrAAccess::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQUsrAAccess";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "crd", srefX1IxIdecVCard);
		writeString(wr, "crd2", titX1IxIdecVCard);
		writeString(wr, "uac", srefsIxIdecWUiaccess);
		writeString(wr, "uac2", titsIxIdecWUiaccess);
	} else {
		writeString(wr, "srefX1IxIdecVCard", srefX1IxIdecVCard);
		writeString(wr, "titX1IxIdecVCard", titX1IxIdecVCard);
		writeString(wr, "srefsIxIdecWUiaccess", srefsIxIdecWUiaccess);
		writeString(wr, "titsIxIdecWUiaccess", titsIxIdecWUiaccess);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQUsrAAccess
 ******************************************************************************/

ListIdecQUsrAAccess::ListIdecQUsrAAccess() {
};

ListIdecQUsrAAccess::ListIdecQUsrAAccess(
			const ListIdecQUsrAAccess& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrAAccess(*(src.nodes[i]));
};

ListIdecQUsrAAccess::~ListIdecQUsrAAccess() {
	clear();
};

void ListIdecQUsrAAccess::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQUsrAAccess::size() const {
	return(nodes.size());
};

void ListIdecQUsrAAccess::append(
			IdecQUsrAAccess* rec
		) {
	nodes.push_back(rec);
};

ListIdecQUsrAAccess& ListIdecQUsrAAccess::operator=(
			const ListIdecQUsrAAccess& src
		) {
	IdecQUsrAAccess* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQUsrAAccess(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQUsrAAccess::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQUsrAAccess";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQUsrAAccess
 ******************************************************************************/

TblIdecQUsrAAccess::TblIdecQUsrAAccess() {
};

TblIdecQUsrAAccess::~TblIdecQUsrAAccess() {
};

bool TblIdecQUsrAAccess::loadRecBySQL(
			const string& sqlstr
			, IdecQUsrAAccess** rec
		) {
	return false;
};

ubigint TblIdecQUsrAAccess::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsrAAccess& rst
		) {
	return 0;
};

void TblIdecQUsrAAccess::insertRec(
			IdecQUsrAAccess* rec
		) {
};

ubigint TblIdecQUsrAAccess::insertNewRec(
			IdecQUsrAAccess** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const uint x1IxIdecVCard
			, const string srefX1IxIdecVCard
			, const string titX1IxIdecVCard
			, const uint ixIdecWUiaccess
			, const string srefsIxIdecWUiaccess
			, const string titsIxIdecWUiaccess
		) {
	ubigint retval = 0;
	IdecQUsrAAccess* _rec = NULL;

	_rec = new IdecQUsrAAccess(0, jref, jnum, ref, x1IxIdecVCard, srefX1IxIdecVCard, titX1IxIdecVCard, ixIdecWUiaccess, srefsIxIdecWUiaccess, titsIxIdecWUiaccess);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQUsrAAccess::appendNewRecToRst(
			ListIdecQUsrAAccess& rst
			, IdecQUsrAAccess** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const uint x1IxIdecVCard
			, const string srefX1IxIdecVCard
			, const string titX1IxIdecVCard
			, const uint ixIdecWUiaccess
			, const string srefsIxIdecWUiaccess
			, const string titsIxIdecWUiaccess
		) {
	ubigint retval = 0;
	IdecQUsrAAccess* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, x1IxIdecVCard, srefX1IxIdecVCard, titX1IxIdecVCard, ixIdecWUiaccess, srefsIxIdecWUiaccess, titsIxIdecWUiaccess);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQUsrAAccess::insertRst(
			ListIdecQUsrAAccess& rst
		) {
};

void TblIdecQUsrAAccess::updateRec(
			IdecQUsrAAccess* rec
		) {
};

void TblIdecQUsrAAccess::updateRst(
			ListIdecQUsrAAccess& rst
		) {
};

void TblIdecQUsrAAccess::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQUsrAAccess::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQUsrAAccess::loadRecByQref(
			ubigint qref
			, IdecQUsrAAccess** rec
		) {
	return false;
};

ubigint TblIdecQUsrAAccess::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsrAAccess& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQUsrAAccess
 ******************************************************************************/

LiteTblIdecQUsrAAccess::LiteTblIdecQUsrAAccess() : TblIdecQUsrAAccess(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQUsrAAccess::~LiteTblIdecQUsrAAccess() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQUsrAAccess::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQUsrAAccess (jref, jnum, ref, x1IxIdecVCard, ixIdecWUiaccess) VALUES (?1,?2,?3,?4,?5)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQUsrAAccess SET jref = ?1, jnum = ?2, ref = ?3, x1IxIdecVCard = ?4, ixIdecWUiaccess = ?5 WHERE qref = ?6");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQUsrAAccess WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQUsrAAccess WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecQUsrAAccess WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecQUsrAAccess WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQUsrAAccess::loadRec(
			sqlite3_stmt* stmt
			, IdecQUsrAAccess** rec
		) {
	int res;

	IdecQUsrAAccess* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQUsrAAccess();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);
		_rec->x1IxIdecVCard = sqlite3_column_int(stmt, 4);
		_rec->ixIdecWUiaccess = sqlite3_column_int(stmt, 5);

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

ubigint LiteTblIdecQUsrAAccess::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsrAAccess& rst
		) {
	int res; ubigint numread = 0;

	IdecQUsrAAccess* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQUsrAAccess();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);
		rec->x1IxIdecVCard = sqlite3_column_int(stmt, 4);
		rec->ixIdecWUiaccess = sqlite3_column_int(stmt, 5);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQUsrAAccess::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQUsrAAccess** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQUsrAAccess::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsrAAccess& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQUsrAAccess::loadRecBySQL(
			const string& sqlstr
			, IdecQUsrAAccess** rec
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

ubigint LiteTblIdecQUsrAAccess::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsrAAccess& rst
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

void LiteTblIdecQUsrAAccess::insertRec(
			IdecQUsrAAccess* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);
	sqlite3_bind_int(stmtInsertRec, 4, rec->x1IxIdecVCard);
	sqlite3_bind_int(stmtInsertRec, 5, rec->ixIdecWUiaccess);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrAAccess / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQUsrAAccess::insertRst(
			ListIdecQUsrAAccess& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQUsrAAccess::updateRec(
			IdecQUsrAAccess* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->x1IxIdecVCard);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->ixIdecWUiaccess);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrAAccess / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQUsrAAccess::updateRst(
			ListIdecQUsrAAccess& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQUsrAAccess::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrAAccess / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQUsrAAccess::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrAAccess / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQUsrAAccess::loadRecByQref(
			ubigint qref
			, IdecQUsrAAccess** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQUsrAAccess::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsrAAccess& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

