/**
  * \file PnlIdecIaqLive_blks.cpp
  * job handler for job PnlIdecIaqLive (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecIaqLive::VecVDo
 ******************************************************************************/

uint PnlIdecIaqLive::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "butsnapclick") return BUTSNAPCLICK;
	else if (s == "butrecclick") return BUTRECCLICK;
	else if (s == "butplayclick") return BUTPLAYCLICK;
	else if (s == "butstopclick") return BUTSTOPCLICK;

	return(0);
};

string PnlIdecIaqLive::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTSNAPCLICK) return("ButSnapClick");
	else if (ix == BUTRECCLICK) return("ButRecClick");
	else if (ix == BUTPLAYCLICK) return("ButPlayClick");
	else if (ix == BUTSTOPCLICK) return("ButStopClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqLive::VecVSge
 ******************************************************************************/

uint PnlIdecIaqLive::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alrgum") return ALRGUM;

	return(0);
};

string PnlIdecIaqLive::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRGUM) return("alrgum");

	return("");
};

void PnlIdecIaqLive::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class PnlIdecIaqLive::VecVSource
 ******************************************************************************/

uint PnlIdecIaqLive::VecVSource::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "visl") return VISL;
	else if (s == "visr") return VISR;
	else if (s == "lwir") return LWIR;
	else if (s == "stereo") return STEREO;
	else if (s == "fusion") return FUSION;

	return(0);
};

string PnlIdecIaqLive::VecVSource::getSref(
			const uint ix
		) {
	if (ix == VISL) return("visl");
	else if (ix == VISR) return("visr");
	else if (ix == LWIR) return("lwir");
	else if (ix == STEREO) return("stereo");
	else if (ix == FUSION) return("fusion");

	return("");
};

string PnlIdecIaqLive::VecVSource::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == VISL) return("VIS-L camera");
		else if (ix == VISR) return("VIS-R camera");
		else if (ix == LWIR) return("LWIR camera");
		else if (ix == STEREO) return("3D reconstruction");
		else if (ix == FUSION) return("fused VIS-L/LWIR image");
	} else if (ixIdecVLocale == 2) {
		if (ix == VISL) return("VIS-L-Kamera");
		else if (ix == VISR) return("VIS-R-Kamera");
		else if (ix == LWIR) return("LWIR-Kamera");
		else if (ix == STEREO) return("3D-Rekonstruktion");
		else if (ix == FUSION) return("fusioniertes VIS-L-/LWIR-Bild");
	};

	return("");
};

void PnlIdecIaqLive::VecVSource::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=5;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class PnlIdecIaqLive::ContIac
 ******************************************************************************/

PnlIdecIaqLive::ContIac::ContIac(
			const uint numFPupSrc
			, const uint numFPupRes
			, const bool ChkGrs
			, const double SldFrr
			, const double SldExt
		) : Block() {
	this->numFPupSrc = numFPupSrc;
	this->numFPupRes = numFPupRes;
	this->ChkGrs = ChkGrs;
	this->SldFrr = SldFrr;
	this->SldExt = SldExt;

	mask = {NUMFPUPSRC, NUMFPUPRES, CHKGRS, SLDFRR, SLDEXT};
};

bool PnlIdecIaqLive::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqLive");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqLive";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupSrc", numFPupSrc)) add(NUMFPUPSRC);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupRes", numFPupRes)) add(NUMFPUPRES);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkGrs", ChkGrs)) add(CHKGRS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldFrr", SldFrr)) add(SLDFRR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldExt", SldExt)) add(SLDEXT);
	};

	return basefound;
};

void PnlIdecIaqLive::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqLive";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqLive";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupSrc", numFPupSrc);
		writeUintAttr(wr, itemtag, "sref", "numFPupRes", numFPupRes);
		writeBoolAttr(wr, itemtag, "sref", "ChkGrs", ChkGrs);
		writeDoubleAttr(wr, itemtag, "sref", "SldFrr", SldFrr);
		writeDoubleAttr(wr, itemtag, "sref", "SldExt", SldExt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqLive::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupSrc == comp->numFPupSrc) insert(items, NUMFPUPSRC);
	if (numFPupRes == comp->numFPupRes) insert(items, NUMFPUPRES);
	if (ChkGrs == comp->ChkGrs) insert(items, CHKGRS);
	if (compareDouble(SldFrr, comp->SldFrr) < 1.0e-4) insert(items, SLDFRR);
	if (compareDouble(SldExt, comp->SldExt) < 1.0e-4) insert(items, SLDEXT);

	return(items);
};

