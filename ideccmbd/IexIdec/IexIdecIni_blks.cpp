/**
  * \file IexIdecIni_blks.cpp
  * import/export handler for database DbsIdec (implementation of blocks)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

/******************************************************************************
 class IexIdecIni::VecVIme
 ******************************************************************************/

uint IexIdecIni::VecVIme::getIx(
			const string& sref
		) {
	string s = StrMod::lc(sref);

	if (s == "imeiavcontrolpar") return IMEIAVCONTROLPAR;
	else if (s == "imeiavkeylistkey") return IMEIAVKEYLISTKEY;
	else if (s == "imeiavvaluelistval") return IMEIAVVALUELISTVAL;
	else if (s == "imeimfile") return IMEIMFILE;
	else if (s == "imeimusergroup") return IMEIMUSERGROUP;
	else if (s == "imeiamusergroupaccess") return IMEIAMUSERGROUPACCESS;
	else if (s == "imeijavkeylistkey") return IMEIJAVKEYLISTKEY;
	else if (s == "imeimuser") return IMEIMUSER;
	else if (s == "imeijmuserstate") return IMEIJMUSERSTATE;
	else if (s == "imeimperson") return IMEIMPERSON;
	else if (s == "imeijmpersonlastname") return IMEIJMPERSONLASTNAME;

	return(0);
};

string IexIdecIni::VecVIme::getSref(
			const uint ix
		) {
	if (ix == IMEIAVCONTROLPAR) return("ImeIAVControlPar");
	else if (ix == IMEIAVKEYLISTKEY) return("ImeIAVKeylistKey");
	else if (ix == IMEIAVVALUELISTVAL) return("ImeIAVValuelistVal");
	else if (ix == IMEIMFILE) return("ImeIMFile");
	else if (ix == IMEIMUSERGROUP) return("ImeIMUsergroup");
	else if (ix == IMEIAMUSERGROUPACCESS) return("ImeIAMUsergroupAccess");
	else if (ix == IMEIJAVKEYLISTKEY) return("ImeIJAVKeylistKey");
	else if (ix == IMEIMUSER) return("ImeIMUser");
	else if (ix == IMEIJMUSERSTATE) return("ImeIJMUserState");
	else if (ix == IMEIMPERSON) return("ImeIMPerson");
	else if (ix == IMEIJMPERSONLASTNAME) return("ImeIJMPersonLastname");

	return("");
};

/******************************************************************************
 class IexIdecIni::ImeitemIAVControlPar
 ******************************************************************************/

IexIdecIni::ImeitemIAVControlPar::ImeitemIAVControlPar(
			const uint ixIdecVControl
			, const string& Par
			, const string& Val
		) : IdecAVControlPar() {
	lineno = 0;
	ixWIelValid = 0;

	this->ixIdecVControl = ixIdecVControl;
	this->Par = Par;
	this->Val = Val;
};

IexIdecIni::ImeitemIAVControlPar::ImeitemIAVControlPar(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIAVControlPar() {
	IdecAVControlPar* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecavcontrolpar->loadRecByRef(ref, &rec)) {
		ixIdecVControl = rec->ixIdecVControl;
		Par = rec->Par;
		Val = rec->Val;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIAVControlPar::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) ixIdecVControl = VecIdecVControl::getIx(txtrd.fields[0]);
	if (txtrd.fields.size() > 1) Par = txtrd.fields[1];
	if (txtrd.fields.size() > 2) Val = txtrd.fields[2];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIAVControlPar::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefIxIdecVControl;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefIxIdecVControl", "ctl", srefIxIdecVControl)) {
			ixIdecVControl = VecIdecVControl::getIx(srefIxIdecVControl);
			ixWIelValid += ImeIAVControlPar::VecWIel::SREFIXIDECVCONTROL;
		};
		if (extractStringUclc(docctx, basexpath, "Par", "par", Par)) ixWIelValid += ImeIAVControlPar::VecWIel::PAR;
		if (extractStringUclc(docctx, basexpath, "Val", "val", Val)) ixWIelValid += ImeIAVControlPar::VecWIel::VAL;
	};
};

void IexIdecIni::ImeitemIAVControlPar::writeTxt(
			fstream& outfile
		) {
	outfile << VecIdecVControl::getSref(ixIdecVControl) << "\t" << Par << "\t" << Val << endl;
};

void IexIdecIni::ImeitemIAVControlPar::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","ctl","par","val"};
	else tags = {"ImeitemIAVControlPar","srefIxIdecVControl","Par","Val"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVControl::getSref(ixIdecVControl));
		writeString(wr, tags[2], Par);
		writeString(wr, tags[3], Val);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIAVControlPar::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIAVControlPar::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefixidecvcontrol") ix |= SREFIXIDECVCONTROL;
		else if (ss[i] == "par") ix |= PAR;
		else if (ss[i] == "val") ix |= VAL;
	};

	return(ix);
};

void IexIdecIni::ImeIAVControlPar::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*VAL);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIAVControlPar::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFIXIDECVCONTROL) ss.push_back("srefIxIdecVControl");
	if (ix & PAR) ss.push_back("Par");
	if (ix & VAL) ss.push_back("Val");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIAVControlPar
 ******************************************************************************/

IexIdecIni::ImeIAVControlPar::ImeIAVControlPar() {
};

IexIdecIni::ImeIAVControlPar::~ImeIAVControlPar() {
	clear();
};

void IexIdecIni::ImeIAVControlPar::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIAVControlPar::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIAVControlPar* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 0)) {
			ii = new IexIdecIni::ImeitemIAVControlPar();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIAVControlPar::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIAVControlPar* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIAVControlPar");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIAVControlPar", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIAVControlPar";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIAVControlPar();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIAVControlPar::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "ImeIAVControlPar." << StrMod::replaceChar(ImeIAVControlPar::VecWIel::getSrefs(7), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIAVControlPar::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIAVControlPar");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIJAVKeylistKey
 ******************************************************************************/

