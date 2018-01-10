/**
  * \file PnlIdecScfConn.cpp
  * API code for job PnlIdecScfConn (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfConn.h"

/******************************************************************************
 class PnlIdecScfConn::VecVDo
 ******************************************************************************/

uint PnlIdecScfConn::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfConn::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfConn::ContIac
 ******************************************************************************/

PnlIdecScfConn::ContIac::ContIac(
			const uint numFPupTsp
			, const uint numFPupPsp
			, const uint numFPupVty
			, const uint numFPupLsn
			, const string& TxfLsn
			, const uint numFPupLpa
			, const string& TxfLpa
			, const uint numFPupLtr
			, const uint numFPupRsn
			, const string& TxfRsn
			, const uint numFPupRpa
			, const string& TxfRpa
			, const uint numFPupRtr
			, const uint numFPupQsp
			, const uint numFPupFld
			, const uint numFPupSpt
			, const uint numFPupSld
		) : Block() {
	this->numFPupTsp = numFPupTsp;
	this->numFPupPsp = numFPupPsp;
	this->numFPupVty = numFPupVty;
	this->numFPupLsn = numFPupLsn;
	this->TxfLsn = TxfLsn;
	this->numFPupLpa = numFPupLpa;
	this->TxfLpa = TxfLpa;
	this->numFPupLtr = numFPupLtr;
	this->numFPupRsn = numFPupRsn;
	this->TxfRsn = TxfRsn;
	this->numFPupRpa = numFPupRpa;
	this->TxfRpa = TxfRpa;
	this->numFPupRtr = numFPupRtr;
	this->numFPupQsp = numFPupQsp;
	this->numFPupFld = numFPupFld;
	this->numFPupSpt = numFPupSpt;
	this->numFPupSld = numFPupSld;

	mask = {NUMFPUPTSP, NUMFPUPPSP, NUMFPUPVTY, NUMFPUPLSN, TXFLSN, NUMFPUPLPA, TXFLPA, NUMFPUPLTR, NUMFPUPRSN, TXFRSN, NUMFPUPRPA, TXFRPA, NUMFPUPRTR, NUMFPUPQSP, NUMFPUPFLD, NUMFPUPSPT, NUMFPUPSLD};
};

bool PnlIdecScfConn::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfConn");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfConn";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupTsp", numFPupTsp)) add(NUMFPUPTSP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupPsp", numFPupPsp)) add(NUMFPUPPSP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupVty", numFPupVty)) add(NUMFPUPVTY);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupLsn", numFPupLsn)) add(NUMFPUPLSN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfLsn", TxfLsn)) add(TXFLSN);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupLpa", numFPupLpa)) add(NUMFPUPLPA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfLpa", TxfLpa)) add(TXFLPA);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupLtr", numFPupLtr)) add(NUMFPUPLTR);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupRsn", numFPupRsn)) add(NUMFPUPRSN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfRsn", TxfRsn)) add(TXFRSN);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupRpa", numFPupRpa)) add(NUMFPUPRPA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfRpa", TxfRpa)) add(TXFRPA);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupRtr", numFPupRtr)) add(NUMFPUPRTR);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupQsp", numFPupQsp)) add(NUMFPUPQSP);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupFld", numFPupFld)) add(NUMFPUPFLD);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupSpt", numFPupSpt)) add(NUMFPUPSPT);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupSld", numFPupSld)) add(NUMFPUPSLD);
	};

	return basefound;
};

