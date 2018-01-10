/**
  * \file PnlIdecScfStatus.cpp
  * API code for job PnlIdecScfStatus (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfStatus.h"

/******************************************************************************
 class PnlIdecScfStatus::VecVDo
 ******************************************************************************/

uint PnlIdecScfStatus::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "buttheclearclick") return BUTTHECLEARCLICK;
	else if (s == "butphiclearclick") return BUTPHICLEARCLICK;
	else if (s == "butsteclearclick") return BUTSTECLEARCLICK;
	else if (s == "butfusclearclick") return BUTFUSCLEARCLICK;
	else if (s == "butqnuclearclick") return BUTQNUCLEARCLICK;
	else if (s == "butqalclearclick") return BUTQALCLEARCLICK;
	else if (s == "butacvclearclick") return BUTACVCLEARCLICK;

	return(0);
};

string PnlIdecScfStatus::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTTHECLEARCLICK) return("ButTheClearClick");
	else if (ix == BUTPHICLEARCLICK) return("ButPhiClearClick");
	else if (ix == BUTSTECLEARCLICK) return("ButSteClearClick");
	else if (ix == BUTFUSCLEARCLICK) return("ButFusClearClick");
	else if (ix == BUTQNUCLEARCLICK) return("ButQnuClearClick");
	else if (ix == BUTQALCLEARCLICK) return("ButQalClearClick");
	else if (ix == BUTACVCLEARCLICK) return("ButAcvClearClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfStatus::VecVSge
 ******************************************************************************/

uint PnlIdecScfStatus::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alrcth") return ALRCTH;
	else if (s == "alrcph") return ALRCPH;
	else if (s == "alrcst") return ALRCST;
	else if (s == "alrcfu") return ALRCFU;
	else if (s == "alrcqn") return ALRCQN;
	else if (s == "alrcqa") return ALRCQA;
	else if (s == "alrcac") return ALRCAC;

	return(0);
};

string PnlIdecScfStatus::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRCTH) return("alrcth");
	else if (ix == ALRCPH) return("alrcph");
	else if (ix == ALRCST) return("alrcst");
	else if (ix == ALRCFU) return("alrcfu");
	else if (ix == ALRCQN) return("alrcqn");
	else if (ix == ALRCQA) return("alrcqa");
	else if (ix == ALRCAC) return("alrcac");

	return("");
};

/******************************************************************************
 class PnlIdecScfStatus::ContInf
 ******************************************************************************/

PnlIdecScfStatus::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtThe
			, const string& TxtPhi
			, const string& TxtSte
			, const string& TxtFus
			, const string& TxtQnu
			, const string& TxtQal
			, const string& TxtAcv
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtThe = TxtThe;
	this->TxtPhi = TxtPhi;
	this->TxtSte = TxtSte;
	this->TxtFus = TxtFus;
	this->TxtQnu = TxtQnu;
	this->TxtQal = TxtQal;
	this->TxtAcv = TxtAcv;

	mask = {BUTMASTERON, TXTTHE, TXTPHI, TXTSTE, TXTFUS, TXTQNU, TXTQAL, TXTACV};
};

bool PnlIdecScfStatus::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfStatus");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfStatus";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtThe", TxtThe)) add(TXTTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtPhi", TxtPhi)) add(TXTPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSte", TxtSte)) add(TXTSTE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtFus", TxtFus)) add(TXTFUS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtQnu", TxtQnu)) add(TXTQNU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtQal", TxtQal)) add(TXTQAL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtAcv", TxtAcv)) add(TXTACV);
	};

	return basefound;
};

set<uint> PnlIdecScfStatus::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtThe.compare(comp->TxtThe) == 0) insert(items, TXTTHE);
	if (TxtPhi.compare(comp->TxtPhi) == 0) insert(items, TXTPHI);
	if (TxtSte.compare(comp->TxtSte) == 0) insert(items, TXTSTE);
	if (TxtFus.compare(comp->TxtFus) == 0) insert(items, TXTFUS);
	if (TxtQnu.compare(comp->TxtQnu) == 0) insert(items, TXTQNU);
	if (TxtQal.compare(comp->TxtQal) == 0) insert(items, TXTQAL);
	if (TxtAcv.compare(comp->TxtAcv) == 0) insert(items, TXTACV);

	return(items);
};

set<uint> PnlIdecScfStatus::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTTHE, TXTPHI, TXTSTE, TXTFUS, TXTQNU, TXTQAL, TXTACV};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfStatus::StatApp
 ******************************************************************************/

