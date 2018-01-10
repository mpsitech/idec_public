/**
  * \file PnlIdecFilList.cpp
  * API code for job PnlIdecFilList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "PnlIdecFilList.h"

/******************************************************************************
 class PnlIdecFilList::VecVDo
 ******************************************************************************/

uint PnlIdecFilList::VecVDo::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "butminimizeclick") return BUTMINIMIZECLICK;
	else if (s == "butregularizeclick") return BUTREGULARIZECLICK;
	else if (s == "butnewclick") return BUTNEWCLICK;
	else if (s == "butdeleteclick") return BUTDELETECLICK;
	else if (s == "butfilterclick") return BUTFILTERCLICK;
	else if (s == "butrefreshclick") return BUTREFRESHCLICK;

	return(0);
};

string PnlIdecFilList::VecVDo::getSref(
			const uint ix
		) {
	if (ix == BUTMINIMIZECLICK) return("ButMinimizeClick");
	else if (ix == BUTREGULARIZECLICK) return("ButRegularizeClick");
	else if (ix == BUTNEWCLICK) return("ButNewClick");
	else if (ix == BUTDELETECLICK) return("ButDeleteClick");
	else if (ix == BUTFILTERCLICK) return("ButFilterClick");
	else if (ix == BUTREFRESHCLICK) return("ButRefreshClick");

	return("");
};

/******************************************************************************
 class PnlIdecFilList::ContIac
 ******************************************************************************/

PnlIdecFilList::ContIac::ContIac(
			const uint numFTos
		) : Block() {
	this->numFTos = numFTos;

	mask = {NUMFTOS};
};

bool PnlIdecFilList::ContIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContIacIdecFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemIacIdecFilList";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFTos", numFTos)) add(NUMFTOS);
	};

	return basefound;
};

void PnlIdecFilList::ContIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "ContIacIdecFilList";

	string itemtag;
	if (shorttags) itemtag = "Ci";
	else itemtag = "ContitemIacIdecFilList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "numFTos", numFTos);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecFilList::ContIac::comm(
			const ContIac* comp
		) {
	set<uint> items;

	if (numFTos == comp->numFTos) insert(items, NUMFTOS);

	return(items);
};

set<uint> PnlIdecFilList::ContIac::diff(
			const ContIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {NUMFTOS};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecFilList::ContInf
 ******************************************************************************/

PnlIdecFilList::ContInf::ContInf(
			const string& TxtFor
			, const string& TxtPre
			, const bool ButFilterOn
			, const uint numFCsiQst
		) : Block() {
	this->TxtFor = TxtFor;
	this->TxtPre = TxtPre;
	this->ButFilterOn = ButFilterOn;
	this->numFCsiQst = numFCsiQst;

	mask = {TXTFOR, TXTPRE, BUTFILTERON, NUMFCSIQST};
};

bool PnlIdecFilList::ContInf::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ContInfIdecFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "ContitemInfIdecFilList";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtFor", TxtFor)) add(TXTFOR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "TxtPre", TxtPre)) add(TXTPRE);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "ButFilterOn", ButFilterOn)) add(BUTFILTERON);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Ci", "sref", "numFCsiQst", numFCsiQst)) add(NUMFCSIQST);
	};

	return basefound;
};

set<uint> PnlIdecFilList::ContInf::comm(
			const ContInf* comp
		) {
	set<uint> items;

	if (TxtFor.compare(comp->TxtFor) == 0) insert(items, TXTFOR);
	if (TxtPre.compare(comp->TxtPre) == 0) insert(items, TXTPRE);
	if (ButFilterOn == comp->ButFilterOn) insert(items, BUTFILTERON);
	if (numFCsiQst == comp->numFCsiQst) insert(items, NUMFCSIQST);

	return(items);
};

set<uint> PnlIdecFilList::ContInf::diff(
			const ContInf* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TXTFOR, TXTPRE, BUTFILTERON, NUMFCSIQST};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecFilList::StatShr
 ******************************************************************************/

PnlIdecFilList::StatShr::StatShr(
			const uint ixIdecVExpstate
			, const bool ButDeleteActive
		) : Block() {
	this->ixIdecVExpstate = ixIdecVExpstate;
	this->ButDeleteActive = ButDeleteActive;

	mask = {IXIDECVEXPSTATE, BUTDELETEACTIVE};
};

bool PnlIdecFilList::StatShr::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVExpstate;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StatShrIdecFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StatitemShrIdecFilList";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVExpstate", srefIxIdecVExpstate)) {
			ixIdecVExpstate = VecIdecVExpstate::getIx(srefIxIdecVExpstate);
			add(IXIDECVEXPSTATE);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ButDeleteActive", ButDeleteActive)) add(BUTDELETEACTIVE);
	};

	return basefound;
};

