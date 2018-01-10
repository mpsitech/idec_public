/**
  * \file IdecAccRMUserUniversal.cpp
  * database access for table TblIdecAccRMUserUniversal (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAccRMUserUniversal.h"

/******************************************************************************
 class IdecAccRMUserUniversal
 ******************************************************************************/

IdecAccRMUserUniversal::IdecAccRMUserUniversal(
			const ubigint ref
			, const ubigint refIdecMUser
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVAccess
		) {

	this->ref = ref;
	this->refIdecMUser = refIdecMUser;
	this->unvIxIdecVMaintable = unvIxIdecVMaintable;
	this->unvUref = unvUref;
	this->ixIdecVAccess = ixIdecVAccess;
};

bool IdecAccRMUserUniversal::operator==(
			const IdecAccRMUserUniversal& comp
		) {
	return false;
};

bool IdecAccRMUserUniversal::operator!=(
			const IdecAccRMUserUniversal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAccRMUserUniversal
 ******************************************************************************/

ListIdecAccRMUserUniversal::ListIdecAccRMUserUniversal() {
};

ListIdecAccRMUserUniversal::ListIdecAccRMUserUniversal(
			const ListIdecAccRMUserUniversal& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAccRMUserUniversal(*(src.nodes[i]));
};

ListIdecAccRMUserUniversal::~ListIdecAccRMUserUniversal() {
	clear();
};

void ListIdecAccRMUserUniversal::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAccRMUserUniversal::size() const {
	return(nodes.size());
};

void ListIdecAccRMUserUniversal::append(
			IdecAccRMUserUniversal* rec
		) {
	nodes.push_back(rec);
};

IdecAccRMUserUniversal* ListIdecAccRMUserUniversal::operator[](
			const uint ix
		) {
	IdecAccRMUserUniversal* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAccRMUserUniversal& ListIdecAccRMUserUniversal::operator=(
			const ListIdecAccRMUserUniversal& src
		) {
	IdecAccRMUserUniversal* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAccRMUserUniversal(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAccRMUserUniversal::operator==(
			const ListIdecAccRMUserUniversal& comp
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

bool ListIdecAccRMUserUniversal::operator!=(
			const ListIdecAccRMUserUniversal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAccRMUserUniversal
 ******************************************************************************/

TblIdecAccRMUserUniversal::TblIdecAccRMUserUniversal() {
};

TblIdecAccRMUserUniversal::~TblIdecAccRMUserUniversal() {
};

bool TblIdecAccRMUserUniversal::loadRecBySQL(
			const string& sqlstr
			, IdecAccRMUserUniversal** rec
		) {
	return false;
};

ubigint TblIdecAccRMUserUniversal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAccRMUserUniversal& rst
		) {
	return 0;
};

void TblIdecAccRMUserUniversal::insertRec(
			IdecAccRMUserUniversal* rec
		) {
};

ubigint TblIdecAccRMUserUniversal::insertNewRec(
			IdecAccRMUserUniversal** rec
			, const ubigint refIdecMUser
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVAccess
		) {
	ubigint retval = 0;
	IdecAccRMUserUniversal* _rec = NULL;

	_rec = new IdecAccRMUserUniversal(0, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVAccess);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAccRMUserUniversal::appendNewRecToRst(
			ListIdecAccRMUserUniversal& rst
			, IdecAccRMUserUniversal** rec
			, const ubigint refIdecMUser
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVAccess
		) {
	ubigint retval = 0;
	IdecAccRMUserUniversal* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVAccess);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAccRMUserUniversal::insertRst(
			ListIdecAccRMUserUniversal& rst
			, bool transact
		) {
};

void TblIdecAccRMUserUniversal::updateRec(
			IdecAccRMUserUniversal* rec
		) {
};

void TblIdecAccRMUserUniversal::updateRst(
			ListIdecAccRMUserUniversal& rst
			, bool transact
		) {
};

void TblIdecAccRMUserUniversal::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAccRMUserUniversal::loadRecByRef(
			ubigint ref
			, IdecAccRMUserUniversal** rec
		) {
	return false;
};

bool TblIdecAccRMUserUniversal::loadRecByUsrMtbUnv(
			ubigint refIdecMUser
			, uint unvIxIdecVMaintable
			, ubigint unvUref
			, IdecAccRMUserUniversal** rec
		) {
	return false;
};

ubigint TblIdecAccRMUserUniversal::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAccRMUserUniversal& rst
		) {
	ubigint numload = 0;
	IdecAccRMUserUniversal* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAccRMUserUniversal
 ******************************************************************************/

LiteTblIdecAccRMUserUniversal::LiteTblIdecAccRMUserUniversal() : TblIdecAccRMUserUniversal(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByUsrMtbUnv = NULL;
};

LiteTblIdecAccRMUserUniversal::~LiteTblIdecAccRMUserUniversal() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByUsrMtbUnv) sqlite3_finalize(stmtLoadRecByUsrMtbUnv);
};

void LiteTblIdecAccRMUserUniversal::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAccRMUserUniversal (refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVAccess) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAccRMUserUniversal SET refIdecMUser = ?1, unvIxIdecVMaintable = ?2, unvUref = ?3, ixIdecVAccess = ?4 WHERE ref = ?5");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAccRMUserUniversal WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVAccess FROM TblIdecAccRMUserUniversal WHERE ref = ?1");
	stmtLoadRecByUsrMtbUnv = createStatement("SELECT ref, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVAccess FROM TblIdecAccRMUserUniversal WHERE refIdecMUser = ?1 AND unvIxIdecVMaintable = ?2 AND unvUref = ?3");
};

bool LiteTblIdecAccRMUserUniversal::loadRec(
			sqlite3_stmt* stmt
			, IdecAccRMUserUniversal** rec
		) {
	int res;

	IdecAccRMUserUniversal* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAccRMUserUniversal();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		_rec->unvIxIdecVMaintable = sqlite3_column_int(stmt, 2);
		_rec->unvUref = sqlite3_column_int64(stmt, 3);
		_rec->ixIdecVAccess = sqlite3_column_int(stmt, 4);

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

ubigint LiteTblIdecAccRMUserUniversal::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAccRMUserUniversal& rst
		) {
	int res; ubigint numread = 0;

	IdecAccRMUserUniversal* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAccRMUserUniversal();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		rec->unvIxIdecVMaintable = sqlite3_column_int(stmt, 2);
		rec->unvUref = sqlite3_column_int64(stmt, 3);
		rec->ixIdecVAccess = sqlite3_column_int(stmt, 4);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAccRMUserUniversal::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAccRMUserUniversal** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAccRMUserUniversal::loadRecBySQL(
			const string& sqlstr
			, IdecAccRMUserUniversal** rec
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

ubigint LiteTblIdecAccRMUserUniversal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAccRMUserUniversal& rst
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

void LiteTblIdecAccRMUserUniversal::insertRec(
			IdecAccRMUserUniversal* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtInsertRec, 2, rec->unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->unvUref);
	sqlite3_bind_int(stmtInsertRec, 4, rec->ixIdecVAccess);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAccRMUserUniversal / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAccRMUserUniversal::insertRst(
			ListIdecAccRMUserUniversal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAccRMUserUniversal::updateRec(
			IdecAccRMUserUniversal* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUser);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->unvUref);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->ixIdecVAccess);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAccRMUserUniversal / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAccRMUserUniversal::updateRst(
			ListIdecAccRMUserUniversal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAccRMUserUniversal::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAccRMUserUniversal / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAccRMUserUniversal::loadRecByRef(
			ubigint ref
			, IdecAccRMUserUniversal** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecAccRMUserUniversal::loadRecByUsrMtbUnv(
			ubigint refIdecMUser
			, uint unvIxIdecVMaintable
			, ubigint unvUref
			, IdecAccRMUserUniversal** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByUsrMtbUnv, 1, refIdecMUser);
	sqlite3_bind_int(stmtLoadRecByUsrMtbUnv, 2, unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtLoadRecByUsrMtbUnv, 3, unvUref);

	return loadRecByStmt(stmtLoadRecByUsrMtbUnv, rec);
};

