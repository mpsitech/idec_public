/**
  * \file PnlIdecMisDetail_blks.cpp
  * job handler for job PnlIdecMisDetail (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecMisDetail::VecVDo
 ******************************************************************************/

uint PnlIdecMisDetail::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butsaveclick") return BUTSAVECLICK;
	else if (s == "butcryeditclick") return BUTCRYEDITCLICK;

	return(0);
};

string PnlIdecMisDetail::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTSAVECLICK) return("ButSaveClick");
	else if (ix == BUTCRYEDITCLICK) return("ButCryEditClick");

	return("");
};

/******************************************************************************
 class PnlIdecMisDetail::ContIac
 ******************************************************************************/

PnlIdecMisDetail::ContIac::ContIac(
			const string& TxfTit
			, const string& TxfSta
			, const string& TxfSto
			, const uint numFPupCry
			, const string& TxfCry
			, const string& TxfReg
			, const string& TxfMun
			, const string& TxfCmt
		) : Block() {
	this->TxfTit = TxfTit;
	this->TxfSta = TxfSta;
	this->TxfSto = TxfSto;
	this->numFPupCry = numFPupCry;
	this->TxfCry = TxfCry;
	this->TxfReg = TxfReg;
	this->TxfMun = TxfMun;
	this->TxfCmt = TxfCmt;

	mask = {TXFTIT, TXFSTA, TXFSTO, NUMFPUPCRY, TXFCRY, TXFREG, TXFMUN, TXFCMT};
};

bool PnlIdecMisDetail::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecMisDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecMisDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfTit", TxfTit)) add(TXFTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSta", TxfSta)) add(TXFSTA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSto", TxfSto)) add(TXFSTO);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupCry", numFPupCry)) add(NUMFPUPCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfCry", TxfCry)) add(TXFCRY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfReg", TxfReg)) add(TXFREG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfMun", TxfMun)) add(TXFMUN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfCmt", TxfCmt)) add(TXFCMT);
	};

	return basefound;
};

void PnlIdecMisDetail::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecMisDetail";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecMisDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfTit", TxfTit);
		writeStringAttr(wr, itemtag, "sref", "TxfSta", TxfSta);
		writeStringAttr(wr, itemtag, "sref", "TxfSto", TxfSto);
		writeUintAttr(wr, itemtag, "sref", "numFPupCry", numFPupCry);
		writeStringAttr(wr, itemtag, "sref", "TxfCry", TxfCry);
		writeStringAttr(wr, itemtag, "sref", "TxfReg", TxfReg);
		writeStringAttr(wr, itemtag, "sref", "TxfMun", TxfMun);
		writeStringAttr(wr, itemtag, "sref", "TxfCmt", TxfCmt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecMisDetail::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfTit == comp->TxfTit) insert(items, TXFTIT);
	if (TxfSta == comp->TxfSta) insert(items, TXFSTA);
	if (TxfSto == comp->TxfSto) insert(items, TXFSTO);
	if (numFPupCry == comp->numFPupCry) insert(items, NUMFPUPCRY);
	if (TxfCry == comp->TxfCry) insert(items, TXFCRY);
	if (TxfReg == comp->TxfReg) insert(items, TXFREG);
	if (TxfMun == comp->TxfMun) insert(items, TXFMUN);
	if (TxfCmt == comp->TxfCmt) insert(items, TXFCMT);

	return(items);
};

set<uint> PnlIdecMisDetail::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFTIT, TXFSTA, TXFSTO, NUMFPUPCRY, TXFCRY, TXFREG, TXFMUN, TXFCMT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecMisDetail::StatApp
 ******************************************************************************/

void PnlIdecMisDetail::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
			, const bool PupCryAlt
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecMisDetail";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecMisDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "PupCryAlt", PupCryAlt);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecMisDetail::StatShr
 ******************************************************************************/

PnlIdecMisDetail::StatShr::StatShr(
			const bool TxfCryValid
			, const bool ButSaveAvail
			, const bool ButSaveActive
			, const bool TxfTitActive
			, const bool TxfStaActive
			, const bool TxfStoActive
			, const bool PupCryActive
			, const bool ButCryEditAvail
			, const bool TxfRegActive
			, const bool TxfMunActive
			, const bool TxfCmtActive
		) : Block() {
	this->TxfCryValid = TxfCryValid;
	this->ButSaveAvail = ButSaveAvail;
	this->ButSaveActive = ButSaveActive;
	this->TxfTitActive = TxfTitActive;
	this->TxfStaActive = TxfStaActive;
	this->TxfStoActive = TxfStoActive;
	this->PupCryActive = PupCryActive;
	this->ButCryEditAvail = ButCryEditAvail;
	this->TxfRegActive = TxfRegActive;
	this->TxfMunActive = TxfMunActive;
	this->TxfCmtActive = TxfCmtActive;

	mask = {TXFCRYVALID, BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, PUPCRYACTIVE, BUTCRYEDITAVAIL, TXFREGACTIVE, TXFMUNACTIVE, TXFCMTACTIVE};
};

