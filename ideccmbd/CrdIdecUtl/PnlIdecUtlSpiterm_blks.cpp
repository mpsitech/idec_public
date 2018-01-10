/**
  * \file PnlIdecUtlSpiterm_blks.cpp
  * job handler for job PnlIdecUtlSpiterm (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class PnlIdecUtlSpiterm::VecVDo
 ******************************************************************************/

uint PnlIdecUtlSpiterm::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butcctclick") return BUTCCTCLICK;
	else if (s == "butdctclick") return BUTDCTCLICK;
	else if (s == "butocaclick") return BUTOCACLICK;
	else if (s == "butosmclick") return BUTOSMCLICK;
	else if (s == "butpcaclick") return BUTPCACLICK;
	else if (s == "butprnclick") return BUTPRNCLICK;
	else if (s == "butpstclick") return BUTPSTCLICK;

	return(0);
};

string PnlIdecUtlSpiterm::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTCCTCLICK) return("ButCctClick");
	else if (ix == BUTDCTCLICK) return("ButDctClick");
	else if (ix == BUTOCACLICK) return("ButOcaClick");
	else if (ix == BUTOSMCLICK) return("ButOsmClick");
	else if (ix == BUTPCACLICK) return("ButPcaClick");
	else if (ix == BUTPRNCLICK) return("ButPrnClick");
	else if (ix == BUTPSTCLICK) return("ButPstClick");

	return("");
};

/******************************************************************************
 class PnlIdecUtlSpiterm::VecVOcxenttype
 ******************************************************************************/

uint PnlIdecUtlSpiterm::VecVOcxenttype::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "csq") return CSQ;
	else if (s == "hsq") return HSQ;
	else if (s == "file") return FILE;

	return(0);
};

string PnlIdecUtlSpiterm::VecVOcxenttype::getSref(
			const uint ix
		) {
	if (ix == CSQ) return("csq");
	else if (ix == HSQ) return("hsq");
	else if (ix == FILE) return("file");

	return("");
};

string PnlIdecUtlSpiterm::VecVOcxenttype::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == CSQ) return("command sequence");
		else if (ix == HSQ) return("hexcode sequences");
		else if (ix == FILE) return("file");
	} else if (ixIdecVLocale == 2) {
		if (ix == CSQ) return("Befehlsfolge");
		else if (ix == HSQ) return("Hexcode-Folgen");
		else if (ix == FILE) return("Datei");
	};

	return("");
};

void PnlIdecUtlSpiterm::VecVOcxenttype::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class PnlIdecUtlSpiterm::VecVPcxenttype
 ******************************************************************************/

uint PnlIdecUtlSpiterm::VecVPcxenttype::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "csq") return CSQ;
	else if (s == "hsq") return HSQ;
	else if (s == "file") return FILE;

	return(0);
};

string PnlIdecUtlSpiterm::VecVPcxenttype::getSref(
			const uint ix
		) {
	if (ix == CSQ) return("csq");
	else if (ix == HSQ) return("hsq");
	else if (ix == FILE) return("file");

	return("");
};

string PnlIdecUtlSpiterm::VecVPcxenttype::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == CSQ) return("command sequence");
		else if (ix == HSQ) return("hexcode sequences");
		else if (ix == FILE) return("file");
	} else if (ixIdecVLocale == 2) {
		if (ix == CSQ) return("Befehlsfolge");
		else if (ix == HSQ) return("Hexcode-Folgen");
		else if (ix == FILE) return("Datei");
	};

	return("");
};

void PnlIdecUtlSpiterm::VecVPcxenttype::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class PnlIdecUtlSpiterm::VecVSge
 ******************************************************************************/

uint PnlIdecUtlSpiterm::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "ctd") return CTD;
	else if (s == "prdexec") return PRDEXEC;
	else if (s == "err") return ERR;

	return(0);
};

string PnlIdecUtlSpiterm::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == CTD) return("ctd");
	else if (ix == PRDEXEC) return("prdexec");
	else if (ix == ERR) return("err");

	return("");
};

