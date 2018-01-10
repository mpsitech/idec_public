/**
  * \file IdecAMUsergroupAccess.cpp
  * database access for table TblIdecAMUsergroupAccess (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAMUsergroupAccess.h"

/******************************************************************************
 class IdecAMUsergroupAccess
 ******************************************************************************/

IdecAMUsergroupAccess::IdecAMUsergroupAccess(
			const ubigint ref
			, const ubigint refIdecMUsergroup
			, const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) {

	this->ref = ref;
	this->refIdecMUsergroup = refIdecMUsergroup;
	this->x1IxIdecVCard = x1IxIdecVCard;
	this->ixIdecWUiaccess = ixIdecWUiaccess;
};

bool IdecAMUsergroupAccess::operator==(
			const IdecAMUsergroupAccess& comp
		) {
	return false;
};

bool IdecAMUsergroupAccess::operator!=(
			const IdecAMUsergroupAccess& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAMUsergroupAccess
 ******************************************************************************/

ListIdecAMUsergroupAccess::ListIdecAMUsergroupAccess() {
};

ListIdecAMUsergroupAccess::ListIdecAMUsergroupAccess(
			const ListIdecAMUsergroupAccess& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAMUsergroupAccess(*(src.nodes[i]));
};

ListIdecAMUsergroupAccess::~ListIdecAMUsergroupAccess() {
	clear();
};

void ListIdecAMUsergroupAccess::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAMUsergroupAccess::size() const {
	return(nodes.size());
};

void ListIdecAMUsergroupAccess::append(
			IdecAMUsergroupAccess* rec
		) {
	nodes.push_back(rec);
};

IdecAMUsergroupAccess* ListIdecAMUsergroupAccess::operator[](
			const uint ix
		) {
	IdecAMUsergroupAccess* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAMUsergroupAccess& ListIdecAMUsergroupAccess::operator=(
			const ListIdecAMUsergroupAccess& src
		) {
	IdecAMUsergroupAccess* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAMUsergroupAccess(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAMUsergroupAccess::operator==(
			const ListIdecAMUsergroupAccess& comp
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

bool ListIdecAMUsergroupAccess::operator!=(
			const ListIdecAMUsergroupAccess& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAMUsergroupAccess
 ******************************************************************************/

TblIdecAMUsergroupAccess::TblIdecAMUsergroupAccess() {
};

TblIdecAMUsergroupAccess::~TblIdecAMUsergroupAccess() {
};

bool TblIdecAMUsergroupAccess::loadRecBySQL(
			const string& sqlstr
			, IdecAMUsergroupAccess** rec
		) {
	return false;
};

ubigint TblIdecAMUsergroupAccess::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAMUsergroupAccess& rst
		) {
	return 0;
};

void TblIdecAMUsergroupAccess::insertRec(
			IdecAMUsergroupAccess* rec
		) {
};

ubigint TblIdecAMUsergroupAccess::insertNewRec(
			IdecAMUsergroupAccess** rec
			, const ubigint refIdecMUsergroup
			, const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) {
	ubigint retval = 0;
	IdecAMUsergroupAccess* _rec = NULL;

	_rec = new IdecAMUsergroupAccess(0, refIdecMUsergroup, x1IxIdecVCard, ixIdecWUiaccess);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAMUsergroupAccess::appendNewRecToRst(
			ListIdecAMUsergroupAccess& rst
			, IdecAMUsergroupAccess** rec
			, const ubigint refIdecMUsergroup
			, const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) {
	ubigint retval = 0;
	IdecAMUsergroupAccess* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMUsergroup, x1IxIdecVCard, ixIdecWUiaccess);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAMUsergroupAccess::insertRst(
			ListIdecAMUsergroupAccess& rst
			, bool transact
		) {
};

void TblIdecAMUsergroupAccess::updateRec(
			IdecAMUsergroupAccess* rec
		) {
};

void TblIdecAMUsergroupAccess::updateRst(
			ListIdecAMUsergroupAccess& rst
			, bool transact
		) {
};

void TblIdecAMUsergroupAccess::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAMUsergroupAccess::loadRecByRef(
			ubigint ref
			, IdecAMUsergroupAccess** rec
		) {
	return false;
};

bool TblIdecAMUsergroupAccess::loadRecByUsgCrd(
			ubigint refIdecMUsergroup
			, uint x1IxIdecVCard
			, IdecAMUsergroupAccess** rec
		) {
	return false;
};

ubigint TblIdecAMUsergroupAccess::loadRefsByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

ubigint TblIdecAMUsergroupAccess::loadRstByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, ListIdecAMUsergroupAccess& rst
		) {
	return 0;
};

ubigint TblIdecAMUsergroupAccess::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAMUsergroupAccess& rst
		) {
	ubigint numload = 0;
	IdecAMUsergroupAccess* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAMUsergroupAccess
 ******************************************************************************/

LiteTblIdecAMUsergroupAccess::LiteTblIdecAMUsergroupAccess() : TblIdecAMUsergroupAccess(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByUsgCrd = NULL;
	stmtLoadRefsByUsg = NULL;
	stmtLoadRstByUsg = NULL;
};

LiteTblIdecAMUsergroupAccess::~LiteTblIdecAMUsergroupAccess() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByUsgCrd) sqlite3_finalize(stmtLoadRecByUsgCrd);
	if (stmtLoadRefsByUsg) sqlite3_finalize(stmtLoadRefsByUsg);
	if (stmtLoadRstByUsg) sqlite3_finalize(stmtLoadRstByUsg);
};

void LiteTblIdecAMUsergroupAccess::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAMUsergroupAccess (refIdecMUsergroup, x1IxIdecVCard, ixIdecWUiaccess) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAMUsergroupAccess SET refIdecMUsergroup = ?1, x1IxIdecVCard = ?2, ixIdecWUiaccess = ?3 WHERE ref = ?4");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAMUsergroupAccess WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMUsergroup, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecAMUsergroupAccess WHERE ref = ?1");
	stmtLoadRecByUsgCrd = createStatement("SELECT ref, refIdecMUsergroup, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecAMUsergroupAccess WHERE refIdecMUsergroup = ?1 AND x1IxIdecVCard = ?2");
	stmtLoadRefsByUsg = createStatement("SELECT ref FROM TblIdecAMUsergroupAccess WHERE refIdecMUsergroup = ?1");
	stmtLoadRstByUsg = createStatement("SELECT ref, refIdecMUsergroup, x1IxIdecVCard, ixIdecWUiaccess FROM TblIdecAMUsergroupAccess WHERE refIdecMUsergroup = ?1 ORDER BY x1IxIdecVCard ASC");
};

bool LiteTblIdecAMUsergroupAccess::loadRec(
			sqlite3_stmt* stmt
			, IdecAMUsergroupAccess** rec
		) {
	int res;

	IdecAMUsergroupAccess* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAMUsergroupAccess();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 1);
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

ubigint LiteTblIdecAMUsergroupAccess::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAMUsergroupAccess& rst
		) {
	int res; ubigint numread = 0;

	IdecAMUsergroupAccess* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAMUsergroupAccess();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 1);
		rec->x1IxIdecVCard = sqlite3_column_int(stmt, 2);
		rec->ixIdecWUiaccess = sqlite3_column_int(stmt, 3);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAMUsergroupAccess::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAMUsergroupAccess** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecAMUsergroupAccess::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAMUsergroupAccess& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAMUsergroupAccess::loadRecBySQL(
			const string& sqlstr
			, IdecAMUsergroupAccess** rec
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

ubigint LiteTblIdecAMUsergroupAccess::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAMUsergroupAccess& rst
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

void LiteTblIdecAMUsergroupAccess::insertRec(
			IdecAMUsergroupAccess* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtInsertRec, 2, rec->x1IxIdecVCard);
	sqlite3_bind_int(stmtInsertRec, 3, rec->ixIdecWUiaccess);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMUsergroupAccess / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAMUsergroupAccess::insertRst(
			ListIdecAMUsergroupAccess& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAMUsergroupAccess::updateRec(
			IdecAMUsergroupAccess* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMUsergroup);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->x1IxIdecVCard);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->ixIdecWUiaccess);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMUsergroupAccess / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAMUsergroupAccess::updateRst(
			ListIdecAMUsergroupAccess& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAMUsergroupAccess::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAMUsergroupAccess / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAMUsergroupAccess::loadRecByRef(
			ubigint ref
			, IdecAMUsergroupAccess** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecAMUsergroupAccess::loadRecByUsgCrd(
			ubigint refIdecMUsergroup
			, uint x1IxIdecVCard
			, IdecAMUsergroupAccess** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByUsgCrd, 1, refIdecMUsergroup);
	sqlite3_bind_int(stmtLoadRecByUsgCrd, 2, x1IxIdecVCard);

	return loadRecByStmt(stmtLoadRecByUsgCrd, rec);
};

ubigint LiteTblIdecAMUsergroupAccess::loadRefsByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByUsg, 1, refIdecMUsergroup);

	return loadRefsByStmt(stmtLoadRefsByUsg, append, refs);
};

ubigint LiteTblIdecAMUsergroupAccess::loadRstByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, ListIdecAMUsergroupAccess& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByUsg, 1, refIdecMUsergroup);

	return loadRstByStmt(stmtLoadRstByUsg, append, rst);
};

