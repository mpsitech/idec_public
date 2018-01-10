/**
  * \file RootIdec.cpp
  * API code for job RootIdec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef _WIN32
	#include "stdafx.h"
#endif

#include "RootIdec.h"

/******************************************************************************
 class RootIdec::DpchAppLogin
 ******************************************************************************/

RootIdec::DpchAppLogin::DpchAppLogin(
			const string& scrJref
			, const string& password
			, const string& username
			, const set<uint>& mask
		) : DpchAppIdec(VecIdecVDpch::DPCHAPPROOTIDECLOGIN, scrJref) {
	if (find(mask, ALL)) this->mask = {SCRJREF, PASSWORD, USERNAME};
	else this->mask = mask;

	this->password = password;
	this->username = username;
};

string RootIdec::DpchAppLogin::getSrefsMask() {
	vector<string> ss;
	string srefs;

	if (has(SCRJREF)) ss.push_back("scrJref");
	if (has(PASSWORD)) ss.push_back("password");
	if (has(USERNAME)) ss.push_back("username");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

void RootIdec::DpchAppLogin::writeXML(
			xmlTextWriter* wr
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "DpchAppRootIdecLogin");
	xmlTextWriterWriteAttribute(wr, BAD_CAST "xmlns", BAD_CAST "http://www.mpsitech.com/idec");
		if (has(SCRJREF)) writeString(wr, "scrJref", scrJref);
		if (has(PASSWORD)) writeString(wr, "password", password);
		if (has(USERNAME)) writeString(wr, "username", username);
	xmlTextWriterEndElement(wr);
};

