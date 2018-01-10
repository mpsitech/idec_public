/**
  * \file PnlIdecScfQcd_blks.cpp
  * job handler for job PnlIdecScfQcd (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecScfQcd::VecVDo
 ******************************************************************************/

uint PnlIdecScfQcd::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfQcd::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfQcd::ContIac
 ******************************************************************************/

PnlIdecScfQcd::ContIac::ContIac(
			const string& TxfLam
			, const string& TxfDlm
			, const bool ChkAon
			, const double SldTof
			, const double SldTmp
			, const uint numFPupFan
			, const double SldFmd
			, const double SldVdd
			, const bool ChkVd2
			, const double SldVrf
			, const int UpdAsl
			, const double SldAmo
			, const bool ChkAad
		) : Block() {
	this->TxfLam = TxfLam;
	this->TxfDlm = TxfDlm;
	this->ChkAon = ChkAon;
	this->SldTof = SldTof;
	this->SldTmp = SldTmp;
	this->numFPupFan = numFPupFan;
	this->SldFmd = SldFmd;
	this->SldVdd = SldVdd;
	this->ChkVd2 = ChkVd2;
	this->SldVrf = SldVrf;
	this->UpdAsl = UpdAsl;
	this->SldAmo = SldAmo;
	this->ChkAad = ChkAad;

	mask = {TXFLAM, TXFDLM, CHKAON, SLDTOF, SLDTMP, NUMFPUPFAN, SLDFMD, SLDVDD, CHKVD2, SLDVRF, UPDASL, SLDAMO, CHKAAD};
};

bool PnlIdecScfQcd::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfQcd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfQcd";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfLam", TxfLam)) add(TXFLAM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfDlm", TxfDlm)) add(TXFDLM);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkAon", ChkAon)) add(CHKAON);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTof", SldTof)) add(SLDTOF);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTmp", SldTmp)) add(SLDTMP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFan", numFPupFan)) add(NUMFPUPFAN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldFmd", SldFmd)) add(SLDFMD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldVdd", SldVdd)) add(SLDVDD);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkVd2", ChkVd2)) add(CHKVD2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldVrf", SldVrf)) add(SLDVRF);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "UpdAsl", UpdAsl)) add(UPDASL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldAmo", SldAmo)) add(SLDAMO);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkAad", ChkAad)) add(CHKAAD);
	};

	return basefound;
};

void PnlIdecScfQcd::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfQcd";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfQcd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfLam", TxfLam);
		writeStringAttr(wr, itemtag, "sref", "TxfDlm", TxfDlm);
		writeBoolAttr(wr, itemtag, "sref", "ChkAon", ChkAon);
		writeDoubleAttr(wr, itemtag, "sref", "SldTof", SldTof);
		writeDoubleAttr(wr, itemtag, "sref", "SldTmp", SldTmp);
		writeUintAttr(wr, itemtag, "sref", "numFPupFan", numFPupFan);
		writeDoubleAttr(wr, itemtag, "sref", "SldFmd", SldFmd);
		writeDoubleAttr(wr, itemtag, "sref", "SldVdd", SldVdd);
		writeBoolAttr(wr, itemtag, "sref", "ChkVd2", ChkVd2);
		writeDoubleAttr(wr, itemtag, "sref", "SldVrf", SldVrf);
		writeIntAttr(wr, itemtag, "sref", "UpdAsl", UpdAsl);
		writeDoubleAttr(wr, itemtag, "sref", "SldAmo", SldAmo);
		writeBoolAttr(wr, itemtag, "sref", "ChkAad", ChkAad);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfQcd::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfLam == comp->TxfLam) insert(items, TXFLAM);
	if (TxfDlm == comp->TxfDlm) insert(items, TXFDLM);
	if (ChkAon == comp->ChkAon) insert(items, CHKAON);
	if (compareDouble(SldTof, comp->SldTof) < 1.0e-4) insert(items, SLDTOF);
	if (compareDouble(SldTmp, comp->SldTmp) < 1.0e-4) insert(items, SLDTMP);
	if (numFPupFan == comp->numFPupFan) insert(items, NUMFPUPFAN);
	if (compareDouble(SldFmd, comp->SldFmd) < 1.0e-4) insert(items, SLDFMD);
	if (compareDouble(SldVdd, comp->SldVdd) < 1.0e-4) insert(items, SLDVDD);
	if (ChkVd2 == comp->ChkVd2) insert(items, CHKVD2);
	if (compareDouble(SldVrf, comp->SldVrf) < 1.0e-4) insert(items, SLDVRF);
	if (UpdAsl == comp->UpdAsl) insert(items, UPDASL);
	if (compareDouble(SldAmo, comp->SldAmo) < 1.0e-4) insert(items, SLDAMO);
	if (ChkAad == comp->ChkAad) insert(items, CHKAAD);

	return(items);
};

