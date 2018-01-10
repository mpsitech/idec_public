/**
  * \file CrdIdecIaq.cpp
  * API code for job CrdIdecIaq (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "CrdIdecIaq.h"

/******************************************************************************
 class CrdIdecIaq::VecVDo
 ******************************************************************************/

uint CrdIdecIaq::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "close") return CLOSE;
	else if (s == "mitappabtclick") return MITAPPABTCLICK;

	return(0);
};

string CrdIdecIaq::VecVDo::getSref(
			const uint ix
		) {
	if (ix == CLOSE) return("close");
	else if (ix == MITAPPABTCLICK) return("MitAppAbtClick");

	return("");
};

/******************************************************************************
 class CrdIdecIaq::VecVSge
 ******************************************************************************/

uint CrdIdecIaq::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alridecabt") return ALRIDECABT;
	else if (s == "close") return CLOSE;

	return(0);
};

string CrdIdecIaq::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRIDECABT) return("alridecabt");
	else if (ix == CLOSE) return("close");

	return("");
};

/******************************************************************************
 class CrdIdecIaq::ContInf
 ******************************************************************************/

CrdIdecIaq::ContInf::ContInf(
			const uint numFSge
			, const string& MrlAppHlp
		) : Block() {
	this->numFSge = numFSge;
	this->MrlAppHlp = MrlAppHlp;

	mask = {NUMFSGE, MRLAPPHLP};
};

bool CrdIdecIaq::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecIaq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecIaq";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
	};

	return basefound;
};

set<uint> CrdIdecIaq::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp.compare(comp->MrlAppHlp) == 0) insert(items, MRLAPPHLP);

	return(items);
};

set<uint> CrdIdecIaq::ContInf::diff(
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
 class CrdIdecIaq::StatApp
 ******************************************************************************/

CrdIdecIaq::StatApp::StatApp(
			const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneLive
			, const bool initdoneMech
			, const bool initdoneScill
			, const bool initdoneQcdsp
			, const bool initdoneHeadbar
		) : Block() {
	this->ixIdecVReqitmode = ixIdecVReqitmode;
	this->latency = latency;
	this->shortMenu = shortMenu;
	this->widthMenu = widthMenu;
	this->initdoneLive = initdoneLive;
	this->initdoneMech = initdoneMech;
	this->initdoneScill = initdoneScill;
	this->initdoneQcdsp = initdoneQcdsp;
	this->initdoneHeadbar = initdoneHeadbar;

	mask = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONELIVE, INITDONEMECH, INITDONESCILL, INITDONEQCDSP, INITDONEHEADBAR};
};

bool CrdIdecIaq::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVReqitmode;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecIaq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecIaq";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVReqitmode", srefIxIdecVReqitmode)) {
			ixIdecVReqitmode = VecIdecVReqitmode::getIx(srefIxIdecVReqitmode);
			add(IXIDECVREQITMODE);
		};
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "latency", latency)) add(LATENCY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "shortMenu", shortMenu)) add(SHORTMENU);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "widthMenu", widthMenu)) add(WIDTHMENU);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneLive", initdoneLive)) add(INITDONELIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneMech", initdoneMech)) add(INITDONEMECH);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneScill", initdoneScill)) add(INITDONESCILL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneQcdsp", initdoneQcdsp)) add(INITDONEQCDSP);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneHeadbar", initdoneHeadbar)) add(INITDONEHEADBAR);
	};

	return basefound;
};

set<uint> CrdIdecIaq::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVReqitmode == comp->ixIdecVReqitmode) insert(items, IXIDECVREQITMODE);
	if (latency == comp->latency) insert(items, LATENCY);
	if (shortMenu.compare(comp->shortMenu) == 0) insert(items, SHORTMENU);
	if (widthMenu == comp->widthMenu) insert(items, WIDTHMENU);
	if (initdoneLive == comp->initdoneLive) insert(items, INITDONELIVE);
	if (initdoneMech == comp->initdoneMech) insert(items, INITDONEMECH);
	if (initdoneScill == comp->initdoneScill) insert(items, INITDONESCILL);
	if (initdoneQcdsp == comp->initdoneQcdsp) insert(items, INITDONEQCDSP);
	if (initdoneHeadbar == comp->initdoneHeadbar) insert(items, INITDONEHEADBAR);

	return(items);
};

set<uint> CrdIdecIaq::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONELIVE, INITDONEMECH, INITDONESCILL, INITDONEQCDSP, INITDONEHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecIaq::StatShr
 ******************************************************************************/

CrdIdecIaq::StatShr::StatShr(
			const string& scrJrefLive
			, const string& scrJrefMech
			, const string& scrJrefScill
			, const string& scrJrefQcdsp
			, const string& scrJrefHeadbar
		) : Block() {
	this->scrJrefLive = scrJrefLive;
	this->scrJrefMech = scrJrefMech;
	this->scrJrefScill = scrJrefScill;
	this->scrJrefQcdsp = scrJrefQcdsp;
	this->scrJrefHeadbar = scrJrefHeadbar;

	mask = {SCRJREFLIVE, SCRJREFMECH, SCRJREFSCILL, SCRJREFQCDSP, SCRJREFHEADBAR};
};

bool CrdIdecIaq::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecIaq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecIaq";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefLive", scrJrefLive)) add(SCRJREFLIVE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefMech", scrJrefMech)) add(SCRJREFMECH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefScill", scrJrefScill)) add(SCRJREFSCILL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefQcdsp", scrJrefQcdsp)) add(SCRJREFQCDSP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefHeadbar", scrJrefHeadbar)) add(SCRJREFHEADBAR);
	};

	return basefound;
};

set<uint> CrdIdecIaq::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (scrJrefLive.compare(comp->scrJrefLive) == 0) insert(items, SCRJREFLIVE);
	if (scrJrefMech.compare(comp->scrJrefMech) == 0) insert(items, SCRJREFMECH);
	if (scrJrefScill.compare(comp->scrJrefScill) == 0) insert(items, SCRJREFSCILL);
	if (scrJrefQcdsp.compare(comp->scrJrefQcdsp) == 0) insert(items, SCRJREFQCDSP);
	if (scrJrefHeadbar.compare(comp->scrJrefHeadbar) == 0) insert(items, SCRJREFHEADBAR);

	return(items);
};

set<uint> CrdIdecIaq::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SCRJREFLIVE, SCRJREFMECH, SCRJREFSCILL, SCRJREFQCDSP, SCRJREFHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecIaq::Tag
 ******************************************************************************/

CrdIdecIaq::Tag::Tag(
			const string& MitAppAbt
			, const string& MrlAppHlp
		) : Block() {
	this->MitAppAbt = MitAppAbt;
	this->MrlAppHlp = MrlAppHlp;

	mask = {MITAPPABT, MRLAPPHLP};
};

bool CrdIdecIaq::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecIaq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecIaq";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitAppAbt", MitAppAbt)) add(MITAPPABT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
	};

	return basefound;
};

/******************************************************************************
 class CrdIdecIaq::DpchAppDo
 ******************************************************************************/

CrdIdecIaq::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string CrdIdecIaq::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecIaq::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecIaq::DpchEngData
 ******************************************************************************/

CrdIdecIaq::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQDATA) {
	feedFSge.tag = "FeedFSge";
};

string CrdIdecIaq::DpchEngData::getSrefsMask() {
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

void CrdIdecIaq::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqData");
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

