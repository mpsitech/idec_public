/**
  * \file CrdIdecNav_blks.cpp
  * job handler for job CrdIdecNav (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

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

void CrdIdecNav::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
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

void CrdIdecNav::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecNav";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecNav";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFSge", numFSge);
		writeStringAttr(wr, itemtag, "sref", "MrlAppHlp", MrlAppHlp);
		writeStringAttr(wr, itemtag, "sref", "MtxSesSes1", MtxSesSes1);
		writeStringAttr(wr, itemtag, "sref", "MtxSesSes2", MtxSesSes2);
		writeStringAttr(wr, itemtag, "sref", "MtxSesSes3", MtxSesSes3);
	xmlTextWriterEndElement(wr);
};

set<uint> CrdIdecNav::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp == comp->MrlAppHlp) insert(items, MRLAPPHLP);
	if (MtxSesSes1 == comp->MtxSesSes1) insert(items, MTXSESSES1);
	if (MtxSesSes2 == comp->MtxSesSes2) insert(items, MTXSESSES2);
	if (MtxSesSes3 == comp->MtxSesSes3) insert(items, MTXSESSES3);

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

void CrdIdecNav::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneHeadbar
			, const bool initdonePre
			, const bool initdoneMaint
			, const bool initdoneOpr
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecNav";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecNav";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVReqitmode", VecIdecVReqitmode::getSref(ixIdecVReqitmode));
		writeUsmallintAttr(wr, itemtag, "sref", "latency", latency);
		writeStringAttr(wr, itemtag, "sref", "shortMenu", shortMenu);
		writeUintAttr(wr, itemtag, "sref", "widthMenu", widthMenu);
		writeBoolAttr(wr, itemtag, "sref", "initdoneHeadbar", initdoneHeadbar);
		writeBoolAttr(wr, itemtag, "sref", "initdonePre", initdonePre);
		writeBoolAttr(wr, itemtag, "sref", "initdoneMaint", initdoneMaint);
		writeBoolAttr(wr, itemtag, "sref", "initdoneOpr", initdoneOpr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecNav::StatShr
 ******************************************************************************/

CrdIdecNav::StatShr::StatShr(
			const ubigint jrefDlgloaini
			, const ubigint jrefHeadbar
			, const ubigint jrefPre
			, const bool pnlpreAvail
			, const ubigint jrefMaint
			, const bool pnlmaintAvail
			, const ubigint jrefOpr
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
	this->jrefDlgloaini = jrefDlgloaini;
	this->jrefHeadbar = jrefHeadbar;
	this->jrefPre = jrefPre;
	this->pnlpreAvail = pnlpreAvail;
	this->jrefMaint = jrefMaint;
	this->pnlmaintAvail = pnlmaintAvail;
	this->jrefOpr = jrefOpr;
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

	mask = {JREFDLGLOAINI, JREFHEADBAR, JREFPRE, PNLPREAVAIL, JREFMAINT, PNLMAINTAVAIL, JREFOPR, PNLOPRAVAIL, MSPCRD1AVAIL, MITCRDUSGAVAIL, MITCRDUSRAVAIL, MITCRDSCFAVAIL, MITCRDUTLAVAIL, MSPCRD2AVAIL, MITCRDMISAVAIL, MITCRDTOUAVAIL, MITCRDIAQAVAIL, MITCRDIAQACTIVE, MITCRDAD1AVAIL, MITCRDAD1ACTIVE, MITCRDFILAVAIL, MSPAPP2AVAIL, MITAPPLOIAVAIL};
};

void CrdIdecNav::StatShr::writeXML(
			pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecNav";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecNav";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgloaini", Scr::scramble(mScr, scr, descr, jrefDlgloaini));
		writeStringAttr(wr, itemtag, "sref", "scrJrefHeadbar", Scr::scramble(mScr, scr, descr, jrefHeadbar));
		writeStringAttr(wr, itemtag, "sref", "scrJrefPre", Scr::scramble(mScr, scr, descr, jrefPre));
		writeBoolAttr(wr, itemtag, "sref", "pnlpreAvail", pnlpreAvail);
		writeStringAttr(wr, itemtag, "sref", "scrJrefMaint", Scr::scramble(mScr, scr, descr, jrefMaint));
		writeBoolAttr(wr, itemtag, "sref", "pnlmaintAvail", pnlmaintAvail);
		writeStringAttr(wr, itemtag, "sref", "scrJrefOpr", Scr::scramble(mScr, scr, descr, jrefOpr));
		writeBoolAttr(wr, itemtag, "sref", "pnloprAvail", pnloprAvail);
		writeBoolAttr(wr, itemtag, "sref", "MspCrd1Avail", MspCrd1Avail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdUsgAvail", MitCrdUsgAvail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdUsrAvail", MitCrdUsrAvail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdScfAvail", MitCrdScfAvail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdUtlAvail", MitCrdUtlAvail);
		writeBoolAttr(wr, itemtag, "sref", "MspCrd2Avail", MspCrd2Avail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdMisAvail", MitCrdMisAvail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdTouAvail", MitCrdTouAvail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdIaqAvail", MitCrdIaqAvail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdIaqActive", MitCrdIaqActive);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdAd1Avail", MitCrdAd1Avail);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdAd1Active", MitCrdAd1Active);
		writeBoolAttr(wr, itemtag, "sref", "MitCrdFilAvail", MitCrdFilAvail);
		writeBoolAttr(wr, itemtag, "sref", "MspApp2Avail", MspApp2Avail);
		writeBoolAttr(wr, itemtag, "sref", "MitAppLoiAvail", MitAppLoiAvail);
	xmlTextWriterEndElement(wr);
};

