/**
  * \file PnlIdecFilHeadbar_blks.cpp
  * job handler for job PnlIdecFilHeadbar (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecFilHeadbar::StgInf
 ******************************************************************************/

void PnlIdecFilHeadbar::StgInf::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgInfIdecFilHeadbar";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemInfIdecFilHeadbar";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "MenAppCptwidth", "220");
			writeStringAttr(wr, itemtag, "sref", "MenAppWidth", "260");
			writeStringAttr(wr, itemtag, "sref", "MenCrdCptwidth", "46");
			writeStringAttr(wr, itemtag, "sref", "MenCrdWidth", "323");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "MenAppCptwidth", "220");
			writeStringAttr(wr, itemtag, "sref", "MenAppWidth", "260");
			writeStringAttr(wr, itemtag, "sref", "MenCrdCptwidth", "55");
			writeStringAttr(wr, itemtag, "sref", "MenCrdWidth", "323");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecFilHeadbar::Tag
 ******************************************************************************/

void PnlIdecFilHeadbar::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecFilHeadbar";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecFilHeadbar";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "MenApp", "ICARUSDetectorControl");
			writeStringAttr(wr, itemtag, "sref", "MenCrd", "File");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "MenApp", "ICARUSDetectorControl");
			writeStringAttr(wr, itemtag, "sref", "MenCrd", "Datei");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecFilHeadbar::DpchEngData
 ******************************************************************************/

PnlIdecFilHeadbar::DpchEngData::DpchEngData(
			const ubigint jref
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECFILHEADBARDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, STGINF, TAG};
	else this->mask = mask;

};

string PnlIdecFilHeadbar::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(STGINF)) ss.push_back("stginf");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecFilHeadbar::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(STGINF)) add(STGINF);
	if (src->has(TAG)) add(TAG);
};

void PnlIdecFilHeadbar::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecFilHeadbarData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(STGINF)) StgInf::writeXML(ixIdecVLocale, wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

