/**
  * \file VecIdecVCamres.cpp
  * vector VecIdecVCamres (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVCamres.h"

/******************************************************************************
 namespace VecIdecVCamres
 ******************************************************************************/

uint VecIdecVCamres::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "off") return OFF;
	else if (s == "_160") return _160;
	else if (s == "_320") return _320;
	else if (s == "_640") return _640;
	else if (s == "_800") return _800;
	else if (s == "_1024") return _1024;
	else if (s == "_1280") return _1280;
	else if (s == "_720p") return _720P;
	else if (s == "_1080p") return _1080P;
	else if (s == "max") return MAX;

	return(0);
};

string VecIdecVCamres::getSref(
			const uint ix
		) {
	if (ix == OFF) return("off");
	else if (ix == _160) return("_160");
	else if (ix == _320) return("_320");
	else if (ix == _640) return("_640");
	else if (ix == _800) return("_800");
	else if (ix == _1024) return("_1024");
	else if (ix == _1280) return("_1280");
	else if (ix == _720P) return("_720p");
	else if (ix == _1080P) return("_1080p");
	else if (ix == MAX) return("max");

	return("");
};

string VecIdecVCamres::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == OFF) return("off");
		else if (ix == _160) return("160x120");
		else if (ix == _320) return("320x240");
		else if (ix == _640) return("640x480");
		else if (ix == _800) return("800x600");
		else if (ix == _1024) return("1024x768");
		else if (ix == _1280) return("1280x960");
		else if (ix == _720P) return("HD");
		else if (ix == _1080P) return("full HD");
		else if (ix == MAX) return("highest");
	} else if (ixIdecVLocale == 2) {
		if (ix == OFF) return("aus");
		else if (ix == MAX) return("h\\u00f6chste");
		else return(getTitle(ix, 1));
	};

	return("");
};

void VecIdecVCamres::appendToFeed(
			const uint ix
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix, ixIdecVLocale));
};

void VecIdecVCamres::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=10;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

