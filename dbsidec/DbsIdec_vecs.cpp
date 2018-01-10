/**
  * \file DbsIdec_vecs.cpp
  * C++ wrapper for database DbsIdec (implementation of vectors)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class DbsIdec::VecVAccess
 ******************************************************************************/

uint DbsIdec::VecVAccess::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "full") return FULL;
	else if (s == "none") return NONE;
	else if (s == "view") return VIEW;

	return(0);
};

string DbsIdec::VecVAccess::getSref(
			const uint ix
		) {
	if (ix == FULL) return("full");
	else if (ix == NONE) return("none");
	else if (ix == VIEW) return("view");

	return("");
};

string DbsIdec::VecVAccess::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == FULL) return("full");
		else if (ix == NONE) return("none");
		else if (ix == VIEW) return("view");
	} else if (ixIdecVLocale == 2) {
		if (ix == FULL) return("voll");
		else if (ix == NONE) return("kein");
		else if (ix == VIEW) return("anschauen");
	};

	return("");
};

void DbsIdec::VecVAccess::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class DbsIdec::VecVCard
 ******************************************************************************/

uint DbsIdec::VecVCard::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "crdidecnav") return CRDIDECNAV;
	else if (s == "crdidecusg") return CRDIDECUSG;
	else if (s == "crdidecusr") return CRDIDECUSR;
	else if (s == "crdidecscf") return CRDIDECSCF;
	else if (s == "crdidecutl") return CRDIDECUTL;
	else if (s == "crdidecmis") return CRDIDECMIS;
	else if (s == "crdidectou") return CRDIDECTOU;
	else if (s == "crdideciaq") return CRDIDECIAQ;
	else if (s == "crdidecad1") return CRDIDECAD1;
	else if (s == "crdidecfil") return CRDIDECFIL;

	return(0);
};

string DbsIdec::VecVCard::getSref(
			const uint ix
		) {
	if (ix == CRDIDECNAV) return("CrdIdecNav");
	else if (ix == CRDIDECUSG) return("CrdIdecUsg");
	else if (ix == CRDIDECUSR) return("CrdIdecUsr");
	else if (ix == CRDIDECSCF) return("CrdIdecScf");
	else if (ix == CRDIDECUTL) return("CrdIdecUtl");
	else if (ix == CRDIDECMIS) return("CrdIdecMis");
	else if (ix == CRDIDECTOU) return("CrdIdecTou");
	else if (ix == CRDIDECIAQ) return("CrdIdecIaq");
	else if (ix == CRDIDECAD1) return("CrdIdecAd1");
	else if (ix == CRDIDECFIL) return("CrdIdecFil");

	return("");
};

string DbsIdec::VecVCard::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == CRDIDECUSG) return("user groups");
		else if (ix == CRDIDECUSR) return("users");
		else if (ix == CRDIDECSCF) return("system configuration");
		else if (ix == CRDIDECUTL) return("utilities");
		else if (ix == CRDIDECMIS) return("missions");
		else if (ix == CRDIDECTOU) return("tours");
		else if (ix == CRDIDECIAQ) return("image acquisition");
		else if (ix == CRDIDECAD1) return("autonomous detection 1");
		else if (ix == CRDIDECFIL) return("files");
		else return(getSref(ix));
	} else if (ixIdecVLocale == 2) {
		if (ix == CRDIDECUSG) return("Benutzergruppen");
		else if (ix == CRDIDECUSR) return("Benutzer");
		else if (ix == CRDIDECSCF) return("Systemkonfiguration");
		else if (ix == CRDIDECUTL) return("Dienstprogramme");
		else if (ix == CRDIDECMIS) return("Missionen");
		else if (ix == CRDIDECTOU) return("Touren");
		else if (ix == CRDIDECIAQ) return("Bilderfassung");
		else if (ix == CRDIDECAD1) return("autonome Detektion 1");
		else if (ix == CRDIDECFIL) return("Dateien");
		else return(getTitle(ix, 1));
	};

	return("");
};

void DbsIdec::VecVCard::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=10;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class DbsIdec::VecVControl
 ******************************************************************************/

