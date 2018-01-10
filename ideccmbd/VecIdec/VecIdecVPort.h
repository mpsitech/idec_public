/**
  * \file VecIdecVPort.h
  * vector VecIdecVPort (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVPORT_H
#define VECIDECVPORT_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVPort
	*/
namespace VecIdecVPort {
	const uint SPI1 = 1;
	const uint SPI2 = 2;
	const uint SPI3 = 3;
	const uint GPIO1 = 4;
	const uint GPIO2 = 5;
	const uint LED1 = 6;
	const uint LED2 = 7;
	const uint USBHOST = 8;
	const uint USBOTG = 9;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	void appendToFeed(const uint ix, Feed& feed);
	void fillFeed(Feed& feed);
};

#endif

