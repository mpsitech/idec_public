/**
  * \file IdecQUsrList.cpp
  * Dbs and XML wrapper for table TblIdecQUsrList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQUsrList.h"

/******************************************************************************
 class IdecQUsrList
 ******************************************************************************/

IdecQUsrList::IdecQUsrList(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const ubigint refIdecMPerson
			, const string stubRefIdecMPerson
			, const string sref
			, const ubigint refIdecMUsergroup
			, const string stubRefIdecMUsergroup
			, const uint ixVState
			, const string srefIxVState
			, const string titIxVState
			, const uint ixIdecVLocale
			, const string srefIxIdecVLocale
			, const string titIxIdecVLocale
			, const uint ixIdecVUserlevel
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->refIdecMPerson = refIdecMPerson;
	this->stubRefIdecMPerson = stubRefIdecMPerson;
	this->sref = sref;
	this->refIdecMUsergroup = refIdecMUsergroup;
	this->stubRefIdecMUsergroup = stubRefIdecMUsergroup;
	this->ixVState = ixVState;
	this->srefIxVState = srefIxVState;
	this->titIxVState = titIxVState;
	this->ixIdecVLocale = ixIdecVLocale;
	this->srefIxIdecVLocale = srefIxIdecVLocale;
	this->titIxIdecVLocale = titIxIdecVLocale;
	this->ixIdecVUserlevel = ixIdecVUserlevel;
	this->srefIxIdecVUserlevel = srefIxIdecVUserlevel;
	this->titIxIdecVUserlevel = titIxIdecVUserlevel;
};