set<uint> PnlIdecFilList::StatShr::comm(
			const StatShr* comp
		) {
	set<uint> items;

	if (ixIdecVExpstate == comp->ixIdecVExpstate) insert(items, IXIDECVEXPSTATE);
	if (ButDeleteActive == comp->ButDeleteActive) insert(items, BUTDELETEACTIVE);

	return(items);
};

set<uint> PnlIdecFilList::StatShr::diff(
			const StatShr* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVEXPSTATE, BUTDELETEACTIVE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecFilList::StgIac
 ******************************************************************************/

PnlIdecFilList::StgIac::StgIac(
			const uint TcoFnmWidth
			, const uint TcoRetWidth
			, const uint TcoReuWidth
			, const uint TcoCntWidth
			, const uint TcoMimWidth
			, const uint TcoSizWidth
		) : Block() {
	this->TcoFnmWidth = TcoFnmWidth;
	this->TcoRetWidth = TcoRetWidth;
	this->TcoReuWidth = TcoReuWidth;
	this->TcoCntWidth = TcoCntWidth;
	this->TcoMimWidth = TcoMimWidth;
	this->TcoSizWidth = TcoSizWidth;

	mask = {TCOFNMWIDTH, TCORETWIDTH, TCOREUWIDTH, TCOCNTWIDTH, TCOMIMWIDTH, TCOSIZWIDTH};
};

bool PnlIdecFilList::StgIac::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIacIdecFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIacIdecFilList";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TcoFnmWidth", TcoFnmWidth)) add(TCOFNMWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TcoRetWidth", TcoRetWidth)) add(TCORETWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TcoReuWidth", TcoReuWidth)) add(TCOREUWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TcoCntWidth", TcoCntWidth)) add(TCOCNTWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TcoMimWidth", TcoMimWidth)) add(TCOMIMWIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "TcoSizWidth", TcoSizWidth)) add(TCOSIZWIDTH);
	};

	return basefound;
};

void PnlIdecFilList::StgIac::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIacIdecFilList";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIacIdecFilList";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "TcoFnmWidth", TcoFnmWidth);
		writeUintAttr(wr, itemtag, "sref", "TcoRetWidth", TcoRetWidth);
		writeUintAttr(wr, itemtag, "sref", "TcoReuWidth", TcoReuWidth);
		writeUintAttr(wr, itemtag, "sref", "TcoCntWidth", TcoCntWidth);
		writeUintAttr(wr, itemtag, "sref", "TcoMimWidth", TcoMimWidth);
		writeUintAttr(wr, itemtag, "sref", "TcoSizWidth", TcoSizWidth);
	xmlTextWriterEndElement(wr);
};

set<uint> PnlIdecFilList::StgIac::comm(
			const StgIac* comp
		) {
	set<uint> items;

	if (TcoFnmWidth == comp->TcoFnmWidth) insert(items, TCOFNMWIDTH);
	if (TcoRetWidth == comp->TcoRetWidth) insert(items, TCORETWIDTH);
	if (TcoReuWidth == comp->TcoReuWidth) insert(items, TCOREUWIDTH);
	if (TcoCntWidth == comp->TcoCntWidth) insert(items, TCOCNTWIDTH);
	if (TcoMimWidth == comp->TcoMimWidth) insert(items, TCOMIMWIDTH);
	if (TcoSizWidth == comp->TcoSizWidth) insert(items, TCOSIZWIDTH);

	return(items);
};

set<uint> PnlIdecFilList::StgIac::diff(
			const StgIac* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TCOFNMWIDTH, TCORETWIDTH, TCOREUWIDTH, TCOCNTWIDTH, TCOMIMWIDTH, TCOSIZWIDTH};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class PnlIdecFilList::Tag
 ******************************************************************************/

PnlIdecFilList::Tag::Tag(
			const string& Cpt
			, const string& TxtFor
			, const string& Trs
			, const string& TxtShowing1
			, const string& TxtShowing2
			, const string& TcoFnm
			, const string& TcoRet
			, const string& TcoReu
			, const string& TcoCnt
			, const string& TcoMim
			, const string& TcoSiz
		) : Block() {
	this->Cpt = Cpt;
	this->TxtFor = TxtFor;
	this->Trs = Trs;
	this->TxtShowing1 = TxtShowing1;
	this->TxtShowing2 = TxtShowing2;
	this->TcoFnm = TcoFnm;
	this->TcoRet = TcoRet;
	this->TcoReu = TcoReu;
	this->TcoCnt = TcoCnt;
	this->TcoMim = TcoMim;
	this->TcoSiz = TcoSiz;

	mask = {CPT, TXTFOR, TRS, TXTSHOWING1, TXTSHOWING2, TCOFNM, TCORET, TCOREU, TCOCNT, TCOMIM, TCOSIZ};
};