void PnlIdecUtlSpiterm::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

/******************************************************************************
 class PnlIdecUtlSpiterm::ContIac
 ******************************************************************************/

PnlIdecUtlSpiterm::ContIac::ContIac(
			const uint numFPupTrg
			, const bool ChkIsd
			, const uint numFRbuOet
			, const uint numFPupOcm
			, const string& TxfOcs
			, const string& TxfOhs
			, const string& TxfOfn
			, const uint numFRbuPet
			, const uint numFPupPcm
			, const string& TxfPcs
			, const string& TxfPhs
			, const string& TxfPfn
			, const double SldPin
		) : Block() {
	this->numFPupTrg = numFPupTrg;
	this->ChkIsd = ChkIsd;
	this->numFRbuOet = numFRbuOet;
	this->numFPupOcm = numFPupOcm;
	this->TxfOcs = TxfOcs;
	this->TxfOhs = TxfOhs;
	this->TxfOfn = TxfOfn;
	this->numFRbuPet = numFRbuPet;
	this->numFPupPcm = numFPupPcm;
	this->TxfPcs = TxfPcs;
	this->TxfPhs = TxfPhs;
	this->TxfPfn = TxfPfn;
	this->SldPin = SldPin;

	mask = {NUMFPUPTRG, CHKISD, NUMFRBUOET, NUMFPUPOCM, TXFOCS, TXFOHS, TXFOFN, NUMFRBUPET, NUMFPUPPCM, TXFPCS, TXFPHS, TXFPFN, SLDPIN};
};

bool PnlIdecUtlSpiterm::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecUtlSpiterm");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecUtlSpiterm";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupTrg", numFPupTrg)) add(NUMFPUPTRG);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ChkIsd", ChkIsd)) add(CHKISD);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFRbuOet", numFRbuOet)) add(NUMFRBUOET);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupOcm", numFPupOcm)) add(NUMFPUPOCM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfOcs", TxfOcs)) add(TXFOCS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfOhs", TxfOhs)) add(TXFOHS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfOfn", TxfOfn)) add(TXFOFN);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFRbuPet", numFRbuPet)) add(NUMFRBUPET);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupPcm", numFPupPcm)) add(NUMFPUPPCM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPcs", TxfPcs)) add(TXFPCS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPhs", TxfPhs)) add(TXFPHS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfPfn", TxfPfn)) add(TXFPFN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "SldPin", SldPin)) add(SLDPIN);
	};

	return basefound;
};

void PnlIdecUtlSpiterm::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecUtlSpiterm";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecUtlSpiterm";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupTrg", numFPupTrg);
		writeBoolAttr(wr, itemtag, "sref", "ChkIsd", ChkIsd);
		writeUintAttr(wr, itemtag, "sref", "numFRbuOet", numFRbuOet);
		writeUintAttr(wr, itemtag, "sref", "numFPupOcm", numFPupOcm);
		writeStringAttr(wr, itemtag, "sref", "TxfOcs", TxfOcs);
		writeStringAttr(wr, itemtag, "sref", "TxfOhs", TxfOhs);
		writeStringAttr(wr, itemtag, "sref", "TxfOfn", TxfOfn);
		writeUintAttr(wr, itemtag, "sref", "numFRbuPet", numFRbuPet);
		writeUintAttr(wr, itemtag, "sref", "numFPupPcm", numFPupPcm);
		writeStringAttr(wr, itemtag, "sref", "TxfPcs", TxfPcs);
		writeStringAttr(wr, itemtag, "sref", "TxfPhs", TxfPhs);
		writeStringAttr(wr, itemtag, "sref", "TxfPfn", TxfPfn);
		writeDoubleAttr(wr, itemtag, "sref", "SldPin", SldPin);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecUtlSpiterm::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupTrg == comp->numFPupTrg) insert(items, NUMFPUPTRG);
	if (ChkIsd == comp->ChkIsd) insert(items, CHKISD);
	if (numFRbuOet == comp->numFRbuOet) insert(items, NUMFRBUOET);
	if (numFPupOcm == comp->numFPupOcm) insert(items, NUMFPUPOCM);
	if (TxfOcs == comp->TxfOcs) insert(items, TXFOCS);
	if (TxfOhs == comp->TxfOhs) insert(items, TXFOHS);
	if (TxfOfn == comp->TxfOfn) insert(items, TXFOFN);
	if (numFRbuPet == comp->numFRbuPet) insert(items, NUMFRBUPET);
	if (numFPupPcm == comp->numFPupPcm) insert(items, NUMFPUPPCM);
	if (TxfPcs == comp->TxfPcs) insert(items, TXFPCS);
	if (TxfPhs == comp->TxfPhs) insert(items, TXFPHS);
	if (TxfPfn == comp->TxfPfn) insert(items, TXFPFN);
	if (compareDouble(SldPin, comp->SldPin) < 1.0e-4) insert(items, SLDPIN);

	return(items);
};