uint DbsIdec::VecVControl::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "pnlidecusglist.tcosrf") return PNLIDECUSGLIST_TCOSRF;
	else if (s == "pnlidecusgaaccess.tcocrd") return PNLIDECUSGAACCESS_TCOCRD;
	else if (s == "pnlidecusgaaccess.tcouac") return PNLIDECUSGAACCESS_TCOUAC;
	else if (s == "pnlidecusgmnuser.tcomref") return PNLIDECUSGMNUSER_TCOMREF;
	else if (s == "pnlidecusgmnuser.tcoulv") return PNLIDECUSGMNUSER_TCOULV;
	else if (s == "pnlidecusrlist.tcoprs") return PNLIDECUSRLIST_TCOPRS;
	else if (s == "pnlidecusrlist.tcosrf") return PNLIDECUSRLIST_TCOSRF;
	else if (s == "pnlidecusrlist.tcousg") return PNLIDECUSRLIST_TCOUSG;
	else if (s == "pnlidecusrlist.tcoste") return PNLIDECUSRLIST_TCOSTE;
	else if (s == "pnlidecusrlist.tcolcl") return PNLIDECUSRLIST_TCOLCL;
	else if (s == "pnlidecusrlist.tcoulv") return PNLIDECUSRLIST_TCOULV;
	else if (s == "pnlidecusraaccess.tcocrd") return PNLIDECUSRAACCESS_TCOCRD;
	else if (s == "pnlidecusraaccess.tcouac") return PNLIDECUSRAACCESS_TCOUAC;
	else if (s == "pnlidecusr1nsession.tcoref") return PNLIDECUSR1NSESSION_TCOREF;
	else if (s == "pnlidecusrmnusergroup.tcomref") return PNLIDECUSRMNUSERGROUP_TCOMREF;
	else if (s == "pnlidecusrmnusergroup.tcoulv") return PNLIDECUSRMNUSERGROUP_TCOULV;
	else if (s == "pnlidecmislist.tcotit") return PNLIDECMISLIST_TCOTIT;
	else if (s == "pnlidecmislist.tcogrp") return PNLIDECMISLIST_TCOGRP;
	else if (s == "pnlidecmislist.tcoown") return PNLIDECMISLIST_TCOOWN;
	else if (s == "pnlidecmislist.tcosta") return PNLIDECMISLIST_TCOSTA;
	else if (s == "pnlidecmislist.tcosto") return PNLIDECMISLIST_TCOSTO;
	else if (s == "pnlidecmislist.tcocry") return PNLIDECMISLIST_TCOCRY;
	else if (s == "pnlidecmislist.tcoreg") return PNLIDECMISLIST_TCOREG;
	else if (s == "pnlidecmislist.tcomun") return PNLIDECMISLIST_TCOMUN;
	else if (s == "pnlidecmis1ntour.tcoref") return PNLIDECMIS1NTOUR_TCOREF;
	else if (s == "pnlidecmisref1nfile.tcoref") return PNLIDECMISREF1NFILE_TCOREF;
	else if (s == "pnlidectoulist.tcotit") return PNLIDECTOULIST_TCOTIT;
	else if (s == "pnlidectoulist.tcomis") return PNLIDECTOULIST_TCOMIS;
	else if (s == "pnlidectoulist.tcosta") return PNLIDECTOULIST_TCOSTA;
	else if (s == "pnlidectoulist.tcosto") return PNLIDECTOULIST_TCOSTO;
	else if (s == "pnlidectoulist.tcoare") return PNLIDECTOULIST_TCOARE;
	else if (s == "pnlidectouref1nfile.tcoref") return PNLIDECTOUREF1NFILE_TCOREF;
	else if (s == "pnlidecfillist.tcofnm") return PNLIDECFILLIST_TCOFNM;
	else if (s == "pnlidecfillist.tcoret") return PNLIDECFILLIST_TCORET;
	else if (s == "pnlidecfillist.tcoreu") return PNLIDECFILLIST_TCOREU;
	else if (s == "pnlidecfillist.tcocnt") return PNLIDECFILLIST_TCOCNT;
	else if (s == "pnlidecfillist.tcomim") return PNLIDECFILLIST_TCOMIM;
	else if (s == "pnlidecfillist.tcosiz") return PNLIDECFILLIST_TCOSIZ;

	return(0);
};

