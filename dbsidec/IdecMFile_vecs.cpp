/**
  * \file IdecMFile_vecs.cpp
  * database access for table TblIdecMFile (implementation of vectors)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class TblIdecMFile::VecVRefTbl
 ******************************************************************************/

uint TblIdecMFile::VecVRefTbl::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "void") return VOID;
	else if (s == "mis") return MIS;
	else if (s == "tou") return TOU;

	return(0);
};

string TblIdecMFile::VecVRefTbl::getSref(
			const uint ix
		) {
	if (ix == VOID) return("void");
	else if (ix == MIS) return("mis");
	else if (ix == TOU) return("tou");

	return("");
};

string TblIdecMFile::VecVRefTbl::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == VOID) return("none");
		else if (ix == MIS) return("mission");
		else if (ix == TOU) return("tour");
	} else if (ixIdecVLocale == 2) {
		if (ix == VOID) return("keine");
		else if (ix == MIS) return("Mission");
		else if (ix == TOU) return("Tour");
	};

	return("");
};

void TblIdecMFile::VecVRefTbl::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=3;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