PnlIdecScfStatus::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecScfStatus::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScfStatus");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScfStatus";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecScfStatus::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecScfStatus::StatApp::diff(
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
 class PnlIdecScfStatus::StatShr
 ******************************************************************************/

PnlIdecScfStatus::StatShr::StatShr(
			const bool ButTheClearActive
			, const bool ButPhiClearActive
			, const bool ButSteClearActive
			, const bool ButFusClearActive
			, const bool ButQnuClearActive
			, const bool ButQalClearActive
			, const bool ButAcvClearActive
		) : Block() {
	this->ButTheClearActive = ButTheClearActive;
	this->ButPhiClearActive = ButPhiClearActive;
	this->ButSteClearActive = ButSteClearActive;
	this->ButFusClearActive = ButFusClearActive;
	this->ButQnuClearActive = ButQnuClearActive;
	this->ButQalClearActive = ButQalClearActive;
	this->ButAcvClearActive = ButAcvClearActive;

	mask = {BUTTHECLEARACTIVE, BUTPHICLEARACTIVE, BUTSTECLEARACTIVE, BUTFUSCLEARACTIVE, BUTQNUCLEARACTIVE, BUTQALCLEARACTIVE, BUTACVCLEARACTIVE};
};

bool PnlIdecScfStatus::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfStatus");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfStatus";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTheClearActive", ButTheClearActive)) add(BUTTHECLEARACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPhiClearActive", ButPhiClearActive)) add(BUTPHICLEARACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSteClearActive", ButSteClearActive)) add(BUTSTECLEARACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButFusClearActive", ButFusClearActive)) add(BUTFUSCLEARACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButQnuClearActive", ButQnuClearActive)) add(BUTQNUCLEARACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButQalClearActive", ButQalClearActive)) add(BUTQALCLEARACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButAcvClearActive", ButAcvClearActive)) add(BUTACVCLEARACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecScfStatus::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ButTheClearActive == comp->ButTheClearActive) insert(items, BUTTHECLEARACTIVE);
	if (ButPhiClearActive == comp->ButPhiClearActive) insert(items, BUTPHICLEARACTIVE);
	if (ButSteClearActive == comp->ButSteClearActive) insert(items, BUTSTECLEARACTIVE);
	if (ButFusClearActive == comp->ButFusClearActive) insert(items, BUTFUSCLEARACTIVE);
	if (ButQnuClearActive == comp->ButQnuClearActive) insert(items, BUTQNUCLEARACTIVE);
	if (ButQalClearActive == comp->ButQalClearActive) insert(items, BUTQALCLEARACTIVE);
	if (ButAcvClearActive == comp->ButAcvClearActive) insert(items, BUTACVCLEARACTIVE);

	return(items);
};

set<uint> PnlIdecScfStatus::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTTHECLEARACTIVE, BUTPHICLEARACTIVE, BUTSTECLEARACTIVE, BUTFUSCLEARACTIVE, BUTQNUCLEARACTIVE, BUTQALCLEARACTIVE, BUTACVCLEARACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfStatus::Tag
 ******************************************************************************/

PnlIdecScfStatus::Tag::Tag(
			const string& Cpt
			, const string& HdgCalib
			, const string& CptThe
			, const string& ButTheClear
			, const string& CptPhi
			, const string& ButPhiClear
			, const string& CptSte
			, const string& ButSteClear
			, const string& CptFus
			, const string& ButFusClear
			, const string& CptQnu
			, const string& ButQnuClear
			, const string& CptQal
			, const string& ButQalClear
			, const string& TxtAcv
			, const string& CptAcv
			, const string& ButAcvClear
		) : Block() {
	this->Cpt = Cpt;
	this->HdgCalib = HdgCalib;
	this->CptThe = CptThe;
	this->ButTheClear = ButTheClear;
	this->CptPhi = CptPhi;
	this->ButPhiClear = ButPhiClear;
	this->CptSte = CptSte;
	this->ButSteClear = ButSteClear;
	this->CptFus = CptFus;
	this->ButFusClear = ButFusClear;
	this->CptQnu = CptQnu;
	this->ButQnuClear = ButQnuClear;
	this->CptQal = CptQal;
	this->ButQalClear = ButQalClear;
	this->TxtAcv = TxtAcv;
	this->CptAcv = CptAcv;
	this->ButAcvClear = ButAcvClear;

	mask = {CPT, HDGCALIB, CPTTHE, BUTTHECLEAR, CPTPHI, BUTPHICLEAR, CPTSTE, BUTSTECLEAR, CPTFUS, BUTFUSCLEAR, CPTQNU, BUTQNUCLEAR, CPTQAL, BUTQALCLEAR, TXTACV, CPTACV, BUTACVCLEAR};
};

bool PnlIdecScfStatus::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfStatus");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfStatus";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgCalib", HdgCalib)) add(HDGCALIB);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptThe", CptThe)) add(CPTTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButTheClear", ButTheClear)) add(BUTTHECLEAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPhi", CptPhi)) add(CPTPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButPhiClear", ButPhiClear)) add(BUTPHICLEAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSte", CptSte)) add(CPTSTE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButSteClear", ButSteClear)) add(BUTSTECLEAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFus", CptFus)) add(CPTFUS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButFusClear", ButFusClear)) add(BUTFUSCLEAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQnu", CptQnu)) add(CPTQNU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButQnuClear", ButQnuClear)) add(BUTQNUCLEAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQal", CptQal)) add(CPTQAL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButQalClear", ButQalClear)) add(BUTQALCLEAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TxtAcv", TxtAcv)) add(TXTACV);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAcv", CptAcv)) add(CPTACV);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButAcvClear", ButAcvClear)) add(BUTACVCLEAR);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfStatus::DpchAppDo
 ******************************************************************************/

PnlIdecScfStatus::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFSTATUSDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfStatus::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfStatus::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfStatusDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfStatus::DpchEngData
 ******************************************************************************/

PnlIdecScfStatus::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFSTATUSDATA) {
};

string PnlIdecScfStatus::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfStatus::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfStatusData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		continf = ContInf();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

