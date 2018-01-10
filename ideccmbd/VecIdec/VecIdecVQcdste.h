/**
  * \file VecIdecVQcdste.h
  * vector VecIdecVQcdste (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVQCDSTE_H
#define VECIDECVQCDSTE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVQcdste
	*/
namespace VecIdecVQcdste {
	const uint NC = 1;
	const uint COOL = 2;
	const uint READY = 3;
	const uint ACTIVE = 4;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void appendToFeed(const uint ix, const uint ixIdecVLocale, Feed& feed);
	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

