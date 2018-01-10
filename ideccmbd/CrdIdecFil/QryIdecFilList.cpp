/**
  * \file QryIdecFilList.cpp
  * job handler for job QryIdecFilList (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecFilList.h"

#include "QryIdecFilList_blks.cpp"

/******************************************************************************
 class QryIdecFilList
 ******************************************************************************/

QryIdecFilList::QryIdecFilList(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECFILLIST, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	xchg->addStmgr(jref, Stub::VecVNonetype::SHORT);
	ixIdecVQrystate = VecIdecVQrystate::OOD;

	// IP constructor.cust2 --- INSERT

	rerun(dbsidec);

	xchg->addClstn(VecIdecVCall::CALLIDECSTUBCHG, jref, Clstn::VecVJobmask::SPEC, jref, Arg(), Clstn::VecVJactype::LOCK);

	xchg->addClstn(VecIdecVCall::CALLIDECFILMOD, jref, Clstn::VecVJobmask::ALL, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

QryIdecFilList::~QryIdecFilList() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecFilList::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);

	xchg->removeClstns(VecIdecVCall::CALLIDECFILUPD_REFEQ, jref);
	if (preRefSel != 0) xchg->addRefClstn(VecIdecVCall::CALLIDECFILUPD_REFEQ, jref, Clstn::VecVJobmask::ALL, 0, preRefSel, Clstn::VecVJactype::LOCK);
};

void QryIdecFilList::rerun(
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
	ubigint preRefTou = xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref);
	string preFnm = xchg->getTxtvalPreset(VecIdecVPreset::PREIDECFILLIST_FNM, jref);
	uint preRet = xchg->getIxPreset(VecIdecVPreset::PREIDECFILLIST_RET, jref);
	ubigint preReu = xchg->getRefPreset(VecIdecVPreset::PREIDECFILLIST_REU, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqfillist->removeRstByJref(jref);

	cntsum = 0;

	if (preIxPre == VecIdecVPreset::PREIDECREFTOU) {
		sqlstr = "SELECT COUNT(TblIdecMFile.ref)";
		sqlstr += " FROM TblIdecMFile";
		sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::TOU);
		sqlstr += " AND TblIdecMFile.refUref = " + to_string(preRefTou) + "";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, false);
		dbsidec->loadUintBySQL(sqlstr, cnt);
		cnts.push_back(cnt); lims.push_back(0); ofss.push_back(0);
		cntsum += cnt;

	} else if (preIxPre == VecIdecVPreset::PREIDECREFMIS) {
		sqlstr = "SELECT COUNT(TblIdecMFile.ref)";
		sqlstr += " FROM TblIdecMFile";
		sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::MIS);
		sqlstr += " AND TblIdecMFile.refUref = " + to_string(preRefMis) + "";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, false);
		dbsidec->loadUintBySQL(sqlstr, cnt);
		cnts.push_back(cnt); lims.push_back(0); ofss.push_back(0);
		cntsum += cnt;

		sqlstr = "SELECT COUNT(TblIdecMFile.ref)";
		sqlstr += " FROM TblIdecMFile, TblIdecMTour";
		sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::TOU);
		sqlstr += " AND TblIdecMFile.refUref = TblIdecMTour.ref";
		sqlstr += " AND TblIdecMTour.refIdecMMission = " + to_string(preRefMis) + "";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, false);
		dbsidec->loadUintBySQL(sqlstr, cnt);
		cnts.push_back(cnt); lims.push_back(0); ofss.push_back(0);
		cntsum += cnt;

	} else {
		sqlstr = "SELECT COUNT(TblIdecMFile.ref)";
		sqlstr += " FROM TblIdecMFile";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, true);
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

	if (preIxPre == VecIdecVPreset::PREIDECREFTOU) {
		rerun_baseSQL(sqlstr);
		sqlstr += " FROM TblIdecMFile";
		sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::TOU);
		sqlstr += " AND TblIdecMFile.refUref = " + to_string(preRefTou) + "";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, false);
		rerun_orderSQL(sqlstr, preIxOrd);
		sqlstr += " LIMIT " + to_string(lims[0]) + " OFFSET " + to_string(ofss[0]);
		dbsidec->executeQuery(sqlstr);

	} else if (preIxPre == VecIdecVPreset::PREIDECREFMIS) {
		rerun_baseSQL(sqlstr);
		sqlstr += " FROM TblIdecMFile";
		sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::MIS);
		sqlstr += " AND TblIdecMFile.refUref = " + to_string(preRefMis) + "";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, false);
		rerun_orderSQL(sqlstr, preIxOrd);
		sqlstr += " LIMIT " + to_string(lims[0]) + " OFFSET " + to_string(ofss[0]);
		dbsidec->executeQuery(sqlstr);

		rerun_baseSQL(sqlstr);
		sqlstr += " FROM TblIdecMFile, TblIdecMTour";
		sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::TOU);
		sqlstr += " AND TblIdecMFile.refUref = TblIdecMTour.ref";
		sqlstr += " AND TblIdecMTour.refIdecMMission = " + to_string(preRefMis) + "";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, false);
		rerun_orderSQL(sqlstr, preIxOrd);
		sqlstr += " LIMIT " + to_string(lims[1]) + " OFFSET " + to_string(ofss[1]);
		dbsidec->executeQuery(sqlstr);

	} else {
		rerun_baseSQL(sqlstr);
		sqlstr += " FROM TblIdecMFile";
		rerun_filtSQL(sqlstr, preFnm, preRet, preReu, true);
		rerun_orderSQL(sqlstr, preIxOrd);
		sqlstr += " LIMIT " + to_string(lims[0]) + " OFFSET " + to_string(ofss[0]);
		dbsidec->executeQuery(sqlstr);
	};

	sqlstr = "UPDATE TblIdecQFilList SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

};

