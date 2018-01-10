/**
  * \file IdecRMUserMUsergroup.cpp
  * database access for table TblIdecRMUserMUsergroup (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecRMUserMUsergroup.h"

/******************************************************************************
 class IdecRMUserMUsergroup
 ******************************************************************************/

IdecRMUserMUsergroup::IdecRMUserMUsergroup(
			const ubigint ref
			, const ubigint refIdecMUser
			, const ubigint refIdecMUsergroup
			, const uint ixIdecVUserlevel
		) {

	this->ref = ref;
	this->refIdecMUser = refIdecMUser;
	this->refIdecMUsergroup = refIdecMUsergroup;
	this->ixIdecVUserlevel = ixIdecVUserlevel;
};

bool IdecRMUserMUsergroup::operator==(
			const IdecRMUserMUsergroup& comp
		) {
	return false;
};

bool IdecRMUserMUsergroup::operator!=(
			const IdecRMUserMUsergroup& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecRMUserMUsergroup
 ******************************************************************************/

ListIdecRMUserMUsergroup::ListIdecRMUserMUsergroup() {
};

ListIdecRMUserMUsergroup::ListIdecRMUserMUsergroup(
			const ListIdecRMUserMUsergroup& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecRMUserMUsergroup(*(src.nodes[i]));
};

ListIdecRMUserMUsergroup::~ListIdecRMUserMUsergroup() {
	clear();
};

void ListIdecRMUserMUsergroup::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecRMUserMUsergroup::size() const {
	return(nodes.size());
};

void ListIdecRMUserMUsergroup::append(
			IdecRMUserMUsergroup* rec
		) {
	nodes.push_back(rec);
};

IdecRMUserMUsergroup* ListIdecRMUserMUsergroup::operator[](
			const uint ix
		) {
	IdecRMUserMUsergroup* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecRMUserMUsergroup& ListIdecRMUserMUsergroup::operator=(
			const ListIdecRMUserMUsergroup& src
		) {
	IdecRMUserMUsergroup* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecRMUserMUsergroup(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecRMUserMUsergroup::operator==(
			const ListIdecRMUserMUsergroup& comp
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

bool ListIdecRMUserMUsergroup::operator!=(
			const ListIdecRMUserMUsergroup& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecRMUserMUsergroup
 ******************************************************************************/

TblIdecRMUserMUsergroup::TblIdecRMUserMUsergroup() {
};

TblIdecRMUserMUsergroup::~TblIdecRMUserMUsergroup() {
};

bool TblIdecRMUserMUsergroup::loadRecBySQL(
			const string& sqlstr
			, IdecRMUserMUsergroup** rec
		) {
	return false;
};

ubigint TblIdecRMUserMUsergroup::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	return 0;
};

void TblIdecRMUserMUsergroup::insertRec(
			IdecRMUserMUsergroup* rec
		) {
};

ubigint TblIdecRMUserMUsergroup::insertNewRec(
			IdecRMUserMUsergroup** rec
			, const ubigint refIdecMUser
			, const ubigint refIdecMUsergroup
			, const uint ixIdecVUserlevel
		) {
	ubigint retval = 0;
	IdecRMUserMUsergroup* _rec = NULL;

	_rec = new IdecRMUserMUsergroup(0, refIdecMUser, refIdecMUsergroup, ixIdecVUserlevel);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecRMUserMUsergroup::appendNewRecToRst(
			ListIdecRMUserMUsergroup& rst
			, IdecRMUserMUsergroup** rec
			, const ubigint refIdecMUser
			, const ubigint refIdecMUsergroup
			, const uint ixIdecVUserlevel
		) {
	ubigint retval = 0;
	IdecRMUserMUsergroup* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUser, refIdecMUsergroup, ixIdecVUserlevel);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecRMUserMUsergroup::insertRst(
			ListIdecRMUserMUsergroup& rst
			, bool transact
		) {
};

void TblIdecRMUserMUsergroup::updateRec(
			IdecRMUserMUsergroup* rec
		) {
};

void TblIdecRMUserMUsergroup::updateRst(
			ListIdecRMUserMUsergroup& rst
			, bool transact
		) {
};

void TblIdecRMUserMUsergroup::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecRMUserMUsergroup::loadRecByRef(
			ubigint ref
			, IdecRMUserMUsergroup** rec
		) {
	return false;
};

ubigint TblIdecRMUserMUsergroup::loadRstByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	return 0;
};

ubigint TblIdecRMUserMUsergroup::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	return 0;
};

ubigint TblIdecRMUserMUsergroup::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	ubigint numload = 0;
	IdecRMUserMUsergroup* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecRMUserMUsergroup
 ******************************************************************************/

LiteTblIdecRMUserMUsergroup::LiteTblIdecRMUserMUsergroup() : TblIdecRMUserMUsergroup(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRstByUsg = NULL;
	stmtLoadRstByUsr = NULL;
};

LiteTblIdecRMUserMUsergroup::~LiteTblIdecRMUserMUsergroup() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRstByUsg) sqlite3_finalize(stmtLoadRstByUsg);
	if (stmtLoadRstByUsr) sqlite3_finalize(stmtLoadRstByUsr);
};

void LiteTblIdecRMUserMUsergroup::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecRMUserMUsergroup (refIdecMUser, refIdecMUsergroup, ixIdecVUserlevel) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecRMUserMUsergroup SET refIdecMUser = ?1, refIdecMUsergroup = ?2, ixIdecVUserlevel = ?3 WHERE ref = ?4");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecRMUserMUsergroup WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUser, refIdecMUsergroup, ixIdecVUserlevel FROM TblIdecRMUserMUsergroup WHERE ref = ?1");
	stmtLoadRstByUsg = createStatement("SELECT ref, refIdecMUser, refIdecMUsergroup, ixIdecVUserlevel FROM TblIdecRMUserMUsergroup WHERE refIdecMUsergroup = ?1");
	stmtLoadRstByUsr = createStatement("SELECT ref, refIdecMUser, refIdecMUsergroup, ixIdecVUserlevel FROM TblIdecRMUserMUsergroup WHERE refIdecMUser = ?1");
};