set<uint> PnlIdecScfQcd::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFLAM, TXFDLM, CHKAON, SLDTOF, SLDTMP, NUMFPUPFAN, SLDFMD, SLDVDD, CHKVD2, SLDVRF, UPDASL, SLDAMO, CHKAAD};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfQcd::ContInf
 ******************************************************************************/

PnlIdecScfQcd::ContInf::ContInf(
			const bool ButMasterOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;

	mask = {BUTMASTERON};
};

void PnlIdecScfQcd::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfQcd";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfQcd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfQcd::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);

	return(items);
};

set<uint> PnlIdecScfQcd::ContInf::diff(
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
 class PnlIdecScfQcd::StatApp
 ******************************************************************************/

void PnlIdecScfQcd::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScfQcd";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScfQcd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfQcd::StatShr
 ******************************************************************************/

PnlIdecScfQcd::StatShr::StatShr(
			const bool TxfLamActive
			, const bool TxfDlmActive
			, const bool ChkAonActive
			, const bool SldTofActive
			, const double SldTofMin
			, const double SldTofMax
			, const double SldTofRast
			, const bool SldTmpActive
			, const double SldTmpMin
			, const double SldTmpMax
			, const double SldTmpRast
			, const bool PupFanActive
			, const bool SldFmdActive
			, const double SldFmdMin
			, const double SldFmdMax
			, const double SldFmdRast
			, const bool SldVddActive
			, const double SldVddMin
			, const double SldVddMax
			, const double SldVddRast
			, const bool ChkVd2Active
			, const bool SldVrfActive
			, const double SldVrfMin
			, const double SldVrfMax
			, const double SldVrfRast
			, const bool UpdAslActive
			, const int UpdAslMin
			, const int UpdAslMax
			, const bool SldAmoActive
			, const double SldAmoMin
			, const double SldAmoMax
			, const double SldAmoRast
			, const bool ChkAadActive
		) : Block() {
	this->TxfLamActive = TxfLamActive;
	this->TxfDlmActive = TxfDlmActive;
	this->ChkAonActive = ChkAonActive;
	this->SldTofActive = SldTofActive;
	this->SldTofMin = SldTofMin;
	this->SldTofMax = SldTofMax;
	this->SldTofRast = SldTofRast;
	this->SldTmpActive = SldTmpActive;
	this->SldTmpMin = SldTmpMin;
	this->SldTmpMax = SldTmpMax;
	this->SldTmpRast = SldTmpRast;
	this->PupFanActive = PupFanActive;
	this->SldFmdActive = SldFmdActive;
	this->SldFmdMin = SldFmdMin;
	this->SldFmdMax = SldFmdMax;
	this->SldFmdRast = SldFmdRast;
	this->SldVddActive = SldVddActive;
	this->SldVddMin = SldVddMin;
	this->SldVddMax = SldVddMax;
	this->SldVddRast = SldVddRast;
	this->ChkVd2Active = ChkVd2Active;
	this->SldVrfActive = SldVrfActive;
	this->SldVrfMin = SldVrfMin;
	this->SldVrfMax = SldVrfMax;
	this->SldVrfRast = SldVrfRast;
	this->UpdAslActive = UpdAslActive;
	this->UpdAslMin = UpdAslMin;
	this->UpdAslMax = UpdAslMax;
	this->SldAmoActive = SldAmoActive;
	this->SldAmoMin = SldAmoMin;
	this->SldAmoMax = SldAmoMax;
	this->SldAmoRast = SldAmoRast;
	this->ChkAadActive = ChkAadActive;

	mask = {TXFLAMACTIVE, TXFDLMACTIVE, CHKAONACTIVE, SLDTOFACTIVE, SLDTOFMIN, SLDTOFMAX, SLDTOFRAST, SLDTMPACTIVE, SLDTMPMIN, SLDTMPMAX, SLDTMPRAST, PUPFANACTIVE, SLDFMDACTIVE, SLDFMDMIN, SLDFMDMAX, SLDFMDRAST, SLDVDDACTIVE, SLDVDDMIN, SLDVDDMAX, SLDVDDRAST, CHKVD2ACTIVE, SLDVRFACTIVE, SLDVRFMIN, SLDVRFMAX, SLDVRFRAST, UPDASLACTIVE, UPDASLMIN, UPDASLMAX, SLDAMOACTIVE, SLDAMOMIN, SLDAMOMAX, SLDAMORAST, CHKAADACTIVE};
};

void PnlIdecScfQcd::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfQcd";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfQcd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "TxfLamActive", TxfLamActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfDlmActive", TxfDlmActive);
		writeBoolAttr(wr, itemtag, "sref", "ChkAonActive", ChkAonActive);
		writeBoolAttr(wr, itemtag, "sref", "SldTofActive", SldTofActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldTofMin", SldTofMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTofMax", SldTofMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldTofRast", SldTofRast);
		writeBoolAttr(wr, itemtag, "sref", "SldTmpActive", SldTmpActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldTmpMin", SldTmpMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTmpMax", SldTmpMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldTmpRast", SldTmpRast);
		writeBoolAttr(wr, itemtag, "sref", "PupFanActive", PupFanActive);
		writeBoolAttr(wr, itemtag, "sref", "SldFmdActive", SldFmdActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldFmdMin", SldFmdMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldFmdMax", SldFmdMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldFmdRast", SldFmdRast);
		writeBoolAttr(wr, itemtag, "sref", "SldVddActive", SldVddActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldVddMin", SldVddMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldVddMax", SldVddMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldVddRast", SldVddRast);
		writeBoolAttr(wr, itemtag, "sref", "ChkVd2Active", ChkVd2Active);
		writeBoolAttr(wr, itemtag, "sref", "SldVrfActive", SldVrfActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldVrfMin", SldVrfMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldVrfMax", SldVrfMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldVrfRast", SldVrfRast);
		writeBoolAttr(wr, itemtag, "sref", "UpdAslActive", UpdAslActive);
		writeIntAttr(wr, itemtag, "sref", "UpdAslMin", UpdAslMin);
		writeIntAttr(wr, itemtag, "sref", "UpdAslMax", UpdAslMax);
		writeBoolAttr(wr, itemtag, "sref", "SldAmoActive", SldAmoActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldAmoMin", SldAmoMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldAmoMax", SldAmoMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldAmoRast", SldAmoRast);
		writeBoolAttr(wr, itemtag, "sref", "ChkAadActive", ChkAadActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfQcd::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxfLamActive == comp->TxfLamActive) insert(items, TXFLAMACTIVE);
	if (TxfDlmActive == comp->TxfDlmActive) insert(items, TXFDLMACTIVE);
	if (ChkAonActive == comp->ChkAonActive) insert(items, CHKAONACTIVE);
	if (SldTofActive == comp->SldTofActive) insert(items, SLDTOFACTIVE);
	if (compareDouble(SldTofMin, comp->SldTofMin) < 1.0e-4) insert(items, SLDTOFMIN);
	if (compareDouble(SldTofMax, comp->SldTofMax) < 1.0e-4) insert(items, SLDTOFMAX);
	if (compareDouble(SldTofRast, comp->SldTofRast) < 1.0e-4) insert(items, SLDTOFRAST);
	if (SldTmpActive == comp->SldTmpActive) insert(items, SLDTMPACTIVE);
	if (compareDouble(SldTmpMin, comp->SldTmpMin) < 1.0e-4) insert(items, SLDTMPMIN);
	if (compareDouble(SldTmpMax, comp->SldTmpMax) < 1.0e-4) insert(items, SLDTMPMAX);
	if (compareDouble(SldTmpRast, comp->SldTmpRast) < 1.0e-4) insert(items, SLDTMPRAST);
	if (PupFanActive == comp->PupFanActive) insert(items, PUPFANACTIVE);
	if (SldFmdActive == comp->SldFmdActive) insert(items, SLDFMDACTIVE);
	if (compareDouble(SldFmdMin, comp->SldFmdMin) < 1.0e-4) insert(items, SLDFMDMIN);
	if (compareDouble(SldFmdMax, comp->SldFmdMax) < 1.0e-4) insert(items, SLDFMDMAX);
	if (compareDouble(SldFmdRast, comp->SldFmdRast) < 1.0e-4) insert(items, SLDFMDRAST);
	if (SldVddActive == comp->SldVddActive) insert(items, SLDVDDACTIVE);
	if (compareDouble(SldVddMin, comp->SldVddMin) < 1.0e-4) insert(items, SLDVDDMIN);
	if (compareDouble(SldVddMax, comp->SldVddMax) < 1.0e-4) insert(items, SLDVDDMAX);
	if (compareDouble(SldVddRast, comp->SldVddRast) < 1.0e-4) insert(items, SLDVDDRAST);
	if (ChkVd2Active == comp->ChkVd2Active) insert(items, CHKVD2ACTIVE);
	if (SldVrfActive == comp->SldVrfActive) insert(items, SLDVRFACTIVE);
	if (compareDouble(SldVrfMin, comp->SldVrfMin) < 1.0e-4) insert(items, SLDVRFMIN);
	if (compareDouble(SldVrfMax, comp->SldVrfMax) < 1.0e-4) insert(items, SLDVRFMAX);
	if (compareDouble(SldVrfRast, comp->SldVrfRast) < 1.0e-4) insert(items, SLDVRFRAST);
	if (UpdAslActive == comp->UpdAslActive) insert(items, UPDASLACTIVE);
	if (UpdAslMin == comp->UpdAslMin) insert(items, UPDASLMIN);
	if (UpdAslMax == comp->UpdAslMax) insert(items, UPDASLMAX);
	if (SldAmoActive == comp->SldAmoActive) insert(items, SLDAMOACTIVE);
	if (compareDouble(SldAmoMin, comp->SldAmoMin) < 1.0e-4) insert(items, SLDAMOMIN);
	if (compareDouble(SldAmoMax, comp->SldAmoMax) < 1.0e-4) insert(items, SLDAMOMAX);
	if (compareDouble(SldAmoRast, comp->SldAmoRast) < 1.0e-4) insert(items, SLDAMORAST);
	if (ChkAadActive == comp->ChkAadActive) insert(items, CHKAADACTIVE);

	return(items);
};

set<uint> PnlIdecScfQcd::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFLAMACTIVE, TXFDLMACTIVE, CHKAONACTIVE, SLDTOFACTIVE, SLDTOFMIN, SLDTOFMAX, SLDTOFRAST, SLDTMPACTIVE, SLDTMPMIN, SLDTMPMAX, SLDTMPRAST, PUPFANACTIVE, SLDFMDACTIVE, SLDFMDMIN, SLDFMDMAX, SLDFMDRAST, SLDVDDACTIVE, SLDVDDMIN, SLDVDDMAX, SLDVDDRAST, CHKVD2ACTIVE, SLDVRFACTIVE, SLDVRFMIN, SLDVRFMAX, SLDVRFRAST, UPDASLACTIVE, UPDASLMIN, UPDASLMAX, SLDAMOACTIVE, SLDAMOMIN, SLDAMOMAX, SLDAMORAST, CHKAADACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfQcd::Tag
 ******************************************************************************/

void PnlIdecScfQcd::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfQcd";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfQcd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "QCD detector");
			writeStringAttr(wr, itemtag, "sref", "CptLam", "center wavelength [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptDlm", "wavelength FWHM [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptAon", "always on");
			writeStringAttr(wr, itemtag, "sref", "CptTof", "turn-off delay [s]");
			writeStringAttr(wr, itemtag, "sref", "CptTmp", "temperature [\\u00b0C]");
			writeStringAttr(wr, itemtag, "sref", "CptFan", "fan policy");
			writeStringAttr(wr, itemtag, "sref", "CptFmd", "modulation frequency [kHz]");
			writeStringAttr(wr, itemtag, "sref", "CptVdd", "supply voltage Vdd [V]");
			writeStringAttr(wr, itemtag, "sref", "CptVd2", "Vref = Vdd/2");
			writeStringAttr(wr, itemtag, "sref", "CptVrf", "reference voltage Vref [V]");
			writeStringAttr(wr, itemtag, "sref", "CptAlign", "Alignment laser");
			writeStringAttr(wr, itemtag, "sref", "CptAsl", "sequence length");
			writeStringAttr(wr, itemtag, "sref", "CptAmo", "maximum output power [mW]");
			writeStringAttr(wr, itemtag, "sref", "CptAad", "adaptive power");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "QCD-Detektor");
			writeStringAttr(wr, itemtag, "sref", "CptLam", "zentrale Wellenl\\u00e4nge [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptDlm", "FWHM der Wellenl\\u00e4nge [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptAon", "immer eingeschaltet");
			writeStringAttr(wr, itemtag, "sref", "CptTof", "Abschalt-Verz\\u00f6gerung [s]");
			writeStringAttr(wr, itemtag, "sref", "CptTmp", "Temperatur [\\u00b0C]");
			writeStringAttr(wr, itemtag, "sref", "CptFan", "L\\u00fcfterverhalten");
			writeStringAttr(wr, itemtag, "sref", "CptFmd", "Modulationsfrequenz [kHz]");
			writeStringAttr(wr, itemtag, "sref", "CptVdd", "Versorgungsspannung Vdd [V]");
			writeStringAttr(wr, itemtag, "sref", "CptVd2", "Vref = Vdd/2");
			writeStringAttr(wr, itemtag, "sref", "CptVrf", "Referenzspannung Vref [V]");
			writeStringAttr(wr, itemtag, "sref", "CptAlign", "Ziellaser");
			writeStringAttr(wr, itemtag, "sref", "CptAsl", "Sequenzl\\u00e4nge");
			writeStringAttr(wr, itemtag, "sref", "CptAmo", "maximale Ausgangsleistung [mW]");
			writeStringAttr(wr, itemtag, "sref", "CptAad", "Leistungsanpassung");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfQcd::DpchAppData
 ******************************************************************************/

PnlIdecScfQcd::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFQCDDATA) {
};

string PnlIdecScfQcd::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfQcd::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfQcdData");
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
 class PnlIdecScfQcd::DpchAppDo
 ******************************************************************************/

PnlIdecScfQcd::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFQCDDO) {
	ixVDo = 0;
};

string PnlIdecScfQcd::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfQcd::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfQcdDo");
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
 class PnlIdecScfQcd::DpchEngData
 ******************************************************************************/

PnlIdecScfQcd::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFPupFan
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFQCDDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFPUPFAN, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFPUPFAN) && feedFPupFan) this->feedFPupFan = *feedFPupFan;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfQcd::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPFAN)) ss.push_back("feedFPupFan");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfQcd::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFPUPFAN)) {feedFPupFan = src->feedFPupFan; add(FEEDFPUPFAN);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfQcd::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfQcdData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFPUPFAN)) feedFPupFan.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

