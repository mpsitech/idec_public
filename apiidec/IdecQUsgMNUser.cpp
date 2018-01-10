/**
  * \file IdecQUsgMNUser.cpp
  * API code for table TblIdecQUsgMNUser (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQUsgMNUser.h"

/******************************************************************************
 class IdecQUsgMNUser
 ******************************************************************************/

IdecQUsgMNUser::IdecQUsgMNUser(
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

bool IdecQUsgMNUser::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQUsgMNUser");
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
 class ListIdecQUsgMNUser
 ******************************************************************************/

ListIdecQUsgMNUser::ListIdecQUsgMNUser() {
};

ListIdecQUsgMNUser::ListIdecQUsgMNUser(
			const ListIdecQUsgMNUser& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgMNUser(*(src.nodes[i]));
};

ListIdecQUsgMNUser& ListIdecQUsgMNUser::operator=(
			const ListIdecQUsgMNUser& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsgMNUser(*(src.nodes[i]));

	return *this;
};

ListIdecQUsgMNUser::~ListIdecQUsgMNUser() {
	clear();
};

void ListIdecQUsgMNUser::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQUsgMNUser::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQUsgMNUser* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQUsgMNUser");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQUsgMNUser", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQUsgMNUser(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQUsgMNUser[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

