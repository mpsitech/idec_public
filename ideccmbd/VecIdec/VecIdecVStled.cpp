/**
  * \file VecIdecVStled.cpp
  * vector VecIdecVStled (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVStled.h"

/******************************************************************************
 namespace VecIdecVStled
 ******************************************************************************/

uint VecIdecVStled::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "on") return ON;
	else if (s == "off") return OFF;
	else if (s == "test") return TEST;

	return(0);
};

string VecIdecVStled::getSref(
			const uint ix
		) {
	if (ix == ON) return("on");
	else if (ix == OFF) return("off");
	else if (ix == TEST) return("test");

	return("");
};

string VecIdecVStled::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == ON) return("always on");
		else if (ix == OFF) return("always off");
		else if (ix == TEST) return("off after self-test");
	} else if (ixIdecVLocale == 2) {
		if (ix == ON) return("immer an");
		else if (ix == OFF) return("immer aus");
		else if (ix == TEST) return("aus nach Selbsttest");
	};

	return("");
};

void VecIdecVStled::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

