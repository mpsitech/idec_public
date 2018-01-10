/**
  * \file VecIdecVLat.cpp
  * vector VecIdecVLat (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVLat.h"

/******************************************************************************
 namespace VecIdecVLat
 ******************************************************************************/

uint VecIdecVLat::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "dlo") return DLO;
	else if (s == "ini") return INI;

	return(0);
};

string VecIdecVLat::getSref(
			const uint ix
		) {
	if (ix == DLO) return("dlo");
	else if (ix == INI) return("ini");

	return("");
};

