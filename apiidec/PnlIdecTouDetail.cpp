/**
  * \file PnlIdecTouDetail.cpp
  * API code for job PnlIdecTouDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecTouDetail.h"

/******************************************************************************
 class PnlIdecTouDetail::VecVDo
 ******************************************************************************/

uint PnlIdecTouDetail::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butsaveclick") return BUTSAVECLICK;
	else if (s == "butmisviewclick") return BUTMISVIEWCLICK;

	return(0);
};

string PnlIdecTouDetail::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTSAVECLICK) return("ButSaveClick");
	else if (ix == BUTMISVIEWCLICK) return("ButMisViewClick");

	return("");
};

/******************************************************************************
 class PnlIdecTouDetail::ContIac
 ******************************************************************************/

PnlIdecTouDetail::ContIac::ContIac(
			const string& TxfTit
			, const string& TxfSta
			, const string& TxfSto
			, const string& TxfAre
			, const string& TxfThe
			, const string& TxfPhi
			, const string& TxfCmt
		) : Block() {
	this->TxfTit = TxfTit;
	this->TxfSta = TxfSta;
	this->TxfSto = TxfSto;
	this->TxfAre = TxfAre;
	this->TxfThe = TxfThe;
	this->TxfPhi = TxfPhi;
	this->TxfCmt = TxfCmt;

	mask = {TXFTIT, TXFSTA, TXFSTO, TXFARE, TXFTHE, TXFPHI, TXFCMT};
};

bool PnlIdecTouDetail::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecTouDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecTouDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfTit", TxfTit)) add(TXFTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSta", TxfSta)) add(TXFSTA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSto", TxfSto)) add(TXFSTO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfAre", TxfAre)) add(TXFARE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfThe", TxfThe)) add(TXFTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPhi", TxfPhi)) add(TXFPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfCmt", TxfCmt)) add(TXFCMT);
	};

	return basefound;
};

void PnlIdecTouDetail::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecTouDetail";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecTouDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfTit", TxfTit);
		writeStringAttr(wr, itemtag, "sref", "TxfSta", TxfSta);
		writeStringAttr(wr, itemtag, "sref", "TxfSto", TxfSto);
		writeStringAttr(wr, itemtag, "sref", "TxfAre", TxfAre);
		writeStringAttr(wr, itemtag, "sref", "TxfThe", TxfThe);
		writeStringAttr(wr, itemtag, "sref", "TxfPhi", TxfPhi);
		writeStringAttr(wr, itemtag, "sref", "TxfCmt", TxfCmt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecTouDetail::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfTit.compare(comp->TxfTit) == 0) insert(items, TXFTIT);
	if (TxfSta.compare(comp->TxfSta) == 0) insert(items, TXFSTA);
	if (TxfSto.compare(comp->TxfSto) == 0) insert(items, TXFSTO);
	if (TxfAre.compare(comp->TxfAre) == 0) insert(items, TXFARE);
	if (TxfThe.compare(comp->TxfThe) == 0) insert(items, TXFTHE);
	if (TxfPhi.compare(comp->TxfPhi) == 0) insert(items, TXFPHI);
	if (TxfCmt.compare(comp->TxfCmt) == 0) insert(items, TXFCMT);

	return(items);
};

set<uint> PnlIdecTouDetail::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFTIT, TXFSTA, TXFSTO, TXFARE, TXFTHE, TXFPHI, TXFCMT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecTouDetail::ContInf
 ******************************************************************************/

PnlIdecTouDetail::ContInf::ContInf(
			const string& TxtMis
		) : Block() {
	this->TxtMis = TxtMis;

	mask = {TXTMIS};
};

bool PnlIdecTouDetail::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecTouDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecTouDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtMis", TxtMis)) add(TXTMIS);
	};

	return basefound;
};

set<uint> PnlIdecTouDetail::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtMis.compare(comp->TxtMis) == 0) insert(items, TXTMIS);

	return(items);
};

set<uint> PnlIdecTouDetail::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTMIS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecTouDetail::StatApp
 ******************************************************************************/

