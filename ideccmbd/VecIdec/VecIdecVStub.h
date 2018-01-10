/**
  * \file VecIdecVStub.h
  * vector VecIdecVStub (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVSTUB_H
#define VECIDECVSTUB_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVStub
	*/
namespace VecIdecVStub {
	const uint STUBIDECFILSTD = 1;
	const uint STUBIDECMISSTD = 2;
	const uint STUBIDECPRSSTD = 3;
	const uint STUBIDECSESMENU = 4;
	const uint STUBIDECSESSTD = 5;
	const uint STUBIDECTOUSTD = 6;
	const uint STUBIDECOWN = 7;
	const uint STUBIDECUSRSTD = 8;
	const uint STUBIDECGRP = 9;
	const uint STUBIDECUSGSTD = 10;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

