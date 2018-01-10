/**
  * \file VecIdecVStled.h
  * vector VecIdecVStled (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVSTLED_H
#define VECIDECVSTLED_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVStled
	*/
namespace VecIdecVStled {
	const uint ON = 1;
	const uint OFF = 2;
	const uint TEST = 3;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

