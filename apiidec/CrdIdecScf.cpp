/**
  * \file CrdIdecScf.cpp
  * API code for job CrdIdecScf (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "CrdIdecScf.h"

/******************************************************************************
 class CrdIdecScf::VecVDo
 ******************************************************************************/

uint CrdIdecScf::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "close") return CLOSE;
	else if (s == "mitappabtclick") return MITAPPABTCLICK;

	return(0);
};

string CrdIdecScf::VecVDo::getSref(
			const uint ix
		) {
	if (ix == CLOSE) return("close");
	else if (ix == MITAPPABTCLICK) return("MitAppAbtClick");

	return("");
};

/******************************************************************************
 class CrdIdecScf::VecVSge
 ******************************************************************************/

uint CrdIdecScf::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alridecabt") return ALRIDECABT;
	else if (s == "close") return CLOSE;

	return(0);
};

string CrdIdecScf::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRIDECABT) return("alridecabt");
	else if (ix == CLOSE) return("close");

	return("");
};

/******************************************************************************
 class CrdIdecScf::ContInf
 ******************************************************************************/

CrdIdecScf::ContInf::ContInf(
			const uint numFSge
			, const string& MrlAppHlp
		) : Block() {
	this->numFSge = numFSge;
	this->MrlAppHlp = MrlAppHlp;

	mask = {NUMFSGE, MRLAPPHLP};
};

bool CrdIdecScf::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScf");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScf";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
	};

	return basefound;
};

set<uint> CrdIdecScf::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp.compare(comp->MrlAppHlp) == 0) insert(items, MRLAPPHLP);

	return(items);
};

set<uint> CrdIdecScf::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE, MRLAPPHLP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecScf::StatApp
 ******************************************************************************/

CrdIdecScf::StatApp::StatApp(
			const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneConn
			, const bool initdoneStatus
			, const bool initdoneMech
			, const bool initdoneOptics
			, const bool initdoneTrigger
			, const bool initdoneLwir
			, const bool initdoneQcd
			, const bool initdoneRecord
			, const bool initdoneHeadbar
		) : Block() {
	this->ixIdecVReqitmode = ixIdecVReqitmode;
	this->latency = latency;
	this->shortMenu = shortMenu;
	this->widthMenu = widthMenu;
	this->initdoneConn = initdoneConn;
	this->initdoneStatus = initdoneStatus;
	this->initdoneMech = initdoneMech;
	this->initdoneOptics = initdoneOptics;
	this->initdoneTrigger = initdoneTrigger;
	this->initdoneLwir = initdoneLwir;
	this->initdoneQcd = initdoneQcd;
	this->initdoneRecord = initdoneRecord;
	this->initdoneHeadbar = initdoneHeadbar;

	mask = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONECONN, INITDONESTATUS, INITDONEMECH, INITDONEOPTICS, INITDONETRIGGER, INITDONELWIR, INITDONEQCD, INITDONERECORD, INITDONEHEADBAR};
};

bool CrdIdecScf::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVReqitmode;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScf");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScf";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVReqitmode", srefIxIdecVReqitmode)) {
			ixIdecVReqitmode = VecIdecVReqitmode::getIx(srefIxIdecVReqitmode);
			add(IXIDECVREQITMODE);
		};
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "latency", latency)) add(LATENCY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "shortMenu", shortMenu)) add(SHORTMENU);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "widthMenu", widthMenu)) add(WIDTHMENU);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneConn", initdoneConn)) add(INITDONECONN);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneStatus", initdoneStatus)) add(INITDONESTATUS);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneMech", initdoneMech)) add(INITDONEMECH);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneOptics", initdoneOptics)) add(INITDONEOPTICS);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneTrigger", initdoneTrigger)) add(INITDONETRIGGER);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneLwir", initdoneLwir)) add(INITDONELWIR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneQcd", initdoneQcd)) add(INITDONEQCD);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneRecord", initdoneRecord)) add(INITDONERECORD);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneHeadbar", initdoneHeadbar)) add(INITDONEHEADBAR);
	};

	return basefound;
};

set<uint> CrdIdecScf::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVReqitmode == comp->ixIdecVReqitmode) insert(items, IXIDECVREQITMODE);
	if (latency == comp->latency) insert(items, LATENCY);
	if (shortMenu.compare(comp->shortMenu) == 0) insert(items, SHORTMENU);
	if (widthMenu == comp->widthMenu) insert(items, WIDTHMENU);
	if (initdoneConn == comp->initdoneConn) insert(items, INITDONECONN);
	if (initdoneStatus == comp->initdoneStatus) insert(items, INITDONESTATUS);
	if (initdoneMech == comp->initdoneMech) insert(items, INITDONEMECH);
	if (initdoneOptics == comp->initdoneOptics) insert(items, INITDONEOPTICS);
	if (initdoneTrigger == comp->initdoneTrigger) insert(items, INITDONETRIGGER);
	if (initdoneLwir == comp->initdoneLwir) insert(items, INITDONELWIR);
	if (initdoneQcd == comp->initdoneQcd) insert(items, INITDONEQCD);
	if (initdoneRecord == comp->initdoneRecord) insert(items, INITDONERECORD);
	if (initdoneHeadbar == comp->initdoneHeadbar) insert(items, INITDONEHEADBAR);

	return(items);
};

