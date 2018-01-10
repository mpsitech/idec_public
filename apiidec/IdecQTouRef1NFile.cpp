/**
  * \file IdecQTouRef1NFile.cpp
  * API code for table TblIdecQTouRef1NFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQTouRef1NFile.h"

/******************************************************************************
 class IdecQTouRef1NFile
 ******************************************************************************/

IdecQTouRef1NFile::IdecQTouRef1NFile(
			const uint jnum
			, const string stubRef
		) {
	this->jnum = jnum;
	this->stubRef = stubRef;
};

bool IdecQTouRef1NFile::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQTouRef1NFile");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "stubRef", "ref", stubRef);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQTouRef1NFile
 ******************************************************************************/

ListIdecQTouRef1NFile::ListIdecQTouRef1NFile() {
};

ListIdecQTouRef1NFile::ListIdecQTouRef1NFile(
			const ListIdecQTouRef1NFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQTouRef1NFile(*(src.nodes[i]));
};

ListIdecQTouRef1NFile& ListIdecQTouRef1NFile::operator=(
			const ListIdecQTouRef1NFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQTouRef1NFile(*(src.nodes[i]));

	return *this;
};

ListIdecQTouRef1NFile::~ListIdecQTouRef1NFile() {
	clear();
};

void ListIdecQTouRef1NFile::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQTouRef1NFile::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQTouRef1NFile* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQTouRef1NFile");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQTouRef1NFile", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQTouRef1NFile(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQTouRef1NFile[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

