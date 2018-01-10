/**
  * \file IexIdecIni.cpp
  * import/export handler for database DbsIdec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "IexIdecIni.h"

#include "IexIdecIni_blks.cpp"

/******************************************************************************
 class IexIdecIni
 ******************************************************************************/

IexIdecIni::IexIdecIni(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::IEXIDECINI, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);
};

IexIdecIni::~IexIdecIni() {
	// remove job reference from job list
	if (jref != 0) xchg->removeJobByJref(jref);
};

// IP cust --- INSERT

void IexIdecIni::reset() {
	imeiavcontrolpar.clear();
	imeiavkeylistkey.clear();
	imeiavvaluelistval.clear();
	imeimfile.clear();
	imeimusergroup.clear();

	lineno = 0;
	impcnt = 0;
};

void IexIdecIni::import(
			DbsIdec* dbsidec
		) {
	ImeitemIAVControlPar* ctlApar = NULL;
	ImeitemIAVKeylistKey* klsAkey = NULL;
	ImeitemIAVValuelistVal* vlsAval = NULL;
	ImeitemIMFile* fil = NULL;
	ImeitemIMUsergroup* usg = NULL;
	ImeitemIAMUsergroupAccess* usgAacc = NULL;
	ImeitemIJAVKeylistKey* kakJkey = NULL;
	ImeitemIMUser* usr = NULL;
	ImeitemIJMUserState* usrJste = NULL;
	ImeitemIMPerson* prs = NULL;
	ImeitemIJMPersonLastname* prsJlnm = NULL;

	uint num0;

	// IP import --- IBEGIN
	IdecRMUserMUsergroup uru;
	// IP import --- IEND

	// IP import.traverse --- RBEGIN

	// -- ImeIAVControlPar
	for (unsigned int ix0=0;ix0<imeiavcontrolpar.nodes.size();ix0++) {
		ctlApar = imeiavcontrolpar.nodes[ix0];

		//ctlApar->ixIdecVControl: IXSREF
		//ctlApar->Par: TBL
		//ctlApar->Val: TBL

		dbsidec->tblidecavcontrolpar->insertRec(ctlApar);
		impcnt++;
	};

	// -- ImeIAVKeylistKey
	for (unsigned int ix0=0;ix0<imeiavkeylistkey.nodes.size();ix0++) {
		klsAkey = imeiavkeylistkey.nodes[ix0];

		//klsAkey->klsIxIdecVKeylist: IXSREF
		klsAkey->klsNum = (ix0+1); // TBD
		klsAkey->x1IxIdecVMaintable = VecIdecVMaintable::VOID;
		klsAkey->Fixed = true;
		//klsAkey->sref: TBL
		//klsAkey->Avail: TBL
		//klsAkey->Implied: TBL
		//klsAkey->refJ: SUB

		dbsidec->tblidecavkeylistkey->insertRec(klsAkey);
		impcnt++;

		for (unsigned int ix1=0;ix1<klsAkey->imeijavkeylistkey.nodes.size();ix1++) {
			kakJkey = klsAkey->imeijavkeylistkey.nodes[ix1];

			kakJkey->refIdecAVKeylistKey = klsAkey->ref;
			//kakJkey->x1IxIdecVLocale: IXSREF
			//kakJkey->Title: TBL
			//kakJkey->Comment: TBL

			dbsidec->tblidecjavkeylistkey->insertRec(kakJkey);
			impcnt++;
		};

		if (klsAkey->imeijavkeylistkey.nodes.size() > 0) {
			kakJkey = klsAkey->imeijavkeylistkey.nodes[0];

			klsAkey->refJ = kakJkey->ref;
			klsAkey->Title = kakJkey->Title;
			klsAkey->Comment = kakJkey->Comment;
			
			dbsidec->tblidecavkeylistkey->updateRec(klsAkey);
		};
	};

	// -- ImeIAVValuelistVal
	for (unsigned int ix0=0;ix0<imeiavvaluelistval.nodes.size();ix0++) {
		vlsAval = imeiavvaluelistval.nodes[ix0];

		//vlsAval->vlsIxIdecVValuelist: IXSREF
		vlsAval->vlsNum = (ix0+1);
		//vlsAval->x1IxIdecVLocale: IXSREF
		//vlsAval->Val: TBL

		dbsidec->tblidecavvaluelistval->insertRec(vlsAval);
		impcnt++;
	};

	// -- ImeIMFile
	for (unsigned int ix0=0;ix0<imeimfile.nodes.size();ix0++) {
		fil = imeimfile.nodes[ix0];

		fil->refIxVTbl = VecIdecVMFileRefTbl::VOID;
		//fil->osrefKContent: TBL
		//fil->Filename: TBL
		//fil->srefKMimetype: TBL
		//fil->Comment: TBL

		dbsidec->tblidecmfile->insertRec(fil);
		impcnt++;
	};

	// -- ImeIMUsergroup
	for (unsigned int ix0=0;ix0<imeimusergroup.nodes.size();ix0++) {
		usg = imeimusergroup.nodes[ix0];

		//usg->sref: TBL
		//usg->Comment: TBL

		dbsidec->tblidecmusergroup->insertRec(usg);
		impcnt++;

		for (unsigned int ix1=0;ix1<usg->imeiamusergroupaccess.nodes.size();ix1++) {
			usgAacc = usg->imeiamusergroupaccess.nodes[ix1];

			usgAacc->refIdecMUsergroup = usg->ref;
			//usgAacc->x1IxIdecVCard: IXSREF
			//usgAacc->ixIdecWUiaccess: IXSREF

			dbsidec->tblidecamusergroupaccess->insertRec(usgAacc);
			impcnt++;
		};

		for (unsigned int ix1=0;ix1<usg->imeimuser.nodes.size();ix1++) {
			usr = usg->imeimuser.nodes[ix1];

			//usr->refRUsergroup: IMPPP
			usr->refIdecMUsergroup = usg->ref;
			//usr->refIdecMPerson: SUB
			//usr->sref: TBL
			//usr->refJState: SUB
			//usr->ixIdecVLocale: IXSREF
			//usr->ixIdecVUserlevel: IXSREF
			//usr->Password: TBL

			dbsidec->tblidecmuser->insertRec(usr);
			impcnt++;

			for (unsigned int ix2=0;ix2<usr->imeijmuserstate.nodes.size();ix2++) {
				usrJste = usr->imeijmuserstate.nodes[ix2];

				usrJste->refIdecMUser = usr->ref;
				//usrJste->ixVState: IXSREF

				dbsidec->tblidecjmuserstate->insertRec(usrJste);
				impcnt++;
			};

			if (usr->imeijmuserstate.nodes.size() > 0) {
				usrJste = usr->imeijmuserstate.nodes[0];

				usr->refJState = usrJste->ref;
				usr->ixVState = usrJste->ixVState;
			
				dbsidec->tblidecmuser->updateRec(usr);
			};

			for (unsigned int ix2=0;ix2<usr->imeimperson.nodes.size();ix2++) {
				prs = usr->imeimperson.nodes[ix2];

				prs->ixWDerivate = VecIdecWMPersonDerivate::USR;
				//prs->ixVSex: IXSREF
				//prs->Title: TBL
				//prs->Firstname: TBL
				//prs->refJLastname: SUB

				dbsidec->tblidecmperson->insertRec(prs);
				impcnt++;

				for (unsigned int ix3=0;ix3<prs->imeijmpersonlastname.nodes.size();ix3++) {
					prsJlnm = prs->imeijmpersonlastname.nodes[ix3];

					prsJlnm->refIdecMPerson = prs->ref;
					//prsJlnm->Lastname: TBL

					dbsidec->tblidecjmpersonlastname->insertRec(prsJlnm);
					impcnt++;
				};

				if (prs->imeijmpersonlastname.nodes.size() > 0) {
					prsJlnm = prs->imeijmpersonlastname.nodes[0];

					prs->refJLastname = prsJlnm->ref;
					prs->Lastname = prsJlnm->Lastname;
					
					dbsidec->tblidecmperson->updateRec(prs);
				};
			};

			if (usr->imeimperson.nodes.size() > 0) {
				prs = usr->imeimperson.nodes[0];

				usr->refIdecMPerson = prs->ref;

				dbsidec->tblidecmuser->updateRec(usr);
			};

			uru.refIdecMUser = usr->ref;
			uru.refIdecMUsergroup = usg->ref;
			uru.ixIdecVUserlevel = usr->ixIdecVUserlevel;
			dbsidec->tblidecrmusermusergroup->insertRec(&uru);

			usr->refRUsergroup = uru.ref;
			dbsidec->tblidecmuser->updateRec(usr);
		};
	};
	// IP import.traverse --- REND

	// IP import.ppr --- INSERT
};

