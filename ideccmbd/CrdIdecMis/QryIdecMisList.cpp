/**
  * \file QryIdecMisList.cpp
  * job handler for job QryIdecMisList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecMisList.h"

#include "QryIdecMisList_blks.cpp"

/******************************************************************************
 class QryIdecMisList
 ******************************************************************************/

QryIdecMisList::QryIdecMisList(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECMISLIST, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	xchg->addStmgr(jref, Stub::VecVNonetype::SHORT);
	ixIdecVQrystate = VecIdecVQrystate::OOD;

	// IP constructor.cust2 --- INSERT

	rerun(dbsidec);

	xchg->addClstn(VecIdecVCall::CALLIDECSTUBCHG, jref, Clstn::VecVJobmask::SPEC, jref, Arg(), Clstn::VecVJactype::LOCK);

	xchg->addClstn(VecIdecVCall::CALLIDECMISMOD, jref, Clstn::VecVJobmask::ALL, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

QryIdecMisList::~QryIdecMisList() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecMisList::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);

	xchg->removeClstns(VecIdecVCall::CALLIDECMISUPD_REFEQ, jref);
	if (preRefSel != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECMISUPD_REFEQ, jref, Clstn::VecVJobmask::ALL, 0, preRefSel, Clstn::VecVJactype::LOCK);
};

void QryIdecMisList::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	uint cnt;

	ubigint preJrefSess = xchg->getRefPreset(VecIdecVPreset::PREIDECJREFSESS, jref);
	uint preIxOrd = xchg->getIxPreset(VecIdecVPreset::PREIDECIXORD, jref);
	string preTit = xchg->getTxtvalPreset(VecIdecVPreset::PREIDECMISLIST_TIT, jref);
	ubigint preGrp = xchg->getRefPreset(VecIdecVPreset::PREIDECMISLIST_GRP, jref);
	ubigint preOwn = xchg->getRefPreset(VecIdecVPreset::PREIDECMISLIST_OWN, jref);
	int preSta = xchg->getIntvalPreset(VecIdecVPreset::PREIDECMISLIST_STA, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqmislist->removeRstByJref(jref);

	sqlstr = "SELECT COUNT(TblIdecMMission.ref)";
	sqlstr += " FROM TblIdecMMission, TblIdecQSelect";
	sqlstr += " WHERE TblIdecQSelect.jref = " + to_string(preJrefSess) + "";
	sqlstr += " AND TblIdecMMission.grp = TblIdecQSelect.ref";
	rerun_filtSQL(sqlstr, preTit, preGrp, preOwn, preSta, false);
	dbsidec->loadUintBySQL(sqlstr, cnt);

	statshr.ntot = cnt;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cnt) {
		if (cnt >= stgiac.nload) stgiac.jnumFirstload = cnt-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	sqlstr = "INSERT INTO TblIdecQMisList(jref, jnum, ref, Title, grp, own, startd, stopd, srefKCountry, Region, Municipality)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMMission.ref, TblIdecMMission.Title, TblIdecMMission.grp, TblIdecMMission.own, TblIdecMMission.startd, TblIdecMMission.stopd, TblIdecMMission.srefKCountry, TblIdecMMission.Region, TblIdecMMission.Municipality";
	sqlstr += " FROM TblIdecMMission, TblIdecQSelect";
	sqlstr += " WHERE TblIdecQSelect.jref = " + to_string(preJrefSess) + "";
	sqlstr += " AND TblIdecMMission.grp = TblIdecQSelect.ref";
	rerun_filtSQL(sqlstr, preTit, preGrp, preOwn, preSta, false);
	rerun_orderSQL(sqlstr, preIxOrd);
	sqlstr += " LIMIT " + to_string(stgiac.nload) + " OFFSET " + to_string(stgiac.jnumFirstload-1);
	dbsidec->executeQuery(sqlstr);

	sqlstr = "UPDATE TblIdecQMisList SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

};