IexIdecIni::ImeitemIJAVKeylistKey::ImeitemIJAVKeylistKey(
			const uint x1IxIdecVLocale
			, const string& Title
			, const string& Comment
		) : IdecJAVKeylistKey() {
	lineno = 0;
	ixWIelValid = 0;

	this->x1IxIdecVLocale = x1IxIdecVLocale;
	this->Title = Title;
	this->Comment = Comment;
};

IexIdecIni::ImeitemIJAVKeylistKey::ImeitemIJAVKeylistKey(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIJAVKeylistKey() {
	IdecJAVKeylistKey* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecjavkeylistkey->loadRecByRef(ref, &rec)) {
		refIdecAVKeylistKey = rec->refIdecAVKeylistKey;
		x1IxIdecVLocale = rec->x1IxIdecVLocale;
		Title = rec->Title;
		Comment = rec->Comment;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIJAVKeylistKey::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) x1IxIdecVLocale = VecIdecVLocale::getIx(txtrd.fields[0]);
	if (txtrd.fields.size() > 1) Title = txtrd.fields[1];
	if (txtrd.fields.size() > 2) Comment = txtrd.fields[2];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIJAVKeylistKey::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefX1IxIdecVLocale;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefX1IxIdecVLocale", "lcl", srefX1IxIdecVLocale)) {
			x1IxIdecVLocale = VecIdecVLocale::getIx(srefX1IxIdecVLocale);
			ixWIelValid += ImeIJAVKeylistKey::VecWIel::SREFX1IXIDECVLOCALE;
		};
		if (extractStringUclc(docctx, basexpath, "Title", "tit", Title)) ixWIelValid += ImeIJAVKeylistKey::VecWIel::TITLE;
		if (extractStringUclc(docctx, basexpath, "Comment", "cmt", Comment)) ixWIelValid += ImeIJAVKeylistKey::VecWIel::COMMENT;
	};
};

void IexIdecIni::ImeitemIJAVKeylistKey::writeTxt(
			fstream& outfile
		) {
	outfile << "\t" << VecIdecVLocale::getSref(x1IxIdecVLocale) << "\t" << Title << "\t" << Comment << endl;
};

void IexIdecIni::ImeitemIJAVKeylistKey::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","lcl","tit","cmt"};
	else tags = {"ImeitemIJAVKeylistKey","srefX1IxIdecVLocale","Title","Comment"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVLocale::getSref(x1IxIdecVLocale));
		writeString(wr, tags[2], Title);
		writeString(wr, tags[3], Comment);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIJAVKeylistKey::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIJAVKeylistKey::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefx1ixidecvlocale") ix |= SREFX1IXIDECVLOCALE;
		else if (ss[i] == "title") ix |= TITLE;
		else if (ss[i] == "comment") ix |= COMMENT;
	};

	return(ix);
};

void IexIdecIni::ImeIJAVKeylistKey::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*COMMENT);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIJAVKeylistKey::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFX1IXIDECVLOCALE) ss.push_back("srefX1IxIdecVLocale");
	if (ix & TITLE) ss.push_back("Title");
	if (ix & COMMENT) ss.push_back("Comment");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIJAVKeylistKey
 ******************************************************************************/

IexIdecIni::ImeIJAVKeylistKey::ImeIJAVKeylistKey() {
};

IexIdecIni::ImeIJAVKeylistKey::~ImeIJAVKeylistKey() {
	clear();
};

void IexIdecIni::ImeIJAVKeylistKey::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIJAVKeylistKey::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIJAVKeylistKey* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || (txtrd.il < 1)) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 1)) {
			ii = new IexIdecIni::ImeitemIJAVKeylistKey();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIJAVKeylistKey::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIJAVKeylistKey* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIJAVKeylistKey");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIJAVKeylistKey", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIJAVKeylistKey";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIJAVKeylistKey();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIJAVKeylistKey::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "\tImeIJAVKeylistKey." << StrMod::replaceChar(ImeIJAVKeylistKey::VecWIel::getSrefs(7), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIJAVKeylistKey::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIJAVKeylistKey");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIAVKeylistKey
 ******************************************************************************/

IexIdecIni::ImeitemIAVKeylistKey::ImeitemIAVKeylistKey(
			const uint klsIxIdecVKeylist
			, const string& sref
			, const string& Avail
			, const string& Implied
		) : IdecAVKeylistKey() {
	lineno = 0;
	ixWIelValid = 0;

	this->klsIxIdecVKeylist = klsIxIdecVKeylist;
	this->sref = sref;
	this->Avail = Avail;
	this->Implied = Implied;
};

IexIdecIni::ImeitemIAVKeylistKey::ImeitemIAVKeylistKey(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIAVKeylistKey() {
	IdecAVKeylistKey* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecavkeylistkey->loadRecByRef(ref, &rec)) {
		klsIxIdecVKeylist = rec->klsIxIdecVKeylist;
		klsNum = rec->klsNum;
		x1IxIdecVMaintable = rec->x1IxIdecVMaintable;
		Fixed = rec->Fixed;
		sref = rec->sref;
		Avail = rec->Avail;
		Implied = rec->Implied;
		refJ = rec->refJ;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIAVKeylistKey::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) klsIxIdecVKeylist = VecIdecVKeylist::getIx(txtrd.fields[0]);
	if (txtrd.fields.size() > 1) sref = txtrd.fields[1];
	if (txtrd.fields.size() > 2) Avail = txtrd.fields[2];
	if (txtrd.fields.size() > 3) Implied = txtrd.fields[3];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header && (txtrd.il == 1) && (txtrd.ixVToken == VecVIme::IMEIJAVKEYLISTKEY)) {
			if (!imeijavkeylistkey.readTxt(txtrd)) return false;

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIAVKeylistKey::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefKlsIxIdecVKeylist;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefKlsIxIdecVKeylist", "kls", srefKlsIxIdecVKeylist)) {
			klsIxIdecVKeylist = VecIdecVKeylist::getIx(srefKlsIxIdecVKeylist);
			ixWIelValid += ImeIAVKeylistKey::VecWIel::SREFKLSIXIDECVKEYLIST;
		};
		if (extractStringUclc(docctx, basexpath, "sref", "srf", sref)) ixWIelValid += ImeIAVKeylistKey::VecWIel::SREF;
		if (extractStringUclc(docctx, basexpath, "Avail", "avl", Avail)) ixWIelValid += ImeIAVKeylistKey::VecWIel::AVAIL;
		if (extractStringUclc(docctx, basexpath, "Implied", "imp", Implied)) ixWIelValid += ImeIAVKeylistKey::VecWIel::IMPLIED;
		imeijavkeylistkey.readXML(docctx, basexpath);
	};
};

