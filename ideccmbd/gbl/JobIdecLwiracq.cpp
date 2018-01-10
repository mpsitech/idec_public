/**
  * \file JobIdecLwiracq.cpp
  * job handler for job JobIdecLwiracq (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecLwiracq.h"

#include "JobIdecLwiracq_blks.cpp"

/******************************************************************************
 class JobIdecLwiracq
 ******************************************************************************/

JobIdecLwiracq::JobIdecLwiracq(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECLWIRACQ, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	jobtrigger = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	jobtrigger = new JobIdecTrigger(xchg, dbsidec, jref, ixIdecVLocale, false);

	// IP constructor.cust2 --- IBEGIN
	bref = 0;
	seqno = 0;
	timestamp = {0,0};
	// IP constructor.cust2 --- IEND

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECTRIGLWIR, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSTART, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTOP, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECIBITRDY, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecLwiracq::~JobIdecLwiracq() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- IBEGIN
	xchg->datajobideclwiracq.gray.releaseByJref(jref);
	// IP destructor.cust --- IEND

	xchg->removeJobByJref(jref);
};

void JobIdecLwiracq::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int res;
	pthread_mutexattr_t attr;

	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	UntIdhwDcx3*& _dcx3 = xchg->datajobideclwiracq.dcx3;
	UntIdhwTau2*& _tau2 = xchg->datajobideclwiracq.tau2;

	_dcx3 = NULL;
	_tau2 = NULL;
	if (!xchg->stgidecgeneral.dummy && _sysidhw) {
		if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) {
			_dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3);
			_tau2 = (UntIdhwTau2*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3_TAU2);
		} else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) {
			_dcx3 = (UntIdhwDcx3*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::DCX3);
			_tau2 = (UntIdhwTau2*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::TAU2);
		};
	};

	xchg->datajobideclwiracq.dummy = (_dcx3 == NULL);

	xchg->datajobideclwiracq.ixIdecVCamste = VecIdecVCamste::NC;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	res = pthread_mutex_init(&(xchg->datajobideclwiracq.mJrefsStarted), &attr);
	if (res != 0) {cout << "JobIdecLwiracq::initXchgdata() error initializing mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobideclwiracq.seqno = 0;

	if ((xchg->stgjobideclwiracq.a == 0.0) || (xchg->stgjobideclwiracq.dS == 0.0) || (xchg->stgjobideclwiracq.dT == 0.0)
				|| (xchg->stgjobideclwiracq.iplTTvsSSx.size() == 0)) {
		setupIplTTvsSS(xchg);
	};

	setupTTvsSS(xchg);

	xchg->datajobideclwiracq.gray0 = NULL;

	xchg->datajobideclwiracq.testpat = NULL;

	xchg->datajobideclwiracq.x = 0;
	xchg->datajobideclwiracq.y = 0;
	xchg->datajobideclwiracq.vx = 0;
	xchg->datajobideclwiracq.vy = 0;
	// IP initXchgdata --- IEND
};

