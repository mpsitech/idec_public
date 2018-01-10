/**
  * \file PnlIdecIaqHeadbar.cpp
  * API code for job PnlIdecIaqHeadbar (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecIaqHeadbar.h"

/******************************************************************************
 class PnlIdecIaqHeadbar::StgInf
 ******************************************************************************/

PnlIdecIaqHeadbar::StgInf::StgInf(
			const uint MenAppCptwidth
			, const uint MenAppWidth
		) : Block() {
	this->MenAppCptwidth = MenAppCptwidth;
	this->MenAppWidth = MenAppWidth;

	mask = {MENAPPCPTWIDTH, MENAPPWIDTH};
};

bool PnlIdecIaqHeadbar::StgInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgInfIdecIaqHeadbar");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemInfIdecIaqHeadbar";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MenAppCptwidth", MenAppCptwidth)) add(MENAPPCPTWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MenAppWidth", MenAppWidth)) add(MENAPPWIDTH);
	};

	return basefound;
};

set<uint> PnlIdecIaqHeadbar::StgInf::comm(
			const StgInf* comp
		) {
	set<uint> items;

	if (MenAppCptwidth == comp->MenAppCptwidth) insert(items, MENAPPCPTWIDTH);
	if (MenAppWidth == comp->MenAppWidth) insert(items, MENAPPWIDTH);

	return(items);
};

set<uint> PnlIdecIaqHeadbar::StgInf::diff(
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
 class PnlIdecIaqHeadbar::Tag
 ******************************************************************************/

PnlIdecIaqHeadbar::Tag::Tag(
			const string& MenApp
		) : Block() {
	this->MenApp = MenApp;

	mask = {MENAPP};
};

bool PnlIdecIaqHeadbar::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecIaqHeadbar");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecIaqHeadbar";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MenApp", MenApp)) add(MENAPP);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecIaqHeadbar::DpchEngData
 ******************************************************************************/

PnlIdecIaqHeadbar::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQHEADBARDATA) {
};

string PnlIdecIaqHeadbar::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(STGINF)) ss.push_back("stginf");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqHeadbar::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqHeadbarData");
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