void IexIdecIni::ImeitemIAVKeylistKey::writeTxt(
			fstream& outfile
		) {
	outfile << VecIdecVKeylist::getSref(klsIxIdecVKeylist) << "\t" << sref << "\t" << Avail << "\t" << Implied << endl;
	imeijavkeylistkey.writeTxt(outfile);
};

void IexIdecIni::ImeitemIAVKeylistKey::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","kls","srf","avl","imp"};
	else tags = {"ImeitemIAVKeylistKey","srefKlsIxIdecVKeylist","sref","Avail","Implied"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVKeylist::getSref(klsIxIdecVKeylist));
		writeString(wr, tags[2], sref);
		writeString(wr, tags[3], Avail);
		writeString(wr, tags[4], Implied);
		imeijavkeylistkey.writeXML(wr, shorttags);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIAVKeylistKey::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIAVKeylistKey::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefklsixidecvkeylist") ix |= SREFKLSIXIDECVKEYLIST;
		else if (ss[i] == "sref") ix |= SREF;
		else if (ss[i] == "avail") ix |= AVAIL;
		else if (ss[i] == "implied") ix |= IMPLIED;
	};

	return(ix);
};

void IexIdecIni::ImeIAVKeylistKey::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*IMPLIED);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIAVKeylistKey::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFKLSIXIDECVKEYLIST) ss.push_back("srefKlsIxIdecVKeylist");
	if (ix & SREF) ss.push_back("sref");
	if (ix & AVAIL) ss.push_back("Avail");
	if (ix & IMPLIED) ss.push_back("Implied");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIAVKeylistKey
 ******************************************************************************/

IexIdecIni::ImeIAVKeylistKey::ImeIAVKeylistKey() {
};

IexIdecIni::ImeIAVKeylistKey::~ImeIAVKeylistKey() {
	clear();
};

void IexIdecIni::ImeIAVKeylistKey::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIAVKeylistKey::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIAVKeylistKey* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 0)) {
			ii = new IexIdecIni::ImeitemIAVKeylistKey();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIAVKeylistKey::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIAVKeylistKey* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIAVKeylistKey");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIAVKeylistKey", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIAVKeylistKey";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIAVKeylistKey();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIAVKeylistKey::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "ImeIAVKeylistKey." << StrMod::replaceChar(ImeIAVKeylistKey::VecWIel::getSrefs(15), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIAVKeylistKey::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIAVKeylistKey");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIAVValuelistVal
 ******************************************************************************/

IexIdecIni::ImeitemIAVValuelistVal::ImeitemIAVValuelistVal(
			const uint vlsIxIdecVValuelist
			, const uint x1IxIdecVLocale
			, const string& Val
		) : IdecAVValuelistVal() {
	lineno = 0;
	ixWIelValid = 0;

	this->vlsIxIdecVValuelist = vlsIxIdecVValuelist;
	this->x1IxIdecVLocale = x1IxIdecVLocale;
	this->Val = Val;
};

IexIdecIni::ImeitemIAVValuelistVal::ImeitemIAVValuelistVal(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIAVValuelistVal() {
	IdecAVValuelistVal* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecavvaluelistval->loadRecByRef(ref, &rec)) {
		vlsIxIdecVValuelist = rec->vlsIxIdecVValuelist;
		vlsNum = rec->vlsNum;
		x1IxIdecVLocale = rec->x1IxIdecVLocale;
		Val = rec->Val;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIAVValuelistVal::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) vlsIxIdecVValuelist = VecIdecVValuelist::getIx(txtrd.fields[0]);
	if (txtrd.fields.size() > 1) x1IxIdecVLocale = VecIdecVLocale::getIx(txtrd.fields[1]);
	if (txtrd.fields.size() > 2) Val = txtrd.fields[2];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIAVValuelistVal::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefVlsIxIdecVValuelist;
	string srefX1IxIdecVLocale;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefVlsIxIdecVValuelist", "vls", srefVlsIxIdecVValuelist)) {
			vlsIxIdecVValuelist = VecIdecVValuelist::getIx(srefVlsIxIdecVValuelist);
			ixWIelValid += ImeIAVValuelistVal::VecWIel::SREFVLSIXIDECVVALUELIST;
		};
		if (extractStringUclc(docctx, basexpath, "srefX1IxIdecVLocale", "lcl", srefX1IxIdecVLocale)) {
			x1IxIdecVLocale = VecIdecVLocale::getIx(srefX1IxIdecVLocale);
			ixWIelValid += ImeIAVValuelistVal::VecWIel::SREFX1IXIDECVLOCALE;
		};
		if (extractStringUclc(docctx, basexpath, "Val", "val", Val)) ixWIelValid += ImeIAVValuelistVal::VecWIel::VAL;
	};
};

void IexIdecIni::ImeitemIAVValuelistVal::writeTxt(
			fstream& outfile
		) {
	outfile << VecIdecVValuelist::getSref(vlsIxIdecVValuelist) << "\t" << VecIdecVLocale::getSref(x1IxIdecVLocale) << "\t" << Val << endl;
};

void IexIdecIni::ImeitemIAVValuelistVal::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","vls","lcl","val"};
	else tags = {"ImeitemIAVValuelistVal","srefVlsIxIdecVValuelist","srefX1IxIdecVLocale","Val"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVValuelist::getSref(vlsIxIdecVValuelist));
		writeString(wr, tags[2], VecIdecVLocale::getSref(x1IxIdecVLocale));
		writeString(wr, tags[3], Val);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIAVValuelistVal::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIAVValuelistVal::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefvlsixidecvvaluelist") ix |= SREFVLSIXIDECVVALUELIST;
		else if (ss[i] == "srefx1ixidecvlocale") ix |= SREFX1IXIDECVLOCALE;
		else if (ss[i] == "val") ix |= VAL;
	};

	return(ix);
};