void PnlIdecScfConn::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfConn";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfConn";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFPupTsp", numFPupTsp);
		writeUintAttr(wr, itemtag, "sref", "numFPupPsp", numFPupPsp);
		writeUintAttr(wr, itemtag, "sref", "numFPupVty", numFPupVty);
		writeUintAttr(wr, itemtag, "sref", "numFPupLsn", numFPupLsn);
		writeStringAttr(wr, itemtag, "sref", "TxfLsn", TxfLsn);
		writeUintAttr(wr, itemtag, "sref", "numFPupLpa", numFPupLpa);
		writeStringAttr(wr, itemtag, "sref", "TxfLpa", TxfLpa);
		writeUintAttr(wr, itemtag, "sref", "numFPupLtr", numFPupLtr);
		writeUintAttr(wr, itemtag, "sref", "numFPupRsn", numFPupRsn);
		writeStringAttr(wr, itemtag, "sref", "TxfRsn", TxfRsn);
		writeUintAttr(wr, itemtag, "sref", "numFPupRpa", numFPupRpa);
		writeStringAttr(wr, itemtag, "sref", "TxfRpa", TxfRpa);
		writeUintAttr(wr, itemtag, "sref", "numFPupRtr", numFPupRtr);
		writeUintAttr(wr, itemtag, "sref", "numFPupQsp", numFPupQsp);
		writeUintAttr(wr, itemtag, "sref", "numFPupFld", numFPupFld);
		writeUintAttr(wr, itemtag, "sref", "numFPupSpt", numFPupSpt);
		writeUintAttr(wr, itemtag, "sref", "numFPupSld", numFPupSld);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfConn::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFPupTsp == comp->numFPupTsp) insert(items, NUMFPUPTSP);
	if (numFPupPsp == comp->numFPupPsp) insert(items, NUMFPUPPSP);
	if (numFPupVty == comp->numFPupVty) insert(items, NUMFPUPVTY);
	if (numFPupLsn == comp->numFPupLsn) insert(items, NUMFPUPLSN);
	if (TxfLsn.compare(comp->TxfLsn) == 0) insert(items, TXFLSN);
	if (numFPupLpa == comp->numFPupLpa) insert(items, NUMFPUPLPA);
	if (TxfLpa.compare(comp->TxfLpa) == 0) insert(items, TXFLPA);
	if (numFPupLtr == comp->numFPupLtr) insert(items, NUMFPUPLTR);
	if (numFPupRsn == comp->numFPupRsn) insert(items, NUMFPUPRSN);
	if (TxfRsn.compare(comp->TxfRsn) == 0) insert(items, TXFRSN);
	if (numFPupRpa == comp->numFPupRpa) insert(items, NUMFPUPRPA);
	if (TxfRpa.compare(comp->TxfRpa) == 0) insert(items, TXFRPA);
	if (numFPupRtr == comp->numFPupRtr) insert(items, NUMFPUPRTR);
	if (numFPupQsp == comp->numFPupQsp) insert(items, NUMFPUPQSP);
	if (numFPupFld == comp->numFPupFld) insert(items, NUMFPUPFLD);
	if (numFPupSpt == comp->numFPupSpt) insert(items, NUMFPUPSPT);
	if (numFPupSld == comp->numFPupSld) insert(items, NUMFPUPSLD);

	return(items);
};

set<uint> PnlIdecScfConn::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFPUPTSP, NUMFPUPPSP, NUMFPUPVTY, NUMFPUPLSN, TXFLSN, NUMFPUPLPA, TXFLPA, NUMFPUPLTR, NUMFPUPRSN, TXFRSN, NUMFPUPRPA, TXFRPA, NUMFPUPRTR, NUMFPUPQSP, NUMFPUPFLD, NUMFPUPSPT, NUMFPUPSLD};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfConn::ContInf
 ******************************************************************************/

