/**
  * \file CrdIdecNav.cpp
  * job handler for job CrdIdecNav (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "CrdIdecNav.h"

#include "CrdIdecNav_blks.cpp"
#include "CrdIdecNav_evals.cpp"

/******************************************************************************
 class CrdIdecNav
 ******************************************************************************/

CrdIdecNav::CrdIdecNav(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::CRDIDECNAV, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	dlgloaini = NULL;
	pnlheadbar = NULL;
	pnlpre = NULL;
	pnlmaint = NULL;
	pnlopr = NULL;

	// IP constructor.cust1 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	pnlheadbar = new PnlIdecNavHeadbar(xchg, dbsidec, jref, ixIdecVLocale);
	pnlpre = new PnlIdecNavPre(xchg, dbsidec, jref, ixIdecVLocale);
	pnlmaint = new PnlIdecNavMaint(xchg, dbsidec, jref, ixIdecVLocale);
	pnlopr = new PnlIdecNavOpr(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefHeadbar = pnlheadbar->jref;
	statshr.jrefPre = pnlpre->jref;
	statshr.jrefMaint = pnlmaint->jref;
	statshr.jrefOpr = pnlopr->jref;

	changeStage(dbsidec, VecVSge::IDLE);

	xchg->addClstn(VecIdecVCall::CALLIDECDLGCLOSE, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

CrdIdecNav::~CrdIdecNav() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* CrdIdecNav::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &continf, &feedFSge, &statshr, items);
	};

	return dpcheng;
};

void CrdIdecNav::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	string s;
	vector<string> ss;

	// continf
	continf.MrlAppHlp = xchg->helpurl + "/CrdIdecNav/" + VecIdecVLocale::getSref(ixIdecVLocale);

	s = StubIdec::getStubSesMenu(dbsidec, xchg->getRefPreset(VecIdecVPreset::PREIDECSESS, jref), ixIdecVLocale, Stub::VecVNonetype::DASH);
	StrMod::stringToVector(s, ss);

	if (ss.size() == 3) {
		continf.MtxSesSes1 = ss[0];
		continf.MtxSesSes2 = ss[1];
		continf.MtxSesSes3 = ss[2];
	};

	// statshr
	statshr.pnlpreAvail = evalPnlpreAvail(dbsidec);
	statshr.pnlmaintAvail = evalPnlmaintAvail(dbsidec);
	statshr.pnloprAvail = evalPnloprAvail(dbsidec);
	statshr.MspCrd1Avail = evalMspCrd1Avail(dbsidec);
	statshr.MitCrdUsgAvail = evalMitCrdUsgAvail(dbsidec);
	statshr.MitCrdUsrAvail = evalMitCrdUsrAvail(dbsidec);
	statshr.MitCrdScfAvail = evalMitCrdScfAvail(dbsidec);
	statshr.MitCrdUtlAvail = evalMitCrdUtlAvail(dbsidec);
	statshr.MspCrd2Avail = evalMspCrd2Avail(dbsidec);
	statshr.MitCrdMisAvail = evalMitCrdMisAvail(dbsidec);
	statshr.MitCrdTouAvail = evalMitCrdTouAvail(dbsidec);
	statshr.MitCrdIaqAvail = evalMitCrdIaqAvail(dbsidec);
	statshr.MitCrdIaqActive = evalMitCrdIaqActive(dbsidec);
	statshr.MitCrdAd1Avail = evalMitCrdAd1Avail(dbsidec);
	statshr.MitCrdAd1Active = evalMitCrdAd1Active(dbsidec);
	statshr.MitCrdFilAvail = evalMitCrdFilAvail(dbsidec);
	statshr.MspApp2Avail = evalMspApp2Avail(dbsidec);
	statshr.MitAppLoiAvail = evalMitAppLoiAvail(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void CrdIdecNav::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	refresh(dbsidec, moditems);
	if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));

	if (pnlpre) if (jrefTrig != pnlpre->jref) pnlpre->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
	if (pnlmaint) pnlmaint->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
	if (pnlopr) pnlopr->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
	// IP updatePreset --- END
};

void CrdIdecNav::changeStage(
			DbsIdec* dbsidec
			, uint _ixVSge
			, DpchEngIdec** dpcheng
		) {
	bool reenter = true;

	do {
		if (ixVSge != _ixVSge) {
			switch (ixVSge) {
				case VecVSge::IDLE: leaveSgeIdle(dbsidec); break;
				case VecVSge::ALRIDECABT: leaveSgeAlridecabt(dbsidec); break;
				case VecVSge::CLOSE: leaveSgeClose(dbsidec); break;
			};

			ixVSge = _ixVSge;
			reenter = false;
			if (!muteRefresh) refreshWithDpchEng(dbsidec, dpcheng); // IP changeStage.refresh1 --- LINE
		};

		switch (_ixVSge) {
			case VecVSge::IDLE: _ixVSge = enterSgeIdle(dbsidec, reenter); break;
			case VecVSge::ALRIDECABT: _ixVSge = enterSgeAlridecabt(dbsidec, reenter); break;
			case VecVSge::CLOSE: _ixVSge = enterSgeClose(dbsidec, reenter); break;
		};

		// IP changeStage.refresh2 --- INSERT
	} while (ixVSge != _ixVSge);
};

