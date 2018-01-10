/**
  * \file Idecd.cpp
  * inter-thread exchange object for Idec daemon (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "Idecd.h"

/******************************************************************************
 namespace DpchIdecdAck
 ******************************************************************************/

void DpchIdecdAck::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchIdecdAck");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 namespace DpchIdecdQuit
 ******************************************************************************/

void DpchIdecdQuit::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchIdecdQuit");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 namespace DpchIdecdReg
 ******************************************************************************/

void DpchIdecdReg::writeXML(
			pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
			, const ubigint nref
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchIdecdReg");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		writeString(wr, "scrNref", Scr::scramble(mScr, scr, descr, nref));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DpchIdecopdReg
 ******************************************************************************/

DpchIdecopdReg::DpchIdecopdReg() : DpchIdec(VecIdecVDpch::DPCHIDECOPDREG) {
};

bool DpchIdecopdReg::all(
			const set<uint>& items
		) {
	if (!find(items, PORT)) return false;
	if (!find(items, IXIDECVOPENGTYPE)) return false;
	if (!find(items, OPPRCN)) return false;

	return true;
};

void DpchIdecopdReg::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVOpengtype;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchIdecopdReg");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractUsmallintUclc(docctx, basexpath, "port", "", port)) add(PORT);
		if (extractStringUclc(docctx, basexpath, "srefIxIdecVOpengtype", "", srefIxIdecVOpengtype)) {
			ixIdecVOpengtype = VecIdecVOpengtype::getIx(srefIxIdecVOpengtype);
			add(IXIDECVOPENGTYPE);
		};
		if (extractUsmallintUclc(docctx, basexpath, "opprcn", "", opprcn)) add(OPPRCN);
	};
};

/******************************************************************************
 class DpchIdecopdUnreg
 ******************************************************************************/

DpchIdecopdUnreg::DpchIdecopdUnreg() : DpchIdec(VecIdecVDpch::DPCHIDECOPDUNREG) {
};

bool DpchIdecopdUnreg::all(
			const set<uint>& items
		) {
	if (!find(items, NREF)) return false;

	return true;
};

void DpchIdecopdUnreg::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	string scrNref;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchIdecopdUnreg");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrNref", "", scrNref)) {
			nref = Scr::descramble(mScr, descr, scrNref);
			add(NREF);
		};
	};
};

/******************************************************************************
 class DpchAppIdec
 ******************************************************************************/

DpchAppIdec::DpchAppIdec(
			const uint ixIdecVDpch
		) : DpchIdec(ixIdecVDpch) {
	jref = 0;
};

DpchAppIdec::~DpchAppIdec() {
};

bool DpchAppIdec::all(
			const set<uint>& items
		) {
	if (!find(items, JREF)) return false;

	return true;
};

string DpchAppIdec::getSrefsMask() {
	if (has(JREF)) return("jref");
	else return("");
};

void DpchAppIdec::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	string scrJref;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, VecIdecVDpch::getSref(ixIdecVDpch));
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) {
			jref = Scr::descramble(mScr, descr, scrJref);
			add(JREF);
		};
	};
};

/******************************************************************************
 class DpchAppIdecAlert
 ******************************************************************************/

DpchAppIdecAlert::DpchAppIdecAlert() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECALERT) {
};

bool DpchAppIdecAlert::all(
			const set<uint>& items
		) {
	if (!find(items, JREF)) return false;
	if (!find(items, NUMFMCB)) return false;

	return true;
};

string DpchAppIdecAlert::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(NUMFMCB)) ss.push_back("numFMcb");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DpchAppIdecAlert::readXML(
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
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppIdecAlert");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) {
			jref = Scr::descramble(mScr, descr, scrJref);
			add(JREF);
		};
		if (extractUintUclc(docctx, basexpath, "numFMcb", "", numFMcb)) add(NUMFMCB);
	} else {
	};
};

/******************************************************************************
 class DpchAppIdecInit
 ******************************************************************************/

DpchAppIdecInit::DpchAppIdecInit() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECINIT) {
};

/******************************************************************************
 class DpchAppIdecResume
 ******************************************************************************/

DpchAppIdecResume::DpchAppIdecResume() : DpchAppIdec(VecIdecVDpch::DPCHAPPIDECRESUME) {
};

/******************************************************************************
 class DpchEngIdec
 ******************************************************************************/

DpchEngIdec::DpchEngIdec(
			const uint ixIdecVDpch
			, const ubigint jref
		) : DpchIdec(ixIdecVDpch) {
	this->jref = jref;

	mask = {JREF};
};

DpchEngIdec::~DpchEngIdec() {
};

bool DpchEngIdec::all(
			const set<uint>& items
		) {
	if (!find(items, JREF)) return false;

	return true;
};

string DpchEngIdec::getSrefsMask() {
	if (has(JREF)) return("jref");
	else return("");
};

void DpchEngIdec::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngIdec* src = dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
};

void DpchEngIdec::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	string tag = VecIdecVDpch::getSref(ixIdecVDpch);

	xmlTextWriterStartElement(wr, BAD_CAST tag.c_str());
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DpchEngIdecAck
 ******************************************************************************/

DpchEngIdecAck::DpchEngIdecAck(
			const ubigint jref
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECACK, jref) {
};

/******************************************************************************
 class DpchEngIdecAlert
 ******************************************************************************/

DpchEngIdecAlert::DpchEngIdecAlert(
			const ubigint jref
			, ContInfIdecAlert* continf
			, Feed* feedFMcb
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECALERT, jref) {
	if (continf) this->continf = *continf;
	if (feedFMcb) this->feedFMcb = *feedFMcb;

	if (find(mask, ALL)) this->mask = {JREF, CONTINF, FEEDFMCB};
	else this->mask = mask;
};

bool DpchEngIdecAlert::all(
			const set<uint>& items
		) {
	if (!find(items, JREF)) return false;
	if (!find(items, CONTINF)) return false;
	if (!find(items, FEEDFMCB)) return false;

	return true;
};

string DpchEngIdecAlert::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(CONTINF)) ss.push_back("continf");
	if (has(FEEDFMCB)) ss.push_back("feedFMcb");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DpchEngIdecAlert::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngIdecAlert* src = (DpchEngIdecAlert*) dpcheng;

	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(CONTINF)) {continf = src->continf; add(CONTINF);};
	if (src->has(FEEDFMCB)) {feedFMcb = src->feedFMcb; add(FEEDFMCB);};
};

void DpchEngIdecAlert::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecAlert");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(CONTINF)) continf.writeXML(wr);
		if (has(FEEDFMCB)) feedFMcb.writeXML(wr);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DpchEngIdecConfirm
 ******************************************************************************/

DpchEngIdecConfirm::DpchEngIdecConfirm(
			const bool accepted
			, const ubigint jref
			, const string& sref
			, const set<uint>& mask
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECCONFIRM, jref) {
	this->accepted = accepted;
	this->jref = jref;
	this->sref = sref;

	if (find(mask, ALL)) this->mask = {ACCEPTED, JREF, SREF};
	else this->mask = mask;
};

bool DpchEngIdecConfirm::all(
			const set<uint>& items
		) {
	if (!find(items, ACCEPTED)) return false;
	if (!find(items, JREF)) return false;
	if (!find(items, SREF)) return false;

	return true;
};

string DpchEngIdecConfirm::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(ACCEPTED)) ss.push_back("accepted");
	if (has(JREF)) ss.push_back("jref");
	if (has(SREF)) ss.push_back("sref");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void DpchEngIdecConfirm::merge(
			DpchEngIdec* dpcheng
		) {
	DpchEngIdecConfirm* src = (DpchEngIdecConfirm*) dpcheng;

	if (src->has(ACCEPTED)) {accepted = src->accepted; add(ACCEPTED);};
	if (src->has(JREF)) {jref = src->jref; add(JREF);};
	if (src->has(SREF)) {sref = src->sref; add(SREF);};
};

void DpchEngIdecConfirm::writeXML(
			const uint ixIdecVLocale
			, pthread_mutex_t* mScr
			, map<ubigint,string>& scr
			, map<string,ubigint>& descr
			, xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchEngIdecConfirm");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(ACCEPTED)) writeBool(wr, "accepted", accepted);
		if (has(JREF)) writeString(wr, "scrJref", Scr::scramble(mScr, scr, descr, jref));
		if (has(SREF)) writeString(wr, "sref", sref);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class DpchEngIdecSuspend
 ******************************************************************************/

DpchEngIdecSuspend::DpchEngIdecSuspend(
			const ubigint jref
		) : DpchEngIdec(VecIdecVDpch::DPCHENGIDECSUSPEND, jref) {
};

/******************************************************************************
 class StgIdecd
 ******************************************************************************/

StgIdecd::StgIdecd(
			const usmallint jobprcn
			, const usmallint opengsrvport
			, const usmallint appsrvport
			, const bool https
			, const usmallint histlength
		) : Block() {
	this->jobprcn = jobprcn;
	this->opengsrvport = opengsrvport;
	this->appsrvport = appsrvport;
	this->https = https;
	this->histlength = histlength;
	mask = {JOBPRCN, OPENGSRVPORT, APPSRVPORT, HTTPS, HISTLENGTH};
};

bool StgIdecd::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecd");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecd";

	if (basefound) {
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "jobprcn", jobprcn)) add(JOBPRCN);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "opengsrvport", opengsrvport)) add(OPENGSRVPORT);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "appsrvport", appsrvport)) add(APPSRVPORT);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "https", https)) add(HTTPS);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "histlength", histlength)) add(HISTLENGTH);
	};

	return basefound;
};

void StgIdecd::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecd";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIdecd";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUsmallintAttr(wr, itemtag, "sref", "jobprcn", jobprcn);
		writeUsmallintAttr(wr, itemtag, "sref", "opengsrvport", opengsrvport);
		writeUsmallintAttr(wr, itemtag, "sref", "appsrvport", appsrvport);
		writeBoolAttr(wr, itemtag, "sref", "https", https);
		writeUsmallintAttr(wr, itemtag, "sref", "histlength", histlength);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecd::comm(
			const StgIdecd* comp
		) {
	set<uint> items;

	if (jobprcn == comp->jobprcn) insert(items, JOBPRCN);
	if (opengsrvport == comp->opengsrvport) insert(items, OPENGSRVPORT);
	if (appsrvport == comp->appsrvport) insert(items, APPSRVPORT);
	if (https == comp->https) insert(items, HTTPS);
	if (histlength == comp->histlength) insert(items, HISTLENGTH);

	return(items);
};

set<uint> StgIdecd::diff(
			const StgIdecd* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {JOBPRCN, OPENGSRVPORT, APPSRVPORT, HTTPS, HISTLENGTH};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgIdecDatabase
 ******************************************************************************/

StgIdecDatabase::StgIdecDatabase(
			const uint ixDbsVDbstype
			, const string& dbspath
			, const string& dbsname
			, const string& username
			, const string& password
			, const string& ip
			, const usmallint port
		) : Block() {
	this->ixDbsVDbstype = ixDbsVDbstype;
	this->dbspath = dbspath;
	this->dbsname = dbsname;
	this->username = username;
	this->password = password;
	this->ip = ip;
	this->port = port;
	mask = {IXDBSVDBSTYPE, DBSPATH, DBSNAME, USERNAME, PASSWORD, IP, PORT};
};

bool StgIdecDatabase::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxDbsVDbstype;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecDatabase");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecDatabase";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxDbsVDbstype", srefIxDbsVDbstype)) {
			ixDbsVDbstype = VecDbsVDbstype::getIx(srefIxDbsVDbstype);
			add(IXDBSVDBSTYPE);
		};
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dbspath", dbspath)) add(DBSPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dbsname", dbsname)) add(DBSNAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "username", username)) add(USERNAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "password", password)) add(PASSWORD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ip", ip)) add(IP);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "port", port)) add(PORT);
	};

	return basefound;
};

void StgIdecDatabase::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecDatabase";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIdecDatabase";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxDbsVDbstype", VecDbsVDbstype::getSref(ixDbsVDbstype));
		writeStringAttr(wr, itemtag, "sref", "dbspath", dbspath);
		writeStringAttr(wr, itemtag, "sref", "dbsname", dbsname);
		writeStringAttr(wr, itemtag, "sref", "username", username);
		writeStringAttr(wr, itemtag, "sref", "password", password);
		writeStringAttr(wr, itemtag, "sref", "ip", ip);
		writeUsmallintAttr(wr, itemtag, "sref", "port", port);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecDatabase::comm(
			const StgIdecDatabase* comp
		) {
	set<uint> items;

	if (ixDbsVDbstype == comp->ixDbsVDbstype) insert(items, IXDBSVDBSTYPE);
	if (dbspath == comp->dbspath) insert(items, DBSPATH);
	if (dbsname == comp->dbsname) insert(items, DBSNAME);
	if (username == comp->username) insert(items, USERNAME);
	if (password == comp->password) insert(items, PASSWORD);
	if (ip == comp->ip) insert(items, IP);
	if (port == comp->port) insert(items, PORT);

	return(items);
};

set<uint> StgIdecDatabase::diff(
			const StgIdecDatabase* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXDBSVDBSTYPE, DBSPATH, DBSNAME, USERNAME, PASSWORD, IP, PORT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgIdecGeneral
 ******************************************************************************/

StgIdecGeneral::StgIdecGeneral(
			const uint ixIdecVStled
			, const bool dummy
		) : Block() {
	this->ixIdecVStled = ixIdecVStled;
	this->dummy = dummy;
	mask = {IXIDECVSTLED, DUMMY};
};

bool StgIdecGeneral::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVStled;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecGeneral");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecGeneral";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVStled", srefIxIdecVStled)) {
			ixIdecVStled = VecIdecVStled::getIx(srefIxIdecVStled);
			add(IXIDECVSTLED);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dummy", dummy)) add(DUMMY);
	};

	return basefound;
};

void StgIdecGeneral::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecGeneral";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIdecGeneral";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVStled", VecIdecVStled::getSref(ixIdecVStled));
		writeBoolAttr(wr, itemtag, "sref", "dummy", dummy);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecGeneral::comm(
			const StgIdecGeneral* comp
		) {
	set<uint> items;

	if (ixIdecVStled == comp->ixIdecVStled) insert(items, IXIDECVSTLED);
	if (dummy == comp->dummy) insert(items, DUMMY);

	return(items);
};

set<uint> StgIdecGeneral::diff(
			const StgIdecGeneral* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVSTLED, DUMMY};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgIdecHardware
 ******************************************************************************/

StgIdecHardware::StgIdecHardware(
			const uint ixIdecVSystem
			, const utinyint Nretry
			, const double dtpoll
			, const string& path
			, const uint bps
			, const string& logpath
		) : Block() {
	this->ixIdecVSystem = ixIdecVSystem;
	this->Nretry = Nretry;
	this->dtpoll = dtpoll;
	this->path = path;
	this->bps = bps;
	this->logpath = logpath;
	mask = {IXIDECVSYSTEM, NRETRY, DTPOLL, PATH, BPS, LOGPATH};
};

bool StgIdecHardware::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVSystem;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecHardware");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecHardware";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVSystem", srefIxIdecVSystem)) {
			ixIdecVSystem = VecIdecVSystem::getIx(srefIxIdecVSystem);
			add(IXIDECVSYSTEM);
		};
		if (extractUtinyintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Nretry", Nretry)) add(NRETRY);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dtpoll", dtpoll)) add(DTPOLL);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "path", path)) add(PATH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "bps", bps)) add(BPS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "logpath", logpath)) add(LOGPATH);
	};

	return basefound;
};

void StgIdecHardware::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecHardware";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIdecHardware";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVSystem", VecIdecVSystem::getSref(ixIdecVSystem));
		writeUtinyintAttr(wr, itemtag, "sref", "Nretry", Nretry);
		writeDoubleAttr(wr, itemtag, "sref", "dtpoll", dtpoll);
		writeStringAttr(wr, itemtag, "sref", "path", path);
		writeUintAttr(wr, itemtag, "sref", "bps", bps);
		writeStringAttr(wr, itemtag, "sref", "logpath", logpath);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecHardware::comm(
			const StgIdecHardware* comp
		) {
	set<uint> items;

	if (ixIdecVSystem == comp->ixIdecVSystem) insert(items, IXIDECVSYSTEM);
	if (Nretry == comp->Nretry) insert(items, NRETRY);
	if (compareDouble(dtpoll, comp->dtpoll) < 1.0e-4) insert(items, DTPOLL);
	if (path == comp->path) insert(items, PATH);
	if (bps == comp->bps) insert(items, BPS);
	if (logpath == comp->logpath) insert(items, LOGPATH);

	return(items);
};

set<uint> StgIdecHardware::diff(
			const StgIdecHardware* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVSYSTEM, NRETRY, DTPOLL, PATH, BPS, LOGPATH};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgIdecMonitor
 ******************************************************************************/

StgIdecMonitor::StgIdecMonitor(
			const string& username
			, const string& password
			, const string& ip
			, const usmallint port
			, const uint ixDbsVDbstype
			, const string& dbspath
			, const string& dbsname
			, const string& dbsusername
			, const string& dbspassword
		) : Block() {
	this->username = username;
	this->password = password;
	this->ip = ip;
	this->port = port;
	this->ixDbsVDbstype = ixDbsVDbstype;
	this->dbspath = dbspath;
	this->dbsname = dbsname;
	this->dbsusername = dbsusername;
	this->dbspassword = dbspassword;
	mask = {USERNAME, PASSWORD, IP, PORT, IXDBSVDBSTYPE, DBSPATH, DBSNAME, DBSUSERNAME, DBSPASSWORD};
};

bool StgIdecMonitor::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxDbsVDbstype;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecMonitor");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecMonitor";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "username", username)) add(USERNAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "password", password)) add(PASSWORD);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ip", ip)) add(IP);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "port", port)) add(PORT);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxDbsVDbstype", srefIxDbsVDbstype)) {
			ixDbsVDbstype = VecDbsVDbstype::getIx(srefIxDbsVDbstype);
			add(IXDBSVDBSTYPE);
		};
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dbspath", dbspath)) add(DBSPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dbsname", dbsname)) add(DBSNAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dbsusername", dbsusername)) add(DBSUSERNAME);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dbspassword", dbspassword)) add(DBSPASSWORD);
	};

	return basefound;
};

void StgIdecMonitor::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecMonitor";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIdecMonitor";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "username", username);
		writeStringAttr(wr, itemtag, "sref", "password", password);
		writeStringAttr(wr, itemtag, "sref", "ip", ip);
		writeUsmallintAttr(wr, itemtag, "sref", "port", port);
		writeStringAttr(wr, itemtag, "sref", "srefIxDbsVDbstype", VecDbsVDbstype::getSref(ixDbsVDbstype));
		writeStringAttr(wr, itemtag, "sref", "dbspath", dbspath);
		writeStringAttr(wr, itemtag, "sref", "dbsname", dbsname);
		writeStringAttr(wr, itemtag, "sref", "dbsusername", dbsusername);
		writeStringAttr(wr, itemtag, "sref", "dbspassword", dbspassword);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecMonitor::comm(
			const StgIdecMonitor* comp
		) {
	set<uint> items;

	if (username == comp->username) insert(items, USERNAME);
	if (password == comp->password) insert(items, PASSWORD);
	if (ip == comp->ip) insert(items, IP);
	if (port == comp->port) insert(items, PORT);
	if (ixDbsVDbstype == comp->ixDbsVDbstype) insert(items, IXDBSVDBSTYPE);
	if (dbspath == comp->dbspath) insert(items, DBSPATH);
	if (dbsname == comp->dbsname) insert(items, DBSNAME);
	if (dbsusername == comp->dbsusername) insert(items, DBSUSERNAME);
	if (dbspassword == comp->dbspassword) insert(items, DBSPASSWORD);

	return(items);
};

set<uint> StgIdecMonitor::diff(
			const StgIdecMonitor* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {USERNAME, PASSWORD, IP, PORT, IXDBSVDBSTYPE, DBSPATH, DBSNAME, DBSUSERNAME, DBSPASSWORD};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgIdecPath
 ******************************************************************************/

StgIdecPath::StgIdecPath(
			const string& acvpath
			, const string& keypath
			, const string& monpath
			, const string& tmppath
			, const string& webpath
			, const string& helpurl
		) : Block() {
	this->acvpath = acvpath;
	this->keypath = keypath;
	this->monpath = monpath;
	this->tmppath = tmppath;
	this->webpath = webpath;
	this->helpurl = helpurl;
	mask = {ACVPATH, KEYPATH, MONPATH, TMPPATH, WEBPATH, HELPURL};
};

bool StgIdecPath::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgIdecPath");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemIdecPath";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "acvpath", acvpath)) add(ACVPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "keypath", keypath)) add(KEYPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "monpath", monpath)) add(MONPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tmppath", tmppath)) add(TMPPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "webpath", webpath)) add(WEBPATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "helpurl", helpurl)) add(HELPURL);
	};

	return basefound;
};

