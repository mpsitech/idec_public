/**
  * \file PnlIdecTouDetail.cpp
  * job handler for job PnlIdecTouDetail (implementation)
  * \author Alexander Wirthmueller
  * \date created: 30 Dec 2017
  * \date modified: 30 Dec 2017
  */

#ifdef IDECCMBD
	#include <Ideccmbd.h>
#else
	#include <Idecd.h>
#endif

#include "PnlIdecTouDetail.h"

#include "PnlIdecTouDetail_blks.cpp"
#include "PnlIdecTouDetail_evals.cpp"

/******************************************************************************
 class PnlIdecTouDetail
 ******************************************************************************/

PnlIdecTouDetail::PnlIdecTouDetail(
			XchgIdec* xchg
			, DbsIdec* dbsidec
			, const ubigint jrefSup
			, const uint ixIdecVLocale
		) : JobIdec(xchg, VecIdecVJob::PNLIDECTOUDETAIL, jrefSup, ixIdecVLocale) {

	jref = xchg->addJob(this);

	// IP constructor.cust1 --- INSERT

	dirty = false;

	// IP constructor.cust2 --- INSERT

	xchg->addClstn(VecIdecVCall::CALLIDECTOU_MISEQ, jref, Clstn::VecVJobmask::TREE, 0, Arg(), Clstn::VecVJactype::LOCK);

	// IP constructor.cust3 --- INSERT

	updatePreset(dbsidec, VecIdecVPreset::PREIDECREFTOU, jref);
};

PnlIdecTouDetail::~PnlIdecTouDetail() {
	// IP destructor.spec --- INSERT

	// IP destructor.cust --- INSERT

	xchg->removeJobByJref(jref);
};

// IP cust --- INSERT
DpchEngIdec* PnlIdecTouDetail::getNewDpchEng(
			set<uint> items
		) {
	DpchEngIdec* dpcheng = NULL;

	if (items.empty()) {
		dpcheng = new DpchEngIdecConfirm(true, jref, "");
	} else {
		insert(items, DpchEngData::JREF);
		dpcheng = new DpchEngData(jref, &contiac, &continf, &statshr, items);
	};

	return dpcheng;
};

void PnlIdecTouDetail::refreshRecTou(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	ContIac oldContiac(contiac);
	ContInf oldContinf(continf);
	StatShr oldStatshr(statshr);

	IdecMTour* _recTou = NULL;

	if (dbsidec->tblidecmtour->loadRecByRef(recTou.ref, &_recTou)) {
		recTou = *_recTou;
		delete _recTou;
	} else recTou = IdecMTour();

	dirty = false;

	contiac.TxfTit = recTou.Title;
	continf.TxtMis = StubIdec::getStubMisStd(dbsidec, recTou.refIdecMMission, ixIdecVLocale, Stub::VecVNonetype::FULL);
	contiac.TxfSta = Ftm::stamp(recTou.start);
	contiac.TxfSto = Ftm::stamp(recTou.stop);
	contiac.TxfAre = recTou.Area;
	contiac.TxfThe = to_string(recTou.theta);
	contiac.TxfPhi = to_string(recTou.phi);
	contiac.TxfCmt = recTou.Comment;

	statshr.TxfTitActive = evalTxfTitActive(dbsidec);
	statshr.TxtMisActive = evalTxtMisActive(dbsidec);
	statshr.ButMisViewAvail = evalButMisViewAvail(dbsidec);
	statshr.ButMisViewActive = evalButMisViewActive(dbsidec);
	statshr.TxfStaActive = evalTxfStaActive(dbsidec);
	statshr.TxfStoActive = evalTxfStoActive(dbsidec);
	statshr.TxfAreActive = evalTxfAreActive(dbsidec);
	statshr.TxfTheActive = evalTxfTheActive(dbsidec);
	statshr.TxfPhiActive = evalTxfPhiActive(dbsidec);
	statshr.TxfCmtActive = evalTxfCmtActive(dbsidec);
	if (contiac.diff(&oldContiac).size() != 0) insert(moditems, DpchEngData::CONTIAC);
	if (continf.diff(&oldContinf).size() != 0) insert(moditems, DpchEngData::CONTINF);
	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);

};

void PnlIdecTouDetail::refresh(
			DbsIdec* dbsidec
			, set<uint>& moditems
		) {
	StatShr oldStatshr(statshr);

	// IP refresh --- BEGIN
	// statshr
	statshr.ButSaveAvail = evalButSaveAvail(dbsidec);
	statshr.ButSaveActive = evalButSaveActive(dbsidec);
	// IP refresh --- END

	if (statshr.diff(&oldStatshr).size() != 0) insert(moditems, DpchEngData::STATSHR);
};

void PnlIdecTouDetail::updatePreset(
			DbsIdec* dbsidec
			, const uint ixIdecVPreset
			, const ubigint jrefTrig
			, const bool notif
		) {
	// IP updatePreset --- BEGIN
	set<uint> moditems;

	if (ixIdecVPreset == VecIdecVPreset::PREIDECREFTOU) {
		recTou.ref = xchg->getRefPreset(VecIdecVPreset::PREIDECREFTOU, jref);
		refreshRecTou(dbsidec, moditems);

		if (notif && !moditems.empty()) xchg->submitDpch(getNewDpchEng(moditems));
	};
	// IP updatePreset --- END
};

