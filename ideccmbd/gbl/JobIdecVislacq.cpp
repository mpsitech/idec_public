/**
  * \file JobIdecVislacq.cpp
  * job handler for job JobIdecVislacq (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "JobIdecVislacq.h"

#include "JobIdecVislacq_blks.cpp"

/******************************************************************************
 class JobIdecVislacq
 ******************************************************************************/

JobIdecVislacq::JobIdecVislacq(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const bool prefmast
		) : JobIdec(xchg, VecIdecVJob::JOBIDECVISLACQ, jrefSup, ixIdecVLocale, prefmast) {

	jref = xchg->addJob(dbsidec, this);

	jobtrigger = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.spec1 --- INSERT

	jobtrigger = new JobIdecTrigger(xchg, dbsidec, jref, ixIdecVLocale, false);

	// IP constructor.cust2 --- IBEGIN
#ifdef __linux__
	camfile = 0;
	buf = {};
	cammmap = NULL;
#endif

	bref = 0;
	seqno = 0;
	timestamp = {0,0};
	// IP constructor.cust2 --- IEND

	// IP constructor.spec2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECTRIGVISL, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSTART, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTOP, jref, Clstn::VecVJobmask::SLV, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECIBITRDY, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::MAST, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

JobIdecVislacq::~JobIdecVislacq() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- IBEGIN
	if (ixVSge == VecVSge::READY) changeStage(NULL, VecVSge::IDLE);

	xchg->datajobidecvislacq.rgb.releaseByJref(jref);
	// IP destructor.cust --- IEND

	xchg->removeJobByJref(jref);
};

