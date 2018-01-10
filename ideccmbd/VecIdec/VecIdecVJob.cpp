/**
  * \file VecIdecVJob.cpp
  * vector VecIdecVJob (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVJob.h"

/******************************************************************************
 namespace VecIdecVJob
 ******************************************************************************/

uint VecIdecVJob::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "crdidecad1") return CRDIDECAD1;
	else if (s == "crdidecfil") return CRDIDECFIL;
	else if (s == "crdideciaq") return CRDIDECIAQ;
	else if (s == "crdidecmis") return CRDIDECMIS;
	else if (s == "crdidecnav") return CRDIDECNAV;
	else if (s == "crdidecscf") return CRDIDECSCF;
	else if (s == "crdidectou") return CRDIDECTOU;
	else if (s == "crdidecusg") return CRDIDECUSG;
	else if (s == "crdidecusr") return CRDIDECUSR;
	else if (s == "crdidecutl") return CRDIDECUTL;
	else if (s == "dlgidecfilextrmed") return DLGIDECFILEXTRMED;
	else if (s == "dlgidecmisnew") return DLGIDECMISNEW;
	else if (s == "dlgidecnavloaini") return DLGIDECNAVLOAINI;
	else if (s == "dlgidectounew") return DLGIDECTOUNEW;
	else if (s == "dlgidecutlfusion") return DLGIDECUTLFUSION;
	else if (s == "dlgidecutlphi") return DLGIDECUTLPHI;
	else if (s == "dlgidecutlqcdaln") return DLGIDECUTLQCDALN;
	else if (s == "dlgidecutlqcdnuc") return DLGIDECUTLQCDNUC;
	else if (s == "dlgidecutlstereo") return DLGIDECUTLSTEREO;
	else if (s == "dlgidecutltheta") return DLGIDECUTLTHETA;
	else if (s == "iexidecini") return IEXIDECINI;
	else if (s == "jobidecautdet1") return JOBIDECAUTDET1;
	else if (s == "jobidecfusion") return JOBIDECFUSION;
	else if (s == "jobidecillum") return JOBIDECILLUM;
	else if (s == "jobideclwiracq") return JOBIDECLWIRACQ;
	else if (s == "jobidecmechctl") return JOBIDECMECHCTL;
	else if (s == "jobidecqcdacq") return JOBIDECQCDACQ;
	else if (s == "jobidecrecord") return JOBIDECRECORD;
	else if (s == "jobidecspotfind") return JOBIDECSPOTFIND;
	else if (s == "jobidecstereo") return JOBIDECSTEREO;
	else if (s == "jobidectrigger") return JOBIDECTRIGGER;
	else if (s == "jobidecvislacq") return JOBIDECVISLACQ;
	else if (s == "jobidecvisracq") return JOBIDECVISRACQ;
	else if (s == "pnlidecad1control") return PNLIDECAD1CONTROL;
	else if (s == "pnlidecad1headbar") return PNLIDECAD1HEADBAR;
	else if (s == "pnlidecfildetail") return PNLIDECFILDETAIL;
	else if (s == "pnlidecfilheadbar") return PNLIDECFILHEADBAR;
	else if (s == "pnlidecfillist") return PNLIDECFILLIST;
	else if (s == "pnlidecfilrec") return PNLIDECFILREC;
	else if (s == "pnlideciaqheadbar") return PNLIDECIAQHEADBAR;
	else if (s == "pnlideciaqlive") return PNLIDECIAQLIVE;
	else if (s == "pnlideciaqmech") return PNLIDECIAQMECH;
	else if (s == "pnlideciaqqcdsp") return PNLIDECIAQQCDSP;
	else if (s == "pnlideciaqscill") return PNLIDECIAQSCILL;
	else if (s == "pnlidecmis1ntour") return PNLIDECMIS1NTOUR;
	else if (s == "pnlidecmisdetail") return PNLIDECMISDETAIL;
	else if (s == "pnlidecmisheadbar") return PNLIDECMISHEADBAR;
	else if (s == "pnlidecmislist") return PNLIDECMISLIST;
	else if (s == "pnlidecmisrec") return PNLIDECMISREC;
	else if (s == "pnlidecmisref1nfile") return PNLIDECMISREF1NFILE;
	else if (s == "pnlidecnavheadbar") return PNLIDECNAVHEADBAR;
	else if (s == "pnlidecnavmaint") return PNLIDECNAVMAINT;
	else if (s == "pnlidecnavopr") return PNLIDECNAVOPR;
	else if (s == "pnlidecnavpre") return PNLIDECNAVPRE;
	else if (s == "pnlidecscfconn") return PNLIDECSCFCONN;
	else if (s == "pnlidecscfheadbar") return PNLIDECSCFHEADBAR;
	else if (s == "pnlidecscflwir") return PNLIDECSCFLWIR;
	else if (s == "pnlidecscfmech") return PNLIDECSCFMECH;
	else if (s == "pnlidecscfoptics") return PNLIDECSCFOPTICS;
	else if (s == "pnlidecscfqcd") return PNLIDECSCFQCD;
	else if (s == "pnlidecscfrecord") return PNLIDECSCFRECORD;
	else if (s == "pnlidecscfstatus") return PNLIDECSCFSTATUS;
	else if (s == "pnlidecscftrigger") return PNLIDECSCFTRIGGER;
	else if (s == "pnlidectoudetail") return PNLIDECTOUDETAIL;
	else if (s == "pnlidectouheadbar") return PNLIDECTOUHEADBAR;
	else if (s == "pnlidectoulist") return PNLIDECTOULIST;
	else if (s == "pnlidectourec") return PNLIDECTOUREC;
	else if (s == "pnlidectouref1nfile") return PNLIDECTOUREF1NFILE;
	else if (s == "pnlidecusgaaccess") return PNLIDECUSGAACCESS;
	else if (s == "pnlidecusgdetail") return PNLIDECUSGDETAIL;
	else if (s == "pnlidecusgheadbar") return PNLIDECUSGHEADBAR;
	else if (s == "pnlidecusglist") return PNLIDECUSGLIST;
	else if (s == "pnlidecusgmnuser") return PNLIDECUSGMNUSER;
	else if (s == "pnlidecusgrec") return PNLIDECUSGREC;
	else if (s == "pnlidecusr1nsession") return PNLIDECUSR1NSESSION;
	else if (s == "pnlidecusraaccess") return PNLIDECUSRAACCESS;
	else if (s == "pnlidecusrdetail") return PNLIDECUSRDETAIL;
	else if (s == "pnlidecusrheadbar") return PNLIDECUSRHEADBAR;
	else if (s == "pnlidecusrlist") return PNLIDECUSRLIST;
	else if (s == "pnlidecusrmnusergroup") return PNLIDECUSRMNUSERGROUP;
	else if (s == "pnlidecusrrec") return PNLIDECUSRREC;
	else if (s == "pnlidecutlheadbar") return PNLIDECUTLHEADBAR;
	else if (s == "pnlidecutlspiterm") return PNLIDECUTLSPITERM;
	else if (s == "qryidecfillist") return QRYIDECFILLIST;
	else if (s == "qryidecmis1ntour") return QRYIDECMIS1NTOUR;
	else if (s == "qryidecmislist") return QRYIDECMISLIST;
	else if (s == "qryidecmisref1nfile") return QRYIDECMISREF1NFILE;
	else if (s == "qryidectoulist") return QRYIDECTOULIST;
	else if (s == "qryidectouref1nfile") return QRYIDECTOUREF1NFILE;
	else if (s == "qryidecusgaaccess") return QRYIDECUSGAACCESS;
	else if (s == "qryidecusglist") return QRYIDECUSGLIST;
	else if (s == "qryidecusgmnuser") return QRYIDECUSGMNUSER;
	else if (s == "qryidecusr1nsession") return QRYIDECUSR1NSESSION;
	else if (s == "qryidecusraaccess") return QRYIDECUSRAACCESS;
	else if (s == "qryidecusrlist") return QRYIDECUSRLIST;
	else if (s == "qryidecusrmnusergroup") return QRYIDECUSRMNUSERGROUP;
	else if (s == "rootidec") return ROOTIDEC;
	else if (s == "sessidec") return SESSIDEC;

	return(0);
};

