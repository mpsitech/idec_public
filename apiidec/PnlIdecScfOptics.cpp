/**
  * \file PnlIdecScfOptics.cpp
  * API code for job PnlIdecScfOptics (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecScfOptics.h"

/******************************************************************************
 class PnlIdecScfOptics::VecVDo
 ******************************************************************************/

uint PnlIdecScfOptics::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butmasterclick") return BUTMASTERCLICK;

	return(0);
};

string PnlIdecScfOptics::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMASTERCLICK) return("ButMasterClick");

	return("");
};

/******************************************************************************
 class PnlIdecScfOptics::ContIac
 ******************************************************************************/

PnlIdecScfOptics::ContIac::ContIac(
			const string& TxfDst
			, const string& TxfIdx
			, const string& TxfIdy
			, const string& TxfQdx
			, const string& TxfQdy
			, const string& TxfAdx
			, const string& TxfAdy
			, const uint numFPupLsg
			, const uint numFPupRsg
			, const uint numFPupIsg
			, const int UpdQwh
			, const string& TxfQhp
			, const string& TxfQdp
			, const string& TxfQfl
			, const string& TxfQfn
			, const uint numFPupQsg
		) : Block() {
	this->TxfDst = TxfDst;
	this->TxfIdx = TxfIdx;
	this->TxfIdy = TxfIdy;
	this->TxfQdx = TxfQdx;
	this->TxfQdy = TxfQdy;
	this->TxfAdx = TxfAdx;
	this->TxfAdy = TxfAdy;
	this->numFPupLsg = numFPupLsg;
	this->numFPupRsg = numFPupRsg;
	this->numFPupIsg = numFPupIsg;
	this->UpdQwh = UpdQwh;
	this->TxfQhp = TxfQhp;
	this->TxfQdp = TxfQdp;
	this->TxfQfl = TxfQfl;
	this->TxfQfn = TxfQfn;
	this->numFPupQsg = numFPupQsg;

	mask = {TXFDST, TXFIDX, TXFIDY, TXFQDX, TXFQDY, TXFADX, TXFADY, NUMFPUPLSG, NUMFPUPRSG, NUMFPUPISG, UPDQWH, TXFQHP, TXFQDP, TXFQFL, TXFQFN, NUMFPUPQSG};
};

bool PnlIdecScfOptics::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecScfOptics");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecScfOptics";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfDst", TxfDst)) add(TXFDST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfIdx", TxfIdx)) add(TXFIDX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfIdy", TxfIdy)) add(TXFIDY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfQdx", TxfQdx)) add(TXFQDX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfQdy", TxfQdy)) add(TXFQDY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfAdx", TxfAdx)) add(TXFADX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfAdy", TxfAdy)) add(TXFADY);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupLsg", numFPupLsg)) add(NUMFPUPLSG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupRsg", numFPupRsg)) add(NUMFPUPRSG);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupIsg", numFPupIsg)) add(NUMFPUPISG);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "UpdQwh", UpdQwh)) add(UPDQWH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfQhp", TxfQhp)) add(TXFQHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfQdp", TxfQdp)) add(TXFQDP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfQfl", TxfQfl)) add(TXFQFL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxfQfn", TxfQfn)) add(TXFQFN);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFPupQsg", numFPupQsg)) add(NUMFPUPQSG);
	};

	return basefound;
};

