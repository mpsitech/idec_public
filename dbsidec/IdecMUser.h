/**
  * \file IdecMUser.h
  * database access for table TblIdecMUser (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMUSER_H
#define IDECMUSER_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

#define VecIdecVMUserState TblIdecMUser::VecVState

/**
  * IdecMUser: record of TblIdecMUser
  */
class IdecMUser {

public:
	IdecMUser(const ubigint ref = 0, const ubigint grp = 0, const ubigint own = 0, const ubigint refRUsergroup = 0, const ubigint refIdecMUsergroup = 0, const ubigint refIdecMPerson = 0, const string sref = "", const ubigint refJState = 0, const uint ixVState = 0, const uint ixIdecVLocale = 0, const uint ixIdecVUserlevel = 0, const string Password = "");

public:
	ubigint ref;
	ubigint grp;
	ubigint own;
	ubigint refRUsergroup;
	ubigint refIdecMUsergroup;
	ubigint refIdecMPerson;
	string sref;
	ubigint refJState;
	uint ixVState;
	uint ixIdecVLocale;
	uint ixIdecVUserlevel;
	string Password;

public:
	bool operator==(const IdecMUser& comp);
	bool operator!=(const IdecMUser& comp);
};

/**
  * ListIdecMUser: recordset of TblIdecMUser
  */
class ListIdecMUser {

public:
	ListIdecMUser();
	ListIdecMUser(const ListIdecMUser& src);
	~ListIdecMUser();

	void clear();
	unsigned int size() const;
	void append(IdecMUser* rec);

	IdecMUser* operator[](const uint ix);
	ListIdecMUser& operator=(const ListIdecMUser& src);
	bool operator==(const ListIdecMUser& comp);
	bool operator!=(const ListIdecMUser& comp);

public:
	vector<IdecMUser*> nodes;
};

/**
  * TblIdecMUser: C++ wrapper for table TblIdecMUser
  */
class TblIdecMUser {

public:
	/**
		* VecVState (full: VecIdecVMUserState)
		*/
	class VecVState {

	public:
		static const uint ACT = 1;
		static const uint DSG = 2;
		static const uint DUE = 3;
		static const uint EXP = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

public:
	TblIdecMUser();
	virtual ~TblIdecMUser();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMUser** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMUser& rst);

	virtual void insertRec(IdecMUser* rec);
	ubigint insertNewRec(IdecMUser** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const ubigint refRUsergroup = 0, const ubigint refIdecMUsergroup = 0, const ubigint refIdecMPerson = 0, const string sref = "", const ubigint refJState = 0, const uint ixVState = 0, const uint ixIdecVLocale = 0, const uint ixIdecVUserlevel = 0, const string Password = "");
	ubigint appendNewRecToRst(ListIdecMUser& rst, IdecMUser** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const ubigint refRUsergroup = 0, const ubigint refIdecMUsergroup = 0, const ubigint refIdecMPerson = 0, const string sref = "", const ubigint refJState = 0, const uint ixVState = 0, const uint ixIdecVLocale = 0, const uint ixIdecVUserlevel = 0, const string Password = "");
	virtual void insertRst(ListIdecMUser& rst, bool transact = false);
	virtual void updateRec(IdecMUser* rec);
	virtual void updateRst(ListIdecMUser& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMUser** rec);
	virtual bool loadRecByPrs(ubigint refIdecMPerson, IdecMUser** rec);
	virtual bool loadRecBySrf(string sref, IdecMUser** rec);
	virtual bool loadRefByPrs(ubigint refIdecMPerson, ubigint& ref);
	virtual bool loadRefBySrf(string sref, ubigint& ref);
	virtual bool loadRefBySrfPwd(string sref, string Password, ubigint& ref);
	virtual ubigint loadRefsByUsg(ubigint refIdecMUsergroup, const bool append, vector<ubigint>& refs);
	virtual bool loadSrfByRef(ubigint ref, string& sref);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMUser& rst);
};

/**
  * LiteTblIdecMUser: C++ wrapper for table TblIdecMUser (SQLite database)
  */
class LiteTblIdecMUser : public TblIdecMUser, public LiteTable {

public:
	LiteTblIdecMUser();
	~LiteTblIdecMUser();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;
	sqlite3_stmt* stmtLoadRecByPrs;
	sqlite3_stmt* stmtLoadRecBySrf;
	sqlite3_stmt* stmtLoadRefByPrs;
	sqlite3_stmt* stmtLoadRefBySrf;
	sqlite3_stmt* stmtLoadRefBySrfPwd;
	sqlite3_stmt* stmtLoadRefsByUsg;
	sqlite3_stmt* stmtLoadSrfByRef;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMUser** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMUser& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMUser** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMUser** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMUser& rst);

	void insertRec(IdecMUser* rec);
	void insertRst(ListIdecMUser& rst, bool transact = false);
	void updateRec(IdecMUser* rec);
	void updateRst(ListIdecMUser& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMUser** rec);
	bool loadRecByPrs(ubigint refIdecMPerson, IdecMUser** rec);
	bool loadRecBySrf(string sref, IdecMUser** rec);
	bool loadRefByPrs(ubigint refIdecMPerson, ubigint& ref);
	bool loadRefBySrf(string sref, ubigint& ref);
	bool loadRefBySrfPwd(string sref, string Password, ubigint& ref);
	ubigint loadRefsByUsg(ubigint refIdecMUsergroup, const bool append, vector<ubigint>& refs);
	bool loadSrfByRef(ubigint ref, string& sref);
};

#endif

