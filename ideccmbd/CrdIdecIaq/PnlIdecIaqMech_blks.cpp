/**
  * \file PnlIdecIaqMech_blks.cpp
  * job handler for job PnlIdecIaqMech (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecIaqMech::VecVDo
 ******************************************************************************/

uint PnlIdecIaqMech::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "buttheccwclick") return BUTTHECCWCLICK;
	else if (s == "buttheccwstmdn") return BUTTHECCWSTMDN;
	else if (s == "buttheccwstmup") return BUTTHECCWSTMUP;
	else if (s == "butthecwstmdn") return BUTTHECWSTMDN;
	else if (s == "butthecwstmup") return BUTTHECWSTMUP;
	else if (s == "butthecwclick") return BUTTHECWCLICK;
	else if (s == "butphiccwclick") return BUTPHICCWCLICK;
	else if (s == "butphiccwstmdn") return BUTPHICCWSTMDN;
	else if (s == "butphiccwstmup") return BUTPHICCWSTMUP;
	else if (s == "butphicwstmdn") return BUTPHICWSTMDN;
	else if (s == "butphicwstmup") return BUTPHICWSTMUP;
	else if (s == "butphicwclick") return BUTPHICWCLICK;

	return(0);
};

string PnlIdecIaqMech::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTTHECCWCLICK) return("ButTheCcwClick");
	else if (ix == BUTTHECCWSTMDN) return("ButTheCcwstMdn");
	else if (ix == BUTTHECCWSTMUP) return("ButTheCcwstMup");
	else if (ix == BUTTHECWSTMDN) return("ButTheCwstMdn");
	else if (ix == BUTTHECWSTMUP) return("ButTheCwstMup");
	else if (ix == BUTTHECWCLICK) return("ButTheCwClick");
	else if (ix == BUTPHICCWCLICK) return("ButPhiCcwClick");
	else if (ix == BUTPHICCWSTMDN) return("ButPhiCcwstMdn");
	else if (ix == BUTPHICCWSTMUP) return("ButPhiCcwstMup");
	else if (ix == BUTPHICWSTMDN) return("ButPhiCwstMdn");
	else if (ix == BUTPHICWSTMUP) return("ButPhiCwstMup");
	else if (ix == BUTPHICWCLICK) return("ButPhiCwClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqMech::VecVMode
 ******************************************************************************/

uint PnlIdecIaqMech::VecVMode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "manual") return MANUAL;
	else if (s == "intact") return INTACT;
	else if (s == "auto") return AUTO;

	return(0);
};

string PnlIdecIaqMech::VecVMode::getSref(
			const uint ix
		) {
	if (ix == MANUAL) return("manual");
	else if (ix == INTACT) return("intact");
	else if (ix == AUTO) return("auto");

	return("");
};

string PnlIdecIaqMech::VecVMode::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == MANUAL) return("manual");
		else if (ix == INTACT) return("interactive with live image");
		else if (ix == AUTO) return("\\u03d1 auto-level, \\u03c6 = 0\\u00b0");
	} else if (ixIdecVLocale == 2) {
		if (ix == MANUAL) return("manuell");
		else if (ix == INTACT) return("interaktiv mit Livebild");
		else if (ix == AUTO) return("\\u03d1 automatisch, \\u03c6 = 0\\u00b0");
	};

	return("");
};

void PnlIdecIaqMech::VecVMode::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class PnlIdecIaqMech::VecVSge
 ******************************************************************************/

uint PnlIdecIaqMech::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;

	return(0);
};

string PnlIdecIaqMech::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");

	return("");
};

void PnlIdecIaqMech::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=1;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class PnlIdecIaqMech::ContIac
 ******************************************************************************/

PnlIdecIaqMech::ContIac::ContIac(
			const uint numFPupMod
			, const double SldTvv
			, const double CusTheAns
			, const double CusPhiAns
		) : Block() {
	this->numFPupMod = numFPupMod;
	this->SldTvv = SldTvv;
	this->CusTheAns = CusTheAns;
	this->CusPhiAns = CusPhiAns;

	mask = {NUMFPUPMOD, SLDTVV, CUSTHEANS, CUSPHIANS};
};

