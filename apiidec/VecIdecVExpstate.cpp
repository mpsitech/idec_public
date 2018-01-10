/**
  * \file VecIdecVExpstate.cpp
  * vector VecIdecVExpstate (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVExpstate.h"

/******************************************************************************
 namespace VecIdecVExpstate
 ******************************************************************************/

uint VecIdecVExpstate::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "detd") return DETD;
	else if (s == "maxd") return MAXD;
	else if (s == "mind") return MIND;
	else if (s == "regd") return REGD;

	return(0);
};

string VecIdecVExpstate::getSref(
			const uint ix
		) {
	if (ix == DETD) return("detd");
	else if (ix == MAXD) return("maxd");
	else if (ix == MIND) return("mind");
	else if (ix == REGD) return("regd");

	return("");
};

