/**
  * \file JobIdecStereo.cpp
  * job handler for job JobIdecStereo (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecStereo.h"

#include "JobIdecStereo_blks.cpp"

/******************************************************************************
 class JobIdecStereo
 ******************************************************************************/

JobIdecStereo::JobIdecStereo(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECSTEREO, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	jobvislacq = NULL;
	jobvisracq = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	jobvislacq = new JobIdecVislacq(xchg, dbsidec, jref, ixIdecVLocale, false);
	jobvisracq = new JobIdecVisracq(xchg, dbsidec, jref, ixIdecVLocale, false);

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

JobIdecStereo::~JobIdecStereo() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- IBEGIN
	if (ixVSge == VecVSge::READY) changeStage(NULL, VecVSge::IDLE);

	xchg->datajobidecstereo.depth.releaseByJref(jref);
	// IP destructor.cust --- IEND

	xchg->removeJobByJref(jref);
};

void JobIdecStereo::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int res;
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	res = pthread_mutex_init(&(xchg->datajobidecstereo.mJrefsStarted), &attr);
	if (res != 0) {cout << "JobIdecStereo::initXchgdata() error initializing mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecstereo.seqno = 0;

	xchg->datajobidecstereo.vislgray = NULL;
	xchg->datajobidecstereo.visrgray = NULL;
	// IP initXchgdata --- IEND
};

void JobIdecStereo::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	int res;

	res = pthread_mutex_destroy(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::termXchgdata() error destroying mutex mJrefsStarted (" << res << ")" << endl;};

	if (xchg->datajobidecstereo.vislgray) delete xchg->datajobidecstereo.vislgray;
	if (xchg->datajobidecstereo.visrgray) delete xchg->datajobidecstereo.visrgray;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
void JobIdecStereo::start(
			DbsIdec* dbsidec
			, vector<Snippet*> _snippets
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecStereo::start() error locking mutex mAccess (" << res << ")" << endl;};

	snippets = _snippets;

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecstereo.mJrefsStarted));
		if (res != 0) {cout << "JobIdecStereo::start() error locking mutex mJrefsStarted (" << res << ")" << endl;};

		xchg->datajobidecstereo.jrefsStarted.insert(jref);

		res = pthread_mutex_unlock(&(xchg->datajobidecstereo.mJrefsStarted));
		if (res != 0) {cout << "JobIdecStereo::start() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTART, jref);
	};

	if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecStereo::start() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecStereo::stop(
			DbsIdec* dbsidec
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecStereo::stop() error locking mutex mAccess (" << res << ")" << endl;};

	snippets.clear();

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecstereo.mJrefsStarted));
		if (res != 0) {cout << "JobIdecStereo::stop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
		xchg->datajobidecstereo.jrefsStarted.erase(jref);
		if (xchg->datajobidecstereo.jrefsStarted.empty() && (ixVSge == VecVSge::READY)) changeStage(dbsidec, VecVSge::IDLE);

		res = pthread_mutex_unlock(&(xchg->datajobidecstereo.mJrefsStarted));
		if (res != 0) {cout << "JobIdecStereo::stop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTOP, jref);
		if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecStereo::stop() error unlocking mutex mAccess (" << res << ")" << endl;};
};

bool JobIdecStereo::started(
			const bool any
		) {
	bool retval = false;

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::started() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	if (any) retval = !xchg->datajobidecstereo.jrefsStarted.empty();
	else retval = (xchg->datajobidecstereo.jrefsStarted.find(jref) != xchg->datajobidecstereo.jrefsStarted.end());

	res = pthread_mutex_unlock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::started() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	return retval;
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecStereo::changeStage(
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

uint JobIdecStereo::enterSgeIdle(
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

	xchg->datajobidecstereo.depth.releaseByJref(jref);

	// IP enterSgeIdle --- IEND
	return retval;
};

void JobIdecStereo::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- IBEGIN

	unsigned int& _seqno = xchg->datajobidecstereo.seqno;
	Snippet*& _vislgray = xchg->datajobidecstereo.vislgray;
	Snippet*& _visrgray = xchg->datajobidecstereo.visrgray;
	Imgbuf& _depth = xchg->datajobidecstereo.depth;

	if (jref == jrefMast) {
		_seqno = 0;
	
		if (!_vislgray) {
			_vislgray = new Snippet(VecIdecVCamres::_640, VecIdecVChannel::GRAY16);
			_visrgray = new Snippet(VecIdecVCamres::_640, VecIdecVChannel::GRAY16);
			_depth.init(4, 640*480*4);
		};

		// start acquisition sub-jobs
		jobvislacq->start(dbsidec, {_vislgray});
		jobvisracq->start(dbsidec, {_visrgray});
	};

	bref = 0;
	seqno = 0;
	timestamp = {0,0};

	// IP leaveSgeIdle --- IEND
};

uint JobIdecStereo::enterSgeReady(
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

void JobIdecStereo::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecStereo::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecStereo::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecStereo::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- IBEGIN

	// should only be invoked as master: overlay snippets from VIS-L and VIS-R
	int res;

	bool valid;

	unsigned int& _seqno = xchg->datajobidecstereo.seqno;
	Snippet*& _vislgray = xchg->datajobidecstereo.vislgray;
	Snippet*& _visrgray = xchg->datajobidecstereo.visrgray;
	Imgbuf& _depth = xchg->datajobidecstereo.depth;

	Imgbufitem* ibit = NULL;

	unsigned short* _l;
	unsigned short* _r;

	float* _f;

	valid = true;

	res = pthread_mutex_lock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::enterSgeAcq() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	bref = 0;

	if (valid) {
		// obtain available slot in _depth
		bref = _depth.getNewItem(jref, _seqno, {0,0}); // seqno from trigger, timestamp generated at this time
		valid = (bref != 0);
	};

	if (valid) {
		ibit = _depth.getItem(bref);

		_l = (unsigned short*) _vislgray->data;
		_r = (unsigned short*) _visrgray->data;

		_f = (float*) ibit->data;

		// 50:50 overlay of VIS-L and VIS-R scaled to 100.0
		for (unsigned int i=0;i<(640*480);i++) {
			_f[i] = (float) _l[i];
			_f[i] += (float) _r[i];
			_f[i] *= 100.0/131070.0;
		};

		// spread the news
		xchg->triggerRefCall(dbsidec, VecIdecVCall::CALLIDECIBITRDY, jref, bref);

		if (!started()) retval = VecVSge::READY;
		else retval = VecVSge::PRC;

	} else {
		retval = VecVSge::READY;
	};

	res = pthread_mutex_unlock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::enterSgeAcq() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	_vislgray->release();
	_visrgray->release();

	if ((bref != 0) && (retval != VecVSge::PRC)) _depth.release(bref, jref);

	// IP enterSgeAcq --- IEND
	return retval;
};

void JobIdecStereo::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecStereo::enterSgePrcidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRCIDLE;
	nextIxVSge = VecVSge::PRC;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgePrcidle --- INSERT
	return retval;
};

void JobIdecStereo::leaveSgePrcidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrcidle --- INSERT
};