void IexIdecIni::collect(
			DbsIdec* dbsidec
			, const map<uint,uint>& icsIdecVIop
		) {
	ImeitemIAVControlPar* ctlApar = NULL;
	ImeitemIAVKeylistKey* klsAkey = NULL;
	ImeitemIAVValuelistVal* vlsAval = NULL;
	ImeitemIMFile* fil = NULL;
	ImeitemIMUsergroup* usg = NULL;
	ImeitemIAMUsergroupAccess* usgAacc = NULL;
	ImeitemIJAVKeylistKey* kakJkey = NULL;
	ImeitemIMUser* usr = NULL;
	ImeitemIJMUserState* usrJste = NULL;
	ImeitemIMPerson* prs = NULL;
	ImeitemIJMPersonLastname* prsJlnm = NULL;

	uint ixIdecVIop;

	vector<ubigint> refs;

	Stcch* stcch = new Stcch(false);

	// IP collect.traverse --- BEGIN

	// -- ImeIAVControlPar
	for (unsigned int ix0=0;ix0<imeiavcontrolpar.nodes.size();ix0++) {
		ctlApar = imeiavcontrolpar.nodes[ix0];

		if (ctlApar->ref != 0) {
		};
	};

	// -- ImeIAVKeylistKey
	for (unsigned int ix0=0;ix0<imeiavkeylistkey.nodes.size();ix0++) {
		klsAkey = imeiavkeylistkey.nodes[ix0];

		if (klsAkey->ref != 0) {
		};

		if (getIxIdecVIop(icsIdecVIop, VecVIme::IMEIJAVKEYLISTKEY, ixIdecVIop)) {
			dbsidec->tblidecjavkeylistkey->loadRefsByKlk(klsAkey->ref, false, refs);
			for (unsigned int i=0;i<refs.size();i++) if (refs[i] == klsAkey->refJ) {refs[i] = refs[0]; refs[0] = klsAkey->refJ; break;};
			for (unsigned int i=0;i<refs.size();i++) klsAkey->imeijavkeylistkey.nodes.push_back(new ImeitemIJAVKeylistKey(dbsidec, refs[i]));
		};

		for (unsigned int ix1=0;ix1<klsAkey->imeijavkeylistkey.nodes.size();ix1++) {
			kakJkey = klsAkey->imeijavkeylistkey.nodes[ix1];

			if (kakJkey->ref != 0) {
			};
		};
	};

	// -- ImeIAVValuelistVal
	for (unsigned int ix0=0;ix0<imeiavvaluelistval.nodes.size();ix0++) {
		vlsAval = imeiavvaluelistval.nodes[ix0];

		if (vlsAval->ref != 0) {
		};
	};

	// -- ImeIMFile
	for (unsigned int ix0=0;ix0<imeimfile.nodes.size();ix0++) {
		fil = imeimfile.nodes[ix0];

		if (fil->ref != 0) {
		};
	};

	// -- ImeIMUsergroup
	for (unsigned int ix0=0;ix0<imeimusergroup.nodes.size();ix0++) {
		usg = imeimusergroup.nodes[ix0];

		if (usg->ref != 0) {
		};

		if (getIxIdecVIop(icsIdecVIop, VecVIme::IMEIAMUSERGROUPACCESS, ixIdecVIop)) {
			dbsidec->tblidecamusergroupaccess->loadRefsByUsg(usg->ref, false, refs);
			for (unsigned int i=0;i<refs.size();i++) usg->imeiamusergroupaccess.nodes.push_back(new ImeitemIAMUsergroupAccess(dbsidec, refs[i]));
		};

		for (unsigned int ix1=0;ix1<usg->imeiamusergroupaccess.nodes.size();ix1++) {
			usgAacc = usg->imeiamusergroupaccess.nodes[ix1];

			if (usgAacc->ref != 0) {
			};
		};

		if (getIxIdecVIop(icsIdecVIop, VecVIme::IMEIMUSER, ixIdecVIop)) {
			dbsidec->tblidecmuser->loadRefsByUsg(usg->ref, false, refs);
			for (unsigned int i=0;i<refs.size();i++) usg->imeimuser.nodes.push_back(new ImeitemIMUser(dbsidec, refs[i]));
		};

		for (unsigned int ix1=0;ix1<usg->imeimuser.nodes.size();ix1++) {
			usr = usg->imeimuser.nodes[ix1];

			if (usr->ref != 0) {
			};

			if (getIxIdecVIop(icsIdecVIop, VecVIme::IMEIJMUSERSTATE, ixIdecVIop)) {
				dbsidec->tblidecjmuserstate->loadRefsByUsr(usr->ref, false, refs);
				for (unsigned int i=0;i<refs.size();i++) if (refs[i] == usr->refJState) {refs[i] = refs[0]; refs[0] = usr->refJState; break;};
				for (unsigned int i=0;i<refs.size();i++) usr->imeijmuserstate.nodes.push_back(new ImeitemIJMUserState(dbsidec, refs[i]));
			};

			for (unsigned int ix2=0;ix2<usr->imeijmuserstate.nodes.size();ix2++) {
				usrJste = usr->imeijmuserstate.nodes[ix2];

				if (usrJste->ref != 0) {
				};
			};

			for (unsigned int ix2=0;ix2<usr->imeimperson.nodes.size();ix2++) {
				prs = usr->imeimperson.nodes[ix2];

				if (prs->ref != 0) {
				};

				if (getIxIdecVIop(icsIdecVIop, VecVIme::IMEIJMPERSONLASTNAME, ixIdecVIop)) {
					dbsidec->tblidecjmpersonlastname->loadRefsByPrs(prs->ref, false, refs);
					for (unsigned int i=0;i<refs.size();i++) if (refs[i] == prs->refJLastname) {refs[i] = refs[0]; refs[0] = prs->refJLastname; break;};
					for (unsigned int i=0;i<refs.size();i++) prs->imeijmpersonlastname.nodes.push_back(new ImeitemIJMPersonLastname(dbsidec, refs[i]));
				};

				for (unsigned int ix3=0;ix3<prs->imeijmpersonlastname.nodes.size();ix3++) {
					prsJlnm = prs->imeijmpersonlastname.nodes[ix3];

					if (prsJlnm->ref != 0) {
					};
				};
			};
		};
	};
	// IP collect.traverse --- END

	// IP collect.ppr --- INSERT

	delete stcch;
};

