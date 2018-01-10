/**
  * \file PnlIdecScfTrigger_blks.cpp
  * job handler for job PnlIdecScfTrigger (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecScfTrigger::VecVDo
 ******************************************************************************/

uint PnlIdecScfTrigger::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfTrigger::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfTrigger::ContIac
 ******************************************************************************/

PnlIdecScfTrigger::ContIac::ContIac(
			const double SldRdl
			, const double SldIdl
			, const double SldQdl
		) : Block() {
	this->SldRdl = SldRdl;
	this->SldIdl = SldIdl;
	this->SldQdl = SldQdl;

	mask = {SLDRDL, SLDIDL, SLDQDL};
};

bool PnlIdecScfTrigger::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfTrigger";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldRdl", SldRdl)) add(SLDRDL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldIdl", SldIdl)) add(SLDIDL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldQdl", SldQdl)) add(SLDQDL);
	};

	return basefound;
};

void PnlIdecScfTrigger::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfTrigger";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "SldRdl", SldRdl);
		writeDoubleAttr(wr, itemtag, "sref", "SldIdl", SldIdl);
		writeDoubleAttr(wr, itemtag, "sref", "SldQdl", SldQdl);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfTrigger::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (compareDouble(SldRdl, comp->SldRdl) < 1.0e-4) insert(items, SLDRDL);
	if (compareDouble(SldIdl, comp->SldIdl) < 1.0e-4) insert(items, SLDIDL);
	if (compareDouble(SldQdl, comp->SldQdl) < 1.0e-4) insert(items, SLDQDL);

	return(items);
};

set<uint> PnlIdecScfTrigger::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDRDL, SLDIDL, SLDQDL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfTrigger::ContInf
 ******************************************************************************/

PnlIdecScfTrigger::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

void PnlIdecScfTrigger::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfTrigger";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfTrigger::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecScfTrigger::ContInf::diff(
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
 class PnlIdecScfTrigger::StatApp
 ******************************************************************************/

void PnlIdecScfTrigger::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScfTrigger";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScfTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfTrigger::StatShr
 ******************************************************************************/

PnlIdecScfTrigger::StatShr::StatShr(
			const bool SldRdlActive
			, const double SldRdlMin
			, const double SldRdlMax
			, const double SldRdlRast
			, const bool SldIdlActive
			, const double SldIdlMin
			, const double SldIdlMax
			, const double SldIdlRast
			, const bool SldQdlActive
			, const double SldQdlMin
			, const double SldQdlMax
			, const double SldQdlRast
		) : Block() {
	this->SldRdlActive = SldRdlActive;
	this->SldRdlMin = SldRdlMin;
	this->SldRdlMax = SldRdlMax;
	this->SldRdlRast = SldRdlRast;
	this->SldIdlActive = SldIdlActive;
	this->SldIdlMin = SldIdlMin;
	this->SldIdlMax = SldIdlMax;
	this->SldIdlRast = SldIdlRast;
	this->SldQdlActive = SldQdlActive;
	this->SldQdlMin = SldQdlMin;
	this->SldQdlMax = SldQdlMax;
	this->SldQdlRast = SldQdlRast;

	mask = {SLDRDLACTIVE, SLDRDLMIN, SLDRDLMAX, SLDRDLRAST, SLDIDLACTIVE, SLDIDLMIN, SLDIDLMAX, SLDIDLRAST, SLDQDLACTIVE, SLDQDLMIN, SLDQDLMAX, SLDQDLRAST};
};

