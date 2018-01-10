/**
  * \file VecIdecVPort.cpp
  * vector VecIdecVPort (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#include "VecIdecVPort.h"

/******************************************************************************
 namespace VecIdecVPort
 ******************************************************************************/

uint VecIdecVPort::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "spi1") return SPI1;
	else if (s == "spi2") return SPI2;
	else if (s == "spi3") return SPI3;
	else if (s == "gpio1") return GPIO1;
	else if (s == "gpio2") return GPIO2;
	else if (s == "led1") return LED1;
	else if (s == "led2") return LED2;
	else if (s == "usbhost") return USBHOST;
	else if (s == "usbotg") return USBOTG;

	return(0);
};

string VecIdecVPort::getSref(
			const uint ix
		) {
	if (ix == SPI1) return("spi1");
	else if (ix == SPI2) return("spi2");
	else if (ix == SPI3) return("spi3");
	else if (ix == GPIO1) return("gpio1");
	else if (ix == GPIO2) return("gpio2");
	else if (ix == LED1) return("led1");
	else if (ix == LED2) return("led2");
	else if (ix == USBHOST) return("usbhost");
	else if (ix == USBOTG) return("usbotg");

	return("");
};

void VecIdecVPort::appendToFeed(
			const uint ix
			, Feed& feed
		) {
	feed.appendIxSrefTitles(ix, getSref(ix), getSref(ix));
};

void VecIdecVPort::fillFeed(
			Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=9;i++) feed.appendIxSrefTitles(i, getSref(i), getSref(i));
};

