/**
  * \file IdecQMis1NTour.cpp
  * API code for table TblIdecQMis1NTour (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQMis1NTour.h"

/******************************************************************************
 class IdecQMis1NTour
 ******************************************************************************/

IdecQMis1NTour::IdecQMis1NTour(
			const uint jnum
			, const string stubRef
		) {
	this->jnum = jnum;
	this->stubRef = stubRef;
};

bool IdecQMis1NTour::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQMis1NTour");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "stubRef", "ref", stubRef);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQMis1NTour
 ******************************************************************************/

ListIdecQMis1NTour::ListIdecQMis1NTour() {
};

ListIdecQMis1NTour::ListIdecQMis1NTour(
			const ListIdecQMis1NTour& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMis1NTour(*(src.nodes[i]));
};

ListIdecQMis1NTour& ListIdecQMis1NTour::operator=(
			const ListIdecQMis1NTour& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMis1NTour(*(src.nodes[i]));

	return *this;
};

ListIdecQMis1NTour::~ListIdecQMis1NTour() {
	clear();
};

void ListIdecQMis1NTour::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQMis1NTour::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQMis1NTour* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQMis1NTour");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQMis1NTour", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQMis1NTour(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQMis1NTour[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

