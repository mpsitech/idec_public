/**
  * \file IdecMMission.cpp
  * database access for table TblIdecMMission (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMMission.h"

/******************************************************************************
 class IdecMMission
 ******************************************************************************/

IdecMMission::IdecMMission(
			const ubigint ref
			, const ubigint grp
			, const ubigint own
			, const string Title
			, const uint startd
			, const uint stopd
			, const string srefKCountry
			, const string Region
			, const string Municipality
			, const string Comment
		) {

	this->ref = ref;
	this->grp = grp;
	this->own = own;
	this->Title = Title;
	this->startd = startd;
	this->stopd = stopd;
	this->srefKCountry = srefKCountry;
	this->Region = Region;
	this->Municipality = Municipality;
	this->Comment = Comment;
};

bool IdecMMission::operator==(
			const IdecMMission& comp
		) {
	return false;
};

bool IdecMMission::operator!=(
			const IdecMMission& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMMission
 ******************************************************************************/

ListIdecMMission::ListIdecMMission() {
};

ListIdecMMission::ListIdecMMission(
			const ListIdecMMission& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMMission(*(src.nodes[i]));
};

ListIdecMMission::~ListIdecMMission() {
	clear();
};

void ListIdecMMission::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMMission::size() const {
	return(nodes.size());
};

void ListIdecMMission::append(
			IdecMMission* rec
		) {
	nodes.push_back(rec);
};

IdecMMission* ListIdecMMission::operator[](
			const uint ix
		) {
	IdecMMission* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMMission& ListIdecMMission::operator=(
			const ListIdecMMission& src
		) {
	IdecMMission* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMMission(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMMission::operator==(
			const ListIdecMMission& comp
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

bool ListIdecMMission::operator!=(
			const ListIdecMMission& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMMission
 ******************************************************************************/

TblIdecMMission::TblIdecMMission() {
};

TblIdecMMission::~TblIdecMMission() {
};

bool TblIdecMMission::loadRecBySQL(
			const string& sqlstr
			, IdecMMission** rec
		) {
	return false;
};

ubigint TblIdecMMission::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMMission& rst
		) {
	return 0;
};

void TblIdecMMission::insertRec(
			IdecMMission* rec
		) {
};

ubigint TblIdecMMission::insertNewRec(
			IdecMMission** rec
			, const ubigint grp
			, const ubigint own
			, const string Title
			, const uint startd
			, const uint stopd
			, const string srefKCountry
			, const string Region
			, const string Municipality
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMMission* _rec = NULL;

	_rec = new IdecMMission(0, grp, own, Title, startd, stopd, srefKCountry, Region, Municipality, Comment);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMMission::appendNewRecToRst(
			ListIdecMMission& rst
			, IdecMMission** rec
			, const ubigint grp
			, const ubigint own
			, const string Title
			, const uint startd
			, const uint stopd
			, const string srefKCountry
			, const string Region
			, const string Municipality
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMMission* _rec = NULL;

	retval = insertNewRec(&_rec, grp, own, Title, startd, stopd, srefKCountry, Region, Municipality, Comment);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMMission::insertRst(
			ListIdecMMission& rst
			, bool transact
		) {
};

void TblIdecMMission::updateRec(
			IdecMMission* rec
		) {
};

void TblIdecMMission::updateRst(
			ListIdecMMission& rst
			, bool transact
		) {
};

void TblIdecMMission::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMMission::loadRecByRef(
			ubigint ref
			, IdecMMission** rec
		) {
	return false;
};

bool TblIdecMMission::loadTitByRef(
			ubigint ref
			, string& Title
		) {
	return false;
};

ubigint TblIdecMMission::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMMission& rst
		) {
	ubigint numload = 0;
	IdecMMission* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMMission
 ******************************************************************************/

LiteTblIdecMMission::LiteTblIdecMMission() : TblIdecMMission(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadTitByRef = NULL;
};

LiteTblIdecMMission::~LiteTblIdecMMission() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadTitByRef) sqlite3_finalize(stmtLoadTitByRef);
};

void LiteTblIdecMMission::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMMission (grp, own, Title, startd, stopd, srefKCountry, Region, Municipality, Comment) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMMission SET grp = ?1, own = ?2, Title = ?3, startd = ?4, stopd = ?5, srefKCountry = ?6, Region = ?7, Municipality = ?8, Comment = ?9 WHERE ref = ?10");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMMission WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, grp, own, Title, startd, stopd, srefKCountry, Region, Municipality, Comment FROM TblIdecMMission WHERE ref = ?1");
	stmtLoadTitByRef = createStatement("SELECT Title FROM TblIdecMMission WHERE ref = ?1");
};

bool LiteTblIdecMMission::loadRec(
			sqlite3_stmt* stmt
			, IdecMMission** rec
		) {
	int res;

	IdecMMission* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMMission();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->grp = sqlite3_column_int64(stmt, 1);
		_rec->own = sqlite3_column_int64(stmt, 2);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 3));
		_rec->startd = sqlite3_column_int(stmt, 4);
		_rec->stopd = sqlite3_column_int(stmt, 5);
		_rec->srefKCountry.assign((const char*) sqlite3_column_text(stmt, 6));
		_rec->Region.assign((const char*) sqlite3_column_text(stmt, 7));
		_rec->Municipality.assign((const char*) sqlite3_column_text(stmt, 8));
		_rec->Comment.assign((const char*) sqlite3_column_text(stmt, 9));

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

ubigint LiteTblIdecMMission::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMMission& rst
		) {
	int res; ubigint numread = 0;

	IdecMMission* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMMission();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->grp = sqlite3_column_int64(stmt, 1);
		rec->own = sqlite3_column_int64(stmt, 2);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 3));
		rec->startd = sqlite3_column_int(stmt, 4);
		rec->stopd = sqlite3_column_int(stmt, 5);
		rec->srefKCountry.assign((const char*) sqlite3_column_text(stmt, 6));
		rec->Region.assign((const char*) sqlite3_column_text(stmt, 7));
		rec->Municipality.assign((const char*) sqlite3_column_text(stmt, 8));
		rec->Comment.assign((const char*) sqlite3_column_text(stmt, 9));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMMission::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMMission** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMMission::loadRecBySQL(
			const string& sqlstr
			, IdecMMission** rec
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

ubigint LiteTblIdecMMission::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMMission& rst
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

void LiteTblIdecMMission::insertRec(
			IdecMMission* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->grp);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->own);
	sqlite3_bind_text(stmtInsertRec, 3, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtInsertRec, 4, rec->startd);
	sqlite3_bind_int(stmtInsertRec, 5, rec->stopd);
	sqlite3_bind_text(stmtInsertRec, 6, rec->srefKCountry.c_str(), rec->srefKCountry.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 7, rec->Region.c_str(), rec->Region.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 8, rec->Municipality.c_str(), rec->Municipality.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 9, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMMission / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMMission::insertRst(
			ListIdecMMission& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMMission::updateRec(
			IdecMMission* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->grp);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->own);
	sqlite3_bind_text(stmtUpdateRec, 3, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->startd);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->stopd);
	sqlite3_bind_text(stmtUpdateRec, 6, rec->srefKCountry.c_str(), rec->srefKCountry.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 7, rec->Region.c_str(), rec->Region.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->Municipality.c_str(), rec->Municipality.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 9, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 10, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMMission / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMMission::updateRst(
			ListIdecMMission& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMMission::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMMission / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMMission::loadRecByRef(
			ubigint ref
			, IdecMMission** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecMMission::loadTitByRef(
			ubigint ref
			, string& Title
		) {
	sqlite3_bind_int64(stmtLoadTitByRef, 1, ref);

	return loadStringByStmt(stmtLoadTitByRef, Title);
};

