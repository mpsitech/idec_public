/**
  * \file JobIdecAutdet1_blks.cpp
  * job handler for job JobIdecAutdet1 (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class JobIdecAutdet1::VecVSge
 ******************************************************************************/

uint JobIdecAutdet1::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "survey") return SURVEY;
	else if (s == "pos") return POS;
	else if (s == "prc") return PRC;

	return(0);
};

string JobIdecAutdet1::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == SURVEY) return("survey");
	else if (ix == POS) return("pos");
	else if (ix == PRC) return("prc");

	return("");
};

void JobIdecAutdet1::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

