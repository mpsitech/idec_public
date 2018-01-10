/**
  * \file DlgIdecNavLoaini_blks.cpp
  * job handler for job DlgIdecNavLoaini (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class DlgIdecNavLoaini::VecVDit
 ******************************************************************************/

uint DlgIdecNavLoaini::VecVDit::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "ifi") return IFI;
	else if (s == "imp") return IMP;
	else if (s == "acv") return ACV;
	else if (s == "lfi") return LFI;

	return(0);
};

string DlgIdecNavLoaini::VecVDit::getSref(
			const uint ix
		) {
	if (ix == IFI) return("Ifi");
	else if (ix == IMP) return("Imp");
	else if (ix == ACV) return("Acv");
	else if (ix == LFI) return("Lfi");

	return("");
};

string DlgIdecNavLoaini::VecVDit::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == IFI) return("Initialization file");
		else if (ix == IMP) return("Import");
		else if (ix == ACV) return("File archive");
		else if (ix == LFI) return("Log file");
	} else if (ixIdecVLocale == 2) {
		if (ix == IFI) return("Initialisierungsdatei");
		else if (ix == IMP) return("Importieren");
		else if (ix == ACV) return("Dateiarchiv");
		else if (ix == LFI) return("Protokoll");
	};

	return("");
};

void DlgIdecNavLoaini::VecVDit::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class DlgIdecNavLoaini::VecVDo
 ******************************************************************************/

uint DlgIdecNavLoaini::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butdneclick") return BUTDNECLICK;

	return(0);
};

string DlgIdecNavLoaini::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTDNECLICK) return("ButDneClick");

	return("");
};

/******************************************************************************
 class DlgIdecNavLoaini::VecVDoImp
 ******************************************************************************/

uint DlgIdecNavLoaini::VecVDoImp::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butrunclick") return BUTRUNCLICK;
	else if (s == "butstoclick") return BUTSTOCLICK;

	return(0);
};

string DlgIdecNavLoaini::VecVDoImp::getSref(
			const uint ix
		) {
	if (ix == BUTRUNCLICK) return("ButRunClick");
	else if (ix == BUTSTOCLICK) return("ButStoClick");

	return("");
};

/******************************************************************************
 class DlgIdecNavLoaini::VecVSge
 ******************************************************************************/

uint DlgIdecNavLoaini::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "prsidle") return PRSIDLE;
	else if (s == "parse") return PARSE;
	else if (s == "alridecper") return ALRIDECPER;
	else if (s == "prsdone") return PRSDONE;
	else if (s == "impidle") return IMPIDLE;
	else if (s == "import") return IMPORT;
	else if (s == "impdone") return IMPDONE;
	else if (s == "upkidle") return UPKIDLE;
	else if (s == "unpack") return UNPACK;
	else if (s == "done") return DONE;

	return(0);
};

string DlgIdecNavLoaini::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == PRSIDLE) return("prsidle");
	else if (ix == PARSE) return("parse");
	else if (ix == ALRIDECPER) return("alridecper");
	else if (ix == PRSDONE) return("prsdone");
	else if (ix == IMPIDLE) return("impidle");
	else if (ix == IMPORT) return("import");
	else if (ix == IMPDONE) return("impdone");
	else if (ix == UPKIDLE) return("upkidle");
	else if (ix == UNPACK) return("unpack");
	else if (ix == DONE) return("done");

	return("");
};

void DlgIdecNavLoaini::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=11;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class DlgIdecNavLoaini::ContIac
 ******************************************************************************/

DlgIdecNavLoaini::ContIac::ContIac(
			const uint numFDse
		) : Block() {
	this->numFDse = numFDse;

	mask = {NUMFDSE};
};

bool DlgIdecNavLoaini::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacDlgIdecNavLoaini");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacDlgIdecNavLoaini";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFDse", numFDse)) add(NUMFDSE);
	};

	return basefound;
};

void DlgIdecNavLoaini::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacDlgIdecNavLoaini";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacDlgIdecNavLoaini";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFDse", numFDse);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFDse == comp->numFDse) insert(items, NUMFDSE);

	return(items);
};

set<uint> DlgIdecNavLoaini::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFDSE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::ContInf
 ******************************************************************************/

