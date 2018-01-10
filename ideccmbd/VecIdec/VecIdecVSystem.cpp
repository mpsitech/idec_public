/**
  * \file VecIdecVSystem.cpp
  * vector VecIdecVSystem (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVSystem.h"

/******************************************************************************
 namespace VecIdecVSystem
 ******************************************************************************/

uint VecIdecVSystem::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "basys3fwd") return BASYS3FWD;
	else if (s == "dspcomplex3spi") return DSPCOMPLEX3SPI;

	return(0);
};

string VecIdecVSystem::getSref(
			const uint ix
		) {
	if (ix == BASYS3FWD) return("basys3fwd");
	else if (ix == DSPCOMPLEX3SPI) return("dspcomplex3spi");

	return("");
};

string VecIdecVSystem::getTitle(
			const uint ix
		) {
	if (ix == BASYS3FWD) return("Basys3 forwarder");
	else if (ix == DSPCOMPLEX3SPI) return("dspcomplex3");

	return("");
};

void VecIdecVSystem::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i));
};