void JobIdecLwiracq::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	int res;

	UntIdhwDcx3*& _dcx3 = xchg->datajobideclwiracq.dcx3;
	UntIdhwTau2*& _tau2 = xchg->datajobideclwiracq.tau2;

	res = pthread_mutex_destroy(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::termXchgdata() error destroying mutex mJrefsStarted (" << res << ")" << endl;};

	if (xchg->datajobideclwiracq.gray0) delete[] xchg->datajobideclwiracq.gray0;

	if (xchg->datajobideclwiracq.testpat) delete[] xchg->datajobideclwiracq.testpat;

	if (_dcx3) delete _dcx3;
	if (_tau2) delete _tau2;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
void JobIdecLwiracq::changeSqrgrp(
			const uint ixIdecVSqrgrp
		) {
	if (ixVSge == VecVSge::IDLE) {
		if (ixIdecVSqrgrp != xchg->stgjobideclwiracq.ixIdecVSqrgrp) {
			xchg->stgjobideclwiracq.ixIdecVSqrgrp = ixIdecVSqrgrp;
		};
	};
};

void JobIdecLwiracq::setupIplTTvsSS(
			XchgIdec* xchg
		) {
	double& _lam0 = xchg->stgjobideclwiracq.lam0;
	double& _lam1 = xchg->stgjobideclwiracq.lam1;
	double& _a = xchg->stgjobideclwiracq.a;
	double& _b = xchg->stgjobideclwiracq.b;
	double& _dS = xchg->stgjobideclwiracq.dS;
	double& _dT = xchg->stgjobideclwiracq.dT;
	vector<usmallint>& _iplTTvsSSx = xchg->stgjobideclwiracq.iplTTvsSSx;
	vector<double>& _iplTTvsSSy = xchg->stgjobideclwiracq.iplTTvsSSy;

	vector<double> lut; // local version of TTvsSS with higher precision than integer-only

	const double Tmax = 373.0;
	double Smax;

	double T, Tstep, S, Stest, tol;
	double TT;

	// - constant and linear mapping ADC signal -> power per area ; S = a * (x - b)

	// considering Stefan-Boltzmann law states: S = 314.06 W/m^2 (T=273K), S = 1097.6 W/m^2 (T=373K)

	// assume a behavior in which the ADC reading x0 = 16200 corr. to S = 0 W/m^2, and x1 = 4000 corr. S = 500 W/m^2

	_a = (500.0-0.0) / (4000.0-16200.0);
	_b = 16200.0;

	// - non-linear mapping power per area -> temperature ; based on filtered blackbody radiation

	// look-up table maps power density level SS = 0 .. 65535 to temperature range TT = 0 .. 65535

	// consider temperature range up to Tmax = 373K
	Smax = Slwir(Tmax, _lam0, _lam1, 0.1, 50.0, 0.1);
	_dS = Smax / 65535.0;

	_dT = Tmax / 65535.0;

	lut.resize(65536);

	tol = 1e-2*_dS; // absolute tolerance of S

	// find T for each S ; S(T) is strictly monotonically increasing
	for (unsigned int i=0;i<lut.size();i++) {
		S = ((double) i) * _dS;

		if (S == 0.0) {
			T = 0.0;

		} else {
			Tstep = _dT;

			// interval search
			while (true) {
				T += Tstep;

				Stest = Slwir(T, _lam0, _lam1, 0.1, 50.0, 0.1);

				if (fabs(Stest-S) <= tol) break;

				if ( ((Stest > S) && (Tstep > 0.0)) || ((Stest < S) && (Tstep < 0.0)) ) Tstep = -Tstep/2.0;
			};
		};

		TT = T/_dT;
		if (TT < 0.0) TT = 0.0;
		if (TT > 65535.0) TT = 65535.0;

		lut[i] = TT;
	};

	// some examples for square window 7µm .. 14µm T -> (SS/TT) -> x = S/a + b = SS*dS/a + b:
	// 273K -> (15537/47965) -> 13197
	// 278K -> (17054/48844) -> 12904
	// 283K -> (18664/49722) -> 12592
	// 288K -> (20368/50601) -> 12263
	// 293K -> (22168/51479) -> 11915
	// 298K -> (24066/52358) -> 11548
	// 303K -> (26064/53236) -> 11162

	// dump lut to file
	fstream outfile;

	outfile.open("lutLwir.txt", ios::out);

	outfile << "SS\tS\tTT\tT\tS0" << endl;
	for (unsigned int i=0;i<lut.size();i++) {
		T = (((double) lut[i])*_dT);
		outfile << i << "\t" << (((double) i)*_dS) << "\t" << lut[i] << "\t" << T << "\t" << (sig*pow(T, 4.0)) << endl;
	};

	outfile.close();

	// - generate interpolation with non-uniformily spaced supporting points
	Idec::setupIpl(1.0, lut, 256, _iplTTvsSSx, _iplTTvsSSy);

	// N=64: resr = 3.71
	// N=128: resr = 0.895
	// N=256: resr = 0.219 (use this in preferences file)
	// N=512: resr = 0.0528
	// N=1024: resr = 0.0139
};

void JobIdecLwiracq::setupTTvsSS(
			XchgIdec* xchg
		) {
	vector<usmallint>& _iplTTvsSSx = xchg->stgjobideclwiracq.iplTTvsSSx;
	vector<double>& _iplTTvsSSy = xchg->stgjobideclwiracq.iplTTvsSSy;

	vector<usmallint>& _TTvsSS = xchg->datajobideclwiracq.TTvsSS;

	vector<double> TTvsSS;

	// dump interpolation table
/*
	cout << "LWIR interpolation table (iTT vs iSS)" << endl;
	cout << "iSS\tiTT" << endl;
	for (unsigned int i=0;i<_iplTTvsSSx.size();i++) cout << _iplTTvsSSx[i] << "\t" << _iplTTvsSSy[i] << endl;
*/

	Idec::setupFromIpl(_iplTTvsSSx, _iplTTvsSSy, 65536, TTvsSS);

	_TTvsSS.resize(65536);
	for (unsigned int i=0;i<65536;i++) _TTvsSS[i] = lround(TTvsSS[i]);
};

inline double JobIdecLwiracq::Slwir(
			const double T
			, const double Flam0
			, const double Flam1
			, const double lam0
			, const double lam1
			, const double dlam
		) {
	// integrate square filtered blackbody radiation ; unit of return value: W/m^2

	double retval = 0.0;

	double _lam0, _lam1;

	if (Flam0 > lam0) _lam0 = Flam0; else _lam0 = lam0;
	if (Flam1 < lam1) _lam1 = Flam1; else _lam1 = lam1;

	for (double lam=_lam0 ; lam<=_lam1 ; lam+=dlam) {
		retval += 1e-6*dlam * 2.0 * pi * h * pow(c0, 2.0) * (1.0/pow(1e-6*lam, 5.0)) * (1.0 / (exp(h*c0/((1e-6*lam)*k*T)) - 1.0));
	};

	return retval;
};

// exact copy from Idec.cpp but inline
inline unsigned int JobIdecLwiracq::intavg(
			const unsigned int in
			, const unsigned int im
			, bool* rshs
			, const unsigned int rshsN
		) {
	unsigned int retval = im*in;

	for (unsigned int i=0;i<rshsN;i++) if (rshs[i]) retval += (in >> (i+1));

	return retval;
};

void JobIdecLwiracq::start(
			DbsIdec* dbsidec
			, vector<Snippet*> _snippets
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecLwiracq::start() error locking mutex mAccess (" << res << ")" << endl;};

	snippets = _snippets;

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobideclwiracq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecLwiracq::start() error locking mutex mJrefsStarted (" << res << ")" << endl;};

		xchg->datajobideclwiracq.jrefsStarted.insert(jref);

		res = pthread_mutex_unlock(&(xchg->datajobideclwiracq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecLwiracq::start() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTART, jref);
	};

	if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecLwiracq::start() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecLwiracq::stop(
			DbsIdec* dbsidec
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecLwiracq::stop() error locking mutex mAccess (" << res << ")" << endl;};

	snippets.clear();

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobideclwiracq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecLwiracq::stop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
		xchg->datajobideclwiracq.jrefsStarted.erase(jref);
		if (xchg->datajobideclwiracq.jrefsStarted.empty() && (ixVSge == VecVSge::READY)) changeStage(dbsidec, VecVSge::IDLE);

		res = pthread_mutex_unlock(&(xchg->datajobideclwiracq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecLwiracq::stop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTOP, jref);
		if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecLwiracq::stop() error unlocking mutex mAccess (" << res << ")" << endl;};
};

bool JobIdecLwiracq::started(
			const bool any
		) {
	bool retval = false;

	int res;

	res = pthread_mutex_lock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::started() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	if (any) retval = !xchg->datajobideclwiracq.jrefsStarted.empty();
	else retval = (xchg->datajobideclwiracq.jrefsStarted.find(jref) != xchg->datajobideclwiracq.jrefsStarted.end());

	res = pthread_mutex_unlock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::started() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	return retval;
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecLwiracq::changeStage(
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
				case VecVSge::PRCIDLE: leaveSgePrcidle(dbsidec); break;
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
			case VecVSge::PRCIDLE: _ixVSge = enterSgePrcidle(dbsidec, reenter); break;
			case VecVSge::PRC: _ixVSge = enterSgePrc(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecLwiracq::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- IBEGIN

	xchg->datajobideclwiracq.gray.releaseByJref(jref);

	// IP enterSgeIdle --- IEND
	return retval;
};

void JobIdecLwiracq::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- IBEGIN

	unsigned int& _w = xchg->stgjobideclwiracq.width;
	unsigned int& _h = xchg->stgjobideclwiracq.height;
	double& _a = xchg->stgjobideclwiracq.a;
	double& _b = xchg->stgjobideclwiracq.b;
	double& _dS = xchg->stgjobideclwiracq.dS;

	bool& _dummy = xchg->datajobideclwiracq.dummy;
	unsigned int& _seqno = xchg->datajobideclwiracq.seqno;
	unsigned short*& _gray0 = xchg->datajobideclwiracq.gray0;
	vector<usmallint>& _TTvsSS = xchg->datajobideclwiracq.TTvsSS;
	Imgbuf& _gray = xchg->datajobideclwiracq.gray;
	unsigned short*& _testpat = xchg->datajobideclwiracq.testpat;
	int& _x = xchg->datajobideclwiracq.x;
	int& _y = xchg->datajobideclwiracq.y;
	int& _vx = xchg->datajobideclwiracq.vx;
	int& _vy = xchg->datajobideclwiracq.vy;

	if (jref == jrefMast) {
		_seqno = 0;

		// reset / initialize buffers
		if (!_gray0) {
			_gray0 = new unsigned short[_w*_h]; memset((void*) _gray0, 127, 2*_w*_h);
			_gray.init(8, 2*_w*_h);
		};

		// initialize dummy pattern
		const double xmin = 11162.0; // ADC reading for 303K
		const double xmax = 13197.0; // ADC reading for 273K

		double d, dmin, dmax;

		int rint;

		const unsigned int hN = 6; // number of superimposed sine waves in horizontal/vertical direction
		const unsigned int vN = 4;

		vector<double> hsins;
		vector<double> vsins;

		vector<double> ds;

		_dummy = true;

		_testpat = new unsigned short[_w*_h];

		hsins.resize(hN*_w);
		vsins.resize(vN*_h);

		ds.resize(_w*_h);

		for (unsigned int i=0;i<hN;i++) {
			rint = (rand() % 20) + 1;
			d = 2.0 * pi * ((double) rint) / ((double) _w);
			for (unsigned int j=0;j<_w;j++) hsins[i*_w+j] = sin(((double) j)*d);
		};

		for (unsigned int i=0;i<vN;i++) {
			rint = (rand() % 20) + 1;
			d = 2.0 * pi * ((double) rint) / ((double) _h);
			for (unsigned int j=0;j<_h;j++) vsins[i*_h+j] = sin(((double) j)*d);
		};

		dmin = 1.0e6;
		dmax = -1.0e6;

		for (unsigned int i=0;i<_h;i++) {
			for (unsigned int j=0;j<_w;j++) {
				d = 0.0;

				// hsins are invariant in y (index i)
				// vsins are invariant in x (index j)

				for (unsigned int k=0;k<hN;k++) d += hsins[k*_w+j];
				for (unsigned int k=0;k<vN;k++) d += vsins[k*_h+i];

				if (d < dmin) dmin = d;
				if (d > dmax) dmax = d;

				ds[i*_w+j] = d;
			};
		};

		for (unsigned int i=0;i<_h;i++) {
			for (unsigned int j=0;j<_w;j++) {
				d = xmin + (xmax-xmin) * (ds[i*_w+j]-dmin)/(dmax-dmin);

				// linear correction
				d = (d - _b) * _a / _dS;

				if (d > 65535.0) d = 65535.0;
				if (d < 0.0) d = 0.0;

				// SS -> TT transform via look-up table
				_testpat[i*_w+j] = _TTvsSS[lround(d)];
			};
		};
		
		rint = 3;
		while (rint == 3) rint = rand() % 7;
		_vx = rint - 5;

		rint = 3;
		while (rint == 3) rint = rand() % 7;
		_vy = rint - 3;

		_x = 0;
		_y = 0;
	};

	bref = 0;
	seqno = 0;
	timestamp = {0,0};

	// IP leaveSgeIdle --- IEND
};

uint JobIdecLwiracq::enterSgeReady(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::READY;
	nextIxVSge = retval;
	// IP enterSgeReady --- IBEGIN

	if (!started(jref == jrefMast)) retval = VecVSge::IDLE;

	// IP enterSgeReady --- IEND
	return retval;
};

void JobIdecLwiracq::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecLwiracq::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecLwiracq::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecLwiracq::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- IBEGIN

	// should only be invoked as master: get raw image data
	int res;

	bool valid;

	unsigned int& _w = xchg->stgjobideclwiracq.width;
	unsigned int& _h = xchg->stgjobideclwiracq.height;
	uint& _ixIdecVSqrgrp = xchg->stgjobideclwiracq.ixIdecVSqrgrp;

	bool& _dummy = xchg->datajobideclwiracq.dummy;
	unsigned int& _seqno = xchg->datajobideclwiracq.seqno;
	set<ubigint>& _jrefsStarted = xchg->datajobideclwiracq.jrefsStarted;
	unsigned short*& _gray0 = xchg->datajobideclwiracq.gray0;
	Imgbuf& _gray = xchg->datajobideclwiracq.gray;
	unsigned short*& _testpat = xchg->datajobideclwiracq.testpat;
	int& _x = xchg->datajobideclwiracq.x;
	int& _y = xchg->datajobideclwiracq.y;
	int& _vx = xchg->datajobideclwiracq.vx;
	int& _vy = xchg->datajobideclwiracq.vy;

	Imgbufitem* ibit = NULL;

	usmallint* _g;

	unsigned int ix, ix2;

	valid = true;

	// - prepare for processing
	res = pthread_mutex_lock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::enterSgeAcq() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	bref = 0;

	if (valid) {
		// obtain available slot in _gray
		bref = _gray.getNewItem(jref, _seqno, {0,0}); // seqno from trigger, timestamp generated at this time
		valid = (bref != 0);
	};
	
	if (valid) {
		if (_dummy) {
			// assemble directly in ibit
			ibit = _gray.getItem(bref);

			_g = (usmallint*) ibit->data;

			// 2x memcpy per line
			for (unsigned int i=0;i<_h;i++) {
				ix = i*_w; // source in _testpat
				ix2 = ((i+_y)%_h)*_w; // target in _g

				memcpy((void*) &(_g[ix2+_x]), (void*) &(_testpat[ix]), 2*(_w-_x));
				memcpy((void*) &(_g[ix2]), (void*) &(_testpat[ix+(_w-_x)]), 2*_x);
			};

			_x += _vx;
			if (_x < 0) _x += _w;
			if (_x >= ((int) _w)) _x -= _w;

			_y += _vy;
			if (_y < 0) _y += _h;
			if (_y >= ((int) _h)) _y -= _h;

		} else {
			// _gray0 -> ibit
			ibit = _gray.getItem(bref);

			_g = (usmallint*) ibit->data;

			// apply orientation transform (r0, r2, s0, s2 are allowed)
			Idec::copytrfBuf((unsigned char*) _gray0, (unsigned char*) _g, 2, _w, _h, _ixIdecVSqrgrp);
		};

		// spread the news
		xchg->triggerRefCall(dbsidec, VecIdecVCall::CALLIDECIBITRDY, jref, bref);

		if (_jrefsStarted.find(jref) == _jrefsStarted.end()) retval = VecVSge::READY;
		else retval = VecVSge::PRC;

	} else {
		retval = VecVSge::READY;
	};

	res = pthread_mutex_unlock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::enterSgeAcq() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	if ((bref != 0) && (retval != VecVSge::PRC)) _gray.release(bref, jref);

	// IP enterSgeAcq --- IEND
	return retval;
};

void JobIdecLwiracq::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecLwiracq::enterSgePrcidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRCIDLE;
	nextIxVSge = VecVSge::PRC;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgePrcidle --- INSERT
	return retval;
};

void JobIdecLwiracq::leaveSgePrcidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrcidle --- INSERT
};

uint JobIdecLwiracq::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- IBEGIN

	bool valid;

	unsigned int& _w = xchg->stgjobideclwiracq.width;
	unsigned int& _h = xchg->stgjobideclwiracq.height;

	Imgbuf& _gray = xchg->datajobideclwiracq.gray;

	Imgbufitem* ibit = NULL;

	usmallint* _g = NULL;

	Snippet* snippet = NULL;

	unsigned int w, h, wh;

	unsigned int mult;

	unsigned int x0, y0;

	unsigned int cpyw, cpyh;

	unsigned int sum;

	unsigned int im;
	unsigned int rshsN;
	bool rshs[16];

	unsigned int ix;

	ibit = _gray.getItem(bref);
	valid = (ibit != NULL);

	if (valid) {
		for (unsigned int i=0;i<snippets.size();i++) {
			valid = snippets[i]->claim(jref);

			if (!valid) {
				for (unsigned int j=0;j<i;j++) snippets[j]->release();
				break;
			};
		};
	};

	if (valid) {
		seqno = ibit->seqno;
		timestamp = ibit->timestamp;

		_g = (usmallint*) (ibit->data);

		for (unsigned int m=0;m<snippets.size();m++) {
			snippet = snippets[m];

			// determine integer scaling factor
			Idec::getCamresWh(snippet->ixIdecVCamres, w, h, _w, _h);
			wh = w*h;

			mult = 1;
			while (((mult*w+16) < _w) && ((mult*h+12) < _h)) mult++;

			// - padding in coordinates of (non-scaled) raw image
			x0 = snippet->x0*mult;
			y0 = snippet->y0*mult;

			cpyw = snippet->w;
			cpyh = snippet->h;

			if ((x0 + mult*cpyw) > _w) cpyw = (_w-x0)/mult;
			if ((y0 + mult*cpyh) > _h) cpyh = (_h-y0)/mult;

			// borders to the right and below
			if (cpyw < snippet->w) for (unsigned int i=0;i<cpyh;i++) memset((void*) &(snippet->data[2*(i*snippet->w+cpyw)]), 127, 2*(snippet->w-cpyw));
			if (cpyh < snippet->h) memset((void*) &(snippet->data[2*(snippet->w*cpyh)]), 127, 2*(snippet->w*(snippet->h-cpyh)));

			if ((mult == 1) && (cpyw == _w) && (cpyh == _h)) {
				if (cpyw == snippet->w) memcpy(snippet->data, (void*) _g, 2*wh);
				else for (unsigned int i=0;i<cpyh;i++) memcpy((void*) &(snippet->data[2*(i*snippet->w)]), (void*) &(_g[i*_w]), 2*cpyw);

			} else {
				rshsN = 16;
				Idec::setupIntavg(mult*mult, 65535, 65535, 0.999, im, rshs, rshsN);

				for (unsigned int i=0;i<cpyh;i++) {
					for (unsigned int j=0;j<cpyw;j++) {
						sum = 0;

						for (unsigned int k=0;k<mult;k++) {
							for (unsigned int l=0;l<mult;l++) {
								ix = (y0+mult*i+k)*_w + (x0+mult*j+l);

								sum += _g[ix];
							};
						};

						((unsigned short*) (snippet->data))[i*snippet->w+j] = intavg(sum, im, rshs, rshsN);
					};
				};
			};

			snippet->release();
		};

		if (snippets.size() > 0) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECIMGRDY, jref);
	};

	if (ibit) _gray.release(bref, jref);

	retval = VecVSge::READY;

	// IP enterSgePrc --- IEND
	return retval;
};

