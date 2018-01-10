/**
  * \file PnlIdecNavHeadbar_blks.cpp
  * job handler for job PnlIdecNavHeadbar (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecNavHeadbar::StatShr
 ******************************************************************************/

PnlIdecNavHeadbar::StatShr::StatShr(
			const bool MenCrdAvail
		) : Block() {
	this->MenCrdAvail = MenCrdAvail;

	mask = {MENCRDAVAIL};
};

void PnlIdecNavHeadbar::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecNavHeadbar";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecNavHeadbar";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "MenCrdAvail", MenCrdAvail);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavHeadbar::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (MenCrdAvail == comp->MenCrdAvail) insert(items, MENCRDAVAIL);

	return(items);
};

set<uint> PnlIdecNavHeadbar::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {MENCRDAVAIL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavHeadbar::StgInf
 ******************************************************************************/

void PnlIdecNavHeadbar::StgInf::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgInfIdecNavHeadbar";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemInfIdecNavHeadbar";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "MenAppCptwidth", "220");
			writeStringAttr(wr, itemtag, "sref", "MenAppWidth", "260");
			writeStringAttr(wr, itemtag, "sref", "MenSesCptwidth", "66");
			writeStringAttr(wr, itemtag, "sref", "MenSesWidth", "323");
			writeStringAttr(wr, itemtag, "sref", "MenCrdCptwidth", "100");
			writeStringAttr(wr, itemtag, "sref", "MenCrdWidth", "190");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "MenAppCptwidth", "220");
			writeStringAttr(wr, itemtag, "sref", "MenAppWidth", "260");
			writeStringAttr(wr, itemtag, "sref", "MenSesCptwidth", "66");
			writeStringAttr(wr, itemtag, "sref", "MenSesWidth", "323");
			writeStringAttr(wr, itemtag, "sref", "MenCrdCptwidth", "100");
			writeStringAttr(wr, itemtag, "sref", "MenCrdWidth", "176");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavHeadbar::Tag
 ******************************************************************************/

void PnlIdecNavHeadbar::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecNavHeadbar";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecNavHeadbar";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "MenApp", "ICARUSDetectorControl");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "MenApp", "ICARUSDetectorControl");
		};
		writeStringAttr(wr, itemtag, "sref", "MenSes", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::SESS, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "MenCrd", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::NAV, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavHeadbar::DpchEngData
 ******************************************************************************/

PnlIdecNavHeadbar::DpchEngData::DpchEngData(
			const ubigint jref
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVHEADBARDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, STATSHR, STGINF, TAG};
	else this->mask = mask;

	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecNavHeadbar::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(STGINF)) ss.push_back("stginf");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavHeadbar::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(STGINF)) add(STGINF);
	if (src->has(TAG)) add(TAG);
};

void PnlIdecNavHeadbar::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecNavHeadbarData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(STGINF)) StgInf::writeXML(ixIdecVLocale, wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

