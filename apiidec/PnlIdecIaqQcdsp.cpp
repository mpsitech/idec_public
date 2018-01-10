/**
  * \file PnlIdecIaqQcdsp.cpp
  * API code for job PnlIdecIaqQcdsp (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecIaqQcdsp.h"

/******************************************************************************
 class PnlIdecIaqQcdsp::VecVDo
 ******************************************************************************/

uint PnlIdecIaqQcdsp::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecIaqQcdsp::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqQcdsp::VecVMode
 ******************************************************************************/

uint PnlIdecIaqQcdsp::VecVMode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "off") return OFF;
	else if (s == "pix") return PIX;
	else if (s == "frm") return FRM;

	return(0);
};

string PnlIdecIaqQcdsp::VecVMode::getSref(
			const uint ix
		) {
	if (ix == OFF) return("off");
	else if (ix == PIX) return("pix");
	else if (ix == FRM) return("frm");

	return("");
};

/******************************************************************************
 class PnlIdecIaqQcdsp::ContIac
 ******************************************************************************/

PnlIdecIaqQcdsp::ContIac::ContIac(
			const uint numFPupMod
			, const double SldTin
			, const usmallint CusImgPxs
		) : Block() {
	this->numFPupMod = numFPupMod;
	this->SldTin = SldTin;
	this->CusImgPxs = CusImgPxs;

	mask = {NUMFPUPMOD, SLDTIN, CUSIMGPXS};
};

bool PnlIdecIaqQcdsp::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqQcdsp");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqQcdsp";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupMod", numFPupMod)) add(NUMFPUPMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTin", SldTin)) add(SLDTIN);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusImgPxs", CusImgPxs)) add(CUSIMGPXS);
	};

	return basefound;
};

void PnlIdecIaqQcdsp::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqQcdsp";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqQcdsp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupMod", numFPupMod);
		writeDoubleAttr(wr, itemtag, "sref", "SldTin", SldTin);
		writeUsmallintAttr(wr, itemtag, "sref", "CusImgPxs", CusImgPxs);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqQcdsp::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupMod == comp->numFPupMod) insert(items, NUMFPUPMOD);
	if (compareDouble(SldTin, comp->SldTin) < 1.0e-4) insert(items, SLDTIN);
	if (CusImgPxs == comp->CusImgPxs) insert(items, CUSIMGPXS);

	return(items);
};

set<uint> PnlIdecIaqQcdsp::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPMOD, SLDTIN, CUSIMGPXS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::ContInf
 ******************************************************************************/

PnlIdecIaqQcdsp::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtImgIl0
			, const string& TxtImgIl1
			, const string& TxtImgQwh
			, const string& TxtImgQhp
			, const string& TxtImgQdp
			, const string& TxtImgSiq
			, const string& TxtImgDxi
			, const string& TxtImgDyi
			, const string& TxtImgQlm
			, const string& TxtImgQdl
			, const uint numFCsiImgSte
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtImgIl0 = TxtImgIl0;
	this->TxtImgIl1 = TxtImgIl1;
	this->TxtImgQwh = TxtImgQwh;
	this->TxtImgQhp = TxtImgQhp;
	this->TxtImgQdp = TxtImgQdp;
	this->TxtImgSiq = TxtImgSiq;
	this->TxtImgDxi = TxtImgDxi;
	this->TxtImgDyi = TxtImgDyi;
	this->TxtImgQlm = TxtImgQlm;
	this->TxtImgQdl = TxtImgQdl;
	this->numFCsiImgSte = numFCsiImgSte;

	mask = {BUTMASTERON, TXTIMGIL0, TXTIMGIL1, TXTIMGQWH, TXTIMGQHP, TXTIMGQDP, TXTIMGSIQ, TXTIMGDXI, TXTIMGDYI, TXTIMGQLM, TXTIMGQDL, NUMFCSIIMGSTE};
};

bool PnlIdecIaqQcdsp::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecIaqQcdsp");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecIaqQcdsp";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgIl0", TxtImgIl0)) add(TXTIMGIL0);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgIl1", TxtImgIl1)) add(TXTIMGIL1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgQwh", TxtImgQwh)) add(TXTIMGQWH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgQhp", TxtImgQhp)) add(TXTIMGQHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgQdp", TxtImgQdp)) add(TXTIMGQDP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgSiq", TxtImgSiq)) add(TXTIMGSIQ);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgDxi", TxtImgDxi)) add(TXTIMGDXI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgDyi", TxtImgDyi)) add(TXTIMGDYI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgQlm", TxtImgQlm)) add(TXTIMGQLM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtImgQdl", TxtImgQdl)) add(TXTIMGQDL);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiImgSte", numFCsiImgSte)) add(NUMFCSIIMGSTE);
	};

	return basefound;
};

