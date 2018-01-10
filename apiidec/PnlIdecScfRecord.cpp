/**
  * \file PnlIdecScfRecord.cpp
  * API code for job PnlIdecScfRecord (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfRecord.h"

/******************************************************************************
 class PnlIdecScfRecord::VecVDo
 ******************************************************************************/

uint PnlIdecScfRecord::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfRecord::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfRecord::ContIac
 ******************************************************************************/

PnlIdecScfRecord::ContIac::ContIac(
			const uint numFPupFlr
			, const bool ChkFlg
			, const uint numFPupFrr
			, const bool ChkFrg
			, const uint numFPupFir
			, const bool ChkFqc
			, const bool ChkFst
			, const double SldVfr
			, const uint numFPupVlr
			, const bool ChkVlg
			, const uint numFPupVrr
			, const bool ChkVrg
			, const uint numFPupVir
			, const bool ChkVqc
			, const bool ChkVst
			, const uint numFPupOwr
		) : Block() {
	this->numFPupFlr = numFPupFlr;
	this->ChkFlg = ChkFlg;
	this->numFPupFrr = numFPupFrr;
	this->ChkFrg = ChkFrg;
	this->numFPupFir = numFPupFir;
	this->ChkFqc = ChkFqc;
	this->ChkFst = ChkFst;
	this->SldVfr = SldVfr;
	this->numFPupVlr = numFPupVlr;
	this->ChkVlg = ChkVlg;
	this->numFPupVrr = numFPupVrr;
	this->ChkVrg = ChkVrg;
	this->numFPupVir = numFPupVir;
	this->ChkVqc = ChkVqc;
	this->ChkVst = ChkVst;
	this->numFPupOwr = numFPupOwr;

	mask = {NUMFPUPFLR, CHKFLG, NUMFPUPFRR, CHKFRG, NUMFPUPFIR, CHKFQC, CHKFST, SLDVFR, NUMFPUPVLR, CHKVLG, NUMFPUPVRR, CHKVRG, NUMFPUPVIR, CHKVQC, CHKVST, NUMFPUPOWR};
};

bool PnlIdecScfRecord::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfRecord";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFlr", numFPupFlr)) add(NUMFPUPFLR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFlg", ChkFlg)) add(CHKFLG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFrr", numFPupFrr)) add(NUMFPUPFRR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFrg", ChkFrg)) add(CHKFRG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFir", numFPupFir)) add(NUMFPUPFIR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFqc", ChkFqc)) add(CHKFQC);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFst", ChkFst)) add(CHKFST);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldVfr", SldVfr)) add(SLDVFR);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVlr", numFPupVlr)) add(NUMFPUPVLR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVlg", ChkVlg)) add(CHKVLG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVrr", numFPupVrr)) add(NUMFPUPVRR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVrg", ChkVrg)) add(CHKVRG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVir", numFPupVir)) add(NUMFPUPVIR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVqc", ChkVqc)) add(CHKVQC);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVst", ChkVst)) add(CHKVST);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupOwr", numFPupOwr)) add(NUMFPUPOWR);
	};

	return basefound;
};

