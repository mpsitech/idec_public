/**
  * \file PnlIdecScfOptics_blks.cpp
  * job handler for job PnlIdecScfOptics (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

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

	if (TxfDst == comp->TxfDst) insert(items, TXFDST);
	if (TxfIdx == comp->TxfIdx) insert(items, TXFIDX);
	if (TxfIdy == comp->TxfIdy) insert(items, TXFIDY);
	if (TxfQdx == comp->TxfQdx) insert(items, TXFQDX);
	if (TxfQdy == comp->TxfQdy) insert(items, TXFQDY);
	if (TxfAdx == comp->TxfAdx) insert(items, TXFADX);
	if (TxfAdy == comp->TxfAdy) insert(items, TXFADY);
	if (numFPupLsg == comp->numFPupLsg) insert(items, NUMFPUPLSG);
	if (numFPupRsg == comp->numFPupRsg) insert(items, NUMFPUPRSG);
	if (numFPupIsg == comp->numFPupIsg) insert(items, NUMFPUPISG);
	if (UpdQwh == comp->UpdQwh) insert(items, UPDQWH);
	if (TxfQhp == comp->TxfQhp) insert(items, TXFQHP);
	if (TxfQdp == comp->TxfQdp) insert(items, TXFQDP);
	if (TxfQfl == comp->TxfQfl) insert(items, TXFQFL);
	if (TxfQfn == comp->TxfQfn) insert(items, TXFQFN);
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

void PnlIdecScfOptics::ContInf::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContInfIdecScfOptics";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemInfIdecScfOptics";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "ButMasterOn", ButMasterOn);
		writeStringAttr(wr, itemtag, "sref", "TxtVwi", TxtVwi);
		writeStringAttr(wr, itemtag, "sref", "TxtVhe", TxtVhe);
		writeStringAttr(wr, itemtag, "sref", "TxtVhp", TxtVhp);
		writeStringAttr(wr, itemtag, "sref", "TxtVfl", TxtVfl);
		writeStringAttr(wr, itemtag, "sref", "TxtVfn", TxtVfn);
		writeStringAttr(wr, itemtag, "sref", "TxtIwi", TxtIwi);
		writeStringAttr(wr, itemtag, "sref", "TxtIhe", TxtIhe);
		writeStringAttr(wr, itemtag, "sref", "TxtIhp", TxtIhp);
		writeStringAttr(wr, itemtag, "sref", "TxtIfl", TxtIfl);
		writeStringAttr(wr, itemtag, "sref", "TxtIfn", TxtIfn);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecScfOptics::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (ButMasterOn == comp->ButMasterOn) insert(items, BUTMASTERON);
	if (TxtVwi == comp->TxtVwi) insert(items, TXTVWI);
	if (TxtVhe == comp->TxtVhe) insert(items, TXTVHE);
	if (TxtVhp == comp->TxtVhp) insert(items, TXTVHP);
	if (TxtVfl == comp->TxtVfl) insert(items, TXTVFL);
	if (TxtVfn == comp->TxtVfn) insert(items, TXTVFN);
	if (TxtIwi == comp->TxtIwi) insert(items, TXTIWI);
	if (TxtIhe == comp->TxtIhe) insert(items, TXTIHE);
	if (TxtIhp == comp->TxtIhp) insert(items, TXTIHP);
	if (TxtIfl == comp->TxtIfl) insert(items, TXTIFL);
	if (TxtIfn == comp->TxtIfn) insert(items, TXTIFN);

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

void PnlIdecScfOptics::StatApp::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
			, const uint ixIdecVExpstate
		) {
	if (difftag.length() == 0) difftag = "StatAppIdecScfOptics";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemAppIdecScfOptics";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVExpstate", VecIdecVExpstate::getSref(ixIdecVExpstate));
	xmlTextWriterEndElement(wr);
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

void PnlIdecScfOptics::StatShr::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StatShrIdecScfOptics";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StatitemShrIdecScfOptics";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeBoolAttr(wr, itemtag, "sref", "TxfDstActive", TxfDstActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfIdxActive", TxfIdxActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfIdyActive", TxfIdyActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfQdxActive", TxfQdxActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfQdyActive", TxfQdyActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfAdxActive", TxfAdxActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfAdyActive", TxfAdyActive);
		writeBoolAttr(wr, itemtag, "sref", "PupLsgActive", PupLsgActive);
		writeBoolAttr(wr, itemtag, "sref", "PupRsgActive", PupRsgActive);
		writeBoolAttr(wr, itemtag, "sref", "PupIsgActive", PupIsgActive);
		writeBoolAttr(wr, itemtag, "sref", "UpdQwhActive", UpdQwhActive);
		writeIntAttr(wr, itemtag, "sref", "UpdQwhMin", UpdQwhMin);
		writeIntAttr(wr, itemtag, "sref", "UpdQwhMax", UpdQwhMax);
		writeBoolAttr(wr, itemtag, "sref", "TxfQhpActive", TxfQhpActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfQdpActive", TxfQdpActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfQflActive", TxfQflActive);
		writeBoolAttr(wr, itemtag, "sref", "TxfQfnActive", TxfQfnActive);
		writeBoolAttr(wr, itemtag, "sref", "PupQsgActive", PupQsgActive);
	xmlTextWriterEndElement(wr);
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

void PnlIdecScfOptics::Tag::writeXML(
			const uint ixIdecVLocale
			, xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "TagIdecScfOptics";

	string itemtag;
	if (shorttags) itemtag = "Ti";
	else itemtag = "TagitemIdecScfOptics";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		if (ixIdecVLocale == VecIdecVLocale::ENUS) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Optics");
			writeStringAttr(wr, itemtag, "sref", "HdgGeom", "Geometry");
			writeStringAttr(wr, itemtag, "sref", "CptDst", "stereo distance \\u0394s [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptIdx", "LWIR camera offset \\u0394xLWIR [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptIdy", "\\u0394yLWIR [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptQdx", "QCD detector offset \\u0394xQCD [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptQdy", "\\u0394yQCD [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptAdx", "alignment laser offset \\u0394xAL [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptAdy", "\\u0394yAL [mm]");
			writeStringAttr(wr, itemtag, "sref", "HdgVislr", "VIS-L/R cameras");
			writeStringAttr(wr, itemtag, "sref", "CptVwi", "width");
			writeStringAttr(wr, itemtag, "sref", "CptVhe", "height");
			writeStringAttr(wr, itemtag, "sref", "CptVhp", "pixel size [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptVfl", "focal length [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptVfn", "f-number");
			writeStringAttr(wr, itemtag, "sref", "CptLsg", "VIS-L camera orientation");
			writeStringAttr(wr, itemtag, "sref", "CptRsg", "VIS-R camera orientation");
			writeStringAttr(wr, itemtag, "sref", "HdgLwir", "LWIR camera");
			writeStringAttr(wr, itemtag, "sref", "CptIwi", "width");
			writeStringAttr(wr, itemtag, "sref", "CptIhe", "height");
			writeStringAttr(wr, itemtag, "sref", "CptIhp", "pixel size [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptIfl", "focal length [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptIfn", "f-number");
			writeStringAttr(wr, itemtag, "sref", "CptIsg", "orientation");
			writeStringAttr(wr, itemtag, "sref", "HdgQcd", "QCD detector");
			writeStringAttr(wr, itemtag, "sref", "CptQwh", "width and height");
			writeStringAttr(wr, itemtag, "sref", "CptQhp", "pixel size [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptQdp", "pixel distance [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptQfl", "focal length [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptQfn", "f-number");
			writeStringAttr(wr, itemtag, "sref", "CptQsg", "orientation");
		} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
			writeStringAttr(wr, itemtag, "sref", "Cpt", "Optik");
			writeStringAttr(wr, itemtag, "sref", "HdgGeom", "Geometrie");
			writeStringAttr(wr, itemtag, "sref", "CptDst", "Stereo-Abstand \\u0394s [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptIdx", "Achsabst. LWIR-Kamera \\u0394xLWIR [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptIdy", "\\u0394yLWIR [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptQdx", "Achsabstand QCD-Detektor \\u0394xQCD [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptQdy", "\\u0394yQCD [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptAdx", "Achsabstand Ziellaser \\u0394xAL [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptAdy", "\\u0394yAL [mm]");
			writeStringAttr(wr, itemtag, "sref", "HdgVislr", "VIS-L/R-Kameras");
			writeStringAttr(wr, itemtag, "sref", "CptVwi", "Breite");
			writeStringAttr(wr, itemtag, "sref", "CptVhe", "H\\u00f6he");
			writeStringAttr(wr, itemtag, "sref", "CptVhp", "Pixelgr\\u00f6sse [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptVfl", "Brennweite [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptVfn", "Blendenzahl");
			writeStringAttr(wr, itemtag, "sref", "CptLsg", "Ausrichtung VIS-L-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptRsg", "Ausrichtung VIS-R-Kamera");
			writeStringAttr(wr, itemtag, "sref", "HdgLwir", "LWIR-Kamera");
			writeStringAttr(wr, itemtag, "sref", "CptIwi", "Breite");
			writeStringAttr(wr, itemtag, "sref", "CptIhe", "H\\u00f6he");
			writeStringAttr(wr, itemtag, "sref", "CptIhp", "Pixelgr\\u00f6sse [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptIfl", "Brennweite [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptIfn", "Blendenzahl");
			writeStringAttr(wr, itemtag, "sref", "CptIsg", "Ausrichtung");
			writeStringAttr(wr, itemtag, "sref", "HdgQcd", "QCD-Detektor");
			writeStringAttr(wr, itemtag, "sref", "CptQwh", "Breite und H\\u00f6he");
			writeStringAttr(wr, itemtag, "sref", "CptQhp", "Pixelgr\\u00f6sse [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptQdp", "Pixelabstand [\\u03bcm]");
			writeStringAttr(wr, itemtag, "sref", "CptQfl", "Brennweite [mm]");
			writeStringAttr(wr, itemtag, "sref", "CptQfn", "Blendenzahl");
			writeStringAttr(wr, itemtag, "sref", "CptQsg", "Ausrichtung");
		};
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecScfOptics::DpchAppData
 ******************************************************************************/

