/**
  * \file IdecQMisRef1NFile.h
  * API code for table TblIdecQMisRef1NFile (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef IDECQMISREF1NFILE_H
#define IDECQMISREF1NFILE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
  * IdecQMisRef1NFile
  */
class IdecQMisRef1NFile {

public:
	IdecQMisRef1NFile(const uint jnum = 0, const string stubRef = "");

public:
	uint jnum;
	string stubRef;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

/**
  * ListIdecQMisRef1NFile
  */
class ListIdecQMisRef1NFile {

public:
	ListIdecQMisRef1NFile();
	ListIdecQMisRef1NFile(const ListIdecQMisRef1NFile& src);
	ListIdecQMisRef1NFile& operator=(const ListIdecQMisRef1NFile& src);
	~ListIdecQMisRef1NFile();

	void clear();

public:
	vector<IdecQMisRef1NFile*> nodes;

public:
	bool readXML(xmlXPathContext* docctx, string basexpath = "", bool addbasetag = false);
};

#endif

