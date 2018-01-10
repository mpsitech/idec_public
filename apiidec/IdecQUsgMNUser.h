/**
  * \file IdecQUsgMNUser.h
  * API code for table TblIdecQUsgMNUser (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSGMNUSER_H
#define IDECQUSGMNUSER_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsgMNUser
  */
class IdecQUsgMNUser {

public:
	IdecQUsgMNUser(const uint jnum = 0, const string stubMref = "", const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");

public:
	uint jnum;
	string stubMref;
	string srefIxIdecVUserlevel;
	string titIxIdecVUserlevel;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQUsgMNUser
  */
class ListIdecQUsgMNUser {

public:
	ListIdecQUsgMNUser();
	ListIdecQUsgMNUser(const ListIdecQUsgMNUser& src);
	ListIdecQUsgMNUser& operator=(const ListIdecQUsgMNUser& src);
	~ListIdecQUsgMNUser();

	void clear();

public:
	vector<IdecQUsgMNUser*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

