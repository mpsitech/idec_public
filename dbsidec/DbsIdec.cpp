/**
  * \file DbsIdec.cpp
  * C++ wrapper for database DbsIdec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "DbsIdec.h"

#include "DbsIdec_vecs.cpp"

/******************************************************************************
 class DbsIdec
 ******************************************************************************/

DbsIdec::DbsIdec() {
	initdone = false;

	dbsLite = NULL;
};

DbsIdec::~DbsIdec() {
	term();
};

void DbsIdec::init(
			const uint _ixDbsVDbstype
			, const string& _dbspath
			, const string& _dbsname
			, const string& _ip
			, const uint _port
			, const string& _username
			, const string& _password
		) {
	ixDbsVDbstype = _ixDbsVDbstype;
	dbspath = _dbspath;
	dbsname = _dbsname;
	username = _username;
	password = _password;
	ip = _ip;
	port = _port;

	if (ixDbsVDbstype == VecDbsVDbstype::LITE) initLite();

	initdone = true;
};

void DbsIdec::term() {
	if (initdone) {
		if (ixDbsVDbstype == VecDbsVDbstype::LITE) termLite();

		initdone = false;
	};
};

void DbsIdec::initLite() {
	int res;

	res = sqlite3_open_v2(dbspath.c_str(), &dbsLite, SQLITE_OPEN_READWRITE | SQLITE_OPEN_NOMUTEX, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: connection failure");

	sqlite3_extended_result_codes(dbsLite, 1);

	tblidecaccrmuseruniversal = new LiteTblIdecAccRMUserUniversal();
	((LiteTblIdecAccRMUserUniversal*) tblidecaccrmuseruniversal)->init(dbsLite);
	tblidecampersondetail = new LiteTblIdecAMPersonDetail();
	((LiteTblIdecAMPersonDetail*) tblidecampersondetail)->init(dbsLite);
	tblidecamuseraccess = new LiteTblIdecAMUserAccess();
	((LiteTblIdecAMUserAccess*) tblidecamuseraccess)->init(dbsLite);
	tblidecamusergroupaccess = new LiteTblIdecAMUsergroupAccess();
	((LiteTblIdecAMUsergroupAccess*) tblidecamusergroupaccess)->init(dbsLite);
	tblidecavcontrolpar = new LiteTblIdecAVControlPar();
	((LiteTblIdecAVControlPar*) tblidecavcontrolpar)->init(dbsLite);
	tblidecavkeylistkey = new LiteTblIdecAVKeylistKey();
	((LiteTblIdecAVKeylistKey*) tblidecavkeylistkey)->init(dbsLite);
	tblidecavvaluelistval = new LiteTblIdecAVValuelistVal();
	((LiteTblIdecAVValuelistVal*) tblidecavvaluelistval)->init(dbsLite);
	tblideccfile = new LiteTblIdecCFile();
	((LiteTblIdecCFile*) tblideccfile)->init(dbsLite);
	tblidechistrmuseruniversal = new LiteTblIdecHistRMUserUniversal();
	((LiteTblIdecHistRMUserUniversal*) tblidechistrmuseruniversal)->init(dbsLite);
	tblidecjavkeylistkey = new LiteTblIdecJAVKeylistKey();
	((LiteTblIdecJAVKeylistKey*) tblidecjavkeylistkey)->init(dbsLite);
	tblidecjmpersonlastname = new LiteTblIdecJMPersonLastname();
	((LiteTblIdecJMPersonLastname*) tblidecjmpersonlastname)->init(dbsLite);
	tblidecjmuserstate = new LiteTblIdecJMUserState();
	((LiteTblIdecJMUserState*) tblidecjmuserstate)->init(dbsLite);
	tblidecmfile = new LiteTblIdecMFile();
	((LiteTblIdecMFile*) tblidecmfile)->init(dbsLite);
	tblidecmmission = new LiteTblIdecMMission();
	((LiteTblIdecMMission*) tblidecmmission)->init(dbsLite);
	tblidecmperson = new LiteTblIdecMPerson();
	((LiteTblIdecMPerson*) tblidecmperson)->init(dbsLite);
	tblidecmsession = new LiteTblIdecMSession();
	((LiteTblIdecMSession*) tblidecmsession)->init(dbsLite);
	tblidecmtour = new LiteTblIdecMTour();
	((LiteTblIdecMTour*) tblidecmtour)->init(dbsLite);
	tblidecmuser = new LiteTblIdecMUser();
	((LiteTblIdecMUser*) tblidecmuser)->init(dbsLite);
	tblidecmusergroup = new LiteTblIdecMUsergroup();
	((LiteTblIdecMUsergroup*) tblidecmusergroup)->init(dbsLite);
	tblidecrmusergroupuniversal = new LiteTblIdecRMUsergroupUniversal();
	((LiteTblIdecRMUsergroupUniversal*) tblidecrmusergroupuniversal)->init(dbsLite);
	tblidecrmusermusergroup = new LiteTblIdecRMUserMUsergroup();
	((LiteTblIdecRMUserMUsergroup*) tblidecrmusermusergroup)->init(dbsLite);

	tblidecqfillist = new LiteTblIdecQFilList();
	((LiteTblIdecQFilList*) tblidecqfillist)->init(dbsLite);
	tblidecqmis1ntour = new LiteTblIdecQMis1NTour();
	((LiteTblIdecQMis1NTour*) tblidecqmis1ntour)->init(dbsLite);
	tblidecqmislist = new LiteTblIdecQMisList();
	((LiteTblIdecQMisList*) tblidecqmislist)->init(dbsLite);
	tblidecqmisref1nfile = new LiteTblIdecQMisRef1NFile();
	((LiteTblIdecQMisRef1NFile*) tblidecqmisref1nfile)->init(dbsLite);
	tblidecqpreselect = new LiteTblIdecQPreselect();
	((LiteTblIdecQPreselect*) tblidecqpreselect)->init(dbsLite);
	tblidecqselect = new LiteTblIdecQSelect();
	((LiteTblIdecQSelect*) tblidecqselect)->init(dbsLite);
	tblidecqtoulist = new LiteTblIdecQTouList();
	((LiteTblIdecQTouList*) tblidecqtoulist)->init(dbsLite);
	tblidecqtouref1nfile = new LiteTblIdecQTouRef1NFile();
	((LiteTblIdecQTouRef1NFile*) tblidecqtouref1nfile)->init(dbsLite);
	tblidecqusgaaccess = new LiteTblIdecQUsgAAccess();
	((LiteTblIdecQUsgAAccess*) tblidecqusgaaccess)->init(dbsLite);
	tblidecqusglist = new LiteTblIdecQUsgList();
	((LiteTblIdecQUsgList*) tblidecqusglist)->init(dbsLite);
	tblidecqusgmnuser = new LiteTblIdecQUsgMNUser();
	((LiteTblIdecQUsgMNUser*) tblidecqusgmnuser)->init(dbsLite);
	tblidecqusr1nsession = new LiteTblIdecQUsr1NSession();
	((LiteTblIdecQUsr1NSession*) tblidecqusr1nsession)->init(dbsLite);
	tblidecqusraaccess = new LiteTblIdecQUsrAAccess();
	((LiteTblIdecQUsrAAccess*) tblidecqusraaccess)->init(dbsLite);
	tblidecqusrlist = new LiteTblIdecQUsrList();
	((LiteTblIdecQUsrList*) tblidecqusrlist)->init(dbsLite);
	tblidecqusrmnusergroup = new LiteTblIdecQUsrMNUsergroup();
	((LiteTblIdecQUsrMNUsergroup*) tblidecqusrmnusergroup)->init(dbsLite);
};

void DbsIdec::termLite() {
	sqlite3_close(dbsLite);
};

void DbsIdec::begin() {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) beginLite();
};

