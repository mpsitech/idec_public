/**
  * \file VecIdecVStub.cpp
  * vector VecIdecVStub (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVStub.h"

/******************************************************************************
 namespace VecIdecVStub
 ******************************************************************************/

uint VecIdecVStub::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "stubidecfilstd") return STUBIDECFILSTD;
	else if (s == "stubidecmisstd") return STUBIDECMISSTD;
	else if (s == "stubidecprsstd") return STUBIDECPRSSTD;
	else if (s == "stubidecsesmenu") return STUBIDECSESMENU;
	else if (s == "stubidecsesstd") return STUBIDECSESSTD;
	else if (s == "stubidectoustd") return STUBIDECTOUSTD;
	else if (s == "stubidecown") return STUBIDECOWN;
	else if (s == "stubidecusrstd") return STUBIDECUSRSTD;
	else if (s == "stubidecgrp") return STUBIDECGRP;
	else if (s == "stubidecusgstd") return STUBIDECUSGSTD;

	return(0);
};

string VecIdecVStub::getSref(
			const uint ix
		) {
	if (ix == STUBIDECFILSTD) return("StubIdecFilStd");
	else if (ix == STUBIDECMISSTD) return("StubIdecMisStd");
	else if (ix == STUBIDECPRSSTD) return("StubIdecPrsStd");
	else if (ix == STUBIDECSESMENU) return("StubIdecSesMenu");
	else if (ix == STUBIDECSESSTD) return("StubIdecSesStd");
	else if (ix == STUBIDECTOUSTD) return("StubIdecTouStd");
	else if (ix == STUBIDECOWN) return("StubIdecOwn");
	else if (ix == STUBIDECUSRSTD) return("StubIdecUsrStd");
	else if (ix == STUBIDECGRP) return("StubIdecGrp");
	else if (ix == STUBIDECUSGSTD) return("StubIdecUsgStd");

	return("");
};

