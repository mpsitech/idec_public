/**
  * \file PnlIdecIaqLive.cpp
  * job handler for job PnlIdecIaqLive (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecIaqLive.h"

#include "PnlIdecIaqLive_blks.cpp"
#include "PnlIdecIaqLive_evals.cpp"

/******************************************************************************
 class PnlIdecIaqLive
 ******************************************************************************/

PnlIdecIaqLive::PnlIdecIaqLive(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECIAQLIVE, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFPupRes.tag = "FeedFPupRes";
	feedFPupSrc.tag = "FeedFPupSrc";
	VecVSource::fillFeed(ixIdecVLocale, feedFPupSrc);

	jobfusion = NULL;
	joblwiracq = NULL;
	jobrecord = NULL;
	jobstereo = NULL;
	jobtrigger = NULL;
	jobvislacq = NULL;
	jobvisracq = NULL;

	// IP constructor.cust1 --- IBEGIN
	ixVSource = 0;

	muteRefresh = false;

	red = NULL;
	green = NULL;
	blue = NULL;
	gray = NULL;
	depth = NULL;

	fnew = 0;
	fps = 0.0;
	// IP constructor.cust1 --- IEND

	jobrecord = new JobIdecRecord(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobtrigger = new JobIdecTrigger(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- IBEGIN
	changeSource(dbsidec, VecVSource::VISL);
	// IP constructor.cust2 --- IEND

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECIMGRDY, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSPTFND, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::TRY);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::WEAK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecIaqLive::~PnlIdecIaqLive() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- IBEGIN
	if (red) delete red;
	if (green) delete green;
	if (blue) delete blue;
	if (gray) delete gray;
	if (depth) delete depth;
	// IP destructor.cust --- IEND

	xchg->removeJobByJref(jref);
};

// IP cust --- IBEGIN
void PnlIdecIaqLive::changeSource(
			DbsIdec* dbsidec
			, const uint _ixVSource
		) {
	if (_ixVSource != ixVSource) {
		ixVSource = 0;

		if (jobvislacq) {delete jobvislacq; jobvislacq = NULL;};
		if (jobvisracq) {delete jobvisracq; jobvisracq = NULL;};
		if (joblwiracq) {delete joblwiracq; joblwiracq = NULL;};
		if (jobstereo) {delete jobstereo; jobstereo = NULL;};
		if (jobfusion) {delete jobfusion; jobfusion = NULL;};

		if (_ixVSource == VecVSource::VISL) jobvislacq = new JobIdecVislacq(xchg, dbsidec, jref, ixIdecVLocale, true);
		else if (_ixVSource == VecVSource::VISR) jobvisracq = new JobIdecVisracq(xchg, dbsidec, jref, ixIdecVLocale, true);
		else if (_ixVSource == VecVSource::LWIR) joblwiracq = new JobIdecLwiracq(xchg, dbsidec, jref, ixIdecVLocale, true);
		else if (_ixVSource == VecVSource::STEREO) jobstereo = new JobIdecStereo(xchg, dbsidec, jref, ixIdecVLocale, true);
		else if (_ixVSource == VecVSource::FUSION) jobfusion = new JobIdecFusion(xchg, dbsidec, jref, ixIdecVLocale, true);

		feedFPupRes.clear();

		VecIdecVCamres::appendToFeed(VecIdecVCamres::_1024, ixIdecVLocale, feedFPupRes);
		VecIdecVCamres::appendToFeed(VecIdecVCamres::_800, ixIdecVLocale, feedFPupRes);
		VecIdecVCamres::appendToFeed(VecIdecVCamres::_640, ixIdecVLocale, feedFPupRes);
		VecIdecVCamres::appendToFeed(VecIdecVCamres::_320, ixIdecVLocale, feedFPupRes);
		VecIdecVCamres::appendToFeed(VecIdecVCamres::_160, ixIdecVLocale, feedFPupRes);

		contiac.numFPupRes = 3;

		ixVSource = _ixVSource;
	};
};

void PnlIdecIaqLive::refreshLive(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ostringstream str;

	// continf
	ContInf oldContinf(continf);

	if (started()) {
		str.str("");
		str << VecVSource::getTitle(ixVSource, ixIdecVLocale);

		if (ixIdecVLocale == VecIdecVLocale::ENUS) str << " is running at ";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) str << " l\\u00e4uft mit ";

		str.precision(1);
		str << fixed << fps << "fps";

		continf.TxtSte = str.str();

	} else {
		if (ixIdecVLocale == VecIdecVLocale::ENUS) continf.TxtSte = "idle";
		else if (ixIdecVLocale == VecIdecVLocale::DECH) continf.TxtSte = "bereit";
	};

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

bool PnlIdecIaqLive::started() {
	bool retval = false;

	if (ixVSource == VecVSource::VISL) retval = jobvislacq->started();
	else if (ixVSource == VecVSource::VISR) retval = jobvisracq->started();
	else if (ixVSource == VecVSource::LWIR) retval = joblwiracq->started();
	else if (ixVSource == VecVSource::STEREO) retval = jobstereo->started();
	else if (ixVSource == VecVSource::FUSION) retval = jobfusion->started();

	return retval;
};

// IP cust --- IEND
DpchEngIdec* PnlIdecIaqLive::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFPupRes, &feedFPupSrc, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecIaqLive::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN

	// contiac
	ContIac oldContiac(contiac);

//	contiac.numFPupSrc;
//	contiac.numFPupRes;
//	contiac.SldFrr;
//	contiac.SldExt;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (continf.ButMasterOn && jobfusion) continf.ButMasterOn = (jobfusion->jref == jobfusion->jrefMast);
	if (continf.ButMasterOn && joblwiracq) continf.ButMasterOn = (joblwiracq->jref == joblwiracq->jrefMast);
	if (continf.ButMasterOn && jobstereo) continf.ButMasterOn = (jobstereo->jref == jobstereo->jrefMast);
	if (continf.ButMasterOn && jobtrigger) continf.ButMasterOn = (jobtrigger->jref == jobtrigger->jrefMast);
	if (continf.ButMasterOn && jobvislacq) continf.ButMasterOn = (jobvislacq->jref == jobvislacq->jrefMast);
	if (continf.ButMasterOn && jobvisracq) continf.ButMasterOn = (jobvisracq->jref == jobvisracq->jrefMast);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	statshr.ChkGrsAvail = ((ixVSource == VecVSource::VISL) || (ixVSource == VecVSource::VISR)); // CUSTOM
	statshr.SldConAvail = (contiac.ChkGrs && ((ixVSource == VecVSource::VISL) || (ixVSource == VecVSource::VISR))) || (ixVSource == VecVSource::LWIR) || (ixVSource == VecVSource::STEREO); // CUSTOM
	statshr.SldBriAvail = (contiac.ChkGrs && ((ixVSource == VecVSource::VISL) || (ixVSource == VecVSource::VISR))) || (ixVSource == VecVSource::LWIR) || (ixVSource == VecVSource::STEREO); // CUSTOM
	statshr.SldFrrActive = evalSldFrrActive(dbsidec);
	//statshr.SldExtAvail = CUSTOM;
	//statshr.SldExtActive = CUSTOM;

	statshr.ButStopActive = started();
	statshr.ButPlayActive = (joblwiracq || jobvislacq || jobvisracq || jobstereo || jobfusion) && !statshr.ButStopActive;

	refreshLive(dbsidec, moditems);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecIaqLive::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::ALRGUM: leaveSgeAlrgum(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::ALRGUM: _ixVSge = enterSgeAlrgum(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint PnlIdecIaqLive::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void PnlIdecIaqLive::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgeIdle --- INSERT
};

uint PnlIdecIaqLive::enterSgeAlrgum(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRGUM;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrgum --- BEGIN
	continf.TxtCpt = VecIdecVTag::getTitle(VecIdecVTag::REQ, ixIdecVLocale);
	continf.TxtCpt = StrMod::cap(continf.TxtCpt);

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Another task is requesting control of the system.";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Eine andere Anwendung fordert die Kontrolle \\u00fcber das System an.";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::DENY, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::ALLOW, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrgum --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecIaqLive::leaveSgeAlrgum(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrgum --- INSERT
};

string PnlIdecIaqLive::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void PnlIdecIaqLive::handleRequest(
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
		if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECINIT) {
			handleDpchAppIdecInit(dbsidec, (DpchAppIdecInit*) (req->dpchapp), &(req->dpcheng));

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQLIVEDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQLIVEDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTREGULARIZECLICK) {
					handleDpchAppDoButRegularizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMINIMIZECLICK) {
					handleDpchAppDoButMinimizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTSNAPCLICK) {
					handleDpchAppDoButSnapClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTRECCLICK) {
					handleDpchAppDoButRecClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPLAYCLICK) {
					handleDpchAppDoButPlayClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTSTOPCLICK) {
					handleDpchAppDoButStopClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
		handleTimer(dbsidec, req->sref);
	};
};

void PnlIdecIaqLive::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecIaqLive::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	muteRefresh = true;

	if (has(diffitems, ContIac::NUMFPUPSRC)) {
		// preliminary
		contiac.numFPupSrc = _contiac->numFPupSrc;
		changeSource(dbsidec, feedFPupSrc.getIxByNum(contiac.numFPupSrc));
	};

	if (has(diffitems, ContIac::NUMFPUPRES)) contiac.numFPupRes = _contiac->numFPupRes;
	if (has(diffitems, ContIac::CHKGRS)) contiac.ChkGrs = _contiac->ChkGrs;

	if (has(diffitems, ContIac::SLDFRR)) contiac.SldFrr = _contiac->SldFrr;

	if (has(diffitems, ContIac::SLDEXT)) contiac.SldExt = _contiac->SldExt;

	refresh(dbsidec, moditems);

	muteRefresh = false;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecIaqLive::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButRegularizeClick --- RBEGIN

	set<uint> moditems;

	statshr.ixIdecVExpstate = VecIdecVExpstate::REGD;
	insert(moditems, DpchEngData::STATSHR);

	refreshLive(dbsidec, moditems);

	if (started()) {
		invalidateWakeups();
		wrefLast = xchg->addWakeup(jref, "idle", 500000, true);
	};

	*dpcheng = getNewDpchEng(moditems);

	// IP handleDpchAppDoButRegularizeClick --- REND
};

void PnlIdecIaqLive::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMinimizeClick --- RBEGIN

	invalidateWakeups();

	statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;
	*dpcheng = getNewDpchEng({DpchEngData::STATSHR});

	// IP handleDpchAppDoButMinimizeClick --- REND
};

