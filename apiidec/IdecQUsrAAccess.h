/**
  * \file IdecQUsrAAccess.h
  * API code for table TblIdecQUsrAAccess (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSRAACCESS_H
#define IDECQUSRAACCESS_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsrAAccess
  */
class IdecQUsrAAccess {

public:
	IdecQUsrAAccess(const uint jnum = 0, const string srefX1IxIdecVCard = "", const string titX1IxIdecVCard = "", const string srefsIxIdecWUiaccess = "", const string titsIxIdecWUiaccess = "");

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
  * ListIdecQUsrAAccess
  */
class ListIdecQUsrAAccess {

public:
	ListIdecQUsrAAccess();
	ListIdecQUsrAAccess(const ListIdecQUsrAAccess& src);
	ListIdecQUsrAAccess& operator=(const ListIdecQUsrAAccess& src);
	~ListIdecQUsrAAccess();

	void clear();

public:
	vector<IdecQUsrAAccess*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

