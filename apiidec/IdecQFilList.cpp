/**
  * \file IdecQFilList.cpp
  * API code for table TblIdecQFilList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "IdecQFilList.h"

/******************************************************************************
 class IdecQFilList
 ******************************************************************************/

IdecQFilList::IdecQFilList(
			const uint jnum
			, const string Filename
			, const string srefRefIxVTbl
			, const string titRefIxVTbl
			, const string stubRefUref
			, const string osrefKContent
			, const string titOsrefKContent
			, const string srefKMimetype
			, const string titSrefKMimetype
			, const usmallint Size
		) {
	this->jnum = jnum;
	this->Filename = Filename;
	this->srefRefIxVTbl = srefRefIxVTbl;
	this->titRefIxVTbl = titRefIxVTbl;
	this->stubRefUref = stubRefUref;
	this->osrefKContent = osrefKContent;
	this->titOsrefKContent = titOsrefKContent;
	this->srefKMimetype = srefKMimetype;
	this->titSrefKMimetype = titSrefKMimetype;
	this->Size = Size;
};

bool IdecQFilList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IdecQFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		extractStringUclc(docctx, basexpath, "Filename", "fnm", Filename);
		extractStringUclc(docctx, basexpath, "srefRefIxVTbl", "ret", srefRefIxVTbl);
		extractStringUclc(docctx, basexpath, "titRefIxVTbl", "ret2", titRefIxVTbl);
		extractStringUclc(docctx, basexpath, "stubRefUref", "reu", stubRefUref);
		extractStringUclc(docctx, basexpath, "osrefKContent", "cnt", osrefKContent);
		extractStringUclc(docctx, basexpath, "titOsrefKContent", "cnt2", titOsrefKContent);
		extractStringUclc(docctx, basexpath, "srefKMimetype", "mim", srefKMimetype);
		extractStringUclc(docctx, basexpath, "titSrefKMimetype", "mim2", titSrefKMimetype);
		extractUsmallintUclc(docctx, basexpath, "Size", "siz", Size);
	};

	return basefound;
};

/******************************************************************************
 class ListIdecQFilList
 ******************************************************************************/

ListIdecQFilList::ListIdecQFilList() {
};

ListIdecQFilList::ListIdecQFilList(
			const ListIdecQFilList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQFilList(*(src.nodes[i]));
};

ListIdecQFilList& ListIdecQFilList::operator=(
			const ListIdecQFilList& src
		) {
	nodes.resize(src.nodes.size(), NULL);
	for (unsigned int i=0;i<nodes.size();i++) nodes[i] = new IdecQFilList(*(src.nodes[i]));

	return *this;
};

ListIdecQFilList::~ListIdecQFilList() {
	clear();
};

void ListIdecQFilList::clear() {
	for (unsigned int i=0;i<nodes.size();i++) if (nodes[i]) delete nodes[i];
	nodes.resize(0);
};

bool ListIdecQFilList::readXML(
			xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	bool basefound;

	vector<unsigned int> ics;
	vector<bool> shorttags;

	IdecQFilList* rec = NULL;

	string s;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ListIdecQFilList");
	else
		basefound = checkXPath(docctx, basexpath);

	extractList(docctx, basexpath, "IdecQFilList", "row", "jnum", ics, shorttags);

	clear();

	for (unsigned int i=0;i<ics.size();i++) {
		rec = new IdecQFilList(ics[i]);

		if (shorttags[i]) s = basexpath + "/row[@jnum='" + to_string(ics[i]) + "']";
		else s = basexpath + "/IdecQFilList[@jnum='" + to_string(ics[i]) + "']";

		if (rec->readXML(docctx, s)) nodes.push_back(rec);
		else delete rec;
	};

	return basefound;
};

