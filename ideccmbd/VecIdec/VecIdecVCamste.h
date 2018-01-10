/**
  * \file VecIdecVCamste.h
  * vector VecIdecVCamste (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVCAMSTE_H
#define VECIDECVCAMSTE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVCamste
	*/
namespace VecIdecVCamste {
	const uint NC = 1;
	const uint READY = 2;
	const uint ACTIVE = 3;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void appendToFeed(const uint ix, const uint ixIdecVLocale, Feed& feed);
	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

