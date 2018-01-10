/**
  * \file PnlIdecIaqMech.cpp
  * API code for job PnlIdecIaqMech (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecIaqMech.h"

/******************************************************************************
 class PnlIdecIaqMech::VecVDo
 ******************************************************************************/

uint PnlIdecIaqMech::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "buttheccwclick") return BUTTHECCWCLICK;
	else if (s == "buttheccwstmdn") return BUTTHECCWSTMDN;
	else if (s == "buttheccwstmup") return BUTTHECCWSTMUP;
	else if (s == "butthecwstmdn") return BUTTHECWSTMDN;
	else if (s == "butthecwstmup") return BUTTHECWSTMUP;
	else if (s == "butthecwclick") return BUTTHECWCLICK;
	else if (s == "butphiccwclick") return BUTPHICCWCLICK;
	else if (s == "butphiccwstmdn") return BUTPHICCWSTMDN;
	else if (s == "butphiccwstmup") return BUTPHICCWSTMUP;
	else if (s == "butphicwstmdn") return BUTPHICWSTMDN;
	else if (s == "butphicwstmup") return BUTPHICWSTMUP;
	else if (s == "butphicwclick") return BUTPHICWCLICK;

	return(0);
};

string PnlIdecIaqMech::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTTHECCWCLICK) return("ButTheCcwClick");
	else if (ix == BUTTHECCWSTMDN) return("ButTheCcwstMdn");
	else if (ix == BUTTHECCWSTMUP) return("ButTheCcwstMup");
	else if (ix == BUTTHECWSTMDN) return("ButTheCwstMdn");
	else if (ix == BUTTHECWSTMUP) return("ButTheCwstMup");
	else if (ix == BUTTHECWCLICK) return("ButTheCwClick");
	else if (ix == BUTPHICCWCLICK) return("ButPhiCcwClick");
	else if (ix == BUTPHICCWSTMDN) return("ButPhiCcwstMdn");
	else if (ix == BUTPHICCWSTMUP) return("ButPhiCcwstMup");
	else if (ix == BUTPHICWSTMDN) return("ButPhiCwstMdn");
	else if (ix == BUTPHICWSTMUP) return("ButPhiCwstMup");
	else if (ix == BUTPHICWCLICK) return("ButPhiCwClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqMech::VecVMode
 ******************************************************************************/

uint PnlIdecIaqMech::VecVMode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "manual") return MANUAL;
	else if (s == "intact") return INTACT;
	else if (s == "auto") return AUTO;

	return(0);
};

string PnlIdecIaqMech::VecVMode::getSref(
			const uint ix
		) {
	if (ix == MANUAL) return("manual");
	else if (ix == INTACT) return("intact");
	else if (ix == AUTO) return("auto");

	return("");
};

/******************************************************************************
 class PnlIdecIaqMech::VecVSge
 ******************************************************************************/

uint PnlIdecIaqMech::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;

	return(0);
};

string PnlIdecIaqMech::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");

	return("");
};

/******************************************************************************
 class PnlIdecIaqMech::ContIac
 ******************************************************************************/

PnlIdecIaqMech::ContIac::ContIac(
			const uint numFPupMod
			, const double SldTvv
			, const double CusTheAns
			, const double CusPhiAns
		) : Block() {
	this->numFPupMod = numFPupMod;
	this->SldTvv = SldTvv;
	this->CusTheAns = CusTheAns;
	this->CusPhiAns = CusPhiAns;

	mask = {NUMFPUPMOD, SLDTVV, CUSTHEANS, CUSPHIANS};
};

bool PnlIdecIaqMech::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqMech";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupMod", numFPupMod)) add(NUMFPUPMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTvv", SldTvv)) add(SLDTVV);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusTheAns", CusTheAns)) add(CUSTHEANS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusPhiAns", CusPhiAns)) add(CUSPHIANS);
	};

	return basefound;
};

