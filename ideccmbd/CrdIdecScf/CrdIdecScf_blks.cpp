/**
  * \file CrdIdecScf_blks.cpp
  * job handler for job CrdIdecScf (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class CrdIdecScf::VecVDo
 ******************************************************************************/

uint CrdIdecScf::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "close") return CLOSE;
	else if (s == "mitappabtclick") return MITAPPABTCLICK;

	return(0);
};

string CrdIdecScf::VecVDo::getSref(
			const uint ix
		) {
	if (ix == CLOSE) return("close");
	else if (ix == MITAPPABTCLICK) return("MitAppAbtClick");

	return("");
};

/******************************************************************************
 class CrdIdecScf::VecVSge
 ******************************************************************************/

uint CrdIdecScf::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "alridecabt") return ALRIDECABT;
	else if (s == "close") return CLOSE;

	return(0);
};

string CrdIdecScf::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == ALRIDECABT) return("alridecabt");
	else if (ix == CLOSE) return("close");

	return("");
};

void CrdIdecScf::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class CrdIdecScf::ContInf
 ******************************************************************************/

CrdIdecScf::ContInf::ContInf(
			const uint numFSge
			, const string& MrlAppHlp
		) : Block() {
	this->numFSge = numFSge;
	this->MrlAppHlp = MrlAppHlp;

	mask = {NUMFSGE, MRLAPPHLP};
};

void CrdIdecScf::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScf";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScf";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFSge", numFSge);
		writeStringAttr(wr, itemtag, "sref", "MrlAppHlp", MrlAppHlp);
	xmlTextWriterEndElement(wr);
};

set<uint> CrdIdecScf::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);
	if (MrlAppHlp == comp->MrlAppHlp) insert(items, MRLAPPHLP);

	return(items);
};

set<uint> CrdIdecScf::ContInf::diff(
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
 class CrdIdecScf::StatApp
 ******************************************************************************/

void CrdIdecScf::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVReqitmode
			, const usmallint latency
			, const string& shortMenu
			, const uint widthMenu
			, const bool initdoneConn
			, const bool initdoneStatus
			, const bool initdoneMech
			, const bool initdoneOptics
			, const bool initdoneTrigger
			, const bool initdoneLwir
			, const bool initdoneQcd
			, const bool initdoneRecord
			, const bool initdoneHeadbar
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScf";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScf";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVReqitmode", VecIdecVReqitmode::getSref(ixIdecVReqitmode));
		writeUsmallintAttr(wr, itemtag, "sref", "latency", latency);
		writeStringAttr(wr, itemtag, "sref", "shortMenu", shortMenu);
		writeUintAttr(wr, itemtag, "sref", "widthMenu", widthMenu);
		writeBoolAttr(wr, itemtag, "sref", "initdoneConn", initdoneConn);
		writeBoolAttr(wr, itemtag, "sref", "initdoneStatus", initdoneStatus);
		writeBoolAttr(wr, itemtag, "sref", "initdoneMech", initdoneMech);
		writeBoolAttr(wr, itemtag, "sref", "initdoneOptics", initdoneOptics);
		writeBoolAttr(wr, itemtag, "sref", "initdoneTrigger", initdoneTrigger);
		writeBoolAttr(wr, itemtag, "sref", "initdoneLwir", initdoneLwir);
		writeBoolAttr(wr, itemtag, "sref", "initdoneQcd", initdoneQcd);
		writeBoolAttr(wr, itemtag, "sref", "initdoneRecord", initdoneRecord);
		writeBoolAttr(wr, itemtag, "sref", "initdoneHeadbar", initdoneHeadbar);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecScf::StatShr
 ******************************************************************************/

CrdIdecScf::StatShr::StatShr(
			const ubigint jrefConn
			, const ubigint jrefStatus
			, const ubigint jrefMech
			, const ubigint jrefOptics
			, const ubigint jrefTrigger
			, const ubigint jrefLwir
			, const ubigint jrefQcd
			, const ubigint jrefRecord
			, const ubigint jrefHeadbar
		) : Block() {
	this->jrefConn = jrefConn;
	this->jrefStatus = jrefStatus;
	this->jrefMech = jrefMech;
	this->jrefOptics = jrefOptics;
	this->jrefTrigger = jrefTrigger;
	this->jrefLwir = jrefLwir;
	this->jrefQcd = jrefQcd;
	this->jrefRecord = jrefRecord;
	this->jrefHeadbar = jrefHeadbar;

	mask = {JREFCONN, JREFSTATUS, JREFMECH, JREFOPTICS, JREFTRIGGER, JREFLWIR, JREFQCD, JREFRECORD, JREFHEADBAR};
};

void CrdIdecScf::StatShr::writeXML(
			pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScf";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScf";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "scrJrefConn", Scr::scramble(mScr, scr, descr, jrefConn));
		writeStringAttr(wr, itemtag, "sref", "scrJrefStatus", Scr::scramble(mScr, scr, descr, jrefStatus));
		writeStringAttr(wr, itemtag, "sref", "scrJrefMech", Scr::scramble(mScr, scr, descr, jrefMech));
		writeStringAttr(wr, itemtag, "sref", "scrJrefOptics", Scr::scramble(mScr, scr, descr, jrefOptics));
		writeStringAttr(wr, itemtag, "sref", "scrJrefTrigger", Scr::scramble(mScr, scr, descr, jrefTrigger));
		writeStringAttr(wr, itemtag, "sref", "scrJrefLwir", Scr::scramble(mScr, scr, descr, jrefLwir));
		writeStringAttr(wr, itemtag, "sref", "scrJrefQcd", Scr::scramble(mScr, scr, descr, jrefQcd));
		writeStringAttr(wr, itemtag, "sref", "scrJrefRecord", Scr::scramble(mScr, scr, descr, jrefRecord));
		writeStringAttr(wr, itemtag, "sref", "scrJrefHeadbar", Scr::scramble(mScr, scr, descr, jrefHeadbar));
	xmlTextWriterEndElement(wr);
};

