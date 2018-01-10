/**
  * \file PnlIdecNavMaint.cpp
  * API code for job PnlIdecNavMaint (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecNavMaint.h"

/******************************************************************************
 class PnlIdecNavMaint::VecVDo
 ******************************************************************************/

uint PnlIdecNavMaint::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butusgviewclick") return BUTUSGVIEWCLICK;
	else if (s == "butusgnewcrdclick") return BUTUSGNEWCRDCLICK;
	else if (s == "butusrviewclick") return BUTUSRVIEWCLICK;
	else if (s == "butusrnewcrdclick") return BUTUSRNEWCRDCLICK;
	else if (s == "butscfnewcrdclick") return BUTSCFNEWCRDCLICK;
	else if (s == "bututlnewcrdclick") return BUTUTLNEWCRDCLICK;

	return(0);
};

string PnlIdecNavMaint::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTUSGVIEWCLICK) return("ButUsgViewClick");
	else if (ix == BUTUSGNEWCRDCLICK) return("ButUsgNewcrdClick");
	else if (ix == BUTUSRVIEWCLICK) return("ButUsrViewClick");
	else if (ix == BUTUSRNEWCRDCLICK) return("ButUsrNewcrdClick");
	else if (ix == BUTSCFNEWCRDCLICK) return("ButScfNewcrdClick");
	else if (ix == BUTUTLNEWCRDCLICK) return("ButUtlNewcrdClick");

	return("");
};

/******************************************************************************
 class PnlIdecNavMaint::ContIac
 ******************************************************************************/

PnlIdecNavMaint::ContIac::ContIac(
			const uint numFLstUsg
			, const uint numFLstUsr
		) : Block() {
	this->numFLstUsg = numFLstUsg;
	this->numFLstUsr = numFLstUsr;

	mask = {NUMFLSTUSG, NUMFLSTUSR};
};

bool PnlIdecNavMaint::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecNavMaint");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecNavMaint";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstUsg", numFLstUsg)) add(NUMFLSTUSG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstUsr", numFLstUsr)) add(NUMFLSTUSR);
	};

	return basefound;
};

void PnlIdecNavMaint::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecNavMaint";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecNavMaint";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFLstUsg", numFLstUsg);
		writeUintAttr(wr, itemtag, "sref", "numFLstUsr", numFLstUsr);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavMaint::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFLstUsg == comp->numFLstUsg) insert(items, NUMFLSTUSG);
	if (numFLstUsr == comp->numFLstUsr) insert(items, NUMFLSTUSR);

	return(items);
};

set<uint> PnlIdecNavMaint::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFLSTUSG, NUMFLSTUSR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavMaint::StatApp
 ******************************************************************************/

PnlIdecNavMaint::StatApp::StatApp(
			const uint ixIdecVExpstate
			, const bool LstUsgAlt
			, const bool LstUsrAlt
			, const uint LstUsgNumFirstdisp
			, const uint LstUsrNumFirstdisp
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->LstUsgAlt = LstUsgAlt;
	this->LstUsrAlt = LstUsrAlt;
	this->LstUsgNumFirstdisp = LstUsgNumFirstdisp;
	this->LstUsrNumFirstdisp = LstUsrNumFirstdisp;

	mask = {IXIDECVEXPSTATE, LSTUSGALT, LSTUSRALT, LSTUSGNUMFIRSTDISP, LSTUSRNUMFIRSTDISP};
};

bool PnlIdecNavMaint::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecNavMaint");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecNavMaint";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstUsgAlt", LstUsgAlt)) add(LSTUSGALT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstUsrAlt", LstUsrAlt)) add(LSTUSRALT);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstUsgNumFirstdisp", LstUsgNumFirstdisp)) add(LSTUSGNUMFIRSTDISP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstUsrNumFirstdisp", LstUsrNumFirstdisp)) add(LSTUSRNUMFIRSTDISP);
	};

	return basefound;
};

