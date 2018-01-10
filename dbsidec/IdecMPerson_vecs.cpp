/**
  * \file IdecMPerson_vecs.cpp
  * database access for table TblIdecMPerson (implementation of vectors)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class TblIdecMPerson::VecVSex
 ******************************************************************************/

uint TblIdecMPerson::VecVSex::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "f") return F;
	else if (s == "m") return M;

	return(0);
};

string TblIdecMPerson::VecVSex::getSref(
			const uint ix
		) {
	if (ix == F) return("f");
	else if (ix == M) return("m");

	return("");
};

string TblIdecMPerson::VecVSex::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == F) return("female");
		else if (ix == M) return("male");
	} else if (ixIdecVLocale == 2) {
		if (ix == F) return("weiblich");
		else if (ix == M) return("m\\u00e4nnlich");
	};

	return("");
};

void TblIdecMPerson::VecVSex::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=2;i++) feed.appendIxSrefTitles(i, getSref(i), getTitle(i, ixIdecVLocale));
};

/******************************************************************************
 class TblIdecMPerson::VecWDerivate
 ******************************************************************************/

uint TblIdecMPerson::VecWDerivate::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "usr") ix |= USR;
	};

	return(ix);
};

void TblIdecMPerson::VecWDerivate::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*USR);i*=2) if (ix & i) ics.insert(i);
};

string TblIdecMPerson::VecWDerivate::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & USR) ss.push_back("usr");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

string TblIdecMPerson::VecWDerivate::getTitle(
			const uint ix
			, const uint ixIdecVLocale
		) {
	if (ixIdecVLocale == 1) {
		if (ix == USR) return("user");
	} else if (ixIdecVLocale == 2) {
		if (ix == USR) return("Benutzer");
	};

	return("");
};

void TblIdecMPerson::VecWDerivate::fillFeed(
			const uint ixIdecVLocale
			, Feed& feed
		) {
	feed.clear();

	for (unsigned int i=1;i<=USR;i*=2) feed.appendIxSrefTitles(i, getSrefs(i), getTitle(i, ixIdecVLocale));
};

