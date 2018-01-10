/**
  * \file PnlIdecScfQcd.cpp
  * API code for job PnlIdecScfQcd (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfQcd.h"

/******************************************************************************
 class PnlIdecScfQcd::VecVDo
 ******************************************************************************/

uint PnlIdecScfQcd::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfQcd::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfQcd::ContIac
 ******************************************************************************/

PnlIdecScfQcd::ContIac::ContIac(
			const string& TxfLam
			, const string& TxfDlm
			, const bool ChkAon
			, const double SldTof
			, const double SldTmp
			, const uint numFPupFan
			, const double SldFmd
			, const double SldVdd
			, const bool ChkVd2
			, const double SldVrf
			, const int UpdAsl
			, const double SldAmo
			, const bool ChkAad
		) : Block() {
	this->TxfLam = TxfLam;
	this->TxfDlm = TxfDlm;
	this->ChkAon = ChkAon;
	this->SldTof = SldTof;
	this->SldTmp = SldTmp;
	this->numFPupFan = numFPupFan;
	this->SldFmd = SldFmd;
	this->SldVdd = SldVdd;
	this->ChkVd2 = ChkVd2;
	this->SldVrf = SldVrf;
	this->UpdAsl = UpdAsl;
	this->SldAmo = SldAmo;
	this->ChkAad = ChkAad;

	mask = {TXFLAM, TXFDLM, CHKAON, SLDTOF, SLDTMP, NUMFPUPFAN, SLDFMD, SLDVDD, CHKVD2, SLDVRF, UPDASL, SLDAMO, CHKAAD};
};

bool PnlIdecScfQcd::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfQcd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfQcd";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfLam", TxfLam)) add(TXFLAM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfDlm", TxfDlm)) add(TXFDLM);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkAon", ChkAon)) add(CHKAON);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTof", SldTof)) add(SLDTOF);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTmp", SldTmp)) add(SLDTMP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFan", numFPupFan)) add(NUMFPUPFAN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldFmd", SldFmd)) add(SLDFMD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldVdd", SldVdd)) add(SLDVDD);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVd2", ChkVd2)) add(CHKVD2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldVrf", SldVrf)) add(SLDVRF);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "UpdAsl", UpdAsl)) add(UPDASL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldAmo", SldAmo)) add(SLDAMO);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkAad", ChkAad)) add(CHKAAD);
	};

	return basefound;
};

void PnlIdecScfQcd::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfQcd";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfQcd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfLam", TxfLam);
		writeStringAttr(wr, itemtag, "sref", "TxfDlm", TxfDlm);
		writeBoolAttr(wr, itemtag, "sref", "ChkAon", ChkAon);
		writeDoubleAttr(wr, itemtag, "sref", "SldTof", SldTof);
		writeDoubleAttr(wr, itemtag, "sref", "SldTmp", SldTmp);
		writeUintAttr(wr, itemtag, "sref", "numFPupFan", numFPupFan);
		writeDoubleAttr(wr, itemtag, "sref", "SldFmd", SldFmd);
		writeDoubleAttr(wr, itemtag, "sref", "SldVdd", SldVdd);
		writeBoolAttr(wr, itemtag, "sref", "ChkVd2", ChkVd2);
		writeDoubleAttr(wr, itemtag, "sref", "SldVrf", SldVrf);
		writeIntAttr(wr, itemtag, "sref", "UpdAsl", UpdAsl);
		writeDoubleAttr(wr, itemtag, "sref", "SldAmo", SldAmo);
		writeBoolAttr(wr, itemtag, "sref", "ChkAad", ChkAad);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfQcd::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfLam.compare(comp->TxfLam) == 0) insert(items, TXFLAM);
	if (TxfDlm.compare(comp->TxfDlm) == 0) insert(items, TXFDLM);
	if (ChkAon == comp->ChkAon) insert(items, CHKAON);
	if (compareDouble(SldTof, comp->SldTof) < 1.0e-4) insert(items, SLDTOF);
	if (compareDouble(SldTmp, comp->SldTmp) < 1.0e-4) insert(items, SLDTMP);
	if (numFPupFan == comp->numFPupFan) insert(items, NUMFPUPFAN);
	if (compareDouble(SldFmd, comp->SldFmd) < 1.0e-4) insert(items, SLDFMD);
	if (compareDouble(SldVdd, comp->SldVdd) < 1.0e-4) insert(items, SLDVDD);
	if (ChkVd2 == comp->ChkVd2) insert(items, CHKVD2);
	if (compareDouble(SldVrf, comp->SldVrf) < 1.0e-4) insert(items, SLDVRF);
	if (UpdAsl == comp->UpdAsl) insert(items, UPDASL);
	if (compareDouble(SldAmo, comp->SldAmo) < 1.0e-4) insert(items, SLDAMO);
	if (ChkAad == comp->ChkAad) insert(items, CHKAAD);

	return(items);
};