void JobIdecVislacq::initXchgdata(
			XchgIdec* xchg
		) {
	// IP initXchgdata --- IBEGIN
	int res;
	pthread_mutexattr_t attr;

	xchg->datajobidecvislacq.dummy = false;

	xchg->datajobidecvislacq.ixIdecVCamste = VecIdecVCamste::NC;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	res = pthread_mutex_init(&(xchg->datajobidecvislacq.mJrefsStarted), &attr);
	if (res != 0) {cout << "JobIdecVislacq::initXchgdata() error initializing mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecvislacq.seqno = 0;

	xchg->datajobidecvislacq.red0 = NULL;
	xchg->datajobidecvislacq.green0 = NULL;
	xchg->datajobidecvislacq.blue0 = NULL;

	xchg->datajobidecvislacq.testpat = NULL;
	// IP initXchgdata --- IEND
};

void JobIdecVislacq::termXchgdata(
			XchgIdec* xchg
		) {
	// IP termXchgdata --- IBEGIN
	int res;

	res = pthread_mutex_destroy(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::termXchgdata() error destroying mutex mJrefsStarted (" << res << ")" << endl;};

	if (xchg->datajobidecvislacq.red0) delete[] xchg->datajobidecvislacq.red0;
	if (xchg->datajobidecvislacq.green0) delete[] xchg->datajobidecvislacq.green0;
	if (xchg->datajobidecvislacq.blue0) delete[] xchg->datajobidecvislacq.blue0;

	if (xchg->datajobidecvislacq.testpat) delete xchg->datajobidecvislacq.testpat;
	// IP termXchgdata --- IEND
};

// IP cust --- IBEGIN
void JobIdecVislacq::changeCamtype(
			const uint ixIdecVCamtype
		) {
	uint& _ixIdecVCamtype = xchg->stgjobidecvislacq.ixIdecVCamtype;
	uint& _width = xchg->stgjobidecvislacq.width;
	uint& _height = xchg->stgjobidecvislacq.height;
	double& _hpix = xchg->stgjobidecvislacq.hpix;
	double& _f = xchg->stgjobidecvislacq.f;
	double& _fn = xchg->stgjobidecvislacq.fn;

	unsigned char*& _red0 = xchg->datajobidecvislacq.red0;
	unsigned char*& _green0 = xchg->datajobidecvislacq.green0;
	unsigned char*& _blue0 = xchg->datajobidecvislacq.blue0;
	Imgbuf& _rgb = xchg->datajobidecvislacq.rgb;

	if (ixVSge == VecVSge::IDLE) {
		if (_ixIdecVCamtype != ixIdecVCamtype) {
			_ixIdecVCamtype = ixIdecVCamtype;

			if (ixIdecVCamtype == VecIdecVCamtype::PGCMLN) {
				_width = 1296;
				_height = 964;
				_hpix = 3.75;
				_f = 4.2;
				_fn = 1.6;
			} else if (ixIdecVCamtype == VecIdecVCamtype::MSLIFE) {
				_width = 1280;
				_height = 720;
				_hpix = 3.0;
				_f = 3.0;
				_fn = 2.0;
			};

			if (_red0) {
				delete[] _red0; _red0 = NULL;
				delete[] _green0; _green0 = NULL;
				delete[] _blue0; _blue0 = NULL;
				_rgb.term();
			};
		};
	};
};

void JobIdecVislacq::changeSqrgrp(
			const uint ixIdecVSqrgrp
		) {
	if (ixVSge == VecVSge::IDLE) {
		if (ixIdecVSqrgrp != xchg->stgjobidecvislacq.ixIdecVSqrgrp) {
			xchg->stgjobidecvislacq.ixIdecVSqrgrp = ixIdecVSqrgrp;
		};
	};
};

bool JobIdecVislacq::openFlycap() {
#ifdef __linux__
	int res;

	bool valid;

	BusManager busmgr;

	PGRGuid guid;

	Format7Info fmt7info;
	bool fmt7ok;

	Format7ImageSettings fmt7stgs;
	Format7PacketInfo fmt7pkginf;

	res = pthread_mutex_lock(&(xchg->datajobprc.mFlycap));
	if (res != 0) {cout << "JobIdecVislacq::openFlycap() error locking mutex xchg->datajobprc.mFlycap (" << res << ")" << endl;};

	valid = (busmgr.GetCameraFromSerialNumber(atoll(xchg->stgjobidecvislacq.serno.c_str()), &guid) == PGRERROR_OK);
	if (!valid) cout << "\terror identifying camera!" << endl;

	if (valid) {
		// open camera
		valid = (cam.Connect(&guid) == PGRERROR_OK);
		if (!valid) cout << "\terror connecting to camera!" << endl;
	};

	if (valid) {
		// check support of Format 7
		valid = (cam.GetFormat7Info(&fmt7info, &fmt7ok) == PGRERROR_OK);
		if (!fmt7ok) valid = false;
		if (!valid) cout << "\tcamera doesn't support Format 7!" << endl;
	};

	if (valid) {
		// validate Format 7 settings
		fmt7stgs.mode = MODE_0;
		fmt7stgs.offsetX = 0;
		fmt7stgs.offsetY = 0;
		fmt7stgs.width = fmt7info.maxWidth;
		fmt7stgs.height = fmt7info.maxHeight;
		fmt7stgs.pixelFormat = PIXEL_FORMAT_RAW8; // for some reason _RAW16 hangs when starting capture

		valid = (cam.ValidateFormat7Settings(&fmt7stgs, &fmt7ok, &fmt7pkginf) == PGRERROR_OK);
		if (!fmt7ok) valid = false;
		if (!valid) cout << "\tinvalid Format 7 image settings!" << endl;
	};

	if (valid) {
		// apply Format 7 settings
		valid = (cam.SetFormat7Configuration(&fmt7stgs, fmt7pkginf.recommendedBytesPerPacket) == PGRERROR_OK);
		if (!valid) cout << "\terror applying Format 7 settings!" << endl;
	};

	if (valid) {
		// start capture
		valid = (cam.StartCapture() == PGRERROR_OK);
		if (!valid) cout << "\terror starting capture!" << endl;
	};

	if (!valid && cam.IsConnected()) cam.Disconnect();

	res = pthread_mutex_unlock(&(xchg->datajobprc.mFlycap));
	if (res != 0) {cout << "JobIdecVislacq::openFlycap() error unlocking mutex xchg->datajobprc.mFlycap (" << res << ")" << endl;};

	return valid;
#else
	return false;
#endif
};

void JobIdecVislacq::closeFlycap() {
#ifdef __linux__
	cam.StopCapture();
	cam.Disconnect();
#endif
};

bool JobIdecVislacq::openLifecam() {
#ifdef __linux__
	bool valid;

	v4l2_format fmt = {};
	v4l2_requestbuffers req = {};

	// open camera
	camfile = open(xchg->stgjobidecvislacq.path.c_str(), O_RDWR);

	valid = (camfile != -1);
	if (!valid) cout << "\terror connecting to camera!" << endl;

	if (valid) {
		// set image format
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt.fmt.pix.width = 1280;
		fmt.fmt.pix.height = 720;

		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
//		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;

		fmt.fmt.pix.field = V4L2_FIELD_NONE;

		while (true) {
			valid = (ioctl(camfile, VIDIOC_S_FMT, &fmt) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror setting image format!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// request buffer
		req.count = 1;
		req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		req.memory = V4L2_MEMORY_MMAP;

		while (true) {
			valid = (ioctl(camfile, VIDIOC_REQBUFS, &req) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror requesting buffer!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// map memory
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = 0;

		while (true) {
			valid = (ioctl(camfile, VIDIOC_QUERYBUF, &buf) != -1);

			if (valid) {
				cammmap = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, camfile, buf.m.offset);
				break;
			};

			if (errno != EINTR) {
				cout << "\terror mapping memory!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// start capture
		while (true) {
			valid = (ioctl(camfile, VIDIOC_STREAMON, &buf.type) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror starting capture!" << endl;
				break;
			};
		};
	};

	if (!valid && cammmap) {
		munmap(cammmap, buf.length);
		buf = {};
		cammmap = NULL;
	};

	if (!valid && (camfile != -1)) {
		close(camfile);
		camfile = 0;
	};

	return valid;
#else
	return false;
#endif
};

void JobIdecVislacq::closeLifecam() {
#ifdef __linux__
	if (cammmap) {
		munmap(cammmap, buf.length);
		buf = {};
		cammmap = NULL;
	};

	if (camfile != -1) {
		close(camfile);
		camfile = 0;
	};
#endif
};

vector<string> JobIdecVislacq::surveyFlycap() {
	vector<string> sns;

#ifdef __linux__
	bool valid;

	BusManager busmgr;

	unsigned int ncam;

	PGRGuid guid;

	Camera cam;
	CameraInfo caminfo;

	// identify serial numbers of connected cameras
	valid = (busmgr.GetNumOfCameras(&ncam) == PGRERROR_OK);
	if (!valid) cout << "\terror determining camera count!" << endl;

	if (valid) {
		for (unsigned int i=0;i<ncam;i++) {
			valid = (busmgr.GetCameraFromIndex(i, &guid) == PGRERROR_OK);
			if (!valid) {
				cout << "\terror identifying camera " << i << "!" << endl;
				break;
			};

			valid = (cam.Connect(&guid) == PGRERROR_OK);
			if (!valid) {
				cout << "\terror connecting to camera " << i << "!" << endl;
				break;
			};

			valid = (cam.GetCameraInfo(&caminfo) == PGRERROR_OK);
			if (valid) {
				sns.push_back(to_string(caminfo.serialNumber));
			} else {
				cout << "\terror retrieving camera " << i << "info!" << endl;
			};
			
			cam.Disconnect();
		};
	};
#endif

	return sns;
};

vector<string> JobIdecVislacq::surveyLifecam() {
	vector<string> paths;

	DIR* dir = NULL;

	dirent* diritem = NULL;

	// identify camera devices at /dev/video*
	dir = opendir("/dev");

	if (dir) {
		diritem = readdir(dir);
		while (diritem) {
			if (diritem->d_type == DT_CHR) {
				if (strncmp(diritem->d_name, "video", 5) == 0) paths.push_back("/dev/" + string(diritem->d_name));
			};

			diritem = readdir(dir);
		};

		closedir(dir);
	};

	return paths;
};

// exact copy from Idec.cpp but inline
inline unsigned int JobIdecVislacq::intavg(
			const unsigned int in
			, const unsigned int im
			, bool* rshs
			, const unsigned int rshsN
		) {
	unsigned int retval = im*in;

	for (unsigned int i=0;i<rshsN;i++) if (rshs[i]) retval += (in >> (i+1));

	return retval;
};

void JobIdecVislacq::start(
			DbsIdec* dbsidec
			, vector<Snippet*> _snippets
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecVislacq::start() error locking mutex mAccess (" << res << ")" << endl;};

	snippets = _snippets;

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecvislacq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecVislacq::start() error locking mutex mJrefsStarted (" << res << ")" << endl;};

		xchg->datajobidecvislacq.jrefsStarted.insert(jref);

		res = pthread_mutex_unlock(&(xchg->datajobidecvislacq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecVislacq::start() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTART, jref);
	};

	if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecVislacq::start() error unlocking mutex mAccess (" << res << ")" << endl;};
};

void JobIdecVislacq::stop(
			DbsIdec* dbsidec
		) {
	int res;

	res = pthread_mutex_lock(&mAccess);
	if (res != 0) {cout << "JobIdecVislacq::stop() error locking mutex mAccess (" << res << ")" << endl;};

	snippets.clear();

	if (jref == jrefMast) {
		res = pthread_mutex_lock(&(xchg->datajobidecvislacq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecVislacq::stop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
		xchg->datajobidecvislacq.jrefsStarted.erase(jref);
		if (xchg->datajobidecvislacq.jrefsStarted.empty() && (ixVSge == VecVSge::READY)) changeStage(dbsidec, VecVSge::IDLE);

		res = pthread_mutex_unlock(&(xchg->datajobidecvislacq.mJrefsStarted));
		if (res != 0) {cout << "JobIdecVislacq::stop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	} else {
		xchg->triggerCall(dbsidec, VecIdecVCall::CALLIDECSTOP, jref);
		if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);
	};

	res = pthread_mutex_unlock(&mAccess);
	if (res != 0) {cout << "JobIdecVislacq::stop() error unlocking mutex mAccess (" << res << ")" << endl;};
};

bool JobIdecVislacq::started(
			const bool any
		) {
	bool retval = false;

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::started() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	if (any) retval = !xchg->datajobidecvislacq.jrefsStarted.empty();
	else retval = (xchg->datajobidecvislacq.jrefsStarted.find(jref) != xchg->datajobidecvislacq.jrefsStarted.end());

	res = pthread_mutex_unlock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::started() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	return retval;
};
// IP cust --- IEND
// IP spec --- INSERT

void JobIdecVislacq::changeStage(
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

uint JobIdecVislacq::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- IBEGIN

	if (jref == jrefMast) {
		// close connection
		if (xchg->stgjobidecvislacq.ixIdecVCamtype == VecIdecVCamtype::PGCMLN) closeFlycap();
		else if (xchg->stgjobidecvislacq.ixIdecVCamtype == VecIdecVCamtype::MSLIFE) closeLifecam();
	};

	xchg->datajobidecvislacq.rgb.releaseByJref(jref);

	// IP enterSgeIdle --- IEND
	return retval;
};

void JobIdecVislacq::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- IBEGIN

	uint& _ixIdecVCamtype = xchg->stgjobidecvislacq.ixIdecVCamtype;
	unsigned int& _w = xchg->stgjobidecvislacq.width;
	unsigned int& _h = xchg->stgjobidecvislacq.height;

	bool& _dummy = xchg->datajobidecvislacq.dummy;
	unsigned int& _seqno = xchg->datajobidecvislacq.seqno;
	unsigned char*& _red0 = xchg->datajobidecvislacq.red0;
	unsigned char*& _green0 = xchg->datajobidecvislacq.green0;
	unsigned char*& _blue0 = xchg->datajobidecvislacq.blue0;
	Imgbuf& _rgb = xchg->datajobidecvislacq.rgb;
	Testpat*& _testpat = xchg->datajobidecvislacq.testpat;

	if (jref == jrefMast) {
		_seqno = 0;

		// reset / initialize buffers
		if (!_red0) {
			_red0 = new unsigned char[_w*_h]; memset(_red0, 127, _w*_h);
			_green0 = new unsigned char[_w*_h]; memset(_green0, 127, _w*_h);
			_blue0 = new unsigned char[_w*_h]; memset(_blue0, 127, _w*_h);
			_rgb.init(8, 3*_w*_h*1);
		};

		// open connection
		_dummy = true;

		if (_ixIdecVCamtype == VecIdecVCamtype::PGCMLN) _dummy = !openFlycap();
		else if (_ixIdecVCamtype == VecIdecVCamtype::MSLIFE) _dummy = !openLifecam();

		// prepare dummy functionality
		if (_dummy) _testpat = new Testpat(_w, _h, false);
	};

	bref = 0;
	seqno = 0;
	timestamp = {0,0};

	// IP leaveSgeIdle --- IEND
};

uint JobIdecVislacq::enterSgeReady(
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

void JobIdecVislacq::leaveSgeReady(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeReady --- INSERT
};

uint JobIdecVislacq::enterSgeAcqidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQIDLE;
	nextIxVSge = VecVSge::ACQ;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgeAcqidle --- INSERT
	return retval;
};

void JobIdecVislacq::leaveSgeAcqidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcqidle --- INSERT
};

uint JobIdecVislacq::enterSgeAcq(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ACQ;
	nextIxVSge = retval;
	// IP enterSgeAcq --- IBEGIN

	// should only be invoked as master: get raw image data
	int res;

	bool valid;

	uint& _ixIdecVCamtype = xchg->stgjobidecvislacq.ixIdecVCamtype;
	unsigned int& _w = xchg->stgjobidecvislacq.width;
	unsigned int& _h = xchg->stgjobidecvislacq.height;
	uint& _ixIdecVSqrgrp = xchg->stgjobidecvislacq.ixIdecVSqrgrp;

	bool& _dummy = xchg->datajobidecvislacq.dummy;
	unsigned int& _seqno = xchg->datajobidecvislacq.seqno;
	unsigned char*& _red0 = xchg->datajobidecvislacq.red0;
	unsigned char*& _green0 = xchg->datajobidecvislacq.green0;
	unsigned char*& _blue0 = xchg->datajobidecvislacq.blue0;
	Imgbuf& _rgb = xchg->datajobidecvislacq.rgb;
	Testpat*& _testpat = xchg->datajobidecvislacq.testpat;

///
	uint& _sfseqlen = xchg->stgjobidecspotfind.seqlen;

	bool& _sfdummy = xchg->datajobidecspotfind.dummy;
	double& _sfA = xchg->datajobidecspotfind.A;
	double& _sfdr = xchg->datajobidecspotfind.dr;
	unsigned int& _sfseqno_last = xchg->datajobidecspotfind.seqno_last;
	double& _sfx0 = xchg->datajobidecspotfind.x0;
	double& _sfy0 = xchg->datajobidecspotfind.y0;
	double& _sfds = xchg->datajobidecspotfind.ds;
	double& _sfvx = xchg->datajobidecspotfind.vx;
	double& _sfvy = xchg->datajobidecspotfind.vy;
///

	Imgbufitem* ibit = NULL;

	utinyint* _r = NULL;
	utinyint* _g = NULL;
	utinyint* _b = NULL;

#ifdef __linux__
	// flycap specific
	unsigned int ipl;

	// lifecam specific
	fd_set fds = {};

	timeval to = {};

	// Y'UV422 floating point version specific
//	double y1, u, y2, v, d;

	// Y'UV422 integer version specific
	int y1, u, y2, v, d;
#endif

	valid = false;

	if (_dummy) {
		// test pattern is assembled directly into ibit
		valid = true;

	} else if (_ixIdecVCamtype == VecIdecVCamtype::PGCMLN) {
#ifdef __linux__
		valid = (cam.RetrieveBuffer(&img) == PGRERROR_OK);

		if (valid) {
			// update _red0, _green0, _blue0
			unsigned int ix, ix2;

// cout << "JobIdecVislacq::enterSgeAcq() img.GetReceivedDataSize() = " << img.GetReceivedDataSize() << endl;

			for (unsigned int i=0;i<_h;i++) {
				for (unsigned int j=0;j<_w;j++) {
					ix = i*_w+j;

					// Bayer mosaic
					if ( ((i%2)==0) && ((j%2)==0) ) {
						_green0[ix] = *(img[ix]);
					} else if ( ((i%2)==0) && ((j%2)==1) ) {
						_blue0[ix] = *(img[ix]);
					} else if ( ((i%2)==1) && ((j%2)==0) ) {
						_red0[ix] = *(img[ix]);
					} else if ( ((i%2)==1) && ((j%2)==1) ) {
						_green0[ix] = *(img[ix]);
					};
				};
			};

			for (unsigned int i=0;i<_h;i++) {
				for (unsigned int j=0;j<_w;j++) {
					ix2 = i*_w+j;

					// bilinear de-mosaic
					if ( ((i%2)==0) && ((j%2)==0) ) {
						if ((i!=0) && (i!=(_h-1))) {
							ipl = (_red0[(i-1)*_w+j]+_red0[(i+1)*_w+j]) >> 1;
							_red0[ix2] = ipl;
						} else _red0[ix2] = 0;
						if ((j!=0) && (j!=(_w-1))) {
							ipl = (_blue0[i*_w+j-1]+_blue0[i*_w+j+1]) >> 1;
							_blue0[ix2] = ipl;
						} else _blue0[ix2] = 0;
					} else if ( ((i%2)==0) && ((j%2)==1) ) {
						if ((i!=0) && (i!=(_h-1)) && (j!=0) && (j!=(_w-1))) {
							ipl = (_red0[(i-1)*_w+j-1]+_red0[(i+1)*_w+j+1]+_red0[(i-1)*_w+j+1]+_red0[(i+1)*_w+j-1]) >> 2;
							_red0[ix2] = ipl;
						} else _red0[ix2] = 0;
						if ((i!=0) && (i!=(_h-1)) && (j!=0) && (j!=(_w-1))) {
							ipl = (_green0[(i-1)*_w+j]+_green0[(i+1)*_w+j]+_green0[i*_w+j-1]+_green0[i*_w+j+1]) >> 2;
							_green0[ix2] = ipl;
						} else _green0[ix2] = 0;
					} else if ( ((i%2)==1) && ((j%2)==0) ) {
						if ((i!=0) && (i!=(_h-1)) && (j!=0) && (j!=(_w-1))) {
							ipl = (_green0[(i-1)*_w+j]+_green0[(i+1)*_w+j]+_green0[i*_w+j-1]+_green0[i*_w+j+1]) >> 2;
							_green0[ix2] = ipl;
						} else _green0[ix2] = 0;
						if ((i!=0) && (i!=(_h-1)) && (j!=0) && (j!=(_w-1))) {
							ipl = (_blue0[(i-1)*_w+j-1]+_blue0[(i+1)*_w+j+1]+_blue0[(i-1)*_w+j+1]+_blue0[(i+1)*_w+j-1]) >> 2;
							_blue0[ix2] = ipl;
						} else _blue0[ix2] = 0;
					} else if ( ((i%2)==1) && ((j%2)==1) ) {
						if ((j!=0) && (j!=(_w-1))) {
							ipl = (_red0[i*_w+j-1]+_red0[i*_w+j+1]) >> 1;
							_red0[ix2] = ipl;
						} else _red0[ix2] = 0;
						if ((i!=0) && (i!=(_h-1))) {
							ipl = (_blue0[(i-1)*_w+j]+_blue0[(i+1)*_w+j]) >> 1;
							_blue0[ix2] = ipl;
						} else _blue0[ix2] = 0;
					};
				};
			};

		} else {
			cout << "\terror retrieving image #" << _seqno << endl;
		};
#endif

	} else if (_ixIdecVCamtype == VecIdecVCamtype::MSLIFE) {
#ifdef __linux__
		FD_SET(camfile, &fds);

		to.tv_sec = 1;

		// queue buffer
		while (true) {
			valid = (ioctl(camfile, VIDIOC_QBUF, &buf) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror queuing buffer at image #" << _seqno << endl;
				break;
			};
		};

		if (valid) {
			valid = (select(camfile+1, &fds, NULL, NULL, &to) != -1);
			if (!valid) cout << "\ttimeout waiting for image #" << _seqno << endl;
		};

		if (valid) {
			// de-queue buffer
			while (true) {
				valid = (ioctl(camfile, VIDIOC_DQBUF, &buf) != -1);

				if (valid) {
					// update _red0, _green0, _blue0
					unsigned int ix, ix2;

// cout << "buf.bytesused = " << buf.bytesused << endl;

					// Y'UV422 floating point version
/*
					for (unsigned int i=0;i<_h;i++) {
						for (unsigned int j=0;j<(_w/2);j++) {
							ix = 2* (i*_w+j*2);
							ix2 = i*_w+j*2;

							y1 = ((unsigned char*) cammmap)[ix];
							u = ((unsigned char*) cammmap)[ix+1];
							y2 = ((unsigned char*) cammmap)[ix+2];
							v = ((unsigned char*) cammmap)[ix+3];

							d = y1 + 1.402*(v-128.0); if (d < 0.0) d = 0.0; if (d > 255.0) d = 255.0;
							_red0[ix2] = lround(d);
							d = y1 - 0.344*(u-128.0) - 0.714*(v-128.0); if (d < 0.0) d = 0.0; if (d > 255.0) d = 255.0;
							_green0[ix2] = lround(d);
							d = y1 + 1.772*(u-128.0); if (d < 0.0) d = 0.0; if (d > 255.0) d = 255.0;
							_blue0[ix2] = lround(d);

							d = y2 + 1.402*(v-128.0); if (d < 0.0) d = 0.0; if (d > 255.0) d = 255.0;
							_red0[ix2+1] = lround(d);
							d = y2 - 0.344*(u-128.0) - 0.714*(v-128.0); if (d < 0.0) d = 0.0; if (d > 255.0) d = 255.0;
							_green0[ix2+1] = lround(d);
							d = y2 + 1.772*(u-128.0); if (d < 0.0) d = 0.0; if (d > 255.0) d = 255.0;
							_blue0[ix2+1] = lround(d);
						};
					};
*/

					// Y'UV422 integer version
					for (unsigned int i=0;i<_h;i++) {
						for (unsigned int j=0;j<(_w/2);j++) {
							ix = 2* (i*_w+j*2);
							ix2 = i*_w+j*2;

							y1 = ((unsigned char*) cammmap)[ix];
							u = ((unsigned char*) cammmap)[ix+1];
							y2 = ((unsigned char*) cammmap)[ix+2];
							v = ((unsigned char*) cammmap)[ix+3];

							v -= 128;
							u -= 128;

							d = y1 + v + (v >> 2) + (v >> 3) + (v >> 5); if (d < 0) d = 0; if (d > 255) d = 255;
							_red0[ix2] = d;
							d = y1 - ((u >> 2) + (u >> 4) + (u >> 5)) - ((v >> 1) + (v >> 3) + (v >> 4) + (v >> 5)); if (d < 0) d = 0; if (d > 255) d = 255;
							_green0[ix2] = d;
							d = y1 + u + (u >> 1) + (u >> 2) + (u >> 6); if (d < 0) d = 0; if (d > 255) d = 255;
							_blue0[ix2] = d;
							
							d = y2 + v + (v >> 2) + (v >> 3) + (v >> 5); if (d < 0) d = 0; if (d > 255) d = 255;
							_red0[ix2+1] = d;
							d = y2 - ((u >> 2) + (u >> 4) + (u >> 5)) - ((v >> 1) + (v >> 3) + (v >> 4) + (v >> 5)); if (d < 0) d = 0; if (d > 255) d = 255;
							_green0[ix2+1] = d;
							d = y2 + u + (u >> 1) + (u >> 2) + (u >> 6); if (d < 0) d = 0; if (d > 255) d = 255;
							_blue0[ix2+1] = d;
						};
					};

					break;
				};

				if (errno != EINTR) {
					cout << "\terror de-queuing buffer at image #" << _seqno << endl;
					break;
				};
			};
		};
#endif
	};

	// - prepare for processing
	res = pthread_mutex_lock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::enterSgeAcq() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	bref = 0;

	if (valid) {
		// obtain available slot in _rgb
		bref = _rgb.getNewItem(jref, _seqno, {0,0}); // seqno from trigger, timestamp generated at this time
		valid = (bref != 0);
	};

	if (valid) {
		ibit = _rgb.getItem(bref);

		if (_dummy) {
			_testpat->step(ibit->data);

		} else {
			// _red0/_green0/_blue0 -> ibit
			_r = ibit->data;
			_g = &(ibit->data[_w*_h]);
			_b = &(ibit->data[2*_w*_h]);

			// apply orientation transform (r0, r2, s0, s2 are allowed)
			Idec::copytrfBuf(_red0, _r, 1, _w, _h, _ixIdecVSqrgrp);
			Idec::copytrfBuf(_green0, _g, 1, _w, _h, _ixIdecVSqrgrp);
			Idec::copytrfBuf(_blue0, _b, 1, _w, _h, _ixIdecVSqrgrp);
		};

		if (_sfdummy && (_sfseqlen != 0)) {
			// simulated red spot for spotfinder

			double phi =  ((double) (_seqno%_sfseqlen))/((double) _sfseqlen);
			double A = _sfA * (1.0 + sin(2.0*pi*phi));

			double x = _sfx0 - 0.5*_sfds + _sfvx*((double) (_seqno-_sfseqno_last));
			double y = _sfy0 + _sfvy*((double) (_seqno-_sfseqno_last));

			Idec::addSpot(ibit->data, _w, _h, A, x, y, _sfdr);
		};

		// spread the news
		xchg->triggerRefCall(dbsidec, VecIdecVCall::CALLIDECIBITRDY, jref, bref);

		if (!started()) retval = VecVSge::READY;
		else retval = VecVSge::PRC;

	} else {
		retval = VecVSge::READY;
	};

	res = pthread_mutex_unlock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::enterSgeAcq() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	if ((bref != 0) && (retval != VecVSge::PRC)) _rgb.release(bref, jref);

	// IP enterSgeAcq --- IEND
	return retval;
};

void JobIdecVislacq::leaveSgeAcq(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAcq --- INSERT
};

uint JobIdecVislacq::enterSgePrcidle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRCIDLE;
	nextIxVSge = VecVSge::PRC;

	wrefLast = xchg->addWakeup(jref, "callback", 0);
	// IP enterSgePrcidle --- INSERT
	return retval;
};

void JobIdecVislacq::leaveSgePrcidle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrcidle --- INSERT
};

uint JobIdecVislacq::enterSgePrc(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::PRC;
	nextIxVSge = retval;
	// IP enterSgePrc --- IBEGIN

	bool valid;

	unsigned int& _w = xchg->stgjobidecvislacq.width;
	unsigned int& _h = xchg->stgjobidecvislacq.height;

	Imgbuf& _rgb = xchg->datajobidecvislacq.rgb;

	Imgbufitem* ibit = NULL;

	utinyint* _r = NULL;
	utinyint* _g = NULL;
	utinyint* _b = NULL;
	utinyint* src = NULL;

	Snippet* snippet = NULL;

	unsigned int wlen;

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

			wlen = (snippet->ixIdecVChannel == VecIdecVChannel::GRAY16) ? 2 : 1;

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
			if (cpyw < snippet->w) for (unsigned int i=0;i<cpyh;i++) memset((void*) &(snippet->data[wlen*(i*snippet->w+cpyw)]), 127, wlen*(snippet->w-cpyw));

			// border below
			if (cpyh < snippet->h) memset((void*) &(snippet->data[wlen*(snippet->w*cpyh)]), 127, wlen*(snippet->w*(snippet->h-cpyh)));

			if ((mult == 1) && (cpyw == _w) && (cpyh == _h)) {
				// straight copy in case of exact overlap
				if ((snippet->ixIdecVChannel == VecIdecVChannel::RED8) || (snippet->ixIdecVChannel == VecIdecVChannel::GREEN8) || (snippet->ixIdecVChannel == VecIdecVChannel::BLUE8)) {
					memcpy(snippet->data, src, wh);

				} else if (snippet->ixIdecVChannel == VecIdecVChannel::GRAY16) {
					rshsN = 16;
					Idec::setupIntavg(3, 255, 65535, 0.999, im, rshs, rshsN);

					for (unsigned int i=0;i<wh;i++) {
						sum = _r[i] + _g[i] + _b[i];
						((unsigned short*) (snippet->data))[i] = intavg(sum, im, rshs, rshsN);
					};
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

				} else if (snippet->ixIdecVChannel == VecIdecVChannel::GRAY16) {
					rshsN = 16;
					Idec::setupIntavg(3*mult*mult, 255, 65535, 0.999, im, rshs, rshsN);

					for (unsigned int i=0;i<cpyh;i++) {
						for (unsigned int j=0;j<cpyw;j++) {
							sum = 0;

							for (unsigned int k=0;k<mult;k++) {
								for (unsigned int l=0;l<mult;l++) {
									ix = (y0+mult*i+k)*_w + (x0+mult*j+l);

									sum += _r[ix];
									sum += _g[ix];
									sum += _b[ix];
								};
							};

							((unsigned short*) (snippet->data))[i*snippet->w+j] = intavg(sum, im, rshs, rshsN);
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

void JobIdecVislacq::leaveSgePrc(
			DbsIdec* dbsidec
		) {
	// IP leaveSgePrc --- INSERT
};

string JobIdecVislacq::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void JobIdecVislacq::giveupMaster(
			DbsIdec* dbsidec
		) {
	// IP giveupMaster --- INSERT
};

void JobIdecVislacq::giveupSlave(
			DbsIdec* dbsidec
		) {
	// IP giveupSlave --- INSERT
};

void JobIdecVislacq::becomeMaster(
			DbsIdec* dbsidec
		) {
	// IP becomeMaster --- INSERT
};

void JobIdecVislacq::becomeSlave(
			DbsIdec* dbsidec
		) {
	// IP becomeSlave --- INSERT
};

bool JobIdecVislacq::handleClaimMaster(
			DbsIdec* dbsidec
		) {
	bool retval = !prefmast;
	// IP handleClaimMaster --- IBEGIN
	retval = true;
	// IP handleClaimMaster --- IEND
	return retval;
};

void JobIdecVislacq::handleRequest(
			DbsIdec* dbsidec
			, ReqIdec* req
		) {
	if (req->ixVBasetype == ReqIdec::VecVBasetype::CMD) {
		reqCmd = req;

		if (req->cmd == "cmdset") {
			cout << "\ttestFlycap" << endl;
			cout << "\ttestLifecam" << endl;
		} else if (req->cmd == "testFlycap") {
			req->retain = handleTestFlycap(dbsidec);

		} else if (req->cmd == "testLifecam") {
			req->retain = handleTestLifecam(dbsidec);

		} else {
			cout << "\tinvalid command!" << endl;
		};

		if (!req->retain) reqCmd = NULL;

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::REGULAR) {

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
		handleTimer(dbsidec, req->sref);
	};
};

bool JobIdecVislacq::handleTestFlycap(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	// IP handleTestFlycap --- IBEGIN
#ifdef __linux__

	int res;

	bool valid;

	BusManager busmgr;

	unsigned int ncam;

	PGRGuid guid;

	Camera cam;
	CameraInfo caminfo;

	Format7Info fmt7info;
	bool fmt7ok;

	Format7ImageSettings fmt7stgs;
	Format7PacketInfo fmt7pkginf;

	Image img;

	// find camera
	valid = (busmgr.GetNumOfCameras(&ncam) == PGRERROR_OK);
	if (!valid) cout << "\terror determining camera count!" << endl;

	if (valid) {
		valid = (ncam > 0);
		if (!valid) cout << "\tnot a single camera detected!" << endl;
	};

	if (valid) {
		valid = (busmgr.GetCameraFromIndex(0, &guid) == PGRERROR_OK);
		if (!valid) cout << "\terror identifying camera!" << endl;
	};

	if (valid) {
		// open camera
		valid = (cam.Connect(&guid) == PGRERROR_OK);
		if (!valid) cout << "\terror connecting to camera!" << endl;
	};

	if (valid) {
		// get serial number
		valid = (cam.GetCameraInfo(&caminfo) == PGRERROR_OK);

		if (valid) {
			cout << "\tserial number: " << caminfo.serialNumber << endl;
		} else {
			cout << "\terror retrieving camera info!" << endl;
		};
	};

	// - set configuration

	// non-Format7:
	// enum PropertyType (not so interesting)
	// enum GrabMode (DROP_FRAMES is default)
	// enum VideoMode (VIDEOMODE_1280x960YUV422 vs VIDEOMODE_1280x960RGB vs VIDEOMODE_FORMAT7)
	// enum FrameRate (FRAMERATE_1_875 vs FRAMERATE_15 vs FRAMERATE_FORMAT7)

	// Format7:
	// enum PixelFormat (PIXEL_FORMAT_422YUV8 vs PIXEL_FORMAT_BGR)

	if (valid) {
		// check support of Format 7
		valid = (cam.GetFormat7Info(&fmt7info, &fmt7ok) == PGRERROR_OK);
		if (valid && fmt7ok) {
			cout << "\tmax. resolution: " << fmt7info.maxWidth << "x" << fmt7info.maxHeight << endl;
		} else {
			cout << "\tcamera doesn't support Format 7!" << endl;
		};
	};

	if (valid) {
		// validate Format 7 settings
		fmt7stgs.mode = MODE_0;
		fmt7stgs.offsetX = 0;
		fmt7stgs.offsetY = 0;
		fmt7stgs.width = fmt7info.maxWidth;
		fmt7stgs.height = fmt7info.maxHeight;
		fmt7stgs.pixelFormat = PIXEL_FORMAT_RAW8; // only PIXEL_FORMAT_RAW8 and PIXEL_FORMAT_RAW16 possible

		valid = (cam.ValidateFormat7Settings(&fmt7stgs, &fmt7ok, &fmt7pkginf) == PGRERROR_OK);
		if (!valid || !fmt7ok) cout << "\tinvalid Format 7 image settings!" << endl;
	};

	if (valid) {
		// apply Format 7 settings
		valid = (cam.SetFormat7Configuration(&fmt7stgs, fmt7pkginf.recommendedBytesPerPacket) == PGRERROR_OK);
		if (!valid) cout << "\terror applying Format 7 settings!" << endl;
	};

	if (valid) {
		// start capture
cout << "start capture ..." << endl;
		valid = (cam.StartCapture() == PGRERROR_OK);
		if (!valid) cout << "\terror starting capture!" << endl;
cout << "... after start capture" << endl;
	};

	if (valid) {
		// acquire ten images
		for (unsigned int i=0;i<10;i++) {

			res = pthread_mutex_lock(&(xchg->datajobprc.mFlycap));
			if (res != 0) {cout << "\terror locking mutex xchg->datajobprc.mFlycap (" << res << ")" << endl;};

cout << "i=" << i << endl;

			valid = (cam.RetrieveBuffer(&img) == PGRERROR_OK);

			res = pthread_mutex_unlock(&(xchg->datajobprc.mFlycap));
			if (res != 0) {cout << "\terror unlocking mutex xchg->datajobprc.mFlycap (" << res << ")" << endl;};

			if (valid) {
				cout << "\timage #" << (i+1) << ": length=" << img.GetReceivedDataSize()
							<< ", 1394 timestamp=" << img.GetTimeStamp().cycleSeconds << " #" << img.GetTimeStamp().cycleCount
							<< ", format=" << img.GetPixelFormat() << endl; // default: FC2_PIXEL_FORMAT_MONO8

			} else {
				cout << "\terror retrieving image #" << (i+1) << endl;
			};
		};
	};

	if (valid) {
		// stop capture
		valid = (cam.StopCapture() == PGRERROR_OK);
		if (!valid) cout << "\terror stopping capture!" << endl;
	};

	// close camera
	if (cam.IsConnected()) cam.Disconnect();

#endif
	// IP handleTestFlycap --- IEND
	return retval;
};

bool JobIdecVislacq::handleTestLifecam(
			DbsIdec* dbsidec
		) {
	bool retval = false;
	// IP handleTestLifecam --- IBEGIN
#ifdef __linux__

	bool valid;

	int camfile = 0;

	v4l2_format fmt = {};
	v4l2_requestbuffers req = {};
	v4l2_buffer buf = {};

	void* cammmap = NULL;

	fd_set fds = {};

	timeval to = {};

	// open camera
	camfile = open("/dev/video0", O_RDWR);

	valid = (camfile != -1);
	if (!valid) cout << "\terror connecting to camera!" << endl;

	if (valid) {
		// set image format
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt.fmt.pix.width = 640;
		fmt.fmt.pix.height = 480;
		//fmt.fmt.pix.width = 1280;
		//fmt.fmt.pix.height = 720;

		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
		//fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;

		fmt.fmt.pix.field = V4L2_FIELD_NONE;

		while (true) {
			valid = (ioctl(camfile, VIDIOC_S_FMT, &fmt) != -1);

			if (valid) {
				cout << "\timage format: width=" << fmt.fmt.pix.width << ", height=" << fmt.fmt.pix.height << endl;
				break;
			};

			if (errno != EINTR) {
				cout << "\terror setting image format!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// request buffer
		req.count = 1;
		req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		req.memory = V4L2_MEMORY_MMAP;

		while (true) {
			valid = (ioctl(camfile, VIDIOC_REQBUFS, &req) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror requesting buffer!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// map memory
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = 0;

		while (true) {
			valid = (ioctl(camfile, VIDIOC_QUERYBUF, &buf) != -1);

			if (valid) {
				cout << "\tbuffer length: " << buf.length << endl;
				cammmap = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, camfile, buf.m.offset);

				break;
			};

			if (errno != EINTR) {
				cout << "\terror mapping memory!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// start capture
		while (true) {
			valid = (ioctl(camfile, VIDIOC_STREAMON, &buf.type) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror starting capture!" << endl;
				break;
			};
		};
	};

	if (valid) {
		FD_SET(camfile, &fds);

		to.tv_sec = 1;

		// acquire ten images
		for (unsigned int i=0;i<10;i++) {
			// queue buffer
			while (true) {
				valid = (ioctl(camfile, VIDIOC_QBUF, &buf) != -1);

				if (valid) break;


				if (errno != EINTR) {
					cout << "\terror queuing buffer at image #" << (i+1) << endl;
					break;
				};
			};

			if (!valid) break;

			valid = (select(camfile+1, &fds, NULL, NULL, &to) != -1);

			if (!valid) {
				cout << "\ttimeout waiting for image #" << (i+1) << endl;
				break;
			};

			// de-queue buffer
			while (true) {
				valid = (ioctl(camfile, VIDIOC_DQBUF, &buf) != -1);

				if (valid) {
					cout << "\timage #" << (i+1) << ": length=" << buf.bytesused
								<< ", timestamp=" << buf.timestamp.tv_sec << "." << buf.timestamp.tv_usec
								<< ", sequence=" << buf.sequence
								<< ", flags=" << buf.flags << endl;
					break;
				};

				if (errno != EINTR) {
					cout << "\terror de-queuing buffer at image #" << (i+1) << endl;
					break;
				};
			};

			if (!valid) break;
		};
	};

	if (valid) {
		// stop capture
		while (true) {
			valid = (ioctl(camfile, VIDIOC_STREAMOFF, &buf.type) != -1);

			if (valid) break;

			if (errno != EINTR) {
				cout << "\terror stopping capture!" << endl;
				break;
			};
		};
	};

	if (valid) {
		// unmap memory
		valid = (munmap(cammmap, buf.length) != -1);
		if (!valid) cout << "\terror unmapping memory!" << endl;
	};

	// close camera
	if (camfile != -1) close(camfile);

#endif
	// IP handleTestLifecam --- IEND
	return retval;
};

void JobIdecVislacq::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if (ixVSge == VecVSge::ACQIDLE) {
		changeStage(dbsidec, nextIxVSge);
	} else if (ixVSge == VecVSge::PRCIDLE) {
		changeStage(dbsidec, nextIxVSge);
	};
};

void JobIdecVislacq::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECTRIGVISL) {
		call->abort = handleCallIdecTrigVisl(dbsidec, call->jref, call->argInv.intval);
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

bool JobIdecVislacq::handleCallIdecTrigVisl(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const int intvalInv
		) {
	bool retval = false;
	// IP handleCallIdecTrigVisl --- IBEGIN

	if ((jref == jrefMast) && (ixVSge == VecVSge::READY)) {
		xchg->datajobidecvislacq.seqno = intvalInv;
		changeStage(dbsidec, VecVSge::ACQIDLE);
	};

	// IP handleCallIdecTrigVisl --- IEND
	return retval;
};

bool JobIdecVislacq::handleCallIdecStart(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecStart --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::handleCallIdecStart() error locking mutex mJrefsStarted (" << res << ")" << endl;};

	xchg->datajobidecvislacq.jrefsStarted.insert(jrefTrig);

	res = pthread_mutex_unlock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::handleCallIdecStart() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	res = pthread_mutex_trylock(&mAccess);

	if (res == 0) {
		if (ixVSge == VecVSge::IDLE) changeStage(dbsidec, VecVSge::READY);

		res = pthread_mutex_unlock(&mAccess);
		if (res != 0) {cout << "JobIdecVislacq::handleCallIdecStart() error unlocking mutex mAccess (" << res << ")" << endl;};

	} else if (res != EBUSY) {cout << "JobIdecVislacq::handleCallIdecStart() error try-locking mutex mAccess (" << res << ")" << endl;};

	// IP handleCallIdecStart --- IEND
	return retval;
};

bool JobIdecVislacq::handleCallIdecStop(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStop --- IBEGIN

	int res;

	res = pthread_mutex_lock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::handleCallIdecStop() error locking mutex mJrefsStarted (" << res << ")" << endl;};
	
	xchg->datajobidecvislacq.jrefsStarted.erase(jrefTrig);

	if (xchg->datajobidecvislacq.jrefsStarted.empty()) {
		res = pthread_mutex_trylock(&mAccess);

		if (res == 0) {
			if (ixVSge == VecVSge::READY) changeStage(dbsidec, VecVSge::IDLE);

			res = pthread_mutex_unlock(&mAccess);
			if (res != 0) {cout << "JobIdecVislacq::handleCallIdecStop() error unlocking mutex mAccess (" << res << ")" << endl;};

		} else if (res != EBUSY) {cout << "JobIdecVislacq::handleCallIdecStop() error try-locking mutex mAccess (" << res << ")" << endl;};
	};

	res = pthread_mutex_unlock(&(xchg->datajobidecvislacq.mJrefsStarted));
	if (res != 0) {cout << "JobIdecVislacq::handleCallIdecStop() error unlocking mutex mJrefsStarted (" << res << ")" << endl;};

	// IP handleCallIdecStop --- IEND
	return retval;
};

bool JobIdecVislacq::handleCallIdecIbitrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecIbitrdy --- IBEGIN

	if ((jref != jrefMast) && (ixVSge == VecVSge::READY)) {
		bref = refInv;
		xchg->datajobidecvislacq.rgb.claim(refInv, jref);

		changeStage(dbsidec, VecVSge::PRCIDLE);
	};

	// IP handleCallIdecIbitrdy --- IEND
	return retval;
};

bool JobIdecVislacq::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- INSERT
	return retval;
};

bool JobIdecVislacq::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool JobIdecVislacq::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- INSERT
	return retval;
};


