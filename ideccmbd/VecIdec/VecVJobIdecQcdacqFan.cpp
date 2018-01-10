/**
  * \file VecVJobIdecQcdacqFan.cpp
  * vector VecVJobIdecQcdacqFan (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecVJobIdecQcdacqFan.h"

/******************************************************************************
 namespace VecVJobIdecQcdacqFan
 ******************************************************************************/

uint VecVJobIdecQcdacqFan::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "off") return OFF;
	else if (s == "offrec") return OFFREC;
	else if (s == "on") return ON;

	return(0);
};

string VecVJobIdecQcdacqFan::getSref(
			const uint ix
		) {
	if (ix == OFF) return("off");
	else if (ix == OFFREC) return("offrec");
	else if (ix == ON) return("on");

	return("");
};

string VecVJobIdecQcdacqFan::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == OFF) return("off");
		else if (ix == OFFREC) return("off during recording");
		else if (ix == ON) return("on while cooling");
	} else if (ixIdecVLocale == 2) {
		if (ix == OFF) return("aus");
		else if (ix == OFFREC) return("aus w\\u00e4hrend Aufnahme");
		else if (ix == ON) return("ein w\\u00e4hrend K\\u00fchlvorgang");
	};

	return("");
};

void VecVJobIdecQcdacqFan::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

