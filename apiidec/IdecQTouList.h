/**
  * \file IdecQTouList.h
  * API code for table TblIdecQTouList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQTOULIST_H
#define IDECQTOULIST_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQTouList
  */
class IdecQTouList {

public:
	IdecQTouList(const uint jnum = 0, const string Title = "", const string stubRefIdecMMission = "", const string ftmStart = "", const string ftmStop = "", const string Area = "");

public:
	uint jnum;
	string Title;
	string stubRefIdecMMission;
	string ftmStart;
	string ftmStop;
	string Area;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQTouList
  */
class ListIdecQTouList {

public:
	ListIdecQTouList();
	ListIdecQTouList(const ListIdecQTouList& src);
	ListIdecQTouList& operator=(const ListIdecQTouList& src);
	~ListIdecQTouList();

	void clear();

public:
	vector<IdecQTouList*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