void PnlIdecScfOptics::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecScfOptics";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecScfOptics";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "TxfDst", TxfDst);
		writeStringAttr(wr, itemtag, "sref", "TxfIdx", TxfIdx);
		writeStringAttr(wr, itemtag, "sref", "TxfIdy", TxfIdy);
		writeStringAttr(wr, itemtag, "sref", "TxfQdx", TxfQdx);
		writeStringAttr(wr, itemtag, "sref", "TxfQdy", TxfQdy);
		writeStringAttr(wr, itemtag, "sref", "TxfAdx", TxfAdx);
		writeStringAttr(wr, itemtag, "sref", "TxfAdy", TxfAdy);
		writeUintAttr(wr, itemtag, "sref", "numFPupLsg", numFPupLsg);
		writeUintAttr(wr, itemtag, "sref", "numFPupRsg", numFPupRsg);
		writeUintAttr(wr, itemtag, "sref", "numFPupIsg", numFPupIsg);
		writeIntAttr(wr, itemtag, "sref", "UpdQwh", UpdQwh);
		writeStringAttr(wr, itemtag, "sref", "TxfQhp", TxfQhp);
		writeStringAttr(wr, itemtag, "sref", "TxfQdp", TxfQdp);
		writeStringAttr(wr, itemtag, "sref", "TxfQfl", TxfQfl);
		writeStringAttr(wr, itemtag, "sref", "TxfQfn", TxfQfn);
		writeUintAttr(wr, itemtag, "sref", "numFPupQsg", numFPupQsg);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfOptics::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (TxfDst.compare(comp->TxfDst) == 0) insert(items, TXFDST);
	if (TxfIdx.compare(comp->TxfIdx) == 0) insert(items, TXFIDX);
	if (TxfIdy.compare(comp->TxfIdy) == 0) insert(items, TXFIDY);
	if (TxfQdx.compare(comp->TxfQdx) == 0) insert(items, TXFQDX);
	if (TxfQdy.compare(comp->TxfQdy) == 0) insert(items, TXFQDY);
	if (TxfAdx.compare(comp->TxfAdx) == 0) insert(items, TXFADX);
	if (TxfAdy.compare(comp->TxfAdy) == 0) insert(items, TXFADY);
	if (numFPupLsg == comp->numFPupLsg) insert(items, NUMFPUPLSG);
	if (numFPupRsg == comp->numFPupRsg) insert(items, NUMFPUPRSG);
	if (numFPupIsg == comp->numFPupIsg) insert(items, NUMFPUPISG);
	if (UpdQwh == comp->UpdQwh) insert(items, UPDQWH);
	if (TxfQhp.compare(comp->TxfQhp) == 0) insert(items, TXFQHP);
	if (TxfQdp.compare(comp->TxfQdp) == 0) insert(items, TXFQDP);
	if (TxfQfl.compare(comp->TxfQfl) == 0) insert(items, TXFQFL);
	if (TxfQfn.compare(comp->TxfQfn) == 0) insert(items, TXFQFN);
	if (numFPupQsg == comp->numFPupQsg) insert(items, NUMFPUPQSG);

	return(items);
};

set<uint> PnlIdecScfOptics::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFDST, TXFIDX, TXFIDY, TXFQDX, TXFQDY, TXFADX, TXFADY, NUMFPUPLSG, NUMFPUPRSG, NUMFPUPISG, UPDQWH, TXFQHP, TXFQDP, TXFQFL, TXFQFN, NUMFPUPQSG};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfOptics::ContInf
 ******************************************************************************/

PnlIdecScfOptics::ContInf::ContInf(
			const bool ButMasterOn
			, const string& TxtVwi
			, const string& TxtVhe
			, const string& TxtVhp
			, const string& TxtVfl
			, const string& TxtVfn
			, const string& TxtIwi
			, const string& TxtIhe
			, const string& TxtIhp
			, const string& TxtIfl
			, const string& TxtIfn
		) : Block() {
	this->ButMasterOn = ButMasterOn;
	this->TxtVwi = TxtVwi;
	this->TxtVhe = TxtVhe;
	this->TxtVhp = TxtVhp;
	this->TxtVfl = TxtVfl;
	this->TxtVfn = TxtVfn;
	this->TxtIwi = TxtIwi;
	this->TxtIhe = TxtIhe;
	this->TxtIhp = TxtIhp;
	this->TxtIfl = TxtIfl;
	this->TxtIfn = TxtIfn;

	mask = {BUTMASTERON, TXTVWI, TXTVHE, TXTVHP, TXTVFL, TXTVFN, TXTIWI, TXTIHE, TXTIHP, TXTIFL, TXTIFN};
};

bool PnlIdecScfOptics::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecScfOptics");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecScfOptics";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButMasterOn", ButMasterOn)) add(BUTMASTERON);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtVwi", TxtVwi)) add(TXTVWI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtVhe", TxtVhe)) add(TXTVHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtVhp", TxtVhp)) add(TXTVHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtVfl", TxtVfl)) add(TXTVFL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtVfn", TxtVfn)) add(TXTVFN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIwi", TxtIwi)) add(TXTIWI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIhe", TxtIhe)) add(TXTIHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIhp", TxtIhp)) add(TXTIHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIfl", TxtIfl)) add(TXTIFL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtIfn", TxtIfn)) add(TXTIFN);
	};

	return basefound;
};

set<uint> PnlIdecScfOptics::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtVwi.compare(comp->TxtVwi) == 0) insert(items, TXTVWI);
	if (TxtVhe.compare(comp->TxtVhe) == 0) insert(items, TXTVHE);
	if (TxtVhp.compare(comp->TxtVhp) == 0) insert(items, TXTVHP);
	if (TxtVfl.compare(comp->TxtVfl) == 0) insert(items, TXTVFL);
	if (TxtVfn.compare(comp->TxtVfn) == 0) insert(items, TXTVFN);
	if (TxtIwi.compare(comp->TxtIwi) == 0) insert(items, TXTIWI);
	if (TxtIhe.compare(comp->TxtIhe) == 0) insert(items, TXTIHE);
	if (TxtIhp.compare(comp->TxtIhp) == 0) insert(items, TXTIHP);
	if (TxtIfl.compare(comp->TxtIfl) == 0) insert(items, TXTIFL);
	if (TxtIfn.compare(comp->TxtIfn) == 0) insert(items, TXTIFN);

	return(items);
};

