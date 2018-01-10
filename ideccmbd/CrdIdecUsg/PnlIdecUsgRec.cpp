/**
  * \file PnlIdecUsgRec.cpp
  * job handler for job PnlIdecUsgRec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecUsgRec.h"

#include "PnlIdecUsgRec_blks.cpp"
#include "PnlIdecUsgRec_evals.cpp"

/******************************************************************************
 class PnlIdecUsgRec
 ******************************************************************************/

PnlIdecUsgRec::PnlIdecUsgRec(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECUSGREC, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	pnldetail = NULL;
	pnlaaccess = NULL;
	pnlmnuser = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.cust2 --- INSERT

	// IP constructor.cust3 --- INSERT

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFUSG, jref);
};

PnlIdecUsgRec::~PnlIdecUsgRec() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecUsgRec::getNewDpchEng(
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

void PnlIdecUsgRec::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.TxtRef = StubIdec::getStubUsgStd(dbsidec, recUsg.ref, ixIdecVLocale, Stub::VecVNonetype::FULL);

	// statshr
	if (recUsg.ref == 0) statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;

	statshr.ButRegularizeActive = evalButRegularizeActive(dbsidec);

	if (statshr.ixIdecVExpstate == VecIdecVExpstate::MIND) {
		if (pnldetail) {delete pnldetail; pnldetail = NULL;};
		if (pnlaaccess) {delete pnlaaccess; pnlaaccess = NULL;};
		if (pnlmnuser) {delete pnlmnuser; pnlmnuser = NULL;};
	} else {
		if (!pnldetail) pnldetail = new PnlIdecUsgDetail(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnlaaccess) pnlaaccess = new PnlIdecUsgAAccess(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnlmnuser) pnlmnuser = new PnlIdecUsgMNUser(xchg, dbsidec, jref, ixIdecVLocale);
	};

	statshr.jrefDetail = ((pnldetail) ? pnldetail->jref : 0);
	statshr.jrefAAccess = ((pnlaaccess) ? pnlaaccess->jref : 0);
	statshr.jrefMNUser = ((pnlmnuser) ? pnlmnuser->jref : 0);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

};

void PnlIdecUsgRec::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFUSG) {
		IdecMUsergroup* _recUsg = NULL;

		if (dbsidec->tblidecmusergroup->loadRecByRef(xchg->getRefPreset(VecIdecVPreset::PREIDECREFUSG, jref), &_recUsg)) {
			recUsg = *_recUsg;
			delete _recUsg;
		} else recUsg = IdecMUsergroup();

		if (recUsg.ref != 0) {
			if (pnldetail) pnldetail->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnlaaccess) pnlaaccess->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnlmnuser) pnlmnuser->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
		};

		refresh(dbsidec, moditems);
		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecUsgRec::minimize(
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

void PnlIdecUsgRec::regularize(
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

void PnlIdecUsgRec::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECUSGRECDO) {
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

void PnlIdecUsgRec::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecUsgRec::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	minimize(dbsidec, true, dpcheng);
};

void PnlIdecUsgRec::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	regularize(dbsidec, true, dpcheng);
};

void PnlIdecUsgRec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECUSGUPD_REFEQ) {
		call->abort = handleCallIdecUsgUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecUsgRec::handleCallIdecUsgUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecUsgUpd_refEq --- INSERT
	return retval;
};

