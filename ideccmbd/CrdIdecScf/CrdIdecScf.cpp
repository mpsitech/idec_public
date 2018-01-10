/**
  * \file CrdIdecScf.cpp
  * job handler for job CrdIdecScf (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "CrdIdecScf.h"

#include "CrdIdecScf_blks.cpp"

/******************************************************************************
 class CrdIdecScf
 ******************************************************************************/

CrdIdecScf::CrdIdecScf(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::CRDIDECSCF, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	feedFMcbAlert.tag = "FeedFMcbAlert";
	feedFSge.tag = "FeedFSge";
	VecVSge::fillFeed(feedFSge);

	pnlconn = NULL;
	pnlstatus = NULL;
	pnlmech = NULL;
	pnloptics = NULL;
	pnltrigger = NULL;
	pnllwir = NULL;
	pnlqcd = NULL;
	pnlrecord = NULL;
	pnlheadbar = NULL;

	// IP constructor.cust1 --- INSERT

	set<uint> moditems;
	refresh(dbsidec, moditems);

	pnlconn = new PnlIdecScfConn(xchg, dbsidec, jref, ixIdecVLocale);
	pnlstatus = new PnlIdecScfStatus(xchg, dbsidec, jref, ixIdecVLocale);
	pnlmech = new PnlIdecScfMech(xchg, dbsidec, jref, ixIdecVLocale);
	pnloptics = new PnlIdecScfOptics(xchg, dbsidec, jref, ixIdecVLocale);
	pnltrigger = new PnlIdecScfTrigger(xchg, dbsidec, jref, ixIdecVLocale);
	pnllwir = new PnlIdecScfLwir(xchg, dbsidec, jref, ixIdecVLocale);
	pnlqcd = new PnlIdecScfQcd(xchg, dbsidec, jref, ixIdecVLocale);
	pnlrecord = new PnlIdecScfRecord(xchg, dbsidec, jref, ixIdecVLocale);
	pnlheadbar = new PnlIdecScfHeadbar(xchg, dbsidec, jref, ixIdecVLocale);

	// IP constructor.cust2 --- INSERT

	statshr.jrefConn = pnlconn->jref;
	statshr.jrefStatus = pnlstatus->jref;
	statshr.jrefMech = pnlmech->jref;
	statshr.jrefOptics = pnloptics->jref;
	statshr.jrefTrigger = pnltrigger->jref;
	statshr.jrefLwir = pnllwir->jref;
	statshr.jrefQcd = pnlqcd->jref;
	statshr.jrefRecord = pnlrecord->jref;
	statshr.jrefHeadbar = pnlheadbar->jref;

	changeStage(dbsidec, VecVSge::IDLE);

	xchg->addClstn(VecIdecVCall::CALLIDECDLGCLOSE, jref, Clstn::VecVJobmask::IMM, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	// IP constructor.spec3 --- INSERT
};

CrdIdecScf::~CrdIdecScf() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* CrdIdecScf::getNewDpchEng(
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

void CrdIdecScf::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);

	// IP refresh --- BEGIN
	// continf
	continf.MrlAppHlp = xchg->helpurl + "/CrdIdecScf/" + VecIdecVLocale::getSref(ixIdecVLocale);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
};

void CrdIdecScf::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- INSERT
};

void CrdIdecScf::changeStage(
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

uint CrdIdecScf::enterSgeIdle(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::IDLE;
	nextIxVSge = retval;
	// IP enterSgeIdle --- INSERT
	return retval;
};

void CrdIdecScf::leaveSgeIdle(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeIdle --- INSERT
};

uint CrdIdecScf::enterSgeAlridecabt(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::ALRIDECABT;
	nextIxVSge = VecVSge::IDLE;
	xchg->submitDpch(AlrIdec::prepareAlrAbt(jref, ixIdecVLocale, feedFMcbAlert)); // IP enterSgeAlridecabt --- LINE
	return retval;
};

void CrdIdecScf::leaveSgeAlridecabt(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeAlridecabt --- INSERT
};

uint CrdIdecScf::enterSgeClose(
			DbsIdec* dbsidec
			, const bool reenter
		) {
	uint retval = VecVSge::CLOSE;
	nextIxVSge = retval;
	xchg->triggerIxCall(dbsidec, VecIdecVCall::CALLIDECCRDCLOSE, jref, VecIdecVCard::CRDIDECSCF);
	return retval;
};

void CrdIdecScf::leaveSgeClose(
			DbsIdec* dbsidec
		) {
	// IP leaveSgeClose --- INSERT
};

string CrdIdecScf::getSquawk(
			DbsIdec* dbsidec
		) {
	string retval;
	// IP getSquawk --- BEGIN
	retval = VecVSge::getSref(ixVSge);
	// IP getSquawk --- END
	return retval;
};

void CrdIdecScf::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECSCFDO) {
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

void CrdIdecScf::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void CrdIdecScf::handleDpchAppDoClose(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	muteRefresh = true;

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
	changeStage(dbsidec, VecVSge::CLOSE);
};

void CrdIdecScf::handleDpchAppDoMitAppAbtClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoMitAppAbtClick --- BEGIN
	changeStage(dbsidec, VecVSge::ALRIDECABT, dpcheng);
	// IP handleDpchAppDoMitAppAbtClick --- END
};

void CrdIdecScf::handleDpchAppIdecAlert(
			DbsIdec* dbsidec
			, DpchAppIdecAlert* dpchappidecalert
			, DpchEngIdec** dpcheng
		) {
	if (ixVSge == VecVSge::ALRIDECABT) {
		changeStage(dbsidec, VecVSge::IDLE);
	};

	*dpcheng = new DpchEngIdecConfirm(true, jref, "");
};

void CrdIdecScf::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECDLGCLOSE) {
		call->abort = handleCallIdecDlgClose(dbsidec, call->jref);
	};
};

bool CrdIdecScf::handleCallIdecDlgClose(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
		) {
	bool retval = false;
	// IP handleCallIdecDlgClose --- INSERT
	return retval;
};

