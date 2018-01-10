/**
  * \file VecIdecVIop.h
  * vector VecIdecVIop (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVIOP_H
#define VECIDECVIOP_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVIop
	*/
namespace VecIdecVIop {
	const uint INS = 1;
	const uint RETR = 2;
	const uint RETRINS = 3;
	const uint RETRUPD = 4;
	const uint RMV = 5;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

