/**
  * \file JobIdecFusion.cpp
  * job handler for job JobIdecFusion (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecFusion.h"

#include "JobIdecFusion_blks.cpp"

/******************************************************************************
 class JobIdecFusion
 ******************************************************************************/

JobIdecFusion::JobIdecFusion(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECFUSION, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	joblwiracq = NULL;
	jobvislacq = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, false);
	jobvislacq = new JobIdecVislacq(xchg, dbsidec, jref, ixIdecVLocale, false);

	// IP constructor.cust2 --- IBEGIN
	bref = 0;
	seqno = 0;
	timestamp = {0,0};
	// IP constructor.cust2 --- IEND

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECSTART, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTOP, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECIMGRDY, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECIBITRDY, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecFusion::~JobIdecFusion() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- IBEGIN
	if (ixVSge == VecVSge::READY) changeStage(NULL, VecVSge::IDLE);

	xchg->datajobidecfusion.rgb.releaseByJref(jref);
	// IP destructor.cust --- IEND

	xchg->removeJobByJref(jref);
};

void JobIdecFusion::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int res;
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	res = pthread_mutex_init(&(xchg->datajobidecfusion.mJrefsStarted), &attr);
	if (res != 0) {cout << "JobIdecFusion::initXchgdata() error initializing mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecfusion.seqno = 0;

	xchg->datajobidecfusion.lwirgray = NULL;
	xchg->datajobidecfusion.vislred = NULL;
	xchg->datajobidecfusion.vislgreen = NULL;
	xchg->datajobidecfusion.vislblue = NULL;
	// IP initXchgdata --- IEND
};