void IexIdecIni::ImeIAVValuelistVal::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*VAL);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIAVValuelistVal::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFVLSIXIDECVVALUELIST) ss.push_back("srefVlsIxIdecVValuelist");
	if (ix & SREFX1IXIDECVLOCALE) ss.push_back("srefX1IxIdecVLocale");
	if (ix & VAL) ss.push_back("Val");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIAVValuelistVal
 ******************************************************************************/

IexIdecIni::ImeIAVValuelistVal::ImeIAVValuelistVal() {
};

IexIdecIni::ImeIAVValuelistVal::~ImeIAVValuelistVal() {
	clear();
};

void IexIdecIni::ImeIAVValuelistVal::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIAVValuelistVal::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIAVValuelistVal* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 0)) {
			ii = new IexIdecIni::ImeitemIAVValuelistVal();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIAVValuelistVal::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIAVValuelistVal* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIAVValuelistVal");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIAVValuelistVal", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIAVValuelistVal";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIAVValuelistVal();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIAVValuelistVal::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "ImeIAVValuelistVal." << StrMod::replaceChar(ImeIAVValuelistVal::VecWIel::getSrefs(7), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIAVValuelistVal::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIAVValuelistVal");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIMFile
 ******************************************************************************/

IexIdecIni::ImeitemIMFile::ImeitemIMFile(
			const string& osrefKContent
			, const string& Filename
			, const string& srefKMimetype
			, const string& Comment
		) : IdecMFile() {
	lineno = 0;
	ixWIelValid = 0;

	this->osrefKContent = osrefKContent;
	this->Filename = Filename;
	this->srefKMimetype = srefKMimetype;
	this->Comment = Comment;
};

IexIdecIni::ImeitemIMFile::ImeitemIMFile(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIMFile() {
	IdecMFile* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecmfile->loadRecByRef(ref, &rec)) {
		refIxVTbl = rec->refIxVTbl;
		osrefKContent = rec->osrefKContent;
		Filename = rec->Filename;
		srefKMimetype = rec->srefKMimetype;
		Comment = rec->Comment;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIMFile::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) osrefKContent = txtrd.fields[0];
	if (txtrd.fields.size() > 1) Filename = txtrd.fields[1];
	if (txtrd.fields.size() > 2) srefKMimetype = txtrd.fields[2];
	if (txtrd.fields.size() > 3) Comment = txtrd.fields[3];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIMFile::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "osrefKContent", "cnt", osrefKContent)) ixWIelValid += ImeIMFile::VecWIel::OSREFKCONTENT;
		if (extractStringUclc(docctx, basexpath, "Filename", "fnm", Filename)) ixWIelValid += ImeIMFile::VecWIel::FILENAME;
		if (extractStringUclc(docctx, basexpath, "srefKMimetype", "mim", srefKMimetype)) ixWIelValid += ImeIMFile::VecWIel::SREFKMIMETYPE;
		if (extractStringUclc(docctx, basexpath, "Comment", "cmt", Comment)) ixWIelValid += ImeIMFile::VecWIel::COMMENT;
	};
};

void IexIdecIni::ImeitemIMFile::writeTxt(
			fstream& outfile
		) {
	outfile << osrefKContent << "\t" << Filename << "\t" << srefKMimetype << "\t" << Comment << endl;
};

void IexIdecIni::ImeitemIMFile::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","cnt","fnm","mim","cmt"};
	else tags = {"ImeitemIMFile","osrefKContent","Filename","srefKMimetype","Comment"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], osrefKContent);
		writeString(wr, tags[2], Filename);
		writeString(wr, tags[3], srefKMimetype);
		writeString(wr, tags[4], Comment);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIMFile::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIMFile::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "osrefkcontent") ix |= OSREFKCONTENT;
		else if (ss[i] == "filename") ix |= FILENAME;
		else if (ss[i] == "srefkmimetype") ix |= SREFKMIMETYPE;
		else if (ss[i] == "comment") ix |= COMMENT;
	};

	return(ix);
};

void IexIdecIni::ImeIMFile::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*COMMENT);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIMFile::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & OSREFKCONTENT) ss.push_back("osrefKContent");
	if (ix & FILENAME) ss.push_back("Filename");
	if (ix & SREFKMIMETYPE) ss.push_back("srefKMimetype");
	if (ix & COMMENT) ss.push_back("Comment");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIMFile
 ******************************************************************************/

IexIdecIni::ImeIMFile::ImeIMFile() {
};

IexIdecIni::ImeIMFile::~ImeIMFile() {
	clear();
};

void IexIdecIni::ImeIMFile::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIMFile::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIMFile* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 0)) {
			ii = new IexIdecIni::ImeitemIMFile();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIMFile::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIMFile* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIMFile");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIMFile", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIMFile";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIMFile();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIMFile::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "ImeIMFile." << StrMod::replaceChar(ImeIMFile::VecWIel::getSrefs(15), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIMFile::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIMFile");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIAMUsergroupAccess
 ******************************************************************************/

IexIdecIni::ImeitemIAMUsergroupAccess::ImeitemIAMUsergroupAccess(
			const uint x1IxIdecVCard
			, const uint ixIdecWUiaccess
		) : IdecAMUsergroupAccess() {
	lineno = 0;
	ixWIelValid = 0;

	this->x1IxIdecVCard = x1IxIdecVCard;
	this->ixIdecWUiaccess = ixIdecWUiaccess;
};

