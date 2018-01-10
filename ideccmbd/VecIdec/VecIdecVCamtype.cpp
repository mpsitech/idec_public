/**
  * \file VecIdecVCamtype.cpp
  * vector VecIdecVCamtype (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVCamtype.h"

/******************************************************************************
 namespace VecIdecVCamtype
 ******************************************************************************/

uint VecIdecVCamtype::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "flirtau2") return FLIRTAU2;
	else if (s == "pgbfly") return PGBFLY;
	else if (s == "pgcmln") return PGCMLN;
	else if (s == "mslife") return MSLIFE;

	return(0);
};

string VecIdecVCamtype::getSref(
			const uint ix
		) {
	if (ix == FLIRTAU2) return("flirtau2");
	else if (ix == PGBFLY) return("pgbfly");
	else if (ix == PGCMLN) return("pgcmln");
	else if (ix == MSLIFE) return("mslife");

	return("");
};

string VecIdecVCamtype::getTitle(
			const uint ix
		) {
	if (ix == FLIRTAU2) return("FLIR Tau2");
	else if (ix == PGBFLY) return("PointGrey BlackFly");
	else if (ix == PGCMLN) return("PointGrey Chameleon");
	else if (ix == MSLIFE) return("Microsoft LifeCam");

	return("");
};

void VecIdecVCamtype::appendToFeed(
			const uint ix
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getTitle(ix));
};

void VecIdecVCamtype::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i));
};

