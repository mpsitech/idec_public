/**
  * \file QryIdecMisRef1NFile.cpp
  * job handler for job QryIdecMisRef1NFile (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "QryIdecMisRef1NFile.h"

#include "QryIdecMisRef1NFile_blks.cpp"

/******************************************************************************
 class QryIdecMisRef1NFile
 ******************************************************************************/

QryIdecMisRef1NFile::QryIdecMisRef1NFile(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::QRYIDECMISREF1NFILE, jrefSup, ixIdecVLocale) {

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

QryIdecMisRef1NFile::~QryIdecMisRef1NFile() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
void QryIdecMisRef1NFile::refreshJnum() {
	ubigint preRefSel = xchg->getRefPreset(VecIdecVPreset::PREIDECREFSEL, jref);

	stgiac.jnum = getJnumByRef(preRefSel);
};

void QryIdecMisRef1NFile::rerun(
			DbsIdec* dbsidec
			, const bool call
		) {
	string sqlstr;

	uint cnt;

	ubigint preRefMis = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);

	xchg->removeClstns(VecIdecVCall::CALLIDECFILMOD_RETREUEQ, jref);

	dbsidec->tblidecqselect->removeRstByJref(jref);
	dbsidec->tblidecqmisref1nfile->removeRstByJref(jref);

	sqlstr = "SELECT COUNT(TblIdecMFile.ref)";
	sqlstr += " FROM TblIdecMFile";
	sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::MIS);
	sqlstr += " AND TblIdecMFile.refUref = " + to_string(preRefMis) + "";
	dbsidec->loadUintBySQL(sqlstr, cnt);

	statshr.ntot = cnt;
	statshr.nload = 0;

	if (stgiac.jnumFirstload > cnt) {
		if (cnt >= stgiac.nload) stgiac.jnumFirstload = cnt-stgiac.nload+1;
		else stgiac.jnumFirstload = 1;
	};

	sqlstr = "INSERT INTO TblIdecQMisRef1NFile(jref, jnum, ref)";
	sqlstr += " SELECT " + to_string(jref) + ", 0, TblIdecMFile.ref";
	sqlstr += " FROM TblIdecMFile";
	sqlstr += " WHERE TblIdecMFile.refIxVTbl = " + to_string(VecIdecVMFileRefTbl::MIS);
	sqlstr += " AND TblIdecMFile.refUref = " + to_string(preRefMis) + "";
	sqlstr += " ORDER BY Filename ASC";
	sqlstr += " LIMIT " + to_string(stgiac.nload) + " OFFSET " + to_string(stgiac.jnumFirstload-1);
	dbsidec->executeQuery(sqlstr);

	sqlstr = "UPDATE TblIdecQMisRef1NFile SET jnum = qref WHERE jref = " + to_string(jref);
	dbsidec->executeQuery(sqlstr);

	ixIdecVQrystate = VecIdecVQrystate::UTD;
	statshr.jnumFirstload = stgiac.jnumFirstload;

	fetch(dbsidec);

	if (call) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);

	xchg->addIxRefClstn(VecIdecVCall::CALLIDECFILMOD_RETREUEQ, jref, Clstn::VecVJobmask::ALL, 0, VecIdecVMFileRefTbl::MIS, preRefMis, Clstn::VecVJactype::LOCK);
};

void QryIdecMisRef1NFile::fetch(
			DbsIdec* dbsidec
		) {
	string sqlstr;

	StmgrIdec* stmgr = NULL;
	Stcch* stcch = NULL;

	IdecQMisRef1NFile* rec = NULL;

	dbsidec->tblidecqmisref1nfile->loadRstByJref(jref, false, rst);
	statshr.nload = rst.nodes.size();

	stmgr = xchg->getStmgrByJref(jref);

	if (stmgr) {
		stmgr->begin();

		stcch = stmgr->stcch;
		stcch->clear();

		for (unsigned int i=0;i<rst.nodes.size();i++) {
			rec = rst.nodes[i];

			rec->jnum = statshr.jnumFirstload + i;
			rec->stubRef = StubIdec::getStubFilStd(dbsidec, rec->ref, ixIdecVLocale, Stub::VecVNonetype::SHORT, stcch);
		};

		stmgr->commit();
		stmgr->unlockAccess("QryIdecMisRef1NFile", "fetch");
	};

	refreshJnum();
};

uint QryIdecMisRef1NFile::getJnumByRef(
			const ubigint ref
		) {
	uint retval = 0;

	IdecQMisRef1NFile* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		if (rec->ref == ref) {
			retval = rec->jnum;
			break;
		};
	};

	return retval;
};

ubigint QryIdecMisRef1NFile::getRefByJnum(
			const uint jnum
		) {
	uint ref = 0;

	IdecQMisRef1NFile* rec = getRecByJnum(jnum);
	if (rec) ref = rec->ref;
	return ref;
};

IdecQMisRef1NFile* QryIdecMisRef1NFile::getRecByJnum(
			const uint jnum
		) {
	IdecQMisRef1NFile* rec = NULL;

	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];
		if (rec->jnum == jnum) break;
	};

	if (rec) if (rec->jnum != jnum) rec = NULL;
	return rec;
};

void QryIdecMisRef1NFile::handleRequest(
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

bool QryIdecMisRef1NFile::handleRerun(
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

bool QryIdecMisRef1NFile::handleShow(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	IdecQMisRef1NFile* rec = NULL;

	// header row
	cout << "\tqref";
	cout << "\tjref";
	cout << "\tjnum";
	cout << "\tref";
	cout << "\tstubRef";
	cout << endl;

	// record rows
	for (unsigned int i=0;i<rst.nodes.size();i++) {
		rec = rst.nodes[i];

		cout << "\t" << rec->qref;
		cout << "\t" << rec->jref;
		cout << "\t" << rec->jnum;
		cout << "\t" << rec->ref;
		cout << "\t" << rec->stubRef;
		cout << endl;
	};
	return retval;
};

void QryIdecMisRef1NFile::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTUBCHG) {
		call->abort = handleCallIdecStubChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECFILMOD_RETREUEQ) {
		call->abort = handleCallIdecFilMod_retReuEq(dbsidec, call->jref, call->argInv.ix, call->argInv.ref);
	};
};

bool QryIdecMisRef1NFile::handleCallIdecStubChg(
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

bool QryIdecMisRef1NFile::handleCallIdecFilMod_retReuEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
		) {
	bool retval = false;

	if (ixIdecVQrystate != VecIdecVQrystate::OOD) {
		ixIdecVQrystate = VecIdecVQrystate::OOD;
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	};

	return retval;
};