string DbsIdec::VecVControl::getSref(
			const uint ix
		) {
	if (ix == PNLIDECUSGLIST_TCOSRF) return("PnlIdecUsgList.TcoSrf");
	else if (ix == PNLIDECUSGAACCESS_TCOCRD) return("PnlIdecUsgAAccess.TcoCrd");
	else if (ix == PNLIDECUSGAACCESS_TCOUAC) return("PnlIdecUsgAAccess.TcoUac");
	else if (ix == PNLIDECUSGMNUSER_TCOMREF) return("PnlIdecUsgMNUser.TcoMref");
	else if (ix == PNLIDECUSGMNUSER_TCOULV) return("PnlIdecUsgMNUser.TcoUlv");
	else if (ix == PNLIDECUSRLIST_TCOPRS) return("PnlIdecUsrList.TcoPrs");
	else if (ix == PNLIDECUSRLIST_TCOSRF) return("PnlIdecUsrList.TcoSrf");
	else if (ix == PNLIDECUSRLIST_TCOUSG) return("PnlIdecUsrList.TcoUsg");
	else if (ix == PNLIDECUSRLIST_TCOSTE) return("PnlIdecUsrList.TcoSte");
	else if (ix == PNLIDECUSRLIST_TCOLCL) return("PnlIdecUsrList.TcoLcl");
	else if (ix == PNLIDECUSRLIST_TCOULV) return("PnlIdecUsrList.TcoUlv");
	else if (ix == PNLIDECUSRAACCESS_TCOCRD) return("PnlIdecUsrAAccess.TcoCrd");
	else if (ix == PNLIDECUSRAACCESS_TCOUAC) return("PnlIdecUsrAAccess.TcoUac");
	else if (ix == PNLIDECUSR1NSESSION_TCOREF) return("PnlIdecUsr1NSession.TcoRef");
	else if (ix == PNLIDECUSRMNUSERGROUP_TCOMREF) return("PnlIdecUsrMNUsergroup.TcoMref");
	else if (ix == PNLIDECUSRMNUSERGROUP_TCOULV) return("PnlIdecUsrMNUsergroup.TcoUlv");
	else if (ix == PNLIDECMISLIST_TCOTIT) return("PnlIdecMisList.TcoTit");
	else if (ix == PNLIDECMISLIST_TCOGRP) return("PnlIdecMisList.TcoGrp");
	else if (ix == PNLIDECMISLIST_TCOOWN) return("PnlIdecMisList.TcoOwn");
	else if (ix == PNLIDECMISLIST_TCOSTA) return("PnlIdecMisList.TcoSta");
	else if (ix == PNLIDECMISLIST_TCOSTO) return("PnlIdecMisList.TcoSto");
	else if (ix == PNLIDECMISLIST_TCOCRY) return("PnlIdecMisList.TcoCry");
	else if (ix == PNLIDECMISLIST_TCOREG) return("PnlIdecMisList.TcoReg");
	else if (ix == PNLIDECMISLIST_TCOMUN) return("PnlIdecMisList.TcoMun");
	else if (ix == PNLIDECMIS1NTOUR_TCOREF) return("PnlIdecMis1NTour.TcoRef");
	else if (ix == PNLIDECMISREF1NFILE_TCOREF) return("PnlIdecMisRef1NFile.TcoRef");
	else if (ix == PNLIDECTOULIST_TCOTIT) return("PnlIdecTouList.TcoTit");
	else if (ix == PNLIDECTOULIST_TCOMIS) return("PnlIdecTouList.TcoMis");
	else if (ix == PNLIDECTOULIST_TCOSTA) return("PnlIdecTouList.TcoSta");
	else if (ix == PNLIDECTOULIST_TCOSTO) return("PnlIdecTouList.TcoSto");
	else if (ix == PNLIDECTOULIST_TCOARE) return("PnlIdecTouList.TcoAre");
	else if (ix == PNLIDECTOUREF1NFILE_TCOREF) return("PnlIdecTouRef1NFile.TcoRef");
	else if (ix == PNLIDECFILLIST_TCOFNM) return("PnlIdecFilList.TcoFnm");
	else if (ix == PNLIDECFILLIST_TCORET) return("PnlIdecFilList.TcoRet");
	else if (ix == PNLIDECFILLIST_TCOREU) return("PnlIdecFilList.TcoReu");
	else if (ix == PNLIDECFILLIST_TCOCNT) return("PnlIdecFilList.TcoCnt");
	else if (ix == PNLIDECFILLIST_TCOMIM) return("PnlIdecFilList.TcoMim");
	else if (ix == PNLIDECFILLIST_TCOSIZ) return("PnlIdecFilList.TcoSiz");

	return("");
};

