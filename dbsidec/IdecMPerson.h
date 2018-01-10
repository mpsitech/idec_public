/**
  * \file IdecMPerson.h
  * database access for table TblIdecMPerson (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECMPERSON_H
#define IDECMPERSON_H

#include <sbecore/LiteDbs.h>

#include <sbecore/Xmlio.h>

using namespace Xmlio;

#define VecIdecVMPersonSex TblIdecMPerson::VecVSex
#define VecIdecWMPersonDerivate TblIdecMPerson::VecWDerivate

/**
  * IdecMPerson: record of TblIdecMPerson
  */
class IdecMPerson {

public:
	IdecMPerson(const ubigint ref = 0, const ubigint grp = 0, const ubigint own = 0, const uint ixWDerivate = 0, const uint ixVSex = 0, const string Title = "", const string Firstname = "", const ubigint refJLastname = 0, const string Lastname = "", const ubigint telRefADetail = 0, const string telVal = "", const ubigint emlRefADetail = 0, const string emlVal = "", const string Salutation = "");

public:
	ubigint ref;
	ubigint grp;
	ubigint own;
	uint ixWDerivate;
	uint ixVSex;
	string Title;
	string Firstname;
	ubigint refJLastname;
	string Lastname;
	ubigint telRefADetail;
	string telVal;
	ubigint emlRefADetail;
	string emlVal;
	string Salutation;

public:
	bool operator==(const IdecMPerson& comp);
	bool operator!=(const IdecMPerson& comp);
};

/**
  * ListIdecMPerson: recordset of TblIdecMPerson
  */
class ListIdecMPerson {

public:
	ListIdecMPerson();
	ListIdecMPerson(const ListIdecMPerson& src);
	~ListIdecMPerson();

	void clear();
	unsigned int size() const;
	void append(IdecMPerson* rec);

	IdecMPerson* operator[](const uint ix);
	ListIdecMPerson& operator=(const ListIdecMPerson& src);
	bool operator==(const ListIdecMPerson& comp);
	bool operator!=(const ListIdecMPerson& comp);

public:
	vector<IdecMPerson*> nodes;
};

/**
  * TblIdecMPerson: C++ wrapper for table TblIdecMPerson
  */
class TblIdecMPerson {

public:
	/**
		* VecVSex (full: VecIdecVMPersonSex)
		*/
	class VecVSex {

	public:
		static const uint F = 1;
		static const uint M = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecWDerivate (full: VecIdecWMPersonDerivate)
		*/
	class VecWDerivate {

	public:
		static const uint USR = 1;

		static uint getIx(const string& srefs);
		static void getIcs(const uint ix, set<uint>& ics);
		static string getSrefs(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

public:
	TblIdecMPerson();
	virtual ~TblIdecMPerson();

public:
	virtual bool loadRecBySQL(const string& sqlstr, IdecMPerson** rec);
	virtual ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMPerson& rst);

	virtual void insertRec(IdecMPerson* rec);
	ubigint insertNewRec(IdecMPerson** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const uint ixWDerivate = 0, const uint ixVSex = 0, const string Title = "", const string Firstname = "", const ubigint refJLastname = 0, const string Lastname = "", const ubigint telRefADetail = 0, const string telVal = "", const ubigint emlRefADetail = 0, const string emlVal = "", const string Salutation = "");
	ubigint appendNewRecToRst(ListIdecMPerson& rst, IdecMPerson** rec = NULL, const ubigint grp = 0, const ubigint own = 0, const uint ixWDerivate = 0, const uint ixVSex = 0, const string Title = "", const string Firstname = "", const ubigint refJLastname = 0, const string Lastname = "", const ubigint telRefADetail = 0, const string telVal = "", const ubigint emlRefADetail = 0, const string emlVal = "", const string Salutation = "");
	virtual void insertRst(ListIdecMPerson& rst, bool transact = false);
	virtual void updateRec(IdecMPerson* rec);
	virtual void updateRst(ListIdecMPerson& rst, bool transact = false);
	virtual void removeRecByRef(ubigint ref);

	virtual bool loadRecByRef(ubigint ref, IdecMPerson** rec);
	ubigint loadRstByRefs(vector<ubigint>& refs, const bool append, ListIdecMPerson& rst);
};

/**
  * LiteTblIdecMPerson: C++ wrapper for table TblIdecMPerson (SQLite database)
  */
class LiteTblIdecMPerson : public TblIdecMPerson, public LiteTable {

public:
	LiteTblIdecMPerson();
	~LiteTblIdecMPerson();

public:
	void initStatements();

public:
	sqlite3_stmt* stmtInsertRec;
	sqlite3_stmt* stmtUpdateRec;
	sqlite3_stmt* stmtRemoveRecByRef;

	sqlite3_stmt* stmtLoadRecByRef;

private:
	bool loadRec(sqlite3_stmt* stmt, IdecMPerson** rec);
	ubigint loadRst(sqlite3_stmt* stmt, const bool append, ListIdecMPerson& rst);
	bool loadRecByStmt(sqlite3_stmt* stmt, IdecMPerson** rec);

public:
	bool loadRecBySQL(const string& sqlstr, IdecMPerson** rec);
	ubigint loadRstBySQL(const string& sqlstr, const bool append, ListIdecMPerson& rst);

	void insertRec(IdecMPerson* rec);
	void insertRst(ListIdecMPerson& rst, bool transact = false);
	void updateRec(IdecMPerson* rec);
	void updateRst(ListIdecMPerson& rst, bool transact = false);
	void removeRecByRef(ubigint ref);

	bool loadRecByRef(ubigint ref, IdecMPerson** rec);
};

#endif

