/**
  * \file JobIdecMechctl.cpp
  * job handler for job JobIdecMechctl (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecMechctl.h"

#include "JobIdecMechctl_blks.cpp"

/******************************************************************************
 class JobIdecMechctl
 ******************************************************************************/

JobIdecMechctl::JobIdecMechctl(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECMECHCTL, jrefSup, ixIdecVLocale, prefmast) {

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

JobIdecMechctl::~JobIdecMechctl() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

void JobIdecMechctl::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int rint;

	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	UntIdhwAxs2*& _thetaaxs2 = xchg->datajobidecmechctl.thetaaxs2;
	UntIdhwAxs2*& _phiaxs2 = xchg->datajobidecmechctl.phiaxs2;

	_thetaaxs2 = NULL;
	_phiaxs2 = NULL;
	if (!xchg->stgidecgeneral.dummy && _sysidhw) {
		if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) {
			_thetaaxs2 = (UntIdhwAxs2*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3_AXS2_THETA);
			_phiaxs2 = (UntIdhwAxs2*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3_AXS2_PHI);
		} else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) {
			_thetaaxs2 = (UntIdhwAxs2*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::AXS2_THETA);
			_phiaxs2 = (UntIdhwAxs2*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::AXS2_PHI);
		};
	};

	xchg->datajobidecmechctl.dummy = ((_thetaaxs2 == NULL) || (_phiaxs2 == NULL));

	xchg->datajobidecmechctl.theIxIdecVAxisste = VecIdecVAxisste::READY;
	xchg->datajobidecmechctl.phiIxIdecVAxisste = VecIdecVAxisste::READY;

	xchg->datajobidecmechctl.alpha = 0.0;
	xchg->datajobidecmechctl.beta = 0.0;

	xchg->datajobidecmechctl.theta = 0.0;
	xchg->datajobidecmechctl.phi = 0.0;

	xchg->datajobidecmechctl.thetaRpm = 0;
	xchg->datajobidecmechctl.phiRpm = 0;

	// --- dummy functionality

	// alpha, beta amplitude between 15° and 20° ; period between 1s and 3s
	rint = (rand() % 5000) + 15000;
	xchg->datajobidecmechctl.alphaA = 1e-3 * ((double) rint);

	rint = (rand() % 2000) + 3000;
	xchg->datajobidecmechctl.alphaT = 1e-3 * ((double) rint);

	rint = (rand() % 5000) + 15000;
	xchg->datajobidecmechctl.betaA = 1e-3 * ((double) rint);

	rint = (rand() % 2000) + 3000;
	xchg->datajobidecmechctl.betaT = 1e-3 * ((double) rint);

	// simulated axis movement rpm plateau and acceleration
	xchg->datajobidecmechctl.rpmp = 4000;
	xchg->datajobidecmechctl.drpmdt = 4000;

	xchg->datajobidecmechctl.theta0 = 0.0;
	xchg->datajobidecmechctl.theta1 = 0.0;
	xchg->datajobidecmechctl.ttheta0 = {0,0};

	xchg->datajobidecmechctl.phi0 = 0.0;
	xchg->datajobidecmechctl.phi1 = 0.0;
	xchg->datajobidecmechctl.tphi0 = {0,0};
	// IP initXchgdata --- IEND
};

void JobIdecMechctl::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	UntIdhwAxs2*& _thetaaxs2 = xchg->datajobidecmechctl.thetaaxs2;
	UntIdhwAxs2*& _phiaxs2 = xchg->datajobidecmechctl.phiaxs2;

	if (_thetaaxs2) delete _thetaaxs2;
	if (_phiaxs2) delete _phiaxs2;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
double JobIdecMechctl::getAlpha() {
	double& _alphaA = xchg->datajobidecmechctl.alphaA;
	double& _alphaT = xchg->datajobidecmechctl.alphaT;

	return(getAlphabeta(_alphaA, _alphaT));
};

double JobIdecMechctl::getBeta() {
	double& _betaA = xchg->datajobidecmechctl.betaA;
	double& _betaT = xchg->datajobidecmechctl.betaT;

	return(getAlphabeta(_betaA, _betaT));
};

