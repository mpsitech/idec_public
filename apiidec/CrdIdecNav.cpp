/**
  * \file CrdIdecNav.cpp
  * API code for job CrdIdecNav (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "CrdIdecNav.h"

/******************************************************************************
 class CrdIdecNav::VecVDo
 ******************************************************************************/

uint CrdIdecNav::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "close") return CLOSE;
	else if (s == "mitappabtclick") return MITAPPABTCLICK;
	else if (s == "mitsestrmclick") return MITSESTRMCLICK;
	else if (s == "mitcrdusgclick") return MITCRDUSGCLICK;
	else if (s == "mitcrdusrclick") return MITCRDUSRCLICK;
	else if (s == "mitcrdscfclick") return MITCRDSCFCLICK;
	else if (s == "mitcrdutlclick") return MITCRDUTLCLICK;
	else if (s == "mitcrdmisclick") return MITCRDMISCLICK;
	else if (s == "mitcrdtouclick") return MITCRDTOUCLICK;
	else if (s == "mitcrdiaqclick") return MITCRDIAQCLICK;
	else if (s == "mitcrdad1click") return MITCRDAD1CLICK;
	else if (s == "mitcrdfilclick") return MITCRDFILCLICK;
	else if (s == "mitapploiclick") return MITAPPLOICLICK;

	return(0);
};

string CrdIdecNav::VecVDo::getSref(
			const uint ix
		) {
	if (ix == CLOSE) return("close");
	else if (ix == MITAPPABTCLICK) return("MitAppAbtClick");
	else if (ix == MITSESTRMCLICK) return("MitSesTrmClick");
	else if (ix == MITCRDUSGCLICK) return("MitCrdUsgClick");
	else if (ix == MITCRDUSRCLICK) return("MitCrdUsrClick");
	else if (ix == MITCRDSCFCLICK) return("MitCrdScfClick");
	else if (ix == MITCRDUTLCLICK) return("MitCrdUtlClick");
	else if (ix == MITCRDMISCLICK) return("MitCrdMisClick");
	else if (ix == MITCRDTOUCLICK) return("MitCrdTouClick");
	else if (ix == MITCRDIAQCLICK) return("MitCrdIaqClick");
	else if (ix == MITCRDAD1CLICK) return("MitCrdAd1Click");
	else if (ix == MITCRDFILCLICK) return("MitCrdFilClick");
	else if (ix == MITAPPLOICLICK) return("MitAppLoiClick");

	return("");
};

/******************************************************************************
 class CrdIdecNav::VecVSge
 ******************************************************************************/

uint CrdIdecNav::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alridecabt") return ALRIDECABT;
	else if (s == "close") return CLOSE;

	return(0);
};

string CrdIdecNav::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRIDECABT) return("alridecabt");
	else if (ix == CLOSE) return("close");

	return("");
};

/******************************************************************************
 class CrdIdecNav::ContInf
 ******************************************************************************/

CrdIdecNav::ContInf::ContInf(
			const uint numFSge
			, const string& MrlAppHlp
			, const string& MtxSesSes1
			, const string& MtxSesSes2
			, const string& MtxSesSes3
		) : Block() {
	this->numFSge = numFSge;
	this->MrlAppHlp = MrlAppHlp;
	this->MtxSesSes1 = MtxSesSes1;
	this->MtxSesSes2 = MtxSesSes2;
	this->MtxSesSes3 = MtxSesSes3;

	mask = {NUMFSGE, MRLAPPHLP, MTXSESSES1, MTXSESSES2, MTXSESSES3};
};

bool CrdIdecNav::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecNav");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecNav";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFSge", numFSge)) add(NUMFSGE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MtxSesSes1", MtxSesSes1)) add(MTXSESSES1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MtxSesSes2", MtxSesSes2)) add(MTXSESSES2);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "MtxSesSes3", MtxSesSes3)) add(MTXSESSES3);
	};

	return basefound;
};

set<uint> CrdIdecNav::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp.compare(comp->MrlAppHlp) == 0) insert(items, MRLAPPHLP);
	if (MtxSesSes1.compare(comp->MtxSesSes1) == 0) insert(items, MTXSESSES1);
	if (MtxSesSes2.compare(comp->MtxSesSes2) == 0) insert(items, MTXSESSES2);
	if (MtxSesSes3.compare(comp->MtxSesSes3) == 0) insert(items, MTXSESSES3);

	return(items);
};

set<uint> CrdIdecNav::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE, MRLAPPHLP, MTXSESSES1, MTXSESSES2, MTXSESSES3};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecNav::StatApp
 ******************************************************************************/

