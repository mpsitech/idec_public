/**
  * \file JobIdecIllum.cpp
  * job handler for job JobIdecIllum (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecIllum.h"

/******************************************************************************
 class JobIdecIllum
 ******************************************************************************/

JobIdecIllum::JobIdecIllum(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECILLUM, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	// IP constructor.cust2 --- INSERT

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecIllum::~JobIdecIllum() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

void JobIdecIllum::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	UntIdhwDcx3*& _dcx3 = xchg->datajobidecillum.dcx3;

	_dcx3 = NULL;
	if (!xchg->stgidecgeneral.dummy && _sysidhw) {
		if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) _dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3);
		else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) _dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::DCX3);
	};
	//dummy = (_dcx3 == NULL);

	xchg->datajobidecillum.pFlood = 0;
	xchg->datajobidecillum.pSpot = 0;
	// IP initXchgdata --- IEND
};

void JobIdecIllum::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	UntIdhwDcx3*& _dcx3 = xchg->datajobidecillum.dcx3;

	if (_dcx3) delete _dcx3;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
void JobIdecIllum::setPFlood(
			DbsIdec* dbsidec
			, const double pFlood
		) {
	if (jref == jrefMast) {
		xchg->datajobidecillum.pFlood = pFlood;
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	};
};

void JobIdecIllum::setPSpot(
			DbsIdec* dbsidec
			, const double pSpot
		) {
	if (jref == jrefMast) {
		xchg->datajobidecillum.pSpot = pSpot;
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	};
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecIllum::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecIllum::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecIllum::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecIllum::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecIllum::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecIllum::handleRequest(
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

void JobIdecIllum::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	};
};

bool JobIdecIllum::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecIllum::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};