void JobIdecLwiracq::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecLwiracq::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecLwiracq::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecLwiracq::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecLwiracq::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecLwiracq::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecLwiracq::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecLwiracq::handleRequest(
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

void JobIdecLwiracq::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if (ixVSge == VecVSge::PRCIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};

void JobIdecLwiracq::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECTRIGLWIR) {
		call->abort = handleCallIdecTrigLwir(dbsidec, call->jref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTART) {
		call->abort = handleCallIdecStart(dbsidec, call->jref, call->argInv.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTOP) {
		call->abort = handleCallIdecStop(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECIBITRDY) {
		call->abort = handleCallIdecIbitrdy(dbsidec, call->jref, call->argInv.ref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool JobIdecLwiracq::handleCallIdecTrigLwir(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigLwir --- IBEGIN

	if ((jref == jrefMast) && (ixVSge == VecVSge::READY)) {
		xchg->datajobideclwiracq.seqno = intvalInv;
		changeStage(dbsidec, VecVSge::ACQIDLE);
	};

	// IP handleCallIdecTrigLwir --- IEND
	return retval;
};

bool JobIdecLwiracq::handleCallIdecStart(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecStart --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::handleCallIdecStart() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobideclwiracq.jrefsStarted.insert(jrefTrig);

	res = pthread_mutex_unlock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::handleCallIdecStart() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	res = pthread_mutex_trylock(&mAccess);

	if (res == 0) {
		if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "JobIdecLwiracq::handleCallIdecStart() error unlocking mutex mAccess (" << res << ")" << endl;};

	} else if (res != EBUSY) {cout << "JobIdecLwiracq::handleCallIdecStart() error try-locking mutex mAccess (" << res << ")" << endl;};

	// IP handleCallIdecStart --- IEND
	return retval;
};

bool JobIdecLwiracq::handleCallIdecStop(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStop --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::handleCallIdecStop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
	xchg->datajobideclwiracq.jrefsStarted.erase(jrefTrig);

	if (xchg->datajobideclwiracq.jrefsStarted.empty()) {
		res = pthread_mutex_trylock(&mAccess);

		if (res == 0) {
			if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);

			res = pthread_mutex_unlock(&mAccess);
			if (res != 0) {cout << "JobIdecLwiracq::handleCallIdecStop() error unlocking mutex mAccess (" << res << ")" << endl;};

		} else if (res != EBUSY) {cout << "JobIdecLwiracq::handleCallIdecStop() error try-locking mutex mAccess (" << res << ")" << endl;};
	};

	res = pthread_mutex_unlock(&(xchg->datajobideclwiracq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecLwiracq::handleCallIdecStop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	// IP handleCallIdecStop --- IEND
	return retval;
};

bool JobIdecLwiracq::handleCallIdecIbitrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecIbitrdy --- IBEGIN

	if ((jref != jrefMast) && (ixVSge == VecVSge::READY)) {
		bref = refInv;
		xchg->datajobideclwiracq.gray.claim(refInv, jref);

		changeStage(dbsidec, VecVSge::PRCIDLE);
	};

	// IP handleCallIdecIbitrdy --- IEND
	return retval;
};

bool JobIdecLwiracq::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecLwiracq::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecLwiracq::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


