/**
  * \file VecIdecVOppack.cpp
  * vector VecIdecVOppack (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVOppack.h"

/******************************************************************************
 namespace VecIdecVOppack
 ******************************************************************************/

uint VecIdecVOppack::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	return(0);
};

string VecIdecVOppack::getSref(
			const uint ix
		) {

	return("");
};

string VecIdecVOppack::getTitle(
			const uint ix
		) {
	return(getSref(ix));

	return("");
};

string VecIdecVOppack::getComment(
			const uint ix
		) {

	return("");
};

void VecIdecVOppack::appendToFeed(
			const uint ix
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix));
};

void VecIdecVOppack::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=0;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i));
};

