/**
  * \file VecIdecVCamtype.h
  * vector VecIdecVCamtype (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVCAMTYPE_H
#define VECIDECVCAMTYPE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVCamtype
	*/
namespace VecIdecVCamtype {
	const uint FLIRTAU2 = 1;
	const uint PGBFLY = 2;
	const uint PGCMLN = 3;
	const uint MSLIFE = 4;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix);

	void appendToFeed(const uint ix, Feed& feed);
	void fillFeed(Feed& feed);
};

#endif

