/**
  * \file PnlIdecMisRec.cpp
  * job handler for job PnlIdecMisRec (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecMisRec.h"

#include "PnlIdecMisRec_blks.cpp"
#include "PnlIdecMisRec_evals.cpp"

/******************************************************************************
 class PnlIdecMisRec
 ******************************************************************************/

PnlIdecMisRec::PnlIdecMisRec(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECMISREC, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	pnldetail = NULL;
	pnl1ntour = NULL;
	pnlref1nfile = NULL;

	// IP constructor.cust1 --- INSERT

	// IP constructor.cust2 --- INSERT

	// IP constructor.cust3 --- INSERT

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFMIS, jref);
};

PnlIdecMisRec::~PnlIdecMisRec() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecMisRec::getNewDpchEng(
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

void PnlIdecMisRec::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// continf
	continf.TxtRef = StubIdec::getStubMisStd(dbsidec, recMis.ref, ixIdecVLocale, Stub::VecVNonetype::FULL);

	// statshr
	if (recMis.ref == 0) statshr.ixIdecVExpstate = VecIdecVExpstate::MIND;

	statshr.ButRegularizeActive = evalButRegularizeActive(dbsidec);

	if (statshr.ixIdecVExpstate == VecIdecVExpstate::MIND) {
		if (pnldetail) {delete pnldetail; pnldetail = NULL;};
		if (pnl1ntour) {delete pnl1ntour; pnl1ntour = NULL;};
		if (pnlref1nfile) {delete pnlref1nfile; pnlref1nfile = NULL;};
	} else {
		if (!pnldetail) pnldetail = new PnlIdecMisDetail(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnl1ntour) pnl1ntour = new PnlIdecMis1NTour(xchg, dbsidec, jref, ixIdecVLocale);
		if (!pnlref1nfile) pnlref1nfile = new PnlIdecMisRef1NFile(xchg, dbsidec, jref, ixIdecVLocale);
	};

	statshr.jrefDetail = ((pnldetail) ? pnldetail->jref : 0);
	statshr.jref1NTour = ((pnl1ntour) ? pnl1ntour->jref : 0);
	statshr.jrefRef1NFile = ((pnlref1nfile) ? pnlref1nfile->jref : 0);

	// IP refresh --- END
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

};

void PnlIdecMisRec::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFMIS) {
		IdecMMission* _recMis = NULL;

		if (dbsidec->tblidecmmission->loadRecByRef(xchg->getRefPreset(VecIdecVPreset::PREIDECREFMIS, jref), &_recMis)) {
			recMis = *_recMis;
			delete _recMis;
		} else recMis = IdecMMission();

		if (recMis.ref != 0) {
			if (pnldetail) pnldetail->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnl1ntour) pnl1ntour->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
			if (pnlref1nfile) pnlref1nfile->updatePreset(dbsidec, ixIdecVPreset, jrefTrig, notif);
		};

		refresh(dbsidec, moditems);
		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecMisRec::minimize(
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

void PnlIdecMisRec::regularize(
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

void PnlIdecMisRec::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECMISRECDO) {
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

void PnlIdecMisRec::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecMisRec::handleDpchAppDoButMinimizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	minimize(dbsidec, true, dpcheng);
};

void PnlIdecMisRec::handleDpchAppDoButRegularizeClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	regularize(dbsidec, true, dpcheng);
};

void PnlIdecMisRec::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECMISUPD_REFEQ) {
		call->abort = handleCallIdecMisUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecMisRec::handleCallIdecMisUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecMisUpd_refEq --- INSERT
	return retval;
};

