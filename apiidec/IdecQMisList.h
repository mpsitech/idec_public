/**
  * \file IdecQMisList.h
  * API code for table TblIdecQMisList (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQMISLIST_H
#define IDECQMISLIST_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQMisList
  */
class IdecQMisList {

public:
	IdecQMisList(const uint jnum = 0, const string Title = "", const string stubGrp = "", const string stubOwn = "", const string ftmStartd = "", const string ftmStopd = "", const string srefKCountry = "", const string titSrefKCountry = "", const string Region = "", const string Municipality = "");

public:
	uint jnum;
	string Title;
	string stubGrp;
	string stubOwn;
	string ftmStartd;
	string ftmStopd;
	string srefKCountry;
	string titSrefKCountry;
	string Region;
	string Municipality;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQMisList
  */
class ListIdecQMisList {

public:
	ListIdecQMisList();
	ListIdecQMisList(const ListIdecQMisList& src);
	ListIdecQMisList& operator=(const ListIdecQMisList& src);
	~ListIdecQMisList();

	void clear();

public:
	vector<IdecQMisList*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

