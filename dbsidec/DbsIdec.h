/**
  * \file DbsIdec.h
  * C++ wrapper for database DbsIdec (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef DBSIDEC_H
#define DBSIDEC_H

#define IDEC_VERSION "0.2.1"
#define IDEC_VERSION_MAJOR 0
#define IDEC_VERSION_MINOR 2
#define IDEC_VERSION_SUB 1

#include <sbecore/LiteDbs.h>

#include "IdecAccRMUserUniversal.h"
#include "IdecAMPersonDetail.h"
#include "IdecAMUserAccess.h"
#include "IdecAMUsergroupAccess.h"
#include "IdecAVControlPar.h"
#include "IdecAVKeylistKey.h"
#include "IdecAVValuelistVal.h"
#include "IdecCFile.h"
#include "IdecHistRMUserUniversal.h"
#include "IdecJAVKeylistKey.h"
#include "IdecJMPersonLastname.h"
#include "IdecJMUserState.h"
#include "IdecMFile.h"
#include "IdecMMission.h"
#include "IdecMPerson.h"
#include "IdecMSession.h"
#include "IdecMTour.h"
#include "IdecMUser.h"
#include "IdecMUsergroup.h"
#include "IdecRMUsergroupUniversal.h"
#include "IdecRMUserMUsergroup.h"

#include "IdecQFilList.h"
#include "IdecQMis1NTour.h"
#include "IdecQMisList.h"
#include "IdecQMisRef1NFile.h"
#include "IdecQPreselect.h"
#include "IdecQSelect.h"
#include "IdecQTouList.h"
#include "IdecQTouRef1NFile.h"
#include "IdecQUsgAAccess.h"
#include "IdecQUsgList.h"
#include "IdecQUsgMNUser.h"
#include "IdecQUsr1NSession.h"
#include "IdecQUsrAAccess.h"
#include "IdecQUsrList.h"
#include "IdecQUsrMNUsergroup.h"

#define VecIdecVAccess DbsIdec::VecVAccess
#define VecIdecVCard DbsIdec::VecVCard
#define VecIdecVControl DbsIdec::VecVControl
#define VecIdecVKeylist DbsIdec::VecVKeylist
#define VecIdecVLocale DbsIdec::VecVLocale
#define VecIdecVMaintable DbsIdec::VecVMaintable
#define VecIdecVPreset DbsIdec::VecVPreset
#define VecIdecVUserlevel DbsIdec::VecVUserlevel
#define VecIdecVValuelist DbsIdec::VecVValuelist
#define VecIdecWUiaccess DbsIdec::VecWUiaccess

/**
  * DbsIdec
  */
class DbsIdec {

public:
	/**
		* VecVAccess (full: VecIdecVAccess)
		*/
	class VecVAccess {

	public:
		static const uint FULL = 1;
		static const uint NONE = 2;
		static const uint VIEW = 3;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVCard (full: VecIdecVCard)
		*/
	class VecVCard {

	public:
		static const uint CRDIDECNAV = 1;
		static const uint CRDIDECUSG = 2;
		static const uint CRDIDECUSR = 3;
		static const uint CRDIDECSCF = 4;
		static const uint CRDIDECUTL = 5;
		static const uint CRDIDECMIS = 6;
		static const uint CRDIDECTOU = 7;
		static const uint CRDIDECIAQ = 8;
		static const uint CRDIDECAD1 = 9;
		static const uint CRDIDECFIL = 10;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVControl (full: VecIdecVControl)
		*/
	class VecVControl {