PnlIdecScfConn::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtSchGp1
			, const string& TxtSchGp2
			, const string& TxtSchSp1
			, const uint numFCsiSchSp1
			, const string& TxtSchSp2
			, const uint numFCsiSchSp2
			, const string& TxtSchSp3
			, const uint numFCsiSchSp3
			, const string& TxtSchLd1
			, const string& TxtSchLd2
			, const string& TxtSchOct
			, const string& TxtSchOps
			, const uint numFCsiSchOst
			, const string& TxtSchHct
			, const string& TxtSchHps
			, const uint numFCsiSchHst
			, const string& TxtSchIps
			, const uint numFCsiSchIst
			, const string& TxtIsn
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtSchGp1 = TxtSchGp1;
	this->TxtSchGp2 = TxtSchGp2;
	this->TxtSchSp1 = TxtSchSp1;
	this->numFCsiSchSp1 = numFCsiSchSp1;
	this->TxtSchSp2 = TxtSchSp2;
	this->numFCsiSchSp2 = numFCsiSchSp2;
	this->TxtSchSp3 = TxtSchSp3;
	this->numFCsiSchSp3 = numFCsiSchSp3;
	this->TxtSchLd1 = TxtSchLd1;
	this->TxtSchLd2 = TxtSchLd2;
	this->TxtSchOct = TxtSchOct;
	this->TxtSchOps = TxtSchOps;
	this->numFCsiSchOst = numFCsiSchOst;
	this->TxtSchHct = TxtSchHct;
	this->TxtSchHps = TxtSchHps;
	this->numFCsiSchHst = numFCsiSchHst;
	this->TxtSchIps = TxtSchIps;
	this->numFCsiSchIst = numFCsiSchIst;
	this->TxtIsn = TxtIsn;

	mask = {BUTMASTERON, TXTSCHGP1, TXTSCHGP2, TXTSCHSP1, NUMFCSISCHSP1, TXTSCHSP2, NUMFCSISCHSP2, TXTSCHSP3, NUMFCSISCHSP3, TXTSCHLD1, TXTSCHLD2, TXTSCHOCT, TXTSCHOPS, NUMFCSISCHOST, TXTSCHHCT, TXTSCHHPS, NUMFCSISCHHST, TXTSCHIPS, NUMFCSISCHIST, TXTISN};
};

bool PnlIdecScfConn::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfConn");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfConn";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchGp1", TxtSchGp1)) add(TXTSCHGP1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchGp2", TxtSchGp2)) add(TXTSCHGP2);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchSp1", TxtSchSp1)) add(TXTSCHSP1);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiSchSp1", numFCsiSchSp1)) add(NUMFCSISCHSP1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchSp2", TxtSchSp2)) add(TXTSCHSP2);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiSchSp2", numFCsiSchSp2)) add(NUMFCSISCHSP2);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchSp3", TxtSchSp3)) add(TXTSCHSP3);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiSchSp3", numFCsiSchSp3)) add(NUMFCSISCHSP3);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchLd1", TxtSchLd1)) add(TXTSCHLD1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchLd2", TxtSchLd2)) add(TXTSCHLD2);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchOct", TxtSchOct)) add(TXTSCHOCT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchOps", TxtSchOps)) add(TXTSCHOPS);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiSchOst", numFCsiSchOst)) add(NUMFCSISCHOST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchHct", TxtSchHct)) add(TXTSCHHCT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchHps", TxtSchHps)) add(TXTSCHHPS);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiSchHst", numFCsiSchHst)) add(NUMFCSISCHHST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtSchIps", TxtSchIps)) add(TXTSCHIPS);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiSchIst", numFCsiSchIst)) add(NUMFCSISCHIST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIsn", TxtIsn)) add(TXTISN);
	};

	return basefound;
};

