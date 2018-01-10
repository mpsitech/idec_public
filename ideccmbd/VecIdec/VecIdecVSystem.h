/**
  * \file VecIdecVSystem.h
  * vector VecIdecVSystem (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVSYSTEM_H
#define VECIDECVSYSTEM_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVSystem
	*/
namespace VecIdecVSystem {
	const uint BASYS3FWD = 1;
	const uint DSPCOMPLEX3SPI = 2;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix);

	void fillFeed(Feed& feed);
};

#endif

