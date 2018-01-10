/**
  * \file PnlIdecUtlSpiterm.cpp
  * API code for job PnlIdecUtlSpiterm (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecUtlSpiterm.h"

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
	if (TxfOcs.compare(comp->TxfOcs) == 0) insert(items, TXFOCS);
	if (TxfOhs.compare(comp->TxfOhs) == 0) insert(items, TXFOHS);
	if (TxfOfn.compare(comp->TxfOfn) == 0) insert(items, TXFOFN);
	if (numFRbuPet == comp->numFRbuPet) insert(items, NUMFRBUPET);
	if (numFPupPcm == comp->numFPupPcm) insert(items, NUMFPUPPCM);
	if (TxfPcs.compare(comp->TxfPcs) == 0) insert(items, TXFPCS);
	if (TxfPhs.compare(comp->TxfPhs) == 0) insert(items, TXFPHS);
	if (TxfPfn.compare(comp->TxfPfn) == 0) insert(items, TXFPFN);
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

bool PnlIdecUtlSpiterm::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecUtlSpiterm");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecUtlSpiterm";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSte", TxtSte)) add(TXTSTE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtOlg", TxtOlg)) add(TXTOLG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtOlf", TxtOlf)) add(TXTOLF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIlg", TxtIlg)) add(TXTILG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIlf", TxtIlf)) add(TXTILF);
	};

	return basefound;
};

set<uint> PnlIdecUtlSpiterm::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtSte.compare(comp->TxtSte) == 0) insert(items, TXTSTE);
	if (TxtOlg.compare(comp->TxtOlg) == 0) insert(items, TXTOLG);
	if (TxtOlf.compare(comp->TxtOlf) == 0) insert(items, TXTOLF);
	if (TxtIlg.compare(comp->TxtIlg) == 0) insert(items, TXTILG);
	if (TxtIlf.compare(comp->TxtIlf) == 0) insert(items, TXTILF);

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

bool PnlIdecUtlSpiterm::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecUtlSpiterm");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecUtlSpiterm";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupTrgActive", PupTrgActive)) add(PUPTRGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButCctActive", ButCctActive)) add(BUTCCTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButDctActive", ButDctActive)) add(BUTDCTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupOcmAvail", PupOcmAvail)) add(PUPOCMAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButOcaActive", ButOcaActive)) add(BUTOCAACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfOcsAvail", TxfOcsAvail)) add(TXFOCSAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfOhsAvail", TxfOhsAvail)) add(TXFOHSAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfOfnAvail", TxfOfnAvail)) add(TXFOFNAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButOsmActive", ButOsmActive)) add(BUTOSMACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "RbuPetActive", RbuPetActive)) add(RBUPETACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupPcmAvail", PupPcmAvail)) add(PUPPCMAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupPcmActive", PupPcmActive)) add(PUPPCMACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPcaActive", ButPcaActive)) add(BUTPCAACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPcsAvail", TxfPcsAvail)) add(TXFPCSAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPcsActive", TxfPcsActive)) add(TXFPCSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPhsAvail", TxfPhsAvail)) add(TXFPHSAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPhsActive", TxfPhsActive)) add(TXFPHSACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPfnAvail", TxfPfnAvail)) add(TXFPFNAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfPfnActive", TxfPfnActive)) add(TXFPFNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPinActive", SldPinActive)) add(SLDPINACTIVE);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPinMin", SldPinMin)) add(SLDPINMIN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPinMax", SldPinMax)) add(SLDPINMAX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "SldPinRast", SldPinRast)) add(SLDPINRAST);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPrnActive", ButPrnActive)) add(BUTPRNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButPstActive", ButPstActive)) add(BUTPSTACTIVE);
	};

	return basefound;
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

PnlIdecUtlSpiterm::Tag::Tag(
			const string& Cpt
			, const string& HdgCon
			, const string& CptTrg
			, const string& CptSte
			, const string& ButCct
			, const string& ButDct
			, const string& HdgDou
			, const string& CptOlf
			, const string& HdgDin
			, const string& CptIlf
			, const string& CptIsd
			, const string& HdgOcx
			, const string& CptOet
			, const string& CptOcm
			, const string& ButOca
			, const string& CptOcs
			, const string& CptOhs
			, const string& CptOfn
			, const string& ButOsm
			, const string& HdgPcx
			, const string& CptPet
			, const string& CptPcm
			, const string& ButPca
			, const string& CptPcs
			, const string& CptPhs
			, const string& CptPfn
			, const string& CptPin
			, const string& ButPrn
			, const string& ButPst
		) : Block() {
	this->Cpt = Cpt;
	this->HdgCon = HdgCon;
	this->CptTrg = CptTrg;
	this->CptSte = CptSte;
	this->ButCct = ButCct;
	this->ButDct = ButDct;
	this->HdgDou = HdgDou;
	this->CptOlf = CptOlf;
	this->HdgDin = HdgDin;
	this->CptIlf = CptIlf;
	this->CptIsd = CptIsd;
	this->HdgOcx = HdgOcx;
	this->CptOet = CptOet;
	this->CptOcm = CptOcm;
	this->ButOca = ButOca;
	this->CptOcs = CptOcs;
	this->CptOhs = CptOhs;
	this->CptOfn = CptOfn;
	this->ButOsm = ButOsm;
	this->HdgPcx = HdgPcx;
	this->CptPet = CptPet;
	this->CptPcm = CptPcm;
	this->ButPca = ButPca;
	this->CptPcs = CptPcs;
	this->CptPhs = CptPhs;
	this->CptPfn = CptPfn;
	this->CptPin = CptPin;
	this->ButPrn = ButPrn;
	this->ButPst = ButPst;

	mask = {CPT, HDGCON, CPTTRG, CPTSTE, BUTCCT, BUTDCT, HDGDOU, CPTOLF, HDGDIN, CPTILF, CPTISD, HDGOCX, CPTOET, CPTOCM, BUTOCA, CPTOCS, CPTOHS, CPTOFN, BUTOSM, HDGPCX, CPTPET, CPTPCM, BUTPCA, CPTPCS, CPTPHS, CPTPFN, CPTPIN, BUTPRN, BUTPST};
};

bool PnlIdecUtlSpiterm::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecUtlSpiterm");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecUtlSpiterm";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgCon", HdgCon)) add(HDGCON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTrg", CptTrg)) add(CPTTRG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSte", CptSte)) add(CPTSTE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButCct", ButCct)) add(BUTCCT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButDct", ButDct)) add(BUTDCT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgDou", HdgDou)) add(HDGDOU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOlf", CptOlf)) add(CPTOLF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgDin", HdgDin)) add(HDGDIN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIlf", CptIlf)) add(CPTILF);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIsd", CptIsd)) add(CPTISD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgOcx", HdgOcx)) add(HDGOCX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOet", CptOet)) add(CPTOET);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOcm", CptOcm)) add(CPTOCM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButOca", ButOca)) add(BUTOCA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOcs", CptOcs)) add(CPTOCS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOhs", CptOhs)) add(CPTOHS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptOfn", CptOfn)) add(CPTOFN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButOsm", ButOsm)) add(BUTOSM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgPcx", HdgPcx)) add(HDGPCX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPet", CptPet)) add(CPTPET);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPcm", CptPcm)) add(CPTPCM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButPca", ButPca)) add(BUTPCA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPcs", CptPcs)) add(CPTPCS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPhs", CptPhs)) add(CPTPHS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPfn", CptPfn)) add(CPTPFN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPin", CptPin)) add(CPTPIN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButPrn", ButPrn)) add(BUTPRN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "ButPst", ButPst)) add(BUTPST);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecUtlSpiterm::DpchAppData
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUTLSPITERMDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecUtlSpiterm::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecUtlSpitermData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::DpchAppDo
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECUTLSPITERMDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecUtlSpiterm::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecUtlSpitermDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecUtlSpiterm::DpchEngData
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUTLSPITERMDATA) {
	feedFPupOcm.tag = "FeedFPupOcm";
	feedFPupPcm.tag = "FeedFPupPcm";
	feedFPupTrg.tag = "FeedFPupTrg";
	feedFRbuOet.tag = "FeedFRbuOet";
	feedFRbuPet.tag = "FeedFRbuPet";
};

string PnlIdecUtlSpiterm::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
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

void PnlIdecUtlSpiterm::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecUtlSpitermData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupOcm.readXML(docctx, basexpath, true)) add(FEEDFPUPOCM);
		if (feedFPupPcm.readXML(docctx, basexpath, true)) add(FEEDFPUPPCM);
		if (feedFPupTrg.readXML(docctx, basexpath, true)) add(FEEDFPUPTRG);
		if (feedFRbuOet.readXML(docctx, basexpath, true)) add(FEEDFRBUOET);
		if (feedFRbuPet.readXML(docctx, basexpath, true)) add(FEEDFRBUPET);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupOcm.clear();
		feedFPupPcm.clear();
		feedFPupTrg.clear();
		feedFRbuOet.clear();
		feedFRbuPet.clear();
		statshr = StatShr();
		tag = Tag();
	};
};

/******************************************************************************
 class PnlIdecUtlSpiterm::DpchEngLive
 ******************************************************************************/

PnlIdecUtlSpiterm::DpchEngLive::DpchEngLive() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECUTLSPITERMLIVE) {
};

string PnlIdecUtlSpiterm::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecUtlSpiterm::DpchEngLive::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecUtlSpitermLive");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
	} else {
		continf = ContInf();
	};
};

