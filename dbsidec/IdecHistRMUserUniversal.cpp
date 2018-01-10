/**
  * \file IdecHistRMUserUniversal.cpp
  * database access for table TblIdecHistRMUserUniversal (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecHistRMUserUniversal.h"

/******************************************************************************
 class IdecHistRMUserUniversal
 ******************************************************************************/

IdecHistRMUserUniversal::IdecHistRMUserUniversal(
			const ubigint ref
			, const ubigint refIdecMUser
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVCard
			, const uint ixIdecVPreset
			, const uint preIxIdecVMaintable
			, const ubigint preUref
			, const uint start
		) {

	this->ref = ref;
	this->refIdecMUser = refIdecMUser;
	this->unvIxIdecVMaintable = unvIxIdecVMaintable;
	this->unvUref = unvUref;
	this->ixIdecVCard = ixIdecVCard;
	this->ixIdecVPreset = ixIdecVPreset;
	this->preIxIdecVMaintable = preIxIdecVMaintable;
	this->preUref = preUref;
	this->start = start;
};

bool IdecHistRMUserUniversal::operator==(
			const IdecHistRMUserUniversal& comp
		) {
	return false;
};

bool IdecHistRMUserUniversal::operator!=(
			const IdecHistRMUserUniversal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecHistRMUserUniversal
 ******************************************************************************/

ListIdecHistRMUserUniversal::ListIdecHistRMUserUniversal() {
};

ListIdecHistRMUserUniversal::ListIdecHistRMUserUniversal(
			const ListIdecHistRMUserUniversal& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecHistRMUserUniversal(*(src.nodes[i]));
};

ListIdecHistRMUserUniversal::~ListIdecHistRMUserUniversal() {
	clear();
};

void ListIdecHistRMUserUniversal::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecHistRMUserUniversal::size() const {
	return(nodes.size());
};

void ListIdecHistRMUserUniversal::append(
			IdecHistRMUserUniversal* rec
		) {
	nodes.push_back(rec);
};

IdecHistRMUserUniversal* ListIdecHistRMUserUniversal::operator[](
			const uint ix
		) {
	IdecHistRMUserUniversal* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecHistRMUserUniversal& ListIdecHistRMUserUniversal::operator=(
			const ListIdecHistRMUserUniversal& src
		) {
	IdecHistRMUserUniversal* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecHistRMUserUniversal(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecHistRMUserUniversal::operator==(
			const ListIdecHistRMUserUniversal& comp
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

bool ListIdecHistRMUserUniversal::operator!=(
			const ListIdecHistRMUserUniversal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecHistRMUserUniversal
 ******************************************************************************/

TblIdecHistRMUserUniversal::TblIdecHistRMUserUniversal() {
};

TblIdecHistRMUserUniversal::~TblIdecHistRMUserUniversal() {
};

bool TblIdecHistRMUserUniversal::loadRecBySQL(
			const string& sqlstr
			, IdecHistRMUserUniversal** rec
		) {
	return false;
};

ubigint TblIdecHistRMUserUniversal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecHistRMUserUniversal& rst
		) {
	return 0;
};

void TblIdecHistRMUserUniversal::insertRec(
			IdecHistRMUserUniversal* rec
		) {
};

ubigint TblIdecHistRMUserUniversal::insertNewRec(
			IdecHistRMUserUniversal** rec
			, const ubigint refIdecMUser
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVCard
			, const uint ixIdecVPreset
			, const uint preIxIdecVMaintable
			, const ubigint preUref
			, const uint start
		) {
	ubigint retval = 0;
	IdecHistRMUserUniversal* _rec = NULL;

	_rec = new IdecHistRMUserUniversal(0, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVCard, ixIdecVPreset, preIxIdecVMaintable, preUref, start);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecHistRMUserUniversal::appendNewRecToRst(
			ListIdecHistRMUserUniversal& rst
			, IdecHistRMUserUniversal** rec
			, const ubigint refIdecMUser
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVCard
			, const uint ixIdecVPreset
			, const uint preIxIdecVMaintable
			, const ubigint preUref
			, const uint start
		) {
	ubigint retval = 0;
	IdecHistRMUserUniversal* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVCard, ixIdecVPreset, preIxIdecVMaintable, preUref, start);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecHistRMUserUniversal::insertRst(
			ListIdecHistRMUserUniversal& rst
			, bool transact
		) {
};

void TblIdecHistRMUserUniversal::updateRec(
			IdecHistRMUserUniversal* rec
		) {
};

void TblIdecHistRMUserUniversal::updateRst(
			ListIdecHistRMUserUniversal& rst
			, bool transact
		) {
};

void TblIdecHistRMUserUniversal::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecHistRMUserUniversal::loadRecByRef(
			ubigint ref
			, IdecHistRMUserUniversal** rec
		) {
	return false;
};

ubigint TblIdecHistRMUserUniversal::loadRstByUsrCrd(
			ubigint refIdecMUser
			, uint ixIdecVCard
			, const bool append
			, ListIdecHistRMUserUniversal& rst
		) {
	return 0;
};

bool TblIdecHistRMUserUniversal::loadUnuByRef(
			ubigint ref
			, ubigint& unvUref
		) {
	return false;
};

ubigint TblIdecHistRMUserUniversal::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecHistRMUserUniversal& rst
		) {
	ubigint numload = 0;
	IdecHistRMUserUniversal* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecHistRMUserUniversal
 ******************************************************************************/

LiteTblIdecHistRMUserUniversal::LiteTblIdecHistRMUserUniversal() : TblIdecHistRMUserUniversal(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRstByUsrCrd = NULL;
	stmtLoadUnuByRef = NULL;
};

LiteTblIdecHistRMUserUniversal::~LiteTblIdecHistRMUserUniversal() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRstByUsrCrd) sqlite3_finalize(stmtLoadRstByUsrCrd);
	if (stmtLoadUnuByRef) sqlite3_finalize(stmtLoadUnuByRef);
};

void LiteTblIdecHistRMUserUniversal::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecHistRMUserUniversal (refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVCard, ixIdecVPreset, preIxIdecVMaintable, preUref, start) VALUES (?1,?2,?3,?4,?5,?6,?7,?8)");
	stmtUpdateRec = createStatement("UPDATE TblIdecHistRMUserUniversal SET refIdecMUser = ?1, unvIxIdecVMaintable = ?2, unvUref = ?3, ixIdecVCard = ?4, ixIdecVPreset = ?5, preIxIdecVMaintable = ?6, preUref = ?7, start = ?8 WHERE ref = ?9");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecHistRMUserUniversal WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVCard, ixIdecVPreset, preIxIdecVMaintable, preUref, start FROM TblIdecHistRMUserUniversal WHERE ref = ?1");
	stmtLoadRstByUsrCrd = createStatement("SELECT ref, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVCard, ixIdecVPreset, preIxIdecVMaintable, preUref, start FROM TblIdecHistRMUserUniversal WHERE refIdecMUser = ?1 AND ixIdecVCard = ?2 ORDER BY start DESC");
	stmtLoadUnuByRef = createStatement("SELECT unvUref FROM TblIdecHistRMUserUniversal WHERE ref = ?1");
};

bool LiteTblIdecHistRMUserUniversal::loadRec(
			sqlite3_stmt* stmt
			, IdecHistRMUserUniversal** rec
		) {
	int res;

	IdecHistRMUserUniversal* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecHistRMUserUniversal();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		_rec->unvIxIdecVMaintable = sqlite3_column_int(stmt, 2);
		_rec->unvUref = sqlite3_column_int64(stmt, 3);
		_rec->ixIdecVCard = sqlite3_column_int(stmt, 4);
		_rec->ixIdecVPreset = sqlite3_column_int(stmt, 5);
		_rec->preIxIdecVMaintable = sqlite3_column_int(stmt, 6);
		_rec->preUref = sqlite3_column_int64(stmt, 7);
		_rec->start = sqlite3_column_int(stmt, 8);

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

ubigint LiteTblIdecHistRMUserUniversal::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecHistRMUserUniversal& rst
		) {
	int res; ubigint numread = 0;

	IdecHistRMUserUniversal* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecHistRMUserUniversal();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		rec->unvIxIdecVMaintable = sqlite3_column_int(stmt, 2);
		rec->unvUref = sqlite3_column_int64(stmt, 3);
		rec->ixIdecVCard = sqlite3_column_int(stmt, 4);
		rec->ixIdecVPreset = sqlite3_column_int(stmt, 5);
		rec->preIxIdecVMaintable = sqlite3_column_int(stmt, 6);
		rec->preUref = sqlite3_column_int64(stmt, 7);
		rec->start = sqlite3_column_int(stmt, 8);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecHistRMUserUniversal::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecHistRMUserUniversal** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecHistRMUserUniversal::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecHistRMUserUniversal& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecHistRMUserUniversal::loadRecBySQL(
			const string& sqlstr
			, IdecHistRMUserUniversal** rec
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

ubigint LiteTblIdecHistRMUserUniversal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecHistRMUserUniversal& rst
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

void LiteTblIdecHistRMUserUniversal::insertRec(
			IdecHistRMUserUniversal* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtInsertRec, 2, rec->unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->unvUref);
	sqlite3_bind_int(stmtInsertRec, 4, rec->ixIdecVCard);
	sqlite3_bind_int(stmtInsertRec, 5, rec->ixIdecVPreset);
	sqlite3_bind_int(stmtInsertRec, 6, rec->preIxIdecVMaintable);
	sqlite3_bind_int64(stmtInsertRec, 7, rec->preUref);
	sqlite3_bind_int(stmtInsertRec, 8, rec->start);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecHistRMUserUniversal / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecHistRMUserUniversal::insertRst(
			ListIdecHistRMUserUniversal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecHistRMUserUniversal::updateRec(
			IdecHistRMUserUniversal* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->unvUref);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->ixIdecVCard);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->ixIdecVPreset);
	sqlite3_bind_int(stmtUpdateRec, 6, rec->preIxIdecVMaintable);
	sqlite3_bind_int64(stmtUpdateRec, 7, rec->preUref);
	sqlite3_bind_int(stmtUpdateRec, 8, rec->start);
	sqlite3_bind_int64(stmtUpdateRec, 9, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecHistRMUserUniversal / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecHistRMUserUniversal::updateRst(
			ListIdecHistRMUserUniversal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecHistRMUserUniversal::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecHistRMUserUniversal / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecHistRMUserUniversal::loadRecByRef(
			ubigint ref
			, IdecHistRMUserUniversal** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

ubigint LiteTblIdecHistRMUserUniversal::loadRstByUsrCrd(
			ubigint refIdecMUser
			, uint ixIdecVCard
			, const bool append
			, ListIdecHistRMUserUniversal& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsrCrd, 1, refIdecMUser);
	sqlite3_bind_int(stmtLoadRstByUsrCrd, 2, ixIdecVCard);

	return loadRstByStmt(stmtLoadRstByUsrCrd, append, rst);
};

bool LiteTblIdecHistRMUserUniversal::loadUnuByRef(
			ubigint ref
			, ubigint& unvUref
		) {
	sqlite3_bind_int64(stmtLoadUnuByRef, 1, ref);

	return loadRefByStmt(stmtLoadUnuByRef, unvUref);
};

