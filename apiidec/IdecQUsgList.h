/**
  * \file IdecQUsgList.h
  * API code for table TblIdecQUsgList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSGLIST_H
#define IDECQUSGLIST_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsgList
  */
class IdecQUsgList {

public:
	IdecQUsgList(const uint jnum = 0, const string sref = "");

public:
	uint jnum;
	string sref;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQUsgList
  */
class ListIdecQUsgList {

public:
	ListIdecQUsgList();
	ListIdecQUsgList(const ListIdecQUsgList& src);
	ListIdecQUsgList& operator=(const ListIdecQUsgList& src);
	~ListIdecQUsgList();

	void clear();

public:
	vector<IdecQUsgList*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

