/**
  * \file VecIdecVLat.h
  * vector VecIdecVLat (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVLAT_H
#define VECIDECVLAT_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVLat
	*/
namespace VecIdecVLat {
	const uint DLO = 1;
	const uint INI = 2;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