	public:
		static const uint PNLIDECUSGLIST_TCOSRF = 1;
		static const uint PNLIDECUSGAACCESS_TCOCRD = 2;
		static const uint PNLIDECUSGAACCESS_TCOUAC = 3;
		static const uint PNLIDECUSGMNUSER_TCOMREF = 4;
		static const uint PNLIDECUSGMNUSER_TCOULV = 5;
		static const uint PNLIDECUSRLIST_TCOPRS = 6;
		static const uint PNLIDECUSRLIST_TCOSRF = 7;
		static const uint PNLIDECUSRLIST_TCOUSG = 8;
		static const uint PNLIDECUSRLIST_TCOSTE = 9;
		static const uint PNLIDECUSRLIST_TCOLCL = 10;
		static const uint PNLIDECUSRLIST_TCOULV = 11;
		static const uint PNLIDECUSRAACCESS_TCOCRD = 12;
		static const uint PNLIDECUSRAACCESS_TCOUAC = 13;
		static const uint PNLIDECUSR1NSESSION_TCOREF = 14;
		static const uint PNLIDECUSRMNUSERGROUP_TCOMREF = 15;
		static const uint PNLIDECUSRMNUSERGROUP_TCOULV = 16;
		static const uint PNLIDECMISLIST_TCOTIT = 17;
		static const uint PNLIDECMISLIST_TCOGRP = 18;
		static const uint PNLIDECMISLIST_TCOOWN = 19;
		static const uint PNLIDECMISLIST_TCOSTA = 20;
		static const uint PNLIDECMISLIST_TCOSTO = 21;
		static const uint PNLIDECMISLIST_TCOCRY = 22;
		static const uint PNLIDECMISLIST_TCOREG = 23;
		static const uint PNLIDECMISLIST_TCOMUN = 24;
		static const uint PNLIDECMIS1NTOUR_TCOREF = 25;
		static const uint PNLIDECMISREF1NFILE_TCOREF = 26;
		static const uint PNLIDECTOULIST_TCOTIT = 27;
		static const uint PNLIDECTOULIST_TCOMIS = 28;
		static const uint PNLIDECTOULIST_TCOSTA = 29;
		static const uint PNLIDECTOULIST_TCOSTO = 30;
		static const uint PNLIDECTOULIST_TCOARE = 31;
		static const uint PNLIDECTOUREF1NFILE_TCOREF = 32;
		static const uint PNLIDECFILLIST_TCOFNM = 33;
		static const uint PNLIDECFILLIST_TCORET = 34;
		static const uint PNLIDECFILLIST_TCOREU = 35;
		static const uint PNLIDECFILLIST_TCOCNT = 36;
		static const uint PNLIDECFILLIST_TCOMIM = 37;
		static const uint PNLIDECFILLIST_TCOSIZ = 38;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);
	};

	/**
		* VecVKeylist (full: VecIdecVKeylist)
		*/
	class VecVKeylist {

	public:
		static const uint KLSTIDECKAMPERSONDETAILTYPE = 1;
		static const uint KLSTIDECKMFILECONTENT = 2;
		static const uint KLSTIDECKMFILEMIMETYPE = 3;
		static const uint KLSTIDECKMMISSIONCOUNTRY = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);
	};

	/**
		* VecVLocale (full: VecIdecVLocale)
		*/
	class VecVLocale {

	public:
		static const uint ENUS = 1;
		static const uint DECH = 2;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVMaintable (full: VecIdecVMaintable)
		*/
	class VecVMaintable {

	public:
		static const uint VOID = 1;
		static const uint TBLIDECMFILE = 2;
		static const uint TBLIDECMMISSION = 3;
		static const uint TBLIDECMPERSON = 4;
		static const uint TBLIDECMSESSION = 5;
		static const uint TBLIDECMTOUR = 6;
		static const uint TBLIDECMUSER = 7;
		static const uint TBLIDECMUSERGROUP = 8;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVPreset (full: VecIdecVPreset)
		*/
	class VecVPreset {

