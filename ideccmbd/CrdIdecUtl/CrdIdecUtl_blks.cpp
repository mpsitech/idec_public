/**
  * \file CrdIdecUtl_blks.cpp
  * job handler for job CrdIdecUtl (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class CrdIdecUtl::VecVDo
 ******************************************************************************/

uint CrdIdecUtl::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "close") return CLOSE;
	else if (s == "mitappabtclick") return MITAPPABTCLICK;
	else if (s == "mitcrdtheclick") return MITCRDTHECLICK;
	else if (s == "mitcrdphiclick") return MITCRDPHICLICK;
	else if (s == "mitcrdsteclick") return MITCRDSTECLICK;
	else if (s == "mitcrdfsnclick") return MITCRDFSNCLICK;
	else if (s == "mitcrdqnuclick") return MITCRDQNUCLICK;
	else if (s == "mitcrdqalclick") return MITCRDQALCLICK;

	return(0);
};

string CrdIdecUtl::VecVDo::getSref(
			const uint ix
		) {
	if (ix == CLOSE) return("close");
	else if (ix == MITAPPABTCLICK) return("MitAppAbtClick");
	else if (ix == MITCRDTHECLICK) return("MitCrdTheClick");
	else if (ix == MITCRDPHICLICK) return("MitCrdPhiClick");
	else if (ix == MITCRDSTECLICK) return("MitCrdSteClick");
	else if (ix == MITCRDFSNCLICK) return("MitCrdFsnClick");
	else if (ix == MITCRDQNUCLICK) return("MitCrdQnuClick");
	else if (ix == MITCRDQALCLICK) return("MitCrdQalClick");

	return("");
};

/******************************************************************************
 class CrdIdecUtl::VecVSge
 ******************************************************************************/

uint CrdIdecUtl::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alridecabt") return ALRIDECABT;
	else if (s == "close") return CLOSE;

	return(0);
};

string CrdIdecUtl::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRIDECABT) return("alridecabt");
	else if (ix == CLOSE) return("close");

	return("");
};

void CrdIdecUtl::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class CrdIdecUtl::ContInf
 ******************************************************************************/

CrdIdecUtl::ContInf::ContInf(
			const uint numFSge
			, const string& MrlAppHlp
		) : Block() {
	this->numFSge = numFSge;
	this->MrlAppHlp = MrlAppHlp;

	mask = {NUMFSGE, MRLAPPHLP};
};

void CrdIdecUtl::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecUtl";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecUtl";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFSge", numFSge);
		writeStringAttr(wr, itemtag, "sref", "MrlAppHlp", MrlAppHlp);
	xmlTextWriterEndElement(wr);
};

set<uint> CrdIdecUtl::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp == comp->MrlAppHlp) insert(items, MRLAPPHLP);

	return(items);
};

set<uint> CrdIdecUtl::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE, MRLAPPHLP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecUtl::StatApp
 ******************************************************************************/

void CrdIdecUtl::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneSpiterm
			, const bool initdoneHeadbar
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecUtl";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecUtl";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVReqitmode", VecIdecVReqitmode::getSref(ixIdecVReqitmode));
		writeUsmallintAttr(wr, itemtag, "sref", "latency", latency);
		writeStringAttr(wr, itemtag, "sref", "shortMenu", shortMenu);
		writeUintAttr(wr, itemtag, "sref", "widthMenu", widthMenu);
		writeBoolAttr(wr, itemtag, "sref", "initdoneSpiterm", initdoneSpiterm);
		writeBoolAttr(wr, itemtag, "sref", "initdoneHeadbar", initdoneHeadbar);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecUtl::StatShr
 ******************************************************************************/

CrdIdecUtl::StatShr::StatShr(
			const ubigint jrefDlgfusion
			, const ubigint jrefDlgphi
			, const ubigint jrefDlgqcdaln
			, const ubigint jrefDlgqcdnuc
			, const ubigint jrefDlgstereo
			, const ubigint jrefDlgtheta
			, const ubigint jrefSpiterm
			, const ubigint jrefHeadbar
		) : Block() {
	this->jrefDlgfusion = jrefDlgfusion;
	this->jrefDlgphi = jrefDlgphi;
	this->jrefDlgqcdaln = jrefDlgqcdaln;
	this->jrefDlgqcdnuc = jrefDlgqcdnuc;
	this->jrefDlgstereo = jrefDlgstereo;
	this->jrefDlgtheta = jrefDlgtheta;
	this->jrefSpiterm = jrefSpiterm;
	this->jrefHeadbar = jrefHeadbar;

	mask = {JREFDLGFUSION, JREFDLGPHI, JREFDLGQCDALN, JREFDLGQCDNUC, JREFDLGSTEREO, JREFDLGTHETA, JREFSPITERM, JREFHEADBAR};
};

