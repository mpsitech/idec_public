/**
  * \file PnlIdecScfRecord_blks.cpp
  * job handler for job PnlIdecScfRecord (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecScfRecord::VecVDo
 ******************************************************************************/

uint PnlIdecScfRecord::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfRecord::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfRecord::ContIac
 ******************************************************************************/

PnlIdecScfRecord::ContIac::ContIac(
			const uint numFPupFlr
			, const bool ChkFlg
			, const uint numFPupFrr
			, const bool ChkFrg
			, const uint numFPupFir
			, const bool ChkFqc
			, const bool ChkFst
			, const double SldVfr
			, const uint numFPupVlr
			, const bool ChkVlg
			, const uint numFPupVrr
			, const bool ChkVrg
			, const uint numFPupVir
			, const bool ChkVqc
			, const bool ChkVst
			, const uint numFPupOwr
		) : Block() {
	this->numFPupFlr = numFPupFlr;
	this->ChkFlg = ChkFlg;
	this->numFPupFrr = numFPupFrr;
	this->ChkFrg = ChkFrg;
	this->numFPupFir = numFPupFir;
	this->ChkFqc = ChkFqc;
	this->ChkFst = ChkFst;
	this->SldVfr = SldVfr;
	this->numFPupVlr = numFPupVlr;
	this->ChkVlg = ChkVlg;
	this->numFPupVrr = numFPupVrr;
	this->ChkVrg = ChkVrg;
	this->numFPupVir = numFPupVir;
	this->ChkVqc = ChkVqc;
	this->ChkVst = ChkVst;
	this->numFPupOwr = numFPupOwr;

	mask = {NUMFPUPFLR, CHKFLG, NUMFPUPFRR, CHKFRG, NUMFPUPFIR, CHKFQC, CHKFST, SLDVFR, NUMFPUPVLR, CHKVLG, NUMFPUPVRR, CHKVRG, NUMFPUPVIR, CHKVQC, CHKVST, NUMFPUPOWR};
};

bool PnlIdecScfRecord::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfRecord";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFlr", numFPupFlr)) add(NUMFPUPFLR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFlg", ChkFlg)) add(CHKFLG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFrr", numFPupFrr)) add(NUMFPUPFRR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFrg", ChkFrg)) add(CHKFRG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFir", numFPupFir)) add(NUMFPUPFIR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFqc", ChkFqc)) add(CHKFQC);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkFst", ChkFst)) add(CHKFST);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldVfr", SldVfr)) add(SLDVFR);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVlr", numFPupVlr)) add(NUMFPUPVLR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVlg", ChkVlg)) add(CHKVLG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVrr", numFPupVrr)) add(NUMFPUPVRR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVrg", ChkVrg)) add(CHKVRG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVir", numFPupVir)) add(NUMFPUPVIR);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVqc", ChkVqc)) add(CHKVQC);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVst", ChkVst)) add(CHKVST);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupOwr", numFPupOwr)) add(NUMFPUPOWR);
	};

	return basefound;
};

