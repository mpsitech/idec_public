/**
  * \file IdecQUsrMNUsergroup.cpp
  * Dbs and XML wrapper for table TblIdecQUsrMNUsergroup (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQUsrMNUsergroup.h"

/******************************************************************************
 class IdecQUsrMNUsergroup
 ******************************************************************************/

IdecQUsrMNUsergroup::IdecQUsrMNUsergroup(
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

void IdecQUsrMNUsergroup::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQUsrMNUsergroup";

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
 class ListIdecQUsrMNUsergroup
 ******************************************************************************/

ListIdecQUsrMNUsergroup::ListIdecQUsrMNUsergroup() {
};

ListIdecQUsrMNUsergroup::ListIdecQUsrMNUsergroup(
			const ListIdecQUsrMNUsergroup& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrMNUsergroup(*(src.nodes[i]));
};

ListIdecQUsrMNUsergroup::~ListIdecQUsrMNUsergroup() {
	clear();
};

void ListIdecQUsrMNUsergroup::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQUsrMNUsergroup::size() const {
	return(nodes.size());
};

void ListIdecQUsrMNUsergroup::append(
			IdecQUsrMNUsergroup* rec
		) {
	nodes.push_back(rec);
};

ListIdecQUsrMNUsergroup& ListIdecQUsrMNUsergroup::operator=(
			const ListIdecQUsrMNUsergroup& src
		) {
	IdecQUsrMNUsergroup* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQUsrMNUsergroup(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQUsrMNUsergroup::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQUsrMNUsergroup";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQUsrMNUsergroup
 ******************************************************************************/

TblIdecQUsrMNUsergroup::TblIdecQUsrMNUsergroup() {
};

TblIdecQUsrMNUsergroup::~TblIdecQUsrMNUsergroup() {
};

bool TblIdecQUsrMNUsergroup::loadRecBySQL(
			const string& sqlstr
			, IdecQUsrMNUsergroup** rec
		) {
	return false;
};

ubigint TblIdecQUsrMNUsergroup::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsrMNUsergroup& rst
		) {
	return 0;
};

void TblIdecQUsrMNUsergroup::insertRec(
			IdecQUsrMNUsergroup* rec
		) {
};

ubigint TblIdecQUsrMNUsergroup::insertNewRec(
			IdecQUsrMNUsergroup** rec
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
	IdecQUsrMNUsergroup* _rec = NULL;

	_rec = new IdecQUsrMNUsergroup(0, jref, jnum, mref, stubMref, ref, ixIdecVUserlevel, srefIxIdecVUserlevel, titIxIdecVUserlevel);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQUsrMNUsergroup::appendNewRecToRst(
			ListIdecQUsrMNUsergroup& rst
			, IdecQUsrMNUsergroup** rec
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
	IdecQUsrMNUsergroup* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, mref, stubMref, ref, ixIdecVUserlevel, srefIxIdecVUserlevel, titIxIdecVUserlevel);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQUsrMNUsergroup::insertRst(
			ListIdecQUsrMNUsergroup& rst
		) {
};

void TblIdecQUsrMNUsergroup::updateRec(
			IdecQUsrMNUsergroup* rec
		) {
};

void TblIdecQUsrMNUsergroup::updateRst(
			ListIdecQUsrMNUsergroup& rst
		) {
};

void TblIdecQUsrMNUsergroup::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQUsrMNUsergroup::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQUsrMNUsergroup::loadRecByQref(
			ubigint qref
			, IdecQUsrMNUsergroup** rec
		) {
	return false;
};

ubigint TblIdecQUsrMNUsergroup::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsrMNUsergroup& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQUsrMNUsergroup
 ******************************************************************************/

LiteTblIdecQUsrMNUsergroup::LiteTblIdecQUsrMNUsergroup() : TblIdecQUsrMNUsergroup(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQUsrMNUsergroup::~LiteTblIdecQUsrMNUsergroup() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQUsrMNUsergroup::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQUsrMNUsergroup (jref, jnum, mref, ref, ixIdecVUserlevel) VALUES (?1,?2,?3,?4,?5)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQUsrMNUsergroup SET jref = ?1, jnum = ?2, mref = ?3, ref = ?4, ixIdecVUserlevel = ?5 WHERE qref = ?6");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQUsrMNUsergroup WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQUsrMNUsergroup WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, mref, ref, ixIdecVUserlevel FROM TblIdecQUsrMNUsergroup WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, mref, ref, ixIdecVUserlevel FROM TblIdecQUsrMNUsergroup WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQUsrMNUsergroup::loadRec(
			sqlite3_stmt* stmt
			, IdecQUsrMNUsergroup** rec
		) {
	int res;

	IdecQUsrMNUsergroup* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQUsrMNUsergroup();

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

ubigint LiteTblIdecQUsrMNUsergroup::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsrMNUsergroup& rst
		) {
	int res; ubigint numread = 0;

	IdecQUsrMNUsergroup* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQUsrMNUsergroup();

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

bool LiteTblIdecQUsrMNUsergroup::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQUsrMNUsergroup** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQUsrMNUsergroup::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsrMNUsergroup& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQUsrMNUsergroup::loadRecBySQL(
			const string& sqlstr
			, IdecQUsrMNUsergroup** rec
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

ubigint LiteTblIdecQUsrMNUsergroup::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsrMNUsergroup& rst
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

void LiteTblIdecQUsrMNUsergroup::insertRec(
			IdecQUsrMNUsergroup* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->mref);
	sqlite3_bind_int64(stmtInsertRec, 4, rec->ref);
	sqlite3_bind_int(stmtInsertRec, 5, rec->ixIdecVUserlevel);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrMNUsergroup / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQUsrMNUsergroup::insertRst(
			ListIdecQUsrMNUsergroup& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQUsrMNUsergroup::updateRec(
			IdecQUsrMNUsergroup* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->mref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->ixIdecVUserlevel);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrMNUsergroup / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQUsrMNUsergroup::updateRst(
			ListIdecQUsrMNUsergroup& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQUsrMNUsergroup::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrMNUsergroup / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQUsrMNUsergroup::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrMNUsergroup / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQUsrMNUsergroup::loadRecByQref(
			ubigint qref
			, IdecQUsrMNUsergroup** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQUsrMNUsergroup::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsrMNUsergroup& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

