/**
  * \file IdecJMPersonLastname.cpp
  * database access for table TblIdecJMPersonLastname (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecJMPersonLastname.h"

/******************************************************************************
 class IdecJMPersonLastname
 ******************************************************************************/

IdecJMPersonLastname::IdecJMPersonLastname(
			const ubigint ref
			, const ubigint refIdecMPerson
			, const uint x1Startd
			, const string Lastname
		) {

	this->ref = ref;
	this->refIdecMPerson = refIdecMPerson;
	this->x1Startd = x1Startd;
	this->Lastname = Lastname;
};

bool IdecJMPersonLastname::operator==(
			const IdecJMPersonLastname& comp
		) {
	return false;
};

bool IdecJMPersonLastname::operator!=(
			const IdecJMPersonLastname& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecJMPersonLastname
 ******************************************************************************/

ListIdecJMPersonLastname::ListIdecJMPersonLastname() {
};

ListIdecJMPersonLastname::ListIdecJMPersonLastname(
			const ListIdecJMPersonLastname& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecJMPersonLastname(*(src.nodes[i]));
};

ListIdecJMPersonLastname::~ListIdecJMPersonLastname() {
	clear();
};

void ListIdecJMPersonLastname::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecJMPersonLastname::size() const {
	return(nodes.size());
};

void ListIdecJMPersonLastname::append(
			IdecJMPersonLastname* rec
		) {
	nodes.push_back(rec);
};

IdecJMPersonLastname* ListIdecJMPersonLastname::operator[](
			const uint ix
		) {
	IdecJMPersonLastname* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecJMPersonLastname& ListIdecJMPersonLastname::operator=(
			const ListIdecJMPersonLastname& src
		) {
	IdecJMPersonLastname* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecJMPersonLastname(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecJMPersonLastname::operator==(
			const ListIdecJMPersonLastname& comp
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

bool ListIdecJMPersonLastname::operator!=(
			const ListIdecJMPersonLastname& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecJMPersonLastname
 ******************************************************************************/

TblIdecJMPersonLastname::TblIdecJMPersonLastname() {
};

TblIdecJMPersonLastname::~TblIdecJMPersonLastname() {
};

bool TblIdecJMPersonLastname::loadRecBySQL(
			const string& sqlstr
			, IdecJMPersonLastname** rec
		) {
	return false;
};

ubigint TblIdecJMPersonLastname::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecJMPersonLastname& rst
		) {
	return 0;
};

void TblIdecJMPersonLastname::insertRec(
			IdecJMPersonLastname* rec
		) {
};

ubigint TblIdecJMPersonLastname::insertNewRec(
			IdecJMPersonLastname** rec
			, const ubigint refIdecMPerson
			, const uint x1Startd
			, const string Lastname
		) {
	ubigint retval = 0;
	IdecJMPersonLastname* _rec = NULL;

	_rec = new IdecJMPersonLastname(0, refIdecMPerson, x1Startd, Lastname);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecJMPersonLastname::appendNewRecToRst(
			ListIdecJMPersonLastname& rst
			, IdecJMPersonLastname** rec
			, const ubigint refIdecMPerson
			, const uint x1Startd
			, const string Lastname
		) {
	ubigint retval = 0;
	IdecJMPersonLastname* _rec = NULL;

	retval = insertNewRec(&_rec, refIdecMPerson, x1Startd, Lastname);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecJMPersonLastname::insertRst(
			ListIdecJMPersonLastname& rst
			, bool transact
		) {
};

void TblIdecJMPersonLastname::updateRec(
			IdecJMPersonLastname* rec
		) {
};

void TblIdecJMPersonLastname::updateRst(
			ListIdecJMPersonLastname& rst
			, bool transact
		) {
};

void TblIdecJMPersonLastname::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecJMPersonLastname::loadRecByRef(
			ubigint ref
			, IdecJMPersonLastname** rec
		) {
	return false;
};

bool TblIdecJMPersonLastname::loadRecByPrsSta(
			ubigint refIdecMPerson
			, uint x1Startd
			, IdecJMPersonLastname** rec
		) {
	return false;
};

ubigint TblIdecJMPersonLastname::loadRefsByPrs(
			ubigint refIdecMPerson
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

ubigint TblIdecJMPersonLastname::loadRstByPrs(
			ubigint refIdecMPerson
			, const bool append
			, ListIdecJMPersonLastname& rst
		) {
	return 0;
};

ubigint TblIdecJMPersonLastname::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecJMPersonLastname& rst
		) {
	ubigint numload = 0;
	IdecJMPersonLastname* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecJMPersonLastname
 ******************************************************************************/

LiteTblIdecJMPersonLastname::LiteTblIdecJMPersonLastname() : TblIdecJMPersonLastname(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByPrsSta = NULL;
	stmtLoadRefsByPrs = NULL;
	stmtLoadRstByPrs = NULL;
};

LiteTblIdecJMPersonLastname::~LiteTblIdecJMPersonLastname() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByPrsSta) sqlite3_finalize(stmtLoadRecByPrsSta);
	if (stmtLoadRefsByPrs) sqlite3_finalize(stmtLoadRefsByPrs);
	if (stmtLoadRstByPrs) sqlite3_finalize(stmtLoadRstByPrs);
};

void LiteTblIdecJMPersonLastname::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecJMPersonLastname (refIdecMPerson, x1Startd, Lastname) VALUES (?1,?2,?3)");
	stmtUpdateRec = createStatement("UPDATE TblIdecJMPersonLastname SET refIdecMPerson = ?1, x1Startd = ?2, Lastname = ?3 WHERE ref = ?4");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecJMPersonLastname WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, refIdecMPerson, x1Startd, Lastname FROM TblIdecJMPersonLastname WHERE ref = ?1");
	stmtLoadRecByPrsSta = createStatement("SELECT ref, refIdecMPerson, x1Startd, Lastname FROM TblIdecJMPersonLastname WHERE refIdecMPerson = ?1 AND x1Startd <= ?2 ORDER BY x1Startd DESC LIMIT 0,1");
	stmtLoadRefsByPrs = createStatement("SELECT ref FROM TblIdecJMPersonLastname WHERE refIdecMPerson = ?1");
	stmtLoadRstByPrs = createStatement("SELECT ref, refIdecMPerson, x1Startd, Lastname FROM TblIdecJMPersonLastname WHERE refIdecMPerson = ?1 ORDER BY x1Startd ASC");
};

bool LiteTblIdecJMPersonLastname::loadRec(
			sqlite3_stmt* stmt
			, IdecJMPersonLastname** rec
		) {
	int res;

	IdecJMPersonLastname* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecJMPersonLastname();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->refIdecMPerson = sqlite3_column_int64(stmt, 1);
		_rec->x1Startd = sqlite3_column_int(stmt, 2);
		_rec->Lastname.assign((const char*) sqlite3_column_text(stmt, 3));

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

ubigint LiteTblIdecJMPersonLastname::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecJMPersonLastname& rst
		) {
	int res; ubigint numread = 0;

	IdecJMPersonLastname* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecJMPersonLastname();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->refIdecMPerson = sqlite3_column_int64(stmt, 1);
		rec->x1Startd = sqlite3_column_int(stmt, 2);
		rec->Lastname.assign((const char*) sqlite3_column_text(stmt, 3));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecJMPersonLastname::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecJMPersonLastname** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecJMPersonLastname::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecJMPersonLastname& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecJMPersonLastname::loadRecBySQL(
			const string& sqlstr
			, IdecJMPersonLastname** rec
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

ubigint LiteTblIdecJMPersonLastname::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecJMPersonLastname& rst
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

void LiteTblIdecJMPersonLastname::insertRec(
			IdecJMPersonLastname* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->refIdecMPerson);
	sqlite3_bind_int(stmtInsertRec, 2, rec->x1Startd);
	sqlite3_bind_text(stmtInsertRec, 3, rec->Lastname.c_str(), rec->Lastname.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJMPersonLastname / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecJMPersonLastname::insertRst(
			ListIdecJMPersonLastname& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecJMPersonLastname::updateRec(
			IdecJMPersonLastname* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->refIdecMPerson);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->x1Startd);
	sqlite3_bind_text(stmtUpdateRec, 3, rec->Lastname.c_str(), rec->Lastname.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJMPersonLastname / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecJMPersonLastname::updateRst(
			ListIdecJMPersonLastname& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecJMPersonLastname::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecJMPersonLastname / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecJMPersonLastname::loadRecByRef(
			ubigint ref
			, IdecJMPersonLastname** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecJMPersonLastname::loadRecByPrsSta(
			ubigint refIdecMPerson
			, uint x1Startd
			, IdecJMPersonLastname** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByPrsSta, 1, refIdecMPerson);
	sqlite3_bind_int(stmtLoadRecByPrsSta, 2, x1Startd);

	return loadRecByStmt(stmtLoadRecByPrsSta, rec);
};

ubigint LiteTblIdecJMPersonLastname::loadRefsByPrs(
			ubigint refIdecMPerson
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByPrs, 1, refIdecMPerson);

	return loadRefsByStmt(stmtLoadRefsByPrs, append, refs);
};

ubigint LiteTblIdecJMPersonLastname::loadRstByPrs(
			ubigint refIdecMPerson
			, const bool append
			, ListIdecJMPersonLastname& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByPrs, 1, refIdecMPerson);

	return loadRstByStmt(stmtLoadRstByPrs, append, rst);
};

