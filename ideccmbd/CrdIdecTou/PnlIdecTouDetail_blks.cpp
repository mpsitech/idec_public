/**
  * \file PnlIdecTouDetail_blks.cpp
  * job handler for job PnlIdecTouDetail (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecTouDetail::VecVDo
 ******************************************************************************/

uint PnlIdecTouDetail::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butsaveclick") return BUTSAVECLICK;
	else if (s == "butmisviewclick") return BUTMISVIEWCLICK;

	return(0);
};

string PnlIdecTouDetail::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTSAVECLICK) return("ButSaveClick");
	else if (ix == BUTMISVIEWCLICK) return("ButMisViewClick");

	return("");
};

/******************************************************************************
 class PnlIdecTouDetail::ContIac
 ******************************************************************************/

PnlIdecTouDetail::ContIac::ContIac(
			const string& TxfTit
			, const string& TxfSta
			, const string& TxfSto
			, const string& TxfAre
			, const string& TxfThe
			, const string& TxfPhi
			, const string& TxfCmt
		) : Block() {
	this->TxfTit = TxfTit;
	this->TxfSta = TxfSta;
	this->TxfSto = TxfSto;
	this->TxfAre = TxfAre;
	this->TxfThe = TxfThe;
	this->TxfPhi = TxfPhi;
	this->TxfCmt = TxfCmt;

	mask = {TXFTIT, TXFSTA, TXFSTO, TXFARE, TXFTHE, TXFPHI, TXFCMT};
};

bool PnlIdecTouDetail::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecTouDetail");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecTouDetail";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfTit", TxfTit)) add(TXFTIT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSta", TxfSta)) add(TXFSTA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfSto", TxfSto)) add(TXFSTO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfAre", TxfAre)) add(TXFARE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfThe", TxfThe)) add(TXFTHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPhi", TxfPhi)) add(TXFPHI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfCmt", TxfCmt)) add(TXFCMT);
	};

	return basefound;
};

void PnlIdecTouDetail::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecTouDetail";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecTouDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfTit", TxfTit);
		writeStringAttr(wr, itemtag, "sref", "TxfSta", TxfSta);
		writeStringAttr(wr, itemtag, "sref", "TxfSto", TxfSto);
		writeStringAttr(wr, itemtag, "sref", "TxfAre", TxfAre);
		writeStringAttr(wr, itemtag, "sref", "TxfThe", TxfThe);
		writeStringAttr(wr, itemtag, "sref", "TxfPhi", TxfPhi);
		writeStringAttr(wr, itemtag, "sref", "TxfCmt", TxfCmt);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecTouDetail::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfTit == comp->TxfTit) insert(items, TXFTIT);
	if (TxfSta == comp->TxfSta) insert(items, TXFSTA);
	if (TxfSto == comp->TxfSto) insert(items, TXFSTO);
	if (TxfAre == comp->TxfAre) insert(items, TXFARE);
	if (TxfThe == comp->TxfThe) insert(items, TXFTHE);
	if (TxfPhi == comp->TxfPhi) insert(items, TXFPHI);
	if (TxfCmt == comp->TxfCmt) insert(items, TXFCMT);

	return(items);
};

set<uint> PnlIdecTouDetail::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFTIT, TXFSTA, TXFSTO, TXFARE, TXFTHE, TXFPHI, TXFCMT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecTouDetail::ContInf
 ******************************************************************************/

PnlIdecTouDetail::ContInf::ContInf(
			const string& TxtMis
		) : Block() {
	this->TxtMis = TxtMis;

	mask = {TXTMIS};
};

void PnlIdecTouDetail::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecTouDetail";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecTouDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxtMis", TxtMis);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecTouDetail::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtMis == comp->TxtMis) insert(items, TXTMIS);

	return(items);
};

set<uint> PnlIdecTouDetail::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTMIS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecTouDetail::StatApp
 ******************************************************************************/

void PnlIdecTouDetail::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecTouDetail";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecTouDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecTouDetail::StatShr
 ******************************************************************************/

PnlIdecTouDetail::StatShr::StatShr(
			const bool ButSaveAvail
			, const bool ButSaveActive
			, const bool TxfTitActive
			, const bool TxtMisActive
			, const bool ButMisViewAvail
			, const bool ButMisViewActive
			, const bool TxfStaActive
			, const bool TxfStoActive
			, const bool TxfAreActive
			, const bool TxfTheActive
			, const bool TxfPhiActive
			, const bool TxfCmtActive
		) : Block() {
	this->ButSaveAvail = ButSaveAvail;
	this->ButSaveActive = ButSaveActive;
	this->TxfTitActive = TxfTitActive;
	this->TxtMisActive = TxtMisActive;
	this->ButMisViewAvail = ButMisViewAvail;
	this->ButMisViewActive = ButMisViewActive;
	this->TxfStaActive = TxfStaActive;
	this->TxfStoActive = TxfStoActive;
	this->TxfAreActive = TxfAreActive;
	this->TxfTheActive = TxfTheActive;
	this->TxfPhiActive = TxfPhiActive;
	this->TxfCmtActive = TxfCmtActive;

	mask = {BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXTMISACTIVE, BUTMISVIEWAVAIL, BUTMISVIEWACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, TXFAREACTIVE, TXFTHEACTIVE, TXFPHIACTIVE, TXFCMTACTIVE};
};