void PnlIdecIaqMech::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqMech";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupMod", numFPupMod);
		writeDoubleAttr(wr, itemtag, "sref", "SldTvv", SldTvv);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAns", CusTheAns);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAns", CusPhiAns);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqMech::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupMod == comp->numFPupMod) insert(items, NUMFPUPMOD);
	if (compareDouble(SldTvv, comp->SldTvv) < 1.0e-4) insert(items, SLDTVV);
	if (compareDouble(CusTheAns, comp->CusTheAns) < 1.0e-4) insert(items, CUSTHEANS);
	if (compareDouble(CusPhiAns, comp->CusPhiAns) < 1.0e-4) insert(items, CUSPHIANS);

	return(items);
};

set<uint> PnlIdecIaqMech::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPMOD, SLDTVV, CUSTHEANS, CUSPHIANS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqMech::ContInf
 ******************************************************************************/

PnlIdecIaqMech::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtTheAng
			, const string& TxtTheRpm
			, const uint numFCsiTheSte
			, const bool ButTheCcwOn
			, const bool ButTheCwOn
			, const string& TxtPhiAng
			, const string& TxtPhiRpm
			, const uint numFCsiPhiSte
			, const bool ButPhiCcwOn
			, const bool ButPhiCwOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtTheAng = TxtTheAng;
	this->TxtTheRpm = TxtTheRpm;
	this->numFCsiTheSte = numFCsiTheSte;
	this->ButTheCcwOn = ButTheCcwOn;
	this->ButTheCwOn = ButTheCwOn;
	this->TxtPhiAng = TxtPhiAng;
	this->TxtPhiRpm = TxtPhiRpm;
	this->numFCsiPhiSte = numFCsiPhiSte;
	this->ButPhiCcwOn = ButPhiCcwOn;
	this->ButPhiCwOn = ButPhiCwOn;

	mask = {BUTMASTERON, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
};

bool PnlIdecIaqMech::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecIaqMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecIaqMech";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtTheAng", TxtTheAng)) add(TXTTHEANG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtTheRpm", TxtTheRpm)) add(TXTTHERPM);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiTheSte", numFCsiTheSte)) add(NUMFCSITHESTE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButTheCcwOn", ButTheCcwOn)) add(BUTTHECCWON);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButTheCwOn", ButTheCwOn)) add(BUTTHECWON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtPhiAng", TxtPhiAng)) add(TXTPHIANG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtPhiRpm", TxtPhiRpm)) add(TXTPHIRPM);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiPhiSte", numFCsiPhiSte)) add(NUMFCSIPHISTE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButPhiCcwOn", ButPhiCcwOn)) add(BUTPHICCWON);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButPhiCwOn", ButPhiCwOn)) add(BUTPHICWON);
	};

	return basefound;
};

set<uint> PnlIdecIaqMech::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtTheAng.compare(comp->TxtTheAng) == 0) insert(items, TXTTHEANG);
	if (TxtTheRpm.compare(comp->TxtTheRpm) == 0) insert(items, TXTTHERPM);
	if (numFCsiTheSte == comp->numFCsiTheSte) insert(items, NUMFCSITHESTE);
	if (ButTheCcwOn == comp->ButTheCcwOn) insert(items, BUTTHECCWON);
	if (ButTheCwOn == comp->ButTheCwOn) insert(items, BUTTHECWON);
	if (TxtPhiAng.compare(comp->TxtPhiAng) == 0) insert(items, TXTPHIANG);
	if (TxtPhiRpm.compare(comp->TxtPhiRpm) == 0) insert(items, TXTPHIRPM);
	if (numFCsiPhiSte == comp->numFCsiPhiSte) insert(items, NUMFCSIPHISTE);
	if (ButPhiCcwOn == comp->ButPhiCcwOn) insert(items, BUTPHICCWON);
	if (ButPhiCwOn == comp->ButPhiCwOn) insert(items, BUTPHICWON);

	return(items);
};

set<uint> PnlIdecIaqMech::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqMech::StatShr
 ******************************************************************************/