bool IexIdecIni::readTxt(
			Txtrd& txtrd
		) {
	bool parseok = true;

	while (txtrd.readLine()) {
		if (txtrd.comment) {
		} else if (txtrd.header && (txtrd.il == 0)) {
			if (txtrd.ixVToken == VecVIme::IMEIAVCONTROLPAR) {
				parseok = imeiavcontrolpar.readTxt(txtrd); if (!parseok) break;
			} else if (txtrd.ixVToken == VecVIme::IMEIAVKEYLISTKEY) {
				parseok = imeiavkeylistkey.readTxt(txtrd); if (!parseok) break;
			} else if (txtrd.ixVToken == VecVIme::IMEIAVVALUELISTVAL) {
				parseok = imeiavvaluelistval.readTxt(txtrd); if (!parseok) break;
			} else if (txtrd.ixVToken == VecVIme::IMEIMFILE) {
				parseok = imeimfile.readTxt(txtrd); if (!parseok) break;
			} else if (txtrd.ixVToken == VecVIme::IMEIMUSERGROUP) {
				parseok = imeimusergroup.readTxt(txtrd); if (!parseok) break;
			} else {
				parseok = false; break;
			};
		} else {
			parseok = false; break;
		};
	};

	lineno = txtrd.linecnt;

	return parseok;
};

