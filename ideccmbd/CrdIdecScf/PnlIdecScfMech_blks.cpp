/**
  * \file PnlIdecScfMech_blks.cpp
  * job handler for job PnlIdecScfMech (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecScfMech::VecVDo
 ******************************************************************************/

uint PnlIdecScfMech::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butmasterclick") return BUTMASTERCLICK;
	else if (s == "buttheccwclick") return BUTTHECCWCLICK;
	else if (s == "buttheccwstmdn") return BUTTHECCWSTMDN;
	else if (s == "buttheccwstmup") return BUTTHECCWSTMUP;
	else if (s == "butthecwstmdn") return BUTTHECWSTMDN;
	else if (s == "butthecwstmup") return BUTTHECWSTMUP;
	else if (s == "butthecwclick") return BUTTHECWCLICK;
	else if (s == "butphiccwclick") return BUTPHICCWCLICK;
	else if (s == "butphiccwstmdn") return BUTPHICCWSTMDN;
	else if (s == "butphiccwstmup") return BUTPHICCWSTMUP;
	else if (s == "butphicwstmdn") return BUTPHICWSTMDN;
	else if (s == "butphicwstmup") return BUTPHICWSTMUP;
	else if (s == "butphicwclick") return BUTPHICWCLICK;

	return(0);
};

string PnlIdecScfMech::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTMASTERCLICK) return("ButMasterClick");
	else if (ix == BUTTHECCWCLICK) return("ButTheCcwClick");
	else if (ix == BUTTHECCWSTMDN) return("ButTheCcwstMdn");
	else if (ix == BUTTHECCWSTMUP) return("ButTheCcwstMup");
	else if (ix == BUTTHECWSTMDN) return("ButTheCwstMdn");
	else if (ix == BUTTHECWSTMUP) return("ButTheCwstMup");
	else if (ix == BUTTHECWCLICK) return("ButTheCwClick");
	else if (ix == BUTPHICCWCLICK) return("ButPhiCcwClick");
	else if (ix == BUTPHICCWSTMDN) return("ButPhiCcwstMdn");
	else if (ix == BUTPHICCWSTMUP) return("ButPhiCcwstMup");
	else if (ix == BUTPHICWSTMDN) return("ButPhiCwstMdn");
	else if (ix == BUTPHICWSTMUP) return("ButPhiCwstMup");
	else if (ix == BUTPHICWCLICK) return("ButPhiCwClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfMech::VecVSge
 ******************************************************************************/

uint PnlIdecScfMech::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;

	return(0);
};

string PnlIdecScfMech::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");

	return("");
};

void PnlIdecScfMech::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=1;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class PnlIdecScfMech::ContIac
 ******************************************************************************/

PnlIdecScfMech::ContIac::ContIac(
			const string& TxfTgr
			, const double SldTll
			, const double SldTul
			, const string& TxfPgr
			, const double SldPll
			, const double SldPul
			, const double CusTheAns
			, const double CusPhiAns
		) : Block() {
	this->TxfTgr = TxfTgr;
	this->SldTll = SldTll;
	this->SldTul = SldTul;
	this->TxfPgr = TxfPgr;
	this->SldPll = SldPll;
	this->SldPul = SldPul;
	this->CusTheAns = CusTheAns;
	this->CusPhiAns = CusPhiAns;

	mask = {TXFTGR, SLDTLL, SLDTUL, TXFPGR, SLDPLL, SLDPUL, CUSTHEANS, CUSPHIANS};
};

bool PnlIdecScfMech::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfMech");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfMech";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfTgr", TxfTgr)) add(TXFTGR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTll", SldTll)) add(SLDTLL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldTul", SldTul)) add(SLDTUL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPgr", TxfPgr)) add(TXFPGR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldPll", SldPll)) add(SLDPLL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldPul", SldPul)) add(SLDPUL);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusTheAns", CusTheAns)) add(CUSTHEANS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "CusPhiAns", CusPhiAns)) add(CUSPHIANS);
	};

	return basefound;
};

