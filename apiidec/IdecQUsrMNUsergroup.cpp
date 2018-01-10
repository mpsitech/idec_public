/**
  * \file IdecQUsrMNUsergroup.cpp
  * API code for table TblIdecQUsrMNUsergroup (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQUsrMNUsergroup.h"

/******************************************************************************
 class IdecQUsrMNUsergroup
 ******************************************************************************/

IdecQUsrMNUsergroup::IdecQUsrMNUsergroup(
			const uint jnum
			, const string stubMref
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	this->jnum = jnum;
	this->stubMref = stubMref;
	this->srefIxIdecVUserlevel = srefIxIdecVUserlevel;
	this->titIxIdecVUserlevel = titIxIdecVUserlevel;
};

bool IdecQUsrMNUsergroup::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQUsrMNUsergroup");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "stubMref", "mref", stubMref);
		extractStringUclc(docctx, basexpath, "srefIxIdecVUserlevel", "ulv", srefIxIdecVUserlevel);
		extractStringUclc(docctx, basexpath, "titIxIdecVUserlevel", "ulv2", titIxIdecVUserlevel);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQUsrMNUsergroup
 ******************************************************************************/

ListIdecQUsrMNUsergroup::ListIdecQUsrMNUsergroup() {
};

ListIdecQUsrMNUsergroup::ListIdecQUsrMNUsergroup(
			const ListIdecQUsrMNUsergroup& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrMNUsergroup(*(src.nodes[i]));
};

ListIdecQUsrMNUsergroup& ListIdecQUsrMNUsergroup::operator=(
			const ListIdecQUsrMNUsergroup& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrMNUsergroup(*(src.nodes[i]));

	return *this;
};

ListIdecQUsrMNUsergroup::~ListIdecQUsrMNUsergroup() {
	clear();
};

void ListIdecQUsrMNUsergroup::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQUsrMNUsergroup::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQUsrMNUsergroup* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQUsrMNUsergroup");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQUsrMNUsergroup", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQUsrMNUsergroup(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQUsrMNUsergroup[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

