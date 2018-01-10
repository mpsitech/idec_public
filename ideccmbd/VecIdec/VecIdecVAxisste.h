/**
  * \file VecIdecVAxisste.h
  * vector VecIdecVAxisste (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVAXISSTE_H
#define VECIDECVAXISSTE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVAxisste
	*/
namespace VecIdecVAxisste {
	const uint NC = 1;
	const uint UNCAL = 2;
	const uint ACTUC = 3;
	const uint READY = 4;
	const uint ACTIVE = 5;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void appendToFeed(const uint ix, const uint ixIdecVLocale, Feed& feed);
	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

