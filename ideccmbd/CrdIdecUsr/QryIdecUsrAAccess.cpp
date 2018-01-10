/**
  * \file QryIdecUsrAAccess.cpp
  * job handler for job QryIdecUsrAAccess (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecUsrAAccess.h"

#include "QryIdecUsrAAccess_blks.cpp"

/******************************************************************************
 class QryIdecUsrAAccess
 ******************************************************************************/

QryIdecUsrAAccess::QryIdecUsrAAccess(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECUSRAACCESS, jrefSup, ixIdecVLocale) {

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

QryIdecUsrAAccess::~QryIdecUsrAAccess() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecUsrAAccess::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);
};

void QryIdecUsrAAccess::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	uint cnt;

	ubigint preRefUsr = xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref);
	uint preX1 = xchg->getIxPreset(VecIdecVPreset::PREIDECUSRAACCESS_X1, jref);

	xchg->removeClstns(VecIdecVCall::CALLIDECUSRAACCMOD_USREQ, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqusraaccess->removeRstByJref(jref);

	sqlstr = "SELECT COUNT(TblIdecAMUserAccess.ref)";
	sqlstr += " FROM TblIdecAMUserAccess";
	sqlstr += " WHERE TblIdecAMUserAccess.refIdecMUser = " + to_string(preRefUsr) + "";
	rerun_filtSQL(sqlstr, preX1, false);
	dbsidec->loadUintBySQL(sqlstr, cnt);

	statshr.ntot = cnt;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cnt) {
		if (cnt >= stgiac.nload) stgiac.jnumFirstload = cnt-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	sqlstr = "INSERT INTO TblIdecQUsrAAccess(jref, jnum, ref, x1IxIdecVCard, ixIdecWUiaccess)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecAMUserAccess.ref, TblIdecAMUserAccess.x1IxIdecVCard, TblIdecAMUserAccess.ixIdecWUiaccess";
	sqlstr += " FROM TblIdecAMUserAccess";
	sqlstr += " WHERE TblIdecAMUserAccess.refIdecMUser = " + to_string(preRefUsr) + "";
	rerun_filtSQL(sqlstr, preX1, false);
	sqlstr += " LIMIT " + to_string(stgiac.nload) + " OFFSET " + to_string(stgiac.jnumFirstload-1);
	dbsidec->executeQuery(sqlstr);

	sqlstr = "UPDATE TblIdecQUsrAAccess SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

	xchg->addRefClstn(VecIdecVCall::CALLIDECUSRAACCMOD_USREQ, jref, Clstn::VecVJobmask::ALL, 0, preRefUsr, Clstn::VecVJactype::LOCK);
};

void QryIdecUsrAAccess::rerun_filtSQL(
			string& sqlstr
			, const uint preX1
			, const bool addwhere
		) {
	bool first = addwhere;

	if (preX1 != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecAMUserAccess.x1IxIdecVCard = " + to_string(preX1) + "";
	};
};

void QryIdecUsrAAccess::rerun_filtSQL_append(
			string& sqlstr
			, bool& first
		) {
	if (first) {
		sqlstr += " WHERE ";
		first = false;
	} else sqlstr += " AND ";
};

void QryIdecUsrAAccess::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQUsrAAccess* rec = NULL;

	dbsidec->tblidecqusraaccess->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->srefX1IxIdecVCard = VecIdecVCard::getSref(rec->x1IxIdecVCard);
			rec->titX1IxIdecVCard = VecIdecVCard::getTitle(rec->x1IxIdecVCard, ixIdecVLocale);
			rec->srefsIxIdecWUiaccess = VecIdecWUiaccess::getSrefs(rec->ixIdecWUiaccess);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecUsrAAccess", "fetch");
	};

	refreshJnum();
};

uint QryIdecUsrAAccess::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQUsrAAccess* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecUsrAAccess::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQUsrAAccess* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQUsrAAccess* QryIdecUsrAAccess::getRecByJnum(
			const uint jnum
		) {
	IdecQUsrAAccess* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecUsrAAccess::handleRequest(
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

bool QryIdecUsrAAccess::handleRerun(
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

bool QryIdecUsrAAccess::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQUsrAAccess* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\tx1IxIdecVCard";
	cout << "\tsrefX1IxIdecVCard";
	cout << "\ttitX1IxIdecVCard";
	cout << "\tixIdecWUiaccess";
	cout << "\tsrefsIxIdecWUiaccess";
	cout << "\ttitsIxIdecWUiaccess";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->x1IxIdecVCard;
		cout << "\t" << rec->srefX1IxIdecVCard;
		cout << "\t" << rec->titX1IxIdecVCard;
		cout << "\t" << rec->ixIdecWUiaccess;
		cout << "\t" << rec->srefsIxIdecWUiaccess;
		cout << "\t" << rec->titsIxIdecWUiaccess;
		cout << endl;
	};
	return retval;
};

void QryIdecUsrAAccess::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECUSRAACCMOD_USREQ) {
		call->abort = handleCallIdecUsrAaccMod_usrEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecUsrAAccess::handleCallIdecStubChg(
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

bool QryIdecUsrAAccess::handleCallIdecUsrAaccMod_usrEq(
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

