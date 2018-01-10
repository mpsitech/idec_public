/**
  * \file PnlIdecScfMech.cpp
  * API code for job PnlIdecScfMech (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfMech.h"

/******************************************************************************
 class PnlIdecScfMech::VecVDo
 ******************************************************************************/

uint PnlIdecScfMech::VecVDo::getIx(
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

string PnlIdecScfMech::VecVDo::getSref(
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
 class PnlIdecScfMech::VecVSge
 ******************************************************************************/

uint PnlIdecScfMech::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;

	return(0);
};

string PnlIdecScfMech::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");

	return("");
};

/******************************************************************************
 class PnlIdecScfMech::ContIac
 ******************************************************************************/

PnlIdecScfMech::ContIac::ContIac(
			const string& TxfTgr
			, const double SldTll
			, const double SldTul
			, const string& TxfPgr
			, const double SldPll
			, const double SldPul
			, const double CusTheAns
			, const double CusPhiAns
		) : Block() {
	this->TxfTgr = TxfTgr;
	this->SldTll = SldTll;
	this->SldTul = SldTul;
	this->TxfPgr = TxfPgr;
	this->SldPll = SldPll;
	this->SldPul = SldPul;
	this->CusTheAns = CusTheAns;
	this->CusPhiAns = CusPhiAns;

	mask = {TXFTGR, SLDTLL, SLDTUL, TXFPGR, SLDPLL, SLDPUL, CUSTHEANS, CUSPHIANS};
};

bool PnlIdecScfMech::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfMech";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfTgr", TxfTgr)) add(TXFTGR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTll", SldTll)) add(SLDTLL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTul", SldTul)) add(SLDTUL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPgr", TxfPgr)) add(TXFPGR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldPll", SldPll)) add(SLDPLL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldPul", SldPul)) add(SLDPUL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusTheAns", CusTheAns)) add(CUSTHEANS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusPhiAns", CusPhiAns)) add(CUSPHIANS);
	};

	return basefound;
};

void PnlIdecScfMech::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfMech";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfTgr", TxfTgr);
		writeDoubleAttr(wr, itemtag, "sref", "SldTll", SldTll);
		writeDoubleAttr(wr, itemtag, "sref", "SldTul", SldTul);
		writeStringAttr(wr, itemtag, "sref", "TxfPgr", TxfPgr);
		writeDoubleAttr(wr, itemtag, "sref", "SldPll", SldPll);
		writeDoubleAttr(wr, itemtag, "sref", "SldPul", SldPul);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAns", CusTheAns);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAns", CusPhiAns);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfMech::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfTgr.compare(comp->TxfTgr) == 0) insert(items, TXFTGR);
	if (compareDouble(SldTll, comp->SldTll) < 1.0e-4) insert(items, SLDTLL);
	if (compareDouble(SldTul, comp->SldTul) < 1.0e-4) insert(items, SLDTUL);
	if (TxfPgr.compare(comp->TxfPgr) == 0) insert(items, TXFPGR);
	if (compareDouble(SldPll, comp->SldPll) < 1.0e-4) insert(items, SLDPLL);
	if (compareDouble(SldPul, comp->SldPul) < 1.0e-4) insert(items, SLDPUL);
	if (compareDouble(CusTheAns, comp->CusTheAns) < 1.0e-4) insert(items, CUSTHEANS);
	if (compareDouble(CusPhiAns, comp->CusPhiAns) < 1.0e-4) insert(items, CUSPHIANS);

	return(items);
};

set<uint> PnlIdecScfMech::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFTGR, SLDTLL, SLDTUL, TXFPGR, SLDPLL, SLDPUL, CUSTHEANS, CUSPHIANS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfMech::ContInf
 ******************************************************************************/

PnlIdecScfMech::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtOrsAlpha
			, const string& TxtOrsBeta
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
	this->TxtOrsAlpha = TxtOrsAlpha;
	this->TxtOrsBeta = TxtOrsBeta;
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

	mask = {BUTMASTERON, TXTORSALPHA, TXTORSBETA, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
};