void PnlIdecTouDetail::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecTouDetail";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecTouDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButSaveAvail", ButSaveAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButSaveActive", ButSaveActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfTitActive", TxfTitActive);
		writeBoolAttr(wr, itemtag, "sref", "TxtMisActive", TxtMisActive);
		writeBoolAttr(wr, itemtag, "sref", "ButMisViewAvail", ButMisViewAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButMisViewActive", ButMisViewActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfStaActive", TxfStaActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfStoActive", TxfStoActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfAreActive", TxfAreActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfTheActive", TxfTheActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfPhiActive", TxfPhiActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfCmtActive", TxfCmtActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecTouDetail::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ButSaveAvail == comp->ButSaveAvail) insert(items, BUTSAVEAVAIL);
	if (ButSaveActive == comp->ButSaveActive) insert(items, BUTSAVEACTIVE);
	if (TxfTitActive == comp->TxfTitActive) insert(items, TXFTITACTIVE);
	if (TxtMisActive == comp->TxtMisActive) insert(items, TXTMISACTIVE);
	if (ButMisViewAvail == comp->ButMisViewAvail) insert(items, BUTMISVIEWAVAIL);
	if (ButMisViewActive == comp->ButMisViewActive) insert(items, BUTMISVIEWACTIVE);
	if (TxfStaActive == comp->TxfStaActive) insert(items, TXFSTAACTIVE);
	if (TxfStoActive == comp->TxfStoActive) insert(items, TXFSTOACTIVE);
	if (TxfAreActive == comp->TxfAreActive) insert(items, TXFAREACTIVE);
	if (TxfTheActive == comp->TxfTheActive) insert(items, TXFTHEACTIVE);
	if (TxfPhiActive == comp->TxfPhiActive) insert(items, TXFPHIACTIVE);
	if (TxfCmtActive == comp->TxfCmtActive) insert(items, TXFCMTACTIVE);

	return(items);
};

set<uint> PnlIdecTouDetail::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTSAVEAVAIL, BUTSAVEACTIVE, TXFTITACTIVE, TXTMISACTIVE, BUTMISVIEWAVAIL, BUTMISVIEWACTIVE, TXFSTAACTIVE, TXFSTOACTIVE, TXFAREACTIVE, TXFTHEACTIVE, TXFPHIACTIVE, TXFCMTACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecTouDetail::Tag
 ******************************************************************************/

void PnlIdecTouDetail::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecTouDetail";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecTouDetail";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "CptTit", "name");
			writeStringAttr(wr, itemtag, "sref", "CptMis", "mission");
			writeStringAttr(wr, itemtag, "sref", "CptSta", "begin");
			writeStringAttr(wr, itemtag, "sref", "CptSto", "end");
			writeStringAttr(wr, itemtag, "sref", "CptAre", "area");
			writeStringAttr(wr, itemtag, "sref", "CptThe", "latitude [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptPhi", "longitude [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptCmt", "comment");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "CptTit", "Name");
			writeStringAttr(wr, itemtag, "sref", "CptMis", "Mission");
			writeStringAttr(wr, itemtag, "sref", "CptSta", "Beginn");
			writeStringAttr(wr, itemtag, "sref", "CptSto", "Ende");
			writeStringAttr(wr, itemtag, "sref", "CptAre", "Gebiet");
			writeStringAttr(wr, itemtag, "sref", "CptThe", "Breite [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptPhi", "L\\u00e4nge [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptCmt", "Notiz");
		};
		writeStringAttr(wr, itemtag, "sref", "Cpt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::DETAIL, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecTouDetail::DpchAppData
 ******************************************************************************/

PnlIdecTouDetail::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECTOUDETAILDATA) {
};

string PnlIdecTouDetail::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecTouDetail::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecTouDetailData");
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
 class PnlIdecTouDetail::DpchAppDo
 ******************************************************************************/

PnlIdecTouDetail::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECTOUDETAILDO) {
	ixVDo = 0;
};

string PnlIdecTouDetail::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecTouDetail::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecTouDetailDo");
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
 class PnlIdecTouDetail::DpchEngData
 ******************************************************************************/

PnlIdecTouDetail::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECTOUDETAILDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecTouDetail::DpchEngData::getSrefsMask() {
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

void PnlIdecTouDetail::DpchEngData::merge(
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

void PnlIdecTouDetail::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecTouDetailData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

