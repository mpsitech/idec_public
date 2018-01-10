/**
  * \file VecVJobIdecMechctlXlorient.cpp
  * vector VecVJobIdecMechctlXlorient (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecVJobIdecMechctlXlorient.h"

/******************************************************************************
 namespace VecVJobIdecMechctlXlorient
 ******************************************************************************/

uint VecVJobIdecMechctlXlorient::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "xup") return XUP;
	else if (s == "xdown") return XDOWN;
	else if (s == "yup") return YUP;
	else if (s == "ydown") return YDOWN;

	return(0);
};

string VecVJobIdecMechctlXlorient::getSref(
			const uint ix
		) {
	if (ix == XUP) return("xup");
	else if (ix == XDOWN) return("xdown");
	else if (ix == YUP) return("yup");
	else if (ix == YDOWN) return("ydown");

	return("");
};

