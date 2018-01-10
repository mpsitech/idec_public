/**
  * \file PnlIdecAd1Control.cpp
  * API code for job PnlIdecAd1Control (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecAd1Control.h"

/******************************************************************************
 class PnlIdecAd1Control::VecVDo
 ******************************************************************************/

uint PnlIdecAd1Control::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "butrunclick") return BUTRUNCLICK;
	else if (s == "butstoclick") return BUTSTOCLICK;

	return(0);
};

string PnlIdecAd1Control::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTRUNCLICK) return("ButRunClick");
	else if (ix == BUTSTOCLICK) return("ButStoClick");

	return("");
};

/******************************************************************************
 class PnlIdecAd1Control::VecVSge
 ******************************************************************************/

uint PnlIdecAd1Control::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alrgum") return ALRGUM;

	return(0);
};

string PnlIdecAd1Control::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRGUM) return("alrgum");

	return("");
};

/******************************************************************************
 class PnlIdecAd1Control::ContIac
 ******************************************************************************/

PnlIdecAd1Control::ContIac::ContIac(
			const double SldTll
			, const double SldTul
			, const int UpdMct
		) : Block() {
	this->SldTll = SldTll;
	this->SldTul = SldTul;
	this->UpdMct = UpdMct;

	mask = {SLDTLL, SLDTUL, UPDMCT};
};

bool PnlIdecAd1Control::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecAd1Control");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecAd1Control";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTll", SldTll)) add(SLDTLL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTul", SldTul)) add(SLDTUL);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "UpdMct", UpdMct)) add(UPDMCT);
	};

	return basefound;
};

void PnlIdecAd1Control::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecAd1Control";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecAd1Control";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "SldTll", SldTll);
		writeDoubleAttr(wr, itemtag, "sref", "SldTul", SldTul);
		writeIntAttr(wr, itemtag, "sref", "UpdMct", UpdMct);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecAd1Control::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (compareDouble(SldTll, comp->SldTll) < 1.0e-4) insert(items, SLDTLL);
	if (compareDouble(SldTul, comp->SldTul) < 1.0e-4) insert(items, SLDTUL);
	if (UpdMct == comp->UpdMct) insert(items, UPDMCT);

	return(items);
};

set<uint> PnlIdecAd1Control::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDTLL, SLDTUL, UPDMCT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::ContInf
 ******************************************************************************/

PnlIdecAd1Control::ContInf::ContInf(
			const uint numFSge
			, const bool ButMasterOn
			, const string& TxtPrg
		) : Block() {
	this->numFSge = numFSge;
	this->ButMasterOn = ButMasterOn;
	this->TxtPrg = TxtPrg;

	mask = {NUMFSGE, BUTMASTERON, TXTPRG};
};

bool PnlIdecAd1Control::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecAd1Control");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecAd1Control";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtPrg", TxtPrg)) add(TXTPRG);
	};

	return basefound;
};

set<uint> PnlIdecAd1Control::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtPrg.compare(comp->TxtPrg) == 0) insert(items, TXTPRG);

	return(items);
};

set<uint> PnlIdecAd1Control::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE, BUTMASTERON, TXTPRG};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::StatApp
 ******************************************************************************/

PnlIdecAd1Control::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecAd1Control::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecAd1Control");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecAd1Control";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecAd1Control::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecAd1Control::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::StatShr
 ******************************************************************************/

PnlIdecAd1Control::StatShr::StatShr(
			const double SldTllMin
			, const double SldTllMax
			, const double SldTulMin
			, const double SldTulMax
			, const int UpdMctMin
			, const int UpdMctMax
			, const bool ButRunActive
			, const bool ButStoActive
		) : Block() {
	this->SldTllMin = SldTllMin;
	this->SldTllMax = SldTllMax;
	this->SldTulMin = SldTulMin;
	this->SldTulMax = SldTulMax;
	this->UpdMctMin = UpdMctMin;
	this->UpdMctMax = UpdMctMax;
	this->ButRunActive = ButRunActive;
	this->ButStoActive = ButStoActive;

	mask = {SLDTLLMIN, SLDTLLMAX, SLDTULMIN, SLDTULMAX, UPDMCTMIN, UPDMCTMAX, BUTRUNACTIVE, BUTSTOACTIVE};
};