set<uint> PnlIdecScfConn::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtSchGp1.compare(comp->TxtSchGp1) == 0) insert(items, TXTSCHGP1);
	if (TxtSchGp2.compare(comp->TxtSchGp2) == 0) insert(items, TXTSCHGP2);
	if (TxtSchSp1.compare(comp->TxtSchSp1) == 0) insert(items, TXTSCHSP1);
	if (numFCsiSchSp1 == comp->numFCsiSchSp1) insert(items, NUMFCSISCHSP1);
	if (TxtSchSp2.compare(comp->TxtSchSp2) == 0) insert(items, TXTSCHSP2);
	if (numFCsiSchSp2 == comp->numFCsiSchSp2) insert(items, NUMFCSISCHSP2);
	if (TxtSchSp3.compare(comp->TxtSchSp3) == 0) insert(items, TXTSCHSP3);
	if (numFCsiSchSp3 == comp->numFCsiSchSp3) insert(items, NUMFCSISCHSP3);
	if (TxtSchLd1.compare(comp->TxtSchLd1) == 0) insert(items, TXTSCHLD1);
	if (TxtSchLd2.compare(comp->TxtSchLd2) == 0) insert(items, TXTSCHLD2);
	if (TxtSchOct.compare(comp->TxtSchOct) == 0) insert(items, TXTSCHOCT);
	if (TxtSchOps.compare(comp->TxtSchOps) == 0) insert(items, TXTSCHOPS);
	if (numFCsiSchOst == comp->numFCsiSchOst) insert(items, NUMFCSISCHOST);
	if (TxtSchHct.compare(comp->TxtSchHct) == 0) insert(items, TXTSCHHCT);
	if (TxtSchHps.compare(comp->TxtSchHps) == 0) insert(items, TXTSCHHPS);
	if (numFCsiSchHst == comp->numFCsiSchHst) insert(items, NUMFCSISCHHST);
	if (TxtSchIps.compare(comp->TxtSchIps) == 0) insert(items, TXTSCHIPS);
	if (numFCsiSchIst == comp->numFCsiSchIst) insert(items, NUMFCSISCHIST);
	if (TxtIsn.compare(comp->TxtIsn) == 0) insert(items, TXTISN);

	return(items);
};

set<uint> PnlIdecScfConn::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTSCHGP1, TXTSCHGP2, TXTSCHSP1, NUMFCSISCHSP1, TXTSCHSP2, NUMFCSISCHSP2, TXTSCHSP3, NUMFCSISCHSP3, TXTSCHLD1, TXTSCHLD2, TXTSCHOCT, TXTSCHOPS, NUMFCSISCHOST, TXTSCHHCT, TXTSCHHPS, NUMFCSISCHHST, TXTSCHIPS, NUMFCSISCHIST, TXTISN};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfConn::StatApp
 ******************************************************************************/

PnlIdecScfConn::StatApp::StatApp(
			const uint ixIdecVExpstate
			, const bool PupLsnAlt
			, const bool PupLpaAlt
			, const bool PupRsnAlt
			, const bool PupRpaAlt
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->PupLsnAlt = PupLsnAlt;
	this->PupLpaAlt = PupLpaAlt;
	this->PupRsnAlt = PupRsnAlt;
	this->PupRpaAlt = PupRpaAlt;

	mask = {IXIDECVEXPSTATE, PUPLSNALT, PUPLPAALT, PUPRSNALT, PUPRPAALT};
};

bool PnlIdecScfConn::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScfConn");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScfConn";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLsnAlt", PupLsnAlt)) add(PUPLSNALT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLpaAlt", PupLpaAlt)) add(PUPLPAALT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRsnAlt", PupRsnAlt)) add(PUPRSNALT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRpaAlt", PupRpaAlt)) add(PUPRPAALT);
	};

	return basefound;
};

set<uint> PnlIdecScfConn::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (PupLsnAlt == comp->PupLsnAlt) insert(items, PUPLSNALT);
	if (PupLpaAlt == comp->PupLpaAlt) insert(items, PUPLPAALT);
	if (PupRsnAlt == comp->PupRsnAlt) insert(items, PUPRSNALT);
	if (PupRpaAlt == comp->PupRpaAlt) insert(items, PUPRPAALT);

	return(items);
};

set<uint> PnlIdecScfConn::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, PUPLSNALT, PUPLPAALT, PUPRSNALT, PUPRPAALT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfConn::StatShr
 ******************************************************************************/

