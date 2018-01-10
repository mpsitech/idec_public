/**
  * \file IdecMUsergroup.cpp
  * database access for table TblIdecMUsergroup (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMUsergroup.h"

/******************************************************************************
 class IdecMUsergroup
 ******************************************************************************/

IdecMUsergroup::IdecMUsergroup(
			const ubigint ref
			, const ubigint grp
			, const ubigint own
			, const string sref
			, const string Comment
		) {

	this->ref = ref;
	this->grp = grp;
	this->own = own;
	this->sref = sref;
	this->Comment = Comment;
};

bool IdecMUsergroup::operator==(
			const IdecMUsergroup& comp
		) {
	return false;
};

bool IdecMUsergroup::operator!=(
			const IdecMUsergroup& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMUsergroup
 ******************************************************************************/

ListIdecMUsergroup::ListIdecMUsergroup() {
};

ListIdecMUsergroup::ListIdecMUsergroup(
			const ListIdecMUsergroup& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMUsergroup(*(src.nodes[i]));
};

ListIdecMUsergroup::~ListIdecMUsergroup() {
	clear();
};

void ListIdecMUsergroup::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMUsergroup::size() const {
	return(nodes.size());
};

void ListIdecMUsergroup::append(
			IdecMUsergroup* rec
		) {
	nodes.push_back(rec);
};

IdecMUsergroup* ListIdecMUsergroup::operator[](
			const uint ix
		) {
	IdecMUsergroup* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMUsergroup& ListIdecMUsergroup::operator=(
			const ListIdecMUsergroup& src
		) {
	IdecMUsergroup* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMUsergroup(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMUsergroup::operator==(
			const ListIdecMUsergroup& comp
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

bool ListIdecMUsergroup::operator!=(
			const ListIdecMUsergroup& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMUsergroup
 ******************************************************************************/

TblIdecMUsergroup::TblIdecMUsergroup() {
};

TblIdecMUsergroup::~TblIdecMUsergroup() {
};

bool TblIdecMUsergroup::loadRecBySQL(
			const string& sqlstr
			, IdecMUsergroup** rec
		) {
	return false;
};

ubigint TblIdecMUsergroup::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMUsergroup& rst
		) {
	return 0;
};

void TblIdecMUsergroup::insertRec(
			IdecMUsergroup* rec
		) {
};

ubigint TblIdecMUsergroup::insertNewRec(
			IdecMUsergroup** rec
			, const ubigint grp
			, const ubigint own
			, const string sref
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMUsergroup* _rec = NULL;

	_rec = new IdecMUsergroup(0, grp, own, sref, Comment);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMUsergroup::appendNewRecToRst(
			ListIdecMUsergroup& rst
			, IdecMUsergroup** rec
			, const ubigint grp
			, const ubigint own
			, const string sref
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMUsergroup* _rec = NULL;

	retval = insertNewRec(&_rec, grp, own, sref, Comment);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMUsergroup::insertRst(
			ListIdecMUsergroup& rst
			, bool transact
		) {
};

void TblIdecMUsergroup::updateRec(
			IdecMUsergroup* rec
		) {
};

void TblIdecMUsergroup::updateRst(
			ListIdecMUsergroup& rst
			, bool transact
		) {
};

void TblIdecMUsergroup::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMUsergroup::loadRecByRef(
			ubigint ref
			, IdecMUsergroup** rec
		) {
	return false;
};

bool TblIdecMUsergroup::loadRecBySrf(
			string sref
			, IdecMUsergroup** rec
		) {
	return false;
};

bool TblIdecMUsergroup::loadRefBySrf(
			string sref
			, ubigint& ref
		) {
	return false;
};

bool TblIdecMUsergroup::loadSrfByRef(
			ubigint ref
			, string& sref
		) {
	return false;
};

ubigint TblIdecMUsergroup::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMUsergroup& rst
		) {
	ubigint numload = 0;
	IdecMUsergroup* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMUsergroup
 ******************************************************************************/

LiteTblIdecMUsergroup::LiteTblIdecMUsergroup() : TblIdecMUsergroup(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecBySrf = NULL;
	stmtLoadRefBySrf = NULL;
	stmtLoadSrfByRef = NULL;
};

LiteTblIdecMUsergroup::~LiteTblIdecMUsergroup() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecBySrf) sqlite3_finalize(stmtLoadRecBySrf);
	if (stmtLoadRefBySrf) sqlite3_finalize(stmtLoadRefBySrf);
	if (stmtLoadSrfByRef) sqlite3_finalize(stmtLoadSrfByRef);
};

void LiteTblIdecMUsergroup::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMUsergroup (grp, own, sref, Comment) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMUsergroup SET grp = ?1, own = ?2, sref = ?3, Comment = ?4 WHERE ref = ?5");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMUsergroup WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, grp, own, sref, Comment FROM TblIdecMUsergroup WHERE ref = ?1");
	stmtLoadRecBySrf = createStatement("SELECT ref, grp, own, sref, Comment FROM TblIdecMUsergroup WHERE sref = ?1");
	stmtLoadRefBySrf = createStatement("SELECT ref FROM TblIdecMUsergroup WHERE sref = ?1");
	stmtLoadSrfByRef = createStatement("SELECT sref FROM TblIdecMUsergroup WHERE ref = ?1");
};

bool LiteTblIdecMUsergroup::loadRec(
			sqlite3_stmt* stmt
			, IdecMUsergroup** rec
		) {
	int res;

	IdecMUsergroup* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMUsergroup();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->grp = sqlite3_column_int64(stmt, 1);
		_rec->own = sqlite3_column_int64(stmt, 2);
		_rec->sref.assign((const char*) sqlite3_column_text(stmt, 3));
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

ubigint LiteTblIdecMUsergroup::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMUsergroup& rst
		) {
	int res; ubigint numread = 0;

	IdecMUsergroup* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMUsergroup();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->grp = sqlite3_column_int64(stmt, 1);
		rec->own = sqlite3_column_int64(stmt, 2);
		rec->sref.assign((const char*) sqlite3_column_text(stmt, 3));
		rec->Comment.assign((const char*) sqlite3_column_text(stmt, 4));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMUsergroup::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMUsergroup** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMUsergroup::loadRecBySQL(
			const string& sqlstr
			, IdecMUsergroup** rec
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

ubigint LiteTblIdecMUsergroup::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMUsergroup& rst
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

void LiteTblIdecMUsergroup::insertRec(
			IdecMUsergroup* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->grp);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->own);
	sqlite3_bind_text(stmtInsertRec, 3, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMUsergroup / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMUsergroup::insertRst(
			ListIdecMUsergroup& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMUsergroup::updateRec(
			IdecMUsergroup* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->grp);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->own);
	sqlite3_bind_text(stmtUpdateRec, 3, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMUsergroup / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMUsergroup::updateRst(
			ListIdecMUsergroup& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMUsergroup::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMUsergroup / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMUsergroup::loadRecByRef(
			ubigint ref
			, IdecMUsergroup** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecMUsergroup::loadRecBySrf(
			string sref
			, IdecMUsergroup** rec
		) {
	sqlite3_bind_text(stmtLoadRecBySrf, 1, sref.c_str(), sref.length(), SQLITE_STATIC);

	return loadRecByStmt(stmtLoadRecBySrf, rec);
};

bool LiteTblIdecMUsergroup::loadRefBySrf(
			string sref
			, ubigint& ref
		) {
	sqlite3_bind_text(stmtLoadRefBySrf, 1, sref.c_str(), sref.length(), SQLITE_STATIC);

	return loadRefByStmt(stmtLoadRefBySrf, ref);
};

bool LiteTblIdecMUsergroup::loadSrfByRef(
			ubigint ref
			, string& sref
		) {
	sqlite3_bind_int64(stmtLoadSrfByRef, 1, ref);

	return loadStringByStmt(stmtLoadSrfByRef, sref);
};