set<uint> PnlIdecNavMaint::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (LstUsgAlt == comp->LstUsgAlt) insert(items, LSTUSGALT);
	if (LstUsrAlt == comp->LstUsrAlt) insert(items, LSTUSRALT);
	if (LstUsgNumFirstdisp == comp->LstUsgNumFirstdisp) insert(items, LSTUSGNUMFIRSTDISP);
	if (LstUsrNumFirstdisp == comp->LstUsrNumFirstdisp) insert(items, LSTUSRNUMFIRSTDISP);

	return(items);
};

set<uint> PnlIdecNavMaint::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, LSTUSGALT, LSTUSRALT, LSTUSGNUMFIRSTDISP, LSTUSRNUMFIRSTDISP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavMaint::StatShr
 ******************************************************************************/

PnlIdecNavMaint::StatShr::StatShr(
			const bool LstUsgAvail
			, const bool ButUsgViewActive
			, const bool LstUsrAvail
			, const bool ButUsrViewActive
		) : Block() {
	this->LstUsgAvail = LstUsgAvail;
	this->ButUsgViewActive = ButUsgViewActive;
	this->LstUsrAvail = LstUsrAvail;
	this->ButUsrViewActive = ButUsrViewActive;

	mask = {LSTUSGAVAIL, BUTUSGVIEWACTIVE, LSTUSRAVAIL, BUTUSRVIEWACTIVE};
};

bool PnlIdecNavMaint::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecNavMaint");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecNavMaint";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstUsgAvail", LstUsgAvail)) add(LSTUSGAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButUsgViewActive", ButUsgViewActive)) add(BUTUSGVIEWACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "LstUsrAvail", LstUsrAvail)) add(LSTUSRAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButUsrViewActive", ButUsrViewActive)) add(BUTUSRVIEWACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecNavMaint::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (LstUsgAvail == comp->LstUsgAvail) insert(items, LSTUSGAVAIL);
	if (ButUsgViewActive == comp->ButUsgViewActive) insert(items, BUTUSGVIEWACTIVE);
	if (LstUsrAvail == comp->LstUsrAvail) insert(items, LSTUSRAVAIL);
	if (ButUsrViewActive == comp->ButUsrViewActive) insert(items, BUTUSRVIEWACTIVE);

	return(items);
};

set<uint> PnlIdecNavMaint::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {LSTUSGAVAIL, BUTUSGVIEWACTIVE, LSTUSRAVAIL, BUTUSRVIEWACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavMaint::Tag
 ******************************************************************************/

PnlIdecNavMaint::Tag::Tag(
			const string& Cpt
			, const string& CptUsg
			, const string& CptUsr
			, const string& CptScf
			, const string& CptUtl
		) : Block() {
	this->Cpt = Cpt;
	this->CptUsg = CptUsg;
	this->CptUsr = CptUsr;
	this->CptScf = CptScf;
	this->CptUtl = CptUtl;

	mask = {CPT, CPTUSG, CPTUSR, CPTSCF, CPTUTL};
};

bool PnlIdecNavMaint::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecNavMaint");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecNavMaint";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptUsg", CptUsg)) add(CPTUSG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptUsr", CptUsr)) add(CPTUSR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptScf", CptScf)) add(CPTSCF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptUtl", CptUtl)) add(CPTUTL);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecNavMaint::DpchAppData
 ******************************************************************************/

PnlIdecNavMaint::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVMAINTDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecNavMaint::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavMaint::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecNavMaintData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavMaint::DpchAppDo
 ******************************************************************************/

PnlIdecNavMaint::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVMAINTDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecNavMaint::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavMaint::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecNavMaintDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavMaint::DpchEngData
 ******************************************************************************/

PnlIdecNavMaint::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVMAINTDATA) {
	feedFLstUsg.tag = "FeedFLstUsg";
	feedFLstUsr.tag = "FeedFLstUsr";
};

string PnlIdecNavMaint::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(FEEDFLSTUSG)) ss.push_back("feedFLstUsg");
	if (has(FEEDFLSTUSR)) ss.push_back("feedFLstUsr");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavMaint::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecNavMaintData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (feedFLstUsg.readXML(docctx, basexpath, true)) add(FEEDFLSTUSG);
		if (feedFLstUsr.readXML(docctx, basexpath, true)) add(FEEDFLSTUSR);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		feedFLstUsg.clear();
		feedFLstUsr.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

