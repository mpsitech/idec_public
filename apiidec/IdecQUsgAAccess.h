/**
  * \file IdecQUsgAAccess.h
  * API code for table TblIdecQUsgAAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSGAACCESS_H
#define IDECQUSGAACCESS_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsgAAccess
  */
class IdecQUsgAAccess {

public:
	IdecQUsgAAccess(const uint jnum = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");

public:
	uint jnum;
	string srefX1IxIdecVCard;
	string titX1IxIdecVCard;
	string srefsIxIdecWUiaccess;
	string titsIxIdecWUiaccess;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQUsgAAccess
  */
class ListIdecQUsgAAccess {

public:
	ListIdecQUsgAAccess();
	ListIdecQUsgAAccess(const ListIdecQUsgAAccess& src);
	ListIdecQUsgAAccess& operator=(const ListIdecQUsgAAccess& src);
	~ListIdecQUsgAAccess();

	void clear();

public:
	vector<IdecQUsgAAccess*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

