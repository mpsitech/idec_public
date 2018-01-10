/**
  * \file PnlIdecNavOpr.cpp
  * API code for job PnlIdecNavOpr (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecNavOpr.h"

/******************************************************************************
 class PnlIdecNavOpr::VecVDo
 ******************************************************************************/

uint PnlIdecNavOpr::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmisviewclick") return BUTMISVIEWCLICK;
	else if (s == "butmisnewcrdclick") return BUTMISNEWCRDCLICK;
	else if (s == "buttouviewclick") return BUTTOUVIEWCLICK;
	else if (s == "buttounewcrdclick") return BUTTOUNEWCRDCLICK;
	else if (s == "butiaqnewcrdclick") return BUTIAQNEWCRDCLICK;
	else if (s == "butad1newcrdclick") return BUTAD1NEWCRDCLICK;
	else if (s == "butfilviewclick") return BUTFILVIEWCLICK;
	else if (s == "butfilnewcrdclick") return BUTFILNEWCRDCLICK;

	return(0);
};

string PnlIdecNavOpr::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMISVIEWCLICK) return("ButMisViewClick");
	else if (ix == BUTMISNEWCRDCLICK) return("ButMisNewcrdClick");
	else if (ix == BUTTOUVIEWCLICK) return("ButTouViewClick");
	else if (ix == BUTTOUNEWCRDCLICK) return("ButTouNewcrdClick");
	else if (ix == BUTIAQNEWCRDCLICK) return("ButIaqNewcrdClick");
	else if (ix == BUTAD1NEWCRDCLICK) return("ButAd1NewcrdClick");
	else if (ix == BUTFILVIEWCLICK) return("ButFilViewClick");
	else if (ix == BUTFILNEWCRDCLICK) return("ButFilNewcrdClick");

	return("");
};

/******************************************************************************
 class PnlIdecNavOpr::ContIac
 ******************************************************************************/

PnlIdecNavOpr::ContIac::ContIac(
			const uint numFLstMis
			, const uint numFLstTou
			, const uint numFLstFil
		) : Block() {
	this->numFLstMis = numFLstMis;
	this->numFLstTou = numFLstTou;
	this->numFLstFil = numFLstFil;

	mask = {NUMFLSTMIS, NUMFLSTTOU, NUMFLSTFIL};
};

bool PnlIdecNavOpr::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecNavOpr");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecNavOpr";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstMis", numFLstMis)) add(NUMFLSTMIS);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstTou", numFLstTou)) add(NUMFLSTTOU);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstFil", numFLstFil)) add(NUMFLSTFIL);
	};

	return basefound;
};

void PnlIdecNavOpr::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecNavOpr";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecNavOpr";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFLstMis", numFLstMis);
		writeUintAttr(wr, itemtag, "sref", "numFLstTou", numFLstTou);
		writeUintAttr(wr, itemtag, "sref", "numFLstFil", numFLstFil);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavOpr::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFLstMis == comp->numFLstMis) insert(items, NUMFLSTMIS);
	if (numFLstTou == comp->numFLstTou) insert(items, NUMFLSTTOU);
	if (numFLstFil == comp->numFLstFil) insert(items, NUMFLSTFIL);

	return(items);
};

set<uint> PnlIdecNavOpr::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFLSTMIS, NUMFLSTTOU, NUMFLSTFIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavOpr::StatApp
 ******************************************************************************/

PnlIdecNavOpr::StatApp::StatApp(
			const uint ixIdecVExpstate
			, const bool LstMisAlt
			, const bool LstTouAlt
			, const bool LstFilAlt
			, const uint LstMisNumFirstdisp
			, const uint LstTouNumFirstdisp
			, const uint LstFilNumFirstdisp
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->LstMisAlt = LstMisAlt;
	this->LstTouAlt = LstTouAlt;
	this->LstFilAlt = LstFilAlt;
	this->LstMisNumFirstdisp = LstMisNumFirstdisp;
	this->LstTouNumFirstdisp = LstTouNumFirstdisp;
	this->LstFilNumFirstdisp = LstFilNumFirstdisp;

	mask = {IXIDECVEXPSTATE, LSTMISALT, LSTTOUALT, LSTFILALT, LSTMISNUMFIRSTDISP, LSTTOUNUMFIRSTDISP, LSTFILNUMFIRSTDISP};
};

