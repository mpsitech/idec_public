/**
  * \file JobIdecMechctl_blks.cpp
  * job handler for job JobIdecMechctl (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class JobIdecMechctl::VecVSge
 ******************************************************************************/

uint JobIdecMechctl::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "move") return MOVE;

	return(0);
};

string JobIdecMechctl::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == MOVE) return("move");

	return("");
};

void JobIdecMechctl::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