/******************************************************************************
 class DbsIdec::VecVKeylist
 ******************************************************************************/

uint DbsIdec::VecVKeylist::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "klstideckampersondetailtype") return KLSTIDECKAMPERSONDETAILTYPE;
	else if (s == "klstideckmfilecontent") return KLSTIDECKMFILECONTENT;
	else if (s == "klstideckmfilemimetype") return KLSTIDECKMFILEMIMETYPE;
	else if (s == "klstideckmmissioncountry") return KLSTIDECKMMISSIONCOUNTRY;

	return(0);
};

string DbsIdec::VecVKeylist::getSref(
			const uint ix
		) {
	if (ix == KLSTIDECKAMPERSONDETAILTYPE) return("KlstIdecKAMPersonDetailType");
	else if (ix == KLSTIDECKMFILECONTENT) return("KlstIdecKMFileContent");
	else if (ix == KLSTIDECKMFILEMIMETYPE) return("KlstIdecKMFileMimetype");
	else if (ix == KLSTIDECKMMISSIONCOUNTRY) return("KlstIdecKMMissionCountry");

	return("");
};

string DbsIdec::VecVKeylist::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == KLSTIDECKAMPERSONDETAILTYPE) return("type");
		else if (ix == KLSTIDECKMFILECONTENT) return("content");
		else if (ix == KLSTIDECKMFILEMIMETYPE) return("MIME type");
		else if (ix == KLSTIDECKMMISSIONCOUNTRY) return("country");
	} else if (ixIdecVLocale == 2) {
		if (ix == KLSTIDECKAMPERSONDETAILTYPE) return("Typ");
		else if (ix == KLSTIDECKMFILECONTENT) return("Inhalt");
		else if (ix == KLSTIDECKMFILEMIMETYPE) return("MIME-Typ");
		else if (ix == KLSTIDECKMMISSIONCOUNTRY) return("Land");
	};

	return("");
};

/******************************************************************************
 class DbsIdec::VecVLocale
 ******************************************************************************/

uint DbsIdec::VecVLocale::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "enus") return ENUS;
	else if (s == "dech") return DECH;

	return(0);
};

string DbsIdec::VecVLocale::getSref(
			const uint ix
		) {
	if (ix == ENUS) return("enus");
	else if (ix == DECH) return("dech");

	return("");
};

string DbsIdec::VecVLocale::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == ENUS) return("English (United States)");
		else if (ix == DECH) return("German (Switzerland)");
	} else if (ixIdecVLocale == 2) {
		if (ix == ENUS) return("Englisch (Vereinigte Staaten)");
		else if (ix == DECH) return("Deutsch (Schweiz)");
	};

	return("");
};

void DbsIdec::VecVLocale::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class DbsIdec::VecVMaintable
 ******************************************************************************/

uint DbsIdec::VecVMaintable::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "void") return VOID;
	else if (s == "tblidecmfile") return TBLIDECMFILE;
	else if (s == "tblidecmmission") return TBLIDECMMISSION;
	else if (s == "tblidecmperson") return TBLIDECMPERSON;
	else if (s == "tblidecmsession") return TBLIDECMSESSION;
	else if (s == "tblidecmtour") return TBLIDECMTOUR;
	else if (s == "tblidecmuser") return TBLIDECMUSER;
	else if (s == "tblidecmusergroup") return TBLIDECMUSERGROUP;

	return(0);
};

string DbsIdec::VecVMaintable::getSref(
			const uint ix
		) {
	if (ix == VOID) return("void");
	else if (ix == TBLIDECMFILE) return("TblIdecMFile");
	else if (ix == TBLIDECMMISSION) return("TblIdecMMission");
	else if (ix == TBLIDECMPERSON) return("TblIdecMPerson");
	else if (ix == TBLIDECMSESSION) return("TblIdecMSession");
	else if (ix == TBLIDECMTOUR) return("TblIdecMTour");
	else if (ix == TBLIDECMUSER) return("TblIdecMUser");
	else if (ix == TBLIDECMUSERGROUP) return("TblIdecMUsergroup");

	return("");
};