bool PnlIdecIaqMech::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqMech";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupMod", numFPupMod)) add(NUMFPUPMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTvv", SldTvv)) add(SLDTVV);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusTheAns", CusTheAns)) add(CUSTHEANS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusPhiAns", CusPhiAns)) add(CUSPHIANS);
	};

	return basefound;
};

void PnlIdecIaqMech::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqMech";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupMod", numFPupMod);
		writeDoubleAttr(wr, itemtag, "sref", "SldTvv", SldTvv);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAns", CusTheAns);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAns", CusPhiAns);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqMech::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupMod == comp->numFPupMod) insert(items, NUMFPUPMOD);
	if (compareDouble(SldTvv, comp->SldTvv) < 1.0e-4) insert(items, SLDTVV);
	if (compareDouble(CusTheAns, comp->CusTheAns) < 1.0e-4) insert(items, CUSTHEANS);
	if (compareDouble(CusPhiAns, comp->CusPhiAns) < 1.0e-4) insert(items, CUSPHIANS);

	return(items);
};

set<uint> PnlIdecIaqMech::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPMOD, SLDTVV, CUSTHEANS, CUSPHIANS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqMech::ContInf
 ******************************************************************************/

PnlIdecIaqMech::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtTheAng
			, const string& TxtTheRpm
			, const uint numFCsiTheSte
			, const bool ButTheCcwOn
			, const bool ButTheCwOn
			, const string& TxtPhiAng
			, const string& TxtPhiRpm
			, const uint numFCsiPhiSte
			, const bool ButPhiCcwOn
			, const bool ButPhiCwOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtTheAng = TxtTheAng;
	this->TxtTheRpm = TxtTheRpm;
	this->numFCsiTheSte = numFCsiTheSte;
	this->ButTheCcwOn = ButTheCcwOn;
	this->ButTheCwOn = ButTheCwOn;
	this->TxtPhiAng = TxtPhiAng;
	this->TxtPhiRpm = TxtPhiRpm;
	this->numFCsiPhiSte = numFCsiPhiSte;
	this->ButPhiCcwOn = ButPhiCcwOn;
	this->ButPhiCwOn = ButPhiCwOn;

	mask = {BUTMASTERON, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
};

void PnlIdecIaqMech::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecIaqMech";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecIaqMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtTheAng", TxtTheAng);
		writeStringAttr(wr, itemtag, "sref", "TxtTheRpm", TxtTheRpm);
		writeUintAttr(wr, itemtag, "sref", "numFCsiTheSte", numFCsiTheSte);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCcwOn", ButTheCcwOn);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCwOn", ButTheCwOn);
		writeStringAttr(wr, itemtag, "sref", "TxtPhiAng", TxtPhiAng);
		writeStringAttr(wr, itemtag, "sref", "TxtPhiRpm", TxtPhiRpm);
		writeUintAttr(wr, itemtag, "sref", "numFCsiPhiSte", numFCsiPhiSte);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCcwOn", ButPhiCcwOn);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCwOn", ButPhiCwOn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqMech::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtTheAng == comp->TxtTheAng) insert(items, TXTTHEANG);
	if (TxtTheRpm == comp->TxtTheRpm) insert(items, TXTTHERPM);
	if (numFCsiTheSte == comp->numFCsiTheSte) insert(items, NUMFCSITHESTE);
	if (ButTheCcwOn == comp->ButTheCcwOn) insert(items, BUTTHECCWON);
	if (ButTheCwOn == comp->ButTheCwOn) insert(items, BUTTHECWON);
	if (TxtPhiAng == comp->TxtPhiAng) insert(items, TXTPHIANG);
	if (TxtPhiRpm == comp->TxtPhiRpm) insert(items, TXTPHIRPM);
	if (numFCsiPhiSte == comp->numFCsiPhiSte) insert(items, NUMFCSIPHISTE);
	if (ButPhiCcwOn == comp->ButPhiCcwOn) insert(items, BUTPHICCWON);
	if (ButPhiCwOn == comp->ButPhiCwOn) insert(items, BUTPHICWON);

	return(items);
};

set<uint> PnlIdecIaqMech::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqMech::StatShr
 ******************************************************************************/

