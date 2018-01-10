/**
  * \file PnlIdecUsrDetail.cpp
  * API code for job PnlIdecUsrDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecUsrDetail.h"

/******************************************************************************
 class PnlIdecUsrDetail::VecVDo
 ******************************************************************************/

uint PnlIdecUsrDetail::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butsaveclick") return BUTSAVECLICK;
	else if (s == "butusgviewclick") return BUTUSGVIEWCLICK;
	else if (s == "butjeditclick") return BUTJEDITCLICK;

	return(0);
};

string PnlIdecUsrDetail::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTSAVECLICK) return("ButSaveClick");
	else if (ix == BUTUSGVIEWCLICK) return("ButUsgViewClick");
	else if (ix == BUTJEDITCLICK) return("ButJEditClick");

	return("");
};

/******************************************************************************
 class PnlIdecUsrDetail::ContIac
 ******************************************************************************/

PnlIdecUsrDetail::ContIac::ContIac(
			const uint numFPupJ
			, const uint numFPupSte
			, const uint numFPupLcl
			, const uint numFPupUlv
			, const string& TxfPwd
		) : Block() {
	this->numFPupJ = numFPupJ;
	this->numFPupSte = numFPupSte;
	this->numFPupLcl = numFPupLcl;
	this->numFPupUlv = numFPupUlv;
	this->TxfPwd = TxfPwd;

	mask = {NUMFPUPJ, NUMFPUPSTE, NUMFPUPLCL, NUMFPUPULV, TXFPWD};
};

bool PnlIdecUsrDetail::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecUsrDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecUsrDetail";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupJ", numFPupJ)) add(NUMFPUPJ);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupSte", numFPupSte)) add(NUMFPUPSTE);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupLcl", numFPupLcl)) add(NUMFPUPLCL);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupUlv", numFPupUlv)) add(NUMFPUPULV);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPwd", TxfPwd)) add(TXFPWD);
	};

	return basefound;
};

void PnlIdecUsrDetail::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecUsrDetail";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecUsrDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupJ", numFPupJ);
		writeUintAttr(wr, itemtag, "sref", "numFPupSte", numFPupSte);
		writeUintAttr(wr, itemtag, "sref", "numFPupLcl", numFPupLcl);
		writeUintAttr(wr, itemtag, "sref", "numFPupUlv", numFPupUlv);
		writeStringAttr(wr, itemtag, "sref", "TxfPwd", TxfPwd);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecUsrDetail::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupJ == comp->numFPupJ) insert(items, NUMFPUPJ);
	if (numFPupSte == comp->numFPupSte) insert(items, NUMFPUPSTE);
	if (numFPupLcl == comp->numFPupLcl) insert(items, NUMFPUPLCL);
	if (numFPupUlv == comp->numFPupUlv) insert(items, NUMFPUPULV);
	if (TxfPwd.compare(comp->TxfPwd) == 0) insert(items, TXFPWD);

	return(items);
};

set<uint> PnlIdecUsrDetail::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPJ, NUMFPUPSTE, NUMFPUPLCL, NUMFPUPULV, TXFPWD};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUsrDetail::ContInf
 ******************************************************************************/

PnlIdecUsrDetail::ContInf::ContInf(
			const string& TxtPrs
			, const string& TxtSrf
			, const string& TxtUsg
		) : Block() {
	this->TxtPrs = TxtPrs;
	this->TxtSrf = TxtSrf;
	this->TxtUsg = TxtUsg;

	mask = {TXTPRS, TXTSRF, TXTUSG};
};

bool PnlIdecUsrDetail::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecUsrDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecUsrDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtPrs", TxtPrs)) add(TXTPRS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSrf", TxtSrf)) add(TXTSRF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtUsg", TxtUsg)) add(TXTUSG);
	};

	return basefound;
};

set<uint> PnlIdecUsrDetail::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtPrs.compare(comp->TxtPrs) == 0) insert(items, TXTPRS);
	if (TxtSrf.compare(comp->TxtSrf) == 0) insert(items, TXTSRF);
	if (TxtUsg.compare(comp->TxtUsg) == 0) insert(items, TXTUSG);

	return(items);
};

