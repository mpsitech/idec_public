/**
  * \file PnlIdecIaqLive.cpp
  * API code for job PnlIdecIaqLive (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecIaqLive.h"

/******************************************************************************
 class PnlIdecIaqLive::VecVDo
 ******************************************************************************/

uint PnlIdecIaqLive::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "butsnapclick") return BUTSNAPCLICK;
	else if (s == "butrecclick") return BUTRECCLICK;
	else if (s == "butplayclick") return BUTPLAYCLICK;
	else if (s == "butstopclick") return BUTSTOPCLICK;

	return(0);
};

string PnlIdecIaqLive::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTSNAPCLICK) return("ButSnapClick");
	else if (ix == BUTRECCLICK) return("ButRecClick");
	else if (ix == BUTPLAYCLICK) return("ButPlayClick");
	else if (ix == BUTSTOPCLICK) return("ButStopClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqLive::VecVSge
 ******************************************************************************/

uint PnlIdecIaqLive::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alrgum") return ALRGUM;

	return(0);
};

string PnlIdecIaqLive::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRGUM) return("alrgum");

	return("");
};

/******************************************************************************
 class PnlIdecIaqLive::VecVSource
 ******************************************************************************/

uint PnlIdecIaqLive::VecVSource::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "visl") return VISL;
	else if (s == "visr") return VISR;
	else if (s == "lwir") return LWIR;
	else if (s == "stereo") return STEREO;
	else if (s == "fusion") return FUSION;

	return(0);
};

string PnlIdecIaqLive::VecVSource::getSref(
			const uint ix
		) {
	if (ix == VISL) return("visl");
	else if (ix == VISR) return("visr");
	else if (ix == LWIR) return("lwir");
	else if (ix == STEREO) return("stereo");
	else if (ix == FUSION) return("fusion");

	return("");
};

/******************************************************************************
 class PnlIdecIaqLive::ContIac
 ******************************************************************************/

PnlIdecIaqLive::ContIac::ContIac(
			const uint numFPupSrc
			, const uint numFPupRes
			, const bool ChkGrs
			, const double SldFrr
			, const double SldExt
		) : Block() {
	this->numFPupSrc = numFPupSrc;
	this->numFPupRes = numFPupRes;
	this->ChkGrs = ChkGrs;
	this->SldFrr = SldFrr;
	this->SldExt = SldExt;

	mask = {NUMFPUPSRC, NUMFPUPRES, CHKGRS, SLDFRR, SLDEXT};
};

bool PnlIdecIaqLive::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqLive");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqLive";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupSrc", numFPupSrc)) add(NUMFPUPSRC);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupRes", numFPupRes)) add(NUMFPUPRES);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkGrs", ChkGrs)) add(CHKGRS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldFrr", SldFrr)) add(SLDFRR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldExt", SldExt)) add(SLDEXT);
	};

	return basefound;
};

void PnlIdecIaqLive::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqLive";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqLive";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupSrc", numFPupSrc);
		writeUintAttr(wr, itemtag, "sref", "numFPupRes", numFPupRes);
		writeBoolAttr(wr, itemtag, "sref", "ChkGrs", ChkGrs);
		writeDoubleAttr(wr, itemtag, "sref", "SldFrr", SldFrr);
		writeDoubleAttr(wr, itemtag, "sref", "SldExt", SldExt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqLive::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupSrc == comp->numFPupSrc) insert(items, NUMFPUPSRC);
	if (numFPupRes == comp->numFPupRes) insert(items, NUMFPUPRES);
	if (ChkGrs == comp->ChkGrs) insert(items, CHKGRS);
	if (compareDouble(SldFrr, comp->SldFrr) < 1.0e-4) insert(items, SLDFRR);
	if (compareDouble(SldExt, comp->SldExt) < 1.0e-4) insert(items, SLDEXT);

	return(items);
};

set<uint> PnlIdecIaqLive::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPSRC, NUMFPUPRES, CHKGRS, SLDFRR, SLDEXT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqLive::ContInf
 ******************************************************************************/

PnlIdecIaqLive::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtSte
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtSte = TxtSte;

	mask = {BUTMASTERON, TXTSTE};
};

bool PnlIdecIaqLive::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecIaqLive");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecIaqLive";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSte", TxtSte)) add(TXTSTE);
	};

	return basefound;
};

set<uint> PnlIdecIaqLive::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtSte.compare(comp->TxtSte) == 0) insert(items, TXTSTE);

	return(items);
};

set<uint> PnlIdecIaqLive::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTSTE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqLive::StatShr
 ******************************************************************************/