void PnlIdecScfMech::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfMech";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfTgr", TxfTgr);
		writeDoubleAttr(wr, itemtag, "sref", "SldTll", SldTll);
		writeDoubleAttr(wr, itemtag, "sref", "SldTul", SldTul);
		writeStringAttr(wr, itemtag, "sref", "TxfPgr", TxfPgr);
		writeDoubleAttr(wr, itemtag, "sref", "SldPll", SldPll);
		writeDoubleAttr(wr, itemtag, "sref", "SldPul", SldPul);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAns", CusTheAns);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAns", CusPhiAns);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfMech::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfTgr == comp->TxfTgr) insert(items, TXFTGR);
	if (compareDouble(SldTll, comp->SldTll) < 1.0e-4) insert(items, SLDTLL);
	if (compareDouble(SldTul, comp->SldTul) < 1.0e-4) insert(items, SLDTUL);
	if (TxfPgr == comp->TxfPgr) insert(items, TXFPGR);
	if (compareDouble(SldPll, comp->SldPll) < 1.0e-4) insert(items, SLDPLL);
	if (compareDouble(SldPul, comp->SldPul) < 1.0e-4) insert(items, SLDPUL);
	if (compareDouble(CusTheAns, comp->CusTheAns) < 1.0e-4) insert(items, CUSTHEANS);
	if (compareDouble(CusPhiAns, comp->CusPhiAns) < 1.0e-4) insert(items, CUSPHIANS);

	return(items);
};

set<uint> PnlIdecScfMech::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFTGR, SLDTLL, SLDTUL, TXFPGR, SLDPLL, SLDPUL, CUSTHEANS, CUSPHIANS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfMech::ContInf
 ******************************************************************************/

PnlIdecScfMech::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtOrsAlpha
			, const string& TxtOrsBeta
			, const string& TxtTheAng
			, const string& TxtTheRpm
			, const uint numFCsiTheSte
			, const bool ButTheCcwOn
			, const bool ButTheCwOn
			, const string& TxtPhiAng
			, const string& TxtPhiRpm
			, const uint numFCsiPhiSte
			, const bool ButPhiCcwOn
			, const bool ButPhiCwOn
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtOrsAlpha = TxtOrsAlpha;
	this->TxtOrsBeta = TxtOrsBeta;
	this->TxtTheAng = TxtTheAng;
	this->TxtTheRpm = TxtTheRpm;
	this->numFCsiTheSte = numFCsiTheSte;
	this->ButTheCcwOn = ButTheCcwOn;
	this->ButTheCwOn = ButTheCwOn;
	this->TxtPhiAng = TxtPhiAng;
	this->TxtPhiRpm = TxtPhiRpm;
	this->numFCsiPhiSte = numFCsiPhiSte;
	this->ButPhiCcwOn = ButPhiCcwOn;
	this->ButPhiCwOn = ButPhiCwOn;

	mask = {BUTMASTERON, TXTORSALPHA, TXTORSBETA, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
};

void PnlIdecScfMech::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfMech";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtOrsAlpha", TxtOrsAlpha);
		writeStringAttr(wr, itemtag, "sref", "TxtOrsBeta", TxtOrsBeta);
		writeStringAttr(wr, itemtag, "sref", "TxtTheAng", TxtTheAng);
		writeStringAttr(wr, itemtag, "sref", "TxtTheRpm", TxtTheRpm);
		writeUintAttr(wr, itemtag, "sref", "numFCsiTheSte", numFCsiTheSte);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCcwOn", ButTheCcwOn);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCwOn", ButTheCwOn);
		writeStringAttr(wr, itemtag, "sref", "TxtPhiAng", TxtPhiAng);
		writeStringAttr(wr, itemtag, "sref", "TxtPhiRpm", TxtPhiRpm);
		writeUintAttr(wr, itemtag, "sref", "numFCsiPhiSte", numFCsiPhiSte);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCcwOn", ButPhiCcwOn);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCwOn", ButPhiCwOn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfMech::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtOrsAlpha == comp->TxtOrsAlpha) insert(items, TXTORSALPHA);
	if (TxtOrsBeta == comp->TxtOrsBeta) insert(items, TXTORSBETA);
	if (TxtTheAng == comp->TxtTheAng) insert(items, TXTTHEANG);
	if (TxtTheRpm == comp->TxtTheRpm) insert(items, TXTTHERPM);
	if (numFCsiTheSte == comp->numFCsiTheSte) insert(items, NUMFCSITHESTE);
	if (ButTheCcwOn == comp->ButTheCcwOn) insert(items, BUTTHECCWON);
	if (ButTheCwOn == comp->ButTheCwOn) insert(items, BUTTHECWON);
	if (TxtPhiAng == comp->TxtPhiAng) insert(items, TXTPHIANG);
	if (TxtPhiRpm == comp->TxtPhiRpm) insert(items, TXTPHIRPM);
	if (numFCsiPhiSte == comp->numFCsiPhiSte) insert(items, NUMFCSIPHISTE);
	if (ButPhiCcwOn == comp->ButPhiCcwOn) insert(items, BUTPHICCWON);
	if (ButPhiCwOn == comp->ButPhiCwOn) insert(items, BUTPHICWON);

	return(items);
};