bool PnlIdecScfMech::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfMech";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtOrsAlpha", TxtOrsAlpha)) add(TXTORSALPHA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtOrsBeta", TxtOrsBeta)) add(TXTORSBETA);
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

set<uint> PnlIdecScfMech::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtOrsAlpha.compare(comp->TxtOrsAlpha) == 0) insert(items, TXTORSALPHA);
	if (TxtOrsBeta.compare(comp->TxtOrsBeta) == 0) insert(items, TXTORSBETA);
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

set<uint> PnlIdecScfMech::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTORSALPHA, TXTORSBETA, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfMech::StatShr
 ******************************************************************************/

PnlIdecScfMech::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool CusTheAnsActive
			, const bool ButTheCcwActive
			, const bool ButTheCcwstActive
			, const bool ButTheCwstActive
			, const bool ButTheCwActive
			, const bool TxfTgrActive
			, const bool SldTllActive
			, const double SldTllMin
			, const double SldTllMax
			, const bool SldTulActive
			, const double SldTulMin
			, const double SldTulMax
			, const bool CusPhiAnsActive
			, const bool ButPhiCcwActive
			, const bool ButPhiCcwstActive
			, const bool ButPhiCwstActive
			, const bool ButPhiCwActive
			, const bool TxfPgrActive
			, const bool SldPllActive
			, const double SldPllMin
			, const double SldPllMax
			, const bool SldPulActive
			, const double SldPulMin
			, const double SldPulMax
			, const double CusTheAnsMin
			, const double CusTheAnsMax
			, const double CusPhiAnsMin
			, const double CusPhiAnsMax
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->CusTheAnsActive = CusTheAnsActive;
	this->ButTheCcwActive = ButTheCcwActive;
	this->ButTheCcwstActive = ButTheCcwstActive;
	this->ButTheCwstActive = ButTheCwstActive;
	this->ButTheCwActive = ButTheCwActive;
	this->TxfTgrActive = TxfTgrActive;
	this->SldTllActive = SldTllActive;
	this->SldTllMin = SldTllMin;
	this->SldTllMax = SldTllMax;
	this->SldTulActive = SldTulActive;
	this->SldTulMin = SldTulMin;
	this->SldTulMax = SldTulMax;
	this->CusPhiAnsActive = CusPhiAnsActive;
	this->ButPhiCcwActive = ButPhiCcwActive;
	this->ButPhiCcwstActive = ButPhiCcwstActive;
	this->ButPhiCwstActive = ButPhiCwstActive;
	this->ButPhiCwActive = ButPhiCwActive;
	this->TxfPgrActive = TxfPgrActive;
	this->SldPllActive = SldPllActive;
	this->SldPllMin = SldPllMin;
	this->SldPllMax = SldPllMax;
	this->SldPulActive = SldPulActive;
	this->SldPulMin = SldPulMin;
	this->SldPulMax = SldPulMax;
	this->CusTheAnsMin = CusTheAnsMin;
	this->CusTheAnsMax = CusTheAnsMax;
	this->CusPhiAnsMin = CusPhiAnsMin;
	this->CusPhiAnsMax = CusPhiAnsMax;

	mask = {IXIDECVEXPSTATE, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, TXFTGRACTIVE, SLDTLLACTIVE, SLDTLLMIN, SLDTLLMAX, SLDTULACTIVE, SLDTULMIN, SLDTULMAX, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, TXFPGRACTIVE, SLDPLLACTIVE, SLDPLLMIN, SLDPLLMAX, SLDPULACTIVE, SLDPULMIN, SLDPULMAX, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
};