PnlIdecIaqMech::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool SldTvvAvail
			, const double SldTvvMin
			, const double SldTvvMax
			, const bool CusTheAnsActive
			, const bool ButTheCcwActive
			, const bool ButTheCcwstActive
			, const bool ButTheCwstActive
			, const bool ButTheCwActive
			, const bool CusPhiAnsActive
			, const bool ButPhiCcwActive
			, const bool ButPhiCcwstActive
			, const bool ButPhiCwstActive
			, const bool ButPhiCwActive
			, const double CusTheAnsMin
			, const double CusTheAnsMax
			, const double CusPhiAnsMin
			, const double CusPhiAnsMax
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->SldTvvAvail = SldTvvAvail;
	this->SldTvvMin = SldTvvMin;
	this->SldTvvMax = SldTvvMax;
	this->CusTheAnsActive = CusTheAnsActive;
	this->ButTheCcwActive = ButTheCcwActive;
	this->ButTheCcwstActive = ButTheCcwstActive;
	this->ButTheCwstActive = ButTheCwstActive;
	this->ButTheCwActive = ButTheCwActive;
	this->CusPhiAnsActive = CusPhiAnsActive;
	this->ButPhiCcwActive = ButPhiCcwActive;
	this->ButPhiCcwstActive = ButPhiCcwstActive;
	this->ButPhiCwstActive = ButPhiCwstActive;
	this->ButPhiCwActive = ButPhiCwActive;
	this->CusTheAnsMin = CusTheAnsMin;
	this->CusTheAnsMax = CusTheAnsMax;
	this->CusPhiAnsMin = CusPhiAnsMin;
	this->CusPhiAnsMax = CusPhiAnsMax;

	mask = {IXIDECVEXPSTATE, SLDTVVAVAIL, SLDTVVMIN, SLDTVVMAX, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
};

void PnlIdecIaqMech::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecIaqMech";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecIaqMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "SldTvvAvail", SldTvvAvail);
		writeDoubleAttr(wr, itemtag, "sref", "SldTvvMin", SldTvvMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTvvMax", SldTvvMax);
		writeBoolAttr(wr, itemtag, "sref", "CusTheAnsActive", CusTheAnsActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCcwActive", ButTheCcwActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCcwstActive", ButTheCcwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCwstActive", ButTheCwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCwActive", ButTheCwActive);
		writeBoolAttr(wr, itemtag, "sref", "CusPhiAnsActive", CusPhiAnsActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCcwActive", ButPhiCcwActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCcwstActive", ButPhiCcwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCwstActive", ButPhiCwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCwActive", ButPhiCwActive);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAnsMin", CusTheAnsMin);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAnsMax", CusTheAnsMax);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAnsMin", CusPhiAnsMin);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAnsMax", CusPhiAnsMax);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqMech::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (SldTvvAvail == comp->SldTvvAvail) insert(items, SLDTVVAVAIL);
	if (compareDouble(SldTvvMin, comp->SldTvvMin) < 1.0e-4) insert(items, SLDTVVMIN);
	if (compareDouble(SldTvvMax, comp->SldTvvMax) < 1.0e-4) insert(items, SLDTVVMAX);
	if (CusTheAnsActive == comp->CusTheAnsActive) insert(items, CUSTHEANSACTIVE);
	if (ButTheCcwActive == comp->ButTheCcwActive) insert(items, BUTTHECCWACTIVE);
	if (ButTheCcwstActive == comp->ButTheCcwstActive) insert(items, BUTTHECCWSTACTIVE);
	if (ButTheCwstActive == comp->ButTheCwstActive) insert(items, BUTTHECWSTACTIVE);
	if (ButTheCwActive == comp->ButTheCwActive) insert(items, BUTTHECWACTIVE);
	if (CusPhiAnsActive == comp->CusPhiAnsActive) insert(items, CUSPHIANSACTIVE);
	if (ButPhiCcwActive == comp->ButPhiCcwActive) insert(items, BUTPHICCWACTIVE);
	if (ButPhiCcwstActive == comp->ButPhiCcwstActive) insert(items, BUTPHICCWSTACTIVE);
	if (ButPhiCwstActive == comp->ButPhiCwstActive) insert(items, BUTPHICWSTACTIVE);
	if (ButPhiCwActive == comp->ButPhiCwActive) insert(items, BUTPHICWACTIVE);
	if (compareDouble(CusTheAnsMin, comp->CusTheAnsMin) < 1.0e-4) insert(items, CUSTHEANSMIN);
	if (compareDouble(CusTheAnsMax, comp->CusTheAnsMax) < 1.0e-4) insert(items, CUSTHEANSMAX);
	if (compareDouble(CusPhiAnsMin, comp->CusPhiAnsMin) < 1.0e-4) insert(items, CUSPHIANSMIN);
	if (compareDouble(CusPhiAnsMax, comp->CusPhiAnsMax) < 1.0e-4) insert(items, CUSPHIANSMAX);

	return(items);
};