PnlIdecIaqMech::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool SldTvvAvail
			, const double SldTvvMin
			, const double SldTvvMax
			, const bool CusTheAnsActive
			, const bool ButTheCcwActive
			, const bool ButTheCcwstActive
			, const bool ButTheCwstActive
			, const bool ButTheCwActive
			, const bool CusPhiAnsActive
			, const bool ButPhiCcwActive
			, const bool ButPhiCcwstActive
			, const bool ButPhiCwstActive
			, const bool ButPhiCwActive
			, const double CusTheAnsMin
			, const double CusTheAnsMax
			, const double CusPhiAnsMin
			, const double CusPhiAnsMax
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->SldTvvAvail = SldTvvAvail;
	this->SldTvvMin = SldTvvMin;
	this->SldTvvMax = SldTvvMax;
	this->CusTheAnsActive = CusTheAnsActive;
	this->ButTheCcwActive = ButTheCcwActive;
	this->ButTheCcwstActive = ButTheCcwstActive;
	this->ButTheCwstActive = ButTheCwstActive;
	this->ButTheCwActive = ButTheCwActive;
	this->CusPhiAnsActive = CusPhiAnsActive;
	this->ButPhiCcwActive = ButPhiCcwActive;
	this->ButPhiCcwstActive = ButPhiCcwstActive;
	this->ButPhiCwstActive = ButPhiCwstActive;
	this->ButPhiCwActive = ButPhiCwActive;
	this->CusTheAnsMin = CusTheAnsMin;
	this->CusTheAnsMax = CusTheAnsMax;
	this->CusPhiAnsMin = CusPhiAnsMin;
	this->CusPhiAnsMax = CusPhiAnsMax;

	mask = {IXIDECVEXPSTATE, SLDTVVAVAIL, SLDTVVMIN, SLDTVVMAX, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
};

bool PnlIdecIaqMech::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecIaqMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecIaqMech";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTvvAvail", SldTvvAvail)) add(SLDTVVAVAIL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTvvMin", SldTvvMin)) add(SLDTVVMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTvvMax", SldTvvMax)) add(SLDTVVMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusTheAnsActive", CusTheAnsActive)) add(CUSTHEANSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCcwActive", ButTheCcwActive)) add(BUTTHECCWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCcwstActive", ButTheCcwstActive)) add(BUTTHECCWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCwstActive", ButTheCwstActive)) add(BUTTHECWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCwActive", ButTheCwActive)) add(BUTTHECWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusPhiAnsActive", CusPhiAnsActive)) add(CUSPHIANSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCcwActive", ButPhiCcwActive)) add(BUTPHICCWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCcwstActive", ButPhiCcwstActive)) add(BUTPHICCWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCwstActive", ButPhiCwstActive)) add(BUTPHICWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCwActive", ButPhiCwActive)) add(BUTPHICWACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusTheAnsMin", CusTheAnsMin)) add(CUSTHEANSMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusTheAnsMax", CusTheAnsMax)) add(CUSTHEANSMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusPhiAnsMin", CusPhiAnsMin)) add(CUSPHIANSMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusPhiAnsMax", CusPhiAnsMax)) add(CUSPHIANSMAX);
	};

	return basefound;
};

