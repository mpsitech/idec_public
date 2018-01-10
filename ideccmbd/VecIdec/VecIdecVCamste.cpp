/**
  * \file VecIdecVCamste.cpp
  * vector VecIdecVCamste (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVCamste.h"

/******************************************************************************
 namespace VecIdecVCamste
 ******************************************************************************/

uint VecIdecVCamste::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "nc") return NC;
	else if (s == "ready") return READY;
	else if (s == "active") return ACTIVE;

	return(0);
};

string VecIdecVCamste::getSref(
			const uint ix
		) {
	if (ix == NC) return("nc");
	else if (ix == READY) return("ready");
	else if (ix == ACTIVE) return("active");

	return("");
};

string VecIdecVCamste::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == NC) return("offline");
		else if (ix == READY) return("ready");
		else if (ix == ACTIVE) return("running");
	} else if (ixIdecVLocale == 2) {
		if (ix == NC) return("nicht verbunden");
		else if (ix == READY) return("bereit");
		else if (ix == ACTIVE) return("l\\u00e4uft");
	};

	return("");
};

void VecIdecVCamste::appendToFeed(
			const uint ix
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix, ixIdecVLocale));
};

void VecIdecVCamste::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