DlgIdecNavLoaini::ContInf::ContInf(
			const uint numFSge
		) : Block() {
	this->numFSge = numFSge;

	mask = {NUMFSGE};
};

void DlgIdecNavLoaini::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfDlgIdecNavLoaini";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfDlgIdecNavLoaini";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFSge", numFSge);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (numFSge == comp->numFSge) insert(items, NUMFSGE);

	return(items);
};

set<uint> DlgIdecNavLoaini::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFSGE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::ContInfImp
 ******************************************************************************/

DlgIdecNavLoaini::ContInfImp::ContInfImp(
			const string& TxtPrg
		) : Block() {
	this->TxtPrg = TxtPrg;

	mask = {TXTPRG};
};

void DlgIdecNavLoaini::ContInfImp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfDlgIdecNavLoainiImp";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfDlgIdecNavLoainiImp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxtPrg", TxtPrg);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::ContInfImp::comm(
			const ContInfImp* comp
		) {
	set<uint> items;

	if (TxtPrg == comp->TxtPrg) insert(items, TXTPRG);

	return(items);
};

set<uint> DlgIdecNavLoaini::ContInfImp::diff(
			const ContInfImp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTPRG};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::StatApp
 ******************************************************************************/

void DlgIdecNavLoaini::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const bool initdone
			, const string& shortMenu
		) {
	if (difftag.length() == 0) difftag = "StatAppDlgIdecNavLoaini";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppDlgIdecNavLoaini";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "initdone", initdone);
		writeStringAttr(wr, itemtag, "sref", "shortMenu", shortMenu);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecNavLoaini::StatShr
 ******************************************************************************/

DlgIdecNavLoaini::StatShr::StatShr(
			const bool ButDneActive
		) : Block() {
	this->ButDneActive = ButDneActive;

	mask = {BUTDNEACTIVE};
};

void DlgIdecNavLoaini::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrDlgIdecNavLoaini";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrDlgIdecNavLoaini";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButDneActive", ButDneActive);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ButDneActive == comp->ButDneActive) insert(items, BUTDNEACTIVE);

	return(items);
};

set<uint> DlgIdecNavLoaini::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTDNEACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::StatShrAcv
 ******************************************************************************/

DlgIdecNavLoaini::StatShrAcv::StatShrAcv(
			const bool UldActive
		) : Block() {
	this->UldActive = UldActive;

	mask = {ULDACTIVE};
};

void DlgIdecNavLoaini::StatShrAcv::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrDlgIdecNavLoainiAcv";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrDlgIdecNavLoainiAcv";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "UldActive", UldActive);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::StatShrAcv::comm(
			const StatShrAcv* comp
		) {
	set<uint> items;

	if (UldActive == comp->UldActive) insert(items, ULDACTIVE);

	return(items);
};

