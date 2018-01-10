/**
  * \file VecIdecVChannel.cpp
  * vector VecIdecVChannel (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVChannel.h"

/******************************************************************************
 namespace VecIdecVChannel
 ******************************************************************************/

uint VecIdecVChannel::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "red8") return RED8;
	else if (s == "green8") return GREEN8;
	else if (s == "blue8") return BLUE8;
	else if (s == "gray8") return GRAY8;
	else if (s == "gray16") return GRAY16;
	else if (s == "depthsp") return DEPTHSP;

	return(0);
};

string VecIdecVChannel::getSref(
			const uint ix
		) {
	if (ix == RED8) return("red8");
	else if (ix == GREEN8) return("green8");
	else if (ix == BLUE8) return("blue8");
	else if (ix == GRAY8) return("gray8");
	else if (ix == GRAY16) return("gray16");
	else if (ix == DEPTHSP) return("depthsp");

	return("");
};