set<uint> PnlIdecIaqLive::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPSRC, NUMFPUPRES, CHKGRS, SLDFRR, SLDEXT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqLive::ContInf
 ******************************************************************************/

PnlIdecIaqLive::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtSte
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtSte = TxtSte;

	mask = {BUTMASTERON, TXTSTE};
};

void PnlIdecIaqLive::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecIaqLive";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecIaqLive";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtSte", TxtSte);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqLive::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtSte == comp->TxtSte) insert(items, TXTSTE);

	return(items);
};

set<uint> PnlIdecIaqLive::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTSTE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqLive::StatShr
 ******************************************************************************/

PnlIdecIaqLive::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const uint CusImgHeight
			, const bool ChkGrsAvail
			, const bool SldConAvail
			, const double SldConMin
			, const double SldConMax
			, const bool SldBriAvail
			, const double SldBriMin
			, const double SldBriMax
			, const bool SldFrrActive
			, const double SldFrrMin
			, const double SldFrrMax
			, const double SldFrrRast
			, const bool SldExtAvail
			, const bool SldExtActive
			, const double SldExtMin
			, const double SldExtMax
			, const double SldExtRast
			, const bool ButPlayActive
			, const bool ButStopActive
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->CusImgHeight = CusImgHeight;
	this->ChkGrsAvail = ChkGrsAvail;
	this->SldConAvail = SldConAvail;
	this->SldConMin = SldConMin;
	this->SldConMax = SldConMax;
	this->SldBriAvail = SldBriAvail;
	this->SldBriMin = SldBriMin;
	this->SldBriMax = SldBriMax;
	this->SldFrrActive = SldFrrActive;
	this->SldFrrMin = SldFrrMin;
	this->SldFrrMax = SldFrrMax;
	this->SldFrrRast = SldFrrRast;
	this->SldExtAvail = SldExtAvail;
	this->SldExtActive = SldExtActive;
	this->SldExtMin = SldExtMin;
	this->SldExtMax = SldExtMax;
	this->SldExtRast = SldExtRast;
	this->ButPlayActive = ButPlayActive;
	this->ButStopActive = ButStopActive;

	mask = {IXIDECVEXPSTATE, CUSIMGHEIGHT, CHKGRSAVAIL, SLDCONAVAIL, SLDCONMIN, SLDCONMAX, SLDBRIAVAIL, SLDBRIMIN, SLDBRIMAX, SLDFRRACTIVE, SLDFRRMIN, SLDFRRMAX, SLDFRRRAST, SLDEXTAVAIL, SLDEXTACTIVE, SLDEXTMIN, SLDEXTMAX, SLDEXTRAST, BUTPLAYACTIVE, BUTSTOPACTIVE};
};