set<uint> PnlIdecScfMech::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTORSALPHA, TXTORSBETA, TXTTHEANG, TXTTHERPM, NUMFCSITHESTE, BUTTHECCWON, BUTTHECWON, TXTPHIANG, TXTPHIRPM, NUMFCSIPHISTE, BUTPHICCWON, BUTPHICWON};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfMech::StatShr
 ******************************************************************************/

PnlIdecScfMech::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool CusTheAnsActive
			, const bool ButTheCcwActive
			, const bool ButTheCcwstActive
			, const bool ButTheCwstActive
			, const bool ButTheCwActive
			, const bool TxfTgrActive
			, const bool SldTllActive
			, const double SldTllMin
			, const double SldTllMax
			, const bool SldTulActive
			, const double SldTulMin
			, const double SldTulMax
			, const bool CusPhiAnsActive
			, const bool ButPhiCcwActive
			, const bool ButPhiCcwstActive
			, const bool ButPhiCwstActive
			, const bool ButPhiCwActive
			, const bool TxfPgrActive
			, const bool SldPllActive
			, const double SldPllMin
			, const double SldPllMax
			, const bool SldPulActive
			, const double SldPulMin
			, const double SldPulMax
			, const double CusTheAnsMin
			, const double CusTheAnsMax
			, const double CusPhiAnsMin
			, const double CusPhiAnsMax
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->CusTheAnsActive = CusTheAnsActive;
	this->ButTheCcwActive = ButTheCcwActive;
	this->ButTheCcwstActive = ButTheCcwstActive;
	this->ButTheCwstActive = ButTheCwstActive;
	this->ButTheCwActive = ButTheCwActive;
	this->TxfTgrActive = TxfTgrActive;
	this->SldTllActive = SldTllActive;
	this->SldTllMin = SldTllMin;
	this->SldTllMax = SldTllMax;
	this->SldTulActive = SldTulActive;
	this->SldTulMin = SldTulMin;
	this->SldTulMax = SldTulMax;
	this->CusPhiAnsActive = CusPhiAnsActive;
	this->ButPhiCcwActive = ButPhiCcwActive;
	this->ButPhiCcwstActive = ButPhiCcwstActive;
	this->ButPhiCwstActive = ButPhiCwstActive;
	this->ButPhiCwActive = ButPhiCwActive;
	this->TxfPgrActive = TxfPgrActive;
	this->SldPllActive = SldPllActive;
	this->SldPllMin = SldPllMin;
	this->SldPllMax = SldPllMax;
	this->SldPulActive = SldPulActive;
	this->SldPulMin = SldPulMin;
	this->SldPulMax = SldPulMax;
	this->CusTheAnsMin = CusTheAnsMin;
	this->CusTheAnsMax = CusTheAnsMax;
	this->CusPhiAnsMin = CusPhiAnsMin;
	this->CusPhiAnsMax = CusPhiAnsMax;

	mask = {IXIDECVEXPSTATE, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, TXFTGRACTIVE, SLDTLLACTIVE, SLDTLLMIN, SLDTLLMAX, SLDTULACTIVE, SLDTULMIN, SLDTULMAX, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, TXFPGRACTIVE, SLDPLLACTIVE, SLDPLLMIN, SLDPLLMAX, SLDPULACTIVE, SLDPULMIN, SLDPULMAX, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
};