void PnlIdecScfRecord::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfRecord";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupFlr", numFPupFlr);
		writeBoolAttr(wr, itemtag, "sref", "ChkFlg", ChkFlg);
		writeUintAttr(wr, itemtag, "sref", "numFPupFrr", numFPupFrr);
		writeBoolAttr(wr, itemtag, "sref", "ChkFrg", ChkFrg);
		writeUintAttr(wr, itemtag, "sref", "numFPupFir", numFPupFir);
		writeBoolAttr(wr, itemtag, "sref", "ChkFqc", ChkFqc);
		writeBoolAttr(wr, itemtag, "sref", "ChkFst", ChkFst);
		writeDoubleAttr(wr, itemtag, "sref", "SldVfr", SldVfr);
		writeUintAttr(wr, itemtag, "sref", "numFPupVlr", numFPupVlr);
		writeBoolAttr(wr, itemtag, "sref", "ChkVlg", ChkVlg);
		writeUintAttr(wr, itemtag, "sref", "numFPupVrr", numFPupVrr);
		writeBoolAttr(wr, itemtag, "sref", "ChkVrg", ChkVrg);
		writeUintAttr(wr, itemtag, "sref", "numFPupVir", numFPupVir);
		writeBoolAttr(wr, itemtag, "sref", "ChkVqc", ChkVqc);
		writeBoolAttr(wr, itemtag, "sref", "ChkVst", ChkVst);
		writeUintAttr(wr, itemtag, "sref", "numFPupOwr", numFPupOwr);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfRecord::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupFlr == comp->numFPupFlr) insert(items, NUMFPUPFLR);
	if (ChkFlg == comp->ChkFlg) insert(items, CHKFLG);
	if (numFPupFrr == comp->numFPupFrr) insert(items, NUMFPUPFRR);
	if (ChkFrg == comp->ChkFrg) insert(items, CHKFRG);
	if (numFPupFir == comp->numFPupFir) insert(items, NUMFPUPFIR);
	if (ChkFqc == comp->ChkFqc) insert(items, CHKFQC);
	if (ChkFst == comp->ChkFst) insert(items, CHKFST);
	if (compareDouble(SldVfr, comp->SldVfr) < 1.0e-4) insert(items, SLDVFR);
	if (numFPupVlr == comp->numFPupVlr) insert(items, NUMFPUPVLR);
	if (ChkVlg == comp->ChkVlg) insert(items, CHKVLG);
	if (numFPupVrr == comp->numFPupVrr) insert(items, NUMFPUPVRR);
	if (ChkVrg == comp->ChkVrg) insert(items, CHKVRG);
	if (numFPupVir == comp->numFPupVir) insert(items, NUMFPUPVIR);
	if (ChkVqc == comp->ChkVqc) insert(items, CHKVQC);
	if (ChkVst == comp->ChkVst) insert(items, CHKVST);
	if (numFPupOwr == comp->numFPupOwr) insert(items, NUMFPUPOWR);

	return(items);
};

set<uint> PnlIdecScfRecord::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPFLR, CHKFLG, NUMFPUPFRR, CHKFRG, NUMFPUPFIR, CHKFQC, CHKFST, SLDVFR, NUMFPUPVLR, CHKVLG, NUMFPUPVRR, CHKVRG, NUMFPUPVIR, CHKVQC, CHKVST, NUMFPUPOWR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfRecord::ContInf
 ******************************************************************************/

PnlIdecScfRecord::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

bool PnlIdecScfRecord::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfRecord";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
	};

	return basefound;
};