void PnlIdecScfTrigger::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfTrigger";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "SldRdlActive", SldRdlActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldRdlMin", SldRdlMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldRdlMax", SldRdlMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldRdlRast", SldRdlRast);
		writeBoolAttr(wr, itemtag, "sref", "SldIdlActive", SldIdlActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldIdlMin", SldIdlMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldIdlMax", SldIdlMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldIdlRast", SldIdlRast);
		writeBoolAttr(wr, itemtag, "sref", "SldQdlActive", SldQdlActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldQdlMin", SldQdlMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldQdlMax", SldQdlMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldQdlRast", SldQdlRast);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfTrigger::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (SldRdlActive == comp->SldRdlActive) insert(items, SLDRDLACTIVE);
	if (compareDouble(SldRdlMin, comp->SldRdlMin) < 1.0e-4) insert(items, SLDRDLMIN);
	if (compareDouble(SldRdlMax, comp->SldRdlMax) < 1.0e-4) insert(items, SLDRDLMAX);
	if (compareDouble(SldRdlRast, comp->SldRdlRast) < 1.0e-4) insert(items, SLDRDLRAST);
	if (SldIdlActive == comp->SldIdlActive) insert(items, SLDIDLACTIVE);
	if (compareDouble(SldIdlMin, comp->SldIdlMin) < 1.0e-4) insert(items, SLDIDLMIN);
	if (compareDouble(SldIdlMax, comp->SldIdlMax) < 1.0e-4) insert(items, SLDIDLMAX);
	if (compareDouble(SldIdlRast, comp->SldIdlRast) < 1.0e-4) insert(items, SLDIDLRAST);
	if (SldQdlActive == comp->SldQdlActive) insert(items, SLDQDLACTIVE);
	if (compareDouble(SldQdlMin, comp->SldQdlMin) < 1.0e-4) insert(items, SLDQDLMIN);
	if (compareDouble(SldQdlMax, comp->SldQdlMax) < 1.0e-4) insert(items, SLDQDLMAX);
	if (compareDouble(SldQdlRast, comp->SldQdlRast) < 1.0e-4) insert(items, SLDQDLRAST);

	return(items);
};

set<uint> PnlIdecScfTrigger::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SLDRDLACTIVE, SLDRDLMIN, SLDRDLMAX, SLDRDLRAST, SLDIDLACTIVE, SLDIDLMIN, SLDIDLMAX, SLDIDLRAST, SLDQDLACTIVE, SLDQDLMIN, SLDQDLMAX, SLDQDLRAST};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfTrigger::Tag
 ******************************************************************************/

void PnlIdecScfTrigger::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfTrigger";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Trigger");
			writeStringAttr(wr, itemtag, "sref", "CptRef", "Reference: VIS-L camera (0ms)");
			writeStringAttr(wr, itemtag, "sref", "CptRdl", "VIS-R camera delay [ms]");
			writeStringAttr(wr, itemtag, "sref", "CptIdl", "LWIR camera delay [ms]");
			writeStringAttr(wr, itemtag, "sref", "CptQdl", "QCD detector delay [ms]");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Ausl\\u00f6ser");
			writeStringAttr(wr, itemtag, "sref", "CptRef", "Referenz: VIS-L-Kamera (0ms)");
			writeStringAttr(wr, itemtag, "sref", "CptRdl", "Verz\\u00f6gerung VIS-R-Kamera [ms]");
			writeStringAttr(wr, itemtag, "sref", "CptIdl", "Verz\\u00f6gerung LWIR-Kamera [ms]");
			writeStringAttr(wr, itemtag, "sref", "CptQdl", "Verz\\u00f6gerung QCD-Detektor [ms]");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfTrigger::DpchAppData
 ******************************************************************************/

PnlIdecScfTrigger::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFTRIGGERDATA) {
};

string PnlIdecScfTrigger::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfTrigger::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfTriggerData");
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
 class PnlIdecScfTrigger::DpchAppDo
 ******************************************************************************/

PnlIdecScfTrigger::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFTRIGGERDO) {
	ixVDo = 0;
};

string PnlIdecScfTrigger::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfTrigger::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfTriggerDo");
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
 class PnlIdecScfTrigger::DpchEngData
 ******************************************************************************/

PnlIdecScfTrigger::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFTRIGGERDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfTrigger::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfTrigger::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfTrigger::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfTriggerData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