PnlIdecScfOptics::DpchAppData::DpchAppData() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFOPTICSDATA) {
};

string PnlIdecScfOptics::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTIAC)) ss.push_back("contiac");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfOptics::DpchAppData::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfOpticsData");
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
 class PnlIdecScfOptics::DpchAppDo
 ******************************************************************************/

PnlIdecScfOptics::DpchAppDo::DpchAppDo() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECSCFOPTICSDO) {
	ixVDo = 0;
};

string PnlIdecScfOptics::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecScfOptics::DpchAppDo::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecScfOpticsDo");
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
 class PnlIdecScfOptics::DpchEngData
 ******************************************************************************/

PnlIdecScfOptics::DpchEngData::DpchEngData(
			const ubigint jref
			, ContIac* contiac
			, ContInf* continf
			, Feed* feedFPupIsg
			, Feed* feedFPupLsg
			, Feed* feedFPupQsg
			, Feed* feedFPupRsg
			, StatShr* statshr
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSCFOPTICSDATA, jref) {
	if (find(mask, ALL)) this->mask = {JREF, CONTIAC, CONTINF, FEEDFPUPISG, FEEDFPUPLSG, FEEDFPUPQSG, FEEDFPUPRSG, STATAPP, STATSHR, TAG};
	else this->mask = mask;

	if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
	if (find(this->mask, CONTINF) && continf) this->continf = *continf;
	if (find(this->mask, FEEDFPUPISG) && feedFPupIsg) this->feedFPupIsg = *feedFPupIsg;
	if (find(this->mask, FEEDFPUPLSG) && feedFPupLsg) this->feedFPupLsg = *feedFPupLsg;
	if (find(this->mask, FEEDFPUPQSG) && feedFPupQsg) this->feedFPupQsg = *feedFPupQsg;
	if (find(this->mask, FEEDFPUPRSG) && feedFPupRsg) this->feedFPupRsg = *feedFPupRsg;
	if (find(this->mask, STATSHR) && statshr) this->statshr = *statshr;
};

