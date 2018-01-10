/**
  * \file JobIdecSpotfind_blks.cpp
  * job handler for job JobIdecSpotfind (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class JobIdecSpotfind::VecVSge
 ******************************************************************************/

uint JobIdecSpotfind::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "ready") return READY;
	else if (s == "acqidle") return ACQIDLE;
	else if (s == "acq") return ACQ;
	else if (s == "prc") return PRC;

	return(0);
};

string JobIdecSpotfind::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == READY) return("ready");
	else if (ix == ACQIDLE) return("acqidle");
	else if (ix == ACQ) return("acq");
	else if (ix == PRC) return("prc");

	return("");
};

void JobIdecSpotfind::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=5;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

