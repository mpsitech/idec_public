/**
  * \file PnlIdecScfConn_blks.cpp
  * job handler for job PnlIdecScfConn (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

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
	if (TxfLsn == comp->TxfLsn) insert(items, TXFLSN);
	if (numFPupLpa == comp->numFPupLpa) insert(items, NUMFPUPLPA);
	if (TxfLpa == comp->TxfLpa) insert(items, TXFLPA);
	if (numFPupLtr == comp->numFPupLtr) insert(items, NUMFPUPLTR);
	if (numFPupRsn == comp->numFPupRsn) insert(items, NUMFPUPRSN);
	if (TxfRsn == comp->TxfRsn) insert(items, TXFRSN);
	if (numFPupRpa == comp->numFPupRpa) insert(items, NUMFPUPRPA);
	if (TxfRpa == comp->TxfRpa) insert(items, TXFRPA);
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

void PnlIdecScfConn::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfConn";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfConn";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtSchGp1", TxtSchGp1);
		writeStringAttr(wr, itemtag, "sref", "TxtSchGp2", TxtSchGp2);
		writeStringAttr(wr, itemtag, "sref", "TxtSchSp1", TxtSchSp1);
		writeUintAttr(wr, itemtag, "sref", "numFCsiSchSp1", numFCsiSchSp1);
		writeStringAttr(wr, itemtag, "sref", "TxtSchSp2", TxtSchSp2);
		writeUintAttr(wr, itemtag, "sref", "numFCsiSchSp2", numFCsiSchSp2);
		writeStringAttr(wr, itemtag, "sref", "TxtSchSp3", TxtSchSp3);
		writeUintAttr(wr, itemtag, "sref", "numFCsiSchSp3", numFCsiSchSp3);
		writeStringAttr(wr, itemtag, "sref", "TxtSchLd1", TxtSchLd1);
		writeStringAttr(wr, itemtag, "sref", "TxtSchLd2", TxtSchLd2);
		writeStringAttr(wr, itemtag, "sref", "TxtSchOct", TxtSchOct);
		writeStringAttr(wr, itemtag, "sref", "TxtSchOps", TxtSchOps);
		writeUintAttr(wr, itemtag, "sref", "numFCsiSchOst", numFCsiSchOst);
		writeStringAttr(wr, itemtag, "sref", "TxtSchHct", TxtSchHct);
		writeStringAttr(wr, itemtag, "sref", "TxtSchHps", TxtSchHps);
		writeUintAttr(wr, itemtag, "sref", "numFCsiSchHst", numFCsiSchHst);
		writeStringAttr(wr, itemtag, "sref", "TxtSchIps", TxtSchIps);
		writeUintAttr(wr, itemtag, "sref", "numFCsiSchIst", numFCsiSchIst);
		writeStringAttr(wr, itemtag, "sref", "TxtIsn", TxtIsn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfConn::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtSchGp1 == comp->TxtSchGp1) insert(items, TXTSCHGP1);
	if (TxtSchGp2 == comp->TxtSchGp2) insert(items, TXTSCHGP2);
	if (TxtSchSp1 == comp->TxtSchSp1) insert(items, TXTSCHSP1);
	if (numFCsiSchSp1 == comp->numFCsiSchSp1) insert(items, NUMFCSISCHSP1);
	if (TxtSchSp2 == comp->TxtSchSp2) insert(items, TXTSCHSP2);
	if (numFCsiSchSp2 == comp->numFCsiSchSp2) insert(items, NUMFCSISCHSP2);
	if (TxtSchSp3 == comp->TxtSchSp3) insert(items, TXTSCHSP3);
	if (numFCsiSchSp3 == comp->numFCsiSchSp3) insert(items, NUMFCSISCHSP3);
	if (TxtSchLd1 == comp->TxtSchLd1) insert(items, TXTSCHLD1);
	if (TxtSchLd2 == comp->TxtSchLd2) insert(items, TXTSCHLD2);
	if (TxtSchOct == comp->TxtSchOct) insert(items, TXTSCHOCT);
	if (TxtSchOps == comp->TxtSchOps) insert(items, TXTSCHOPS);
	if (numFCsiSchOst == comp->numFCsiSchOst) insert(items, NUMFCSISCHOST);
	if (TxtSchHct == comp->TxtSchHct) insert(items, TXTSCHHCT);
	if (TxtSchHps == comp->TxtSchHps) insert(items, TXTSCHHPS);
	if (numFCsiSchHst == comp->numFCsiSchHst) insert(items, NUMFCSISCHHST);
	if (TxtSchIps == comp->TxtSchIps) insert(items, TXTSCHIPS);
	if (numFCsiSchIst == comp->numFCsiSchIst) insert(items, NUMFCSISCHIST);
	if (TxtIsn == comp->TxtIsn) insert(items, TXTISN);

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

void PnlIdecScfConn::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
			, const bool PupLsnAlt
			, const bool PupLpaAlt
			, const bool PupRsnAlt
			, const bool PupRpaAlt
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScfConn";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScfConn";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
		writeBoolAttr(wr, itemtag, "sref", "PupLsnAlt", PupLsnAlt);
		writeBoolAttr(wr, itemtag, "sref", "PupLpaAlt", PupLpaAlt);
		writeBoolAttr(wr, itemtag, "sref", "PupRsnAlt", PupRsnAlt);
		writeBoolAttr(wr, itemtag, "sref", "PupRpaAlt", PupRpaAlt);
	xmlTextWriterEndElement(wr);
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

void PnlIdecScfConn::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfConn";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfConn";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "TxfLsnValid", TxfLsnValid);
		writeBoolAttr(wr, itemtag, "sref", "TxfLpaValid", TxfLpaValid);
		writeBoolAttr(wr, itemtag, "sref", "TxfRsnValid", TxfRsnValid);
		writeBoolAttr(wr, itemtag, "sref", "TxfRpaValid", TxfRpaValid);
		writeBoolAttr(wr, itemtag, "sref", "PupTspActive", PupTspActive);
		writeBoolAttr(wr, itemtag, "sref", "PupPspActive", PupPspActive);
		writeBoolAttr(wr, itemtag, "sref", "PupVtyActive", PupVtyActive);
		writeBoolAttr(wr, itemtag, "sref", "PupLsnAvail", PupLsnAvail);
		writeBoolAttr(wr, itemtag, "sref", "PupLsnActive", PupLsnActive);
		writeBoolAttr(wr, itemtag, "sref", "PupLpaAvail", PupLpaAvail);
		writeBoolAttr(wr, itemtag, "sref", "PupLpaActive", PupLpaActive);
		writeBoolAttr(wr, itemtag, "sref", "PupLtrActive", PupLtrActive);
		writeBoolAttr(wr, itemtag, "sref", "PupRsnAvail", PupRsnAvail);
		writeBoolAttr(wr, itemtag, "sref", "PupRsnActive", PupRsnActive);
		writeBoolAttr(wr, itemtag, "sref", "PupRpaAvail", PupRpaAvail);
		writeBoolAttr(wr, itemtag, "sref", "PupRpaActive", PupRpaActive);
		writeBoolAttr(wr, itemtag, "sref", "PupRtrActive", PupRtrActive);
		writeBoolAttr(wr, itemtag, "sref", "TxtIsnActive", TxtIsnActive);
		writeBoolAttr(wr, itemtag, "sref", "PupQspActive", PupQspActive);
		writeBoolAttr(wr, itemtag, "sref", "PupFldActive", PupFldActive);
		writeBoolAttr(wr, itemtag, "sref", "PupSptActive", PupSptActive);
	xmlTextWriterEndElement(wr);
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

void PnlIdecScfConn::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfConn";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfConn";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Connections");
			writeStringAttr(wr, itemtag, "sref", "CptSchAll", "alignment laser");
			writeStringAttr(wr, itemtag, "sref", "CptSchLwi", "LWIR camera");
			writeStringAttr(wr, itemtag, "sref", "CptTsp", "\\u03d1 axis SPI");
			writeStringAttr(wr, itemtag, "sref", "CptPsp", "\\u03c6 axis SPI");
			writeStringAttr(wr, itemtag, "sref", "CptVty", "VIS camera type");
			writeStringAttr(wr, itemtag, "sref", "CptLsn", "VIS-L camera serial number");
			writeStringAttr(wr, itemtag, "sref", "CptLpa", "VIS-L camera path");
			writeStringAttr(wr, itemtag, "sref", "CptLtr", "trigger");
			writeStringAttr(wr, itemtag, "sref", "CptRsn", "VIS-R camera serial number");
			writeStringAttr(wr, itemtag, "sref", "CptRpa", "VIS-R camera path");
			writeStringAttr(wr, itemtag, "sref", "CptRtr", "trigger");
			writeStringAttr(wr, itemtag, "sref", "CptIsn", "LWIR camera serial number");
			writeStringAttr(wr, itemtag, "sref", "CptQsp", "QCD detector SPI");
			writeStringAttr(wr, itemtag, "sref", "CptFld", "floodlight LED");
			writeStringAttr(wr, itemtag, "sref", "CptSpt", "spotlight LED");
			writeStringAttr(wr, itemtag, "sref", "CptSld", "status LED policy");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Anschl\\u00fcsse");
			writeStringAttr(wr, itemtag, "sref", "CptSchAll", "Ziellaser");
			writeStringAttr(wr, itemtag, "sref", "CptSchLwi", "LWIR-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptTsp", "SPI \\u03d1-Achse");
			writeStringAttr(wr, itemtag, "sref", "CptPsp", "SPI \\u03c6-Achse");
			writeStringAttr(wr, itemtag, "sref", "CptVty", "VIS-Kameratyp");
			writeStringAttr(wr, itemtag, "sref", "CptLsn", "Seriennummer VIS-L-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptLpa", "Pfad VIS-L-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptLtr", "Ausl\\u00f6ser");
			writeStringAttr(wr, itemtag, "sref", "CptRsn", "Seriennummer VIS-R-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptRpa", "Pfad VIS-R-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptRtr", "Ausl\\u00f6ser");
			writeStringAttr(wr, itemtag, "sref", "CptIsn", "Seriennummer LWIR-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptQsp", "SPI QCD-Detektor");
			writeStringAttr(wr, itemtag, "sref", "CptFld", "LED Scheinwerfer");
			writeStringAttr(wr, itemtag, "sref", "CptSpt", "LED Spot");
			writeStringAttr(wr, itemtag, "sref", "CptSld", "Status-LED-Verhalten");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfConn::DpchAppData
 ******************************************************************************/

