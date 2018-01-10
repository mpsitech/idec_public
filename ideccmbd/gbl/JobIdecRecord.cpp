/**
  * \file JobIdecRecord.cpp
  * job handler for job JobIdecRecord (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecRecord.h"

#include "JobIdecRecord_blks.cpp"

/******************************************************************************
 class JobIdecRecord
 ******************************************************************************/

JobIdecRecord::JobIdecRecord(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECRECORD, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	joblwiracq = NULL;
	jobqcdacq = NULL;
	jobstereo = NULL;
	jobvislacq = NULL;
	jobvisracq = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	// IP constructor.cust2 --- INSERT

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECIMGRDY, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecRecord::~JobIdecRecord() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- IBEGIN
void JobIdecRecord::snapshot(
			DbsIdec* dbsidec
		) {
	string path;
	uint refIxVTbl;
	ubigint refUref;

	fstream txtfile;

	// determine reference
	refIxVTbl = VecIdecVMFileRefTbl::VOID;
	refUref = 0;

	refUref = xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref);
	if (refUref) {
		refIxVTbl = VecIdecVMFileRefTbl::TOU;
	} else {
		refUref = xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref);
		if (refUref) refIxVTbl = VecIdecVMFileRefTbl::MIS;
	};

	// create dummy file
	path = Tmp::newfile(xchg->tmppath, "txt");
	path = xchg->tmppath + path;

	txtfile.open(path.c_str(), ios::out);

	txtfile << "demo file" << endl;

	txtfile.close();

	// add to archive
	Acv::addfile(dbsidec, xchg->acvpath, path, refIxVTbl, refUref, "sngfrm", "demo.txt", "txt", "");
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecRecord::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::READY: leaveSgeReady(dbsidec); break;
				case VecVSge::ACQIDLE: leaveSgeAcqidle(dbsidec); break;
				case VecVSge::ACQ: leaveSgeAcq(dbsidec); break;
				case VecVSge::PAUSE: leaveSgePause(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			// IP changeStage.refresh1 --- INSERT
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::READY: _ixVSge = enterSgeReady(dbsidec, reenter); break;
			case VecVSge::ACQIDLE: _ixVSge = enterSgeAcqidle(dbsidec, reenter); break;
			case VecVSge::ACQ: _ixVSge = enterSgeAcq(dbsidec, reenter); break;
			case VecVSge::PAUSE: _ixVSge = enterSgePause(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecRecord::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void JobIdecRecord::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint JobIdecRecord::enterSgeReady(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::READY;
	nextIxVSge = retval;
	// IP enterSgeReady --- INSERT
	return retval;
};

void JobIdecRecord::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecRecord::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecRecord::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecRecord::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- INSERT
	return retval;
};

void JobIdecRecord::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecRecord::enterSgePause(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PAUSE;
	nextIxVSge = retval;
	// IP enterSgePause --- INSERT
	return retval;
};

void JobIdecRecord::leaveSgePause(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgePause --- INSERT
};

string JobIdecRecord::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecRecord::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecRecord::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecRecord::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecRecord::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecRecord::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- INSERT
	return retval;
};

void JobIdecRecord::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
		handleTimer(dbsidec, req->sref);
	};
};

void JobIdecRecord::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if ((ixVSge == VecVSge::PAUSE) && (sref == "pause")) {
		// IP handleTimer.pause --- INSERT
	};
};

void JobIdecRecord::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECIMGRDY) {
		call->abort = handleCallIdecImgrdy(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool JobIdecRecord::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- INSERT
	return retval;
};

bool JobIdecRecord::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecRecord::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


