/**
  * \file SessIdec.cpp
  * job handler for job SessIdec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "SessIdec.h"

#include "SessIdec_blks.cpp"

/******************************************************************************
 class SessIdec
 ******************************************************************************/

SessIdec::SessIdec(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const ubigint refIdecMUser
			, const string& ip
		) : JobIdec(xchg, VecIdecVJob::SESSIDEC, jrefSup) {

	jref = xchg->addJob(this);

	crdnav = NULL;

	// IP constructor.cust1 --- INSERT

	vector<ubigint> refs;

	ubigint refSes;

	IdecMUser* usr = NULL;

	bool adm;

	ListIdecRMUserMUsergroup urus;
	IdecRMUserMUsergroup* uru = NULL;

	// create new session with start time
	time_t rawtime;
	time(&rawtime);

	refSes = dbsidec->tblidecmsession->insertNewRec(NULL, refIdecMUser, (uint) rawtime, 0, ip);

	xchg->addRefPreset(VecIdecVPreset::PREIDECSESS, jref, refSes);
	xchg->addTxtvalPreset(VecIdecVPreset::PREIDECIP, jref, ip);

	// set locale and presetings corresponding to user
	dbsidec->tblidecmuser->loadRecByRef(refIdecMUser, &usr);

	ixIdecVLocale = usr->ixIdecVLocale;
	adm = (usr->ixIdecVUserlevel == VecIdecVUserlevel::ADM);

	xchg->addBoolvalPreset(VecIdecVPreset::PREIDECADM, jref, adm);

	xchg->addRefPreset(VecIdecVPreset::PREIDECGRP, jref, usr->refIdecMUsergroup);
	xchg->addRefPreset(VecIdecVPreset::PREIDECOWN, jref, refIdecMUser);

	delete usr;

	// set jrefSess locale (for access to IdecQSelect from rst-type panel queries)
	xchg->addRefPreset(VecIdecVPreset::PREIDECJREFSESS, jref, jref);

	// fill query in IdecQSelect with all applicable user groups
	dbsidec->tblidecqselect->insertNewRec(NULL, jref, 1, 0, 0);

	if (usr->ixIdecVUserlevel == VecIdecVUserlevel::ADM) {
		dbsidec->loadRefsBySQL("SELECT ref FROM TblIdecMUsergroup ORDER BY ref ASC", false, refs);

		for (unsigned int i=0;i<refs.size();i++) dbsidec->tblidecqselect->insertNewRec(NULL, jref, i+2, 0, refs[i]);

	} else {
		dbsidec->tblidecrmusermusergroup->loadRstByUsr(refIdecMUser, false, urus);

		for (unsigned int i=0;i<urus.nodes.size();i++) {
			uru = urus.nodes[i];

			usgaccs[uru->refIdecMUsergroup] = uru->ixIdecVUserlevel;
			dbsidec->tblidecqselect->insertNewRec(NULL, jref, i+2, 0, uru->refIdecMUsergroup);
		};
	};

	// determine UI access rights for each card
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECUSG, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECUSR, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACSCF, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECSCF, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACUTL, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECUTL, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECMIS, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECTOU, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACIAQ, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECIAQ, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACAD1, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECAD1, adm, urus, refIdecMUser));
	xchg->addIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref, getIxUac(dbsidec, VecIdecVCard::CRDIDECFIL, adm, urus, refIdecMUser));

	crdnav = new CrdIdecNav(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefCrdnav = crdnav->jref;

	xchg->addClstn(VecIdecVCall::CALLIDECACCESS, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECCRDACTIVE, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECCRDCLOSE, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECCRDOPEN, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECDESCR, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECLOG, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSCR, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECREFPRESET, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

SessIdec::~SessIdec() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
uint SessIdec::checkCrdActive(
			const uint ixIdecVCard
		) {
	if (ixIdecVCard == VecIdecVCard::CRDIDECTOU) return evalCrdtouActive();
	else if (ixIdecVCard == VecIdecVCard::CRDIDECIAQ) return evalCrdiaqActive();
	else if (ixIdecVCard == VecIdecVCard::CRDIDECAD1) return evalCrdad1Active();
	else if (ixIdecVCard == VecIdecVCard::CRDIDECFIL) return evalCrdfilActive();

	return 0;
};

uint SessIdec::evalCrdtouActive() {
	// pre.refMis() > pre.void()

	vector<uint> args;
	uint a, b;

	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref)) ? VecIdecVPreset::PREIDECREFMIS : 0);
	args.push_back([](){uint preVoid = VecIdecVPreset::VOID; return preVoid;}());
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	if (a != 0) args.push_back(a);
	else args.push_back(b);

	return(args.back());
};

