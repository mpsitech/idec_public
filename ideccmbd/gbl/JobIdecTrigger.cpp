/**
  * \file JobIdecTrigger.cpp
  * job handler for job JobIdecTrigger (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecTrigger.h"

#include "JobIdecTrigger_blks.cpp"

/******************************************************************************
 class JobIdecTrigger
 ******************************************************************************/

JobIdecTrigger::JobIdecTrigger(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECTRIGGER, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	// IP constructor.cust2 --- INSERT

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECTRIGVISL, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECTRIGVISR, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECTRIGLWIR, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECTRIGQCD, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecTrigger::~JobIdecTrigger() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

void JobIdecTrigger::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	UntIdhwDcx3*& _dcx3 = xchg->datajobidectrigger.dcx3;

	_dcx3 = NULL;
	if (!xchg->stgidecgeneral.dummy && _sysidhw) {
		if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) _dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3);
		else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) _dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::DCX3);
	};
	
	xchg->datajobidectrigger.dummy = (_dcx3 == NULL);

	xchg->datajobidectrigger.usecFps = 1000000;

	xchg->datajobidectrigger.ixUsecWaits = 0;
	xchg->datajobidectrigger.seqno = 0;
	// IP initXchgdata --- IEND
};

void JobIdecTrigger::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	UntIdhwDcx3*& _dcx3 = xchg->datajobidectrigger.dcx3;

	if (_dcx3) delete _dcx3;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
void JobIdecTrigger::setupUsecWaits() {
	double& _tvisr = xchg->stgjobidectrigger.tvisr;
	double& _tlwir = xchg->stgjobidectrigger.tlwir;
	double& _tqcd = xchg->stgjobidectrigger.tqcd;

	unsigned int& _usecFps = xchg->datajobidectrigger.usecFps;
	vector<int>& _usecWaits = xchg->datajobidectrigger.usecWaits;
	vector<uint>& _icsIdecVCall = xchg->datajobidectrigger.icsIdecVCall;

	int usecWait;
	uint ixIdecVCall;

	unsigned int jmin;

	_usecWaits.clear();
	_icsIdecVCall.clear();

	_usecWaits.push_back(0); _icsIdecVCall.push_back(VecIdecVCall::CALLIDECTRIGVISL);
	_usecWaits.push_back(1000.0*_tvisr); _icsIdecVCall.push_back(VecIdecVCall::CALLIDECTRIGVISR);
	_usecWaits.push_back(1000.0*_tlwir); _icsIdecVCall.push_back(VecIdecVCall::CALLIDECTRIGLWIR);
	_usecWaits.push_back(1000.0*_tqcd); _icsIdecVCall.push_back(VecIdecVCall::CALLIDECTRIGQCD);

	// sort
	for (unsigned int i=0;i<_usecWaits.size();i++) {
		jmin = i;

		for (unsigned int j=i+1;j<_usecWaits.size();j++) if (_usecWaits[j] < _usecWaits[jmin]) jmin = j;

		if (jmin != i) {
			usecWait = _usecWaits[i];
			ixIdecVCall = _icsIdecVCall[i];

			_usecWaits[i] = _usecWaits[jmin];
			_icsIdecVCall[i] = _icsIdecVCall[jmin];

			_usecWaits[jmin] = usecWait;
			_icsIdecVCall[jmin] = ixIdecVCall;
		};
	};

	// align to start at t=0
	for (unsigned int i=0;i<_usecWaits.size();i++) _usecWaits[_usecWaits.size()-i-1] -= _usecWaits[0];

	// trigger spread can't be larger than frame period
	if (((unsigned int) _usecWaits[_usecWaits.size()-1]) > _usecFps) for (unsigned int i=0;i<_usecWaits.size();i++) _usecWaits[i] = 0;

	// t -> dt
	for (unsigned int i=0;i<_usecWaits.size()-1;i++) _usecWaits[i] = _usecWaits[i+1] - _usecWaits[i];
	_usecWaits[_usecWaits.size()-1] = _usecFps - _usecWaits[_usecWaits.size()-1];
};

void JobIdecTrigger::start(
			DbsIdec* dbsidec
			, const double fps
		) {
	if ((jrefMast == jref) && (ixVSge == VecVSge::IDLE)) {
		xchg->datajobidectrigger.usecFps = lround(1000000.0/fps);
		changeStage(dbsidec, VecVSge::RUN);
	};
};