set<uint> PnlIdecScfQcd::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFLAM, TXFDLM, CHKAON, SLDTOF, SLDTMP, NUMFPUPFAN, SLDFMD, SLDVDD, CHKVD2, SLDVRF, UPDASL, SLDAMO, CHKAAD};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfQcd::ContInf
 ******************************************************************************/

PnlIdecScfQcd::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

bool PnlIdecScfQcd::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfQcd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfQcd";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
	};

	return basefound;
};

set<uint> PnlIdecScfQcd::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecScfQcd::ContInf::diff(
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
 class PnlIdecScfQcd::StatApp
 ******************************************************************************/

PnlIdecScfQcd::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecScfQcd::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScfQcd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScfQcd";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecScfQcd::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecScfQcd::StatApp::diff(
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
 class PnlIdecScfQcd::StatShr
 ******************************************************************************/

PnlIdecScfQcd::StatShr::StatShr(
			const bool TxfLamActive
			, const bool TxfDlmActive
			, const bool ChkAonActive
			, const bool SldTofActive
			, const double SldTofMin
			, const double SldTofMax
			, const double SldTofRast
			, const bool SldTmpActive
			, const double SldTmpMin
			, const double SldTmpMax
			, const double SldTmpRast
			, const bool PupFanActive
			, const bool SldFmdActive
			, const double SldFmdMin
			, const double SldFmdMax
			, const double SldFmdRast
			, const bool SldVddActive
			, const double SldVddMin
			, const double SldVddMax
			, const double SldVddRast
			, const bool ChkVd2Active
			, const bool SldVrfActive
			, const double SldVrfMin
			, const double SldVrfMax
			, const double SldVrfRast
			, const bool UpdAslActive
			, const int UpdAslMin
			, const int UpdAslMax
			, const bool SldAmoActive
			, const double SldAmoMin
			, const double SldAmoMax
			, const double SldAmoRast
			, const bool ChkAadActive
		) : Block() {
	this->TxfLamActive = TxfLamActive;
	this->TxfDlmActive = TxfDlmActive;
	this->ChkAonActive = ChkAonActive;
	this->SldTofActive = SldTofActive;
	this->SldTofMin = SldTofMin;
	this->SldTofMax = SldTofMax;
	this->SldTofRast = SldTofRast;
	this->SldTmpActive = SldTmpActive;
	this->SldTmpMin = SldTmpMin;
	this->SldTmpMax = SldTmpMax;
	this->SldTmpRast = SldTmpRast;
	this->PupFanActive = PupFanActive;
	this->SldFmdActive = SldFmdActive;
	this->SldFmdMin = SldFmdMin;
	this->SldFmdMax = SldFmdMax;
	this->SldFmdRast = SldFmdRast;
	this->SldVddActive = SldVddActive;
	this->SldVddMin = SldVddMin;
	this->SldVddMax = SldVddMax;
	this->SldVddRast = SldVddRast;
	this->ChkVd2Active = ChkVd2Active;
	this->SldVrfActive = SldVrfActive;
	this->SldVrfMin = SldVrfMin;
	this->SldVrfMax = SldVrfMax;
	this->SldVrfRast = SldVrfRast;
	this->UpdAslActive = UpdAslActive;
	this->UpdAslMin = UpdAslMin;
	this->UpdAslMax = UpdAslMax;
	this->SldAmoActive = SldAmoActive;
	this->SldAmoMin = SldAmoMin;
	this->SldAmoMax = SldAmoMax;
	this->SldAmoRast = SldAmoRast;
	this->ChkAadActive = ChkAadActive;

	mask = {TXFLAMACTIVE, TXFDLMACTIVE, CHKAONACTIVE, SLDTOFACTIVE, SLDTOFMIN, SLDTOFMAX, SLDTOFRAST, SLDTMPACTIVE, SLDTMPMIN, SLDTMPMAX, SLDTMPRAST, PUPFANACTIVE, SLDFMDACTIVE, SLDFMDMIN, SLDFMDMAX, SLDFMDRAST, SLDVDDACTIVE, SLDVDDMIN, SLDVDDMAX, SLDVDDRAST, CHKVD2ACTIVE, SLDVRFACTIVE, SLDVRFMIN, SLDVRFMAX, SLDVRFRAST, UPDASLACTIVE, UPDASLMIN, UPDASLMAX, SLDAMOACTIVE, SLDAMOMIN, SLDAMOMAX, SLDAMORAST, CHKAADACTIVE};
};

bool PnlIdecScfQcd::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfQcd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfQcd";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfLamActive", TxfLamActive)) add(TXFLAMACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfDlmActive", TxfDlmActive)) add(TXFDLMACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkAonActive", ChkAonActive)) add(CHKAONACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTofActive", SldTofActive)) add(SLDTOFACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTofMin", SldTofMin)) add(SLDTOFMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTofMax", SldTofMax)) add(SLDTOFMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTofRast", SldTofRast)) add(SLDTOFRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTmpActive", SldTmpActive)) add(SLDTMPACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTmpMin", SldTmpMin)) add(SLDTMPMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTmpMax", SldTmpMax)) add(SLDTMPMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTmpRast", SldTmpRast)) add(SLDTMPRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupFanActive", PupFanActive)) add(PUPFANACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFmdActive", SldFmdActive)) add(SLDFMDACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFmdMin", SldFmdMin)) add(SLDFMDMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFmdMax", SldFmdMax)) add(SLDFMDMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFmdRast", SldFmdRast)) add(SLDFMDRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVddActive", SldVddActive)) add(SLDVDDACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVddMin", SldVddMin)) add(SLDVDDMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVddMax", SldVddMax)) add(SLDVDDMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVddRast", SldVddRast)) add(SLDVDDRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkVd2Active", ChkVd2Active)) add(CHKVD2ACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVrfActive", SldVrfActive)) add(SLDVRFACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVrfMin", SldVrfMin)) add(SLDVRFMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVrfMax", SldVrfMax)) add(SLDVRFMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldVrfRast", SldVrfRast)) add(SLDVRFRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdAslActive", UpdAslActive)) add(UPDASLACTIVE);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdAslMin", UpdAslMin)) add(UPDASLMIN);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdAslMax", UpdAslMax)) add(UPDASLMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldAmoActive", SldAmoActive)) add(SLDAMOACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldAmoMin", SldAmoMin)) add(SLDAMOMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldAmoMax", SldAmoMax)) add(SLDAMOMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldAmoRast", SldAmoRast)) add(SLDAMORAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkAadActive", ChkAadActive)) add(CHKAADACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecScfQcd::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxfLamActive == comp->TxfLamActive) insert(items, TXFLAMACTIVE);
	if (TxfDlmActive == comp->TxfDlmActive) insert(items, TXFDLMACTIVE);
	if (ChkAonActive == comp->ChkAonActive) insert(items, CHKAONACTIVE);
	if (SldTofActive == comp->SldTofActive) insert(items, SLDTOFACTIVE);
	if (compareDouble(SldTofMin, comp->SldTofMin) < 1.0e-4) insert(items, SLDTOFMIN);
	if (compareDouble(SldTofMax, comp->SldTofMax) < 1.0e-4) insert(items, SLDTOFMAX);
	if (compareDouble(SldTofRast, comp->SldTofRast) < 1.0e-4) insert(items, SLDTOFRAST);
	if (SldTmpActive == comp->SldTmpActive) insert(items, SLDTMPACTIVE);
	if (compareDouble(SldTmpMin, comp->SldTmpMin) < 1.0e-4) insert(items, SLDTMPMIN);
	if (compareDouble(SldTmpMax, comp->SldTmpMax) < 1.0e-4) insert(items, SLDTMPMAX);
	if (compareDouble(SldTmpRast, comp->SldTmpRast) < 1.0e-4) insert(items, SLDTMPRAST);
	if (PupFanActive == comp->PupFanActive) insert(items, PUPFANACTIVE);
	if (SldFmdActive == comp->SldFmdActive) insert(items, SLDFMDACTIVE);
	if (compareDouble(SldFmdMin, comp->SldFmdMin) < 1.0e-4) insert(items, SLDFMDMIN);
	if (compareDouble(SldFmdMax, comp->SldFmdMax) < 1.0e-4) insert(items, SLDFMDMAX);
	if (compareDouble(SldFmdRast, comp->SldFmdRast) < 1.0e-4) insert(items, SLDFMDRAST);
	if (SldVddActive == comp->SldVddActive) insert(items, SLDVDDACTIVE);
	if (compareDouble(SldVddMin, comp->SldVddMin) < 1.0e-4) insert(items, SLDVDDMIN);
	if (compareDouble(SldVddMax, comp->SldVddMax) < 1.0e-4) insert(items, SLDVDDMAX);
	if (compareDouble(SldVddRast, comp->SldVddRast) < 1.0e-4) insert(items, SLDVDDRAST);
	if (ChkVd2Active == comp->ChkVd2Active) insert(items, CHKVD2ACTIVE);
	if (SldVrfActive == comp->SldVrfActive) insert(items, SLDVRFACTIVE);
	if (compareDouble(SldVrfMin, comp->SldVrfMin) < 1.0e-4) insert(items, SLDVRFMIN);
	if (compareDouble(SldVrfMax, comp->SldVrfMax) < 1.0e-4) insert(items, SLDVRFMAX);
	if (compareDouble(SldVrfRast, comp->SldVrfRast) < 1.0e-4) insert(items, SLDVRFRAST);
	if (UpdAslActive == comp->UpdAslActive) insert(items, UPDASLACTIVE);
	if (UpdAslMin == comp->UpdAslMin) insert(items, UPDASLMIN);
	if (UpdAslMax == comp->UpdAslMax) insert(items, UPDASLMAX);
	if (SldAmoActive == comp->SldAmoActive) insert(items, SLDAMOACTIVE);
	if (compareDouble(SldAmoMin, comp->SldAmoMin) < 1.0e-4) insert(items, SLDAMOMIN);
	if (compareDouble(SldAmoMax, comp->SldAmoMax) < 1.0e-4) insert(items, SLDAMOMAX);
	if (compareDouble(SldAmoRast, comp->SldAmoRast) < 1.0e-4) insert(items, SLDAMORAST);
	if (ChkAadActive == comp->ChkAadActive) insert(items, CHKAADACTIVE);

	return(items);
};

