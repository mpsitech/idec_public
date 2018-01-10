/**
  * \file IdecQUsgList.cpp
  * API code for table TblIdecQUsgList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQUsgList.h"

/******************************************************************************
 class IdecQUsgList
 ******************************************************************************/

IdecQUsgList::IdecQUsgList(
			const uint jnum
			, const string sref
		) {
	this->jnum = jnum;
	this->sref = sref;
};

bool IdecQUsgList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQUsgList");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "sref", "srf", sref);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQUsgList
 ******************************************************************************/

ListIdecQUsgList::ListIdecQUsgList() {
};

ListIdecQUsgList::ListIdecQUsgList(
			const ListIdecQUsgList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgList(*(src.nodes[i]));
};

ListIdecQUsgList& ListIdecQUsgList::operator=(
			const ListIdecQUsgList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgList(*(src.nodes[i]));

	return *this;
};

ListIdecQUsgList::~ListIdecQUsgList() {
	clear();
};

void ListIdecQUsgList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQUsgList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQUsgList* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQUsgList");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQUsgList", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQUsgList(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQUsgList[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