set<uint> CrdIdecNav::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (jrefDlgloaini == comp->jrefDlgloaini) insert(items, JREFDLGLOAINI);
	if (jrefHeadbar == comp->jrefHeadbar) insert(items, JREFHEADBAR);
	if (jrefPre == comp->jrefPre) insert(items, JREFPRE);
	if (pnlpreAvail == comp->pnlpreAvail) insert(items, PNLPREAVAIL);
	if (jrefMaint == comp->jrefMaint) insert(items, JREFMAINT);
	if (pnlmaintAvail == comp->pnlmaintAvail) insert(items, PNLMAINTAVAIL);
	if (jrefOpr == comp->jrefOpr) insert(items, JREFOPR);
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

	diffitems = {JREFDLGLOAINI, JREFHEADBAR, JREFPRE, PNLPREAVAIL, JREFMAINT, PNLMAINTAVAIL, JREFOPR, PNLOPRAVAIL, MSPCRD1AVAIL, MITCRDUSGAVAIL, MITCRDUSRAVAIL, MITCRDSCFAVAIL, MITCRDUTLAVAIL, MSPCRD2AVAIL, MITCRDMISAVAIL, MITCRDTOUAVAIL, MITCRDIAQAVAIL, MITCRDIAQACTIVE, MITCRDAD1AVAIL, MITCRDAD1ACTIVE, MITCRDFILAVAIL, MSPAPP2AVAIL, MITAPPLOIAVAIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecNav::Tag
 ******************************************************************************/

void CrdIdecNav::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecNav";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecNav";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "MitCrdUsg", "User groups ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdUsr", "Users ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdScf", "System configuration ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdUtl", "Utilities ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdMis", "Missions ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdTou", "Tours ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdIaq", "Image acquisition ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdAd1", "Autonomous detection 1 ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdFil", "Files ...");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "MitCrdUsg", "Benutzergruppen ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdUsr", "Benutzer ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdScf", "Systemkonfiguration ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdUtl", "Dienstprogramme ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdMis", "Missionen ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdTou", "Touren ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdIaq", "Bilderfassung ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdAd1", "Autonome Detektion 1 ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdFil", "Dateien ...");
		};
		writeStringAttr(wr, itemtag, "sref", "MitAppAbt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::ABOUT, ixIdecVLocale)) + " ...");
		writeStringAttr(wr, itemtag, "sref", "MrlAppHlp", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::HELP, ixIdecVLocale)) + " ...");
		writeStringAttr(wr, itemtag, "sref", "MitSesTrm", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLSESS, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "MitAppLoi", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::LOAINI, ixIdecVLocale)) + " ...");
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecNav::DpchAppDo
 ******************************************************************************/

CrdIdecNav::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVDO) {
	ixVDo = 0;
};

string CrdIdecNav::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecNav::DpchAppDo::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string scrJref;
	string srefIxVDo;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecNavDo");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) {
			jref = Scr::descramble(mScr, descr, scrJref);
			add(JREF);
		};
		if (extractStringUclc(docctx, basexpath, "srefIxVDo", "", srefIxVDo)) {
			ixVDo = VecVDo::getIx(srefIxVDo);
			add(IXVDO);
		};
	} else {
	};
};

/******************************************************************************
 class CrdIdecNav::DpchEngData
 ******************************************************************************/

CrdIdecNav::DpchEngData::DpchEngData(
			const ubigint jref
			, ContInf* continf
			, Feed* feedFSge
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, FEEDFSGE, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFSGE) && feedFSge) this->feedFSge = *feedFSge;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string CrdIdecNav::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecNav::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFSGE)) {feedFSge = src->feedFSge; add(FEEDFSGE);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void CrdIdecNav::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecNavData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFSGE)) feedFSge.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(mScr, scr, descr, wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