set<uint> PnlIdecUtlSpiterm::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPTRG, CHKISD, NUMFRBUOET, NUMFPUPOCM, TXFOCS, TXFOHS, TXFOFN, NUMFRBUPET, NUMFPUPPCM, TXFPCS, TXFPHS, TXFPFN, SLDPIN};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::ContInf
 ******************************************************************************/

PnlIdecUtlSpiterm::ContInf::ContInf(
			const string& TxtSte
			, const string& TxtOlg
			, const string& TxtOlf
			, const string& TxtIlg
			, const string& TxtIlf
		) : Block() {
	this->TxtSte = TxtSte;
	this->TxtOlg = TxtOlg;
	this->TxtOlf = TxtOlf;
	this->TxtIlg = TxtIlg;
	this->TxtIlf = TxtIlf;

	mask = {TXTSTE, TXTOLG, TXTOLF, TXTILG, TXTILF};
};

void PnlIdecUtlSpiterm::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecUtlSpiterm";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecUtlSpiterm";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxtSte", TxtSte);
		writeStringAttr(wr, itemtag, "sref", "TxtOlg", TxtOlg);
		writeStringAttr(wr, itemtag, "sref", "TxtOlf", TxtOlf);
		writeStringAttr(wr, itemtag, "sref", "TxtIlg", TxtIlg);
		writeStringAttr(wr, itemtag, "sref", "TxtIlf", TxtIlf);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecUtlSpiterm::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtSte == comp->TxtSte) insert(items, TXTSTE);
	if (TxtOlg == comp->TxtOlg) insert(items, TXTOLG);
	if (TxtOlf == comp->TxtOlf) insert(items, TXTOLF);
	if (TxtIlg == comp->TxtIlg) insert(items, TXTILG);
	if (TxtIlf == comp->TxtIlf) insert(items, TXTILF);

	return(items);
};

set<uint> PnlIdecUtlSpiterm::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTSTE, TXTOLG, TXTOLF, TXTILG, TXTILF};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::StatShr
 ******************************************************************************/

