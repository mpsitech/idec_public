/**
  * \file ApiIdec.cpp
  * Idec API library global functionality (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "ApiIdec.h"

/******************************************************************************
 class StgIdecapi
 ******************************************************************************/

StgIdecapi::StgIdecapi(
			const string ip
			, const uint port
			, const string username
			, const string password
		) : Block() {
	this->ip = ip;
	this->port = port;
	this->username = username;
	this->password = password;

	mask = {IP, PORT, USERNAME, PASSWORD};
};

bool StgIdecapi::all(
			const set<uint>& items
		) {
	if (!find(items, IP)) return false;
	if (!find(items, PORT)) return false;
	if (!find(items, USERNAME)) return false;
	if (!find(items, PASSWORD)) return false;

	return true;
};

bool StgIdecapi::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecapi");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecapi";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ip", ip)) add(IP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "port", port)) add(PORT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "username", username)) add(USERNAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "password", password)) add(PASSWORD);
	};

	return basefound;
};

void StgIdecapi::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecapi";

	string itemtag;
	if (shorttags)
		itemtag = "Si";
	else
		itemtag = "StgitemIdecapi";

	// XML output
	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "ip", ip);
		writeUintAttr(wr, itemtag, "sref", "port", port);
		writeStringAttr(wr, itemtag, "sref", "username", username);
		writeStringAttr(wr, itemtag, "sref", "password", password);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecapi::compare(
			const StgIdecapi* comp
		) {
	set<uint> items;

	if (ip == comp->ip) insert(items, IP);
	if (port == comp->port) insert(items, PORT);
	if (username == comp->username) insert(items, USERNAME);
	if (password == comp->password) insert(items, PASSWORD);

	return items;
};

/******************************************************************************
 namespace ApiIdec
 ******************************************************************************/

