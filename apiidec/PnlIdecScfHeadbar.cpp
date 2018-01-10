/**
  * \file PnlIdecScfHeadbar.cpp
  * API code for job PnlIdecScfHeadbar (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfHeadbar.h"

/******************************************************************************
 class PnlIdecScfHeadbar::StgInf
 ******************************************************************************/

PnlIdecScfHeadbar::StgInf::StgInf(
			const uint MenAppCptwidth
			, const uint MenAppWidth
		) : Block() {
	this->MenAppCptwidth = MenAppCptwidth;
	this->MenAppWidth = MenAppWidth;

	mask = {MENAPPCPTWIDTH, MENAPPWIDTH};
};

bool PnlIdecScfHeadbar::StgInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgInfIdecScfHeadbar");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemInfIdecScfHeadbar";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MenAppCptwidth", MenAppCptwidth)) add(MENAPPCPTWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MenAppWidth", MenAppWidth)) add(MENAPPWIDTH);
	};

	return basefound;
};

set<uint> PnlIdecScfHeadbar::StgInf::comm(
			const StgInf* comp
		) {
	set<uint> items;

	if (MenAppCptwidth == comp->MenAppCptwidth) insert(items, MENAPPCPTWIDTH);
	if (MenAppWidth == comp->MenAppWidth) insert(items, MENAPPWIDTH);

	return(items);
};

set<uint> PnlIdecScfHeadbar::StgInf::diff(
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
 class PnlIdecScfHeadbar::Tag
 ******************************************************************************/

PnlIdecScfHeadbar::Tag::Tag(
			const string& MenApp
		) : Block() {
	this->MenApp = MenApp;

	mask = {MENAPP};
};

bool PnlIdecScfHeadbar::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfHeadbar");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfHeadbar";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MenApp", MenApp)) add(MENAPP);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfHeadbar::DpchEngData
 ******************************************************************************/

PnlIdecScfHeadbar::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFHEADBARDATA) {
};

string PnlIdecScfHeadbar::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(STGINF)) ss.push_back("stginf");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfHeadbar::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfHeadbarData");
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