set<uint> PnlIdecScfOptics::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {BUTMASTERON, TXTVWI, TXTVHE, TXTVHP, TXTVFL, TXTVFN, TXTIWI, TXTIHE, TXTIHP, TXTIFL, TXTIFN};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfOptics::StatApp
 ******************************************************************************/

PnlIdecScfOptics::StatApp::StatApp(
			const uint ixIdecVExpstate
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;

	mask = {IXIDECVEXPSTATE};
};

bool PnlIdecScfOptics::StatApp::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatAppIdecScfOptics");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemAppIdecScfOptics";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
	};

	return basefound;
};

set<uint> PnlIdecScfOptics::StatApp::comm(
			const StatApp* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);

	return(items);
};

set<uint> PnlIdecScfOptics::StatApp::diff(
			const StatApp* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfOptics::StatShr
 ******************************************************************************/

PnlIdecScfOptics::StatShr::StatShr(
			const bool TxfDstActive
			, const bool TxfIdxActive
			, const bool TxfIdyActive
			, const bool TxfQdxActive
			, const bool TxfQdyActive
			, const bool TxfAdxActive
			, const bool TxfAdyActive
			, const bool PupLsgActive
			, const bool PupRsgActive
			, const bool PupIsgActive
			, const bool UpdQwhActive
			, const int UpdQwhMin
			, const int UpdQwhMax
			, const bool TxfQhpActive
			, const bool TxfQdpActive
			, const bool TxfQflActive
			, const bool TxfQfnActive
			, const bool PupQsgActive
		) : Block() {
	this->TxfDstActive = TxfDstActive;
	this->TxfIdxActive = TxfIdxActive;
	this->TxfIdyActive = TxfIdyActive;
	this->TxfQdxActive = TxfQdxActive;
	this->TxfQdyActive = TxfQdyActive;
	this->TxfAdxActive = TxfAdxActive;
	this->TxfAdyActive = TxfAdyActive;
	this->PupLsgActive = PupLsgActive;
	this->PupRsgActive = PupRsgActive;
	this->PupIsgActive = PupIsgActive;
	this->UpdQwhActive = UpdQwhActive;
	this->UpdQwhMin = UpdQwhMin;
	this->UpdQwhMax = UpdQwhMax;
	this->TxfQhpActive = TxfQhpActive;
	this->TxfQdpActive = TxfQdpActive;
	this->TxfQflActive = TxfQflActive;
	this->TxfQfnActive = TxfQfnActive;
	this->PupQsgActive = PupQsgActive;

	mask = {TXFDSTACTIVE, TXFIDXACTIVE, TXFIDYACTIVE, TXFQDXACTIVE, TXFQDYACTIVE, TXFADXACTIVE, TXFADYACTIVE, PUPLSGACTIVE, PUPRSGACTIVE, PUPISGACTIVE, UPDQWHACTIVE, UPDQWHMIN, UPDQWHMAX, TXFQHPACTIVE, TXFQDPACTIVE, TXFQFLACTIVE, TXFQFNACTIVE, PUPQSGACTIVE};
};

bool PnlIdecScfOptics::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecScfOptics");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecScfOptics";

	if (basefound) {
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfDstActive", TxfDstActive)) add(TXFDSTACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfIdxActive", TxfIdxActive)) add(TXFIDXACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfIdyActive", TxfIdyActive)) add(TXFIDYACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfQdxActive", TxfQdxActive)) add(TXFQDXACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfQdyActive", TxfQdyActive)) add(TXFQDYACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfAdxActive", TxfAdxActive)) add(TXFADXACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfAdyActive", TxfAdyActive)) add(TXFADYACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupLsgActive", PupLsgActive)) add(PUPLSGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupRsgActive", PupRsgActive)) add(PUPRSGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupIsgActive", PupIsgActive)) add(PUPISGACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdQwhActive", UpdQwhActive)) add(UPDQWHACTIVE);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdQwhMin", UpdQwhMin)) add(UPDQWHMIN);
		if (extractIntAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "UpdQwhMax", UpdQwhMax)) add(UPDQWHMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfQhpActive", TxfQhpActive)) add(TXFQHPACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfQdpActive", TxfQdpActive)) add(TXFQDPACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfQflActive", TxfQflActive)) add(TXFQFLACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TxfQfnActive", TxfQfnActive)) add(TXFQFNACTIVE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "PupQsgActive", PupQsgActive)) add(PUPQSGACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecScfOptics::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (TxfDstActive == comp->TxfDstActive) insert(items, TXFDSTACTIVE);
	if (TxfIdxActive == comp->TxfIdxActive) insert(items, TXFIDXACTIVE);
	if (TxfIdyActive == comp->TxfIdyActive) insert(items, TXFIDYACTIVE);
	if (TxfQdxActive == comp->TxfQdxActive) insert(items, TXFQDXACTIVE);
	if (TxfQdyActive == comp->TxfQdyActive) insert(items, TXFQDYACTIVE);
	if (TxfAdxActive == comp->TxfAdxActive) insert(items, TXFADXACTIVE);
	if (TxfAdyActive == comp->TxfAdyActive) insert(items, TXFADYACTIVE);
	if (PupLsgActive == comp->PupLsgActive) insert(items, PUPLSGACTIVE);
	if (PupRsgActive == comp->PupRsgActive) insert(items, PUPRSGACTIVE);
	if (PupIsgActive == comp->PupIsgActive) insert(items, PUPISGACTIVE);
	if (UpdQwhActive == comp->UpdQwhActive) insert(items, UPDQWHACTIVE);
	if (UpdQwhMin == comp->UpdQwhMin) insert(items, UPDQWHMIN);
	if (UpdQwhMax == comp->UpdQwhMax) insert(items, UPDQWHMAX);
	if (TxfQhpActive == comp->TxfQhpActive) insert(items, TXFQHPACTIVE);
	if (TxfQdpActive == comp->TxfQdpActive) insert(items, TXFQDPACTIVE);
	if (TxfQflActive == comp->TxfQflActive) insert(items, TXFQFLACTIVE);
	if (TxfQfnActive == comp->TxfQfnActive) insert(items, TXFQFNACTIVE);
	if (PupQsgActive == comp->PupQsgActive) insert(items, PUPQSGACTIVE);

	return(items);
};

