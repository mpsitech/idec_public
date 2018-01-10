/**
  * \file PnlIdecIaqScill_blks.cpp
  * job handler for job PnlIdecIaqScill (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecIaqScill::VecVDo
 ******************************************************************************/

uint PnlIdecIaqScill::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecIaqScill::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqScill::VecVMode
 ******************************************************************************/

uint PnlIdecIaqScill::VecVMode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "manual") return MANUAL;
	else if (s == "autolive") return AUTOLIVE;
	else if (s == "autorec") return AUTOREC;

	return(0);
};

string PnlIdecIaqScill::VecVMode::getSref(
			const uint ix
		) {
	if (ix == MANUAL) return("manual");
	else if (ix == AUTOLIVE) return("autolive");
	else if (ix == AUTOREC) return("autorec");

	return("");
};

string PnlIdecIaqScill::VecVMode::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == MANUAL) return("manual");
		else if (ix == AUTOLIVE) return("automatic during visible live image");
		else if (ix == AUTOREC) return("automatic during recording");
	} else if (ixIdecVLocale == 2) {
		if (ix == MANUAL) return("manuell");
		else if (ix == AUTOLIVE) return("automatisch bei sichtbarem Livebild");
		else if (ix == AUTOREC) return("automatisch w\\u00e4hrend Aufnahme");
	};

	return("");
};

void PnlIdecIaqScill::VecVMode::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class PnlIdecIaqScill::ContIac
 ******************************************************************************/

PnlIdecIaqScill::ContIac::ContIac(
			const uint numFPupMod
			, const double SldThr
			, const double SldFld
			, const double SldSpt
		) : Block() {
	this->numFPupMod = numFPupMod;
	this->SldThr = SldThr;
	this->SldFld = SldFld;
	this->SldSpt = SldSpt;

	mask = {NUMFPUPMOD, SLDTHR, SLDFLD, SLDSPT};
};

bool PnlIdecIaqScill::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqScill");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqScill";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupMod", numFPupMod)) add(NUMFPUPMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldThr", SldThr)) add(SLDTHR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldFld", SldFld)) add(SLDFLD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldSpt", SldSpt)) add(SLDSPT);
	};

	return basefound;
};

void PnlIdecIaqScill::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqScill";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqScill";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupMod", numFPupMod);
		writeDoubleAttr(wr, itemtag, "sref", "SldThr", SldThr);
		writeDoubleAttr(wr, itemtag, "sref", "SldFld", SldFld);
		writeDoubleAttr(wr, itemtag, "sref", "SldSpt", SldSpt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqScill::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupMod == comp->numFPupMod) insert(items, NUMFPUPMOD);
	if (compareDouble(SldThr, comp->SldThr) < 1.0e-4) insert(items, SLDTHR);
	if (compareDouble(SldFld, comp->SldFld) < 1.0e-4) insert(items, SLDFLD);
	if (compareDouble(SldSpt, comp->SldSpt) < 1.0e-4) insert(items, SLDSPT);

	return(items);
};

set<uint> PnlIdecIaqScill::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPMOD, SLDTHR, SLDFLD, SLDSPT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqScill::ContInf
 ******************************************************************************/

PnlIdecIaqScill::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

void PnlIdecIaqScill::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecIaqScill";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecIaqScill";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqScill::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecIaqScill::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqScill::StatApp
 ******************************************************************************/

void PnlIdecIaqScill::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecIaqScill";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecIaqScill";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqScill::StatShr
 ******************************************************************************/

PnlIdecIaqScill::StatShr::StatShr(
			const bool PupModActive
			, const bool SldThrAvail
			, const bool SldThrActive
			, const double SldThrMin
			, const double SldThrMax
			, const bool SldFldActive
			, const double SldFldMin
			, const double SldFldMax
			, const bool SldSptActive
			, const double SldSptMin
			, const double SldSptMax
		) : Block() {
	this->PupModActive = PupModActive;
	this->SldThrAvail = SldThrAvail;
	this->SldThrActive = SldThrActive;
	this->SldThrMin = SldThrMin;
	this->SldThrMax = SldThrMax;
	this->SldFldActive = SldFldActive;
	this->SldFldMin = SldFldMin;
	this->SldFldMax = SldFldMax;
	this->SldSptActive = SldSptActive;
	this->SldSptMin = SldSptMin;
	this->SldSptMax = SldSptMax;

	mask = {PUPMODACTIVE, SLDTHRAVAIL, SLDTHRACTIVE, SLDTHRMIN, SLDTHRMAX, SLDFLDACTIVE, SLDFLDMIN, SLDFLDMAX, SLDSPTACTIVE, SLDSPTMIN, SLDSPTMAX};
};