void IdecQUsrList::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQUsrList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "prs", stubRefIdecMPerson);
		writeString(wr, "srf", sref);
		writeString(wr, "usg", stubRefIdecMUsergroup);
		writeString(wr, "ste", srefIxVState);
		writeString(wr, "ste2", titIxVState);
		writeString(wr, "lcl", srefIxIdecVLocale);
		writeString(wr, "lcl2", titIxIdecVLocale);
		writeString(wr, "ulv", srefIxIdecVUserlevel);
		writeString(wr, "ulv2", titIxIdecVUserlevel);
	} else {
		writeString(wr, "stubRefIdecMPerson", stubRefIdecMPerson);
		writeString(wr, "sref", sref);
		writeString(wr, "stubRefIdecMUsergroup", stubRefIdecMUsergroup);
		writeString(wr, "srefIxVState", srefIxVState);
		writeString(wr, "titIxVState", titIxVState);
		writeString(wr, "srefIxIdecVLocale", srefIxIdecVLocale);
		writeString(wr, "titIxIdecVLocale", titIxIdecVLocale);
		writeString(wr, "srefIxIdecVUserlevel", srefIxIdecVUserlevel);
		writeString(wr, "titIxIdecVUserlevel", titIxIdecVUserlevel);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQUsrList
 ******************************************************************************/

ListIdecQUsrList::ListIdecQUsrList() {
};

ListIdecQUsrList::ListIdecQUsrList(
			const ListIdecQUsrList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrList(*(src.nodes[i]));
};

ListIdecQUsrList::~ListIdecQUsrList() {
	clear();
};

void ListIdecQUsrList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQUsrList::size() const {
	return(nodes.size());
};

void ListIdecQUsrList::append(
			IdecQUsrList* rec
		) {
	nodes.push_back(rec);
};

ListIdecQUsrList& ListIdecQUsrList::operator=(
			const ListIdecQUsrList& src
		) {
	IdecQUsrList* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQUsrList(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQUsrList::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQUsrList";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQUsrList
 ******************************************************************************/

TblIdecQUsrList::TblIdecQUsrList() {
};

TblIdecQUsrList::~TblIdecQUsrList() {
};

bool TblIdecQUsrList::loadRecBySQL(
			const string& sqlstr
			, IdecQUsrList** rec
		) {
	return false;
};

ubigint TblIdecQUsrList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsrList& rst
		) {
	return 0;
};

void TblIdecQUsrList::insertRec(
			IdecQUsrList* rec
		) {
};

ubigint TblIdecQUsrList::insertNewRec(
			IdecQUsrList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const ubigint refIdecMPerson
			, const string stubRefIdecMPerson
			, const string sref
			, const ubigint refIdecMUsergroup
			, const string stubRefIdecMUsergroup
			, const uint ixVState
			, const string srefIxVState
			, const string titIxVState
			, const uint ixIdecVLocale
			, const string srefIxIdecVLocale
			, const string titIxIdecVLocale
			, const uint ixIdecVUserlevel
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	ubigint retval = 0;
	IdecQUsrList* _rec = NULL;

	_rec = new IdecQUsrList(0, jref, jnum, ref, refIdecMPerson, stubRefIdecMPerson, sref, refIdecMUsergroup, stubRefIdecMUsergroup, ixVState, srefIxVState, titIxVState, ixIdecVLocale, srefIxIdecVLocale, titIxIdecVLocale, ixIdecVUserlevel, srefIxIdecVUserlevel, titIxIdecVUserlevel);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQUsrList::appendNewRecToRst(
			ListIdecQUsrList& rst
			, IdecQUsrList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const ubigint refIdecMPerson
			, const string stubRefIdecMPerson
			, const string sref
			, const ubigint refIdecMUsergroup
			, const string stubRefIdecMUsergroup
			, const uint ixVState
			, const string srefIxVState
			, const string titIxVState
			, const uint ixIdecVLocale
			, const string srefIxIdecVLocale
			, const string titIxIdecVLocale
			, const uint ixIdecVUserlevel
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	ubigint retval = 0;
	IdecQUsrList* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, refIdecMPerson, stubRefIdecMPerson, sref, refIdecMUsergroup, stubRefIdecMUsergroup, ixVState, srefIxVState, titIxVState, ixIdecVLocale, srefIxIdecVLocale, titIxIdecVLocale, ixIdecVUserlevel, srefIxIdecVUserlevel, titIxIdecVUserlevel);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQUsrList::insertRst(
			ListIdecQUsrList& rst
		) {
};

void TblIdecQUsrList::updateRec(
			IdecQUsrList* rec
		) {
};

void TblIdecQUsrList::updateRst(
			ListIdecQUsrList& rst
		) {
};

void TblIdecQUsrList::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQUsrList::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQUsrList::loadRecByQref(
			ubigint qref
			, IdecQUsrList** rec
		) {
	return false;
};

ubigint TblIdecQUsrList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsrList& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQUsrList
 ******************************************************************************/

LiteTblIdecQUsrList::LiteTblIdecQUsrList() : TblIdecQUsrList(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQUsrList::~LiteTblIdecQUsrList() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQUsrList::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQUsrList (jref, jnum, ref, refIdecMPerson, sref, refIdecMUsergroup, ixVState, ixIdecVLocale, ixIdecVUserlevel) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQUsrList SET jref = ?1, jnum = ?2, ref = ?3, refIdecMPerson = ?4, sref = ?5, refIdecMUsergroup = ?6, ixVState = ?7, ixIdecVLocale = ?8, ixIdecVUserlevel = ?9 WHERE qref = ?10");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQUsrList WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQUsrList WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref, refIdecMPerson, sref, refIdecMUsergroup, ixVState, ixIdecVLocale, ixIdecVUserlevel FROM TblIdecQUsrList WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref, refIdecMPerson, sref, refIdecMUsergroup, ixVState, ixIdecVLocale, ixIdecVUserlevel FROM TblIdecQUsrList WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQUsrList::loadRec(
			sqlite3_stmt* stmt
			, IdecQUsrList** rec
		) {
	int res;

	IdecQUsrList* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQUsrList();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);
		_rec->refIdecMPerson = sqlite3_column_int64(stmt, 4);
		_rec->sref.assign((const char*) sqlite3_column_text(stmt, 5));
		_rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 6);
		_rec->ixVState = sqlite3_column_int(stmt, 7);
		_rec->ixIdecVLocale = sqlite3_column_int(stmt, 8);
		_rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 9);

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

ubigint LiteTblIdecQUsrList::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsrList& rst
		) {
	int res; ubigint numread = 0;

	IdecQUsrList* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQUsrList();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);
		rec->refIdecMPerson = sqlite3_column_int64(stmt, 4);
		rec->sref.assign((const char*) sqlite3_column_text(stmt, 5));
		rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 6);
		rec->ixVState = sqlite3_column_int(stmt, 7);
		rec->ixIdecVLocale = sqlite3_column_int(stmt, 8);
		rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 9);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQUsrList::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQUsrList** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQUsrList::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQUsrList& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQUsrList::loadRecBySQL(
			const string& sqlstr
			, IdecQUsrList** rec
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

ubigint LiteTblIdecQUsrList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQUsrList& rst
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

void LiteTblIdecQUsrList::insertRec(
			IdecQUsrList* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);
	sqlite3_bind_int64(stmtInsertRec, 4, rec->refIdecMPerson);
	sqlite3_bind_text(stmtInsertRec, 5, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 6, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtInsertRec, 7, rec->ixVState);
	sqlite3_bind_int(stmtInsertRec, 8, rec->ixIdecVLocale);
	sqlite3_bind_int(stmtInsertRec, 9, rec->ixIdecVUserlevel);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrList / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQUsrList::insertRst(
			ListIdecQUsrList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQUsrList::updateRec(
			IdecQUsrList* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->refIdecMPerson);
	sqlite3_bind_text(stmtUpdateRec, 5, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtUpdateRec, 7, rec->ixVState);
	sqlite3_bind_int(stmtUpdateRec, 8, rec->ixIdecVLocale);
	sqlite3_bind_int(stmtUpdateRec, 9, rec->ixIdecVUserlevel);
	sqlite3_bind_int64(stmtUpdateRec, 10, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrList / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQUsrList::updateRst(
			ListIdecQUsrList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQUsrList::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrList / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQUsrList::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQUsrList / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQUsrList::loadRecByQref(
			ubigint qref
			, IdecQUsrList** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQUsrList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQUsrList& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