void PnlIdecMisDetail::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecMisDetail";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecMisDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "TxfCryValid", TxfCryValid);
		writeBoolAttr(wr, itemtag, "sref", "ButSaveAvail", ButSaveAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButSaveActive", ButSaveActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfTitActive", TxfTitActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfStaActive", TxfStaActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfStoActive", TxfStoActive);
		writeBoolAttr(wr, itemtag, "sref", "PupCryActive", PupCryActive);
		writeBoolAttr(wr, itemtag, "sref", "ButCryEditAvail", ButCryEditAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxfRegActive", TxfRegActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfMunActive", TxfMunActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfCmtActive", TxfCmtActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecMisDetail::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxfCryValid == comp->TxfCryValid) insert(items, TXFCRYVALID);
	if (ButSaveAvail == comp->ButSaveAvail) insert(items, BUTSAVEAVAIL);
	if (ButSaveActive == comp->ButSaveActive) insert(items, BUTSAVEACTIVE);
	if (TxfTitActive == comp->TxfTitActive) insert(items, TXFTITACTIVE);
	if (TxfStaActive == comp->TxfStaActive) insert(items, TXFSTAACTIVE);
	if (TxfStoActive == comp->TxfStoActive) insert(items, TXFSTOACTIVE);
	if (PupCryActive == comp->PupCryActive) insert(items, PUPCRYACTIVE);
	if (ButCryEditAvail == comp->ButCryEditAvail) insert(items, BUTCRYEDITAVAIL);
	if (TxfRegActive == comp->TxfRegActive) insert(items, TXFREGACTIVE);
	if (TxfMunActive == comp->TxfMunActive) insert(items, TXFMUNACTIVE);
	if (TxfCmtActive == comp->TxfCmtActive) insert(items, TXFCMTACTIVE);

	return(items);
};

set<uint> PnlIdecMisDetail::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFCRYVALID, BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, PUPCRYACTIVE, BUTCRYEDITAVAIL, TXFREGACTIVE, TXFMUNACTIVE, TXFCMTACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecMisDetail::Tag
 ******************************************************************************/

void PnlIdecMisDetail::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecMisDetail";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecMisDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "CptTit", "name");
			writeStringAttr(wr, itemtag, "sref", "CptSta", "begin");
			writeStringAttr(wr, itemtag, "sref", "CptSto", "end");
			writeStringAttr(wr, itemtag, "sref", "CptCry", "country");
			writeStringAttr(wr, itemtag, "sref", "CptReg", "region");
			writeStringAttr(wr, itemtag, "sref", "CptMun", "municipality");
			writeStringAttr(wr, itemtag, "sref", "CptCmt", "comment");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "CptTit", "Name");
			writeStringAttr(wr, itemtag, "sref", "CptSta", "Beginn");
			writeStringAttr(wr, itemtag, "sref", "CptSto", "Ende");
			writeStringAttr(wr, itemtag, "sref", "CptCry", "Land");
			writeStringAttr(wr, itemtag, "sref", "CptReg", "Region");
			writeStringAttr(wr, itemtag, "sref", "CptMun", "Ort");
			writeStringAttr(wr, itemtag, "sref", "CptCmt", "Notiz");
		};
		writeStringAttr(wr, itemtag, "sref", "Cpt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::DETAIL, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecMisDetail::DpchAppData
 ******************************************************************************/

PnlIdecMisDetail::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECMISDETAILDATA) {
};

string PnlIdecMisDetail::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecMisDetail::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecMisDetailData");
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
 class PnlIdecMisDetail::DpchAppDo
 ******************************************************************************/

PnlIdecMisDetail::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECMISDETAILDO) {
	ixVDo = 0;
};

string PnlIdecMisDetail::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecMisDetail::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecMisDetailDo");
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
 class PnlIdecMisDetail::DpchEngData
 ******************************************************************************/

PnlIdecMisDetail::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, Feed* feedFPupCry
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECMISDETAILDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, FEEDFPUPCRY, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, FEEDFPUPCRY) && feedFPupCry) this->feedFPupCry = *feedFPupCry;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecMisDetail::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(FEEDFPUPCRY)) ss.push_back("feedFPupCry");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecMisDetail::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(FEEDFPUPCRY)) {feedFPupCry = src->feedFPupCry; add(FEEDFPUPCRY);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecMisDetail::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecMisDetailData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(FEEDFPUPCRY)) feedFPupCry.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