PnlIdecScfConn::StatShr::StatShr(
			const bool TxfLsnValid
			, const bool TxfLpaValid
			, const bool TxfRsnValid
			, const bool TxfRpaValid
			, const bool PupTspActive
			, const bool PupPspActive
			, const bool PupVtyActive
			, const bool PupLsnAvail
			, const bool PupLsnActive
			, const bool PupLpaAvail
			, const bool PupLpaActive
			, const bool PupLtrActive
			, const bool PupRsnAvail
			, const bool PupRsnActive
			, const bool PupRpaAvail
			, const bool PupRpaActive
			, const bool PupRtrActive
			, const bool TxtIsnActive
			, const bool PupQspActive
			, const bool PupFldActive
			, const bool PupSptActive
		) : Block() {
	this->TxfLsnValid = TxfLsnValid;
	this->TxfLpaValid = TxfLpaValid;
	this->TxfRsnValid = TxfRsnValid;
	this->TxfRpaValid = TxfRpaValid;
	this->PupTspActive = PupTspActive;
	this->PupPspActive = PupPspActive;
	this->PupVtyActive = PupVtyActive;
	this->PupLsnAvail = PupLsnAvail;
	this->PupLsnActive = PupLsnActive;
	this->PupLpaAvail = PupLpaAvail;
	this->PupLpaActive = PupLpaActive;
	this->PupLtrActive = PupLtrActive;
	this->PupRsnAvail = PupRsnAvail;
	this->PupRsnActive = PupRsnActive;
	this->PupRpaAvail = PupRpaAvail;
	this->PupRpaActive = PupRpaActive;
	this->PupRtrActive = PupRtrActive;
	this->TxtIsnActive = TxtIsnActive;
	this->PupQspActive = PupQspActive;
	this->PupFldActive = PupFldActive;
	this->PupSptActive = PupSptActive;

	mask = {TXFLSNVALID, TXFLPAVALID, TXFRSNVALID, TXFRPAVALID, PUPTSPACTIVE, PUPPSPACTIVE, PUPVTYACTIVE, PUPLSNAVAIL, PUPLSNACTIVE, PUPLPAAVAIL, PUPLPAACTIVE, PUPLTRACTIVE, PUPRSNAVAIL, PUPRSNACTIVE, PUPRPAAVAIL, PUPRPAACTIVE, PUPRTRACTIVE, TXTISNACTIVE, PUPQSPACTIVE, PUPFLDACTIVE, PUPSPTACTIVE};
};