set<uint> PnlIdecUsrDetail::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTPRS, TXTSRF, TXTUSG};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUsrDetail::StatApp
 ******************************************************************************/

PnlIdecUsrDetail::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecUsrDetail::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecUsrDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecUsrDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecUsrDetail::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecUsrDetail::StatApp::diff(
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
 class PnlIdecUsrDetail::StatShr
 ******************************************************************************/

PnlIdecUsrDetail::StatShr::StatShr(
			const bool ButSaveAvail
			, const bool ButSaveActive
			, const bool TxtPrsActive
			, const bool TxtSrfActive
			, const bool TxtUsgActive
			, const bool ButUsgViewAvail
			, const bool ButUsgViewActive
			, const bool PupJActive
			, const bool ButJEditAvail
			, const bool PupSteActive
			, const bool PupLclActive
			, const bool PupUlvActive
			, const bool TxfPwdActive
		) : Block() {
	this->ButSaveAvail = ButSaveAvail;
	this->ButSaveActive = ButSaveActive;
	this->TxtPrsActive = TxtPrsActive;
	this->TxtSrfActive = TxtSrfActive;
	this->TxtUsgActive = TxtUsgActive;
	this->ButUsgViewAvail = ButUsgViewAvail;
	this->ButUsgViewActive = ButUsgViewActive;
	this->PupJActive = PupJActive;
	this->ButJEditAvail = ButJEditAvail;
	this->PupSteActive = PupSteActive;
	this->PupLclActive = PupLclActive;
	this->PupUlvActive = PupUlvActive;
	this->TxfPwdActive = TxfPwdActive;

	mask = {BUTSAVEAVAIL, BUTSAVEACTIVE, TXTPRSACTIVE, TXTSRFACTIVE, TXTUSGACTIVE, BUTUSGVIEWAVAIL, BUTUSGVIEWACTIVE, PUPJACTIVE, BUTJEDITAVAIL, PUPSTEACTIVE, PUPLCLACTIVE, PUPULVACTIVE, TXFPWDACTIVE};
};

bool PnlIdecUsrDetail::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecUsrDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecUsrDetail";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSaveAvail", ButSaveAvail)) add(BUTSAVEAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButSaveActive", ButSaveActive)) add(BUTSAVEACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtPrsActive", TxtPrsActive)) add(TXTPRSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtSrfActive", TxtSrfActive)) add(TXTSRFACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtUsgActive", TxtUsgActive)) add(TXTUSGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButUsgViewAvail", ButUsgViewAvail)) add(BUTUSGVIEWAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButUsgViewActive", ButUsgViewActive)) add(BUTUSGVIEWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupJActive", PupJActive)) add(PUPJACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButJEditAvail", ButJEditAvail)) add(BUTJEDITAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupSteActive", PupSteActive)) add(PUPSTEACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLclActive", PupLclActive)) add(PUPLCLACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupUlvActive", PupUlvActive)) add(PUPULVACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPwdActive", TxfPwdActive)) add(TXFPWDACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecUsrDetail::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ButSaveAvail == comp->ButSaveAvail) insert(items, BUTSAVEAVAIL);
	if (ButSaveActive == comp->ButSaveActive) insert(items, BUTSAVEACTIVE);
	if (TxtPrsActive == comp->TxtPrsActive) insert(items, TXTPRSACTIVE);
	if (TxtSrfActive == comp->TxtSrfActive) insert(items, TXTSRFACTIVE);
	if (TxtUsgActive == comp->TxtUsgActive) insert(items, TXTUSGACTIVE);
	if (ButUsgViewAvail == comp->ButUsgViewAvail) insert(items, BUTUSGVIEWAVAIL);
	if (ButUsgViewActive == comp->ButUsgViewActive) insert(items, BUTUSGVIEWACTIVE);
	if (PupJActive == comp->PupJActive) insert(items, PUPJACTIVE);
	if (ButJEditAvail == comp->ButJEditAvail) insert(items, BUTJEDITAVAIL);
	if (PupSteActive == comp->PupSteActive) insert(items, PUPSTEACTIVE);
	if (PupLclActive == comp->PupLclActive) insert(items, PUPLCLACTIVE);
	if (PupUlvActive == comp->PupUlvActive) insert(items, PUPULVACTIVE);
	if (TxfPwdActive == comp->TxfPwdActive) insert(items, TXFPWDACTIVE);

	return(items);
};

