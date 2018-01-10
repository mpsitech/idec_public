DROP TABLE IF EXISTS TblIdecAccRMUserUniversal;
DROP TABLE IF EXISTS TblIdecAMPersonDetail;
DROP TABLE IF EXISTS TblIdecAMUserAccess;
DROP TABLE IF EXISTS TblIdecAMUsergroupAccess;
DROP TABLE IF EXISTS TblIdecAVControlPar;
DROP TABLE IF EXISTS TblIdecAVKeylistKey;
DROP TABLE IF EXISTS TblIdecAVValuelistVal;
DROP TABLE IF EXISTS TblIdecCFile;
DROP TABLE IF EXISTS TblIdecHistRMUserUniversal;
DROP TABLE IF EXISTS TblIdecJAVKeylistKey;
DROP TABLE IF EXISTS TblIdecJMPersonLastname;
DROP TABLE IF EXISTS TblIdecJMUserState;
DROP TABLE IF EXISTS TblIdecMFile;
DROP TABLE IF EXISTS TblIdecMMission;
DROP TABLE IF EXISTS TblIdecMPerson;
DROP TABLE IF EXISTS TblIdecMSession;
DROP TABLE IF EXISTS TblIdecMTour;
DROP TABLE IF EXISTS TblIdecMUser;
DROP TABLE IF EXISTS TblIdecMUsergroup;
DROP TABLE IF EXISTS TblIdecRMUsergroupUniversal;
DROP TABLE IF EXISTS TblIdecRMUserMUsergroup;

DROP TABLE IF EXISTS TblIdecQFilList;
DROP TABLE IF EXISTS TblIdecQMis1NTour;
DROP TABLE IF EXISTS TblIdecQMisList;
DROP TABLE IF EXISTS TblIdecQMisRef1NFile;
DROP TABLE IF EXISTS TblIdecQPreselect;
DROP TABLE IF EXISTS TblIdecQSelect;
DROP TABLE IF EXISTS TblIdecQTouList;
DROP TABLE IF EXISTS TblIdecQTouRef1NFile;
DROP TABLE IF EXISTS TblIdecQUsgAAccess;
DROP TABLE IF EXISTS TblIdecQUsgList;
DROP TABLE IF EXISTS TblIdecQUsgMNUser;
DROP TABLE IF EXISTS TblIdecQUsr1NSession;
DROP TABLE IF EXISTS TblIdecQUsrAAccess;
DROP TABLE IF EXISTS TblIdecQUsrList;
DROP TABLE IF EXISTS TblIdecQUsrMNUsergroup;

CREATE TABLE TblIdecAccRMUserUniversal(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUser BIGINT,
	unvIxIdecVMaintable INT,
	unvUref BIGINT,
	ixIdecVAccess INT
);
CREATE INDEX TblIdecAccRMUserUniversal_refIdecMUser ON TblIdecAccRMUserUniversal (refIdecMUser);
CREATE INDEX TblIdecAccRMUserUniversal_unvIxIdecVMaintable ON TblIdecAccRMUserUniversal (unvIxIdecVMaintable);
CREATE INDEX TblIdecAccRMUserUniversal_unvUref ON TblIdecAccRMUserUniversal (unvUref);

CREATE TABLE TblIdecAMPersonDetail(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMPerson BIGINT,
	x1SrefKType VARCHAR(50),
	Val VARCHAR(256)
);
CREATE INDEX TblIdecAMPersonDetail_refIdecMPerson ON TblIdecAMPersonDetail (refIdecMPerson);

CREATE TABLE TblIdecAMUserAccess(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUser BIGINT,
	x1IxIdecVCard INT,
	ixIdecWUiaccess INT
);
CREATE INDEX TblIdecAMUserAccess_refIdecMUser ON TblIdecAMUserAccess (refIdecMUser);
CREATE INDEX TblIdecAMUserAccess_x1IxIdecVCard ON TblIdecAMUserAccess (x1IxIdecVCard);

CREATE TABLE TblIdecAMUsergroupAccess(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUsergroup BIGINT,
	x1IxIdecVCard INT,
	ixIdecWUiaccess INT
);
CREATE INDEX TblIdecAMUsergroupAccess_refIdecMUsergroup ON TblIdecAMUsergroupAccess (refIdecMUsergroup);
CREATE INDEX TblIdecAMUsergroupAccess_x1IxIdecVCard ON TblIdecAMUsergroupAccess (x1IxIdecVCard);