PnlIdecUtlSpiterm::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool PupTrgActive
			, const bool ButCctActive
			, const bool ButDctActive
			, const bool PupOcmAvail
			, const bool ButOcaActive
			, const bool TxfOcsAvail
			, const bool TxfOhsAvail
			, const bool TxfOfnAvail
			, const bool ButOsmActive
			, const bool RbuPetActive
			, const bool PupPcmAvail
			, const bool PupPcmActive
			, const bool ButPcaActive
			, const bool TxfPcsAvail
			, const bool TxfPcsActive
			, const bool TxfPhsAvail
			, const bool TxfPhsActive
			, const bool TxfPfnAvail
			, const bool TxfPfnActive
			, const bool SldPinActive
			, const double SldPinMin
			, const double SldPinMax
			, const double SldPinRast
			, const bool ButPrnActive
			, const bool ButPstActive
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->PupTrgActive = PupTrgActive;
	this->ButCctActive = ButCctActive;
	this->ButDctActive = ButDctActive;
	this->PupOcmAvail = PupOcmAvail;
	this->ButOcaActive = ButOcaActive;
	this->TxfOcsAvail = TxfOcsAvail;
	this->TxfOhsAvail = TxfOhsAvail;
	this->TxfOfnAvail = TxfOfnAvail;
	this->ButOsmActive = ButOsmActive;
	this->RbuPetActive = RbuPetActive;
	this->PupPcmAvail = PupPcmAvail;
	this->PupPcmActive = PupPcmActive;
	this->ButPcaActive = ButPcaActive;
	this->TxfPcsAvail = TxfPcsAvail;
	this->TxfPcsActive = TxfPcsActive;
	this->TxfPhsAvail = TxfPhsAvail;
	this->TxfPhsActive = TxfPhsActive;
	this->TxfPfnAvail = TxfPfnAvail;
	this->TxfPfnActive = TxfPfnActive;
	this->SldPinActive = SldPinActive;
	this->SldPinMin = SldPinMin;
	this->SldPinMax = SldPinMax;
	this->SldPinRast = SldPinRast;
	this->ButPrnActive = ButPrnActive;
	this->ButPstActive = ButPstActive;

	mask = {IXIDECVEXPSTATE, PUPTRGACTIVE, BUTCCTACTIVE, BUTDCTACTIVE, PUPOCMAVAIL, BUTOCAACTIVE, TXFOCSAVAIL, TXFOHSAVAIL, TXFOFNAVAIL, BUTOSMACTIVE, RBUPETACTIVE, PUPPCMAVAIL, PUPPCMACTIVE, BUTPCAACTIVE, TXFPCSAVAIL, TXFPCSACTIVE, TXFPHSAVAIL, TXFPHSACTIVE, TXFPFNAVAIL, TXFPFNACTIVE, SLDPINACTIVE, SLDPINMIN, SLDPINMAX, SLDPINRAST, BUTPRNACTIVE, BUTPSTACTIVE};
};

