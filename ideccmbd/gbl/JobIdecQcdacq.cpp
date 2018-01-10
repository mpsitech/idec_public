/**
  * \file JobIdecQcdacq.cpp
  * job handler for job JobIdecQcdacq (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecQcdacq.h"

#include "JobIdecQcdacq_blks.cpp"

/******************************************************************************
 class JobIdecQcdacq
 ******************************************************************************/

JobIdecQcdacq::JobIdecQcdacq(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECQCDACQ, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	jobtrigger = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	jobtrigger = new JobIdecTrigger(xchg, dbsidec, jref, ixIdecVLocale, false);

	// IP constructor.cust2 --- IBEGIN
	bref = 0;
	seqno = 0;
	// IP constructor.cust2 --- IEND

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECTRIGQCD, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSTART, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTOP, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSPTFND, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECIBITRDY, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecQcdacq::~JobIdecQcdacq() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

void JobIdecQcdacq::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int res;

	SysIdhw*& _sysidhw = xchg->datajobprc.sysidhw;
	UntIdhwIcm2*& _icm2 = xchg->datajobidecqcdacq.icm2;

	_icm2 = NULL;
	if (!xchg->stgidecgeneral.dummy && _sysidhw) {
		if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::BASYS3FWD) _icm2 = (UntIdhwIcm2*) _sysidhw->connectToTarget(VecVSysIdhwBasys3FwdTarget::DCX3_ICM2);
		else if (xchg->stgidechardware.ixIdecVSystem == VecIdecVSystem::DSPCOMPLEX3SPI) _icm2 = (UntIdhwIcm2*) _sysidhw->connectToTarget(VecVSysIdhwDspcomplex3SpiTarget::ICM2);
	};

	xchg->datajobidecqcdacq.dummy = (_icm2 == NULL);

	/// DEMO
	xchg->datajobidecqcdacq.ixIdecVQcdste = VecIdecVQcdste::COOL;

	res = pthread_mutex_init(&(xchg->datajobidecqcdacq.mJrefsStarted), NULL);
	if (res != 0) {cout << "JobIdecQcdacq::initXchgdata() error initializing mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecqcdacq.seqno = 0;

	uint& _w = xchg->stgjobidecqcdacq.width;
	vector<double>& _a = xchg->stgjobidecqcdacq.a;
	vector<double>& _err = xchg->stgjobidecqcdacq.err;
	double& _multerr = xchg->stgjobidecqcdacq.multerr;
	double& _dS = xchg->stgjobidecqcdacq.dS;
	double& _dT = xchg->stgjobidecqcdacq.dT;
	vector<usmallint>& _iplTTvsSSx = xchg->stgjobidecqcdacq.iplTTvsSSx;
	vector<usmallint>& _iplDTdSvsSSx = xchg->stgjobidecqcdacq.iplDTdSvsSSx;

	uint ww = _w*_w;

	// initialize TTvsSS and dTDSvsSS
	if ((_a.size() != ww) || (_err.size() != ww) || (_multerr == 0.0) || (_dS == 0.0) || (_dT == 0.0) || (_iplTTvsSSx.size() == 0) || (_iplDTdSvsSSx.size() == 0)) {
		setupIplTTvsSS(xchg);
	};

	setupTTvsSS(xchg);
	setupDTdSvsSS(xchg);

	// --- dummy functionality

	// cooling / heating time constant
	xchg->datajobidecqcdacq.dTdetDt = 5.0;

	xchg->datajobidecqcdacq.Tdet0 = 25.0;
	xchg->datajobidecqcdacq.Tdet1 = 25.0;
	xchg->datajobidecqcdacq.tTdet0 = {0,0};

/* STOCK
/// content of settings block
	double& _lam0 = xchg->stgjobidecqcdacq.lam0;
	double& _dlam = xchg->stgjobidecqcdacq.dlam;
	uint& _w = xchg->stgjobidecqcdacq.width;
	double& _hpix = xchg->stgjobidecqcdacq.hpix;
	double& _dpix = xchg->stgjobidecqcdacq.dpix;

	vector<double>& _a = xchg->stgjobidecqcdacq.a;
	vector<double>& _b = xchg->stgjobidecqcdacq.b;
	vector<double>& _err = xchg->stgjobidecqcdacq.err;
	double& _multerr = xchg->stgjobidecqcdacq.multerr;
	double& _dS = xchg->stgjobidecqcdacq.dS;
	double& _dT = xchg->stgjobidecqcdacq.dT;
	vector<usmallint>& _iplTTvsSSx = xchg->stgjobidecqcdacq.iplTTvsSSx;
	vector<double>& _iplTTvsSSy = xchg->stgjobidecqcdacq.iplTTvsSSy;
	vector<usmallint>& _iplDTdSvsSSx = xchg->stgjobidecqcdacq.iplDTdSvsSSx;
	vector<double>& _iplDTdSvsSSy = xchg->stgjobidecqcdacq.iplDTdSvsSSy;
	uint& _ixIdecVSqrgrp = xchg->stgjobidecqcdacq.ixIdecVSqrgrp;

	double& _f = xchg->stgjobidecqcdacq.f;
	double& _fn = xchg->stgjobidecqcdacq.fn;
///

/// content of data block
	uint& _ixIdecVQcdste = xchg->datajobidecqcdacq.ixIdecVQcdste;

	vector<usmallint>& _TTvsSS = xchg->datajobidecqcdacq.TTvsSS;
	vector<double>& _dTdSvsSS = xchg->datajobidecqcdacq.dTdSvsSS;

	uint& _seqno = xchg->datajobidecqcdacq.seqno;

	vector<double>& _T = xchg->datajobidecqcdacq.T;
	vector<double>& _DeltaT = xchg->datajobidecqcdacq.DeltaT;
///
*/
	// IP initXchgdata --- IEND
};

