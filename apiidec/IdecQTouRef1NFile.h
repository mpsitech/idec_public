/**
  * \file IdecQTouRef1NFile.h
  * API code for table TblIdecQTouRef1NFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQTOUREF1NFILE_H
#define IDECQTOUREF1NFILE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQTouRef1NFile
  */
class IdecQTouRef1NFile {

public:
	IdecQTouRef1NFile(const uint jnum = 0, const string stubRef = "");

public:
	uint jnum;
	string stubRef;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQTouRef1NFile
  */
class ListIdecQTouRef1NFile {

public:
	ListIdecQTouRef1NFile();
	ListIdecQTouRef1NFile(const ListIdecQTouRef1NFile& src);
	ListIdecQTouRef1NFile& operator=(const ListIdecQTouRef1NFile& src);
	~ListIdecQTouRef1NFile();

	void clear();

public:
	vector<IdecQTouRef1NFile*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

