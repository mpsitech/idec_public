/**
  * \file DlgIdecTouNew_blks.cpp
  * job handler for job DlgIdecTouNew (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class DlgIdecTouNew::VecVDo
 ******************************************************************************/

uint DlgIdecTouNew::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butcncclick") return BUTCNCCLICK;
	else if (s == "butcreclick") return BUTCRECLICK;

	return(0);
};

string DlgIdecTouNew::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTCNCCLICK) return("ButCncClick");
	else if (ix == BUTCRECLICK) return("ButCreClick");

	return("");
};

/******************************************************************************
 class DlgIdecTouNew::VecVSge
 ******************************************************************************/

uint DlgIdecTouNew::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "create") return CREATE;
	else if (s == "done") return DONE;

	return(0);
};

string DlgIdecTouNew::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == CREATE) return("create");
	else if (ix == DONE) return("done");

	return("");
};

void DlgIdecTouNew::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class DlgIdecTouNew::ContIac
 ******************************************************************************/

DlgIdecTouNew::ContIac::ContIac(
			const uint numFDetPupMis
			, const string& DetTxfTit
			, const string& DetTxfAre
			, const string& DetTxfThe
			, const string& DetTxfPhi
		) : Block() {
	this->numFDetPupMis = numFDetPupMis;
	this->DetTxfTit = DetTxfTit;
	this->DetTxfAre = DetTxfAre;
	this->DetTxfThe = DetTxfThe;
	this->DetTxfPhi = DetTxfPhi;

	mask = {NUMFDETPUPMIS, DETTXFTIT, DETTXFARE, DETTXFTHE, DETTXFPHI};
};

bool DlgIdecTouNew::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacDlgIdecTouNew");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacDlgIdecTouNew";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFDetPupMis", numFDetPupMis)) add(NUMFDETPUPMIS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfTit", DetTxfTit)) add(DETTXFTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfAre", DetTxfAre)) add(DETTXFARE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfThe", DetTxfThe)) add(DETTXFTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "DetTxfPhi", DetTxfPhi)) add(DETTXFPHI);
	};

	return basefound;
};

void DlgIdecTouNew::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacDlgIdecTouNew";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacDlgIdecTouNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFDetPupMis", numFDetPupMis);
		writeStringAttr(wr, itemtag, "sref", "DetTxfTit", DetTxfTit);
		writeStringAttr(wr, itemtag, "sref", "DetTxfAre", DetTxfAre);
		writeStringAttr(wr, itemtag, "sref", "DetTxfThe", DetTxfThe);
		writeStringAttr(wr, itemtag, "sref", "DetTxfPhi", DetTxfPhi);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecTouNew::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFDetPupMis == comp->numFDetPupMis) insert(items, NUMFDETPUPMIS);
	if (DetTxfTit == comp->DetTxfTit) insert(items, DETTXFTIT);
	if (DetTxfAre == comp->DetTxfAre) insert(items, DETTXFARE);
	if (DetTxfThe == comp->DetTxfThe) insert(items, DETTXFTHE);
	if (DetTxfPhi == comp->DetTxfPhi) insert(items, DETTXFPHI);

	return(items);
};

set<uint> DlgIdecTouNew::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFDETPUPMIS, DETTXFTIT, DETTXFARE, DETTXFTHE, DETTXFPHI};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecTouNew::ContInf
 ******************************************************************************/

DlgIdecTouNew::ContInf::ContInf(
			const uint numFSge
		) : Block() {
	this->numFSge = numFSge;

	mask = {NUMFSGE};
};

void DlgIdecTouNew::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfDlgIdecTouNew";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfDlgIdecTouNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFSge", numFSge);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecTouNew::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);

	return(items);
};

set<uint> DlgIdecTouNew::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecTouNew::StatApp
 ******************************************************************************/

void DlgIdecTouNew::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const string& shortMenu
		) {
	if (difftag.length() == 0) difftag = "StatAppDlgIdecTouNew";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppDlgIdecTouNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "shortMenu", shortMenu);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecTouNew::StatShr
 ******************************************************************************/

