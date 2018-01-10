/**
  * \file IdecJAVKeylistKey.cpp
  * database access for table TblIdecJAVKeylistKey (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecJAVKeylistKey.h"

/******************************************************************************
 class IdecJAVKeylistKey
 ******************************************************************************/

IdecJAVKeylistKey::IdecJAVKeylistKey(
			const ubigint ref
			, const ubigint refIdecAVKeylistKey
			, const uint x1IxIdecVLocale
			, const string Title
			, const string Comment
		) {

	this->ref = ref;
	this->refIdecAVKeylistKey = refIdecAVKeylistKey;
	this->x1IxIdecVLocale = x1IxIdecVLocale;
	this->Title = Title;
	this->Comment = Comment;
};

bool IdecJAVKeylistKey::operator==(
			const IdecJAVKeylistKey& comp
		) {
	return false;
};

bool IdecJAVKeylistKey::operator!=(
			const IdecJAVKeylistKey& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecJAVKeylistKey
 ******************************************************************************/

ListIdecJAVKeylistKey::ListIdecJAVKeylistKey() {
};

ListIdecJAVKeylistKey::ListIdecJAVKeylistKey(
			const ListIdecJAVKeylistKey& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecJAVKeylistKey(*(src.nodes[i]));
};

ListIdecJAVKeylistKey::~ListIdecJAVKeylistKey() {
	clear();
};

void ListIdecJAVKeylistKey::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecJAVKeylistKey::size() const {
	return(nodes.size());
};

void ListIdecJAVKeylistKey::append(
			IdecJAVKeylistKey* rec
		) {
	nodes.push_back(rec);
};

IdecJAVKeylistKey* ListIdecJAVKeylistKey::operator[](
			const uint ix
		) {
	IdecJAVKeylistKey* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecJAVKeylistKey& ListIdecJAVKeylistKey::operator=(
			const ListIdecJAVKeylistKey& src
		) {
	IdecJAVKeylistKey* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecJAVKeylistKey(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecJAVKeylistKey::operator==(
			const ListIdecJAVKeylistKey& comp
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

bool ListIdecJAVKeylistKey::operator!=(
			const ListIdecJAVKeylistKey& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecJAVKeylistKey
 ******************************************************************************/

TblIdecJAVKeylistKey::TblIdecJAVKeylistKey() {
};

TblIdecJAVKeylistKey::~TblIdecJAVKeylistKey() {
};

bool TblIdecJAVKeylistKey::loadRecBySQL(
			const string& sqlstr
			, IdecJAVKeylistKey** rec
		) {
	return false;
};

ubigint TblIdecJAVKeylistKey::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecJAVKeylistKey& rst
		) {
	return 0;
};

void TblIdecJAVKeylistKey::insertRec(
			IdecJAVKeylistKey* rec
		) {
};

ubigint TblIdecJAVKeylistKey::insertNewRec(
			IdecJAVKeylistKey** rec
			, const ubigint refIdecAVKeylistKey
			, const uint x1IxIdecVLocale
			, const string Title
			, const string Comment
		) {
	ubigint retval = 0;
	IdecJAVKeylistKey* _rec = NULL;

	_rec = new IdecJAVKeylistKey(0, refIdecAVKeylistKey, x1IxIdecVLocale, Title, Comment);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecJAVKeylistKey::appendNewRecToRst(
			ListIdecJAVKeylistKey& rst
			, IdecJAVKeylistKey** rec
			, const ubigint refIdecAVKeylistKey
			, const uint x1IxIdecVLocale
			, const string Title
			, const string Comment
		) {
	ubigint retval = 0;
	IdecJAVKeylistKey* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecAVKeylistKey, x1IxIdecVLocale, Title, Comment);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecJAVKeylistKey::insertRst(
			ListIdecJAVKeylistKey& rst
			, bool transact
		) {
};

void TblIdecJAVKeylistKey::updateRec(
			IdecJAVKeylistKey* rec
		) {
};

void TblIdecJAVKeylistKey::updateRst(
			ListIdecJAVKeylistKey& rst
			, bool transact
		) {
};

void TblIdecJAVKeylistKey::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecJAVKeylistKey::loadRecByRef(
			ubigint ref
			, IdecJAVKeylistKey** rec
		) {
	return false;
};

bool TblIdecJAVKeylistKey::loadRecByKlkLcl(
			ubigint refIdecAVKeylistKey
			, uint x1IxIdecVLocale
			, IdecJAVKeylistKey** rec
		) {
	return false;
};

ubigint TblIdecJAVKeylistKey::loadRefsByKlk(
			ubigint refIdecAVKeylistKey
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

bool TblIdecJAVKeylistKey::loadTitByKlkLcl(
			ubigint refIdecAVKeylistKey
			, uint x1IxIdecVLocale
			, string& Title
		) {
	return false;
};

ubigint TblIdecJAVKeylistKey::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecJAVKeylistKey& rst
		) {
	ubigint numload = 0;
	IdecJAVKeylistKey* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecJAVKeylistKey
 ******************************************************************************/

LiteTblIdecJAVKeylistKey::LiteTblIdecJAVKeylistKey() : TblIdecJAVKeylistKey(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByKlkLcl = NULL;
	stmtLoadRefsByKlk = NULL;
	stmtLoadTitByKlkLcl = NULL;
};

LiteTblIdecJAVKeylistKey::~LiteTblIdecJAVKeylistKey() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByKlkLcl) sqlite3_finalize(stmtLoadRecByKlkLcl);
	if (stmtLoadRefsByKlk) sqlite3_finalize(stmtLoadRefsByKlk);
	if (stmtLoadTitByKlkLcl) sqlite3_finalize(stmtLoadTitByKlkLcl);
};

void LiteTblIdecJAVKeylistKey::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecJAVKeylistKey (refIdecAVKeylistKey, x1IxIdecVLocale, Title, Comment) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecJAVKeylistKey SET refIdecAVKeylistKey = ?1, x1IxIdecVLocale = ?2, Title = ?3, Comment = ?4 WHERE ref = ?5");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecJAVKeylistKey WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecAVKeylistKey, x1IxIdecVLocale, Title, Comment FROM TblIdecJAVKeylistKey WHERE ref = ?1");
	stmtLoadRecByKlkLcl = createStatement("SELECT ref, refIdecAVKeylistKey, x1IxIdecVLocale, Title, Comment FROM TblIdecJAVKeylistKey WHERE refIdecAVKeylistKey = ?1 AND x1IxIdecVLocale = ?2");
	stmtLoadRefsByKlk = createStatement("SELECT ref FROM TblIdecJAVKeylistKey WHERE refIdecAVKeylistKey = ?1");
	stmtLoadTitByKlkLcl = createStatement("SELECT Title FROM TblIdecJAVKeylistKey WHERE refIdecAVKeylistKey = ?1 AND x1IxIdecVLocale = ?2");
};

bool LiteTblIdecJAVKeylistKey::loadRec(
			sqlite3_stmt* stmt
			, IdecJAVKeylistKey** rec
		) {
	int res;

	IdecJAVKeylistKey* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecJAVKeylistKey();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecAVKeylistKey = sqlite3_column_int64(stmt, 1);
		_rec->x1IxIdecVLocale = sqlite3_column_int(stmt, 2);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 3));
		_rec->Comment.assign((const char*) sqlite3_column_text(stmt, 4));

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

ubigint LiteTblIdecJAVKeylistKey::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecJAVKeylistKey& rst
		) {
	int res; ubigint numread = 0;

	IdecJAVKeylistKey* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecJAVKeylistKey();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecAVKeylistKey = sqlite3_column_int64(stmt, 1);
		rec->x1IxIdecVLocale = sqlite3_column_int(stmt, 2);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 3));
		rec->Comment.assign((const char*) sqlite3_column_text(stmt, 4));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecJAVKeylistKey::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecJAVKeylistKey** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecJAVKeylistKey::loadRecBySQL(
			const string& sqlstr
			, IdecJAVKeylistKey** rec
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

ubigint LiteTblIdecJAVKeylistKey::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecJAVKeylistKey& rst
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

void LiteTblIdecJAVKeylistKey::insertRec(
			IdecJAVKeylistKey* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecAVKeylistKey);
	sqlite3_bind_int(stmtInsertRec, 2, rec->x1IxIdecVLocale);
	sqlite3_bind_text(stmtInsertRec, 3, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJAVKeylistKey / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecJAVKeylistKey::insertRst(
			ListIdecJAVKeylistKey& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecJAVKeylistKey::updateRec(
			IdecJAVKeylistKey* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecAVKeylistKey);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->x1IxIdecVLocale);
	sqlite3_bind_text(stmtUpdateRec, 3, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJAVKeylistKey / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecJAVKeylistKey::updateRst(
			ListIdecJAVKeylistKey& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecJAVKeylistKey::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJAVKeylistKey / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecJAVKeylistKey::loadRecByRef(
			ubigint ref
			, IdecJAVKeylistKey** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecJAVKeylistKey::loadRecByKlkLcl(
			ubigint refIdecAVKeylistKey
			, uint x1IxIdecVLocale
			, IdecJAVKeylistKey** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByKlkLcl, 1, refIdecAVKeylistKey);
	sqlite3_bind_int(stmtLoadRecByKlkLcl, 2, x1IxIdecVLocale);

	return loadRecByStmt(stmtLoadRecByKlkLcl, rec);
};

ubigint LiteTblIdecJAVKeylistKey::loadRefsByKlk(
			ubigint refIdecAVKeylistKey
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByKlk, 1, refIdecAVKeylistKey);

	return loadRefsByStmt(stmtLoadRefsByKlk, append, refs);
};

bool LiteTblIdecJAVKeylistKey::loadTitByKlkLcl(
			ubigint refIdecAVKeylistKey
			, uint x1IxIdecVLocale
			, string& Title
		) {
	sqlite3_bind_int64(stmtLoadTitByKlkLcl, 1, refIdecAVKeylistKey);
	sqlite3_bind_int(stmtLoadTitByKlkLcl, 2, x1IxIdecVLocale);

	return loadStringByStmt(stmtLoadTitByKlkLcl, Title);
};