set<uint> PnlIdecScfQcd::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFLAMACTIVE, TXFDLMACTIVE, CHKAONACTIVE, SLDTOFACTIVE, SLDTOFMIN, SLDTOFMAX, SLDTOFRAST, SLDTMPACTIVE, SLDTMPMIN, SLDTMPMAX, SLDTMPRAST, PUPFANACTIVE, SLDFMDACTIVE, SLDFMDMIN, SLDFMDMAX, SLDFMDRAST, SLDVDDACTIVE, SLDVDDMIN, SLDVDDMAX, SLDVDDRAST, CHKVD2ACTIVE, SLDVRFACTIVE, SLDVRFMIN, SLDVRFMAX, SLDVRFRAST, UPDASLACTIVE, UPDASLMIN, UPDASLMAX, SLDAMOACTIVE, SLDAMOMIN, SLDAMOMAX, SLDAMORAST, CHKAADACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfQcd::Tag
 ******************************************************************************/

PnlIdecScfQcd::Tag::Tag(
			const string& Cpt
			, const string& CptLam
			, const string& CptDlm
			, const string& CptAon
			, const string& CptTof
			, const string& CptTmp
			, const string& CptFan
			, const string& CptFmd
			, const string& CptVdd
			, const string& CptVd2
			, const string& CptVrf
			, const string& CptAlign
			, const string& CptAsl
			, const string& CptAmo
			, const string& CptAad
		) : Block() {
	this->Cpt = Cpt;
	this->CptLam = CptLam;
	this->CptDlm = CptDlm;
	this->CptAon = CptAon;
	this->CptTof = CptTof;
	this->CptTmp = CptTmp;
	this->CptFan = CptFan;
	this->CptFmd = CptFmd;
	this->CptVdd = CptVdd;
	this->CptVd2 = CptVd2;
	this->CptVrf = CptVrf;
	this->CptAlign = CptAlign;
	this->CptAsl = CptAsl;
	this->CptAmo = CptAmo;
	this->CptAad = CptAad;

	mask = {CPT, CPTLAM, CPTDLM, CPTAON, CPTTOF, CPTTMP, CPTFAN, CPTFMD, CPTVDD, CPTVD2, CPTVRF, CPTALIGN, CPTASL, CPTAMO, CPTAAD};
};

