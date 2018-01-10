/**
  * \file VecIdecVSqrgrp.h
  * vector VecIdecVSqrgrp (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVSQRGRP_H
#define VECIDECVSQRGRP_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVSqrgrp
	*/
namespace VecIdecVSqrgrp {
	const uint R0 = 1;
	const uint R1 = 2;
	const uint R2 = 3;
	const uint R3 = 4;
	const uint S0 = 5;
	const uint S1 = 6;
	const uint S2 = 7;
	const uint S3 = 8;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	void appendToFeed(const uint ix, Feed& feed);
	void fillFeed(Feed& feed);
};

#endif