bool LiteTblIdecRMUserMUsergroup::loadRec(
			sqlite3_stmt* stmt
			, IdecRMUserMUsergroup** rec
		) {
	int res;

	IdecRMUserMUsergroup* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecRMUserMUsergroup();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		_rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 2);
		_rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 3);

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

ubigint LiteTblIdecRMUserMUsergroup::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	int res; ubigint numread = 0;

	IdecRMUserMUsergroup* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecRMUserMUsergroup();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUser = sqlite3_column_int64(stmt, 1);
		rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 2);
		rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 3);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecRMUserMUsergroup::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecRMUserMUsergroup** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecRMUserMUsergroup::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecRMUserMUsergroup::loadRecBySQL(
			const string& sqlstr
			, IdecRMUserMUsergroup** rec
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

ubigint LiteTblIdecRMUserMUsergroup::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecRMUserMUsergroup& rst
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

void LiteTblIdecRMUserMUsergroup::insertRec(
			IdecRMUserMUsergroup* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUser);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtInsertRec, 3, rec->ixIdecVUserlevel);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecRMUserMUsergroup / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecRMUserMUsergroup::insertRst(
			ListIdecRMUserMUsergroup& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecRMUserMUsergroup::updateRec(
			IdecRMUserMUsergroup* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUser);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->ixIdecVUserlevel);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecRMUserMUsergroup / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecRMUserMUsergroup::updateRst(
			ListIdecRMUserMUsergroup& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecRMUserMUsergroup::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecRMUserMUsergroup / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecRMUserMUsergroup::loadRecByRef(
			ubigint ref
			, IdecRMUserMUsergroup** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

ubigint LiteTblIdecRMUserMUsergroup::loadRstByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsg, 1, refIdecMUsergroup);

	return loadRstByStmt(stmtLoadRstByUsg, append, rst);
};

ubigint LiteTblIdecRMUserMUsergroup::loadRstByUsr(
			ubigint refIdecMUser
			, const bool append
			, ListIdecRMUserMUsergroup& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsr, 1, refIdecMUser);

	return loadRstByStmt(stmtLoadRstByUsr, append, rst);
};

