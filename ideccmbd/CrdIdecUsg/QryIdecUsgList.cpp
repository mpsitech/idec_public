/**
  * \file QryIdecUsgList.cpp
  * job handler for job QryIdecUsgList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecUsgList.h"

#include "QryIdecUsgList_blks.cpp"

/******************************************************************************
 class QryIdecUsgList
 ******************************************************************************/

QryIdecUsgList::QryIdecUsgList(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECUSGLIST, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	xchg->addStmgr(jref, Stub::VecVNonetype::SHORT);
	ixIdecVQrystate = VecIdecVQrystate::OOD;

	// IP constructor.cust2 --- INSERT

	rerun(dbsidec);

	xchg->addClstn(VecIdecVCall::CALLIDECSTUBCHG, jref, Clstn::VecVJobmask::SPEC, jref, Arg(), Clstn::VecVJactype::LOCK);

	xchg->addClstn(VecIdecVCall::CALLIDECUSGMOD, jref, Clstn::VecVJobmask::ALL, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

QryIdecUsgList::~QryIdecUsgList() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecUsgList::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);

	xchg->removeClstns(VecIdecVCall::CALLIDECUSGUPD_REFEQ, jref);
	if (preRefSel != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECUSGUPD_REFEQ, jref, Clstn::VecVJobmask::ALL, 0, preRefSel, Clstn::VecVJactype::LOCK);
};

void QryIdecUsgList::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	uint cnt;

	string preSrf = xchg->getSrefPreset(VecIdecVPreset::PREIDECUSGLIST_SRF, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqusglist->removeRstByJref(jref);

	sqlstr = "SELECT COUNT(TblIdecMUsergroup.ref)";
	sqlstr += " FROM TblIdecMUsergroup";
	rerun_filtSQL(sqlstr, preSrf, true);
	dbsidec->loadUintBySQL(sqlstr, cnt);

	statshr.ntot = cnt;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cnt) {
		if (cnt >= stgiac.nload) stgiac.jnumFirstload = cnt-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	sqlstr = "INSERT INTO TblIdecQUsgList(jref, jnum, ref, sref)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMUsergroup.ref, TblIdecMUsergroup.sref";
	sqlstr += " FROM TblIdecMUsergroup";
	rerun_filtSQL(sqlstr, preSrf, true);
	sqlstr += " ORDER BY TblIdecMUsergroup.sref ASC";
	sqlstr += " LIMIT " + to_string(stgiac.nload) + " OFFSET " + to_string(stgiac.jnumFirstload-1);
	dbsidec->executeQuery(sqlstr);

	sqlstr = "UPDATE TblIdecQUsgList SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

};

void QryIdecUsgList::rerun_filtSQL(
			string& sqlstr
			, const string& preSrf
			, const bool addwhere
		) {
	bool first = addwhere;

	if (preSrf.length() > 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMUsergroup.sref = '" + preSrf + "'";
	};
};

void QryIdecUsgList::rerun_filtSQL_append(
			string& sqlstr
			, bool& first
		) {
	if (first) {
		sqlstr += " WHERE ";
		first = false;
	} else sqlstr += " AND ";
};

void QryIdecUsgList::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQUsgList* rec = NULL;

	dbsidec->tblidecqusglist->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecUsgList", "fetch");
	};

	refreshJnum();
};

uint QryIdecUsgList::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQUsgList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecUsgList::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQUsgList* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQUsgList* QryIdecUsgList::getRecByJnum(
			const uint jnum
		) {
	IdecQUsgList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecUsgList::handleRequest(
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

bool QryIdecUsgList::handleRerun(
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

bool QryIdecUsgList::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQUsgList* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\tsref";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->sref;
		cout << endl;
	};
	return retval;
};

void QryIdecUsgList::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSGMOD) {
		call->abort = handleCallIdecUsgMod(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSGUPD_REFEQ) {
		call->abort = handleCallIdecUsgUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecUsgList::handleCallIdecStubChg(
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

bool QryIdecUsgList::handleCallIdecUsgMod(
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

bool QryIdecUsgList::handleCallIdecUsgUpd_refEq(
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