void QryIdecMisList::rerun_filtSQL(
			string& sqlstr
			, const string& preTit
			, const ubigint preGrp
			, const ubigint preOwn
			, const int preSta
			, const bool addwhere
		) {
	bool first = addwhere;

	if (preTit.length() > 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMMission.Title LIKE '" + preTit + "'";
	};

	if (preGrp != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMMission.grp = " + to_string(preGrp) + "";
	};

	if (preOwn != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMMission.own = " + to_string(preOwn) + "";
	};

	if (preSta != numeric_limits<int>::min()) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMMission.startd = " + to_string(preSta) + "";
	};
};

void QryIdecMisList::rerun_filtSQL_append(
			string& sqlstr
			, bool& first
		) {
	if (first) {
		sqlstr += " WHERE ";
		first = false;
	} else sqlstr += " AND ";
};

void QryIdecMisList::rerun_orderSQL(
			string& sqlstr
			, const uint preIxOrd
		) {
	if (preIxOrd == VecVOrd::TIT) sqlstr += " ORDER BY TblIdecMMission.Title ASC";
	else if (preIxOrd == VecVOrd::GRP) sqlstr += " ORDER BY TblIdecMMission.grp ASC";
	else if (preIxOrd == VecVOrd::OWN) sqlstr += " ORDER BY TblIdecMMission.own ASC";
	else if (preIxOrd == VecVOrd::STA) sqlstr += " ORDER BY TblIdecMMission.startd ASC";
};

void QryIdecMisList::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQMisList* rec = NULL;

	dbsidec->tblidecqmislist->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->stubGrp = StubIdec::getStubGrp(dbsidec, rec->grp, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			rec->stubOwn = StubIdec::getStubOwn(dbsidec, rec->own, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			rec->ftmStartd = Ftm::date(rec->startd);
			rec->ftmStopd = Ftm::date(rec->stopd);
			rec->titSrefKCountry = dbsidec->getKlstTitleBySref(VecIdecVKeylist::KLSTIDECKMMISSIONCOUNTRY, rec->srefKCountry, ixIdecVLocale);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecMisList", "fetch");
	};

	refreshJnum();
};

uint QryIdecMisList::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQMisList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecMisList::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQMisList* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQMisList* QryIdecMisList::getRecByJnum(
			const uint jnum
		) {
	IdecQMisList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecMisList::handleRequest(
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

bool QryIdecMisList::handleRerun(
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

bool QryIdecMisList::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQMisList* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\tTitle";
	cout << "\tgrp";
	cout << "\tstubGrp";
	cout << "\town";
	cout << "\tstubOwn";
	cout << "\tstartd";
	cout << "\tftmStartd";
	cout << "\tstopd";
	cout << "\tftmStopd";
	cout << "\tsrefKCountry";
	cout << "\ttitSrefKCountry";
	cout << "\tRegion";
	cout << "\tMunicipality";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->Title;
		cout << "\t" << rec->grp;
		cout << "\t" << rec->stubGrp;
		cout << "\t" << rec->own;
		cout << "\t" << rec->stubOwn;
		cout << "\t" << rec->startd;
		cout << "\t" << rec->ftmStartd;
		cout << "\t" << rec->stopd;
		cout << "\t" << rec->ftmStopd;
		cout << "\t" << rec->srefKCountry;
		cout << "\t" << rec->titSrefKCountry;
		cout << "\t" << rec->Region;
		cout << "\t" << rec->Municipality;
		cout << endl;
	};
	return retval;
};

void QryIdecMisList::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMISMOD) {
		call->abort = handleCallIdecMisMod(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMISUPD_REFEQ) {
		call->abort = handleCallIdecMisUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecMisList::handleCallIdecStubChg(
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

bool QryIdecMisList::handleCallIdecMisMod(
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

bool QryIdecMisList::handleCallIdecMisUpd_refEq(
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

