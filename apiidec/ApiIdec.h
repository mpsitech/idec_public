/**
  * \file ApiIdec.h
  * Idec API library global functionality (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef APIIDEC_H
#define APIIDEC_H

#define IDEC_VERSION "0.2.1"
#define IDEC_VERSION_MAJOR 0
#define IDEC_VERSION_MINOR 2
#define IDEC_VERSION_SUB 1

#include "ApiIdec_blks.h"

#include "IdecQFilList.h"
#include "IdecQMis1NTour.h"
#include "IdecQMisList.h"
#include "IdecQMisRef1NFile.h"
#include "IdecQTouList.h"
#include "IdecQTouRef1NFile.h"
#include "IdecQUsgAAccess.h"
#include "IdecQUsgList.h"
#include "IdecQUsgMNUser.h"
#include "IdecQUsr1NSession.h"
#include "IdecQUsrAAccess.h"
#include "IdecQUsrList.h"
#include "IdecQUsrMNUsergroup.h"

#include "CrdIdecAd1.h"
#include "CrdIdecFil.h"
#include "CrdIdecIaq.h"
#include "CrdIdecMis.h"
#include "CrdIdecNav.h"
#include "CrdIdecScf.h"
#include "CrdIdecTou.h"
#include "CrdIdecUsg.h"
#include "CrdIdecUsr.h"
#include "CrdIdecUtl.h"
#include "DlgIdecFilExtrmed.h"
#include "DlgIdecMisNew.h"
#include "DlgIdecNavLoaini.h"
#include "DlgIdecTouNew.h"
#include "DlgIdecUtlFusion.h"
#include "DlgIdecUtlPhi.h"
#include "DlgIdecUtlQcdaln.h"
#include "DlgIdecUtlQcdnuc.h"
#include "DlgIdecUtlStereo.h"
#include "DlgIdecUtlTheta.h"
#include "PnlIdecAd1Control.h"
#include "PnlIdecAd1Headbar.h"
#include "PnlIdecFilDetail.h"
#include "PnlIdecFilHeadbar.h"
#include "PnlIdecFilList.h"
#include "PnlIdecFilRec.h"
#include "PnlIdecIaqHeadbar.h"
#include "PnlIdecIaqLive.h"
#include "PnlIdecIaqMech.h"
#include "PnlIdecIaqQcdsp.h"
#include "PnlIdecIaqScill.h"
#include "PnlIdecMis1NTour.h"
#include "PnlIdecMisDetail.h"
#include "PnlIdecMisHeadbar.h"
#include "PnlIdecMisList.h"
#include "PnlIdecMisRec.h"
#include "PnlIdecMisRef1NFile.h"
#include "PnlIdecNavHeadbar.h"
#include "PnlIdecNavMaint.h"
#include "PnlIdecNavOpr.h"
#include "PnlIdecNavPre.h"
#include "PnlIdecScfConn.h"
#include "PnlIdecScfHeadbar.h"
#include "PnlIdecScfLwir.h"
#include "PnlIdecScfMech.h"
#include "PnlIdecScfOptics.h"
#include "PnlIdecScfQcd.h"
#include "PnlIdecScfRecord.h"
#include "PnlIdecScfStatus.h"
#include "PnlIdecScfTrigger.h"
#include "PnlIdecTouDetail.h"
#include "PnlIdecTouHeadbar.h"
#include "PnlIdecTouList.h"
#include "PnlIdecTouRec.h"
#include "PnlIdecTouRef1NFile.h"
#include "PnlIdecUsgAAccess.h"
#include "PnlIdecUsgDetail.h"
#include "PnlIdecUsgHeadbar.h"
#include "PnlIdecUsgList.h"
#include "PnlIdecUsgMNUser.h"
#include "PnlIdecUsgRec.h"
#include "PnlIdecUsr1NSession.h"
#include "PnlIdecUsrAAccess.h"
#include "PnlIdecUsrDetail.h"
#include "PnlIdecUsrHeadbar.h"
#include "PnlIdecUsrList.h"
#include "PnlIdecUsrMNUsergroup.h"
#include "PnlIdecUsrRec.h"
#include "PnlIdecUtlHeadbar.h"
#include "PnlIdecUtlSpiterm.h"
#include "QryIdecFilList.h"
#include "QryIdecMis1NTour.h"
#include "QryIdecMisList.h"
#include "QryIdecMisRef1NFile.h"
#include "QryIdecTouList.h"
#include "QryIdecTouRef1NFile.h"
#include "QryIdecUsgAAccess.h"
#include "QryIdecUsgList.h"
#include "QryIdecUsgMNUser.h"
#include "QryIdecUsr1NSession.h"
#include "QryIdecUsrAAccess.h"
#include "QryIdecUsrList.h"
#include "QryIdecUsrMNUsergroup.h"
#include "RootIdec.h"
#include "SessIdec.h"

/**
  * StgIdecapi
  */
class StgIdecapi : public Block {

public:
	static const ubigint IP = 1;
	static const ubigint PORT = 2;
	static const ubigint USERNAME = 3;
	static const ubigint PASSWORD = 4;

public:
	StgIdecapi(const string ip = "", const uint port = 0, const string username = "", const string password = "");

public:
	string ip;
	uint port;
	string username;
	string password;

public:
	static bool all(const set<uint>& items);
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
	void writeXML(xmlTextWriter* wr, string difftag = "", bool shorttags = true);
	set<uint> compare(const StgIdecapi* comp);
};

/**
  * ApiIdec
  */
namespace ApiIdec {
	uint readDpchEng(char* buf, unsigned long buflen, DpchEngIdec** dpcheng);
	void writeDpchApp(DpchAppIdec* dpchapp, char** buf, unsigned long& buflen, unsigned long ofs = 0);
};

#endif

