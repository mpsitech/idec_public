/**
  * \file IdecQUsgMNUser.cpp
  * Dbs and XML wrapper for table TblIdecQUsgMNUser (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQUsgMNUser.h"

/******************************************************************************
 class IdecQUsgMNUser
 ******************************************************************************/

IdecQUsgMNUser::IdecQUsgMNUser(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint mref
			, const string stubMref
			, const ubigint ref
			, const uint ixIdecVUserlevel
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->mref = mref;
	this->stubMref = stubMref;
	this->ref = ref;
	this->ixIdecVUserlevel = ixIdecVUserlevel;
	this->srefIxIdecVUserlevel = srefIxIdecVUserlevel;
	this->titIxIdecVUserlevel = titIxIdecVUserlevel;
};

void IdecQUsgMNUser::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQUsgMNUser";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "mref", stubMref);
		writeString(wr, "ulv", srefIxIdecVUserlevel);
		writeString(wr, "ulv2", titIxIdecVUserlevel);
	} else {
		writeString(wr, "stubMref", stubMref);
		writeString(wr, "srefIxIdecVUserlevel", srefIxIdecVUserlevel);
		writeString(wr, "titIxIdecVUserlevel", titIxIdecVUserlevel);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQUsgMNUser
 ******************************************************************************/

ListIdecQUsgMNUser::ListIdecQUsgMNUser() {
};

ListIdecQUsgMNUser::ListIdecQUsgMNUser(
			const ListIdecQUsgMNUser& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgMNUser(*(src.nodes[i]));
};

ListIdecQUsgMNUser::~ListIdecQUsgMNUser() {
	clear();
};

void ListIdecQUsgMNUser::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQUsgMNUser::size() const {
	return(nodes.size());
};

void ListIdecQUsgMNUser::append(
			IdecQUsgMNUser* rec
		) {
	nodes.push_back(rec);
};

ListIdecQUsgMNUser& ListIdecQUsgMNUser::operator=(
			const ListIdecQUsgMNUser& src
		) {
	IdecQUsgMNUser* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQUsgMNUser(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQUsgMNUser::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQUsgMNUser";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQUsgMNUser
 ******************************************************************************/

TblIdecQUsgMNUser::TblIdecQUsgMNUser() {
};

TblIdecQUsgMNUser::~TblIdecQUsgMNUser() {
};

bool TblIdecQUsgMNUser::loadRecBySQL(
			const string& sqlstr
			, IdecQUsgMNUser** rec
		) {
	return false;
};

ubigint TblIdecQUsgMNUser::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsgMNUser& rst
		) {
	return 0;
};

void TblIdecQUsgMNUser::insertRec(
			IdecQUsgMNUser* rec
		) {
};

ubigint TblIdecQUsgMNUser::insertNewRec(
			IdecQUsgMNUser** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint mref
			, const string stubMref
			, const ubigint ref
			, const uint ixIdecVUserlevel
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	ubigint retval = 0;
	IdecQUsgMNUser* _rec = NULL;

	_rec = new IdecQUsgMNUser(0, jref, jnum, mref, stubMref, ref, ixIdecVUserlevel, srefIxIdecVUserlevel, titIxIdecVUserlevel);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQUsgMNUser::appendNewRecToRst(
			ListIdecQUsgMNUser& rst
			, IdecQUsgMNUser** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint mref
			, const string stubMref
			, const ubigint ref
			, const uint ixIdecVUserlevel
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	ubigint retval = 0;
	IdecQUsgMNUser* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, mref, stubMref, ref, ixIdecVUserlevel, srefIxIdecVUserlevel, titIxIdecVUserlevel);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQUsgMNUser::insertRst(
			ListIdecQUsgMNUser& rst
		) {
};

void TblIdecQUsgMNUser::updateRec(
			IdecQUsgMNUser* rec
		) {
};

void TblIdecQUsgMNUser::updateRst(
			ListIdecQUsgMNUser& rst
		) {
};

void TblIdecQUsgMNUser::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQUsgMNUser::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQUsgMNUser::loadRecByQref(
			ubigint qref
			, IdecQUsgMNUser** rec
		) {
	return false;
};

ubigint TblIdecQUsgMNUser::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsgMNUser& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQUsgMNUser
 ******************************************************************************/

LiteTblIdecQUsgMNUser::LiteTblIdecQUsgMNUser() : TblIdecQUsgMNUser(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQUsgMNUser::~LiteTblIdecQUsgMNUser() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQUsgMNUser::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQUsgMNUser (jref, jnum, mref, ref, ixIdecVUserlevel) VALUES (?1,?2,?3,?4,?5)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQUsgMNUser SET jref = ?1, jnum = ?2, mref = ?3, ref = ?4, ixIdecVUserlevel = ?5 WHERE qref = ?6");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQUsgMNUser WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQUsgMNUser WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, mref, ref, ixIdecVUserlevel FROM TblIdecQUsgMNUser WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, mref, ref, ixIdecVUserlevel FROM TblIdecQUsgMNUser WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQUsgMNUser::loadRec(
			sqlite3_stmt* stmt
			, IdecQUsgMNUser** rec
		) {
	int res;

	IdecQUsgMNUser* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQUsgMNUser();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->mref = sqlite3_column_int64(stmt, 3);
		_rec->ref = sqlite3_column_int64(stmt, 4);
		_rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 5);

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

ubigint LiteTblIdecQUsgMNUser::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsgMNUser& rst
		) {
	int res; ubigint numread = 0;

	IdecQUsgMNUser* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQUsgMNUser();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->mref = sqlite3_column_int64(stmt, 3);
		rec->ref = sqlite3_column_int64(stmt, 4);
		rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 5);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQUsgMNUser::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQUsgMNUser** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQUsgMNUser::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsgMNUser& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQUsgMNUser::loadRecBySQL(
			const string& sqlstr
			, IdecQUsgMNUser** rec
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

ubigint LiteTblIdecQUsgMNUser::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsgMNUser& rst
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

void LiteTblIdecQUsgMNUser::insertRec(
			IdecQUsgMNUser* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->mref);
	sqlite3_bind_int64(stmtInsertRec, 4, rec->ref);
	sqlite3_bind_int(stmtInsertRec, 5, rec->ixIdecVUserlevel);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgMNUser / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQUsgMNUser::insertRst(
			ListIdecQUsgMNUser& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQUsgMNUser::updateRec(
			IdecQUsgMNUser* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->mref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->ixIdecVUserlevel);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgMNUser / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQUsgMNUser::updateRst(
			ListIdecQUsgMNUser& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQUsgMNUser::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgMNUser / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQUsgMNUser::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsgMNUser / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQUsgMNUser::loadRecByQref(
			ubigint qref
			, IdecQUsgMNUser** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQUsgMNUser::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsgMNUser& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