bool PnlIdecScfConn::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfConn");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfConn";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfLsnValid", TxfLsnValid)) add(TXFLSNVALID);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfLpaValid", TxfLpaValid)) add(TXFLPAVALID);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfRsnValid", TxfRsnValid)) add(TXFRSNVALID);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfRpaValid", TxfRpaValid)) add(TXFRPAVALID);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupTspActive", PupTspActive)) add(PUPTSPACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupPspActive", PupPspActive)) add(PUPPSPACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupVtyActive", PupVtyActive)) add(PUPVTYACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLsnAvail", PupLsnAvail)) add(PUPLSNAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLsnActive", PupLsnActive)) add(PUPLSNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLpaAvail", PupLpaAvail)) add(PUPLPAAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLpaActive", PupLpaActive)) add(PUPLPAACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLtrActive", PupLtrActive)) add(PUPLTRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRsnAvail", PupRsnAvail)) add(PUPRSNAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRsnActive", PupRsnActive)) add(PUPRSNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRpaAvail", PupRpaAvail)) add(PUPRPAAVAIL);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRpaActive", PupRpaActive)) add(PUPRPAACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRtrActive", PupRtrActive)) add(PUPRTRACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxtIsnActive", TxtIsnActive)) add(TXTISNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupQspActive", PupQspActive)) add(PUPQSPACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupFldActive", PupFldActive)) add(PUPFLDACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupSptActive", PupSptActive)) add(PUPSPTACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecScfConn::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxfLsnValid == comp->TxfLsnValid) insert(items, TXFLSNVALID);
	if (TxfLpaValid == comp->TxfLpaValid) insert(items, TXFLPAVALID);
	if (TxfRsnValid == comp->TxfRsnValid) insert(items, TXFRSNVALID);
	if (TxfRpaValid == comp->TxfRpaValid) insert(items, TXFRPAVALID);
	if (PupTspActive == comp->PupTspActive) insert(items, PUPTSPACTIVE);
	if (PupPspActive == comp->PupPspActive) insert(items, PUPPSPACTIVE);
	if (PupVtyActive == comp->PupVtyActive) insert(items, PUPVTYACTIVE);
	if (PupLsnAvail == comp->PupLsnAvail) insert(items, PUPLSNAVAIL);
	if (PupLsnActive == comp->PupLsnActive) insert(items, PUPLSNACTIVE);
	if (PupLpaAvail == comp->PupLpaAvail) insert(items, PUPLPAAVAIL);
	if (PupLpaActive == comp->PupLpaActive) insert(items, PUPLPAACTIVE);
	if (PupLtrActive == comp->PupLtrActive) insert(items, PUPLTRACTIVE);
	if (PupRsnAvail == comp->PupRsnAvail) insert(items, PUPRSNAVAIL);
	if (PupRsnActive == comp->PupRsnActive) insert(items, PUPRSNACTIVE);
	if (PupRpaAvail == comp->PupRpaAvail) insert(items, PUPRPAAVAIL);
	if (PupRpaActive == comp->PupRpaActive) insert(items, PUPRPAACTIVE);
	if (PupRtrActive == comp->PupRtrActive) insert(items, PUPRTRACTIVE);
	if (TxtIsnActive == comp->TxtIsnActive) insert(items, TXTISNACTIVE);
	if (PupQspActive == comp->PupQspActive) insert(items, PUPQSPACTIVE);
	if (PupFldActive == comp->PupFldActive) insert(items, PUPFLDACTIVE);
	if (PupSptActive == comp->PupSptActive) insert(items, PUPSPTACTIVE);

	return(items);
};

set<uint> PnlIdecScfConn::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFLSNVALID, TXFLPAVALID, TXFRSNVALID, TXFRPAVALID, PUPTSPACTIVE, PUPPSPACTIVE, PUPVTYACTIVE, PUPLSNAVAIL, PUPLSNACTIVE, PUPLPAAVAIL, PUPLPAACTIVE, PUPLTRACTIVE, PUPRSNAVAIL, PUPRSNACTIVE, PUPRPAAVAIL, PUPRPAACTIVE, PUPRTRACTIVE, TXTISNACTIVE, PUPQSPACTIVE, PUPFLDACTIVE, PUPSPTACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfConn::Tag
 ******************************************************************************/

PnlIdecScfConn::Tag::Tag(
			const string& Cpt
			, const string& CptSchAll
			, const string& CptSchLwi
			, const string& CptTsp
			, const string& CptPsp
			, const string& CptVty
			, const string& CptLsn
			, const string& CptLpa
			, const string& CptLtr
			, const string& CptRsn
			, const string& CptRpa
			, const string& CptRtr
			, const string& CptIsn
			, const string& CptQsp
			, const string& CptFld
			, const string& CptSpt
			, const string& CptSld
		) : Block() {
	this->Cpt = Cpt;
	this->CptSchAll = CptSchAll;
	this->CptSchLwi = CptSchLwi;
	this->CptTsp = CptTsp;
	this->CptPsp = CptPsp;
	this->CptVty = CptVty;
	this->CptLsn = CptLsn;
	this->CptLpa = CptLpa;
	this->CptLtr = CptLtr;
	this->CptRsn = CptRsn;
	this->CptRpa = CptRpa;
	this->CptRtr = CptRtr;
	this->CptIsn = CptIsn;
	this->CptQsp = CptQsp;
	this->CptFld = CptFld;
	this->CptSpt = CptSpt;
	this->CptSld = CptSld;

	mask = {CPT, CPTSCHALL, CPTSCHLWI, CPTTSP, CPTPSP, CPTVTY, CPTLSN, CPTLPA, CPTLTR, CPTRSN, CPTRPA, CPTRTR, CPTISN, CPTQSP, CPTFLD, CPTSPT, CPTSLD};
};

