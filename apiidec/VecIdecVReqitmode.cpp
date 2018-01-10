/**
  * \file VecIdecVReqitmode.cpp
  * vector VecIdecVReqitmode (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVReqitmode.h"

/******************************************************************************
 namespace VecIdecVReqitmode
 ******************************************************************************/

uint VecIdecVReqitmode::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "notify") return NOTIFY;
	else if (s == "poll") return POLL;

	return(0);
};

string VecIdecVReqitmode::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == NOTIFY) return("notify");
	else if (ix == POLL) return("poll");

	return("");
};

