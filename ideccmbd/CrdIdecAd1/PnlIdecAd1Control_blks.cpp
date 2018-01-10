/**
  * \file PnlIdecAd1Control_blks.cpp
  * job handler for job PnlIdecAd1Control (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecAd1Control::VecVDo
 ******************************************************************************/

uint PnlIdecAd1Control::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "butrunclick") return BUTRUNCLICK;
	else if (s == "butstoclick") return BUTSTOCLICK;

	return(0);
};

string PnlIdecAd1Control::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTRUNCLICK) return("ButRunClick");
	else if (ix == BUTSTOCLICK) return("ButStoClick");

	return("");
};

/******************************************************************************
 class PnlIdecAd1Control::VecVSge
 ******************************************************************************/

uint PnlIdecAd1Control::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alrgum") return ALRGUM;

	return(0);
};

string PnlIdecAd1Control::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRGUM) return("alrgum");

	return("");
};

void PnlIdecAd1Control::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class PnlIdecAd1Control::ContIac
 ******************************************************************************/

PnlIdecAd1Control::ContIac::ContIac(
			const double SldTll
			, const double SldTul
			, const int UpdMct
		) : Block() {
	this->SldTll = SldTll;
	this->SldTul = SldTul;
	this->UpdMct = UpdMct;

	mask = {SLDTLL, SLDTUL, UPDMCT};
};

bool PnlIdecAd1Control::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecAd1Control");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecAd1Control";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTll", SldTll)) add(SLDTLL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTul", SldTul)) add(SLDTUL);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "UpdMct", UpdMct)) add(UPDMCT);
	};

	return basefound;
};

void PnlIdecAd1Control::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecAd1Control";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecAd1Control";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "SldTll", SldTll);
		writeDoubleAttr(wr, itemtag, "sref", "SldTul", SldTul);
		writeIntAttr(wr, itemtag, "sref", "UpdMct", UpdMct);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecAd1Control::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (compareDouble(SldTll, comp->SldTll) < 1.0e-4) insert(items, SLDTLL);
	if (compareDouble(SldTul, comp->SldTul) < 1.0e-4) insert(items, SLDTUL);
	if (UpdMct == comp->UpdMct) insert(items, UPDMCT);

	return(items);
};

set<uint> PnlIdecAd1Control::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDTLL, SLDTUL, UPDMCT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::ContInf
 ******************************************************************************/

PnlIdecAd1Control::ContInf::ContInf(
			const uint numFSge
			, const bool ButMasterOn
			, const string& TxtPrg
		) : Block() {
	this->numFSge = numFSge;
	this->ButMasterOn = ButMasterOn;
	this->TxtPrg = TxtPrg;

	mask = {NUMFSGE, BUTMASTERON, TXTPRG};
};

void PnlIdecAd1Control::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecAd1Control";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecAd1Control";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFSge", numFSge);
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtPrg", TxtPrg);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecAd1Control::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtPrg == comp->TxtPrg) insert(items, TXTPRG);

	return(items);
};

set<uint> PnlIdecAd1Control::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE, BUTMASTERON, TXTPRG};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::StatApp
 ******************************************************************************/

void PnlIdecAd1Control::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecAd1Control";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecAd1Control";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecAd1Control::StatShr
 ******************************************************************************/

PnlIdecAd1Control::StatShr::StatShr(
			const double SldTllMin
			, const double SldTllMax
			, const double SldTulMin
			, const double SldTulMax
			, const int UpdMctMin
			, const int UpdMctMax
			, const bool ButRunActive
			, const bool ButStoActive
		) : Block() {
	this->SldTllMin = SldTllMin;
	this->SldTllMax = SldTllMax;
	this->SldTulMin = SldTulMin;
	this->SldTulMax = SldTulMax;
	this->UpdMctMin = UpdMctMin;
	this->UpdMctMax = UpdMctMax;
	this->ButRunActive = ButRunActive;
	this->ButStoActive = ButStoActive;

	mask = {SLDTLLMIN, SLDTLLMAX, SLDTULMIN, SLDTULMAX, UPDMCTMIN, UPDMCTMAX, BUTRUNACTIVE, BUTSTOACTIVE};
};