uint CrdIdecNav::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void CrdIdecNav::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint CrdIdecNav::enterSgeAlridecabt(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECABT;
	nextIxVSge = VecVSge::IDLE;
	xchg->submitDpch(AlrIdec::prepareAlrAbt(jref, ixIdecVLocale, feedFMcbAlert)); // IP enterSgeAlridecabt --- LINE
	return retval;
};

void CrdIdecNav::leaveSgeAlridecabt(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecabt --- INSERT
};

uint CrdIdecNav::enterSgeClose(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CLOSE;
	nextIxVSge = retval;
	xchg->triggerIxCall(dbsidec, VecIdecVCall::CALLIDECCRDCLOSE, jref, VecIdecVCard::CRDIDECNAV);
	return retval;
};

void CrdIdecNav::leaveSgeClose(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeClose --- INSERT
};

string CrdIdecNav::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void CrdIdecNav::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECNAVDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::CLOSE) {
					handleDpchAppDoClose(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITAPPABTCLICK) {
					handleDpchAppDoMitAppAbtClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITSESTRMCLICK) {
					handleDpchAppDoMitSesTrmClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDUSGCLICK) {
					handleDpchAppDoMitCrdUsgClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDUSRCLICK) {
					handleDpchAppDoMitCrdUsrClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDSCFCLICK) {
					handleDpchAppDoMitCrdScfClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDUTLCLICK) {
					handleDpchAppDoMitCrdUtlClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDMISCLICK) {
					handleDpchAppDoMitCrdMisClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDTOUCLICK) {
					handleDpchAppDoMitCrdTouClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDIAQCLICK) {
					handleDpchAppDoMitCrdIaqClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDAD1CLICK) {
					handleDpchAppDoMitCrdAd1Click(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDFILCLICK) {
					handleDpchAppDoMitCrdFilClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITAPPLOICLICK) {
					handleDpchAppDoMitAppLoiClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

void CrdIdecNav::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void CrdIdecNav::handleDpchAppDoClose(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecNav::handleDpchAppDoMitAppAbtClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoMitAppAbtClick --- BEGIN
	changeStage(dbsidec, VecVSge::ALRIDECABT, dpcheng);
	// IP handleDpchAppDoMitAppAbtClick --- END
};

void CrdIdecNav::handleDpchAppDoMitSesTrmClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecNav::handleDpchAppDoMitCrdUsgClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecUsg", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUsg");
};

void CrdIdecNav::handleDpchAppDoMitCrdUsrClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecUsr", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUsr");
};

void CrdIdecNav::handleDpchAppDoMitCrdScfClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecScf", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecScf");
};

void CrdIdecNav::handleDpchAppDoMitCrdUtlClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecUtl", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecUtl");
};

void CrdIdecNav::handleDpchAppDoMitCrdMisClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecMis", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecMis");
};

void CrdIdecNav::handleDpchAppDoMitCrdTouClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecTou", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecTou");
};

void CrdIdecNav::handleDpchAppDoMitCrdIaqClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecIaq", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecIaq");
};

void CrdIdecNav::handleDpchAppDoMitCrdAd1Click(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecAd1", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecAd1");
};

void CrdIdecNav::handleDpchAppDoMitCrdFilClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;

	xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, "CrdIdecFil", 0, jrefNew);

	if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
	else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, "CrdIdecFil");
};

void CrdIdecNav::handleDpchAppDoMitAppLoiClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgloaini) {
		dlgloaini = new DlgIdecNavLoaini(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgloaini = dlgloaini->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecNav::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	if (ixVSge == VecVSge::ALRIDECABT) {
		changeStage(dbsidec, VecVSge::IDLE);
	};

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
};

void CrdIdecNav::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECDLGCLOSE) {
		call->abort = handleCallIdecDlgClose(dbsidec, call->jref);
	};
};

bool CrdIdecNav::handleCallIdecDlgClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;

	if (dlgloaini) {
		delete dlgloaini;
		dlgloaini = NULL;
		statshr.jrefDlgloaini = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	};

	return retval;
};

