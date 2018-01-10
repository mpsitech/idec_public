/**
  * \file JobIdecSpotfind.cpp
  * job handler for job JobIdecSpotfind (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecSpotfind.h"

#include "JobIdecSpotfind_blks.cpp"

/******************************************************************************
 class JobIdecSpotfind
 ******************************************************************************/

JobIdecSpotfind::JobIdecSpotfind(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECSPOTFIND, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	jobvislacq = NULL;
	jobvisracq = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	jobvislacq = new JobIdecVislacq(xchg, dbsidec, jref, ixIdecVLocale, false);

	// IP constructor.cust2 --- INSERT

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECSTART, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTOP, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECIMGRDY, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSPTFND, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecSpotfind::~JobIdecSpotfind() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

void JobIdecSpotfind::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int res;
	pthread_mutexattr_t attr;

	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	UntIdhwDcx3*& _dcx3 = xchg->datajobidecspotfind.dcx3;

	_dcx3 = NULL;
	if (!xchg->stgidecgeneral.dummy && _sysidhw) {
		if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) _dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3);
		else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) _dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::DCX3);
	};

	xchg->datajobidecspotfind.dummy = (_dcx3 == NULL);

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	res = pthread_mutex_init(&(xchg->datajobidecspotfind.mJrefsStartedVisr), NULL);
	if (res != 0) {cout << "JobIdecSpotfind::initXchgdata() error initializing mutex mJrefsStartedVisr (" << res << ")" << endl;};

	xchg->datajobidecspotfind.vislred = NULL;
	xchg->datajobidecspotfind.visrred = NULL;

	xchg->datajobidecspotfind.A = 100.0;
	xchg->datajobidecspotfind.dr = 5.0;

	xchg->datajobidecspotfind.Njump = 50;

	xchg->datajobidecspotfind.seqno_last = 0;

	xchg->datajobidecspotfind.x0 = 320.0;
	xchg->datajobidecspotfind.y0 = 240.0;

	xchg->datajobidecspotfind.ds = 40.0;

	xchg->datajobidecspotfind.vx = 0.0;
	xchg->datajobidecspotfind.vy = 0.0;
	// IP initXchgdata --- IEND
};