set<uint> PnlIdecIaqMech::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, SLDTVVAVAIL, SLDTVVMIN, SLDTVVMAX, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqMech::Tag
 ******************************************************************************/

void PnlIdecIaqMech::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecIaqMech";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecIaqMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Mechatronics");
			writeStringAttr(wr, itemtag, "sref", "CptMod", "mode");
			writeStringAttr(wr, itemtag, "sref", "CptTvv", "\\u03d1 with respect to vertical [\\u00b0]");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Mechatronik");
			writeStringAttr(wr, itemtag, "sref", "CptMod", "Betriebsart");
			writeStringAttr(wr, itemtag, "sref", "CptTvv", "\\u03d1 gegen\\u00fcber Vertikaler [\\u00b0]");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqMech::DpchAppData
 ******************************************************************************/

PnlIdecIaqMech::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQMECHDATA) {
};

string PnlIdecIaqMech::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqMechData");
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
 class PnlIdecIaqMech::DpchAppDo
 ******************************************************************************/

PnlIdecIaqMech::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQMECHDO) {
	ixVDo = 0;
};

string PnlIdecIaqMech::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqMechDo");
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
 class PnlIdecIaqMech::DpchEngData
 ******************************************************************************/

PnlIdecIaqMech::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFCsiPhiSte
			, Feed* feedFCsiTheSte
			, Feed* feedFPupMod
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQMECHDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFCSIPHISTE, FEEDFCSITHESTE, FEEDFPUPMOD, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFCSIPHISTE) && feedFCsiPhiSte) this->feedFCsiPhiSte = *feedFCsiPhiSte;
	if (find(this->mask, FEEDFCSITHESTE) && feedFCsiTheSte) this->feedFCsiTheSte = *feedFCsiTheSte;
	if (find(this->mask, FEEDFPUPMOD) && feedFPupMod) this->feedFPupMod = *feedFPupMod;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecIaqMech::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIPHISTE)) ss.push_back("feedFCsiPhiSte");
	if (has(FEEDFCSITHESTE)) ss.push_back("feedFCsiTheSte");
	if (has(FEEDFPUPMOD)) ss.push_back("feedFPupMod");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFCSIPHISTE)) {feedFCsiPhiSte = src->feedFCsiPhiSte; add(FEEDFCSIPHISTE);};
	if (src->has(FEEDFCSITHESTE)) {feedFCsiTheSte = src->feedFCsiTheSte; add(FEEDFCSITHESTE);};
	if (src->has(FEEDFPUPMOD)) {feedFPupMod = src->feedFPupMod; add(FEEDFPUPMOD);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecIaqMech::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqMechData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFCSIPHISTE)) feedFCsiPhiSte.writeXML(wr);
		if (has(FEEDFCSITHESTE)) feedFCsiTheSte.writeXML(wr);
		if (has(FEEDFPUPMOD)) feedFPupMod.writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqMech::DpchEngLive
 ******************************************************************************/

PnlIdecIaqMech::DpchEngLive::DpchEngLive(
			const ubigint jref
			, ContInf* continf
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQMECHLIVE, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
};

string PnlIdecIaqMech::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqMech::DpchEngLive::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngLive* src = (DpchEngLive*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
};

void PnlIdecIaqMech::DpchEngLive::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqMechLive");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

