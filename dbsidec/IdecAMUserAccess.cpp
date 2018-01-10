/**
  * \file IdecAMUserAccess.cpp
  * database access for table TblIdecAMUserAccess (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAMUserAccess.h"

/******************************************************************************
 class IdecAMUserAccess
 ******************************************************************************/

IdecAMUserAccess::IdecAMUserAccess(
			const ubigint ref
			, const ubigint refIdecMUser
			, const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) {

	this->ref = ref;
	this->refIdecMUser = refIdecMUser;
	this->x1IxIdecVCard = x1IxIdecVCard;
	this->ixIdecWUiaccess = ixIdecWUiaccess;
};

bool IdecAMUserAccess::operator==(
			const IdecAMUserAccess& comp
		) {
	return false;
};

bool IdecAMUserAccess::operator!=(
			const IdecAMUserAccess& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAMUserAccess
 ******************************************************************************/

ListIdecAMUserAccess::ListIdecAMUserAccess() {
};

ListIdecAMUserAccess::ListIdecAMUserAccess(
			const ListIdecAMUserAccess& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAMUserAccess(*(src.nodes[i]));
};

ListIdecAMUserAccess::~ListIdecAMUserAccess() {
	clear();
};

void ListIdecAMUserAccess::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAMUserAccess::size() const {
	return(nodes.size());
};

void ListIdecAMUserAccess::append(
			IdecAMUserAccess* rec
		) {
	nodes.push_back(rec);
};

IdecAMUserAccess* ListIdecAMUserAccess::operator[](
			const uint ix
		) {
	IdecAMUserAccess* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAMUserAccess& ListIdecAMUserAccess::operator=(
			const ListIdecAMUserAccess& src
		) {
	IdecAMUserAccess* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAMUserAccess(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAMUserAccess::operator==(
			const ListIdecAMUserAccess& comp
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

bool ListIdecAMUserAccess::operator!=(
			const ListIdecAMUserAccess& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAMUserAccess
 ******************************************************************************/

TblIdecAMUserAccess::TblIdecAMUserAccess() {
};

TblIdecAMUserAccess::~TblIdecAMUserAccess() {
};

bool TblIdecAMUserAccess::loadRecBySQL(
			const string& sqlstr
			, IdecAMUserAccess** rec
		) {
	return false;
};

ubigint TblIdecAMUserAccess::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAMUserAccess& rst
		) {
	return 0;
};

void TblIdecAMUserAccess::insertRec(
			IdecAMUserAccess* rec
		) {
};

ubigint TblIdecAMUserAccess::insertNewRec(
			IdecAMUserAccess** rec
			, const ubigint refIdecMUser
			, const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) {
	ubigint retval = 0;
	IdecAMUserAccess* _rec = NULL;

	_rec = new IdecAMUserAccess(0, refIdecMUser, x1IxIdecVCard, ixIdecWUiaccess);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAMUserAccess::appendNewRecToRst(
			ListIdecAMUserAccess& rst
			, IdecAMUserAccess** rec
			, const ubigint refIdecMUser
			, const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) {
	ubigint retval = 0;
	IdecAMUserAccess* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUser, x1IxIdecVCard, ixIdecWUiaccess);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAMUserAccess::insertRst(
			ListIdecAMUserAccess& rst
			, bool transact
		) {
};

void TblIdecAMUserAccess::updateRec(
			IdecAMUserAccess* rec
		) {
};

void TblIdecAMUserAccess::updateRst(
			ListIdecAMUserAccess& rst
			, bool transact
		) {
};

void TblIdecAMUserAccess::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAMUserAccess::loadRecByRef(
			ubigint ref
			, IdecAMUserAccess** rec
		) {
	return false;
};

bool TblIdecAMUserAccess::loadRecByUsrCrd(
			ubigint refIdecMUser
			, uint x1IxIdecVCard
			, IdecAMUserAccess** rec
		) {
	return false;
};

ubigint TblIdecAMUserAccess::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecAMUserAccess& rst
		) {
	return 0;
};

ubigint TblIdecAMUserAccess::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAMUserAccess& rst
		) {
	ubigint numload = 0;
	IdecAMUserAccess* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAMUserAccess
 ******************************************************************************/

LiteTblIdecAMUserAccess::LiteTblIdecAMUserAccess() : TblIdecAMUserAccess(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByUsrCrd = NULL;
	stmtLoadRstByUsr = NULL;
};

LiteTblIdecAMUserAccess::~LiteTblIdecAMUserAccess() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByUsrCrd) sqlite3_finalize(stmtLoadRecByUsrCrd);
	if (stmtLoadRstByUsr) sqlite3_finalize(stmtLoadRstByUsr);
};

void LiteTblIdecAMUserAccess::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAMUserAccess (refIdecMUser, x1IxIdecVCard, ixIdecWUiaccess) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAMUserAccess SET refIdecMUser = ?1, x1IxIdecVCard = ?2, ixIdecWUiaccess = ?3 WHERE ref = ?4");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAMUserAccess WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUser, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecAMUserAccess WHERE ref = ?1");
	stmtLoadRecByUsrCrd = createStatement("SELECT ref, refIdecMUser, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecAMUserAccess WHERE refIdecMUser = ?1 AND x1IxIdecVCard = ?2");
	stmtLoadRstByUsr = createStatement("SELECT ref, refIdecMUser, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecAMUserAccess WHERE refIdecMUser = ?1 ORDER BY x1IxIdecVCard ASC");
};

bool LiteTblIdecAMUserAccess::loadRec(
			sqlite3_stmt* stmt
			, IdecAMUserAccess** rec
		) {
	int res;

	IdecAMUserAccess* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAMUserAccess();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		_rec->x1IxIdecVCard = sqlite3_column_int(stmt, 2);
		_rec->ixIdecWUiaccess = sqlite3_column_int(stmt, 3);

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

ubigint LiteTblIdecAMUserAccess::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAMUserAccess& rst
		) {
	int res; ubigint numread = 0;

	IdecAMUserAccess* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAMUserAccess();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		rec->x1IxIdecVCard = sqlite3_column_int(stmt, 2);
		rec->ixIdecWUiaccess = sqlite3_column_int(stmt, 3);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAMUserAccess::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAMUserAccess** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecAMUserAccess::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAMUserAccess& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAMUserAccess::loadRecBySQL(
			const string& sqlstr
			, IdecAMUserAccess** rec
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

ubigint LiteTblIdecAMUserAccess::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAMUserAccess& rst
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

void LiteTblIdecAMUserAccess::insertRec(
			IdecAMUserAccess* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtInsertRec, 2, rec->x1IxIdecVCard);
	sqlite3_bind_int(stmtInsertRec, 3, rec->ixIdecWUiaccess);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMUserAccess / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAMUserAccess::insertRst(
			ListIdecAMUserAccess& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAMUserAccess::updateRec(
			IdecAMUserAccess* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->x1IxIdecVCard);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->ixIdecWUiaccess);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMUserAccess / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAMUserAccess::updateRst(
			ListIdecAMUserAccess& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAMUserAccess::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMUserAccess / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAMUserAccess::loadRecByRef(
			ubigint ref
			, IdecAMUserAccess** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecAMUserAccess::loadRecByUsrCrd(
			ubigint refIdecMUser
			, uint x1IxIdecVCard
			, IdecAMUserAccess** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByUsrCrd, 1, refIdecMUser);
	sqlite3_bind_int(stmtLoadRecByUsrCrd, 2, x1IxIdecVCard);

	return loadRecByStmt(stmtLoadRecByUsrCrd, rec);
};

ubigint LiteTblIdecAMUserAccess::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecAMUserAccess& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsr, 1, refIdecMUser);

	return loadRstByStmt(stmtLoadRstByUsr, append, rst);
};