void StgIdecPath::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgIdecPath";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemIdecPath";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "acvpath", acvpath);
		writeStringAttr(wr, itemtag, "sref", "keypath", keypath);
		writeStringAttr(wr, itemtag, "sref", "monpath", monpath);
		writeStringAttr(wr, itemtag, "sref", "tmppath", tmppath);
		writeStringAttr(wr, itemtag, "sref", "webpath", webpath);
		writeStringAttr(wr, itemtag, "sref", "helpurl", helpurl);
	xmlTextWriterEndElement(wr);
};

set<uint> StgIdecPath::comm(
			const StgIdecPath* comp
		) {
	set<uint> items;

	if (acvpath == comp->acvpath) insert(items, ACVPATH);
	if (keypath == comp->keypath) insert(items, KEYPATH);
	if (monpath == comp->monpath) insert(items, MONPATH);
	if (tmppath == comp->tmppath) insert(items, TMPPATH);
	if (webpath == comp->webpath) insert(items, WEBPATH);
	if (helpurl == comp->helpurl) insert(items, HELPURL);

	return(items);
};

set<uint> StgIdecPath::diff(
			const StgIdecPath* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {ACVPATH, KEYPATH, MONPATH, TMPPATH, WEBPATH, HELPURL};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecFusion
 ******************************************************************************/

StgJobIdecFusion::StgJobIdecFusion(
			const uint tcalib
			, const double dxlwir
			, const double dylwir
			, const double dthetalwir
			, const double dphilwir
		) : Block() {
	this->tcalib = tcalib;
	this->dxlwir = dxlwir;
	this->dylwir = dylwir;
	this->dthetalwir = dthetalwir;
	this->dphilwir = dphilwir;
	mask = {TCALIB, DXLWIR, DYLWIR, DTHETALWIR, DPHILWIR};
};

bool StgJobIdecFusion::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecFusion");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecFusion";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tcalib", tcalib)) add(TCALIB);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dxlwir", dxlwir)) add(DXLWIR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dylwir", dylwir)) add(DYLWIR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dthetalwir", dthetalwir)) add(DTHETALWIR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dphilwir", dphilwir)) add(DPHILWIR);
	};

	return basefound;
};

void StgJobIdecFusion::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecFusion";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecFusion";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "tcalib", tcalib);
		writeDoubleAttr(wr, itemtag, "sref", "dxlwir", dxlwir);
		writeDoubleAttr(wr, itemtag, "sref", "dylwir", dylwir);
		writeDoubleAttr(wr, itemtag, "sref", "dthetalwir", dthetalwir);
		writeDoubleAttr(wr, itemtag, "sref", "dphilwir", dphilwir);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecFusion::comm(
			const StgJobIdecFusion* comp
		) {
	set<uint> items;

	if (tcalib == comp->tcalib) insert(items, TCALIB);
	if (compareDouble(dxlwir, comp->dxlwir) < 1.0e-4) insert(items, DXLWIR);
	if (compareDouble(dylwir, comp->dylwir) < 1.0e-4) insert(items, DYLWIR);
	if (compareDouble(dthetalwir, comp->dthetalwir) < 1.0e-4) insert(items, DTHETALWIR);
	if (compareDouble(dphilwir, comp->dphilwir) < 1.0e-4) insert(items, DPHILWIR);

	return(items);
};

set<uint> StgJobIdecFusion::diff(
			const StgJobIdecFusion* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TCALIB, DXLWIR, DYLWIR, DTHETALWIR, DPHILWIR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecIllum
 ******************************************************************************/

StgJobIdecIllum::StgJobIdecIllum(
			const uint fldIxIdecVPort
			, const uint sptIxIdecVPort
		) : Block() {
	this->fldIxIdecVPort = fldIxIdecVPort;
	this->sptIxIdecVPort = sptIxIdecVPort;
	mask = {FLDIXIDECVPORT, SPTIXIDECVPORT};
};

bool StgJobIdecIllum::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefFldIxIdecVPort;
	string srefSptIxIdecVPort;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecIllum");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecIllum";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefFldIxIdecVPort", srefFldIxIdecVPort)) {
			fldIxIdecVPort = VecIdecVPort::getIx(srefFldIxIdecVPort);
			add(FLDIXIDECVPORT);
		};
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefSptIxIdecVPort", srefSptIxIdecVPort)) {
			sptIxIdecVPort = VecIdecVPort::getIx(srefSptIxIdecVPort);
			add(SPTIXIDECVPORT);
		};
	};

	return basefound;
};

void StgJobIdecIllum::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecIllum";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecIllum";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefFldIxIdecVPort", VecIdecVPort::getSref(fldIxIdecVPort));
		writeStringAttr(wr, itemtag, "sref", "srefSptIxIdecVPort", VecIdecVPort::getSref(sptIxIdecVPort));
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecIllum::comm(
			const StgJobIdecIllum* comp
		) {
	set<uint> items;

	if (fldIxIdecVPort == comp->fldIxIdecVPort) insert(items, FLDIXIDECVPORT);
	if (sptIxIdecVPort == comp->sptIxIdecVPort) insert(items, SPTIXIDECVPORT);

	return(items);
};

set<uint> StgJobIdecIllum::diff(
			const StgJobIdecIllum* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {FLDIXIDECVPORT, SPTIXIDECVPORT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecLwiracq
 ******************************************************************************/

StgJobIdecLwiracq::StgJobIdecLwiracq(
			const uint ixIdecVCamtype
			, const double lam0
			, const double lam1
			, const uint width
			, const uint height
			, const double hpix
			, const string& serno
			, const double a
			, const double b
			, const double dS
			, const double dT
			, const vector<usmallint>& iplTTvsSSx
			, const vector<double>& iplTTvsSSy
			, const uint ixIdecVSqrgrp
			, const double f
			, const double fn
			, const double k1
			, const double k2
			, const double p1
			, const double p2
			, const double k3
			, const double k4
			, const double k5
			, const double k6
		) : Block() {
	this->ixIdecVCamtype = ixIdecVCamtype;
	this->lam0 = lam0;
	this->lam1 = lam1;
	this->width = width;
	this->height = height;
	this->hpix = hpix;
	this->serno = serno;
	this->a = a;
	this->b = b;
	this->dS = dS;
	this->dT = dT;
	this->iplTTvsSSx = iplTTvsSSx;
	this->iplTTvsSSy = iplTTvsSSy;
	this->ixIdecVSqrgrp = ixIdecVSqrgrp;
	this->f = f;
	this->fn = fn;
	this->k1 = k1;
	this->k2 = k2;
	this->p1 = p1;
	this->p2 = p2;
	this->k3 = k3;
	this->k4 = k4;
	this->k5 = k5;
	this->k6 = k6;
	mask = {IXIDECVCAMTYPE, LAM0, LAM1, WIDTH, HEIGHT, HPIX, SERNO, A, B, DS, DT, IPLTTVSSSX, IPLTTVSSSY, IXIDECVSQRGRP, F, FN, K1, K2, P1, P2, K3, K4, K5, K6};
};

bool StgJobIdecLwiracq::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVCamtype;
	string srefIxIdecVSqrgrp;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecLwiracq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecLwiracq";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVCamtype", srefIxIdecVCamtype)) {
			ixIdecVCamtype = VecIdecVCamtype::getIx(srefIxIdecVCamtype);
			add(IXIDECVCAMTYPE);
		};
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "lam0", lam0)) add(LAM0);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "lam1", lam1)) add(LAM1);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "width", width)) add(WIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "height", height)) add(HEIGHT);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "hpix", hpix)) add(HPIX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "serno", serno)) add(SERNO);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "a", a)) add(A);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "b", b)) add(B);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dS", dS)) add(DS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dT", dT)) add(DT);
		if (extractUsmallintvecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "iplTTvsSSx", iplTTvsSSx)) add(IPLTTVSSSX);
		if (extractDoublevecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "iplTTvsSSy", iplTTvsSSy)) add(IPLTTVSSSY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVSqrgrp", srefIxIdecVSqrgrp)) {
			ixIdecVSqrgrp = VecIdecVSqrgrp::getIx(srefIxIdecVSqrgrp);
			add(IXIDECVSQRGRP);
		};
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "f", f)) add(F);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "fn", fn)) add(FN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k1", k1)) add(K1);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k2", k2)) add(K2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "p1", p1)) add(P1);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "p2", p2)) add(P2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k3", k3)) add(K3);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k4", k4)) add(K4);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k5", k5)) add(K5);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k6", k6)) add(K6);
	};

	return basefound;
};

void StgJobIdecLwiracq::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecLwiracq";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecLwiracq";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVCamtype", VecIdecVCamtype::getSref(ixIdecVCamtype));
		writeDoubleAttr(wr, itemtag, "sref", "lam0", lam0);
		writeDoubleAttr(wr, itemtag, "sref", "lam1", lam1);
		writeUintAttr(wr, itemtag, "sref", "width", width);
		writeUintAttr(wr, itemtag, "sref", "height", height);
		writeDoubleAttr(wr, itemtag, "sref", "hpix", hpix);
		writeStringAttr(wr, itemtag, "sref", "serno", serno);
		writeDoubleAttr(wr, itemtag, "sref", "a", a);
		writeDoubleAttr(wr, itemtag, "sref", "b", b);
		writeDoubleAttr(wr, itemtag, "sref", "dS", dS);
		writeDoubleAttr(wr, itemtag, "sref", "dT", dT);
		writeUsmallintvecAttr(wr, itemtag, "sref", "iplTTvsSSx", iplTTvsSSx);
		writeDoublevecAttr(wr, itemtag, "sref", "iplTTvsSSy", iplTTvsSSy);
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVSqrgrp", VecIdecVSqrgrp::getSref(ixIdecVSqrgrp));
		writeDoubleAttr(wr, itemtag, "sref", "f", f);
		writeDoubleAttr(wr, itemtag, "sref", "fn", fn);
		writeDoubleAttr(wr, itemtag, "sref", "k1", k1);
		writeDoubleAttr(wr, itemtag, "sref", "k2", k2);
		writeDoubleAttr(wr, itemtag, "sref", "p1", p1);
		writeDoubleAttr(wr, itemtag, "sref", "p2", p2);
		writeDoubleAttr(wr, itemtag, "sref", "k3", k3);
		writeDoubleAttr(wr, itemtag, "sref", "k4", k4);
		writeDoubleAttr(wr, itemtag, "sref", "k5", k5);
		writeDoubleAttr(wr, itemtag, "sref", "k6", k6);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecLwiracq::comm(
			const StgJobIdecLwiracq* comp
		) {
	set<uint> items;

	if (ixIdecVCamtype == comp->ixIdecVCamtype) insert(items, IXIDECVCAMTYPE);
	if (compareDouble(lam0, comp->lam0) < 1.0e-4) insert(items, LAM0);
	if (compareDouble(lam1, comp->lam1) < 1.0e-4) insert(items, LAM1);
	if (width == comp->width) insert(items, WIDTH);
	if (height == comp->height) insert(items, HEIGHT);
	if (compareDouble(hpix, comp->hpix) < 1.0e-4) insert(items, HPIX);
	if (serno == comp->serno) insert(items, SERNO);
	if (compareDouble(a, comp->a) < 1.0e-4) insert(items, A);
	if (compareDouble(b, comp->b) < 1.0e-4) insert(items, B);
	if (compareDouble(dS, comp->dS) < 1.0e-4) insert(items, DS);
	if (compareDouble(dT, comp->dT) < 1.0e-4) insert(items, DT);
	if (compareUsmallintvec(iplTTvsSSx, comp->iplTTvsSSx)) insert(items, IPLTTVSSSX);
	if (compareDoublevec(iplTTvsSSy, comp->iplTTvsSSy) < 1.0e-4) insert(items, IPLTTVSSSY);
	if (ixIdecVSqrgrp == comp->ixIdecVSqrgrp) insert(items, IXIDECVSQRGRP);
	if (compareDouble(f, comp->f) < 1.0e-4) insert(items, F);
	if (compareDouble(fn, comp->fn) < 1.0e-4) insert(items, FN);
	if (compareDouble(k1, comp->k1) < 1.0e-4) insert(items, K1);
	if (compareDouble(k2, comp->k2) < 1.0e-4) insert(items, K2);
	if (compareDouble(p1, comp->p1) < 1.0e-4) insert(items, P1);
	if (compareDouble(p2, comp->p2) < 1.0e-4) insert(items, P2);
	if (compareDouble(k3, comp->k3) < 1.0e-4) insert(items, K3);
	if (compareDouble(k4, comp->k4) < 1.0e-4) insert(items, K4);
	if (compareDouble(k5, comp->k5) < 1.0e-4) insert(items, K5);
	if (compareDouble(k6, comp->k6) < 1.0e-4) insert(items, K6);

	return(items);
};

set<uint> StgJobIdecLwiracq::diff(
			const StgJobIdecLwiracq* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVCAMTYPE, LAM0, LAM1, WIDTH, HEIGHT, HPIX, SERNO, A, B, DS, DT, IPLTTVSSSX, IPLTTVSSSY, IXIDECVSQRGRP, F, FN, K1, K2, P1, P2, K3, K4, K5, K6};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecMechctl
 ******************************************************************************/

StgJobIdecMechctl::StgJobIdecMechctl(
			const uint ixVXlorient
		) : Block() {
	this->ixVXlorient = ixVXlorient;
	mask = {IXVXLORIENT};
};

bool StgJobIdecMechctl::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxVXlorient;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecMechctl");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecMechctl";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxVXlorient", srefIxVXlorient)) {
			ixVXlorient = VecVJobIdecMechctlXlorient::getIx(srefIxVXlorient);
			add(IXVXLORIENT);
		};
	};

	return basefound;
};

void StgJobIdecMechctl::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecMechctl";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecMechctl";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxVXlorient", VecVJobIdecMechctlXlorient::getSref(ixVXlorient));
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecMechctl::comm(
			const StgJobIdecMechctl* comp
		) {
	set<uint> items;

	if (ixVXlorient == comp->ixVXlorient) insert(items, IXVXLORIENT);

	return(items);
};

set<uint> StgJobIdecMechctl::diff(
			const StgJobIdecMechctl* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXVXLORIENT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecMechctlPhi
 ******************************************************************************/

StgJobIdecMechctlPhi::StgJobIdecMechctlPhi(
			const uint ixIdecVPort
			, const utinyint tpr
			, const uint tcalib
			, const usmallint gr
			, const double Ox
			, const double Oy
			, const double Axm
			, const double Aym
			, const double phix
			, const double phiy
			, const double llim
			, const double ulim
			, const usmallint tstep
		) : Block() {
	this->ixIdecVPort = ixIdecVPort;
	this->tpr = tpr;
	this->tcalib = tcalib;
	this->gr = gr;
	this->Ox = Ox;
	this->Oy = Oy;
	this->Axm = Axm;
	this->Aym = Aym;
	this->phix = phix;
	this->phiy = phiy;
	this->llim = llim;
	this->ulim = ulim;
	this->tstep = tstep;
	mask = {IXIDECVPORT, TPR, TCALIB, GR, OX, OY, AXM, AYM, PHIX, PHIY, LLIM, ULIM, TSTEP};
};

bool StgJobIdecMechctlPhi::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVPort;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecMechctlPhi");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecMechctlPhi";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVPort", srefIxIdecVPort)) {
			ixIdecVPort = VecIdecVPort::getIx(srefIxIdecVPort);
			add(IXIDECVPORT);
		};
		if (extractUtinyintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tpr", tpr)) add(TPR);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tcalib", tcalib)) add(TCALIB);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "gr", gr)) add(GR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Ox", Ox)) add(OX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Oy", Oy)) add(OY);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Axm", Axm)) add(AXM);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Aym", Aym)) add(AYM);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "phix", phix)) add(PHIX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "phiy", phiy)) add(PHIY);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "llim", llim)) add(LLIM);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ulim", ulim)) add(ULIM);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tstep", tstep)) add(TSTEP);
	};

	return basefound;
};

void StgJobIdecMechctlPhi::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecMechctlPhi";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecMechctlPhi";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVPort", VecIdecVPort::getSref(ixIdecVPort));
		writeUtinyintAttr(wr, itemtag, "sref", "tpr", tpr);
		writeUintAttr(wr, itemtag, "sref", "tcalib", tcalib);
		writeUsmallintAttr(wr, itemtag, "sref", "gr", gr);
		writeDoubleAttr(wr, itemtag, "sref", "Ox", Ox);
		writeDoubleAttr(wr, itemtag, "sref", "Oy", Oy);
		writeDoubleAttr(wr, itemtag, "sref", "Axm", Axm);
		writeDoubleAttr(wr, itemtag, "sref", "Aym", Aym);
		writeDoubleAttr(wr, itemtag, "sref", "phix", phix);
		writeDoubleAttr(wr, itemtag, "sref", "phiy", phiy);
		writeDoubleAttr(wr, itemtag, "sref", "llim", llim);
		writeDoubleAttr(wr, itemtag, "sref", "ulim", ulim);
		writeUsmallintAttr(wr, itemtag, "sref", "tstep", tstep);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecMechctlPhi::comm(
			const StgJobIdecMechctlPhi* comp
		) {
	set<uint> items;

	if (ixIdecVPort == comp->ixIdecVPort) insert(items, IXIDECVPORT);
	if (tpr == comp->tpr) insert(items, TPR);
	if (tcalib == comp->tcalib) insert(items, TCALIB);
	if (gr == comp->gr) insert(items, GR);
	if (compareDouble(Ox, comp->Ox) < 1.0e-4) insert(items, OX);
	if (compareDouble(Oy, comp->Oy) < 1.0e-4) insert(items, OY);
	if (compareDouble(Axm, comp->Axm) < 1.0e-4) insert(items, AXM);
	if (compareDouble(Aym, comp->Aym) < 1.0e-4) insert(items, AYM);
	if (compareDouble(phix, comp->phix) < 1.0e-4) insert(items, PHIX);
	if (compareDouble(phiy, comp->phiy) < 1.0e-4) insert(items, PHIY);
	if (compareDouble(llim, comp->llim) < 1.0e-4) insert(items, LLIM);
	if (compareDouble(ulim, comp->ulim) < 1.0e-4) insert(items, ULIM);
	if (tstep == comp->tstep) insert(items, TSTEP);

	return(items);
};

set<uint> StgJobIdecMechctlPhi::diff(
			const StgJobIdecMechctlPhi* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVPORT, TPR, TCALIB, GR, OX, OY, AXM, AYM, PHIX, PHIY, LLIM, ULIM, TSTEP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecMechctlTheta
 ******************************************************************************/

StgJobIdecMechctlTheta::StgJobIdecMechctlTheta(
			const uint ixIdecVPort
			, const utinyint tpr
			, const uint tcalib
			, const usmallint gr
			, const double Ox
			, const double Oy
			, const double Axm
			, const double Aym
			, const double phix
			, const double phiy
			, const double llim
			, const double ulim
			, const usmallint tstep
		) : Block() {
	this->ixIdecVPort = ixIdecVPort;
	this->tpr = tpr;
	this->tcalib = tcalib;
	this->gr = gr;
	this->Ox = Ox;
	this->Oy = Oy;
	this->Axm = Axm;
	this->Aym = Aym;
	this->phix = phix;
	this->phiy = phiy;
	this->llim = llim;
	this->ulim = ulim;
	this->tstep = tstep;
	mask = {IXIDECVPORT, TPR, TCALIB, GR, OX, OY, AXM, AYM, PHIX, PHIY, LLIM, ULIM, TSTEP};
};

bool StgJobIdecMechctlTheta::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVPort;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecMechctlTheta");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecMechctlTheta";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVPort", srefIxIdecVPort)) {
			ixIdecVPort = VecIdecVPort::getIx(srefIxIdecVPort);
			add(IXIDECVPORT);
		};
		if (extractUtinyintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tpr", tpr)) add(TPR);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tcalib", tcalib)) add(TCALIB);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "gr", gr)) add(GR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Ox", Ox)) add(OX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Oy", Oy)) add(OY);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Axm", Axm)) add(AXM);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Aym", Aym)) add(AYM);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "phix", phix)) add(PHIX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "phiy", phiy)) add(PHIY);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "llim", llim)) add(LLIM);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "ulim", ulim)) add(ULIM);
		if (extractUsmallintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tstep", tstep)) add(TSTEP);
	};

	return basefound;
};