CrdIdecNav::StatApp::StatApp(
			const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneHeadbar
			, const bool initdonePre
			, const bool initdoneMaint
			, const bool initdoneOpr
		) : Block() {
	this->ixIdecVReqitmode = ixIdecVReqitmode;
	this->latency = latency;
	this->shortMenu = shortMenu;
	this->widthMenu = widthMenu;
	this->initdoneHeadbar = initdoneHeadbar;
	this->initdonePre = initdonePre;
	this->initdoneMaint = initdoneMaint;
	this->initdoneOpr = initdoneOpr;

	mask = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONEHEADBAR, INITDONEPRE, INITDONEMAINT, INITDONEOPR};
};

bool CrdIdecNav::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVReqitmode;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecNav");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecNav";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVReqitmode", srefIxIdecVReqitmode)) {
			ixIdecVReqitmode = VecIdecVReqitmode::getIx(srefIxIdecVReqitmode);
			add(IXIDECVREQITMODE);
		};
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "latency", latency)) add(LATENCY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "shortMenu", shortMenu)) add(SHORTMENU);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "widthMenu", widthMenu)) add(WIDTHMENU);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneHeadbar", initdoneHeadbar)) add(INITDONEHEADBAR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdonePre", initdonePre)) add(INITDONEPRE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneMaint", initdoneMaint)) add(INITDONEMAINT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "initdoneOpr", initdoneOpr)) add(INITDONEOPR);
	};

	return basefound;
};

set<uint> CrdIdecNav::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVReqitmode == comp->ixIdecVReqitmode) insert(items, IXIDECVREQITMODE);
	if (latency == comp->latency) insert(items, LATENCY);
	if (shortMenu.compare(comp->shortMenu) == 0) insert(items, SHORTMENU);
	if (widthMenu == comp->widthMenu) insert(items, WIDTHMENU);
	if (initdoneHeadbar == comp->initdoneHeadbar) insert(items, INITDONEHEADBAR);
	if (initdonePre == comp->initdonePre) insert(items, INITDONEPRE);
	if (initdoneMaint == comp->initdoneMaint) insert(items, INITDONEMAINT);
	if (initdoneOpr == comp->initdoneOpr) insert(items, INITDONEOPR);

	return(items);
};

set<uint> CrdIdecNav::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVREQITMODE, LATENCY, SHORTMENU, WIDTHMENU, INITDONEHEADBAR, INITDONEPRE, INITDONEMAINT, INITDONEOPR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecNav::StatShr
 ******************************************************************************/

CrdIdecNav::StatShr::StatShr(
			const string& scrJrefDlgloaini
			, const string& scrJrefHeadbar
			, const string& scrJrefPre
			, const bool pnlpreAvail
			, const string& scrJrefMaint
			, const bool pnlmaintAvail
			, const string& scrJrefOpr
			, const bool pnloprAvail
			, const bool MspCrd1Avail
			, const bool MitCrdUsgAvail
			, const bool MitCrdUsrAvail
			, const bool MitCrdScfAvail
			, const bool MitCrdUtlAvail
			, const bool MspCrd2Avail
			, const bool MitCrdMisAvail
			, const bool MitCrdTouAvail
			, const bool MitCrdIaqAvail
			, const bool MitCrdIaqActive
			, const bool MitCrdAd1Avail
			, const bool MitCrdAd1Active
			, const bool MitCrdFilAvail
			, const bool MspApp2Avail
			, const bool MitAppLoiAvail
		) : Block() {
	this->scrJrefDlgloaini = scrJrefDlgloaini;
	this->scrJrefHeadbar = scrJrefHeadbar;
	this->scrJrefPre = scrJrefPre;
	this->pnlpreAvail = pnlpreAvail;
	this->scrJrefMaint = scrJrefMaint;
	this->pnlmaintAvail = pnlmaintAvail;
	this->scrJrefOpr = scrJrefOpr;
	this->pnloprAvail = pnloprAvail;
	this->MspCrd1Avail = MspCrd1Avail;
	this->MitCrdUsgAvail = MitCrdUsgAvail;
	this->MitCrdUsrAvail = MitCrdUsrAvail;
	this->MitCrdScfAvail = MitCrdScfAvail;
	this->MitCrdUtlAvail = MitCrdUtlAvail;
	this->MspCrd2Avail = MspCrd2Avail;
	this->MitCrdMisAvail = MitCrdMisAvail;
	this->MitCrdTouAvail = MitCrdTouAvail;
	this->MitCrdIaqAvail = MitCrdIaqAvail;
	this->MitCrdIaqActive = MitCrdIaqActive;
	this->MitCrdAd1Avail = MitCrdAd1Avail;
	this->MitCrdAd1Active = MitCrdAd1Active;
	this->MitCrdFilAvail = MitCrdFilAvail;
	this->MspApp2Avail = MspApp2Avail;
	this->MitAppLoiAvail = MitAppLoiAvail;

	mask = {SCRJREFDLGLOAINI, SCRJREFHEADBAR, SCRJREFPRE, PNLPREAVAIL, SCRJREFMAINT, PNLMAINTAVAIL, SCRJREFOPR, PNLOPRAVAIL, MSPCRD1AVAIL, MITCRDUSGAVAIL, MITCRDUSRAVAIL, MITCRDSCFAVAIL, MITCRDUTLAVAIL, MSPCRD2AVAIL, MITCRDMISAVAIL, MITCRDTOUAVAIL, MITCRDIAQAVAIL, MITCRDIAQACTIVE, MITCRDAD1AVAIL, MITCRDAD1ACTIVE, MITCRDFILAVAIL, MSPAPP2AVAIL, MITAPPLOIAVAIL};
};