bool PnlIdecFilList::Tag::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "TagIdecFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "TagitemIdecFilList";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Cpt", Cpt)) add(CPT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TxtFor", TxtFor)) add(TXTFOR);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "Trs", Trs)) add(TRS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TxtShowing1", TxtShowing1)) add(TXTSHOWING1);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TxtShowing2", TxtShowing2)) add(TXTSHOWING2);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TcoFnm", TcoFnm)) add(TCOFNM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TcoRet", TcoRet)) add(TCORET);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TcoReu", TcoReu)) add(TCOREU);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TcoCnt", TcoCnt)) add(TCOCNT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TcoMim", TcoMim)) add(TCOMIM);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Ti", "sref", "TcoSiz", TcoSiz)) add(TCOSIZ);
	};

	return basefound;
};

/******************************************************************************
 class PnlIdecFilList::DpchAppData
 ******************************************************************************/

PnlIdecFilList::DpchAppData::DpchAppData(
			const string& scrJref
			, ContIac* contiac
			, StgIac* stgiac
			, QryIdecFilList::StgIac* stgiacqry
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECFILLISTDATA, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, CONTIAC, STGIAC, STGIACQRY};
	else this->mask = mask;

		if (find(this->mask, CONTIAC) && contiac) this->contiac = *contiac;
		if (find(this->mask, STGIAC) && stgiac) this->stgiac = *stgiac;
		if (find(this->mask, STGIACQRY) && stgiacqry) this->stgiacqry = *stgiacqry;
};

string PnlIdecFilList::DpchAppData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(STGIAC)) ss.push_back("stgiac");
	if (has(STGIACQRY)) ss.push_back("stgiacqry");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecFilList::DpchAppData::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecFilListData");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(CONTIAC)) contiac.writeXML(wr);
		if (has(STGIAC)) stgiac.writeXML(wr);
		if (has(STGIACQRY)) stgiacqry.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecFilList::DpchAppDo
 ******************************************************************************/

PnlIdecFilList::DpchAppDo::DpchAppDo(
			const string& scrJref
			, const uint ixVDo
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECFILLISTDO, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, IXVDO};
	else this->mask = mask;

	this->ixVDo = ixVDo;
};

string PnlIdecFilList::DpchAppDo::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(IXVDO)) ss.push_back("ixVDo");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecFilList::DpchAppDo::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppIdecFilListDo");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(IXVDO)) writeString(wr, "srefIxVDo", VecVDo::getSref(ixVDo));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class PnlIdecFilList::DpchEngData
 ******************************************************************************/

PnlIdecFilList::DpchEngData::DpchEngData() : DpchEngIdec(VecIdecVDpch::DPCHENGIDECFILLISTDATA) {
	feedFCsiQst.tag = "FeedFCsiQst";
	feedFTos.tag = "FeedFTos";
};

string PnlIdecFilList::DpchEngData::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(CONTIAC)) ss.push_back("contiac");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFCSIQST)) ss.push_back("feedFCsiQst");
	if (has(FEEDFTOS)) ss.push_back("feedFTos");
	if (has(STATSHR)) ss.push_back("statshr");
	if (has(STGIAC)) ss.push_back("stgiac");
	if (has(TAG)) ss.push_back("tag");
	if (has(RST)) ss.push_back("rst");
	if (has(STATAPPQRY)) ss.push_back("statappqry");
	if (has(STATSHRQRY)) ss.push_back("statshrqry");
	if (has(STGIACQRY)) ss.push_back("stgiacqry");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void PnlIdecFilList::DpchEngData::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchEngIdecFilListData");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) add(SCRJREF);
		if (contiac.readXML(docctx, basexpath, true)) add(CONTIAC);
		if (continf.readXML(docctx, basexpath, true)) add(CONTINF);
		if (feedFCsiQst.readXML(docctx, basexpath, true)) add(FEEDFCSIQST);
		if (feedFTos.readXML(docctx, basexpath, true)) add(FEEDFTOS);
		if (statshr.readXML(docctx, basexpath, true)) add(STATSHR);
		if (stgiac.readXML(docctx, basexpath, true)) add(STGIAC);
		if (tag.readXML(docctx, basexpath, true)) add(TAG);
		if (rst.readXML(docctx, basexpath, true)) add(RST);
		if (statappqry.readXML(docctx, basexpath, true)) add(STATAPPQRY);
		if (statshrqry.readXML(docctx, basexpath, true)) add(STATSHRQRY);
		if (stgiacqry.readXML(docctx, basexpath, true)) add(STGIACQRY);
	} else {
		contiac = ContIac();
		continf = ContInf();
		feedFCsiQst.clear();
		feedFTos.clear();
		statshr = StatShr();
		stgiac = StgIac();
		tag = Tag();
		rst.clear();
		statappqry = QryIdecFilList::StatApp();
		statshrqry = QryIdecFilList::StatShr();
		stgiacqry = QryIdecFilList::StgIac();
	};
};

