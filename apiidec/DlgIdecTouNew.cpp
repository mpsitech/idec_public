/**
  * \file DlgIdecTouNew.cpp
  * API code for job DlgIdecTouNew (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "DlgIdecTouNew.h"

/******************************************************************************
 class DlgIdecTouNew::VecVDo
 ******************************************************************************/

uint DlgIdecTouNew::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butcncclick") return BUTCNCCLICK;
	else if (s == "butcreclick") return BUTCRECLICK;

	return(0);
};

string DlgIdecTouNew::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTCNCCLICK) return("ButCncClick");
	else if (ix == BUTCRECLICK) return("ButCreClick");

	return("");
};

/******************************************************************************
 class DlgIdecTouNew::VecVSge
 ******************************************************************************/

uint DlgIdecTouNew::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "create") return CREATE;
	else if (s == "done") return DONE;

	return(0);
};

string DlgIdecTouNew::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == CREATE) return("create");
	else if (ix == DONE) return("done");

	return("");
};

/******************************************************************************
 class DlgIdecTouNew::ContIac
 ******************************************************************************/

DlgIdecTouNew::ContIac::ContIac(
			const uint numFDetPupMis
			, const string& DetTxfTit
			, const string& DetTxfAre
			, const string& DetTxfThe
			, const string& DetTxfPhi
		) : Block() {
	this->numFDetPupMis = numFDetPupMis;
	this->DetTxfTit = DetTxfTit;
	this->DetTxfAre = DetTxfAre;
	this->DetTxfThe = DetTxfThe;
	this->DetTxfPhi = DetTxfPhi;

	mask = {NUMFDETPUPMIS, DETTXFTIT, DETTXFARE, DETTXFTHE, DETTXFPHI};
};

bool DlgIdecTouNew::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacDlgIdecTouNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacDlgIdecTouNew";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFDetPupMis", numFDetPupMis)) add(NUMFDETPUPMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfTit", DetTxfTit)) add(DETTXFTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfAre", DetTxfAre)) add(DETTXFARE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfThe", DetTxfThe)) add(DETTXFTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfPhi", DetTxfPhi)) add(DETTXFPHI);
	};

	return basefound;
};

void DlgIdecTouNew::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacDlgIdecTouNew";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacDlgIdecTouNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFDetPupMis", numFDetPupMis);
		writeStringAttr(wr, itemtag, "sref", "DetTxfTit", DetTxfTit);
		writeStringAttr(wr, itemtag, "sref", "DetTxfAre", DetTxfAre);
		writeStringAttr(wr, itemtag, "sref", "DetTxfThe", DetTxfThe);
		writeStringAttr(wr, itemtag, "sref", "DetTxfPhi", DetTxfPhi);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecTouNew::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFDetPupMis == comp->numFDetPupMis) insert(items, NUMFDETPUPMIS);
	if (DetTxfTit.compare(comp->DetTxfTit) == 0) insert(items, DETTXFTIT);
	if (DetTxfAre.compare(comp->DetTxfAre) == 0) insert(items, DETTXFARE);
	if (DetTxfThe.compare(comp->DetTxfThe) == 0) insert(items, DETTXFTHE);
	if (DetTxfPhi.compare(comp->DetTxfPhi) == 0) insert(items, DETTXFPHI);

	return(items);
};

set<uint> DlgIdecTouNew::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFDETPUPMIS, DETTXFTIT, DETTXFARE, DETTXFTHE, DETTXFPHI};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecTouNew::ContInf
 ******************************************************************************/

DlgIdecTouNew::ContInf::ContInf(
			const uint numFSge
		) : Block() {
	this->numFSge = numFSge;

	mask = {NUMFSGE};
};

bool DlgIdecTouNew::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfDlgIdecTouNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfDlgIdecTouNew";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
	};

	return basefound;
};

set<uint> DlgIdecTouNew::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);

	return(items);
};

set<uint> DlgIdecTouNew::ContInf::diff(
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
 class DlgIdecTouNew::StatApp
 ******************************************************************************/

DlgIdecTouNew::StatApp::StatApp(
			const string& shortMenu
		) : Block() {
	this->shortMenu = shortMenu;

	mask = {SHORTMENU};
};

bool DlgIdecTouNew::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppDlgIdecTouNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppDlgIdecTouNew";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "shortMenu", shortMenu)) add(SHORTMENU);
	};

	return basefound;
};

