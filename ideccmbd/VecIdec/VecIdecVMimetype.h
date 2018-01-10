/**
  * \file VecIdecVMimetype.h
  * vector VecIdecVMimetype (declarations)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifndef VECIDECVMIMETYPE_H
#define VECIDECVMIMETYPE_H

#include <sbecore/Xmlio.h>

using namespace Xmlio;

/**
	* VecIdecVMimetype
	*/
namespace VecIdecVMimetype {
	const uint BMP = 1;
	const uint CPP = 2;
	const uint CSS = 3;
	const uint CSV = 4;
	const uint DOC = 5;
	const uint DOCX = 6;
	const uint EPS = 7;
	const uint GIF = 8;
	const uint H = 9;
	const uint HDF = 10;
	const uint HTML = 11;
	const uint JPG = 12;
	const uint JS = 13;
	const uint MAKE = 14;
	const uint NC = 15;
	const uint PDF = 16;
	const uint PNG = 17;
	const uint PPT = 18;
	const uint PPTX = 19;
	const uint SH = 20;
	const uint SQL = 21;
	const uint SVG = 22;
	const uint TEX = 23;
	const uint TGZ = 24;
	const uint TIF = 25;
	const uint TXT = 26;
	const uint XLS = 27;
	const uint XLSX = 28;
	const uint XML = 29;
	const uint ZIP = 30;

	uint getIx(const string& sref);
	string getSref(const uint ix);

	string getTitle(const uint ix);
};

#endif

