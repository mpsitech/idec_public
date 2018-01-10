/**
  * \file VecIdecVSqrgrp.cpp
  * vector VecIdecVSqrgrp (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVSqrgrp.h"

/******************************************************************************
 namespace VecIdecVSqrgrp
 ******************************************************************************/

uint VecIdecVSqrgrp::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "r0") return R0;
	else if (s == "r1") return R1;
	else if (s == "r2") return R2;
	else if (s == "r3") return R3;
	else if (s == "s0") return S0;
	else if (s == "s1") return S1;
	else if (s == "s2") return S2;
	else if (s == "s3") return S3;

	return(0);
};

string VecIdecVSqrgrp::getSref(
			const uint ix
		) {
	if (ix == R0) return("r0");
	else if (ix == R1) return("r1");
	else if (ix == R2) return("r2");
	else if (ix == R3) return("r3");
	else if (ix == S0) return("s0");
	else if (ix == S1) return("s1");
	else if (ix == S2) return("s2");
	else if (ix == S3) return("s3");

	return("");
};

void VecIdecVSqrgrp::appendToFeed(
			const uint ix
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getSref(ix));
};

void VecIdecVSqrgrp::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=8;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

