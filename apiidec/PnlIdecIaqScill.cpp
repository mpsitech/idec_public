/**
  * \file PnlIdecIaqScill.cpp
  * API code for job PnlIdecIaqScill (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecIaqScill.h"

/******************************************************************************
 class PnlIdecIaqScill::VecVDo
 ******************************************************************************/

uint PnlIdecIaqScill::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecIaqScill::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqScill::VecVMode
 ******************************************************************************/

uint PnlIdecIaqScill::VecVMode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "manual") return MANUAL;
	else if (s == "autolive") return AUTOLIVE;
	else if (s == "autorec") return AUTOREC;

	return(0);
};

string PnlIdecIaqScill::VecVMode::getSref(
			const uint ix
		) {
	if (ix == MANUAL) return("manual");
	else if (ix == AUTOLIVE) return("autolive");
	else if (ix == AUTOREC) return("autorec");

	return("");
};

/******************************************************************************
 class PnlIdecIaqScill::ContIac
 ******************************************************************************/

PnlIdecIaqScill::ContIac::ContIac(
			const uint numFPupMod
			, const double SldThr
			, const double SldFld
			, const double SldSpt
		) : Block() {
	this->numFPupMod = numFPupMod;
	this->SldThr = SldThr;
	this->SldFld = SldFld;
	this->SldSpt = SldSpt;

	mask = {NUMFPUPMOD, SLDTHR, SLDFLD, SLDSPT};
};

bool PnlIdecIaqScill::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqScill");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqScill";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupMod", numFPupMod)) add(NUMFPUPMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldThr", SldThr)) add(SLDTHR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldFld", SldFld)) add(SLDFLD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldSpt", SldSpt)) add(SLDSPT);
	};

	return basefound;
};

void PnlIdecIaqScill::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqScill";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqScill";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupMod", numFPupMod);
		writeDoubleAttr(wr, itemtag, "sref", "SldThr", SldThr);
		writeDoubleAttr(wr, itemtag, "sref", "SldFld", SldFld);
		writeDoubleAttr(wr, itemtag, "sref", "SldSpt", SldSpt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqScill::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupMod == comp->numFPupMod) insert(items, NUMFPUPMOD);
	if (compareDouble(SldThr, comp->SldThr) < 1.0e-4) insert(items, SLDTHR);
	if (compareDouble(SldFld, comp->SldFld) < 1.0e-4) insert(items, SLDFLD);
	if (compareDouble(SldSpt, comp->SldSpt) < 1.0e-4) insert(items, SLDSPT);

	return(items);
};

set<uint> PnlIdecIaqScill::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPMOD, SLDTHR, SLDFLD, SLDSPT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqScill::ContInf
 ******************************************************************************/

PnlIdecIaqScill::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

bool PnlIdecIaqScill::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecIaqScill");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecIaqScill";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
	};

	return basefound;
};

set<uint> PnlIdecIaqScill::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecIaqScill::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqScill::StatApp
 ******************************************************************************/

PnlIdecIaqScill::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecIaqScill::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecIaqScill");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecIaqScill";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecIaqScill::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecIaqScill::StatApp::diff(
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
 class PnlIdecIaqScill::StatShr
 ******************************************************************************/

PnlIdecIaqScill::StatShr::StatShr(
			const bool PupModActive
			, const bool SldThrAvail
			, const bool SldThrActive
			, const double SldThrMin
			, const double SldThrMax
			, const bool SldFldActive
			, const double SldFldMin
			, const double SldFldMax
			, const bool SldSptActive
			, const double SldSptMin
			, const double SldSptMax
		) : Block() {
	this->PupModActive = PupModActive;
	this->SldThrAvail = SldThrAvail;
	this->SldThrActive = SldThrActive;
	this->SldThrMin = SldThrMin;
	this->SldThrMax = SldThrMax;
	this->SldFldActive = SldFldActive;
	this->SldFldMin = SldFldMin;
	this->SldFldMax = SldFldMax;
	this->SldSptActive = SldSptActive;
	this->SldSptMin = SldSptMin;
	this->SldSptMax = SldSptMax;

	mask = {PUPMODACTIVE, SLDTHRAVAIL, SLDTHRACTIVE, SLDTHRMIN, SLDTHRMAX, SLDFLDACTIVE, SLDFLDMIN, SLDFLDMAX, SLDSPTACTIVE, SLDSPTMIN, SLDSPTMAX};
};

bool PnlIdecIaqScill::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecIaqScill");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecIaqScill";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupModActive", PupModActive)) add(PUPMODACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldThrAvail", SldThrAvail)) add(SLDTHRAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldThrActive", SldThrActive)) add(SLDTHRACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldThrMin", SldThrMin)) add(SLDTHRMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldThrMax", SldThrMax)) add(SLDTHRMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFldActive", SldFldActive)) add(SLDFLDACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFldMin", SldFldMin)) add(SLDFLDMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFldMax", SldFldMax)) add(SLDFLDMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldSptActive", SldSptActive)) add(SLDSPTACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldSptMin", SldSptMin)) add(SLDSPTMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldSptMax", SldSptMax)) add(SLDSPTMAX);
	};

	return basefound;
};

