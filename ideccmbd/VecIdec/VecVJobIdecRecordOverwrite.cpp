/**
  * \file VecVJobIdecRecordOverwrite.cpp
  * vector VecVJobIdecRecordOverwrite (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecVJobIdecRecordOverwrite.h"

/******************************************************************************
 namespace VecVJobIdecRecordOverwrite
 ******************************************************************************/

uint VecVJobIdecRecordOverwrite::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "never") return NEVER;
	else if (s == "old") return OLD;
	else if (s == "oldvid") return OLDVID;

	return(0);
};

string VecVJobIdecRecordOverwrite::getSref(
			const uint ix
		) {
	if (ix == NEVER) return("never");
	else if (ix == OLD) return("old");
	else if (ix == OLDVID) return("oldvid");

	return("");
};

string VecVJobIdecRecordOverwrite::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == NEVER) return("never");
		else if (ix == OLD) return("oldest first");
		else if (ix == OLDVID) return("oldest videos first");
	} else if (ixIdecVLocale == 2) {
		if (ix == NEVER) return("niemals");
		else if (ix == OLD) return("\\u00e4lteste zuerst");
		else if (ix == OLDVID) return("\\u00e4lteste Videos zuerst");
	};

	return("");
};

void VecVJobIdecRecordOverwrite::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