double JobIdecMechctl::getAlphabeta(
			const double A
			, const double T
		) {
	timespec timestamp;
	double t;

	Idec::getTimestamp(&timestamp);
	t = Idec::getDoubletime(&timestamp);

	return(A * sin(2.0*pi*t/T));
};

void JobIdecMechctl::getThetaThetarpm(
			double& theta
			, int& thetarpm
		) {
	usmallint& _gr = xchg->stgjobidecmechctltheta.gr;

	double& _theta0 = xchg->datajobidecmechctl.theta0;
	double& _theta1 = xchg->datajobidecmechctl.theta1;
	timespec& _ttheta0 = xchg->datajobidecmechctl.ttheta0;

	getAngAngrpm(_theta0, _theta1, _gr, &_ttheta0, theta, thetarpm);
};

void JobIdecMechctl::getPhiPhirpm(
			double& phi
			, int& phirpm
		) {
	usmallint& _gr = xchg->stgjobidecmechctlphi.gr;

	double& _phi0 = xchg->datajobidecmechctl.phi0;
	double& _phi1 = xchg->datajobidecmechctl.phi1;
	timespec& _tphi0 = xchg->datajobidecmechctl.tphi0;

	getAngAngrpm(_phi0, _phi1, _gr, &_tphi0, phi, phirpm);
};

void JobIdecMechctl::getAngAngrpm(
			const double ang0
			, const double ang3
			, const double gr
			, timespec* tang0
			, double& ang
			, int& irpm
		) {
	// 0: start, 1: rpm plateau start, 2: rpm plateau stop, 3: stop
	double t0, t1, t2, t3;

	double inv;

	timespec timestamp;
	double t;

	double rpm;

	uint& _rpmp = xchg->datajobidecmechctl.rpmp;
	uint& _drpmdt = xchg->datajobidecmechctl.drpmdt;

	double dpsp = ((double) _rpmp) * 6.0/gr; // deg/sec taking into account gear reduction
	double ddpsdt = ((double) _drpmdt) * 6.0/gr;

	t0 = Idec::getDoubletime(tang0);

	if ( (fabs(ang3-ang0)/dpsp) > (dpsp/ddpsdt) ) {
		// displacement with rpm plateau
		t1 = t0 + dpsp/ddpsdt;
		t3 = t1 + fabs(ang3-ang0)/dpsp;
		t2 = t3 - dpsp/ddpsdt;

	} else {
		// displacement without rpm plateau
		t1 = t0 + sqrt(fabs(ang3-ang0)/ddpsdt);
		t2 = t1;
		t3 = t2 + sqrt(fabs(ang3-ang0)/ddpsdt);
	};

	if (ang0 < ang3) inv = 1.0;
	else inv = -1.0;

	Idec::getTimestamp(&timestamp);
	t = Idec::getDoubletime(&timestamp);

	if (t <= t0) {
		ang = ang0;
		rpm = 0;
	} else if (t >= t3) {
		ang = ang3;
		rpm = 0;
	} else {
		if ((t > t0) && (t <= t1)) {
			// accelerating
			ang = ang0 + inv/2.0 * ddpsdt * pow(t-t0, 2.0);
			rpm = inv * ((double) _drpmdt) * (t-t0);
		} else if ((t > t1) && (t <= t2)) {
			// on rpm plateau
			ang = ang0 + inv/2.0 * ddpsdt * pow(t1-t0, 2.0) + inv * dpsp * (t-t1);
			rpm = inv * _rpmp;
		} else {
			// decelerating
			ang = ang3 - inv/2.0 * ddpsdt * pow(t3-t, 2.0);
			rpm = inv * (_rpmp - ((double) _drpmdt) * (t-t2));
		};
	};

	irpm = lround(rpm);
};

void JobIdecMechctl::setTargetTheta(
			DbsIdec* dbsidec
			, const double theta
		) {
	if (jref == jrefMast) {
		// invalidateWakeups() not possible due to possible theta/phi simultaneous movement
		usmallint& _gr = xchg->stgjobidecmechctltheta.gr;

		uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
		double& _theta0 = xchg->datajobidecmechctl.theta0;
		double& _theta1 = xchg->datajobidecmechctl.theta1;
		timespec& _ttheta0 = xchg->datajobidecmechctl.ttheta0;

		setTargetAng(dbsidec, theta, _gr, _theIxIdecVAxisste, _theta0, _theta1, _ttheta0);
	};
};