IexIdecIni::ImeitemIAMUsergroupAccess::ImeitemIAMUsergroupAccess(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIAMUsergroupAccess() {
	IdecAMUsergroupAccess* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecamusergroupaccess->loadRecByRef(ref, &rec)) {
		refIdecMUsergroup = rec->refIdecMUsergroup;
		x1IxIdecVCard = rec->x1IxIdecVCard;
		ixIdecWUiaccess = rec->ixIdecWUiaccess;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIAMUsergroupAccess::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) x1IxIdecVCard = VecIdecVCard::getIx(txtrd.fields[0]);
	if (txtrd.fields.size() > 1) ixIdecWUiaccess = VecIdecWUiaccess::getIx(txtrd.fields[1]);

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIAMUsergroupAccess::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefX1IxIdecVCard;
	string srefsIxIdecWUiaccess;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefX1IxIdecVCard", "crd", srefX1IxIdecVCard)) {
			x1IxIdecVCard = VecIdecVCard::getIx(srefX1IxIdecVCard);
			ixWIelValid += ImeIAMUsergroupAccess::VecWIel::SREFX1IXIDECVCARD;
		};
		if (extractStringUclc(docctx, basexpath, "srefsIxIdecWUiaccess", "uac", srefsIxIdecWUiaccess)) {
			ixIdecWUiaccess = VecIdecWUiaccess::getIx(srefsIxIdecWUiaccess);
			ixWIelValid += ImeIAMUsergroupAccess::VecWIel::SREFSIXIDECWUIACCESS;
		};
	};
};

void IexIdecIni::ImeitemIAMUsergroupAccess::writeTxt(
			fstream& outfile
		) {
	outfile << "\t" << VecIdecVCard::getSref(x1IxIdecVCard) << "\t" << VecIdecWUiaccess::getSrefs(ixIdecWUiaccess) << endl;
};

void IexIdecIni::ImeitemIAMUsergroupAccess::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","crd","uac"};
	else tags = {"ImeitemIAMUsergroupAccess","srefX1IxIdecVCard","srefsIxIdecWUiaccess"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVCard::getSref(x1IxIdecVCard));
		writeString(wr, tags[2], VecIdecWUiaccess::getSrefs(ixIdecWUiaccess));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIAMUsergroupAccess::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIAMUsergroupAccess::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefx1ixidecvcard") ix |= SREFX1IXIDECVCARD;
		else if (ss[i] == "srefsixidecwuiaccess") ix |= SREFSIXIDECWUIACCESS;
	};

	return(ix);
};

void IexIdecIni::ImeIAMUsergroupAccess::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*SREFSIXIDECWUIACCESS);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIAMUsergroupAccess::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFX1IXIDECVCARD) ss.push_back("srefX1IxIdecVCard");
	if (ix & SREFSIXIDECWUIACCESS) ss.push_back("srefsIxIdecWUiaccess");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIAMUsergroupAccess
 ******************************************************************************/

IexIdecIni::ImeIAMUsergroupAccess::ImeIAMUsergroupAccess() {
};

IexIdecIni::ImeIAMUsergroupAccess::~ImeIAMUsergroupAccess() {
	clear();
};

void IexIdecIni::ImeIAMUsergroupAccess::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIAMUsergroupAccess::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIAMUsergroupAccess* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || (txtrd.il < 1)) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 1)) {
			ii = new IexIdecIni::ImeitemIAMUsergroupAccess();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIAMUsergroupAccess::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIAMUsergroupAccess* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIAMUsergroupAccess");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIAMUsergroupAccess", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIAMUsergroupAccess";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIAMUsergroupAccess();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIAMUsergroupAccess::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "\tImeIAMUsergroupAccess." << StrMod::replaceChar(ImeIAMUsergroupAccess::VecWIel::getSrefs(3), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIAMUsergroupAccess::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIAMUsergroupAccess");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIJMUserState
 ******************************************************************************/

IexIdecIni::ImeitemIJMUserState::ImeitemIJMUserState(
			const uint ixVState
		) : IdecJMUserState() {
	lineno = 0;
	ixWIelValid = 0;

	this->ixVState = ixVState;
};

IexIdecIni::ImeitemIJMUserState::ImeitemIJMUserState(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIJMUserState() {
	IdecJMUserState* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecjmuserstate->loadRecByRef(ref, &rec)) {
		refIdecMUser = rec->refIdecMUser;
		ixVState = rec->ixVState;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIJMUserState::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) ixVState = VecIdecVMUserState::getIx(txtrd.fields[0]);

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIJMUserState::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefIxVState;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefIxVState", "ste", srefIxVState)) {
			ixVState = VecIdecVMUserState::getIx(srefIxVState);
			ixWIelValid += ImeIJMUserState::VecWIel::SREFIXVSTATE;
		};
	};
};

void IexIdecIni::ImeitemIJMUserState::writeTxt(
			fstream& outfile
		) {
	outfile << "\t\t" << VecIdecVMUserState::getSref(ixVState) << endl;
};

void IexIdecIni::ImeitemIJMUserState::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","ste"};
	else tags = {"ImeitemIJMUserState","srefIxVState"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVMUserState::getSref(ixVState));
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIJMUserState::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIJMUserState::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefixvstate") ix |= SREFIXVSTATE;
	};

	return(ix);
};

void IexIdecIni::ImeIJMUserState::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*SREFIXVSTATE);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIJMUserState::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFIXVSTATE) ss.push_back("srefIxVState");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIJMUserState
 ******************************************************************************/

IexIdecIni::ImeIJMUserState::ImeIJMUserState() {
};

IexIdecIni::ImeIJMUserState::~ImeIJMUserState() {
	clear();
};

void IexIdecIni::ImeIJMUserState::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIJMUserState::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIJMUserState* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || (txtrd.il < 2)) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 2)) {
			ii = new IexIdecIni::ImeitemIJMUserState();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIJMUserState::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIJMUserState* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIJMUserState");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIJMUserState", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIJMUserState";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIJMUserState();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIJMUserState::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "\t\tImeIJMUserState." << StrMod::replaceChar(ImeIJMUserState::VecWIel::getSrefs(1), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIJMUserState::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIJMUserState");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIJMPersonLastname
 ******************************************************************************/

IexIdecIni::ImeitemIJMPersonLastname::ImeitemIJMPersonLastname(
			const string& Lastname
		) : IdecJMPersonLastname() {
	lineno = 0;
	ixWIelValid = 0;

	this->Lastname = Lastname;
};