bool PnlIdecScfQcd::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfQcd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfQcd";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptLam", CptLam)) add(CPTLAM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptDlm", CptDlm)) add(CPTDLM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAon", CptAon)) add(CPTAON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTof", CptTof)) add(CPTTOF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTmp", CptTmp)) add(CPTTMP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFan", CptFan)) add(CPTFAN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFmd", CptFmd)) add(CPTFMD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVdd", CptVdd)) add(CPTVDD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVd2", CptVd2)) add(CPTVD2);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVrf", CptVrf)) add(CPTVRF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAlign", CptAlign)) add(CPTALIGN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAsl", CptAsl)) add(CPTASL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAmo", CptAmo)) add(CPTAMO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAad", CptAad)) add(CPTAAD);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfQcd::DpchAppData
 ******************************************************************************/

PnlIdecScfQcd::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFQCDDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecScfQcd::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfQcd::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfQcdData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfQcd::DpchAppDo
 ******************************************************************************/

PnlIdecScfQcd::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFQCDDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfQcd::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfQcd::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfQcdDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfQcd::DpchEngData
 ******************************************************************************/

PnlIdecScfQcd::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFQCDDATA) {
	feedFPupFan.tag = "FeedFPupFan";
};

string PnlIdecScfQcd::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPFAN)) ss.push_back("feedFPupFan");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfQcd::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfQcdData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupFan.readXML(docctx, basexpath, true)) add(FEEDFPUPFAN);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupFan.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

