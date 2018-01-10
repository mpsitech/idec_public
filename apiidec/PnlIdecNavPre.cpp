/**
  * \file PnlIdecNavPre.cpp
  * API code for job PnlIdecNavPre (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecNavPre.h"

/******************************************************************************
 class PnlIdecNavPre::VecVDo
 ******************************************************************************/

uint PnlIdecNavPre::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmisremoveclick") return BUTMISREMOVECLICK;
	else if (s == "buttouremoveclick") return BUTTOUREMOVECLICK;

	return(0);
};

string PnlIdecNavPre::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMISREMOVECLICK) return("ButMisRemoveClick");
	else if (ix == BUTTOUREMOVECLICK) return("ButTouRemoveClick");

	return("");
};

/******************************************************************************
 class PnlIdecNavPre::ContInf
 ******************************************************************************/

PnlIdecNavPre::ContInf::ContInf(
			const string& TxtMis
			, const string& TxtTou
		) : Block() {
	this->TxtMis = TxtMis;
	this->TxtTou = TxtTou;

	mask = {TXTMIS, TXTTOU};
};

bool PnlIdecNavPre::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecNavPre");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecNavPre";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtMis", TxtMis)) add(TXTMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtTou", TxtTou)) add(TXTTOU);
	};

	return basefound;
};

set<uint> PnlIdecNavPre::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtMis.compare(comp->TxtMis) == 0) insert(items, TXTMIS);
	if (TxtTou.compare(comp->TxtTou) == 0) insert(items, TXTTOU);

	return(items);
};

set<uint> PnlIdecNavPre::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTMIS, TXTTOU};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavPre::StatShr
 ******************************************************************************/

PnlIdecNavPre::StatShr::StatShr(
			const bool TxtMisAvail
			, const bool TxtTouAvail
		) : Block() {
	this->TxtMisAvail = TxtMisAvail;
	this->TxtTouAvail = TxtTouAvail;

	mask = {TXTMISAVAIL, TXTTOUAVAIL};
};

bool PnlIdecNavPre::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecNavPre");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecNavPre";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtMisAvail", TxtMisAvail)) add(TXTMISAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtTouAvail", TxtTouAvail)) add(TXTTOUAVAIL);
	};

	return basefound;
};

set<uint> PnlIdecNavPre::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxtMisAvail == comp->TxtMisAvail) insert(items, TXTMISAVAIL);
	if (TxtTouAvail == comp->TxtTouAvail) insert(items, TXTTOUAVAIL);

	return(items);
};

set<uint> PnlIdecNavPre::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTMISAVAIL, TXTTOUAVAIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavPre::Tag
 ******************************************************************************/

PnlIdecNavPre::Tag::Tag(
			const string& CptMis
			, const string& CptTou
		) : Block() {
	this->CptMis = CptMis;
	this->CptTou = CptTou;

	mask = {CPTMIS, CPTTOU};
};

bool PnlIdecNavPre::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecNavPre");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecNavPre";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMis", CptMis)) add(CPTMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTou", CptTou)) add(CPTTOU);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecNavPre::DpchAppDo
 ******************************************************************************/

PnlIdecNavPre::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVPREDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecNavPre::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavPre::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecNavPreDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavPre::DpchEngData
 ******************************************************************************/

PnlIdecNavPre::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVPREDATA) {
};

string PnlIdecNavPre::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavPre::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecNavPreData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		continf = ContInf();
		statshr = StatShr();
		tag = Tag();
	};
};

