/**
  * \file PnlIdecNavMaint_blks.cpp
  * job handler for job PnlIdecNavMaint (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecNavMaint::VecVDo
 ******************************************************************************/

uint PnlIdecNavMaint::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butusgviewclick") return BUTUSGVIEWCLICK;
	else if (s == "butusgnewcrdclick") return BUTUSGNEWCRDCLICK;
	else if (s == "butusrviewclick") return BUTUSRVIEWCLICK;
	else if (s == "butusrnewcrdclick") return BUTUSRNEWCRDCLICK;
	else if (s == "butscfnewcrdclick") return BUTSCFNEWCRDCLICK;
	else if (s == "bututlnewcrdclick") return BUTUTLNEWCRDCLICK;

	return(0);
};

string PnlIdecNavMaint::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTUSGVIEWCLICK) return("ButUsgViewClick");
	else if (ix == BUTUSGNEWCRDCLICK) return("ButUsgNewcrdClick");
	else if (ix == BUTUSRVIEWCLICK) return("ButUsrViewClick");
	else if (ix == BUTUSRNEWCRDCLICK) return("ButUsrNewcrdClick");
	else if (ix == BUTSCFNEWCRDCLICK) return("ButScfNewcrdClick");
	else if (ix == BUTUTLNEWCRDCLICK) return("ButUtlNewcrdClick");

	return("");
};

/******************************************************************************
 class PnlIdecNavMaint::ContIac
 ******************************************************************************/

PnlIdecNavMaint::ContIac::ContIac(
			const uint numFLstUsg
			, const uint numFLstUsr
		) : Block() {
	this->numFLstUsg = numFLstUsg;
	this->numFLstUsr = numFLstUsr;

	mask = {NUMFLSTUSG, NUMFLSTUSR};
};

bool PnlIdecNavMaint::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecNavMaint");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecNavMaint";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstUsg", numFLstUsg)) add(NUMFLSTUSG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFLstUsr", numFLstUsr)) add(NUMFLSTUSR);
	};

	return basefound;
};

void PnlIdecNavMaint::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecNavMaint";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecNavMaint";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFLstUsg", numFLstUsg);
		writeUintAttr(wr, itemtag, "sref", "numFLstUsr", numFLstUsr);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavMaint::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFLstUsg == comp->numFLstUsg) insert(items, NUMFLSTUSG);
	if (numFLstUsr == comp->numFLstUsr) insert(items, NUMFLSTUSR);

	return(items);
};

set<uint> PnlIdecNavMaint::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFLSTUSG, NUMFLSTUSR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavMaint::StatApp
 ******************************************************************************/

void PnlIdecNavMaint::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
			, const bool LstUsgAlt
			, const bool LstUsrAlt
			, const uint LstUsgNumFirstdisp
			, const uint LstUsrNumFirstdisp
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecNavMaint";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecNavMaint";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "LstUsgAlt", LstUsgAlt);
		writeBoolAttr(wr, itemtag, "sref", "LstUsrAlt", LstUsrAlt);
		writeUintAttr(wr, itemtag, "sref", "LstUsgNumFirstdisp", LstUsgNumFirstdisp);
		writeUintAttr(wr, itemtag, "sref", "LstUsrNumFirstdisp", LstUsrNumFirstdisp);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavMaint::StatShr
 ******************************************************************************/

PnlIdecNavMaint::StatShr::StatShr(
			const bool LstUsgAvail
			, const bool ButUsgViewActive
			, const bool LstUsrAvail
			, const bool ButUsrViewActive
		) : Block() {
	this->LstUsgAvail = LstUsgAvail;
	this->ButUsgViewActive = ButUsgViewActive;
	this->LstUsrAvail = LstUsrAvail;
	this->ButUsrViewActive = ButUsrViewActive;

	mask = {LSTUSGAVAIL, BUTUSGVIEWACTIVE, LSTUSRAVAIL, BUTUSRVIEWACTIVE};
};

void PnlIdecNavMaint::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecNavMaint";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecNavMaint";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "LstUsgAvail", LstUsgAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButUsgViewActive", ButUsgViewActive);
		writeBoolAttr(wr, itemtag, "sref", "LstUsrAvail", LstUsrAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButUsrViewActive", ButUsrViewActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecNavMaint::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (LstUsgAvail == comp->LstUsgAvail) insert(items, LSTUSGAVAIL);
	if (ButUsgViewActive == comp->ButUsgViewActive) insert(items, BUTUSGVIEWACTIVE);
	if (LstUsrAvail == comp->LstUsrAvail) insert(items, LSTUSRAVAIL);
	if (ButUsrViewActive == comp->ButUsrViewActive) insert(items, BUTUSRVIEWACTIVE);

	return(items);
};

set<uint> PnlIdecNavMaint::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {LSTUSGAVAIL, BUTUSGVIEWACTIVE, LSTUSRAVAIL, BUTUSRVIEWACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecNavMaint::Tag
 ******************************************************************************/

void PnlIdecNavMaint::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecNavMaint";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecNavMaint";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Maintenance module");
			writeStringAttr(wr, itemtag, "sref", "CptUsg", "user groups");
			writeStringAttr(wr, itemtag, "sref", "CptUsr", "users");
			writeStringAttr(wr, itemtag, "sref", "CptScf", "system configuration");
			writeStringAttr(wr, itemtag, "sref", "CptUtl", "utilities");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Wartung");
			writeStringAttr(wr, itemtag, "sref", "CptUsg", "Benutzergruppen");
			writeStringAttr(wr, itemtag, "sref", "CptUsr", "Benutzer");
			writeStringAttr(wr, itemtag, "sref", "CptScf", "Systemkonfiguration");
			writeStringAttr(wr, itemtag, "sref", "CptUtl", "Dienstprogramme");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecNavMaint::DpchAppData
 ******************************************************************************/

PnlIdecNavMaint::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVMAINTDATA) {
};

string PnlIdecNavMaint::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavMaint::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecNavMaintData");
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
 class PnlIdecNavMaint::DpchAppDo
 ******************************************************************************/

PnlIdecNavMaint::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECNAVMAINTDO) {
	ixVDo = 0;
};

string PnlIdecNavMaint::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavMaint::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecNavMaintDo");
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
 class PnlIdecNavMaint::DpchEngData
 ******************************************************************************/

PnlIdecNavMaint::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, Feed* feedFLstUsg
			, Feed* feedFLstUsr
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECNAVMAINTDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, FEEDFLSTUSG, FEEDFLSTUSR, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, FEEDFLSTUSG) && feedFLstUsg) this->feedFLstUsg = *feedFLstUsg;
	if (find(this->mask, FEEDFLSTUSR) && feedFLstUsr) this->feedFLstUsr = *feedFLstUsr;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecNavMaint::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(FEEDFLSTUSG)) ss.push_back("feedFLstUsg");
	if (has(FEEDFLSTUSR)) ss.push_back("feedFLstUsr");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecNavMaint::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(FEEDFLSTUSG)) {feedFLstUsg = src->feedFLstUsg; add(FEEDFLSTUSG);};
	if (src->has(FEEDFLSTUSR)) {feedFLstUsr = src->feedFLstUsr; add(FEEDFLSTUSR);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecNavMaint::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecNavMaintData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(FEEDFLSTUSG)) feedFLstUsg.writeXML(wr);
		if (has(FEEDFLSTUSR)) feedFLstUsr.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