void StgJobIdecMechctlTheta::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecMechctlTheta";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecMechctlTheta";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVPort", VecIdecVPort::getSref(ixIdecVPort));
		writeUtinyintAttr(wr, itemtag, "sref", "tpr", tpr);
		writeUintAttr(wr, itemtag, "sref", "tcalib", tcalib);
		writeUsmallintAttr(wr, itemtag, "sref", "gr", gr);
		writeDoubleAttr(wr, itemtag, "sref", "Ox", Ox);
		writeDoubleAttr(wr, itemtag, "sref", "Oy", Oy);
		writeDoubleAttr(wr, itemtag, "sref", "Axm", Axm);
		writeDoubleAttr(wr, itemtag, "sref", "Aym", Aym);
		writeDoubleAttr(wr, itemtag, "sref", "phix", phix);
		writeDoubleAttr(wr, itemtag, "sref", "phiy", phiy);
		writeDoubleAttr(wr, itemtag, "sref", "llim", llim);
		writeDoubleAttr(wr, itemtag, "sref", "ulim", ulim);
		writeUsmallintAttr(wr, itemtag, "sref", "tstep", tstep);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecMechctlTheta::comm(
			const StgJobIdecMechctlTheta* comp
		) {
	set<uint> items;

	if (ixIdecVPort == comp->ixIdecVPort) insert(items, IXIDECVPORT);
	if (tpr == comp->tpr) insert(items, TPR);
	if (tcalib == comp->tcalib) insert(items, TCALIB);
	if (gr == comp->gr) insert(items, GR);
	if (compareDouble(Ox, comp->Ox) < 1.0e-4) insert(items, OX);
	if (compareDouble(Oy, comp->Oy) < 1.0e-4) insert(items, OY);
	if (compareDouble(Axm, comp->Axm) < 1.0e-4) insert(items, AXM);
	if (compareDouble(Aym, comp->Aym) < 1.0e-4) insert(items, AYM);
	if (compareDouble(phix, comp->phix) < 1.0e-4) insert(items, PHIX);
	if (compareDouble(phiy, comp->phiy) < 1.0e-4) insert(items, PHIY);
	if (compareDouble(llim, comp->llim) < 1.0e-4) insert(items, LLIM);
	if (compareDouble(ulim, comp->ulim) < 1.0e-4) insert(items, ULIM);
	if (tstep == comp->tstep) insert(items, TSTEP);

	return(items);
};

set<uint> StgJobIdecMechctlTheta::diff(
			const StgJobIdecMechctlTheta* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVPORT, TPR, TCALIB, GR, OX, OY, AXM, AYM, PHIX, PHIY, LLIM, ULIM, TSTEP};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecQcdacq
 ******************************************************************************/

StgJobIdecQcdacq::StgJobIdecQcdacq(
			const double lam0
			, const double dlam
			, const uint width
			, const double hpix
			, const double dpix
			, const uint ixIdecVPort
			, const uint tcalnuc
			, const vector<double>& a
			, const vector<double>& b
			, const vector<double>& err
			, const double multerr
			, const double dS
			, const double dT
			, const vector<usmallint>& iplTTvsSSx
			, const vector<double>& iplTTvsSSy
			, const vector<usmallint>& iplDTdSvsSSx
			, const vector<double>& iplDTdSvsSSy
			, const uint ixIdecVSqrgrp
			, const double f
			, const double fn
			, const bool on
			, const double tturnoff
			, const double Tdet
			, const uint ixVFan
			, const bool mod
			, const double fmod
			, const double Vdd
			, const double Vref
			, const uint tcalaln
			, const double dxqcd
			, const double dyqcd
			, const double dxalign
			, const double dyalign
			, const double dthetaalign
			, const double dphialign
		) : Block() {
	this->lam0 = lam0;
	this->dlam = dlam;
	this->width = width;
	this->hpix = hpix;
	this->dpix = dpix;
	this->ixIdecVPort = ixIdecVPort;
	this->tcalnuc = tcalnuc;
	this->a = a;
	this->b = b;
	this->err = err;
	this->multerr = multerr;
	this->dS = dS;
	this->dT = dT;
	this->iplTTvsSSx = iplTTvsSSx;
	this->iplTTvsSSy = iplTTvsSSy;
	this->iplDTdSvsSSx = iplDTdSvsSSx;
	this->iplDTdSvsSSy = iplDTdSvsSSy;
	this->ixIdecVSqrgrp = ixIdecVSqrgrp;
	this->f = f;
	this->fn = fn;
	this->on = on;
	this->tturnoff = tturnoff;
	this->Tdet = Tdet;
	this->ixVFan = ixVFan;
	this->mod = mod;
	this->fmod = fmod;
	this->Vdd = Vdd;
	this->Vref = Vref;
	this->tcalaln = tcalaln;
	this->dxqcd = dxqcd;
	this->dyqcd = dyqcd;
	this->dxalign = dxalign;
	this->dyalign = dyalign;
	this->dthetaalign = dthetaalign;
	this->dphialign = dphialign;
	mask = {LAM0, DLAM, WIDTH, HPIX, DPIX, IXIDECVPORT, TCALNUC, A, B, ERR, MULTERR, DS, DT, IPLTTVSSSX, IPLTTVSSSY, IPLDTDSVSSSX, IPLDTDSVSSSY, IXIDECVSQRGRP, F, FN, ON, TTURNOFF, TDET, IXVFAN, MOD, FMOD, VDD, VREF, TCALALN, DXQCD, DYQCD, DXALIGN, DYALIGN, DTHETAALIGN, DPHIALIGN};
};

bool StgJobIdecQcdacq::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVPort;
	string srefIxIdecVSqrgrp;
	string srefIxVFan;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecQcdacq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecQcdacq";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "lam0", lam0)) add(LAM0);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dlam", dlam)) add(DLAM);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "width", width)) add(WIDTH);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "hpix", hpix)) add(HPIX);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dpix", dpix)) add(DPIX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVPort", srefIxIdecVPort)) {
			ixIdecVPort = VecIdecVPort::getIx(srefIxIdecVPort);
			add(IXIDECVPORT);
		};
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tcalnuc", tcalnuc)) add(TCALNUC);
		if (extractDoublevecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "a", a)) add(A);
		if (extractDoublevecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "b", b)) add(B);
		if (extractDoublevecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "err", err)) add(ERR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "multerr", multerr)) add(MULTERR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dS", dS)) add(DS);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dT", dT)) add(DT);
		if (extractUsmallintvecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "iplTTvsSSx", iplTTvsSSx)) add(IPLTTVSSSX);
		if (extractDoublevecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "iplTTvsSSy", iplTTvsSSy)) add(IPLTTVSSSY);
		if (extractUsmallintvecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "iplDTdSvsSSx", iplDTdSvsSSx)) add(IPLDTDSVSSSX);
		if (extractDoublevecAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "iplDTdSvsSSy", iplDTdSvsSSy)) add(IPLDTDSVSSSY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVSqrgrp", srefIxIdecVSqrgrp)) {
			ixIdecVSqrgrp = VecIdecVSqrgrp::getIx(srefIxIdecVSqrgrp);
			add(IXIDECVSQRGRP);
		};
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "f", f)) add(F);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "fn", fn)) add(FN);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "on", on)) add(ON);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tturnoff", tturnoff)) add(TTURNOFF);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Tdet", Tdet)) add(TDET);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxVFan", srefIxVFan)) {
			ixVFan = VecVJobIdecQcdacqFan::getIx(srefIxVFan);
			add(IXVFAN);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "mod", mod)) add(MOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "fmod", fmod)) add(FMOD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Vdd", Vdd)) add(VDD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Vref", Vref)) add(VREF);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tcalaln", tcalaln)) add(TCALALN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dxqcd", dxqcd)) add(DXQCD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dyqcd", dyqcd)) add(DYQCD);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dxalign", dxalign)) add(DXALIGN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dyalign", dyalign)) add(DYALIGN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dthetaalign", dthetaalign)) add(DTHETAALIGN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dphialign", dphialign)) add(DPHIALIGN);
	};

	return basefound;
};

void StgJobIdecQcdacq::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecQcdacq";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecQcdacq";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "lam0", lam0);
		writeDoubleAttr(wr, itemtag, "sref", "dlam", dlam);
		writeUintAttr(wr, itemtag, "sref", "width", width);
		writeDoubleAttr(wr, itemtag, "sref", "hpix", hpix);
		writeDoubleAttr(wr, itemtag, "sref", "dpix", dpix);
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVPort", VecIdecVPort::getSref(ixIdecVPort));
		writeUintAttr(wr, itemtag, "sref", "tcalnuc", tcalnuc);
		writeDoublevecAttr(wr, itemtag, "sref", "a", a);
		writeDoublevecAttr(wr, itemtag, "sref", "b", b);
		writeDoublevecAttr(wr, itemtag, "sref", "err", err);
		writeDoubleAttr(wr, itemtag, "sref", "multerr", multerr);
		writeDoubleAttr(wr, itemtag, "sref", "dS", dS);
		writeDoubleAttr(wr, itemtag, "sref", "dT", dT);
		writeUsmallintvecAttr(wr, itemtag, "sref", "iplTTvsSSx", iplTTvsSSx);
		writeDoublevecAttr(wr, itemtag, "sref", "iplTTvsSSy", iplTTvsSSy);
		writeUsmallintvecAttr(wr, itemtag, "sref", "iplDTdSvsSSx", iplDTdSvsSSx);
		writeDoublevecAttr(wr, itemtag, "sref", "iplDTdSvsSSy", iplDTdSvsSSy);
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVSqrgrp", VecIdecVSqrgrp::getSref(ixIdecVSqrgrp));
		writeDoubleAttr(wr, itemtag, "sref", "f", f);
		writeDoubleAttr(wr, itemtag, "sref", "fn", fn);
		writeBoolAttr(wr, itemtag, "sref", "on", on);
		writeDoubleAttr(wr, itemtag, "sref", "tturnoff", tturnoff);
		writeDoubleAttr(wr, itemtag, "sref", "Tdet", Tdet);
		writeStringAttr(wr, itemtag, "sref", "srefIxVFan", VecVJobIdecQcdacqFan::getSref(ixVFan));
		writeBoolAttr(wr, itemtag, "sref", "mod", mod);
		writeDoubleAttr(wr, itemtag, "sref", "fmod", fmod);
		writeDoubleAttr(wr, itemtag, "sref", "Vdd", Vdd);
		writeDoubleAttr(wr, itemtag, "sref", "Vref", Vref);
		writeUintAttr(wr, itemtag, "sref", "tcalaln", tcalaln);
		writeDoubleAttr(wr, itemtag, "sref", "dxqcd", dxqcd);
		writeDoubleAttr(wr, itemtag, "sref", "dyqcd", dyqcd);
		writeDoubleAttr(wr, itemtag, "sref", "dxalign", dxalign);
		writeDoubleAttr(wr, itemtag, "sref", "dyalign", dyalign);
		writeDoubleAttr(wr, itemtag, "sref", "dthetaalign", dthetaalign);
		writeDoubleAttr(wr, itemtag, "sref", "dphialign", dphialign);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecQcdacq::comm(
			const StgJobIdecQcdacq* comp
		) {
	set<uint> items;

	if (compareDouble(lam0, comp->lam0) < 1.0e-4) insert(items, LAM0);
	if (compareDouble(dlam, comp->dlam) < 1.0e-4) insert(items, DLAM);
	if (width == comp->width) insert(items, WIDTH);
	if (compareDouble(hpix, comp->hpix) < 1.0e-4) insert(items, HPIX);
	if (compareDouble(dpix, comp->dpix) < 1.0e-4) insert(items, DPIX);
	if (ixIdecVPort == comp->ixIdecVPort) insert(items, IXIDECVPORT);
	if (tcalnuc == comp->tcalnuc) insert(items, TCALNUC);
	if (compareDoublevec(a, comp->a) < 1.0e-4) insert(items, A);
	if (compareDoublevec(b, comp->b) < 1.0e-4) insert(items, B);
	if (compareDoublevec(err, comp->err) < 1.0e-4) insert(items, ERR);
	if (compareDouble(multerr, comp->multerr) < 1.0e-4) insert(items, MULTERR);
	if (compareDouble(dS, comp->dS) < 1.0e-4) insert(items, DS);
	if (compareDouble(dT, comp->dT) < 1.0e-4) insert(items, DT);
	if (compareUsmallintvec(iplTTvsSSx, comp->iplTTvsSSx)) insert(items, IPLTTVSSSX);
	if (compareDoublevec(iplTTvsSSy, comp->iplTTvsSSy) < 1.0e-4) insert(items, IPLTTVSSSY);
	if (compareUsmallintvec(iplDTdSvsSSx, comp->iplDTdSvsSSx)) insert(items, IPLDTDSVSSSX);
	if (compareDoublevec(iplDTdSvsSSy, comp->iplDTdSvsSSy) < 1.0e-4) insert(items, IPLDTDSVSSSY);
	if (ixIdecVSqrgrp == comp->ixIdecVSqrgrp) insert(items, IXIDECVSQRGRP);
	if (compareDouble(f, comp->f) < 1.0e-4) insert(items, F);
	if (compareDouble(fn, comp->fn) < 1.0e-4) insert(items, FN);
	if (on == comp->on) insert(items, ON);
	if (compareDouble(tturnoff, comp->tturnoff) < 1.0e-4) insert(items, TTURNOFF);
	if (compareDouble(Tdet, comp->Tdet) < 1.0e-4) insert(items, TDET);
	if (ixVFan == comp->ixVFan) insert(items, IXVFAN);
	if (mod == comp->mod) insert(items, MOD);
	if (compareDouble(fmod, comp->fmod) < 1.0e-4) insert(items, FMOD);
	if (compareDouble(Vdd, comp->Vdd) < 1.0e-4) insert(items, VDD);
	if (compareDouble(Vref, comp->Vref) < 1.0e-4) insert(items, VREF);
	if (tcalaln == comp->tcalaln) insert(items, TCALALN);
	if (compareDouble(dxqcd, comp->dxqcd) < 1.0e-4) insert(items, DXQCD);
	if (compareDouble(dyqcd, comp->dyqcd) < 1.0e-4) insert(items, DYQCD);
	if (compareDouble(dxalign, comp->dxalign) < 1.0e-4) insert(items, DXALIGN);
	if (compareDouble(dyalign, comp->dyalign) < 1.0e-4) insert(items, DYALIGN);
	if (compareDouble(dthetaalign, comp->dthetaalign) < 1.0e-4) insert(items, DTHETAALIGN);
	if (compareDouble(dphialign, comp->dphialign) < 1.0e-4) insert(items, DPHIALIGN);

	return(items);
};

set<uint> StgJobIdecQcdacq::diff(
			const StgJobIdecQcdacq* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {LAM0, DLAM, WIDTH, HPIX, DPIX, IXIDECVPORT, TCALNUC, A, B, ERR, MULTERR, DS, DT, IPLTTVSSSX, IPLTTVSSSY, IPLDTDSVSSSX, IPLDTDSVSSSY, IXIDECVSQRGRP, F, FN, ON, TTURNOFF, TDET, IXVFAN, MOD, FMOD, VDD, VREF, TCALALN, DXQCD, DYQCD, DXALIGN, DYALIGN, DTHETAALIGN, DPHIALIGN};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecRecord
 ******************************************************************************/

StgJobIdecRecord::StgJobIdecRecord(
			const uint frmlIxIdecVCamres
			, const bool frmlGray
			, const uint frmrIxIdecVCamres
			, const bool frmrGray
			, const uint frmiIxIdecVCamres
			, const bool frmqcd
			, const bool frmstereo
			, const double vidfps
			, const uint vidlIxIdecVCamres
			, const bool vidlGray
			, const uint vidrIxIdecVCamres
			, const bool vidrGray
			, const uint vidiIxIdecVCamres
			, const bool vidqcd
			, const bool vidstereo
			, const uint ixVOverwrite
		) : Block() {
	this->frmlIxIdecVCamres = frmlIxIdecVCamres;
	this->frmlGray = frmlGray;
	this->frmrIxIdecVCamres = frmrIxIdecVCamres;
	this->frmrGray = frmrGray;
	this->frmiIxIdecVCamres = frmiIxIdecVCamres;
	this->frmqcd = frmqcd;
	this->frmstereo = frmstereo;
	this->vidfps = vidfps;
	this->vidlIxIdecVCamres = vidlIxIdecVCamres;
	this->vidlGray = vidlGray;
	this->vidrIxIdecVCamres = vidrIxIdecVCamres;
	this->vidrGray = vidrGray;
	this->vidiIxIdecVCamres = vidiIxIdecVCamres;
	this->vidqcd = vidqcd;
	this->vidstereo = vidstereo;
	this->ixVOverwrite = ixVOverwrite;
	mask = {FRMLIXIDECVCAMRES, FRMLGRAY, FRMRIXIDECVCAMRES, FRMRGRAY, FRMIIXIDECVCAMRES, FRMQCD, FRMSTEREO, VIDFPS, VIDLIXIDECVCAMRES, VIDLGRAY, VIDRIXIDECVCAMRES, VIDRGRAY, VIDIIXIDECVCAMRES, VIDQCD, VIDSTEREO, IXVOVERWRITE};
};

bool StgJobIdecRecord::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefFrmlIxIdecVCamres;
	string srefFrmrIxIdecVCamres;
	string srefFrmiIxIdecVCamres;
	string srefVidlIxIdecVCamres;
	string srefVidrIxIdecVCamres;
	string srefVidiIxIdecVCamres;
	string srefIxVOverwrite;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecRecord");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecRecord";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefFrmlIxIdecVCamres", srefFrmlIxIdecVCamres)) {
			frmlIxIdecVCamres = VecIdecVCamres::getIx(srefFrmlIxIdecVCamres);
			add(FRMLIXIDECVCAMRES);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "frmlGray", frmlGray)) add(FRMLGRAY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefFrmrIxIdecVCamres", srefFrmrIxIdecVCamres)) {
			frmrIxIdecVCamres = VecIdecVCamres::getIx(srefFrmrIxIdecVCamres);
			add(FRMRIXIDECVCAMRES);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "frmrGray", frmrGray)) add(FRMRGRAY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefFrmiIxIdecVCamres", srefFrmiIxIdecVCamres)) {
			frmiIxIdecVCamres = VecIdecVCamres::getIx(srefFrmiIxIdecVCamres);
			add(FRMIIXIDECVCAMRES);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "frmqcd", frmqcd)) add(FRMQCD);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "frmstereo", frmstereo)) add(FRMSTEREO);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "vidfps", vidfps)) add(VIDFPS);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefVidlIxIdecVCamres", srefVidlIxIdecVCamres)) {
			vidlIxIdecVCamres = VecIdecVCamres::getIx(srefVidlIxIdecVCamres);
			add(VIDLIXIDECVCAMRES);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "vidlGray", vidlGray)) add(VIDLGRAY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefVidrIxIdecVCamres", srefVidrIxIdecVCamres)) {
			vidrIxIdecVCamres = VecIdecVCamres::getIx(srefVidrIxIdecVCamres);
			add(VIDRIXIDECVCAMRES);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "vidrGray", vidrGray)) add(VIDRGRAY);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefVidiIxIdecVCamres", srefVidiIxIdecVCamres)) {
			vidiIxIdecVCamres = VecIdecVCamres::getIx(srefVidiIxIdecVCamres);
			add(VIDIIXIDECVCAMRES);
		};
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "vidqcd", vidqcd)) add(VIDQCD);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "vidstereo", vidstereo)) add(VIDSTEREO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxVOverwrite", srefIxVOverwrite)) {
			ixVOverwrite = VecVJobIdecRecordOverwrite::getIx(srefIxVOverwrite);
			add(IXVOVERWRITE);
		};
	};

	return basefound;
};

