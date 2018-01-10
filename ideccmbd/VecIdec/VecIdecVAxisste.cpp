/**
  * \file VecIdecVAxisste.cpp
  * vector VecIdecVAxisste (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVAxisste.h"

/******************************************************************************
 namespace VecIdecVAxisste
 ******************************************************************************/

uint VecIdecVAxisste::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "nc") return NC;
	else if (s == "uncal") return UNCAL;
	else if (s == "actuc") return ACTUC;
	else if (s == "ready") return READY;
	else if (s == "active") return ACTIVE;

	return(0);
};

string VecIdecVAxisste::getSref(
			const uint ix
		) {
	if (ix == NC) return("nc");
	else if (ix == UNCAL) return("uncal");
	else if (ix == ACTUC) return("actuc");
	else if (ix == READY) return("ready");
	else if (ix == ACTIVE) return("active");

	return("");
};

string VecIdecVAxisste::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == NC) return("offline");
		else if (ix == UNCAL) return("uncalibrated");
		else if (ix == ACTUC) return("in motion (uncalibrated)");
		else if (ix == READY) return("ready");
		else if (ix == ACTIVE) return("in motion");
	} else if (ixIdecVLocale == 2) {
		if (ix == NC) return("nicht verbunden");
		else if (ix == UNCAL) return("unkalibriert");
		else if (ix == ACTUC) return("in Bewegung (unkalibriert)");
		else if (ix == READY) return("bereit");
		else if (ix == ACTIVE) return("in Bewegung");
	};

	return("");
};

void VecIdecVAxisste::appendToFeed(
			const uint ix
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix, ixIdecVLocale));
};

void VecIdecVAxisste::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=5;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

