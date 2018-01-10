/**
  * \file VecIdecVQrystate.cpp
  * vector VecIdecVQrystate (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVQrystate.h"

/******************************************************************************
 namespace VecIdecVQrystate
 ******************************************************************************/

uint VecIdecVQrystate::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "mnr") return MNR;
	else if (s == "ood") return OOD;
	else if (s == "slm") return SLM;
	else if (s == "utd") return UTD;

	return(0);
};

string VecIdecVQrystate::getSref(
			const uint ix
		) {
	if (ix == MNR) return("mnr");
	else if (ix == OOD) return("ood");
	else if (ix == SLM) return("slm");
	else if (ix == UTD) return("utd");

	return("");
};

