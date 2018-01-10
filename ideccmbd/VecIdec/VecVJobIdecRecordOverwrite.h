/**
  * \file VecVJobIdecRecordOverwrite.h
  * vector VecVJobIdecRecordOverwrite (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECVJOBIDECRECORDOVERWRITE_H
#define VECVJOBIDECRECORDOVERWRITE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecVJobIdecRecordOverwrite
	*/
namespace VecVJobIdecRecordOverwrite {
	const uint NEVER = 1;
	const uint OLD = 2;
	const uint OLDVID = 3;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void fillFeed(const uint ixIdecVLocale, Feed& feed);
};

#endif

