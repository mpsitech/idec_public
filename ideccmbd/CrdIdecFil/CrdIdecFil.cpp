/**
  * \file CrdIdecFil.cpp
  * job handler for job CrdIdecFil (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "CrdIdecFil.h"

#include "CrdIdecFil_blks.cpp"
#include "CrdIdecFil_evals.cpp"

/******************************************************************************
 class CrdIdecFil
 ******************************************************************************/

CrdIdecFil::CrdIdecFil(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const ubigint ref
			, const uint ixIdecVPreset
			, const ubigint preUref
		) : JobIdec(xchg, VecIdecVJob::CRDIDECFIL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	dlgextrmed = NULL;
	pnlrec = NULL;
	pnlheadbar = NULL;
	pnllist = NULL;

	// IP constructor.cust1 --- INSERT

	xchg->addIxPreset(VecIdecVPreset::PREIDECIXPRE, jref, ixIdecVPreset);
	if (ixIdecVPreset != VecIdecVPreset::VOID) xchg->addRefPreset(ixIdecVPreset, jref, preUref);

	// initialize according to ref
	changeRef(dbsidec, jref, ((ref+1) == 0) ? 0 : ref, false);

	pnlrec = new PnlIdecFilRec(xchg, dbsidec, jref, ixIdecVLocale);
	pnlheadbar = new PnlIdecFilHeadbar(xchg, dbsidec, jref, ixIdecVLocale);
	pnllist = new PnlIdecFilList(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefHeadbar = pnlheadbar->jref;
	statshr.jrefList = pnllist->jref;
	statshr.jrefRec = pnlrec->jref;

	changeStage(dbsidec, VecVSge::IDLE);

	xchg->addClstn(VecIdecVCall::CALLIDECDLGCLOSE, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECSTATCHG, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);
	xchg->addClstn(VecIdecVCall::CALLIDECREFPRESET, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

CrdIdecFil::~CrdIdecFil() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* CrdIdecFil::getNewDpchEng(
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

void CrdIdecFil::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.MrlAppHlp = xchg->helpurl + "/CrdIdecFil/" + VecIdecVLocale::getSref(ixIdecVLocale);
	continf.MtxCrdFil = StubIdec::getStubFilStd(dbsidec, xchg->getRefPreset(VecIdecVPreset::PREIDECREFFIL, jref), ixIdecVLocale, Stub::VecVNonetype::FULL);

	// statshr
	statshr.MitCrdExmActive = evalMitCrdExmActive(dbsidec);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void CrdIdecFil::changeRef(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint ref
			, const bool notif
		) {
	set<uint> moditems;

	uint ixIdecVPreset = xchg->getIxPreset(VecIdecVPreset::PREIDECIXPRE, jref);

	uint ixIdecVAccess;
	xchg->triggerIxRefToIxCall(dbsidec, VecIdecVCall::CALLIDECACCESS, jref, VecIdecVMaintable::TBLIDECMFILE, ref, ixIdecVAccess);

	if (ixIdecVAccess != VecIdecVAccess::NONE) {
		xchg->addIxPreset(VecIdecVPreset::PREIDECIXACC, jref, ixIdecVAccess);

		if (ref != 0) xchg->triggerIxRefSrefIntvalCall(dbsidec, VecIdecVCall::CALLIDECLOG, jref, ixIdecVPreset, xchg->getRefPreset(ixIdecVPreset, jref), "CrdIdecFil", ref);
		xchg->addRefPreset(VecIdecVPreset::PREIDECREFFIL, jref, ref);

		refresh(dbsidec, moditems);
		if (notif) xchg->submitDpch(getNewDpchEng(moditems));

		if (pnllist) pnllist->updatePreset(dbsidec, VecIdecVPreset::PREIDECREFFIL, jrefTrig, notif);
		if (pnlrec) pnlrec->updatePreset(dbsidec, VecIdecVPreset::PREIDECREFFIL, jrefTrig, notif);
	};
};

void CrdIdecFil::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- INSERT
};

void CrdIdecFil::changeStage(
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

uint CrdIdecFil::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void CrdIdecFil::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint CrdIdecFil::enterSgeAlridecabt(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECABT;
	nextIxVSge = VecVSge::IDLE;
	xchg->submitDpch(AlrIdec::prepareAlrAbt(jref, ixIdecVLocale, feedFMcbAlert)); // IP enterSgeAlridecabt --- LINE
	return retval;
};

void CrdIdecFil::leaveSgeAlridecabt(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecabt --- INSERT
};

uint CrdIdecFil::enterSgeClose(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CLOSE;
	nextIxVSge = retval;
	xchg->triggerIxCall(dbsidec, VecIdecVCall::CALLIDECCRDCLOSE, jref, VecIdecVCard::CRDIDECFIL);
	return retval;
};

void CrdIdecFil::leaveSgeClose(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeClose --- INSERT
};

string CrdIdecFil::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void CrdIdecFil::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECFILDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::CLOSE) {
					handleDpchAppDoClose(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITAPPABTCLICK) {
					handleDpchAppDoMitAppAbtClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITCRDEXMCLICK) {
					handleDpchAppDoMitCrdExmClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

void CrdIdecFil::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void CrdIdecFil::handleDpchAppDoClose(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecFil::handleDpchAppDoMitAppAbtClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoMitAppAbtClick --- BEGIN
	changeStage(dbsidec, VecVSge::ALRIDECABT, dpcheng);
	// IP handleDpchAppDoMitAppAbtClick --- END
};

void CrdIdecFil::handleDpchAppDoMitCrdExmClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	if (!dlgextrmed) {
		dlgextrmed = new DlgIdecFilExtrmed(xchg, dbsidec, jref, ixIdecVLocale);
		statshr.jrefDlgextrmed = dlgextrmed->jref;

		*dpcheng = getNewDpchEng({DpchEngData::STATSHR});
	};
};

void CrdIdecFil::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	if (ixVSge == VecVSge::ALRIDECABT) {
		changeStage(dbsidec, VecVSge::IDLE);
	};

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
};

void CrdIdecFil::handleCall(
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

bool CrdIdecFil::handleCallIdecDlgClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;

	if (dlgextrmed) {
		delete dlgextrmed;
		dlgextrmed = NULL;
		statshr.jrefDlgextrmed = 0;

		xchg->submitDpch(getNewDpchEng({DpchEngData::STATSHR}));
	};

	return retval;
};

bool CrdIdecFil::handleCallIdecStatChg(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	if (jrefTrig == pnlrec->jref) if ((pnllist->statshr.ixIdecVExpstate == VecIdecVExpstate::REGD) && (pnlrec->statshr.ixIdecVExpstate == VecIdecVExpstate::REGD)) pnllist->minimize(dbsidec, true);
	return retval;
};

bool CrdIdecFil::handleCallIdecRefPreSet(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const uint ixInv
			, const ubigint refInv
		) {
	bool retval = false;

	if (ixInv == VecIdecVPreset::PREIDECREFFIL) {
		changeRef(dbsidec, jrefTrig, refInv, true);

		if (refInv == 0) pnlrec->minimize(dbsidec, true);
	};

	return retval;
};

