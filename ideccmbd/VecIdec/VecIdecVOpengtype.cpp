/**
  * \file VecIdecVOpengtype.cpp
  * vector VecIdecVOpengtype (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVOpengtype.h"

/******************************************************************************
 namespace VecIdecVOpengtype
 ******************************************************************************/

uint VecIdecVOpengtype::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	return(0);
};

string VecIdecVOpengtype::getSref(
			const uint ix
		) {

	return("");
};

string VecIdecVOpengtype::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		return(getSref(ix));
	} else if (ixIdecVLocale == 2) {
		return(getTitle(ix, 1));
	};

	return("");
};

void VecIdecVOpengtype::appendToFeed(
			const uint ix
			, const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix, ixIdecVLocale));
};

void VecIdecVOpengtype::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=0;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

