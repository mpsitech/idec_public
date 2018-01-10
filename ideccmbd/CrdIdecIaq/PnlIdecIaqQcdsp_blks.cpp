/**
  * \file PnlIdecIaqQcdsp_blks.cpp
  * job handler for job PnlIdecIaqQcdsp (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecIaqQcdsp::VecVDo
 ******************************************************************************/

uint PnlIdecIaqQcdsp::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecIaqQcdsp::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecIaqQcdsp::VecVMode
 ******************************************************************************/

uint PnlIdecIaqQcdsp::VecVMode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "off") return OFF;
	else if (s == "pix") return PIX;
	else if (s == "frm") return FRM;

	return(0);
};

string PnlIdecIaqQcdsp::VecVMode::getSref(
			const uint ix
		) {
	if (ix == OFF) return("off");
	else if (ix == PIX) return("pix");
	else if (ix == FRM) return("frm");

	return("");
};

string PnlIdecIaqQcdsp::VecVMode::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == OFF) return("off");
		else if (ix == PIX) return("single pixel");
		else if (ix == FRM) return("full frame");
	} else if (ixIdecVLocale == 2) {
		if (ix == OFF) return("aus");
		else if (ix == PIX) return("Einzeldetektor");
		else if (ix == FRM) return("Gesamtbild");
	};

	return("");
};

void PnlIdecIaqQcdsp::VecVMode::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class PnlIdecIaqQcdsp::ContIac
 ******************************************************************************/

PnlIdecIaqQcdsp::ContIac::ContIac(
			const uint numFPupMod
			, const double SldTin
			, const usmallint CusImgPxs
		) : Block() {
	this->numFPupMod = numFPupMod;
	this->SldTin = SldTin;
	this->CusImgPxs = CusImgPxs;

	mask = {NUMFPUPMOD, SLDTIN, CUSIMGPXS};
};

bool PnlIdecIaqQcdsp::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecIaqQcdsp");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecIaqQcdsp";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupMod", numFPupMod)) add(NUMFPUPMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTin", SldTin)) add(SLDTIN);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusImgPxs", CusImgPxs)) add(CUSIMGPXS);
	};

	return basefound;
};

void PnlIdecIaqQcdsp::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecIaqQcdsp";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecIaqQcdsp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupMod", numFPupMod);
		writeDoubleAttr(wr, itemtag, "sref", "SldTin", SldTin);
		writeUsmallintAttr(wr, itemtag, "sref", "CusImgPxs", CusImgPxs);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqQcdsp::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupMod == comp->numFPupMod) insert(items, NUMFPUPMOD);
	if (compareDouble(SldTin, comp->SldTin) < 1.0e-4) insert(items, SLDTIN);
	if (CusImgPxs == comp->CusImgPxs) insert(items, CUSIMGPXS);

	return(items);
};

set<uint> PnlIdecIaqQcdsp::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPMOD, SLDTIN, CUSIMGPXS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::ContInf
 ******************************************************************************/

PnlIdecIaqQcdsp::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtImgIl0
			, const string& TxtImgIl1
			, const string& TxtImgQwh
			, const string& TxtImgQhp
			, const string& TxtImgQdp
			, const string& TxtImgSiq
			, const string& TxtImgDxi
			, const string& TxtImgDyi
			, const string& TxtImgQlm
			, const string& TxtImgQdl
			, const uint numFCsiImgSte
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtImgIl0 = TxtImgIl0;
	this->TxtImgIl1 = TxtImgIl1;
	this->TxtImgQwh = TxtImgQwh;
	this->TxtImgQhp = TxtImgQhp;
	this->TxtImgQdp = TxtImgQdp;
	this->TxtImgSiq = TxtImgSiq;
	this->TxtImgDxi = TxtImgDxi;
	this->TxtImgDyi = TxtImgDyi;
	this->TxtImgQlm = TxtImgQlm;
	this->TxtImgQdl = TxtImgQdl;
	this->numFCsiImgSte = numFCsiImgSte;

	mask = {BUTMASTERON, TXTIMGIL0, TXTIMGIL1, TXTIMGQWH, TXTIMGQHP, TXTIMGQDP, TXTIMGSIQ, TXTIMGDXI, TXTIMGDYI, TXTIMGQLM, TXTIMGQDL, NUMFCSIIMGSTE};
};

