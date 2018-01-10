/**
  * \file IdecMUser.cpp
  * database access for table TblIdecMUser (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMUser.h"

#include "IdecMUser_vecs.cpp"

/******************************************************************************
 class IdecMUser
 ******************************************************************************/

IdecMUser::IdecMUser(
			const ubigint ref
			, const ubigint grp
			, const ubigint own
			, const ubigint refRUsergroup
			, const ubigint refIdecMUsergroup
			, const ubigint refIdecMPerson
			, const string sref
			, const ubigint refJState
			, const uint ixVState
			, const uint ixIdecVLocale
			, const uint ixIdecVUserlevel
			, const string Password
		) {

	this->ref = ref;
	this->grp = grp;
	this->own = own;
	this->refRUsergroup = refRUsergroup;
	this->refIdecMUsergroup = refIdecMUsergroup;
	this->refIdecMPerson = refIdecMPerson;
	this->sref = sref;
	this->refJState = refJState;
	this->ixVState = ixVState;
	this->ixIdecVLocale = ixIdecVLocale;
	this->ixIdecVUserlevel = ixIdecVUserlevel;
	this->Password = Password;
};

bool IdecMUser::operator==(
			const IdecMUser& comp
		) {
	return false;
};

bool IdecMUser::operator!=(
			const IdecMUser& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMUser
 ******************************************************************************/

ListIdecMUser::ListIdecMUser() {
};

ListIdecMUser::ListIdecMUser(
			const ListIdecMUser& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMUser(*(src.nodes[i]));
};

ListIdecMUser::~ListIdecMUser() {
	clear();
};

void ListIdecMUser::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMUser::size() const {
	return(nodes.size());
};

void ListIdecMUser::append(
			IdecMUser* rec
		) {
	nodes.push_back(rec);
};

IdecMUser* ListIdecMUser::operator[](
			const uint ix
		) {
	IdecMUser* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMUser& ListIdecMUser::operator=(
			const ListIdecMUser& src
		) {
	IdecMUser* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMUser(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMUser::operator==(
			const ListIdecMUser& comp
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

bool ListIdecMUser::operator!=(
			const ListIdecMUser& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMUser
 ******************************************************************************/

TblIdecMUser::TblIdecMUser() {
};

TblIdecMUser::~TblIdecMUser() {
};

bool TblIdecMUser::loadRecBySQL(
			const string& sqlstr
			, IdecMUser** rec
		) {
	return false;
};

ubigint TblIdecMUser::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMUser& rst
		) {
	return 0;
};

void TblIdecMUser::insertRec(
			IdecMUser* rec
		) {
};

ubigint TblIdecMUser::insertNewRec(
			IdecMUser** rec
			, const ubigint grp
			, const ubigint own
			, const ubigint refRUsergroup
			, const ubigint refIdecMUsergroup
			, const ubigint refIdecMPerson
			, const string sref
			, const ubigint refJState
			, const uint ixVState
			, const uint ixIdecVLocale
			, const uint ixIdecVUserlevel
			, const string Password
		) {
	ubigint retval = 0;
	IdecMUser* _rec = NULL;

	_rec = new IdecMUser(0, grp, own, refRUsergroup, refIdecMUsergroup, refIdecMPerson, sref, refJState, ixVState, ixIdecVLocale, ixIdecVUserlevel, Password);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMUser::appendNewRecToRst(
			ListIdecMUser& rst
			, IdecMUser** rec
			, const ubigint grp
			, const ubigint own
			, const ubigint refRUsergroup
			, const ubigint refIdecMUsergroup
			, const ubigint refIdecMPerson
			, const string sref
			, const ubigint refJState
			, const uint ixVState
			, const uint ixIdecVLocale
			, const uint ixIdecVUserlevel
			, const string Password
		) {
	ubigint retval = 0;
	IdecMUser* _rec = NULL;

	retval = insertNewRec(&_rec, grp, own, refRUsergroup, refIdecMUsergroup, refIdecMPerson, sref, refJState, ixVState, ixIdecVLocale, ixIdecVUserlevel, Password);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMUser::insertRst(
			ListIdecMUser& rst
			, bool transact
		) {
};

void TblIdecMUser::updateRec(
			IdecMUser* rec
		) {
};

void TblIdecMUser::updateRst(
			ListIdecMUser& rst
			, bool transact
		) {
};

void TblIdecMUser::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMUser::loadRecByRef(
			ubigint ref
			, IdecMUser** rec
		) {
	return false;
};

bool TblIdecMUser::loadRecByPrs(
			ubigint refIdecMPerson
			, IdecMUser** rec
		) {
	return false;
};

bool TblIdecMUser::loadRecBySrf(
			string sref
			, IdecMUser** rec
		) {
	return false;
};

bool TblIdecMUser::loadRefByPrs(
			ubigint refIdecMPerson
			, ubigint& ref
		) {
	return false;
};

bool TblIdecMUser::loadRefBySrf(
			string sref
			, ubigint& ref
		) {
	return false;
};

bool TblIdecMUser::loadRefBySrfPwd(
			string sref
			, string Password
			, ubigint& ref
		) {
	return false;
};

ubigint TblIdecMUser::loadRefsByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

bool TblIdecMUser::loadSrfByRef(
			ubigint ref
			, string& sref
		) {
	return false;
};

ubigint TblIdecMUser::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMUser& rst
		) {
	ubigint numload = 0;
	IdecMUser* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMUser
 ******************************************************************************/

LiteTblIdecMUser::LiteTblIdecMUser() : TblIdecMUser(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRecByPrs = NULL;
	stmtLoadRecBySrf = NULL;
	stmtLoadRefByPrs = NULL;
	stmtLoadRefBySrf = NULL;
	stmtLoadRefBySrfPwd = NULL;
	stmtLoadRefsByUsg = NULL;
	stmtLoadSrfByRef = NULL;
};

LiteTblIdecMUser::~LiteTblIdecMUser() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRecByPrs) sqlite3_finalize(stmtLoadRecByPrs);
	if (stmtLoadRecBySrf) sqlite3_finalize(stmtLoadRecBySrf);
	if (stmtLoadRefByPrs) sqlite3_finalize(stmtLoadRefByPrs);
	if (stmtLoadRefBySrf) sqlite3_finalize(stmtLoadRefBySrf);
	if (stmtLoadRefBySrfPwd) sqlite3_finalize(stmtLoadRefBySrfPwd);
	if (stmtLoadRefsByUsg) sqlite3_finalize(stmtLoadRefsByUsg);
	if (stmtLoadSrfByRef) sqlite3_finalize(stmtLoadSrfByRef);
};

void LiteTblIdecMUser::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMUser (grp, own, refRUsergroup, refIdecMUsergroup, refIdecMPerson, sref, refJState, ixVState, ixIdecVLocale, ixIdecVUserlevel, Password) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9,?10,?11)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMUser SET grp = ?1, own = ?2, refRUsergroup = ?3, refIdecMUsergroup = ?4, refIdecMPerson = ?5, sref = ?6, refJState = ?7, ixVState = ?8, ixIdecVLocale = ?9, ixIdecVUserlevel = ?10, Password = ?11 WHERE ref = ?12");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMUser WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, grp, own, refRUsergroup, refIdecMUsergroup, refIdecMPerson, sref, refJState, ixVState, ixIdecVLocale, ixIdecVUserlevel, Password FROM TblIdecMUser WHERE ref = ?1");
	stmtLoadRecByPrs = createStatement("SELECT ref, grp, own, refRUsergroup, refIdecMUsergroup, refIdecMPerson, sref, refJState, ixVState, ixIdecVLocale, ixIdecVUserlevel, Password FROM TblIdecMUser WHERE refIdecMPerson = ?1");
	stmtLoadRecBySrf = createStatement("SELECT ref, grp, own, refRUsergroup, refIdecMUsergroup, refIdecMPerson, sref, refJState, ixVState, ixIdecVLocale, ixIdecVUserlevel, Password FROM TblIdecMUser WHERE sref = ?1");
	stmtLoadRefByPrs = createStatement("SELECT ref FROM TblIdecMUser WHERE refIdecMPerson = ?1");
	stmtLoadRefBySrf = createStatement("SELECT ref FROM TblIdecMUser WHERE sref = ?1");
	stmtLoadRefBySrfPwd = createStatement("SELECT ref FROM TblIdecMUser WHERE sref = ?1 AND Password = ?2");
	stmtLoadRefsByUsg = createStatement("SELECT ref FROM TblIdecMUser WHERE refIdecMUsergroup = ?1");
	stmtLoadSrfByRef = createStatement("SELECT sref FROM TblIdecMUser WHERE ref = ?1");
};

bool LiteTblIdecMUser::loadRec(
			sqlite3_stmt* stmt
			, IdecMUser** rec
		) {
	int res;

	IdecMUser* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMUser();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->grp = sqlite3_column_int64(stmt, 1);
		_rec->own = sqlite3_column_int64(stmt, 2);
		_rec->refRUsergroup = sqlite3_column_int64(stmt, 3);
		_rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 4);
		_rec->refIdecMPerson = sqlite3_column_int64(stmt, 5);
		_rec->sref.assign((const char*) sqlite3_column_text(stmt, 6));
		_rec->refJState = sqlite3_column_int64(stmt, 7);
		_rec->ixVState = sqlite3_column_int(stmt, 8);
		_rec->ixIdecVLocale = sqlite3_column_int(stmt, 9);
		_rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 10);
		_rec->Password.assign((const char*) sqlite3_column_text(stmt, 11));

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

ubigint LiteTblIdecMUser::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMUser& rst
		) {
	int res; ubigint numread = 0;

	IdecMUser* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMUser();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->grp = sqlite3_column_int64(stmt, 1);
		rec->own = sqlite3_column_int64(stmt, 2);
		rec->refRUsergroup = sqlite3_column_int64(stmt, 3);
		rec->refIdecMUsergroup = sqlite3_column_int64(stmt, 4);
		rec->refIdecMPerson = sqlite3_column_int64(stmt, 5);
		rec->sref.assign((const char*) sqlite3_column_text(stmt, 6));
		rec->refJState = sqlite3_column_int64(stmt, 7);
		rec->ixVState = sqlite3_column_int(stmt, 8);
		rec->ixIdecVLocale = sqlite3_column_int(stmt, 9);
		rec->ixIdecVUserlevel = sqlite3_column_int(stmt, 10);
		rec->Password.assign((const char*) sqlite3_column_text(stmt, 11));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMUser::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMUser** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMUser::loadRecBySQL(
			const string& sqlstr
			, IdecMUser** rec
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

ubigint LiteTblIdecMUser::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMUser& rst
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

void LiteTblIdecMUser::insertRec(
			IdecMUser* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->grp);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->own);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->refRUsergroup);
	sqlite3_bind_int64(stmtInsertRec, 4, rec->refIdecMUsergroup);
	sqlite3_bind_int64(stmtInsertRec, 5, rec->refIdecMPerson);
	sqlite3_bind_text(stmtInsertRec, 6, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 7, rec->refJState);
	sqlite3_bind_int(stmtInsertRec, 8, rec->ixVState);
	sqlite3_bind_int(stmtInsertRec, 9, rec->ixIdecVLocale);
	sqlite3_bind_int(stmtInsertRec, 10, rec->ixIdecVUserlevel);
	sqlite3_bind_text(stmtInsertRec, 11, rec->Password.c_str(), rec->Password.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMUser / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMUser::insertRst(
			ListIdecMUser& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMUser::updateRec(
			IdecMUser* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->grp);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->own);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->refRUsergroup);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->refIdecMUsergroup);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->refIdecMPerson);
	sqlite3_bind_text(stmtUpdateRec, 6, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 7, rec->refJState);
	sqlite3_bind_int(stmtUpdateRec, 8, rec->ixVState);
	sqlite3_bind_int(stmtUpdateRec, 9, rec->ixIdecVLocale);
	sqlite3_bind_int(stmtUpdateRec, 10, rec->ixIdecVUserlevel);
	sqlite3_bind_text(stmtUpdateRec, 11, rec->Password.c_str(), rec->Password.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 12, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMUser / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMUser::updateRst(
			ListIdecMUser& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMUser::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMUser / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMUser::loadRecByRef(
			ubigint ref
			, IdecMUser** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecMUser::loadRecByPrs(
			ubigint refIdecMPerson
			, IdecMUser** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByPrs, 1, refIdecMPerson);

	return loadRecByStmt(stmtLoadRecByPrs, rec);
};

bool LiteTblIdecMUser::loadRecBySrf(
			string sref
			, IdecMUser** rec
		) {
	sqlite3_bind_text(stmtLoadRecBySrf, 1, sref.c_str(), sref.length(), SQLITE_STATIC);

	return loadRecByStmt(stmtLoadRecBySrf, rec);
};

bool LiteTblIdecMUser::loadRefByPrs(
			ubigint refIdecMPerson
			, ubigint& ref
		) {
	sqlite3_bind_int64(stmtLoadRefByPrs, 1, refIdecMPerson);

	return loadRefByStmt(stmtLoadRefByPrs, ref);
};

bool LiteTblIdecMUser::loadRefBySrf(
			string sref
			, ubigint& ref
		) {
	sqlite3_bind_text(stmtLoadRefBySrf, 1, sref.c_str(), sref.length(), SQLITE_STATIC);

	return loadRefByStmt(stmtLoadRefBySrf, ref);
};

bool LiteTblIdecMUser::loadRefBySrfPwd(
			string sref
			, string Password
			, ubigint& ref
		) {
	sqlite3_bind_text(stmtLoadRefBySrfPwd, 1, sref.c_str(), sref.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtLoadRefBySrfPwd, 2, Password.c_str(), Password.length(), SQLITE_STATIC);

	return loadRefByStmt(stmtLoadRefBySrfPwd, ref);
};

ubigint LiteTblIdecMUser::loadRefsByUsg(
			ubigint refIdecMUsergroup
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByUsg, 1, refIdecMUsergroup);

	return loadRefsByStmt(stmtLoadRefsByUsg, append, refs);
};

bool LiteTblIdecMUser::loadSrfByRef(
			ubigint ref
			, string& sref
		) {
	sqlite3_bind_int64(stmtLoadSrfByRef, 1, ref);

	return loadStringByStmt(stmtLoadSrfByRef, sref);
};

