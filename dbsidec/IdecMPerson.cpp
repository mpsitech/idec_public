/**
  * \file IdecMPerson.cpp
  * database access for table TblIdecMPerson (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMPerson.h"

#include "IdecMPerson_vecs.cpp"

/******************************************************************************
 class IdecMPerson
 ******************************************************************************/

IdecMPerson::IdecMPerson(
			const ubigint ref
			, const ubigint grp
			, const ubigint own
			, const uint ixWDerivate
			, const uint ixVSex
			, const string Title
			, const string Firstname
			, const ubigint refJLastname
			, const string Lastname
			, const ubigint telRefADetail
			, const string telVal
			, const ubigint emlRefADetail
			, const string emlVal
			, const string Salutation
		) {

	this->ref = ref;
	this->grp = grp;
	this->own = own;
	this->ixWDerivate = ixWDerivate;
	this->ixVSex = ixVSex;
	this->Title = Title;
	this->Firstname = Firstname;
	this->refJLastname = refJLastname;
	this->Lastname = Lastname;
	this->telRefADetail = telRefADetail;
	this->telVal = telVal;
	this->emlRefADetail = emlRefADetail;
	this->emlVal = emlVal;
	this->Salutation = Salutation;
};

bool IdecMPerson::operator==(
			const IdecMPerson& comp
		) {
	return false;
};

