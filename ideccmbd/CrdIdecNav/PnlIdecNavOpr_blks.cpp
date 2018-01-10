/**
  * \file PnlIdecNavOpr_blks.cpp
  * job handler for job PnlIdecNavOpr (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecNavOpr::VecVDo
 ******************************************************************************/

uint PnlIdecNavOpr::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmisviewclick") return BUTMISVIEWCLICK;
	else if (s == "butmisnewcrdclick") return BUTMISNEWCRDCLICK;
	else if (s == "buttouviewclick") return BUTTOUVIEWCLICK;
	else if (s == "buttounewcrdclick") return BUTTOUNEWCRDCLICK;
	else if (s == "butiaqnewcrdclick") return BUTIAQNEWCRDCLICK;
	else if (s == "butad1newcrdclick") return BUTAD1NEWCRDCLICK;
	else if (s == "butfilviewclick") return BUTFILVIEWCLICK;
	else if (s == "butfilnewcrdclick") return BUTFILNEWCRDCLICK;

	return(0);
};

string PnlIdecNavOpr::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMISVIEWCLICK) return("ButMisViewClick");
	else if (ix == BUTMISNEWCRDCLICK) return("ButMisNewcrdClick");
	else if (ix == BUTTOUVIEWCLICK) return("ButTouViewClick");
	else if (ix == BUTTOUNEWCRDCLICK) return("ButTouNewcrdClick");
	else if (ix == BUTIAQNEWCRDCLICK) return("ButIaqNewcrdClick");
	else if (ix == BUTAD1NEWCRDCLICK) return("ButAd1NewcrdClick");
	else if (ix == BUTFILVIEWCLICK) return("ButFilViewClick");
	else if (ix == BUTFILNEWCRDCLICK) return("ButFilNewcrdClick");

	return("");
};

/******************************************************************************
 class PnlIdecNavOpr::ContIac
 ******************************************************************************/

PnlIdecNavOpr::ContIac::ContIac(
			const uint numFLstMis
			, const uint numFLstTou
			, const uint numFLstFil
		) : Block() {
	this->numFLstMis = numFLstMis;
	this->numFLstTou = numFLstTou;
	this->numFLstFil = numFLstFil;

	mask = {NUMFLSTMIS, NUMFLSTTOU, NUMFLSTFIL};
};

bool PnlIdecNavOpr::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecNavOpr");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecNavOpr";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstMis", numFLstMis)) add(NUMFLSTMIS);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstTou", numFLstTou)) add(NUMFLSTTOU);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstFil", numFLstFil)) add(NUMFLSTFIL);
	};

	return basefound;
};

void PnlIdecNavOpr::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecNavOpr";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecNavOpr";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFLstMis", numFLstMis);
		writeUintAttr(wr, itemtag, "sref", "numFLstTou", numFLstTou);
		writeUintAttr(wr, itemtag, "sref", "numFLstFil", numFLstFil);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavOpr::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFLstMis == comp->numFLstMis) insert(items, NUMFLSTMIS);
	if (numFLstTou == comp->numFLstTou) insert(items, NUMFLSTTOU);
	if (numFLstFil == comp->numFLstFil) insert(items, NUMFLSTFIL);

	return(items);
};

set<uint> PnlIdecNavOpr::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFLSTMIS, NUMFLSTTOU, NUMFLSTFIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavOpr::StatApp
 ******************************************************************************/

void PnlIdecNavOpr::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
			, const bool LstMisAlt
			, const bool LstTouAlt
			, const bool LstFilAlt
			, const uint LstMisNumFirstdisp
			, const uint LstTouNumFirstdisp
			, const uint LstFilNumFirstdisp
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecNavOpr";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecNavOpr";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "LstMisAlt", LstMisAlt);
		writeBoolAttr(wr, itemtag, "sref", "LstTouAlt", LstTouAlt);
		writeBoolAttr(wr, itemtag, "sref", "LstFilAlt", LstFilAlt);
		writeUintAttr(wr, itemtag, "sref", "LstMisNumFirstdisp", LstMisNumFirstdisp);
		writeUintAttr(wr, itemtag, "sref", "LstTouNumFirstdisp", LstTouNumFirstdisp);
		writeUintAttr(wr, itemtag, "sref", "LstFilNumFirstdisp", LstFilNumFirstdisp);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavOpr::StatShr
 ******************************************************************************/

PnlIdecNavOpr::StatShr::StatShr(
			const bool LstMisAvail
			, const bool ButMisViewActive
			, const bool LstTouAvail
			, const bool ButTouViewActive
			, const bool ButTouNewcrdActive
			, const bool ButIaqNewcrdActive
			, const bool ButAd1NewcrdActive
			, const bool LstFilAvail
			, const bool ButFilViewActive
			, const bool ButFilNewcrdActive
		) : Block() {
	this->LstMisAvail = LstMisAvail;
	this->ButMisViewActive = ButMisViewActive;
	this->LstTouAvail = LstTouAvail;
	this->ButTouViewActive = ButTouViewActive;
	this->ButTouNewcrdActive = ButTouNewcrdActive;
	this->ButIaqNewcrdActive = ButIaqNewcrdActive;
	this->ButAd1NewcrdActive = ButAd1NewcrdActive;
	this->LstFilAvail = LstFilAvail;
	this->ButFilViewActive = ButFilViewActive;
	this->ButFilNewcrdActive = ButFilNewcrdActive;

	mask = {LSTMISAVAIL, BUTMISVIEWACTIVE, LSTTOUAVAIL, BUTTOUVIEWACTIVE, BUTTOUNEWCRDACTIVE, BUTIAQNEWCRDACTIVE, BUTAD1NEWCRDACTIVE, LSTFILAVAIL, BUTFILVIEWACTIVE, BUTFILNEWCRDACTIVE};
};

