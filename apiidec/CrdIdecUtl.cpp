/**
  * \file CrdIdecUtl.cpp
  * API code for job CrdIdecUtl (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "CrdIdecUtl.h"

/******************************************************************************
 class CrdIdecUtl::VecVDo
 ******************************************************************************/

uint CrdIdecUtl::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "close") return CLOSE;
	else if (s == "mitappabtclick") return MITAPPABTCLICK;
	else if (s == "mitcrdtheclick") return MITCRDTHECLICK;
	else if (s == "mitcrdphiclick") return MITCRDPHICLICK;
	else if (s == "mitcrdsteclick") return MITCRDSTECLICK;
	else if (s == "mitcrdfsnclick") return MITCRDFSNCLICK;
	else if (s == "mitcrdqnuclick") return MITCRDQNUCLICK;
	else if (s == "mitcrdqalclick") return MITCRDQALCLICK;

	return(0);
};

string CrdIdecUtl::VecVDo::getSref(
			const uint ix
		) {
	if (ix == CLOSE) return("close");
	else if (ix == MITAPPABTCLICK) return("MitAppAbtClick");
	else if (ix == MITCRDTHECLICK) return("MitCrdTheClick");
	else if (ix == MITCRDPHICLICK) return("MitCrdPhiClick");
	else if (ix == MITCRDSTECLICK) return("MitCrdSteClick");
	else if (ix == MITCRDFSNCLICK) return("MitCrdFsnClick");
	else if (ix == MITCRDQNUCLICK) return("MitCrdQnuClick");
	else if (ix == MITCRDQALCLICK) return("MitCrdQalClick");

	return("");
};

/******************************************************************************
 class CrdIdecUtl::VecVSge
 ******************************************************************************/

uint CrdIdecUtl::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alridecabt") return ALRIDECABT;
	else if (s == "close") return CLOSE;

	return(0);
};

string CrdIdecUtl::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRIDECABT) return("alridecabt");
	else if (ix == CLOSE) return("close");

	return("");
};

/******************************************************************************
 class CrdIdecUtl::ContInf
 ******************************************************************************/

CrdIdecUtl::ContInf::ContInf(
			const uint numFSge
			, const string& MrlAppHlp
		) : Block() {
	this->numFSge = numFSge;
	this->MrlAppHlp = MrlAppHlp;

	mask = {NUMFSGE, MRLAPPHLP};
};

bool CrdIdecUtl::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecUtl");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecUtl";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
	};

	return basefound;
};

set<uint> CrdIdecUtl::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp.compare(comp->MrlAppHlp) == 0) insert(items, MRLAPPHLP);

	return(items);
};

set<uint> CrdIdecUtl::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE, MRLAPPHLP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecUtl::StatApp
 ******************************************************************************/

CrdIdecUtl::StatApp::StatApp(
			const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneSpiterm
			, const bool initdoneHeadbar
		) : Block() {
	this->ixIdecVReqitmode = ixIdecVReqitmode;
	this->latency = latency;
	this->shortMenu = shortMenu;
	this->widthMenu = widthMenu;
	this->initdoneSpiterm = initdoneSpiterm;
	this->initdoneHeadbar = initdoneHeadbar;

	mask = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONESPITERM, INITDONEHEADBAR};
};

bool CrdIdecUtl::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVReqitmode;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecUtl");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecUtl";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVReqitmode", srefIxIdecVReqitmode)) {
			ixIdecVReqitmode = VecIdecVReqitmode::getIx(srefIxIdecVReqitmode);
			add(IXIDECVREQITMODE);
		};
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "latency", latency)) add(LATENCY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "shortMenu", shortMenu)) add(SHORTMENU);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "widthMenu", widthMenu)) add(WIDTHMENU);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneSpiterm", initdoneSpiterm)) add(INITDONESPITERM);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneHeadbar", initdoneHeadbar)) add(INITDONEHEADBAR);
	};

	return basefound;
};

set<uint> CrdIdecUtl::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVReqitmode == comp->ixIdecVReqitmode) insert(items, IXIDECVREQITMODE);
	if (latency == comp->latency) insert(items, LATENCY);
	if (shortMenu.compare(comp->shortMenu) == 0) insert(items, SHORTMENU);
	if (widthMenu == comp->widthMenu) insert(items, WIDTHMENU);
	if (initdoneSpiterm == comp->initdoneSpiterm) insert(items, INITDONESPITERM);
	if (initdoneHeadbar == comp->initdoneHeadbar) insert(items, INITDONEHEADBAR);

	return(items);
};

set<uint> CrdIdecUtl::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONESPITERM, INITDONEHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecUtl::StatShr
 ******************************************************************************/