uint JobIdecStereo::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- IBEGIN

	bool valid;

	Imgbuf& _depth = xchg->datajobidecstereo.depth;

	Imgbufitem* ibit = NULL;

	Snippet* snippet = NULL;

	unsigned int w, h, wh;

	unsigned int mult;

	unsigned int x0, y0;

	unsigned int cpyw, cpyh;

	float sum;

	float fm;

	unsigned int ix;

	ibit = _depth.getItem(bref);
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

		for (unsigned int m=0;m<snippets.size();m++) {
			snippet = snippets[m];

			// determine integer scaling factor
			Idec::getCamresWh(snippet->ixIdecVCamres, w, h, 640, 480);
			wh = w*h;

			mult = 1;
			while (((mult*w+16) < 640) && ((mult*h+12) < 480)) mult++;

			// - padding in coordinates of (non-scaled) raw image
			x0 = snippet->x0*mult;
			y0 = snippet->y0*mult;

			cpyw = snippet->w;
			cpyh = snippet->h;

			if ((x0 + mult*cpyw) > 640) cpyw = (640-x0)/mult;
			if ((y0 + mult*cpyh) > 480) cpyh = (480-y0)/mult;

			// border to the right
			if (cpyw < snippet->w) for (unsigned int i=0;i<cpyh;i++) memset((void*) &(snippet->data[4*(i*snippet->w+cpyw)]), 0, 4*(snippet->w-cpyw));

			// border below
			if (cpyh < snippet->h) memset((void*) &(snippet->data[4*(snippet->w*cpyh)]), 0, 4*(snippet->w*(snippet->h-cpyh)));

			if ((mult == 1) && (cpyw == 640) && (cpyh == 480)) {
				// straight copy in case of exact overlap
				if (snippet->ixIdecVChannel == VecIdecVChannel::DEPTHSP) memcpy(snippet->data, ibit->data, 4*wh);

			} else {
				if (snippet->ixIdecVChannel == VecIdecVChannel::DEPTHSP) {
					fm = 1.0/((float) mult)/((float) mult);

					for (unsigned int i=0;i<cpyh;i++) {
						for (unsigned int j=0;j<cpyw;j++) {
							sum = 0.0;

							for (unsigned int k=0;k<mult;k++) {
								for (unsigned int l=0;l<mult;l++) {
									ix = (y0+mult*i+k)*640 + (x0+mult*j+l);

									sum += ((float*) ibit->data)[ix];
								};
							};

							((float*) snippet->data)[i*snippet->w+j] = fm*sum;
						};
					};
				};
			};

			snippet->release();
		};

		if (snippets.size() > 0) xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECIMGRDY, jref);
	};

	if (ibit) _depth.release(bref, jref);

	retval = VecVSge::READY;

	// IP enterSgePrc --- IEND
	return retval;
};