bool DbsIdec::commit() {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) return commitLite();

	return false;
};

void DbsIdec::rollback() {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) rollbackLite();
};

void DbsIdec::beginLite() {
	if (sqlite3_exec(dbsLite, "BEGIN", NULL, NULL, NULL) != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to begin transaction\n");
};

bool DbsIdec::commitLite() {
	if (sqlite3_exec(dbsLite, "COMMIT", NULL, NULL, NULL) != SQLITE_OK) {
		rollbackLite();
		return false;
	};

	return true;
};

void DbsIdec::rollbackLite() {
	if (sqlite3_exec(dbsLite, "ROLLBACK", NULL, NULL, NULL) != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to roll back transaction\n");
};

bool DbsIdec::loadUintBySQL(
			const string& sqlstr
			, uint& val
		) {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) return loadUintBySQLLite(sqlstr, val);

	return false;
};

bool DbsIdec::loadStringBySQL(
			const string& sqlstr
			, string& val
		) {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) return loadStringBySQLLite(sqlstr, val);

	return false;
};

bool DbsIdec::loadRefBySQL(
			const string& sqlstr
			, ubigint& ref
		) {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) return loadRefBySQLLite(sqlstr, ref);

	return false;
};

ubigint DbsIdec::loadRefsBySQL(
			const string& sqlstr
			, const bool append
			, vector<ubigint>& refs
		) {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) return loadRefsBySQLLite(sqlstr, append, refs);

	return 0;
};

