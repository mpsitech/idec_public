/**
  * \file IdecAVControlPar.cpp
  * database access for table TblIdecAVControlPar (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAVControlPar.h"

/******************************************************************************
 class IdecAVControlPar
 ******************************************************************************/

IdecAVControlPar::IdecAVControlPar(
			const ubigint ref
			, const uint ixIdecVControl
			, const ubigint x1RefIdecMUser
			, const uint x2IxIdecVLocale
			, const string Par
			, const string Val
		) {

	this->ref = ref;
	this->ixIdecVControl = ixIdecVControl;
	this->x1RefIdecMUser = x1RefIdecMUser;
	this->x2IxIdecVLocale = x2IxIdecVLocale;
	this->Par = Par;
	this->Val = Val;
};

bool IdecAVControlPar::operator==(
			const IdecAVControlPar& comp
		) {
	return false;
};

bool IdecAVControlPar::operator!=(
			const IdecAVControlPar& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAVControlPar
 ******************************************************************************/

ListIdecAVControlPar::ListIdecAVControlPar() {
};

ListIdecAVControlPar::ListIdecAVControlPar(
			const ListIdecAVControlPar& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAVControlPar(*(src.nodes[i]));
};

ListIdecAVControlPar::~ListIdecAVControlPar() {
	clear();
};

void ListIdecAVControlPar::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAVControlPar::size() const {
	return(nodes.size());
};

void ListIdecAVControlPar::append(
			IdecAVControlPar* rec
		) {
	nodes.push_back(rec);
};

IdecAVControlPar* ListIdecAVControlPar::operator[](
			const uint ix
		) {
	IdecAVControlPar* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAVControlPar& ListIdecAVControlPar::operator=(
			const ListIdecAVControlPar& src
		) {
	IdecAVControlPar* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAVControlPar(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAVControlPar::operator==(
			const ListIdecAVControlPar& comp
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

bool ListIdecAVControlPar::operator!=(
			const ListIdecAVControlPar& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAVControlPar
 ******************************************************************************/

TblIdecAVControlPar::TblIdecAVControlPar() {
};

TblIdecAVControlPar::~TblIdecAVControlPar() {
};

bool TblIdecAVControlPar::loadRecBySQL(
			const string& sqlstr
			, IdecAVControlPar** rec
		) {
	return false;
};

ubigint TblIdecAVControlPar::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAVControlPar& rst
		) {
	return 0;
};

void TblIdecAVControlPar::insertRec(
			IdecAVControlPar* rec
		) {
};

ubigint TblIdecAVControlPar::insertNewRec(
			IdecAVControlPar** rec
			, const uint ixIdecVControl
			, const ubigint x1RefIdecMUser
			, const uint x2IxIdecVLocale
			, const string Par
			, const string Val
		) {
	ubigint retval = 0;
	IdecAVControlPar* _rec = NULL;

	_rec = new IdecAVControlPar(0, ixIdecVControl, x1RefIdecMUser, x2IxIdecVLocale, Par, Val);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAVControlPar::appendNewRecToRst(
			ListIdecAVControlPar& rst
			, IdecAVControlPar** rec
			, const uint ixIdecVControl
			, const ubigint x1RefIdecMUser
			, const uint x2IxIdecVLocale
			, const string Par
			, const string Val
		) {
	ubigint retval = 0;
	IdecAVControlPar* _rec = NULL;

	retval = insertNewRec(&_rec, ixIdecVControl, x1RefIdecMUser, x2IxIdecVLocale, Par, Val);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAVControlPar::insertRst(
			ListIdecAVControlPar& rst
			, bool transact
		) {
};

void TblIdecAVControlPar::updateRec(
			IdecAVControlPar* rec
		) {
};

void TblIdecAVControlPar::updateRst(
			ListIdecAVControlPar& rst
			, bool transact
		) {
};

void TblIdecAVControlPar::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAVControlPar::loadRecByRef(
			ubigint ref
			, IdecAVControlPar** rec
		) {
	return false;
};

bool TblIdecAVControlPar::loadRefByCtlUsrPar(
			uint ixIdecVControl
			, ubigint x1RefIdecMUser
			, string Par
			, ubigint& ref
		) {
	return false;
};

bool TblIdecAVControlPar::loadValByCtlUsrPar(
			uint ixIdecVControl
			, ubigint x1RefIdecMUser
			, string Par
			, string& Val
		) {
	return false;
};

ubigint TblIdecAVControlPar::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAVControlPar& rst
		) {
	ubigint numload = 0;
	IdecAVControlPar* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAVControlPar
 ******************************************************************************/

LiteTblIdecAVControlPar::LiteTblIdecAVControlPar() : TblIdecAVControlPar(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRefByCtlUsrPar = NULL;
	stmtLoadValByCtlUsrPar = NULL;
};

LiteTblIdecAVControlPar::~LiteTblIdecAVControlPar() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRefByCtlUsrPar) sqlite3_finalize(stmtLoadRefByCtlUsrPar);
	if (stmtLoadValByCtlUsrPar) sqlite3_finalize(stmtLoadValByCtlUsrPar);
};

void LiteTblIdecAVControlPar::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAVControlPar (ixIdecVControl, x1RefIdecMUser, x2IxIdecVLocale, Par, Val) VALUES (?1,?2,?3,?4,?5)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAVControlPar SET ixIdecVControl = ?1, x1RefIdecMUser = ?2, x2IxIdecVLocale = ?3, Par = ?4, Val = ?5 WHERE ref = ?6");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAVControlPar WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, ixIdecVControl, x1RefIdecMUser, x2IxIdecVLocale, Par, Val FROM TblIdecAVControlPar WHERE ref = ?1");
	stmtLoadRefByCtlUsrPar = createStatement("SELECT ref FROM TblIdecAVControlPar WHERE ixIdecVControl = ?1 AND x1RefIdecMUser = ?2 AND Par = ?3");
	stmtLoadValByCtlUsrPar = createStatement("SELECT Val FROM TblIdecAVControlPar WHERE ixIdecVControl = ?1 AND x1RefIdecMUser = ?2 AND Par = ?3");
};

bool LiteTblIdecAVControlPar::loadRec(
			sqlite3_stmt* stmt
			, IdecAVControlPar** rec
		) {
	int res;

	IdecAVControlPar* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAVControlPar();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->ixIdecVControl = sqlite3_column_int(stmt, 1);
		_rec->x1RefIdecMUser = sqlite3_column_int64(stmt, 2);
		_rec->x2IxIdecVLocale = sqlite3_column_int(stmt, 3);
		_rec->Par.assign((const char*) sqlite3_column_text(stmt, 4));
		_rec->Val.assign((const char*) sqlite3_column_text(stmt, 5));

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

ubigint LiteTblIdecAVControlPar::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAVControlPar& rst
		) {
	int res; ubigint numread = 0;

	IdecAVControlPar* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAVControlPar();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->ixIdecVControl = sqlite3_column_int(stmt, 1);
		rec->x1RefIdecMUser = sqlite3_column_int64(stmt, 2);
		rec->x2IxIdecVLocale = sqlite3_column_int(stmt, 3);
		rec->Par.assign((const char*) sqlite3_column_text(stmt, 4));
		rec->Val.assign((const char*) sqlite3_column_text(stmt, 5));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAVControlPar::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAVControlPar** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAVControlPar::loadRecBySQL(
			const string& sqlstr
			, IdecAVControlPar** rec
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

ubigint LiteTblIdecAVControlPar::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAVControlPar& rst
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

void LiteTblIdecAVControlPar::insertRec(
			IdecAVControlPar* rec
		) {
	sqlite3_bind_int(stmtInsertRec, 1, rec->ixIdecVControl);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->x1RefIdecMUser);
	sqlite3_bind_int(stmtInsertRec, 3, rec->x2IxIdecVLocale);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Par.c_str(), rec->Par.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 5, rec->Val.c_str(), rec->Val.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVControlPar / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAVControlPar::insertRst(
			ListIdecAVControlPar& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAVControlPar::updateRec(
			IdecAVControlPar* rec
		) {
	sqlite3_bind_int(stmtUpdateRec, 1, rec->ixIdecVControl);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->x1RefIdecMUser);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->x2IxIdecVLocale);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Par.c_str(), rec->Par.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 5, rec->Val.c_str(), rec->Val.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVControlPar / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAVControlPar::updateRst(
			ListIdecAVControlPar& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAVControlPar::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVControlPar / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAVControlPar::loadRecByRef(
			ubigint ref
			, IdecAVControlPar** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecAVControlPar::loadRefByCtlUsrPar(
			uint ixIdecVControl
			, ubigint x1RefIdecMUser
			, string Par
			, ubigint& ref
		) {
	sqlite3_bind_int(stmtLoadRefByCtlUsrPar, 1, ixIdecVControl);
	sqlite3_bind_int64(stmtLoadRefByCtlUsrPar, 2, x1RefIdecMUser);
	sqlite3_bind_text(stmtLoadRefByCtlUsrPar, 3, Par.c_str(), Par.length(), SQLITE_STATIC);

	return loadRefByStmt(stmtLoadRefByCtlUsrPar, ref);
};

bool LiteTblIdecAVControlPar::loadValByCtlUsrPar(
			uint ixIdecVControl
			, ubigint x1RefIdecMUser
			, string Par
			, string& Val
		) {
	sqlite3_bind_int(stmtLoadValByCtlUsrPar, 1, ixIdecVControl);
	sqlite3_bind_int64(stmtLoadValByCtlUsrPar, 2, x1RefIdecMUser);
	sqlite3_bind_text(stmtLoadValByCtlUsrPar, 3, Par.c_str(), Par.length(), SQLITE_STATIC);

	return loadStringByStmt(stmtLoadValByCtlUsrPar, Val);
};