IexIdecIni::ImeitemIJMPersonLastname::ImeitemIJMPersonLastname(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIJMPersonLastname() {
	IdecJMPersonLastname* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecjmpersonlastname->loadRecByRef(ref, &rec)) {
		refIdecMPerson = rec->refIdecMPerson;
		Lastname = rec->Lastname;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIJMPersonLastname::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) Lastname = txtrd.fields[0];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIJMPersonLastname::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "Lastname", "lnm", Lastname)) ixWIelValid += ImeIJMPersonLastname::VecWIel::LASTNAME;
	};
};

void IexIdecIni::ImeitemIJMPersonLastname::writeTxt(
			fstream& outfile
		) {
	outfile << "\t\t\t" << Lastname << endl;
};

void IexIdecIni::ImeitemIJMPersonLastname::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","lnm"};
	else tags = {"ImeitemIJMPersonLastname","Lastname"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], Lastname);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIJMPersonLastname::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIJMPersonLastname::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "lastname") ix |= LASTNAME;
	};

	return(ix);
};

void IexIdecIni::ImeIJMPersonLastname::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*LASTNAME);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIJMPersonLastname::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & LASTNAME) ss.push_back("Lastname");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIJMPersonLastname
 ******************************************************************************/

IexIdecIni::ImeIJMPersonLastname::ImeIJMPersonLastname() {
};

IexIdecIni::ImeIJMPersonLastname::~ImeIJMPersonLastname() {
	clear();
};

void IexIdecIni::ImeIJMPersonLastname::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIJMPersonLastname::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIJMPersonLastname* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || (txtrd.il < 3)) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 3)) {
			ii = new IexIdecIni::ImeitemIJMPersonLastname();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIJMPersonLastname::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIJMPersonLastname* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIJMPersonLastname");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIJMPersonLastname", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIJMPersonLastname";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIJMPersonLastname();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIJMPersonLastname::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "\t\t\tImeIJMPersonLastname." << StrMod::replaceChar(ImeIJMPersonLastname::VecWIel::getSrefs(1), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIJMPersonLastname::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIJMPersonLastname");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIMPerson
 ******************************************************************************/

IexIdecIni::ImeitemIMPerson::ImeitemIMPerson(
			const uint ixVSex
			, const string& Title
			, const string& Firstname
		) : IdecMPerson() {
	lineno = 0;
	ixWIelValid = 0;

	this->ixVSex = ixVSex;
	this->Title = Title;
	this->Firstname = Firstname;
};

IexIdecIni::ImeitemIMPerson::ImeitemIMPerson(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIMPerson() {
	IdecMPerson* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecmperson->loadRecByRef(ref, &rec)) {
		ixWDerivate = rec->ixWDerivate;
		ixVSex = rec->ixVSex;
		Title = rec->Title;
		Firstname = rec->Firstname;
		refJLastname = rec->refJLastname;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIMPerson::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) ixVSex = VecIdecVMPersonSex::getIx(txtrd.fields[0]);
	if (txtrd.fields.size() > 1) Title = txtrd.fields[1];
	if (txtrd.fields.size() > 2) Firstname = txtrd.fields[2];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header && (txtrd.il == 3) && (txtrd.ixVToken == VecVIme::IMEIJMPERSONLASTNAME)) {
			if (!imeijmpersonlastname.readTxt(txtrd)) return false;

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIMPerson::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefIxVSex;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "srefIxVSex", "sex", srefIxVSex)) {
			ixVSex = VecIdecVMPersonSex::getIx(srefIxVSex);
			ixWIelValid += ImeIMPerson::VecWIel::SREFIXVSEX;
		};
		if (extractStringUclc(docctx, basexpath, "Title", "tit", Title)) ixWIelValid += ImeIMPerson::VecWIel::TITLE;
		if (extractStringUclc(docctx, basexpath, "Firstname", "fnm", Firstname)) ixWIelValid += ImeIMPerson::VecWIel::FIRSTNAME;
		imeijmpersonlastname.readXML(docctx, basexpath);
	};
};

void IexIdecIni::ImeitemIMPerson::writeTxt(
			fstream& outfile
		) {
	outfile << "\t\t" << VecIdecVMPersonSex::getSref(ixVSex) << "\t" << Title << "\t" << Firstname << endl;
	imeijmpersonlastname.writeTxt(outfile);
};

void IexIdecIni::ImeitemIMPerson::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","sex","tit","fnm"};
	else tags = {"ImeitemIMPerson","srefIxVSex","Title","Firstname"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], VecIdecVMPersonSex::getSref(ixVSex));
		writeString(wr, tags[2], Title);
		writeString(wr, tags[3], Firstname);
		imeijmpersonlastname.writeXML(wr, shorttags);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIMPerson::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIMPerson::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "srefixvsex") ix |= SREFIXVSEX;
		else if (ss[i] == "title") ix |= TITLE;
		else if (ss[i] == "firstname") ix |= FIRSTNAME;
	};

	return(ix);
};

void IexIdecIni::ImeIMPerson::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*FIRSTNAME);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIMPerson::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREFIXVSEX) ss.push_back("srefIxVSex");
	if (ix & TITLE) ss.push_back("Title");
	if (ix & FIRSTNAME) ss.push_back("Firstname");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIMPerson
 ******************************************************************************/

IexIdecIni::ImeIMPerson::ImeIMPerson() {
};

IexIdecIni::ImeIMPerson::~ImeIMPerson() {
	clear();
};

void IexIdecIni::ImeIMPerson::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIMPerson::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIMPerson* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || (txtrd.il < 2)) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 2)) {
			ii = new IexIdecIni::ImeitemIMPerson();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIMPerson::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIMPerson* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIMPerson");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIMPerson", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIMPerson";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIMPerson();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIMPerson::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "\t\tImeIMPerson." << StrMod::replaceChar(ImeIMPerson::VecWIel::getSrefs(7), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIMPerson::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIMPerson");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIMUser
 ******************************************************************************/

IexIdecIni::ImeitemIMUser::ImeitemIMUser(
			const string& sref
			, const uint ixIdecVLocale
			, const uint ixIdecVUserlevel
			, const string& Password
		) : IdecMUser() {
	lineno = 0;
	ixWIelValid = 0;

	this->sref = sref;
	this->ixIdecVLocale = ixIdecVLocale;
	this->ixIdecVUserlevel = ixIdecVUserlevel;
	this->Password = Password;
};