void JobIdecStereo::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecStereo::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecStereo::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecStereo::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecStereo::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecStereo::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecStereo::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN

	retval = true;

	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecStereo::handleRequest(
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

void JobIdecStereo::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if (ixVSge == VecVSge::PRCIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};

void JobIdecStereo::handleCall(
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

bool JobIdecStereo::handleCallIdecStart(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecStart --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::handleCallIdecStart() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecstereo.jrefsStarted.insert(jrefTrig);

	res = pthread_mutex_unlock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::handleCallIdecStart() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	res = pthread_mutex_trylock(&mAccess);

	if (res == 0) {
		if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "JobIdecStereo::handleCallIdecStart() error unlocking mutex mAccess (" << res << ")" << endl;};

	} else if (res != EBUSY) {cout << "JobIdecStereo::handleCallIdecStart() error try-locking mutex mAccess (" << res << ")" << endl;};

	// IP handleCallIdecStart --- IEND
	return retval;
};

bool JobIdecStereo::handleCallIdecStop(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStop --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::handleCallIdecStop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
	xchg->datajobidecstereo.jrefsStarted.erase(jrefTrig);

	if (xchg->datajobidecstereo.jrefsStarted.empty()) {
		res = pthread_mutex_trylock(&mAccess);

		if (res == 0) {
			if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);

			res = pthread_mutex_unlock(&mAccess);
			if (res != 0) {cout << "JobIdecStereo::handleCallIdecStop() error unlocking mutex mAccess (" << res << ")" << endl;};

		} else if (res != EBUSY) {cout << "JobIdecStereo::handleCallIdecStop() error try-locking mutex mAccess (" << res << ")" << endl;};
	};

	res = pthread_mutex_unlock(&(xchg->datajobidecstereo.mJrefsStarted));
	if (res != 0) {cout << "JobIdecStereo::handleCallIdecStop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	// IP handleCallIdecStop --- IEND
	return retval;
};

bool JobIdecStereo::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- IBEGIN

	Snippet*& _vislgray = xchg->datajobidecstereo.vislgray;
	Snippet*& _visrgray = xchg->datajobidecstereo.visrgray;

	if (ixVSge == VecVSge::READY) {
		if (jrefTrig == jobvislacq->jref) {
			_vislgray->claim(jref);
		} else if (jrefTrig == jobvisracq->jref) {
			_visrgray->claim(jref);
		};

		if ((_vislgray->jrefClaim == jref) && (_visrgray->jrefClaim == jref)) changeStage(dbsidec, VecVSge::ACQIDLE);
	};

	// IP handleCallIdecImgrdy --- IEND
	return retval;
};

bool JobIdecStereo::handleCallIdecIbitrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecIbitrdy --- IBEGIN

	if ((jref != jrefMast) && (ixVSge == VecVSge::READY)) {
		bref = refInv;
		xchg->datajobidecstereo.depth.claim(refInv, jref);

		changeStage(dbsidec, VecVSge::PRCIDLE);
	};

	// IP handleCallIdecIbitrdy --- IEND
	return retval;
};

bool JobIdecStereo::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecStereo::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecStereo::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


