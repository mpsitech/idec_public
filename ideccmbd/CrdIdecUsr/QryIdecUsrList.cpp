/**
  * \file QryIdecUsrList.cpp
  * job handler for job QryIdecUsrList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecUsrList.h"

#include "QryIdecUsrList_blks.cpp"

/******************************************************************************
 class QryIdecUsrList
 ******************************************************************************/

QryIdecUsrList::QryIdecUsrList(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECUSRLIST, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	xchg->addStmgr(jref, Stub::VecVNonetype::SHORT);
	ixIdecVQrystate = VecIdecVQrystate::OOD;

	// IP constructor.cust2 --- INSERT

	rerun(dbsidec);

	xchg->addClstn(VecIdecVCall::CALLIDECSTUBCHG, jref, Clstn::VecVJobmask::SPEC, jref, Arg(), Clstn::VecVJactype::LOCK);

	xchg->addClstn(VecIdecVCall::CALLIDECUSRMOD, jref, Clstn::VecVJobmask::ALL, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

QryIdecUsrList::~QryIdecUsrList() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecUsrList::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);

	xchg->removeClstns(VecIdecVCall::CALLIDECUSRUPD_REFEQ, jref);
	if (preRefSel != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECUSRUPD_REFEQ, jref, Clstn::VecVJobmask::ALL, 0, preRefSel, Clstn::VecVJactype::LOCK);
};

void QryIdecUsrList::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	uint cnt;

	uint preIxOrd = xchg->getIxPreset(VecIdecVPreset::PREIDECIXORD, jref);
	ubigint prePrs = xchg->getRefPreset(VecIdecVPreset::PREIDECUSRLIST_PRS, jref);
	string preSrf = xchg->getSrefPreset(VecIdecVPreset::PREIDECUSRLIST_SRF, jref);
	ubigint preUsg = xchg->getRefPreset(VecIdecVPreset::PREIDECUSRLIST_USG, jref);
	uint preSte = xchg->getIxPreset(VecIdecVPreset::PREIDECUSRLIST_STE, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqusrlist->removeRstByJref(jref);

	sqlstr = "SELECT COUNT(TblIdecMUser.ref)";
	sqlstr += " FROM TblIdecMUser";
	rerun_filtSQL(sqlstr, prePrs, preSrf, preUsg, preSte, true);
	dbsidec->loadUintBySQL(sqlstr, cnt);

	statshr.ntot = cnt;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cnt) {
		if (cnt >= stgiac.nload) stgiac.jnumFirstload = cnt-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	sqlstr = "INSERT INTO TblIdecQUsrList(jref, jnum, ref, refIdecMPerson, sref, refIdecMUsergroup, ixVState, ixIdecVLocale, ixIdecVUserlevel)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMUser.ref, TblIdecMUser.refIdecMPerson, TblIdecMUser.sref, TblIdecMUser.refIdecMUsergroup, TblIdecMUser.ixVState, TblIdecMUser.ixIdecVLocale, TblIdecMUser.ixIdecVUserlevel";
	sqlstr += " FROM TblIdecMUser";
	rerun_filtSQL(sqlstr, prePrs, preSrf, preUsg, preSte, true);
	rerun_orderSQL(sqlstr, preIxOrd);
	sqlstr += " LIMIT " + to_string(stgiac.nload) + " OFFSET " + to_string(stgiac.jnumFirstload-1);
	dbsidec->executeQuery(sqlstr);

	sqlstr = "UPDATE TblIdecQUsrList SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

};

void QryIdecUsrList::rerun_filtSQL(
			string& sqlstr
			, const ubigint prePrs
			, const string& preSrf
			, const ubigint preUsg
			, const uint preSte
			, const bool addwhere
		) {
	bool first = addwhere;

	if (prePrs != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMUser.refIdecMPerson = " + to_string(prePrs) + "";
	};

	if (preSrf.length() > 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMUser.sref = '" + preSrf + "'";
	};

	if (preUsg != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMUser.refIdecMUsergroup = " + to_string(preUsg) + "";
	};

	if (preSte != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMUser.ixVState = " + to_string(preSte) + "";
	};
};

void QryIdecUsrList::rerun_filtSQL_append(
			string& sqlstr
			, bool& first
		) {
	if (first) {
		sqlstr += " WHERE ";
		first = false;
	} else sqlstr += " AND ";
};