CrdIdecUtl::StatShr::StatShr(
			const string& scrJrefDlgfusion
			, const string& scrJrefDlgphi
			, const string& scrJrefDlgqcdaln
			, const string& scrJrefDlgqcdnuc
			, const string& scrJrefDlgstereo
			, const string& scrJrefDlgtheta
			, const string& scrJrefSpiterm
			, const string& scrJrefHeadbar
		) : Block() {
	this->scrJrefDlgfusion = scrJrefDlgfusion;
	this->scrJrefDlgphi = scrJrefDlgphi;
	this->scrJrefDlgqcdaln = scrJrefDlgqcdaln;
	this->scrJrefDlgqcdnuc = scrJrefDlgqcdnuc;
	this->scrJrefDlgstereo = scrJrefDlgstereo;
	this->scrJrefDlgtheta = scrJrefDlgtheta;
	this->scrJrefSpiterm = scrJrefSpiterm;
	this->scrJrefHeadbar = scrJrefHeadbar;

	mask = {SCRJREFDLGFUSION, SCRJREFDLGPHI, SCRJREFDLGQCDALN, SCRJREFDLGQCDNUC, SCRJREFDLGSTEREO, SCRJREFDLGTHETA, SCRJREFSPITERM, SCRJREFHEADBAR};
};

bool CrdIdecUtl::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecUtl");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecUtl";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgfusion", scrJrefDlgfusion)) add(SCRJREFDLGFUSION);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgphi", scrJrefDlgphi)) add(SCRJREFDLGPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgqcdaln", scrJrefDlgqcdaln)) add(SCRJREFDLGQCDALN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgqcdnuc", scrJrefDlgqcdnuc)) add(SCRJREFDLGQCDNUC);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgstereo", scrJrefDlgstereo)) add(SCRJREFDLGSTEREO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgtheta", scrJrefDlgtheta)) add(SCRJREFDLGTHETA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefSpiterm", scrJrefSpiterm)) add(SCRJREFSPITERM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefHeadbar", scrJrefHeadbar)) add(SCRJREFHEADBAR);
	};

	return basefound;
};

set<uint> CrdIdecUtl::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (scrJrefDlgfusion.compare(comp->scrJrefDlgfusion) == 0) insert(items, SCRJREFDLGFUSION);
	if (scrJrefDlgphi.compare(comp->scrJrefDlgphi) == 0) insert(items, SCRJREFDLGPHI);
	if (scrJrefDlgqcdaln.compare(comp->scrJrefDlgqcdaln) == 0) insert(items, SCRJREFDLGQCDALN);
	if (scrJrefDlgqcdnuc.compare(comp->scrJrefDlgqcdnuc) == 0) insert(items, SCRJREFDLGQCDNUC);
	if (scrJrefDlgstereo.compare(comp->scrJrefDlgstereo) == 0) insert(items, SCRJREFDLGSTEREO);
	if (scrJrefDlgtheta.compare(comp->scrJrefDlgtheta) == 0) insert(items, SCRJREFDLGTHETA);
	if (scrJrefSpiterm.compare(comp->scrJrefSpiterm) == 0) insert(items, SCRJREFSPITERM);
	if (scrJrefHeadbar.compare(comp->scrJrefHeadbar) == 0) insert(items, SCRJREFHEADBAR);

	return(items);
};

set<uint> CrdIdecUtl::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SCRJREFDLGFUSION, SCRJREFDLGPHI, SCRJREFDLGQCDALN, SCRJREFDLGQCDNUC, SCRJREFDLGSTEREO, SCRJREFDLGTHETA, SCRJREFSPITERM, SCRJREFHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecUtl::Tag
 ******************************************************************************/

CrdIdecUtl::Tag::Tag(
			const string& MitAppAbt
			, const string& MrlAppHlp
			, const string& MitCrdThe
			, const string& MitCrdPhi
			, const string& MitCrdSte
			, const string& MitCrdFsn
			, const string& MitCrdQnu
			, const string& MitCrdQal
		) : Block() {
	this->MitAppAbt = MitAppAbt;
	this->MrlAppHlp = MrlAppHlp;
	this->MitCrdThe = MitCrdThe;
	this->MitCrdPhi = MitCrdPhi;
	this->MitCrdSte = MitCrdSte;
	this->MitCrdFsn = MitCrdFsn;
	this->MitCrdQnu = MitCrdQnu;
	this->MitCrdQal = MitCrdQal;

	mask = {MITAPPABT, MRLAPPHLP, MITCRDTHE, MITCRDPHI, MITCRDSTE, MITCRDFSN, MITCRDQNU, MITCRDQAL};
};

bool CrdIdecUtl::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecUtl");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecUtl";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitAppAbt", MitAppAbt)) add(MITAPPABT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdThe", MitCrdThe)) add(MITCRDTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdPhi", MitCrdPhi)) add(MITCRDPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdSte", MitCrdSte)) add(MITCRDSTE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdFsn", MitCrdFsn)) add(MITCRDFSN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdQnu", MitCrdQnu)) add(MITCRDQNU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdQal", MitCrdQal)) add(MITCRDQAL);
	};

	return basefound;
};

/******************************************************************************
 class CrdIdecUtl::DpchAppDo
 ******************************************************************************/

CrdIdecUtl::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUTLDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string CrdIdecUtl::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecUtl::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecUtlDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecUtl::DpchEngData
 ******************************************************************************/

CrdIdecUtl::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUTLDATA) {
	feedFSge.tag = "FeedFSge";
};

string CrdIdecUtl::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecUtl::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecUtlData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFSge.readXML(docctx, basexpath, true)) add(FEEDFSGE);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		continf = ContInf();
		feedFSge.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