void PnlIdecIaqLive::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN

	muteRefresh = true;

	if (jobfusion) if (jobfusion->jref != jobfusion->jrefMast) xchg->claimMaster(dbsidec, jobfusion->jref);
	if (joblwiracq) if (joblwiracq->jref != joblwiracq->jrefMast) xchg->claimMaster(dbsidec, joblwiracq->jref);
	if (jobstereo) if (jobstereo->jref != jobstereo->jrefMast) xchg->claimMaster(dbsidec, jobstereo->jref);
	if (jobtrigger) if (jobtrigger->jref != jobtrigger->jrefMast) xchg->claimMaster(dbsidec, jobtrigger->jref);
	if (jobvislacq) if (jobvislacq->jref != jobvislacq->jrefMast) xchg->claimMaster(dbsidec, jobvislacq->jref);
	if (jobvisracq) if (jobvisracq->jref != jobvisracq->jrefMast) xchg->claimMaster(dbsidec, jobvisracq->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;

	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecIaqLive::handleDpchAppDoButSnapClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButSnapClick --- IBEGIN

	jobrecord->snapshot(dbsidec);
	*dpcheng = new DpchEngIdecConfirm(true, jref);

	// IP handleDpchAppDoButSnapClick --- IEND
};

void PnlIdecIaqLive::handleDpchAppDoButRecClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButRecClick --- INSERT
};