void StgJobIdecRecord::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecRecord";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecRecord";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefFrmlIxIdecVCamres", VecIdecVCamres::getSref(frmlIxIdecVCamres));
		writeBoolAttr(wr, itemtag, "sref", "frmlGray", frmlGray);
		writeStringAttr(wr, itemtag, "sref", "srefFrmrIxIdecVCamres", VecIdecVCamres::getSref(frmrIxIdecVCamres));
		writeBoolAttr(wr, itemtag, "sref", "frmrGray", frmrGray);
		writeStringAttr(wr, itemtag, "sref", "srefFrmiIxIdecVCamres", VecIdecVCamres::getSref(frmiIxIdecVCamres));
		writeBoolAttr(wr, itemtag, "sref", "frmqcd", frmqcd);
		writeBoolAttr(wr, itemtag, "sref", "frmstereo", frmstereo);
		writeDoubleAttr(wr, itemtag, "sref", "vidfps", vidfps);
		writeStringAttr(wr, itemtag, "sref", "srefVidlIxIdecVCamres", VecIdecVCamres::getSref(vidlIxIdecVCamres));
		writeBoolAttr(wr, itemtag, "sref", "vidlGray", vidlGray);
		writeStringAttr(wr, itemtag, "sref", "srefVidrIxIdecVCamres", VecIdecVCamres::getSref(vidrIxIdecVCamres));
		writeBoolAttr(wr, itemtag, "sref", "vidrGray", vidrGray);
		writeStringAttr(wr, itemtag, "sref", "srefVidiIxIdecVCamres", VecIdecVCamres::getSref(vidiIxIdecVCamres));
		writeBoolAttr(wr, itemtag, "sref", "vidqcd", vidqcd);
		writeBoolAttr(wr, itemtag, "sref", "vidstereo", vidstereo);
		writeStringAttr(wr, itemtag, "sref", "srefIxVOverwrite", VecVJobIdecRecordOverwrite::getSref(ixVOverwrite));
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecRecord::comm(
			const StgJobIdecRecord* comp
		) {
	set<uint> items;

	if (frmlIxIdecVCamres == comp->frmlIxIdecVCamres) insert(items, FRMLIXIDECVCAMRES);
	if (frmlGray == comp->frmlGray) insert(items, FRMLGRAY);
	if (frmrIxIdecVCamres == comp->frmrIxIdecVCamres) insert(items, FRMRIXIDECVCAMRES);
	if (frmrGray == comp->frmrGray) insert(items, FRMRGRAY);
	if (frmiIxIdecVCamres == comp->frmiIxIdecVCamres) insert(items, FRMIIXIDECVCAMRES);
	if (frmqcd == comp->frmqcd) insert(items, FRMQCD);
	if (frmstereo == comp->frmstereo) insert(items, FRMSTEREO);
	if (compareDouble(vidfps, comp->vidfps) < 1.0e-4) insert(items, VIDFPS);
	if (vidlIxIdecVCamres == comp->vidlIxIdecVCamres) insert(items, VIDLIXIDECVCAMRES);
	if (vidlGray == comp->vidlGray) insert(items, VIDLGRAY);
	if (vidrIxIdecVCamres == comp->vidrIxIdecVCamres) insert(items, VIDRIXIDECVCAMRES);
	if (vidrGray == comp->vidrGray) insert(items, VIDRGRAY);
	if (vidiIxIdecVCamres == comp->vidiIxIdecVCamres) insert(items, VIDIIXIDECVCAMRES);
	if (vidqcd == comp->vidqcd) insert(items, VIDQCD);
	if (vidstereo == comp->vidstereo) insert(items, VIDSTEREO);
	if (ixVOverwrite == comp->ixVOverwrite) insert(items, IXVOVERWRITE);

	return(items);
};

set<uint> StgJobIdecRecord::diff(
			const StgJobIdecRecord* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {FRMLIXIDECVCAMRES, FRMLGRAY, FRMRIXIDECVCAMRES, FRMRGRAY, FRMIIXIDECVCAMRES, FRMQCD, FRMSTEREO, VIDFPS, VIDLIXIDECVCAMRES, VIDLGRAY, VIDRIXIDECVCAMRES, VIDRGRAY, VIDIIXIDECVCAMRES, VIDQCD, VIDSTEREO, IXVOVERWRITE};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecSpotfind
 ******************************************************************************/

StgJobIdecSpotfind::StgJobIdecSpotfind(
			const uint seqlen
			, const double Pmax
			, const bool adapt
		) : Block() {
	this->seqlen = seqlen;
	this->Pmax = Pmax;
	this->adapt = adapt;
	mask = {SEQLEN, PMAX, ADAPT};
};

bool StgJobIdecSpotfind::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecSpotfind");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecSpotfind";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "seqlen", seqlen)) add(SEQLEN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "Pmax", Pmax)) add(PMAX);
		if (extractBoolAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "adapt", adapt)) add(ADAPT);
	};

	return basefound;
};

void StgJobIdecSpotfind::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecSpotfind";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecSpotfind";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "seqlen", seqlen);
		writeDoubleAttr(wr, itemtag, "sref", "Pmax", Pmax);
		writeBoolAttr(wr, itemtag, "sref", "adapt", adapt);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecSpotfind::comm(
			const StgJobIdecSpotfind* comp
		) {
	set<uint> items;

	if (seqlen == comp->seqlen) insert(items, SEQLEN);
	if (compareDouble(Pmax, comp->Pmax) < 1.0e-4) insert(items, PMAX);
	if (adapt == comp->adapt) insert(items, ADAPT);

	return(items);
};

set<uint> StgJobIdecSpotfind::diff(
			const StgJobIdecSpotfind* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {SEQLEN, PMAX, ADAPT};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecStereo
 ******************************************************************************/

StgJobIdecStereo::StgJobIdecStereo(
			const uint tcalib
			, const double dstereo
			, const double dthetavisr
			, const double dphivisr
		) : Block() {
	this->tcalib = tcalib;
	this->dstereo = dstereo;
	this->dthetavisr = dthetavisr;
	this->dphivisr = dphivisr;
	mask = {TCALIB, DSTEREO, DTHETAVISR, DPHIVISR};
};

bool StgJobIdecStereo::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecStereo");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecStereo";

	if (basefound) {
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tcalib", tcalib)) add(TCALIB);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dstereo", dstereo)) add(DSTEREO);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dthetavisr", dthetavisr)) add(DTHETAVISR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "dphivisr", dphivisr)) add(DPHIVISR);
	};

	return basefound;
};

void StgJobIdecStereo::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecStereo";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecStereo";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeUintAttr(wr, itemtag, "sref", "tcalib", tcalib);
		writeDoubleAttr(wr, itemtag, "sref", "dstereo", dstereo);
		writeDoubleAttr(wr, itemtag, "sref", "dthetavisr", dthetavisr);
		writeDoubleAttr(wr, itemtag, "sref", "dphivisr", dphivisr);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecStereo::comm(
			const StgJobIdecStereo* comp
		) {
	set<uint> items;

	if (tcalib == comp->tcalib) insert(items, TCALIB);
	if (compareDouble(dstereo, comp->dstereo) < 1.0e-4) insert(items, DSTEREO);
	if (compareDouble(dthetavisr, comp->dthetavisr) < 1.0e-4) insert(items, DTHETAVISR);
	if (compareDouble(dphivisr, comp->dphivisr) < 1.0e-4) insert(items, DPHIVISR);

	return(items);
};

set<uint> StgJobIdecStereo::diff(
			const StgJobIdecStereo* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TCALIB, DSTEREO, DTHETAVISR, DPHIVISR};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecTrigger
 ******************************************************************************/

StgJobIdecTrigger::StgJobIdecTrigger(
			const double tvisr
			, const double tlwir
			, const double tqcd
		) : Block() {
	this->tvisr = tvisr;
	this->tlwir = tlwir;
	this->tqcd = tqcd;
	mask = {TVISR, TLWIR, TQCD};
};

bool StgJobIdecTrigger::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecTrigger");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecTrigger";

	if (basefound) {
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tvisr", tvisr)) add(TVISR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tlwir", tlwir)) add(TLWIR);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "tqcd", tqcd)) add(TQCD);
	};

	return basefound;
};

void StgJobIdecTrigger::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecTrigger";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecTrigger";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeDoubleAttr(wr, itemtag, "sref", "tvisr", tvisr);
		writeDoubleAttr(wr, itemtag, "sref", "tlwir", tlwir);
		writeDoubleAttr(wr, itemtag, "sref", "tqcd", tqcd);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecTrigger::comm(
			const StgJobIdecTrigger* comp
		) {
	set<uint> items;

	if (compareDouble(tvisr, comp->tvisr) < 1.0e-4) insert(items, TVISR);
	if (compareDouble(tlwir, comp->tlwir) < 1.0e-4) insert(items, TLWIR);
	if (compareDouble(tqcd, comp->tqcd) < 1.0e-4) insert(items, TQCD);

	return(items);
};

set<uint> StgJobIdecTrigger::diff(
			const StgJobIdecTrigger* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {TVISR, TLWIR, TQCD};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecVislacq
 ******************************************************************************/

StgJobIdecVislacq::StgJobIdecVislacq(
			const uint ixIdecVCamtype
			, const uint width
			, const uint height
			, const double hpix
			, const uint trigIxIdecVPort
			, const string& path
			, const string& serno
			, const uint ixIdecVSqrgrp
			, const double f
			, const double fn
			, const double k1
			, const double k2
			, const double p1
			, const double p2
			, const double k3
			, const double k4
			, const double k5
			, const double k6
		) : Block() {
	this->ixIdecVCamtype = ixIdecVCamtype;
	this->width = width;
	this->height = height;
	this->hpix = hpix;
	this->trigIxIdecVPort = trigIxIdecVPort;
	this->path = path;
	this->serno = serno;
	this->ixIdecVSqrgrp = ixIdecVSqrgrp;
	this->f = f;
	this->fn = fn;
	this->k1 = k1;
	this->k2 = k2;
	this->p1 = p1;
	this->p2 = p2;
	this->k3 = k3;
	this->k4 = k4;
	this->k5 = k5;
	this->k6 = k6;
	mask = {IXIDECVCAMTYPE, WIDTH, HEIGHT, HPIX, TRIGIXIDECVPORT, PATH, SERNO, IXIDECVSQRGRP, F, FN, K1, K2, P1, P2, K3, K4, K5, K6};
};

bool StgJobIdecVislacq::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVCamtype;
	string srefTrigIxIdecVPort;
	string srefIxIdecVSqrgrp;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecVislacq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecVislacq";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVCamtype", srefIxIdecVCamtype)) {
			ixIdecVCamtype = VecIdecVCamtype::getIx(srefIxIdecVCamtype);
			add(IXIDECVCAMTYPE);
		};
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "width", width)) add(WIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "height", height)) add(HEIGHT);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "hpix", hpix)) add(HPIX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefTrigIxIdecVPort", srefTrigIxIdecVPort)) {
			trigIxIdecVPort = VecIdecVPort::getIx(srefTrigIxIdecVPort);
			add(TRIGIXIDECVPORT);
		};
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "path", path)) add(PATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "serno", serno)) add(SERNO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVSqrgrp", srefIxIdecVSqrgrp)) {
			ixIdecVSqrgrp = VecIdecVSqrgrp::getIx(srefIxIdecVSqrgrp);
			add(IXIDECVSQRGRP);
		};
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "f", f)) add(F);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "fn", fn)) add(FN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k1", k1)) add(K1);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k2", k2)) add(K2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "p1", p1)) add(P1);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "p2", p2)) add(P2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k3", k3)) add(K3);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k4", k4)) add(K4);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k5", k5)) add(K5);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k6", k6)) add(K6);
	};

	return basefound;
};

void StgJobIdecVislacq::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecVislacq";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecVislacq";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVCamtype", VecIdecVCamtype::getSref(ixIdecVCamtype));
		writeUintAttr(wr, itemtag, "sref", "width", width);
		writeUintAttr(wr, itemtag, "sref", "height", height);
		writeDoubleAttr(wr, itemtag, "sref", "hpix", hpix);
		writeStringAttr(wr, itemtag, "sref", "srefTrigIxIdecVPort", VecIdecVPort::getSref(trigIxIdecVPort));
		writeStringAttr(wr, itemtag, "sref", "path", path);
		writeStringAttr(wr, itemtag, "sref", "serno", serno);
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVSqrgrp", VecIdecVSqrgrp::getSref(ixIdecVSqrgrp));
		writeDoubleAttr(wr, itemtag, "sref", "f", f);
		writeDoubleAttr(wr, itemtag, "sref", "fn", fn);
		writeDoubleAttr(wr, itemtag, "sref", "k1", k1);
		writeDoubleAttr(wr, itemtag, "sref", "k2", k2);
		writeDoubleAttr(wr, itemtag, "sref", "p1", p1);
		writeDoubleAttr(wr, itemtag, "sref", "p2", p2);
		writeDoubleAttr(wr, itemtag, "sref", "k3", k3);
		writeDoubleAttr(wr, itemtag, "sref", "k4", k4);
		writeDoubleAttr(wr, itemtag, "sref", "k5", k5);
		writeDoubleAttr(wr, itemtag, "sref", "k6", k6);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecVislacq::comm(
			const StgJobIdecVislacq* comp
		) {
	set<uint> items;

	if (ixIdecVCamtype == comp->ixIdecVCamtype) insert(items, IXIDECVCAMTYPE);
	if (width == comp->width) insert(items, WIDTH);
	if (height == comp->height) insert(items, HEIGHT);
	if (compareDouble(hpix, comp->hpix) < 1.0e-4) insert(items, HPIX);
	if (trigIxIdecVPort == comp->trigIxIdecVPort) insert(items, TRIGIXIDECVPORT);
	if (path == comp->path) insert(items, PATH);
	if (serno == comp->serno) insert(items, SERNO);
	if (ixIdecVSqrgrp == comp->ixIdecVSqrgrp) insert(items, IXIDECVSQRGRP);
	if (compareDouble(f, comp->f) < 1.0e-4) insert(items, F);
	if (compareDouble(fn, comp->fn) < 1.0e-4) insert(items, FN);
	if (compareDouble(k1, comp->k1) < 1.0e-4) insert(items, K1);
	if (compareDouble(k2, comp->k2) < 1.0e-4) insert(items, K2);
	if (compareDouble(p1, comp->p1) < 1.0e-4) insert(items, P1);
	if (compareDouble(p2, comp->p2) < 1.0e-4) insert(items, P2);
	if (compareDouble(k3, comp->k3) < 1.0e-4) insert(items, K3);
	if (compareDouble(k4, comp->k4) < 1.0e-4) insert(items, K4);
	if (compareDouble(k5, comp->k5) < 1.0e-4) insert(items, K5);
	if (compareDouble(k6, comp->k6) < 1.0e-4) insert(items, K6);

	return(items);
};

set<uint> StgJobIdecVislacq::diff(
			const StgJobIdecVislacq* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVCAMTYPE, WIDTH, HEIGHT, HPIX, TRIGIXIDECVPORT, PATH, SERNO, IXIDECVSQRGRP, F, FN, K1, K2, P1, P2, K3, K4, K5, K6};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 class StgJobIdecVisracq
 ******************************************************************************/

StgJobIdecVisracq::StgJobIdecVisracq(
			const uint ixIdecVCamtype
			, const uint width
			, const uint height
			, const double hpix
			, const uint trigIxIdecVPort
			, const string& path
			, const string& serno
			, const uint ixIdecVSqrgrp
			, const double f
			, const double fn
			, const double k1
			, const double k2
			, const double p1
			, const double p2
			, const double k3
			, const double k4
			, const double k5
			, const double k6
		) : Block() {
	this->ixIdecVCamtype = ixIdecVCamtype;
	this->width = width;
	this->height = height;
	this->hpix = hpix;
	this->trigIxIdecVPort = trigIxIdecVPort;
	this->path = path;
	this->serno = serno;
	this->ixIdecVSqrgrp = ixIdecVSqrgrp;
	this->f = f;
	this->fn = fn;
	this->k1 = k1;
	this->k2 = k2;
	this->p1 = p1;
	this->p2 = p2;
	this->k3 = k3;
	this->k4 = k4;
	this->k5 = k5;
	this->k6 = k6;
	mask = {IXIDECVCAMTYPE, WIDTH, HEIGHT, HPIX, TRIGIXIDECVPORT, PATH, SERNO, IXIDECVSQRGRP, F, FN, K1, K2, P1, P2, K3, K4, K5, K6};
};

bool StgJobIdecVisracq::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string srefIxIdecVCamtype;
	string srefTrigIxIdecVPort;
	string srefIxIdecVSqrgrp;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "StgJobIdecVisracq");
	else
		basefound = checkXPath(docctx, basexpath);

	string itemtag = "StgitemJobIdecVisracq";

	if (basefound) {
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVCamtype", srefIxIdecVCamtype)) {
			ixIdecVCamtype = VecIdecVCamtype::getIx(srefIxIdecVCamtype);
			add(IXIDECVCAMTYPE);
		};
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "width", width)) add(WIDTH);
		if (extractUintAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "height", height)) add(HEIGHT);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "hpix", hpix)) add(HPIX);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefTrigIxIdecVPort", srefTrigIxIdecVPort)) {
			trigIxIdecVPort = VecIdecVPort::getIx(srefTrigIxIdecVPort);
			add(TRIGIXIDECVPORT);
		};
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "path", path)) add(PATH);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "serno", serno)) add(SERNO);
		if (extractStringAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "srefIxIdecVSqrgrp", srefIxIdecVSqrgrp)) {
			ixIdecVSqrgrp = VecIdecVSqrgrp::getIx(srefIxIdecVSqrgrp);
			add(IXIDECVSQRGRP);
		};
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "f", f)) add(F);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "fn", fn)) add(FN);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k1", k1)) add(K1);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k2", k2)) add(K2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "p1", p1)) add(P1);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "p2", p2)) add(P2);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k3", k3)) add(K3);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k4", k4)) add(K4);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k5", k5)) add(K5);
		if (extractDoubleAttrUclc(docctx, basexpath, itemtag, "Si", "sref", "k6", k6)) add(K6);
	};

	return basefound;
};

void StgJobIdecVisracq::writeXML(
			xmlTextWriter* wr
			, string difftag
			, bool shorttags
		) {
	if (difftag.length() == 0) difftag = "StgJobIdecVisracq";

	string itemtag;
	if (shorttags) itemtag = "Si";
	else itemtag = "StgitemJobIdecVisracq";

	xmlTextWriterStartElement(wr, BAD_CAST difftag.c_str());
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVCamtype", VecIdecVCamtype::getSref(ixIdecVCamtype));
		writeUintAttr(wr, itemtag, "sref", "width", width);
		writeUintAttr(wr, itemtag, "sref", "height", height);
		writeDoubleAttr(wr, itemtag, "sref", "hpix", hpix);
		writeStringAttr(wr, itemtag, "sref", "srefTrigIxIdecVPort", VecIdecVPort::getSref(trigIxIdecVPort));
		writeStringAttr(wr, itemtag, "sref", "path", path);
		writeStringAttr(wr, itemtag, "sref", "serno", serno);
		writeStringAttr(wr, itemtag, "sref", "srefIxIdecVSqrgrp", VecIdecVSqrgrp::getSref(ixIdecVSqrgrp));
		writeDoubleAttr(wr, itemtag, "sref", "f", f);
		writeDoubleAttr(wr, itemtag, "sref", "fn", fn);
		writeDoubleAttr(wr, itemtag, "sref", "k1", k1);
		writeDoubleAttr(wr, itemtag, "sref", "k2", k2);
		writeDoubleAttr(wr, itemtag, "sref", "p1", p1);
		writeDoubleAttr(wr, itemtag, "sref", "p2", p2);
		writeDoubleAttr(wr, itemtag, "sref", "k3", k3);
		writeDoubleAttr(wr, itemtag, "sref", "k4", k4);
		writeDoubleAttr(wr, itemtag, "sref", "k5", k5);
		writeDoubleAttr(wr, itemtag, "sref", "k6", k6);
	xmlTextWriterEndElement(wr);
};

set<uint> StgJobIdecVisracq::comm(
			const StgJobIdecVisracq* comp
		) {
	set<uint> items;

	if (ixIdecVCamtype == comp->ixIdecVCamtype) insert(items, IXIDECVCAMTYPE);
	if (width == comp->width) insert(items, WIDTH);
	if (height == comp->height) insert(items, HEIGHT);
	if (compareDouble(hpix, comp->hpix) < 1.0e-4) insert(items, HPIX);
	if (trigIxIdecVPort == comp->trigIxIdecVPort) insert(items, TRIGIXIDECVPORT);
	if (path == comp->path) insert(items, PATH);
	if (serno == comp->serno) insert(items, SERNO);
	if (ixIdecVSqrgrp == comp->ixIdecVSqrgrp) insert(items, IXIDECVSQRGRP);
	if (compareDouble(f, comp->f) < 1.0e-4) insert(items, F);
	if (compareDouble(fn, comp->fn) < 1.0e-4) insert(items, FN);
	if (compareDouble(k1, comp->k1) < 1.0e-4) insert(items, K1);
	if (compareDouble(k2, comp->k2) < 1.0e-4) insert(items, K2);
	if (compareDouble(p1, comp->p1) < 1.0e-4) insert(items, P1);
	if (compareDouble(p2, comp->p2) < 1.0e-4) insert(items, P2);
	if (compareDouble(k3, comp->k3) < 1.0e-4) insert(items, K3);
	if (compareDouble(k4, comp->k4) < 1.0e-4) insert(items, K4);
	if (compareDouble(k5, comp->k5) < 1.0e-4) insert(items, K5);
	if (compareDouble(k6, comp->k6) < 1.0e-4) insert(items, K6);

	return(items);
};