void JobIdecFusion::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	int res;

	res = pthread_mutex_destroy(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::termXchgdata() error destroying mutex mJrefsStarted (" << res << ")" << endl;};

	if (xchg->datajobidecfusion.lwirgray) delete xchg->datajobidecfusion.lwirgray;
	if (xchg->datajobidecfusion.vislred) delete xchg->datajobidecfusion.vislred;
	if (xchg->datajobidecfusion.vislgreen) delete xchg->datajobidecfusion.vislgreen;
	if (xchg->datajobidecfusion.vislblue) delete xchg->datajobidecfusion.vislblue;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
// exact copy from Idec.cpp but inline
inline unsigned int JobIdecFusion::intavg(
			const unsigned int in
			, const unsigned int im
			, bool* rshs
			, const unsigned int rshsN
		) {
	unsigned int retval = im*in;

	for (unsigned int i=0;i<rshsN;i++) if (rshs[i]) retval += (in >> (i+1));

	return retval;
};

void JobIdecFusion::start(
			DbsIdec* dbsidec
			, vector<Snippet*> _snippets
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecFusion::start() error locking mutex mAccess (" << res << ")" << endl;};

	snippets = _snippets;

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecfusion.mJrefsStarted));
		if (res != 0) {cout << "JobIdecFusion::start() error locking mutex mJrefsStarted (" << res << ")" << endl;};

		xchg->datajobidecfusion.jrefsStarted.insert(jref);

		res = pthread_mutex_unlock(&(xchg->datajobidecfusion.mJrefsStarted));
		if (res != 0) {cout << "JobIdecFusion::start() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTART, jref);
	};

	if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecFusion::start() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecFusion::stop(
			DbsIdec* dbsidec
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecFusion::stop() error locking mutex mAccess (" << res << ")" << endl;};

	snippets.clear();

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecfusion.mJrefsStarted));
		if (res != 0) {cout << "JobIdecFusion::stop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
		xchg->datajobidecfusion.jrefsStarted.erase(jref);
		if (xchg->datajobidecfusion.jrefsStarted.empty() && (ixVSge == VecVSge::READY)) changeStage(dbsidec, VecVSge::IDLE);

		res = pthread_mutex_unlock(&(xchg->datajobidecfusion.mJrefsStarted));
		if (res != 0) {cout << "JobIdecFusion::stop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTOP, jref);
		if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecFusion::stop() error unlocking mutex mAccess (" << res << ")" << endl;};
};

bool JobIdecFusion::started(
			const bool any
		) {
	bool retval = false;

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::started() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	if (any) retval = !xchg->datajobidecfusion.jrefsStarted.empty();
	else retval = (xchg->datajobidecfusion.jrefsStarted.find(jref) != xchg->datajobidecfusion.jrefsStarted.end());

	res = pthread_mutex_unlock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::started() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	return retval;
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecFusion::changeStage(
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

uint JobIdecFusion::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- IBEGIN

	if (jref == jrefMast) {
		// stop acquisition sub-jobs
		joblwiracq->stop(dbsidec);
		jobvislacq->stop(dbsidec);
	};

	xchg->datajobidecfusion.rgb.releaseByJref(jref);

	// IP enterSgeIdle --- IEND
	return retval;
};

void JobIdecFusion::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- IBEGIN
	unsigned int& _lwirw = xchg->stgjobideclwiracq.width;
	unsigned int& _lwirh = xchg->stgjobideclwiracq.height;

	unsigned int& _vislw = xchg->stgjobidecvislacq.width;
	unsigned int& _vislh = xchg->stgjobidecvislacq.height;

	unsigned int& _seqno = xchg->datajobidecfusion.seqno;
	Snippet*& _lwirgray = xchg->datajobidecfusion.lwirgray;
	Snippet*& _vislred = xchg->datajobidecfusion.vislred;
	Snippet*& _vislgreen = xchg->datajobidecfusion.vislgreen;
	Snippet*& _vislblue = xchg->datajobidecfusion.vislblue;
	Imgbuf& _rgb = xchg->datajobidecfusion.rgb;

	if (jref == jrefMast) {
		_seqno = 0;
	
		if (_lwirgray) {
			if ((_vislred->w != _vislw) || (_vislred->h != _vislh)) {
				delete _lwirgray; _lwirgray = NULL;
				delete _vislred; _vislred = NULL;
				delete _vislgreen; _vislgreen = NULL;
				delete _vislblue; _vislblue = NULL;
				_rgb.term();
			};
		};
	
		if (!_lwirgray) {
			_lwirgray = new Snippet(VecIdecVCamres::MAX, VecIdecVChannel::GRAY16, _lwirw, _lwirh);
			_vislred = new Snippet(VecIdecVCamres::MAX, VecIdecVChannel::RED8, _vislw, _vislh);
			_vislgreen = new Snippet(VecIdecVCamres::MAX, VecIdecVChannel::GREEN8, _vislw, _vislh);
			_vislblue = new Snippet(VecIdecVCamres::MAX, VecIdecVChannel::BLUE8, _vislw, _vislh);
			_rgb.init(8, 3*_vislw*_vislh*1);
		};

		// start acquisition sub-jobs
		joblwiracq->start(dbsidec, {_lwirgray});
		jobvislacq->start(dbsidec, {_vislred,_vislgreen,_vislblue});
	};

	bref = 0;
	seqno = 0;
	timestamp = {0,0};
	// IP leaveSgeIdle --- IEND
};

uint JobIdecFusion::enterSgeReady(
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

void JobIdecFusion::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecFusion::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecFusion::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecFusion::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- IBEGIN

	// should only be invoked as master: fuse together snippets from LWIR and VIS-L
	int res;

	bool valid;

	unsigned int& _lwirw = xchg->stgjobideclwiracq.width;
	unsigned int& _lwirh = xchg->stgjobideclwiracq.height;

	unsigned int& _vislw = xchg->stgjobidecvislacq.width;
	unsigned int& _vislh = xchg->stgjobidecvislacq.height;

	unsigned int& _seqno = xchg->datajobidecfusion.seqno;
	Snippet*& _lwirgray = xchg->datajobidecfusion.lwirgray;
	Snippet*& _vislred = xchg->datajobidecfusion.vislred;
	Snippet*& _vislgreen = xchg->datajobidecfusion.vislgreen;
	Snippet*& _vislblue = xchg->datajobidecfusion.vislblue;
	Imgbuf& _rgb = xchg->datajobidecfusion.rgb;

	Imgbufitem* ibit = NULL;

	utinyint* _r = NULL;
	utinyint* _g = NULL;
	utinyint* _b = NULL;

	unsigned int x0, y0;
	unsigned int ix, ix2;

	valid = true;

	res = pthread_mutex_lock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::enterSgeAcq() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	bref = 0;

	if (valid) {
		// obtain available slot in _rgb
		bref = _rgb.getNewItem(jref, _seqno, {0,0}); // seqno from trigger, timestamp generated at this time
		valid = (bref != 0);
	};

	if (valid) {
		ibit = _rgb.getItem(bref);

		_r = ibit->data;
		_g = &(ibit->data[_vislw*_vislh]);
		_b = &(ibit->data[2*_vislw*_vislh]);

		// straight copy from VIS-L image
		memcpy((void*) _r, (void*) (_vislred->data), _vislw*_vislh);
		memcpy((void*) _g, (void*) (_vislgreen->data), _vislw*_vislh);
		memcpy((void*) _b, (void*) (_vislblue->data), _vislw*_vislh);

		if ((_lwirw < _vislw) && (_lwirh < _vislh)) {
			// LWIR image inset (requires GRAY16 to RGB8 transform)
			x0 = (_vislw-_lwirw)/2;
			y0 = (_vislh-_lwirh)/2;

			for (unsigned int i=0;i<_lwirh;i++) {
				for (unsigned int j=0;j<_lwirw;j++) {
					ix = i*_lwirw+j;
					ix2 = (y0+i)*_vislw + x0+j;

					_r[ix2] = ((unsigned short*) (_lwirgray->data))[ix] >> 8;
					_g[ix2] = _r[ix2];
					_b[ix2] = _r[ix2];
				};
			};
		};

		// spread the news
		xchg->triggerRefCall(dbsidec, VecIdecVCall::CALLIDECIBITRDY, jref, bref);

		if (!started()) retval = VecVSge::READY;
		else retval = VecVSge::PRC;

	} else {
		retval = VecVSge::READY;
	};

	res = pthread_mutex_unlock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::enterSgeAcq() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	_lwirgray->release();
	_vislred->release();
	_vislgreen->release();
	_vislblue->release();

	if ((bref != 0) && (retval != VecVSge::PRC)) _rgb.release(bref, jref);

	// IP enterSgeAcq --- IEND
	return retval;
};

void JobIdecFusion::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecFusion::enterSgePrcidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRCIDLE;
	nextIxVSge = VecVSge::PRC;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgePrcidle --- INSERT
	return retval;
};