bool IdecMPerson::operator!=(
			const IdecMPerson& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMPerson
 ******************************************************************************/

ListIdecMPerson::ListIdecMPerson() {
};

ListIdecMPerson::ListIdecMPerson(
			const ListIdecMPerson& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMPerson(*(src.nodes[i]));
};

ListIdecMPerson::~ListIdecMPerson() {
	clear();
};

void ListIdecMPerson::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMPerson::size() const {
	return(nodes.size());
};

void ListIdecMPerson::append(
			IdecMPerson* rec
		) {
	nodes.push_back(rec);
};

IdecMPerson* ListIdecMPerson::operator[](
			const uint ix
		) {
	IdecMPerson* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMPerson& ListIdecMPerson::operator=(
			const ListIdecMPerson& src
		) {
	IdecMPerson* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMPerson(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMPerson::operator==(
			const ListIdecMPerson& comp
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

bool ListIdecMPerson::operator!=(
			const ListIdecMPerson& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMPerson
 ******************************************************************************/

TblIdecMPerson::TblIdecMPerson() {
};

TblIdecMPerson::~TblIdecMPerson() {
};

bool TblIdecMPerson::loadRecBySQL(
			const string& sqlstr
			, IdecMPerson** rec
		) {
	return false;
};

ubigint TblIdecMPerson::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMPerson& rst
		) {
	return 0;
};

void TblIdecMPerson::insertRec(
			IdecMPerson* rec
		) {
};

ubigint TblIdecMPerson::insertNewRec(
			IdecMPerson** rec
			, const ubigint grp
			, const ubigint own
			, const uint ixWDerivate
			, const uint ixVSex
			, const string Title
			, const string Firstname
			, const ubigint refJLastname
			, const string Lastname
			, const ubigint telRefADetail
			, const string telVal
			, const ubigint emlRefADetail
			, const string emlVal
			, const string Salutation
		) {
	ubigint retval = 0;
	IdecMPerson* _rec = NULL;

	_rec = new IdecMPerson(0, grp, own, ixWDerivate, ixVSex, Title, Firstname, refJLastname, Lastname, telRefADetail, telVal, emlRefADetail, emlVal, Salutation);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMPerson::appendNewRecToRst(
			ListIdecMPerson& rst
			, IdecMPerson** rec
			, const ubigint grp
			, const ubigint own
			, const uint ixWDerivate
			, const uint ixVSex
			, const string Title
			, const string Firstname
			, const ubigint refJLastname
			, const string Lastname
			, const ubigint telRefADetail
			, const string telVal
			, const ubigint emlRefADetail
			, const string emlVal
			, const string Salutation
		) {
	ubigint retval = 0;
	IdecMPerson* _rec = NULL;

	retval = insertNewRec(&_rec, grp, own, ixWDerivate, ixVSex, Title, Firstname, refJLastname, Lastname, telRefADetail, telVal, emlRefADetail, emlVal, Salutation);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMPerson::insertRst(
			ListIdecMPerson& rst
			, bool transact
		) {
};

void TblIdecMPerson::updateRec(
			IdecMPerson* rec
		) {
};

void TblIdecMPerson::updateRst(
			ListIdecMPerson& rst
			, bool transact
		) {
};

void TblIdecMPerson::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMPerson::loadRecByRef(
			ubigint ref
			, IdecMPerson** rec
		) {
	return false;
};

ubigint TblIdecMPerson::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMPerson& rst
		) {
	ubigint numload = 0;
	IdecMPerson* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMPerson
 ******************************************************************************/

LiteTblIdecMPerson::LiteTblIdecMPerson() : TblIdecMPerson(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

};

LiteTblIdecMPerson::~LiteTblIdecMPerson() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

};

void LiteTblIdecMPerson::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMPerson (grp, own, ixWDerivate, ixVSex, Title, Firstname, refJLastname, Lastname, telRefADetail, telVal, emlRefADetail, emlVal, Salutation) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9,?10,?11,?12,?13)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMPerson SET grp = ?1, own = ?2, ixWDerivate = ?3, ixVSex = ?4, Title = ?5, Firstname = ?6, refJLastname = ?7, Lastname = ?8, telRefADetail = ?9, telVal = ?10, emlRefADetail = ?11, emlVal = ?12, Salutation = ?13 WHERE ref = ?14");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMPerson WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, grp, own, ixWDerivate, ixVSex, Title, Firstname, refJLastname, Lastname, telRefADetail, telVal, emlRefADetail, emlVal, Salutation FROM TblIdecMPerson WHERE ref = ?1");
};

bool LiteTblIdecMPerson::loadRec(
			sqlite3_stmt* stmt
			, IdecMPerson** rec
		) {
	int res;

	IdecMPerson* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMPerson();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->grp = sqlite3_column_int64(stmt, 1);
		_rec->own = sqlite3_column_int64(stmt, 2);
		_rec->ixWDerivate = sqlite3_column_int(stmt, 3);
		_rec->ixVSex = sqlite3_column_int(stmt, 4);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 5));
		_rec->Firstname.assign((const char*) sqlite3_column_text(stmt, 6));
		_rec->refJLastname = sqlite3_column_int64(stmt, 7);
		_rec->Lastname.assign((const char*) sqlite3_column_text(stmt, 8));
		_rec->telRefADetail = sqlite3_column_int64(stmt, 9);
		_rec->telVal.assign((const char*) sqlite3_column_text(stmt, 10));
		_rec->emlRefADetail = sqlite3_column_int64(stmt, 11);
		_rec->emlVal.assign((const char*) sqlite3_column_text(stmt, 12));
		_rec->Salutation.assign((const char*) sqlite3_column_text(stmt, 13));

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

ubigint LiteTblIdecMPerson::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMPerson& rst
		) {
	int res; ubigint numread = 0;

	IdecMPerson* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMPerson();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->grp = sqlite3_column_int64(stmt, 1);
		rec->own = sqlite3_column_int64(stmt, 2);
		rec->ixWDerivate = sqlite3_column_int(stmt, 3);
		rec->ixVSex = sqlite3_column_int(stmt, 4);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 5));
		rec->Firstname.assign((const char*) sqlite3_column_text(stmt, 6));
		rec->refJLastname = sqlite3_column_int64(stmt, 7);
		rec->Lastname.assign((const char*) sqlite3_column_text(stmt, 8));
		rec->telRefADetail = sqlite3_column_int64(stmt, 9);
		rec->telVal.assign((const char*) sqlite3_column_text(stmt, 10));
		rec->emlRefADetail = sqlite3_column_int64(stmt, 11);
		rec->emlVal.assign((const char*) sqlite3_column_text(stmt, 12));
		rec->Salutation.assign((const char*) sqlite3_column_text(stmt, 13));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMPerson::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMPerson** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMPerson::loadRecBySQL(
			const string& sqlstr
			, IdecMPerson** rec
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

ubigint LiteTblIdecMPerson::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMPerson& rst
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

void LiteTblIdecMPerson::insertRec(
			IdecMPerson* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->grp);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->own);
	sqlite3_bind_int(stmtInsertRec, 3, rec->ixWDerivate);
	sqlite3_bind_int(stmtInsertRec, 4, rec->ixVSex);
	sqlite3_bind_text(stmtInsertRec, 5, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 6, rec->Firstname.c_str(), rec->Firstname.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 7, rec->refJLastname);
	sqlite3_bind_text(stmtInsertRec, 8, rec->Lastname.c_str(), rec->Lastname.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 9, rec->telRefADetail);
	sqlite3_bind_text(stmtInsertRec, 10, rec->telVal.c_str(), rec->telVal.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 11, rec->emlRefADetail);
	sqlite3_bind_text(stmtInsertRec, 12, rec->emlVal.c_str(), rec->emlVal.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 13, rec->Salutation.c_str(), rec->Salutation.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMPerson / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMPerson::insertRst(
			ListIdecMPerson& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMPerson::updateRec(
			IdecMPerson* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->grp);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->own);
	sqlite3_bind_int(stmtUpdateRec, 3, rec->ixWDerivate);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->ixVSex);
	sqlite3_bind_text(stmtUpdateRec, 5, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 6, rec->Firstname.c_str(), rec->Firstname.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 7, rec->refJLastname);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->Lastname.c_str(), rec->Lastname.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 9, rec->telRefADetail);
	sqlite3_bind_text(stmtUpdateRec, 10, rec->telVal.c_str(), rec->telVal.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 11, rec->emlRefADetail);
	sqlite3_bind_text(stmtUpdateRec, 12, rec->emlVal.c_str(), rec->emlVal.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 13, rec->Salutation.c_str(), rec->Salutation.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 14, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMPerson / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMPerson::updateRst(
			ListIdecMPerson& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMPerson::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMPerson / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMPerson::loadRecByRef(
			ubigint ref
			, IdecMPerson** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