bool PnlIdecAd1Control::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecAd1Control");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecAd1Control";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTllMin", SldTllMin)) add(SLDTLLMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTllMax", SldTllMax)) add(SLDTLLMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTulMin", SldTulMin)) add(SLDTULMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTulMax", SldTulMax)) add(SLDTULMAX);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdMctMin", UpdMctMin)) add(UPDMCTMIN);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdMctMax", UpdMctMax)) add(UPDMCTMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButRunActive", ButRunActive)) add(BUTRUNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButStoActive", ButStoActive)) add(BUTSTOACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecAd1Control::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (compareDouble(SldTllMin, comp->SldTllMin) < 1.0e-4) insert(items, SLDTLLMIN);
	if (compareDouble(SldTllMax, comp->SldTllMax) < 1.0e-4) insert(items, SLDTLLMAX);
	if (compareDouble(SldTulMin, comp->SldTulMin) < 1.0e-4) insert(items, SLDTULMIN);
	if (compareDouble(SldTulMax, comp->SldTulMax) < 1.0e-4) insert(items, SLDTULMAX);
	if (UpdMctMin == comp->UpdMctMin) insert(items, UPDMCTMIN);
	if (UpdMctMax == comp->UpdMctMax) insert(items, UPDMCTMAX);
	if (ButRunActive == comp->ButRunActive) insert(items, BUTRUNACTIVE);
	if (ButStoActive == comp->ButStoActive) insert(items, BUTSTOACTIVE);

	return(items);
};

set<uint> PnlIdecAd1Control::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDTLLMIN, SLDTLLMAX, SLDTULMIN, SLDTULMAX, UPDMCTMIN, UPDMCTMAX, BUTRUNACTIVE, BUTSTOACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::Tag
 ******************************************************************************/

PnlIdecAd1Control::Tag::Tag(
			const string& Cpt
			, const string& HdgRoi
			, const string& CptTll
			, const string& CptTul
			, const string& CptMct
			, const string& CptPrg
			, const string& ButRun
			, const string& ButSto
		) : Block() {
	this->Cpt = Cpt;
	this->HdgRoi = HdgRoi;
	this->CptTll = CptTll;
	this->CptTul = CptTul;
	this->CptMct = CptMct;
	this->CptPrg = CptPrg;
	this->ButRun = ButRun;
	this->ButSto = ButSto;

	mask = {CPT, HDGROI, CPTTLL, CPTTUL, CPTMCT, CPTPRG, BUTRUN, BUTSTO};
};

bool PnlIdecAd1Control::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecAd1Control");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecAd1Control";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgRoi", HdgRoi)) add(HDGROI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTll", CptTll)) add(CPTTLL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTul", CptTul)) add(CPTTUL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMct", CptMct)) add(CPTMCT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPrg", CptPrg)) add(CPTPRG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButRun", ButRun)) add(BUTRUN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButSto", ButSto)) add(BUTSTO);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecAd1Control::DpchAppData
 ******************************************************************************/

PnlIdecAd1Control::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECAD1CONTROLDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecAd1Control::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Control::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecAd1ControlData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecAd1Control::DpchAppDo
 ******************************************************************************/

PnlIdecAd1Control::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECAD1CONTROLDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecAd1Control::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Control::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecAd1ControlDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecAd1Control::DpchEngData
 ******************************************************************************/

PnlIdecAd1Control::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECAD1CONTROLDATA) {
	feedFSge.tag = "FeedFSge";
};

string PnlIdecAd1Control::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Control::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecAd1ControlData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFSge.readXML(docctx, basexpath, true)) add(FEEDFSGE);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFSge.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

