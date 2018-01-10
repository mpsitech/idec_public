/**
  * \file PnlIdecNavPre_blks.cpp
  * job handler for job PnlIdecNavPre (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecNavPre::VecVDo
 ******************************************************************************/

uint PnlIdecNavPre::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmisremoveclick") return BUTMISREMOVECLICK;
	else if (s == "buttouremoveclick") return BUTTOUREMOVECLICK;

	return(0);
};

string PnlIdecNavPre::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMISREMOVECLICK) return("ButMisRemoveClick");
	else if (ix == BUTTOUREMOVECLICK) return("ButTouRemoveClick");

	return("");
};

/******************************************************************************
 class PnlIdecNavPre::ContInf
 ******************************************************************************/

PnlIdecNavPre::ContInf::ContInf(
			const string& TxtMis
			, const string& TxtTou
		) : Block() {
	this->TxtMis = TxtMis;
	this->TxtTou = TxtTou;

	mask = {TXTMIS, TXTTOU};
};

void PnlIdecNavPre::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecNavPre";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecNavPre";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxtMis", TxtMis);
		writeStringAttr(wr, itemtag, "sref", "TxtTou", TxtTou);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavPre::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtMis == comp->TxtMis) insert(items, TXTMIS);
	if (TxtTou == comp->TxtTou) insert(items, TXTTOU);

	return(items);
};

set<uint> PnlIdecNavPre::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTMIS, TXTTOU};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavPre::StatShr
 ******************************************************************************/

PnlIdecNavPre::StatShr::StatShr(
			const bool TxtMisAvail
			, const bool TxtTouAvail
		) : Block() {
	this->TxtMisAvail = TxtMisAvail;
	this->TxtTouAvail = TxtTouAvail;

	mask = {TXTMISAVAIL, TXTTOUAVAIL};
};

void PnlIdecNavPre::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecNavPre";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecNavPre";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "TxtMisAvail", TxtMisAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxtTouAvail", TxtTouAvail);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavPre::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxtMisAvail == comp->TxtMisAvail) insert(items, TXTMISAVAIL);
	if (TxtTouAvail == comp->TxtTouAvail) insert(items, TXTTOUAVAIL);

	return(items);
};

set<uint> PnlIdecNavPre::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTMISAVAIL, TXTTOUAVAIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavPre::Tag
 ******************************************************************************/

void PnlIdecNavPre::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecNavPre";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecNavPre";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "CptMis", "mission");
			writeStringAttr(wr, itemtag, "sref", "CptTou", "tour");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "CptMis", "Mission");
			writeStringAttr(wr, itemtag, "sref", "CptTou", "Tour");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavPre::DpchAppDo
 ******************************************************************************/

PnlIdecNavPre::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVPREDO) {
	ixVDo = 0;
};

string PnlIdecNavPre::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavPre::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecNavPreDo");
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
 class PnlIdecNavPre::DpchEngData
 ******************************************************************************/

PnlIdecNavPre::DpchEngData::DpchEngData(
			const ubigint jref
			, ContInf* continf
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVPREDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecNavPre::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavPre::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecNavPre::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecNavPreData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