set<uint> PnlIdecIaqMech::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (SldTvvAvail == comp->SldTvvAvail) insert(items, SLDTVVAVAIL);
	if (compareDouble(SldTvvMin, comp->SldTvvMin) < 1.0e-4) insert(items, SLDTVVMIN);
	if (compareDouble(SldTvvMax, comp->SldTvvMax) < 1.0e-4) insert(items, SLDTVVMAX);
	if (CusTheAnsActive == comp->CusTheAnsActive) insert(items, CUSTHEANSACTIVE);
	if (ButTheCcwActive == comp->ButTheCcwActive) insert(items, BUTTHECCWACTIVE);
	if (ButTheCcwstActive == comp->ButTheCcwstActive) insert(items, BUTTHECCWSTACTIVE);
	if (ButTheCwstActive == comp->ButTheCwstActive) insert(items, BUTTHECWSTACTIVE);
	if (ButTheCwActive == comp->ButTheCwActive) insert(items, BUTTHECWACTIVE);
	if (CusPhiAnsActive == comp->CusPhiAnsActive) insert(items, CUSPHIANSACTIVE);
	if (ButPhiCcwActive == comp->ButPhiCcwActive) insert(items, BUTPHICCWACTIVE);
	if (ButPhiCcwstActive == comp->ButPhiCcwstActive) insert(items, BUTPHICCWSTACTIVE);
	if (ButPhiCwstActive == comp->ButPhiCwstActive) insert(items, BUTPHICWSTACTIVE);
	if (ButPhiCwActive == comp->ButPhiCwActive) insert(items, BUTPHICWACTIVE);
	if (compareDouble(CusTheAnsMin, comp->CusTheAnsMin) < 1.0e-4) insert(items, CUSTHEANSMIN);
	if (compareDouble(CusTheAnsMax, comp->CusTheAnsMax) < 1.0e-4) insert(items, CUSTHEANSMAX);
	if (compareDouble(CusPhiAnsMin, comp->CusPhiAnsMin) < 1.0e-4) insert(items, CUSPHIANSMIN);
	if (compareDouble(CusPhiAnsMax, comp->CusPhiAnsMax) < 1.0e-4) insert(items, CUSPHIANSMAX);

	return(items);
};

set<uint> PnlIdecIaqMech::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, SLDTVVAVAIL, SLDTVVMIN, SLDTVVMAX, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqMech::Tag
 ******************************************************************************/

PnlIdecIaqMech::Tag::Tag(
			const string& Cpt
			, const string& CptMod
			, const string& CptTvv
		) : Block() {
	this->Cpt = Cpt;
	this->CptMod = CptMod;
	this->CptTvv = CptTvv;

	mask = {CPT, CPTMOD, CPTTVV};
};

bool PnlIdecIaqMech::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecIaqMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecIaqMech";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMod", CptMod)) add(CPTMOD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTvv", CptTvv)) add(CPTTVV);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecIaqMech::DpchAppData
 ******************************************************************************/

PnlIdecIaqMech::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQMECHDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecIaqMech::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqMechData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqMech::DpchAppDo
 ******************************************************************************/

PnlIdecIaqMech::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQMECHDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecIaqMech::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqMechDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqMech::DpchEngData
 ******************************************************************************/

PnlIdecIaqMech::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQMECHDATA) {
	feedFCsiPhiSte.tag = "FeedFCsiPhiSte";
	feedFCsiTheSte.tag = "FeedFCsiTheSte";
	feedFPupMod.tag = "FeedFPupMod";
};

string PnlIdecIaqMech::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIPHISTE)) ss.push_back("feedFCsiPhiSte");
	if (has(FEEDFCSITHESTE)) ss.push_back("feedFCsiTheSte");
	if (has(FEEDFPUPMOD)) ss.push_back("feedFPupMod");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqMechData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFCsiPhiSte.readXML(docctx, basexpath, true)) add(FEEDFCSIPHISTE);
		if (feedFCsiTheSte.readXML(docctx, basexpath, true)) add(FEEDFCSITHESTE);
		if (feedFPupMod.readXML(docctx, basexpath, true)) add(FEEDFPUPMOD);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFCsiPhiSte.clear();
		feedFCsiTheSte.clear();
		feedFPupMod.clear();
		statshr = StatShr();
		tag = Tag();
	};
};

/******************************************************************************
 class PnlIdecIaqMech::DpchEngLive
 ******************************************************************************/

PnlIdecIaqMech::DpchEngLive::DpchEngLive() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQMECHLIVE) {
};

string PnlIdecIaqMech::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchEngLive::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqMechLive");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
	} else {
		continf = ContInf();
	};
};