uint SessIdec::evalCrdiaqActive() {
	// pre.refTou() > pre.refMis()

	vector<uint> args;
	uint a, b;

	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref)) ? VecIdecVPreset::PREIDECREFTOU : 0);
	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref)) ? VecIdecVPreset::PREIDECREFMIS : 0);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	if (a != 0) args.push_back(a);
	else args.push_back(b);

	return(args.back());
};

uint SessIdec::evalCrdad1Active() {
	// pre.refTou() > pre.refMis()

	vector<uint> args;
	uint a, b;

	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref)) ? VecIdecVPreset::PREIDECREFTOU : 0);
	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref)) ? VecIdecVPreset::PREIDECREFMIS : 0);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	if (a != 0) args.push_back(a);
	else args.push_back(b);

	return(args.back());
};

uint SessIdec::evalCrdfilActive() {
	// pre.refTou() > pre.refMis() > pre.void()

	vector<uint> args;
	uint a, b;

	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref)) ? VecIdecVPreset::PREIDECREFTOU : 0);
	args.push_back((xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref)) ? VecIdecVPreset::PREIDECREFMIS : 0);
	args.push_back([](){uint preVoid = VecIdecVPreset::VOID; return preVoid;}());
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	if (a != 0) args.push_back(a);
	else args.push_back(b);
	b = args.back(); args.pop_back();
	a = args.back(); args.pop_back();
	if (a != 0) args.push_back(a);
	else args.push_back(b);

	return(args.back());
};

uint SessIdec::checkUiaccess(
			const uint ixIdecVCard
		) {
	if (ixIdecVCard == VecIdecVCard::CRDIDECUSG) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSG, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECUSR) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUSR, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECSCF) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACSCF, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECUTL) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACUTL, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECMIS) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECTOU) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACTOU, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECIAQ) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACIAQ, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECAD1) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACAD1, jref);
	else if (ixIdecVCard == VecIdecVCard::CRDIDECFIL) return xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACFIL, jref);

	return 0;
};

uint SessIdec::getIxUac(
			DbsIdec* dbsidec
			, const uint ixIdecVCard
			, const bool adm
			, ListIdecRMUserMUsergroup& urus
			, const ubigint refIdecMUser
		) {
	uint retval = 0;

	IdecRMUserMUsergroup* uru = NULL;
	IdecAMUsergroupAccess* usgAacc = NULL;
	IdecAMUserAccess* usrAacc = NULL;

	if (adm) {
		retval = VecIdecWUiaccess::EDIT + VecIdecWUiaccess::EXEC + VecIdecWUiaccess::VIEW;

	} else {
		for (unsigned int i=0;i<urus.nodes.size();i++) {
			uru = urus.nodes[i];

			if (dbsidec->tblidecamusergroupaccess->loadRecBySQL("SELECT * FROM TblIdecAMUsergroupAccess WHERE refIdecMUsergroup = " + to_string(uru->refIdecMUsergroup) + " AND x1IxIdecVCard = " + to_string(ixIdecVCard), &usgAacc)) {
				retval |= usgAacc->ixIdecWUiaccess;
				delete usgAacc;
			};
		};

		if (dbsidec->tblidecamuseraccess->loadRecBySQL("SELECT * FROM TblIdecAMUserAccess WHERE refIdecMUser = " + to_string(refIdecMUser) + " AND x1IxIdecVCard = " + to_string(ixIdecVCard), &usrAacc)) {
			retval = usrAacc->ixIdecWUiaccess;
			delete usrAacc;
		};
	};

	return retval;
};

