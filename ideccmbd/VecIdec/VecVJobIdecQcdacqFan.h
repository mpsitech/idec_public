/**
  * \file VecVJobIdecQcdacqFan.h
  * vector VecVJobIdecQcdacqFan (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECVJOBIDECQCDACQFAN_H
#define VECVJOBIDECQCDACQFAN_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecVJobIdecQcdacqFan
	*/
namespace VecVJobIdecQcdacqFan {
	const uint OFF = 1;
	const uint OFFREC = 2;
	const uint ON = 3;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