void QryIdecFilList::rerun_baseSQL(
			string& sqlstr
		) {
	sqlstr = "INSERT INTO TblIdecQFilList(jref, jnum, ref, Filename, refIxVTbl, refUref, osrefKContent, srefKMimetype, Size)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMFile.ref, TblIdecMFile.Filename, TblIdecMFile.refIxVTbl, TblIdecMFile.refUref, TblIdecMFile.osrefKContent, TblIdecMFile.srefKMimetype, TblIdecMFile.Size";
};

void QryIdecFilList::rerun_filtSQL(
			string& sqlstr
			, const string& preFnm
			, const uint preRet
			, const ubigint preReu
			, const bool addwhere
		) {
	bool first = addwhere;

	if (preFnm.length() > 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMFile.Filename LIKE '" + preFnm + "'";
	};

	if (preRet != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMFile.refIxVTbl = " + to_string(preRet) + "";
	};

	if (preReu != 0) {
		rerun_filtSQL_append(sqlstr, first);
		sqlstr += "TblIdecMFile.refUref = " + to_string(preReu) + "";
	};
};

void QryIdecFilList::rerun_filtSQL_append(
			string& sqlstr
			, bool& first
		) {
	if (first) {
		sqlstr += " WHERE ";
		first = false;
	} else sqlstr += " AND ";
};

void QryIdecFilList::rerun_orderSQL(
			string& sqlstr
			, const uint preIxOrd
		) {
	if (preIxOrd == VecVOrd::FNM) sqlstr += " ORDER BY TblIdecMFile.Filename ASC";
	else if (preIxOrd == VecVOrd::RET) sqlstr += " ORDER BY TblIdecMFile.refIxVTbl ASC";
	else if (preIxOrd == VecVOrd::REU) sqlstr += " ORDER BY TblIdecMFile.refUref ASC";
};

void QryIdecFilList::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQFilList* rec = NULL;

	dbsidec->tblidecqfillist->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->srefRefIxVTbl = VecIdecVMFileRefTbl::getSref(rec->refIxVTbl);
			rec->titRefIxVTbl = VecIdecVMFileRefTbl::getTitle(rec->refIxVTbl, ixIdecVLocale);
			if (rec->refIxVTbl == VecIdecVMFileRefTbl::MIS) {
				rec->stubRefUref = StubIdec::getStubMisStd(dbsidec, rec->refUref, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			} else if (rec->refIxVTbl == VecIdecVMFileRefTbl::TOU) {
				rec->stubRefUref = StubIdec::getStubTouStd(dbsidec, rec->refUref, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
			} else rec->stubRefUref = "-";
			rec->titOsrefKContent = dbsidec->getKlstTitleBySref(VecIdecVKeylist::KLSTIDECKMFILECONTENT, rec->osrefKContent, ixIdecVLocale);
			rec->titSrefKMimetype = dbsidec->getKlstTitleBySref(VecIdecVKeylist::KLSTIDECKMFILEMIMETYPE, rec->srefKMimetype, ixIdecVLocale);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecFilList", "fetch");
	};

	refreshJnum();
};

uint QryIdecFilList::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQFilList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecFilList::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQFilList* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQFilList* QryIdecFilList::getRecByJnum(
			const uint jnum
		) {
	IdecQFilList* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecFilList::handleRequest(
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

bool QryIdecFilList::handleRerun(
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

bool QryIdecFilList::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQFilList* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\tFilename";
	cout << "\trefIxVTbl";
	cout << "\tsrefRefIxVTbl";
	cout << "\ttitRefIxVTbl";
	cout << "\trefUref";
	cout << "\tstubRefUref";
	cout << "\tosrefKContent";
	cout << "\ttitOsrefKContent";
	cout << "\tsrefKMimetype";
	cout << "\ttitSrefKMimetype";
	cout << "\tSize";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->Filename;
		cout << "\t" << rec->refIxVTbl;
		cout << "\t" << rec->srefRefIxVTbl;
		cout << "\t" << rec->titRefIxVTbl;
		cout << "\t" << rec->refUref;
		cout << "\t" << rec->stubRefUref;
		cout << "\t" << rec->osrefKContent;
		cout << "\t" << rec->titOsrefKContent;
		cout << "\t" << rec->srefKMimetype;
		cout << "\t" << rec->titSrefKMimetype;
		cout << "\t" << rec->Size;
		cout << endl;
	};
	return retval;
};

void QryIdecFilList::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFILMOD) {
		call->abort = handleCallIdecFilMod(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFILUPD_REFEQ) {
		call->abort = handleCallIdecFilUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool QryIdecFilList::handleCallIdecStubChg(
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

bool QryIdecFilList::handleCallIdecFilMod(
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

bool QryIdecFilList::handleCallIdecFilUpd_refEq(
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