DlgIdecTouNew::StatShr::StatShr(
			const bool DetPupMisActive
			, const bool ButCncActive
			, const bool ButCreActive
		) : Block() {
	this->DetPupMisActive = DetPupMisActive;
	this->ButCncActive = ButCncActive;
	this->ButCreActive = ButCreActive;

	mask = {DETPUPMISACTIVE, BUTCNCACTIVE, BUTCREACTIVE};
};

void DlgIdecTouNew::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrDlgIdecTouNew";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrDlgIdecTouNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "DetPupMisActive", DetPupMisActive);
		writeBoolAttr(wr, itemtag, "sref", "ButCncActive", ButCncActive);
		writeBoolAttr(wr, itemtag, "sref", "ButCreActive", ButCreActive);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecTouNew::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (DetPupMisActive == comp->DetPupMisActive) insert(items, DETPUPMISACTIVE);
	if (ButCncActive == comp->ButCncActive) insert(items, BUTCNCACTIVE);
	if (ButCreActive == comp->ButCreActive) insert(items, BUTCREACTIVE);

	return(items);
};

set<uint> DlgIdecTouNew::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {DETPUPMISACTIVE, BUTCNCACTIVE, BUTCREACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecTouNew::Tag
 ******************************************************************************/

void DlgIdecTouNew::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagDlgIdecTouNew";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemDlgIdecTouNew";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Create new tour");
			writeStringAttr(wr, itemtag, "sref", "DetCptMis", "Mission");
			writeStringAttr(wr, itemtag, "sref", "DetCptTit", "Name");
			writeStringAttr(wr, itemtag, "sref", "DetCptAre", "Area");
			writeStringAttr(wr, itemtag, "sref", "DetCptThe", "Latitude [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "DetCptPhi", "Longitude [\\u00b0]");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Neue Tour erstellen");
			writeStringAttr(wr, itemtag, "sref", "DetCptMis", "Mission");
			writeStringAttr(wr, itemtag, "sref", "DetCptTit", "Name");
			writeStringAttr(wr, itemtag, "sref", "DetCptAre", "Gebiet");
			writeStringAttr(wr, itemtag, "sref", "DetCptThe", "Breite [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "DetCptPhi", "L\\u00e4nge [\\u00b0]");
		};
		writeStringAttr(wr, itemtag, "sref", "ButCnc", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CANCEL, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButCre", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CREATE, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecTouNew::DpchAppData
 ******************************************************************************/

DlgIdecTouNew::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDATA) {
};

string DlgIdecTouNew::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecTouNew::DpchAppData::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string scrJref;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppDlgIdecTouNewData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) {
			jref = Scr::descramble(mScr, descr, scrJref);
			add(JREF);
		};
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
	} else {
		contiac = ContIac();
	};
};

/******************************************************************************
 class DlgIdecTouNew::DpchAppDo
 ******************************************************************************/

DlgIdecTouNew::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECTOUNEWDO) {
	ixVDo = 0;
};

string DlgIdecTouNew::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecTouNew::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppDlgIdecTouNewDo");
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
 class DlgIdecTouNew::DpchEngData
 ******************************************************************************/

DlgIdecTouNew::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFDetPupMis
			, Feed* feedFSge
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGDLGIDECTOUNEWDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFDETPUPMIS, FEEDFSGE, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFDETPUPMIS) && feedFDetPupMis) this->feedFDetPupMis = *feedFDetPupMis;
	if (find(this->mask, FEEDFSGE) && feedFSge) this->feedFSge = *feedFSge;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string DlgIdecTouNew::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFDETPUPMIS)) ss.push_back("feedFDetPupMis");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecTouNew::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFDETPUPMIS)) {feedFDetPupMis = src->feedFDetPupMis; add(FEEDFDETPUPMIS);};
	if (src->has(FEEDFSGE)) {feedFSge = src->feedFSge; add(FEEDFSGE);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void DlgIdecTouNew::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngDlgIdecTouNewData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFDETPUPMIS)) feedFDetPupMis.writeXML(wr);
		if (has(FEEDFSGE)) feedFSge.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

