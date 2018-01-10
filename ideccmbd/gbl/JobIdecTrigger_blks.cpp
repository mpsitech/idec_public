/**
  * \file JobIdecTrigger_blks.cpp
  * job handler for job JobIdecTrigger (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class JobIdecTrigger::VecVSge
 ******************************************************************************/

uint JobIdecTrigger::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "run") return RUN;

	return(0);
};

string JobIdecTrigger::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == RUN) return("run");

	return("");
};

void JobIdecTrigger::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

