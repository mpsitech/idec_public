/**
  * \file DlgIdecMisNew.cpp
  * API code for job DlgIdecMisNew (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "DlgIdecMisNew.h"

/******************************************************************************
 class DlgIdecMisNew::VecVDo
 ******************************************************************************/

uint DlgIdecMisNew::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butcncclick") return BUTCNCCLICK;
	else if (s == "butcreclick") return BUTCRECLICK;

	return(0);
};

string DlgIdecMisNew::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTCNCCLICK) return("ButCncClick");
	else if (ix == BUTCRECLICK) return("ButCreClick");

	return("");
};

/******************************************************************************
 class DlgIdecMisNew::VecVSge
 ******************************************************************************/

uint DlgIdecMisNew::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "create") return CREATE;
	else if (s == "done") return DONE;

	return(0);
};

string DlgIdecMisNew::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == CREATE) return("create");
	else if (ix == DONE) return("done");

	return("");
};

/******************************************************************************
 class DlgIdecMisNew::ContIac
 ******************************************************************************/

DlgIdecMisNew::ContIac::ContIac(
			const string& DetTxfTit
			, const uint numFDetPupCry
			, const string& DetTxfReg
			, const string& DetTxfMun
		) : Block() {
	this->DetTxfTit = DetTxfTit;
	this->numFDetPupCry = numFDetPupCry;
	this->DetTxfReg = DetTxfReg;
	this->DetTxfMun = DetTxfMun;

	mask = {DETTXFTIT, NUMFDETPUPCRY, DETTXFREG, DETTXFMUN};
};

bool DlgIdecMisNew::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacDlgIdecMisNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacDlgIdecMisNew";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfTit", DetTxfTit)) add(DETTXFTIT);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFDetPupCry", numFDetPupCry)) add(NUMFDETPUPCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfReg", DetTxfReg)) add(DETTXFREG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfMun", DetTxfMun)) add(DETTXFMUN);
	};

	return basefound;
};

void DlgIdecMisNew::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacDlgIdecMisNew";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacDlgIdecMisNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "DetTxfTit", DetTxfTit);
		writeUintAttr(wr, itemtag, "sref", "numFDetPupCry", numFDetPupCry);
		writeStringAttr(wr, itemtag, "sref", "DetTxfReg", DetTxfReg);
		writeStringAttr(wr, itemtag, "sref", "DetTxfMun", DetTxfMun);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecMisNew::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (DetTxfTit.compare(comp->DetTxfTit) == 0) insert(items, DETTXFTIT);
	if (numFDetPupCry == comp->numFDetPupCry) insert(items, NUMFDETPUPCRY);
	if (DetTxfReg.compare(comp->DetTxfReg) == 0) insert(items, DETTXFREG);
	if (DetTxfMun.compare(comp->DetTxfMun) == 0) insert(items, DETTXFMUN);

	return(items);
};

set<uint> DlgIdecMisNew::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {DETTXFTIT, NUMFDETPUPCRY, DETTXFREG, DETTXFMUN};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecMisNew::ContInf
 ******************************************************************************/

DlgIdecMisNew::ContInf::ContInf(
			const uint numFSge
		) : Block() {
	this->numFSge = numFSge;

	mask = {NUMFSGE};
};

bool DlgIdecMisNew::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfDlgIdecMisNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfDlgIdecMisNew";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
	};

	return basefound;
};

set<uint> DlgIdecMisNew::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);

	return(items);
};

set<uint> DlgIdecMisNew::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecMisNew::StatApp
 ******************************************************************************/

DlgIdecMisNew::StatApp::StatApp(
			const string& shortMenu
		) : Block() {
	this->shortMenu = shortMenu;

	mask = {SHORTMENU};
};

bool DlgIdecMisNew::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppDlgIdecMisNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppDlgIdecMisNew";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "shortMenu", shortMenu)) add(SHORTMENU);
	};

	return basefound;
};

set<uint> DlgIdecMisNew::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (shortMenu.compare(comp->shortMenu) == 0) insert(items, SHORTMENU);

	return(items);
};

set<uint> DlgIdecMisNew::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SHORTMENU};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecMisNew::StatShr
 ******************************************************************************/

DlgIdecMisNew::StatShr::StatShr(
			const bool ButCncActive
			, const bool ButCreActive
		) : Block() {
	this->ButCncActive = ButCncActive;
	this->ButCreActive = ButCreActive;

	mask = {BUTCNCACTIVE, BUTCREACTIVE};
};

bool DlgIdecMisNew::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrDlgIdecMisNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrDlgIdecMisNew";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButCncActive", ButCncActive)) add(BUTCNCACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButCreActive", ButCreActive)) add(BUTCREACTIVE);
	};

	return basefound;
};

set<uint> DlgIdecMisNew::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ButCncActive == comp->ButCncActive) insert(items, BUTCNCACTIVE);
	if (ButCreActive == comp->ButCreActive) insert(items, BUTCREACTIVE);

	return(items);
};

set<uint> DlgIdecMisNew::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTCNCACTIVE, BUTCREACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecMisNew::Tag
 ******************************************************************************/

DlgIdecMisNew::Tag::Tag(
			const string& Cpt
			, const string& DetCptTit
			, const string& DetCptCry
			, const string& DetCptReg
			, const string& DetCptMun
			, const string& ButCnc
			, const string& ButCre
		) : Block() {
	this->Cpt = Cpt;
	this->DetCptTit = DetCptTit;
	this->DetCptCry = DetCptCry;
	this->DetCptReg = DetCptReg;
	this->DetCptMun = DetCptMun;
	this->ButCnc = ButCnc;
	this->ButCre = ButCre;

	mask = {CPT, DETCPTTIT, DETCPTCRY, DETCPTREG, DETCPTMUN, BUTCNC, BUTCRE};
};

bool DlgIdecMisNew::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagDlgIdecMisNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemDlgIdecMisNew";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptTit", DetCptTit)) add(DETCPTTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptCry", DetCptCry)) add(DETCPTCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptReg", DetCptReg)) add(DETCPTREG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptMun", DetCptMun)) add(DETCPTMUN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButCnc", ButCnc)) add(BUTCNC);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButCre", ButCre)) add(BUTCRE);
	};

	return basefound;
};

/******************************************************************************
 class DlgIdecMisNew::DpchAppData
 ******************************************************************************/

DlgIdecMisNew::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECMISNEWDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string DlgIdecMisNew::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecMisNew::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppDlgIdecMisNewData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecMisNew::DpchAppDo
 ******************************************************************************/

DlgIdecMisNew::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECMISNEWDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string DlgIdecMisNew::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecMisNew::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppDlgIdecMisNewDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecMisNew::DpchEngData
 ******************************************************************************/

DlgIdecMisNew::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGDLGIDECMISNEWDATA) {
	feedFDetPupCry.tag = "FeedFDetPupCry";
	feedFSge.tag = "FeedFSge";
};

string DlgIdecMisNew::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFDETPUPCRY)) ss.push_back("feedFDetPupCry");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecMisNew::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngDlgIdecMisNewData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFDetPupCry.readXML(docctx, basexpath, true)) add(FEEDFDETPUPCRY);
		if (feedFSge.readXML(docctx, basexpath, true)) add(FEEDFSGE);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFDetPupCry.clear();
		feedFSge.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