void PnlIdecIaqLive::handleDpchAppDoButPlayClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPlayClick --- IBEGIN

	muteRefresh = true;

	fnew = 0;
	fps = 0.0;

	jobtrigger->start(dbsidec, contiac.SldFrr);

	if (ixVSource == VecVSource::VISL) {
		if (contiac.ChkGrs) {
			if (gray) delete gray;
			gray = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::GRAY16);

			jobvislacq->start(dbsidec, {gray});

		} else {
			if (red) delete red;
			red = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::RED8);
			if (green) delete green;
			green = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::GREEN8);
			if (blue) delete blue;
			blue = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::BLUE8);

			jobvislacq->start(dbsidec, {red,green,blue});
		};

	} else if (ixVSource == VecVSource::VISR) {
		if (contiac.ChkGrs) {
			if (gray) delete gray;
			gray = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::GRAY16);

			jobvisracq->start(dbsidec, {gray});

		} else {
			if (red) delete red;
			red = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::RED8);
			if (green) delete green;
			green = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::GREEN8);
			if (blue) delete blue;
			blue = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::BLUE8);

			jobvisracq->start(dbsidec, {red,green,blue});
		};

	} else if (ixVSource == VecVSource::LWIR) {
		if (gray) delete gray;
		gray = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::GRAY16);

		joblwiracq->start(dbsidec, {gray});

	} else if (ixVSource == VecVSource::STEREO) {
		if (depth) delete depth;
		depth = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::DEPTHSP);

		jobstereo->start(dbsidec, {depth});

	} else if (ixVSource == VecVSource::FUSION) {
		if (red) delete red;
		red = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::RED8);
		if (green) delete green;
		green = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::GREEN8);
		if (blue) delete blue;
		blue = new Snippet(feedFPupRes.getIxByNum(contiac.numFPupRes), VecIdecVChannel::BLUE8);

		jobfusion->start(dbsidec, {red,green,blue});
	};

	if ((statshr.ixIdecVExpstate == VecIdecVExpstate::REGD) && (joblwiracq || jobvislacq || jobvisracq || jobstereo || jobfusion)) {
		invalidateWakeups();
		wrefLast = xchg->addWakeup(jref, "idle", 500000, true);
	};

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;

	// IP handleDpchAppDoButPlayClick --- IEND
};