uint SessIdec::checkAccess(
			DbsIdec* dbsidec
			, const uint ixIdecVCard
			, const ubigint ref
		) {
	uint retval = VecIdecVAccess::NONE;

	ubigint grp;
	ubigint own;

	map<ubigint,uint>::iterator it;

	ubigint refIdecMUser;
	uint ixIdecVMaintable;

	IdecAccRMUserUniversal* ausrRunv = NULL;
	IdecRMUsergroupUniversal* usgRunv = NULL;

	ixIdecVMaintable = crdToMtb(ixIdecVCard);

	if (ixIdecVMaintable == VecIdecVMaintable::VOID) {
		retval = VecIdecVAccess::FULL;

	} else if (hasGrpown(ixIdecVMaintable)) {
		// find record's group and owner
		dbsidec->loadRefBySQL("SELECT grp FROM " + VecIdecVMaintable::getSref(ixIdecVMaintable) + " WHERE ref = " + to_string(ref), grp);
		dbsidec->loadRefBySQL("SELECT own FROM " + VecIdecVMaintable::getSref(ixIdecVMaintable) + " WHERE ref = " + to_string(ref), own);

		// administrators can edit any record
		if (xchg->getBoolvalPreset(VecIdecVPreset::PREIDECADM, jref)) retval = VecIdecVAccess::FULL;

		// all non-administrators can view user group non-specific records but not edit them
		if (retval == VecIdecVAccess::NONE) {
			if (grp == 0) retval = VecIdecVAccess::VIEW;
		};

		if (retval == VecIdecVAccess::NONE) {
			refIdecMUser = xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref);

			// a record's owner has full rights on his records
			if (refIdecMUser == own) retval = VecIdecVAccess::FULL;

			if (retval == VecIdecVAccess::NONE) {
				it = usgaccs.find(grp);
				if (it != usgaccs.end()) {
					if (it->second == VecIdecVUserlevel::GADM) {
						// group admins have full access to all of the group's records
						retval = VecIdecVAccess::FULL;
					} else {
						// other group members have view access only
						retval = VecIdecVAccess::VIEW;
					};
				};
			};

			if (retval != VecIdecVAccess::FULL) {
				// individual record access right
				if (dbsidec->tblidecaccrmuseruniversal->loadRecByUsrMtbUnv(refIdecMUser, ixIdecVMaintable, ref, &ausrRunv)) {
					retval = ausrRunv->ixIdecVAccess;
					delete ausrRunv;
				};
			};

			if (retval != VecIdecVAccess::FULL) {
				// individual record access right due to group membership
				for (it = usgaccs.begin() ; it != usgaccs.end() ; it++) {

					if (dbsidec->tblidecrmusergroupuniversal->loadRecByUsgMtbUnv(it->second, ixIdecVMaintable, ref, &usgRunv)) {
						if (retval == VecIdecVAccess::VIEW) {
							if (usgRunv->ixIdecVAccess == VecIdecVAccess::FULL) retval = VecIdecVAccess::FULL;
						} else {
							retval = usgRunv->ixIdecVAccess;
						};

						delete usgRunv;
					};

					if (retval == VecIdecVAccess::FULL) break;
				};
			};
		};

	} else {
		if (xchg->getBoolvalPreset(VecIdecVPreset::PREIDECADM, jref)) retval = VecIdecVAccess::FULL;
		else retval = VecIdecVAccess::VIEW;
	};

	return retval;
};

void SessIdec::logAccess(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint preUref
			, const uint ixIdecVCard
			, const ubigint unvUref
		) {
	ubigint refIdecMUser;
	uint unvIxIdecVMaintable;
	uint preIxIdecVMaintable;

	IdecHistRMUserUniversal* husrRunv = NULL;

	refIdecMUser = xchg->getRefPreset(VecIdecVPreset::PREIDECOWN, jref);
	unvIxIdecVMaintable = crdToMtb(ixIdecVCard);
	preIxIdecVMaintable = preToMtb(ixIdecVPreset);

	if (!dbsidec->tblidechistrmuseruniversal->loadRecBySQL("SELECT * FROM TblIdecHistRMUserUniversal WHERE refIdecMUser = " + to_string(refIdecMUser)
				+ " AND unvIxIdecVMaintable = " + to_string(unvIxIdecVMaintable) + " AND unvUref = " + to_string(unvUref) + " AND ixIdecVCard = " + to_string(ixIdecVCard), &husrRunv)) {
		husrRunv = new IdecHistRMUserUniversal(0, refIdecMUser, unvIxIdecVMaintable, unvUref, ixIdecVCard, ixIdecVPreset, preIxIdecVMaintable, preUref, 0);
	};

	husrRunv->start = time(NULL);

	if (husrRunv->ref == 0) dbsidec->tblidechistrmuseruniversal->insertRec(husrRunv);
	else dbsidec->tblidechistrmuseruniversal->updateRec(husrRunv);

	xchg->triggerIxRefCall(dbsidec, VecIdecVCall::CALLIDECHUSRRUNVMOD_CRDUSREQ, jref, ixIdecVCard, refIdecMUser);

	delete husrRunv;
};

uint SessIdec::crdToMtb(
			const uint ixIdecVCard
		) {
	if (ixIdecVCard == VecIdecVCard::CRDIDECUSG) return VecIdecVMaintable::TBLIDECMUSERGROUP;
	else if (ixIdecVCard == VecIdecVCard::CRDIDECUSR) return VecIdecVMaintable::TBLIDECMUSER;
	else if (ixIdecVCard == VecIdecVCard::CRDIDECMIS) return VecIdecVMaintable::TBLIDECMMISSION;
	else if (ixIdecVCard == VecIdecVCard::CRDIDECTOU) return VecIdecVMaintable::TBLIDECMTOUR;
	else if (ixIdecVCard == VecIdecVCard::CRDIDECFIL) return VecIdecVMaintable::TBLIDECMFILE;

	return VecIdecVMaintable::VOID;
};