void PnlIdecUtlSpiterm::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecUtlSpiterm";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecUtlSpiterm";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "PupTrgActive", PupTrgActive);
		writeBoolAttr(wr, itemtag, "sref", "ButCctActive", ButCctActive);
		writeBoolAttr(wr, itemtag, "sref", "ButDctActive", ButDctActive);
		writeBoolAttr(wr, itemtag, "sref", "PupOcmAvail", PupOcmAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButOcaActive", ButOcaActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfOcsAvail", TxfOcsAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxfOhsAvail", TxfOhsAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxfOfnAvail", TxfOfnAvail);
		writeBoolAttr(wr, itemtag, "sref", "ButOsmActive", ButOsmActive);
		writeBoolAttr(wr, itemtag, "sref", "RbuPetActive", RbuPetActive);
		writeBoolAttr(wr, itemtag, "sref", "PupPcmAvail", PupPcmAvail);
		writeBoolAttr(wr, itemtag, "sref", "PupPcmActive", PupPcmActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPcaActive", ButPcaActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfPcsAvail", TxfPcsAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxfPcsActive", TxfPcsActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfPhsAvail", TxfPhsAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxfPhsActive", TxfPhsActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfPfnAvail", TxfPfnAvail);
		writeBoolAttr(wr, itemtag, "sref", "TxfPfnActive", TxfPfnActive);
		writeBoolAttr(wr, itemtag, "sref", "SldPinActive", SldPinActive);
		writeDoubleAttr(wr, itemtag, "sref", "SldPinMin", SldPinMin);
		writeDoubleAttr(wr, itemtag, "sref", "SldPinMax", SldPinMax);
		writeDoubleAttr(wr, itemtag, "sref", "SldPinRast", SldPinRast);
		writeBoolAttr(wr, itemtag, "sref", "ButPrnActive", ButPrnActive);
		writeBoolAttr(wr, itemtag, "sref", "ButPstActive", ButPstActive);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecUtlSpiterm::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (PupTrgActive == comp->PupTrgActive) insert(items, PUPTRGACTIVE);
	if (ButCctActive == comp->ButCctActive) insert(items, BUTCCTACTIVE);
	if (ButDctActive == comp->ButDctActive) insert(items, BUTDCTACTIVE);
	if (PupOcmAvail == comp->PupOcmAvail) insert(items, PUPOCMAVAIL);
	if (ButOcaActive == comp->ButOcaActive) insert(items, BUTOCAACTIVE);
	if (TxfOcsAvail == comp->TxfOcsAvail) insert(items, TXFOCSAVAIL);
	if (TxfOhsAvail == comp->TxfOhsAvail) insert(items, TXFOHSAVAIL);
	if (TxfOfnAvail == comp->TxfOfnAvail) insert(items, TXFOFNAVAIL);
	if (ButOsmActive == comp->ButOsmActive) insert(items, BUTOSMACTIVE);
	if (RbuPetActive == comp->RbuPetActive) insert(items, RBUPETACTIVE);
	if (PupPcmAvail == comp->PupPcmAvail) insert(items, PUPPCMAVAIL);
	if (PupPcmActive == comp->PupPcmActive) insert(items, PUPPCMACTIVE);
	if (ButPcaActive == comp->ButPcaActive) insert(items, BUTPCAACTIVE);
	if (TxfPcsAvail == comp->TxfPcsAvail) insert(items, TXFPCSAVAIL);
	if (TxfPcsActive == comp->TxfPcsActive) insert(items, TXFPCSACTIVE);
	if (TxfPhsAvail == comp->TxfPhsAvail) insert(items, TXFPHSAVAIL);
	if (TxfPhsActive == comp->TxfPhsActive) insert(items, TXFPHSACTIVE);
	if (TxfPfnAvail == comp->TxfPfnAvail) insert(items, TXFPFNAVAIL);
	if (TxfPfnActive == comp->TxfPfnActive) insert(items, TXFPFNACTIVE);
	if (SldPinActive == comp->SldPinActive) insert(items, SLDPINACTIVE);
	if (compareDouble(SldPinMin, comp->SldPinMin) < 1.0e-4) insert(items, SLDPINMIN);
	if (compareDouble(SldPinMax, comp->SldPinMax) < 1.0e-4) insert(items, SLDPINMAX);
	if (compareDouble(SldPinRast, comp->SldPinRast) < 1.0e-4) insert(items, SLDPINRAST);
	if (ButPrnActive == comp->ButPrnActive) insert(items, BUTPRNACTIVE);
	if (ButPstActive == comp->ButPstActive) insert(items, BUTPSTACTIVE);

	return(items);
};

set<uint> PnlIdecUtlSpiterm::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, PUPTRGACTIVE, BUTCCTACTIVE, BUTDCTACTIVE, PUPOCMAVAIL, BUTOCAACTIVE, TXFOCSAVAIL, TXFOHSAVAIL, TXFOFNAVAIL, BUTOSMACTIVE, RBUPETACTIVE, PUPPCMAVAIL, PUPPCMACTIVE, BUTPCAACTIVE, TXFPCSAVAIL, TXFPCSACTIVE, TXFPHSAVAIL, TXFPHSACTIVE, TXFPFNAVAIL, TXFPFNACTIVE, SLDPINACTIVE, SLDPINMIN, SLDPINMAX, SLDPINRAST, BUTPRNACTIVE, BUTPSTACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::Tag
 ******************************************************************************/