void PnlIdecIaqLive::handleDpchAppDoButStopClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButStopClick --- IBEGIN

	muteRefresh = true;

	if (ixVSource == VecVSource::VISL) jobvislacq->stop(dbsidec);
	else if (ixVSource == VecVSource::VISR) jobvisracq->stop(dbsidec);
	else if (ixVSource == VecVSource::LWIR) joblwiracq->stop(dbsidec);
	else if (ixVSource == VecVSource::STEREO) jobstereo->stop(dbsidec);
	else if (ixVSource == VecVSource::FUSION) jobfusion->stop(dbsidec);

	jobtrigger->stop(dbsidec);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;

	// IP handleDpchAppDoButStopClick --- IEND
};

void PnlIdecIaqLive::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppIdecAlert --- INSERT
};

void PnlIdecIaqLive::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if ((ixVSge == VecVSge::IDLE) && (sref == "idle")) {
		// IP handleTimer.idle --- IBEGIN

		set<uint> moditems;

		fps = 0.6*fps + 0.4*2.0*((double) fnew);
		fnew = 0;

		if (statshr.ixIdecVExpstate == VecIdecVExpstate::REGD)
					if (started()) wrefLast = xchg->addWakeup(jref, "idle", 500000, true);

		if (!muteRefresh) {
			refreshLive(dbsidec, moditems);
			if (!moditems.empty()) xchg->submitDpch(new DpchEngLive(jref, &continf, {}, {}, {}, {}, {}, {}, {DpchEngLive::JREF, DpchEngLive::CONTINF}));
		};

		// IP handleTimer.idle --- IEND
	};
};