uint SessIdec::preToMtb(
			const uint ixIdecVPreset
		) {
	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFFIL) return VecIdecVMaintable::TBLIDECMFILE;
	else if (ixIdecVPreset == VecIdecVPreset::PREIDECREFMIS) return VecIdecVMaintable::TBLIDECMMISSION;
	else if (ixIdecVPreset == VecIdecVPreset::PREIDECREFPRS) return VecIdecVMaintable::TBLIDECMPERSON;
	else if (ixIdecVPreset == VecIdecVPreset::PREIDECREFSES) return VecIdecVMaintable::TBLIDECMSESSION;
	else if (ixIdecVPreset == VecIdecVPreset::PREIDECREFTOU) return VecIdecVMaintable::TBLIDECMTOUR;
	else if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSG) return VecIdecVMaintable::TBLIDECMUSERGROUP;
	else if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSR) return VecIdecVMaintable::TBLIDECMUSER;

	return VecIdecVMaintable::VOID;
};

bool SessIdec::hasActive(
			const uint ixIdecVCard
		) {
	return((ixIdecVCard == VecIdecVCard::CRDIDECTOU) || (ixIdecVCard == VecIdecVCard::CRDIDECIAQ) || (ixIdecVCard == VecIdecVCard::CRDIDECAD1) || (ixIdecVCard == VecIdecVCard::CRDIDECFIL));
};

bool SessIdec::hasGrpown(
			const uint ixIdecVMaintable
		) {
	return((ixIdecVMaintable == VecIdecVMaintable::TBLIDECMFILE) || (ixIdecVMaintable == VecIdecVMaintable::TBLIDECMMISSION) || (ixIdecVMaintable == VecIdecVMaintable::TBLIDECMPERSON) || (ixIdecVMaintable == VecIdecVMaintable::TBLIDECMUSER) || (ixIdecVMaintable == VecIdecVMaintable::TBLIDECMUSERGROUP));
};

