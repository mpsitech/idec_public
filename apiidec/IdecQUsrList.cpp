/**
  * \file IdecQUsrList.cpp
  * API code for table TblIdecQUsrList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQUsrList.h"

/******************************************************************************
 class IdecQUsrList
 ******************************************************************************/

IdecQUsrList::IdecQUsrList(
			const uint jnum
			, const string stubRefIdecMPerson
			, const string sref
			, const string stubRefIdecMUsergroup
			, const string srefIxVState
			, const string titIxVState
			, const string srefIxIdecVLocale
			, const string titIxIdecVLocale
			, const string srefIxIdecVUserlevel
			, const string titIxIdecVUserlevel
		) {
	this->jnum = jnum;
	this->stubRefIdecMPerson = stubRefIdecMPerson;
	this->sref = sref;
	this->stubRefIdecMUsergroup = stubRefIdecMUsergroup;
	this->srefIxVState = srefIxVState;
	this->titIxVState = titIxVState;
	this->srefIxIdecVLocale = srefIxIdecVLocale;
	this->titIxIdecVLocale = titIxIdecVLocale;
	this->srefIxIdecVUserlevel = srefIxIdecVUserlevel;
	this->titIxIdecVUserlevel = titIxIdecVUserlevel;
};

bool IdecQUsrList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQUsrList");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "stubRefIdecMPerson", "prs", stubRefIdecMPerson);
		extractStringUclc(docctx, basexpath, "sref", "srf", sref);
		extractStringUclc(docctx, basexpath, "stubRefIdecMUsergroup", "usg", stubRefIdecMUsergroup);
		extractStringUclc(docctx, basexpath, "srefIxVState", "ste", srefIxVState);
		extractStringUclc(docctx, basexpath, "titIxVState", "ste2", titIxVState);
		extractStringUclc(docctx, basexpath, "srefIxIdecVLocale", "lcl", srefIxIdecVLocale);
		extractStringUclc(docctx, basexpath, "titIxIdecVLocale", "lcl2", titIxIdecVLocale);
		extractStringUclc(docctx, basexpath, "srefIxIdecVUserlevel", "ulv", srefIxIdecVUserlevel);
		extractStringUclc(docctx, basexpath, "titIxIdecVUserlevel", "ulv2", titIxIdecVUserlevel);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQUsrList
 ******************************************************************************/

ListIdecQUsrList::ListIdecQUsrList() {
};

ListIdecQUsrList::ListIdecQUsrList(
			const ListIdecQUsrList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrList(*(src.nodes[i]));
};

ListIdecQUsrList& ListIdecQUsrList::operator=(
			const ListIdecQUsrList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsrList(*(src.nodes[i]));

	return *this;
};

ListIdecQUsrList::~ListIdecQUsrList() {
	clear();
};

void ListIdecQUsrList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQUsrList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQUsrList* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQUsrList");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQUsrList", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQUsrList(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQUsrList[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