set<uint> PnlIdecScfOptics::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXFDSTACTIVE, TXFIDXACTIVE, TXFIDYACTIVE, TXFQDXACTIVE, TXFQDYACTIVE, TXFADXACTIVE, TXFADYACTIVE, PUPLSGACTIVE, PUPRSGACTIVE, PUPISGACTIVE, UPDQWHACTIVE, UPDQWHMIN, UPDQWHMAX, TXFQHPACTIVE, TXFQDPACTIVE, TXFQFLACTIVE, TXFQFNACTIVE, PUPQSGACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecScfOptics::Tag
 ******************************************************************************/

PnlIdecScfOptics::Tag::Tag(
			const string& Cpt
			, const string& HdgGeom
			, const string& CptDst
			, const string& CptIdx
			, const string& CptIdy
			, const string& CptQdx
			, const string& CptQdy
			, const string& CptAdx
			, const string& CptAdy
			, const string& HdgVislr
			, const string& CptVwi
			, const string& CptVhe
			, const string& CptVhp
			, const string& CptVfl
			, const string& CptVfn
			, const string& CptLsg
			, const string& CptRsg
			, const string& HdgLwir
			, const string& CptIwi
			, const string& CptIhe
			, const string& CptIhp
			, const string& CptIfl
			, const string& CptIfn
			, const string& CptIsg
			, const string& HdgQcd
			, const string& CptQwh
			, const string& CptQhp
			, const string& CptQdp
			, const string& CptQfl
			, const string& CptQfn
			, const string& CptQsg
		) : Block() {
	this->Cpt = Cpt;
	this->HdgGeom = HdgGeom;
	this->CptDst = CptDst;
	this->CptIdx = CptIdx;
	this->CptIdy = CptIdy;
	this->CptQdx = CptQdx;
	this->CptQdy = CptQdy;
	this->CptAdx = CptAdx;
	this->CptAdy = CptAdy;
	this->HdgVislr = HdgVislr;
	this->CptVwi = CptVwi;
	this->CptVhe = CptVhe;
	this->CptVhp = CptVhp;
	this->CptVfl = CptVfl;
	this->CptVfn = CptVfn;
	this->CptLsg = CptLsg;
	this->CptRsg = CptRsg;
	this->HdgLwir = HdgLwir;
	this->CptIwi = CptIwi;
	this->CptIhe = CptIhe;
	this->CptIhp = CptIhp;
	this->CptIfl = CptIfl;
	this->CptIfn = CptIfn;
	this->CptIsg = CptIsg;
	this->HdgQcd = HdgQcd;
	this->CptQwh = CptQwh;
	this->CptQhp = CptQhp;
	this->CptQdp = CptQdp;
	this->CptQfl = CptQfl;
	this->CptQfn = CptQfn;
	this->CptQsg = CptQsg;

	mask = {CPT, HDGGEOM, CPTDST, CPTIDX, CPTIDY, CPTQDX, CPTQDY, CPTADX, CPTADY, HDGVISLR, CPTVWI, CPTVHE, CPTVHP, CPTVFL, CPTVFN, CPTLSG, CPTRSG, HDGLWIR, CPTIWI, CPTIHE, CPTIHP, CPTIFL, CPTIFN, CPTISG, HDGQCD, CPTQWH, CPTQHP, CPTQDP, CPTQFL, CPTQFN, CPTQSG};
};

