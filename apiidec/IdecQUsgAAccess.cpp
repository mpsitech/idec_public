/**
  * \file IdecQUsgAAccess.cpp
  * API code for table TblIdecQUsgAAccess (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQUsgAAccess.h"

/******************************************************************************
 class IdecQUsgAAccess
 ******************************************************************************/

IdecQUsgAAccess::IdecQUsgAAccess(
			const uint jnum
			, const string srefX1IxIdecVCard
			, const string titX1IxIdecVCard
			, const string srefsIxIdecWUiaccess
			, const string titsIxIdecWUiaccess
		) {
	this->jnum = jnum;
	this->srefX1IxIdecVCard = srefX1IxIdecVCard;
	this->titX1IxIdecVCard = titX1IxIdecVCard;
	this->srefsIxIdecWUiaccess = srefsIxIdecWUiaccess;
	this->titsIxIdecWUiaccess = titsIxIdecWUiaccess;
};

bool IdecQUsgAAccess::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQUsgAAccess");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "srefX1IxIdecVCard", "crd", srefX1IxIdecVCard);
		extractStringUclc(docctx, basexpath, "titX1IxIdecVCard", "crd2", titX1IxIdecVCard);
		extractStringUclc(docctx, basexpath, "srefsIxIdecWUiaccess", "uac", srefsIxIdecWUiaccess);
		extractStringUclc(docctx, basexpath, "titsIxIdecWUiaccess", "uac2", titsIxIdecWUiaccess);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQUsgAAccess
 ******************************************************************************/

ListIdecQUsgAAccess::ListIdecQUsgAAccess() {
};

ListIdecQUsgAAccess::ListIdecQUsgAAccess(
			const ListIdecQUsgAAccess& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgAAccess(*(src.nodes[i]));
};

ListIdecQUsgAAccess& ListIdecQUsgAAccess::operator=(
			const ListIdecQUsgAAccess& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgAAccess(*(src.nodes[i]));

	return *this;
};

ListIdecQUsgAAccess::~ListIdecQUsgAAccess() {
	clear();
};

void ListIdecQUsgAAccess::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQUsgAAccess::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQUsgAAccess* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQUsgAAccess");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQUsgAAccess", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQUsgAAccess(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQUsgAAccess[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

