/**
  * \file PnlIdecScfTrigger.cpp
  * API code for job PnlIdecScfTrigger (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfTrigger.h"

/******************************************************************************
 class PnlIdecScfTrigger::VecVDo
 ******************************************************************************/

uint PnlIdecScfTrigger::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfTrigger::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfTrigger::ContIac
 ******************************************************************************/

PnlIdecScfTrigger::ContIac::ContIac(
			const double SldRdl
			, const double SldIdl
			, const double SldQdl
		) : Block() {
	this->SldRdl = SldRdl;
	this->SldIdl = SldIdl;
	this->SldQdl = SldQdl;

	mask = {SLDRDL, SLDIDL, SLDQDL};
};

bool PnlIdecScfTrigger::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfTrigger";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldRdl", SldRdl)) add(SLDRDL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldIdl", SldIdl)) add(SLDIDL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldQdl", SldQdl)) add(SLDQDL);
	};

	return basefound;
};

void PnlIdecScfTrigger::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfTrigger";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "SldRdl", SldRdl);
		writeDoubleAttr(wr, itemtag, "sref", "SldIdl", SldIdl);
		writeDoubleAttr(wr, itemtag, "sref", "SldQdl", SldQdl);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfTrigger::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (compareDouble(SldRdl, comp->SldRdl) < 1.0e-4) insert(items, SLDRDL);
	if (compareDouble(SldIdl, comp->SldIdl) < 1.0e-4) insert(items, SLDIDL);
	if (compareDouble(SldQdl, comp->SldQdl) < 1.0e-4) insert(items, SLDQDL);

	return(items);
};

set<uint> PnlIdecScfTrigger::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDRDL, SLDIDL, SLDQDL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfTrigger::ContInf
 ******************************************************************************/

PnlIdecScfTrigger::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

bool PnlIdecScfTrigger::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfTrigger";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
	};

	return basefound;
};

set<uint> PnlIdecScfTrigger::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecScfTrigger::ContInf::diff(
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
 class PnlIdecScfTrigger::StatApp
 ******************************************************************************/

PnlIdecScfTrigger::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecScfTrigger::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScfTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScfTrigger";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecScfTrigger::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecScfTrigger::StatApp::diff(
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
 class PnlIdecScfTrigger::StatShr
 ******************************************************************************/

PnlIdecScfTrigger::StatShr::StatShr(
			const bool SldRdlActive
			, const double SldRdlMin
			, const double SldRdlMax
			, const double SldRdlRast
			, const bool SldIdlActive
			, const double SldIdlMin
			, const double SldIdlMax
			, const double SldIdlRast
			, const bool SldQdlActive
			, const double SldQdlMin
			, const double SldQdlMax
			, const double SldQdlRast
		) : Block() {
	this->SldRdlActive = SldRdlActive;
	this->SldRdlMin = SldRdlMin;
	this->SldRdlMax = SldRdlMax;
	this->SldRdlRast = SldRdlRast;
	this->SldIdlActive = SldIdlActive;
	this->SldIdlMin = SldIdlMin;
	this->SldIdlMax = SldIdlMax;
	this->SldIdlRast = SldIdlRast;
	this->SldQdlActive = SldQdlActive;
	this->SldQdlMin = SldQdlMin;
	this->SldQdlMax = SldQdlMax;
	this->SldQdlRast = SldQdlRast;

	mask = {SLDRDLACTIVE, SLDRDLMIN, SLDRDLMAX, SLDRDLRAST, SLDIDLACTIVE, SLDIDLMIN, SLDIDLMAX, SLDIDLRAST, SLDQDLACTIVE, SLDQDLMIN, SLDQDLMAX, SLDQDLRAST};
};

bool PnlIdecScfTrigger::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfTrigger";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldRdlActive", SldRdlActive)) add(SLDRDLACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldRdlMin", SldRdlMin)) add(SLDRDLMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldRdlMax", SldRdlMax)) add(SLDRDLMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldRdlRast", SldRdlRast)) add(SLDRDLRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldIdlActive", SldIdlActive)) add(SLDIDLACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldIdlMin", SldIdlMin)) add(SLDIDLMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldIdlMax", SldIdlMax)) add(SLDIDLMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldIdlRast", SldIdlRast)) add(SLDIDLRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldQdlActive", SldQdlActive)) add(SLDQDLACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldQdlMin", SldQdlMin)) add(SLDQDLMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldQdlMax", SldQdlMax)) add(SLDQDLMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldQdlRast", SldQdlRast)) add(SLDQDLRAST);
	};

	return basefound;
};