set<uint> CrdIdecScf::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (jrefConn == comp->jrefConn) insert(items, JREFCONN);
	if (jrefStatus == comp->jrefStatus) insert(items, JREFSTATUS);
	if (jrefMech == comp->jrefMech) insert(items, JREFMECH);
	if (jrefOptics == comp->jrefOptics) insert(items, JREFOPTICS);
	if (jrefTrigger == comp->jrefTrigger) insert(items, JREFTRIGGER);
	if (jrefLwir == comp->jrefLwir) insert(items, JREFLWIR);
	if (jrefQcd == comp->jrefQcd) insert(items, JREFQCD);
	if (jrefRecord == comp->jrefRecord) insert(items, JREFRECORD);
	if (jrefHeadbar == comp->jrefHeadbar) insert(items, JREFHEADBAR);

	return(items);
};

set<uint> CrdIdecScf::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {JREFCONN, JREFSTATUS, JREFMECH, JREFOPTICS, JREFTRIGGER, JREFLWIR, JREFQCD, JREFRECORD, JREFHEADBAR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class CrdIdecScf::Tag
 ******************************************************************************/

void CrdIdecScf::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScf";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScf";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		};
		writeStringAttr(wr, itemtag, "sref", "MitAppAbt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::ABOUT, ixIdecVLocale)) + " ...");
		writeStringAttr(wr, itemtag, "sref", "MrlAppHlp", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::HELP, ixIdecVLocale)) + " ...");
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class CrdIdecScf::DpchAppDo
 ******************************************************************************/

CrdIdecScf::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFDO) {
	ixVDo = 0;
};

string CrdIdecScf::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void CrdIdecScf::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfDo");
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
 class CrdIdecScf::DpchEngData
 ******************************************************************************/

CrdIdecScf::DpchEngData::DpchEngData(
			const ubigint jref
			, ContInf* continf
			, Feed* feedFSge
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF, FEEDFSGE, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFSGE) && feedFSge) this->feedFSge = *feedFSge;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string CrdIdecScf::DpchEngData::getSrefsMask() {
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

void CrdIdecScf::DpchEngData::merge(
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

void CrdIdecScf::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFSGE)) feedFSge.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(mScr, scr, descr, wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