set<uint> DlgIdecNavLoaini::StatShrAcv::diff(
			const StatShrAcv* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {ULDACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::StatShrIfi
 ******************************************************************************/

DlgIdecNavLoaini::StatShrIfi::StatShrIfi(
			const bool UldActive
		) : Block() {
	this->UldActive = UldActive;

	mask = {ULDACTIVE};
};

void DlgIdecNavLoaini::StatShrIfi::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrDlgIdecNavLoainiIfi";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrDlgIdecNavLoainiIfi";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "UldActive", UldActive);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::StatShrIfi::comm(
			const StatShrIfi* comp
		) {
	set<uint> items;

	if (UldActive == comp->UldActive) insert(items, ULDACTIVE);

	return(items);
};

set<uint> DlgIdecNavLoaini::StatShrIfi::diff(
			const StatShrIfi* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {ULDACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::StatShrImp
 ******************************************************************************/

DlgIdecNavLoaini::StatShrImp::StatShrImp(
			const bool ButRunActive
			, const bool ButStoActive
		) : Block() {
	this->ButRunActive = ButRunActive;
	this->ButStoActive = ButStoActive;

	mask = {BUTRUNACTIVE, BUTSTOACTIVE};
};

void DlgIdecNavLoaini::StatShrImp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrDlgIdecNavLoainiImp";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrDlgIdecNavLoainiImp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButRunActive", ButRunActive);
		writeBoolAttr(wr, itemtag, "sref", "ButStoActive", ButStoActive);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::StatShrImp::comm(
			const StatShrImp* comp
		) {
	set<uint> items;

	if (ButRunActive == comp->ButRunActive) insert(items, BUTRUNACTIVE);
	if (ButStoActive == comp->ButStoActive) insert(items, BUTSTOACTIVE);

	return(items);
};

set<uint> DlgIdecNavLoaini::StatShrImp::diff(
			const StatShrImp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTRUNACTIVE, BUTSTOACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::StatShrLfi
 ******************************************************************************/

DlgIdecNavLoaini::StatShrLfi::StatShrLfi(
			const bool DldActive
		) : Block() {
	this->DldActive = DldActive;

	mask = {DLDACTIVE};
};

void DlgIdecNavLoaini::StatShrLfi::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrDlgIdecNavLoainiLfi";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrDlgIdecNavLoainiLfi";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "DldActive", DldActive);
	xmlTextWriterEndElement(wr);
};

set<uint> DlgIdecNavLoaini::StatShrLfi::comm(
			const StatShrLfi* comp
		) {
	set<uint> items;

	if (DldActive == comp->DldActive) insert(items, DLDACTIVE);

	return(items);
};

set<uint> DlgIdecNavLoaini::StatShrLfi::diff(
			const StatShrLfi* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {DLDACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class DlgIdecNavLoaini::Tag
 ******************************************************************************/

void DlgIdecNavLoaini::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagDlgIdecNavLoaini";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemDlgIdecNavLoaini";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		};
		writeStringAttr(wr, itemtag, "sref", "Cpt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::LOAINI, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButDne", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::DONE, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecNavLoaini::TagAcv
 ******************************************************************************/

void DlgIdecNavLoaini::TagAcv::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagDlgIdecNavLoainiAcv";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemDlgIdecNavLoainiAcv";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		};
		writeStringAttr(wr, itemtag, "sref", "Uld", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::UPLOAD, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "Cpt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::FILENAME, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecNavLoaini::TagIfi
 ******************************************************************************/

void DlgIdecNavLoaini::TagIfi::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagDlgIdecNavLoainiIfi";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemDlgIdecNavLoainiIfi";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		};
		writeStringAttr(wr, itemtag, "sref", "Uld", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::UPLOAD, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "Cpt", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::FILENAME, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecNavLoaini::TagImp
 ******************************************************************************/

void DlgIdecNavLoaini::TagImp::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagDlgIdecNavLoainiImp";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemDlgIdecNavLoainiImp";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		};
		writeStringAttr(wr, itemtag, "sref", "CptPrg", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::PROGRESS, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButRun", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::RUN, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButSto", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::STOP, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecNavLoaini::TagLfi
 ******************************************************************************/

void DlgIdecNavLoaini::TagLfi::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagDlgIdecNavLoainiLfi";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemDlgIdecNavLoainiLfi";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		};
		writeStringAttr(wr, itemtag, "sref", "Dld", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::DOWNLOAD, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DlgIdecNavLoaini::DpchAppData
 ******************************************************************************/

DlgIdecNavLoaini::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECNAVLOAINIDATA) {
};

string DlgIdecNavLoaini::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecNavLoaini::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppDlgIdecNavLoainiData");
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
 class DlgIdecNavLoaini::DpchAppDo
 ******************************************************************************/

DlgIdecNavLoaini::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPDLGIDECNAVLOAINIDO) {
	ixVDo = 0;
	ixVDoImp = 0;
};

string DlgIdecNavLoaini::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");
	if (has(IXVDOIMP)) ss.push_back("ixVDoImp");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecNavLoaini::DpchAppDo::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string scrJref;
	string srefIxVDo;
	string srefIxVDoImp;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppDlgIdecNavLoainiDo");
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
		if (extractStringUclc(docctx, basexpath, "srefIxVDoImp", "", srefIxVDoImp)) {
			ixVDoImp = VecVDoImp::getIx(srefIxVDoImp);
			add(IXVDOIMP);
		};
	} else {
	};
};

/******************************************************************************
 class DlgIdecNavLoaini::DpchEngData
 ******************************************************************************/

