/**
  * \file VecIdecVChannel.h
  * vector VecIdecVChannel (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVCHANNEL_H
#define VECIDECVCHANNEL_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVChannel
	*/
namespace VecIdecVChannel {
	const uint RED8 = 1;
	const uint GREEN8 = 2;
	const uint BLUE8 = 3;
	const uint GRAY8 = 4;
	const uint GRAY16 = 5;
	const uint DEPTHSP = 6;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

