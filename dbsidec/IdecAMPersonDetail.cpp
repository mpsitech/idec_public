/**
  * \file IdecAMPersonDetail.cpp
  * database access for table TblIdecAMPersonDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAMPersonDetail.h"

/******************************************************************************
 class IdecAMPersonDetail
 ******************************************************************************/

IdecAMPersonDetail::IdecAMPersonDetail(
			const ubigint ref
			, const ubigint refIdecMPerson
			, const string x1SrefKType
			, const string Val
		) {

	this->ref = ref;
	this->refIdecMPerson = refIdecMPerson;
	this->x1SrefKType = x1SrefKType;
	this->Val = Val;
};

bool IdecAMPersonDetail::operator==(
			const IdecAMPersonDetail& comp
		) {
	return false;
};

bool IdecAMPersonDetail::operator!=(
			const IdecAMPersonDetail& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAMPersonDetail
 ******************************************************************************/

ListIdecAMPersonDetail::ListIdecAMPersonDetail() {
};

ListIdecAMPersonDetail::ListIdecAMPersonDetail(
			const ListIdecAMPersonDetail& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAMPersonDetail(*(src.nodes[i]));
};

ListIdecAMPersonDetail::~ListIdecAMPersonDetail() {
	clear();
};

void ListIdecAMPersonDetail::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAMPersonDetail::size() const {
	return(nodes.size());
};

void ListIdecAMPersonDetail::append(
			IdecAMPersonDetail* rec
		) {
	nodes.push_back(rec);
};

IdecAMPersonDetail* ListIdecAMPersonDetail::operator[](
			const uint ix
		) {
	IdecAMPersonDetail* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAMPersonDetail& ListIdecAMPersonDetail::operator=(
			const ListIdecAMPersonDetail& src
		) {
	IdecAMPersonDetail* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAMPersonDetail(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAMPersonDetail::operator==(
			const ListIdecAMPersonDetail& comp
		) {
	bool retval;

	retval = (size() == comp.size());

	if (retval) {
		for (unsigned int i=0;i<size();i++) {
			retval = ( *(nodes[i]) == *(comp.nodes[i]) );

			if (!retval) break;
		};
	};

	return retval;
};

bool ListIdecAMPersonDetail::operator!=(
			const ListIdecAMPersonDetail& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAMPersonDetail
 ******************************************************************************/

TblIdecAMPersonDetail::TblIdecAMPersonDetail() {
};

TblIdecAMPersonDetail::~TblIdecAMPersonDetail() {
};

bool TblIdecAMPersonDetail::loadRecBySQL(
			const string& sqlstr
			, IdecAMPersonDetail** rec
		) {
	return false;
};

ubigint TblIdecAMPersonDetail::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAMPersonDetail& rst
		) {
	return 0;
};

void TblIdecAMPersonDetail::insertRec(
			IdecAMPersonDetail* rec
		) {
};

ubigint TblIdecAMPersonDetail::insertNewRec(
			IdecAMPersonDetail** rec
			, const ubigint refIdecMPerson
			, const string x1SrefKType
			, const string Val
		) {
	ubigint retval = 0;
	IdecAMPersonDetail* _rec = NULL;

	_rec = new IdecAMPersonDetail(0, refIdecMPerson, x1SrefKType, Val);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAMPersonDetail::appendNewRecToRst(
			ListIdecAMPersonDetail& rst
			, IdecAMPersonDetail** rec
			, const ubigint refIdecMPerson
			, const string x1SrefKType
			, const string Val
		) {
	ubigint retval = 0;
	IdecAMPersonDetail* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMPerson, x1SrefKType, Val);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAMPersonDetail::insertRst(
			ListIdecAMPersonDetail& rst
			, bool transact
		) {
};

void TblIdecAMPersonDetail::updateRec(
			IdecAMPersonDetail* rec
		) {
};

void TblIdecAMPersonDetail::updateRst(
			ListIdecAMPersonDetail& rst
			, bool transact
		) {
};

void TblIdecAMPersonDetail::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAMPersonDetail::loadRecByRef(
			ubigint ref
			, IdecAMPersonDetail** rec
		) {
	return false;
};

bool TblIdecAMPersonDetail::loadRecByPrsTyp(
			ubigint refIdecMPerson
			, string x1SrefKType
			, IdecAMPersonDetail** rec
		) {
	return false;
};

ubigint TblIdecAMPersonDetail::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAMPersonDetail& rst
		) {
	ubigint numload = 0;
	IdecAMPersonDetail* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAMPersonDetail
 ******************************************************************************/

LiteTblIdecAMPersonDetail::LiteTblIdecAMPersonDetail() : TblIdecAMPersonDetail(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByPrsTyp = NULL;
};

LiteTblIdecAMPersonDetail::~LiteTblIdecAMPersonDetail() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByPrsTyp) sqlite3_finalize(stmtLoadRecByPrsTyp);
};

void LiteTblIdecAMPersonDetail::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAMPersonDetail (refIdecMPerson, x1SrefKType, Val) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAMPersonDetail SET refIdecMPerson = ?1, x1SrefKType = ?2, Val = ?3 WHERE ref = ?4");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAMPersonDetail WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMPerson, x1SrefKType, Val FROM TblIdecAMPersonDetail WHERE ref = ?1");
	stmtLoadRecByPrsTyp = createStatement("SELECT ref, refIdecMPerson, x1SrefKType, Val FROM TblIdecAMPersonDetail WHERE refIdecMPerson = ?1 AND x1SrefKType = ?2");
};

bool LiteTblIdecAMPersonDetail::loadRec(
			sqlite3_stmt* stmt
			, IdecAMPersonDetail** rec
		) {
	int res;

	IdecAMPersonDetail* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAMPersonDetail();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMPerson = sqlite3_column_int64(stmt, 1);
		_rec->x1SrefKType.assign((const char*) sqlite3_column_text(stmt, 2));
		_rec->Val.assign((const char*) sqlite3_column_text(stmt, 3));

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

ubigint LiteTblIdecAMPersonDetail::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAMPersonDetail& rst
		) {
	int res; ubigint numread = 0;

	IdecAMPersonDetail* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAMPersonDetail();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMPerson = sqlite3_column_int64(stmt, 1);
		rec->x1SrefKType.assign((const char*) sqlite3_column_text(stmt, 2));
		rec->Val.assign((const char*) sqlite3_column_text(stmt, 3));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAMPersonDetail::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAMPersonDetail** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAMPersonDetail::loadRecBySQL(
			const string& sqlstr
			, IdecAMPersonDetail** rec
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

ubigint LiteTblIdecAMPersonDetail::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAMPersonDetail& rst
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

void LiteTblIdecAMPersonDetail::insertRec(
			IdecAMPersonDetail* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMPerson);
	sqlite3_bind_text(stmtInsertRec, 2, rec->x1SrefKType.c_str(), rec->x1SrefKType.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 3, rec->Val.c_str(), rec->Val.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMPersonDetail / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAMPersonDetail::insertRst(
			ListIdecAMPersonDetail& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAMPersonDetail::updateRec(
			IdecAMPersonDetail* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMPerson);
	sqlite3_bind_text(stmtUpdateRec, 2, rec->x1SrefKType.c_str(), rec->x1SrefKType.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 3, rec->Val.c_str(), rec->Val.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMPersonDetail / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAMPersonDetail::updateRst(
			ListIdecAMPersonDetail& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAMPersonDetail::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMPersonDetail / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAMPersonDetail::loadRecByRef(
			ubigint ref
			, IdecAMPersonDetail** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecAMPersonDetail::loadRecByPrsTyp(
			ubigint refIdecMPerson
			, string x1SrefKType
			, IdecAMPersonDetail** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByPrsTyp, 1, refIdecMPerson);
	sqlite3_bind_text(stmtLoadRecByPrsTyp, 2, x1SrefKType.c_str(), x1SrefKType.length(), SQLITE_STATIC);

	return loadRecByStmt(stmtLoadRecByPrsTyp, rec);
};

