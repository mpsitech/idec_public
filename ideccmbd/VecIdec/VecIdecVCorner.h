/**
  * \file VecIdecVCorner.h
  * vector VecIdecVCorner (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVCORNER_H
#define VECIDECVCORNER_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVCorner
	*/
namespace VecIdecVCorner {
	const uint N = 1;
	const uint NE = 2;
	const uint E = 3;
	const uint SE = 4;
	const uint S = 5;
	const uint SW = 6;
	const uint W = 7;
	const uint NW = 8;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