void PnlIdecScfRecord::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfRecord";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupFlr", numFPupFlr);
		writeBoolAttr(wr, itemtag, "sref", "ChkFlg", ChkFlg);
		writeUintAttr(wr, itemtag, "sref", "numFPupFrr", numFPupFrr);
		writeBoolAttr(wr, itemtag, "sref", "ChkFrg", ChkFrg);
		writeUintAttr(wr, itemtag, "sref", "numFPupFir", numFPupFir);
		writeBoolAttr(wr, itemtag, "sref", "ChkFqc", ChkFqc);
		writeBoolAttr(wr, itemtag, "sref", "ChkFst", ChkFst);
		writeDoubleAttr(wr, itemtag, "sref", "SldVfr", SldVfr);
		writeUintAttr(wr, itemtag, "sref", "numFPupVlr", numFPupVlr);
		writeBoolAttr(wr, itemtag, "sref", "ChkVlg", ChkVlg);
		writeUintAttr(wr, itemtag, "sref", "numFPupVrr", numFPupVrr);
		writeBoolAttr(wr, itemtag, "sref", "ChkVrg", ChkVrg);
		writeUintAttr(wr, itemtag, "sref", "numFPupVir", numFPupVir);
		writeBoolAttr(wr, itemtag, "sref", "ChkVqc", ChkVqc);
		writeBoolAttr(wr, itemtag, "sref", "ChkVst", ChkVst);
		writeUintAttr(wr, itemtag, "sref", "numFPupOwr", numFPupOwr);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfRecord::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupFlr == comp->numFPupFlr) insert(items, NUMFPUPFLR);
	if (ChkFlg == comp->ChkFlg) insert(items, CHKFLG);
	if (numFPupFrr == comp->numFPupFrr) insert(items, NUMFPUPFRR);
	if (ChkFrg == comp->ChkFrg) insert(items, CHKFRG);
	if (numFPupFir == comp->numFPupFir) insert(items, NUMFPUPFIR);
	if (ChkFqc == comp->ChkFqc) insert(items, CHKFQC);
	if (ChkFst == comp->ChkFst) insert(items, CHKFST);
	if (compareDouble(SldVfr, comp->SldVfr) < 1.0e-4) insert(items, SLDVFR);
	if (numFPupVlr == comp->numFPupVlr) insert(items, NUMFPUPVLR);
	if (ChkVlg == comp->ChkVlg) insert(items, CHKVLG);
	if (numFPupVrr == comp->numFPupVrr) insert(items, NUMFPUPVRR);
	if (ChkVrg == comp->ChkVrg) insert(items, CHKVRG);
	if (numFPupVir == comp->numFPupVir) insert(items, NUMFPUPVIR);
	if (ChkVqc == comp->ChkVqc) insert(items, CHKVQC);
	if (ChkVst == comp->ChkVst) insert(items, CHKVST);
	if (numFPupOwr == comp->numFPupOwr) insert(items, NUMFPUPOWR);

	return(items);
};

set<uint> PnlIdecScfRecord::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPFLR, CHKFLG, NUMFPUPFRR, CHKFRG, NUMFPUPFIR, CHKFQC, CHKFST, SLDVFR, NUMFPUPVLR, CHKVLG, NUMFPUPVRR, CHKVRG, NUMFPUPVIR, CHKVQC, CHKVST, NUMFPUPOWR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfRecord::ContInf
 ******************************************************************************/

PnlIdecScfRecord::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

void PnlIdecScfRecord::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfRecord";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfRecord::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecScfRecord::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfRecord::StatApp
 ******************************************************************************/

void PnlIdecScfRecord::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScfRecord";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScfRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfRecord::StatShr
 ******************************************************************************/

PnlIdecScfRecord::StatShr::StatShr(
			const bool PupFlrActive
			, const bool ChkFlgActive
			, const bool PupFrrActive
			, const bool ChkFrgActive
			, const bool PupFirActive
			, const bool ChkFqcActive
			, const bool ChkFstActive
			, const bool SldVfrActive
			, const double SldVfrMin
			, const double SldVfrMax
			, const bool PupVlrActive
			, const bool ChkVlgActive
			, const bool PupVrrActive
			, const bool ChkVrgActive
			, const bool PupVirActive
			, const bool ChkVqcActive
			, const bool ChkVstActive
			, const bool PupOwrActive
		) : Block() {
	this->PupFlrActive = PupFlrActive;
	this->ChkFlgActive = ChkFlgActive;
	this->PupFrrActive = PupFrrActive;
	this->ChkFrgActive = ChkFrgActive;
	this->PupFirActive = PupFirActive;
	this->ChkFqcActive = ChkFqcActive;
	this->ChkFstActive = ChkFstActive;
	this->SldVfrActive = SldVfrActive;
	this->SldVfrMin = SldVfrMin;
	this->SldVfrMax = SldVfrMax;
	this->PupVlrActive = PupVlrActive;
	this->ChkVlgActive = ChkVlgActive;
	this->PupVrrActive = PupVrrActive;
	this->ChkVrgActive = ChkVrgActive;
	this->PupVirActive = PupVirActive;
	this->ChkVqcActive = ChkVqcActive;
	this->ChkVstActive = ChkVstActive;
	this->PupOwrActive = PupOwrActive;

	mask = {PUPFLRACTIVE, CHKFLGACTIVE, PUPFRRACTIVE, CHKFRGACTIVE, PUPFIRACTIVE, CHKFQCACTIVE, CHKFSTACTIVE, SLDVFRACTIVE, SLDVFRMIN, SLDVFRMAX, PUPVLRACTIVE, CHKVLGACTIVE, PUPVRRACTIVE, CHKVRGACTIVE, PUPVIRACTIVE, CHKVQCACTIVE, CHKVSTACTIVE, PUPOWRACTIVE};
};