void JobIdecMechctl::setTargetPhi(
			DbsIdec* dbsidec
			, const double phi
		) {
	if (jref == jrefMast) {
		usmallint& _gr = xchg->stgjobidecmechctlphi.gr;

		uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;
		double& _phi0 = xchg->datajobidecmechctl.phi0;
		double& _phi1 = xchg->datajobidecmechctl.phi1;
		timespec& _tphi0 = xchg->datajobidecmechctl.tphi0;

		setTargetAng(dbsidec, phi, _gr, _phiIxIdecVAxisste, _phi0, _phi1, _tphi0);
	};
};

void JobIdecMechctl::setTargetAng(
			DbsIdec* dbsidec
			, const double ang
			, const double gr
			, uint& ixIdecVAxisste
			, double& ang0
			, double& ang1
			, timespec& tang0
		) {
	int res;

	double oldAng;
	int oldIrpm;

	double dt;

	uint& _rpmp = xchg->datajobidecmechctl.rpmp;
	uint& _drpmdt = xchg->datajobidecmechctl.drpmdt;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecMechctl::setTargetAng() error locking mutex mAccess (" << res << ")" << endl;};

	double dpsp = ((double) _rpmp) * 6.0/gr;
	double ddpsdt = ((double) _drpmdt) * 6.0/gr;

	if (ang != ang1) {
		getAngAngrpm(ang0, ang1, gr, &tang0, oldAng, oldIrpm);

		ang0 = oldAng;
		ang1 = ang;

		Idec::getTimestamp(&tang0);

		if ( (fabs(ang1-ang0)/dpsp) > (dpsp/ddpsdt) ) {
			// displacement with rpm plateau
			dt = dpsp/ddpsdt + fabs(ang1-ang0)/dpsp;
		} else {
			// displacement without rpm plateau
			dt = 2.0 * sqrt(fabs(ang1-ang0)/ddpsdt);
		};

		wrefLast = xchg->addWakeup(jref, "move", lround(1e6*dt), false);
		ixIdecVAxisste = VecIdecVAxisste::ACTIVE;
		changeStage(dbsidec, VecVSge::MOVE);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecMechctl::setTargetAng() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecMechctl::stopTheta() {
	if (jref == jrefMast) {
		usmallint& _gr = xchg->stgjobidecmechctltheta.gr;
		double& _llim = xchg->stgjobidecmechctltheta.llim;
		double& _ulim = xchg->stgjobidecmechctltheta.ulim;

		double& _theta0 = xchg->datajobidecmechctl.theta0;
		double& _theta1 = xchg->datajobidecmechctl.theta1;
		timespec& _ttheta0 = xchg->datajobidecmechctl.ttheta0;

		stopAng(_llim, _ulim, _gr, _theta0, _theta1, _ttheta0);
	};
};

void JobIdecMechctl::stopPhi() {
	if (jref == jrefMast) {
		usmallint& _gr = xchg->stgjobidecmechctlphi.gr;
		double& _llim = xchg->stgjobidecmechctlphi.llim;
		double& _ulim = xchg->stgjobidecmechctlphi.ulim;

		double& _phi0 = xchg->datajobidecmechctl.phi0;
		double& _phi1 = xchg->datajobidecmechctl.phi1;
		timespec& _tphi0 = xchg->datajobidecmechctl.tphi0;

		stopAng(_llim, _ulim, _gr, _phi0, _phi1, _tphi0);
	};
};

void JobIdecMechctl::stopAng(
			const double llim
			, const double ulim
			, const double gr
			, double& ang0
			, double& ang1
			, timespec& tang0
		) {
	int res;

	uint& _rpmp = xchg->datajobidecmechctl.rpmp;
	uint& _drpmdt = xchg->datajobidecmechctl.drpmdt;

	double ang, dang;

	int irpm;
	double dps;

	timespec timestamp;
	double t, dt;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecMechctl::stopAng() error locking mutex mAccess (" << res << ")" << endl;};

	double ddpsdt = ((double) _drpmdt) * 6.0/gr;

	Idec::getTimestamp(&timestamp);
	t = Idec::getDoubletime(&timestamp);

	getAngAngrpm(ang0, ang1, gr, &tang0, ang, irpm);
	dps = ((double) irpm) * 6.0/gr;

	if ( (irpm == ((int) _rpmp)) || (irpm == -((int)_rpmp)) || (fabs(ang-ang0) < fabs(ang1-ang)) ) {
		// on rpm plateau or accelerating

		// change to an imagined displacement which is at its peak rpm right now, and half-way
		dt = fabs(dps/ddpsdt);
		tang0.tv_sec = lround(floor(t-dt));
		tang0.tv_nsec = lround(1e9 * ((t-dt) - floor(t-dt)));

		dang = 0.5 * pow(dps, 2.0) / ddpsdt;
		if (irpm < 0) dang *= -1.0;

		ang0 = ang - dang;
		ang1 = ang + dang;
		if (ang1 < llim) ang1 = llim;
		if (ang1 > ulim) ang1 = ulim;

		wrefLast = xchg->addWakeup(jref, "move", lround(1e6*dt), false);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecMechctl::stopAng() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecMechctl::refresh(
			DbsIdec* dbsidec
		) {
	double ang;
	int irpm;

	usmallint& _theGr = xchg->stgjobidecmechctltheta.gr;
	usmallint& _phiGr = xchg->stgjobidecmechctlphi.gr;

	uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
	uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;

	double& _theta0 = xchg->datajobidecmechctl.theta0;
	double& _theta1 = xchg->datajobidecmechctl.theta1;
	timespec& _ttheta0 = xchg->datajobidecmechctl.ttheta0;

	double& _phi0 = xchg->datajobidecmechctl.phi0;
	double& _phi1 = xchg->datajobidecmechctl.phi1;
	timespec& _tphi0 = xchg->datajobidecmechctl.tphi0;

	if ( (ixVSge == VecVSge::MOVE) && ((_theIxIdecVAxisste == VecIdecVAxisste::ACTIVE) || (_phiIxIdecVAxisste == VecIdecVAxisste::ACTIVE)) ) {

		if (_theIxIdecVAxisste == VecIdecVAxisste::ACTIVE) {
			getAngAngrpm(_theta0, _theta1, _theGr, &_ttheta0, ang, irpm);
			if (ang == _theta1) _theIxIdecVAxisste = VecIdecVAxisste::READY;
		};

		if (_phiIxIdecVAxisste == VecIdecVAxisste::ACTIVE) {
			getAngAngrpm(_phi0, _phi1, _phiGr, &_tphi0, ang, irpm);
			if (ang == _phi1) _phiIxIdecVAxisste = VecIdecVAxisste::READY;
		};

		if ((_theIxIdecVAxisste == VecIdecVAxisste::READY) && (_phiIxIdecVAxisste == VecIdecVAxisste::READY)) changeStage(dbsidec, VecVSge::IDLE);
	};
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecMechctl::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::MOVE: leaveSgeMove(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			// IP changeStage.refresh1 --- IBEGIN
			xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
			// IP changeStage.refresh1 --- IEND
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::MOVE: _ixVSge = enterSgeMove(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecMechctl::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void JobIdecMechctl::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint JobIdecMechctl::enterSgeMove(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::MOVE;
	nextIxVSge = retval;
	// IP enterSgeMove --- INSERT
	return retval;
};

void JobIdecMechctl::leaveSgeMove(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgeMove --- INSERT
};

string JobIdecMechctl::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecMechctl::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecMechctl::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecMechctl::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecMechctl::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecMechctl::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecMechctl::handleRequest(
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

void JobIdecMechctl::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if ((ixVSge == VecVSge::MOVE) && (sref == "move")) {
		refresh(dbsidec); // IP handleTimer.move --- ILINE
	};
};

void JobIdecMechctl::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	};
};

bool JobIdecMechctl::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- IBEGIN
	if (jrefTrig == jrefMast) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
	// IP handleCallIdecStatChg --- IEND
	return retval;
};

bool JobIdecMechctl::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};