bool PnlIdecNavOpr::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecNavOpr");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecNavOpr";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstMisAlt", LstMisAlt)) add(LSTMISALT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstTouAlt", LstTouAlt)) add(LSTTOUALT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstFilAlt", LstFilAlt)) add(LSTFILALT);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstMisNumFirstdisp", LstMisNumFirstdisp)) add(LSTMISNUMFIRSTDISP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstTouNumFirstdisp", LstTouNumFirstdisp)) add(LSTTOUNUMFIRSTDISP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstFilNumFirstdisp", LstFilNumFirstdisp)) add(LSTFILNUMFIRSTDISP);
	};

	return basefound;
};

set<uint> PnlIdecNavOpr::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (LstMisAlt == comp->LstMisAlt) insert(items, LSTMISALT);
	if (LstTouAlt == comp->LstTouAlt) insert(items, LSTTOUALT);
	if (LstFilAlt == comp->LstFilAlt) insert(items, LSTFILALT);
	if (LstMisNumFirstdisp == comp->LstMisNumFirstdisp) insert(items, LSTMISNUMFIRSTDISP);
	if (LstTouNumFirstdisp == comp->LstTouNumFirstdisp) insert(items, LSTTOUNUMFIRSTDISP);
	if (LstFilNumFirstdisp == comp->LstFilNumFirstdisp) insert(items, LSTFILNUMFIRSTDISP);

	return(items);
};

set<uint> PnlIdecNavOpr::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, LSTMISALT, LSTTOUALT, LSTFILALT, LSTMISNUMFIRSTDISP, LSTTOUNUMFIRSTDISP, LSTFILNUMFIRSTDISP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavOpr::StatShr
 ******************************************************************************/

PnlIdecNavOpr::StatShr::StatShr(
			const bool LstMisAvail
			, const bool ButMisViewActive
			, const bool LstTouAvail
			, const bool ButTouViewActive
			, const bool ButTouNewcrdActive
			, const bool ButIaqNewcrdActive
			, const bool ButAd1NewcrdActive
			, const bool LstFilAvail
			, const bool ButFilViewActive
			, const bool ButFilNewcrdActive
		) : Block() {
	this->LstMisAvail = LstMisAvail;
	this->ButMisViewActive = ButMisViewActive;
	this->LstTouAvail = LstTouAvail;
	this->ButTouViewActive = ButTouViewActive;
	this->ButTouNewcrdActive = ButTouNewcrdActive;
	this->ButIaqNewcrdActive = ButIaqNewcrdActive;
	this->ButAd1NewcrdActive = ButAd1NewcrdActive;
	this->LstFilAvail = LstFilAvail;
	this->ButFilViewActive = ButFilViewActive;
	this->ButFilNewcrdActive = ButFilNewcrdActive;

	mask = {LSTMISAVAIL, BUTMISVIEWACTIVE, LSTTOUAVAIL, BUTTOUVIEWACTIVE, BUTTOUNEWCRDACTIVE, BUTIAQNEWCRDACTIVE, BUTAD1NEWCRDACTIVE, LSTFILAVAIL, BUTFILVIEWACTIVE, BUTFILNEWCRDACTIVE};
};