void IexIdecIni::readXML(
			xmlXPathContext* docctx
			, string basexpath
		) {
	bool basefound;

	basefound = checkUclcXPaths(docctx, basexpath, basexpath, "IexIdecIni");

	if (basefound) {
		// look for XML sub-blocks
		imeiavcontrolpar.readXML(docctx, basexpath);
		imeiavkeylistkey.readXML(docctx, basexpath);
		imeiavvaluelistval.readXML(docctx, basexpath);
		imeimfile.readXML(docctx, basexpath);
		imeimusergroup.readXML(docctx, basexpath);
	} else {
		imeiavcontrolpar = ImeIAVControlPar();
		imeiavkeylistkey = ImeIAVKeylistKey();
		imeiavvaluelistval = ImeIAVValuelistVal();
		imeimfile = ImeIMFile();
		imeimusergroup = ImeIMUsergroup();
	};
};

bool IexIdecIni::readTxtFile(
			const string& fullpath
		) {
	bool retval;

	Txtrd rd(VecVIme::getIx);

	rd.openFile(fullpath);

	retval = readTxt(rd);

	rd.closeFile();

	return retval;
};

bool IexIdecIni::readXMLFile(
			const string& fullpath
		) {
	xmlDoc* doc = NULL;
	xmlXPathContext* docctx = NULL;

	parseFile(fullpath, &doc, &docctx);
	readXML(docctx, "/");

	closeParsed(doc, docctx);

	return true;
};

