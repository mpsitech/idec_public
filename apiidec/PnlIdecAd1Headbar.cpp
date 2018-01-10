/**
  * \file PnlIdecAd1Headbar.cpp
  * API code for job PnlIdecAd1Headbar (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecAd1Headbar.h"

/******************************************************************************
 class PnlIdecAd1Headbar::StgInf
 ******************************************************************************/

PnlIdecAd1Headbar::StgInf::StgInf(
			const uint MenAppCptwidth
			, const uint MenAppWidth
		) : Block() {
	this->MenAppCptwidth = MenAppCptwidth;
	this->MenAppWidth = MenAppWidth;

	mask = {MENAPPCPTWIDTH, MENAPPWIDTH};
};

bool PnlIdecAd1Headbar::StgInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgInfIdecAd1Headbar");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemInfIdecAd1Headbar";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MenAppCptwidth", MenAppCptwidth)) add(MENAPPCPTWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MenAppWidth", MenAppWidth)) add(MENAPPWIDTH);
	};

	return basefound;
};

set<uint> PnlIdecAd1Headbar::StgInf::comm(
			const StgInf* comp
		) {
	set<uint> items;

	if (MenAppCptwidth == comp->MenAppCptwidth) insert(items, MENAPPCPTWIDTH);
	if (MenAppWidth == comp->MenAppWidth) insert(items, MENAPPWIDTH);

	return(items);
};

set<uint> PnlIdecAd1Headbar::StgInf::diff(
			const StgInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {MENAPPCPTWIDTH, MENAPPWIDTH};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Headbar::Tag
 ******************************************************************************/

PnlIdecAd1Headbar::Tag::Tag(
			const string& MenApp
		) : Block() {
	this->MenApp = MenApp;

	mask = {MENAPP};
};

bool PnlIdecAd1Headbar::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecAd1Headbar");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecAd1Headbar";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MenApp", MenApp)) add(MENAPP);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecAd1Headbar::DpchEngData
 ******************************************************************************/

PnlIdecAd1Headbar::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECAD1HEADBARDATA) {
};

string PnlIdecAd1Headbar::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(STGINF)) ss.push_back("stginf");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Headbar::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecAd1HeadbarData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (stginf.readXML(docctx, basexpath, true)) add(STGINF);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		stginf = StgInf();
		tag = Tag();
	};
};