PnlIdecIaqLive::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const uint CusImgHeight
			, const bool ChkGrsAvail
			, const bool SldConAvail
			, const double SldConMin
			, const double SldConMax
			, const bool SldBriAvail
			, const double SldBriMin
			, const double SldBriMax
			, const bool SldFrrActive
			, const double SldFrrMin
			, const double SldFrrMax
			, const double SldFrrRast
			, const bool SldExtAvail
			, const bool SldExtActive
			, const double SldExtMin
			, const double SldExtMax
			, const double SldExtRast
			, const bool ButPlayActive
			, const bool ButStopActive
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->CusImgHeight = CusImgHeight;
	this->ChkGrsAvail = ChkGrsAvail;
	this->SldConAvail = SldConAvail;
	this->SldConMin = SldConMin;
	this->SldConMax = SldConMax;
	this->SldBriAvail = SldBriAvail;
	this->SldBriMin = SldBriMin;
	this->SldBriMax = SldBriMax;
	this->SldFrrActive = SldFrrActive;
	this->SldFrrMin = SldFrrMin;
	this->SldFrrMax = SldFrrMax;
	this->SldFrrRast = SldFrrRast;
	this->SldExtAvail = SldExtAvail;
	this->SldExtActive = SldExtActive;
	this->SldExtMin = SldExtMin;
	this->SldExtMax = SldExtMax;
	this->SldExtRast = SldExtRast;
	this->ButPlayActive = ButPlayActive;
	this->ButStopActive = ButStopActive;

	mask = {IXIDECVEXPSTATE, CUSIMGHEIGHT, CHKGRSAVAIL, SLDCONAVAIL, SLDCONMIN, SLDCONMAX, SLDBRIAVAIL, SLDBRIMIN, SLDBRIMAX, SLDFRRACTIVE, SLDFRRMIN, SLDFRRMAX, SLDFRRRAST, SLDEXTAVAIL, SLDEXTACTIVE, SLDEXTMIN, SLDEXTMAX, SLDEXTRAST, BUTPLAYACTIVE, BUTSTOPACTIVE};
};

bool PnlIdecIaqLive::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecIaqLive");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecIaqLive";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "CusImgHeight", CusImgHeight)) add(CUSIMGHEIGHT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ChkGrsAvail", ChkGrsAvail)) add(CHKGRSAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldConAvail", SldConAvail)) add(SLDCONAVAIL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldConMin", SldConMin)) add(SLDCONMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldConMax", SldConMax)) add(SLDCONMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldBriAvail", SldBriAvail)) add(SLDBRIAVAIL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldBriMin", SldBriMin)) add(SLDBRIMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldBriMax", SldBriMax)) add(SLDBRIMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFrrActive", SldFrrActive)) add(SLDFRRACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFrrMin", SldFrrMin)) add(SLDFRRMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFrrMax", SldFrrMax)) add(SLDFRRMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldFrrRast", SldFrrRast)) add(SLDFRRRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldExtAvail", SldExtAvail)) add(SLDEXTAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldExtActive", SldExtActive)) add(SLDEXTACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldExtMin", SldExtMin)) add(SLDEXTMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldExtMax", SldExtMax)) add(SLDEXTMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldExtRast", SldExtRast)) add(SLDEXTRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPlayActive", ButPlayActive)) add(BUTPLAYACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButStopActive", ButStopActive)) add(BUTSTOPACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecIaqLive::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (CusImgHeight == comp->CusImgHeight) insert(items, CUSIMGHEIGHT);
	if (ChkGrsAvail == comp->ChkGrsAvail) insert(items, CHKGRSAVAIL);
	if (SldConAvail == comp->SldConAvail) insert(items, SLDCONAVAIL);
	if (compareDouble(SldConMin, comp->SldConMin) < 1.0e-4) insert(items, SLDCONMIN);
	if (compareDouble(SldConMax, comp->SldConMax) < 1.0e-4) insert(items, SLDCONMAX);
	if (SldBriAvail == comp->SldBriAvail) insert(items, SLDBRIAVAIL);
	if (compareDouble(SldBriMin, comp->SldBriMin) < 1.0e-4) insert(items, SLDBRIMIN);
	if (compareDouble(SldBriMax, comp->SldBriMax) < 1.0e-4) insert(items, SLDBRIMAX);
	if (SldFrrActive == comp->SldFrrActive) insert(items, SLDFRRACTIVE);
	if (compareDouble(SldFrrMin, comp->SldFrrMin) < 1.0e-4) insert(items, SLDFRRMIN);
	if (compareDouble(SldFrrMax, comp->SldFrrMax) < 1.0e-4) insert(items, SLDFRRMAX);
	if (compareDouble(SldFrrRast, comp->SldFrrRast) < 1.0e-4) insert(items, SLDFRRRAST);
	if (SldExtAvail == comp->SldExtAvail) insert(items, SLDEXTAVAIL);
	if (SldExtActive == comp->SldExtActive) insert(items, SLDEXTACTIVE);
	if (compareDouble(SldExtMin, comp->SldExtMin) < 1.0e-4) insert(items, SLDEXTMIN);
	if (compareDouble(SldExtMax, comp->SldExtMax) < 1.0e-4) insert(items, SLDEXTMAX);
	if (compareDouble(SldExtRast, comp->SldExtRast) < 1.0e-4) insert(items, SLDEXTRAST);
	if (ButPlayActive == comp->ButPlayActive) insert(items, BUTPLAYACTIVE);
	if (ButStopActive == comp->ButStopActive) insert(items, BUTSTOPACTIVE);

	return(items);
};