void QryIdecUsrList::rerun_orderSQL(
			string& sqlstr
			, const uint preIxOrd
		) {
	if (preIxOrd == VecVOrd::PRS) sqlstr += " ORDER BY TblIdecMUser.refIdecMPerson ASC";
	else if (preIxOrd == VecVOrd::SRF) sqlstr += " ORDER BY TblIdecMUser.sref ASC";
	else if (preIxOrd == VecVOrd::USG) sqlstr += " ORDER BY TblIdecMUser.refIdecMUsergroup ASC";
	else if (preIxOrd == VecVOrd::STE) sqlstr += " ORDER BY TblIdecMUser.ixVState ASC";
};

void QryIdecUsrList::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQUsrList* rec = NULL;

	dbsidec->tblidecqusrlist->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->stubRefIdecMPerson = StubIdec::getStubPrsStd(dbsidec, rec->refIdecMPerson, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			rec->stubRefIdecMUsergroup = StubIdec::getStubUsgStd(dbsidec, rec->refIdecMUsergroup, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			rec->srefIxVState = VecIdecVMUserState::getSref(rec->ixVState);
			rec->titIxVState = VecIdecVMUserState::getTitle(rec->ixVState, ixIdecVLocale);
			rec->srefIxIdecVLocale = VecIdecVLocale::getSref(rec->ixIdecVLocale);
			rec->titIxIdecVLocale = VecIdecVLocale::getTitle(rec->ixIdecVLocale, ixIdecVLocale);
			rec->srefIxIdecVUserlevel = VecIdecVUserlevel::getSref(rec->ixIdecVUserlevel);
			rec->titIxIdecVUserlevel = VecIdecVUserlevel::getTitle(rec->ixIdecVUserlevel, ixIdecVLocale);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecUsrList", "fetch");
	};

	refreshJnum();
};

uint QryIdecUsrList::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQUsrList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecUsrList::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQUsrList* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQUsrList* QryIdecUsrList::getRecByJnum(
			const uint jnum
		) {
	IdecQUsrList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecUsrList::handleRequest(
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

bool QryIdecUsrList::handleRerun(
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

bool QryIdecUsrList::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQUsrList* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\trefIdecMPerson";
	cout << "\tstubRefIdecMPerson";
	cout << "\tsref";
	cout << "\trefIdecMUsergroup";
	cout << "\tstubRefIdecMUsergroup";
	cout << "\tixVState";
	cout << "\tsrefIxVState";
	cout << "\ttitIxVState";
	cout << "\tixIdecVLocale";
	cout << "\tsrefIxIdecVLocale";
	cout << "\ttitIxIdecVLocale";
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
		cout << "\t" << rec->ref;
		cout << "\t" << rec->refIdecMPerson;
		cout << "\t" << rec->stubRefIdecMPerson;
		cout << "\t" << rec->sref;
		cout << "\t" << rec->refIdecMUsergroup;
		cout << "\t" << rec->stubRefIdecMUsergroup;
		cout << "\t" << rec->ixVState;
		cout << "\t" << rec->srefIxVState;
		cout << "\t" << rec->titIxVState;
		cout << "\t" << rec->ixIdecVLocale;
		cout << "\t" << rec->srefIxIdecVLocale;
		cout << "\t" << rec->titIxIdecVLocale;
		cout << "\t" << rec->ixIdecVUserlevel;
		cout << "\t" << rec->srefIxIdecVUserlevel;
		cout << "\t" << rec->titIxIdecVUserlevel;
		cout << endl;
	};
	return retval;
};

void QryIdecUsrList::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRMOD) {
		call->abort = handleCallIdecUsrMod(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRUPD_REFEQ) {
		call->abort = handleCallIdecUsrUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecUsrList::handleCallIdecStubChg(
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

bool QryIdecUsrList::handleCallIdecUsrMod(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;

	if ((ixIdecVQrystate == VecIdecVQrystate::UTD) || (ixIdecVQrystate == VecIdecVQrystate::SLM)) {
		ixIdecVQrystate = VecIdecVQrystate::MNR;
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	};

	return retval;
};

bool QryIdecUsrList::handleCallIdecUsrUpd_refEq(
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

