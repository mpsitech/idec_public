/**
  * \file VecIdecVExpstate.h
  * vector VecIdecVExpstate (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVEXPSTATE_H
#define VECIDECVEXPSTATE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVExpstate
	*/
namespace VecIdecVExpstate {
	const uint DETD = 1;
	const uint MAXD = 2;
	const uint MIND = 3;
	const uint REGD = 4;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

