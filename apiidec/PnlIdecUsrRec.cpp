/**
  * \file PnlIdecUsrRec.cpp
  * API code for job PnlIdecUsrRec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecUsrRec.h"

/******************************************************************************
 class PnlIdecUsrRec::VecVDo
 ******************************************************************************/

uint PnlIdecUsrRec::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butregularizeclick") return BUTREGULARIZECLICK;

	return(0);
};

string PnlIdecUsrRec::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");

	return("");
};

/******************************************************************************
 class PnlIdecUsrRec::ContInf
 ******************************************************************************/

PnlIdecUsrRec::ContInf::ContInf(
			const string& TxtRef
		) : Block() {
	this->TxtRef = TxtRef;

	mask = {TXTREF};
};

bool PnlIdecUsrRec::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecUsrRec");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecUsrRec";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtRef", TxtRef)) add(TXTREF);
	};

	return basefound;
};

set<uint> PnlIdecUsrRec::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtRef.compare(comp->TxtRef) == 0) insert(items, TXTREF);

	return(items);
};

set<uint> PnlIdecUsrRec::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTREF};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUsrRec::StatApp
 ******************************************************************************/

PnlIdecUsrRec::StatApp::StatApp(
			const bool initdoneDetail
			, const bool initdoneAAccess
			, const bool initdone1NSession
			, const bool initdoneMNUsergroup
		) : Block() {
	this->initdoneDetail = initdoneDetail;
	this->initdoneAAccess = initdoneAAccess;
	this->initdone1NSession = initdone1NSession;
	this->initdoneMNUsergroup = initdoneMNUsergroup;

	mask = {INITDONEDETAIL, INITDONEAACCESS, INITDONE1NSESSION, INITDONEMNUSERGROUP};
};

bool PnlIdecUsrRec::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecUsrRec");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecUsrRec";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneDetail", initdoneDetail)) add(INITDONEDETAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneAAccess", initdoneAAccess)) add(INITDONEAACCESS);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdone1NSession", initdone1NSession)) add(INITDONE1NSESSION);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneMNUsergroup", initdoneMNUsergroup)) add(INITDONEMNUSERGROUP);
	};

	return basefound;
};

set<uint> PnlIdecUsrRec::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (initdoneDetail == comp->initdoneDetail) insert(items, INITDONEDETAIL);
	if (initdoneAAccess == comp->initdoneAAccess) insert(items, INITDONEAACCESS);
	if (initdone1NSession == comp->initdone1NSession) insert(items, INITDONE1NSESSION);
	if (initdoneMNUsergroup == comp->initdoneMNUsergroup) insert(items, INITDONEMNUSERGROUP);

	return(items);
};

set<uint> PnlIdecUsrRec::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {INITDONEDETAIL, INITDONEAACCESS, INITDONE1NSESSION, INITDONEMNUSERGROUP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUsrRec::StatShr
 ******************************************************************************/

PnlIdecUsrRec::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const string& scrJrefDetail
			, const string& scrJrefAAccess
			, const string& scrJref1NSession
			, const string& scrJrefMNUsergroup
			, const bool ButRegularizeActive
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->scrJrefDetail = scrJrefDetail;
	this->scrJrefAAccess = scrJrefAAccess;
	this->scrJref1NSession = scrJref1NSession;
	this->scrJrefMNUsergroup = scrJrefMNUsergroup;
	this->ButRegularizeActive = ButRegularizeActive;

	mask = {IXIDECVEXPSTATE, SCRJREFDETAIL, SCRJREFAACCESS, SCRJREF1NSESSION, SCRJREFMNUSERGROUP, BUTREGULARIZEACTIVE};
};

bool PnlIdecUsrRec::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecUsrRec");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecUsrRec";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDetail", scrJrefDetail)) add(SCRJREFDETAIL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefAAccess", scrJrefAAccess)) add(SCRJREFAACCESS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJref1NSession", scrJref1NSession)) add(SCRJREF1NSESSION);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefMNUsergroup", scrJrefMNUsergroup)) add(SCRJREFMNUSERGROUP);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButRegularizeActive", ButRegularizeActive)) add(BUTREGULARIZEACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecUsrRec::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (scrJrefDetail.compare(comp->scrJrefDetail) == 0) insert(items, SCRJREFDETAIL);
	if (scrJrefAAccess.compare(comp->scrJrefAAccess) == 0) insert(items, SCRJREFAACCESS);
	if (scrJref1NSession.compare(comp->scrJref1NSession) == 0) insert(items, SCRJREF1NSESSION);
	if (scrJrefMNUsergroup.compare(comp->scrJrefMNUsergroup) == 0) insert(items, SCRJREFMNUSERGROUP);
	if (ButRegularizeActive == comp->ButRegularizeActive) insert(items, BUTREGULARIZEACTIVE);

	return(items);
};

set<uint> PnlIdecUsrRec::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, SCRJREFDETAIL, SCRJREFAACCESS, SCRJREF1NSESSION, SCRJREFMNUSERGROUP, BUTREGULARIZEACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUsrRec::Tag
 ******************************************************************************/

PnlIdecUsrRec::Tag::Tag(
			const string& Cpt
		) : Block() {
	this->Cpt = Cpt;

	mask = {CPT};
};

bool PnlIdecUsrRec::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecUsrRec");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecUsrRec";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecUsrRec::DpchAppDo
 ******************************************************************************/

PnlIdecUsrRec::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUSRRECDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecUsrRec::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUsrRec::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecUsrRecDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUsrRec::DpchEngData
 ******************************************************************************/

PnlIdecUsrRec::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUSRRECDATA) {
};

string PnlIdecUsrRec::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUsrRec::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecUsrRecData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		continf = ContInf();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

