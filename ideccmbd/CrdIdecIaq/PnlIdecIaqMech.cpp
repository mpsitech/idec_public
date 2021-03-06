/**
  * \file PnlIdecIaqMech.cpp
  * job handler for job PnlIdecIaqMech (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecIaqMech.h"

#include "PnlIdecIaqMech_blks.cpp"
#include "PnlIdecIaqMech_evals.cpp"

/******************************************************************************
 class PnlIdecIaqMech
 ******************************************************************************/

PnlIdecIaqMech::PnlIdecIaqMech(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECIAQMECH, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFCsiPhiSte.tag = "FeedFCsiPhiSte";
	feedFCsiPhiSte.appendIxSrefTitles(VecIdecVAxisste::NC, "gry", VecIdecVAxisste::getTitle(VecIdecVAxisste::NC, ixIdecVLocale));
	feedFCsiPhiSte.appendIxSrefTitles(VecIdecVAxisste::UNCAL, "ong", VecIdecVAxisste::getTitle(VecIdecVAxisste::UNCAL, ixIdecVLocale));
	feedFCsiPhiSte.appendIxSrefTitles(VecIdecVAxisste::ACTUC, "ong.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTUC, ixIdecVLocale));
	feedFCsiPhiSte.appendIxSrefTitles(VecIdecVAxisste::READY, "grn", VecIdecVAxisste::getTitle(VecIdecVAxisste::READY, ixIdecVLocale));
	feedFCsiPhiSte.appendIxSrefTitles(VecIdecVAxisste::ACTIVE, "grn.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTIVE, ixIdecVLocale));
	feedFCsiTheSte.tag = "FeedFCsiTheSte";
	feedFCsiTheSte.appendIxSrefTitles(VecIdecVAxisste::NC, "gry", VecIdecVAxisste::getTitle(VecIdecVAxisste::NC, ixIdecVLocale));
	feedFCsiTheSte.appendIxSrefTitles(VecIdecVAxisste::UNCAL, "ong", VecIdecVAxisste::getTitle(VecIdecVAxisste::UNCAL, ixIdecVLocale));
	feedFCsiTheSte.appendIxSrefTitles(VecIdecVAxisste::ACTUC, "ong.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTUC, ixIdecVLocale));
	feedFCsiTheSte.appendIxSrefTitles(VecIdecVAxisste::READY, "grn", VecIdecVAxisste::getTitle(VecIdecVAxisste::READY, ixIdecVLocale));
	feedFCsiTheSte.appendIxSrefTitles(VecIdecVAxisste::ACTIVE, "grn.fl", VecIdecVAxisste::getTitle(VecIdecVAxisste::ACTIVE, ixIdecVLocale));
	feedFPupMod.tag = "FeedFPupMod";
	VecVMode::fillFeed(ixIdecVLocale, feedFPupMod);

	jobmechctl = NULL;

	// IP constructor.cust1 --- IBEGIN
	muteRefresh = false;
	// IP constructor.cust1 --- IEND

	jobmechctl = new JobIdecMechctl(xchg, dbsidec, jref, ixIdecVLocale, true);

	// IP constructor.cust2 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECMASTSLVCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

};

PnlIdecIaqMech::~PnlIdecIaqMech() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- IBEGIN
void PnlIdecIaqMech::refreshLive(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	double theta, phi;
	int thetarpm, phirpm;

	uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
	uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;

	jobmechctl->getThetaThetarpm(theta, thetarpm);
	jobmechctl->getPhiPhirpm(phi, phirpm);

	// continf
	ContInf oldContinf(continf);

	continf.TxtTheAng = to_string(theta);

	continf.TxtTheRpm = to_string(thetarpm);
	if (ixIdecVLocale == VecIdecVLocale::ENUS) continf.TxtTheRpm += "rpm";
	else if (ixIdecVLocale == VecIdecVLocale::DECH) continf.TxtTheRpm += "U/min";

	continf.numFCsiTheSte = feedFCsiTheSte.getNumByIx(_theIxIdecVAxisste);

	if (_theIxIdecVAxisste != VecIdecVAxisste::ACTIVE) {
		continf.ButTheCcwOn = false;
		continf.ButTheCwOn = false;
	};

	continf.TxtPhiAng = to_string(phi);

	continf.TxtPhiRpm = to_string(phirpm);
	if (ixIdecVLocale == VecIdecVLocale::ENUS) continf.TxtPhiRpm += "rpm";
	else if (ixIdecVLocale == VecIdecVLocale::DECH) continf.TxtPhiRpm += "U/min";

	continf.numFCsiPhiSte = feedFCsiPhiSte.getNumByIx(xchg->datajobidecmechctl.phiIxIdecVAxisste);

	if (_phiIxIdecVAxisste != VecIdecVAxisste::ACTIVE) {
		continf.ButPhiCcwOn = false;
		continf.ButPhiCwOn = false;
	};

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

// IP cust --- IEND
DpchEngIdec* PnlIdecIaqMech::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &feedFCsiPhiSte, &feedFCsiTheSte, &feedFPupMod, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecIaqMech::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- RBEGIN
	double& _theLlim = xchg->stgjobidecmechctltheta.llim;
	double& _theUlim = xchg->stgjobidecmechctltheta.ulim;
	double& _phiLlim = xchg->stgjobidecmechctlphi.llim;
	double& _phiUlim = xchg->stgjobidecmechctlphi.ulim;

	double theta, phi;
	int thetarpm, phirpm;

	jobmechctl->getThetaThetarpm(theta, thetarpm);
	jobmechctl->getPhiPhirpm(phi, phirpm);

	// contiac
	ContIac oldContiac(contiac);

//	contiac.numFPupMod;
//	contiac.SldTvv;

	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);

	// continf
	ContInf oldContinf(continf);

	continf.ButMasterOn = true;
	if (continf.ButMasterOn && jobmechctl) continf.ButMasterOn = (jobmechctl->jref == jobmechctl->jrefMast);

	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);

	// statshr
	//statshr.SldTvvAvail = CUSTOM;

	statshr.CusTheAnsMin = _theLlim;
	statshr.CusTheAnsMax = _theUlim;
	statshr.CusPhiAnsMin = _phiLlim;
	statshr.CusPhiAnsMax = _phiUlim;

	/// DEMO
/*
	statshr.CusTheAnsActive = evalCusTheAnsActive(dbsidec);
	statshr.ButTheCcwActive = evalButTheCcwActive(dbsidec);
	statshr.ButTheCcwstActive = evalButTheCcwstActive(dbsidec);
	statshr.ButTheCwstActive = evalButTheCwstActive(dbsidec);
	statshr.ButTheCwActive = evalButTheCwActive(dbsidec);
*/
	statshr.CusTheAnsActive = (jobmechctl->jref == jobmechctl->jrefMast);
	statshr.ButTheCcwActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (theta != _theUlim));
	statshr.ButTheCcwstActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (theta != _theUlim));
	statshr.ButTheCwstActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (theta != _theLlim));
	statshr.ButTheCwActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (theta != _theLlim));

