/**
  * \file IdecQMisRef1NFile.cpp
  * API code for table TblIdecQMisRef1NFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQMisRef1NFile.h"

/******************************************************************************
 class IdecQMisRef1NFile
 ******************************************************************************/

IdecQMisRef1NFile::IdecQMisRef1NFile(
			const uint jnum
			, const string stubRef
		) {
	this->jnum = jnum;
	this->stubRef = stubRef;
};

bool IdecQMisRef1NFile::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQMisRef1NFile");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "stubRef", "ref", stubRef);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQMisRef1NFile
 ******************************************************************************/

ListIdecQMisRef1NFile::ListIdecQMisRef1NFile() {
};

ListIdecQMisRef1NFile::ListIdecQMisRef1NFile(
			const ListIdecQMisRef1NFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMisRef1NFile(*(src.nodes[i]));
};

ListIdecQMisRef1NFile& ListIdecQMisRef1NFile::operator=(
			const ListIdecQMisRef1NFile& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQMisRef1NFile(*(src.nodes[i]));

	return *this;
};

ListIdecQMisRef1NFile::~ListIdecQMisRef1NFile() {
	clear();
};

void ListIdecQMisRef1NFile::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQMisRef1NFile::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQMisRef1NFile* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQMisRef1NFile");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQMisRef1NFile", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQMisRef1NFile(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQMisRef1NFile[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

