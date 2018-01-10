/**
  * \file IdecRMUsergroupUniversal.cpp
  * database access for table TblIdecRMUsergroupUniversal (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecRMUsergroupUniversal.h"

/******************************************************************************
 class IdecRMUsergroupUniversal
 ******************************************************************************/

IdecRMUsergroupUniversal::IdecRMUsergroupUniversal(
			const ubigint ref
			, const ubigint refIdecMUsergroup
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVAccess
		) {

	this->ref = ref;
	this->refIdecMUsergroup = refIdecMUsergroup;
	this->unvIxIdecVMaintable = unvIxIdecVMaintable;
	this->unvUref = unvUref;
	this->ixIdecVAccess = ixIdecVAccess;
};

bool IdecRMUsergroupUniversal::operator==(
			const IdecRMUsergroupUniversal& comp
		) {
	return false;
};

bool IdecRMUsergroupUniversal::operator!=(
			const IdecRMUsergroupUniversal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecRMUsergroupUniversal
 ******************************************************************************/

ListIdecRMUsergroupUniversal::ListIdecRMUsergroupUniversal() {
};

ListIdecRMUsergroupUniversal::ListIdecRMUsergroupUniversal(
			const ListIdecRMUsergroupUniversal& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecRMUsergroupUniversal(*(src.nodes[i]));
};

ListIdecRMUsergroupUniversal::~ListIdecRMUsergroupUniversal() {
	clear();
};

void ListIdecRMUsergroupUniversal::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecRMUsergroupUniversal::size() const {
	return(nodes.size());
};

void ListIdecRMUsergroupUniversal::append(
			IdecRMUsergroupUniversal* rec
		) {
	nodes.push_back(rec);
};

IdecRMUsergroupUniversal* ListIdecRMUsergroupUniversal::operator[](
			const uint ix
		) {
	IdecRMUsergroupUniversal* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecRMUsergroupUniversal& ListIdecRMUsergroupUniversal::operator=(
			const ListIdecRMUsergroupUniversal& src
		) {
	IdecRMUsergroupUniversal* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecRMUsergroupUniversal(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecRMUsergroupUniversal::operator==(
			const ListIdecRMUsergroupUniversal& comp
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

bool ListIdecRMUsergroupUniversal::operator!=(
			const ListIdecRMUsergroupUniversal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecRMUsergroupUniversal
 ******************************************************************************/

TblIdecRMUsergroupUniversal::TblIdecRMUsergroupUniversal() {
};

TblIdecRMUsergroupUniversal::~TblIdecRMUsergroupUniversal() {
};

bool TblIdecRMUsergroupUniversal::loadRecBySQL(
			const string& sqlstr
			, IdecRMUsergroupUniversal** rec
		) {
	return false;
};

ubigint TblIdecRMUsergroupUniversal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecRMUsergroupUniversal& rst
		) {
	return 0;
};

void TblIdecRMUsergroupUniversal::insertRec(
			IdecRMUsergroupUniversal* rec
		) {
};

ubigint TblIdecRMUsergroupUniversal::insertNewRec(
			IdecRMUsergroupUniversal** rec
			, const ubigint refIdecMUsergroup
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVAccess
		) {
	ubigint retval = 0;
	IdecRMUsergroupUniversal* _rec = NULL;

	_rec = new IdecRMUsergroupUniversal(0, refIdecMUsergroup, unvIxIdecVMaintable, unvUref, ixIdecVAccess);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecRMUsergroupUniversal::appendNewRecToRst(
			ListIdecRMUsergroupUniversal& rst
			, IdecRMUsergroupUniversal** rec
			, const ubigint refIdecMUsergroup
			, const uint unvIxIdecVMaintable
			, const ubigint unvUref
			, const uint ixIdecVAccess
		) {
	ubigint retval = 0;
	IdecRMUsergroupUniversal* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUsergroup, unvIxIdecVMaintable, unvUref, ixIdecVAccess);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecRMUsergroupUniversal::insertRst(
			ListIdecRMUsergroupUniversal& rst
			, bool transact
		) {
};

void TblIdecRMUsergroupUniversal::updateRec(
			IdecRMUsergroupUniversal* rec
		) {
};

void TblIdecRMUsergroupUniversal::updateRst(
			ListIdecRMUsergroupUniversal& rst
			, bool transact
		) {
};

void TblIdecRMUsergroupUniversal::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecRMUsergroupUniversal::loadRecByRef(
			ubigint ref
			, IdecRMUsergroupUniversal** rec
		) {
	return false;
};

bool TblIdecRMUsergroupUniversal::loadRecByUsgMtbUnv(
			ubigint refIdecMUsergroup
			, uint unvIxIdecVMaintable
			, ubigint unvUref
			, IdecRMUsergroupUniversal** rec
		) {
	return false;
};

ubigint TblIdecRMUsergroupUniversal::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecRMUsergroupUniversal& rst
		) {
	ubigint numload = 0;
	IdecRMUsergroupUniversal* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecRMUsergroupUniversal
 ******************************************************************************/

LiteTblIdecRMUsergroupUniversal::LiteTblIdecRMUsergroupUniversal() : TblIdecRMUsergroupUniversal(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByUsgMtbUnv = NULL;
};

LiteTblIdecRMUsergroupUniversal::~LiteTblIdecRMUsergroupUniversal() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByUsgMtbUnv) sqlite3_finalize(stmtLoadRecByUsgMtbUnv);
};

void LiteTblIdecRMUsergroupUniversal::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecRMUsergroupUniversal (refIdecMUsergroup, unvIxIdecVMaintable, unvUref, ixIdecVAccess) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecRMUsergroupUniversal SET refIdecMUsergroup = ?1, unvIxIdecVMaintable = ?2, unvUref = ?3, ixIdecVAccess = ?4 WHERE ref = ?5");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecRMUsergroupUniversal WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUsergroup, unvIxIdecVMaintable, unvUref, ixIdecVAccess FROM TblIdecRMUsergroupUniversal WHERE ref = ?1");
	stmtLoadRecByUsgMtbUnv = createStatement("SELECT ref, refIdecMUsergroup, unvIxIdecVMaintable, unvUref, ixIdecVAccess FROM TblIdecRMUsergroupUniversal WHERE refIdecMUsergroup = ?1 AND unvIxIdecVMaintable = ?2 AND unvUref = ?3");
};

bool LiteTblIdecRMUsergroupUniversal::loadRec(
			sqlite3_stmt* stmt
			, IdecRMUsergroupUniversal** rec
		) {
	int res;

	IdecRMUsergroupUniversal* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecRMUsergroupUniversal();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 1);
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

ubigint LiteTblIdecRMUsergroupUniversal::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecRMUsergroupUniversal& rst
		) {
	int res; ubigint numread = 0;

	IdecRMUsergroupUniversal* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecRMUsergroupUniversal();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 1);
		rec->unvIxIdecVMaintable = sqlite3_column_int(stmt, 2);
		rec->unvUref = sqlite3_column_int64(stmt, 3);
		rec->ixIdecVAccess = sqlite3_column_int(stmt, 4);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecRMUsergroupUniversal::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecRMUsergroupUniversal** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecRMUsergroupUniversal::loadRecBySQL(
			const string& sqlstr
			, IdecRMUsergroupUniversal** rec
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

ubigint LiteTblIdecRMUsergroupUniversal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecRMUsergroupUniversal& rst
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

void LiteTblIdecRMUsergroupUniversal::insertRec(
			IdecRMUsergroupUniversal* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtInsertRec, 2, rec->unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->unvUref);
	sqlite3_bind_int(stmtInsertRec, 4, rec->ixIdecVAccess);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecRMUsergroupUniversal / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecRMUsergroupUniversal::insertRst(
			ListIdecRMUsergroupUniversal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecRMUsergroupUniversal::updateRec(
			IdecRMUsergroupUniversal* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->unvUref);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->ixIdecVAccess);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecRMUsergroupUniversal / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecRMUsergroupUniversal::updateRst(
			ListIdecRMUsergroupUniversal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecRMUsergroupUniversal::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecRMUsergroupUniversal / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecRMUsergroupUniversal::loadRecByRef(
			ubigint ref
			, IdecRMUsergroupUniversal** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecRMUsergroupUniversal::loadRecByUsgMtbUnv(
			ubigint refIdecMUsergroup
			, uint unvIxIdecVMaintable
			, ubigint unvUref
			, IdecRMUsergroupUniversal** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByUsgMtbUnv, 1, refIdecMUsergroup);
	sqlite3_bind_int(stmtLoadRecByUsgMtbUnv, 2, unvIxIdecVMaintable);
	sqlite3_bind_int64(stmtLoadRecByUsgMtbUnv, 3, unvUref);

	return loadRecByStmt(stmtLoadRecByUsgMtbUnv, rec);
};