set<uint> StgJobIdecVisracq::diff(
			const StgJobIdecVisracq* comp
		) {
	set<uint> commitems;
	set<uint> diffitems;

	commitems = comm(comp);

	diffitems = {IXIDECVCAMTYPE, WIDTH, HEIGHT, HPIX, TRIGIXIDECVPORT, PATH, SERNO, IXIDECVSQRGRP, F, FN, K1, K2, P1, P2, K3, K4, K5, K6};
	for (auto it=commitems.begin();it!=commitems.end();it++) diffitems.erase(*it);

	return(diffitems);
};

/******************************************************************************
 namespace AlrIdec
 ******************************************************************************/

DpchEngIdecAlert* AlrIdec::prepareAlrAbt(
			const ubigint jref
			, const uint ixIdecVLocale
			, Feed& feedFMcbAlert
		) {
	ContInfIdecAlert continf;
	// IP prepareAlrAbt --- BEGIN
	continf.TxtCpt = VecIdecVTag::getTitle(VecIdecVTag::ABOUT, ixIdecVLocale);
	continf.TxtCpt = StrMod::cap(continf.TxtCpt);

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "ICARUSDetectorControl version 0.2.1 released on 30-12-2017";
		continf.TxtMsg2 = "\\u00a9 Mpsi Technologies GmbH";
		continf.TxtMsg4 = "contributors: Alexander Wirthmueller";
		continf.TxtMsg6 = "libraries: jpeg 8, opencv 2.4.8, netcdf 4.2.1.1, flycapture 2.8.3.1, devidhw 1.0.0 and aravis 0.6";
		continf.TxtMsg8 = "ICARUSDetectorControl provides users and machines with access to the ICARUS four-camera detection device.";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "ICARUSDetectorControl Version 0.2.1 ver\\u00f6ffentlicht am 30-12-2017";
		continf.TxtMsg2 = "\\u00a9 Mpsi Technologies GmbH";
		continf.TxtMsg4 = "Mitwirkende: Alexander Wirthmueller";
		continf.TxtMsg6 = "Programmbibliotheken: jpeg 8, opencv 2.4.8, netcdf 4.2.1.1, flycapture 2.8.3.1, devidhw 1.0.0 und aravis 0.6";
		continf.TxtMsg8 = "ICARUSDetectorControl erm\\u00f6glicht Benutzern und Ger\\u00e4ten Zugriff auf den ICARUS Vier-Kamera-Detektor.";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CLOSE, ixIdecVLocale, feedFMcbAlert);
	feedFMcbAlert.cap();
	// IP prepareAlrAbt --- END
	return(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
};

DpchEngIdecAlert* AlrIdec::prepareAlrPer(
			const ubigint jref
			, const uint ixIdecVLocale
			, const string& lineno
			, Feed& feedFMcbAlert
		) {
	ContInfIdecAlert continf;
	// IP prepareAlrPer --- BEGIN
	continf.TxtCpt = VecIdecVTag::getTitle(VecIdecVTag::ERROR, ixIdecVLocale);
	continf.TxtCpt = StrMod::cap(continf.TxtCpt);

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Parse error in line " + lineno + ".";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Syntaxfehler in Zeile " + lineno + ".";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::OK, ixIdecVLocale, feedFMcbAlert);
	feedFMcbAlert.cap();
	// IP prepareAlrPer --- END
	return(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
};

DpchEngIdecAlert* AlrIdec::prepareAlrSav(
			const ubigint jref
			, const uint ixIdecVLocale
			, Feed& feedFMcbAlert
		) {
	ContInfIdecAlert continf;
	// IP prepareAlrSav --- BEGIN
	continf.TxtCpt = VecIdecVTag::getTitle(VecIdecVTag::QUEST, ixIdecVLocale);
	continf.TxtCpt = StrMod::cap(continf.TxtCpt);

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Save changes?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "\\u00c4nderungen speichern?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::FLS, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::TRU, ixIdecVLocale, feedFMcbAlert);
	feedFMcbAlert.cap();
	// IP prepareAlrSav --- END
	return(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
};

/******************************************************************************
 class ReqIdec
 ******************************************************************************/

ReqIdec::ReqIdec(
			const uint ixVBasetype
			, const uint ixVState
			, const string& ip
		) {
	this->ixVBasetype = ixVBasetype;
	this->ixVState = ixVState;
	this->ip = ip;

	pp = NULL;

	if ((ixVBasetype == VecVBasetype::CMD) || (ixVBasetype == VecVBasetype::REGULAR) || (ixVBasetype == VecVBasetype::NOTIFY)
					|| (ixVBasetype == VecVBasetype::UPLOAD) || (ixVBasetype == VecVBasetype::DOWNLOAD)) {
		retain = false;
		Mutex::init(&mcReady, false, "mcReady", "ReqIdec", "ReqIdec");
		Cond::init(&cReady, "cReady", "ReqIdec", "ReqIdec");

	} else {
		retain = true;
	};

	file = NULL;
	filelen = 0;

	request = NULL;
	requestlen = 0;

	jref = 0;

	wref = 0;

	call = NULL;

	weak = false;

	dpchapp = NULL;

	dpcheng = NULL;
	ixIdecVLocale = VecIdecVLocale::ENUS;

	dpchinv = NULL;
	dpchret = NULL;

	reply = NULL;
	replylen = 0;
};

ReqIdec::~ReqIdec() {
	// specific data for base types REGULAR, NOTIFY, POLL, UPLOAD
	if (pp) MHD_destroy_post_processor(pp);

	// specific data for base types CMD, REGULAR, NOTIFY, UPLOAD, DOWNLOAD
	if ((ixVBasetype == VecVBasetype::CMD) || (ixVBasetype == VecVBasetype::REGULAR) || (ixVBasetype == VecVBasetype::NOTIFY)
					|| (ixVBasetype == VecVBasetype::UPLOAD) || (ixVBasetype == VecVBasetype::DOWNLOAD)) {
		Mutex::destroy(&mcReady, false, "mcReady", "ReqIdec", "~ReqIdec");
		Cond::destroy(&cReady, "cReady", "ReqIdec", "~ReqIdec");
	};

	// specific data for base types WEB, UPLOAD, DOWNLOAD
	if (file) {
		if (file->is_open()) file->close();
		delete file;
	};

	// specific data for base type EXTCALL
	if (call) delete call;

	// specific data for base types REGULAR, NOTIFY, POLL, RET
	if (request) delete[] request;

	// specific data for base types REGULAR
	if (dpchapp) delete dpchapp;

	// specific data for base types REGULAR, NOTIFY, POLL
	if (dpcheng) delete dpcheng;

	// specific data for base types RET
	if (dpchinv) delete dpchinv;
	if (dpchret) delete dpchret;

	// specific data for base types REGULAR, NOTIFY, POLL
	if (reply) delete[] reply;
};

void ReqIdec::setStateReply() {
	Mutex::lock(&mcReady, "mcReady", "ReqIdec", "setStateReply");
	ixVState = VecVState::REPLY;
	Mutex::unlock(&mcReady, "mcReady", "ReqIdec", "setStateReply");

	Cond::signal(&cReady, &mcReady, "cReady", "mcReady", "ReqIdec", "setStateReply");
};

/******************************************************************************
 class ReqopengconIdec
 ******************************************************************************/

ReqopengconIdec::ReqopengconIdec(
			const uint ixVState
			, const string& ip
		) {
	this->ixVState = ixVState;
	this->ip = ip;

	pp = NULL;

	request = NULL;
	requestlen = 0;

	dpchopd = NULL;

	reply = NULL;
	replylen = 0;
};

ReqopengconIdec::~ReqopengconIdec() {
	if (pp) MHD_destroy_post_processor(pp);

	if (request) delete[] request;

	if (dpchopd) delete dpchopd;

	if (reply) delete[] reply;
};

/******************************************************************************
 class DcolIdec
 ******************************************************************************/

DcolIdec::DcolIdec(
			const ubigint jref
			, const uint ixIdecVLocale
		) {
	this->jref = jref;
	this->ixIdecVLocale = ixIdecVLocale;

	Mutex::init(&mAccess, false, "mAccess", "DcolIdec", "DcolIdec");

	hot = false;

	req = NULL;
};

DcolIdec::~DcolIdec() {
	Mutex::lock(&mAccess, "mAccess", "DcolIdec", "~DcolIdec");
	Mutex::unlock(&mAccess, "mAccess", "DcolIdec", "~DcolIdec");
	Mutex::destroy(&mAccess, true, "mAccess", "DcolIdec", "~DcolIdec");

	for (auto it=dpchs.begin();it!=dpchs.end();it++) delete(*it);

	if (req) Cond::signal(&(req->cReady), &(req->mcReady), "req->cReady", "req->mcReady", "DcolIdec", "~DcolIdec");
};

int DcolIdec::lockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::lock(&mAccess, "dcol(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

int DcolIdec::unlockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::unlock(&mAccess, "dcol(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

/******************************************************************************
 class JobIdec
 ******************************************************************************/

JobIdec::JobIdec(
			XchgIdec* xchg
			, const uint ixIdecVJob
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) {
	this->xchg = xchg;

	jref = 0;

	this->ixIdecVJob = ixIdecVJob;

	this->jrefSup = jrefSup;

	this->ixIdecVLocale = ixIdecVLocale;

	jrefMast = 0;

	this->prefmast = prefmast;

	Mutex::init(&mAccess, true, "mAccess", VecIdecVJob::getSref(ixIdecVJob) + "(jrefSup=" + to_string(jrefSup) + ")", VecIdecVJob::getSref(ixIdecVJob));

	muteRefresh = false;

	ixVSge = 1;
	nextIxVSge = 1;

	opNdone = 0;
	opN = 0;

	Mutex::init(&mOps, true, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(jrefSup=" + to_string(jrefSup) + ")", VecIdecVJob::getSref(ixIdecVJob));

	wrefLast = 0;
	wrefMin = 0;

	reqCmd = NULL;
};

JobIdec::~JobIdec() {
	Mutex::lock(&mAccess, "mAccess", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "~" + VecIdecVJob::getSref(ixIdecVJob));
	Mutex::unlock(&mAccess, "mAccess", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "~" + VecIdecVJob::getSref(ixIdecVJob));
	Mutex::destroy(&mAccess, true, "mAccess", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "~" + VecIdecVJob::getSref(ixIdecVJob));

	Mutex::destroy(&mOps, true, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "~" + VecIdecVJob::getSref(ixIdecVJob));

	if (reqCmd) delete reqCmd;
};

DpchEngIdec* JobIdec::getNewDpchEng(
			set<uint> items
		) {
	return new DpchEngIdecConfirm(true, jref, "");
};

void JobIdec::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
};

void JobIdec::refreshWithDpchEng(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	DpchEngIdec* _dpcheng = NULL;

	refresh(dbsidec, moditems);

	if (dpcheng) {
		_dpcheng = getNewDpchEng(moditems);

		if (*dpcheng) {
			if (_dpcheng->ixIdecVDpch == VecIdecVDpch::DPCHENGIDECCONFIRM) delete _dpcheng;
			else if (_dpcheng->ixIdecVDpch == (*dpcheng)->ixIdecVDpch) {
				(*dpcheng)->merge(_dpcheng);
				delete _dpcheng;

			} else xchg->submitDpch(_dpcheng);

		} else *dpcheng = _dpcheng;

	} else if (!moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
};

string JobIdec::getSquawk(
			DbsIdec* dbsidec
		) {
	return "";
};

void JobIdec::giveupMaster(
			DbsIdec* dbsidec
		) {
};

void JobIdec::giveupSlave(
			DbsIdec* dbsidec
		) {
};

void JobIdec::becomeMaster(
			DbsIdec* dbsidec
		) {
};

void JobIdec::becomeSlave(
			DbsIdec* dbsidec
		) {
};

bool JobIdec::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	return false;
};

void JobIdec::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
};

void JobIdec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
};

int JobIdec::lockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::lock(&mAccess, "job(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

int JobIdec::trylockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::trylock(&mAccess, "job(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

int JobIdec::unlockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::unlock(&mAccess, "job(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

int JobIdec::lockAccess(
			const string& srefMember
		) {
	return Mutex::lock(&mAccess, "mAccess", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", srefMember);
};

int JobIdec::unlockAccess(
			const string& srefMember
		) {
	return Mutex::unlock(&mAccess, "mAccess", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", srefMember);
};

void JobIdec::clearInvs() {
	for (unsigned int i=0;i<invs.size();i++) delete invs[i];
	invs.clear();
};

ubigint JobIdec::addInv(
			DpchInvIdec* inv
		) {
	inv->oref = xchg->orefseq->getNewRef();
	inv->jref = jref;

	invs.push_back(inv);

	opN++;

	return(inv->oref);
};

void JobIdec::addInvs(
			vector<DpchInvIdec*>& _invs
		) {
	for (unsigned int i=0;i<_invs.size();i++) addInv(_invs[i]);
};

void JobIdec::submitInvs(
			DbsIdec* dbsidec
			, const uint emptyIxVSge
			, uint& _ixVSge
		) {
	if (opN == 0) {
		_ixVSge = emptyIxVSge;

	} else {
		xchg->addInvs(dbsidec, jref, invs);
		invs.clear();
	};
};

void JobIdec::clearOps() {
	Mutex::lock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "clearOps");

	for (auto it=ops.begin();it!=ops.end();it++) delete(*it);
	ops.clear();

	Mutex::unlock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "clearOps");
};

void JobIdec::addOp(
			DbsIdec* dbsidec
			, DpchInvIdec* inv
		) {
	string squawk;

	Mutex::lock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "addOp");

	// generate squawk

	// append to op list
	ops.push_back(new Op(inv->oref, inv->ixIdecVDpch, squawk));

	Mutex::unlock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "addOp");
};

void JobIdec::removeOp(
			const ubigint oref
		) {
	Op* op = NULL;

	Mutex::lock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "removeOp");

	for (auto it=ops.begin();it!=ops.end();it++) {
		op = *it;

		if (op->oref == oref) {
			// found
			ops.erase(it);

			// keep squawk of this op
			opsqkLast = op->squawk;

			delete op;
			
			break;
		};
	};

	Mutex::unlock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "removeOp");
};

string JobIdec::getOpsqkLast() {
	string retval;

	Mutex::lock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "getOpsqkLast");

	retval = opsqkLast;

	Mutex::unlock(&mOps, "mOps", VecIdecVJob::getSref(ixIdecVJob) + "(" + to_string(jref) + ")", "getOpsqkLast");

	return retval;
};

void JobIdec::callback(
			const uint _nextIxVSge
		) {
	nextIxVSge = _nextIxVSge;
	wrefLast = xchg->addWakeup(jref, "callback", 0);
};

void JobIdec::invalidateWakeups() {
	wrefMin = wrefLast + 1;
};

/******************************************************************************
 class StmgrIdec
 ******************************************************************************/

StmgrIdec::StmgrIdec(
			XchgIdec* xchg
			, const ubigint jref
			, const uint ixVNonetype
		) {
	this->xchg = xchg;

	this->jref = jref;
	this->ixVNonetype = ixVNonetype;

	stcch = new Stcch(true);

	Mutex::init(&mAccess, true, "mAccess", "StmgrIdec(" + to_string(jref) + ")", "StmgrIdec");
};

StmgrIdec::~StmgrIdec() {
	Mutex::lock(&mAccess, "mAccess", "StmgrIdec(" + to_string(jref) + ")", "~StmgrIdec");
	Mutex::unlock(&mAccess, "mAccess", "StmgrIdec(" + to_string(jref) + ")", "~StmgrIdec");
	Mutex::destroy(&mAccess, true, "mAccess", "StmgrIdec(" + to_string(jref) + ")", "~StmgrIdec");

	delete stcch;
};

void StmgrIdec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	set<uint> icsIdecVStub;
	pair<multimap<stcchitemref_t,Stcchitem*>::iterator,multimap<stcchitemref_t,Stcchitem*>::iterator> rng;

	bool notif = false;

	begin();

	if (call->ixVCall == VecIdecVCall::CALLIDECFILUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECFILSTD);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMISUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECMISSTD);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECPRSUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECPRSSTD);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSESUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECSESMENU);
		insert(icsIdecVStub, VecIdecVStub::STUBIDECSESSTD);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTOUUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECTOUSTD);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSGUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECUSGSTD);
		insert(icsIdecVStub, VecIdecVStub::STUBIDECGRP);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRUPD_REFEQ) {
		insert(icsIdecVStub, VecIdecVStub::STUBIDECUSRSTD);
		insert(icsIdecVStub, VecIdecVStub::STUBIDECOWN);
	};

	for (auto it=icsIdecVStub.begin();it!=icsIdecVStub.end();it++) {
		rng = stcch->nodes.equal_range(stcchitemref_t(*it, call->argInv.ref, 0));
		for (auto it2=rng.first;it2!=rng.second;it2++) if (refresh(dbsidec, it2->second)) notif = true;
	};

	commit();

	if (notif) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTUBCHG, jref);
};

bool StmgrIdec::refresh(
			DbsIdec* dbsidec
			, Stcchitem* stit
		) {
	set<stcchitemref_t> strefsSub_backup;
	string stub_backup;

	while (!stit->strefsSup.empty()) stcch->unlink(*stit->strefsSup.begin(), stit->stref);

	strefsSub_backup = stit->strefsSub;
	stub_backup = stit->stub;

	StubIdec::getStub(dbsidec, stit->stref.ixVStub, stit->stref.ref, stit->stref.ixVLocale, ixVNonetype, stcch, NULL, true);

	if (stit->stub != stub_backup) {
		for (auto it=strefsSub_backup.begin();it!=strefsSub_backup.end();it++) refresh(dbsidec, stcch->getStitByStref(*it));
		return true;
	} else return false;
};

void StmgrIdec::begin() {
	stcch->begin();
};

void StmgrIdec::commit() {
	for (auto it=stcch->icsVStubNew.begin();it!=stcch->icsVStubNew.end();it++) {
		if (*it == VecIdecVStub::STUBIDECFILSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECFILUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECGRP) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECUSGUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECMISSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECMISUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECOWN) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECUSRUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECPRSSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECPRSUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECSESMENU) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECSESUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECSESSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECSESUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECTOUSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECTOUUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECUSGSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECUSGUPD_REFEQ, jref);
		} else if (*it == VecIdecVStub::STUBIDECUSRSTD) {
			xchg->addClstnStmgr(VecIdecVCall::CALLIDECUSRUPD_REFEQ, jref);
		};
	};

	stcch->commit();
};

int StmgrIdec::lockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::lock(&mAccess, "stmgr(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

int StmgrIdec::unlockAccess(
			const string& srefObject
			, const string& srefMember
		) {
	return Mutex::unlock(&mAccess, "stmgr(" + to_string(jref) + ")->mAccess", srefObject, srefMember);
};

/******************************************************************************
 class WakeupIdec
 ******************************************************************************/

WakeupIdec::WakeupIdec(
			XchgIdec* xchg
			, const ubigint wref
			, const ubigint jref
			, const string sref
			, const unsigned int deltat
			, const bool weak
		) {
	this->xchg = xchg;
	this->wref = wref;
	this->jref = jref;
	this->sref = sref;
	this->deltat = deltat;
	this->weak = weak;
};

/******************************************************************************
 class ExtcallIdec
 ******************************************************************************/

ExtcallIdec::ExtcallIdec(
			XchgIdec* xchg
			, Call* call
		) {
	this->xchg = xchg;
	this->call = call;
};

/******************************************************************************
 class ConopengIdec
 ******************************************************************************/

ConopengIdec::ConopengIdec(
			const string& ip
			, const uint port
		) {
	string url;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		url = "http://" + ip + ":" + to_string(port) + "/dpch";
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	};

	busy = true;
};

ConopengIdec::~ConopengIdec() {
	if (curl) curl_easy_cleanup(curl);
};

/******************************************************************************
 class NodeIdec
 ******************************************************************************/

NodeIdec::NodeIdec(
			const ubigint nref
			, const string& ip
			, const uint port
			, const uint opprcn
			, const uint ixIdecVOpengtype
		) {
	this->nref = nref;
	this->ip = ip;
	this->port = port;
	this->opprcn = opprcn;
	this->ixIdecVOpengtype = ixIdecVOpengtype;

	vector<uint> icsIdecVOppack;
	
	OpengIdec::getIcsIdecVOppackByIxIdecVOpengtype(ixIdecVOpengtype, icsIdecVOppack);
	for (unsigned int i=0;i<icsIdecVOppack.size();i++) OpengIdec::getIcsIdecVDpchByIxIdecVOppack(icsIdecVOppack[i], icsIdecVDpch);

	opprcbusy = 0;

	err = false;

	Mutex::init(&mCons, false, "mCons", "NodeIdec", "NodeIdec");
};

