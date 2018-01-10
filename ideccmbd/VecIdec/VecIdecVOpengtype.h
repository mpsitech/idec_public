/**
  * \file VecIdecVOpengtype.h
  * vector VecIdecVOpengtype (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVOPENGTYPE_H
#define VECIDECVOPENGTYPE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVOpengtype
	*/
namespace VecIdecVOpengtype {

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void appendToFeed(const uint ix, const uint ixIdecVLocale, Feed& feed);
	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

