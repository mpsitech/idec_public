/**
  * \file CrdIdecTou.cpp
  * job handler for job CrdIdecTou (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "CrdIdecTou.h"

#include "CrdIdecTou_blks.cpp"
#include "CrdIdecTou_evals.cpp"

/******************************************************************************
 class CrdIdecTou
 ******************************************************************************/

CrdIdecTou::CrdIdecTou(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const ubigint ref
			, const uint ixIdecVPreset
			, const ubigint preUref
		) : JobIdec(xchg, VecIdecVJob::CRDIDECTOU, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	dlgnew = NULL;
	pnlrec = NULL;
	pnlheadbar = NULL;
	pnllist = NULL;

	// IP constructor.cust1 --- INSERT

	xchg->addIxPreset(VecIdecVPreset::PREIDECIXPRE, jref, ixIdecVPreset);
	if (ixIdecVPreset != VecIdecVPreset::VOID) xchg->addRefPreset(ixIdecVPreset, jref, preUref);

	// initialize according to ref
	changeRef(dbsidec, jref, ((ref+1) == 0) ? 0 : ref, false);

	pnlrec = new PnlIdecTouRec(xchg, dbsidec, jref, ixIdecVLocale);
	pnlheadbar = new PnlIdecTouHeadbar(xchg, dbsidec, jref, ixIdecVLocale);
	pnllist = new PnlIdecTouList(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefHeadbar = pnlheadbar->jref;
	statshr.jrefList = pnllist->jref;
	statshr.jrefRec = pnlrec->jref;

	if ((ref+1) == 0) {
		dlgnew = new DlgIdecTouNew(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgnew = dlgnew->jref;
	};

	changeStage(dbsidec, VecVSge::IDLE);

	xchg->addClstn(VecIdecVCall::CALLIDECDLGCLOSE, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECREFPRESET, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

CrdIdecTou::~CrdIdecTou() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* CrdIdecTou::getNewDpchEng(
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

void CrdIdecTou::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.MrlAppHlp = xchg->helpurl + "/CrdIdecTou/" + VecIdecVLocale::getSref(ixIdecVLocale);
	continf.MtxCrdTou = StubIdec::getStubTouStd(dbsidec, xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref), ixIdecVLocale, Stub::VecVNonetype::FULL);

	// statshr
	statshr.MspCrd1Avail = evalMspCrd1Avail(dbsidec);
	statshr.MitCrdNewAvail = evalMitCrdNewAvail(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void CrdIdecTou::changeRef(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint ref
			, const bool notif
		) {
	set<uint> moditems;

	uint ixIdecVPreset = xchg->getIxPreset(VecIdecVPreset::PREIDECIXPRE, jref);

	if (ref != 0) xchg->triggerIxRefSrefIntvalCall(dbsidec, VecIdecVCall::CALLIDECLOG, jref, ixIdecVPreset, xchg->getRefPreset(ixIdecVPreset, jref), "CrdIdecTou", ref);
	xchg->addRefPreset(VecIdecVPreset::PREIDECREFTOU, jref, ref);

	refresh(dbsidec, moditems);
	if (notif) xchg->submitDpch(getNewDpchEng(moditems));

	if (pnllist) pnllist->updatePreset(dbsidec, VecIdecVPreset::PREIDECREFTOU, jrefTrig, notif);
	if (pnlrec) pnlrec->updatePreset(dbsidec, VecIdecVPreset::PREIDECREFTOU, jrefTrig, notif);
};

void CrdIdecTou::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- INSERT
};

void CrdIdecTou::changeStage(
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

uint CrdIdecTou::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void CrdIdecTou::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint CrdIdecTou::enterSgeAlridecabt(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECABT;
	nextIxVSge = VecVSge::IDLE;
	xchg->submitDpch(AlrIdec::prepareAlrAbt(jref, ixIdecVLocale, feedFMcbAlert)); // IP enterSgeAlridecabt --- LINE
	return retval;
};

void CrdIdecTou::leaveSgeAlridecabt(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecabt --- INSERT
};

uint CrdIdecTou::enterSgeClose(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CLOSE;
	nextIxVSge = retval;
	xchg->triggerIxCall(dbsidec, VecIdecVCall::CALLIDECCRDCLOSE, jref, VecIdecVCard::CRDIDECTOU);
	return retval;
};

void CrdIdecTou::leaveSgeClose(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeClose --- INSERT
};

string CrdIdecTou::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void CrdIdecTou::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::CLOSE) {
					handleDpchAppDoClose(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITAPPABTCLICK) {
					handleDpchAppDoMitAppAbtClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDNEWCLICK) {
					handleDpchAppDoMitCrdNewClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

void CrdIdecTou::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void CrdIdecTou::handleDpchAppDoClose(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecTou::handleDpchAppDoMitAppAbtClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoMitAppAbtClick --- BEGIN
	changeStage(dbsidec, VecVSge::ALRIDECABT, dpcheng);
	// IP handleDpchAppDoMitAppAbtClick --- END
};

void CrdIdecTou::handleDpchAppDoMitCrdNewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgnew) {
		dlgnew = new DlgIdecTouNew(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgnew = dlgnew->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecTou::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	if (ixVSge == VecVSge::ALRIDECABT) {
		changeStage(dbsidec, VecVSge::IDLE);
	};

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
};

void CrdIdecTou::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECDLGCLOSE) {
		call->abort = handleCallIdecDlgClose(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECSTATCHG) {
		call->abort = handleCallIdecStatChg(dbsidec, call->jref);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECREFPRESET) {
		call->abort = handleCallIdecRefPreSet(dbsidec, call->jref, call->argInv.ix, call->argInv.ref);
	};
};

bool CrdIdecTou::handleCallIdecDlgClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;

	if (dlgnew) {
		delete dlgnew;
		dlgnew = NULL;
		statshr.jrefDlgnew = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	};

	return retval;
};

bool CrdIdecTou::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	if (jrefTrig == pnlrec->jref) if ((pnllist->statshr.ixIdecVExpstate == VecIdecVExpstate::REGD) && (pnlrec->statshr.ixIdecVExpstate == VecIdecVExpstate::REGD)) pnllist->minimize(dbsidec, true);
	return retval;
};

bool CrdIdecTou::handleCallIdecRefPreSet(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
		) {
	bool retval = false;

	if (ixInv == VecIdecVPreset::PREIDECREFTOU) {
		changeRef(dbsidec, jrefTrig, refInv, true);

		if (refInv == 0) pnlrec->minimize(dbsidec, true);
		else if ((jrefTrig == statshr.jrefDlgnew) && (refInv != 0)) {
			pnllist->qry->rerun(dbsidec, true);
			pnllist->minimize(dbsidec, true);
			pnlrec->regularize(dbsidec, true);
		};
	};

	return retval;
};

