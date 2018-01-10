/**
  * \file IdecMFile.cpp
  * database access for table TblIdecMFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "IdecMFile.h"

#include "IdecMFile_vecs.cpp"

/******************************************************************************
 class IdecMFile
 ******************************************************************************/

IdecMFile::IdecMFile(
			const ubigint ref
			, const ubigint grp
			, const ubigint own
			, const ubigint refIdecCFile
			, const uint refIxVTbl
			, const ubigint refUref
			, const string osrefKContent
			, const uint Archived
			, const string Filename
			, const string Archivename
			, const string srefKMimetype
			, const usmallint Size
			, const string Comment
		) {

	this->ref = ref;
	this->grp = grp;
	this->own = own;
	this->refIdecCFile = refIdecCFile;
	this->refIxVTbl = refIxVTbl;
	this->refUref = refUref;
	this->osrefKContent = osrefKContent;
	this->Archived = Archived;
	this->Filename = Filename;
	this->Archivename = Archivename;
	this->srefKMimetype = srefKMimetype;
	this->Size = Size;
	this->Comment = Comment;
};

bool IdecMFile::operator==(
			const IdecMFile& comp
		) {
	return false;
};

bool IdecMFile::operator!=(
			const IdecMFile& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class ListIdecMFile
 ******************************************************************************/

ListIdecMFile::ListIdecMFile() {
};

ListIdecMFile::ListIdecMFile(
			const ListIdecMFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecMFile(*(src.nodes[i]));
};

ListIdecMFile::~ListIdecMFile() {
	clear();
};

void ListIdecMFile::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

unsigned int ListIdecMFile::size() const {
	return(nodes.size());
};

void ListIdecMFile::append(
			IdecMFile* rec
		) {
	nodes.push_back(rec);
};

IdecMFile* ListIdecMFile::operator[](
			const uint ix
		) {
	IdecMFile* retval = NULL;

	if (ix < size()) retval = nodes[ix];

	return retval;
};

ListIdecMFile& ListIdecMFile::operator=(
			const ListIdecMFile& src
		) {
	IdecMFile* rec;

	if (&src != this) {
		clear();
		for (unsigned int i=0;i<src.size();i++) {
			rec = new IdecMFile(*(src.nodes[i]));
			nodes.push_back(rec);
		};
	};

	return(*this);
};

bool ListIdecMFile::operator==(
			const ListIdecMFile& comp
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

bool ListIdecMFile::operator!=(
			const ListIdecMFile& comp
		) {
	return(!operator==(comp));
};

/******************************************************************************
 class TblIdecMFile
 ******************************************************************************/

TblIdecMFile::TblIdecMFile() {
};

TblIdecMFile::~TblIdecMFile() {
};

bool TblIdecMFile::loadRecBySQL(
			const string& sqlstr
			, IdecMFile** rec
		) {
	return false;
};

ubigint TblIdecMFile::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMFile& rst
		) {
	return 0;
};

void TblIdecMFile::insertRec(
			IdecMFile* rec
		) {
};

ubigint TblIdecMFile::insertNewRec(
			IdecMFile** rec
			, const ubigint grp
			, const ubigint own
			, const ubigint refIdecCFile
			, const uint refIxVTbl
			, const ubigint refUref
			, const string osrefKContent
			, const uint Archived
			, const string Filename
			, const string Archivename
			, const string srefKMimetype
			, const usmallint Size
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMFile* _rec = NULL;

	_rec = new IdecMFile(0, grp, own, refIdecCFile, refIxVTbl, refUref, osrefKContent, Archived, Filename, Archivename, srefKMimetype, Size, Comment);
	insertRec(_rec);

	retval = _rec->ref;

	if (rec == NULL) delete _rec;
	else *rec = _rec;

	return retval;
};

ubigint TblIdecMFile::appendNewRecToRst(
			ListIdecMFile& rst
			, IdecMFile** rec
			, const ubigint grp
			, const ubigint own
			, const ubigint refIdecCFile
			, const uint refIxVTbl
			, const ubigint refUref
			, const string osrefKContent
			, const uint Archived
			, const string Filename
			, const string Archivename
			, const string srefKMimetype
			, const usmallint Size
			, const string Comment
		) {
	ubigint retval = 0;
	IdecMFile* _rec = NULL;

	retval = insertNewRec(&_rec, grp, own, refIdecCFile, refIxVTbl, refUref, osrefKContent, Archived, Filename, Archivename, srefKMimetype, Size, Comment);
	rst.nodes.push_back(_rec);

	if (rec != NULL) *rec = _rec;

	return retval;
};

void TblIdecMFile::insertRst(
			ListIdecMFile& rst
			, bool transact
		) {
};

void TblIdecMFile::updateRec(
			IdecMFile* rec
		) {
};

void TblIdecMFile::updateRst(
			ListIdecMFile& rst
			, bool transact
		) {
};

void TblIdecMFile::removeRecByRef(
			ubigint ref
		) {
};

bool TblIdecMFile::loadRecByRef(
			ubigint ref
			, IdecMFile** rec
		) {
	return false;
};

bool TblIdecMFile::loadFnmByRef(
			ubigint ref
			, string& Filename
		) {
	return false;
};

ubigint TblIdecMFile::loadRefsByClu(
			ubigint refIdecCFile
			, const bool append
			, vector<ubigint>& refs
		) {
	return 0;
};

ubigint TblIdecMFile::loadRstByClu(
			ubigint refIdecCFile
			, const bool append
			, ListIdecMFile& rst
		) {
	return 0;
};

ubigint TblIdecMFile::loadRstByRetReu(
			uint refIxVTbl
			, ubigint refUref
			, const bool append
			, ListIdecMFile& rst
		) {
	return 0;
};

ubigint TblIdecMFile::loadRstByRefs(
			vector<ubigint>& refs
			, const bool append
			, ListIdecMFile& rst
		) {
	ubigint numload = 0;
	IdecMFile* rec = NULL;

	if (!append) rst.clear();

	for (unsigned int i=0;i<refs.size();i++) if (loadRecByRef(refs[i], &rec)) {
		rst.nodes.push_back(rec);
		numload++;
	};

	return numload;
};

/******************************************************************************
 class LiteTblIdecMFile
 ******************************************************************************/

LiteTblIdecMFile::LiteTblIdecMFile() : TblIdecMFile(), LiteTable() {
	stmtInsertRec = NULL;
	stmtUpdateRec = NULL;
	stmtRemoveRecByRef = NULL;

	stmtLoadFnmByRef = NULL;
	stmtLoadRefsByClu = NULL;
	stmtLoadRstByClu = NULL;
	stmtLoadRstByRetReu = NULL;
};

LiteTblIdecMFile::~LiteTblIdecMFile() {
	if (stmtInsertRec) sqlite3_finalize(stmtInsertRec);
	if (stmtUpdateRec) sqlite3_finalize(stmtUpdateRec);
	if (stmtRemoveRecByRef) sqlite3_finalize(stmtRemoveRecByRef);

	if (stmtLoadFnmByRef) sqlite3_finalize(stmtLoadFnmByRef);
	if (stmtLoadRefsByClu) sqlite3_finalize(stmtLoadRefsByClu);
	if (stmtLoadRstByClu) sqlite3_finalize(stmtLoadRstByClu);
	if (stmtLoadRstByRetReu) sqlite3_finalize(stmtLoadRstByRetReu);
};

void LiteTblIdecMFile::initStatements() {
	stmtInsertRec = createStatement("INSERT INTO TblIdecMFile (grp, own, refIdecCFile, refIxVTbl, refUref, osrefKContent, Archived, Filename, Archivename, srefKMimetype, Size, Comment) VALUES (?1,?2,?3,?4,?5,?6,?7,?8,?9,?10,?11,?12)");
	stmtUpdateRec = createStatement("UPDATE TblIdecMFile SET grp = ?1, own = ?2, refIdecCFile = ?3, refIxVTbl = ?4, refUref = ?5, osrefKContent = ?6, Archived = ?7, Filename = ?8, Archivename = ?9, srefKMimetype = ?10, Size = ?11, Comment = ?12 WHERE ref = ?13");
	stmtRemoveRecByRef = createStatement("DELETE FROM TblIdecMFile WHERE ref = ?1");

	stmtLoadRecByRef = createStatement("SELECT ref, grp, own, refIdecCFile, refIxVTbl, refUref, osrefKContent, Archived, Filename, Archivename, srefKMimetype, Size, Comment FROM TblIdecMFile WHERE ref = ?1");
	stmtLoadFnmByRef = createStatement("SELECT Filename FROM TblIdecMFile WHERE ref = ?1");
	stmtLoadRefsByClu = createStatement("SELECT ref FROM TblIdecMFile WHERE refIdecCFile = ?1");
	stmtLoadRstByClu = createStatement("SELECT ref, grp, own, refIdecCFile, refIxVTbl, refUref, osrefKContent, Archived, Filename, Archivename, srefKMimetype, Size, Comment FROM TblIdecMFile WHERE refIdecCFile = ?1");
	stmtLoadRstByRetReu = createStatement("SELECT ref, grp, own, refIdecCFile, refIxVTbl, refUref, osrefKContent, Archived, Filename, Archivename, srefKMimetype, Size, Comment FROM TblIdecMFile WHERE refIxVTbl = ?1 AND refUref = ?2 ORDER BY Filename ASC");
};

bool LiteTblIdecMFile::loadRec(
			sqlite3_stmt* stmt
			, IdecMFile** rec
		) {
	int res;

	IdecMFile* _rec = NULL;
	bool retval = false;

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		_rec = new IdecMFile();

		_rec->ref = sqlite3_column_int64(stmt, 0);
		_rec->grp = sqlite3_column_int64(stmt, 1);
		_rec->own = sqlite3_column_int64(stmt, 2);
		_rec->refIdecCFile = sqlite3_column_int64(stmt, 3);
		_rec->refIxVTbl = sqlite3_column_int(stmt, 4);
		_rec->refUref = sqlite3_column_int64(stmt, 5);
		_rec->osrefKContent.assign((const char*) sqlite3_column_text(stmt, 6));
		_rec->Archived = sqlite3_column_int(stmt, 7);
		_rec->Filename.assign((const char*) sqlite3_column_text(stmt, 8));
		_rec->Archivename.assign((const char*) sqlite3_column_text(stmt, 9));
		_rec->srefKMimetype.assign((const char*) sqlite3_column_text(stmt, 10));
		_rec->Size = sqlite3_column_int(stmt, 11);
		_rec->Comment.assign((const char*) sqlite3_column_text(stmt, 12));

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

ubigint LiteTblIdecMFile::loadRst(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMFile& rst
		) {
	int res; ubigint numread = 0;

	IdecMFile* rec;

	if (!append) rst.clear();

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		rec = new IdecMFile();

		rec->ref = sqlite3_column_int64(stmt, 0);
		rec->grp = sqlite3_column_int64(stmt, 1);
		rec->own = sqlite3_column_int64(stmt, 2);
		rec->refIdecCFile = sqlite3_column_int64(stmt, 3);
		rec->refIxVTbl = sqlite3_column_int(stmt, 4);
		rec->refUref = sqlite3_column_int64(stmt, 5);
		rec->osrefKContent.assign((const char*) sqlite3_column_text(stmt, 6));
		rec->Archived = sqlite3_column_int(stmt, 7);
		rec->Filename.assign((const char*) sqlite3_column_text(stmt, 8));
		rec->Archivename.assign((const char*) sqlite3_column_text(stmt, 9));
		rec->srefKMimetype.assign((const char*) sqlite3_column_text(stmt, 10));
		rec->Size = sqlite3_column_int(stmt, 11);
		rec->Comment.assign((const char*) sqlite3_column_text(stmt, 12));

		rst.nodes.push_back(rec);

		numread++;

		res = sqlite3_step(stmt);
	};

	return(numread);
};

bool LiteTblIdecMFile::loadRecByStmt(
			sqlite3_stmt* stmt
			, IdecMFile** rec
		) {
	bool retval = loadRec(stmt, rec);

	sqlite3_reset(stmt);

	return retval;
};

ubigint LiteTblIdecMFile::loadRstByStmt(
			sqlite3_stmt* stmt
			, const bool append
			, ListIdecMFile& rst
		) {
	ubigint retval = loadRst(stmt, append, rst);

	sqlite3_reset(stmt);

	return retval;
};

bool LiteTblIdecMFile::loadRecBySQL(
			const string& sqlstr
			, IdecMFile** rec
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

ubigint LiteTblIdecMFile::loadRstBySQL(
			const string& sqlstr
			, const bool append
			, ListIdecMFile& rst
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

void LiteTblIdecMFile::insertRec(
			IdecMFile* rec
		) {
	sqlite3_bind_int64(stmtInsertRec, 1, rec->grp);
	sqlite3_bind_int64(stmtInsertRec, 2, rec->own);
	sqlite3_bind_int64(stmtInsertRec, 3, rec->refIdecCFile);
	sqlite3_bind_int(stmtInsertRec, 4, rec->refIxVTbl);
	sqlite3_bind_int64(stmtInsertRec, 5, rec->refUref);
	sqlite3_bind_text(stmtInsertRec, 6, rec->osrefKContent.c_str(), rec->osrefKContent.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtInsertRec, 7, rec->Archived);
	sqlite3_bind_text(stmtInsertRec, 8, rec->Filename.c_str(), rec->Filename.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 9, rec->Archivename.c_str(), rec->Archivename.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtInsertRec, 10, rec->srefKMimetype.c_str(), rec->srefKMimetype.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtInsertRec, 11, rec->Size);
	sqlite3_bind_text(stmtInsertRec, 12, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);

	if (sqlite3_step(stmtInsertRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMFile / stmtInsertRec)\n");
	rec->ref = sqlite3_last_insert_rowid(dbs);

	sqlite3_reset(stmtInsertRec);
};

void LiteTblIdecMFile::insertRst(
			ListIdecMFile& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) insertRec(rst.nodes[i]);
};

void LiteTblIdecMFile::updateRec(
			IdecMFile* rec
		) {
	sqlite3_bind_int64(stmtUpdateRec, 1, rec->grp);
	sqlite3_bind_int64(stmtUpdateRec, 2, rec->own);
	sqlite3_bind_int64(stmtUpdateRec, 3, rec->refIdecCFile);
	sqlite3_bind_int(stmtUpdateRec, 4, rec->refIxVTbl);
	sqlite3_bind_int64(stmtUpdateRec, 5, rec->refUref);
	sqlite3_bind_text(stmtUpdateRec, 6, rec->osrefKContent.c_str(), rec->osrefKContent.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtUpdateRec, 7, rec->Archived);
	sqlite3_bind_text(stmtUpdateRec, 8, rec->Filename.c_str(), rec->Filename.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 9, rec->Archivename.c_str(), rec->Archivename.length(), SQLITE_STATIC);
	sqlite3_bind_text(stmtUpdateRec, 10, rec->srefKMimetype.c_str(), rec->srefKMimetype.length(), SQLITE_STATIC);
	sqlite3_bind_int(stmtUpdateRec, 11, rec->Size);
	sqlite3_bind_text(stmtUpdateRec, 12, rec->Comment.c_str(), rec->Comment.length(), SQLITE_STATIC);
	sqlite3_bind_int64(stmtUpdateRec, 13, rec->ref);

	if (sqlite3_step(stmtUpdateRec) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMFile / stmtUpdateRec)\n");

	sqlite3_reset(stmtUpdateRec);
};

void LiteTblIdecMFile::updateRst(
			ListIdecMFile& rst
			, bool transact
		) {
	if (transact) begin();
	for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
	if (transact) if (!commit()) for (unsigned int i=0;i<rst.nodes.size();i++) updateRec(rst.nodes[i]);
};

void LiteTblIdecMFile::removeRecByRef(
			ubigint ref
		) {
	sqlite3_bind_int64(stmtRemoveRecByRef, 1, ref);

	if (sqlite3_step(stmtRemoveRecByRef) != SQLITE_DONE) throw DbsException("DbsException / SQLite: error executing statement! (TblIdecMFile / stmtRemoveRecByRef)\n");

	sqlite3_reset(stmtRemoveRecByRef);
};

bool LiteTblIdecMFile::loadRecByRef(
			ubigint ref
			, IdecMFile** rec
		) {
	sqlite3_bind_int64(stmtLoadRecByRef, 1, ref);

	return loadRecByStmt(stmtLoadRecByRef, rec);
};

bool LiteTblIdecMFile::loadFnmByRef(
			ubigint ref
			, string& Filename
		) {
	sqlite3_bind_int64(stmtLoadFnmByRef, 1, ref);

	return loadStringByStmt(stmtLoadFnmByRef, Filename);
};

ubigint LiteTblIdecMFile::loadRefsByClu(
			ubigint refIdecCFile
			, const bool append
			, vector<ubigint>& refs
		) {
	sqlite3_bind_int64(stmtLoadRefsByClu, 1, refIdecCFile);

	return loadRefsByStmt(stmtLoadRefsByClu, append, refs);
};

ubigint LiteTblIdecMFile::loadRstByClu(
			ubigint refIdecCFile
			, const bool append
			, ListIdecMFile& rst
		) {
	sqlite3_bind_int64(stmtLoadRstByClu, 1, refIdecCFile);

	return loadRstByStmt(stmtLoadRstByClu, append, rst);
};

ubigint LiteTblIdecMFile::loadRstByRetReu(
			uint refIxVTbl
			, ubigint refUref
			, const bool append
			, ListIdecMFile& rst
		) {
	sqlite3_bind_int(stmtLoadRstByRetReu, 1, refIxVTbl);
	sqlite3_bind_int64(stmtLoadRstByRetReu, 2, refUref);

	return loadRstByStmt(stmtLoadRstByRetReu, append, rst);
};