NodeIdec::~NodeIdec() {
	Mutex::destroy(&mCons, false, "mCons", "NodeIdec", "~NodeIdec");

	for (unsigned int i=0;i<cons.size();i++) delete cons[i];
};

ConopengIdec* NodeIdec::getCon() {
	ConopengIdec* con;

	Mutex::lock(&mCons, "mCons", "NodeIdec", "getCon");

	con = NULL;

	// look for existing connections that are idle
	for (unsigned int i=0;i<cons.size();i++) {
		if (!cons[i]->busy) {
			con = cons[i];
			con->busy = true;
			break;
		};
	};

	if (!con) {
		// create new connection
		con = new ConopengIdec(ip, port);
		cons.push_back(con);
	};

	Mutex::unlock(&mCons, "mCons", "NodeIdec", "getCon");

	return con;
};

// IP datajobprc.subs --- INSERT

/******************************************************************************
 class XchgdataIdecJobprc
 ******************************************************************************/

XchgdataIdecJobprc::XchgdataIdecJobprc() {
};

// IP XchgdataJobIdecFusion.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecFusion
 ******************************************************************************/

XchgdataJobIdecFusion::XchgdataJobIdecFusion() {
};

// IP XchgdataJobIdecIllum.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecIllum
 ******************************************************************************/

XchgdataJobIdecIllum::XchgdataJobIdecIllum() {
};

// IP XchgdataJobIdecLwiracq.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecLwiracq
 ******************************************************************************/

XchgdataJobIdecLwiracq::XchgdataJobIdecLwiracq() {
};

// IP XchgdataJobIdecMechctl.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecMechctl
 ******************************************************************************/

XchgdataJobIdecMechctl::XchgdataJobIdecMechctl() {
};

// IP XchgdataJobIdecQcdacq.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecQcdacq
 ******************************************************************************/

XchgdataJobIdecQcdacq::XchgdataJobIdecQcdacq() {
};

// IP XchgdataJobIdecSpotfind.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecSpotfind
 ******************************************************************************/

XchgdataJobIdecSpotfind::XchgdataJobIdecSpotfind() {
};

// IP XchgdataJobIdecStereo.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecStereo
 ******************************************************************************/

XchgdataJobIdecStereo::XchgdataJobIdecStereo() {
};

// IP XchgdataJobIdecTrigger.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecTrigger
 ******************************************************************************/

XchgdataJobIdecTrigger::XchgdataJobIdecTrigger() {
};

// IP XchgdataJobIdecVislacq.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecVislacq
 ******************************************************************************/

XchgdataJobIdecVislacq::XchgdataJobIdecVislacq() {
};

// IP XchgdataJobIdecVisracq.subs --- INSERT

/******************************************************************************
 class XchgdataJobIdecVisracq
 ******************************************************************************/

XchgdataJobIdecVisracq::XchgdataJobIdecVisracq() {
};

/******************************************************************************
 class XchgIdecd
 ******************************************************************************/

XchgIdecd::XchgIdecd() {
	// root job
	jrefRoot = 0;

	// job receiving commands
	jrefCmd = 0;

	// scrambled ref codes
	Mutex::init(&mScr, true, "mScr", "XchgIdecd", "XchgIdecd");

	// log file
	Mutex::init(&mLogfile, true, "mLogfile", "XchgIdecd", "XchgIdecd");

	// condition for op engine client
	Mutex::init(&mcOpengcli, true, "mcOpengcli", "XchgIdecd", "XchgIdecd");
	Cond::init(&cOpengcli, "cOpengcli", "XchgIdecd", "XchgIdecd");

	// condition for job processors
	Mutex::init(&mcJobprcs, true, "mcJobprcs", "XchgIdecd", "XchgIdecd");
	Cond::init(&cJobprcs, "cJobprcs", "XchgIdecd", "XchgIdecd");

	// request list
	Mutex::init(&mReqs, true, "mReqs", "XchgIdecd", "XchgIdecd");

	// operation invocation list
	orefseq = new Refseq("orefseq");
	Mutex::init(&mInvs, true, "mInvs", "XchgIdecd", "XchgIdecd");

	// presetting list
	Mutex::init(&mPresets, true, "mPresets", "XchgIdecd", "XchgIdecd");

	// stub manager list
	Mutex::init(&mStmgrs, true, "mStmgrs", "XchgIdecd", "XchgIdecd");

	// call listener list
	Mutex::init(&mClstns, true, "mClstns", "XchgIdecd", "XchgIdecd");

	// dispatch collector list
	Mutex::init(&mDcols, true, "mDcols", "XchgIdecd", "XchgIdecd");

	// job list
	jrefseq = new Refseq("jrefseq");
	Mutex::init(&mJobs, true, "mJobs", "XchgIdecd", "XchgIdecd");

	// sequence for wakeup references
	wrefseq = new Refseq("wrefseq");

	// node list
	nrefseq = new Refseq("nrefseq");
	Mutex::init(&mNodes, true, "mNodes", "XchgIdecd", "XchgIdecd");

	curlrecv = NULL;
	curlrecvlen = 0;
};

XchgIdecd::~XchgIdecd() {
	// empty out lists
	for (auto it=reqs.begin();it!=reqs.end();it++) delete(*it);
	for (auto it=invs.begin();it!=invs.end();it++) delete(*it);
	for (auto it=presets.begin();it!=presets.end();it++) delete(it->second);
	for (auto it=stmgrs.begin();it!=stmgrs.end();it++) delete(it->second);
	for (auto it=clstns.begin();it!=clstns.end();it++) delete(it->second);
	for (auto it=dcols.begin();it!=dcols.end();it++) delete(it->second);
	for (auto it=jobs.begin();it!=jobs.end();it++) delete(it->second);
	for (auto it=nodes.begin();it!=nodes.end();it++) delete(it->second);

	// scrambled ref codes
	Mutex::destroy(&mScr, true, "mScr", "XchgIdecd", "~XchgIdecd");

	// log file
	Mutex::destroy(&mLogfile, true, "mLogfile", "XchgIdecd", "~XchgIdecd");

	// condition for op engine client
	Mutex::destroy(&mcOpengcli, true, "mcOpengcli", "XchgIdecd", "~XchgIdecd");
	Cond::destroy(&cOpengcli, "cOpengcli", "XchgIdecd", "~XchgIdecd");

	// condition for job processors
	Mutex::destroy(&mcJobprcs, true, "mcJobprcs", "XchgIdecd", "~XchgIdecd");
	Cond::destroy(&cJobprcs, "cJobprcs", "XchgIdecd", "~XchgIdecd");

	// request list
	Mutex::destroy(&mReqs, true, "mReqs", "XchgIdecd", "~XchgIdecd");

	// operation invocation list
	delete orefseq;
	Mutex::destroy(&mInvs, true, "mInvs", "XchgIdecd", "~XchgIdecd");

	// presetting list
	Mutex::destroy(&mPresets, true, "mPresets", "XchgIdecd", "~XchgIdecd");

	// stub manager list
	Mutex::destroy(&mStmgrs, true, "mStmgrs", "XchgIdecd", "~XchgIdecd");

	// call listener list
	Mutex::destroy(&mClstns, true, "mClstns", "XchgIdecd", "~XchgIdecd");

	// dispatch collector list
	Mutex::destroy(&mDcols, true, "mDcols", "XchgIdecd", "~XchgIdecd");

	// job list
	delete jrefseq;
	Mutex::destroy(&mJobs, true, "mJobs", "XchgIdecd", "~XchgIdecd");

	// sequence for wakeup references
	delete wrefseq;

	// node list
	delete nrefseq;
	Mutex::destroy(&mNodes, true, "mNodes", "XchgIdecd", "~XchgIdecd");
};

// IP cust --- INSERT

void XchgIdecd::startMon() {
	JobIdec* job = NULL;

	DcolIdec* dcol = NULL;
	bool Dcol;

	StmgrIdec* stmgr = NULL;
	bool Stmgr;

	Clstn* clstn = NULL;
	Preset* preset = NULL;
	NodeIdec* node = NULL;

	mon.start("ICARUSDetectorControl 0.2.1", stgidecmonitor.ixDbsVDbstype, stgidecmonitor.dbspath, stgidecmonitor.dbsname, stgidecmonitor.ip, stgidecmonitor.port, stgidecmonitor.dbsusername, stgidecmonitor.dbspassword, stgidecmonitor.username, stgidecmonitor.password);

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "startMon");
	for (auto it=jobs.begin();it!=jobs.end();it++) {
		job = it->second;

		dcol = getDcolByJref(job->jref, false);
		if (dcol) {
			Dcol = true;
			dcol->unlockAccess("XchgIdecd", "startMon");
		} else Dcol = false;

		stmgr = getStmgrByJref(job->jref);
		if (stmgr) {
			Stmgr = true;
			stmgr->unlockAccess("XchgIdecd", "startMon");
		} else Stmgr = false;

		mon.insertJob(job->jrefSup, VecIdecVJob::getSref(job->ixIdecVJob), job->jref, (job->jrefMast == job->jref), (job->jrefMast == job->jref) && (job->jrefMast != 0), Dcol, Stmgr);
	};
	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "startMon");

	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "startMon");
	for (auto it=clstns.begin();it!=clstns.end();it++) {
		clstn = it->second;
		mon.insertClstn(clstn->cref.jref, VecIdecVCall::getSref(clstn->cref.ixVCall), clstn->cref.stmgr, Clstn::VecVJobmask::getSref(clstn->cref.ixVJobmask), clstn->cref.jrefTrig, clstn->argMask.writeText(), Clstn::VecVJactype::getSref(clstn->ixVJactype));
	};
	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "startMon");

	Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "startMon");
	for (auto it=presets.begin();it!=presets.end();it++) {
		preset = it->second;
		mon.insertPreset(preset->pref.jref, VecIdecVPreset::getSref(preset->pref.ixVPreset), preset->arg.writeText());
	};
	Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "startMon");

	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "startMon");
	for (auto it=nodes.begin();it!=nodes.end();it++) {
		node = it->second;
		mon.insertNode(node->nref, node->ip, node->port, node->opprcn);
	};
	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "startMon");

	triggerCall(NULL, VecIdecVCall::CALLIDECMONSTATCHG, jrefRoot);
};

void XchgIdecd::stopMon() {
	mon.stop();

	triggerCall(NULL, VecIdecVCall::CALLIDECMONSTATCHG, jrefRoot);
};

void XchgIdecd::appendToLogfile(
			const string& str
		) {
	time_t rawtime;
	fstream logfile;

	Mutex::lock(&mLogfile, "mLogfile", "XchgIdecd", "appendToLogfile");

	time(&rawtime);

	logfile.open("./log.txt", ios::out | ios::app);
	logfile << Ftm::stamp(rawtime) << ": " << str << endl;
	logfile.close();

	Mutex::unlock(&mLogfile, "mLogfile", "XchgIdecd", "appendToLogfile");
};

void XchgIdecd::addReq(
			ReqIdec* req
		) {
	Mutex::lock(&mReqs, "mReqs", "XchgIdecd", "addReq");

	req->ixVState = ReqIdec::VecVState::WAITPRC;
	reqs.push_back(req);

	Mutex::unlock(&mReqs, "mReqs", "XchgIdecd", "addReq");

	Cond::signal(&cJobprcs, &mcJobprcs, "cJobprcs", "mcJobprcs", "XchgIdecd", "addReq");
};

ReqIdec* XchgIdecd::pullFirstReq() {
	ReqIdec* req;

	// get first element from list
	Mutex::lock(&mReqs, "mReqs", "XchgIdecd", "pullFirstReq");

	req = NULL;

	if (!reqs.empty()) {
		req = *(reqs.begin());
		req->ixVState = ReqIdec::VecVState::PRC;
		reqs.pop_front();
	};

	Mutex::unlock(&mReqs, "mReqs", "XchgIdecd", "pullFirstReq");

	return req;
};

void XchgIdecd::addInvs(
			DbsIdec* dbsidec
			, const ubigint jref
			, vector<DpchInvIdec*>& dpchinvs
		) {
	JobIdec* job;

	job = getJobByJref(jref);

	if (job != NULL) {
		// append to inv list and signal the news (note the double-lock)
		Mutex::lock(&mInvs, "mInvs", "XchgIdecd", "addInvs");
		Mutex::lock(&(job->mOps), "job->mOps", "XchgIdecd", "addInvs");

		for (unsigned int i=0;i<dpchinvs.size();i++) {
			job->addOp(dbsidec, dpchinvs[i]);

			invs.push_back(dpchinvs[i]);

			mon.eventAddInv(jref, VecIdecVDpch::getSref(dpchinvs[i]->ixIdecVDpch), "", dpchinvs[i]->oref);
		};

		Mutex::unlock(&(job->mOps), "job->mOps", "XchgIdecd", "addInvs");
		Mutex::unlock(&mInvs, "mInvs", "XchgIdecd", "addInvs");

		Cond::signal(&cOpengcli, &mcOpengcli, "cOpengcli", "mcOpengcli", "XchgIdecd", "addInvs");
	};
};

bool XchgIdecd::pullFirstInv(
			DpchInvIdec** dpchinv
			, NodeIdec** node
		) {
	bool match = false;

	// retrieve first match inv-node
	Mutex::lock(&mInvs, "mInvs", "XchgIdecd", "pullFirstInv");
	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "pullFirstInv");

	for (auto it=invs.begin();it!=invs.end();it++) {
		*dpchinv = *it;

		for (auto it2=nodes.begin();it2!=nodes.end();it2++) {
			*node = it2->second;

			if ( ((*node)->opprcbusy < (*node)->opprcn) && !(*node)->err ) {

				// node available ; check compatibility with inv

				if ((*node)->icsIdecVDpch.find((*dpchinv)->ixIdecVDpch) != (*node)->icsIdecVDpch.end()) {
					// match found

					// remove inv from list
					invs.erase(it);

					// increase busy count for node
					(*node)->opprcbusy++;

					match = true;
					break;
				};
			};

			if (match) break;
		};
		if (match) break;
	};

	if (!match) {
		*dpchinv = NULL;
		*node = NULL;
	};

	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "pullFirstInv");
	Mutex::unlock(&mInvs, "mInvs", "XchgIdecd", "pullFirstInv");

	return(match);
};

void XchgIdecd::returnInv(
			DpchInvIdec* dpchinv
		) {
	// un-successful execution of op returns

	// append to inv list and signal the news
	Mutex::lock(&mInvs, "mInvs", "XchgIdecd", "returnInv");
	invs.push_back(dpchinv);
	Mutex::unlock(&mInvs, "mInvs", "XchgIdecd", "returnInv");

	Cond::signal(&cOpengcli, &mcOpengcli, "cOpengcli", "mcOpengcli", "XchgIdecd", "returnInv");
};

Preset* XchgIdecd::addPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const Arg& arg
		) {
	presetref_t pref(jref, ixIdecVPreset);
	Preset* preset;

	// create new presetting (override value if exists) and append to presetting list
	Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "addPreset");

	preset = getPresetByPref(pref);

	if (preset) {
		preset->arg = arg;

		mon.eventChangePreset(jref, VecIdecVPreset::getSref(ixIdecVPreset), arg.writeText());

	} else {
		preset = new Preset(pref, arg);
		presets.insert(pair<presetref_t,Preset*>(pref, preset));

		mon.eventAddPreset(jref, VecIdecVPreset::getSref(ixIdecVPreset), arg.writeText());
	};

	Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "addPreset");

	return(preset);
};

Preset* XchgIdecd::addIxPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const uint ix
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(ix, 0, {}, "", 0, 0.0, false, "", Arg::IX)));
};

Preset* XchgIdecd::addRefPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const ubigint ref
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(0, ref, {}, "", 0, 0.0, false, "", Arg::REF)));
};

Preset* XchgIdecd::addRefsPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const vector<ubigint>& refs
		) {
	Arg arg(0, 0, refs, "", 0, 0.0, false, "", Arg::REFS);

	return(addPreset(ixIdecVPreset, jref, arg));
};

Preset* XchgIdecd::addSrefPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const string& sref
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(0, 0, {}, sref, 0, 0.0, false, "", Arg::SREF)));
};

Preset* XchgIdecd::addIntvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const int intval
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(0, 0, {}, "", intval, 0.0, false, "", Arg::INTVAL)));
};

Preset* XchgIdecd::addDblvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const double dblval
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(0, 0, {}, "", 0, dblval, false, "", Arg::DBLVAL)));
};

Preset* XchgIdecd::addBoolvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const bool boolval
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(0, 0, {}, "", 0, 0.0, boolval, "", Arg::BOOLVAL)));
};

Preset* XchgIdecd::addTxtvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
			, const string& txtval
		) {
	return(addPreset(ixIdecVPreset, jref, Arg(0, 0, {}, "", 0, 0.0, false, txtval, Arg::TXTVAL)));
};

Preset* XchgIdecd::getPresetByPref(
			const presetref_t& pref
		) {
	Preset* preset = NULL;

	Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "getPresetByPref");

	auto it = presets.find(pref);
	if (it != presets.end()) preset = it->second;

	Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "getPresetByPref");

	return preset;
};

Arg XchgIdecd::getPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg;

	JobIdec* job = NULL;
	Preset* preset = NULL;

	if ( (ixIdecVPreset == VecIdecVPreset::PREIDECSYSDATE) || (ixIdecVPreset == VecIdecVPreset::PREIDECSYSTIME) || (ixIdecVPreset == VecIdecVPreset::PREIDECSYSSTAMP) ) {
		time_t rawtime;
		time(&rawtime);

		arg.mask = Arg::INTVAL;

		if (ixIdecVPreset == VecIdecVPreset::PREIDECSYSDATE) arg.intval = (rawtime-rawtime%(3600*24))/(3600*24);
		else if (ixIdecVPreset == VecIdecVPreset::PREIDECSYSTIME) arg.intval = rawtime%(3600*24);
		else if (ixIdecVPreset == VecIdecVPreset::PREIDECSYSSTAMP) arg.intval = rawtime;

	} else {
		Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "getPreset");
		Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "getPreset");
		
		job = getJobByJref(jref);

		if ( (job != NULL) && (ixIdecVPreset == VecIdecVPreset::PREIDECIXLCL) ) {
			arg.mask = Arg::IX;
			arg.ix = job->ixIdecVLocale;

		} else {
			while (job && !preset) {
				preset = getPresetByPref(presetref_t(job->jref, ixIdecVPreset));

				if (preset) arg = preset->arg;
				else job = getJobByJref(job->jrefSup);
			};
		};

		Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "getPreset");
		Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "getPreset");
	};

	return(arg);
};

uint XchgIdecd::getIxPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::IX) return(arg.ix);
	else return(0);
};

ubigint XchgIdecd::getRefPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::REF) return(arg.ref);
	else return(0);
};

vector<ubigint> XchgIdecd::getRefsPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);
	vector<ubigint> empty;

	if (arg.mask & Arg::REFS) return(arg.refs);
	else return(empty);
};

string XchgIdecd::getSrefPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::SREF) return(arg.sref);
	else return("");
};

int XchgIdecd::getIntvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::INTVAL) return(arg.intval);
	else return(intvalInvalid);
};

double XchgIdecd::getDblvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::DBLVAL) return(arg.dblval);
	else return(dblvalInvalid);
};

bool XchgIdecd::getBoolvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::BOOLVAL) return(arg.boolval);
	else return(false);
};

string XchgIdecd::getTxtvalPreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Arg arg = getPreset(ixIdecVPreset, jref);

	if (arg.mask & Arg::TXTVAL) return(arg.txtval);
	else return("");
};

void XchgIdecd::getPresetsByJref(
			const ubigint jref
			, vector<uint>& icsIdecVPreset
			, vector<Arg>& args
		) {
	Preset* preset = NULL;

	icsIdecVPreset.clear();
	args.clear();

	Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "getPresetsByJref");

	auto rng = presets.equal_range(presetref_t(jref, 0));
	for (auto it=rng.first;it!=rng.second;it++) {
		preset = it->second;

		icsIdecVPreset.push_back(preset->pref.ixVPreset);
		args.push_back(preset->arg);
	};

	Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "getPresetsByJref");
};

void XchgIdecd::removePreset(
			const uint ixIdecVPreset
			, const ubigint jref
		) {
	Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "removePreset");

	auto it = presets.find(presetref_t(jref, ixIdecVPreset));
	if (it != presets.end()) {
		delete it->second;
		presets.erase(it);

		mon.eventRemovePreset(jref, VecIdecVPreset::getSref(ixIdecVPreset));
	};

	Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "removePreset");
};