bool CrdIdecNav::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecNav");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecNav";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefDlgloaini", scrJrefDlgloaini)) add(SCRJREFDLGLOAINI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefHeadbar", scrJrefHeadbar)) add(SCRJREFHEADBAR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefPre", scrJrefPre)) add(SCRJREFPRE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "pnlpreAvail", pnlpreAvail)) add(PNLPREAVAIL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefMaint", scrJrefMaint)) add(SCRJREFMAINT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "pnlmaintAvail", pnlmaintAvail)) add(PNLMAINTAVAIL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "scrJrefOpr", scrJrefOpr)) add(SCRJREFOPR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "pnloprAvail", pnloprAvail)) add(PNLOPRAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MspCrd1Avail", MspCrd1Avail)) add(MSPCRD1AVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdUsgAvail", MitCrdUsgAvail)) add(MITCRDUSGAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdUsrAvail", MitCrdUsrAvail)) add(MITCRDUSRAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdScfAvail", MitCrdScfAvail)) add(MITCRDSCFAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdUtlAvail", MitCrdUtlAvail)) add(MITCRDUTLAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MspCrd2Avail", MspCrd2Avail)) add(MSPCRD2AVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdMisAvail", MitCrdMisAvail)) add(MITCRDMISAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdTouAvail", MitCrdTouAvail)) add(MITCRDTOUAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdIaqAvail", MitCrdIaqAvail)) add(MITCRDIAQAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdIaqActive", MitCrdIaqActive)) add(MITCRDIAQACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdAd1Avail", MitCrdAd1Avail)) add(MITCRDAD1AVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdAd1Active", MitCrdAd1Active)) add(MITCRDAD1ACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitCrdFilAvail", MitCrdFilAvail)) add(MITCRDFILAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MspApp2Avail", MspApp2Avail)) add(MSPAPP2AVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "MitAppLoiAvail", MitAppLoiAvail)) add(MITAPPLOIAVAIL);
	};

	return basefound;
};

set<uint> CrdIdecNav::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (scrJrefDlgloaini.compare(comp->scrJrefDlgloaini) == 0) insert(items, SCRJREFDLGLOAINI);
	if (scrJrefHeadbar.compare(comp->scrJrefHeadbar) == 0) insert(items, SCRJREFHEADBAR);
	if (scrJrefPre.compare(comp->scrJrefPre) == 0) insert(items, SCRJREFPRE);
	if (pnlpreAvail == comp->pnlpreAvail) insert(items, PNLPREAVAIL);
	if (scrJrefMaint.compare(comp->scrJrefMaint) == 0) insert(items, SCRJREFMAINT);
	if (pnlmaintAvail == comp->pnlmaintAvail) insert(items, PNLMAINTAVAIL);
	if (scrJrefOpr.compare(comp->scrJrefOpr) == 0) insert(items, SCRJREFOPR);
	if (pnloprAvail == comp->pnloprAvail) insert(items, PNLOPRAVAIL);
	if (MspCrd1Avail == comp->MspCrd1Avail) insert(items, MSPCRD1AVAIL);
	if (MitCrdUsgAvail == comp->MitCrdUsgAvail) insert(items, MITCRDUSGAVAIL);
	if (MitCrdUsrAvail == comp->MitCrdUsrAvail) insert(items, MITCRDUSRAVAIL);
	if (MitCrdScfAvail == comp->MitCrdScfAvail) insert(items, MITCRDSCFAVAIL);
	if (MitCrdUtlAvail == comp->MitCrdUtlAvail) insert(items, MITCRDUTLAVAIL);
	if (MspCrd2Avail == comp->MspCrd2Avail) insert(items, MSPCRD2AVAIL);
	if (MitCrdMisAvail == comp->MitCrdMisAvail) insert(items, MITCRDMISAVAIL);
	if (MitCrdTouAvail == comp->MitCrdTouAvail) insert(items, MITCRDTOUAVAIL);
	if (MitCrdIaqAvail == comp->MitCrdIaqAvail) insert(items, MITCRDIAQAVAIL);
	if (MitCrdIaqActive == comp->MitCrdIaqActive) insert(items, MITCRDIAQACTIVE);
	if (MitCrdAd1Avail == comp->MitCrdAd1Avail) insert(items, MITCRDAD1AVAIL);
	if (MitCrdAd1Active == comp->MitCrdAd1Active) insert(items, MITCRDAD1ACTIVE);
	if (MitCrdFilAvail == comp->MitCrdFilAvail) insert(items, MITCRDFILAVAIL);
	if (MspApp2Avail == comp->MspApp2Avail) insert(items, MSPAPP2AVAIL);
	if (MitAppLoiAvail == comp->MitAppLoiAvail) insert(items, MITAPPLOIAVAIL);

	return(items);
};

