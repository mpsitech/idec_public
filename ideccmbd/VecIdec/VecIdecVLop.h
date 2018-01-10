/**
  * \file VecIdecVLop.h
  * vector VecIdecVLop (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVLOP_H
#define VECIDECVLOP_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVLop
	*/
namespace VecIdecVLop {
	const uint INS = 1;
	const uint RMV = 2;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