void SessIdec::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {
			cout << "\tcreateCrdad1" << endl;
			cout << "\tcreateCrdfil" << endl;
			cout << "\tcreateCrdiaq" << endl;
			cout << "\tcreateCrdmis" << endl;
			cout << "\tcreateCrdscf" << endl;
			cout << "\tcreateCrdtou" << endl;
			cout << "\tcreateCrdusg" << endl;
			cout << "\tcreateCrdusr" << endl;
			cout << "\tcreateCrdutl" << endl;
			cout << "\teraseCrdad1" << endl;
			cout << "\teraseCrdfil" << endl;
			cout << "\teraseCrdiaq" << endl;
			cout << "\teraseCrdmis" << endl;
			cout << "\teraseCrdscf" << endl;
			cout << "\teraseCrdtou" << endl;
			cout << "\teraseCrdusg" << endl;
			cout << "\teraseCrdusr" << endl;
			cout << "\teraseCrdutl" << endl;
		} else if (req->cmd == "createCrdad1") {
			req->retain = handleCreateCrdad1(dbsidec);

		} else if (req->cmd == "createCrdfil") {
			req->retain = handleCreateCrdfil(dbsidec);

		} else if (req->cmd == "createCrdiaq") {
			req->retain = handleCreateCrdiaq(dbsidec);

		} else if (req->cmd == "createCrdmis") {
			req->retain = handleCreateCrdmis(dbsidec);

		} else if (req->cmd == "createCrdscf") {
			req->retain = handleCreateCrdscf(dbsidec);

		} else if (req->cmd == "createCrdtou") {
			req->retain = handleCreateCrdtou(dbsidec);

		} else if (req->cmd == "createCrdusg") {
			req->retain = handleCreateCrdusg(dbsidec);

		} else if (req->cmd == "createCrdusr") {
			req->retain = handleCreateCrdusr(dbsidec);

		} else if (req->cmd == "createCrdutl") {
			req->retain = handleCreateCrdutl(dbsidec);

		} else if (req->cmd == "eraseCrdad1") {
			req->retain = handleEraseCrdad1(dbsidec);

		} else if (req->cmd == "eraseCrdfil") {
			req->retain = handleEraseCrdfil(dbsidec);

		} else if (req->cmd == "eraseCrdiaq") {
			req->retain = handleEraseCrdiaq(dbsidec);

		} else if (req->cmd == "eraseCrdmis") {
			req->retain = handleEraseCrdmis(dbsidec);

		} else if (req->cmd == "eraseCrdscf") {
			req->retain = handleEraseCrdscf(dbsidec);

		} else if (req->cmd == "eraseCrdtou") {
			req->retain = handleEraseCrdtou(dbsidec);

		} else if (req->cmd == "eraseCrdusg") {
			req->retain = handleEraseCrdusg(dbsidec);

		} else if (req->cmd == "eraseCrdusr") {
			req->retain = handleEraseCrdusr(dbsidec);

		} else if (req->cmd == "eraseCrdutl") {
			req->retain = handleEraseCrdutl(dbsidec);

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
		if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECINIT) {
			handleDpchAppIdecInit(dbsidec, (DpchAppIdecInit*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

bool SessIdec::handleCreateCrdad1(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecAd1* crdad1 = NULL;

	uint ixIdecVPreset = evalCrdad1Active();

	if (ixIdecVPreset == 0) {
		cout << "\tcard is not activated!" << endl;
	} else {
		crdad1 = new CrdIdecAd1(xchg, dbsidec, jref, ixIdecVLocale, ixIdecVPreset, xchg->getRefPreset(ixIdecVPreset, jref));
		crdad1s.push_back(crdad1);
		cout << "\tjob reference: " << crdad1->jref << endl;
		xchg->jrefCmd = crdad1->jref;
	};

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdfil(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecFil* crdfil = NULL;

	uint ixIdecVPreset = evalCrdfilActive();

	if (ixIdecVPreset == 0) {
		cout << "\tcard is not activated!" << endl;
	} else {
		crdfil = new CrdIdecFil(xchg, dbsidec, jref, ixIdecVLocale, 0, ixIdecVPreset, xchg->getRefPreset(ixIdecVPreset, jref));
		crdfils.push_back(crdfil);
		cout << "\tjob reference: " << crdfil->jref << endl;
		xchg->jrefCmd = crdfil->jref;
	};

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdiaq(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecIaq* crdiaq = NULL;

	uint ixIdecVPreset = evalCrdiaqActive();

	if (ixIdecVPreset == 0) {
		cout << "\tcard is not activated!" << endl;
	} else {
		crdiaq = new CrdIdecIaq(xchg, dbsidec, jref, ixIdecVLocale, ixIdecVPreset, xchg->getRefPreset(ixIdecVPreset, jref));
		crdiaqs.push_back(crdiaq);
		cout << "\tjob reference: " << crdiaq->jref << endl;
		xchg->jrefCmd = crdiaq->jref;
	};

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdmis(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecMis* crdmis = NULL;

	crdmis = new CrdIdecMis(xchg, dbsidec, jref, ixIdecVLocale, 0);
	crdmiss.push_back(crdmis);
	cout << "\tjob reference: " << crdmis->jref << endl;
	xchg->jrefCmd = crdmis->jref;

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdscf(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecScf* crdscf = NULL;

	crdscf = new CrdIdecScf(xchg, dbsidec, jref, ixIdecVLocale);
	crdscfs.push_back(crdscf);
	cout << "\tjob reference: " << crdscf->jref << endl;
	xchg->jrefCmd = crdscf->jref;

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdtou(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecTou* crdtou = NULL;

	uint ixIdecVPreset = evalCrdtouActive();

	if (ixIdecVPreset == 0) {
		cout << "\tcard is not activated!" << endl;
	} else {
		crdtou = new CrdIdecTou(xchg, dbsidec, jref, ixIdecVLocale, 0, ixIdecVPreset, xchg->getRefPreset(ixIdecVPreset, jref));
		crdtous.push_back(crdtou);
		cout << "\tjob reference: " << crdtou->jref << endl;
		xchg->jrefCmd = crdtou->jref;
	};

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdusg(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecUsg* crdusg = NULL;

	crdusg = new CrdIdecUsg(xchg, dbsidec, jref, ixIdecVLocale, 0);
	crdusgs.push_back(crdusg);
	cout << "\tjob reference: " << crdusg->jref << endl;
	xchg->jrefCmd = crdusg->jref;

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdusr(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecUsr* crdusr = NULL;

	crdusr = new CrdIdecUsr(xchg, dbsidec, jref, ixIdecVLocale, 0);
	crdusrs.push_back(crdusr);
	cout << "\tjob reference: " << crdusr->jref << endl;
	xchg->jrefCmd = crdusr->jref;

	return false;
	return retval;
};

bool SessIdec::handleCreateCrdutl(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	CrdIdecUtl* crdutl = NULL;

	crdutl = new CrdIdecUtl(xchg, dbsidec, jref, ixIdecVLocale);
	crdutls.push_back(crdutl);
	cout << "\tjob reference: " << crdutl->jref << endl;
	xchg->jrefCmd = crdutl->jref;

	return false;
	return retval;
};

bool SessIdec::handleEraseCrdad1(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecAd1* crdad1 = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdad1s.begin();it!=crdad1s.end();) {
		crdad1 = *it;
		if (crdad1->jref == iinput) {
			it = crdad1s.erase(it);
			delete crdad1;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdfil(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecFil* crdfil = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdfils.begin();it!=crdfils.end();) {
		crdfil = *it;
		if (crdfil->jref == iinput) {
			it = crdfils.erase(it);
			delete crdfil;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdiaq(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecIaq* crdiaq = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdiaqs.begin();it!=crdiaqs.end();) {
		crdiaq = *it;
		if (crdiaq->jref == iinput) {
			it = crdiaqs.erase(it);
			delete crdiaq;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdmis(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecMis* crdmis = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdmiss.begin();it!=crdmiss.end();) {
		crdmis = *it;
		if (crdmis->jref == iinput) {
			it = crdmiss.erase(it);
			delete crdmis;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdscf(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecScf* crdscf = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdscfs.begin();it!=crdscfs.end();) {
		crdscf = *it;
		if (crdscf->jref == iinput) {
			it = crdscfs.erase(it);
			delete crdscf;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdtou(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecTou* crdtou = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdtous.begin();it!=crdtous.end();) {
		crdtou = *it;
		if (crdtou->jref == iinput) {
			it = crdtous.erase(it);
			delete crdtou;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdusg(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecUsg* crdusg = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdusgs.begin();it!=crdusgs.end();) {
		crdusg = *it;
		if (crdusg->jref == iinput) {
			it = crdusgs.erase(it);
			delete crdusg;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdusr(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecUsr* crdusr = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdusrs.begin();it!=crdusrs.end();) {
		crdusr = *it;
		if (crdusr->jref == iinput) {
			it = crdusrs.erase(it);
			delete crdusr;
			break;
		} else it++;
	};

	return retval;
};

bool SessIdec::handleEraseCrdutl(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;
	uint iinput;

	CrdIdecUtl* crdutl = NULL;

	cout << "\tjob reference: ";
	cin >> input;
	iinput = atoi(input.c_str());

	for (auto it=crdutls.begin();it!=crdutls.end();) {
		crdutl = *it;
		if (crdutl->jref == iinput) {
			it = crdutls.erase(it);
			delete crdutl;
			break;
		} else it++;
	};

	return retval;
};

void SessIdec::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = new DpchEngData(jref, &statshr, {DpchEngData::ALL});
};

void SessIdec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECACCESS) {
		call->abort = handleCallIdecAccess(dbsidec, call->jref, call->argInv.ix, call->argInv.ref, call->argRet.ix);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECCRDACTIVE) {
		call->abort = handleCallIdecCrdActive(dbsidec, call->jref, call->argInv.ix, call->argRet.ix);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECCRDCLOSE) {
		call->abort = handleCallIdecCrdClose(dbsidec, call->jref, call->argInv.ix);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECCRDOPEN) {
		call->abort = handleCallIdecCrdOpen(dbsidec, call->jref, call->argInv.ix, call->argInv.ref, call->argInv.sref, call->argInv.intval, call->argRet.ref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECDESCR) {
		call->abort = handleCallIdecDescr(dbsidec, call->jref, call->argInv.sref, call->argRet.ref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECLOG) {
		call->abort = handleCallIdecLog(dbsidec, call->jref, call->argInv.ix, call->argInv.ref, call->argInv.sref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSCR) {
		call->abort = handleCallIdecScr(dbsidec, call->jref, call->argInv.ref, call->argRet.sref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECREFPRESET) {
		call->abort = handleCallIdecRefPreSet(dbsidec, call->jref, call->argInv.ix, call->argInv.ref);
	};
};

bool SessIdec::handleCallIdecAccess(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
			, uint& ixRet
		) {
	bool retval = false;
	ixRet = checkAccess(dbsidec, ixInv, refInv);
	return retval;
};

bool SessIdec::handleCallIdecCrdActive(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, uint& ixRet
		) {
	bool retval = false;
	ixRet = checkCrdActive(ixInv);
	return retval;
};

bool SessIdec::handleCallIdecCrdClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
		) {
	bool retval = false;
	ubigint jrefNotif = xchg->getRefPreset(VecIdecVPreset::PREIDECJREFNOTIFY, jref);
	if (jrefNotif == jrefTrig) xchg->removePreset(VecIdecVPreset::PREIDECJREFNOTIFY, jref);

	if (ixInv == VecIdecVCard::CRDIDECNAV) {
		IdecMSession* ses = NULL;

		time_t rawtime;

		if (crdnav) {
			delete crdnav;
			crdnav = NULL;
		};

		// update session with stop time
		time(&rawtime);

		dbsidec->tblidecmsession->loadRecByRef(xchg->getRefPreset(VecIdecVPreset::PREIDECSESS, jref), &ses);
		ses->stop = rawtime;
		dbsidec->tblidecmsession->updateRec(ses);

		delete ses;

		// notify root
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECLOGOUT, jref);
	} else if (ixInv == VecIdecVCard::CRDIDECUSG) {
		CrdIdecUsg* crdusg = NULL;

		for (auto it=crdusgs.begin();it!=crdusgs.end();) {
			crdusg = *it;
			if (crdusg->jref == jrefTrig) {
				it = crdusgs.erase(it);
				delete crdusg;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECUSR) {
		CrdIdecUsr* crdusr = NULL;

		for (auto it=crdusrs.begin();it!=crdusrs.end();) {
			crdusr = *it;
			if (crdusr->jref == jrefTrig) {
				it = crdusrs.erase(it);
				delete crdusr;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECSCF) {
		CrdIdecScf* crdscf = NULL;

		for (auto it=crdscfs.begin();it!=crdscfs.end();) {
			crdscf = *it;
			if (crdscf->jref == jrefTrig) {
				it = crdscfs.erase(it);
				delete crdscf;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECUTL) {
		CrdIdecUtl* crdutl = NULL;

		for (auto it=crdutls.begin();it!=crdutls.end();) {
			crdutl = *it;
			if (crdutl->jref == jrefTrig) {
				it = crdutls.erase(it);
				delete crdutl;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECMIS) {
		CrdIdecMis* crdmis = NULL;

		for (auto it=crdmiss.begin();it!=crdmiss.end();) {
			crdmis = *it;
			if (crdmis->jref == jrefTrig) {
				it = crdmiss.erase(it);
				delete crdmis;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECTOU) {
		CrdIdecTou* crdtou = NULL;

		for (auto it=crdtous.begin();it!=crdtous.end();) {
			crdtou = *it;
			if (crdtou->jref == jrefTrig) {
				it = crdtous.erase(it);
				delete crdtou;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECIAQ) {
		CrdIdecIaq* crdiaq = NULL;

		for (auto it=crdiaqs.begin();it!=crdiaqs.end();) {
			crdiaq = *it;
			if (crdiaq->jref == jrefTrig) {
				it = crdiaqs.erase(it);
				delete crdiaq;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECAD1) {
		CrdIdecAd1* crdad1 = NULL;

		for (auto it=crdad1s.begin();it!=crdad1s.end();) {
			crdad1 = *it;
			if (crdad1->jref == jrefTrig) {
				it = crdad1s.erase(it);
				delete crdad1;
				break;
			} else it++;
		};
	} else if (ixInv == VecIdecVCard::CRDIDECFIL) {
		CrdIdecFil* crdfil = NULL;

		for (auto it=crdfils.begin();it!=crdfils.end();) {
			crdfil = *it;
			if (crdfil->jref == jrefTrig) {
				it = crdfils.erase(it);
				delete crdfil;
				break;
			} else it++;
		};
	};
	return retval;
};

bool SessIdec::handleCallIdecCrdOpen(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
			, const string& srefInv
			, const int intvalInv
			, ubigint& refRet
		) {
	bool retval = false;
	bool denied = false;

	uint ixIdecVCard = VecIdecVCard::getIx(srefInv);

	ubigint ref = (ubigint) intvalInv;
	if (intvalInv == -1) {
		ref = 0;
		ref--;
	};

	uint ixIdecVPreset;
	ubigint preUref = 0;

	uint ixIdecWUiaccess;
	uint ixIdecVAccess;

	if (hasActive(ixIdecVCard)) {
		if (ixInv == 0) {
			ixIdecVPreset = checkCrdActive(ixIdecVCard);
			if (ixIdecVPreset == 0) {
				denied = true;
			} else {
				preUref = xchg->getRefPreset(ixIdecVPreset, jref);
			};

		} else {
			ixIdecVPreset = ixInv;
			preUref = refInv;
		};
	};

	if (!denied) {
		ixIdecWUiaccess = checkUiaccess(ixIdecVCard);
		denied = (ixIdecWUiaccess == 0);
	};

	if (!denied) {
		if (intvalInv == -1) {
			denied = (((ixIdecWUiaccess & VecIdecWUiaccess::EDIT) == 0) || ((ixIdecWUiaccess & VecIdecWUiaccess::EXEC) == 0));
		} else if (intvalInv > 0) {
			ixIdecVAccess = checkAccess(dbsidec, ixIdecVCard, intvalInv);
			denied = (ixIdecVAccess == VecIdecVAccess::NONE);
		};
	};

	if (denied) {
		refRet = 0;

	} else {
		if (ixIdecVCard == VecIdecVCard::CRDIDECNAV) {
		} else if (ixIdecVCard == VecIdecVCard::CRDIDECUSG) {
			CrdIdecUsg* crdusg = NULL;

			crdusg = new CrdIdecUsg(xchg, dbsidec, jref, ixIdecVLocale, ref);
			crdusgs.push_back(crdusg);

			refRet = crdusg->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECUSR) {
			CrdIdecUsr* crdusr = NULL;

			crdusr = new CrdIdecUsr(xchg, dbsidec, jref, ixIdecVLocale, ref);
			crdusrs.push_back(crdusr);

			refRet = crdusr->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECSCF) {
			CrdIdecScf* crdscf = NULL;

			crdscf = new CrdIdecScf(xchg, dbsidec, jref, ixIdecVLocale);
			crdscfs.push_back(crdscf);

			refRet = crdscf->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECUTL) {
			CrdIdecUtl* crdutl = NULL;

			crdutl = new CrdIdecUtl(xchg, dbsidec, jref, ixIdecVLocale);
			crdutls.push_back(crdutl);

			refRet = crdutl->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECMIS) {
			CrdIdecMis* crdmis = NULL;

			crdmis = new CrdIdecMis(xchg, dbsidec, jref, ixIdecVLocale, ref);
			crdmiss.push_back(crdmis);

			refRet = crdmis->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECTOU) {
			CrdIdecTou* crdtou = NULL;

			crdtou = new CrdIdecTou(xchg, dbsidec, jref, ixIdecVLocale, ref, ixIdecVPreset, preUref);
			crdtous.push_back(crdtou);

			refRet = crdtou->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECIAQ) {
			CrdIdecIaq* crdiaq = NULL;

			crdiaq = new CrdIdecIaq(xchg, dbsidec, jref, ixIdecVLocale, ixIdecVPreset, preUref);
			crdiaqs.push_back(crdiaq);

			refRet = crdiaq->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECAD1) {
			CrdIdecAd1* crdad1 = NULL;

			crdad1 = new CrdIdecAd1(xchg, dbsidec, jref, ixIdecVLocale, ixIdecVPreset, preUref);
			crdad1s.push_back(crdad1);

			refRet = crdad1->jref;

		} else if (ixIdecVCard == VecIdecVCard::CRDIDECFIL) {
			CrdIdecFil* crdfil = NULL;

			crdfil = new CrdIdecFil(xchg, dbsidec, jref, ixIdecVLocale, ref, ixIdecVPreset, preUref);
			crdfils.push_back(crdfil);

			refRet = crdfil->jref;

		};
	};

	return retval;
};

bool SessIdec::handleCallIdecDescr(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const string& srefInv
			, ubigint& refRet
		) {
	bool retval = false;
	refRet = Scr::descramble(&mAccess, descr, srefInv);
	return retval;
};

bool SessIdec::handleCallIdecLog(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
			, const string& srefInv
			, const int intvalInv
		) {
	bool retval = false;
	logAccess(dbsidec, ixInv, refInv, VecIdecVCard::getIx(srefInv), intvalInv);
	return retval;
};

bool SessIdec::handleCallIdecScr(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
			, string& srefRet
		) {
	bool retval = false;
	srefRet = Scr::scramble(&mAccess, scr, descr, refInv);
	return retval;
};

bool SessIdec::handleCallIdecRefPreSet(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
		) {
	bool retval = false;
	if (ixInv == VecIdecVPreset::PREIDECJREFNOTIFY) {
		ubigint jrefNotify_old = xchg->getRefPreset(VecIdecVPreset::PREIDECJREFNOTIFY, jref);

		if (refInv != jrefNotify_old) {
			if (jrefNotify_old != 0) xchg->submitDpch(new DpchEngIdecSuspend(jrefNotify_old));

			if (refInv == 0) xchg->removePreset(ixInv, jref);
			else xchg->addRefPreset(ixInv, jref, refInv);
		};

	} else if ((ixInv == VecIdecVPreset::PREIDECREFMIS) || (ixInv == VecIdecVPreset::PREIDECREFTOU)) {
		if (refInv == 0) xchg->removePreset(ixInv, jref);
		else xchg->addRefPreset(ixInv, jref, refInv);

		if (crdnav) crdnav->updatePreset(dbsidec, ixInv, jrefTrig, true);
	};
	return retval;
};