void JobIdecFusion::leaveSgePrcidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrcidle --- INSERT
};

uint JobIdecFusion::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- IBEGIN

	bool valid;

	unsigned int& _w = xchg->stgjobidecvislacq.width;
	unsigned int& _h = xchg->stgjobidecvislacq.height;

	Imgbuf& _rgb = xchg->datajobidecfusion.rgb;

	Imgbufitem* ibit = NULL;

	utinyint* _r = NULL;
	utinyint* _g = NULL;
	utinyint* _b = NULL;
	utinyint* src = NULL;

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

	ibit = _rgb.getItem(bref);
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

		_r = ibit->data;
		_g = &(ibit->data[_w*_h]);
		_b = &(ibit->data[2*_w*_h]);

		for (unsigned int m=0;m<snippets.size();m++) {
			snippet = snippets[m];

			if (snippet->ixIdecVChannel == VecIdecVChannel::RED8) src = _r;
			else if (snippet->ixIdecVChannel == VecIdecVChannel::GREEN8) src = _g;
			else if (snippet->ixIdecVChannel == VecIdecVChannel::BLUE8) src = _b;

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

			// border to the right
			if (cpyw < snippet->w) for (unsigned int i=0;i<cpyh;i++) memset((void*) &(snippet->data[i*snippet->w+cpyw]), 127, snippet->w-cpyw);

			// border below
			if (cpyh < snippet->h) memset((void*) &(snippet->data[snippet->w*cpyh]), 127, snippet->w*(snippet->h-cpyh));

			if ((mult == 1) && (cpyw == _w) && (cpyh == _h)) {
				// straight copy in case of exact overlap
				if ((snippet->ixIdecVChannel == VecIdecVChannel::RED8) || (snippet->ixIdecVChannel == VecIdecVChannel::GREEN8) || (snippet->ixIdecVChannel == VecIdecVChannel::BLUE8)) {
					memcpy(snippet->data, src, wh);
				};

			} else {
				if ((snippet->ixIdecVChannel == VecIdecVChannel::RED8) || (snippet->ixIdecVChannel == VecIdecVChannel::GREEN8) || (snippet->ixIdecVChannel == VecIdecVChannel::BLUE8)) {
					rshsN = 16;
					Idec::setupIntavg(mult*mult, 255, 255, 0.999, im, rshs, rshsN);

					for (unsigned int i=0;i<cpyh;i++) {
						for (unsigned int j=0;j<cpyw;j++) {
							sum = 0;

							for (unsigned int k=0;k<mult;k++) {
								for (unsigned int l=0;l<mult;l++) {
									ix = (y0+mult*i+k)*_w + (x0+mult*j+l);

									sum += src[ix];
								};
							};

							snippet->data[i*snippet->w+j] = intavg(sum, im, rshs, rshsN);
						};
					};
				};
			};

			snippet->release();
		};

		if (snippets.size() > 0) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECIMGRDY, jref);
	};

	if (ibit) _rgb.release(bref, jref);

	retval = VecVSge::READY;

	// IP enterSgePrc --- IEND
	return retval;
};