void PnlIdecIaqLive::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECIMGRDY) {
		call->abort = handleCallIdecImgrdy(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSPTFND) {
		call->abort = handleCallIdecSptfnd(dbsidec, call->jref, call->argInv.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecIaqLive::handleCallIdecImgrdy(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecImgrdy --- IBEGIN

	DpchEngLive* dpchlive = NULL;

	set<uint> mask;

	if (statshr.ixIdecVExpstate == VecIdecVExpstate::REGD) {
		if (ixVSource == VecVSource::VISL) {
			if (jrefTrig == jobvislacq->jref) {
				fnew++;

				if (contiac.ChkGrs) insert(mask, DpchEngLive::GRAY);
				else {
/*
					insert(mask, DpchEngLive::RED);
					insert(mask, DpchEngLive::GREEN);
					insert(mask, DpchEngLive::BLUE);
*/
					insert(mask, DpchEngLive::RGB);
				};
			};
		};

		if (ixVSource == VecVSource::VISR) {
			if (jrefTrig == jobvisracq->jref) {
				fnew++;

				if (contiac.ChkGrs) insert(mask, DpchEngLive::GRAY);
				else {
					insert(mask, DpchEngLive::RED);
					insert(mask, DpchEngLive::GREEN);
					insert(mask, DpchEngLive::BLUE);
				};
			};
		};
		
		if (ixVSource == VecVSource::LWIR) {
			if (jrefTrig == joblwiracq->jref) {
				fnew++;

				insert(mask, DpchEngLive::GRAY);
			};
		};
		
		if (ixVSource == VecVSource::STEREO) {
			if (jrefTrig == jobstereo->jref) {
				fnew++;

				insert(mask, DpchEngLive::DEPTH);
			};
		};

		if (ixVSource == VecVSource::FUSION) {
			if (jrefTrig == jobfusion->jref) {
				fnew++;

				insert(mask, DpchEngLive::RED);
				insert(mask, DpchEngLive::GREEN);
				insert(mask, DpchEngLive::BLUE);
			};
		};

		if (!mask.empty()) {
			insert(mask, DpchEngLive::JREF);

			dpchlive = new DpchEngLive(jref, NULL, {}, {}, {}, {}, {}, {}, mask);

			if (has(mask, DpchEngLive::RED)) {
				dpchlive->red.resize(red->w*red->h);
				memcpy((void*) dpchlive->red.data(), (void*) red->data, red->w*red->h);
			};
			if (has(mask, DpchEngLive::GREEN)) {
				dpchlive->green.resize(green->w*green->h);
				memcpy((void*) dpchlive->green.data(), (void*) green->data, green->w*green->h);
			};
			if (has(mask, DpchEngLive::BLUE)) {
				dpchlive->blue.resize(blue->w*blue->h);
				memcpy((void*) dpchlive->blue.data(), (void*) blue->data, blue->w*blue->h);
			};
///
			if (has(mask, DpchEngLive::RGB)) {
				size_t rgblen = 4*red->w*red->h;

				dpchlive->rgb.resize(rgblen);

				memset((void*) dpchlive->rgb.data(), 0xFF, rgblen);

				unsigned int i = 0;
				for (unsigned int ix=0;ix<rgblen;ix+=4) {
					dpchlive->rgb[ix] = red->data[i];
					dpchlive->rgb[ix+1] = green->data[i];
					dpchlive->rgb[ix+2] = blue->data[i];

					i++;
				};
			};
///
			if (has(mask, DpchEngLive::GRAY)) {
///
				gray->addDottext("Alexander Wirthmueller", VecIdecVCorner::NW, 10, false);
				gray->addDottext("Rue Louis-Bourguet 16", VecIdecVCorner::N, 10, true);
				gray->addDottext("2000 Neuchatel", VecIdecVCorner::NE, 10, false);
				gray->addDottext("Switzerland", VecIdecVCorner::E, 10, true);
				gray->addDottext("+41 32 534 4662", VecIdecVCorner::SE, 10, false);
				gray->addDottext("+41 76 597 1514 (mobile)", VecIdecVCorner::S, 10, true);
				gray->addDottext("awirthm(at)gmail.com", VecIdecVCorner::SW, 10, false);
				gray->addDottext("www.epsitechnologies.com", VecIdecVCorner::W, 10, true);
///
				dpchlive->gray.resize(gray->w*gray->h);
				memcpy((void*) dpchlive->gray.data(), (void*) gray->data, 2*gray->w*gray->h);
			};
			if (has(mask, DpchEngLive::DEPTH)) {
				dpchlive->depth.resize(depth->w*depth->h);
				memcpy((void*) dpchlive->depth.data(), (void*) depth->data, 4*depth->w*depth->h);
			};

			xchg->submitDpch(dpchlive);
		};
	};

	// IP handleCallIdecImgrdy --- IEND
	return retval;
};

bool PnlIdecIaqLive::handleCallIdecSptfnd(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const bool boolvalInv
		) {
	bool retval = false;
	// IP handleCallIdecSptfnd --- INSERT
	return retval;
};

bool PnlIdecIaqLive::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- IBEGIN

	bool toidle = false;

	if (ixVSource == VecVSource::VISL) toidle = ((jrefTrig == jobvislacq->jref) && !jobvislacq->started());
	else if (ixVSource == VecVSource::VISR) toidle = ((jrefTrig == jobvisracq->jref) && !jobvisracq->started());
	else if (ixVSource == VecVSource::LWIR) toidle = ((jrefTrig == joblwiracq->jref) && !joblwiracq->started());
	else if (ixVSource == VecVSource::STEREO) toidle = ((jrefTrig == jobstereo->jref) && !jobstereo->started());
	else if (ixVSource == VecVSource::FUSION) toidle = ((jrefTrig == jobfusion->jref) && !jobfusion->started());

	if (toidle) {
		invalidateWakeups();
		if (!muteRefresh) refreshWithDpchEng(dbsidec);
	};

	// IP handleCallIdecStatChg --- IEND
	return retval;
};

bool PnlIdecIaqLive::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN

	if (!muteRefresh) refreshWithDpchEng(dbsidec);

	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