DlgIdecNavLoaini::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, ContInfImp* continfimp
			, Feed* feedFDse
			, Feed* feedFSge
			, StatShr* statshr
			, StatShrAcv* statshracv
			, StatShrIfi* statshrifi
			, StatShrImp* statshrimp
			, StatShrLfi* statshrlfi
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGDLGIDECNAVLOAINIDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, CONTINFIMP, FEEDFDSE, FEEDFSGE, STATAPP, STATSHR, STATSHRACV, STATSHRIFI, STATSHRIMP, STATSHRLFI, TAG, TAGACV, TAGIFI, TAGIMP, TAGLFI};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, CONTINFIMP) && continfimp) this->continfimp = *continfimp;
	if (find(this->mask, FEEDFDSE) && feedFDse) this->feedFDse = *feedFDse;
	if (find(this->mask, FEEDFSGE) && feedFSge) this->feedFSge = *feedFSge;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
	if (find(this->mask, STATSHRACV) && statshracv) this->statshracv = *statshracv;
	if (find(this->mask, STATSHRIFI) && statshrifi) this->statshrifi = *statshrifi;
	if (find(this->mask, STATSHRIMP) && statshrimp) this->statshrimp = *statshrimp;
	if (find(this->mask, STATSHRLFI) && statshrlfi) this->statshrlfi = *statshrlfi;
};

string DlgIdecNavLoaini::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(CONTINFIMP)) ss.push_back("continfimp");
	if (has(FEEDFDSE)) ss.push_back("feedFDse");
	if (has(FEEDFSGE)) ss.push_back("feedFSge");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(STATSHRACV)) ss.push_back("statshracv");
	if (has(STATSHRIFI)) ss.push_back("statshrifi");
	if (has(STATSHRIMP)) ss.push_back("statshrimp");
	if (has(STATSHRLFI)) ss.push_back("statshrlfi");
	if (has(TAG)) ss.push_back("tag");
	if (has(TAGACV)) ss.push_back("tagacv");
	if (has(TAGIFI)) ss.push_back("tagifi");
	if (has(TAGIMP)) ss.push_back("tagimp");
	if (has(TAGLFI)) ss.push_back("taglfi");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DlgIdecNavLoaini::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(CONTINFIMP)) {continfimp = src->continfimp; add(CONTINFIMP);};
	if (src->has(FEEDFDSE)) {feedFDse = src->feedFDse; add(FEEDFDSE);};
	if (src->has(FEEDFSGE)) {feedFSge = src->feedFSge; add(FEEDFSGE);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(STATSHRACV)) {statshracv = src->statshracv; add(STATSHRACV);};
	if (src->has(STATSHRIFI)) {statshrifi = src->statshrifi; add(STATSHRIFI);};
	if (src->has(STATSHRIMP)) {statshrimp = src->statshrimp; add(STATSHRIMP);};
	if (src->has(STATSHRLFI)) {statshrlfi = src->statshrlfi; add(STATSHRLFI);};
	if (src->has(TAG)) add(TAG);
	if (src->has(TAGACV)) add(TAGACV);
	if (src->has(TAGIFI)) add(TAGIFI);
	if (src->has(TAGIMP)) add(TAGIMP);
	if (src->has(TAGLFI)) add(TAGLFI);
};

void DlgIdecNavLoaini::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngDlgIdecNavLoainiData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(CONTINFIMP)) continfimp.writeXML(wr);
		if (has(FEEDFDSE)) feedFDse.writeXML(wr);
		if (has(FEEDFSGE)) feedFSge.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(STATSHRACV)) statshracv.writeXML(wr);
		if (has(STATSHRIFI)) statshrifi.writeXML(wr);
		if (has(STATSHRIMP)) statshrimp.writeXML(wr);
		if (has(STATSHRLFI)) statshrlfi.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
		if (has(TAGACV)) TagAcv::writeXML(ixIdecVLocale, wr);
		if (has(TAGIFI)) TagIfi::writeXML(ixIdecVLocale, wr);
		if (has(TAGIMP)) TagImp::writeXML(ixIdecVLocale, wr);
		if (has(TAGLFI)) TagLfi::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

