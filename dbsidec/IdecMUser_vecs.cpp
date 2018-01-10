/**
  * \file IdecMUser_vecs.cpp
  * database access for table TblIdecMUser (implementation of vectors)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class TblIdecMUser::VecVState
 ******************************************************************************/

uint TblIdecMUser::VecVState::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "act") return ACT;
	else if (s == "dsg") return DSG;
	else if (s == "due") return DUE;
	else if (s == "exp") return EXP;

	return(0);
};

string TblIdecMUser::VecVState::getSref(
			const uint ix
		) {
	if (ix == ACT) return("act");
	else if (ix == DSG) return("dsg");
	else if (ix == DUE) return("due");
	else if (ix == EXP) return("exp");

	return("");
};

string TblIdecMUser::VecVState::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == ACT) return("active");
		else if (ix == DSG) return("designated");
		else if (ix == DUE) return("due for expiration");
		else if (ix == EXP) return("expired");
	} else if (ixIdecVLocale == 2) {
		if (ix == ACT) return("aktiv");
		else if (ix == DSG) return("vorgesehen");
		else if (ix == DUE) return("l\\u00e4uft ab");
		else if (ix == EXP) return("abgelaufen");
	};

	return("");
};

void TblIdecMUser::VecVState::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=4;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

