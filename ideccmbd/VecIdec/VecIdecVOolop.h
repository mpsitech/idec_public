/**
  * \file VecIdecVOolop.h
  * vector VecIdecVOolop (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVOOLOP_H
#define VECIDECVOOLOP_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVOolop
	*/
namespace VecIdecVOolop {
	const uint INA = 1;
	const uint INB = 2;
	const uint RMV = 3;
	const uint SWP = 4;
	const uint TOA = 5;
	const uint TOB = 6;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