CREATE TABLE TblIdecAVControlPar(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	ixIdecVControl INT,
	x1RefIdecMUser BIGINT,
	x2IxIdecVLocale INT,
	Par VARCHAR(256),
	Val VARCHAR(256)
);
CREATE INDEX TblIdecAVControlPar_ixIdecVControl ON TblIdecAVControlPar (ixIdecVControl);
CREATE INDEX TblIdecAVControlPar_x1RefIdecMUser ON TblIdecAVControlPar (x1RefIdecMUser);
CREATE INDEX TblIdecAVControlPar_x2IxIdecVLocale ON TblIdecAVControlPar (x2IxIdecVLocale);
CREATE INDEX TblIdecAVControlPar_Par ON TblIdecAVControlPar (Par);

CREATE TABLE TblIdecAVKeylistKey(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	klsIxIdecVKeylist INT,
	klsNum INT,
	x1IxIdecVMaintable INT,
	x1Uref BIGINT,
	Fixed SMALLINT,
	sref VARCHAR(50),
	Avail VARCHAR(1024),
	Implied VARCHAR(1024),
	refJ BIGINT,
	Title VARCHAR(256),
	Comment TEXT
);
CREATE INDEX TblIdecAVKeylistKey_klsIxIdecVKeylist ON TblIdecAVKeylistKey (klsIxIdecVKeylist);
CREATE INDEX TblIdecAVKeylistKey_klsNum ON TblIdecAVKeylistKey (klsNum);
CREATE INDEX TblIdecAVKeylistKey_x1IxIdecVMaintable ON TblIdecAVKeylistKey (x1IxIdecVMaintable);
CREATE INDEX TblIdecAVKeylistKey_x1Uref ON TblIdecAVKeylistKey (x1Uref);
CREATE INDEX TblIdecAVKeylistKey_sref ON TblIdecAVKeylistKey (sref);

CREATE TABLE TblIdecAVValuelistVal(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	vlsIxIdecVValuelist INT,
	vlsNum INT,
	x1IxIdecVLocale INT,
	Val VARCHAR(256)
);
CREATE INDEX TblIdecAVValuelistVal_vlsIxIdecVValuelist ON TblIdecAVValuelistVal (vlsIxIdecVValuelist);
CREATE INDEX TblIdecAVValuelistVal_vlsNum ON TblIdecAVValuelistVal (vlsNum);
CREATE INDEX TblIdecAVValuelistVal_x1IxIdecVLocale ON TblIdecAVValuelistVal (x1IxIdecVLocale);

CREATE TABLE TblIdecCFile(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	void SMALLINT

);

CREATE TABLE TblIdecHistRMUserUniversal(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUser BIGINT,
	unvIxIdecVMaintable INT,
	unvUref BIGINT,
	ixIdecVCard INT,
	ixIdecVPreset INT,
	preIxIdecVMaintable INT,
	preUref BIGINT,
	start INT
);
CREATE INDEX TblIdecHistRMUserUniversal_refIdecMUser ON TblIdecHistRMUserUniversal (refIdecMUser);
CREATE INDEX TblIdecHistRMUserUniversal_unvIxIdecVMaintable ON TblIdecHistRMUserUniversal (unvIxIdecVMaintable);
CREATE INDEX TblIdecHistRMUserUniversal_unvUref ON TblIdecHistRMUserUniversal (unvUref);
CREATE INDEX TblIdecHistRMUserUniversal_ixIdecVCard ON TblIdecHistRMUserUniversal (ixIdecVCard);
CREATE INDEX TblIdecHistRMUserUniversal_ixIdecVPreset ON TblIdecHistRMUserUniversal (ixIdecVPreset);
CREATE INDEX TblIdecHistRMUserUniversal_preIxIdecVMaintable ON TblIdecHistRMUserUniversal (preIxIdecVMaintable);
CREATE INDEX TblIdecHistRMUserUniversal_preUref ON TblIdecHistRMUserUniversal (preUref);

