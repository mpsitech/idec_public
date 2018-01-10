/**
  * \file IdecQFilList.cpp
  * Dbs and XML wrapper for table TblIdecQFilList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecQFilList.h"

/******************************************************************************
 class IdecQFilList
 ******************************************************************************/

IdecQFilList::IdecQFilList(
			const ubigint qref
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Filename
			, const uint refIxVTbl
			, const string srefRefIxVTbl
			, const string titRefIxVTbl
			, const ubigint refUref
			, const string stubRefUref
			, const string osrefKContent
			, const string titOsrefKContent
			, const string srefKMimetype
			, const string titSrefKMimetype
			, const usmallint Size
		) {
	this->qref = qref;
	this->jref = jref;
	this->jnum = jnum;
	this->ref = ref;
	this->Filename = Filename;
	this->refIxVTbl = refIxVTbl;
	this->srefRefIxVTbl = srefRefIxVTbl;
	this->titRefIxVTbl = titRefIxVTbl;
	this->refUref = refUref;
	this->stubRefUref = stubRefUref;
	this->osrefKContent = osrefKContent;
	this->titOsrefKContent = titOsrefKContent;
	this->srefKMimetype = srefKMimetype;
	this->titSrefKMimetype = titSrefKMimetype;
	this->Size = Size;
};

void IdecQFilList::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool jnumattr
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "IdecQFilList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
	if (jnumattr) xmlTextWriterWriteAttribute(wr, BAD_CAST "jnum", BAD_CAST to_string(jnum).c_str());
	if (shorttags) {
		writeString(wr, "fnm", Filename);
		writeString(wr, "ret", srefRefIxVTbl);
		writeString(wr, "ret2", titRefIxVTbl);
		writeString(wr, "reu", stubRefUref);
		writeString(wr, "cnt", osrefKContent);
		writeString(wr, "cnt2", titOsrefKContent);
		writeString(wr, "mim", srefKMimetype);
		writeString(wr, "mim2", titSrefKMimetype);
		writeUint(wr, "siz", Size);
	} else {
		writeString(wr, "Filename", Filename);
		writeString(wr, "srefRefIxVTbl", srefRefIxVTbl);
		writeString(wr, "titRefIxVTbl", titRefIxVTbl);
		writeString(wr, "stubRefUref", stubRefUref);
		writeString(wr, "osrefKContent", osrefKContent);
		writeString(wr, "titOsrefKContent", titOsrefKContent);
		writeString(wr, "srefKMimetype", srefKMimetype);
		writeString(wr, "titSrefKMimetype", titSrefKMimetype);
		writeUint(wr, "Size", Size);
	};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class ListIdecQFilList
 ******************************************************************************/

ListIdecQFilList::ListIdecQFilList() {
};

ListIdecQFilList::ListIdecQFilList(
			const ListIdecQFilList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQFilList(*(src.nodes[i]));
};

ListIdecQFilList::~ListIdecQFilList() {
	clear();
};

void ListIdecQFilList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecQFilList::size() const {
	return(nodes.size());
};

void ListIdecQFilList::append(
			IdecQFilList* rec
		) {
	nodes.push_back(rec);
};

