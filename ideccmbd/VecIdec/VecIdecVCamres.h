/**
  * \file VecIdecVCamres.h
  * vector VecIdecVCamres (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVCAMRES_H
#define VECIDECVCAMRES_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVCamres
	*/
namespace VecIdecVCamres {
	const uint OFF = 1;
	const uint _160 = 2;
	const uint _320 = 3;
	const uint _640 = 4;
	const uint _800 = 5;
	const uint _1024 = 6;
	const uint _1280 = 7;
	const uint _720P = 8;
	const uint _1080P = 9;
	const uint MAX = 10;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void appendToFeed(const uint ix, const uint ixIdecVLocale, Feed& feed);
	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