bool DbsIdec::loadUintBySQLLite(
			const string& sqlstr
			, uint& val
		) {
	int res;
	sqlite3_stmt* stmt;

	bool retval = false;

	res = sqlite3_prepare_v2(dbsLite, sqlstr.c_str(), -1, &stmt, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		val = sqlite3_column_int(stmt, 0);

		res = sqlite3_step(stmt);
		if (res == SQLITE_DONE) retval = true;
	};

	sqlite3_finalize(stmt);

	return retval;
};

bool DbsIdec::loadStringBySQLLite(
			const string& sqlstr
			, string& val
		) {
	int res;
	sqlite3_stmt* stmt;

	bool retval = false;

	res = sqlite3_prepare_v2(dbsLite, sqlstr.c_str(), sqlstr.length()+1, &stmt, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		val.assign((const char*) sqlite3_column_text(stmt, 0));

		res = sqlite3_step(stmt);
		if (res == SQLITE_DONE) retval = true;
	};

	sqlite3_finalize(stmt);

	return retval;
};

bool DbsIdec::loadRefBySQLLite(
			const string& sqlstr
			, ubigint& val
		) {
	int res;
	sqlite3_stmt* stmt;

	bool retval = false;

	res = sqlite3_prepare_v2(dbsLite, sqlstr.c_str(), sqlstr.length()+1, &stmt, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) {
		val = sqlite3_column_int64(stmt, 0);

		res = sqlite3_step(stmt);
		if (res == SQLITE_DONE) retval = true;
	};

	sqlite3_finalize(stmt);

	return retval;
};

ubigint DbsIdec::loadRefsBySQLLite(
			const string& sqlstr
			, const bool append
			, vector<ubigint>& refs
		) {
	int res; ubigint numread = 0;
	sqlite3_stmt* stmt;

	res = sqlite3_prepare_v2(dbsLite, sqlstr.c_str(), sqlstr.length()+1, &stmt, NULL);
	if (res != SQLITE_OK) throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	if (!append) refs.resize(0);

	res = sqlite3_step(stmt);
	while (res == SQLITE_ROW) {
		refs.push_back(sqlite3_column_int64(stmt, 0));
		numread++;

		res = sqlite3_step(stmt);
	};

	sqlite3_finalize(stmt);

	return(numread);
};

void DbsIdec::executeQuery(
			const string& sqlstr
		) {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) {
		int res;

		res = sqlite3_exec(dbsLite, sqlstr.c_str(), NULL, NULL, NULL);
		if (res != SQLITE_OK)
			throw DbsException("DbsException / SQLite: failed to execute query '" + sqlstr + "'\n");

	};
};

void DbsIdec::executeQueryDiv(
			const string& sqlstrlite
		) {
	if (ixDbsVDbstype == VecDbsVDbstype::LITE) executeQuery(sqlstrlite);
};