set<uint> PnlIdecIaqScill::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (PupModActive == comp->PupModActive) insert(items, PUPMODACTIVE);
	if (SldThrAvail == comp->SldThrAvail) insert(items, SLDTHRAVAIL);
	if (SldThrActive == comp->SldThrActive) insert(items, SLDTHRACTIVE);
	if (compareDouble(SldThrMin, comp->SldThrMin) < 1.0e-4) insert(items, SLDTHRMIN);
	if (compareDouble(SldThrMax, comp->SldThrMax) < 1.0e-4) insert(items, SLDTHRMAX);
	if (SldFldActive == comp->SldFldActive) insert(items, SLDFLDACTIVE);
	if (compareDouble(SldFldMin, comp->SldFldMin) < 1.0e-4) insert(items, SLDFLDMIN);
	if (compareDouble(SldFldMax, comp->SldFldMax) < 1.0e-4) insert(items, SLDFLDMAX);
	if (SldSptActive == comp->SldSptActive) insert(items, SLDSPTACTIVE);
	if (compareDouble(SldSptMin, comp->SldSptMin) < 1.0e-4) insert(items, SLDSPTMIN);
	if (compareDouble(SldSptMax, comp->SldSptMax) < 1.0e-4) insert(items, SLDSPTMAX);

	return(items);
};

set<uint> PnlIdecIaqScill::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {PUPMODACTIVE, SLDTHRAVAIL, SLDTHRACTIVE, SLDTHRMIN, SLDTHRMAX, SLDFLDACTIVE, SLDFLDMIN, SLDFLDMAX, SLDSPTACTIVE, SLDSPTMIN, SLDSPTMAX};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqScill::Tag
 ******************************************************************************/

PnlIdecIaqScill::Tag::Tag(
			const string& Cpt
			, const string& CptMod
			, const string& CptThr
			, const string& CptFld
			, const string& CptSpt
		) : Block() {
	this->Cpt = Cpt;
	this->CptMod = CptMod;
	this->CptThr = CptThr;
	this->CptFld = CptFld;
	this->CptSpt = CptSpt;

	mask = {CPT, CPTMOD, CPTTHR, CPTFLD, CPTSPT};
};

bool PnlIdecIaqScill::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecIaqScill");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecIaqScill";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMod", CptMod)) add(CPTMOD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptThr", CptThr)) add(CPTTHR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFld", CptFld)) add(CPTFLD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSpt", CptSpt)) add(CPTSPT);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecIaqScill::DpchAppData
 ******************************************************************************/

PnlIdecIaqScill::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQSCILLDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecIaqScill::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqScill::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqScillData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqScill::DpchAppDo
 ******************************************************************************/

PnlIdecIaqScill::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQSCILLDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecIaqScill::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqScill::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqScillDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqScill::DpchEngData
 ******************************************************************************/

PnlIdecIaqScill::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQSCILLDATA) {
	feedFPupMod.tag = "FeedFPupMod";
};

string PnlIdecIaqScill::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPMOD)) ss.push_back("feedFPupMod");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqScill::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqScillData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupMod.readXML(docctx, basexpath, true)) add(FEEDFPUPMOD);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupMod.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