void JobIdecFusion::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecFusion::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecFusion::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecFusion::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecFusion::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecFusion::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecFusion::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecFusion::handleRequest(
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

void JobIdecFusion::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if (ixVSge == VecVSge::PRCIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};

void JobIdecFusion::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTART) {
		call->abort = handleCallIdecStart(dbsidec, call->jref, call->argInv.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTOP) {
		call->abort = handleCallIdecStop(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECIMGRDY) {
		call->abort = handleCallIdecImgrdy(dbsidec, call->jref);
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

bool JobIdecFusion::handleCallIdecStart(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecStart --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::handleCallIdecStart() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecfusion.jrefsStarted.insert(jrefTrig);

	res = pthread_mutex_unlock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::handleCallIdecStart() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	res = pthread_mutex_trylock(&mAccess);

	if (res == 0) {
		if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "JobIdecFusion::handleCallIdecStart() error unlocking mutex mAccess (" << res << ")" << endl;};

	} else if (res != EBUSY) {cout << "JobIdecFusion::handleCallIdecStart() error try-locking mutex mAccess (" << res << ")" << endl;};

	// IP handleCallIdecStart --- IEND
	return retval;
};

bool JobIdecFusion::handleCallIdecStop(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStop --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::handleCallIdecStop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
	xchg->datajobidecfusion.jrefsStarted.erase(jrefTrig);

	if (xchg->datajobidecfusion.jrefsStarted.empty()) {
		res = pthread_mutex_trylock(&mAccess);

		if (res == 0) {
			if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);

			res = pthread_mutex_unlock(&mAccess);
			if (res != 0) {cout << "JobIdecFusion::handleCallIdecStop() error unlocking mutex mAccess (" << res << ")" << endl;};

		} else if (res != EBUSY) {cout << "JobIdecFusion::handleCallIdecStop() error try-locking mutex mAccess (" << res << ")" << endl;};
	};

	res = pthread_mutex_unlock(&(xchg->datajobidecfusion.mJrefsStarted));
	if (res != 0) {cout << "JobIdecFusion::handleCallIdecStop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	// IP handleCallIdecStop --- IEND
	return retval;
};

bool JobIdecFusion::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- IBEGIN

	Snippet*& _lwirgray = xchg->datajobidecfusion.lwirgray;
	Snippet*& _vislred = xchg->datajobidecfusion.vislred;
	Snippet*& _vislgreen = xchg->datajobidecfusion.vislgreen;
	Snippet*& _vislblue = xchg->datajobidecfusion.vislblue;

	if (ixVSge == VecVSge::READY) {
		if (jrefTrig == joblwiracq->jref) {
			_lwirgray->claim(jref);
		} else if (jrefTrig == jobvislacq->jref) {
			_vislred->claim(jref);
			_vislgreen->claim(jref);
			_vislblue->claim(jref);
		};

		if ((_lwirgray->jrefClaim == jref) && (_vislred->jrefClaim == jref)) changeStage(dbsidec, VecVSge::ACQIDLE);
	};

	// IP handleCallIdecImgrdy --- IEND
	return retval;
};

bool JobIdecFusion::handleCallIdecIbitrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecIbitrdy --- IBEGIN

	if ((jref != jrefMast) && (ixVSge == VecVSge::READY)) {
		bref = refInv;
		xchg->datajobidecfusion.rgb.claim(refInv, jref);

		changeStage(dbsidec, VecVSge::PRCIDLE);
	};

	// IP handleCallIdecIbitrdy --- IEND
	return retval;
};

bool JobIdecFusion::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecFusion::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecFusion::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