void DbsIdec::executeFile(
			const string& fullpath
		) {
	string sqlstr = "";
	char c;
	
	ifstream sqlfile(fullpath.c_str());

	while (sqlfile.get(c)) {
		switch (c) {
			case '\n':
				break;
			case '\t':
				break;
			case ';':
				executeQuery(sqlstr);
				sqlstr = "";
				break;
			default:
				sqlstr = sqlstr + c;
				break;
		};
	};
	sqlfile.close();
};

void DbsIdec::fillFeedFromKlst(
			const uint klsIxIdecVKeylist
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	ListIdecAVKeylistKey klsAkeys;
	IdecAVKeylistKey* klsAkey = NULL;

	tblidecavkeylistkey->loadRstByKls(klsIxIdecVKeylist, false, klsAkeys);

	feed.clear();
	for (unsigned int i=0;i<klsAkeys.nodes.size();i++) {
		klsAkey = klsAkeys.nodes[i];

		tblidecjavkeylistkey->loadTitByKlkLcl(klsAkey->ref, ixIdecVLocale, klsAkey->Title);
		feed.appendIxSrefTitles(i+1, klsAkey->sref, klsAkey->Title);
	};
};

void DbsIdec::fillFeedFromKlstByMtbUref(
			const uint klsIxIdecVKeylist
			, const uint x1IxIdecVMaintable
			, const ubigint x1Uref
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	ListIdecAVKeylistKey klsAkeys;
	IdecAVKeylistKey* klsAkey = NULL;

	tblidecavkeylistkey->loadRstByKlsMtbUrf(klsIxIdecVKeylist, x1IxIdecVMaintable, x1Uref, false, klsAkeys);

	feed.clear();
	for (unsigned int i=0;i<klsAkeys.nodes.size();i++) {
		klsAkey = klsAkeys.nodes[i];

		tblidecjavkeylistkey->loadTitByKlkLcl(klsAkey->ref, ixIdecVLocale, klsAkey->Title);
		feed.appendIxSrefTitles(i+1, klsAkey->sref, klsAkey->Title);
	};
};

string DbsIdec::getKlstTitleBySref(
			const uint klsIxIdecVKeylist
			, const string& sref
			, const uint ixIdecVLocale
		) {
	string retval;

	ubigint refKlk;

	if (tblidecavkeylistkey->loadRefByKlsSrf(klsIxIdecVKeylist, sref, refKlk))
		if (!tblidecjavkeylistkey->loadTitByKlkLcl(refKlk, ixIdecVLocale, retval))
			tblidecavkeylistkey->loadTitByRef(refKlk, retval);

	return retval;
};

string DbsIdec::getKlstTitleByMtbUrefSref(
			const uint klsIxIdecVKeylist
			, const uint x1IxIdecVMaintable
			, const ubigint x1Uref
			, const string& sref
			, const uint ixIdecVLocale
		) {
	string retval;

	ubigint refKlk;

	if (tblidecavkeylistkey->loadRefByKlsMtbUrfSrf(klsIxIdecVKeylist, x1IxIdecVMaintable, x1Uref, sref, refKlk))
		if (!tblidecjavkeylistkey->loadTitByKlkLcl(refKlk, ixIdecVLocale, retval))
			tblidecavkeylistkey->loadTitByRef(refKlk, retval);

	return retval;
};

void DbsIdec::fillFeedFromVlst(
			const uint vlsIxIdecVValuelist
			, const uint x1IxIdecVLocale
			, Feed& feed
		) {
	ListIdecAVValuelistVal vlsAvals;
	IdecAVValuelistVal* vlsAval = NULL;

	tblidecavvaluelistval->loadRstByVlsLcl(vlsIxIdecVValuelist, x1IxIdecVLocale, false, vlsAvals);

	feed.clear();
	for (unsigned int i=0;i<vlsAvals.nodes.size();i++) {
		vlsAval = vlsAvals.nodes[i];

		feed.appendTitles(vlsAval->Val);
	};
};