CREATE TABLE TblIdecJAVKeylistKey(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecAVKeylistKey BIGINT,
	x1IxIdecVLocale INT,
	Title VARCHAR(256),
	Comment TEXT
);
CREATE INDEX TblIdecJAVKeylistKey_refIdecAVKeylistKey ON TblIdecJAVKeylistKey (refIdecAVKeylistKey);
CREATE INDEX TblIdecJAVKeylistKey_x1IxIdecVLocale ON TblIdecJAVKeylistKey (x1IxIdecVLocale);

CREATE TABLE TblIdecJMPersonLastname(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMPerson BIGINT,
	x1Startd INT,
	Lastname VARCHAR(50)
);
CREATE INDEX TblIdecJMPersonLastname_refIdecMPerson ON TblIdecJMPersonLastname (refIdecMPerson);
CREATE INDEX TblIdecJMPersonLastname_x1Startd ON TblIdecJMPersonLastname (x1Startd);
CREATE INDEX TblIdecJMPersonLastname_Lastname ON TblIdecJMPersonLastname (Lastname);

CREATE TABLE TblIdecJMUserState(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUser BIGINT,
	x1Startd INT,
	ixVState INT
);
CREATE INDEX TblIdecJMUserState_refIdecMUser ON TblIdecJMUserState (refIdecMUser);
CREATE INDEX TblIdecJMUserState_x1Startd ON TblIdecJMUserState (x1Startd);

CREATE TABLE TblIdecMFile(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	grp BIGINT,
	own BIGINT,
	refIdecCFile BIGINT,
	refIxVTbl INT,
	refUref BIGINT,
	osrefKContent VARCHAR(50),
	Archived INT,
	Filename VARCHAR(50),
	Archivename VARCHAR(30),
	srefKMimetype VARCHAR(50),
	Size SMALLINT,
	Comment TEXT
);
CREATE INDEX TblIdecMFile_grp ON TblIdecMFile (grp);
CREATE INDEX TblIdecMFile_own ON TblIdecMFile (own);
CREATE INDEX TblIdecMFile_refIdecCFile ON TblIdecMFile (refIdecCFile);
CREATE INDEX TblIdecMFile_refIxVTbl ON TblIdecMFile (refIxVTbl);
CREATE INDEX TblIdecMFile_refUref ON TblIdecMFile (refUref);
CREATE INDEX TblIdecMFile_Filename ON TblIdecMFile (Filename);

CREATE TABLE TblIdecMMission(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	grp BIGINT,
	own BIGINT,
	Title VARCHAR(50),
	startd INT,
	stopd INT,
	srefKCountry VARCHAR(50),
	Region VARCHAR(50),
	Municipality VARCHAR(50),
	Comment TEXT
);
CREATE INDEX TblIdecMMission_grp ON TblIdecMMission (grp);
CREATE INDEX TblIdecMMission_own ON TblIdecMMission (own);
CREATE INDEX TblIdecMMission_Title ON TblIdecMMission (Title);
CREATE INDEX TblIdecMMission_startd ON TblIdecMMission (startd);

CREATE TABLE TblIdecMPerson(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	grp BIGINT,
	own BIGINT,
	ixWDerivate INT,
	ixVSex INT,
	Title VARCHAR(30),
	Firstname VARCHAR(30),
	refJLastname BIGINT,
	Lastname VARCHAR(50),
	telRefADetail BIGINT,
	telVal VARCHAR(256),
	emlRefADetail BIGINT,
	emlVal VARCHAR(256),
	Salutation VARCHAR(100)
);
CREATE INDEX TblIdecMPerson_grp ON TblIdecMPerson (grp);
CREATE INDEX TblIdecMPerson_own ON TblIdecMPerson (own);
CREATE INDEX TblIdecMPerson_ixWDerivate ON TblIdecMPerson (ixWDerivate);
CREATE INDEX TblIdecMPerson_Lastname ON TblIdecMPerson (Lastname);

CREATE TABLE TblIdecMSession(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUser BIGINT,
	start INT,
	stop INT,
	Ip VARCHAR(30)
);
CREATE INDEX TblIdecMSession_refIdecMUser ON TblIdecMSession (refIdecMUser);
CREATE INDEX TblIdecMSession_start ON TblIdecMSession (start);

