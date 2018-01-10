/**
  * \file VecIdecVJob.h
  * vector VecIdecVJob (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVJOB_H
#define VECIDECVJOB_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVJob
	*/
namespace VecIdecVJob {
	const uint CRDIDECAD1 = 1;
	const uint CRDIDECFIL = 2;
	const uint CRDIDECIAQ = 3;
	const uint CRDIDECMIS = 4;
	const uint CRDIDECNAV = 5;
	const uint CRDIDECSCF = 6;
	const uint CRDIDECTOU = 7;
	const uint CRDIDECUSG = 8;
	const uint CRDIDECUSR = 9;
	const uint CRDIDECUTL = 10;
	const uint DLGIDECFILEXTRMED = 11;
	const uint DLGIDECMISNEW = 12;
	const uint DLGIDECNAVLOAINI = 13;
	const uint DLGIDECTOUNEW = 14;
	const uint DLGIDECUTLFUSION = 15;
	const uint DLGIDECUTLPHI = 16;
	const uint DLGIDECUTLQCDALN = 17;
	const uint DLGIDECUTLQCDNUC = 18;
	const uint DLGIDECUTLSTEREO = 19;
	const uint DLGIDECUTLTHETA = 20;
	const uint IEXIDECINI = 21;
	const uint JOBIDECAUTDET1 = 22;
	const uint JOBIDECFUSION = 23;
	const uint JOBIDECILLUM = 24;
	const uint JOBIDECLWIRACQ = 25;
	const uint JOBIDECMECHCTL = 26;
	const uint JOBIDECQCDACQ = 27;
	const uint JOBIDECRECORD = 28;
	const uint JOBIDECSPOTFIND = 29;
	const uint JOBIDECSTEREO = 30;
	const uint JOBIDECTRIGGER = 31;
	const uint JOBIDECVISLACQ = 32;
	const uint JOBIDECVISRACQ = 33;
	const uint PNLIDECAD1CONTROL = 34;
	const uint PNLIDECAD1HEADBAR = 35;
	const uint PNLIDECFILDETAIL = 36;
	const uint PNLIDECFILHEADBAR = 37;
	const uint PNLIDECFILLIST = 38;
	const uint PNLIDECFILREC = 39;
	const uint PNLIDECIAQHEADBAR = 40;
	const uint PNLIDECIAQLIVE = 41;
	const uint PNLIDECIAQMECH = 42;
	const uint PNLIDECIAQQCDSP = 43;
	const uint PNLIDECIAQSCILL = 44;
	const uint PNLIDECMIS1NTOUR = 45;
	const uint PNLIDECMISDETAIL = 46;
	const uint PNLIDECMISHEADBAR = 47;
	const uint PNLIDECMISLIST = 48;
	const uint PNLIDECMISREC = 49;
	const uint PNLIDECMISREF1NFILE = 50;
	const uint PNLIDECNAVHEADBAR = 51;
	const uint PNLIDECNAVMAINT = 52;
	const uint PNLIDECNAVOPR = 53;
	const uint PNLIDECNAVPRE = 54;
	const uint PNLIDECSCFCONN = 55;
	const uint PNLIDECSCFHEADBAR = 56;
	const uint PNLIDECSCFLWIR = 57;
	const uint PNLIDECSCFMECH = 58;
	const uint PNLIDECSCFOPTICS = 59;
	const uint PNLIDECSCFQCD = 60;
	const uint PNLIDECSCFRECORD = 61;
	const uint PNLIDECSCFSTATUS = 62;
	const uint PNLIDECSCFTRIGGER = 63;
	const uint PNLIDECTOUDETAIL = 64;
	const uint PNLIDECTOUHEADBAR = 65;
	const uint PNLIDECTOULIST = 66;
	const uint PNLIDECTOUREC = 67;
	const uint PNLIDECTOUREF1NFILE = 68;
	const uint PNLIDECUSGAACCESS = 69;
	const uint PNLIDECUSGDETAIL = 70;
	const uint PNLIDECUSGHEADBAR = 71;
	const uint PNLIDECUSGLIST = 72;
	const uint PNLIDECUSGMNUSER = 73;
	const uint PNLIDECUSGREC = 74;
	const uint PNLIDECUSR1NSESSION = 75;
	const uint PNLIDECUSRAACCESS = 76;
	const uint PNLIDECUSRDETAIL = 77;
	const uint PNLIDECUSRHEADBAR = 78;
	const uint PNLIDECUSRLIST = 79;
	const uint PNLIDECUSRMNUSERGROUP = 80;
	const uint PNLIDECUSRREC = 81;
	const uint PNLIDECUTLHEADBAR = 82;
	const uint PNLIDECUTLSPITERM = 83;
	const uint QRYIDECFILLIST = 84;
	const uint QRYIDECMIS1NTOUR = 85;
	const uint QRYIDECMISLIST = 86;
	const uint QRYIDECMISREF1NFILE = 87;
	const uint QRYIDECTOULIST = 88;
	const uint QRYIDECTOUREF1NFILE = 89;
	const uint QRYIDECUSGAACCESS = 90;
	const uint QRYIDECUSGLIST = 91;
	const uint QRYIDECUSGMNUSER = 92;
	const uint QRYIDECUSR1NSESSION = 93;
	const uint QRYIDECUSRAACCESS = 94;
	const uint QRYIDECUSRLIST = 95;
	const uint QRYIDECUSRMNUSERGROUP = 96;
	const uint ROOTIDEC = 97;
	const uint SESSIDEC = 98;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