void XchgIdecd::removePresetsByJref(
			const ubigint jref
		) {
	Mutex::lock(&mPresets, "mPresets", "XchgIdecd", "removePresetsByJref");

	uint ixVPreset;

	auto rng = presets.equal_range(presetref_t(jref, 0));
	for (auto it=rng.first;it!=rng.second;it++) {
		ixVPreset = it->second->pref.ixVPreset;
		delete it->second;

		mon.eventRemovePreset(jref, VecIdecVPreset::getSref(ixVPreset));
	};
	presets.erase(rng.first, rng.second);

	Mutex::unlock(&mPresets, "mPresets", "XchgIdecd", "removePresetsByJref");
};

StmgrIdec* XchgIdecd::addStmgr(
			const ubigint jref
			, const uint ixVNonetype
		) {
	StmgrIdec* stmgr = NULL;

	// create new stmgr and append to stmgr list
	Mutex::lock(&mStmgrs, "mStmgrs", "XchgIdecd", "addStmgr");

	stmgr = getStmgrByJref(jref);

	if (!stmgr) {
		stmgr = new StmgrIdec(this, jref, ixVNonetype);
		stmgrs[jref] = stmgr;

		mon.eventAddStmgr(jref);
	};

	Mutex::unlock(&mStmgrs, "mStmgrs", "XchgIdecd", "addStmgr");

	return(stmgr);
};

StmgrIdec* XchgIdecd::getStmgrByJref(
			const ubigint jref
		) {
	StmgrIdec* stmgr = NULL;

	Mutex::lock(&mStmgrs, "mStmgrs", "XchgIdecd", "getStmgrByJref");

	auto it = stmgrs.find(jref);

	if (it != stmgrs.end()) {
		stmgr = it->second;
		stmgr->lockAccess("XchgIdecd", "getStmgrByJref");
	};

	Mutex::unlock(&mStmgrs, "mStmgrs", "XchgIdecd", "getStmgrByJref");

	return(stmgr);
};

void XchgIdecd::removeStmgrByJref(
			const ubigint jref
		) {
	Mutex::lock(&mStmgrs, "mStmgrs", "XchgIdecd", "removeStmgrByJref");

	removeClstnsByJref(jref, true);

	auto it = stmgrs.find(jref);
	if (it != stmgrs.end()) {
		delete it->second;
		stmgrs.erase(it);

		mon.eventRemoveStmgr(jref);
	};

	Mutex::unlock(&mStmgrs, "mStmgrs", "XchgIdecd", "removeStmgrByJref");
};

Clstn* XchgIdecd::addClstn(
			const uint ixIdecVCall
			, const ubigint jref
			, const uint ixVJobmask
			, const ubigint jrefTrig
			, const Arg& argMask
			, const uint ixVJactype
		) {
	clstnref_t cref(ixIdecVCall, jref, false, ixVJobmask, jrefTrig);
	clstnref2_t cref2(cref);
	Clstn* clstn;

	// create new clstn and append to clstn list
	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "addClstn");

	clstn = getClstnByCref(cref);

	if (clstn) {
		clstn->argMask = argMask;
		clstn->ixVJactype = ixVJactype;

		mon.eventChangeClstn(jref, VecIdecVCall::getSref(ixIdecVCall), false, Clstn::VecVJobmask::getSref(ixVJobmask), jrefTrig, argMask.writeText(), Clstn::VecVJactype::getSref(ixVJactype));

	} else {
		clstn = new Clstn(cref, argMask, ixVJactype);
		clstns.insert(pair<clstnref_t,Clstn*>(cref, clstn));
		cref2sClstns.insert(pair<clstnref2_t,clstnref_t>(cref2, cref));

		mon.eventAddClstn(jref, VecIdecVCall::getSref(ixIdecVCall), false, Clstn::VecVJobmask::getSref(ixVJobmask), jrefTrig, argMask.writeText(), Clstn::VecVJactype::getSref(ixVJactype));
	};

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "addClstn");

	return(clstn);
};

Clstn* XchgIdecd::addIxClstn(
			const uint ixIdecVCall
			, const ubigint jref
			, const uint ixVJobmask
			, const ubigint jrefTrig
			, const uint ixMask
			, const uint ixVJactype
		) {
	Arg argMask(ixMask, 0, {}, "", 0, 0.0, false, "", Arg::IX);

	return(addClstn(ixIdecVCall, jref, ixVJobmask, jrefTrig, argMask, ixVJactype));
};

Clstn* XchgIdecd::addRefClstn(
			const uint ixIdecVCall
			, const ubigint jref
			, const uint ixVJobmask
			, const ubigint jrefTrig
			, const ubigint refMask
			, const uint ixVJactype
		) {
	Arg argMask(0, refMask, {}, "", 0, 0.0, false, "", Arg::REF);

	return(addClstn(ixIdecVCall, jref, ixVJobmask, jrefTrig, argMask, ixVJactype));
};

Clstn* XchgIdecd::addIxRefClstn(
			const uint ixIdecVCall
			, const ubigint jref
			, const uint ixVJobmask
			, const ubigint jrefTrig
			, const uint ixMask
			, const ubigint refMask
			, const uint ixVJactype
		) {
	Arg argMask(ixMask, refMask, {}, "", 0, 0.0, false, "", Arg::IX + Arg::REF);

	return(addClstn(ixIdecVCall, jref, ixVJobmask, jrefTrig, argMask, ixVJactype));
};

Clstn* XchgIdecd::addIxRefSrefClstn(
			const uint ixIdecVCall
			, const ubigint jref
			, const uint ixVJobmask
			, const ubigint jrefTrig
			, const uint ixMask
			, const ubigint refMask
			, const string& srefMask
			, const uint ixVJactype
		) {
	Arg argMask(ixMask, refMask, {}, srefMask, 0, 0.0, false, "", Arg::IX + Arg::REF + Arg::SREF);

	return(addClstn(ixIdecVCall, jref, ixVJobmask, jrefTrig, argMask, ixVJactype));
};

Clstn* XchgIdecd::addClstnStmgr(
			const uint ixIdecVCall
			, const ubigint jref
		) {
	clstnref_t cref(ixIdecVCall, jref, true, Clstn::VecVJobmask::ALL, 0);
	clstnref2_t cref2(cref);
	Clstn* clstn;

	// create new clstn and append to clstn list
	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "addClstnStmgr");

	clstn = getClstnByCref(cref);

	if (!clstn) {
		clstn = new Clstn(cref, Arg(), Clstn::VecVJactype::LOCK);
		clstns.insert(pair<clstnref_t,Clstn*>(cref, clstn));
		cref2sClstns.insert(pair<clstnref2_t,clstnref_t>(cref2, cref));

		mon.eventAddClstn(jref, VecIdecVCall::getSref(ixIdecVCall), true, Clstn::VecVJobmask::getSref(Clstn::VecVJobmask::ALL), 0, "", Clstn::VecVJactype::getSref(Clstn::VecVJactype::LOCK));
	};

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "addClstnStmgr");

	return(clstn);
};

Clstn* XchgIdecd::getClstnByCref(
			const clstnref_t& cref
		) {
	Clstn* clstn = NULL;

	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "getClstnByCref");

	auto it = clstns.find(cref);
	if (it != clstns.end()) clstn = it->second;

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "getClstnByCref");

	return clstn;
};

void XchgIdecd::getClstnsByJref(
			const ubigint jref
			, const bool stmgr
			, vector<uint>& icsIdecVCall
			, vector<uint>& icsVJobmask
		) {
	Clstn* clstn = NULL;

	icsIdecVCall.clear();
	icsVJobmask.clear();

	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "getClstnsByJref");

	auto rng = cref2sClstns.equal_range(clstnref2_t(jref, stmgr, 0));
	for (auto it=rng.first;it!=rng.second;it++) {
		clstn = getClstnByCref(it->second);

		if (clstn) {
			icsIdecVCall.push_back(clstn->cref.ixVCall);
			icsVJobmask.push_back(clstn->cref.ixVJobmask);
		};
	};

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "getClstnsByJref");
};

void XchgIdecd::removeClstns(
			const uint ixIdecVCall
			, const ubigint jref
			, const bool stmgr
		) {
	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "removeClstns");

	uint ixVJobmask;
	ubigint jrefTrig;

	auto rng = clstns.equal_range(clstnref_t(ixIdecVCall, jref, stmgr));
	for (auto it=rng.first;it!=rng.second;it++) {
		ixVJobmask = it->second->cref.ixVJobmask;
		jrefTrig = it->second->cref.jrefTrig;

		cref2sClstns.erase(clstnref2_t(it->first));
		delete it->second;

		mon.eventRemoveClstn(jref, VecIdecVCall::getSref(ixIdecVCall), stmgr, Clstn::VecVJobmask::getSref(ixVJobmask), jrefTrig);
	};
	clstns.erase(rng.first, rng.second);

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "removeClstns");
};

void XchgIdecd::removeClstnsByJref(
			const ubigint jref
			, const bool stmgr
		) {
	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "removeClstnsByJref");

	uint ixVCall;
	uint ixVJobmask;
	ubigint jrefTrig;

	auto rng = cref2sClstns.equal_range(clstnref2_t(jref, stmgr));
	for (auto it=rng.first;it!=rng.second;it++) {
		auto it2 = clstns.find(it->second);

		ixVCall = it2->second->cref.ixVCall;
		ixVJobmask = it2->second->cref.ixVJobmask;
		jrefTrig = it2->second->cref.jrefTrig;

		delete it2->second;
		clstns.erase(it2);

		mon.eventRemoveClstn(jref, VecIdecVCall::getSref(ixVCall), stmgr, Clstn::VecVJobmask::getSref(ixVJobmask), jrefTrig);
	};
	cref2sClstns.erase(rng.first, rng.second);

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "removeClstnsByJref");
};

void XchgIdecd::findJrefsByCall(
			Call* call
			, vector<ubigint>& jrefs
			, vector<bool>& stmgrs
			, vector<uint>& icsVJactype
		) {
	Clstn* clstn = NULL;

	JobIdec* job = NULL;

	bool match;

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "findJrefsByCall");
	Mutex::lock(&mClstns, "mClstns", "XchgIdecd", "findJrefsByCall");

	auto rng = clstns.equal_range(clstnref_t(call->ixVCall, 0));
	for (auto it=rng.first;it!=rng.second;it++) {
		clstn = it->second;

		if (clstn->cref.stmgr) {
			jrefs.push_back(clstn->cref.jref);
			stmgrs.push_back(true);
			icsVJactype.push_back(0);

		} else {
			match = true;

			if (clstn->argMask.mask & Arg::IX) if (clstn->argMask.ix != call->argInv.ix) match = false;
			if (clstn->argMask.mask & Arg::REF) if (clstn->argMask.ref != call->argInv.ref) match = false;
			if (clstn->argMask.mask & Arg::SREF) if (clstn->argMask.sref != call->argInv.sref) match = false;
			if (clstn->argMask.mask & Arg::INTVAL) if (clstn->argMask.intval != call->argInv.intval) match = false;
			if (clstn->argMask.mask & Arg::DBLVAL) if (clstn->argMask.dblval != call->argInv.dblval) match = false;
			if (clstn->argMask.mask & Arg::BOOLVAL) if (clstn->argMask.boolval != call->argInv.boolval) match = false;
			if (clstn->argMask.mask & Arg::TXTVAL) if (clstn->argMask.txtval != call->argInv.txtval) match = false;

			if (match) {
				match = false;

				if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::ALL) {
					// don't care about call->jref
					match = true;

				} else if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::IMM) {
					// check if trigger job is immediate sub-job to listener job
					job = getJobByJref(call->jref);
					if (job) if (job->jrefSup == clstn->cref.jref) match = true;

				} else if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::MAST) {
					// check if trigger job is master-job to listener job
					if (call->jref != clstn->cref.jref) {
						job = getJobByJref(clstn->cref.jref);
						if (job) if (call->jref == job->jrefMast) match = true;
					};

				} else if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::SELF) {
					// check if trigger job is equivalent to listener job
					if (call->jref == clstn->cref.jref) match = true;

				} else if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::SLV) {
					// check if listener job is master-job to trigger job
					if (call->jref != clstn->cref.jref) {
						job = getJobByJref(call->jref);
						if (job) if (clstn->cref.jref == job->jrefMast) match = true;
					};

				} else if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::SPEC) {
					// require specific jref
					if (clstn->cref.jrefTrig == call->jref) match = true;

				} else if (clstn->cref.ixVJobmask == Clstn::VecVJobmask::TREE) {
					// check if trigger job is down the tree from listener job ; note that the order in jobs is unordered (unfortunately)
					job = getJobByJref(call->jref);

					while (job != NULL) {
						if (job->jref == clstn->cref.jref) {
							// add
							match = true;
							break;
						};

						job = getJobByJref(job->jrefSup);
					};
				};
			};

			if (match) {
				jrefs.push_back(clstn->cref.jref);
				stmgrs.push_back(false);
				icsVJactype.push_back(clstn->ixVJactype);
			};
		};
	};

	Mutex::unlock(&mClstns, "mClstns", "XchgIdecd", "findJrefsByCall");
	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "findJrefsByCall");
};

void XchgIdecd::triggerCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	vector<ubigint> jrefs;
	vector<bool> stmgrs;
	vector<uint> icsVJactype;

	ubigint jref;
	uint ixVJactype;

	StmgrIdec* stmgr = NULL;

	JobIdec* job = NULL;

	ubigint eref;

	Arg argRet_old;

	eref = mon.eventTriggerCall(call->jref, VecIdecVCall::getSref(call->ixVCall), call->argInv.writeText());

	findJrefsByCall(call, jrefs, stmgrs, icsVJactype);

	for (unsigned int i=0;i<jrefs.size();i++) {
		jref = jrefs[i];
		ixVJactype = icsVJactype[i];

		if (stmgrs[i]) {
			stmgr = getStmgrByJref(jref);

			if (stmgr) {
				mon.eventHandleCall(eref, jref);
				argRet_old = call->argRet;

				stmgr->handleCall(dbsidec, call);

				if (!(call->argRet == argRet_old)) mon.eventRetCall(eref, jref, call->argRet.writeText());

				stmgr->unlockAccess("XchgIdecd", "triggerCall");
			};

		} else {
			job = getJobByJref(jref);
			if (job) {
				if (ixVJactype != Clstn::VecVJactype::WEAK) {
					if (ixVJactype == Clstn::VecVJactype::LOCK) {
						job->lockAccess("XchgIdecd", "triggerCall");

					} else if (ixVJactype == Clstn::VecVJactype::TRY) {
						if (Mutex::trylock(&(job->mAccess), "job(" + to_string(jref) + ")->mAccess", "XchgIdecd", "triggerCall") == EBUSY) continue;
					};
				};

				mon.eventHandleCall(eref, jref);
				argRet_old = call->argRet;

				job->handleCall(dbsidec, call);

				if (call->argRet != argRet_old) mon.eventRetCall(eref, jref, call->argRet.writeText());
			};

			if (ixVJactype != Clstn::VecVJactype::WEAK) {
				job = getJobByJref(jref);
				if (job) job->unlockAccess("XchgIdecd", "triggerCall");
			};
		};

		if (call->abort) break;
	};

	mon.eventFinalizeCall(eref);
};

bool XchgIdecd::triggerArgToArgCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const Arg& argInv
			, Arg& argRet
		) {
	Call* call;
	ubigint retval;

  call = new Call(ixIdecVCall, jref, argInv);
	triggerCall(dbsidec, call);

	argRet = call->argRet;
	retval = call->abort;

  delete call;
	return retval;
};

bool XchgIdecd::triggerCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
		) {
	Arg argInv;
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIxCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
		) {
	Arg argInv(ixInv, 0, {}, "", 0, 0.0, false, "", Arg::IX);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerRefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const ubigint refInv
		) {
	Arg argInv(0, refInv, {}, "", 0, 0.0, false, "", Arg::REF);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIntvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const int intvalInv
		) {
	Arg argInv(0, 0, {}, "", intvalInv, 0.0, false, "", Arg::INTVAL);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerBoolvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const bool boolvalInv
		) {
	Arg argInv(0, 0, {}, "", 0, 0.0, boolvalInv, "", Arg::BOOLVAL);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIxRefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const ubigint refInv
		) {
	Arg argInv(ixInv, refInv, {}, "", 0, 0.0, false, "", Arg::IX + Arg::REF);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIxSrefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const string& srefInv
		) {
	Arg argInv(ixInv, 0, {}, srefInv, 0, 0.0, false, "", Arg::IX + Arg::SREF);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIxIntvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const int intvalInv
		) {
	Arg argInv(ixInv, 0, {}, "", intvalInv, 0.0, false, "", Arg::IX + Arg::INTVAL);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIxDblvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const double dblvalInv
		) {
	Arg argInv(ixInv, 0, {}, "", 0, dblvalInv, false, "", Arg::IX + Arg::DBLVAL);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerIxTxtvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const string& txtvalInv
		) {
	Arg argInv(ixInv, 0, {}, "", 0, 0.0, false, txtvalInv, Arg::IX + Arg::TXTVAL);
	Arg argRet;

	return(triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet));
};

bool XchgIdecd::triggerToBoolvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, bool& boolvalRet
		) {
	bool retval;

	Arg argInv;
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) boolvalRet = argRet.boolval;

	return(retval);
};

bool XchgIdecd::triggerIxToBoolvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, bool& boolvalRet
		) {
	bool retval;

	Arg argInv(ixInv, 0, {}, "", 0, 0.0, false, "", Arg::IX);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) boolvalRet = argRet.boolval;

	return(retval);
};

bool XchgIdecd::triggerRefToSrefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const ubigint refInv
			, string& srefRet
		) {
	bool retval;

	Arg argInv(0, refInv, {}, "", 0, 0.0, false, "", Arg::REF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) srefRet = argRet.sref;

	return(retval);
};

bool XchgIdecd::triggerRefToBoolvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const ubigint refInv
			, bool& boolvalRet
		) {
	bool retval;

	Arg argInv(0, refInv, {}, "", 0, 0.0, false, "", Arg::REF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) boolvalRet = argRet.boolval;

	return(retval);
};

bool XchgIdecd::triggerIxRefToIxCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const ubigint refInv
			, uint& ixRet
		) {
	bool retval;

	Arg argInv(ixInv, refInv, {}, "", 0, 0.0, false, "", Arg::IX + Arg::REF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) ixRet = argRet.ix;

	return(retval);
};

bool XchgIdecd::triggerIxRefToRefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const ubigint refInv
			, ubigint& refRet
		) {
	bool retval;

	Arg argInv(ixInv, refInv, {}, "", 0, 0.0, false, "", Arg::IX + Arg::REF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) refRet = argRet.ref;

	return(retval);
};

bool XchgIdecd::triggerIxRefSrefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const ubigint refInv
			, const string& srefInv
		) {
	bool retval;

	Arg argInv(ixInv, refInv, {}, srefInv, 0, 0.0, false, "", Arg::IX + Arg::REF + Arg::SREF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	return(retval);
};

bool XchgIdecd::triggerIxRefSrefIntvalCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const ubigint refInv
			, const string& srefInv
			, const int intvalInv
		) {
	bool retval;

	Arg argInv(ixInv, refInv, {}, srefInv, intvalInv, 0.0, false, "", Arg::IX + Arg::REF + Arg::SREF + Arg::INTVAL);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	return(retval);
};

bool XchgIdecd::triggerIxRefSrefIntvalToRefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const uint ixInv
			, const ubigint refInv
			, const string& srefInv
			, const int intvalInv
			, ubigint& refRet
		) {
	bool retval;

	Arg argInv(ixInv, refInv, {}, srefInv, intvalInv, 0.0, false, "", Arg::IX + Arg::REF + Arg::SREF + Arg::INTVAL);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) refRet = argRet.ref;

	return(retval);
};

bool XchgIdecd::triggerRefToIxCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const ubigint refInv
			, uint& ixRet
		) {
	bool retval;

	Arg argInv(0, refInv, {}, "", 0, 0.0, false, "", Arg::REF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) ixRet = argRet.ix;

	return(retval);
};

bool XchgIdecd::triggerSrefToRefCall(
			DbsIdec* dbsidec
			, const uint ixIdecVCall
			, const ubigint jref
			, const string& srefInv
			, ubigint& refRet
		) {
	bool retval;

	Arg argInv(0, 0, {}, srefInv, 0, 0.0, false, "", Arg::SREF);
	Arg argRet;

	retval = triggerArgToArgCall(dbsidec, ixIdecVCall, jref, argInv, argRet);

	if (!retval) refRet = argRet.ref;

	return(retval);
};