void PnlIdecScfMech::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfMech";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "CusTheAnsActive", CusTheAnsActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCcwActive", ButTheCcwActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCcwstActive", ButTheCcwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCwstActive", ButTheCwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButTheCwActive", ButTheCwActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfTgrActive", TxfTgrActive);
		writeBoolAttr(wr, itemtag, "sref", "SldTllActive", SldTllActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldTllMin", SldTllMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTllMax", SldTllMax);
		writeBoolAttr(wr, itemtag, "sref", "SldTulActive", SldTulActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldTulMin", SldTulMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldTulMax", SldTulMax);
		writeBoolAttr(wr, itemtag, "sref", "CusPhiAnsActive", CusPhiAnsActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCcwActive", ButPhiCcwActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCcwstActive", ButPhiCcwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCwstActive", ButPhiCwstActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPhiCwActive", ButPhiCwActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfPgrActive", TxfPgrActive);
		writeBoolAttr(wr, itemtag, "sref", "SldPllActive", SldPllActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldPllMin", SldPllMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldPllMax", SldPllMax);
		writeBoolAttr(wr, itemtag, "sref", "SldPulActive", SldPulActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldPulMin", SldPulMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldPulMax", SldPulMax);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAnsMin", CusTheAnsMin);
		writeDoubleAttr(wr, itemtag, "sref", "CusTheAnsMax", CusTheAnsMax);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAnsMin", CusPhiAnsMin);
		writeDoubleAttr(wr, itemtag, "sref", "CusPhiAnsMax", CusPhiAnsMax);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfMech::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (CusTheAnsActive == comp->CusTheAnsActive) insert(items, CUSTHEANSACTIVE);
	if (ButTheCcwActive == comp->ButTheCcwActive) insert(items, BUTTHECCWACTIVE);
	if (ButTheCcwstActive == comp->ButTheCcwstActive) insert(items, BUTTHECCWSTACTIVE);
	if (ButTheCwstActive == comp->ButTheCwstActive) insert(items, BUTTHECWSTACTIVE);
	if (ButTheCwActive == comp->ButTheCwActive) insert(items, BUTTHECWACTIVE);
	if (TxfTgrActive == comp->TxfTgrActive) insert(items, TXFTGRACTIVE);
	if (SldTllActive == comp->SldTllActive) insert(items, SLDTLLACTIVE);
	if (compareDouble(SldTllMin, comp->SldTllMin) < 1.0e-4) insert(items, SLDTLLMIN);
	if (compareDouble(SldTllMax, comp->SldTllMax) < 1.0e-4) insert(items, SLDTLLMAX);
	if (SldTulActive == comp->SldTulActive) insert(items, SLDTULACTIVE);
	if (compareDouble(SldTulMin, comp->SldTulMin) < 1.0e-4) insert(items, SLDTULMIN);
	if (compareDouble(SldTulMax, comp->SldTulMax) < 1.0e-4) insert(items, SLDTULMAX);
	if (CusPhiAnsActive == comp->CusPhiAnsActive) insert(items, CUSPHIANSACTIVE);
	if (ButPhiCcwActive == comp->ButPhiCcwActive) insert(items, BUTPHICCWACTIVE);
	if (ButPhiCcwstActive == comp->ButPhiCcwstActive) insert(items, BUTPHICCWSTACTIVE);
	if (ButPhiCwstActive == comp->ButPhiCwstActive) insert(items, BUTPHICWSTACTIVE);
	if (ButPhiCwActive == comp->ButPhiCwActive) insert(items, BUTPHICWACTIVE);
	if (TxfPgrActive == comp->TxfPgrActive) insert(items, TXFPGRACTIVE);
	if (SldPllActive == comp->SldPllActive) insert(items, SLDPLLACTIVE);
	if (compareDouble(SldPllMin, comp->SldPllMin) < 1.0e-4) insert(items, SLDPLLMIN);
	if (compareDouble(SldPllMax, comp->SldPllMax) < 1.0e-4) insert(items, SLDPLLMAX);
	if (SldPulActive == comp->SldPulActive) insert(items, SLDPULACTIVE);
	if (compareDouble(SldPulMin, comp->SldPulMin) < 1.0e-4) insert(items, SLDPULMIN);
	if (compareDouble(SldPulMax, comp->SldPulMax) < 1.0e-4) insert(items, SLDPULMAX);
	if (compareDouble(CusTheAnsMin, comp->CusTheAnsMin) < 1.0e-4) insert(items, CUSTHEANSMIN);
	if (compareDouble(CusTheAnsMax, comp->CusTheAnsMax) < 1.0e-4) insert(items, CUSTHEANSMAX);
	if (compareDouble(CusPhiAnsMin, comp->CusPhiAnsMin) < 1.0e-4) insert(items, CUSPHIANSMIN);
	if (compareDouble(CusPhiAnsMax, comp->CusPhiAnsMax) < 1.0e-4) insert(items, CUSPHIANSMAX);

	return(items);
};