string DbsIdec::VecVMaintable::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == VOID) return("none");
		else if (ix == TBLIDECMFILE) return("file");
		else if (ix == TBLIDECMMISSION) return("mission");
		else if (ix == TBLIDECMPERSON) return("person");
		else if (ix == TBLIDECMSESSION) return("session");
		else if (ix == TBLIDECMTOUR) return("tour");
		else if (ix == TBLIDECMUSER) return("user");
		else if (ix == TBLIDECMUSERGROUP) return("user group");
	} else if (ixIdecVLocale == 2) {
		if (ix == VOID) return("kein");
		else if (ix == TBLIDECMFILE) return("Datei");
		else if (ix == TBLIDECMMISSION) return("Mission");
		else if (ix == TBLIDECMPERSON) return("Person");
		else if (ix == TBLIDECMSESSION) return("Sitzung");
		else if (ix == TBLIDECMTOUR) return("Tour");
		else if (ix == TBLIDECMUSER) return("Benutzer");
		else if (ix == TBLIDECMUSERGROUP) return("Benutzergruppe");
	};

	return("");
};

void DbsIdec::VecVMaintable::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=8;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class DbsIdec::VecVPreset
 ******************************************************************************/

uint DbsIdec::VecVPreset::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "void") return VOID;
	else if (s == "preidecadm") return PREIDECADM;
	else if (s == "preidecfillist.fnm") return PREIDECFILLIST_FNM;
	else if (s == "preidecfillist.ret") return PREIDECFILLIST_RET;
	else if (s == "preidecfillist.reu") return PREIDECFILLIST_REU;
	else if (s == "preidecgrp") return PREIDECGRP;
	else if (s == "preidecip") return PREIDECIP;
	else if (s == "preidecixacc") return PREIDECIXACC;
	else if (s == "preidecixlcl") return PREIDECIXLCL;
	else if (s == "preidecixord") return PREIDECIXORD;
	else if (s == "preidecixpre") return PREIDECIXPRE;
	else if (s == "preidecixuacad1") return PREIDECIXUACAD1;
	else if (s == "preidecixuacfil") return PREIDECIXUACFIL;
	else if (s == "preidecixuaciaq") return PREIDECIXUACIAQ;
	else if (s == "preidecixuacmis") return PREIDECIXUACMIS;
	else if (s == "preidecixuacscf") return PREIDECIXUACSCF;
	else if (s == "preidecixuactou") return PREIDECIXUACTOU;
	else if (s == "preidecixuacusg") return PREIDECIXUACUSG;
	else if (s == "preidecixuacusr") return PREIDECIXUACUSR;
	else if (s == "preidecixuacutl") return PREIDECIXUACUTL;
	else if (s == "preidecjrefnotify") return PREIDECJREFNOTIFY;
	else if (s == "preidecjrefsess") return PREIDECJREFSESS;
	else if (s == "preidecmislist.grp") return PREIDECMISLIST_GRP;
	else if (s == "preidecmislist.own") return PREIDECMISLIST_OWN;
	else if (s == "preidecmislist.sta") return PREIDECMISLIST_STA;
	else if (s == "preidecmislist.tit") return PREIDECMISLIST_TIT;
	else if (s == "preidecown") return PREIDECOWN;
	else if (s == "preidecreffil") return PREIDECREFFIL;
	else if (s == "preidecrefmis") return PREIDECREFMIS;
	else if (s == "preidecrefprs") return PREIDECREFPRS;
	else if (s == "preidecrefsel") return PREIDECREFSEL;
	else if (s == "preidecrefses") return PREIDECREFSES;
	else if (s == "preidecreftou") return PREIDECREFTOU;
	else if (s == "preidecrefusg") return PREIDECREFUSG;
	else if (s == "preidecrefusr") return PREIDECREFUSR;
	else if (s == "preidecsess") return PREIDECSESS;
	else if (s == "preidecsysdate") return PREIDECSYSDATE;
	else if (s == "preidecsysstamp") return PREIDECSYSSTAMP;
	else if (s == "preidecsystime") return PREIDECSYSTIME;
	else if (s == "preidectoulist.mis") return PREIDECTOULIST_MIS;
	else if (s == "preidectoulist.sta") return PREIDECTOULIST_STA;
	else if (s == "preidectoulist.tit") return PREIDECTOULIST_TIT;
	else if (s == "preidecusgaaccess.x1") return PREIDECUSGAACCESS_X1;
	else if (s == "preidecusglist.srf") return PREIDECUSGLIST_SRF;
	else if (s == "preidecusraaccess.x1") return PREIDECUSRAACCESS_X1;
	else if (s == "preidecusrlist.prs") return PREIDECUSRLIST_PRS;
	else if (s == "preidecusrlist.srf") return PREIDECUSRLIST_SRF;
	else if (s == "preidecusrlist.ste") return PREIDECUSRLIST_STE;
	else if (s == "preidecusrlist.usg") return PREIDECUSRLIST_USG;

	return(0);
};

