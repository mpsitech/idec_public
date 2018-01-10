/**
  * \file IdecQTouList.cpp
  * API code for table TblIdecQTouList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQTouList.h"

/******************************************************************************
 class IdecQTouList
 ******************************************************************************/

IdecQTouList::IdecQTouList(
			const uint jnum
			, const string Title
			, const string stubRefIdecMMission
			, const string ftmStart
			, const string ftmStop
			, const string Area
		) {
	this->jnum = jnum;
	this->Title = Title;
	this->stubRefIdecMMission = stubRefIdecMMission;
	this->ftmStart = ftmStart;
	this->ftmStop = ftmStop;
	this->Area = Area;
};

bool IdecQTouList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQTouList");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "Title", "tit", Title);
		extractStringUclc(docctx, basexpath, "stubRefIdecMMission", "mis", stubRefIdecMMission);
		extractStringUclc(docctx, basexpath, "ftmStart", "sta", ftmStart);
		extractStringUclc(docctx, basexpath, "ftmStop", "sto", ftmStop);
		extractStringUclc(docctx, basexpath, "Area", "are", Area);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQTouList
 ******************************************************************************/

ListIdecQTouList::ListIdecQTouList() {
};

ListIdecQTouList::ListIdecQTouList(
			const ListIdecQTouList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQTouList(*(src.nodes[i]));
};

ListIdecQTouList& ListIdecQTouList::operator=(
			const ListIdecQTouList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQTouList(*(src.nodes[i]));

	return *this;
};

ListIdecQTouList::~ListIdecQTouList() {
	clear();
};

void ListIdecQTouList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQTouList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQTouList* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQTouList");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQTouList", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQTouList(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQTouList[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