bool PnlIdecNavOpr::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecNavOpr");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecNavOpr";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstMisAvail", LstMisAvail)) add(LSTMISAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButMisViewActive", ButMisViewActive)) add(BUTMISVIEWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstTouAvail", LstTouAvail)) add(LSTTOUAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTouViewActive", ButTouViewActive)) add(BUTTOUVIEWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButTouNewcrdActive", ButTouNewcrdActive)) add(BUTTOUNEWCRDACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButIaqNewcrdActive", ButIaqNewcrdActive)) add(BUTIAQNEWCRDACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButAd1NewcrdActive", ButAd1NewcrdActive)) add(BUTAD1NEWCRDACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstFilAvail", LstFilAvail)) add(LSTFILAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButFilViewActive", ButFilViewActive)) add(BUTFILVIEWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButFilNewcrdActive", ButFilNewcrdActive)) add(BUTFILNEWCRDACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecNavOpr::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (LstMisAvail == comp->LstMisAvail) insert(items, LSTMISAVAIL);
	if (ButMisViewActive == comp->ButMisViewActive) insert(items, BUTMISVIEWACTIVE);
	if (LstTouAvail == comp->LstTouAvail) insert(items, LSTTOUAVAIL);
	if (ButTouViewActive == comp->ButTouViewActive) insert(items, BUTTOUVIEWACTIVE);
	if (ButTouNewcrdActive == comp->ButTouNewcrdActive) insert(items, BUTTOUNEWCRDACTIVE);
	if (ButIaqNewcrdActive == comp->ButIaqNewcrdActive) insert(items, BUTIAQNEWCRDACTIVE);
	if (ButAd1NewcrdActive == comp->ButAd1NewcrdActive) insert(items, BUTAD1NEWCRDACTIVE);
	if (LstFilAvail == comp->LstFilAvail) insert(items, LSTFILAVAIL);
	if (ButFilViewActive == comp->ButFilViewActive) insert(items, BUTFILVIEWACTIVE);
	if (ButFilNewcrdActive == comp->ButFilNewcrdActive) insert(items, BUTFILNEWCRDACTIVE);

	return(items);
};

set<uint> PnlIdecNavOpr::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {LSTMISAVAIL, BUTMISVIEWACTIVE, LSTTOUAVAIL, BUTTOUVIEWACTIVE, BUTTOUNEWCRDACTIVE, BUTIAQNEWCRDACTIVE, BUTAD1NEWCRDACTIVE, LSTFILAVAIL, BUTFILVIEWACTIVE, BUTFILNEWCRDACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavOpr::Tag
 ******************************************************************************/

PnlIdecNavOpr::Tag::Tag(
			const string& Cpt
			, const string& CptMis
			, const string& CptTou
			, const string& CptIaq
			, const string& CptAd1
			, const string& CptFil
		) : Block() {
	this->Cpt = Cpt;
	this->CptMis = CptMis;
	this->CptTou = CptTou;
	this->CptIaq = CptIaq;
	this->CptAd1 = CptAd1;
	this->CptFil = CptFil;

	mask = {CPT, CPTMIS, CPTTOU, CPTIAQ, CPTAD1, CPTFIL};
};

bool PnlIdecNavOpr::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecNavOpr");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecNavOpr";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptMis", CptMis)) add(CPTMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTou", CptTou)) add(CPTTOU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIaq", CptIaq)) add(CPTIAQ);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAd1", CptAd1)) add(CPTAD1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFil", CptFil)) add(CPTFIL);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecNavOpr::DpchAppData
 ******************************************************************************/

PnlIdecNavOpr::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVOPRDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecNavOpr::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavOpr::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecNavOprData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavOpr::DpchAppDo
 ******************************************************************************/

PnlIdecNavOpr::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVOPRDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecNavOpr::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavOpr::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecNavOprDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavOpr::DpchEngData
 ******************************************************************************/

PnlIdecNavOpr::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVOPRDATA) {
	feedFLstFil.tag = "FeedFLstFil";
	feedFLstMis.tag = "FeedFLstMis";
	feedFLstTou.tag = "FeedFLstTou";
};

string PnlIdecNavOpr::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(FEEDFLSTFIL)) ss.push_back("feedFLstFil");
	if (has(FEEDFLSTMIS)) ss.push_back("feedFLstMis");
	if (has(FEEDFLSTTOU)) ss.push_back("feedFLstTou");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavOpr::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecNavOprData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (feedFLstFil.readXML(docctx, basexpath, true)) add(FEEDFLSTFIL);
		if (feedFLstMis.readXML(docctx, basexpath, true)) add(FEEDFLSTMIS);
		if (feedFLstTou.readXML(docctx, basexpath, true)) add(FEEDFLSTTOU);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		feedFLstFil.clear();
		feedFLstMis.clear();
		feedFLstTou.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

