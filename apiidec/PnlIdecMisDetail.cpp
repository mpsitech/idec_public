/**
  * \file PnlIdecMisDetail.cpp
  * API code for job PnlIdecMisDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecMisDetail.h"

/******************************************************************************
 class PnlIdecMisDetail::VecVDo
 ******************************************************************************/

uint PnlIdecMisDetail::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butsaveclick") return BUTSAVECLICK;
	else if (s == "butcryeditclick") return BUTCRYEDITCLICK;

	return(0);
};

string PnlIdecMisDetail::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTSAVECLICK) return("ButSaveClick");
	else if (ix == BUTCRYEDITCLICK) return("ButCryEditClick");

	return("");
};

/******************************************************************************
 class PnlIdecMisDetail::ContIac
 ******************************************************************************/

PnlIdecMisDetail::ContIac::ContIac(
			const string& TxfTit
			, const string& TxfSta
			, const string& TxfSto
			, const uint numFPupCry
			, const string& TxfCry
			, const string& TxfReg
			, const string& TxfMun
			, const string& TxfCmt
		) : Block() {
	this->TxfTit = TxfTit;
	this->TxfSta = TxfSta;
	this->TxfSto = TxfSto;
	this->numFPupCry = numFPupCry;
	this->TxfCry = TxfCry;
	this->TxfReg = TxfReg;
	this->TxfMun = TxfMun;
	this->TxfCmt = TxfCmt;

	mask = {TXFTIT, TXFSTA, TXFSTO, NUMFPUPCRY, TXFCRY, TXFREG, TXFMUN, TXFCMT};
};

bool PnlIdecMisDetail::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecMisDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecMisDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfTit", TxfTit)) add(TXFTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSta", TxfSta)) add(TXFSTA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSto", TxfSto)) add(TXFSTO);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupCry", numFPupCry)) add(NUMFPUPCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfCry", TxfCry)) add(TXFCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfReg", TxfReg)) add(TXFREG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfMun", TxfMun)) add(TXFMUN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfCmt", TxfCmt)) add(TXFCMT);
	};

	return basefound;
};

void PnlIdecMisDetail::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecMisDetail";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecMisDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfTit", TxfTit);
		writeStringAttr(wr, itemtag, "sref", "TxfSta", TxfSta);
		writeStringAttr(wr, itemtag, "sref", "TxfSto", TxfSto);
		writeUintAttr(wr, itemtag, "sref", "numFPupCry", numFPupCry);
		writeStringAttr(wr, itemtag, "sref", "TxfCry", TxfCry);
		writeStringAttr(wr, itemtag, "sref", "TxfReg", TxfReg);
		writeStringAttr(wr, itemtag, "sref", "TxfMun", TxfMun);
		writeStringAttr(wr, itemtag, "sref", "TxfCmt", TxfCmt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecMisDetail::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfTit.compare(comp->TxfTit) == 0) insert(items, TXFTIT);
	if (TxfSta.compare(comp->TxfSta) == 0) insert(items, TXFSTA);
	if (TxfSto.compare(comp->TxfSto) == 0) insert(items, TXFSTO);
	if (numFPupCry == comp->numFPupCry) insert(items, NUMFPUPCRY);
	if (TxfCry.compare(comp->TxfCry) == 0) insert(items, TXFCRY);
	if (TxfReg.compare(comp->TxfReg) == 0) insert(items, TXFREG);
	if (TxfMun.compare(comp->TxfMun) == 0) insert(items, TXFMUN);
	if (TxfCmt.compare(comp->TxfCmt) == 0) insert(items, TXFCMT);

	return(items);
};

set<uint> PnlIdecMisDetail::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFTIT, TXFSTA, TXFSTO, NUMFPUPCRY, TXFCRY, TXFREG, TXFMUN, TXFCMT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecMisDetail::StatApp
 ******************************************************************************/

PnlIdecMisDetail::StatApp::StatApp(
			const uint ixIdecVExpstate
			, const bool PupCryAlt
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->PupCryAlt = PupCryAlt;

	mask = {IXIDECVEXPSTATE, PUPCRYALT};
};

bool PnlIdecMisDetail::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecMisDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecMisDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupCryAlt", PupCryAlt)) add(PUPCRYALT);
	};

	return basefound;
};

set<uint> PnlIdecMisDetail::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (PupCryAlt == comp->PupCryAlt) insert(items, PUPCRYALT);

	return(items);
};

set<uint> PnlIdecMisDetail::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, PUPCRYALT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecMisDetail::StatShr
 ******************************************************************************/