	public:
		static const uint VOID = 1;
		static const uint PREIDECADM = 2;
		static const uint PREIDECFILLIST_FNM = 3;
		static const uint PREIDECFILLIST_RET = 4;
		static const uint PREIDECFILLIST_REU = 5;
		static const uint PREIDECGRP = 6;
		static const uint PREIDECIP = 7;
		static const uint PREIDECIXACC = 8;
		static const uint PREIDECIXLCL = 9;
		static const uint PREIDECIXORD = 10;
		static const uint PREIDECIXPRE = 11;
		static const uint PREIDECIXUACAD1 = 12;
		static const uint PREIDECIXUACFIL = 13;
		static const uint PREIDECIXUACIAQ = 14;
		static const uint PREIDECIXUACMIS = 15;
		static const uint PREIDECIXUACSCF = 16;
		static const uint PREIDECIXUACTOU = 17;
		static const uint PREIDECIXUACUSG = 18;
		static const uint PREIDECIXUACUSR = 19;
		static const uint PREIDECIXUACUTL = 20;
		static const uint PREIDECJREFNOTIFY = 21;
		static const uint PREIDECJREFSESS = 22;
		static const uint PREIDECMISLIST_GRP = 23;
		static const uint PREIDECMISLIST_OWN = 24;
		static const uint PREIDECMISLIST_STA = 25;
		static const uint PREIDECMISLIST_TIT = 26;
		static const uint PREIDECOWN = 27;
		static const uint PREIDECREFFIL = 28;
		static const uint PREIDECREFMIS = 29;
		static const uint PREIDECREFPRS = 30;
		static const uint PREIDECREFSEL = 31;
		static const uint PREIDECREFSES = 32;
		static const uint PREIDECREFTOU = 33;
		static const uint PREIDECREFUSG = 34;
		static const uint PREIDECREFUSR = 35;
		static const uint PREIDECSESS = 36;
		static const uint PREIDECSYSDATE = 37;
		static const uint PREIDECSYSSTAMP = 38;
		static const uint PREIDECSYSTIME = 39;
		static const uint PREIDECTOULIST_MIS = 40;
		static const uint PREIDECTOULIST_STA = 41;
		static const uint PREIDECTOULIST_TIT = 42;
		static const uint PREIDECUSGAACCESS_X1 = 43;
		static const uint PREIDECUSGLIST_SRF = 44;
		static const uint PREIDECUSRAACCESS_X1 = 45;
		static const uint PREIDECUSRLIST_PRS = 46;
		static const uint PREIDECUSRLIST_SRF = 47;
		static const uint PREIDECUSRLIST_STE = 48;
		static const uint PREIDECUSRLIST_USG = 49;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);
	};

	/**
		* VecVUserlevel (full: VecIdecVUserlevel)
		*/
	class VecVUserlevel {

	public:
		static const uint ADM = 1;
		static const uint GADM = 2;
		static const uint REG = 3;
		static const uint VTOR = 4;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

	/**
		* VecVValuelist (full: VecIdecVValuelist)
		*/
	class VecVValuelist {

	public:
		static const uint VLSTIDECUMPERSONTITLE = 1;

		static uint getIx(const string& sref);
		static string getSref(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);
	};

	/**
		* VecWUiaccess (full: VecIdecWUiaccess)
		*/
	class VecWUiaccess {

	public:
		static const uint EDIT = 1;
		static const uint EXEC = 2;
		static const uint VIEW = 4;

		static uint getIx(const string& srefs);
		static void getIcs(const uint ix, set<uint>& ics);
		static string getSrefs(const uint ix);

		static string getTitle(const uint ix, const uint ixIdecVLocale);

		static void fillFeed(const uint ixIdecVLocale, Feed& feed);
	};

public:
	DbsIdec();
	~DbsIdec();

	void init(const uint _ixDbsVDbstype, const string& _dbspath, const string& _dbsname, const string& _ip, const uint _port, const string& _username, const string& _password);
	void term();

	void initLite();
	void termLite();

public:
	uint ixDbsVDbstype;
	string dbspath;
	string dbsname;
	string username;
	string password;
	string ip;
	int port;

	bool initdone;

	sqlite3* dbsLite;

public:
	void begin();																						//!< transaction functionality
	bool commit();
	void rollback();

	void beginLite();
	bool commitLite();
	void rollbackLite();

	bool loadUintBySQL(const string& sqlstr, uint& val);		//!< execute a SQL query returning a single uint (arbitrary tables)
	bool loadStringBySQL(const string& sqlstr, string& val);//!< execute a SQL query returning a single string (arbitrary tables)

