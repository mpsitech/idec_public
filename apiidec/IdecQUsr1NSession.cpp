/**
  * \file IdecQUsr1NSession.cpp
  * API code for table TblIdecQUsr1NSession (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQUsr1NSession.h"

/******************************************************************************
 class IdecQUsr1NSession
 ******************************************************************************/

IdecQUsr1NSession::IdecQUsr1NSession(
			const uint jnum
			, const string stubRef
		) {
	this->jnum = jnum;
	this->stubRef = stubRef;
};

bool IdecQUsr1NSession::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQUsr1NSession");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "stubRef", "ref", stubRef);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQUsr1NSession
 ******************************************************************************/

ListIdecQUsr1NSession::ListIdecQUsr1NSession() {
};

ListIdecQUsr1NSession::ListIdecQUsr1NSession(
			const ListIdecQUsr1NSession& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsr1NSession(*(src.nodes[i]));
};

ListIdecQUsr1NSession& ListIdecQUsr1NSession::operator=(
			const ListIdecQUsr1NSession& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQUsr1NSession(*(src.nodes[i]));

	return *this;
};

ListIdecQUsr1NSession::~ListIdecQUsr1NSession() {
	clear();
};

void ListIdecQUsr1NSession::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQUsr1NSession::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQUsr1NSession* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQUsr1NSession");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQUsr1NSession", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQUsr1NSession(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQUsr1NSession[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