PnlIdecMisDetail::StatShr::StatShr(
			const bool TxfCryValid
			, const bool ButSaveAvail
			, const bool ButSaveActive
			, const bool TxfTitActive
			, const bool TxfStaActive
			, const bool TxfStoActive
			, const bool PupCryActive
			, const bool ButCryEditAvail
			, const bool TxfRegActive
			, const bool TxfMunActive
			, const bool TxfCmtActive
		) : Block() {
	this->TxfCryValid = TxfCryValid;
	this->ButSaveAvail = ButSaveAvail;
	this->ButSaveActive = ButSaveActive;
	this->TxfTitActive = TxfTitActive;
	this->TxfStaActive = TxfStaActive;
	this->TxfStoActive = TxfStoActive;
	this->PupCryActive = PupCryActive;
	this->ButCryEditAvail = ButCryEditAvail;
	this->TxfRegActive = TxfRegActive;
	this->TxfMunActive = TxfMunActive;
	this->TxfCmtActive = TxfCmtActive;

	mask = {TXFCRYVALID, BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, PUPCRYACTIVE, BUTCRYEDITAVAIL, TXFREGACTIVE, TXFMUNACTIVE, TXFCMTACTIVE};
};

bool PnlIdecMisDetail::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecMisDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecMisDetail";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfCryValid", TxfCryValid)) add(TXFCRYVALID);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSaveAvail", ButSaveAvail)) add(BUTSAVEAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSaveActive", ButSaveActive)) add(BUTSAVEACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfTitActive", TxfTitActive)) add(TXFTITACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfStaActive", TxfStaActive)) add(TXFSTAACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfStoActive", TxfStoActive)) add(TXFSTOACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupCryActive", PupCryActive)) add(PUPCRYACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButCryEditAvail", ButCryEditAvail)) add(BUTCRYEDITAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfRegActive", TxfRegActive)) add(TXFREGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfMunActive", TxfMunActive)) add(TXFMUNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfCmtActive", TxfCmtActive)) add(TXFCMTACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecMisDetail::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxfCryValid == comp->TxfCryValid) insert(items, TXFCRYVALID);
	if (ButSaveAvail == comp->ButSaveAvail) insert(items, BUTSAVEAVAIL);
	if (ButSaveActive == comp->ButSaveActive) insert(items, BUTSAVEACTIVE);
	if (TxfTitActive == comp->TxfTitActive) insert(items, TXFTITACTIVE);
	if (TxfStaActive == comp->TxfStaActive) insert(items, TXFSTAACTIVE);
	if (TxfStoActive == comp->TxfStoActive) insert(items, TXFSTOACTIVE);
	if (PupCryActive == comp->PupCryActive) insert(items, PUPCRYACTIVE);
	if (ButCryEditAvail == comp->ButCryEditAvail) insert(items, BUTCRYEDITAVAIL);
	if (TxfRegActive == comp->TxfRegActive) insert(items, TXFREGACTIVE);
	if (TxfMunActive == comp->TxfMunActive) insert(items, TXFMUNACTIVE);
	if (TxfCmtActive == comp->TxfCmtActive) insert(items, TXFCMTACTIVE);

	return(items);
};

set<uint> PnlIdecMisDetail::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFCRYVALID, BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, PUPCRYACTIVE, BUTCRYEDITAVAIL, TXFREGACTIVE, TXFMUNACTIVE, TXFCMTACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecMisDetail::Tag
 ******************************************************************************/

PnlIdecMisDetail::Tag::Tag(
			const string& Cpt
			, const string& CptTit
			, const string& CptSta
			, const string& CptSto
			, const string& CptCry
			, const string& CptReg
			, const string& CptMun
			, const string& CptCmt
		) : Block() {
	this->Cpt = Cpt;
	this->CptTit = CptTit;
	this->CptSta = CptSta;
	this->CptSto = CptSto;
	this->CptCry = CptCry;
	this->CptReg = CptReg;
	this->CptMun = CptMun;
	this->CptCmt = CptCmt;

	mask = {CPT, CPTTIT, CPTSTA, CPTSTO, CPTCRY, CPTREG, CPTMUN, CPTCMT};
};

bool PnlIdecMisDetail::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecMisDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecMisDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTit", CptTit)) add(CPTTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSta", CptSta)) add(CPTSTA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSto", CptSto)) add(CPTSTO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptCry", CptCry)) add(CPTCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptReg", CptReg)) add(CPTREG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMun", CptMun)) add(CPTMUN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptCmt", CptCmt)) add(CPTCMT);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecMisDetail::DpchAppData
 ******************************************************************************/

PnlIdecMisDetail::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECMISDETAILDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecMisDetail::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecMisDetail::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecMisDetailData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecMisDetail::DpchAppDo
 ******************************************************************************/

PnlIdecMisDetail::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECMISDETAILDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecMisDetail::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecMisDetail::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecMisDetailDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecMisDetail::DpchEngData
 ******************************************************************************/

PnlIdecMisDetail::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECMISDETAILDATA) {
	feedFPupCry.tag = "FeedFPupCry";
};

string PnlIdecMisDetail::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(FEEDFPUPCRY)) ss.push_back("feedFPupCry");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecMisDetail::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecMisDetailData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (feedFPupCry.readXML(docctx, basexpath, true)) add(FEEDFPUPCRY);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		feedFPupCry.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

