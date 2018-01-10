/**
  * \file VecIdecVOolop.cpp
  * vector VecIdecVOolop (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVOolop.h"

/******************************************************************************
 namespace VecIdecVOolop
 ******************************************************************************/

uint VecIdecVOolop::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "ina") return INA;
	else if (s == "inb") return INB;
	else if (s == "rmv") return RMV;
	else if (s == "swp") return SWP;
	else if (s == "toa") return TOA;
	else if (s == "tob") return TOB;

	return(0);
};

string VecIdecVOolop::getSref(
			const uint ix
		) {
	if (ix == INA) return("ina");
	else if (ix == INB) return("inb");
	else if (ix == RMV) return("rmv");
	else if (ix == SWP) return("swp");
	else if (ix == TOA) return("toa");
	else if (ix == TOB) return("tob");

	return("");
};