/*
	statshr.CusPhiAnsActive = evalCusPhiAnsActive(dbsidec);
	statshr.ButPhiCcwActive = evalButPhiCcwActive(dbsidec);
	statshr.ButPhiCcwstActive = evalButPhiCcwstActive(dbsidec);
	statshr.ButPhiCwstActive = evalButPhiCwstActive(dbsidec);
	statshr.ButPhiCwActive = evalButPhiCwActive(dbsidec);
*/
	statshr.CusPhiAnsActive = (jobmechctl->jref == jobmechctl->jrefMast);
	statshr.ButPhiCcwActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (phi != _phiUlim));
	statshr.ButPhiCcwstActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (phi != _phiUlim));
	statshr.ButPhiCwstActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (phi != _phiLlim));
	statshr.ButPhiCwActive = ((jobmechctl->jref == jobmechctl->jrefMast) && (phi != _phiLlim));

	refreshLive(dbsidec, moditems);
	// IP refresh --- REND

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecIaqMech::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint PnlIdecIaqMech::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void PnlIdecIaqMech::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	invalidateWakeups();
	// IP leaveSgeIdle --- INSERT
};

string PnlIdecIaqMech::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void PnlIdecIaqMech::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQMECHDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECIAQMECHDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTREGULARIZECLICK) {
					handleDpchAppDoButRegularizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMINIMIZECLICK) {
					handleDpchAppDoButMinimizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMASTERCLICK) {
					handleDpchAppDoButMasterClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECCWCLICK) {
					handleDpchAppDoButTheCcwClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECCWSTMDN) {
					handleDpchAppDoButTheCcwstMdn(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECCWSTMUP) {
					handleDpchAppDoButTheCcwstMup(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECWSTMDN) {
					handleDpchAppDoButTheCwstMdn(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECWSTMUP) {
					handleDpchAppDoButTheCwstMup(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTTHECWCLICK) {
					handleDpchAppDoButTheCwClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICCWCLICK) {
					handleDpchAppDoButPhiCcwClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICCWSTMDN) {
					handleDpchAppDoButPhiCcwstMdn(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICCWSTMUP) {
					handleDpchAppDoButPhiCcwstMup(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICWSTMDN) {
					handleDpchAppDoButPhiCwstMdn(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICWSTMUP) {
					handleDpchAppDoButPhiCwstMup(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTPHICWCLICK) {
					handleDpchAppDoButPhiCwClick(dbsidec, &(req->dpcheng));
				};

			};

		};

	} else if (req->ixVBasetype == ReqIdec::VecVBasetype::TIMER) {
		handleTimer(dbsidec, req->sref);
	};
};

void PnlIdecIaqMech::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecIaqMech::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);
	// IP handleDpchAppDataContiac --- IBEGIN

	uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
	uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;

	muteRefresh = true;

	if (hasAny(diffitems, {ContIac::NUMFPUPMOD,ContIac::SLDTVV})) {
		if (has(diffitems, ContIac::NUMFPUPMOD)) contiac.numFPupMod = _contiac->numFPupMod;
		if (has(diffitems, ContIac::SLDTVV)) contiac.SldTvv = _contiac->SldTvv;
	};
	
	if (hasAny(diffitems, {ContIac::CUSTHEANS,ContIac::CUSPHIANS})) {
		if (has(diffitems, ContIac::CUSTHEANS)) {
			contiac.CusTheAns = _contiac->CusTheAns;
			if (contiac.CusTheAns < xchg->stgjobidecmechctltheta.llim) contiac.CusTheAns = xchg->stgjobidecmechctltheta.llim;
			if (contiac.CusTheAns > xchg->stgjobidecmechctltheta.ulim) contiac.CusTheAns = xchg->stgjobidecmechctltheta.ulim;

			jobmechctl->setTargetTheta(dbsidec, contiac.CusTheAns);
		};

		if (has(diffitems, ContIac::CUSPHIANS)) {
			contiac.CusPhiAns = _contiac->CusPhiAns;
			if (contiac.CusPhiAns < xchg->stgjobidecmechctlphi.llim) contiac.CusPhiAns = xchg->stgjobidecmechctlphi.llim;
			if (contiac.CusPhiAns > xchg->stgjobidecmechctlphi.ulim) contiac.CusPhiAns = xchg->stgjobidecmechctlphi.ulim;

			jobmechctl->setTargetPhi(dbsidec, contiac.CusPhiAns);
		};

		if (statshr.ixIdecVExpstate == VecIdecVExpstate::REGD) {
			if ((_theIxIdecVAxisste == VecIdecVAxisste::ACTIVE) || (_phiIxIdecVAxisste == VecIdecVAxisste::ACTIVE)) {
				invalidateWakeups();
				wrefLast = xchg->addWakeup(jref, "idle", 100000, true);
			};
		};

		refresh(dbsidec, moditems);
	};

	muteRefresh = false;

	// IP handleDpchAppDataContiac --- IEND
	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecIaqMech::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButRegularizeClick --- RBEGIN
	set<uint> moditems;

	uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
	uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;

	statshr.ixIdecVExpstate = VecIdecVExpstate::REGD;
	insert(moditems, DpchEngData::STATSHR);

	if ((_theIxIdecVAxisste == VecIdecVAxisste::ACTIVE) || (_phiIxIdecVAxisste == VecIdecVAxisste::ACTIVE)) {
		invalidateWakeups();
		wrefLast = xchg->addWakeup(jref, "idle", 100000, true);
	};

	refreshLive(dbsidec, moditems);

	*dpcheng = getNewDpchEng(moditems);
	// IP handleDpchAppDoButRegularizeClick --- REND
};

void PnlIdecIaqMech::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMinimizeClick --- RBEGIN
	invalidateWakeups();

	statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;
	*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	// IP handleDpchAppDoButMinimizeClick --- REND
};

void PnlIdecIaqMech::handleDpchAppDoButMasterClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButMasterClick --- IBEGIN
	muteRefresh = true;

	if (jobmechctl) if (jobmechctl->jref != jobmechctl->jrefMast) xchg->claimMaster(dbsidec, jobmechctl->jref);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButMasterClick --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButTheCcwClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheCcwClick --- IBEGIN
	set<uint> moditems;

	muteRefresh = true;

	jobmechctl->setTargetTheta(dbsidec, xchg->stgjobidecmechctltheta.ulim);

	continf.ButTheCcwOn = true;
	insert(moditems, DpchEngData::CONTINF);

	refresh(dbsidec, moditems);
	*dpcheng = getNewDpchEng(moditems);

	muteRefresh = false;
	// IP handleDpchAppDoButTheCcwClick --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButTheCcwstMdn(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheCcwstMdn --- IBEGIN
	muteRefresh = true;

	jobmechctl->setTargetTheta(dbsidec, xchg->stgjobidecmechctltheta.ulim);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButTheCcwstMdn --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButTheCcwstMup(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheCcwstMup --- IBEGIN
	jobmechctl->stopTheta();
	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	// IP handleDpchAppDoButTheCcwstMup --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButTheCwstMdn(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheCwstMdn --- IBEGIN
	muteRefresh = true;

	jobmechctl->setTargetTheta(dbsidec, xchg->stgjobidecmechctltheta.llim);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButTheCwstMdn --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButTheCwstMup(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheCwstMup --- IBEGIN
	jobmechctl->stopTheta();
	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	// IP handleDpchAppDoButTheCwstMup --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButTheCwClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButTheCwClick --- IBEGIN
	set<uint> moditems;

	muteRefresh = true;

	jobmechctl->setTargetTheta(dbsidec, xchg->stgjobidecmechctltheta.llim);

	continf.ButTheCwOn = true;
	insert(moditems, DpchEngData::CONTINF);

	refresh(dbsidec, moditems);
	*dpcheng = getNewDpchEng(moditems);

	muteRefresh = false;
	// IP handleDpchAppDoButTheCwClick --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButPhiCcwClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiCcwClick --- IBEGIN
	set<uint> moditems;

	muteRefresh = true;

	jobmechctl->setTargetPhi(dbsidec, xchg->stgjobidecmechctlphi.ulim);

	continf.ButPhiCcwOn = true;
	insert(moditems, DpchEngData::CONTINF);

	refresh(dbsidec, moditems);
	*dpcheng = getNewDpchEng(moditems);

	muteRefresh = false;
	// IP handleDpchAppDoButPhiCcwClick --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButPhiCcwstMdn(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiCcwstMdn --- IBEGIN
	muteRefresh = true;

	jobmechctl->setTargetPhi(dbsidec, xchg->stgjobidecmechctlphi.ulim);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButPhiCcwstMdn --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButPhiCcwstMup(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiCcwstMup --- IBEGIN
	jobmechctl->stopPhi();
	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	// IP handleDpchAppDoButPhiCcwstMup --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButPhiCwstMdn(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiCwstMdn --- IBEGIN
	muteRefresh = true;

	jobmechctl->setTargetPhi(dbsidec, xchg->stgjobidecmechctlphi.llim);

	refreshWithDpchEng(dbsidec, dpcheng);

	muteRefresh = false;
	// IP handleDpchAppDoButPhiCwstMdn --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButPhiCwstMup(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiCwstMup --- IBEGIN
	jobmechctl->stopPhi();
	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	// IP handleDpchAppDoButPhiCwstMup --- IEND
};

void PnlIdecIaqMech::handleDpchAppDoButPhiCwClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButPhiCwClick --- IBEGIN
	set<uint> moditems;

	muteRefresh = true;

	jobmechctl->setTargetPhi(dbsidec, xchg->stgjobidecmechctlphi.llim);

	continf.ButPhiCwOn = true;
	insert(moditems, DpchEngData::CONTINF);

	refresh(dbsidec, moditems);
	*dpcheng = getNewDpchEng(moditems);

	muteRefresh = false;
	// IP handleDpchAppDoButPhiCwClick --- IEND
};

void PnlIdecIaqMech::handleTimer(
			DbsIdec* dbsidec
			, const string& sref
		) {
	if ((ixVSge == VecVSge::IDLE) && (sref == "idle")) {
		// IP handleTimer.idle --- IBEGIN
		set<uint> moditems;

		uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
		uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;

		if (statshr.ixIdecVExpstate == VecIdecVExpstate::REGD)
					if ((_theIxIdecVAxisste == VecIdecVAxisste::ACTIVE) || (_phiIxIdecVAxisste == VecIdecVAxisste::ACTIVE))
								wrefLast = xchg->addWakeup(jref, "idle", 100000, true);

		if (!muteRefresh) {
			refreshLive(dbsidec, moditems);
			if (!moditems.empty()) xchg->submitDpch(new DpchEngLive(jref, &continf, {DpchEngLive::ALL}));
		};
		// IP handleTimer.idle --- IEND
	};
};

void PnlIdecIaqMech::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECMASTSLVCHG) {
		call->abort = handleCallIdecMastslvChg(dbsidec, call->jref);
	};
};

bool PnlIdecIaqMech::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecStatChg --- IBEGIN

	uint& _theIxIdecVAxisste = xchg->datajobidecmechctl.theIxIdecVAxisste;
	uint& _phiIxIdecVAxisste = xchg->datajobidecmechctl.phiIxIdecVAxisste;

	if (jrefTrig == jobmechctl->jref) {
		invalidateWakeups();

		if (statshr.ixIdecVExpstate == VecIdecVExpstate::REGD)
					if ((_theIxIdecVAxisste == VecIdecVAxisste::ACTIVE) || (_phiIxIdecVAxisste == VecIdecVAxisste::ACTIVE))
								wrefLast = xchg->addWakeup(jref, "idle", 100000, true);
	};

	if (!muteRefresh) refreshWithDpchEng(dbsidec);

	// IP handleCallIdecStatChg --- IEND
	return retval;
};

bool PnlIdecIaqMech::handleCallIdecMastslvChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecMastslvChg --- IBEGIN
	if (!muteRefresh) refreshWithDpchEng(dbsidec);
	// IP handleCallIdecMastslvChg --- IEND
	return retval;
};