IexIdecIni::ImeitemIMUser::ImeitemIMUser(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIMUser() {
	IdecMUser* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecmuser->loadRecByRef(ref, &rec)) {
		refRUsergroup = rec->refRUsergroup;
		refIdecMUsergroup = rec->refIdecMUsergroup;
		refIdecMPerson = rec->refIdecMPerson;
		sref = rec->sref;
		refJState = rec->refJState;
		ixIdecVLocale = rec->ixIdecVLocale;
		ixIdecVUserlevel = rec->ixIdecVUserlevel;
		Password = rec->Password;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIMUser::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) sref = txtrd.fields[0];
	if (txtrd.fields.size() > 1) ixIdecVLocale = VecIdecVLocale::getIx(txtrd.fields[1]);
	if (txtrd.fields.size() > 2) ixIdecVUserlevel = VecIdecVUserlevel::getIx(txtrd.fields[2]);
	if (txtrd.fields.size() > 3) Password = txtrd.fields[3];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header && (txtrd.il == 2) && (txtrd.ixVToken == VecVIme::IMEIJMUSERSTATE)) {
			if (!imeijmuserstate.readTxt(txtrd)) return false;

		} else if (txtrd.header && (txtrd.il == 2) && (txtrd.ixVToken == VecVIme::IMEIMPERSON)) {
			if (!imeimperson.readTxt(txtrd)) return false;

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIMUser::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	string srefIxIdecVLocale;
	string srefIxIdecVUserlevel;

	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "sref", "srf", sref)) ixWIelValid += ImeIMUser::VecWIel::SREF;
		if (extractStringUclc(docctx, basexpath, "srefIxIdecVLocale", "lcl", srefIxIdecVLocale)) {
			ixIdecVLocale = VecIdecVLocale::getIx(srefIxIdecVLocale);
			ixWIelValid += ImeIMUser::VecWIel::SREFIXIDECVLOCALE;
		};
		if (extractStringUclc(docctx, basexpath, "srefIxIdecVUserlevel", "ulv", srefIxIdecVUserlevel)) {
			ixIdecVUserlevel = VecIdecVUserlevel::getIx(srefIxIdecVUserlevel);
			ixWIelValid += ImeIMUser::VecWIel::SREFIXIDECVUSERLEVEL;
		};
		if (extractStringUclc(docctx, basexpath, "Password", "pwd", Password)) ixWIelValid += ImeIMUser::VecWIel::PASSWORD;
		imeijmuserstate.readXML(docctx, basexpath);
		imeimperson.readXML(docctx, basexpath);
	};
};

void IexIdecIni::ImeitemIMUser::writeTxt(
			fstream& outfile
		) {
	outfile << "\t" << sref << "\t" << VecIdecVLocale::getSref(ixIdecVLocale) << "\t" << VecIdecVUserlevel::getSref(ixIdecVUserlevel) << "\t" << Password << endl;
	imeijmuserstate.writeTxt(outfile);
	imeimperson.writeTxt(outfile);
};

void IexIdecIni::ImeitemIMUser::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","srf","lcl","ulv","pwd"};
	else tags = {"ImeitemIMUser","sref","srefIxIdecVLocale","srefIxIdecVUserlevel","Password"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], sref);
		writeString(wr, tags[2], VecIdecVLocale::getSref(ixIdecVLocale));
		writeString(wr, tags[3], VecIdecVUserlevel::getSref(ixIdecVUserlevel));
		writeString(wr, tags[4], Password);
		imeijmuserstate.writeXML(wr, shorttags);
		imeimperson.writeXML(wr, shorttags);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIMUser::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIMUser::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "sref") ix |= SREF;
		else if (ss[i] == "srefixidecvlocale") ix |= SREFIXIDECVLOCALE;
		else if (ss[i] == "srefixidecvuserlevel") ix |= SREFIXIDECVUSERLEVEL;
		else if (ss[i] == "password") ix |= PASSWORD;
	};

	return(ix);
};

void IexIdecIni::ImeIMUser::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*PASSWORD);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIMUser::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREF) ss.push_back("sref");
	if (ix & SREFIXIDECVLOCALE) ss.push_back("srefIxIdecVLocale");
	if (ix & SREFIXIDECVUSERLEVEL) ss.push_back("srefIxIdecVUserlevel");
	if (ix & PASSWORD) ss.push_back("Password");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIMUser
 ******************************************************************************/

IexIdecIni::ImeIMUser::ImeIMUser() {
};

IexIdecIni::ImeIMUser::~ImeIMUser() {
	clear();
};

void IexIdecIni::ImeIMUser::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIMUser::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIMUser* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header || (txtrd.il < 1)) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 1)) {
			ii = new IexIdecIni::ImeitemIMUser();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIMUser::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIMUser* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIMUser");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIMUser", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIMUser";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIMUser();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIMUser::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "\tImeIMUser." << StrMod::replaceChar(ImeIMUser::VecWIel::getSrefs(15), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIMUser::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIMUser");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

/******************************************************************************
 class IexIdecIni::ImeitemIMUsergroup
 ******************************************************************************/

IexIdecIni::ImeitemIMUsergroup::ImeitemIMUsergroup(
			const string& sref
			, const string& Comment
		) : IdecMUsergroup() {
	lineno = 0;
	ixWIelValid = 0;

	this->sref = sref;
	this->Comment = Comment;
};

IexIdecIni::ImeitemIMUsergroup::ImeitemIMUsergroup(
			DbsIdec* dbsidec
			, const ubigint ref
		) : ImeitemIMUsergroup() {
	IdecMUsergroup* rec = NULL;

	this->ref = ref;

	if (dbsidec->tblidecmusergroup->loadRecByRef(ref, &rec)) {
		sref = rec->sref;
		Comment = rec->Comment;

		delete rec;
	};
};