bool PnlIdecScfMech::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfMech";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusTheAnsActive", CusTheAnsActive)) add(CUSTHEANSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCcwActive", ButTheCcwActive)) add(BUTTHECCWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCcwstActive", ButTheCcwstActive)) add(BUTTHECCWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCwstActive", ButTheCwstActive)) add(BUTTHECWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheCwActive", ButTheCwActive)) add(BUTTHECWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfTgrActive", TxfTgrActive)) add(TXFTGRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTllActive", SldTllActive)) add(SLDTLLACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTllMin", SldTllMin)) add(SLDTLLMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTllMax", SldTllMax)) add(SLDTLLMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTulActive", SldTulActive)) add(SLDTULACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTulMin", SldTulMin)) add(SLDTULMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTulMax", SldTulMax)) add(SLDTULMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusPhiAnsActive", CusPhiAnsActive)) add(CUSPHIANSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCcwActive", ButPhiCcwActive)) add(BUTPHICCWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCcwstActive", ButPhiCcwstActive)) add(BUTPHICCWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCwstActive", ButPhiCwstActive)) add(BUTPHICWSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiCwActive", ButPhiCwActive)) add(BUTPHICWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPgrActive", TxfPgrActive)) add(TXFPGRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPllActive", SldPllActive)) add(SLDPLLACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPllMin", SldPllMin)) add(SLDPLLMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPllMax", SldPllMax)) add(SLDPLLMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPulActive", SldPulActive)) add(SLDPULACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPulMin", SldPulMin)) add(SLDPULMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPulMax", SldPulMax)) add(SLDPULMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusTheAnsMin", CusTheAnsMin)) add(CUSTHEANSMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusTheAnsMax", CusTheAnsMax)) add(CUSTHEANSMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusPhiAnsMin", CusPhiAnsMin)) add(CUSPHIANSMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusPhiAnsMax", CusPhiAnsMax)) add(CUSPHIANSMAX);
	};

	return basefound;
};

set<uint> PnlIdecScfMech::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (CusTheAnsActive == comp->CusTheAnsActive) insert(items, CUSTHEANSACTIVE);
	if (ButTheCcwActive == comp->ButTheCcwActive) insert(items, BUTTHECCWACTIVE);
	if (ButTheCcwstActive == comp->ButTheCcwstActive) insert(items, BUTTHECCWSTACTIVE);
	if (ButTheCwstActive == comp->ButTheCwstActive) insert(items, BUTTHECWSTACTIVE);
	if (ButTheCwActive == comp->ButTheCwActive) insert(items, BUTTHECWACTIVE);
	if (TxfTgrActive == comp->TxfTgrActive) insert(items, TXFTGRACTIVE);
	if (SldTllActive == comp->SldTllActive) insert(items, SLDTLLACTIVE);
	if (compareDouble(SldTllMin, comp->SldTllMin) < 1.0e-4) insert(items, SLDTLLMIN);
	if (compareDouble(SldTllMax, comp->SldTllMax) < 1.0e-4) insert(items, SLDTLLMAX);
	if (SldTulActive == comp->SldTulActive) insert(items, SLDTULACTIVE);
	if (compareDouble(SldTulMin, comp->SldTulMin) < 1.0e-4) insert(items, SLDTULMIN);
	if (compareDouble(SldTulMax, comp->SldTulMax) < 1.0e-4) insert(items, SLDTULMAX);
	if (CusPhiAnsActive == comp->CusPhiAnsActive) insert(items, CUSPHIANSACTIVE);
	if (ButPhiCcwActive == comp->ButPhiCcwActive) insert(items, BUTPHICCWACTIVE);
	if (ButPhiCcwstActive == comp->ButPhiCcwstActive) insert(items, BUTPHICCWSTACTIVE);
	if (ButPhiCwstActive == comp->ButPhiCwstActive) insert(items, BUTPHICWSTACTIVE);
	if (ButPhiCwActive == comp->ButPhiCwActive) insert(items, BUTPHICWACTIVE);
	if (TxfPgrActive == comp->TxfPgrActive) insert(items, TXFPGRACTIVE);
	if (SldPllActive == comp->SldPllActive) insert(items, SLDPLLACTIVE);
	if (compareDouble(SldPllMin, comp->SldPllMin) < 1.0e-4) insert(items, SLDPLLMIN);
	if (compareDouble(SldPllMax, comp->SldPllMax) < 1.0e-4) insert(items, SLDPLLMAX);
	if (SldPulActive == comp->SldPulActive) insert(items, SLDPULACTIVE);
	if (compareDouble(SldPulMin, comp->SldPulMin) < 1.0e-4) insert(items, SLDPULMIN);
	if (compareDouble(SldPulMax, comp->SldPulMax) < 1.0e-4) insert(items, SLDPULMAX);
	if (compareDouble(CusTheAnsMin, comp->CusTheAnsMin) < 1.0e-4) insert(items, CUSTHEANSMIN);
	if (compareDouble(CusTheAnsMax, comp->CusTheAnsMax) < 1.0e-4) insert(items, CUSTHEANSMAX);
	if (compareDouble(CusPhiAnsMin, comp->CusPhiAnsMin) < 1.0e-4) insert(items, CUSPHIANSMIN);
	if (compareDouble(CusPhiAnsMax, comp->CusPhiAnsMax) < 1.0e-4) insert(items, CUSPHIANSMAX);

	return(items);
};