void PnlIdecScfRecord::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfRecord";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "PupFlrActive", PupFlrActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkFlgActive", ChkFlgActive);
		writeBoolAttr(wr, itemtag, "sref", "PupFrrActive", PupFrrActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkFrgActive", ChkFrgActive);
		writeBoolAttr(wr, itemtag, "sref", "PupFirActive", PupFirActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkFqcActive", ChkFqcActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkFstActive", ChkFstActive);
		writeBoolAttr(wr, itemtag, "sref", "SldVfrActive", SldVfrActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldVfrMin", SldVfrMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldVfrMax", SldVfrMax);
		writeBoolAttr(wr, itemtag, "sref", "PupVlrActive", PupVlrActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkVlgActive", ChkVlgActive);
		writeBoolAttr(wr, itemtag, "sref", "PupVrrActive", PupVrrActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkVrgActive", ChkVrgActive);
		writeBoolAttr(wr, itemtag, "sref", "PupVirActive", PupVirActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkVqcActive", ChkVqcActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkVstActive", ChkVstActive);
		writeBoolAttr(wr, itemtag, "sref", "PupOwrActive", PupOwrActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfRecord::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (PupFlrActive == comp->PupFlrActive) insert(items, PUPFLRACTIVE);
	if (ChkFlgActive == comp->ChkFlgActive) insert(items, CHKFLGACTIVE);
	if (PupFrrActive == comp->PupFrrActive) insert(items, PUPFRRACTIVE);
	if (ChkFrgActive == comp->ChkFrgActive) insert(items, CHKFRGACTIVE);
	if (PupFirActive == comp->PupFirActive) insert(items, PUPFIRACTIVE);
	if (ChkFqcActive == comp->ChkFqcActive) insert(items, CHKFQCACTIVE);
	if (ChkFstActive == comp->ChkFstActive) insert(items, CHKFSTACTIVE);
	if (SldVfrActive == comp->SldVfrActive) insert(items, SLDVFRACTIVE);
	if (compareDouble(SldVfrMin, comp->SldVfrMin) < 1.0e-4) insert(items, SLDVFRMIN);
	if (compareDouble(SldVfrMax, comp->SldVfrMax) < 1.0e-4) insert(items, SLDVFRMAX);
	if (PupVlrActive == comp->PupVlrActive) insert(items, PUPVLRACTIVE);
	if (ChkVlgActive == comp->ChkVlgActive) insert(items, CHKVLGACTIVE);
	if (PupVrrActive == comp->PupVrrActive) insert(items, PUPVRRACTIVE);
	if (ChkVrgActive == comp->ChkVrgActive) insert(items, CHKVRGACTIVE);
	if (PupVirActive == comp->PupVirActive) insert(items, PUPVIRACTIVE);
	if (ChkVqcActive == comp->ChkVqcActive) insert(items, CHKVQCACTIVE);
	if (ChkVstActive == comp->ChkVstActive) insert(items, CHKVSTACTIVE);
	if (PupOwrActive == comp->PupOwrActive) insert(items, PUPOWRACTIVE);

	return(items);
};

set<uint> PnlIdecScfRecord::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {PUPFLRACTIVE, CHKFLGACTIVE, PUPFRRACTIVE, CHKFRGACTIVE, PUPFIRACTIVE, CHKFQCACTIVE, CHKFSTACTIVE, SLDVFRACTIVE, SLDVFRMIN, SLDVFRMAX, PUPVLRACTIVE, CHKVLGACTIVE, PUPVRRACTIVE, CHKVRGACTIVE, PUPVIRACTIVE, CHKVQCACTIVE, CHKVSTACTIVE, PUPOWRACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfRecord::Tag
 ******************************************************************************/

void PnlIdecScfRecord::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfRecord";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Recording");
			writeStringAttr(wr, itemtag, "sref", "HdgFrame", "Single frame storage");
			writeStringAttr(wr, itemtag, "sref", "CptFlr", "VIS-L camera");
			writeStringAttr(wr, itemtag, "sref", "CptFlg", "grayscale");
			writeStringAttr(wr, itemtag, "sref", "CptFrr", "VIS-R camera");
			writeStringAttr(wr, itemtag, "sref", "CptFrg", "grayscale");
			writeStringAttr(wr, itemtag, "sref", "CptFir", "LWIR camera");
			writeStringAttr(wr, itemtag, "sref", "CptFqc", "QCD detector");
			writeStringAttr(wr, itemtag, "sref", "CptFst", "3D map");
			writeStringAttr(wr, itemtag, "sref", "HdgVideo", "Video storage");
			writeStringAttr(wr, itemtag, "sref", "CptVfr", "maximum frame rate [fps]");
			writeStringAttr(wr, itemtag, "sref", "CptVlr", "VIS-L camera");
			writeStringAttr(wr, itemtag, "sref", "CptVlg", "grayscale");
			writeStringAttr(wr, itemtag, "sref", "CptVrr", "VIS-R camera");
			writeStringAttr(wr, itemtag, "sref", "CptVrg", "grayscale");
			writeStringAttr(wr, itemtag, "sref", "CptVir", "LWIR camera");
			writeStringAttr(wr, itemtag, "sref", "CptVqc", "QCD detector");
			writeStringAttr(wr, itemtag, "sref", "CptVst", "3D map");
			writeStringAttr(wr, itemtag, "sref", "CptOwr", "overwrite policy");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Aufnahme");
			writeStringAttr(wr, itemtag, "sref", "HdgFrame", "Einzelbildspeicher");
			writeStringAttr(wr, itemtag, "sref", "CptFlr", "VIS-L-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptFlg", "Graustufen");
			writeStringAttr(wr, itemtag, "sref", "CptFrr", "VIS-R-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptFrg", "Graustufen");
			writeStringAttr(wr, itemtag, "sref", "CptFir", "LWIR-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptFqc", "QCD-Detektor");
			writeStringAttr(wr, itemtag, "sref", "CptFst", "3D-Karte");
			writeStringAttr(wr, itemtag, "sref", "HdgVideo", "Videospeicher");
			writeStringAttr(wr, itemtag, "sref", "CptVfr", "maximale Bildwiederholrate [fps]");
			writeStringAttr(wr, itemtag, "sref", "CptVlr", "VIS-L-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptVlg", "Graustufen");
			writeStringAttr(wr, itemtag, "sref", "CptVrr", "VIS-R-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptVrg", "Graustufen");
			writeStringAttr(wr, itemtag, "sref", "CptVir", "LWIR-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptVqc", "QCD-Detektor");
			writeStringAttr(wr, itemtag, "sref", "CptVst", "3D-Karte");
			writeStringAttr(wr, itemtag, "sref", "CptOwr", "\\u00dcberschreibverhalten");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfRecord::DpchAppData
 ******************************************************************************/

PnlIdecScfRecord::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFRECORDDATA) {
};

string PnlIdecScfRecord::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfRecord::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfRecordData");
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
 class PnlIdecScfRecord::DpchAppDo
 ******************************************************************************/

PnlIdecScfRecord::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFRECORDDO) {
	ixVDo = 0;
};

string PnlIdecScfRecord::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfRecord::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfRecordDo");
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
 class PnlIdecScfRecord::DpchEngData
 ******************************************************************************/

PnlIdecScfRecord::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFPupFir
			, Feed* feedFPupFlr
			, Feed* feedFPupFrr
			, Feed* feedFPupOwr
			, Feed* feedFPupVir
			, Feed* feedFPupVlr
			, Feed* feedFPupVrr
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFRECORDDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFPUPFIR, FEEDFPUPFLR, FEEDFPUPFRR, FEEDFPUPOWR, FEEDFPUPVIR, FEEDFPUPVLR, FEEDFPUPVRR, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFPUPFIR) && feedFPupFir) this->feedFPupFir = *feedFPupFir;
	if (find(this->mask, FEEDFPUPFLR) && feedFPupFlr) this->feedFPupFlr = *feedFPupFlr;
	if (find(this->mask, FEEDFPUPFRR) && feedFPupFrr) this->feedFPupFrr = *feedFPupFrr;
	if (find(this->mask, FEEDFPUPOWR) && feedFPupOwr) this->feedFPupOwr = *feedFPupOwr;
	if (find(this->mask, FEEDFPUPVIR) && feedFPupVir) this->feedFPupVir = *feedFPupVir;
	if (find(this->mask, FEEDFPUPVLR) && feedFPupVlr) this->feedFPupVlr = *feedFPupVlr;
	if (find(this->mask, FEEDFPUPVRR) && feedFPupVrr) this->feedFPupVrr = *feedFPupVrr;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfRecord::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPFIR)) ss.push_back("feedFPupFir");
	if (has(FEEDFPUPFLR)) ss.push_back("feedFPupFlr");
	if (has(FEEDFPUPFRR)) ss.push_back("feedFPupFrr");
	if (has(FEEDFPUPOWR)) ss.push_back("feedFPupOwr");
	if (has(FEEDFPUPVIR)) ss.push_back("feedFPupVir");
	if (has(FEEDFPUPVLR)) ss.push_back("feedFPupVlr");
	if (has(FEEDFPUPVRR)) ss.push_back("feedFPupVrr");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfRecord::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFPUPFIR)) {feedFPupFir = src->feedFPupFir; add(FEEDFPUPFIR);};
	if (src->has(FEEDFPUPFLR)) {feedFPupFlr = src->feedFPupFlr; add(FEEDFPUPFLR);};
	if (src->has(FEEDFPUPFRR)) {feedFPupFrr = src->feedFPupFrr; add(FEEDFPUPFRR);};
	if (src->has(FEEDFPUPOWR)) {feedFPupOwr = src->feedFPupOwr; add(FEEDFPUPOWR);};
	if (src->has(FEEDFPUPVIR)) {feedFPupVir = src->feedFPupVir; add(FEEDFPUPVIR);};
	if (src->has(FEEDFPUPVLR)) {feedFPupVlr = src->feedFPupVlr; add(FEEDFPUPVLR);};
	if (src->has(FEEDFPUPVRR)) {feedFPupVrr = src->feedFPupVrr; add(FEEDFPUPVRR);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfRecord::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfRecordData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFPUPFIR)) feedFPupFir.writeXML(wr);
		if (has(FEEDFPUPFLR)) feedFPupFlr.writeXML(wr);
		if (has(FEEDFPUPFRR)) feedFPupFrr.writeXML(wr);
		if (has(FEEDFPUPOWR)) feedFPupOwr.writeXML(wr);
		if (has(FEEDFPUPVIR)) feedFPupVir.writeXML(wr);
		if (has(FEEDFPUPVLR)) feedFPupVlr.writeXML(wr);
		if (has(FEEDFPUPVRR)) feedFPupVrr.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

