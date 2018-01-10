/**
  * \file VecIdecVQrystate.h
  * vector VecIdecVQrystate (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVQRYSTATE_H
#define VECIDECVQRYSTATE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVQrystate
	*/
namespace VecIdecVQrystate {
	const uint MNR = 1;
	const uint OOD = 2;
	const uint SLM = 3;
	const uint UTD = 4;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

