/**
  * \file PnlIdecUsrRec.cpp
  * job handler for job PnlIdecUsrRec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecUsrRec.h"

#include "PnlIdecUsrRec_blks.cpp"
#include "PnlIdecUsrRec_evals.cpp"

/******************************************************************************
 class PnlIdecUsrRec
 ******************************************************************************/

PnlIdecUsrRec::PnlIdecUsrRec(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECUSRREC, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	pnldetail = NULL;
	pnlaaccess = NULL;
	pnl1nsession = NULL;
	pnlmnusergroup = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.cust2 --- INSERT

	// IP constructor.cust3 --- INSERT

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFUSR, jref);
};

PnlIdecUsrRec::~PnlIdecUsrRec() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecUsrRec::getNewDpchEng(
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

void PnlIdecUsrRec::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.TxtRef = StubIdec::getStubUsrStd(dbsidec, recUsr.ref, ixIdecVLocale, Stub::VecVNonetype::FULL);

	// statshr
	if (recUsr.ref == 0) statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;

	statshr.ButRegularizeActive = evalButRegularizeActive(dbsidec);

	if (statshr.ixIdecVExpstate == VecIdecVExpstate::MIND) {
		if (pnldetail) {delete pnldetail; pnldetail = NULL;};
		if (pnlaaccess) {delete pnlaaccess; pnlaaccess = NULL;};
		if (pnl1nsession) {delete pnl1nsession; pnl1nsession = NULL;};
		if (pnlmnusergroup) {delete pnlmnusergroup; pnlmnusergroup = NULL;};
	} else {
		if (!pnldetail) pnldetail = new PnlIdecUsrDetail(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnlaaccess) pnlaaccess = new PnlIdecUsrAAccess(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnl1nsession) pnl1nsession = new PnlIdecUsr1NSession(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnlmnusergroup) pnlmnusergroup = new PnlIdecUsrMNUsergroup(xchg, dbsidec, jref, ixIdecVLocale);
	};

	statshr.jrefDetail = ((pnldetail) ? pnldetail->jref : 0);
	statshr.jrefAAccess = ((pnlaaccess) ? pnlaaccess->jref : 0);
	statshr.jref1NSession = ((pnl1nsession) ? pnl1nsession->jref : 0);
	statshr.jrefMNUsergroup = ((pnlmnusergroup) ? pnlmnusergroup->jref : 0);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

};

void PnlIdecUsrRec::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSR) {
		IdecMUser* _recUsr = NULL;

		if (dbsidec->tblidecmuser->loadRecByRef(xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSR, jref), &_recUsr)) {
			recUsr = *_recUsr;
			delete _recUsr;
		} else recUsr = IdecMUser();

		if (recUsr.ref != 0) {
			if (pnldetail) pnldetail->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnlaaccess) pnlaaccess->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnl1nsession) pnl1nsession->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnlmnusergroup) pnlmnusergroup->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
		};

		refresh(dbsidec, moditems);
		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecUsrRec::minimize(
			DbsIdec* dbsidec
			, const bool notif
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	if (statshr.ixIdecVExpstate != VecIdecVExpstate::MIND) {
		statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;
		insert(moditems, DpchEngData::STATSHR);

		refresh(dbsidec, moditems);
	};

	if (notif) {
		if (dpcheng) *dpcheng = getNewDpchEng(moditems);
		else if (!moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
};

void PnlIdecUsrRec::regularize(
			DbsIdec* dbsidec
			, const bool notif
			, DpchEngIdec** dpcheng
		) {
	set<uint> moditems;

	if (statshr.ixIdecVExpstate != VecIdecVExpstate::REGD) {
		statshr.ixIdecVExpstate = VecIdecVExpstate::REGD;
		insert(moditems, DpchEngData::STATSHR);

		refresh(dbsidec, moditems);
	};

	if (notif) {
		if (dpcheng) *dpcheng = getNewDpchEng(moditems);
		else if (!moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
};

void PnlIdecUsrRec::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSRRECDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTMINIMIZECLICK) {
					handleDpchAppDoButMinimizeClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTREGULARIZECLICK) {
					handleDpchAppDoButRegularizeClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecUsrRec::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecUsrRec::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	minimize(dbsidec, true, dpcheng);
};

void PnlIdecUsrRec::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	regularize(dbsidec, true, dpcheng);
};

void PnlIdecUsrRec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECUSRUPD_REFEQ) {
		call->abort = handleCallIdecUsrUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecUsrRec::handleCallIdecUsrUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecUsrUpd_refEq --- INSERT
	return retval;
};

