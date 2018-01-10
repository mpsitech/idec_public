/**
  * \file JobIdecQcdacq_blks.cpp
  * job handler for job JobIdecQcdacq (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class JobIdecQcdacq::VecVSge
 ******************************************************************************/

uint JobIdecQcdacq::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "cool") return COOL;
	else if (s == "ready") return READY;
	else if (s == "acqidle") return ACQIDLE;
	else if (s == "acq") return ACQ;
	else if (s == "prc") return PRC;

	return(0);
};

string JobIdecQcdacq::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == COOL) return("cool");
	else if (ix == READY) return("ready");
	else if (ix == ACQIDLE) return("acqidle");
	else if (ix == ACQ) return("acq");
	else if (ix == PRC) return("prc");

	return("");
};

void JobIdecQcdacq::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=6;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