void JobIdecQcdacq::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	int res;

	UntIdhwIcm2*& _icm2 = xchg->datajobidecqcdacq.icm2;

	res = pthread_mutex_destroy(&(xchg->datajobidecqcdacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecQcdacq::termXchgdata() error destroying mutex mJrefsStarted (" << res << ")" << endl;};

	if (_icm2) delete _icm2;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
double JobIdecQcdacq::getTdet() {
	double t0;

	double inv;

	timespec timestamp;
	double t;

	double& _dTdetDt = xchg->datajobidecqcdacq.dTdetDt;
	double& _Tdet0 = xchg->datajobidecqcdacq.Tdet0;
	double& _Tdet1 = xchg->datajobidecqcdacq.Tdet1;
	timespec& _tTdet0 = xchg->datajobidecqcdacq.tTdet0;

	t0 = Idec::getDoubletime(&_tTdet0);

	if (_Tdet0 < _Tdet1) inv = 1.0;
	else inv = -1.0;

	Idec::getTimestamp(&timestamp);
	t = Idec::getDoubletime(&timestamp);

	if (t <= t0) return _Tdet0;
	else if (t >= (t0 + fabs(_Tdet1-_Tdet0)/_dTdetDt)) return _Tdet1;
	else return _Tdet0 + inv * (t-t0) * _dTdetDt;
};

void JobIdecQcdacq::setTargetTdet(
			DbsIdec* dbsidec
			, const double Tdet
		) {
	double oldTdet;

	double dt;

	uint& _ixIdecVQcdste = xchg->datajobidecqcdacq.ixIdecVQcdste;
	double& _dTdetDt = xchg->datajobidecqcdacq.dTdetDt;
	double& _Tdet0 = xchg->datajobidecqcdacq.Tdet0;
	double& _Tdet1 = xchg->datajobidecqcdacq.Tdet1;
	timespec& _tTdet0 = xchg->datajobidecqcdacq.tTdet0;

	if (Tdet != _Tdet1) {
		oldTdet = getTdet();

		_Tdet0 = oldTdet;
		_Tdet1 = Tdet;

		Idec::getTimestamp(&_tTdet0);

		dt = fabs(_Tdet1-_Tdet0)/_dTdetDt;

		wrefLast = xchg->addWakeup(jref, "cool", lround(1e6*dt), false);
		_ixIdecVQcdste = VecIdecVQcdste::COOL;
		changeStage(dbsidec, VecVSge::COOL);
	};
};

void JobIdecQcdacq::refresh(
			DbsIdec* dbsidec
		) {
	bool mod = false;

	double Tdet;

	uint& _ixIdecVQcdste = xchg->datajobidecqcdacq.ixIdecVQcdste;
	double& _Tdet1 = xchg->datajobidecqcdacq.Tdet1;

	if (ixVSge == VecVSge::COOL) {
		if (_ixIdecVQcdste == VecIdecVQcdste::COOL) {
			Tdet = getTdet();
			if (Tdet == _Tdet1) {
				_ixIdecVQcdste = VecIdecVQcdste::READY;
				mod = true;
			};
		};

		if (mod) changeStage(dbsidec, VecVSge::READY);
	};
};

void JobIdecQcdacq::changeSqrgrp(
			const uint ixIdecVSqrgrp
		) {
	if (ixVSge == VecVSge::IDLE) {
		if (ixIdecVSqrgrp != xchg->stgjobidecqcdacq.ixIdecVSqrgrp) {
			xchg->stgjobidecqcdacq.ixIdecVSqrgrp = ixIdecVSqrgrp;
		};
	};
};

void JobIdecQcdacq::setupIplTTvsSS(
			XchgIdec* xchg
		) {
	double& _lam0 = xchg->stgjobidecqcdacq.lam0;
	double& _dlam = xchg->stgjobidecqcdacq.dlam;
	uint& _w = xchg->stgjobidecqcdacq.width;
	vector<double>& _a = xchg->stgjobidecqcdacq.a;
	vector<double>& _b = xchg->stgjobidecqcdacq.b;
	vector<double>& _err = xchg->stgjobidecqcdacq.err;
	double& _multerr = xchg->stgjobidecqcdacq.multerr;
	double& _dS = xchg->stgjobidecqcdacq.dS;
	double& _dT = xchg->stgjobidecqcdacq.dT;
	vector<usmallint>& _iplTTvsSSx = xchg->stgjobidecqcdacq.iplTTvsSSx;
	vector<double>& _iplTTvsSSy = xchg->stgjobidecqcdacq.iplTTvsSSy;
	vector<usmallint>& _iplDTdSvsSSx = xchg->stgjobidecqcdacq.iplDTdSvsSSx;
	vector<double>& _iplDTdSvsSSy = xchg->stgjobidecqcdacq.iplDTdSvsSSy;

	uint ww = _w*_w;

	vector<double> lut; // local version of TTvsSS with higher precision than integer-only
	vector<double>& _dTdSvsSS = xchg->datajobidecqcdacq.dTdSvsSS;

	double a, b, err;

	const double Tmax = 373.0;
	double Smax;

	double T, Tstep, S, Stest, tol;
	double TT;

	// - constant and linear mapping ADC signal -> power per area ; S = a * (x - b)

	// alternative (correct) initialization by DlgIdecCalQcdnuc

	if ((_a.size() != ww) || (_err.size() != ww) || (_multerr == 0.0)) {
		default_random_engine randgen(chrono::system_clock::now().time_since_epoch().count());
		normal_distribution<double> nrand;

		_a.resize(ww);
		_b.resize(ww);
		_err.resize(ww);

		_multerr = 1.2;

		// considering Stefan-Boltzmann law states: S = 314.06 W/m^2 (T=273K), S = 1097.6 W/m^2 (T=373K)

		// Ppix = S * (hpix/fn)^2 / 8, for S = 20 W/m^2, hpix = 75 µm and fn = 1.8, Ppix = 4.340 nW
		// U = 2 * Ppix * Resp * R * A, for Resp = 20 mA/W, R = 1e5 Ohm and A = 40000, U = 0.6944 V (wrt. Vref)
		// ADC (AD7946) range is 14Bit between 0 V and Uref = 1.65 V ; thus, x0 = 16383 * (U / Uref) + b = 6895 + b
		// b is an offset of 50mV due to modulation signal leakage ; b = 16383 * 50 mV / Uref = 496
		// up to 1024 values are added up to form a 24 Bit (per pixel) result, i.e. x = 1024 * x0 = 7568384
		// 1/a = 1024 * 16383 / Uref * A * R * Resp * 2 * (hpix/fn)^2 / 8 = 353034

		a = 1.0/353034.0;
		b = 496.0;

		// normal distribution for both a and b, corresponding to +/- 10% in pixel gain -> a, and 2mV in offset -> b
		nrand = normal_distribution<double>(a, 0.1*a);
		for (unsigned int i=0;i<ww;i++) _a[i] = nrand(randgen);

		nrand = normal_distribution<double>(b, 19.86);
		for (unsigned int i=0;i<ww;i++) _b[i] = nrand(randgen);

		// error corresponds to detector white noise multiplied with the ROIC noise figute: Un = NF * sqrt(4*k*T*R) / sqrt(tint)
		// considering S = S +/- multerr*err*sqrt(tint), need transformation to equivalent power density
		// Sn = 8 * NF * sqrt(k*T/R) * (fn/hpix)^2 / Resp / sqrt(tint), for NF = 2, T = 243 K and remainder as above, Sn = 0.0844 W/m^2/sqrt(s)
		// this translates to a minimal error in x after a maximum integration time 1.024s of Deltax = 29796 = 0x7464
		// implying that the 14 LSB's of the 24 Bit result do not carry any information and no information is lost by storing it in a usmallint

		err = 0.0844;

		// normal distribution of R +/- 10% ; use simplified error propagation DeltaSn = abs(dSn/dR) * DeltaR = Sn/(2*R) * DeltaR
		nrand = normal_distribution<double>(err, err/2.0 * 0.1);
		for (unsigned int i=0;i<ww;i++) _err[i] = nrand(randgen);
	};

	// dump a, b and err
/*
	cout << "a\tb\terr" << endl;
	for (unsigned int i=0;i<_a.size();i++) cout << _a[i] << "\t" << _b[i] << "\t" << _err[i] << endl;
*/

	// - non-linear mapping power per area -> temperature ; based on filtered blackbody radiation

	// look-up table maps power density level SS = 0 .. 65535 to temperature range TT = 0 .. 65535

	// consider temperature range up to Tmax = 373K
	Smax = Sqcd(Tmax, _lam0, _dlam, 4, 0.1, 50.0, 0.1);
	_dS = Smax / 65535.0;

	_dT = Tmax / 65535.0;

	lut.resize(65536);
	_dTdSvsSS.resize(65536);

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

				Stest = Sqcd(T, _lam0, _dlam, 4, 0.1, 50.0, 0.1);

				if (fabs(Stest-S) <= tol) break;

				if ( ((Stest > S) && (Tstep > 0.0)) || ((Stest < S) && (Tstep < 0.0)) ) Tstep = -Tstep/2.0;
			};
		};

		TT = T/_dT;
		if (TT < 0.0) TT = 0.0;
		if (TT > 65535.0) TT = 65535.0;

		lut[i] = TT;
	};

	// calculate derivative
	_dTdSvsSS[0] = fabs(_dT*(lut[1]-lut[0])/_dS);
	for (unsigned int i=1;(i+1)<lut.size();i++) _dTdSvsSS[i] = fabs(_dT*(lut[i+1]-lut[i-1])/_dS/2.0);
	_dTdSvsSS[lut.size()-1] = fabs(_dT*(lut[lut.size()-1]-lut[lut.size()-2])/_dS);
	
	// some examples for lam0=4.4µm w/ 440nm FWHM T -> (SS/TT) -> x = S/a + b = SS*dS/a + b:
	// 273K -> (2707/47965) -> 242400
	// 278K -> (3351/48844) -> 299950
	// 283K -> (4116/49722) -> 368312
	// 288K -> (5021/50601) -> 449185
	// 293K -> (6083/51479) -> 544088
	// 298K -> (7324/52358) -> 654986
	// 303K -> (8764/53236) -> 783668

	// dump lut to file
	fstream outfile;

	outfile.open("lutQcd.txt", ios::out);

	outfile << "SS\tS\tTT\tT\tS0\tdTdS" << endl;
	for (unsigned int i=0;i<lut.size();i++) {
		T = (((double) lut[i])*_dT);
		outfile << i << "\t" << (((double) i)*_dS) << "\t" << lut[i] << "\t" << T << "\t" << (sig*pow(T, 4.0)) << "\t" << _dTdSvsSS[i] << endl;
	};

	outfile.close();

	// - generate interpolations with non-uniformily spaced supporting points
	Idec::setupIpl(1.0, lut, 256, _iplTTvsSSx, _iplTTvsSSy);
	Idec::setupIpl(_dTdSvsSS[_dTdSvsSS.size()-1] / 65535.0, _dTdSvsSS, 256, _iplDTdSvsSSx, _iplDTdSvsSSy);
};