set<uint> PnlIdecScfMech::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, TXFTGRACTIVE, SLDTLLACTIVE, SLDTLLMIN, SLDTLLMAX, SLDTULACTIVE, SLDTULMIN, SLDTULMAX, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, TXFPGRACTIVE, SLDPLLACTIVE, SLDPLLMIN, SLDPLLMAX, SLDPULACTIVE, SLDPULMIN, SLDPULMAX, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfMech::Tag
 ******************************************************************************/

PnlIdecScfMech::Tag::Tag(
			const string& Cpt
			, const string& HdgOrsns
			, const string& HdgTheax
			, const string& CptTgr
			, const string& CptTll
			, const string& CptTul
			, const string& HdgPhiax
			, const string& CptPgr
			, const string& CptPll
			, const string& CptPul
		) : Block() {
	this->Cpt = Cpt;
	this->HdgOrsns = HdgOrsns;
	this->HdgTheax = HdgTheax;
	this->CptTgr = CptTgr;
	this->CptTll = CptTll;
	this->CptTul = CptTul;
	this->HdgPhiax = HdgPhiax;
	this->CptPgr = CptPgr;
	this->CptPll = CptPll;
	this->CptPul = CptPul;

	mask = {CPT, HDGORSNS, HDGTHEAX, CPTTGR, CPTTLL, CPTTUL, HDGPHIAX, CPTPGR, CPTPLL, CPTPUL};
};

bool PnlIdecScfMech::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfMech";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgOrsns", HdgOrsns)) add(HDGORSNS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgTheax", HdgTheax)) add(HDGTHEAX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTgr", CptTgr)) add(CPTTGR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTll", CptTll)) add(CPTTLL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTul", CptTul)) add(CPTTUL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgPhiax", HdgPhiax)) add(HDGPHIAX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPgr", CptPgr)) add(CPTPGR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPll", CptPll)) add(CPTPLL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPul", CptPul)) add(CPTPUL);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfMech::DpchAppData
 ******************************************************************************/

PnlIdecScfMech::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFMECHDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecScfMech::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfMechData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfMech::DpchAppDo
 ******************************************************************************/

PnlIdecScfMech::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFMECHDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfMech::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfMechDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfMech::DpchEngData
 ******************************************************************************/

PnlIdecScfMech::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFMECHDATA) {
	feedFCsiPhiSte.tag = "FeedFCsiPhiSte";
	feedFCsiTheSte.tag = "FeedFCsiTheSte";
};

string PnlIdecScfMech::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIPHISTE)) ss.push_back("feedFCsiPhiSte");
	if (has(FEEDFCSITHESTE)) ss.push_back("feedFCsiTheSte");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfMechData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFCsiPhiSte.readXML(docctx, basexpath, true)) add(FEEDFCSIPHISTE);
		if (feedFCsiTheSte.readXML(docctx, basexpath, true)) add(FEEDFCSITHESTE);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFCsiPhiSte.clear();
		feedFCsiTheSte.clear();
		statshr = StatShr();
		tag = Tag();
	};
};

/******************************************************************************
 class PnlIdecScfMech::DpchEngLive
 ******************************************************************************/

PnlIdecScfMech::DpchEngLive::DpchEngLive() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFMECHLIVE) {
};

string PnlIdecScfMech::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchEngLive::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfMechLive");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
	} else {
		continf = ContInf();
	};
};