void PnlIdecIaqQcdsp::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecIaqQcdsp";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecIaqQcdsp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtImgIl0", TxtImgIl0);
		writeStringAttr(wr, itemtag, "sref", "TxtImgIl1", TxtImgIl1);
		writeStringAttr(wr, itemtag, "sref", "TxtImgQwh", TxtImgQwh);
		writeStringAttr(wr, itemtag, "sref", "TxtImgQhp", TxtImgQhp);
		writeStringAttr(wr, itemtag, "sref", "TxtImgQdp", TxtImgQdp);
		writeStringAttr(wr, itemtag, "sref", "TxtImgSiq", TxtImgSiq);
		writeStringAttr(wr, itemtag, "sref", "TxtImgDxi", TxtImgDxi);
		writeStringAttr(wr, itemtag, "sref", "TxtImgDyi", TxtImgDyi);
		writeStringAttr(wr, itemtag, "sref", "TxtImgQlm", TxtImgQlm);
		writeStringAttr(wr, itemtag, "sref", "TxtImgQdl", TxtImgQdl);
		writeUintAttr(wr, itemtag, "sref", "numFCsiImgSte", numFCsiImgSte);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqQcdsp::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtImgIl0 == comp->TxtImgIl0) insert(items, TXTIMGIL0);
	if (TxtImgIl1 == comp->TxtImgIl1) insert(items, TXTIMGIL1);
	if (TxtImgQwh == comp->TxtImgQwh) insert(items, TXTIMGQWH);
	if (TxtImgQhp == comp->TxtImgQhp) insert(items, TXTIMGQHP);
	if (TxtImgQdp == comp->TxtImgQdp) insert(items, TXTIMGQDP);
	if (TxtImgSiq == comp->TxtImgSiq) insert(items, TXTIMGSIQ);
	if (TxtImgDxi == comp->TxtImgDxi) insert(items, TXTIMGDXI);
	if (TxtImgDyi == comp->TxtImgDyi) insert(items, TXTIMGDYI);
	if (TxtImgQlm == comp->TxtImgQlm) insert(items, TXTIMGQLM);
	if (TxtImgQdl == comp->TxtImgQdl) insert(items, TXTIMGQDL);
	if (numFCsiImgSte == comp->numFCsiImgSte) insert(items, NUMFCSIIMGSTE);

	return(items);
};

set<uint> PnlIdecIaqQcdsp::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTIMGIL0, TXTIMGIL1, TXTIMGQWH, TXTIMGQHP, TXTIMGQDP, TXTIMGSIQ, TXTIMGDXI, TXTIMGDYI, TXTIMGQLM, TXTIMGQDL, NUMFCSIIMGSTE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::StatShr
 ******************************************************************************/

PnlIdecIaqQcdsp::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool PupModActive
			, const double SldTinMin
			, const double SldTinMax
			, const double SldTinRast
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->PupModActive = PupModActive;
	this->SldTinMin = SldTinMin;
	this->SldTinMax = SldTinMax;
	this->SldTinRast = SldTinRast;

	mask = {IXIDECVEXPSTATE, PUPMODACTIVE, SLDTINMIN, SLDTINMAX, SLDTINRAST};
};

void PnlIdecIaqQcdsp::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecIaqQcdsp";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecIaqQcdsp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "PupModActive", PupModActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldTinMin", SldTinMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTinMax", SldTinMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldTinRast", SldTinRast);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecIaqQcdsp::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (PupModActive == comp->PupModActive) insert(items, PUPMODACTIVE);
	if (compareDouble(SldTinMin, comp->SldTinMin) < 1.0e-4) insert(items, SLDTINMIN);
	if (compareDouble(SldTinMax, comp->SldTinMax) < 1.0e-4) insert(items, SLDTINMAX);
	if (compareDouble(SldTinRast, comp->SldTinRast) < 1.0e-4) insert(items, SLDTINRAST);

	return(items);
};