set<uint> CrdIdecNav::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SCRJREFDLGLOAINI, SCRJREFHEADBAR, SCRJREFPRE, PNLPREAVAIL, SCRJREFMAINT, PNLMAINTAVAIL, SCRJREFOPR, PNLOPRAVAIL, MSPCRD1AVAIL, MITCRDUSGAVAIL, MITCRDUSRAVAIL, MITCRDSCFAVAIL, MITCRDUTLAVAIL, MSPCRD2AVAIL, MITCRDMISAVAIL, MITCRDTOUAVAIL, MITCRDIAQAVAIL, MITCRDIAQACTIVE, MITCRDAD1AVAIL, MITCRDAD1ACTIVE, MITCRDFILAVAIL, MSPAPP2AVAIL, MITAPPLOIAVAIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecNav::Tag
 ******************************************************************************/

CrdIdecNav::Tag::Tag(
			const string& MitAppAbt
			, const string& MrlAppHlp
			, const string& MitSesTrm
			, const string& MitCrdUsg
			, const string& MitCrdUsr
			, const string& MitCrdScf
			, const string& MitCrdUtl
			, const string& MitCrdMis
			, const string& MitCrdTou
			, const string& MitCrdIaq
			, const string& MitCrdAd1
			, const string& MitCrdFil
			, const string& MitAppLoi
		) : Block() {
	this->MitAppAbt = MitAppAbt;
	this->MrlAppHlp = MrlAppHlp;
	this->MitSesTrm = MitSesTrm;
	this->MitCrdUsg = MitCrdUsg;
	this->MitCrdUsr = MitCrdUsr;
	this->MitCrdScf = MitCrdScf;
	this->MitCrdUtl = MitCrdUtl;
	this->MitCrdMis = MitCrdMis;
	this->MitCrdTou = MitCrdTou;
	this->MitCrdIaq = MitCrdIaq;
	this->MitCrdAd1 = MitCrdAd1;
	this->MitCrdFil = MitCrdFil;
	this->MitAppLoi = MitAppLoi;

	mask = {MITAPPABT, MRLAPPHLP, MITSESTRM, MITCRDUSG, MITCRDUSR, MITCRDSCF, MITCRDUTL, MITCRDMIS, MITCRDTOU, MITCRDIAQ, MITCRDAD1, MITCRDFIL, MITAPPLOI};
};

bool CrdIdecNav::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecNav");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecNav";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitAppAbt", MitAppAbt)) add(MITAPPABT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MrlAppHlp", MrlAppHlp)) add(MRLAPPHLP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitSesTrm", MitSesTrm)) add(MITSESTRM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdUsg", MitCrdUsg)) add(MITCRDUSG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdUsr", MitCrdUsr)) add(MITCRDUSR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdScf", MitCrdScf)) add(MITCRDSCF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdUtl", MitCrdUtl)) add(MITCRDUTL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdMis", MitCrdMis)) add(MITCRDMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdTou", MitCrdTou)) add(MITCRDTOU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdIaq", MitCrdIaq)) add(MITCRDIAQ);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdAd1", MitCrdAd1)) add(MITCRDAD1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitCrdFil", MitCrdFil)) add(MITCRDFIL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "MitAppLoi", MitAppLoi)) add(MITAPPLOI);
	};

	return basefound;
};

/******************************************************************************
 class CrdIdecNav::DpchAppDo
 ******************************************************************************/

CrdIdecNav::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string CrdIdecNav::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecNav::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecNavDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecNav::DpchEngData
 ******************************************************************************/

CrdIdecNav::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVDATA) {
	feedFSge.tag = "FeedFSge";
};

string CrdIdecNav::DpchEngData::getSrefsMask() {
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

void CrdIdecNav::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecNavData");
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