PnlIdecTouDetail::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecTouDetail::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecTouDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecTouDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecTouDetail::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecTouDetail::StatApp::diff(
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
 class PnlIdecTouDetail::StatShr
 ******************************************************************************/

PnlIdecTouDetail::StatShr::StatShr(
			const bool ButSaveAvail
			, const bool ButSaveActive
			, const bool TxfTitActive
			, const bool TxtMisActive
			, const bool ButMisViewAvail
			, const bool ButMisViewActive
			, const bool TxfStaActive
			, const bool TxfStoActive
			, const bool TxfAreActive
			, const bool TxfTheActive
			, const bool TxfPhiActive
			, const bool TxfCmtActive
		) : Block() {
	this->ButSaveAvail = ButSaveAvail;
	this->ButSaveActive = ButSaveActive;
	this->TxfTitActive = TxfTitActive;
	this->TxtMisActive = TxtMisActive;
	this->ButMisViewAvail = ButMisViewAvail;
	this->ButMisViewActive = ButMisViewActive;
	this->TxfStaActive = TxfStaActive;
	this->TxfStoActive = TxfStoActive;
	this->TxfAreActive = TxfAreActive;
	this->TxfTheActive = TxfTheActive;
	this->TxfPhiActive = TxfPhiActive;
	this->TxfCmtActive = TxfCmtActive;

	mask = {BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXTMISACTIVE, BUTMISVIEWAVAIL, BUTMISVIEWACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, TXFAREACTIVE, TXFTHEACTIVE, TXFPHIACTIVE, TXFCMTACTIVE};
};

bool PnlIdecTouDetail::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecTouDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecTouDetail";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSaveAvail", ButSaveAvail)) add(BUTSAVEAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSaveActive", ButSaveActive)) add(BUTSAVEACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfTitActive", TxfTitActive)) add(TXFTITACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtMisActive", TxtMisActive)) add(TXTMISACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButMisViewAvail", ButMisViewAvail)) add(BUTMISVIEWAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButMisViewActive", ButMisViewActive)) add(BUTMISVIEWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfStaActive", TxfStaActive)) add(TXFSTAACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfStoActive", TxfStoActive)) add(TXFSTOACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfAreActive", TxfAreActive)) add(TXFAREACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfTheActive", TxfTheActive)) add(TXFTHEACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPhiActive", TxfPhiActive)) add(TXFPHIACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfCmtActive", TxfCmtActive)) add(TXFCMTACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecTouDetail::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ButSaveAvail == comp->ButSaveAvail) insert(items, BUTSAVEAVAIL);
	if (ButSaveActive == comp->ButSaveActive) insert(items, BUTSAVEACTIVE);
	if (TxfTitActive == comp->TxfTitActive) insert(items, TXFTITACTIVE);
	if (TxtMisActive == comp->TxtMisActive) insert(items, TXTMISACTIVE);
	if (ButMisViewAvail == comp->ButMisViewAvail) insert(items, BUTMISVIEWAVAIL);
	if (ButMisViewActive == comp->ButMisViewActive) insert(items, BUTMISVIEWACTIVE);
	if (TxfStaActive == comp->TxfStaActive) insert(items, TXFSTAACTIVE);
	if (TxfStoActive == comp->TxfStoActive) insert(items, TXFSTOACTIVE);
	if (TxfAreActive == comp->TxfAreActive) insert(items, TXFAREACTIVE);
	if (TxfTheActive == comp->TxfTheActive) insert(items, TXFTHEACTIVE);
	if (TxfPhiActive == comp->TxfPhiActive) insert(items, TXFPHIACTIVE);
	if (TxfCmtActive == comp->TxfCmtActive) insert(items, TXFCMTACTIVE);

	return(items);
};

set<uint> PnlIdecTouDetail::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXTMISACTIVE, BUTMISVIEWAVAIL, BUTMISVIEWACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, TXFAREACTIVE, TXFTHEACTIVE, TXFPHIACTIVE, TXFCMTACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecTouDetail::Tag
 ******************************************************************************/

PnlIdecTouDetail::Tag::Tag(
			const string& Cpt
			, const string& CptTit
			, const string& CptMis
			, const string& CptSta
			, const string& CptSto
			, const string& CptAre
			, const string& CptThe
			, const string& CptPhi
			, const string& CptCmt
		) : Block() {
	this->Cpt = Cpt;
	this->CptTit = CptTit;
	this->CptMis = CptMis;
	this->CptSta = CptSta;
	this->CptSto = CptSto;
	this->CptAre = CptAre;
	this->CptThe = CptThe;
	this->CptPhi = CptPhi;
	this->CptCmt = CptCmt;

	mask = {CPT, CPTTIT, CPTMIS, CPTSTA, CPTSTO, CPTARE, CPTTHE, CPTPHI, CPTCMT};
};

bool PnlIdecTouDetail::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecTouDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecTouDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTit", CptTit)) add(CPTTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMis", CptMis)) add(CPTMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSta", CptSta)) add(CPTSTA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSto", CptSto)) add(CPTSTO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAre", CptAre)) add(CPTARE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptThe", CptThe)) add(CPTTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPhi", CptPhi)) add(CPTPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptCmt", CptCmt)) add(CPTCMT);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecTouDetail::DpchAppData
 ******************************************************************************/

PnlIdecTouDetail::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECTOUDETAILDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecTouDetail::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecTouDetail::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecTouDetailData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecTouDetail::DpchAppDo
 ******************************************************************************/

PnlIdecTouDetail::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECTOUDETAILDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecTouDetail::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecTouDetail::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecTouDetailDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecTouDetail::DpchEngData
 ******************************************************************************/

PnlIdecTouDetail::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECTOUDETAILDATA) {
};

string PnlIdecTouDetail::DpchEngData::getSrefsMask() {
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

void PnlIdecTouDetail::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecTouDetailData");
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