set<uint> PnlIdecIaqQcdsp::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, PUPMODACTIVE, SLDTINMIN, SLDTINMAX, SLDTINRAST};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::Tag
 ******************************************************************************/

void PnlIdecIaqQcdsp::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecIaqQcdsp";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecIaqQcdsp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "QCD spot measurement");
			writeStringAttr(wr, itemtag, "sref", "CptMod", "mode");
			writeStringAttr(wr, itemtag, "sref", "ButImgShow", "show");
			writeStringAttr(wr, itemtag, "sref", "CptTin", "integration time [ms]");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "QCD Punktmessung");
			writeStringAttr(wr, itemtag, "sref", "CptMod", "Betriebsart");
			writeStringAttr(wr, itemtag, "sref", "ButImgShow", "zeigen");
			writeStringAttr(wr, itemtag, "sref", "CptTin", "Integrationszeit [ms]");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::DpchAppData
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQQCDSPDATA) {
};

string PnlIdecIaqQcdsp::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqQcdspData");
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
 class PnlIdecIaqQcdsp::DpchAppDo
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECIAQQCDSPDO) {
	ixVDo = 0;
};

string PnlIdecIaqQcdsp::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecIaqQcdspDo");
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
 class PnlIdecIaqQcdsp::DpchEngData
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFCsiImgSte
			, Feed* feedFPupMod
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQQCDSPDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFCSIIMGSTE, FEEDFPUPMOD, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFCSIIMGSTE) && feedFCsiImgSte) this->feedFCsiImgSte = *feedFCsiImgSte;
	if (find(this->mask, FEEDFPUPMOD) && feedFPupMod) this->feedFPupMod = *feedFPupMod;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecIaqQcdsp::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIIMGSTE)) ss.push_back("feedFCsiImgSte");
	if (has(FEEDFPUPMOD)) ss.push_back("feedFPupMod");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFCSIIMGSTE)) {feedFCsiImgSte = src->feedFCsiImgSte; add(FEEDFCSIIMGSTE);};
	if (src->has(FEEDFPUPMOD)) {feedFPupMod = src->feedFPupMod; add(FEEDFPUPMOD);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecIaqQcdsp::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqQcdspData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFCSIIMGSTE)) feedFCsiImgSte.writeXML(wr);
		if (has(FEEDFPUPMOD)) feedFPupMod.writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecIaqQcdsp::DpchEngLive
 ******************************************************************************/

PnlIdecIaqQcdsp::DpchEngLive::DpchEngLive(
			const ubigint jref
			, ContInf* continf
			, const vector<double>& Tlwir
			, const vector<double>& Tqcd
			, const vector<double>& DeltaTqcd
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECIAQQCDSPLIVE, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, TLWIR, TQCD, DELTATQCD};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	this->Tlwir = Tlwir;
	this->Tqcd = Tqcd;
	this->DeltaTqcd = DeltaTqcd;
};

string PnlIdecIaqQcdsp::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(TLWIR)) ss.push_back("Tlwir");
	if (has(TQCD)) ss.push_back("Tqcd");
	if (has(DELTATQCD)) ss.push_back("DeltaTqcd");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecIaqQcdsp::DpchEngLive::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngLive* src = (DpchEngLive*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(TLWIR)) {Tlwir = src->Tlwir; add(TLWIR);};
	if (src->has(TQCD)) {Tqcd = src->Tqcd; add(TQCD);};
	if (src->has(DELTATQCD)) {DeltaTqcd = src->DeltaTqcd; add(DELTATQCD);};
};

void PnlIdecIaqQcdsp::DpchEngLive::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecIaqQcdspLive");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(TLWIR)) writeDoublevec(wr, "Tlwir", Tlwir);
		if (has(TQCD)) writeDoublevec(wr, "Tqcd", Tqcd);
		if (has(DELTATQCD)) writeDoublevec(wr, "DeltaTqcd", DeltaTqcd);
	xmlTextWriterEndElement(wr);
};