string DbsIdec::VecVPreset::getSref(
			const uint ix
		) {
	if (ix == VOID) return("void");
	else if (ix == PREIDECADM) return("PreIdecAdm");
	else if (ix == PREIDECFILLIST_FNM) return("PreIdecFilList.fnm");
	else if (ix == PREIDECFILLIST_RET) return("PreIdecFilList.ret");
	else if (ix == PREIDECFILLIST_REU) return("PreIdecFilList.reu");
	else if (ix == PREIDECGRP) return("PreIdecGrp");
	else if (ix == PREIDECIP) return("PreIdecIp");
	else if (ix == PREIDECIXACC) return("PreIdecIxAcc");
	else if (ix == PREIDECIXLCL) return("PreIdecIxLcl");
	else if (ix == PREIDECIXORD) return("PreIdecIxOrd");
	else if (ix == PREIDECIXPRE) return("PreIdecIxPre");
	else if (ix == PREIDECIXUACAD1) return("PreIdecIxUacAd1");
	else if (ix == PREIDECIXUACFIL) return("PreIdecIxUacFil");
	else if (ix == PREIDECIXUACIAQ) return("PreIdecIxUacIaq");
	else if (ix == PREIDECIXUACMIS) return("PreIdecIxUacMis");
	else if (ix == PREIDECIXUACSCF) return("PreIdecIxUacScf");
	else if (ix == PREIDECIXUACTOU) return("PreIdecIxUacTou");
	else if (ix == PREIDECIXUACUSG) return("PreIdecIxUacUsg");
	else if (ix == PREIDECIXUACUSR) return("PreIdecIxUacUsr");
	else if (ix == PREIDECIXUACUTL) return("PreIdecIxUacUtl");
	else if (ix == PREIDECJREFNOTIFY) return("PreIdecJrefNotify");
	else if (ix == PREIDECJREFSESS) return("PreIdecJrefSess");
	else if (ix == PREIDECMISLIST_GRP) return("PreIdecMisList.grp");
	else if (ix == PREIDECMISLIST_OWN) return("PreIdecMisList.own");
	else if (ix == PREIDECMISLIST_STA) return("PreIdecMisList.sta");
	else if (ix == PREIDECMISLIST_TIT) return("PreIdecMisList.tit");
	else if (ix == PREIDECOWN) return("PreIdecOwn");
	else if (ix == PREIDECREFFIL) return("PreIdecRefFil");
	else if (ix == PREIDECREFMIS) return("PreIdecRefMis");
	else if (ix == PREIDECREFPRS) return("PreIdecRefPrs");
	else if (ix == PREIDECREFSEL) return("PreIdecRefSel");
	else if (ix == PREIDECREFSES) return("PreIdecRefSes");
	else if (ix == PREIDECREFTOU) return("PreIdecRefTou");
	else if (ix == PREIDECREFUSG) return("PreIdecRefUsg");
	else if (ix == PREIDECREFUSR) return("PreIdecRefUsr");
	else if (ix == PREIDECSESS) return("PreIdecSess");
	else if (ix == PREIDECSYSDATE) return("PreIdecSysdate");
	else if (ix == PREIDECSYSSTAMP) return("PreIdecSysstamp");
	else if (ix == PREIDECSYSTIME) return("PreIdecSystime");
	else if (ix == PREIDECTOULIST_MIS) return("PreIdecTouList.mis");
	else if (ix == PREIDECTOULIST_STA) return("PreIdecTouList.sta");
	else if (ix == PREIDECTOULIST_TIT) return("PreIdecTouList.tit");
	else if (ix == PREIDECUSGAACCESS_X1) return("PreIdecUsgAAccess.x1");
	else if (ix == PREIDECUSGLIST_SRF) return("PreIdecUsgList.srf");
	else if (ix == PREIDECUSRAACCESS_X1) return("PreIdecUsrAAccess.x1");
	else if (ix == PREIDECUSRLIST_PRS) return("PreIdecUsrList.prs");
	else if (ix == PREIDECUSRLIST_SRF) return("PreIdecUsrList.srf");
	else if (ix == PREIDECUSRLIST_STE) return("PreIdecUsrList.ste");
	else if (ix == PREIDECUSRLIST_USG) return("PreIdecUsrList.usg");

	return("");
};

