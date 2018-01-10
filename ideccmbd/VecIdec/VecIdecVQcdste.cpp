/**
  * \file VecIdecVQcdste.cpp
  * vector VecIdecVQcdste (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVQcdste.h"

/******************************************************************************
 namespace VecIdecVQcdste
 ******************************************************************************/

uint VecIdecVQcdste::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "nc") return NC;
	else if (s == "cool") return COOL;
	else if (s == "ready") return READY;
	else if (s == "active") return ACTIVE;

	return(0);
};

string VecIdecVQcdste::getSref(
			const uint ix
		) {
	if (ix == NC) return("nc");
	else if (ix == COOL) return("cool");
	else if (ix == READY) return("ready");
	else if (ix == ACTIVE) return("active");

	return("");
};

string VecIdecVQcdste::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == NC) return("offline");
		else if (ix == COOL) return("cooling");
		else if (ix == READY) return("ready");
		else if (ix == ACTIVE) return("recording");
	} else if (ixIdecVLocale == 2) {
		if (ix == NC) return("nicht verbunden");
		else if (ix == COOL) return("am Herunterk\\u00fchlen");
		else if (ix == READY) return("bereit");
		else if (ix == ACTIVE) return("bei der Aufnahme");
	};

	return("");
};

void VecIdecVQcdste::appendToFeed(
			const uint ix
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix, ixIdecVLocale));
};

void VecIdecVQcdste::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