uint ApiIdec::readDpchEng(
			char* buf
			, unsigned long buflen
			, DpchEngIdec** dpcheng
		) {
	xmlDoc* doc = NULL;
	xmlXPathContext* docctx = NULL;

	parseBuffer(buf, buflen, &doc, &docctx);

	uint ixIdecVDpch = VecIdecVDpch::getIx(extractRoot(doc));

	if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECFILEXTRMEDDATA) {
		*dpcheng = new DlgIdecFilExtrmed::DpchEngData();
		((DlgIdecFilExtrmed::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECMISNEWDATA) {
		*dpcheng = new DlgIdecMisNew::DpchEngData();
		((DlgIdecMisNew::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECNAVLOAINIDATA) {
		*dpcheng = new DlgIdecNavLoaini::DpchEngData();
		((DlgIdecNavLoaini::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECTOUNEWDATA) {
		*dpcheng = new DlgIdecTouNew::DpchEngData();
		((DlgIdecTouNew::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECUTLFUSIONDATA) {
		*dpcheng = new DlgIdecUtlFusion::DpchEngData();
		((DlgIdecUtlFusion::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECUTLPHIDATA) {
		*dpcheng = new DlgIdecUtlPhi::DpchEngData();
		((DlgIdecUtlPhi::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECUTLQCDALNDATA) {
		*dpcheng = new DlgIdecUtlQcdaln::DpchEngData();
		((DlgIdecUtlQcdaln::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECUTLQCDNUCDATA) {
		*dpcheng = new DlgIdecUtlQcdnuc::DpchEngData();
		((DlgIdecUtlQcdnuc::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECUTLSTEREODATA) {
		*dpcheng = new DlgIdecUtlStereo::DpchEngData();
		((DlgIdecUtlStereo::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGDLGIDECUTLTHETADATA) {
		*dpcheng = new DlgIdecUtlTheta::DpchEngData();
		((DlgIdecUtlTheta::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECACK) {
		*dpcheng = new DpchEngIdecAck();
		((DpchEngIdecAck*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECAD1CONTROLDATA) {
		*dpcheng = new PnlIdecAd1Control::DpchEngData();
		((PnlIdecAd1Control::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECAD1DATA) {
		*dpcheng = new CrdIdecAd1::DpchEngData();
		((CrdIdecAd1::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECAD1HEADBARDATA) {
		*dpcheng = new PnlIdecAd1Headbar::DpchEngData();
		((PnlIdecAd1Headbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECALERT) {
		*dpcheng = new DpchEngIdecAlert();
		((DpchEngIdecAlert*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECCONFIRM) {
		*dpcheng = new DpchEngIdecConfirm();
		((DpchEngIdecConfirm*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECFILDATA) {
		*dpcheng = new CrdIdecFil::DpchEngData();
		((CrdIdecFil::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECFILDETAILDATA) {
		*dpcheng = new PnlIdecFilDetail::DpchEngData();
		((PnlIdecFilDetail::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECFILHEADBARDATA) {
		*dpcheng = new PnlIdecFilHeadbar::DpchEngData();
		((PnlIdecFilHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECFILLISTDATA) {
		*dpcheng = new PnlIdecFilList::DpchEngData();
		((PnlIdecFilList::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECFILRECDATA) {
		*dpcheng = new PnlIdecFilRec::DpchEngData();
		((PnlIdecFilRec::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQDATA) {
		*dpcheng = new CrdIdecIaq::DpchEngData();
		((CrdIdecIaq::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQHEADBARDATA) {
		*dpcheng = new PnlIdecIaqHeadbar::DpchEngData();
		((PnlIdecIaqHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQLIVEDATA) {
		*dpcheng = new PnlIdecIaqLive::DpchEngData();
		((PnlIdecIaqLive::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQLIVELIVE) {
		*dpcheng = new PnlIdecIaqLive::DpchEngLive();
		((PnlIdecIaqLive::DpchEngLive*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQMECHDATA) {
		*dpcheng = new PnlIdecIaqMech::DpchEngData();
		((PnlIdecIaqMech::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQMECHLIVE) {
		*dpcheng = new PnlIdecIaqMech::DpchEngLive();
		((PnlIdecIaqMech::DpchEngLive*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQQCDSPDATA) {
		*dpcheng = new PnlIdecIaqQcdsp::DpchEngData();
		((PnlIdecIaqQcdsp::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQQCDSPLIVE) {
		*dpcheng = new PnlIdecIaqQcdsp::DpchEngLive();
		((PnlIdecIaqQcdsp::DpchEngLive*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECIAQSCILLDATA) {
		*dpcheng = new PnlIdecIaqScill::DpchEngData();
		((PnlIdecIaqScill::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMIS1NTOURDATA) {
		*dpcheng = new PnlIdecMis1NTour::DpchEngData();
		((PnlIdecMis1NTour::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMISDATA) {
		*dpcheng = new CrdIdecMis::DpchEngData();
		((CrdIdecMis::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMISDETAILDATA) {
		*dpcheng = new PnlIdecMisDetail::DpchEngData();
		((PnlIdecMisDetail::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMISHEADBARDATA) {
		*dpcheng = new PnlIdecMisHeadbar::DpchEngData();
		((PnlIdecMisHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMISLISTDATA) {
		*dpcheng = new PnlIdecMisList::DpchEngData();
		((PnlIdecMisList::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMISRECDATA) {
		*dpcheng = new PnlIdecMisRec::DpchEngData();
		((PnlIdecMisRec::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECMISREF1NFILEDATA) {
		*dpcheng = new PnlIdecMisRef1NFile::DpchEngData();
		((PnlIdecMisRef1NFile::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECNAVDATA) {
		*dpcheng = new CrdIdecNav::DpchEngData();
		((CrdIdecNav::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECNAVHEADBARDATA) {
		*dpcheng = new PnlIdecNavHeadbar::DpchEngData();
		((PnlIdecNavHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECNAVMAINTDATA) {
		*dpcheng = new PnlIdecNavMaint::DpchEngData();
		((PnlIdecNavMaint::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECNAVOPRDATA) {
		*dpcheng = new PnlIdecNavOpr::DpchEngData();
		((PnlIdecNavOpr::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECNAVPREDATA) {
		*dpcheng = new PnlIdecNavPre::DpchEngData();
		((PnlIdecNavPre::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFCONNDATA) {
		*dpcheng = new PnlIdecScfConn::DpchEngData();
		((PnlIdecScfConn::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFCONNLIVE) {
		*dpcheng = new PnlIdecScfConn::DpchEngLive();
		((PnlIdecScfConn::DpchEngLive*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFDATA) {
		*dpcheng = new CrdIdecScf::DpchEngData();
		((CrdIdecScf::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFHEADBARDATA) {
		*dpcheng = new PnlIdecScfHeadbar::DpchEngData();
		((PnlIdecScfHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFLWIRDATA) {
		*dpcheng = new PnlIdecScfLwir::DpchEngData();
		((PnlIdecScfLwir::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFMECHDATA) {
		*dpcheng = new PnlIdecScfMech::DpchEngData();
		((PnlIdecScfMech::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFMECHLIVE) {
		*dpcheng = new PnlIdecScfMech::DpchEngLive();
		((PnlIdecScfMech::DpchEngLive*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFOPTICSDATA) {
		*dpcheng = new PnlIdecScfOptics::DpchEngData();
		((PnlIdecScfOptics::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFQCDDATA) {
		*dpcheng = new PnlIdecScfQcd::DpchEngData();
		((PnlIdecScfQcd::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFRECORDDATA) {
		*dpcheng = new PnlIdecScfRecord::DpchEngData();
		((PnlIdecScfRecord::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFSTATUSDATA) {
		*dpcheng = new PnlIdecScfStatus::DpchEngData();
		((PnlIdecScfStatus::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSCFTRIGGERDATA) {
		*dpcheng = new PnlIdecScfTrigger::DpchEngData();
		((PnlIdecScfTrigger::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECSUSPEND) {
		*dpcheng = new DpchEngIdecSuspend();
		((DpchEngIdecSuspend*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECTOUDATA) {
		*dpcheng = new CrdIdecTou::DpchEngData();
		((CrdIdecTou::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECTOUDETAILDATA) {
		*dpcheng = new PnlIdecTouDetail::DpchEngData();
		((PnlIdecTouDetail::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECTOUHEADBARDATA) {
		*dpcheng = new PnlIdecTouHeadbar::DpchEngData();
		((PnlIdecTouHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECTOULISTDATA) {
		*dpcheng = new PnlIdecTouList::DpchEngData();
		((PnlIdecTouList::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECTOURECDATA) {
		*dpcheng = new PnlIdecTouRec::DpchEngData();
		((PnlIdecTouRec::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECTOUREF1NFILEDATA) {
		*dpcheng = new PnlIdecTouRef1NFile::DpchEngData();
		((PnlIdecTouRef1NFile::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGAACCESSDATA) {
		*dpcheng = new PnlIdecUsgAAccess::DpchEngData();
		((PnlIdecUsgAAccess::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGDATA) {
		*dpcheng = new CrdIdecUsg::DpchEngData();
		((CrdIdecUsg::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGDETAILDATA) {
		*dpcheng = new PnlIdecUsgDetail::DpchEngData();
		((PnlIdecUsgDetail::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGHEADBARDATA) {
		*dpcheng = new PnlIdecUsgHeadbar::DpchEngData();
		((PnlIdecUsgHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGLISTDATA) {
		*dpcheng = new PnlIdecUsgList::DpchEngData();
		((PnlIdecUsgList::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGMNUSERDATA) {
		*dpcheng = new PnlIdecUsgMNUser::DpchEngData();
		((PnlIdecUsgMNUser::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSGRECDATA) {
		*dpcheng = new PnlIdecUsgRec::DpchEngData();
		((PnlIdecUsgRec::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSR1NSESSIONDATA) {
		*dpcheng = new PnlIdecUsr1NSession::DpchEngData();
		((PnlIdecUsr1NSession::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRAACCESSDATA) {
		*dpcheng = new PnlIdecUsrAAccess::DpchEngData();
		((PnlIdecUsrAAccess::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRDATA) {
		*dpcheng = new CrdIdecUsr::DpchEngData();
		((CrdIdecUsr::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRDETAILDATA) {
		*dpcheng = new PnlIdecUsrDetail::DpchEngData();
		((PnlIdecUsrDetail::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRHEADBARDATA) {
		*dpcheng = new PnlIdecUsrHeadbar::DpchEngData();
		((PnlIdecUsrHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRLISTDATA) {
		*dpcheng = new PnlIdecUsrList::DpchEngData();
		((PnlIdecUsrList::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRMNUSERGROUPDATA) {
		*dpcheng = new PnlIdecUsrMNUsergroup::DpchEngData();
		((PnlIdecUsrMNUsergroup::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUSRRECDATA) {
		*dpcheng = new PnlIdecUsrRec::DpchEngData();
		((PnlIdecUsrRec::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUTLDATA) {
		*dpcheng = new CrdIdecUtl::DpchEngData();
		((CrdIdecUtl::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUTLHEADBARDATA) {
		*dpcheng = new PnlIdecUtlHeadbar::DpchEngData();
		((PnlIdecUtlHeadbar::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUTLSPITERMDATA) {
		*dpcheng = new PnlIdecUtlSpiterm::DpchEngData();
		((PnlIdecUtlSpiterm::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGIDECUTLSPITERMLIVE) {
		*dpcheng = new PnlIdecUtlSpiterm::DpchEngLive();
		((PnlIdecUtlSpiterm::DpchEngLive*) *dpcheng)->readXML(docctx, "/", true);
	} else if (ixIdecVDpch == VecIdecVDpch::DPCHENGSESSIDECDATA) {
		*dpcheng = new SessIdec::DpchEngData();
		((SessIdec::DpchEngData*) *dpcheng)->readXML(docctx, "/", true);
	};

	if (docctx) xmlXPathFreeContext(docctx);
	if (doc) xmlFreeDoc(doc);
	
	return ixIdecVDpch;
};

void ApiIdec::writeDpchApp(
			DpchAppIdec* dpchapp
			, char** buf
			, unsigned long& buflen
			, unsigned long ofs
		) {
	xmlBuffer* xbuf = NULL;
	xmlTextWriter* wr = NULL;

	startwriteBuffer(&wr, &xbuf);
		dpchapp->writeXML(wr);
	closewriteBuffer(wr);

	buflen = xbuf->use + ofs;
	*buf = new char[buflen];
	memcpy(&((*buf)[ofs]), xbuf->content, buflen-ofs);

	xmlBufferFree(xbuf);
};