void PnlIdecUtlSpiterm::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecUtlSpiterm";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecUtlSpiterm";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "SPI terminal");
			writeStringAttr(wr, itemtag, "sref", "HdgCon", "Connection");
			writeStringAttr(wr, itemtag, "sref", "CptTrg", "Target device");
			writeStringAttr(wr, itemtag, "sref", "CptSte", "State");
			writeStringAttr(wr, itemtag, "sref", "ButCct", "Connect");
			writeStringAttr(wr, itemtag, "sref", "ButDct", "Disconnect");
			writeStringAttr(wr, itemtag, "sref", "HdgDou", "Data out");
			writeStringAttr(wr, itemtag, "sref", "CptOlf", "Log file");
			writeStringAttr(wr, itemtag, "sref", "HdgDin", "Data in");
			writeStringAttr(wr, itemtag, "sref", "CptIlf", "Log file");
			writeStringAttr(wr, itemtag, "sref", "CptIsd", "Store binary data");
			writeStringAttr(wr, itemtag, "sref", "HdgOcx", "One-time command execution");
			writeStringAttr(wr, itemtag, "sref", "CptOet", "Entry type");
			writeStringAttr(wr, itemtag, "sref", "CptOcm", "Command");
			writeStringAttr(wr, itemtag, "sref", "ButOca", "Append");
			writeStringAttr(wr, itemtag, "sref", "CptOcs", "Command sequence");
			writeStringAttr(wr, itemtag, "sref", "CptOhs", "Hexcode sequences");
			writeStringAttr(wr, itemtag, "sref", "CptOfn", "File name");
			writeStringAttr(wr, itemtag, "sref", "ButOsm", "Submit");
			writeStringAttr(wr, itemtag, "sref", "HdgPcx", "Periodic command execution");
			writeStringAttr(wr, itemtag, "sref", "CptPet", "Entry type");
			writeStringAttr(wr, itemtag, "sref", "CptPcm", "Command");
			writeStringAttr(wr, itemtag, "sref", "ButPca", "Append");
			writeStringAttr(wr, itemtag, "sref", "CptPcs", "Command sequence");
			writeStringAttr(wr, itemtag, "sref", "CptPhs", "Hexcode sequences");
			writeStringAttr(wr, itemtag, "sref", "CptPfn", "File name");
			writeStringAttr(wr, itemtag, "sref", "CptPin", "Interval [ms]");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "SPI Terminal");
			writeStringAttr(wr, itemtag, "sref", "HdgCon", "Verbindung");
			writeStringAttr(wr, itemtag, "sref", "CptTrg", "Endger\\u00e4t");
			writeStringAttr(wr, itemtag, "sref", "CptSte", "Status");
			writeStringAttr(wr, itemtag, "sref", "ButCct", "Verbinden");
			writeStringAttr(wr, itemtag, "sref", "ButDct", "Trennen");
			writeStringAttr(wr, itemtag, "sref", "HdgDou", "Ausgehende Daten");
			writeStringAttr(wr, itemtag, "sref", "CptOlf", "Protokoll");
			writeStringAttr(wr, itemtag, "sref", "HdgDin", "Eingehende Daten");
			writeStringAttr(wr, itemtag, "sref", "CptIlf", "Protokoll");
			writeStringAttr(wr, itemtag, "sref", "CptIsd", "Bin\\u00e4rdaten speichern");
			writeStringAttr(wr, itemtag, "sref", "HdgOcx", "Einmalige Befehlsausf\\u00fchrung");
			writeStringAttr(wr, itemtag, "sref", "CptOet", "Eingabetyp");
			writeStringAttr(wr, itemtag, "sref", "CptOcm", "Befehl");
			writeStringAttr(wr, itemtag, "sref", "ButOca", "Hinzuf\\u00fcgen");
			writeStringAttr(wr, itemtag, "sref", "CptOcs", "Befehlsfolge");
			writeStringAttr(wr, itemtag, "sref", "CptOhs", "Hexcodefolgen");
			writeStringAttr(wr, itemtag, "sref", "CptOfn", "Dateiname");
			writeStringAttr(wr, itemtag, "sref", "ButOsm", "Absenden");
			writeStringAttr(wr, itemtag, "sref", "HdgPcx", "Periodische Befehlsausf\\u00fchrung");
			writeStringAttr(wr, itemtag, "sref", "CptPet", "Eingabetyp");
			writeStringAttr(wr, itemtag, "sref", "CptPcm", "Befehl");
			writeStringAttr(wr, itemtag, "sref", "ButPca", "Hinzuf\\u00fcgen");
			writeStringAttr(wr, itemtag, "sref", "CptPcs", "Befehlsfolge");
			writeStringAttr(wr, itemtag, "sref", "CptPhs", "Hexcodefolgen");
			writeStringAttr(wr, itemtag, "sref", "CptPfn", "Dateiname");
			writeStringAttr(wr, itemtag, "sref", "CptPin", "Intervall [ms]");
		};
		writeStringAttr(wr, itemtag, "sref", "ButPrn", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::RUN, ixIdecVLocale)));
		writeStringAttr(wr, itemtag, "sref", "ButPst", StrMod::cap(VecIdecVTag::getTitle(VecIdecVTag::STOP, ixIdecVLocale)));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::DpchAppData
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUTLSPITERMDATA) {
};