set<uint> PnlIdecIaqLive::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, CUSIMGHEIGHT, CHKGRSAVAIL, SLDCONAVAIL, SLDCONMIN, SLDCONMAX, SLDBRIAVAIL, SLDBRIMIN, SLDBRIMAX, SLDFRRACTIVE, SLDFRRMIN, SLDFRRMAX, SLDFRRRAST, SLDEXTAVAIL, SLDEXTACTIVE, SLDEXTMIN, SLDEXTMAX, SLDEXTRAST, BUTPLAYACTIVE, BUTSTOPACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqLive::Tag
 ******************************************************************************/

PnlIdecIaqLive::Tag::Tag(
			const string& Cpt
			, const string& CptSrc
			, const string& CptRes
			, const string& CptGrs
			, const string& CptCon
			, const string& CptBri
			, const string& CptFrr
			, const string& CptExt
			, const string& CptSte
		) : Block() {
	this->Cpt = Cpt;
	this->CptSrc = CptSrc;
	this->CptRes = CptRes;
	this->CptGrs = CptGrs;
	this->CptCon = CptCon;
	this->CptBri = CptBri;
	this->CptFrr = CptFrr;
	this->CptExt = CptExt;
	this->CptSte = CptSte;

	mask = {CPT, CPTSRC, CPTRES, CPTGRS, CPTCON, CPTBRI, CPTFRR, CPTEXT, CPTSTE};
};

bool PnlIdecIaqLive::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecIaqLive");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecIaqLive";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSrc", CptSrc)) add(CPTSRC);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRes", CptRes)) add(CPTRES);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptGrs", CptGrs)) add(CPTGRS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptCon", CptCon)) add(CPTCON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptBri", CptBri)) add(CPTBRI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFrr", CptFrr)) add(CPTFRR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptExt", CptExt)) add(CPTEXT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSte", CptSte)) add(CPTSTE);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecIaqLive::DpchAppData
 ******************************************************************************/

PnlIdecIaqLive::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQLIVEDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecIaqLive::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqLiveData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqLive::DpchAppDo
 ******************************************************************************/

PnlIdecIaqLive::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQLIVEDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecIaqLive::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqLiveDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqLive::DpchEngData
 ******************************************************************************/

PnlIdecIaqLive::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQLIVEDATA) {
	feedFPupRes.tag = "FeedFPupRes";
	feedFPupSrc.tag = "FeedFPupSrc";
};

string PnlIdecIaqLive::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPRES)) ss.push_back("feedFPupRes");
	if (has(FEEDFPUPSRC)) ss.push_back("feedFPupSrc");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqLiveData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupRes.readXML(docctx, basexpath, true)) add(FEEDFPUPRES);
		if (feedFPupSrc.readXML(docctx, basexpath, true)) add(FEEDFPUPSRC);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupRes.clear();
		feedFPupSrc.clear();
		statshr = StatShr();
		tag = Tag();
	};
};

/******************************************************************************
 class PnlIdecIaqLive::DpchEngLive
 ******************************************************************************/

PnlIdecIaqLive::DpchEngLive::DpchEngLive() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQLIVELIVE) {
};

string PnlIdecIaqLive::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(RGB)) ss.push_back("rgb");
	if (has(RED)) ss.push_back("red");
	if (has(GREEN)) ss.push_back("green");
	if (has(BLUE)) ss.push_back("blue");
	if (has(GRAY)) ss.push_back("gray");
	if (has(DEPTH)) ss.push_back("depth");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchEngLive::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqLiveLive");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (extractUtinyintvecUclc(docctx, basexpath, "rgb", "", rgb)) add(RGB);
		if (extractUtinyintvecUclc(docctx, basexpath, "red", "", red)) add(RED);
		if (extractUtinyintvecUclc(docctx, basexpath, "green", "", green)) add(GREEN);
		if (extractUtinyintvecUclc(docctx, basexpath, "blue", "", blue)) add(BLUE);
		if (extractUsmallintvecUclc(docctx, basexpath, "gray", "", gray)) add(GRAY);
		if (extractFloatvecUclc(docctx, basexpath, "depth", "", depth)) add(DEPTH);
	} else {
		continf = ContInf();
	};
};