string PnlIdecScfOptics::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
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

void PnlIdecScfOptics::DpchEngData::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngData* src = (DpchEngData*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTIAC)) {contiac = src->contiac; add(CONTIAC);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFPUPISG)) {feedFPupIsg = src->feedFPupIsg; add(FEEDFPUPISG);};
	if (src->has(FEEDFPUPLSG)) {feedFPupLsg = src->feedFPupLsg; add(FEEDFPUPLSG);};
	if (src->has(FEEDFPUPQSG)) {feedFPupQsg = src->feedFPupQsg; add(FEEDFPUPQSG);};
	if (src->has(FEEDFPUPRSG)) {feedFPupRsg = src->feedFPupRsg; add(FEEDFPUPRSG);};
	if (src->has(STATAPP)) add(STATAPP);
	if (src->has(STATSHR)) {statshr = src->statshr; add(STATSHR);};
	if (src->has(TAG)) add(TAG);
};

void PnlIdecScfOptics::DpchEngData::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecScfOpticsData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFPUPISG)) feedFPupIsg.writeXML(wr);
		if (has(FEEDFPUPLSG)) feedFPupLsg.writeXML(wr);
		if (has(FEEDFPUPQSG)) feedFPupQsg.writeXML(wr);
		if (has(FEEDFPUPRSG)) feedFPupRsg.writeXML(wr);
		if (has(STATAPP)) StatApp::writeXML(wr);
		if (has(STATSHR)) statshr.writeXML(wr);
		if (has(TAG)) Tag::writeXML(ixIdecVLocale, wr);
	xmlTextWriterEndElement(wr);
};

