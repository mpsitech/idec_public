/**
  * \file VecIdecVTag.h
  * vector VecIdecVTag (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVTAG_H
#define VECIDECVTAG_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVTag
	*/
namespace VecIdecVTag {
	const uint ABOUT = 1;
	const uint ALLOW = 2;
	const uint ALWAYS = 3;
	const uint CANCEL = 4;
	const uint CLEAR = 5;
	const uint CLOSE = 6;
	const uint CLSESS = 7;
	const uint CLUST = 8;
	const uint CREATE = 9;
	const uint DENY = 10;
	const uint DETAIL = 11;
	const uint DONE = 12;
	const uint DOWNLOAD = 13;
	const uint EMPLONG = 14;
	const uint EMPSHORT = 15;
	const uint ERROR = 16;
	const uint FILENAME = 17;
	const uint FLS = 18;
	const uint FOR = 19;
	const uint GENERAL = 20;
	const uint GOTO = 21;
	const uint GRP = 22;
	const uint HELP = 23;
	const uint IMPORT = 24;
	const uint LOAINI = 25;
	const uint NAV = 26;
	const uint NEW = 27;
	const uint NO = 28;
	const uint OK = 29;
	const uint OPSCPLLAST = 30;
	const uint OPSPREP = 31;
	const uint OWN = 32;
	const uint PROCEED = 33;
	const uint PROGRESS = 34;
	const uint QUEST = 35;
	const uint REQ = 36;
	const uint RUN = 37;
	const uint SESS = 38;
	const uint SHOWLONG = 39;
	const uint SHOWSHORT = 40;
	const uint STOP = 41;
	const uint TRU = 42;
	const uint UPLOAD = 43;
	const uint YES = 44;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix, const uint ixIdecVLocale);

	void appendToFeed(const uint ix, const uint ixIdecVLocale, Feed& feed);
};

#endif