void CrdIdecUtl::StatShr::writeXML(
			pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecUtl";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecUtl";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgfusion", Scr::scramble(mScr, scr, descr, jrefDlgfusion));
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgphi", Scr::scramble(mScr, scr, descr, jrefDlgphi));
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgqcdaln", Scr::scramble(mScr, scr, descr, jrefDlgqcdaln));
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgqcdnuc", Scr::scramble(mScr, scr, descr, jrefDlgqcdnuc));
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgstereo", Scr::scramble(mScr, scr, descr, jrefDlgstereo));
		writeStringAttr(wr, itemtag, "sref", "scrJrefDlgtheta", Scr::scramble(mScr, scr, descr, jrefDlgtheta));
		writeStringAttr(wr, itemtag, "sref", "scrJrefSpiterm", Scr::scramble(mScr, scr, descr, jrefSpiterm));
		writeStringAttr(wr, itemtag, "sref", "scrJrefHeadbar", Scr::scramble(mScr, scr, descr, jrefHeadbar));
	xmlTextWriterEndElement(wr);
};

set<uint> CrdIdecUtl::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (jrefDlgfusion == comp->jrefDlgfusion) insert(items, JREFDLGFUSION);
	if (jrefDlgphi == comp->jrefDlgphi) insert(items, JREFDLGPHI);
	if (jrefDlgqcdaln == comp->jrefDlgqcdaln) insert(items, JREFDLGQCDALN);
	if (jrefDlgqcdnuc == comp->jrefDlgqcdnuc) insert(items, JREFDLGQCDNUC);
	if (jrefDlgstereo == comp->jrefDlgstereo) insert(items, JREFDLGSTEREO);
	if (jrefDlgtheta == comp->jrefDlgtheta) insert(items, JREFDLGTHETA);
	if (jrefSpiterm == comp->jrefSpiterm) insert(items, JREFSPITERM);
	if (jrefHeadbar == comp->jrefHeadbar) insert(items, JREFHEADBAR);

	return(items);
};

set<uint> CrdIdecUtl::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {JREFDLGFUSION, JREFDLGPHI, JREFDLGQCDALN, JREFDLGQCDNUC, JREFDLGSTEREO, JREFDLGTHETA, JREFSPITERM, JREFHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecUtl::Tag
 ******************************************************************************/

void CrdIdecUtl::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecUtl";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecUtl";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "MitCrdThe", "Calibrate \\u03d1 axis ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdPhi", "Calibrate \\u03c6 axis ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdSte", "Calibrate stereo overlay ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdFsn", "Calibrate VIS-LWIR overlay ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdQnu", "Calibrate QCD non-uniformity ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdQal", "Calibrate QCD alignment ...");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "MitCrdThe", "\\u0398-Achse kalibrieren ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdPhi", "\\u03a6-Achse kalibrieren ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdSte", "Stereo-\\u00dcberlagerung kalibrieren ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdFsn", "VIS-LWIR \\u00dcberlagerung kalibrieren ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdQnu", "QCD-Ungleichf\\u00f6rmigkeit kalibrieren ...");
			writeStringAttr(wr, itemtag, "sref", "MitCrdQal", "QCD-Ausrichtung kalibrieren ...");
		};
		writeStringAttr(wr, itemtag, "sref", "MitAppAbt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::ABOUT, ixIdecVLocale)) + " ...");
		writeStringAttr(wr, itemtag, "sref", "MrlAppHlp", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::HELP, ixIdecVLocale)) + " ...");
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecUtl::DpchAppDo
 ******************************************************************************/

CrdIdecUtl::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUTLDO) {
	ixVDo = 0;
};

string CrdIdecUtl::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecUtl::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecUtlDo");
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
 class CrdIdecUtl::DpchEngData
 ******************************************************************************/

CrdIdecUtl::DpchEngData::DpchEngData(
			const ubigint jref
			, ContInf* continf
			, Feed* feedFSge
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUTLDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, FEEDFSGE, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFSGE) && feedFSge) this->feedFSge = *feedFSge;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string CrdIdecUtl::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecUtl::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFSGE)) {feedFSge = src->feedFSge; add(FEEDFSGE);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void CrdIdecUtl::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecUtlData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFSGE)) feedFSge.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(mScr, scr, descr, wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