bool PnlIdecScfOptics::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecScfOptics");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecScfOptics";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgGeom", HdgGeom)) add(HDGGEOM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptDst", CptDst)) add(CPTDST);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIdx", CptIdx)) add(CPTIDX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIdy", CptIdy)) add(CPTIDY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQdx", CptQdx)) add(CPTQDX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQdy", CptQdy)) add(CPTQDY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAdx", CptAdx)) add(CPTADX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptAdy", CptAdy)) add(CPTADY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgVislr", HdgVislr)) add(HDGVISLR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVwi", CptVwi)) add(CPTVWI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVhe", CptVhe)) add(CPTVHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVhp", CptVhp)) add(CPTVHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVfl", CptVfl)) add(CPTVFL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptVfn", CptVfn)) add(CPTVFN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptLsg", CptLsg)) add(CPTLSG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptRsg", CptRsg)) add(CPTRSG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgLwir", HdgLwir)) add(HDGLWIR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIwi", CptIwi)) add(CPTIWI);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIhe", CptIhe)) add(CPTIHE);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIhp", CptIhp)) add(CPTIHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIfl", CptIfl)) add(CPTIFL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIfn", CptIfn)) add(CPTIFN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptIsg", CptIsg)) add(CPTISG);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "HdgQcd", HdgQcd)) add(HDGQCD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQwh", CptQwh)) add(CPTQWH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQhp", CptQhp)) add(CPTQHP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQdp", CptQdp)) add(CPTQDP);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQfl", CptQfl)) add(CPTQFL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQfn", CptQfn)) add(CPTQFN);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "CptQsg", CptQsg)) add(CPTQSG);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecScfOptics::DpchAppData
 ******************************************************************************/

PnlIdecScfOptics::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFOPTICSDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
};

string PnlIdecScfOptics::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfOptics::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfOpticsData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfOptics::DpchAppDo
 ******************************************************************************/

PnlIdecScfOptics::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFOPTICSDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecScfOptics::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfOptics::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecScfOpticsDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfOptics::DpchEngData
 ******************************************************************************/

PnlIdecScfOptics::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFOPTICSDATA) {
	feedFPupIsg.tag = "FeedFPupIsg";
	feedFPupLsg.tag = "FeedFPupLsg";
	feedFPupQsg.tag = "FeedFPupQsg";
	feedFPupRsg.tag = "FeedFPupRsg";
};

string PnlIdecScfOptics::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFPUPISG)) ss.push_back("feedFPupIsg");
	if (has(FEEDFPUPLSG)) ss.push_back("feedFPupLsg");
	if (has(FEEDFPUPQSG)) ss.push_back("feedFPupQsg");
	if (has(FEEDFPUPRSG)) ss.push_back("feedFPupRsg");
	if (has(STATAPP)) ss.push_back("statapp");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(TAG)) ss.push_back("tag");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfOptics::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecScfOpticsData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFPupIsg.readXML(docctx, basexpath, true)) add(FEEDFPUPISG);
		if (feedFPupLsg.readXML(docctx, basexpath, true)) add(FEEDFPUPLSG);
		if (feedFPupQsg.readXML(docctx, basexpath, true)) add(FEEDFPUPQSG);
		if (feedFPupRsg.readXML(docctx, basexpath, true)) add(FEEDFPUPRSG);
		if (statapp.readXML(docctx, basexpath, true)) add(STATAPP);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFPupIsg.clear();
		feedFPupLsg.clear();
		feedFPupQsg.clear();
		feedFPupRsg.clear();
		statapp = StatApp();
		statshr = StatShr();
		tag = Tag();
	};
};

