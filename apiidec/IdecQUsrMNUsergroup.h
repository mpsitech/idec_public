/**
  * \file IdecQUsrMNUsergroup.h
  * API code for table TblIdecQUsrMNUsergroup (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSRMNUSERGROUP_H
#define IDECQUSRMNUSERGROUP_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsrMNUsergroup
  */
class IdecQUsrMNUsergroup {

public:
	IdecQUsrMNUsergroup(const uint jnum = 0, const string stubMref = "", const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");

public:
	uint jnum;
	string stubMref;
	string srefIxIdecVUserlevel;
	string titIxIdecVUserlevel;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQUsrMNUsergroup
  */
class ListIdecQUsrMNUsergroup {

public:
	ListIdecQUsrMNUsergroup();
	ListIdecQUsrMNUsergroup(const ListIdecQUsrMNUsergroup& src);
	ListIdecQUsrMNUsergroup& operator=(const ListIdecQUsrMNUsergroup& src);
	~ListIdecQUsrMNUsergroup();

	void clear();

public:
	vector<IdecQUsrMNUsergroup*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