void IexIdecIni::writeTxt(
			fstream& outfile
		) {
	imeiavcontrolpar.writeTxt(outfile);
	imeiavkeylistkey.writeTxt(outfile);
	imeiavvaluelistval.writeTxt(outfile);
	imeimfile.writeTxt(outfile);
	imeimusergroup.writeTxt(outfile);
};

void IexIdecIni::writeXML(
			xmlTextWriter* wr
			, const bool shorttags
		) {
	xmlTextWriterStartElement(wr, BAD_CAST "IexIdecIni");
		imeiavcontrolpar.writeXML(wr, shorttags);
		imeiavkeylistkey.writeXML(wr, shorttags);
		imeiavvaluelistval.writeXML(wr, shorttags);
		imeimfile.writeXML(wr, shorttags);
		imeimusergroup.writeXML(wr, shorttags);
	xmlTextWriterEndElement(wr);
};

void IexIdecIni::writeTxtFile(
			const string& fullpath
		) {
	fstream txtfile;

	txtfile.open(fullpath.c_str(), ios::out);

	writeTxt(txtfile);
	
	txtfile.close();
};

void IexIdecIni::writeXMLFile(
			const string& fullpath
			, const bool shorttags
		) {
	xmlTextWriter* wr = NULL;

	startwriteFile(fullpath, &wr);
		writeXML(wr, shorttags);
	closewriteFile(wr);
};

map<uint,uint> IexIdecIni::icsIdecVIopInsAll() {
	return {{(uint)VecVIme::IMEIAVCONTROLPAR,VecIdecVIop::INS},{(uint)VecVIme::IMEIAVKEYLISTKEY,VecIdecVIop::INS},{(uint)VecVIme::IMEIAVVALUELISTVAL,VecIdecVIop::INS},{(uint)VecVIme::IMEIMFILE,VecIdecVIop::INS},{(uint)VecVIme::IMEIMUSERGROUP,VecIdecVIop::INS},{(uint)VecVIme::IMEIAMUSERGROUPACCESS,VecIdecVIop::INS},{(uint)VecVIme::IMEIJAVKEYLISTKEY,VecIdecVIop::INS},{(uint)VecVIme::IMEIMUSER,VecIdecVIop::INS},{(uint)VecVIme::IMEIJMUSERSTATE,VecIdecVIop::INS},{(uint)VecVIme::IMEIMPERSON,VecIdecVIop::INS},{(uint)VecVIme::IMEIJMPERSONLASTNAME,VecIdecVIop::INS}};
};

uint IexIdecIni::getIxIdecVIop(
			const map<uint,uint>& icsIdecVIop
			, const uint ixVIme
			, uint& ixIdecVIop
		) {
	ixIdecVIop = 0;

	auto it = icsIdecVIop.find(ixVIme);
	if (it != icsIdecVIop.end()) ixIdecVIop = it->second;

	return ixIdecVIop;
};

void IexIdecIni::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		if (req->cmd == "cmdset") {

		} else {
			cout << "\tinvalid command!" << endl;
		};
	};
};

void IexIdecIni::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
};


