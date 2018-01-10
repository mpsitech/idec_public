/**
  * \file IdecQMis1NTour.h
  * API code for table TblIdecQMis1NTour (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQMIS1NTOUR_H
#define IDECQMIS1NTOUR_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQMis1NTour
  */
class IdecQMis1NTour {

public:
	IdecQMis1NTour(const uint jnum = 0, const string stubRef = "");

public:
	uint jnum;
	string stubRef;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQMis1NTour
  */
class ListIdecQMis1NTour {

public:
	ListIdecQMis1NTour();
	ListIdecQMis1NTour(const ListIdecQMis1NTour& src);
	ListIdecQMis1NTour& operator=(const ListIdecQMis1NTour& src);
	~ListIdecQMis1NTour();

	void clear();

public:
	vector<IdecQMis1NTour*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