PnlIdecScfConn::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFCONNDATA) {
};

string PnlIdecScfConn::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfConnData");
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
 class PnlIdecScfConn::DpchAppDo
 ******************************************************************************/

PnlIdecScfConn::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFCONNDO) {
	ixVDo = 0;
};

string PnlIdecScfConn::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfConnDo");
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
 class PnlIdecScfConn::DpchEngData
 ******************************************************************************/

PnlIdecScfConn::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFCsiSchHst
			, Feed* feedFCsiSchIst
			, Feed* feedFCsiSchOst
			, Feed* feedFCsiSchSp1
			, Feed* feedFCsiSchSp2
			, Feed* feedFCsiSchSp3
			, Feed* feedFPupFld
			, Feed* feedFPupLpa
			, Feed* feedFPupLsn
			, Feed* feedFPupLtr
			, Feed* feedFPupPsp
			, Feed* feedFPupQsp
			, Feed* feedFPupRpa
			, Feed* feedFPupRsn
			, Feed* feedFPupRtr
			, Feed* feedFPupSld
			, Feed* feedFPupSpt
			, Feed* feedFPupTsp
			, Feed* feedFPupVty
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFCONNDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFCSISCHHST, FEEDFCSISCHIST, FEEDFCSISCHOST, FEEDFCSISCHSP1, FEEDFCSISCHSP2, FEEDFCSISCHSP3, FEEDFPUPFLD, FEEDFPUPLPA, FEEDFPUPLSN, FEEDFPUPLTR, FEEDFPUPPSP, FEEDFPUPQSP, FEEDFPUPRPA, FEEDFPUPRSN, FEEDFPUPRTR, FEEDFPUPSLD, FEEDFPUPSPT, FEEDFPUPTSP, FEEDFPUPVTY, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFCSISCHHST) && feedFCsiSchHst) this->feedFCsiSchHst = *feedFCsiSchHst;
	if (find(this->mask, FEEDFCSISCHIST) && feedFCsiSchIst) this->feedFCsiSchIst = *feedFCsiSchIst;
	if (find(this->mask, FEEDFCSISCHOST) && feedFCsiSchOst) this->feedFCsiSchOst = *feedFCsiSchOst;
	if (find(this->mask, FEEDFCSISCHSP1) && feedFCsiSchSp1) this->feedFCsiSchSp1 = *feedFCsiSchSp1;
	if (find(this->mask, FEEDFCSISCHSP2) && feedFCsiSchSp2) this->feedFCsiSchSp2 = *feedFCsiSchSp2;
	if (find(this->mask, FEEDFCSISCHSP3) && feedFCsiSchSp3) this->feedFCsiSchSp3 = *feedFCsiSchSp3;
	if (find(this->mask, FEEDFPUPFLD) && feedFPupFld) this->feedFPupFld = *feedFPupFld;
	if (find(this->mask, FEEDFPUPLPA) && feedFPupLpa) this->feedFPupLpa = *feedFPupLpa;
	if (find(this->mask, FEEDFPUPLSN) && feedFPupLsn) this->feedFPupLsn = *feedFPupLsn;
	if (find(this->mask, FEEDFPUPLTR) && feedFPupLtr) this->feedFPupLtr = *feedFPupLtr;
	if (find(this->mask, FEEDFPUPPSP) && feedFPupPsp) this->feedFPupPsp = *feedFPupPsp;
	if (find(this->mask, FEEDFPUPQSP) && feedFPupQsp) this->feedFPupQsp = *feedFPupQsp;
	if (find(this->mask, FEEDFPUPRPA) && feedFPupRpa) this->feedFPupRpa = *feedFPupRpa;
	if (find(this->mask, FEEDFPUPRSN) && feedFPupRsn) this->feedFPupRsn = *feedFPupRsn;
	if (find(this->mask, FEEDFPUPRTR) && feedFPupRtr) this->feedFPupRtr = *feedFPupRtr;
	if (find(this->mask, FEEDFPUPSLD) && feedFPupSld) this->feedFPupSld = *feedFPupSld;
	if (find(this->mask, FEEDFPUPSPT) && feedFPupSpt) this->feedFPupSpt = *feedFPupSpt;
	if (find(this->mask, FEEDFPUPTSP) && feedFPupTsp) this->feedFPupTsp = *feedFPupTsp;
	if (find(this->mask, FEEDFPUPVTY) && feedFPupVty) this->feedFPupVty = *feedFPupVty;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfConn::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
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