CREATE TABLE TblIdecMTour(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMMission BIGINT,
	Title VARCHAR(50),
	start INT,
	stop INT,
	Area VARCHAR(50),
	theta DOUBLE PRECISION,
	phi DOUBLE PRECISION,
	Comment TEXT
);
CREATE INDEX TblIdecMTour_refIdecMMission ON TblIdecMTour (refIdecMMission);
CREATE INDEX TblIdecMTour_Title ON TblIdecMTour (Title);
CREATE INDEX TblIdecMTour_start ON TblIdecMTour (start);

CREATE TABLE TblIdecMUser(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	grp BIGINT,
	own BIGINT,
	refRUsergroup BIGINT,
	refIdecMUsergroup BIGINT,
	refIdecMPerson BIGINT,
	sref VARCHAR(50),
	refJState BIGINT,
	ixVState INT,
	ixIdecVLocale INT,
	ixIdecVUserlevel INT,
	Password VARCHAR(30)
);
CREATE INDEX TblIdecMUser_grp ON TblIdecMUser (grp);
CREATE INDEX TblIdecMUser_own ON TblIdecMUser (own);
CREATE INDEX TblIdecMUser_refIdecMUsergroup ON TblIdecMUser (refIdecMUsergroup);
CREATE INDEX TblIdecMUser_refIdecMPerson ON TblIdecMUser (refIdecMPerson);
CREATE INDEX TblIdecMUser_sref ON TblIdecMUser (sref);
CREATE INDEX TblIdecMUser_ixVState ON TblIdecMUser (ixVState);

CREATE TABLE TblIdecMUsergroup(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	grp BIGINT,
	own BIGINT,
	sref VARCHAR(50),
	Comment TEXT
);
CREATE INDEX TblIdecMUsergroup_grp ON TblIdecMUsergroup (grp);
CREATE INDEX TblIdecMUsergroup_own ON TblIdecMUsergroup (own);
CREATE INDEX TblIdecMUsergroup_sref ON TblIdecMUsergroup (sref);

CREATE TABLE TblIdecRMUsergroupUniversal(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUsergroup BIGINT,
	unvIxIdecVMaintable INT,
	unvUref BIGINT,
	ixIdecVAccess INT
);
CREATE INDEX TblIdecRMUsergroupUniversal_refIdecMUsergroup ON TblIdecRMUsergroupUniversal (refIdecMUsergroup);
CREATE INDEX TblIdecRMUsergroupUniversal_unvIxIdecVMaintable ON TblIdecRMUsergroupUniversal (unvIxIdecVMaintable);
CREATE INDEX TblIdecRMUsergroupUniversal_unvUref ON TblIdecRMUsergroupUniversal (unvUref);

CREATE TABLE TblIdecRMUserMUsergroup(
	ref INTEGER PRIMARY KEY AUTOINCREMENT,
	refIdecMUser BIGINT,
	refIdecMUsergroup BIGINT,
	ixIdecVUserlevel INT
);
CREATE INDEX TblIdecRMUserMUsergroup_refIdecMUser ON TblIdecRMUserMUsergroup (refIdecMUser);
CREATE INDEX TblIdecRMUserMUsergroup_refIdecMUsergroup ON TblIdecRMUserMUsergroup (refIdecMUsergroup);

CREATE TABLE TblIdecQFilList(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	Filename VARCHAR(50),
	refIxVTbl INT,
	refUref BIGINT,
	osrefKContent VARCHAR(50),
	srefKMimetype VARCHAR(50),
	Size SMALLINT
);
CREATE INDEX TblIdecQFilList_jref ON TblIdecQFilList (jref);
CREATE INDEX TblIdecQFilList_jnum ON TblIdecQFilList (jnum);

CREATE TABLE TblIdecQMis1NTour(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT
);
CREATE INDEX TblIdecQMis1NTour_jref ON TblIdecQMis1NTour (jref);
CREATE INDEX TblIdecQMis1NTour_jnum ON TblIdecQMis1NTour (jnum);

CREATE TABLE TblIdecQMisList(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	Title VARCHAR(50),
	grp BIGINT,
	own BIGINT,
	startd INT,
	stopd INT,
	srefKCountry VARCHAR(50),
	Region VARCHAR(50),
	Municipality VARCHAR(50)
);
CREATE INDEX TblIdecQMisList_jref ON TblIdecQMisList (jref);
CREATE INDEX TblIdecQMisList_jnum ON TblIdecQMisList (jnum);

