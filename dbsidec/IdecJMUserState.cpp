/**
  * \file IdecJMUserState.cpp
  * database access for table TblIdecJMUserState (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecJMUserState.h"

/******************************************************************************
 class IdecJMUserState
 ******************************************************************************/

IdecJMUserState::IdecJMUserState(
			const ubigint ref
			, const ubigint refIdecMUser
			, const uint x1Startd
			, const uint ixVState
		) {

	this->ref = ref;
	this->refIdecMUser = refIdecMUser;
	this->x1Startd = x1Startd;
	this->ixVState = ixVState;
};

bool IdecJMUserState::operator==(
			const IdecJMUserState& comp
		) {
	return false;
};

bool IdecJMUserState::operator!=(
			const IdecJMUserState& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecJMUserState
 ******************************************************************************/

ListIdecJMUserState::ListIdecJMUserState() {
};

ListIdecJMUserState::ListIdecJMUserState(
			const ListIdecJMUserState& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecJMUserState(*(src.nodes[i]));
};

ListIdecJMUserState::~ListIdecJMUserState() {
	clear();
};

void ListIdecJMUserState::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecJMUserState::size() const {
	return(nodes.size());
};

void ListIdecJMUserState::append(
			IdecJMUserState* rec
		) {
	nodes.push_back(rec);
};

IdecJMUserState* ListIdecJMUserState::operator[](
			const uint ix
		) {
	IdecJMUserState* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecJMUserState& ListIdecJMUserState::operator=(
			const ListIdecJMUserState& src
		) {
	IdecJMUserState* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecJMUserState(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecJMUserState::operator==(
			const ListIdecJMUserState& comp
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

bool ListIdecJMUserState::operator!=(
			const ListIdecJMUserState& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecJMUserState
 ******************************************************************************/

TblIdecJMUserState::TblIdecJMUserState() {
};

TblIdecJMUserState::~TblIdecJMUserState() {
};

bool TblIdecJMUserState::loadRecBySQL(
			const string& sqlstr
			, IdecJMUserState** rec
		) {
	return false;
};

ubigint TblIdecJMUserState::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecJMUserState& rst
		) {
	return 0;
};

void TblIdecJMUserState::insertRec(
			IdecJMUserState* rec
		) {
};

ubigint TblIdecJMUserState::insertNewRec(
			IdecJMUserState** rec
			, const ubigint refIdecMUser
			, const uint x1Startd
			, const uint ixVState
		) {
	ubigint retval = 0;
	IdecJMUserState* _rec = NULL;

	_rec = new IdecJMUserState(0, refIdecMUser, x1Startd, ixVState);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecJMUserState::appendNewRecToRst(
			ListIdecJMUserState& rst
			, IdecJMUserState** rec
			, const ubigint refIdecMUser
			, const uint x1Startd
			, const uint ixVState
		) {
	ubigint retval = 0;
	IdecJMUserState* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUser, x1Startd, ixVState);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecJMUserState::insertRst(
			ListIdecJMUserState& rst
			, bool transact
		) {
};

void TblIdecJMUserState::updateRec(
			IdecJMUserState* rec
		) {
};

void TblIdecJMUserState::updateRst(
			ListIdecJMUserState& rst
			, bool transact
		) {
};

void TblIdecJMUserState::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecJMUserState::loadRecByRef(
			ubigint ref
			, IdecJMUserState** rec
		) {
	return false;
};

bool TblIdecJMUserState::loadRecByUsrSta(
			ubigint refIdecMUser
			, uint x1Startd
			, IdecJMUserState** rec
		) {
	return false;
};

ubigint TblIdecJMUserState::loadRefsByUsr(
			ubigint refIdecMUser
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

ubigint TblIdecJMUserState::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecJMUserState& rst
		) {
	return 0;
};

ubigint TblIdecJMUserState::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecJMUserState& rst
		) {
	ubigint numload = 0;
	IdecJMUserState* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecJMUserState
 ******************************************************************************/

LiteTblIdecJMUserState::LiteTblIdecJMUserState() : TblIdecJMUserState(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByUsrSta = NULL;
	stmtLoadRefsByUsr = NULL;
	stmtLoadRstByUsr = NULL;
};

LiteTblIdecJMUserState::~LiteTblIdecJMUserState() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByUsrSta) sqlite3_finalize(stmtLoadRecByUsrSta);
	if (stmtLoadRefsByUsr) sqlite3_finalize(stmtLoadRefsByUsr);
	if (stmtLoadRstByUsr) sqlite3_finalize(stmtLoadRstByUsr);
};

void LiteTblIdecJMUserState::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecJMUserState (refIdecMUser, x1Startd, ixVState) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecJMUserState SET refIdecMUser = ?1, x1Startd = ?2, ixVState = ?3 WHERE ref = ?4");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecJMUserState WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUser, x1Startd, ixVState FROM TblIdecJMUserState WHERE ref = ?1");
	stmtLoadRecByUsrSta = createStatement("SELECT ref, refIdecMUser, x1Startd, ixVState FROM TblIdecJMUserState WHERE refIdecMUser = ?1 AND x1Startd <= ?2 ORDER BY x1Startd DESC LIMIT 0,1");
	stmtLoadRefsByUsr = createStatement("SELECT ref FROM TblIdecJMUserState WHERE refIdecMUser = ?1");
	stmtLoadRstByUsr = createStatement("SELECT ref, refIdecMUser, x1Startd, ixVState FROM TblIdecJMUserState WHERE refIdecMUser = ?1 ORDER BY x1Startd ASC");
};

bool LiteTblIdecJMUserState::loadRec(
			sqlite3_stmt* stmt
			, IdecJMUserState** rec
		) {
	int res;

	IdecJMUserState* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecJMUserState();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		_rec->x1Startd = sqlite3_column_int(stmt, 2);
		_rec->ixVState = sqlite3_column_int(stmt, 3);

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

ubigint LiteTblIdecJMUserState::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecJMUserState& rst
		) {
	int res; ubigint numread = 0;

	IdecJMUserState* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecJMUserState();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		rec->x1Startd = sqlite3_column_int(stmt, 2);
		rec->ixVState = sqlite3_column_int(stmt, 3);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecJMUserState::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecJMUserState** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecJMUserState::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecJMUserState& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecJMUserState::loadRecBySQL(
			const string& sqlstr
			, IdecJMUserState** rec
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

ubigint LiteTblIdecJMUserState::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecJMUserState& rst
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

void LiteTblIdecJMUserState::insertRec(
			IdecJMUserState* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtInsertRec, 2, rec->x1Startd);
	sqlite3_bind_int(stmtInsertRec, 3, rec->ixVState);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJMUserState / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecJMUserState::insertRst(
			ListIdecJMUserState& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecJMUserState::updateRec(
			IdecJMUserState* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->x1Startd);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->ixVState);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJMUserState / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecJMUserState::updateRst(
			ListIdecJMUserState& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecJMUserState::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJMUserState / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecJMUserState::loadRecByRef(
			ubigint ref
			, IdecJMUserState** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecJMUserState::loadRecByUsrSta(
			ubigint refIdecMUser
			, uint x1Startd
			, IdecJMUserState** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByUsrSta, 1, refIdecMUser);
	sqlite3_bind_int(stmtLoadRecByUsrSta, 2, x1Startd);

	return loadRecByStmt(stmtLoadRecByUsrSta, rec);
};

ubigint LiteTblIdecJMUserState::loadRefsByUsr(
			ubigint refIdecMUser
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByUsr, 1, refIdecMUser);

	return loadRefsByStmt(stmtLoadRefsByUsr, append, refs);
};

ubigint LiteTblIdecJMUserState::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecJMUserState& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsr, 1, refIdecMUser);

	return loadRstByStmt(stmtLoadRstByUsr, append, rst);
};

