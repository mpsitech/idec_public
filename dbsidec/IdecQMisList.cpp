/**
  * \file IdecQMisList.cpp
  * Dbs and XML wrapper for table TblIdecQMisList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQMisList.h"

/******************************************************************************
 class IdecQMisList
 ******************************************************************************/

IdecQMisList::IdecQMisList(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Title
			, const ubigint grp
			, const string stubGrp
			, const ubigint own
			, const string stubOwn
			, const uint startd
			, const string ftmStartd
			, const uint stopd
			, const string ftmStopd
			, const string srefKCountry
			, const string titSrefKCountry
			, const string Region
			, const string Municipality
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->Title = Title;
	this->grp = grp;
	this->stubGrp = stubGrp;
	this->own = own;
	this->stubOwn = stubOwn;
	this->startd = startd;
	this->ftmStartd = ftmStartd;
	this->stopd = stopd;
	this->ftmStopd = ftmStopd;
	this->srefKCountry = srefKCountry;
	this->titSrefKCountry = titSrefKCountry;
	this->Region = Region;
	this->Municipality = Municipality;
};

void IdecQMisList::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQMisList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "tit", Title);
		writeString(wr, "grp", stubGrp);
		writeString(wr, "own", stubOwn);
		writeString(wr, "sta", ftmStartd);
		writeString(wr, "sto", ftmStopd);
		writeString(wr, "cry", srefKCountry);
		writeString(wr, "cry2", titSrefKCountry);
		writeString(wr, "reg", Region);
		writeString(wr, "mun", Municipality);
	} else {
		writeString(wr, "Title", Title);
		writeString(wr, "stubGrp", stubGrp);
		writeString(wr, "stubOwn", stubOwn);
		writeString(wr, "ftmStartd", ftmStartd);
		writeString(wr, "ftmStopd", ftmStopd);
		writeString(wr, "srefKCountry", srefKCountry);
		writeString(wr, "titSrefKCountry", titSrefKCountry);
		writeString(wr, "Region", Region);
		writeString(wr, "Municipality", Municipality);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQMisList
 ******************************************************************************/

ListIdecQMisList::ListIdecQMisList() {
};

ListIdecQMisList::ListIdecQMisList(
			const ListIdecQMisList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMisList(*(src.nodes[i]));
};

ListIdecQMisList::~ListIdecQMisList() {
	clear();
};

void ListIdecQMisList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQMisList::size() const {
	return(nodes.size());
};

void ListIdecQMisList::append(
			IdecQMisList* rec
		) {
	nodes.push_back(rec);
};

ListIdecQMisList& ListIdecQMisList::operator=(
			const ListIdecQMisList& src
		) {
	IdecQMisList* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQMisList(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQMisList::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQMisList";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQMisList
 ******************************************************************************/

TblIdecQMisList::TblIdecQMisList() {
};

TblIdecQMisList::~TblIdecQMisList() {
};

bool TblIdecQMisList::loadRecBySQL(
			const string& sqlstr
			, IdecQMisList** rec
		) {
	return false;
};

ubigint TblIdecQMisList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQMisList& rst
		) {
	return 0;
};

void TblIdecQMisList::insertRec(
			IdecQMisList* rec
		) {
};

ubigint TblIdecQMisList::insertNewRec(
			IdecQMisList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Title
			, const ubigint grp
			, const string stubGrp
			, const ubigint own
			, const string stubOwn
			, const uint startd
			, const string ftmStartd
			, const uint stopd
			, const string ftmStopd
			, const string srefKCountry
			, const string titSrefKCountry
			, const string Region
			, const string Municipality
		) {
	ubigint retval = 0;
	IdecQMisList* _rec = NULL;

	_rec = new IdecQMisList(0, jref, jnum, ref, Title, grp, stubGrp, own, stubOwn, startd, ftmStartd, stopd, ftmStopd, srefKCountry, titSrefKCountry, Region, Municipality);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQMisList::appendNewRecToRst(
			ListIdecQMisList& rst
			, IdecQMisList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Title
			, const ubigint grp
			, const string stubGrp
			, const ubigint own
			, const string stubOwn
			, const uint startd
			, const string ftmStartd
			, const uint stopd
			, const string ftmStopd
			, const string srefKCountry
			, const string titSrefKCountry
			, const string Region
			, const string Municipality
		) {
	ubigint retval = 0;
	IdecQMisList* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, Title, grp, stubGrp, own, stubOwn, startd, ftmStartd, stopd, ftmStopd, srefKCountry, titSrefKCountry, Region, Municipality);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQMisList::insertRst(
			ListIdecQMisList& rst
		) {
};

void TblIdecQMisList::updateRec(
			IdecQMisList* rec
		) {
};

void TblIdecQMisList::updateRst(
			ListIdecQMisList& rst
		) {
};

void TblIdecQMisList::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQMisList::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQMisList::loadRecByQref(
			ubigint qref
			, IdecQMisList** rec
		) {
	return false;
};

ubigint TblIdecQMisList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQMisList& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQMisList
 ******************************************************************************/

LiteTblIdecQMisList::LiteTblIdecQMisList() : TblIdecQMisList(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQMisList::~LiteTblIdecQMisList() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQMisList::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQMisList (jref, jnum, ref, Title, grp, own, startd, stopd, srefKCountry, Region, Municipality) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9,?10,?11)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQMisList SET jref = ?1, jnum = ?2, ref = ?3, Title = ?4, grp = ?5, own = ?6, startd = ?7, stopd = ?8, srefKCountry = ?9, Region = ?10, Municipality = ?11 WHERE qref = ?12");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQMisList WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQMisList WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref, Title, grp, own, startd, stopd, srefKCountry, Region, Municipality FROM TblIdecQMisList WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref, Title, grp, own, startd, stopd, srefKCountry, Region, Municipality FROM TblIdecQMisList WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQMisList::loadRec(
			sqlite3_stmt* stmt
			, IdecQMisList** rec
		) {
	int res;

	IdecQMisList* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQMisList();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);
		_rec->Title.assign((const char*) sqlite3_column_text(stmt, 4));
		_rec->grp = sqlite3_column_int64(stmt, 5);
		_rec->own = sqlite3_column_int64(stmt, 6);
		_rec->startd = sqlite3_column_int(stmt, 7);
		_rec->stopd = sqlite3_column_int(stmt, 8);
		_rec->srefKCountry.assign((const char*) sqlite3_column_text(stmt, 9));
		_rec->Region.assign((const char*) sqlite3_column_text(stmt, 10));
		_rec->Municipality.assign((const char*) sqlite3_column_text(stmt, 11));

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

ubigint LiteTblIdecQMisList::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQMisList& rst
		) {
	int res; ubigint numread = 0;

	IdecQMisList* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQMisList();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);
		rec->Title.assign((const char*) sqlite3_column_text(stmt, 4));
		rec->grp = sqlite3_column_int64(stmt, 5);
		rec->own = sqlite3_column_int64(stmt, 6);
		rec->startd = sqlite3_column_int(stmt, 7);
		rec->stopd = sqlite3_column_int(stmt, 8);
		rec->srefKCountry.assign((const char*) sqlite3_column_text(stmt, 9));
		rec->Region.assign((const char*) sqlite3_column_text(stmt, 10));
		rec->Municipality.assign((const char*) sqlite3_column_text(stmt, 11));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQMisList::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQMisList** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQMisList::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQMisList& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQMisList::loadRecBySQL(
			const string& sqlstr
			, IdecQMisList** rec
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

ubigint LiteTblIdecQMisList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQMisList& rst
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

void LiteTblIdecQMisList::insertRec(
			IdecQMisList* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtInsertRec, 5, rec->grp);
	sqlite3_bind_int64(stmtInsertRec, 6, rec->own);
	sqlite3_bind_int(stmtInsertRec, 7, rec->startd);
	sqlite3_bind_int(stmtInsertRec, 8, rec->stopd);
	sqlite3_bind_text(stmtInsertRec, 9, rec->srefKCountry.c_str(), rec->srefKCountry.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 10, rec->Region.c_str(), rec->Region.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 11, rec->Municipality.c_str(), rec->Municipality.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisList / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQMisList::insertRst(
			ListIdecQMisList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQMisList::updateRec(
			IdecQMisList* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Title.c_str(), rec->Title.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->grp);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->own);
	sqlite3_bind_int(stmtUpdateRec, 7, rec->startd);
	sqlite3_bind_int(stmtUpdateRec, 8, rec->stopd);
	sqlite3_bind_text(stmtUpdateRec, 9, rec->srefKCountry.c_str(), rec->srefKCountry.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 10, rec->Region.c_str(), rec->Region.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 11, rec->Municipality.c_str(), rec->Municipality.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 12, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisList / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQMisList::updateRst(
			ListIdecQMisList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQMisList::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisList / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQMisList::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQMisList / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQMisList::loadRecByQref(
			ubigint qref
			, IdecQMisList** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQMisList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQMisList& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