void PnlIdecScfConn::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFCSISCHHST)) {feedFCsiSchHst = src->feedFCsiSchHst; add(FEEDFCSISCHHST);};
	if (src->has(FEEDFCSISCHIST)) {feedFCsiSchIst = src->feedFCsiSchIst; add(FEEDFCSISCHIST);};
	if (src->has(FEEDFCSISCHOST)) {feedFCsiSchOst = src->feedFCsiSchOst; add(FEEDFCSISCHOST);};
	if (src->has(FEEDFCSISCHSP1)) {feedFCsiSchSp1 = src->feedFCsiSchSp1; add(FEEDFCSISCHSP1);};
	if (src->has(FEEDFCSISCHSP2)) {feedFCsiSchSp2 = src->feedFCsiSchSp2; add(FEEDFCSISCHSP2);};
	if (src->has(FEEDFCSISCHSP3)) {feedFCsiSchSp3 = src->feedFCsiSchSp3; add(FEEDFCSISCHSP3);};
	if (src->has(FEEDFPUPFLD)) {feedFPupFld = src->feedFPupFld; add(FEEDFPUPFLD);};
	if (src->has(FEEDFPUPLPA)) {feedFPupLpa = src->feedFPupLpa; add(FEEDFPUPLPA);};
	if (src->has(FEEDFPUPLSN)) {feedFPupLsn = src->feedFPupLsn; add(FEEDFPUPLSN);};
	if (src->has(FEEDFPUPLTR)) {feedFPupLtr = src->feedFPupLtr; add(FEEDFPUPLTR);};
	if (src->has(FEEDFPUPPSP)) {feedFPupPsp = src->feedFPupPsp; add(FEEDFPUPPSP);};
	if (src->has(FEEDFPUPQSP)) {feedFPupQsp = src->feedFPupQsp; add(FEEDFPUPQSP);};
	if (src->has(FEEDFPUPRPA)) {feedFPupRpa = src->feedFPupRpa; add(FEEDFPUPRPA);};
	if (src->has(FEEDFPUPRSN)) {feedFPupRsn = src->feedFPupRsn; add(FEEDFPUPRSN);};
	if (src->has(FEEDFPUPRTR)) {feedFPupRtr = src->feedFPupRtr; add(FEEDFPUPRTR);};
	if (src->has(FEEDFPUPSLD)) {feedFPupSld = src->feedFPupSld; add(FEEDFPUPSLD);};
	if (src->has(FEEDFPUPSPT)) {feedFPupSpt = src->feedFPupSpt; add(FEEDFPUPSPT);};
	if (src->has(FEEDFPUPTSP)) {feedFPupTsp = src->feedFPupTsp; add(FEEDFPUPTSP);};
	if (src->has(FEEDFPUPVTY)) {feedFPupVty = src->feedFPupVty; add(FEEDFPUPVTY);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfConn::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfConnData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFCSISCHHST)) feedFCsiSchHst.writeXML(wr);
		if (has(FEEDFCSISCHIST)) feedFCsiSchIst.writeXML(wr);
		if (has(FEEDFCSISCHOST)) feedFCsiSchOst.writeXML(wr);
		if (has(FEEDFCSISCHSP1)) feedFCsiSchSp1.writeXML(wr);
		if (has(FEEDFCSISCHSP2)) feedFCsiSchSp2.writeXML(wr);
		if (has(FEEDFCSISCHSP3)) feedFCsiSchSp3.writeXML(wr);
		if (has(FEEDFPUPFLD)) feedFPupFld.writeXML(wr);
		if (has(FEEDFPUPLPA)) feedFPupLpa.writeXML(wr);
		if (has(FEEDFPUPLSN)) feedFPupLsn.writeXML(wr);
		if (has(FEEDFPUPLTR)) feedFPupLtr.writeXML(wr);
		if (has(FEEDFPUPPSP)) feedFPupPsp.writeXML(wr);
		if (has(FEEDFPUPQSP)) feedFPupQsp.writeXML(wr);
		if (has(FEEDFPUPRPA)) feedFPupRpa.writeXML(wr);
		if (has(FEEDFPUPRSN)) feedFPupRsn.writeXML(wr);
		if (has(FEEDFPUPRTR)) feedFPupRtr.writeXML(wr);
		if (has(FEEDFPUPSLD)) feedFPupSld.writeXML(wr);
		if (has(FEEDFPUPSPT)) feedFPupSpt.writeXML(wr);
		if (has(FEEDFPUPTSP)) feedFPupTsp.writeXML(wr);
		if (has(FEEDFPUPVTY)) feedFPupVty.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfConn::DpchEngLive
 ******************************************************************************/

PnlIdecScfConn::DpchEngLive::DpchEngLive(
			const ubigint jref
			, ContInf* continf
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFCONNLIVE, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTINF};
	else this->mask = mask;

	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
};

string PnlIdecScfConn::DpchEngLive::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfConn::DpchEngLive::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngLive* src = (DpchEngLive*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
};

void PnlIdecScfConn::DpchEngLive::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfConnLive");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