string DbsIdec::VecVPreset::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == VOID) return("none");
		else if (ix == PREIDECREFFIL) return("file");
		else if (ix == PREIDECREFMIS) return("mission");
		else if (ix == PREIDECREFPRS) return("person");
		else if (ix == PREIDECREFSES) return("session");
		else if (ix == PREIDECREFTOU) return("tour");
		else if (ix == PREIDECREFUSG) return("user group");
		else if (ix == PREIDECREFUSR) return("user");
		else return(getSref(ix));
	} else if (ixIdecVLocale == 2) {
		if (ix == VOID) return("kein");
		else if (ix == PREIDECREFFIL) return("Datei");
		else if (ix == PREIDECREFMIS) return("Mission");
		else if (ix == PREIDECREFPRS) return("Person");
		else if (ix == PREIDECREFSES) return("Sitzung");
		else if (ix == PREIDECREFTOU) return("Tour");
		else if (ix == PREIDECREFUSG) return("Benutzergruppe");
		else if (ix == PREIDECREFUSR) return("Benutzer");
		else return(getTitle(ix, 1));
	};

	return("");
};

/******************************************************************************
 class DbsIdec::VecVUserlevel
 ******************************************************************************/

uint DbsIdec::VecVUserlevel::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "adm") return ADM;
	else if (s == "gadm") return GADM;
	else if (s == "reg") return REG;
	else if (s == "vtor") return VTOR;

	return(0);
};

string DbsIdec::VecVUserlevel::getSref(
			const uint ix
		) {
	if (ix == ADM) return("adm");
	else if (ix == GADM) return("gadm");
	else if (ix == REG) return("reg");
	else if (ix == VTOR) return("vtor");

	return("");
};

string DbsIdec::VecVUserlevel::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == ADM) return("administrator");
		else if (ix == GADM) return("user group administrator");
		else if (ix == REG) return("regular user");
		else if (ix == VTOR) return("visitor");
	} else if (ixIdecVLocale == 2) {
		if (ix == ADM) return("Administrator");
		else if (ix == GADM) return("Gruppenadministrator");
		else if (ix == REG) return("regul\\u00e4rer Benutzer");
		else if (ix == VTOR) return("Besucher");
	};

	return("");
};

void DbsIdec::VecVUserlevel::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class DbsIdec::VecVValuelist
 ******************************************************************************/

uint DbsIdec::VecVValuelist::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "vlstidecumpersontitle") return VLSTIDECUMPERSONTITLE;

	return(0);
};

string DbsIdec::VecVValuelist::getSref(
			const uint ix
		) {
	if (ix == VLSTIDECUMPERSONTITLE) return("VlstIdecUMPersonTitle");

	return("");
};

string DbsIdec::VecVValuelist::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == VLSTIDECUMPERSONTITLE) return("title");
	} else if (ixIdecVLocale == 2) {
		if (ix == VLSTIDECUMPERSONTITLE) return("Anrede");
	};

	return("");
};

/******************************************************************************
 class DbsIdec::VecWUiaccess
 ******************************************************************************/

uint DbsIdec::VecWUiaccess::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "edit") ix |= EDIT;
		else if (ss[i] == "exec") ix |= EXEC;
		else if (ss[i] == "view") ix |= VIEW;
	};

	return(ix);
};

void DbsIdec::VecWUiaccess::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*VIEW);i*=2) if (ix & i) ics.insert(i);
};

string DbsIdec::VecWUiaccess::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & EDIT) ss.push_back("edit");
	if (ix & EXEC) ss.push_back("exec");
	if (ix & VIEW) ss.push_back("view");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

string DbsIdec::VecWUiaccess::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == EDIT) return("edit");
		else if (ix == EXEC) return("execute");
		else if (ix == VIEW) return("view");
	} else if (ixIdecVLocale == 2) {
		if (ix == EDIT) return("\\u00e4ndern");
		else if (ix == EXEC) return("ausf\\u00fchren");
		else if (ix == VIEW) return("anschauen");
	};

	return("");
};

void DbsIdec::VecWUiaccess::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=VIEW;i*=2) feed.appendIxSrefTitles(i, getSrefs(i), getTitle(i, ixIdecVLocale));
};