void PnlIdecIaqLive::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecIaqLive";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecIaqLive";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeUintAttr(wr, itemtag, "sref", "CusImgHeight", CusImgHeight);
		writeBoolAttr(wr, itemtag, "sref", "ChkGrsAvail", ChkGrsAvail);
		writeBoolAttr(wr, itemtag, "sref", "SldConAvail", SldConAvail);
		writeDoubleAttr(wr, itemtag, "sref", "SldConMin", SldConMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldConMax", SldConMax);
		writeBoolAttr(wr, itemtag, "sref", "SldBriAvail", SldBriAvail);
		writeDoubleAttr(wr, itemtag, "sref", "SldBriMin", SldBriMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldBriMax", SldBriMax);
		writeBoolAttr(wr, itemtag, "sref", "SldFrrActive", SldFrrActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldFrrMin", SldFrrMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldFrrMax", SldFrrMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldFrrRast", SldFrrRast);
		writeBoolAttr(wr, itemtag, "sref", "SldExtAvail", SldExtAvail);
		writeBoolAttr(wr, itemtag, "sref", "SldExtActive", SldExtActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldExtMin", SldExtMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldExtMax", SldExtMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldExtRast", SldExtRast);
		writeBoolAttr(wr, itemtag, "sref", "ButPlayActive", ButPlayActive);
		writeBoolAttr(wr, itemtag, "sref", "ButStopActive", ButStopActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqLive::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (CusImgHeight == comp->CusImgHeight) insert(items, CUSIMGHEIGHT);
	if (ChkGrsAvail == comp->ChkGrsAvail) insert(items, CHKGRSAVAIL);
	if (SldConAvail == comp->SldConAvail) insert(items, SLDCONAVAIL);
	if (compareDouble(SldConMin, comp->SldConMin) < 1.0e-4) insert(items, SLDCONMIN);
	if (compareDouble(SldConMax, comp->SldConMax) < 1.0e-4) insert(items, SLDCONMAX);
	if (SldBriAvail == comp->SldBriAvail) insert(items, SLDBRIAVAIL);
	if (compareDouble(SldBriMin, comp->SldBriMin) < 1.0e-4) insert(items, SLDBRIMIN);
	if (compareDouble(SldBriMax, comp->SldBriMax) < 1.0e-4) insert(items, SLDBRIMAX);
	if (SldFrrActive == comp->SldFrrActive) insert(items, SLDFRRACTIVE);
	if (compareDouble(SldFrrMin, comp->SldFrrMin) < 1.0e-4) insert(items, SLDFRRMIN);
	if (compareDouble(SldFrrMax, comp->SldFrrMax) < 1.0e-4) insert(items, SLDFRRMAX);
	if (compareDouble(SldFrrRast, comp->SldFrrRast) < 1.0e-4) insert(items, SLDFRRRAST);
	if (SldExtAvail == comp->SldExtAvail) insert(items, SLDEXTAVAIL);
	if (SldExtActive == comp->SldExtActive) insert(items, SLDEXTACTIVE);
	if (compareDouble(SldExtMin, comp->SldExtMin) < 1.0e-4) insert(items, SLDEXTMIN);
	if (compareDouble(SldExtMax, comp->SldExtMax) < 1.0e-4) insert(items, SLDEXTMAX);
	if (compareDouble(SldExtRast, comp->SldExtRast) < 1.0e-4) insert(items, SLDEXTRAST);
	if (ButPlayActive == comp->ButPlayActive) insert(items, BUTPLAYACTIVE);
	if (ButStopActive == comp->ButStopActive) insert(items, BUTSTOPACTIVE);

	return(items);
};

set<uint> PnlIdecIaqLive::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, CUSIMGHEIGHT, CHKGRSAVAIL, SLDCONAVAIL, SLDCONMIN, SLDCONMAX, SLDBRIAVAIL, SLDBRIMIN, SLDBRIMAX, SLDFRRACTIVE, SLDFRRMIN, SLDFRRMAX, SLDFRRRAST, SLDEXTAVAIL, SLDEXTACTIVE, SLDEXTMIN, SLDEXTMAX, SLDEXTRAST, BUTPLAYACTIVE, BUTSTOPACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqLive::Tag
 ******************************************************************************/

void PnlIdecIaqLive::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecIaqLive";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecIaqLive";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Live image");
			writeStringAttr(wr, itemtag, "sref", "CptSrc", "source");
			writeStringAttr(wr, itemtag, "sref", "CptRes", "resolution");
			writeStringAttr(wr, itemtag, "sref", "CptGrs", "grayscale");
			writeStringAttr(wr, itemtag, "sref", "CptCon", "contrast");
			writeStringAttr(wr, itemtag, "sref", "CptBri", "brightness");
			writeStringAttr(wr, itemtag, "sref", "CptFrr", "frame rate [fps]");
			writeStringAttr(wr, itemtag, "sref", "CptExt", "exposure time [ms]");
			writeStringAttr(wr, itemtag, "sref", "CptSte", "status");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Livebild");
			writeStringAttr(wr, itemtag, "sref", "CptSrc", "Quelle");
			writeStringAttr(wr, itemtag, "sref", "CptRes", "Aufl\\u00f6sung");
			writeStringAttr(wr, itemtag, "sref", "CptGrs", "Graustufen");
			writeStringAttr(wr, itemtag, "sref", "CptCon", "Kontrast");
			writeStringAttr(wr, itemtag, "sref", "CptBri", "Helligkeit");
			writeStringAttr(wr, itemtag, "sref", "CptFrr", "Bildwiederholrate [fps]");
			writeStringAttr(wr, itemtag, "sref", "CptExt", "Belichtungszeit [ms]");
			writeStringAttr(wr, itemtag, "sref", "CptSte", "Status");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqLive::DpchAppData
 ******************************************************************************/

PnlIdecIaqLive::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQLIVEDATA) {
};

string PnlIdecIaqLive::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqLiveData");
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
 class PnlIdecIaqLive::DpchAppDo
 ******************************************************************************/

PnlIdecIaqLive::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQLIVEDO) {
	ixVDo = 0;
};

string PnlIdecIaqLive::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqLiveDo");
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
 class PnlIdecIaqLive::DpchEngData
 ******************************************************************************/

PnlIdecIaqLive::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFPupRes
			, Feed* feedFPupSrc
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQLIVEDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFPUPRES, FEEDFPUPSRC, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFPUPRES) && feedFPupRes) this->feedFPupRes = *feedFPupRes;
	if (find(this->mask, FEEDFPUPSRC) && feedFPupSrc) this->feedFPupSrc = *feedFPupSrc;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecIaqLive::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPRES)) ss.push_back("feedFPupRes");
	if (has(FEEDFPUPSRC)) ss.push_back("feedFPupSrc");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFPUPRES)) {feedFPupRes = src->feedFPupRes; add(FEEDFPUPRES);};
	if (src->has(FEEDFPUPSRC)) {feedFPupSrc = src->feedFPupSrc; add(FEEDFPUPSRC);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecIaqLive::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqLiveData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFPUPRES)) feedFPupRes.writeXML(wr);
		if (has(FEEDFPUPSRC)) feedFPupSrc.writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqLive::DpchEngLive
 ******************************************************************************/

