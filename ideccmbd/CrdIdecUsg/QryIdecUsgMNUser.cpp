/**
  * \file QryIdecUsgMNUser.cpp
  * job handler for job QryIdecUsgMNUser (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecUsgMNUser.h"

#include "QryIdecUsgMNUser_blks.cpp"

/******************************************************************************
 class QryIdecUsgMNUser
 ******************************************************************************/

QryIdecUsgMNUser::QryIdecUsgMNUser(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECUSGMNUSER, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	xchg->addStmgr(jref, Stub::VecVNonetype::SHORT);
	ixIdecVQrystate = VecIdecVQrystate::OOD;

	// IP constructor.cust2 --- INSERT

	rerun(dbsidec);

	xchg->addClstn(VecIdecVCall::CALLIDECSTUBCHG, jref, Clstn::VecVJobmask::SPEC, jref, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

QryIdecUsgMNUser::~QryIdecUsgMNUser() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecUsgMNUser::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);
};

void QryIdecUsgMNUser::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	uint cnt;

	ubigint preRefUsg = xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSG, jref);

	xchg->removeClstns(VecIdecVCall::CALLIDECUSRRUSGMOD_USGEQ, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqusgmnuser->removeRstByJref(jref);

	sqlstr = "SELECT COUNT(TblIdecRMUserMUsergroup.ref)";
	sqlstr += " FROM TblIdecRMUserMUsergroup, TblIdecMUser";
	sqlstr += " WHERE TblIdecRMUserMUsergroup.refIdecMUser = TblIdecMUser.ref";
	sqlstr += " AND TblIdecRMUserMUsergroup.refIdecMUsergroup = " + to_string(preRefUsg) + "";
	dbsidec->loadUintBySQL(sqlstr, cnt);

	statshr.ntot = cnt;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cnt) {
		if (cnt >= stgiac.nload) stgiac.jnumFirstload = cnt-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	sqlstr = "INSERT INTO TblIdecQUsgMNUser(jref, jnum, mref, ref, ixIdecVUserlevel)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMUser.ref, TblIdecRMUserMUsergroup.ref, TblIdecRMUserMUsergroup.ixIdecVUserlevel";
	sqlstr += " FROM TblIdecRMUserMUsergroup, TblIdecMUser";
	sqlstr += " WHERE TblIdecRMUserMUsergroup.refIdecMUser = TblIdecMUser.ref";
	sqlstr += " AND TblIdecRMUserMUsergroup.refIdecMUsergroup = " + to_string(preRefUsg) + "";
	sqlstr += " ORDER BY TblIdecMUser.sref ASC";
	sqlstr += " LIMIT " + to_string(stgiac.nload) + " OFFSET " + to_string(stgiac.jnumFirstload-1);
	dbsidec->executeQuery(sqlstr);

	sqlstr = "UPDATE TblIdecQUsgMNUser SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

	xchg->addRefClstn(VecIdecVCall::CALLIDECUSRRUSGMOD_USGEQ, jref, Clstn::VecVJobmask::ALL, 0, preRefUsg, Clstn::VecVJactype::LOCK);
};

void QryIdecUsgMNUser::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQUsgMNUser* rec = NULL;

	dbsidec->tblidecqusgmnuser->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->stubMref = StubIdec::getStubUsrStd(dbsidec, rec->mref, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			rec->srefIxIdecVUserlevel = VecIdecVUserlevel::getSref(rec->ixIdecVUserlevel);
			rec->titIxIdecVUserlevel = VecIdecVUserlevel::getTitle(rec->ixIdecVUserlevel, ixIdecVLocale);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecUsgMNUser", "fetch");
	};

	refreshJnum();
};

uint QryIdecUsgMNUser::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQUsgMNUser* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecUsgMNUser::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQUsgMNUser* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQUsgMNUser* QryIdecUsgMNUser::getRecByJnum(
			const uint jnum
		) {
	IdecQUsgMNUser* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecUsgMNUser::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {
			cout << "\trerun" << endl;
			cout << "\tshow" << endl;
		} else if (req->cmd == "rerun") {
			req->retain = handleRerun(dbsidec);

		} else if (req->cmd == "show") {
			req->retain = handleShow(dbsidec);

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {
	};
};

bool QryIdecUsgMNUser::handleRerun(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	string input;

	cout << "\tjnumFirstload (" << stgiac.jnumFirstload << "): ";
	cin >> input;
	stgiac.jnumFirstload = atol(input.c_str());
	cout << "\tnload (" << stgiac.nload << "): ";
	cin >> input;
	stgiac.nload = atol(input.c_str());

	rerun(dbsidec);
	return retval;
};

bool QryIdecUsgMNUser::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQUsgMNUser* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tmref";
	cout << "\tstubMref";
	cout << "\tref";
	cout << "\tixIdecVUserlevel";
	cout << "\tsrefIxIdecVUserlevel";
	cout << "\ttitIxIdecVUserlevel";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->mref;
		cout << "\t" << rec->stubMref;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->ixIdecVUserlevel;
		cout << "\t" << rec->srefIxIdecVUserlevel;
		cout << "\t" << rec->titIxIdecVUserlevel;
		cout << endl;
	};
	return retval;
};

void QryIdecUsgMNUser::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRRUSGMOD_USGEQ) {
		call->abort = handleCallIdecUsrRusgMod_usgEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecUsgMNUser::handleCallIdecStubChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;

	if (ixIdecVQrystate == VecIdecVQrystate::UTD) {
		ixIdecVQrystate = VecIdecVQrystate::SLM;
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	};

	return retval;
};

bool QryIdecUsgMNUser::handleCallIdecUsrRusgMod_usgEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;

	if (ixIdecVQrystate != VecIdecVQrystate::OOD) {
		ixIdecVQrystate = VecIdecVQrystate::OOD;
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	};

	return retval;
};