void PnlIdecIaqScill::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecIaqScill";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecIaqScill";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "PupModActive", PupModActive);
		writeBoolAttr(wr, itemtag, "sref", "SldThrAvail", SldThrAvail);
		writeBoolAttr(wr, itemtag, "sref", "SldThrActive", SldThrActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldThrMin", SldThrMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldThrMax", SldThrMax);
		writeBoolAttr(wr, itemtag, "sref", "SldFldActive", SldFldActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldFldMin", SldFldMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldFldMax", SldFldMax);
		writeBoolAttr(wr, itemtag, "sref", "SldSptActive", SldSptActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldSptMin", SldSptMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldSptMax", SldSptMax);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqScill::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (PupModActive == comp->PupModActive) insert(items, PUPMODACTIVE);
	if (SldThrAvail == comp->SldThrAvail) insert(items, SLDTHRAVAIL);
	if (SldThrActive == comp->SldThrActive) insert(items, SLDTHRACTIVE);
	if (compareDouble(SldThrMin, comp->SldThrMin) < 1.0e-4) insert(items, SLDTHRMIN);
	if (compareDouble(SldThrMax, comp->SldThrMax) < 1.0e-4) insert(items, SLDTHRMAX);
	if (SldFldActive == comp->SldFldActive) insert(items, SLDFLDACTIVE);
	if (compareDouble(SldFldMin, comp->SldFldMin) < 1.0e-4) insert(items, SLDFLDMIN);
	if (compareDouble(SldFldMax, comp->SldFldMax) < 1.0e-4) insert(items, SLDFLDMAX);
	if (SldSptActive == comp->SldSptActive) insert(items, SLDSPTACTIVE);
	if (compareDouble(SldSptMin, comp->SldSptMin) < 1.0e-4) insert(items, SLDSPTMIN);
	if (compareDouble(SldSptMax, comp->SldSptMax) < 1.0e-4) insert(items, SLDSPTMAX);

	return(items);
};

set<uint> PnlIdecIaqScill::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {PUPMODACTIVE, SLDTHRAVAIL, SLDTHRACTIVE, SLDTHRMIN, SLDTHRMAX, SLDFLDACTIVE, SLDFLDMIN, SLDFLDMAX, SLDSPTACTIVE, SLDSPTMIN, SLDSPTMAX};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqScill::Tag
 ******************************************************************************/

void PnlIdecIaqScill::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecIaqScill";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecIaqScill";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Scene illumination");
			writeStringAttr(wr, itemtag, "sref", "CptMod", "mode");
			writeStringAttr(wr, itemtag, "sref", "CptThr", "threshold");
			writeStringAttr(wr, itemtag, "sref", "CptFld", "floodlight");
			writeStringAttr(wr, itemtag, "sref", "CptSpt", "spotlight");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Szenenbeleuchtung");
			writeStringAttr(wr, itemtag, "sref", "CptMod", "Betriebsart");
			writeStringAttr(wr, itemtag, "sref", "CptThr", "Schwellwert");
			writeStringAttr(wr, itemtag, "sref", "CptFld", "Scheinwerfer");
			writeStringAttr(wr, itemtag, "sref", "CptSpt", "Spot");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqScill::DpchAppData
 ******************************************************************************/

PnlIdecIaqScill::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQSCILLDATA) {
};

string PnlIdecIaqScill::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqScill::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqScillData");
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
 class PnlIdecIaqScill::DpchAppDo
 ******************************************************************************/

PnlIdecIaqScill::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQSCILLDO) {
	ixVDo = 0;
};

string PnlIdecIaqScill::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqScill::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqScillDo");
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
 class PnlIdecIaqScill::DpchEngData
 ******************************************************************************/

PnlIdecIaqScill::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFPupMod
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQSCILLDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFPUPMOD, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFPUPMOD) && feedFPupMod) this->feedFPupMod = *feedFPupMod;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecIaqScill::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPMOD)) ss.push_back("feedFPupMod");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqScill::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFPUPMOD)) {feedFPupMod = src->feedFPupMod; add(FEEDFPUPMOD);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecIaqScill::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqScillData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFPUPMOD)) feedFPupMod.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