set<uint> PnlIdecUsrDetail::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTSAVEAVAIL, BUTSAVEACTIVE, TXTPRSACTIVE, TXTSRFACTIVE, TXTUSGACTIVE, BUTUSGVIEWAVAIL, BUTUSGVIEWACTIVE, PUPJACTIVE, BUTJEDITAVAIL, PUPSTEACTIVE, PUPLCLACTIVE, PUPULVACTIVE, TXFPWDACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUsrDetail::Tag
 ******************************************************************************/

PnlIdecUsrDetail::Tag::Tag(
			const string& Cpt
			, const string& CptPrs
			, const string& CptSrf
			, const string& CptUsg
			, const string& CptSte
			, const string& CptLcl
			, const string& CptUlv
			, const string& CptPwd
		) : Block() {
	this->Cpt = Cpt;
	this->CptPrs = CptPrs;
	this->CptSrf = CptSrf;
	this->CptUsg = CptUsg;
	this->CptSte = CptSte;
	this->CptLcl = CptLcl;
	this->CptUlv = CptUlv;
	this->CptPwd = CptPwd;

	mask = {CPT, CPTPRS, CPTSRF, CPTUSG, CPTSTE, CPTLCL, CPTULV, CPTPWD};
};

bool PnlIdecUsrDetail::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecUsrDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecUsrDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPrs", CptPrs)) add(CPTPRS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSrf", CptSrf)) add(CPTSRF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptUsg", CptUsg)) add(CPTUSG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSte", CptSte)) add(CPTSTE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptLcl", CptLcl)) add(CPTLCL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptUlv", CptUlv)) add(CPTULV);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPwd", CptPwd)) add(CPTPWD);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecUsrDetail::DpchAppData
 ******************************************************************************/

PnlIdecUsrDetail::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUSRDETAILDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecUsrDetail::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUsrDetail::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecUsrDetailData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUsrDetail::DpchAppDo
 ******************************************************************************/

PnlIdecUsrDetail::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUSRDETAILDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecUsrDetail::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUsrDetail::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecUsrDetailDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUsrDetail::DpchEngData
 ******************************************************************************/

PnlIdecUsrDetail::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUSRDETAILDATA) {
	feedFPupJ.tag = "FeedFPupJ";
	feedFPupLcl.tag = "FeedFPupLcl";
	feedFPupSte.tag = "FeedFPupSte";
	feedFPupUlv.tag = "FeedFPupUlv";
};

string PnlIdecUsrDetail::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPJ)) ss.push_back("feedFPupJ");
	if (has(FEEDFPUPLCL)) ss.push_back("feedFPupLcl");
	if (has(FEEDFPUPSTE)) ss.push_back("feedFPupSte");
	if (has(FEEDFPUPULV)) ss.push_back("feedFPupUlv");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUsrDetail::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecUsrDetailData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupJ.readXML(docctx, basexpath, true)) add(FEEDFPUPJ);
		if (feedFPupLcl.readXML(docctx, basexpath, true)) add(FEEDFPUPLCL);
		if (feedFPupSte.readXML(docctx, basexpath, true)) add(FEEDFPUPSTE);
		if (feedFPupUlv.readXML(docctx, basexpath, true)) add(FEEDFPUPULV);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupJ.clear();
		feedFPupLcl.clear();
		feedFPupSte.clear();
		feedFPupUlv.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