set<uint> PnlIdecScfRecord::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecScfRecord::ContInf::diff(
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
 class PnlIdecScfRecord::StatApp
 ******************************************************************************/

PnlIdecScfRecord::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecScfRecord::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScfRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScfRecord";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecScfRecord::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecScfRecord::StatApp::diff(
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
 class PnlIdecScfRecord::StatShr
 ******************************************************************************/

PnlIdecScfRecord::StatShr::StatShr(
			const bool PupFlrActive
			, const bool ChkFlgActive
			, const bool PupFrrActive
			, const bool ChkFrgActive
			, const bool PupFirActive
			, const bool ChkFqcActive
			, const bool ChkFstActive
			, const bool SldVfrActive
			, const double SldVfrMin
			, const double SldVfrMax
			, const bool PupVlrActive
			, const bool ChkVlgActive
			, const bool PupVrrActive
			, const bool ChkVrgActive
			, const bool PupVirActive
			, const bool ChkVqcActive
			, const bool ChkVstActive
			, const bool PupOwrActive
		) : Block() {
	this->PupFlrActive = PupFlrActive;
	this->ChkFlgActive = ChkFlgActive;
	this->PupFrrActive = PupFrrActive;
	this->ChkFrgActive = ChkFrgActive;
	this->PupFirActive = PupFirActive;
	this->ChkFqcActive = ChkFqcActive;
	this->ChkFstActive = ChkFstActive;
	this->SldVfrActive = SldVfrActive;
	this->SldVfrMin = SldVfrMin;
	this->SldVfrMax = SldVfrMax;
	this->PupVlrActive = PupVlrActive;
	this->ChkVlgActive = ChkVlgActive;
	this->PupVrrActive = PupVrrActive;
	this->ChkVrgActive = ChkVrgActive;
	this->PupVirActive = PupVirActive;
	this->ChkVqcActive = ChkVqcActive;
	this->ChkVstActive = ChkVstActive;
	this->PupOwrActive = PupOwrActive;

	mask = {PUPFLRACTIVE, CHKFLGACTIVE, PUPFRRACTIVE, CHKFRGACTIVE, PUPFIRACTIVE, CHKFQCACTIVE, CHKFSTACTIVE, SLDVFRACTIVE, SLDVFRMIN, SLDVFRMAX, PUPVLRACTIVE, CHKVLGACTIVE, PUPVRRACTIVE, CHKVRGACTIVE, PUPVIRACTIVE, CHKVQCACTIVE, CHKVSTACTIVE, PUPOWRACTIVE};
};

bool PnlIdecScfRecord::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfRecord";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupFlrActive", PupFlrActive)) add(PUPFLRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkFlgActive", ChkFlgActive)) add(CHKFLGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupFrrActive", PupFrrActive)) add(PUPFRRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkFrgActive", ChkFrgActive)) add(CHKFRGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupFirActive", PupFirActive)) add(PUPFIRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkFqcActive", ChkFqcActive)) add(CHKFQCACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkFstActive", ChkFstActive)) add(CHKFSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVfrActive", SldVfrActive)) add(SLDVFRACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVfrMin", SldVfrMin)) add(SLDVFRMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVfrMax", SldVfrMax)) add(SLDVFRMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupVlrActive", PupVlrActive)) add(PUPVLRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkVlgActive", ChkVlgActive)) add(CHKVLGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupVrrActive", PupVrrActive)) add(PUPVRRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkVrgActive", ChkVrgActive)) add(CHKVRGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupVirActive", PupVirActive)) add(PUPVIRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkVqcActive", ChkVqcActive)) add(CHKVQCACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkVstActive", ChkVstActive)) add(CHKVSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupOwrActive", PupOwrActive)) add(PUPOWRACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecScfRecord::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (PupFlrActive == comp->PupFlrActive) insert(items, PUPFLRACTIVE);
	if (ChkFlgActive == comp->ChkFlgActive) insert(items, CHKFLGACTIVE);
	if (PupFrrActive == comp->PupFrrActive) insert(items, PUPFRRACTIVE);
	if (ChkFrgActive == comp->ChkFrgActive) insert(items, CHKFRGACTIVE);
	if (PupFirActive == comp->PupFirActive) insert(items, PUPFIRACTIVE);
	if (ChkFqcActive == comp->ChkFqcActive) insert(items, CHKFQCACTIVE);
	if (ChkFstActive == comp->ChkFstActive) insert(items, CHKFSTACTIVE);
	if (SldVfrActive == comp->SldVfrActive) insert(items, SLDVFRACTIVE);
	if (compareDouble(SldVfrMin, comp->SldVfrMin) < 1.0e-4) insert(items, SLDVFRMIN);
	if (compareDouble(SldVfrMax, comp->SldVfrMax) < 1.0e-4) insert(items, SLDVFRMAX);
	if (PupVlrActive == comp->PupVlrActive) insert(items, PUPVLRACTIVE);
	if (ChkVlgActive == comp->ChkVlgActive) insert(items, CHKVLGACTIVE);
	if (PupVrrActive == comp->PupVrrActive) insert(items, PUPVRRACTIVE);
	if (ChkVrgActive == comp->ChkVrgActive) insert(items, CHKVRGACTIVE);
	if (PupVirActive == comp->PupVirActive) insert(items, PUPVIRACTIVE);
	if (ChkVqcActive == comp->ChkVqcActive) insert(items, CHKVQCACTIVE);
	if (ChkVstActive == comp->ChkVstActive) insert(items, CHKVSTACTIVE);
	if (PupOwrActive == comp->PupOwrActive) insert(items, PUPOWRACTIVE);

	return(items);
};