void JobIdecQcdacq::setupTTvsSS(
			XchgIdec* xchg
		) {
	vector<usmallint>& _iplTTvsSSx = xchg->stgjobidecqcdacq.iplTTvsSSx;
	vector<double>& _iplTTvsSSy = xchg->stgjobidecqcdacq.iplTTvsSSy;

	vector<usmallint>& _TTvsSS = xchg->datajobidecqcdacq.TTvsSS;

	vector<double> TTvsSS;

	// dump interpolation table
/*
	cout << "QCD interpolation table (iTT vs iSS)" << endl;
	cout << "iSS\tiTT" << endl;
	for (unsigned int i=0;i<_iplTTvsSSx.size();i++) cout << _iplTTvsSSx[i] << "\t" << _iplTTvsSSy[i] << endl;
*/

	Idec::setupFromIpl(_iplTTvsSSx, _iplTTvsSSy, 65536, TTvsSS);

	_TTvsSS.resize(65536);
	for (unsigned int i=0;i<65536;i++) _TTvsSS[i] = lround(TTvsSS[i]);
};

void JobIdecQcdacq::setupDTdSvsSS(
			XchgIdec* xchg
		) {
	vector<usmallint>& _iplDTdSvsSSx = xchg->stgjobidecqcdacq.iplDTdSvsSSx;
	vector<double>& _iplDTdSvsSSy = xchg->stgjobidecqcdacq.iplDTdSvsSSy;

	vector<double>& _dTdSvsSS = xchg->datajobidecqcdacq.dTdSvsSS;

	// dump interpolation table
/*
	cout << "QCD interpolation table (idTDS vs iSS)" << endl;
	cout << "iSS\tidTDS" << endl;
	for (unsigned int i=0;i<_iplDTdSvsSSx.size();i++) cout << _iplDTdSvsSSx[i] << "\t" << _iplDTdSvsSSy[i] << endl;
*/

	Idec::setupFromIpl(_iplDTdSvsSSx, _iplDTdSvsSSy, 65536, _dTdSvsSS);
};

