/**
  * \file QryIdecTouList.cpp
  * job handler for job QryIdecTouList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecTouList.h"

#include "QryIdecTouList_blks.cpp"

/******************************************************************************
 class QryIdecTouList
 ******************************************************************************/

QryIdecTouList::QryIdecTouList(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECTOULIST, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	xchg->addStmgr(jref, Stub::VecVNonetype::SHORT);
	ixIdecVQrystate = VecIdecVQrystate::OOD;

	// IP constructor.cust2 --- INSERT

	rerun(dbsidec);

	xchg->addClstn(VecIdecVCall::CALLIDECSTUBCHG, jref, Clstn::VecVJobmask::SPEC, jref, Arg(), Clstn::VecVJactype::LOCK);

	xchg->addClstn(VecIdecVCall::CALLIDECTOUMOD, jref, Clstn::VecVJobmask::ALL, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

QryIdecTouList::~QryIdecTouList() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecTouList::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);

	xchg->removeClstns(VecIdecVCall::CALLIDECTOUUPD_REFEQ, jref);
	if (preRefSel != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECTOUUPD_REFEQ, jref, Clstn::VecVJobmask::ALL, 0, preRefSel, Clstn::VecVJactype::LOCK);
};

void QryIdecTouList::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	vector<ubigint> cnts;
	uint cnt, cntsum;

	vector<ubigint> lims;
	vector<ubigint> ofss;

	uint preIxPre = xchg->getIxPreset(VecIdecVPreset::PREIDECIXPRE, jref);
	uint preIxOrd = xchg->getIxPreset(VecIdecVPreset::PREIDECIXORD, jref);
	ubigint preRefMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);
	string preTit = xchg->getTxtvalPreset(VecIdecVPreset::PREIDECTOULIST_TIT, jref);
	ubigint preMis = xchg->getRefPreset(VecIdecVPreset::PREIDECTOULIST_MIS, jref);
	int preSta = xchg->getIntvalPreset(VecIdecVPreset::PREIDECTOULIST_STA, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqtoulist->removeRstByJref(jref);

	cntsum = 0;

	if (preIxPre == VecIdecVPreset::PREIDECREFMIS) {
		sqlstr = "SELECT COUNT(TblIdecMTour.ref)";
		sqlstr += " FROM TblIdecMTour";
		sqlstr += " WHERE TblIdecMTour.refIdecMMission = " + to_string(preRefMis) + "";
		rerun_filtSQL(sqlstr, preTit, preMis, preSta, false);
		dbsidec->loadUintBySQL(sqlstr, cnt);
		cnts.push_back(cnt); lims.push_back(0); ofss.push_back(0);
		cntsum += cnt;

	} else {
		sqlstr = "SELECT COUNT(TblIdecMTour.ref)";
		sqlstr += " FROM TblIdecMTour";
		rerun_filtSQL(sqlstr, preTit, preMis, preSta, true);
		dbsidec->loadUintBySQL(sqlstr, cnt);
		cnts.push_back(cnt); lims.push_back(0); ofss.push_back(0);
		cntsum += cnt;
	};

	statshr.ntot = 0;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cntsum) {
		if (cntsum >= stgiac.nload) stgiac.jnumFirstload = cntsum-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	for (unsigned int i=0;i<cnts.size();i++) {
		if (statshr.nload < stgiac.nload) {
			if ((statshr.ntot+cnts[i]) >= stgiac.jnumFirstload) {
				if (statshr.ntot >= stgiac.jnumFirstload) {
					ofss[i] = 0;
				} else {
					ofss[i] = stgiac.jnumFirstload-statshr.ntot-1;
				};

				if ((statshr.nload+cnts[i]-ofss[i]) > stgiac.nload) lims[i] = stgiac.nload-statshr.nload;
				else lims[i] = cnts[i]-ofss[i];
			};
		};

		statshr.ntot += cnts[i];
		statshr.nload += lims[i];
	};

	if (preIxPre == VecIdecVPreset::PREIDECREFMIS) {
		rerun_baseSQL(sqlstr);
		sqlstr += " FROM TblIdecMTour";
		sqlstr += " WHERE TblIdecMTour.refIdecMMission = " + to_string(preRefMis) + "";
		rerun_filtSQL(sqlstr, preTit, preMis, preSta, false);
		rerun_orderSQL(sqlstr, preIxOrd);
		sqlstr += " LIMIT " + to_string(lims[0]) + " OFFSET " + to_string(ofss[0]);
		dbsidec->executeQuery(sqlstr);

	} else {
		rerun_baseSQL(sqlstr);
		sqlstr += " FROM TblIdecMTour";
		rerun_filtSQL(sqlstr, preTit, preMis, preSta, true);
		rerun_orderSQL(sqlstr, preIxOrd);
		sqlstr += " LIMIT " + to_string(lims[0]) + " OFFSET " + to_string(ofss[0]);
		dbsidec->executeQuery(sqlstr);
	};

	sqlstr = "UPDATE TblIdecQTouList SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

};

