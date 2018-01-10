/**
  * \file IdecAVValuelistVal.cpp
  * database access for table TblIdecAVValuelistVal (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAVValuelistVal.h"

/******************************************************************************
 class IdecAVValuelistVal
 ******************************************************************************/

IdecAVValuelistVal::IdecAVValuelistVal(
			const ubigint ref
			, const uint vlsIxIdecVValuelist
			, const uint vlsNum
			, const uint x1IxIdecVLocale
			, const string Val
		) {

	this->ref = ref;
	this->vlsIxIdecVValuelist = vlsIxIdecVValuelist;
	this->vlsNum = vlsNum;
	this->x1IxIdecVLocale = x1IxIdecVLocale;
	this->Val = Val;
};

bool IdecAVValuelistVal::operator==(
			const IdecAVValuelistVal& comp
		) {
	return false;
};

bool IdecAVValuelistVal::operator!=(
			const IdecAVValuelistVal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAVValuelistVal
 ******************************************************************************/

ListIdecAVValuelistVal::ListIdecAVValuelistVal() {
};

ListIdecAVValuelistVal::ListIdecAVValuelistVal(
			const ListIdecAVValuelistVal& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAVValuelistVal(*(src.nodes[i]));
};

ListIdecAVValuelistVal::~ListIdecAVValuelistVal() {
	clear();
};

void ListIdecAVValuelistVal::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAVValuelistVal::size() const {
	return(nodes.size());
};

void ListIdecAVValuelistVal::append(
			IdecAVValuelistVal* rec
		) {
	nodes.push_back(rec);
};

IdecAVValuelistVal* ListIdecAVValuelistVal::operator[](
			const uint ix
		) {
	IdecAVValuelistVal* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAVValuelistVal& ListIdecAVValuelistVal::operator=(
			const ListIdecAVValuelistVal& src
		) {
	IdecAVValuelistVal* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAVValuelistVal(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAVValuelistVal::operator==(
			const ListIdecAVValuelistVal& comp
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

bool ListIdecAVValuelistVal::operator!=(
			const ListIdecAVValuelistVal& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAVValuelistVal
 ******************************************************************************/

TblIdecAVValuelistVal::TblIdecAVValuelistVal() {
};

TblIdecAVValuelistVal::~TblIdecAVValuelistVal() {
};

bool TblIdecAVValuelistVal::loadRecBySQL(
			const string& sqlstr
			, IdecAVValuelistVal** rec
		) {
	return false;
};

ubigint TblIdecAVValuelistVal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAVValuelistVal& rst
		) {
	return 0;
};

void TblIdecAVValuelistVal::insertRec(
			IdecAVValuelistVal* rec
		) {
};

ubigint TblIdecAVValuelistVal::insertNewRec(
			IdecAVValuelistVal** rec
			, const uint vlsIxIdecVValuelist
			, const uint vlsNum
			, const uint x1IxIdecVLocale
			, const string Val
		) {
	ubigint retval = 0;
	IdecAVValuelistVal* _rec = NULL;

	_rec = new IdecAVValuelistVal(0, vlsIxIdecVValuelist, vlsNum, x1IxIdecVLocale, Val);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAVValuelistVal::appendNewRecToRst(
			ListIdecAVValuelistVal& rst
			, IdecAVValuelistVal** rec
			, const uint vlsIxIdecVValuelist
			, const uint vlsNum
			, const uint x1IxIdecVLocale
			, const string Val
		) {
	ubigint retval = 0;
	IdecAVValuelistVal* _rec = NULL;

	retval = insertNewRec(&_rec, vlsIxIdecVValuelist, vlsNum, x1IxIdecVLocale, Val);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAVValuelistVal::insertRst(
			ListIdecAVValuelistVal& rst
			, bool transact
		) {
};

void TblIdecAVValuelistVal::updateRec(
			IdecAVValuelistVal* rec
		) {
};

void TblIdecAVValuelistVal::updateRst(
			ListIdecAVValuelistVal& rst
			, bool transact
		) {
};

void TblIdecAVValuelistVal::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAVValuelistVal::loadRecByRef(
			ubigint ref
			, IdecAVValuelistVal** rec
		) {
	return false;
};

ubigint TblIdecAVValuelistVal::loadRstByVlsLcl(
			uint vlsIxIdecVValuelist
			, uint x1IxIdecVLocale
			, const bool append
			, ListIdecAVValuelistVal& rst
		) {
	return 0;
};

ubigint TblIdecAVValuelistVal::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAVValuelistVal& rst
		) {
	ubigint numload = 0;
	IdecAVValuelistVal* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAVValuelistVal
 ******************************************************************************/

LiteTblIdecAVValuelistVal::LiteTblIdecAVValuelistVal() : TblIdecAVValuelistVal(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRstByVlsLcl = NULL;
};

LiteTblIdecAVValuelistVal::~LiteTblIdecAVValuelistVal() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRstByVlsLcl) sqlite3_finalize(stmtLoadRstByVlsLcl);
};

void LiteTblIdecAVValuelistVal::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAVValuelistVal (vlsIxIdecVValuelist, vlsNum, x1IxIdecVLocale, Val) VALUES (?1,?2,?3,?4)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAVValuelistVal SET vlsIxIdecVValuelist = ?1, vlsNum = ?2, x1IxIdecVLocale = ?3, Val = ?4 WHERE ref = ?5");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAVValuelistVal WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, vlsIxIdecVValuelist, vlsNum, x1IxIdecVLocale, Val FROM TblIdecAVValuelistVal WHERE ref = ?1");
	stmtLoadRstByVlsLcl = createStatement("SELECT ref, vlsIxIdecVValuelist, vlsNum, x1IxIdecVLocale, Val FROM TblIdecAVValuelistVal WHERE vlsIxIdecVValuelist = ?1 AND x1IxIdecVLocale = ?2 ORDER BY vlsNum ASC");
};

bool LiteTblIdecAVValuelistVal::loadRec(
			sqlite3_stmt* stmt
			, IdecAVValuelistVal** rec
		) {
	int res;

	IdecAVValuelistVal* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAVValuelistVal();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->vlsIxIdecVValuelist = sqlite3_column_int(stmt, 1);
		_rec->vlsNum = sqlite3_column_int(stmt, 2);
		_rec->x1IxIdecVLocale = sqlite3_column_int(stmt, 3);
		_rec->Val.assign((const char*) sqlite3_column_text(stmt, 4));

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

ubigint LiteTblIdecAVValuelistVal::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAVValuelistVal& rst
		) {
	int res; ubigint numread = 0;

	IdecAVValuelistVal* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAVValuelistVal();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->vlsIxIdecVValuelist = sqlite3_column_int(stmt, 1);
		rec->vlsNum = sqlite3_column_int(stmt, 2);
		rec->x1IxIdecVLocale = sqlite3_column_int(stmt, 3);
		rec->Val.assign((const char*) sqlite3_column_text(stmt, 4));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAVValuelistVal::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAVValuelistVal** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecAVValuelistVal::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAVValuelistVal& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAVValuelistVal::loadRecBySQL(
			const string& sqlstr
			, IdecAVValuelistVal** rec
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

ubigint LiteTblIdecAVValuelistVal::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAVValuelistVal& rst
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

void LiteTblIdecAVValuelistVal::insertRec(
			IdecAVValuelistVal* rec
		) {
	sqlite3_bind_int(stmtInsertRec, 1, rec->vlsIxIdecVValuelist);
	sqlite3_bind_int(stmtInsertRec, 2, rec->vlsNum);
	sqlite3_bind_int(stmtInsertRec, 3, rec->x1IxIdecVLocale);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Val.c_str(), rec->Val.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVValuelistVal / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAVValuelistVal::insertRst(
			ListIdecAVValuelistVal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAVValuelistVal::updateRec(
			IdecAVValuelistVal* rec
		) {
	sqlite3_bind_int(stmtUpdateRec, 1, rec->vlsIxIdecVValuelist);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->vlsNum);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->x1IxIdecVLocale);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Val.c_str(), rec->Val.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVValuelistVal / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAVValuelistVal::updateRst(
			ListIdecAVValuelistVal& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAVValuelistVal::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVValuelistVal / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAVValuelistVal::loadRecByRef(
			ubigint ref
			, IdecAVValuelistVal** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

ubigint LiteTblIdecAVValuelistVal::loadRstByVlsLcl(
			uint vlsIxIdecVValuelist
			, uint x1IxIdecVLocale
			, const bool append
			, ListIdecAVValuelistVal& rst
		) {
	sqlite3_bind_int(stmtLoadRstByVlsLcl, 1, vlsIxIdecVValuelist);
	sqlite3_bind_int(stmtLoadRstByVlsLcl, 2, x1IxIdecVLocale);

	return loadRstByStmt(stmtLoadRstByVlsLcl, append, rst);
};

