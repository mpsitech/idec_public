/**
  * \file VecIdecVReqitmode.h
  * vector VecIdecVReqitmode (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVREQITMODE_H
#define VECIDECVREQITMODE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVReqitmode
	*/
namespace VecIdecVReqitmode {
	const uint IDLE = 1;
	const uint NOTIFY = 2;
	const uint POLL = 3;

	uint getIx(const string& sref);
	string getSref(const uint ix);
};

#endif

