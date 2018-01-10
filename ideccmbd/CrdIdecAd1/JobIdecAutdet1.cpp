/**
  * \file JobIdecAutdet1.cpp
  * job handler for job JobIdecAutdet1 (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecAutdet1.h"

#include "JobIdecAutdet1_blks.cpp"

/******************************************************************************
 class JobIdecAutdet1
 ******************************************************************************/

JobIdecAutdet1::JobIdecAutdet1(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECAUTDET1, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	jobillum = NULL;
	joblwiracq = NULL;
	jobmechctl = NULL;
	jobqcdacq = NULL;
	jobrecord = NULL;
	jobtrigger = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	jobillum = new JobIdecIllum(xchg, dbsidec, jref, ixIdecVLocale, true);
	joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobmechctl = new JobIdecMechctl(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobrecord = new JobIdecRecord(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobtrigger = new JobIdecTrigger(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECIMGRDY, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecAutdet1::~JobIdecAutdet1() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
// IP spec --- INSERT

void JobIdecAutdet1::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::SURVEY: leaveSgeSurvey(dbsidec); break;
				case VecVSge::POS: leaveSgePos(dbsidec); break;
				case VecVSge::PRC: leaveSgePrc(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			// IP changeStage.refresh1 --- INSERT
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::SURVEY: _ixVSge = enterSgeSurvey(dbsidec, reenter); break;
			case VecVSge::POS: _ixVSge = enterSgePos(dbsidec, reenter); break;
			case VecVSge::PRC: _ixVSge = enterSgePrc(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecAutdet1::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void JobIdecAutdet1::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint JobIdecAutdet1::enterSgeSurvey(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::SURVEY;
	nextIxVSge = retval;
	// IP enterSgeSurvey --- INSERT
	return retval;
};

void JobIdecAutdet1::leaveSgeSurvey(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeSurvey --- INSERT
};

uint JobIdecAutdet1::enterSgePos(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::POS;
	nextIxVSge = retval;
	// IP enterSgePos --- INSERT
	return retval;
};

void JobIdecAutdet1::leaveSgePos(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePos --- INSERT
};

uint JobIdecAutdet1::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- INSERT
	return retval;
};

void JobIdecAutdet1::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecAutdet1::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecAutdet1::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecAutdet1::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecAutdet1::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecAutdet1::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecAutdet1::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- INSERT
	return retval;
};

void JobIdecAutdet1::handleRequest(
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
	};
};

void JobIdecAutdet1::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECIMGRDY) {
		call->abort = handleCallIdecImgrdy(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool JobIdecAutdet1::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- INSERT
	return retval;
};

bool JobIdecAutdet1::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecAutdet1::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};