PnlIdecIaqLive::DpchEngLive::DpchEngLive(
			const ubigint jref
			, ContInf* continf
			, const vector<utinyint>& rgb
			, const vector<utinyint>& red
			, const vector<utinyint>& green
			, const vector<utinyint>& blue
			, const vector<usmallint>& gray
			, const vector<float>& depth
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQLIVELIVE, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, RGB, RED, GREEN, BLUE, GRAY, DEPTH};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	this->rgb = rgb;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->gray = gray;
	this->depth = depth;
};

string PnlIdecIaqLive::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(RGB)) ss.push_back("rgb");
	if (has(RED)) ss.push_back("red");
	if (has(GREEN)) ss.push_back("green");
	if (has(BLUE)) ss.push_back("blue");
	if (has(GRAY)) ss.push_back("gray");
	if (has(DEPTH)) ss.push_back("depth");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqLive::DpchEngLive::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngLive* src = (DpchEngLive*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(RGB)) {rgb = src->rgb; add(RGB);};
	if (src->has(RED)) {red = src->red; add(RED);};
	if (src->has(GREEN)) {green = src->green; add(GREEN);};
	if (src->has(BLUE)) {blue = src->blue; add(BLUE);};
	if (src->has(GRAY)) {gray = src->gray; add(GRAY);};
	if (src->has(DEPTH)) {depth = src->depth; add(DEPTH);};
};

void PnlIdecIaqLive::DpchEngLive::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqLiveLive");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(RGB)) writeUtinyintvec(wr, "rgb", rgb);
		if (has(RED)) writeUtinyintvec(wr, "red", red);
		if (has(GREEN)) writeUtinyintvec(wr, "green", green);
		if (has(BLUE)) writeUtinyintvec(wr, "blue", blue);
		if (has(GRAY)) writeUsmallintvec(wr, "gray", gray);
		if (has(DEPTH)) writeFloatvec(wr, "depth", depth);
	xmlTextWriterEndElement(wr);
};