void JobIdecSpotfind::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	int res;

	UntIdhwDcx3*& _dcx3 = xchg->datajobidecspotfind.dcx3;

	res = pthread_mutex_destroy(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
	if (res != 0) {cout << "JobIdecSpotfind::termXchgdata() error destroying mutex mJrefsStartedVisr (" << res << ")" << endl;};

	delete _dcx3;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
void JobIdecSpotfind::start(
			DbsIdec* dbsidec
			, const bool visr
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecSpotfind::start() error locking mutex mAccess (" << res << ")" << endl;};

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
		if (res != 0) {cout << "JobIdecSpotfind::start() error locking mutex mJrefsStartedVisr (" << res << ")" << endl;};

		xchg->datajobidecspotfind.jrefsStarted.insert(jref);
		if (visr) xchg->datajobidecspotfind.jrefsVisr.insert(jref);

/// somewhere here, need to create jobvisr, if needed

		res = pthread_mutex_unlock(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
		if (res != 0) {cout << "JobIdecSpotfind::start() error unlocking mutex mJrefsStartedVisr (" << res << ")" << endl;};

	} else {
		xchg->triggerBoolvalCall(dbsidec, VecIdecVCall::CALLIDECSTART, jref, visr);
	};

	if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecSpotfind::start() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecSpotfind::stop(
			DbsIdec* dbsidec
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecSpotfind::stop() error locking mutex mAccess (" << res << ")" << endl;};

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
		if (res != 0) {cout << "JobIdecSpotfind::stop() error locking mutex mJrefsStartedVisr (" << res << ")" << endl;};
	
		xchg->datajobidecspotfind.jrefsStarted.erase(jref);
		xchg->datajobidecspotfind.jrefsVisr.erase(jref);
		if (xchg->datajobidecspotfind.jrefsStarted.empty() && (ixVSge == VecVSge::READY)) changeStage(dbsidec, VecVSge::IDLE);

/// again, somewhere here, stopping / removing jobvisr needs to take place

		res = pthread_mutex_unlock(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
		if (res != 0) {cout << "JobIdecSpotfind::stop() error unlocking mutex mJrefsStartedVisr (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTOP, jref);
		if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecSpotfind::stop() error unlocking mutex mAccess (" << res << ")" << endl;};
};

bool JobIdecSpotfind::started(
			const bool any
		) {
	bool retval = false;

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
	if (res != 0) {cout << "JobIdecSpotfind::started() error locking mutex mJrefsStartedVisr (" << res << ")" << endl;};

	if (any) retval = !xchg->datajobidecspotfind.jrefsStarted.empty();
	else retval = (xchg->datajobidecspotfind.jrefsStarted.find(jref) != xchg->datajobidecspotfind.jrefsStarted.end());

	res = pthread_mutex_unlock(&(xchg->datajobidecspotfind.mJrefsStartedVisr));
	if (res != 0) {cout << "JobIdecSpotfind::started() error unlocking mutex mJrefsStartedVisr (" << res << ")" << endl;};

	return retval;
};

/*
void JobIdecSpotfind::find() {
	unsigned char* buf;

	unsigned int w, h, wh;

	wh = w*h;

/// RE-START WITH NEW SEQLEN (TYP. FIRST START)
	vector<double> sincoefs;
	vector<double> coscoefs;

	sincoefs.resize(seqlen);
	coscoefs.resize(seqlen);

	// prepare sin/cos multipliers based on seqlen
	for (unsigned int i=0;i<seqlen;i++) {
		sincoefs[i] = sin(2.0*pi*((double)i)/((double)seqlen));
		coscoefs[i] = cos(2.0*pi*((double)i)/((double)seqlen));
	};

/// RE-START WITH NEW BUFFER SIZE (E.G. 32x32 instead of 160x120)
	unsigned int seqno0;

	double* sinbuf;
	double* cosbuf;

	seqno0 = seqno;

	sinbuf = new double[wh];
	cosbuf = new double[wh];

/// RE-START
	memset(sinbuf, 0, wh*sizeof(double));
	memset(cosbuf, 0, wh*sizeof(double));

	icsMax.clear();

/// FOR EACH NEW FRAME
	double max;
	unsigned int ixMax, xMax, yMax, x, y;

	double d;

	// multiply and add based on seqno mod seqlen (160 and 32)
	sincoef = sincoefs[seqno%seqlen];
	coscoef = coscoefs[seqno%seqlen];

	for (unsigned int i=0;i<wh;i++)
		sinbuf[i] += sincoef*((double) buf[i]);
		cosbuf[i] += coscoef*((double) buf[i]);
	};

	// find maximum amplitude (160 and 32)
	max = 0.0;
	ixMax = 0;

	for (unsigned int i=0;i<wh;i++) {
		d = sinbuf[i]*sinbuf[i] + cosbuf[i]*cosbuf[i];
		if (d > max) {
			max = d;
			ixMax = i;
		};
	};

	// note maximum position in timeline (160 and 32)
	icsMax.push_back(ixMax);

	// - success if all of these are fulfilled:

	found = false;

	// observation for at least prdmin periods (160)
	found = (((seqno-seqno0) / seqlen) >= prdmin);

	// at least 0.8*prdmin*seqlen samples (160)
	if (found) found = (icsMax.size() >= ((4*prdmin*seqlen)/5));

	// ixMax at the same spot for at least seqlen samples (160)
	if (found) found = (icsMax.size() >= seqlen);

	if (found) {
		found = true;
		for (unsigned int i=icsMax.size()-1;i>icsMax.size()-seqlen;i--)
			if (icsMax[i-1] != icsMax[i-2]) {
				found = false;
				break;
			};
	};

	// global maximum with at least twice the amplitude of the next maximum (160)
	if (found) {
		found = false;

		xMax = (ixMax%w);
		yMax = (ixMax-xMax)/w;

		for (unsigned int i=0;i<wh;i++) {
			d = sinbuf[i]*sinbuf[i] + cosbuf[i]*cosbuf[i];

			if ((2.0*d) > max) {
				if (i != ixMax) {
					x = (i%w);
					y = (i-x)/w;

					if ((x-xMax >= -1) && (x-xMax <= 1) && (y-yMax >= -1) && (y-yMax <= 1)) {
						found = true;
						break;
					};
				};
			};
		};

		found = !found;
	};

	// - re-start measurement if prdmax periods are reached without success
	if (found) {
		retval = VecVSge::TRACK;
	} else {
		if (((seqno-seqno0) / seqlen) >= prdmax) restart();
	};
};

void JobIdecSpotfind::track() {
	// also implement adaptive power (max power is independent)

	// max power independent

	// ring buffer & re-calculate each time - FIR filter

	// track xMax, yMax as double value - IIR filter

///
	uint& _width = xchg->stgjobidecvislacq.width;
	double& _hpix = xchg->stgjobidecvislacq.hpix;
	double& _f = xchg->stgjobidecvislacq.f;

	double& _dstereo = xchg->stgjobidecstereo.dstereo;
	double& _dphivisr = xchg->stgjobidecstereo.dphivisr;

	d = triangulate(1e-3*_dstereo, 1e-3*_hpix * (xmaxVisl - 0.5*(((double) _width)-1.0)), _f, 1e-3*_hpix * (xmaxVisr - 0.5*(((double) _width)-1.0)), _f, _dphivisr*pi/180.0);
};
*/

double JobIdecSpotfind::triangulate(
			const double ds
			, const double x1
			, const double f1
			, const double x2
			, const double f2
			, const double dphi
		) {
	return(ds / (x2/f2 - x1/f1 - sin(dphi)));
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecSpotfind::changeStage(
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
				case VecVSge::PRC: leaveSgePrc(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			// IP changeStage.refresh1 --- IBEGIN
			xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTATCHG, jref);
			// IP changeStage.refresh1 --- IEND
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::READY: _ixVSge = enterSgeReady(dbsidec, reenter); break;
			case VecVSge::ACQIDLE: _ixVSge = enterSgeAcqidle(dbsidec, reenter); break;
			case VecVSge::ACQ: _ixVSge = enterSgeAcq(dbsidec, reenter); break;
			case VecVSge::PRC: _ixVSge = enterSgePrc(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecSpotfind::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- IBEGIN

	if (jref == jrefMast) {
		// stop acquisition sub-jobs
		jobvislacq->stop(dbsidec);
		jobvisracq->stop(dbsidec);
	};

	// IP enterSgeIdle --- IEND
	return retval;
};

void JobIdecSpotfind::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- IBEGIN
	// IP leaveSgeIdle --- IEND
};

uint JobIdecSpotfind::enterSgeReady(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::READY;
	nextIxVSge = retval;
	// IP enterSgeReady --- INSERT
	return retval;
};

void JobIdecSpotfind::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecSpotfind::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecSpotfind::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecSpotfind::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- INSERT
	return retval;
};

void JobIdecSpotfind::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecSpotfind::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- INSERT
	return retval;
};

void JobIdecSpotfind::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecSpotfind::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecSpotfind::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecSpotfind::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecSpotfind::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecSpotfind::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecSpotfind::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecSpotfind::handleRequest(
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

void JobIdecSpotfind::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};

void JobIdecSpotfind::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTART) {
		call->abort = handleCallIdecStart(dbsidec, call->jref, call->argInv.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTOP) {
		call->abort = handleCallIdecStop(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECIMGRDY) {
		call->abort = handleCallIdecImgrdy(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSPTFND) {
		call->abort = handleCallIdecSptfnd(dbsidec, call->jref, call->argInv.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool JobIdecSpotfind::handleCallIdecStart(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecStart --- INSERT
	return retval;
};

bool JobIdecSpotfind::handleCallIdecStop(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStop --- INSERT
	return retval;
};

bool JobIdecSpotfind::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- INSERT
	return retval;
};

bool JobIdecSpotfind::handleCallIdecSptfnd(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecSptfnd --- INSERT
	return retval;
};

bool JobIdecSpotfind::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecSpotfind::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecSpotfind::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


