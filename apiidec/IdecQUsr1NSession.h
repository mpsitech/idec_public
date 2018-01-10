/**
  * \file IdecQUsr1NSession.h
  * API code for table TblIdecQUsr1NSession (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQUSR1NSESSION_H
#define IDECQUSR1NSESSION_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQUsr1NSession
  */
class IdecQUsr1NSession {

public:
	IdecQUsr1NSession(const uint jnum = 0, const string stubRef = "");

public:
	uint jnum;
	string stubRef;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQUsr1NSession
  */
class ListIdecQUsr1NSession {

public:
	ListIdecQUsr1NSession();
	ListIdecQUsr1NSession(const ListIdecQUsr1NSession& src);
	ListIdecQUsr1NSession& operator=(const ListIdecQUsr1NSession& src);
	~ListIdecQUsr1NSession();

	void clear();

public:
	vector<IdecQUsr1NSession*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

