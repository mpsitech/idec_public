/**
  * \file IdecAVKeylistKey.cpp
  * database access for table TblIdecAVKeylistKey (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecAVKeylistKey.h"

/******************************************************************************
 class IdecAVKeylistKey
 ******************************************************************************/

IdecAVKeylistKey::IdecAVKeylistKey(
			const ubigint ref
			, const uint klsIxIdecVKeylist
			, const uint klsNum
			, const uint x1IxIdecVMaintable
			, const ubigint x1Uref
			, const bool Fixed
			, const string sref
			, const string Avail
			, const string Implied
			, const ubigint refJ
			, const string Title
			, const string Comment
		) {

	this->ref = ref;
	this->klsIxIdecVKeylist = klsIxIdecVKeylist;
	this->klsNum = klsNum;
	this->x1IxIdecVMaintable = x1IxIdecVMaintable;
	this->x1Uref = x1Uref;
	this->Fixed = Fixed;
	this->sref = sref;
	this->Avail = Avail;
	this->Implied = Implied;
	this->refJ = refJ;
	this->Title = Title;
	this->Comment = Comment;
};

bool IdecAVKeylistKey::operator==(
			const IdecAVKeylistKey& comp
		) {
	return false;
};

bool IdecAVKeylistKey::operator!=(
			const IdecAVKeylistKey& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecAVKeylistKey
 ******************************************************************************/

ListIdecAVKeylistKey::ListIdecAVKeylistKey() {
};

ListIdecAVKeylistKey::ListIdecAVKeylistKey(
			const ListIdecAVKeylistKey& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecAVKeylistKey(*(src.nodes[i]));
};

ListIdecAVKeylistKey::~ListIdecAVKeylistKey() {
	clear();
};

void ListIdecAVKeylistKey::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecAVKeylistKey::size() const {
	return(nodes.size());
};

void ListIdecAVKeylistKey::append(
			IdecAVKeylistKey* rec
		) {
	nodes.push_back(rec);
};

IdecAVKeylistKey* ListIdecAVKeylistKey::operator[](
			const uint ix
		) {
	IdecAVKeylistKey* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecAVKeylistKey& ListIdecAVKeylistKey::operator=(
			const ListIdecAVKeylistKey& src
		) {
	IdecAVKeylistKey* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecAVKeylistKey(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecAVKeylistKey::operator==(
			const ListIdecAVKeylistKey& comp
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

bool ListIdecAVKeylistKey::operator!=(
			const ListIdecAVKeylistKey& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecAVKeylistKey
 ******************************************************************************/

TblIdecAVKeylistKey::TblIdecAVKeylistKey() {
};

TblIdecAVKeylistKey::~TblIdecAVKeylistKey() {
};

bool TblIdecAVKeylistKey::loadRecBySQL(
			const string& sqlstr
			, IdecAVKeylistKey** rec
		) {
	return false;
};

ubigint TblIdecAVKeylistKey::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	return 0;
};

void TblIdecAVKeylistKey::insertRec(
			IdecAVKeylistKey* rec
		) {
};

ubigint TblIdecAVKeylistKey::insertNewRec(
			IdecAVKeylistKey** rec
			, const uint klsIxIdecVKeylist
			, const uint klsNum
			, const uint x1IxIdecVMaintable
			, const ubigint x1Uref
			, const bool Fixed
			, const string sref
			, const string Avail
			, const string Implied
			, const ubigint refJ
			, const string Title
			, const string Comment
		) {
	ubigint retval = 0;
	IdecAVKeylistKey* _rec = NULL;

	_rec = new IdecAVKeylistKey(0, klsIxIdecVKeylist, klsNum, x1IxIdecVMaintable, x1Uref, Fixed, sref, Avail, Implied, refJ, Title, Comment);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecAVKeylistKey::appendNewRecToRst(
			ListIdecAVKeylistKey& rst
			, IdecAVKeylistKey** rec
			, const uint klsIxIdecVKeylist
			, const uint klsNum
			, const uint x1IxIdecVMaintable
			, const ubigint x1Uref
			, const bool Fixed
			, const string sref
			, const string Avail
			, const string Implied
			, const ubigint refJ
			, const string Title
			, const string Comment
		) {
	ubigint retval = 0;
	IdecAVKeylistKey* _rec = NULL;

	retval = insertNewRec(&_rec, klsIxIdecVKeylist, klsNum, x1IxIdecVMaintable, x1Uref, Fixed, sref, Avail, Implied, refJ, Title, Comment);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecAVKeylistKey::insertRst(
			ListIdecAVKeylistKey& rst
			, bool transact
		) {
};

void TblIdecAVKeylistKey::updateRec(
			IdecAVKeylistKey* rec
		) {
};

void TblIdecAVKeylistKey::updateRst(
			ListIdecAVKeylistKey& rst
			, bool transact
		) {
};

void TblIdecAVKeylistKey::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecAVKeylistKey::loadRecByRef(
			ubigint ref
			, IdecAVKeylistKey** rec
		) {
	return false;
};

bool TblIdecAVKeylistKey::loadRefByKlsMtbUrfSrf(
			uint klsIxIdecVKeylist
			, uint x1IxIdecVMaintable
			, ubigint x1Uref
			, string sref
			, ubigint& ref
		) {
	return false;
};

bool TblIdecAVKeylistKey::loadRefByKlsSrf(
			uint klsIxIdecVKeylist
			, string sref
			, ubigint& ref
		) {
	return false;
};

ubigint TblIdecAVKeylistKey::loadRstByKls(
			uint klsIxIdecVKeylist
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	return 0;
};

ubigint TblIdecAVKeylistKey::loadRstByKlsMtbUrf(
			uint klsIxIdecVKeylist
			, uint x1IxIdecVMaintable
			, ubigint x1Uref
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	return 0;
};

bool TblIdecAVKeylistKey::loadTitByRef(
			ubigint ref
			, string& Title
		) {
	return false;
};

ubigint TblIdecAVKeylistKey::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	ubigint numload = 0;
	IdecAVKeylistKey* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecAVKeylistKey
 ******************************************************************************/

LiteTblIdecAVKeylistKey::LiteTblIdecAVKeylistKey() : TblIdecAVKeylistKey(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadRefByKlsMtbUrfSrf = NULL;
	stmtLoadRefByKlsSrf = NULL;
	stmtLoadRstByKls = NULL;
	stmtLoadRstByKlsMtbUrf = NULL;
	stmtLoadTitByRef = NULL;
};

LiteTblIdecAVKeylistKey::~LiteTblIdecAVKeylistKey() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadRefByKlsMtbUrfSrf) sqlite3_finalize(stmtLoadRefByKlsMtbUrfSrf);
	if (stmtLoadRefByKlsSrf) sqlite3_finalize(stmtLoadRefByKlsSrf);
	if (stmtLoadRstByKls) sqlite3_finalize(stmtLoadRstByKls);
	if (stmtLoadRstByKlsMtbUrf) sqlite3_finalize(stmtLoadRstByKlsMtbUrf);
	if (stmtLoadTitByRef) sqlite3_finalize(stmtLoadTitByRef);
};

void LiteTblIdecAVKeylistKey::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecAVKeylistKey (klsIxIdecVKeylist, klsNum, x1IxIdecVMaintable, x1Uref, Fixed, sref, Avail, Implied, refJ, Title, Comment) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9,?10,?11)");
	stmtUpdateRec = createStatement("UPDATE TblIdecAVKeylistKey SET klsIxIdecVKeylist = ?1, klsNum = ?2, x1IxIdecVMaintable = ?3, x1Uref = ?4, Fixed = ?5, sref = ?6, Avail = ?7, Implied = ?8, refJ = ?9, Title = ?10, Comment = ?11 WHERE ref = ?12");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecAVKeylistKey WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, klsIxIdecVKeylist, klsNum, x1IxIdecVMaintable, x1Uref, Fixed, sref, Avail, Implied, refJ, Title, Comment FROM TblIdecAVKeylistKey WHERE ref = ?1");
	stmtLoadRefByKlsMtbUrfSrf = createStatement("SELECT ref FROM TblIdecAVKeylistKey WHERE klsIxIdecVKeylist = ?1 AND x1IxIdecVMaintable = ?2 AND x1Uref = ?3 AND sref = ?4");
	stmtLoadRefByKlsSrf = createStatement("SELECT ref FROM TblIdecAVKeylistKey WHERE klsIxIdecVKeylist = ?1 AND sref = ?2");
	stmtLoadRstByKls = createStatement("SELECT ref, klsIxIdecVKeylist, klsNum, x1IxIdecVMaintable, x1Uref, Fixed, sref, Avail, Implied, refJ, Title, Comment FROM TblIdecAVKeylistKey WHERE klsIxIdecVKeylist = ?1 ORDER BY klsNum ASC");
	stmtLoadRstByKlsMtbUrf = createStatement("SELECT ref, klsIxIdecVKeylist, klsNum, x1IxIdecVMaintable, x1Uref, Fixed, sref, Avail, Implied, refJ, Title, Comment FROM TblIdecAVKeylistKey WHERE klsIxIdecVKeylist = ?1 AND x1IxIdecVMaintable = ?2 AND x1Uref = ?3 ORDER BY klsNum ASC");
	stmtLoadTitByRef = createStatement("SELECT Title FROM TblIdecAVKeylistKey WHERE ref = ?1");
};

bool LiteTblIdecAVKeylistKey::loadRec(
			sqlite3_stmt* stmt
			, IdecAVKeylistKey** rec
		) {
	int res;

	IdecAVKeylistKey* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecAVKeylistKey();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->klsIxIdecVKeylist = sqlite3_column_int(stmt, 1);
		_rec->klsNum = sqlite3_column_int(stmt, 2);
		_rec->x1IxIdecVMaintable = sqlite3_column_int(stmt, 3);
		_rec->x1Uref = sqlite3_column_int64(stmt, 4);
		_rec->Fixed = (sqlite3_column_int(stmt, 5) != 0);
		_rec->sref.assign((const char*) sqlite3_column_text(stmt, 6));
		_rec->Avail.assign((const char*) sqlite3_column_text(stmt, 7));
		_rec->Implied.assign((const char*) sqlite3_column_text(stmt, 8));
		_rec->refJ = sqlite3_column_int64(stmt, 9);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 10));
		_rec->Comment.assign((const char*) sqlite3_column_text(stmt, 11));

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

ubigint LiteTblIdecAVKeylistKey::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	int res; ubigint numread = 0;

	IdecAVKeylistKey* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecAVKeylistKey();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->klsIxIdecVKeylist = sqlite3_column_int(stmt, 1);
		rec->klsNum = sqlite3_column_int(stmt, 2);
		rec->x1IxIdecVMaintable = sqlite3_column_int(stmt, 3);
		rec->x1Uref = sqlite3_column_int64(stmt, 4);
		rec->Fixed = (sqlite3_column_int(stmt, 5) != 0);
		rec->sref.assign((const char*) sqlite3_column_text(stmt, 6));
		rec->Avail.assign((const char*) sqlite3_column_text(stmt, 7));
		rec->Implied.assign((const char*) sqlite3_column_text(stmt, 8));
		rec->refJ = sqlite3_column_int64(stmt, 9);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 10));
		rec->Comment.assign((const char*) sqlite3_column_text(stmt, 11));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecAVKeylistKey::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecAVKeylistKey** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecAVKeylistKey::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecAVKeylistKey::loadRecBySQL(
			const string& sqlstr
			, IdecAVKeylistKey** rec
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

ubigint LiteTblIdecAVKeylistKey::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecAVKeylistKey& rst
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

void LiteTblIdecAVKeylistKey::insertRec(
			IdecAVKeylistKey* rec
		) {
	sqlite3_bind_int(stmtInsertRec, 1, rec->klsIxIdecVKeylist);
	sqlite3_bind_int(stmtInsertRec, 2, rec->klsNum);
	sqlite3_bind_int(stmtInsertRec, 3, rec->x1IxIdecVMaintable);
	sqlite3_bind_int64(stmtInsertRec, 4, rec->x1Uref);
	sqlite3_bind_int(stmtInsertRec, 5, rec->Fixed);
	sqlite3_bind_text(stmtInsertRec, 6, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 7, rec->Avail.c_str(), rec->Avail.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 8, rec->Implied.c_str(), rec->Implied.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 9, rec->refJ);
	sqlite3_bind_text(stmtInsertRec, 10, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 11, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVKeylistKey / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecAVKeylistKey::insertRst(
			ListIdecAVKeylistKey& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecAVKeylistKey::updateRec(
			IdecAVKeylistKey* rec
		) {
	sqlite3_bind_int(stmtUpdateRec, 1, rec->klsIxIdecVKeylist);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->klsNum);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->x1IxIdecVMaintable);
	sqlite3_bind_int64(stmtUpdateRec, 4, rec->x1Uref);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->Fixed);
	sqlite3_bind_text(stmtUpdateRec, 6, rec->sref.c_str(), rec->sref.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 7, rec->Avail.c_str(), rec->Avail.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->Implied.c_str(), rec->Implied.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 9, rec->refJ);
	sqlite3_bind_text(stmtUpdateRec, 10, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 11, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 12, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVKeylistKey / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecAVKeylistKey::updateRst(
			ListIdecAVKeylistKey& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecAVKeylistKey::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecAVKeylistKey / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecAVKeylistKey::loadRecByRef(
			ubigint ref
			, IdecAVKeylistKey** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecAVKeylistKey::loadRefByKlsMtbUrfSrf(
			uint klsIxIdecVKeylist
			, uint x1IxIdecVMaintable
			, ubigint x1Uref
			, string sref
			, ubigint& ref
		) {
	sqlite3_bind_int(stmtLoadRefByKlsMtbUrfSrf, 1, klsIxIdecVKeylist);
	sqlite3_bind_int(stmtLoadRefByKlsMtbUrfSrf, 2, x1IxIdecVMaintable);
	sqlite3_bind_int64(stmtLoadRefByKlsMtbUrfSrf, 3, x1Uref);
	sqlite3_bind_text(stmtLoadRefByKlsMtbUrfSrf, 4, sref.c_str(), sref.length(), SQLITE_STATIC);

	return loadRefByStmt(stmtLoadRefByKlsMtbUrfSrf, ref);
};

bool LiteTblIdecAVKeylistKey::loadRefByKlsSrf(
			uint klsIxIdecVKeylist
			, string sref
			, ubigint& ref
		) {
	sqlite3_bind_int(stmtLoadRefByKlsSrf, 1, klsIxIdecVKeylist);
	sqlite3_bind_text(stmtLoadRefByKlsSrf, 2, sref.c_str(), sref.length(), SQLITE_STATIC);

	return loadRefByStmt(stmtLoadRefByKlsSrf, ref);
};

ubigint LiteTblIdecAVKeylistKey::loadRstByKls(
			uint klsIxIdecVKeylist
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	sqlite3_bind_int(stmtLoadRstByKls, 1, klsIxIdecVKeylist);

	return loadRstByStmt(stmtLoadRstByKls, append, rst);
};

ubigint LiteTblIdecAVKeylistKey::loadRstByKlsMtbUrf(
			uint klsIxIdecVKeylist
			, uint x1IxIdecVMaintable
			, ubigint x1Uref
			, const bool append
			, ListIdecAVKeylistKey& rst
		) {
	sqlite3_bind_int(stmtLoadRstByKlsMtbUrf, 1, klsIxIdecVKeylist);
	sqlite3_bind_int(stmtLoadRstByKlsMtbUrf, 2, x1IxIdecVMaintable);
	sqlite3_bind_int64(stmtLoadRstByKlsMtbUrf, 3, x1Uref);

	return loadRstByStmt(stmtLoadRstByKlsMtbUrf, append, rst);
};

bool LiteTblIdecAVKeylistKey::loadTitByRef(
			ubigint ref
			, string& Title
		) {
	sqlite3_bind_int64(stmtLoadTitByRef, 1, ref);

	return loadStringByStmt(stmtLoadTitByRef, Title);
};