	bool loadRefBySQL(const string& sqlstr, ubigint& ref);	//!< execute a SQL query returning a single reference (arbitrary tables)
																													//! load a list of references by a SQL query (arbitrary tables)
	ubigint loadRefsBySQL(const string& sqlstr, const bool append, vector<ubigint>& refs);

	bool loadUintBySQLLite(const string& sqlstr, uint& val);
	bool loadStringBySQLLite(const string& sqlstr, string& val);

	bool loadRefBySQLLite(const string& sqlstr, ubigint& ref);
	ubigint loadRefsBySQLLite(const string& sqlstr, const bool append, vector<ubigint>& refs);

	void executeQuery(const string& sqlstr);								//!< run single SQL command
	void executeQueryDiv(const string& sqlstrlite);
	void executeFile(const string& fullpath);								//!< SQL file batch execution

public:

	void fillFeedFromKlst(const uint klsIxIdecVKeylist, const uint ixIdecVLocale, Feed& feed);
	void fillFeedFromKlstByMtbUref(const uint klsIxIdecVKeylist, const uint x1IxIdecVMaintable, const ubigint x1Uref, const uint ixIdecVLocale, Feed& feed);

	string getKlstTitleBySref(const uint klsIxIdecVKeylist, const string& sref, const uint ixIdecVLocale = 0);
	string getKlstTitleByMtbUrefSref(const uint klsIxIdecVKeylist, const uint x1IxIdecVMaintable, const ubigint x1Uref, const string& sref, const uint ixIdecVLocale = 0);

	void fillFeedFromVlst(const uint vlsIxIdecVValuelist, const uint x1IxIdecVLocale, Feed& feed);

public:
	TblIdecAccRMUserUniversal* tblidecaccrmuseruniversal;
	TblIdecAMPersonDetail* tblidecampersondetail;
	TblIdecAMUserAccess* tblidecamuseraccess;
	TblIdecAMUsergroupAccess* tblidecamusergroupaccess;
	TblIdecAVControlPar* tblidecavcontrolpar;
	TblIdecAVKeylistKey* tblidecavkeylistkey;
	TblIdecAVValuelistVal* tblidecavvaluelistval;
	TblIdecCFile* tblideccfile;
	TblIdecHistRMUserUniversal* tblidechistrmuseruniversal;
	TblIdecJAVKeylistKey* tblidecjavkeylistkey;
	TblIdecJMPersonLastname* tblidecjmpersonlastname;
	TblIdecJMUserState* tblidecjmuserstate;
	TblIdecMFile* tblidecmfile;
	TblIdecMMission* tblidecmmission;
	TblIdecMPerson* tblidecmperson;
	TblIdecMSession* tblidecmsession;
	TblIdecMTour* tblidecmtour;
	TblIdecMUser* tblidecmuser;
	TblIdecMUsergroup* tblidecmusergroup;
	TblIdecRMUsergroupUniversal* tblidecrmusergroupuniversal;
	TblIdecRMUserMUsergroup* tblidecrmusermusergroup;

	TblIdecQFilList* tblidecqfillist;
	TblIdecQMis1NTour* tblidecqmis1ntour;
	TblIdecQMisList* tblidecqmislist;
	TblIdecQMisRef1NFile* tblidecqmisref1nfile;
	TblIdecQPreselect* tblidecqpreselect;
	TblIdecQSelect* tblidecqselect;
	TblIdecQTouList* tblidecqtoulist;
	TblIdecQTouRef1NFile* tblidecqtouref1nfile;
	TblIdecQUsgAAccess* tblidecqusgaaccess;
	TblIdecQUsgList* tblidecqusglist;
	TblIdecQUsgMNUser* tblidecqusgmnuser;
	TblIdecQUsr1NSession* tblidecqusr1nsession;
	TblIdecQUsrAAccess* tblidecqusraaccess;
	TblIdecQUsrList* tblidecqusrlist;
	TblIdecQUsrMNUsergroup* tblidecqusrmnusergroup;
};
#endif

