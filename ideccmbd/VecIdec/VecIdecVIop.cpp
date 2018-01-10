/**
  * \file VecIdecVIop.cpp
  * vector VecIdecVIop (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVIop.h"

/******************************************************************************
 namespace VecIdecVIop
 ******************************************************************************/

uint VecIdecVIop::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "ins") return INS;
	else if (s == "retr") return RETR;
	else if (s == "retrins") return RETRINS;
	else if (s == "retrupd") return RETRUPD;
	else if (s == "rmv") return RMV;

	return(0);
};

string VecIdecVIop::getSref(
			const uint ix
		) {
	if (ix == INS) return("ins");
	else if (ix == RETR) return("retr");
	else if (ix == RETRINS) return("retrins");
	else if (ix == RETRUPD) return("retrupd");
	else if (ix == RMV) return("rmv");

	return("");
};

string VecIdecVIop::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == INS) return("insert");
		else if (ix == RETR) return("retrieve");
		else if (ix == RETRINS) return("retrieve, else insert");
		else if (ix == RETRUPD) return("retrieve and update");
		else if (ix == RMV) return("remove");
	} else if (ixIdecVLocale == 2) {
		if (ix == INS) return("einf\\u00fcgen");
		else if (ix == RETR) return("auffinden");
		else if (ix == RETRINS) return("auffinden, sonst einf\\u00fcgen");
		else if (ix == RETRUPD) return("auffinden und aktualisieren");
		else if (ix == RMV) return("entfernen");
	};

	return("");
};

void VecIdecVIop::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=5;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