set<uint> DlgIdecTouNew::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (shortMenu.compare(comp->shortMenu) == 0) insert(items, SHORTMENU);

	return(items);
};

set<uint> DlgIdecTouNew::StatApp::diff(
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
 class DlgIdecTouNew::StatShr
 ******************************************************************************/

DlgIdecTouNew::StatShr::StatShr(
			const bool DetPupMisActive
			, const bool ButCncActive
			, const bool ButCreActive
		) : Block() {
	this->DetPupMisActive = DetPupMisActive;
	this->ButCncActive = ButCncActive;
	this->ButCreActive = ButCreActive;

	mask = {DETPUPMISACTIVE, BUTCNCACTIVE, BUTCREACTIVE};
};

bool DlgIdecTouNew::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrDlgIdecTouNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrDlgIdecTouNew";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "DetPupMisActive", DetPupMisActive)) add(DETPUPMISACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButCncActive", ButCncActive)) add(BUTCNCACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButCreActive", ButCreActive)) add(BUTCREACTIVE);
	};

	return basefound;
};

set<uint> DlgIdecTouNew::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (DetPupMisActive == comp->DetPupMisActive) insert(items, DETPUPMISACTIVE);
	if (ButCncActive == comp->ButCncActive) insert(items, BUTCNCACTIVE);
	if (ButCreActive == comp->ButCreActive) insert(items, BUTCREACTIVE);

	return(items);
};

set<uint> DlgIdecTouNew::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {DETPUPMISACTIVE, BUTCNCACTIVE, BUTCREACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecTouNew::Tag
 ******************************************************************************/

DlgIdecTouNew::Tag::Tag(
			const string& Cpt
			, const string& DetCptMis
			, const string& DetCptTit
			, const string& DetCptAre
			, const string& DetCptThe
			, const string& DetCptPhi
			, const string& ButCnc
			, const string& ButCre
		) : Block() {
	this->Cpt = Cpt;
	this->DetCptMis = DetCptMis;
	this->DetCptTit = DetCptTit;
	this->DetCptAre = DetCptAre;
	this->DetCptThe = DetCptThe;
	this->DetCptPhi = DetCptPhi;
	this->ButCnc = ButCnc;
	this->ButCre = ButCre;

	mask = {CPT, DETCPTMIS, DETCPTTIT, DETCPTARE, DETCPTTHE, DETCPTPHI, BUTCNC, BUTCRE};
};

bool DlgIdecTouNew::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagDlgIdecTouNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemDlgIdecTouNew";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptMis", DetCptMis)) add(DETCPTMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptTit", DetCptTit)) add(DETCPTTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptAre", DetCptAre)) add(DETCPTARE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptThe", DetCptThe)) add(DETCPTTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "DetCptPhi", DetCptPhi)) add(DETCPTPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButCnc", ButCnc)) add(BUTCNC);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButCre", ButCre)) add(BUTCRE);
	};

	return basefound;
};

/******************************************************************************
 class DlgIdecTouNew::DpchAppData
 ******************************************************************************/

DlgIdecTouNew::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string DlgIdecTouNew::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecTouNew::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppDlgIdecTouNewData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecTouNew::DpchAppDo
 ******************************************************************************/

DlgIdecTouNew::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string DlgIdecTouNew::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecTouNew::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppDlgIdecTouNewDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecTouNew::DpchEngData
 ******************************************************************************/

DlgIdecTouNew::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGDLGIDECTOUNEWDATA) {
	feedFDetPupMis.tag = "FeedFDetPupMis";
	feedFSge.tag = "FeedFSge";
};

string DlgIdecTouNew::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFDETPUPMIS)) ss.push_back("feedFDetPupMis");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecTouNew::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngDlgIdecTouNewData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFDetPupMis.readXML(docctx, basexpath, true)) add(FEEDFDETPUPMIS);
		if (feedFSge.readXML(docctx, basexpath, true)) add(FEEDFSGE);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFDetPupMis.clear();
		feedFSge.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

