/**
  * \file VecIdecVOppack.h
  * vector VecIdecVOppack (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVOPPACK_H
#define VECIDECVOPPACK_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVOppack
	*/
namespace VecIdecVOppack {

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix);
	string getComment(const uint ix);

	void appendToFeed(const uint ix, Feed& feed);
	void fillFeed(Feed& feed);
};

#endif

