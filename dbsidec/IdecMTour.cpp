/**
  * \file IdecMTour.cpp
  * database access for table TblIdecMTour (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMTour.h"

/******************************************************************************
 class IdecMTour
 ******************************************************************************/

IdecMTour::IdecMTour(
			const ubigint ref
			, const ubigint refIdecMMission
			, const string Title
			, const uint start
			, const uint stop
			, const string Area
			, const double theta
			, const double phi
			, const string Comment
		) {

	this->ref = ref;
	this->refIdecMMission = refIdecMMission;
	this->Title = Title;
	this->start = start;
	this->stop = stop;
	this->Area = Area;
	this->theta = theta;
	this->phi = phi;
	this->Comment = Comment;
};

bool IdecMTour::operator==(
			const IdecMTour& comp
		) {
	return false;
};

bool IdecMTour::operator!=(
			const IdecMTour& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMTour
 ******************************************************************************/

ListIdecMTour::ListIdecMTour() {
};

ListIdecMTour::ListIdecMTour(
			const ListIdecMTour& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMTour(*(src.nodes[i]));
};

ListIdecMTour::~ListIdecMTour() {
	clear();
};

void ListIdecMTour::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMTour::size() const {
	return(nodes.size());
};

void ListIdecMTour::append(
			IdecMTour* rec
		) {
	nodes.push_back(rec);
};

IdecMTour* ListIdecMTour::operator[](
			const uint ix
		) {
	IdecMTour* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMTour& ListIdecMTour::operator=(
			const ListIdecMTour& src
		) {
	IdecMTour* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMTour(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMTour::operator==(
			const ListIdecMTour& comp
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

bool ListIdecMTour::operator!=(
			const ListIdecMTour& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMTour
 ******************************************************************************/

TblIdecMTour::TblIdecMTour() {
};

TblIdecMTour::~TblIdecMTour() {
};

bool TblIdecMTour::loadRecBySQL(
			const string& sqlstr
			, IdecMTour** rec
		) {
	return false;
};

ubigint TblIdecMTour::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMTour& rst
		) {
	return 0;
};

void TblIdecMTour::insertRec(
			IdecMTour* rec
		) {
};

ubigint TblIdecMTour::insertNewRec(
			IdecMTour** rec
			, const ubigint refIdecMMission
			, const string Title
			, const uint start
			, const uint stop
			, const string Area
			, const double theta
			, const double phi
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMTour* _rec = NULL;

	_rec = new IdecMTour(0, refIdecMMission, Title, start, stop, Area, theta, phi, Comment);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMTour::appendNewRecToRst(
			ListIdecMTour& rst
			, IdecMTour** rec
			, const ubigint refIdecMMission
			, const string Title
			, const uint start
			, const uint stop
			, const string Area
			, const double theta
			, const double phi
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMTour* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMMission, Title, start, stop, Area, theta, phi, Comment);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMTour::insertRst(
			ListIdecMTour& rst
			, bool transact
		) {
};

void TblIdecMTour::updateRec(
			IdecMTour* rec
		) {
};

void TblIdecMTour::updateRst(
			ListIdecMTour& rst
			, bool transact
		) {
};

void TblIdecMTour::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMTour::loadRecByRef(
			ubigint ref
			, IdecMTour** rec
		) {
	return false;
};

ubigint TblIdecMTour::loadRstByMis(
			ubigint refIdecMMission
			, const bool append
			, ListIdecMTour& rst
		) {
	return 0;
};

ubigint TblIdecMTour::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMTour& rst
		) {
	ubigint numload = 0;
	IdecMTour* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMTour
 ******************************************************************************/

LiteTblIdecMTour::LiteTblIdecMTour() : TblIdecMTour(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRstByMis = NULL;
};

LiteTblIdecMTour::~LiteTblIdecMTour() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRstByMis) sqlite3_finalize(stmtLoadRstByMis);
};

void LiteTblIdecMTour::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMTour (refIdecMMission, Title, start, stop, Area, theta, phi, Comment) VALUES (?1,?2,?3,?4,?5,?6,?7,?8)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMTour SET refIdecMMission = ?1, Title = ?2, start = ?3, stop = ?4, Area = ?5, theta = ?6, phi = ?7, Comment = ?8 WHERE ref = ?9");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMTour WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMMission, Title, start, stop, Area, theta, phi, Comment FROM TblIdecMTour WHERE ref = ?1");
	stmtLoadRstByMis = createStatement("SELECT ref, refIdecMMission, Title, start, stop, Area, theta, phi, Comment FROM TblIdecMTour WHERE refIdecMMission = ?1 ORDER BY Title ASC");
};

bool LiteTblIdecMTour::loadRec(
			sqlite3_stmt* stmt
			, IdecMTour** rec
		) {
	int res;

	IdecMTour* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMTour();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMMission = sqlite3_column_int64(stmt, 1);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 2));
		_rec->start = sqlite3_column_int(stmt, 3);
		_rec->stop = sqlite3_column_int(stmt, 4);
		_rec->Area.assign((const char*) sqlite3_column_text(stmt, 5));
		_rec->theta = sqlite3_column_double(stmt, 6);
		_rec->phi = sqlite3_column_double(stmt, 7);
		_rec->Comment.assign((const char*) sqlite3_column_text(stmt, 8));

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

ubigint LiteTblIdecMTour::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMTour& rst
		) {
	int res; ubigint numread = 0;

	IdecMTour* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMTour();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMMission = sqlite3_column_int64(stmt, 1);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 2));
		rec->start = sqlite3_column_int(stmt, 3);
		rec->stop = sqlite3_column_int(stmt, 4);
		rec->Area.assign((const char*) sqlite3_column_text(stmt, 5));
		rec->theta = sqlite3_column_double(stmt, 6);
		rec->phi = sqlite3_column_double(stmt, 7);
		rec->Comment.assign((const char*) sqlite3_column_text(stmt, 8));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMTour::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMTour** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecMTour::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMTour& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMTour::loadRecBySQL(
			const string& sqlstr
			, IdecMTour** rec
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

ubigint LiteTblIdecMTour::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMTour& rst
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

void LiteTblIdecMTour::insertRec(
			IdecMTour* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMMission);
	sqlite3_bind_text(stmtInsertRec, 2, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtInsertRec, 3, rec->start);
	sqlite3_bind_int(stmtInsertRec, 4, rec->stop);
	sqlite3_bind_text(stmtInsertRec, 5, rec->Area.c_str(), rec->Area.length(), SQLITE_STATIC);
	sqlite3_bind_double(stmtInsertRec, 6, rec->theta);
	sqlite3_bind_double(stmtInsertRec, 7, rec->phi);
	sqlite3_bind_text(stmtInsertRec, 8, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMTour / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMTour::insertRst(
			ListIdecMTour& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMTour::updateRec(
			IdecMTour* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMMission);
	sqlite3_bind_text(stmtUpdateRec, 2, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->start);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->stop);
	sqlite3_bind_text(stmtUpdateRec, 5, rec->Area.c_str(), rec->Area.length(), SQLITE_STATIC);
	sqlite3_bind_double(stmtUpdateRec, 6, rec->theta);
	sqlite3_bind_double(stmtUpdateRec, 7, rec->phi);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 9, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMTour / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMTour::updateRst(
			ListIdecMTour& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMTour::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMTour / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMTour::loadRecByRef(
			ubigint ref
			, IdecMTour** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

ubigint LiteTblIdecMTour::loadRstByMis(
			ubigint refIdecMMission
			, const bool append
			, ListIdecMTour& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByMis, 1, refIdecMMission);

	return loadRstByStmt(stmtLoadRstByMis, append, rst);
};