void JobIdecTrigger::stop(
			DbsIdec* dbsidec
		) {
	if (jrefMast == jref) changeStage(dbsidec, VecVSge::IDLE);
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecTrigger::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::RUN: leaveSgeRun(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			// IP changeStage.refresh1 --- IBEGIN
			xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
			// IP changeStage.refresh1 --- IEND
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::RUN: _ixVSge = enterSgeRun(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecTrigger::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void JobIdecTrigger::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint JobIdecTrigger::enterSgeRun(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::RUN;
	nextIxVSge = retval;
	// IP enterSgeRun --- IBEGIN

	setupUsecWaits();

	xchg->datajobidectrigger.ixUsecWaits = xchg->datajobidectrigger.usecWaits.size()-1;
	xchg->datajobidectrigger.seqno = 0; xchg->datajobidectrigger.seqno--;

	wrefLast = xchg->addWakeup(jref, "run", 0);

	// IP enterSgeRun --- IEND
	return retval;
};

void JobIdecTrigger::leaveSgeRun(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgeRun --- INSERT
};

string JobIdecTrigger::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecTrigger::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecTrigger::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecTrigger::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecTrigger::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecTrigger::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecTrigger::handleRequest(
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

void JobIdecTrigger::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if ((ixVSge == VecVSge::RUN) && (sref == "run")) {
		// IP handleTimer.run --- IBEGIN
		vector<int>& _usecWaits = xchg->datajobidectrigger.usecWaits;
		vector<uint>& _icsIdecVCall = xchg->datajobidectrigger.icsIdecVCall;
		unsigned int& _ixUsecWaits = xchg->datajobidectrigger.ixUsecWaits;
		uint& _seqno = xchg->datajobidectrigger.seqno;

		bool first;

		if (_usecWaits.size() > 0) {
			first = true;

			while (true) {
				_ixUsecWaits++;

				if (_ixUsecWaits >= _usecWaits.size()) {
					if (first) {
						_ixUsecWaits = 0;
						_seqno++;
						first = false;

					} else break; // protection against all-zero usecWaits
				};

				xchg->triggerIntvalCall(dbsidec, _icsIdecVCall[_ixUsecWaits], jref, _seqno);

				if (_usecWaits[_ixUsecWaits] != 0) {
					wrefLast = xchg->addWakeup(jref, "run", _usecWaits[_ixUsecWaits]);
					break;
				};
			};
		};
		// IP handleTimer.run --- IEND
	};
};

void JobIdecTrigger::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECTRIGVISL) {
		call->abort = handleCallIdecTrigVisl(dbsidec, call->jref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTRIGVISR) {
		call->abort = handleCallIdecTrigVisr(dbsidec, call->jref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTRIGLWIR) {
		call->abort = handleCallIdecTrigLwir(dbsidec, call->jref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTRIGQCD) {
		call->abort = handleCallIdecTrigQcd(dbsidec, call->jref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	};
};

bool JobIdecTrigger::handleCallIdecTrigVisl(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigVisl --- IBEGIN

//cout << "JobIdecTrigger::handleCallIdecTrigVisl() ; jref = " << jref << endl;

	xchg->triggerIntvalCall(dbsidec, VecIdecVCall::CALLIDECTRIGVISL, jref, intvalInv);

	// IP handleCallIdecTrigVisl --- IEND
	return retval;
};

bool JobIdecTrigger::handleCallIdecTrigVisr(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigVisr --- IBEGIN
	xchg->triggerIntvalCall(dbsidec, VecIdecVCall::CALLIDECTRIGVISR, jref, intvalInv);
	// IP handleCallIdecTrigVisr --- IEND
	return retval;
};

bool JobIdecTrigger::handleCallIdecTrigLwir(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigLwir --- IBEGIN
	xchg->triggerIntvalCall(dbsidec, VecIdecVCall::CALLIDECTRIGLWIR, jref, intvalInv);
	// IP handleCallIdecTrigLwir --- IEND
	return retval;
};

bool JobIdecTrigger::handleCallIdecTrigQcd(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigQcd --- IBEGIN
	xchg->triggerIntvalCall(dbsidec, VecIdecVCall::CALLIDECTRIGQCD, jref, intvalInv);
	// IP handleCallIdecTrigQcd --- IEND
	return retval;
};

bool JobIdecTrigger::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- IBEGIN
	if (jrefTrig == jrefMast) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	// IP handleCallIdecStatChg --- IEND
	return retval;
};

bool JobIdecTrigger::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};