set<uint> PnlIdecScfRecord::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {PUPFLRACTIVE, CHKFLGACTIVE, PUPFRRACTIVE, CHKFRGACTIVE, PUPFIRACTIVE, CHKFQCACTIVE, CHKFSTACTIVE, SLDVFRACTIVE, SLDVFRMIN, SLDVFRMAX, PUPVLRACTIVE, CHKVLGACTIVE, PUPVRRACTIVE, CHKVRGACTIVE, PUPVIRACTIVE, CHKVQCACTIVE, CHKVSTACTIVE, PUPOWRACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfRecord::Tag
 ******************************************************************************/

PnlIdecScfRecord::Tag::Tag(
			const string& Cpt
			, const string& HdgFrame
			, const string& CptFlr
			, const string& CptFlg
			, const string& CptFrr
			, const string& CptFrg
			, const string& CptFir
			, const string& CptFqc
			, const string& CptFst
			, const string& HdgVideo
			, const string& CptVfr
			, const string& CptVlr
			, const string& CptVlg
			, const string& CptVrr
			, const string& CptVrg
			, const string& CptVir
			, const string& CptVqc
			, const string& CptVst
			, const string& CptOwr
		) : Block() {
	this->Cpt = Cpt;
	this->HdgFrame = HdgFrame;
	this->CptFlr = CptFlr;
	this->CptFlg = CptFlg;
	this->CptFrr = CptFrr;
	this->CptFrg = CptFrg;
	this->CptFir = CptFir;
	this->CptFqc = CptFqc;
	this->CptFst = CptFst;
	this->HdgVideo = HdgVideo;
	this->CptVfr = CptVfr;
	this->CptVlr = CptVlr;
	this->CptVlg = CptVlg;
	this->CptVrr = CptVrr;
	this->CptVrg = CptVrg;
	this->CptVir = CptVir;
	this->CptVqc = CptVqc;
	this->CptVst = CptVst;
	this->CptOwr = CptOwr;

	mask = {CPT, HDGFRAME, CPTFLR, CPTFLG, CPTFRR, CPTFRG, CPTFIR, CPTFQC, CPTFST, HDGVIDEO, CPTVFR, CPTVLR, CPTVLG, CPTVRR, CPTVRG, CPTVIR, CPTVQC, CPTVST, CPTOWR};
};

bool PnlIdecScfRecord::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfRecord";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgFrame", HdgFrame)) add(HDGFRAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFlr", CptFlr)) add(CPTFLR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFlg", CptFlg)) add(CPTFLG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFrr", CptFrr)) add(CPTFRR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFrg", CptFrg)) add(CPTFRG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFir", CptFir)) add(CPTFIR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFqc", CptFqc)) add(CPTFQC);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFst", CptFst)) add(CPTFST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgVideo", HdgVideo)) add(HDGVIDEO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVfr", CptVfr)) add(CPTVFR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVlr", CptVlr)) add(CPTVLR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVlg", CptVlg)) add(CPTVLG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVrr", CptVrr)) add(CPTVRR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVrg", CptVrg)) add(CPTVRG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVir", CptVir)) add(CPTVIR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVqc", CptVqc)) add(CPTVQC);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVst", CptVst)) add(CPTVST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOwr", CptOwr)) add(CPTOWR);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfRecord::DpchAppData
 ******************************************************************************/

PnlIdecScfRecord::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFRECORDDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecScfRecord::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfRecord::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfRecordData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfRecord::DpchAppDo
 ******************************************************************************/

PnlIdecScfRecord::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFRECORDDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfRecord::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfRecord::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfRecordDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfRecord::DpchEngData
 ******************************************************************************/

PnlIdecScfRecord::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFRECORDDATA) {
	feedFPupFir.tag = "FeedFPupFir";
	feedFPupFlr.tag = "FeedFPupFlr";
	feedFPupFrr.tag = "FeedFPupFrr";
	feedFPupOwr.tag = "FeedFPupOwr";
	feedFPupVir.tag = "FeedFPupVir";
	feedFPupVlr.tag = "FeedFPupVlr";
	feedFPupVrr.tag = "FeedFPupVrr";
};

string PnlIdecScfRecord::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPFIR)) ss.push_back("feedFPupFir");
	if (has(FEEDFPUPFLR)) ss.push_back("feedFPupFlr");
	if (has(FEEDFPUPFRR)) ss.push_back("feedFPupFrr");
	if (has(FEEDFPUPOWR)) ss.push_back("feedFPupOwr");
	if (has(FEEDFPUPVIR)) ss.push_back("feedFPupVir");
	if (has(FEEDFPUPVLR)) ss.push_back("feedFPupVlr");
	if (has(FEEDFPUPVRR)) ss.push_back("feedFPupVrr");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfRecord::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfRecordData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupFir.readXML(docctx, basexpath, true)) add(FEEDFPUPFIR);
		if (feedFPupFlr.readXML(docctx, basexpath, true)) add(FEEDFPUPFLR);
		if (feedFPupFrr.readXML(docctx, basexpath, true)) add(FEEDFPUPFRR);
		if (feedFPupOwr.readXML(docctx, basexpath, true)) add(FEEDFPUPOWR);
		if (feedFPupVir.readXML(docctx, basexpath, true)) add(FEEDFPUPVIR);
		if (feedFPupVlr.readXML(docctx, basexpath, true)) add(FEEDFPUPVLR);
		if (feedFPupVrr.readXML(docctx, basexpath, true)) add(FEEDFPUPVRR);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupFir.clear();
		feedFPupFlr.clear();
		feedFPupFrr.clear();
		feedFPupOwr.clear();
		feedFPupVir.clear();
		feedFPupVlr.clear();
		feedFPupVrr.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