CREATE TABLE TblIdecQMisRef1NFile(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT
);
CREATE INDEX TblIdecQMisRef1NFile_jref ON TblIdecQMisRef1NFile (jref);
CREATE INDEX TblIdecQMisRef1NFile_jnum ON TblIdecQMisRef1NFile (jnum);

CREATE TABLE TblIdecQPreselect(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT
);
CREATE INDEX TblIdecQPreselect_jref ON TblIdecQPreselect (jref);

CREATE TABLE TblIdecQSelect(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ix INT,
	ref BIGINT
);
CREATE INDEX TblIdecQSelect_jref ON TblIdecQSelect (jref);
CREATE INDEX TblIdecQSelect_ix ON TblIdecQSelect (ix);

CREATE TABLE TblIdecQTouList(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	Title VARCHAR(50),
	refIdecMMission BIGINT,
	start INT,
	stop INT,
	Area VARCHAR(50)
);
CREATE INDEX TblIdecQTouList_jref ON TblIdecQTouList (jref);
CREATE INDEX TblIdecQTouList_jnum ON TblIdecQTouList (jnum);

CREATE TABLE TblIdecQTouRef1NFile(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT
);
CREATE INDEX TblIdecQTouRef1NFile_jref ON TblIdecQTouRef1NFile (jref);
CREATE INDEX TblIdecQTouRef1NFile_jnum ON TblIdecQTouRef1NFile (jnum);

CREATE TABLE TblIdecQUsgAAccess(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	x1IxIdecVCard INT,
	ixIdecWUiaccess INT
);
CREATE INDEX TblIdecQUsgAAccess_jref ON TblIdecQUsgAAccess (jref);
CREATE INDEX TblIdecQUsgAAccess_jnum ON TblIdecQUsgAAccess (jnum);

CREATE TABLE TblIdecQUsgList(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	sref VARCHAR(50)
);
CREATE INDEX TblIdecQUsgList_jref ON TblIdecQUsgList (jref);
CREATE INDEX TblIdecQUsgList_jnum ON TblIdecQUsgList (jnum);

CREATE TABLE TblIdecQUsgMNUser(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	mref BIGINT,
	ref BIGINT,
	ixIdecVUserlevel INT
);
CREATE INDEX TblIdecQUsgMNUser_jref ON TblIdecQUsgMNUser (jref);
CREATE INDEX TblIdecQUsgMNUser_jnum ON TblIdecQUsgMNUser (jnum);

CREATE TABLE TblIdecQUsr1NSession(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT
);
CREATE INDEX TblIdecQUsr1NSession_jref ON TblIdecQUsr1NSession (jref);
CREATE INDEX TblIdecQUsr1NSession_jnum ON TblIdecQUsr1NSession (jnum);

CREATE TABLE TblIdecQUsrAAccess(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	x1IxIdecVCard INT,
	ixIdecWUiaccess INT
);
CREATE INDEX TblIdecQUsrAAccess_jref ON TblIdecQUsrAAccess (jref);
CREATE INDEX TblIdecQUsrAAccess_jnum ON TblIdecQUsrAAccess (jnum);

CREATE TABLE TblIdecQUsrList(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	ref BIGINT,
	refIdecMPerson BIGINT,
	sref VARCHAR(50),
	refIdecMUsergroup BIGINT,
	ixVState INT,
	ixIdecVLocale INT,
	ixIdecVUserlevel INT
);
CREATE INDEX TblIdecQUsrList_jref ON TblIdecQUsrList (jref);
CREATE INDEX TblIdecQUsrList_jnum ON TblIdecQUsrList (jnum);

CREATE TABLE TblIdecQUsrMNUsergroup(
	qref INTEGER PRIMARY KEY AUTOINCREMENT,
	jref BIGINT,
	jnum INT,
	mref BIGINT,
	ref BIGINT,
	ixIdecVUserlevel INT
);
CREATE INDEX TblIdecQUsrMNUsergroup_jref ON TblIdecQUsrMNUsergroup (jref);
CREATE INDEX TblIdecQUsrMNUsergroup_jnum ON TblIdecQUsrMNUsergroup (jnum);

