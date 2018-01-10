/**
  * \file IdecQTouList.cpp
  * Dbs and XML wrapper for table TblIdecQTouList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQTouList.h"

/******************************************************************************
 class IdecQTouList
 ******************************************************************************/

IdecQTouList::IdecQTouList(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Title
			, const ubigint refIdecMMission
			, const string stubRefIdecMMission
			, const uint start
			, const string ftmStart
			, const uint stop
			, const string ftmStop
			, const string Area
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->Title = Title;
	this->refIdecMMission = refIdecMMission;
	this->stubRefIdecMMission = stubRefIdecMMission;
	this->start = start;
	this->ftmStart = ftmStart;
	this->stop = stop;
	this->ftmStop = ftmStop;
	this->Area = Area;
};

void IdecQTouList::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQTouList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "tit", Title);
		writeString(wr, "mis", stubRefIdecMMission);
		writeString(wr, "sta", ftmStart);
		writeString(wr, "sto", ftmStop);
		writeString(wr, "are", Area);
	} else {
		writeString(wr, "Title", Title);
		writeString(wr, "stubRefIdecMMission", stubRefIdecMMission);
		writeString(wr, "ftmStart", ftmStart);
		writeString(wr, "ftmStop", ftmStop);
		writeString(wr, "Area", Area);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQTouList
 ******************************************************************************/

ListIdecQTouList::ListIdecQTouList() {
};

ListIdecQTouList::ListIdecQTouList(
			const ListIdecQTouList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQTouList(*(src.nodes[i]));
};

ListIdecQTouList::~ListIdecQTouList() {
	clear();
};

void ListIdecQTouList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQTouList::size() const {
	return(nodes.size());
};

void ListIdecQTouList::append(
			IdecQTouList* rec
		) {
	nodes.push_back(rec);
};

ListIdecQTouList& ListIdecQTouList::operator=(
			const ListIdecQTouList& src
		) {
	IdecQTouList* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQTouList(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQTouList::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQTouList";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQTouList
 ******************************************************************************/

TblIdecQTouList::TblIdecQTouList() {
};

TblIdecQTouList::~TblIdecQTouList() {
};

bool TblIdecQTouList::loadRecBySQL(
			const string& sqlstr
			, IdecQTouList** rec
		) {
	return false;
};

ubigint TblIdecQTouList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQTouList& rst
		) {
	return 0;
};

void TblIdecQTouList::insertRec(
			IdecQTouList* rec
		) {
};

ubigint TblIdecQTouList::insertNewRec(
			IdecQTouList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Title
			, const ubigint refIdecMMission
			, const string stubRefIdecMMission
			, const uint start
			, const string ftmStart
			, const uint stop
			, const string ftmStop
			, const string Area
		) {
	ubigint retval = 0;
	IdecQTouList* _rec = NULL;

	_rec = new IdecQTouList(0, jref, jnum, ref, Title, refIdecMMission, stubRefIdecMMission, start, ftmStart, stop, ftmStop, Area);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQTouList::appendNewRecToRst(
			ListIdecQTouList& rst
			, IdecQTouList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Title
			, const ubigint refIdecMMission
			, const string stubRefIdecMMission
			, const uint start
			, const string ftmStart
			, const uint stop
			, const string ftmStop
			, const string Area
		) {
	ubigint retval = 0;
	IdecQTouList* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, Title, refIdecMMission, stubRefIdecMMission, start, ftmStart, stop, ftmStop, Area);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQTouList::insertRst(
			ListIdecQTouList& rst
		) {
};

void TblIdecQTouList::updateRec(
			IdecQTouList* rec
		) {
};

void TblIdecQTouList::updateRst(
			ListIdecQTouList& rst
		) {
};

void TblIdecQTouList::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQTouList::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQTouList::loadRecByQref(
			ubigint qref
			, IdecQTouList** rec
		) {
	return false;
};

ubigint TblIdecQTouList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQTouList& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQTouList
 ******************************************************************************/

LiteTblIdecQTouList::LiteTblIdecQTouList() : TblIdecQTouList(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQTouList::~LiteTblIdecQTouList() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQTouList::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQTouList (jref, jnum, ref, Title, refIdecMMission, start, stop, Area) VALUES (?1,?2,?3,?4,?5,?6,?7,?8)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQTouList SET jref = ?1, jnum = ?2, ref = ?3, Title = ?4, refIdecMMission = ?5, start = ?6, stop = ?7, Area = ?8 WHERE qref = ?9");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQTouList WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQTouList WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref, Title, refIdecMMission, start, stop, Area FROM TblIdecQTouList WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref, Title, refIdecMMission, start, stop, Area FROM TblIdecQTouList WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQTouList::loadRec(
			sqlite3_stmt* stmt
			, IdecQTouList** rec
		) {
	int res;

	IdecQTouList* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQTouList();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 4));
		_rec->refIdecMMission = sqlite3_column_int64(stmt, 5);
		_rec->start = sqlite3_column_int(stmt, 6);
		_rec->stop = sqlite3_column_int(stmt, 7);
		_rec->Area.assign((const char*) sqlite3_column_text(stmt, 8));

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

ubigint LiteTblIdecQTouList::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQTouList& rst
		) {
	int res; ubigint numread = 0;

	IdecQTouList* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQTouList();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 4));
		rec->refIdecMMission = sqlite3_column_int64(stmt, 5);
		rec->start = sqlite3_column_int(stmt, 6);
		rec->stop = sqlite3_column_int(stmt, 7);
		rec->Area.assign((const char*) sqlite3_column_text(stmt, 8));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQTouList::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQTouList** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQTouList::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQTouList& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQTouList::loadRecBySQL(
			const string& sqlstr
			, IdecQTouList** rec
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

ubigint LiteTblIdecQTouList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQTouList& rst
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

void LiteTblIdecQTouList::insertRec(
			IdecQTouList* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 5, rec->refIdecMMission);
	sqlite3_bind_int(stmtInsertRec, 6, rec->start);
	sqlite3_bind_int(stmtInsertRec, 7, rec->stop);
	sqlite3_bind_text(stmtInsertRec, 8, rec->Area.c_str(), rec->Area.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouList / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQTouList::insertRst(
			ListIdecQTouList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQTouList::updateRec(
			IdecQTouList* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->refIdecMMission);
	sqlite3_bind_int(stmtUpdateRec, 6, rec->start);
	sqlite3_bind_int(stmtUpdateRec, 7, rec->stop);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->Area.c_str(), rec->Area.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 9, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouList / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQTouList::updateRst(
			ListIdecQTouList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQTouList::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouList / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQTouList::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQTouList / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQTouList::loadRecByQref(
			ubigint qref
			, IdecQTouList** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQTouList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQTouList& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