bool PnlIdecScfConn::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfConn");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfConn";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSchAll", CptSchAll)) add(CPTSCHALL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSchLwi", CptSchLwi)) add(CPTSCHLWI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptTsp", CptTsp)) add(CPTTSP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptPsp", CptPsp)) add(CPTPSP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVty", CptVty)) add(CPTVTY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptLsn", CptLsn)) add(CPTLSN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptLpa", CptLpa)) add(CPTLPA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptLtr", CptLtr)) add(CPTLTR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRsn", CptRsn)) add(CPTRSN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRpa", CptRpa)) add(CPTRPA);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRtr", CptRtr)) add(CPTRTR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIsn", CptIsn)) add(CPTISN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQsp", CptQsp)) add(CPTQSP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptFld", CptFld)) add(CPTFLD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSpt", CptSpt)) add(CPTSPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptSld", CptSld)) add(CPTSLD);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfConn::DpchAppData
 ******************************************************************************/

PnlIdecScfConn::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFCONNDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecScfConn::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfConnData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfConn::DpchAppDo
 ******************************************************************************/

PnlIdecScfConn::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFCONNDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfConn::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfConnDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfConn::DpchEngData
 ******************************************************************************/

PnlIdecScfConn::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFCONNDATA) {
	feedFCsiSchHst.tag = "FeedFCsiSchHst";
	feedFCsiSchIst.tag = "FeedFCsiSchIst";
	feedFCsiSchOst.tag = "FeedFCsiSchOst";
	feedFCsiSchSp1.tag = "FeedFCsiSchSp1";
	feedFCsiSchSp2.tag = "FeedFCsiSchSp2";
	feedFCsiSchSp3.tag = "FeedFCsiSchSp3";
	feedFPupFld.tag = "FeedFPupFld";
	feedFPupLpa.tag = "FeedFPupLpa";
	feedFPupLsn.tag = "FeedFPupLsn";
	feedFPupLtr.tag = "FeedFPupLtr";
	feedFPupPsp.tag = "FeedFPupPsp";
	feedFPupQsp.tag = "FeedFPupQsp";
	feedFPupRpa.tag = "FeedFPupRpa";
	feedFPupRsn.tag = "FeedFPupRsn";
	feedFPupRtr.tag = "FeedFPupRtr";
	feedFPupSld.tag = "FeedFPupSld";
	feedFPupSpt.tag = "FeedFPupSpt";
	feedFPupTsp.tag = "FeedFPupTsp";
	feedFPupVty.tag = "FeedFPupVty";
};

