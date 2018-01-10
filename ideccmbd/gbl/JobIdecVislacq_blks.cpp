/**
  * \file JobIdecVislacq_blks.cpp
  * job handler for job JobIdecVislacq (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class JobIdecVislacq::VecVSge
 ******************************************************************************/

uint JobIdecVislacq::VecVSge::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "idle") return IDLE;
	else if (s == "ready") return READY;
	else if (s == "acqidle") return ACQIDLE;
	else if (s == "acq") return ACQ;
	else if (s == "prcidle") return PRCIDLE;
	else if (s == "prc") return PRC;

	return(0);
};

string JobIdecVislacq::VecVSge::getSref(
			const uint ix
		) {
	if (ix == IDLE) return("idle");
	else if (ix == READY) return("ready");
	else if (ix == ACQIDLE) return("acqidle");
	else if (ix == ACQ) return("acq");
	else if (ix == PRCIDLE) return("prcidle");
	else if (ix == PRC) return("prc");

	return("");
};

void JobIdecVislacq::VecVSge::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=6;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

