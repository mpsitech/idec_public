/**
  * \file IdecQMisList.cpp
  * API code for table TblIdecQMisList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQMisList.h"

/******************************************************************************
 class IdecQMisList
 ******************************************************************************/

IdecQMisList::IdecQMisList(
			const uint jnum
			, const string Title
			, const string stubGrp
			, const string stubOwn
			, const string ftmStartd
			, const string ftmStopd
			, const string srefKCountry
			, const string titSrefKCountry
			, const string Region
			, const string Municipality
		) {
	this->jnum = jnum;
	this->Title = Title;
	this->stubGrp = stubGrp;
	this->stubOwn = stubOwn;
	this->ftmStartd = ftmStartd;
	this->ftmStopd = ftmStopd;
	this->srefKCountry = srefKCountry;
	this->titSrefKCountry = titSrefKCountry;
	this->Region = Region;
	this->Municipality = Municipality;
};

bool IdecQMisList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQMisList");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "Title", "tit", Title);
		extractStringUclc(docctx, basexpath, "stubGrp", "grp", stubGrp);
		extractStringUclc(docctx, basexpath, "stubOwn", "own", stubOwn);
		extractStringUclc(docctx, basexpath, "ftmStartd", "sta", ftmStartd);
		extractStringUclc(docctx, basexpath, "ftmStopd", "sto", ftmStopd);
		extractStringUclc(docctx, basexpath, "srefKCountry", "cry", srefKCountry);
		extractStringUclc(docctx, basexpath, "titSrefKCountry", "cry2", titSrefKCountry);
		extractStringUclc(docctx, basexpath, "Region", "reg", Region);
		extractStringUclc(docctx, basexpath, "Municipality", "mun", Municipality);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQMisList
 ******************************************************************************/

ListIdecQMisList::ListIdecQMisList() {
};

ListIdecQMisList::ListIdecQMisList(
			const ListIdecQMisList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMisList(*(src.nodes[i]));
};

ListIdecQMisList& ListIdecQMisList::operator=(
			const ListIdecQMisList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMisList(*(src.nodes[i]));

	return *this;
};

ListIdecQMisList::~ListIdecQMisList() {
	clear();
};

void ListIdecQMisList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQMisList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQMisList* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQMisList");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQMisList", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQMisList(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQMisList[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