string PnlIdecScfConn::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSISCHHST)) ss.push_back("feedFCsiSchHst");
	if (has(FEEDFCSISCHIST)) ss.push_back("feedFCsiSchIst");
	if (has(FEEDFCSISCHOST)) ss.push_back("feedFCsiSchOst");
	if (has(FEEDFCSISCHSP1)) ss.push_back("feedFCsiSchSp1");
	if (has(FEEDFCSISCHSP2)) ss.push_back("feedFCsiSchSp2");
	if (has(FEEDFCSISCHSP3)) ss.push_back("feedFCsiSchSp3");
	if (has(FEEDFPUPFLD)) ss.push_back("feedFPupFld");
	if (has(FEEDFPUPLPA)) ss.push_back("feedFPupLpa");
	if (has(FEEDFPUPLSN)) ss.push_back("feedFPupLsn");
	if (has(FEEDFPUPLTR)) ss.push_back("feedFPupLtr");
	if (has(FEEDFPUPPSP)) ss.push_back("feedFPupPsp");
	if (has(FEEDFPUPQSP)) ss.push_back("feedFPupQsp");
	if (has(FEEDFPUPRPA)) ss.push_back("feedFPupRpa");
	if (has(FEEDFPUPRSN)) ss.push_back("feedFPupRsn");
	if (has(FEEDFPUPRTR)) ss.push_back("feedFPupRtr");
	if (has(FEEDFPUPSLD)) ss.push_back("feedFPupSld");
	if (has(FEEDFPUPSPT)) ss.push_back("feedFPupSpt");
	if (has(FEEDFPUPTSP)) ss.push_back("feedFPupTsp");
	if (has(FEEDFPUPVTY)) ss.push_back("feedFPupVty");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfConnData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFCsiSchHst.readXML(docctx, basexpath, true)) add(FEEDFCSISCHHST);
		if (feedFCsiSchIst.readXML(docctx, basexpath, true)) add(FEEDFCSISCHIST);
		if (feedFCsiSchOst.readXML(docctx, basexpath, true)) add(FEEDFCSISCHOST);
		if (feedFCsiSchSp1.readXML(docctx, basexpath, true)) add(FEEDFCSISCHSP1);
		if (feedFCsiSchSp2.readXML(docctx, basexpath, true)) add(FEEDFCSISCHSP2);
		if (feedFCsiSchSp3.readXML(docctx, basexpath, true)) add(FEEDFCSISCHSP3);
		if (feedFPupFld.readXML(docctx, basexpath, true)) add(FEEDFPUPFLD);
		if (feedFPupLpa.readXML(docctx, basexpath, true)) add(FEEDFPUPLPA);
		if (feedFPupLsn.readXML(docctx, basexpath, true)) add(FEEDFPUPLSN);
		if (feedFPupLtr.readXML(docctx, basexpath, true)) add(FEEDFPUPLTR);
		if (feedFPupPsp.readXML(docctx, basexpath, true)) add(FEEDFPUPPSP);
		if (feedFPupQsp.readXML(docctx, basexpath, true)) add(FEEDFPUPQSP);
		if (feedFPupRpa.readXML(docctx, basexpath, true)) add(FEEDFPUPRPA);
		if (feedFPupRsn.readXML(docctx, basexpath, true)) add(FEEDFPUPRSN);
		if (feedFPupRtr.readXML(docctx, basexpath, true)) add(FEEDFPUPRTR);
		if (feedFPupSld.readXML(docctx, basexpath, true)) add(FEEDFPUPSLD);
		if (feedFPupSpt.readXML(docctx, basexpath, true)) add(FEEDFPUPSPT);
		if (feedFPupTsp.readXML(docctx, basexpath, true)) add(FEEDFPUPTSP);
		if (feedFPupVty.readXML(docctx, basexpath, true)) add(FEEDFPUPVTY);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFCsiSchHst.clear();
		feedFCsiSchIst.clear();
		feedFCsiSchOst.clear();
		feedFCsiSchSp1.clear();
		feedFCsiSchSp2.clear();
		feedFCsiSchSp3.clear();
		feedFPupFld.clear();
		feedFPupLpa.clear();
		feedFPupLsn.clear();
		feedFPupLtr.clear();
		feedFPupPsp.clear();
		feedFPupQsp.clear();
		feedFPupRpa.clear();
		feedFPupRsn.clear();
		feedFPupRtr.clear();
		feedFPupSld.clear();
		feedFPupSpt.clear();
		feedFPupTsp.clear();
		feedFPupVty.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

/******************************************************************************
 class PnlIdecScfConn::DpchEngLive
 ******************************************************************************/

PnlIdecScfConn::DpchEngLive::DpchEngLive() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFCONNLIVE) {
};

string PnlIdecScfConn::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchEngLive::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfConnLive");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
	} else {
		continf = ContInf();
	};
};