inline double JobIdecQcdacq::Sqcd(
			const double T
			, const double Flam0
			, const double Fdlam
			, const unsigned int FsigN
			, const double lam0
			, const double lam1
			, const double dlam
		) {
	// integrate Gaussian-filtered blackbody radiation ; unit of return value: W/m^2

	double retval = 0.0;

	double _lam0, _lam1;

	if ((Flam0-0.5*((double) FsigN)*Fdlam) > lam0) _lam0 = Flam0-0.5*((double) FsigN)*Fdlam; else _lam0 = lam0;
	if ((Flam0+0.5*((double) FsigN)*Fdlam) < lam1) _lam1 = Flam0+0.5*((double) FsigN)*Fdlam; else _lam1 = lam1;

	for (double lam=_lam0 ; lam<=_lam1 ; lam+=dlam) {
		retval += 1e-6*dlam * (exp(-2.773 * pow(lam-Flam0, 2.0) / pow(Fdlam, 2.0))) * (2.0 * pi * h * pow(c0, 2.0) * (1.0/pow(1e-6*lam, 5.0)) * (1.0 / (exp(h*c0/((1e-6*lam)*k*T)) - 1.0)));
	};

	return retval;
};

void JobIdecQcdacq::start(
			DbsIdec* dbsidec
			, const bool fullframe
			, const usmallint pixel
			, const double tint
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecQcdacq::start() error locking mutex mAccess (" << res << ")" << endl;};

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecqcdacq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecQcdacq::start() error locking mutex mJrefsStarted (" << res << ")" << endl;};

///
		
///

		xchg->datajobidecqcdacq.jrefsStarted.insert(jref);

		res = pthread_mutex_unlock(&(xchg->datajobidecqcdacq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecQcdacq::start() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTART, jref);
	};

	if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecQcdacq::start() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecQcdacq::stop(
			DbsIdec* dbsidec
		) {
};

bool JobIdecQcdacq::started(
			const bool any
		) {
	bool retval = false;

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecqcdacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecQcdacq::started() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	if (any) retval = !xchg->datajobidecqcdacq.jrefsStarted.empty();
	else retval = (xchg->datajobidecqcdacq.jrefsStarted.find(jref) != xchg->datajobidecqcdacq.jrefsStarted.end());

	res = pthread_mutex_unlock(&(xchg->datajobidecqcdacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecQcdacq::started() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	return retval;
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecQcdacq::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::COOL: leaveSgeCool(dbsidec); break;
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
			case VecVSge::COOL: _ixVSge = enterSgeCool(dbsidec, reenter); break;
			case VecVSge::READY: _ixVSge = enterSgeReady(dbsidec, reenter); break;
			case VecVSge::ACQIDLE: _ixVSge = enterSgeAcqidle(dbsidec, reenter); break;
			case VecVSge::ACQ: _ixVSge = enterSgeAcq(dbsidec, reenter); break;
			case VecVSge::PRC: _ixVSge = enterSgePrc(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint JobIdecQcdacq::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void JobIdecQcdacq::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint JobIdecQcdacq::enterSgeCool(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::COOL;
	nextIxVSge = VecVSge::READY;
	// IP enterSgeCool --- INSERT
	retval = nextIxVSge;
	return retval;
};

void JobIdecQcdacq::leaveSgeCool(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgeCool --- INSERT
};

uint JobIdecQcdacq::enterSgeReady(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::READY;
	nextIxVSge = retval;
	// IP enterSgeReady --- INSERT
	return retval;
};

void JobIdecQcdacq::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecQcdacq::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecQcdacq::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecQcdacq::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- INSERT
	return retval;
};

void JobIdecQcdacq::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecQcdacq::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- INSERT
	return retval;
};

void JobIdecQcdacq::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecQcdacq::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecQcdacq::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecQcdacq::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecQcdacq::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecQcdacq::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecQcdacq::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecQcdacq::handleRequest(
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

void JobIdecQcdacq::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if ((ixVSge == VecVSge::COOL) && (sref == "cool")) {
		// IP handleTimer.cool --- INSERT
	} else if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};

void JobIdecQcdacq::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECTRIGQCD) {
		call->abort = handleCallIdecTrigQcd(dbsidec, call->jref, call->argInv.intval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTART) {
		call->abort = handleCallIdecStart(dbsidec, call->jref, call->argInv.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTOP) {
		call->abort = handleCallIdecStop(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSPTFND) {
		call->abort = handleCallIdecSptfnd(dbsidec, call->jref, call->argInv.boolval);
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

bool JobIdecQcdacq::handleCallIdecTrigQcd(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigQcd --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecStart(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecStart --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecStop(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStop --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecSptfnd(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecSptfnd --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecIbitrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecIbitrdy --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecQcdacq::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