void PnlIdecNavOpr::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecNavOpr";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecNavOpr";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "LstMisAvail", LstMisAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButMisViewActive", ButMisViewActive);
		writeBoolAttr(wr, itemtag, "sref", "LstTouAvail", LstTouAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButTouViewActive", ButTouViewActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTouNewcrdActive", ButTouNewcrdActive);
		writeBoolAttr(wr, itemtag, "sref", "ButIaqNewcrdActive", ButIaqNewcrdActive);
		writeBoolAttr(wr, itemtag, "sref", "ButAd1NewcrdActive", ButAd1NewcrdActive);
		writeBoolAttr(wr, itemtag, "sref", "LstFilAvail", LstFilAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButFilViewActive", ButFilViewActive);
		writeBoolAttr(wr, itemtag, "sref", "ButFilNewcrdActive", ButFilNewcrdActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavOpr::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (LstMisAvail == comp->LstMisAvail) insert(items, LSTMISAVAIL);
	if (ButMisViewActive == comp->ButMisViewActive) insert(items, BUTMISVIEWACTIVE);
	if (LstTouAvail == comp->LstTouAvail) insert(items, LSTTOUAVAIL);
	if (ButTouViewActive == comp->ButTouViewActive) insert(items, BUTTOUVIEWACTIVE);
	if (ButTouNewcrdActive == comp->ButTouNewcrdActive) insert(items, BUTTOUNEWCRDACTIVE);
	if (ButIaqNewcrdActive == comp->ButIaqNewcrdActive) insert(items, BUTIAQNEWCRDACTIVE);
	if (ButAd1NewcrdActive == comp->ButAd1NewcrdActive) insert(items, BUTAD1NEWCRDACTIVE);
	if (LstFilAvail == comp->LstFilAvail) insert(items, LSTFILAVAIL);
	if (ButFilViewActive == comp->ButFilViewActive) insert(items, BUTFILVIEWACTIVE);
	if (ButFilNewcrdActive == comp->ButFilNewcrdActive) insert(items, BUTFILNEWCRDACTIVE);

	return(items);
};

set<uint> PnlIdecNavOpr::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {LSTMISAVAIL, BUTMISVIEWACTIVE, LSTTOUAVAIL, BUTTOUVIEWACTIVE, BUTTOUNEWCRDACTIVE, BUTIAQNEWCRDACTIVE, BUTAD1NEWCRDACTIVE, LSTFILAVAIL, BUTFILVIEWACTIVE, BUTFILNEWCRDACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavOpr::Tag
 ******************************************************************************/

void PnlIdecNavOpr::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecNavOpr";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecNavOpr";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Operation module");
			writeStringAttr(wr, itemtag, "sref", "CptMis", "missions");
			writeStringAttr(wr, itemtag, "sref", "CptTou", "tours");
			writeStringAttr(wr, itemtag, "sref", "CptIaq", "image acquisition");
			writeStringAttr(wr, itemtag, "sref", "CptAd1", "autonomous detection 1");
			writeStringAttr(wr, itemtag, "sref", "CptFil", "files");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Betrieb");
			writeStringAttr(wr, itemtag, "sref", "CptMis", "Missionen");
			writeStringAttr(wr, itemtag, "sref", "CptTou", "Touren");
			writeStringAttr(wr, itemtag, "sref", "CptIaq", "Bilderfassung");
			writeStringAttr(wr, itemtag, "sref", "CptAd1", "autonome Detektion 1");
			writeStringAttr(wr, itemtag, "sref", "CptFil", "Dateien");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavOpr::DpchAppData
 ******************************************************************************/

PnlIdecNavOpr::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVOPRDATA) {
};

string PnlIdecNavOpr::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavOpr::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecNavOprData");
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
 class PnlIdecNavOpr::DpchAppDo
 ******************************************************************************/

PnlIdecNavOpr::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVOPRDO) {
	ixVDo = 0;
};

string PnlIdecNavOpr::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavOpr::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecNavOprDo");
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
 class PnlIdecNavOpr::DpchEngData
 ******************************************************************************/

PnlIdecNavOpr::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, Feed* feedFLstFil
			, Feed* feedFLstMis
			, Feed* feedFLstTou
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVOPRDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, FEEDFLSTFIL, FEEDFLSTMIS, FEEDFLSTTOU, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, FEEDFLSTFIL) && feedFLstFil) this->feedFLstFil = *feedFLstFil;
	if (find(this->mask, FEEDFLSTMIS) && feedFLstMis) this->feedFLstMis = *feedFLstMis;
	if (find(this->mask, FEEDFLSTTOU) && feedFLstTou) this->feedFLstTou = *feedFLstTou;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecNavOpr::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(FEEDFLSTFIL)) ss.push_back("feedFLstFil");
	if (has(FEEDFLSTMIS)) ss.push_back("feedFLstMis");
	if (has(FEEDFLSTTOU)) ss.push_back("feedFLstTou");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavOpr::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(FEEDFLSTFIL)) {feedFLstFil = src->feedFLstFil; add(FEEDFLSTFIL);};
	if (src->has(FEEDFLSTMIS)) {feedFLstMis = src->feedFLstMis; add(FEEDFLSTMIS);};
	if (src->has(FEEDFLSTTOU)) {feedFLstTou = src->feedFLstTou; add(FEEDFLSTTOU);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecNavOpr::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecNavOprData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(FEEDFLSTFIL)) feedFLstFil.writeXML(wr);
		if (has(FEEDFLSTMIS)) feedFLstMis.writeXML(wr);
		if (has(FEEDFLSTTOU)) feedFLstTou.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