ListIdecQFilList& ListIdecQFilList::operator=(
			const ListIdecQFilList& src
		) {
	IdecQFilList* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecQFilList(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

void ListIdecQFilList::writeXML(
			xmlTextWriter* wr
			, string difftag
		) {
	// generate top XML tag
	if (difftag.length() == 0) difftag = "ListIdecQFilList";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, "row", true, true);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class TblIdecQFilList
 ******************************************************************************/

TblIdecQFilList::TblIdecQFilList() {
};

TblIdecQFilList::~TblIdecQFilList() {
};

bool TblIdecQFilList::loadRecBySQL(
			const string& sqlstr
			, IdecQFilList** rec
		) {
	return false;
};

ubigint TblIdecQFilList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQFilList& rst
		) {
	return 0;
};

void TblIdecQFilList::insertRec(
			IdecQFilList* rec
		) {
};

ubigint TblIdecQFilList::insertNewRec(
			IdecQFilList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Filename
			, const uint refIxVTbl
			, const string srefRefIxVTbl
			, const string titRefIxVTbl
			, const ubigint refUref
			, const string stubRefUref
			, const string osrefKContent
			, const string titOsrefKContent
			, const string srefKMimetype
			, const string titSrefKMimetype
			, const usmallint Size
		) {
	ubigint retval = 0;
	IdecQFilList* _rec = NULL;

	_rec = new IdecQFilList(0, jref, jnum, ref, Filename, refIxVTbl, srefRefIxVTbl, titRefIxVTbl, refUref, stubRefUref, osrefKContent, titOsrefKContent, srefKMimetype, titSrefKMimetype, Size);
	insertRec(_rec);

	retval = _rec->qref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecQFilList::appendNewRecToRst(
			ListIdecQFilList& rst
			, IdecQFilList** rec
			, const ubigint jref
			, const uint jnum
			, const ubigint ref
			, const string Filename
			, const uint refIxVTbl
			, const string srefRefIxVTbl
			, const string titRefIxVTbl
			, const ubigint refUref
			, const string stubRefUref
			, const string osrefKContent
			, const string titOsrefKContent
			, const string srefKMimetype
			, const string titSrefKMimetype
			, const usmallint Size
		) {
	ubigint retval = 0;
	IdecQFilList* _rec = NULL;

	retval = insertNewRec(&_rec, jref, jnum, ref, Filename, refIxVTbl, srefRefIxVTbl, titRefIxVTbl, refUref, stubRefUref, osrefKContent, titOsrefKContent, srefKMimetype, titSrefKMimetype, Size);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecQFilList::insertRst(
			ListIdecQFilList& rst
		) {
};

void TblIdecQFilList::updateRec(
			IdecQFilList* rec
		) {
};

void TblIdecQFilList::updateRst(
			ListIdecQFilList& rst
		) {
};

void TblIdecQFilList::removeRecByQref(
			ubigint qref
		) {
};

void TblIdecQFilList::removeRstByJref(
			ubigint jref
		) {
};

bool TblIdecQFilList::loadRecByQref(
			ubigint qref
			, IdecQFilList** rec
		) {
	return false;
};

ubigint TblIdecQFilList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQFilList& rst
		) {
	return 0;
};

/******************************************************************************
 class LiteTblIdecQFilList
 ******************************************************************************/

LiteTblIdecQFilList::LiteTblIdecQFilList() : TblIdecQFilList(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByQref = NULL;
	stmtRemoveRstByJref = NULL;

	stmtLoadRecByQref = NULL;
	stmtLoadRecByJref = NULL;
	stmtLoadRstByJref = NULL;
};

LiteTblIdecQFilList::~LiteTblIdecQFilList() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByQref) sqlite3_finalize(stmtRemoveRecByQref);
	if (stmtRemoveRstByJref) sqlite3_finalize(stmtRemoveRstByJref);

	if (stmtLoadRecByQref) sqlite3_finalize(stmtLoadRecByQref);
	if (stmtLoadRecByJref) sqlite3_finalize(stmtLoadRecByJref);
	if (stmtLoadRstByJref) sqlite3_finalize(stmtLoadRstByJref);
};

void LiteTblIdecQFilList::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecQFilList (jref, jnum, ref, Filename, refIxVTbl, refUref, osrefKContent, srefKMimetype, Size) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9)");
	stmtUpdateRec = createStatement("UPDATE TblIdecQFilList SET jref = ?1, jnum = ?2, ref = ?3, Filename = ?4, refIxVTbl = ?5, refUref = ?6, osrefKContent = ?7, srefKMimetype = ?8, Size = ?9 WHERE qref = ?10");
	stmtRemoveRecByQref = createStatement("DELETE FROM TblIdecQFilList WHERE qref = ?1");
	stmtRemoveRstByJref = createStatement("DELETE FROM TblIdecQFilList WHERE jref = ?1");

	stmtLoadRecByQref = createStatement("SELECT qref, jref, jnum, ref, Filename, refIxVTbl, refUref, osrefKContent, srefKMimetype, Size FROM TblIdecQFilList WHERE qref = ?1");
	stmtLoadRstByJref = createStatement("SELECT qref, jref, jnum, ref, Filename, refIxVTbl, refUref, osrefKContent, srefKMimetype, Size FROM TblIdecQFilList WHERE jref = ?1 ORDER BY jnum ASC");
};