DcolIdec* XchgIdecd::addDcol(
			const ubigint jref
		) {
	JobIdec* job = NULL;

	DcolIdec* dcol = NULL;

	// create new dcol and append to dcol list
	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "addDcol");
	Mutex::lock(&mDcols, "mDcols", "XchgIdecd", "addDcol");

	job = getJobByJref(jref);

	if (job) {
		dcol = getDcolByJref(jref);

		if (!dcol) {
			dcol = new DcolIdec(jref, job->ixIdecVLocale);
			dcols[jref] = dcol;

			mon.eventAddDcol(jref);

			dcol->lockAccess("XchgIdecd", "addDcol");
		};

		// make dcol the session's active notify dcol
		triggerIxRefCall(NULL, VecIdecVCall::CALLIDECREFPRESET, jref, VecIdecVPreset::PREIDECJREFNOTIFY, jref);
	};

	Mutex::unlock(&mDcols, "mDcols", "XchgIdecd", "addDcol");
	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "addDcol");

	return(dcol);
};

DcolIdec* XchgIdecd::getDcolByJref(
			const ubigint jref
			, const bool tree
		) {
	JobIdec* job = NULL;

	DcolIdec* dcol = NULL;

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "getDcolByJref");
	Mutex::lock(&mDcols, "mDcols", "XchgIdecd", "getDcolByJref");

	job = getJobByJref(jref);

	while (job != NULL) {
		auto it = dcols.find(job->jref);

		if (it != dcols.end()) {
			dcol = it->second;
			dcol->lockAccess("XchgIdecd", "getDcolByJref");

			break;
		};

		if (!tree) break;

		job = getJobByJref(job->jrefSup);
	};

	Mutex::unlock(&mDcols, "mDcols", "XchgIdecd", "addDcol");
	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "addDcol");

	return(dcol);
};

void XchgIdecd::removeDcolByJref(
			const ubigint jref
		) {
	Mutex::lock(&mDcols, "mDcols", "XchgIdecd", "removeDcolByJref");

	auto it = dcols.find(jref);
	if (it != dcols.end()) {
		delete it->second;
		dcols.erase(it);

		mon.eventRemoveDcol(jref);
	};

	Mutex::unlock(&mDcols, "mDcols", "XchgIdecd", "removeDcolByJref");
};

void XchgIdecd::submitDpch(
			DpchEngIdec* dpcheng
		) {
	DcolIdec* dcol = NULL;

	pthread_cond_t* cReady_backup;
	pthread_mutex_t* mcReady_backup;

	DpchEngIdec* dpchtest;

	// find dcol in charge
	dcol = getDcolByJref(dpcheng->jref);

	if (dcol) {
		mon.eventSubmitDpch(dpcheng->jref, VecIdecVDpch::getSref(dpcheng->ixIdecVDpch), dpcheng->getSrefsMask(), "");

		if (dcol->req != NULL) {
			// a request is waiting
			delete dcol->req->dpcheng;
			dcol->req->dpcheng = dpcheng;

			cReady_backup = &(dcol->req->cReady);
			mcReady_backup = &(dcol->req->mcReady);

			dcol->req = NULL;
			//cout << "XchgIdecd::submitDpch() waiting request for ixIdecVDpch = " << dpcheng->ixIdecVDpch << ", jref = " << dpcheng->jref << endl;

			Cond::signal(cReady_backup, mcReady_backup, "dcol(" + to_string(dcol->jref) + ")->req->cReady", "dcol(" + to_string(dcol->jref) + ")->req->mcReady", "XchgIdecd", "submitDpch");

			dcol->unlockAccess("XchgIdecd", "submitDpch");

		} else {
			// merge with similar dispatch if available
			for (auto it=dcol->dpchs.begin();it!=dcol->dpchs.end();) {
				dpchtest = *it;

				if ((dpchtest->ixIdecVDpch == dpcheng->ixIdecVDpch) && (dpchtest->jref == dpcheng->jref)) {
					dpchtest->merge(dpcheng);
					//cout << "XchgIdecd::submitDpch() merge for ixIdecVDpch = " << dpcheng->ixIdecVDpch << ", jref = " << dpcheng->jref << endl;

					delete dpcheng;
					dpcheng = NULL;

					break;

				} else it++;
			};

			// append to list of dispatches
			if (dpcheng) {
				dcol->dpchs.push_back(dpcheng);
				//cout << "XchgIdecd::submitDpch() append for ixIdecVDpch = " << dpcheng->ixIdecVDpch << ", jref = " << dpcheng->jref << endl;
			};

			dcol->unlockAccess("XchgIdecd", "submitDpch");
		};

	} else {
		delete dpcheng;
	};
};

DpchEngIdec* XchgIdecd::pullFirstDpch(
			DcolIdec* dcol
		) {
	DpchEngIdec* dpcheng = NULL;

	// get first element from list ; assume access is locked
	if (!dcol->dpchs.empty()) {
		dpcheng = *(dcol->dpchs.begin());
		dcol->dpchs.pop_front();
	};

	return dpcheng;
};

ubigint XchgIdecd::addJob(
			JobIdec* job
		) {
	JobIdec* supjob = NULL;

	// get new jref and append to job list
	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "addJob");

	job->jref = jrefseq->getNewRef();
	jobs[job->jref] = job;

	if (jobs.size() == 1) {
		// root job
		jrefRoot = job->jref;
		jrefCmd = job->jref;
	};

	supjob = getJobByJref(job->jrefSup);
	if (supjob) supjob->jrefsSub.insert(job->jref);

	mon.eventAddJob(job->jrefSup, VecIdecVJob::getSref(job->ixIdecVJob), job->jref);

	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "addJob");

	return(job->jref);
};

ubigint XchgIdecd::addJob(
			DbsIdec* dbsidec
			, JobIdec* job
		) {
	JobIdec* supjob = NULL;

	JobIdec* mastjob = NULL;

	// get new jref, append to job list and integrate into master/slave structure
	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "addJob");

	job->jref = jrefseq->getNewRef();
	jobs[job->jref] = job;

	supjob = getJobByJref(job->jrefSup);
	if (supjob) supjob->jrefsSub.insert(job->jref);

	mon.eventAddJob(job->jrefSup, VecIdecVJob::getSref(job->ixIdecVJob), job->jref);

	// find current master job
	for (auto it=jobs.begin();it!=jobs.end();it++) {
		if (it->second->ixIdecVJob == job->ixIdecVJob) {
			mastjob = getJobByJref(it->second->jrefMast);
			break;
		};
	};

	if (mastjob) {
		job->jrefMast = mastjob->jref;

		if (job->prefmast) {
			// priority for becoming new master
			mastjob->jrefsSlv.push_front(job->jref);

			mon.eventBecomeSlave(job->jref);

			job->becomeSlave(dbsidec);

			claimMaster(dbsidec, job->jref);

		} else {
			mastjob->jrefsSlv.push_back(job->jref);

			mon.eventBecomeSlave(job->jref);

			job->becomeSlave(dbsidec);
		};

	} else {
		// only job of its type
		job->jrefMast = job->jref;

		mon.eventBecomeMaster(job->jref);

		job->becomeMaster(dbsidec);
	};

	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "addJob");

	return(job->jref);
};

JobIdec* XchgIdecd::getJobByJref(
			const ubigint jref
		) {
	JobIdec* job = NULL;

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "getJobByJref");

	auto it = jobs.find(jref);
	if (it != jobs.end()) job = it->second;

	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "getJobByJref");

	return job;
};

void XchgIdecd::removeJobByJref(
			const ubigint jref
		) {
	JobIdec* supjob = NULL;
	JobIdec* job = NULL;
	JobIdec* subjob = NULL;

	JobIdec* mastjob = NULL;
	JobIdec* slvjob = NULL;

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "removeJobByJref");

	job = getJobByJref(jref);

	if (job) {
		job->invalidateWakeups();

		removePresetsByJref(jref);
		removeStmgrByJref(jref);
		removeClstnsByJref(jref);
		removeDcolByJref(jref);

		// remove from master/slave structure
		if (job->jrefMast != 0) {
			if (job->jref == job->jrefMast) {
				mastjob = NULL;

				if (!job->jrefsSlv.empty()) {
					mon.eventGiveupMaster(job->jref);
					job->giveupMaster(NULL);

					mastjob = getJobByJref(job->jrefsSlv.front());
				};

				if (mastjob) {
					mon.eventGiveupSlave(mastjob->jref);
					mastjob->giveupSlave(NULL);

					mon.eventGiveupMaster(job->jref);
					job->giveupMaster(NULL);

					mastjob->jrefsSlv = job->jrefsSlv;
					mastjob->jrefsSlv.pop_front();

					mastjob->jrefMast = mastjob->jref;

					for (auto it=mastjob->jrefsSlv.begin();it!=mastjob->jrefsSlv.end();it++) {
						slvjob = getJobByJref(*it);
						if (slvjob) slvjob->jrefMast = mastjob->jref;
					};

					mon.eventBecomeMaster(mastjob->jref);
					mastjob->becomeMaster(NULL);

					triggerCall(NULL, VecIdecVCall::CALLIDECMASTSLVCHG, mastjob->jref);

				} else {
					mon.eventGiveupMaster(job->jref);
					job->giveupMaster(NULL);
				};

			} else {
				mon.eventGiveupSlave(job->jref);
				job->giveupSlave(NULL);

				mastjob = getJobByJref(job->jrefMast);
				if (mastjob) mastjob->jrefsSlv.remove(job->jref);
			};
		};

		// super-job
		supjob = getJobByJref(job->jrefSup);
		if (supjob) supjob->jrefsSub.erase(jref);

		// sub-jobs
		while (job->jrefsSub.size() > 0) {
			subjob = getJobByJref(*(job->jrefsSub.begin()));
			if (subjob) delete subjob;
		};

		// remove job from list only here otherwise sub-job delete will loop forever
		jobs.erase(jref);

		mon.eventRemoveJob(jref);
	};

	if (jobs.empty()) {
		// root job
		jrefRoot = 0;
		jrefCmd = 0;
	};

	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "removeJobByJref");
};

void XchgIdecd::transferMaster(
			DbsIdec* dbsidec
			, JobIdec* fromjob
			, JobIdec* tojob
		) {
	// requires mJobs locked and tojob at first position in fromjob->jrefsSlv
	JobIdec* job = NULL;

	mon.eventGiveupSlave(tojob->jref);
	tojob->giveupSlave(dbsidec);

	mon.eventGiveupMaster(fromjob->jref);
	fromjob->giveupMaster(dbsidec);

	tojob->jrefsSlv = fromjob->jrefsSlv;
	fromjob->jrefsSlv.clear();
	tojob->jrefsSlv.pop_front();

	if (fromjob->prefmast) tojob->jrefsSlv.push_front(fromjob->jref);
	else tojob->jrefsSlv.push_back(fromjob->jref);

	tojob->jrefMast = tojob->jref;

	for (auto it=tojob->jrefsSlv.begin();it!=tojob->jrefsSlv.end();it++) {
		job = getJobByJref(*it);
		if (job) job->jrefMast = tojob->jref;
	};

	mon.eventBecomeMaster(tojob->jref);
	tojob->becomeMaster(dbsidec);

	mon.eventBecomeSlave(fromjob->jref);
	fromjob->becomeSlave(dbsidec);

	triggerCall(dbsidec, VecIdecVCall::CALLIDECMASTSLVCHG, tojob->jref);
	triggerCall(dbsidec, VecIdecVCall::CALLIDECMASTSLVCHG, fromjob->jref);
};

void XchgIdecd::offerMaster(
			DbsIdec* dbsidec
			, const ubigint jref
		) {
	JobIdec* mastjob = NULL;
	JobIdec* slvjob = NULL;

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "offerMaster");

	mastjob = getJobByJref(jref);

	if (mastjob) {
		if (!mastjob->jrefsSlv.empty()) {
			slvjob = getJobByJref(mastjob->jrefsSlv.front());

			if (slvjob) if (slvjob->prefmast) transferMaster(dbsidec, mastjob, slvjob);
		};
	};

	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "offerMaster");
};

bool XchgIdecd::claimMaster(
			DbsIdec* dbsidec
			, const ubigint jref
		) {
	bool retval = false;

	JobIdec* mastjob = NULL;
	JobIdec* slvjob = NULL;

	Mutex::lock(&mJobs, "mJobs", "XchgIdecd", "claimMaster");

	slvjob = getJobByJref(jref);

	if (slvjob) {
		if (slvjob->jref != slvjob->jrefMast) {
			mastjob = getJobByJref(slvjob->jrefMast);

			if (mastjob) {
				for (auto it=mastjob->jrefsSlv.begin();it!=mastjob->jrefsSlv.end();it++) {
					// put slvjob first
					if (*it == jref) {
						*it = mastjob->jrefsSlv.front();
						mastjob->jrefsSlv.pop_front();
						mastjob->jrefsSlv.push_front(jref);

						break;
					};
				};

				if (mastjob->handleClaimMaster(dbsidec)) transferMaster(dbsidec, mastjob, slvjob);
			};
		};

		retval = (slvjob->jref == slvjob->jrefMast);
	};

	Mutex::unlock(&mJobs, "mJobs", "XchgIdecd", "claimMaster");

	return retval;
};

ubigint XchgIdecd::addWakeup(
			const ubigint jref
			, const string sref
			, const unsigned int deltat
			, const bool weak
		) {
	int res;

	ubigint wref;

	pthread_t timer;

	wref = wrefseq->getNewRef();

	if (deltat == 0) {
		// immediate callback: generate request to be treated by job processor
		ReqIdec* req = new ReqIdec(ReqIdec::VecVBasetype::TIMER);
		req->jref = jref;
		req->wref = wref;
		req->sref = sref;
		req->weak = false;

		addReq(req);

	} else {
		// delayed callback: generate dedicated wait thread
		WakeupIdec* wakeup = new WakeupIdec(this, wref, jref, sref, deltat, weak);

		res = pthread_create(&timer, NULL, &runWakeup, (void*) wakeup);
		if (res != 0) cout << "XchgIdecd::addWakeup() error creating timer thread (" << res << ")" << endl;
		res = pthread_detach(timer);
		if (res != 0) cout << "XchgIdecd::addWakeup() error detaching timer thread (" << res << ")" << endl;
	};

	return(wref);
};

void* XchgIdecd::runWakeup(
			void* arg
		) {
	WakeupIdec* wakeup = (WakeupIdec*) arg;

	// wait for time specified in microseconds
	timespec deltat;
	deltat.tv_sec = wakeup->deltat / 1000000;
	deltat.tv_nsec = 1000 * (wakeup->deltat%1000000);
#ifdef _WIN32
	usleep(wakeup->deltat);
#else
	nanosleep(&deltat, NULL);
#endif

	// generate request to be treated by job processor
	ReqIdec* req = new ReqIdec(ReqIdec::VecVBasetype::TIMER);
	req->jref = wakeup->jref;
	req->wref = wakeup->wref;
	req->sref = wakeup->sref;
	req->weak = wakeup->weak;

	wakeup->xchg->addReq(req);

	delete wakeup;

	return(NULL);
};

void XchgIdecd::runExtcall(
			void* arg
		) {
	ExtcallIdec* extcall = (ExtcallIdec*) arg;

	// generate request to be treated by job processor
	ReqIdec* req = new ReqIdec(ReqIdec::VecVBasetype::EXTCALL);
	req->call = new Call(*(extcall->call));

	extcall->xchg->addReq(req);
};

NodeIdec* XchgIdecd::addNode(
			const string& ip
			, const uint port
			, const uint opprcn
			, const uint ixIdecVOpengtype
		) {
	NodeIdec* node = NULL;

	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "addNode");

	node = new NodeIdec(nrefseq->getNewRef(), ip, port, opprcn, ixIdecVOpengtype);
	nodes[node->nref] = node;

	mon.eventAddNode(node->nref, ip, port, opprcn);

	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "addNode");

	Cond::signal(&cOpengcli, &mcOpengcli, "cOpengcli", "mcOpengcli", "XchgIdecd", "addNode");

	triggerCall(NULL, VecIdecVCall::CALLIDECNODECHG, jrefRoot);

	return(node);
};

NodeIdec* XchgIdecd::getNodeByNref(
			const ubigint nref
		) {
	NodeIdec* node = NULL;

	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "getNodeByNref");

	auto it = nodes.find(nref);
	if (it != nodes.end()) node = it->second;

	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "getNodeByNref");

	return(node);
};

void XchgIdecd::quitNodes() {
	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "quitNodes");

	for (auto it=nodes.begin();it!=nodes.end();it++) quitNodeByNref(it->first);

	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "quitNodes");
};

void XchgIdecd::quitNodeByNref(
			const ubigint nref
		) {
	NodeIdec* node = NULL;

	xmlBuffer* xbuf = NULL;
	xmlTextWriter* wr = NULL;

	xmlDoc* doc = NULL;
	xmlXPathContext* docctx = NULL;
	string rplydpch;

	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "quitNodeByNref");

	node = getNodeByNref(nref);
	
	if (node) {
		// POST content (DpchIdecdQuit)
		Xmlio::startwriteBuffer(&wr, &xbuf);
			DpchIdecdQuit::writeXML(wr);
		Xmlio::closewriteBuffer(wr);

		if (CurlPostDpch("http://" + node->ip + ":" + to_string(node->port) + "/dpch", xbuf, &doc, &docctx, rplydpch)) {
			// evaluate reply
			if (rplydpch == "dpchidecopdack") {
				// acknowledged
			};

		} else {
			// cout << "\terror notifying op engine!" << endl;
		};

		if (docctx) xmlXPathFreeContext(docctx);
		if (doc) xmlFreeDoc(doc);
		xmlBufferFree(xbuf);
	};

	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "quitNodeByNref");
};

void XchgIdecd::removeNodeByNref(
			const ubigint nref
		) {
	Mutex::lock(&mNodes, "mNodes", "XchgIdecd", "removeNodeByNref");

	auto it = nodes.find(nref);
	if (it != nodes.end()) {
		delete it->second;
		nodes.erase(it);

		mon.eventRemoveNode(nref);
	};

	Mutex::unlock(&mNodes, "mNodes", "XchgIdecd", "removeNodeByNref");

	triggerCall(NULL, VecIdecVCall::CALLIDECNODECHG, jrefRoot);
};

uint XchgIdecd::CurlPostrecv(
			void* data
			, uint size
			, uint blocksize
			, void* _inst
		) {
	XchgIdecd* inst = (XchgIdecd*) _inst;

	char* olddata;

	if (size > 0) {
		if (!inst->curlrecv) {
			inst->curlrecv = new char[size*blocksize];
			memcpy(inst->curlrecv, data, size*blocksize);
			inst->curlrecvlen = size*blocksize;

		} else {
			olddata = inst->curlrecv;

			inst->curlrecv = new char[inst->curlrecvlen + size*blocksize];
			memcpy(inst->curlrecv, olddata, inst->curlrecvlen);
			memcpy(&(inst->curlrecv[inst->curlrecvlen]), data, size*blocksize);
			inst->curlrecvlen = inst->curlrecvlen + size*blocksize;

			delete[] olddata;
		};
	};

  return(size*blocksize);
};

bool XchgIdecd::CurlPostDpch(
			const string& url
			, xmlBuffer* xbuf
			, xmlDoc** rplydoc
			, xmlXPathContext** rplydocctx
			, string& rplydpch
		) {
	CURL* curl;
	CURLcode res;

	bool retval = false;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// receive buffer
		if (curlrecv) delete[] curlrecv;
		curlrecv = NULL;
		curlrecvlen = 0;

		// string to be sent is "xml=<xbuf>"
		size_t buflen = xbuf->use + 4;
		char* buf = new char[buflen];

		buf[0] = 'x'; buf[1] = 'm'; buf[2] = 'l'; buf[3] = '=';
		memcpy(&(buf[4]), xbuf->content, xbuf->use);

		// strip '\r' and '\n' characters
		for (size_t i=0;i<buflen;) {
			if ((buf[i] == '\r') || (buf[i] == '\n')) {
				memmove(&(buf[i]), &(buf[i+1]), buflen-i-1);
				buflen--;
			} else i++;
		};

		// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, buflen);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlPostrecv);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

		res = curl_easy_perform(curl);

		delete[] buf;

		curl_easy_cleanup(curl);

		// evaluate result
		if (curlrecv) {
			if (res == 0) {
				// check for root XML node
				Xmlio::parseBuffer(curlrecv, curlrecvlen, rplydoc, rplydocctx);
				rplydpch = StrMod::lc(Xmlio::extractRoot(*rplydoc));
				retval = true;
			};

			delete[] curlrecv;
			curlrecv = NULL;
			curlrecvlen = 0;
		};
	};

	return retval;
};

