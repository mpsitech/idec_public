/**
  * \file PnlIdecScfStatus.cpp
  * job handler for job PnlIdecScfStatus (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecScfStatus.h"

#include "PnlIdecScfStatus_blks.cpp"
#include "PnlIdecScfStatus_evals.cpp"

/******************************************************************************
 class PnlIdecScfStatus
 ******************************************************************************/

PnlIdecScfStatus::PnlIdecScfStatus(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECSCFSTATUS, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";

	jobfusion = NULL;
	jobmechctl = NULL;
	jobqcdacq = NULL;
	jobrecord = NULL;
	jobstereo = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	jobfusion = new JobIdecFusion(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobmechctl = new JobIdecMechctl(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobqcdacq = new JobIdecQcdacq(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobrecord = new JobIdecRecord(xchg, dbsidec, jref, ixIdecVLocale, true);
	jobstereo = new JobIdecStereo(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTGCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecScfStatus::~PnlIdecScfStatus() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecScfStatus::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &continf, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecScfStatus::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN
	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (jobfusion) continf.ButMasterOn = (jobfusion->jref == jobfusion->jrefMast);
	if (continf.ButMasterOn && jobmechctl) continf.ButMasterOn = (jobmechctl->jref == jobmechctl->jrefMast);
	if (continf.ButMasterOn && jobqcdacq) continf.ButMasterOn = (jobqcdacq->jref == jobqcdacq->jrefMast);
	if (continf.ButMasterOn && jobrecord) continf.ButMasterOn = (jobrecord->jref == jobrecord->jrefMast);
	if (continf.ButMasterOn && jobstereo) continf.ButMasterOn = (jobstereo->jref == jobstereo->jrefMast);

	if (xchg->stgjobidecmechctltheta.tcalib == 0) continf.TxtThe = "-"; else continf.TxtThe = Ftm::stamp(xchg->stgjobidecmechctltheta.tcalib);
	if (xchg->stgjobidecmechctlphi.tcalib == 0) continf.TxtPhi = "-"; else continf.TxtPhi = Ftm::stamp(xchg->stgjobidecmechctlphi.tcalib);
	if (xchg->stgjobidecstereo.tcalib == 0) continf.TxtSte = "-"; else continf.TxtSte = Ftm::stamp(xchg->stgjobidecstereo.tcalib);
	if (xchg->stgjobidecfusion.tcalib == 0) continf.TxtFus = "-"; else continf.TxtFus = Ftm::stamp(xchg->stgjobidecfusion.tcalib);
	if (xchg->stgjobidecqcdacq.tcalnuc == 0) continf.TxtQnu = "-"; else continf.TxtQnu = Ftm::stamp(xchg->stgjobidecqcdacq.tcalnuc);
	if (xchg->stgjobidecqcdacq.tcalaln == 0) continf.TxtQal = "-"; else continf.TxtQal = Ftm::stamp(xchg->stgjobidecqcdacq.tcalaln);

	ListIdecMFile fils;

	struct statvfs stats;

	unsigned long used, free;

	used = 0;
	dbsidec->tblidecmfile->loadRstBySQL("SELECT * FROM TblIdecMFile", false, fils);
	for (unsigned int i=0;i<fils.nodes.size();i++) used += fils.nodes[i]->Size;
	used /= 1000;

	statvfs(xchg->acvpath.c_str(), &stats);
	free = stats.f_bsize * stats.f_bfree;
	free /= 1000000;

	if (ixIdecVLocale == VecIdecVLocale::ENUS) continf.TxtAcv = "&mbused;MB in &fileN; file(s), &mbfree;MB of free memory";
	else if (ixIdecVLocale == VecIdecVLocale::DECH) continf.TxtAcv = "&mbused;MB in &fileN; Datei(en), &mbfree;MB freier Speicherplatz";

	continf.TxtAcv = StrMod::replacePlh(continf.TxtAcv, "mbused", to_string(used));
	continf.TxtAcv = StrMod::replacePlh(continf.TxtAcv, "fileN", to_string(fils.nodes.size()));
	continf.TxtAcv = StrMod::replacePlh(continf.TxtAcv, "mbfree", to_string(free));

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	statshr.ButTheClearActive = evalButTheClearActive(dbsidec);
	statshr.ButPhiClearActive = evalButPhiClearActive(dbsidec);
	statshr.ButSteClearActive = evalButSteClearActive(dbsidec);
	statshr.ButFusClearActive = evalButFusClearActive(dbsidec);
	statshr.ButQnuClearActive = evalButQnuClearActive(dbsidec);
	statshr.ButQalClearActive = evalButQalClearActive(dbsidec);
	statshr.ButAcvClearActive = evalButAcvClearActive(dbsidec);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecScfStatus::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::ALRCTH: leaveSgeAlrcth(dbsidec); break;
				case VecVSge::ALRCPH: leaveSgeAlrcph(dbsidec); break;
				case VecVSge::ALRCST: leaveSgeAlrcst(dbsidec); break;
				case VecVSge::ALRCFU: leaveSgeAlrcfu(dbsidec); break;
				case VecVSge::ALRCQN: leaveSgeAlrcqn(dbsidec); break;
				case VecVSge::ALRCQA: leaveSgeAlrcqa(dbsidec); break;
				case VecVSge::ALRCAC: leaveSgeAlrcac(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::ALRCTH: _ixVSge = enterSgeAlrcth(dbsidec, reenter); break;
			case VecVSge::ALRCPH: _ixVSge = enterSgeAlrcph(dbsidec, reenter); break;
			case VecVSge::ALRCST: _ixVSge = enterSgeAlrcst(dbsidec, reenter); break;
			case VecVSge::ALRCFU: _ixVSge = enterSgeAlrcfu(dbsidec, reenter); break;
			case VecVSge::ALRCQN: _ixVSge = enterSgeAlrcqn(dbsidec, reenter); break;
			case VecVSge::ALRCQA: _ixVSge = enterSgeAlrcqa(dbsidec, reenter); break;
			case VecVSge::ALRCAC: _ixVSge = enterSgeAlrcac(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint PnlIdecScfStatus::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void PnlIdecScfStatus::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcth(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCTH;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcth --- BEGIN
	continf.TxtCpt = VecIdecVTag::getTitle(VecIdecVTag::QUEST, ixIdecVLocale);
	continf.TxtCpt = StrMod::cap(continf.TxtCpt);

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the \\u03d1-axis calibration?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie die Kalibrierung der \\u03d1-Achse wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcth --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcth(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcth --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcph(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCPH;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcph --- BEGIN
	continf.TxtCpt = "AlrCph";

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the \\u03c6-axis calibration?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie die Kalibrierung der \\u03c6-Achse wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcph --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcph(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcph --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcst(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCST;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcst --- BEGIN
	continf.TxtCpt = "AlrCst";

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the stereo overlay calibration?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie die Kalibrierung der Stereo-\\u00dcberlagerung wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcst --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcst(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcst --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcfu(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCFU;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcfu --- BEGIN
	continf.TxtCpt = "AlrCfu";

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the VIS-LWIR overlay calibration?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie die Kalibrierung der VIS-LWIR \\u00dcberlagerung wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcfu --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcfu(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcfu --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcqn(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCQN;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcqn --- BEGIN
	continf.TxtCpt = "AlrCqn";

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the QCD non-uniformity calibration?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie die Kalibrierung der QCD-Ungleichf\\u00f6rmigkeit wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcqn --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcqn(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcqn --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcqa(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCQA;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcqa --- BEGIN
	continf.TxtCpt = "AlrCqa";

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the QCD alignment calibration?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie die Kalibrierung der QCD-Ausrichtung wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcqa --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcqa(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcqa --- INSERT
};

uint PnlIdecScfStatus::enterSgeAlrcac(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRCAC;
	nextIxVSge = retval;
	ContInfIdecAlert continf;
	// IP enterSgeAlrcac --- BEGIN
	continf.TxtCpt = "AlrCac";

	if (ixIdecVLocale == VecIdecVLocale::ENUS) {
		continf.TxtMsg1 = "Are you sure you want to clear the archive?";
	} else if (ixIdecVLocale == VecIdecVLocale::DECH) {
		continf.TxtMsg1 = "Wollen Sie das Archiv wirklich l\\u00f6schen?";
	};

	feedFMcbAlert.clear();

	VecIdecVTag::appendToFeed(VecIdecVTag::CANCEL, ixIdecVLocale, feedFMcbAlert);
	VecIdecVTag::appendToFeed(VecIdecVTag::PROCEED, ixIdecVLocale, feedFMcbAlert);
	// IP enterSgeAlrcac --- END
	xchg->submitDpch(new DpchEngIdecAlert(jref, &continf, &feedFMcbAlert, {DpchEngIdecAlert::ALL}));
	return retval;
};

void PnlIdecScfStatus::leaveSgeAlrcac(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlrcac --- INSERT
};

string PnlIdecScfStatus::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void PnlIdecScfStatus::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFSTATUSDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECLEARCLICK) {
					handleDpchAppDoButTheClearClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICLEARCLICK) {
					handleDpchAppDoButPhiClearClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTSTECLEARCLICK) {
					handleDpchAppDoButSteClearClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTFUSCLEARCLICK) {
					handleDpchAppDoButFusClearClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTQNUCLEARCLICK) {
					handleDpchAppDoButQnuClearClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTQALCLEARCLICK) {
					handleDpchAppDoButQalClearClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTACVCLEARCLICK) {
					handleDpchAppDoButAcvClearClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

void PnlIdecScfStatus::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecScfStatus::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobfusion) if (jobfusion->jref != jobfusion->jrefMast) xchg->claimMaster(dbsidec, jobfusion->jref);
	if (jobmechctl) if (jobmechctl->jref != jobmechctl->jrefMast) xchg->claimMaster(dbsidec, jobmechctl->jref);
	if (jobqcdacq) if (jobqcdacq->jref != jobqcdacq->jrefMast) xchg->claimMaster(dbsidec, jobqcdacq->jref);
	if (jobstereo) if (jobstereo->jref != jobstereo->jrefMast) xchg->claimMaster(dbsidec, jobstereo->jref);
	if (jobstereo) if (jobstereo->jref != jobstereo->jrefMast) xchg->claimMaster(dbsidec, jobstereo->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecScfStatus::handleDpchAppDoButTheClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppDoButPhiClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppDoButSteClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButSteClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppDoButFusClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButFusClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppDoButQnuClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButQnuClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppDoButQalClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButQalClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppDoButAcvClearClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButAcvClearClick --- INSERT
};

void PnlIdecScfStatus::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppIdecAlert --- INSERT
};

void PnlIdecScfStatus::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTGCHG) {
		call->abort = handleCallIdecStgChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecScfStatus::handleCallIdecStgChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStgChg --- INSERT
	return retval;
};

bool PnlIdecScfStatus::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


