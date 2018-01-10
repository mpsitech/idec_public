/**
  * \file VecIdecVLop.cpp
  * vector VecIdecVLop (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVLop.h"

/******************************************************************************
 namespace VecIdecVLop
 ******************************************************************************/

uint VecIdecVLop::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "ins") return INS;
	else if (s == "rmv") return RMV;

	return(0);
};

string VecIdecVLop::getSref(
			const uint ix
		) {
	if (ix == INS) return("ins");
	else if (ix == RMV) return("rmv");

	return("");
};

