/**
  * \file IdecQFilList.h
  * API code for table TblIdecQFilList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQFILLIST_H
#define IDECQFILLIST_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQFilList
  */
class IdecQFilList {

public:
	IdecQFilList(const uint jnum = 0, const string Filename = "", const string srefRefIxVTbl = "", const string titRefIxVTbl = "", const string stubRefUref = "", const string osrefKContent = "", const string titOsrefKContent = "", const string srefKMimetype = "", const string titSrefKMimetype = "", const usmallint Size = 0);

public:
	uint jnum;
	string Filename;
	string srefRefIxVTbl;
	string titRefIxVTbl;
	string stubRefUref;
	string osrefKContent;
	string titOsrefKContent;
	string srefKMimetype;
	string titSrefKMimetype;
	usmallint Size;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQFilList
  */
class ListIdecQFilList {

public:
	ListIdecQFilList();
	ListIdecQFilList(const ListIdecQFilList& src);
	ListIdecQFilList& operator=(const ListIdecQFilList& src);
	~ListIdecQFilList();

	void clear();

public:
	vector<IdecQFilList*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