bool LiteTblIdecQFilList::loadRec(
			sqlite3_stmt* stmt
			, IdecQFilList** rec
		) {
	int res;

	IdecQFilList* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecQFilList();

		_rec->qref = sqlite3_column_int64(stmt, 0);
		_rec->jref = sqlite3_column_int64(stmt, 1);
		_rec->jnum = sqlite3_column_int(stmt, 2);
		_rec->ref = sqlite3_column_int64(stmt, 3);
		_rec->Filename.assign((const char*) sqlite3_column_text(stmt, 4));
		_rec->refIxVTbl = sqlite3_column_int(stmt, 5);
		_rec->refUref = sqlite3_column_int64(stmt, 6);
		_rec->osrefKContent.assign((const char*) sqlite3_column_text(stmt, 7));
		_rec->srefKMimetype.assign((const char*) sqlite3_column_text(stmt, 8));
		_rec->Size = sqlite3_column_int(stmt, 9);

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

ubigint LiteTblIdecQFilList::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQFilList& rst
		) {
	int res; ubigint numread = 0;

	IdecQFilList* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecQFilList();

		rec->qref = sqlite3_column_int64(stmt, 0);
		rec->jref = sqlite3_column_int64(stmt, 1);
		rec->jnum = sqlite3_column_int(stmt, 2);
		rec->ref = sqlite3_column_int64(stmt, 3);
		rec->Filename.assign((const char*) sqlite3_column_text(stmt, 4));
		rec->refIxVTbl = sqlite3_column_int(stmt, 5);
		rec->refUref = sqlite3_column_int64(stmt, 6);
		rec->osrefKContent.assign((const char*) sqlite3_column_text(stmt, 7));
		rec->srefKMimetype.assign((const char*) sqlite3_column_text(stmt, 8));
		rec->Size = sqlite3_column_int(stmt, 9);

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecQFilList::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecQFilList** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecQFilList::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecQFilList& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecQFilList::loadRecBySQL(
			const string& sqlstr
			, IdecQFilList** rec
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

ubigint LiteTblIdecQFilList::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecQFilList& rst
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

void LiteTblIdecQFilList::insertRec(
			IdecQFilList* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->jref);
	sqlite3_bind_int(stmtInsertRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->ref);
	sqlite3_bind_text(stmtInsertRec, 4, rec->Filename.c_str(), rec->Filename.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtInsertRec, 5, rec->refIxVTbl);
	sqlite3_bind_int64(stmtInsertRec, 6, rec->refUref);
	sqlite3_bind_text(stmtInsertRec, 7, rec->osrefKContent.c_str(), rec->osrefKContent.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 8, rec->srefKMimetype.c_str(), rec->srefKMimetype.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtInsertRec, 9, rec->Size);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQFilList / stmtInsertRec)\n");

	rec->qref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecQFilList::insertRst(
			ListIdecQFilList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecQFilList::updateRec(
			IdecQFilList* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->jref);
	sqlite3_bind_int(stmtUpdateRec, 2, rec->jnum);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->ref);
	sqlite3_bind_text(stmtUpdateRec, 4, rec->Filename.c_str(), rec->Filename.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtUpdateRec, 5, rec->refIxVTbl);
	sqlite3_bind_int64(stmtUpdateRec, 6, rec->refUref);
	sqlite3_bind_text(stmtUpdateRec, 7, rec->osrefKContent.c_str(), rec->osrefKContent.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->srefKMimetype.c_str(), rec->srefKMimetype.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtUpdateRec, 9, rec->Size);
	sqlite3_bind_int64(stmtUpdateRec, 10, rec->qref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQFilList / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecQFilList::updateRst(
			ListIdecQFilList& rst
		) {
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecQFilList::removeRecByQref(
			ubigint qref
		) {
	sqlite3_bind_int64(stmtRemoveRecByQref, 1, qref);

	if (sqlite3_step(stmtRemoveRecByQref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQFilList / stmtRemoveRecByQref)\n");

	sqlite3_reset(stmtRemoveRecByQref);
};

void LiteTblIdecQFilList::removeRstByJref(
			ubigint jref
		) {
	sqlite3_bind_int64(stmtRemoveRstByJref, 1, jref);

	if (sqlite3_step(stmtRemoveRstByJref) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecQFilList / stmtRemoveRstByJref)\n");

	sqlite3_reset(stmtRemoveRstByJref);
};

bool LiteTblIdecQFilList::loadRecByQref(
			ubigint qref
			, IdecQFilList** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByQref, 1, qref);

	return loadRecByStmt(stmtLoadRecByQref, rec);
};

ubigint LiteTblIdecQFilList::loadRstByJref(
			ubigint jref
			, const bool append
			, ListIdecQFilList& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByJref, 1, jref);

	return loadRstByStmt(stmtLoadRstByJref, append, rst);
};

