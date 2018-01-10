/**
  * \file IdecQUsrList.h
  * API code for table TblIdecQUsrList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSRLIST_H
#define IDECQUSRLIST_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsrList
  */
class IdecQUsrList {

public:
	IdecQUsrList(const uint jnum = 0, const string stubRefIdecMPerson = "", const string sref = "", const string stubRefIdecMUsergroup = "", const string srefIxVState = "", const string titIxVState = "", const string srefIxIdecVLocale = "", const string titIxIdecVLocale = "", const string srefIxIdecVUserlevel = "", const string titIxIdecVUserlevel = "");

public:
	uint jnum;
	string stubRefIdecMPerson;
	string sref;
	string stubRefIdecMUsergroup;
	string srefIxVState;
	string titIxVState;
	string srefIxIdecVLocale;
	string titIxIdecVLocale;
	string srefIxIdecVUserlevel;
	string titIxIdecVUserlevel;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQUsrList
  */
class ListIdecQUsrList {

public:
	ListIdecQUsrList();
	ListIdecQUsrList(const ListIdecQUsrList& src);
	ListIdecQUsrList& operator=(const ListIdecQUsrList& src);
	~ListIdecQUsrList();

	void clear();

public:
	vector<IdecQUsrList*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