string PnlIdecUtlSpiterm::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecUtlSpitermData");
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
 class PnlIdecUtlSpiterm::DpchAppDo
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUTLSPITERMDO) {
	ixVDo = 0;
};

string PnlIdecUtlSpiterm::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecUtlSpitermDo");
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
 class PnlIdecUtlSpiterm::DpchEngData
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFPupOcm
			, Feed* feedFPupPcm
			, Feed* feedFPupTrg
			, Feed* feedFRbuOet
			, Feed* feedFRbuPet
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUTLSPITERMDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFPUPOCM, FEEDFPUPPCM, FEEDFPUPTRG, FEEDFRBUOET, FEEDFRBUPET, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFPUPOCM) && feedFPupOcm) this->feedFPupOcm = *feedFPupOcm;
	if (find(this->mask, FEEDFPUPPCM) && feedFPupPcm) this->feedFPupPcm = *feedFPupPcm;
	if (find(this->mask, FEEDFPUPTRG) && feedFPupTrg) this->feedFPupTrg = *feedFPupTrg;
	if (find(this->mask, FEEDFRBUOET) && feedFRbuOet) this->feedFRbuOet = *feedFRbuOet;
	if (find(this->mask, FEEDFRBUPET) && feedFRbuPet) this->feedFRbuPet = *feedFRbuPet;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecUtlSpiterm::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPOCM)) ss.push_back("feedFPupOcm");
	if (has(FEEDFPUPPCM)) ss.push_back("feedFPupPcm");
	if (has(FEEDFPUPTRG)) ss.push_back("feedFPupTrg");
	if (has(FEEDFRBUOET)) ss.push_back("feedFRbuOet");
	if (has(FEEDFRBUPET)) ss.push_back("feedFRbuPet");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFPUPOCM)) {feedFPupOcm = src->feedFPupOcm; add(FEEDFPUPOCM);};
	if (src->has(FEEDFPUPPCM)) {feedFPupPcm = src->feedFPupPcm; add(FEEDFPUPPCM);};
	if (src->has(FEEDFPUPTRG)) {feedFPupTrg = src->feedFPupTrg; add(FEEDFPUPTRG);};
	if (src->has(FEEDFRBUOET)) {feedFRbuOet = src->feedFRbuOet; add(FEEDFRBUOET);};
	if (src->has(FEEDFRBUPET)) {feedFRbuPet = src->feedFRbuPet; add(FEEDFRBUPET);};
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecUtlSpiterm::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecUtlSpitermData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFPUPOCM)) feedFPupOcm.writeXML(wr);
		if (has(FEEDFPUPPCM)) feedFPupPcm.writeXML(wr);
		if (has(FEEDFPUPTRG)) feedFPupTrg.writeXML(wr);
		if (has(FEEDFRBUOET)) feedFRbuOet.writeXML(wr);
		if (has(FEEDFRBUPET)) feedFRbuPet.writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::DpchEngLive
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchEngLive::DpchEngLive(
			const ubigint jref
			, ContInf* continf
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUTLSPITERMLIVE, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
};

string PnlIdecUtlSpiterm::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchEngLive::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngLive* src = (DpchEngLive*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
};

void PnlIdecUtlSpiterm::DpchEngLive::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecUtlSpitermLive");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

