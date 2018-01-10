/**
  * \file IdecMSession.cpp
  * database access for table TblIdecMSession (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMSession.h"

/******************************************************************************
 class IdecMSession
 ******************************************************************************/

IdecMSession::IdecMSession(
			const ubigint ref
			, const ubigint refIdecMUser
			, const uint start
			, const uint stop
			, const string Ip
		) {

	this->ref = ref;
	this->refIdecMUser = refIdecMUser;
	this->start = start;
	this->stop = stop;
	this->Ip = Ip;
};

bool IdecMSession::operator==(
			const IdecMSession& comp
		) {
	return false;
};

bool IdecMSession::operator!=(
			const IdecMSession& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMSession
 ******************************************************************************/

ListIdecMSession::ListIdecMSession() {
};

ListIdecMSession::ListIdecMSession(
			const ListIdecMSession& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMSession(*(src.nodes[i]));
};

ListIdecMSession::~ListIdecMSession() {
	clear();
};

void ListIdecMSession::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMSession::size() const {
	return(nodes.size());
};

void ListIdecMSession::append(
			IdecMSession* rec
		) {
	nodes.push_back(rec);
};

IdecMSession* ListIdecMSession::operator[](
			const uint ix
		) {
	IdecMSession* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMSession& ListIdecMSession::operator=(
			const ListIdecMSession& src
		) {
	IdecMSession* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMSession(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMSession::operator==(
			const ListIdecMSession& comp
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

bool ListIdecMSession::operator!=(
			const ListIdecMSession& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMSession
 ******************************************************************************/

TblIdecMSession::TblIdecMSession() {
};

TblIdecMSession::~TblIdecMSession() {
};

bool TblIdecMSession::loadRecBySQL(
			const string& sqlstr
			, IdecMSession** rec
		) {
	return false;
};

ubigint TblIdecMSession::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMSession& rst
		) {
	return 0;
};

void TblIdecMSession::insertRec(
			IdecMSession* rec
		) {
};

ubigint TblIdecMSession::insertNewRec(
			IdecMSession** rec
			, const ubigint refIdecMUser
			, const uint start
			, const uint stop
			, const string Ip
		) {
	ubigint retval = 0;
	IdecMSession* _rec = NULL;

	_rec = new IdecMSession(0, refIdecMUser, start, stop, Ip);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMSession::appendNewRecToRst(
			ListIdecMSession& rst
			, IdecMSession** rec
			, const ubigint refIdecMUser
			, const uint start
			, const uint stop
			, const string Ip
		) {
	ubigint retval = 0;
	IdecMSession* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUser, start, stop, Ip);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMSession::insertRst(
			ListIdecMSession& rst
			, bool transact
		) {
};

void TblIdecMSession::updateRec(
			IdecMSession* rec
		) {
};

void TblIdecMSession::updateRst(
			ListIdecMSession& rst
			, bool transact
		) {
};

void TblIdecMSession::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMSession::loadRecByRef(
			ubigint ref
			, IdecMSession** rec
		) {
	return false;
};

ubigint TblIdecMSession::loadRefsByUsr(
			ubigint refIdecMUser
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

ubigint TblIdecMSession::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecMSession& rst
		) {
	return 0;
};

ubigint TblIdecMSession::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMSession& rst
		) {
	ubigint numload = 0;
	IdecMSession* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMSession
 ******************************************************************************/

LiteTblIdecMSession::LiteTblIdecMSession() : TblIdecMSession(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRefsByUsr = NULL;
	stmtLoadRstByUsr = NULL;
};

LiteTblIdecMSession::~LiteTblIdecMSession() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRefsByUsr) sqlite3_finalize(stmtLoadRefsByUsr);
	if (stmtLoadRstByUsr) sqlite3_finalize(stmtLoadRstByUsr);
};

void LiteTblIdecMSession::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMSession (refIdecMUser, start, stop, Ip) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMSession SET refIdecMUser = ?1, start = ?2, stop = ?3, Ip = ?4 WHERE ref = ?5");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMSession WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUser, start, stop, Ip FROM TblIdecMSession WHERE ref = ?1");
	stmtLoadRefsByUsr = createStatement("SELECT ref FROM TblIdecMSession WHERE refIdecMUser = ?1 ORDER BY start ASC");
	stmtLoadRstByUsr = createStatement("SELECT ref, refIdecMUser, start, stop, Ip FROM TblIdecMSession WHERE refIdecMUser = ?1 ORDER BY start ASC");
};

bool LiteTblIdecMSession::loadRec(
			sqlite3_stmt* stmt
			, IdecMSession** rec
		) {
	int res;

	IdecMSession* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMSession();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		_rec->start = sqlite3_column_int(stmt, 2);
		_rec->stop = sqlite3_column_int(stmt, 3);
		_rec->Ip.assign((const char*) sqlite3_column_text(stmt, 4));

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

ubigint LiteTblIdecMSession::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMSession& rst
		) {
	int res; ubigint numread = 0;

	IdecMSession* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMSession();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		rec->start = sqlite3_column_int(stmt, 2);
		rec->stop = sqlite3_column_int(stmt, 3);
		rec->Ip.assign((const char*) sqlite3_column_text(stmt, 4));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMSession::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMSession** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecMSession::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMSession& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMSession::loadRecBySQL(
			const string& sqlstr
			, IdecMSession** rec
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

ubigint LiteTblIdecMSession::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMSession& rst
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

void LiteTblIdecMSession::insertRec(
			IdecMSession* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtInsertRec, 2, rec->start);
	sqlite3_bind_int(stmtInsertRec, 3, rec->stop);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Ip.c_str(), rec->Ip.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMSession / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMSession::insertRst(
			ListIdecMSession& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMSession::updateRec(
			IdecMSession* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->start);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->stop);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Ip.c_str(), rec->Ip.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMSession / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMSession::updateRst(
			ListIdecMSession& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMSession::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMSession / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMSession::loadRecByRef(
			ubigint ref
			, IdecMSession** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

ubigint LiteTblIdecMSession::loadRefsByUsr(
			ubigint refIdecMUser
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByUsr, 1, refIdecMUser);

	return loadRefsByStmt(stmtLoadRefsByUsr, append, refs);
};

ubigint LiteTblIdecMSession::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecMSession& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsr, 1, refIdecMUser);

	return loadRstByStmt(stmtLoadRstByUsr, append, rst);
};