set<uint> PnlIdecScfMech::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, CUSTHEANSACTIVE, BUTTHECCWACTIVE, BUTTHECCWSTACTIVE, BUTTHECWSTACTIVE, BUTTHECWACTIVE, TXFTGRACTIVE, SLDTLLACTIVE, SLDTLLMIN, SLDTLLMAX, SLDTULACTIVE, SLDTULMIN, SLDTULMAX, CUSPHIANSACTIVE, BUTPHICCWACTIVE, BUTPHICCWSTACTIVE, BUTPHICWSTACTIVE, BUTPHICWACTIVE, TXFPGRACTIVE, SLDPLLACTIVE, SLDPLLMIN, SLDPLLMAX, SLDPULACTIVE, SLDPULMIN, SLDPULMAX, CUSTHEANSMIN, CUSTHEANSMAX, CUSPHIANSMIN, CUSPHIANSMAX};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfMech::Tag
 ******************************************************************************/

void PnlIdecScfMech::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfMech";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfMech";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Mechatronics");
			writeStringAttr(wr, itemtag, "sref", "HdgOrsns", "Orientation sensor");
			writeStringAttr(wr, itemtag, "sref", "HdgTheax", "\\u0398 axis");
			writeStringAttr(wr, itemtag, "sref", "CptTgr", "gear reduction [:1]");
			writeStringAttr(wr, itemtag, "sref", "CptTll", "lower limit [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptTul", "upper limit [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "HdgPhiax", "\\u03a6 axis");
			writeStringAttr(wr, itemtag, "sref", "CptPgr", "gear reduction [:1]");
			writeStringAttr(wr, itemtag, "sref", "CptPll", "lower limit [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptPul", "upper limit [\\u00b0]");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Mechatronik");
			writeStringAttr(wr, itemtag, "sref", "HdgOrsns", "Lagesensor");
			writeStringAttr(wr, itemtag, "sref", "HdgTheax", "\\u0398-Achse");
			writeStringAttr(wr, itemtag, "sref", "CptTgr", "Untersetzung [:1]");
			writeStringAttr(wr, itemtag, "sref", "CptTll", "untere Begrenzung [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptTul", "obere Begrenzung [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "HdgPhiax", "\\u03a6-Achse");
			writeStringAttr(wr, itemtag, "sref", "CptPgr", "Untersetzung [:1]");
			writeStringAttr(wr, itemtag, "sref", "CptPll", "untere Begrenzung [\\u00b0]");
			writeStringAttr(wr, itemtag, "sref", "CptPul", "obere Begrenzung [\\u00b0]");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfMech::DpchAppData
 ******************************************************************************/

PnlIdecScfMech::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFMECHDATA) {
};

string PnlIdecScfMech::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfMechData");
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
 class PnlIdecScfMech::DpchAppDo
 ******************************************************************************/

PnlIdecScfMech::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFMECHDO) {
	ixVDo = 0;
};

string PnlIdecScfMech::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfMechDo");
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
 class PnlIdecScfMech::DpchEngData
 ******************************************************************************/

PnlIdecScfMech::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFCsiPhiSte
			, Feed* feedFCsiTheSte
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFMECHDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFCSIPHISTE, FEEDFCSITHESTE, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFCSIPHISTE) && feedFCsiPhiSte) this->feedFCsiPhiSte = *feedFCsiPhiSte;
	if (find(this->mask, FEEDFCSITHESTE) && feedFCsiTheSte) this->feedFCsiTheSte = *feedFCsiTheSte;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfMech::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIPHISTE)) ss.push_back("feedFCsiPhiSte");
	if (has(FEEDFCSITHESTE)) ss.push_back("feedFCsiTheSte");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFCSIPHISTE)) {feedFCsiPhiSte = src->feedFCsiPhiSte; add(FEEDFCSIPHISTE);};
	if (src->has(FEEDFCSITHESTE)) {feedFCsiTheSte = src->feedFCsiTheSte; add(FEEDFCSITHESTE);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfMech::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfMechData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFCSIPHISTE)) feedFCsiPhiSte.writeXML(wr);
		if (has(FEEDFCSITHESTE)) feedFCsiTheSte.writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfMech::DpchEngLive
 ******************************************************************************/

PnlIdecScfMech::DpchEngLive::DpchEngLive(
			const ubigint jref
			, ContInf* continf
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFMECHLIVE, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
};

string PnlIdecScfMech::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfMech::DpchEngLive::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngLive* src = (DpchEngLive*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
};

void PnlIdecScfMech::DpchEngLive::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfMechLive");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