bool IexIdecIni::ImeitemIMUsergroup::readTxt(
			Txtrd& txtrd
		) {
	this->lineno = txtrd.linecnt;

	if (txtrd.fields.size() > 0) sref = txtrd.fields[0];
	if (txtrd.fields.size() > 1) Comment = txtrd.fields[1];

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header && (txtrd.il == 1) && (txtrd.ixVToken == VecVIme::IMEIAMUSERGROUPACCESS)) {
			if (!imeiamusergroupaccess.readTxt(txtrd)) return false;

		} else if (txtrd.header && (txtrd.il == 1) && (txtrd.ixVToken == VecVIme::IMEIMUSER)) {
			if (!imeimuser.readTxt(txtrd)) return false;

		} else if (txtrd.header || txtrd.data) {
			txtrd.skip = true;
			break;

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeitemIMUsergroup::readXML(
			xmlXPathContext* docctx
			, const string& basexpath
		) {
	ixWIelValid = 0;

	if (checkXPath(docctx, basexpath)) {
		if (extractStringUclc(docctx, basexpath, "sref", "srf", sref)) ixWIelValid += ImeIMUsergroup::VecWIel::SREF;
		if (extractStringUclc(docctx, basexpath, "Comment", "cmt", Comment)) ixWIelValid += ImeIMUsergroup::VecWIel::COMMENT;
		imeiamusergroupaccess.readXML(docctx, basexpath);
		imeimuser.readXML(docctx, basexpath);
	};
};

void IexIdecIni::ImeitemIMUsergroup::writeTxt(
			fstream& outfile
		) {
	outfile << sref << "\t" << Comment << endl;
	imeiamusergroupaccess.writeTxt(outfile);
	imeimuser.writeTxt(outfile);
};

void IexIdecIni::ImeitemIMUsergroup::writeXML(
			xmlTextWriter* wr
			, const uint num
			, const bool shorttags
		) {
	vector<string> tags;
	if (shorttags) tags = {"Ii","srf","cmt"};
	else tags = {"ImeitemIMUsergroup","sref","Comment"};

	xmlTextWriterStartElement(wr, BAD_CAST tags[0].c_str());
		xmlTextWriterWriteAttribute(wr, BAD_CAST "num", BAD_CAST to_string(num).c_str());
		writeString(wr, tags[1], sref);
		writeString(wr, tags[2], Comment);
		imeiamusergroupaccess.writeXML(wr, shorttags);
		imeimuser.writeXML(wr, shorttags);
	xmlTextWriterEndElement(wr);
};

/******************************************************************************
 class IexIdecIni::ImeIMUsergroup::VecWIel
 ******************************************************************************/

uint IexIdecIni::ImeIMUsergroup::VecWIel::getIx(
			const string& srefs
		) {
	uint ix = 0;

	vector<string> ss;
	StrMod::stringToVector(StrMod::lc(srefs), ss);

	for (unsigned int i=0;i<ss.size();i++) {
		if (ss[i] == "sref") ix |= SREF;
		else if (ss[i] == "comment") ix |= COMMENT;
	};

	return(ix);
};

void IexIdecIni::ImeIMUsergroup::VecWIel::getIcs(
			const uint ix
			, set<uint>& ics
		) {
	ics.clear();
	for (unsigned int i=1;i<(2*COMMENT);i*=2) if (ix & i) ics.insert(i);
};

string IexIdecIni::ImeIMUsergroup::VecWIel::getSrefs(
			const uint ix
		) {
	vector<string> ss;
	string srefs;

	if (ix & SREF) ss.push_back("sref");
	if (ix & COMMENT) ss.push_back("Comment");

	StrMod::vectorToString(ss, srefs);

	return(srefs);
};

/******************************************************************************
 class IexIdecIni::ImeIMUsergroup
 ******************************************************************************/

IexIdecIni::ImeIMUsergroup::ImeIMUsergroup() {
};

IexIdecIni::ImeIMUsergroup::~ImeIMUsergroup() {
	clear();
};

void IexIdecIni::ImeIMUsergroup::clear() {
	for (unsigned int i=0;i<nodes.size();i++) delete nodes[i];
	nodes.resize(0);
};

bool IexIdecIni::ImeIMUsergroup::readTxt(
			Txtrd& txtrd
		) {
	IexIdecIni::ImeitemIMUsergroup* ii = NULL;

	clear();

	while (txtrd.readLine()) {
		if (txtrd.comment) {

		} else if (txtrd.header) {
			txtrd.skip = true;
			break;

		} else if (txtrd.data && (txtrd.il == 0)) {
			ii = new IexIdecIni::ImeitemIMUsergroup();

			if (ii->readTxt(txtrd)) {
				nodes.push_back(ii);
			} else {
				delete ii;
				return false;
			};

		} else {
			return false;
		};
	};

	return true;
};

void IexIdecIni::ImeIMUsergroup::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	vector<unsigned int> nums;
	vector<bool> _shorttags;

	IexIdecIni::ImeitemIMUsergroup* ii = NULL;

	bool basefound;

	string s;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "ImeIMUsergroup");

	clear();

	if (basefound) {
		extractList(docctx, basexpath, "ImeitemIMUsergroup", "Ii", "num", nums, _shorttags);

		for (unsigned int i=0;i<nums.size();i++) {
			s = basexpath + "/";
			if (_shorttags[i]) s += "Ii"; else s += "ImeitemIMUsergroup";
			s += "[@num='" + to_string(nums[i]) + "']";

			ii = new IexIdecIni::ImeitemIMUsergroup();
			ii->readXML(docctx, s);
			nodes.push_back(ii);
		};
	};
};

void IexIdecIni::ImeIMUsergroup::writeTxt(
			fstream& outfile
		) {
	if (nodes.size() > 0) {
		outfile << "ImeIMUsergroup." << StrMod::replaceChar(ImeIMUsergroup::VecWIel::getSrefs(3), ';', '\t') << endl;
		for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeTxt(outfile);
	};
};

void IexIdecIni::ImeIMUsergroup::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	if (nodes.size() > 0) {
		xmlTextWriterStartElement(wr, BAD_CAST "ImeIMUsergroup");
			for (unsigned int i=0;i<nodes.size();i++) nodes[i]->writeXML(wr, i+1, shorttags);
		xmlTextWriterEndElement(wr);
	};
};