void PnlIdecAd1Control::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecAd1Control";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecAd1Control";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "SldTllMin", SldTllMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTllMax", SldTllMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldTulMin", SldTulMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTulMax", SldTulMax);
		writeIntAttr(wr, itemtag, "sref", "UpdMctMin", UpdMctMin);
		writeIntAttr(wr, itemtag, "sref", "UpdMctMax", UpdMctMax);
		writeBoolAttr(wr, itemtag, "sref", "ButRunActive", ButRunActive);
		writeBoolAttr(wr, itemtag, "sref", "ButStoActive", ButStoActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecAd1Control::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (compareDouble(SldTllMin, comp->SldTllMin) < 1.0e-4) insert(items, SLDTLLMIN);
	if (compareDouble(SldTllMax, comp->SldTllMax) < 1.0e-4) insert(items, SLDTLLMAX);
	if (compareDouble(SldTulMin, comp->SldTulMin) < 1.0e-4) insert(items, SLDTULMIN);
	if (compareDouble(SldTulMax, comp->SldTulMax) < 1.0e-4) insert(items, SLDTULMAX);
	if (UpdMctMin == comp->UpdMctMin) insert(items, UPDMCTMIN);
	if (UpdMctMax == comp->UpdMctMax) insert(items, UPDMCTMAX);
	if (ButRunActive == comp->ButRunActive) insert(items, BUTRUNACTIVE);
	if (ButStoActive == comp->ButStoActive) insert(items, BUTSTOACTIVE);

	return(items);
};

set<uint> PnlIdecAd1Control::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDTLLMIN, SLDTLLMAX, SLDTULMIN, SLDTULMAX, UPDMCTMIN, UPDMCTMAX, BUTRUNACTIVE, BUTSTOACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecAd1Control::Tag
 ******************************************************************************/

void PnlIdecAd1Control::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecAd1Control";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecAd1Control";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Control");
			writeStringAttr(wr, itemtag, "sref", "HdgRoi", "Regions of interest");
			writeStringAttr(wr, itemtag, "sref", "CptTll", "lower temperature limit [\\u00b0C]");
			writeStringAttr(wr, itemtag, "sref", "CptTul", "upper temperature limit [\\u00b0C]");
			writeStringAttr(wr, itemtag, "sref", "CptMct", "maximum count");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Steuerung");
			writeStringAttr(wr, itemtag, "sref", "HdgRoi", "Zu analysierende Bereiche");
			writeStringAttr(wr, itemtag, "sref", "CptTll", "untere Temperaturgrenze [\\u00b0C]");
			writeStringAttr(wr, itemtag, "sref", "CptTul", "obere Temperaturgrenze [\\u00b0C]");
			writeStringAttr(wr, itemtag, "sref", "CptMct", "maximale Anzahl");
		};
		writeStringAttr(wr, itemtag, "sref", "CptPrg", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::PROGRESS, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButRun", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::RUN, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButSto", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::STOP, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecAd1Control::DpchAppData
 ******************************************************************************/

PnlIdecAd1Control::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECAD1CONTROLDATA) {
};

string PnlIdecAd1Control::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Control::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecAd1ControlData");
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
 class PnlIdecAd1Control::DpchAppDo
 ******************************************************************************/

PnlIdecAd1Control::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECAD1CONTROLDO) {
	ixVDo = 0;
};

string PnlIdecAd1Control::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Control::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecAd1ControlDo");
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
 class PnlIdecAd1Control::DpchEngData
 ******************************************************************************/

PnlIdecAd1Control::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFSge
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECAD1CONTROLDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFSGE, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFSGE) && feedFSge) this->feedFSge = *feedFSge;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecAd1Control::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecAd1Control::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFSGE)) {feedFSge = src->feedFSge; add(FEEDFSGE);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecAd1Control::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecAd1ControlData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFSGE)) feedFSge.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

