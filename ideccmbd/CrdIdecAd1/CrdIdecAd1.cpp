/**
  * \file CrdIdecAd1.cpp
  * job handler for job CrdIdecAd1 (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "CrdIdecAd1.h"

#include "CrdIdecAd1_blks.cpp"

/******************************************************************************
 class CrdIdecAd1
 ******************************************************************************/

CrdIdecAd1::CrdIdecAd1(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
			, const uint ixIdecVPreset
			, const ubigint preUref
		) : JobIdec(xchg, VecIdecVJob::CRDIDECAD1, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	pnlcontrol = NULL;
	pnlheadbar = NULL;

	// IP constructor.cust1 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	pnlcontrol = new PnlIdecAd1Control(xchg, dbsidec, jref, ixIdecVLocale);
	pnlheadbar = new PnlIdecAd1Headbar(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefControl = pnlcontrol->jref;
	statshr.jrefHeadbar = pnlheadbar->jref;

	changeStage(dbsidec, VecVSge::IDLE);

	xchg->addClstn(VecIdecVCall::CALLIDECDLGCLOSE, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

CrdIdecAd1::~CrdIdecAd1() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* CrdIdecAd1::getNewDpchEng(
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

void CrdIdecAd1::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);

	// IP refresh --- BEGIN
	// continf
	continf.MrlAppHlp = xchg->helpurl + "/CrdIdecAd1/" + VecIdecVLocale::getSref(ixIdecVLocale);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

void CrdIdecAd1::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- INSERT
};

void CrdIdecAd1::changeStage(
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

uint CrdIdecAd1::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void CrdIdecAd1::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint CrdIdecAd1::enterSgeAlridecabt(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECABT;
	nextIxVSge = VecVSge::IDLE;
	xchg->submitDpch(AlrIdec::prepareAlrAbt(jref, ixIdecVLocale, feedFMcbAlert)); // IP enterSgeAlridecabt --- LINE
	return retval;
};

void CrdIdecAd1::leaveSgeAlridecabt(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecabt --- INSERT
};

uint CrdIdecAd1::enterSgeClose(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CLOSE;
	nextIxVSge = retval;
	xchg->triggerIxCall(dbsidec, VecIdecVCall::CALLIDECCRDCLOSE, jref, VecIdecVCard::CRDIDECAD1);
	return retval;
};

void CrdIdecAd1::leaveSgeClose(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeClose --- INSERT
};

string CrdIdecAd1::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void CrdIdecAd1::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECAD1DO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::CLOSE) {
					handleDpchAppDoClose(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::MITAPPABTCLICK) {
					handleDpchAppDoMitAppAbtClick(dbsidec, &(req->dpcheng));
				};

			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECALERT) {
			handleDpchAppIdecAlert(dbsidec, (DpchAppIdecAlert*) (req->dpchapp), &(req->dpcheng));

		};
	};
};

void CrdIdecAd1::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void CrdIdecAd1::handleDpchAppDoClose(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecAd1::handleDpchAppDoMitAppAbtClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoMitAppAbtClick --- BEGIN
	changeStage(dbsidec, VecVSge::ALRIDECABT, dpcheng);
	// IP handleDpchAppDoMitAppAbtClick --- END
};

void CrdIdecAd1::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	if (ixVSge == VecVSge::ALRIDECABT) {
		changeStage(dbsidec, VecVSge::IDLE);
	};

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
};

void CrdIdecAd1::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECDLGCLOSE) {
		call->abort = handleCallIdecDlgClose(dbsidec, call->jref);
	};
};

bool CrdIdecAd1::handleCallIdecDlgClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecDlgClose --- INSERT
	return retval;
};