set<uint> CrdIdecScf::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONECONN, INITDONESTATUS, INITDONEMECH, INITDONEOPTICS, INITDONETRIGGER, INITDONELWIR, INITDONEQCD, INITDONERECORD, INITDONEHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecScf::StatShr
 ******************************************************************************/

CrdIdecScf::StatShr::StatShr(
			const string& scrJrefConn
			, const string& scrJrefStatus
			, const string& scrJrefMech
			, const string& scrJrefOptics
			, const string& scrJrefTrigger
			, const string& scrJrefLwir
			, const string& scrJrefQcd
			, const string& scrJrefRecord
			, const string& scrJrefHeadbar
		) : Block() {
	this->scrJrefConn = scrJrefConn;
	this->scrJrefStatus = scrJrefStatus;
	this->scrJrefMech = scrJrefMech;
	this->scrJrefOptics = scrJrefOptics;
	this->scrJrefTrigger = scrJrefTrigger;
	this->scrJrefLwir = scrJrefLwir;
	this->scrJrefQcd = scrJrefQcd;
	this->scrJrefRecord = scrJrefRecord;
	this->scrJrefHeadbar = scrJrefHeadbar;

	mask = {SCRJREFCONN, SCRJREFSTATUS, SCRJREFMECH, SCRJREFOPTICS, SCRJREFTRIGGER, SCRJREFLWIR, SCRJREFQCD, SCRJREFRECORD, SCRJREFHEADBAR};
};

bool CrdIdecScf::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScf");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScf";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefConn", scrJrefConn)) add(SCRJREFCONN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefStatus", scrJrefStatus)) add(SCRJREFSTATUS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefMech", scrJrefMech)) add(SCRJREFMECH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefOptics", scrJrefOptics)) add(SCRJREFOPTICS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefTrigger", scrJrefTrigger)) add(SCRJREFTRIGGER);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefLwir", scrJrefLwir)) add(SCRJREFLWIR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefQcd", scrJrefQcd)) add(SCRJREFQCD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefRecord", scrJrefRecord)) add(SCRJREFRECORD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefHeadbar", scrJrefHeadbar)) add(SCRJREFHEADBAR);
	};

	return basefound;
};

set<uint> CrdIdecScf::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (scrJrefConn.compare(comp->scrJrefConn) == 0) insert(items, SCRJREFCONN);
	if (scrJrefStatus.compare(comp->scrJrefStatus) == 0) insert(items, SCRJREFSTATUS);
	if (scrJrefMech.compare(comp->scrJrefMech) == 0) insert(items, SCRJREFMECH);
	if (scrJrefOptics.compare(comp->scrJrefOptics) == 0) insert(items, SCRJREFOPTICS);
	if (scrJrefTrigger.compare(comp->scrJrefTrigger) == 0) insert(items, SCRJREFTRIGGER);
	if (scrJrefLwir.compare(comp->scrJrefLwir) == 0) insert(items, SCRJREFLWIR);
	if (scrJrefQcd.compare(comp->scrJrefQcd) == 0) insert(items, SCRJREFQCD);
	if (scrJrefRecord.compare(comp->scrJrefRecord) == 0) insert(items, SCRJREFRECORD);
	if (scrJrefHeadbar.compare(comp->scrJrefHeadbar) == 0) insert(items, SCRJREFHEADBAR);

	return(items);
};

set<uint> CrdIdecScf::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SCRJREFCONN, SCRJREFSTATUS, SCRJREFMECH, SCRJREFOPTICS, SCRJREFTRIGGER, SCRJREFLWIR, SCRJREFQCD, SCRJREFRECORD, SCRJREFHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecScf::Tag
 ******************************************************************************/

CrdIdecScf::Tag::Tag(
			const string& MitAppAbt
			, const string& MrlAppHlp
		) : Block() {
	this->MitAppAbt = MitAppAbt;
	this->MrlAppHlp = MrlAppHlp;

	mask = {MITAPPABT, MRLAPPHLP};
};

bool CrdIdecScf::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScf");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScf";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitAppAbt", MitAppAbt)) add(MITAPPABT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
	};

	return basefound;
};

/******************************************************************************
 class CrdIdecScf::DpchAppDo
 ******************************************************************************/

CrdIdecScf::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string CrdIdecScf::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecScf::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecScf::DpchEngData
 ******************************************************************************/

CrdIdecScf::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFDATA) {
	feedFSge.tag = "FeedFSge";
};

string CrdIdecScf::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecScf::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFSge.readXML(docctx, basexpath, true)) add(FEEDFSGE);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		continf = ContInf();
		feedFSge.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