set<uint> PnlIdecIaqQcdsp::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtImgIl0.compare(comp->TxtImgIl0) == 0) insert(items, TXTIMGIL0);
	if (TxtImgIl1.compare(comp->TxtImgIl1) == 0) insert(items, TXTIMGIL1);
	if (TxtImgQwh.compare(comp->TxtImgQwh) == 0) insert(items, TXTIMGQWH);
	if (TxtImgQhp.compare(comp->TxtImgQhp) == 0) insert(items, TXTIMGQHP);
	if (TxtImgQdp.compare(comp->TxtImgQdp) == 0) insert(items, TXTIMGQDP);
	if (TxtImgSiq.compare(comp->TxtImgSiq) == 0) insert(items, TXTIMGSIQ);
	if (TxtImgDxi.compare(comp->TxtImgDxi) == 0) insert(items, TXTIMGDXI);
	if (TxtImgDyi.compare(comp->TxtImgDyi) == 0) insert(items, TXTIMGDYI);
	if (TxtImgQlm.compare(comp->TxtImgQlm) == 0) insert(items, TXTIMGQLM);
	if (TxtImgQdl.compare(comp->TxtImgQdl) == 0) insert(items, TXTIMGQDL);
	if (numFCsiImgSte == comp->numFCsiImgSte) insert(items, NUMFCSIIMGSTE);

	return(items);
};

set<uint> PnlIdecIaqQcdsp::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTIMGIL0, TXTIMGIL1, TXTIMGQWH, TXTIMGQHP, TXTIMGQDP, TXTIMGSIQ, TXTIMGDXI, TXTIMGDYI, TXTIMGQLM, TXTIMGQDL, NUMFCSIIMGSTE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::StatShr
 ******************************************************************************/

PnlIdecIaqQcdsp::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool PupModActive
			, const double SldTinMin
			, const double SldTinMax
			, const double SldTinRast
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->PupModActive = PupModActive;
	this->SldTinMin = SldTinMin;
	this->SldTinMax = SldTinMax;
	this->SldTinRast = SldTinRast;

	mask = {IXIDECVEXPSTATE, PUPMODACTIVE, SLDTINMIN, SLDTINMAX, SLDTINRAST};
};

bool PnlIdecIaqQcdsp::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecIaqQcdsp");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecIaqQcdsp";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupModActive", PupModActive)) add(PUPMODACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTinMin", SldTinMin)) add(SLDTINMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTinMax", SldTinMax)) add(SLDTINMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldTinRast", SldTinRast)) add(SLDTINRAST);
	};

	return basefound;
};

set<uint> PnlIdecIaqQcdsp::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (PupModActive == comp->PupModActive) insert(items, PUPMODACTIVE);
	if (compareDouble(SldTinMin, comp->SldTinMin) < 1.0e-4) insert(items, SLDTINMIN);
	if (compareDouble(SldTinMax, comp->SldTinMax) < 1.0e-4) insert(items, SLDTINMAX);
	if (compareDouble(SldTinRast, comp->SldTinRast) < 1.0e-4) insert(items, SLDTINRAST);

	return(items);
};

set<uint> PnlIdecIaqQcdsp::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, PUPMODACTIVE, SLDTINMIN, SLDTINMAX, SLDTINRAST};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::Tag
 ******************************************************************************/

PnlIdecIaqQcdsp::Tag::Tag(
			const string& Cpt
			, const string& CptMod
			, const string& ButImgShow
			, const string& CptTin
		) : Block() {
	this->Cpt = Cpt;
	this->CptMod = CptMod;
	this->ButImgShow = ButImgShow;
	this->CptTin = CptTin;

	mask = {CPT, CPTMOD, BUTIMGSHOW, CPTTIN};
};

bool PnlIdecIaqQcdsp::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecIaqQcdsp");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecIaqQcdsp";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMod", CptMod)) add(CPTMOD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButImgShow", ButImgShow)) add(BUTIMGSHOW);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTin", CptTin)) add(CPTTIN);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecIaqQcdsp::DpchAppData
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQQCDSPDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecIaqQcdsp::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqQcdspData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::DpchAppDo
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQQCDSPDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecIaqQcdsp::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecIaqQcdspDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::DpchEngData
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQQCDSPDATA) {
	feedFCsiImgSte.tag = "FeedFCsiImgSte";
	feedFPupMod.tag = "FeedFPupMod";
};

string PnlIdecIaqQcdsp::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIIMGSTE)) ss.push_back("feedFCsiImgSte");
	if (has(FEEDFPUPMOD)) ss.push_back("feedFPupMod");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqQcdspData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFCsiImgSte.readXML(docctx, basexpath, true)) add(FEEDFCSIIMGSTE);
		if (feedFPupMod.readXML(docctx, basexpath, true)) add(FEEDFPUPMOD);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFCsiImgSte.clear();
		feedFPupMod.clear();
		statshr = StatShr();
		tag = Tag();
	};
};

/******************************************************************************
 class PnlIdecIaqQcdsp::DpchEngLive
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchEngLive::DpchEngLive() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQQCDSPLIVE) {
};

string PnlIdecIaqQcdsp::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(TLWIR)) ss.push_back("Tlwir");
	if (has(TQCD)) ss.push_back("Tqcd");
	if (has(DELTATQCD)) ss.push_back("DeltaTqcd");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchEngLive::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecIaqQcdspLive");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (extractDoublevecUclc(docctx, basexpath, "Tlwir", "", Tlwir)) add(TLWIR);
		if (extractDoublevecUclc(docctx, basexpath, "Tqcd", "", Tqcd)) add(TQCD);
		if (extractDoublevecUclc(docctx, basexpath, "DeltaTqcd", "", DeltaTqcd)) add(DELTATQCD);
	} else {
		continf = ContInf();
	};
};

