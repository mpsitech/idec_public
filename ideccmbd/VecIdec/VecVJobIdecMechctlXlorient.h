/**
  * \file VecVJobIdecMechctlXlorient.h
  * vector VecVJobIdecMechctlXlorient (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECVJOBIDECMECHCTLXLORIENT_H
#define VECVJOBIDECMECHCTLXLORIENT_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecVJobIdecMechctlXlorient
	*/
namespace VecVJobIdecMechctlXlorient {
	const uint XUP = 1;
	const uint XDOWN = 2;
	const uint YUP = 3;
	const uint YDOWN = 4;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

