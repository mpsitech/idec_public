/**
  * \file VecIdecVCorner.cpp
  * vector VecIdecVCorner (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVCorner.h"

/******************************************************************************
 namespace VecIdecVCorner
 ******************************************************************************/

uint VecIdecVCorner::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "n") return N;
	else if (s == "ne") return NE;
	else if (s == "e") return E;
	else if (s == "se") return SE;
	else if (s == "s") return S;
	else if (s == "sw") return SW;
	else if (s == "w") return W;
	else if (s == "nw") return NW;

	return(0);
};

string VecIdecVCorner::getSref(
			const uint ix
		) {
	if (ix == N) return("n");
	else if (ix == NE) return("ne");
	else if (ix == E) return("e");
	else if (ix == SE) return("se");
	else if (ix == S) return("s");
	else if (ix == SW) return("sw");
	else if (ix == W) return("w");
	else if (ix == NW) return("nw");

	return("");
};