set<uint> PnlIdecScfTrigger::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (SldRdlActive == comp->SldRdlActive) insert(items, SLDRDLACTIVE);
	if (compareDouble(SldRdlMin, comp->SldRdlMin) < 1.0e-4) insert(items, SLDRDLMIN);
	if (compareDouble(SldRdlMax, comp->SldRdlMax) < 1.0e-4) insert(items, SLDRDLMAX);
	if (compareDouble(SldRdlRast, comp->SldRdlRast) < 1.0e-4) insert(items, SLDRDLRAST);
	if (SldIdlActive == comp->SldIdlActive) insert(items, SLDIDLACTIVE);
	if (compareDouble(SldIdlMin, comp->SldIdlMin) < 1.0e-4) insert(items, SLDIDLMIN);
	if (compareDouble(SldIdlMax, comp->SldIdlMax) < 1.0e-4) insert(items, SLDIDLMAX);
	if (compareDouble(SldIdlRast, comp->SldIdlRast) < 1.0e-4) insert(items, SLDIDLRAST);
	if (SldQdlActive == comp->SldQdlActive) insert(items, SLDQDLACTIVE);
	if (compareDouble(SldQdlMin, comp->SldQdlMin) < 1.0e-4) insert(items, SLDQDLMIN);
	if (compareDouble(SldQdlMax, comp->SldQdlMax) < 1.0e-4) insert(items, SLDQDLMAX);
	if (compareDouble(SldQdlRast, comp->SldQdlRast) < 1.0e-4) insert(items, SLDQDLRAST);

	return(items);
};

set<uint> PnlIdecScfTrigger::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDRDLACTIVE, SLDRDLMIN, SLDRDLMAX, SLDRDLRAST, SLDIDLACTIVE, SLDIDLMIN, SLDIDLMAX, SLDIDLRAST, SLDQDLACTIVE, SLDQDLMIN, SLDQDLMAX, SLDQDLRAST};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfTrigger::Tag
 ******************************************************************************/

PnlIdecScfTrigger::Tag::Tag(
			const string& Cpt
			, const string& CptRef
			, const string& CptRdl
			, const string& CptIdl
			, const string& CptQdl
		) : Block() {
	this->Cpt = Cpt;
	this->CptRef = CptRef;
	this->CptRdl = CptRdl;
	this->CptIdl = CptIdl;
	this->CptQdl = CptQdl;

	mask = {CPT, CPTREF, CPTRDL, CPTIDL, CPTQDL};
};

bool PnlIdecScfTrigger::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfTrigger";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRef", CptRef)) add(CPTREF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRdl", CptRdl)) add(CPTRDL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIdl", CptIdl)) add(CPTIDL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQdl", CptQdl)) add(CPTQDL);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfTrigger::DpchAppData
 ******************************************************************************/

PnlIdecScfTrigger::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFTRIGGERDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecScfTrigger::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfTrigger::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfTriggerData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfTrigger::DpchAppDo
 ******************************************************************************/

PnlIdecScfTrigger::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFTRIGGERDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfTrigger::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfTrigger::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfTriggerDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfTrigger::DpchEngData
 ******************************************************************************/

PnlIdecScfTrigger::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFTRIGGERDATA) {
};

string PnlIdecScfTrigger::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfTrigger::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfTriggerData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

