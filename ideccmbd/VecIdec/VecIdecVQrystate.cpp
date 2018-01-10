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

string VecIdecVQrystate::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == MNR) return("might need refresh");
		else if (ix == OOD) return("out of date");
		else if (ix == SLM) return("slightly modified");
		else if (ix == UTD) return("up to date");
	} else if (ixIdecVLocale == 2) {
		if (ix == MNR) return("eventuell veraltet");
		else if (ix == OOD) return("veraltet");
		else if (ix == SLM) return("geringf\\u00fcgig ver\\u00e4ndert");
		else if (ix == UTD) return("aktuell");
	};

	return("");
};

void VecIdecVQrystate::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