void QryIdecTouList::rerun_baseSQL(
			string& sqlstr
		) {
	sqlstr = "INSERT INTO TblIdecQTouList(jref, jnum, ref, Title, refIdecMMission, start, stop, Area)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMTour.ref, TblIdecMTour.Title, TblIdecMTour.refIdecMMission, TblIdecMTour.start, TblIdecMTour.stop, TblIdecMTour.Area";
};

void QryIdecTouList::rerun_filtSQL(
			string& sqlstr
			, const string& preTit
			, const ubigint preMis
			, const int preSta
			, const bool addwhere
		) {
	bool first = addwhere;

	if (preTit.length() > 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMTour.Title LIKE '" + preTit + "'";
	};

	if (preMis != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMTour.refIdecMMission = " + to_string(preMis) + "";
	};

	if (preSta != numeric_limits<int>::min()) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMTour.start = " + to_string(preSta) + "";
	};
};

void QryIdecTouList::rerun_filtSQL_append(
			string& sqlstr
			, bool& first
		) {
	if (first) {
		sqlstr += " WHERE ";
		first = false;
	} else sqlstr += " AND ";
};

void QryIdecTouList::rerun_orderSQL(
			string& sqlstr
			, const uint preIxOrd
		) {
	if (preIxOrd == VecVOrd::TIT) sqlstr += " ORDER BY TblIdecMTour.Title ASC";
	else if (preIxOrd == VecVOrd::MIS) sqlstr += " ORDER BY TblIdecMTour.refIdecMMission ASC";
	else if (preIxOrd == VecVOrd::STA) sqlstr += " ORDER BY TblIdecMTour.start ASC";
};

void QryIdecTouList::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQTouList* rec = NULL;

	dbsidec->tblidecqtoulist->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->stubRefIdecMMission = StubIdec::getStubMisStd(dbsidec, rec->refIdecMMission, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecTouList", "fetch");
	};

	refreshJnum();
};

uint QryIdecTouList::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQTouList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecTouList::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQTouList* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQTouList* QryIdecTouList::getRecByJnum(
			const uint jnum
		) {
	IdecQTouList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecTouList::handleRequest(
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

bool QryIdecTouList::handleRerun(
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

bool QryIdecTouList::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQTouList* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\tTitle";
	cout << "\trefIdecMMission";
	cout << "\tstubRefIdecMMission";
	cout << "\tstart";
	cout << "\tftmStart";
	cout << "\tstop";
	cout << "\tftmStop";
	cout << "\tArea";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->Title;
		cout << "\t" << rec->refIdecMMission;
		cout << "\t" << rec->stubRefIdecMMission;
		cout << "\t" << rec->start;
		cout << "\t" << rec->ftmStart;
		cout << "\t" << rec->stop;
		cout << "\t" << rec->ftmStop;
		cout << "\t" << rec->Area;
		cout << endl;
	};
	return retval;
};

void QryIdecTouList::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTOUMOD) {
		call->abort = handleCallIdecTouMod(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTOUUPD_REFEQ) {
		call->abort = handleCallIdecTouUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecTouList::handleCallIdecStubChg(
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

bool QryIdecTouList::handleCallIdecTouMod(
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

bool QryIdecTouList::handleCallIdecTouUpd_refEq(
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

