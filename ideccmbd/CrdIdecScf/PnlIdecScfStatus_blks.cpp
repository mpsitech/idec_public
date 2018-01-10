/**
  * \file PnlIdecScfStatus_blks.cpp
  * job handler for job PnlIdecScfStatus (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

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

void PnlIdecScfStatus::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=8;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
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

void PnlIdecScfStatus::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfStatus";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfStatus";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtThe", TxtThe);
		writeStringAttr(wr, itemtag, "sref", "TxtPhi", TxtPhi);
		writeStringAttr(wr, itemtag, "sref", "TxtSte", TxtSte);
		writeStringAttr(wr, itemtag, "sref", "TxtFus", TxtFus);
		writeStringAttr(wr, itemtag, "sref", "TxtQnu", TxtQnu);
		writeStringAttr(wr, itemtag, "sref", "TxtQal", TxtQal);
		writeStringAttr(wr, itemtag, "sref", "TxtAcv", TxtAcv);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfStatus::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtThe == comp->TxtThe) insert(items, TXTTHE);
	if (TxtPhi == comp->TxtPhi) insert(items, TXTPHI);
	if (TxtSte == comp->TxtSte) insert(items, TXTSTE);
	if (TxtFus == comp->TxtFus) insert(items, TXTFUS);
	if (TxtQnu == comp->TxtQnu) insert(items, TXTQNU);
	if (TxtQal == comp->TxtQal) insert(items, TXTQAL);
	if (TxtAcv == comp->TxtAcv) insert(items, TXTACV);

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

void PnlIdecScfStatus::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScfStatus";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScfStatus";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
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

void PnlIdecScfStatus::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfStatus";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfStatus";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButTheClearActive", ButTheClearActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiClearActive", ButPhiClearActive);
		writeBoolAttr(wr, itemtag, "sref", "ButSteClearActive", ButSteClearActive);
		writeBoolAttr(wr, itemtag, "sref", "ButFusClearActive", ButFusClearActive);
		writeBoolAttr(wr, itemtag, "sref", "ButQnuClearActive", ButQnuClearActive);
		writeBoolAttr(wr, itemtag, "sref", "ButQalClearActive", ButQalClearActive);
		writeBoolAttr(wr, itemtag, "sref", "ButAcvClearActive", ButAcvClearActive);
	xmlTextWriterEndElement(wr);
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

void PnlIdecScfStatus::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfStatus";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfStatus";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Status");
			writeStringAttr(wr, itemtag, "sref", "HdgCalib", "Calibration");
			writeStringAttr(wr, itemtag, "sref", "CptThe", "\\u03d1 axis");
			writeStringAttr(wr, itemtag, "sref", "CptPhi", "\\u03c6 axis");
			writeStringAttr(wr, itemtag, "sref", "CptSte", "stereo overlay");
			writeStringAttr(wr, itemtag, "sref", "CptFus", "VIS-LWIR overlay");
			writeStringAttr(wr, itemtag, "sref", "CptQnu", "QCD non-uniformity");
			writeStringAttr(wr, itemtag, "sref", "CptQal", "QCD alignment");
			writeStringAttr(wr, itemtag, "sref", "TxtAcv", "&mbused;MB in &fileN; file(s), &mbfree;MB of free memory");
			writeStringAttr(wr, itemtag, "sref", "CptAcv", "archive");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Status");
			writeStringAttr(wr, itemtag, "sref", "HdgCalib", "Kalibrierung");
			writeStringAttr(wr, itemtag, "sref", "CptThe", "\\u03d1-Achse");
			writeStringAttr(wr, itemtag, "sref", "CptPhi", "\\u03c6-Achse");
			writeStringAttr(wr, itemtag, "sref", "CptSte", "Stereo-\\u00dcberlagerung");
			writeStringAttr(wr, itemtag, "sref", "CptFus", "VIS-LWIR \\u00dcberlagerung");
			writeStringAttr(wr, itemtag, "sref", "CptQnu", "QCD-Ungleichf\\u00f6rmigkeit");
			writeStringAttr(wr, itemtag, "sref", "CptQal", "QCD-Ausrichtung");
			writeStringAttr(wr, itemtag, "sref", "TxtAcv", "&mbused;MB in &fileN; Datei(en), &mbfree;MB freier Speicherplatz");
			writeStringAttr(wr, itemtag, "sref", "CptAcv", "Archiv");
		};
		writeStringAttr(wr, itemtag, "sref", "ButTheClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButPhiClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButSteClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButFusClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButQnuClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButQalClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButAcvClear", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::CLEAR, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfStatus::DpchAppDo
 ******************************************************************************/

PnlIdecScfStatus::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFSTATUSDO) {
	ixVDo = 0;
};

string PnlIdecScfStatus::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfStatus::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfStatusDo");
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
 class PnlIdecScfStatus::DpchEngData
 ******************************************************************************/

PnlIdecScfStatus::DpchEngData::DpchEngData(
			const ubigint jref
			, ContInf* continf
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFSTATUSDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfStatus::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfStatus::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfStatus::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfStatusData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