string VecIdecVJob::getSref(
			const uint ix
		) {
	if (ix == CRDIDECAD1) return("CrdIdecAd1");
	else if (ix == CRDIDECFIL) return("CrdIdecFil");
	else if (ix == CRDIDECIAQ) return("CrdIdecIaq");
	else if (ix == CRDIDECMIS) return("CrdIdecMis");
	else if (ix == CRDIDECNAV) return("CrdIdecNav");
	else if (ix == CRDIDECSCF) return("CrdIdecScf");
	else if (ix == CRDIDECTOU) return("CrdIdecTou");
	else if (ix == CRDIDECUSG) return("CrdIdecUsg");
	else if (ix == CRDIDECUSR) return("CrdIdecUsr");
	else if (ix == CRDIDECUTL) return("CrdIdecUtl");
	else if (ix == DLGIDECFILEXTRMED) return("DlgIdecFilExtrmed");
	else if (ix == DLGIDECMISNEW) return("DlgIdecMisNew");
	else if (ix == DLGIDECNAVLOAINI) return("DlgIdecNavLoaini");
	else if (ix == DLGIDECTOUNEW) return("DlgIdecTouNew");
	else if (ix == DLGIDECUTLFUSION) return("DlgIdecUtlFusion");
	else if (ix == DLGIDECUTLPHI) return("DlgIdecUtlPhi");
	else if (ix == DLGIDECUTLQCDALN) return("DlgIdecUtlQcdaln");
	else if (ix == DLGIDECUTLQCDNUC) return("DlgIdecUtlQcdnuc");
	else if (ix == DLGIDECUTLSTEREO) return("DlgIdecUtlStereo");
	else if (ix == DLGIDECUTLTHETA) return("DlgIdecUtlTheta");
	else if (ix == IEXIDECINI) return("IexIdecIni");
	else if (ix == JOBIDECAUTDET1) return("JobIdecAutdet1");
	else if (ix == JOBIDECFUSION) return("JobIdecFusion");
	else if (ix == JOBIDECILLUM) return("JobIdecIllum");
	else if (ix == JOBIDECLWIRACQ) return("JobIdecLwiracq");
	else if (ix == JOBIDECMECHCTL) return("JobIdecMechctl");
	else if (ix == JOBIDECQCDACQ) return("JobIdecQcdacq");
	else if (ix == JOBIDECRECORD) return("JobIdecRecord");
	else if (ix == JOBIDECSPOTFIND) return("JobIdecSpotfind");
	else if (ix == JOBIDECSTEREO) return("JobIdecStereo");
	else if (ix == JOBIDECTRIGGER) return("JobIdecTrigger");
	else if (ix == JOBIDECVISLACQ) return("JobIdecVislacq");
	else if (ix == JOBIDECVISRACQ) return("JobIdecVisracq");
	else if (ix == PNLIDECAD1CONTROL) return("PnlIdecAd1Control");
	else if (ix == PNLIDECAD1HEADBAR) return("PnlIdecAd1Headbar");
	else if (ix == PNLIDECFILDETAIL) return("PnlIdecFilDetail");
	else if (ix == PNLIDECFILHEADBAR) return("PnlIdecFilHeadbar");
	else if (ix == PNLIDECFILLIST) return("PnlIdecFilList");
	else if (ix == PNLIDECFILREC) return("PnlIdecFilRec");
	else if (ix == PNLIDECIAQHEADBAR) return("PnlIdecIaqHeadbar");
	else if (ix == PNLIDECIAQLIVE) return("PnlIdecIaqLive");
	else if (ix == PNLIDECIAQMECH) return("PnlIdecIaqMech");
	else if (ix == PNLIDECIAQQCDSP) return("PnlIdecIaqQcdsp");
	else if (ix == PNLIDECIAQSCILL) return("PnlIdecIaqScill");
	else if (ix == PNLIDECMIS1NTOUR) return("PnlIdecMis1NTour");
	else if (ix == PNLIDECMISDETAIL) return("PnlIdecMisDetail");
	else if (ix == PNLIDECMISHEADBAR) return("PnlIdecMisHeadbar");
	else if (ix == PNLIDECMISLIST) return("PnlIdecMisList");
	else if (ix == PNLIDECMISREC) return("PnlIdecMisRec");
	else if (ix == PNLIDECMISREF1NFILE) return("PnlIdecMisRef1NFile");
	else if (ix == PNLIDECNAVHEADBAR) return("PnlIdecNavHeadbar");
	else if (ix == PNLIDECNAVMAINT) return("PnlIdecNavMaint");
	else if (ix == PNLIDECNAVOPR) return("PnlIdecNavOpr");
	else if (ix == PNLIDECNAVPRE) return("PnlIdecNavPre");
	else if (ix == PNLIDECSCFCONN) return("PnlIdecScfConn");
	else if (ix == PNLIDECSCFHEADBAR) return("PnlIdecScfHeadbar");
	else if (ix == PNLIDECSCFLWIR) return("PnlIdecScfLwir");
	else if (ix == PNLIDECSCFMECH) return("PnlIdecScfMech");
	else if (ix == PNLIDECSCFOPTICS) return("PnlIdecScfOptics");
	else if (ix == PNLIDECSCFQCD) return("PnlIdecScfQcd");
	else if (ix == PNLIDECSCFRECORD) return("PnlIdecScfRecord");
	else if (ix == PNLIDECSCFSTATUS) return("PnlIdecScfStatus");
	else if (ix == PNLIDECSCFTRIGGER) return("PnlIdecScfTrigger");
	else if (ix == PNLIDECTOUDETAIL) return("PnlIdecTouDetail");
	else if (ix == PNLIDECTOUHEADBAR) return("PnlIdecTouHeadbar");
	else if (ix == PNLIDECTOULIST) return("PnlIdecTouList");
	else if (ix == PNLIDECTOUREC) return("PnlIdecTouRec");
	else if (ix == PNLIDECTOUREF1NFILE) return("PnlIdecTouRef1NFile");
	else if (ix == PNLIDECUSGAACCESS) return("PnlIdecUsgAAccess");
	else if (ix == PNLIDECUSGDETAIL) return("PnlIdecUsgDetail");
	else if (ix == PNLIDECUSGHEADBAR) return("PnlIdecUsgHeadbar");
	else if (ix == PNLIDECUSGLIST) return("PnlIdecUsgList");
	else if (ix == PNLIDECUSGMNUSER) return("PnlIdecUsgMNUser");
	else if (ix == PNLIDECUSGREC) return("PnlIdecUsgRec");
	else if (ix == PNLIDECUSR1NSESSION) return("PnlIdecUsr1NSession");
	else if (ix == PNLIDECUSRAACCESS) return("PnlIdecUsrAAccess");
	else if (ix == PNLIDECUSRDETAIL) return("PnlIdecUsrDetail");
	else if (ix == PNLIDECUSRHEADBAR) return("PnlIdecUsrHeadbar");
	else if (ix == PNLIDECUSRLIST) return("PnlIdecUsrList");
	else if (ix == PNLIDECUSRMNUSERGROUP) return("PnlIdecUsrMNUsergroup");
	else if (ix == PNLIDECUSRREC) return("PnlIdecUsrRec");
	else if (ix == PNLIDECUTLHEADBAR) return("PnlIdecUtlHeadbar");
	else if (ix == PNLIDECUTLSPITERM) return("PnlIdecUtlSpiterm");
	else if (ix == QRYIDECFILLIST) return("QryIdecFilList");
	else if (ix == QRYIDECMIS1NTOUR) return("QryIdecMis1NTour");
	else if (ix == QRYIDECMISLIST) return("QryIdecMisList");
	else if (ix == QRYIDECMISREF1NFILE) return("QryIdecMisRef1NFile");
	else if (ix == QRYIDECTOULIST) return("QryIdecTouList");
	else if (ix == QRYIDECTOUREF1NFILE) return("QryIdecTouRef1NFile");
	else if (ix == QRYIDECUSGAACCESS) return("QryIdecUsgAAccess");
	else if (ix == QRYIDECUSGLIST) return("QryIdecUsgList");
	else if (ix == QRYIDECUSGMNUSER) return("QryIdecUsgMNUser");
	else if (ix == QRYIDECUSR1NSESSION) return("QryIdecUsr1NSession");
	else if (ix == QRYIDECUSRAACCESS) return("QryIdecUsrAAccess");
	else if (ix == QRYIDECUSRLIST) return("QryIdecUsrList");
	else if (ix == QRYIDECUSRMNUSERGROUP) return("QryIdecUsrMNUsergroup");
	else if (ix == ROOTIDEC) return("RootIdec");
	else if (ix == SESSIDEC) return("SessIdec");

	return("");
};

