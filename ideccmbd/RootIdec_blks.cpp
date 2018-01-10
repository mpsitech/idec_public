/**
  * \file RootIdec_blks.cpp
  * job handler for job RootIdec (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class RootIdec::DpchAppLogin
 ******************************************************************************/

RootIdec::DpchAppLogin::DpchAppLogin() : DpchAppIdec(VecIdecVDpch::DPCHAPPROOTIDECLOGIN) {
};

string RootIdec::DpchAppLogin::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(JREF)) ss.push_back("jref");
	if (has(PASSWORD)) ss.push_back("password");
	if (has(USERNAME)) ss.push_back("username");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void RootIdec::DpchAppLogin::readXML(
			pthread_mutex_t* mScr
			, map<string,ubigint>& descr
			, xmlXPathContext* docctx
			, string basexpath
			, bool addbasetag
		) {
	clear();

	string scrJref;

	bool basefound;

	if (addbasetag)
		basefound = checkUclcXPaths(docctx, basexpath, basexpath, "DpchAppRootIdecLogin");
	else
		basefound = checkXPath(docctx, basexpath);

	if (basefound) {
		if (extractStringUclc(docctx, basexpath, "scrJref", "", scrJref)) {
			jref = Scr::descramble(mScr, descr, scrJref);
			add(JREF);
		};
		if (extractStringUclc(docctx, basexpath, "password", "", password)) add(PASSWORD);
		if (extractStringUclc(docctx, basexpath, "username", "", username)) add(USERNAME);
	} else {
	};
};