void PnlIdecTouDetail::handleRequest(
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

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUDETAILDATA) {
			DpchAppData* dpchappdata = (DpchAppData*) (req->dpchapp);

			if (dpchappdata->has(DpchAppData::CONTIAC)) {
				handleDpchAppDataContiac(dbsidec, &(dpchappdata->contiac), &(req->dpcheng));
			};

		} else if (req->dpchapp->ixIdecVDpch == VecIdecVDpch::DPCHAPPIDECTOUDETAILDO) {
			DpchAppDo* dpchappdo = (DpchAppDo*) (req->dpchapp);

			if (dpchappdo->ixVDo != 0) {
				if (dpchappdo->ixVDo == VecVDo::BUTSAVECLICK) {
					handleDpchAppDoButSaveClick(dbsidec, &(req->dpcheng));
				} else if (dpchappdo->ixVDo == VecVDo::BUTMISVIEWCLICK) {
					handleDpchAppDoButMisViewClick(dbsidec, &(req->dpcheng));
				};

			};

		};
	};
};

void PnlIdecTouDetail::handleDpchAppIdecInit(
			DbsIdec* dbsidec
			, DpchAppIdecInit* dpchappidecinit
			, DpchEngIdec** dpcheng
		) {
	*dpcheng = getNewDpchEng({DpchEngData::ALL});
};

void PnlIdecTouDetail::handleDpchAppDataContiac(
			DbsIdec* dbsidec
			, ContIac* _contiac
			, DpchEngIdec** dpcheng
		) {
	set<uint> diffitems;
	set<uint> moditems;

	diffitems = _contiac->diff(&contiac);

	if (hasAny(diffitems, {ContIac::TXFTIT, ContIac::TXFSTA, ContIac::TXFSTO, ContIac::TXFARE, ContIac::TXFTHE, ContIac::TXFPHI, ContIac::TXFCMT})) {
		if (has(diffitems, ContIac::TXFTIT)) contiac.TxfTit = _contiac->TxfTit;
		if (has(diffitems, ContIac::TXFSTA)) contiac.TxfSta = _contiac->TxfSta;
		if (has(diffitems, ContIac::TXFSTO)) contiac.TxfSto = _contiac->TxfSto;
		if (has(diffitems, ContIac::TXFARE)) contiac.TxfAre = _contiac->TxfAre;
		if (has(diffitems, ContIac::TXFTHE)) contiac.TxfThe = _contiac->TxfThe;
		if (has(diffitems, ContIac::TXFPHI)) contiac.TxfPhi = _contiac->TxfPhi;
		if (has(diffitems, ContIac::TXFCMT)) contiac.TxfCmt = _contiac->TxfCmt;
	};

	insert(moditems, DpchEngData::CONTIAC);
	*dpcheng = getNewDpchEng(moditems);
};

void PnlIdecTouDetail::handleDpchAppDoButSaveClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	// IP handleDpchAppDoButSaveClick --- INSERT
};

void PnlIdecTouDetail::handleDpchAppDoButMisViewClick(
			DbsIdec* dbsidec
			, DpchEngIdec** dpcheng
		) {
	ubigint jrefNew = 0;
	string sref;

	if (statshr.ButMisViewAvail && statshr.ButMisViewActive) {
		if (xchg->getIxPreset(VecIdecVPreset::PREIDECIXUACMIS, jref)) {
			sref = "CrdIdecMis";
			xchg->triggerIxRefSrefIntvalToRefCall(dbsidec, VecIdecVCall::CALLIDECCRDOPEN, jref, 0, 0, sref, recTou.refIdecMMission, jrefNew);
		};

		if (jrefNew == 0) *dpcheng = new DpchEngIdecConfirm(false, 0, "");
		else *dpcheng = new DpchEngIdecConfirm(true, jrefNew, sref);
	};
};

void PnlIdecTouDetail::handleCall(
			DbsIdec* dbsidec
			, Call* call
		) {
	if (call->ixVCall == VecIdecVCall::CALLIDECTOU_MISEQ) {
		call->abort = handleCallIdecTou_misEq(dbsidec, call->jref, call->argInv.ref, call->argRet.boolval);
	} else if (call->ixVCall == VecIdecVCall::CALLIDECTOUUPD_REFEQ) {
		call->abort = handleCallIdecTouUpd_refEq(dbsidec, call->jref, call->argInv.ref);
	};
};

bool PnlIdecTouDetail::handleCallIdecTou_misEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
			, bool& boolvalRet
		) {
	bool retval = false;
	// IP handleCallIdecTou_misEq --- BEGIN
	boolvalRet = (recTou.refIdecMMission == refInv);
	// IP handleCallIdecTou_misEq --- END
	return retval;
};

bool PnlIdecTouDetail::handleCallIdecTouUpd_refEq(
			DbsIdec* dbsidec
			, const ubigint jrefTrig
			, const ubigint refInv
		) {
	bool retval = false;
	// IP handleCallIdecTouUpd_refEq --- INSERT
	return retval;
};

